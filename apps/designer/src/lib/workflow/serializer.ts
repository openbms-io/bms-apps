import { z } from 'zod'
import { Node, Edge } from '@xyflow/react'
import { getVersionMetadata } from '@/lib/schemas'
import {
  WorkflowConfigSchema as StrictWorkflowConfigSchema,
  VersionedWorkflowConfigSchema as StrictVersionedWorkflowConfigSchema,
} from '@/lib/workflow/config-schema'
import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'
import {
  serializeNodeData,
  deserializeNodeData,
  type SerializedNodeData,
} from '../node-serializer'
import factory from '@/lib/data-nodes/factory'
import { type ConstantNodeMetadata } from '@/lib/data-nodes/constant-node'
import { type CalculationOperation } from '@/lib/data-nodes/calculation-node'
import { type ComparisonOperation } from '@/lib/data-nodes/comparison-node'
import { type DayOfWeek } from '@/lib/data-nodes/schedule-node'
import { type FunctionNodeMetadata } from '@/lib/data-nodes/function-node'
import { type TimerNodeMetadata } from '@/lib/data-nodes/timer-node'
import { type ScheduleNodeMetadata } from '@/lib/data-nodes/schedule-node'
import { type BacnetConfig, NodeType } from '@/types/infrastructure'
import { type SwitchNodeMetadata } from '@/lib/data-nodes/switch-node'
import { MqttBusManager } from '@/lib/mqtt/mqtt-bus'

export interface WorkflowMetadata {
  readonly lastModified: string
  readonly createdBy?: string
  readonly description?: string
}

export interface SerializedNode {
  readonly id: string
  readonly type: string
  readonly position: { readonly x: number; readonly y: number }
  readonly data: SerializedNodeData
}

export interface WorkflowConfig {
  readonly metadata: WorkflowMetadata
  readonly nodes: SerializedNode[]
  readonly edges: Edge[]
}

export interface ReactFlowObject {
  readonly nodes: Node<Record<string, unknown>>[]
  readonly edges: Edge[]
  readonly viewport: {
    readonly x: number
    readonly y: number
    readonly zoom: number
  }
}

export interface DeserializedWorkflowState {
  readonly nodes: Node<Record<string, unknown>>[]
  readonly edges: Edge[]
  readonly metadata: WorkflowMetadata
}

export interface ValidationResult {
  readonly isValid: boolean
  readonly errors: string[]
}

export type VersionedWorkflowConfig = ValidatedWorkflowConfig

export function createWorkflowConfig({
  nodes,
  edges,
  metadata,
}: {
  readonly nodes: Node<Record<string, unknown>>[]
  readonly edges: Edge[]
  readonly metadata: WorkflowMetadata
}): WorkflowConfig {
  const serializedNodes: SerializedNode[] = nodes.map((node) => ({
    id: node.id,
    type: node.type || 'unknown',
    position: node.position,
    data: serializeNodeData(node.data),
  }))

  return {
    metadata,
    nodes: serializedNodes,
    edges,
  }
}

export function serializeWorkflow({
  reactFlowObject,
  metadata,
}: {
  readonly reactFlowObject: ReactFlowObject
  readonly metadata: WorkflowMetadata
}): VersionedWorkflowConfig {
  const workflowConfig = createWorkflowConfig({
    nodes: reactFlowObject.nodes,
    edges: reactFlowObject.edges,
    metadata,
  })

  const versionMetadata = getVersionMetadata('WorkflowConfig')

  return {
    schema_info: versionMetadata,
    data: workflowConfig,
  } as VersionedWorkflowConfig
}

export function deserializeWorkflow({
  versionedConfig,
  mqttBus,
  onDataChange,
}: {
  readonly versionedConfig: VersionedWorkflowConfig
  mqttBus: MqttBusManager
  onDataChange: () => void
}): DeserializedWorkflowState {
  const { data } = versionedConfig
  const nodeFactory = createNodeFactory({ mqttBus, onDataChange })

  const deserializedNodes: Node<Record<string, unknown>>[] = data.nodes.map(
    (serializedNode) => {
      return {
        id: serializedNode.id,
        type: serializedNode.type,
        position: serializedNode.position,
        data: nodeFactory(
          serializedNode.data.nodeType,
          serializedNode.data.serializedData
        ) as Record<string, unknown>,
      }
    }
  )

  return {
    nodes: deserializedNodes,
    edges: data.edges,
    metadata: data.metadata,
  }
}

export function validateWorkflowConfig({
  config,
}: {
  readonly config: unknown
}): ValidationResult {
  try {
    StrictWorkflowConfigSchema.parse(config)
    return {
      isValid: true,
      errors: [],
    }
  } catch (error) {
    if (error instanceof z.ZodError) {
      const errors = error.issues.map((issue) => {
        const path = issue.path.join('.')
        return `${path}: ${issue.message}`
      })
      return {
        isValid: false,
        errors,
      }
    }

    return {
      isValid: false,
      errors: ['Unknown validation error'],
    }
  }
}

export function validateVersionedWorkflowConfig({
  versionedConfig,
}: {
  readonly versionedConfig: unknown
}): ValidationResult {
  try {
    StrictVersionedWorkflowConfigSchema.parse(versionedConfig)
    return {
      isValid: true,
      errors: [],
    }
  } catch (error) {
    if (error instanceof z.ZodError) {
      const errors = error.issues.map((issue) => {
        const path = issue.path.join('.')
        return `${path}: ${issue.message}`
      })
      return {
        isValid: false,
        errors,
      }
    }

    return {
      isValid: false,
      errors: ['Unknown validation error'],
    }
  }
}

export function serializeFromReactFlowObject({
  toObjectResult,
  metadata,
}: {
  readonly toObjectResult: ReactFlowObject
  readonly metadata: WorkflowMetadata
}): VersionedWorkflowConfig {
  return serializeWorkflow({
    reactFlowObject: toObjectResult,
    metadata,
  })
}

export function createNodeFactory({
  mqttBus,
  onDataChange,
}: {
  mqttBus: MqttBusManager
  onDataChange: () => void
}) {
  return function nodeFactory(
    nodeType: NodeType,
    data: Record<string, unknown>
  ): unknown {
    switch (nodeType) {
      // Logic nodes (enum string values)
      case 'constant':
        return factory.createConstantNode({
          label: data.label as string,
          value: (data.metadata as ConstantNodeMetadata)?.value,
          valueType: (data.metadata as ConstantNodeMetadata)?.valueType,
          id: data.id as string,
        })
      case 'calculation':
        return factory.createCalculationNode({
          label: data.label as string,
          operation: (data.metadata as { operation: CalculationOperation })
            ?.operation,
          id: data.id as string,
        })
      case 'comparison':
        return factory.createComparisonNode({
          label: data.label as string,
          operation: (data.metadata as { operation: ComparisonOperation })
            ?.operation,
          id: data.id as string,
        })
      case 'write-setpoint':
        return factory.createWriteSetpointNode({
          label: data.label as string,
          priority: (data.metadata as { priority: number })?.priority,
          id: data.id as string,
        })
      case 'switch':
        const switchMeta = data.metadata as SwitchNodeMetadata
        return factory.createSwitchNode({
          label: data.label as string,
          condition: switchMeta?.condition,
          threshold: switchMeta?.threshold,
          activeLabel: switchMeta?.activeLabel,
          inactiveLabel: switchMeta?.inactiveLabel,
          id: data.id as string,
        })
      case 'timer':
        const timerMeta = data.metadata as TimerNodeMetadata
        return factory.createTimerNode({
          label: data.label as string,
          duration: timerMeta?.duration,
          id: data.id as string,
        })
      case 'schedule':
        const scheduleMeta = data.metadata as ScheduleNodeMetadata
        return factory.createScheduleNode({
          label: data.label as string,
          startTime: scheduleMeta?.startTime,
          endTime: scheduleMeta?.endTime,
          days: scheduleMeta?.days as DayOfWeek[],
          id: data.id as string,
        })
      case 'function':
        const fnMeta = data.metadata as FunctionNodeMetadata
        return factory.createFunctionNode({
          label: data.label as string,
          code: fnMeta?.code,
          inputs: fnMeta?.inputs,
          timeout: fnMeta?.timeout,
          id: data.id as string,
        })
      case 'analog-input':
      case 'analog-output':
      case 'analog-value':
      case 'binary-input':
      case 'binary-output':
      case 'binary-value':
      case 'multi-state-input':
      case 'multi-state-output':
      case 'multi-state-value': {
        const metadata = data.metadata as BacnetConfig & {
          semanticMappingKey?: string
        }
        return factory.createDataNodeFromBacnetConfig({
          config: metadata,
          mqttBus,
          onDataChange,
          id: data.id as string,
          semanticMappingKey: metadata.semanticMappingKey,
        })
      }
      default:
        throw new Error(`Unknown node type: ${nodeType}`)
    }
  }
}
