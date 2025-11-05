import {
  deserializeWorkflow,
  createNodeFactory,
  type VersionedWorkflowConfig,
} from './serializer'
import { SCHEMA_VERSION } from '@/lib/schemas'
import {
  NodeType,
  NodeCategory,
  type BacnetConfig,
} from '@/types/infrastructure'
import { ConstantNode } from '@/lib/data-nodes/constant-node'
import { AnalogInputNode } from '@/lib/data-nodes/analog-input-node'

describe('WorkflowSerializer factory compatibility', () => {
  const mockMqttBus = { pointBulkStream$: { subscribe: jest.fn() } }
  const mockOnDataChange = jest.fn()
  const nodeFactory = createNodeFactory({
    mqttBus: mockMqttBus as any,
    onDataChange: mockOnDataChange,
  })

  function versionedOf(
    data: VersionedWorkflowConfig['data']
  ): VersionedWorkflowConfig {
    return {
      schema_info: {
        version: SCHEMA_VERSION,
        compatibility: '>=1.0.0',
        schema_name: 'WorkflowConfig',
        generated_at: '2025-09-19T10:30:00Z',
      },
      data,
    }
  }

  it('deserializes ConstantNode when nodeType is enum value', () => {
    const config = versionedOf({
      metadata: { lastModified: '2025-09-19T10:30:00Z' },
      nodes: [
        {
          id: 'n1',
          type: 'logic.constant',
          position: { x: 0, y: 0 },
          data: {
            nodeType: NodeType.CONSTANT,
            serializedData: {
              id: 'n1',
              type: NodeType.CONSTANT,
              category: NodeCategory.LOGIC,
              label: 'C',
              metadata: { value: 10, valueType: 'number' },
            },
          },
        },
      ],
      edges: [],
    })

    const result = deserializeWorkflow({
      versionedConfig: config,
      mqttBus: mockMqttBus as any,
      onDataChange: mockOnDataChange,
    })
    expect(result.nodes[0].data).toBeInstanceOf(ConstantNode)
  })

  it('deserializes ConstantNode when nodeType is enum string', () => {
    const config = versionedOf({
      metadata: { lastModified: '2025-09-19T10:30:00Z' },
      nodes: [
        {
          id: 'n1',
          type: 'logic.constant',
          position: { x: 0, y: 0 },
          data: {
            nodeType: 'constant',
            serializedData: {
              id: 'n1',
              type: NodeType.CONSTANT,
              category: NodeCategory.LOGIC,
              label: 'C',
              metadata: { value: true, valueType: 'boolean' },
            },
          },
        },
      ],
      edges: [],
    })

    const result = deserializeWorkflow({
      versionedConfig: config,
      mqttBus: mockMqttBus as any,
      onDataChange: mockOnDataChange,
    })
    expect(result.nodes[0].data).toBeInstanceOf(ConstantNode)
  })

  it('deserializes AnalogInputNode for enum-string nodeType', () => {
    const metadata: BacnetConfig = {
      pointId: 'pid-1',
      objectType: 'analog-input',
      objectId: 7,
      supervisorId: 'sup-1',
      controllerId: 'ctl-1',
      name: 'Temp',
      discoveredProperties: { presentValue: 21.5 },
    }

    const cfgEnum = versionedOf({
      metadata: { lastModified: '2025-09-19T10:30:00Z' },
      nodes: [
        {
          id: 'n2',
          type: 'bacnet.analog-input',
          position: { x: 0, y: 0 },
          data: {
            nodeType: NodeType.ANALOG_INPUT,
            serializedData: {
              id: 'n2',
              type: NodeType.ANALOG_INPUT,
              category: NodeCategory.BACNET,
              label: 'AI2',
              metadata,
            },
          },
        },
      ],
      edges: [],
    })

    const r2 = deserializeWorkflow({
      versionedConfig: cfgEnum,
      mqttBus: mockMqttBus as any,
      onDataChange: mockOnDataChange,
    })

    expect(r2.nodes[0].data).toBeInstanceOf(AnalogInputNode)
  })
})
