import {
  DataNode,
  NodeCategory,
  NodeDirection,
  NodeType,
  generateInstanceId,
  ControlSequenceNode,
  ComputeValue,
} from '@/types/infrastructure'
import type {
  ControlSequenceInputHandle,
  ControlSequenceOutputHandle,
  SequenceType,
  InputCategory,
  OutputCategory,
  ConditionalLabel,
} from '@/domains/control-sequence'
import { Message, SendCallback } from '@/lib/message-system/types'
import {
  createMessageBuffer,
  MessageBuffer,
} from '@/lib/message-system/message-buffer'
import { v4 as uuidv4 } from 'uuid'
import { makeSerializable } from '@/lib/workflow/serialization-utils'
import { deleteFmu } from '@/domains/control-sequence/api/client'
import { toComputeValue } from './utils/compute-value-utils'

const DEFAULT_STEP_SIZE = 1.0

export interface ControlSequenceHandles {
  allInputs: readonly ControlSequenceInputHandle[]
  allOutputs: readonly ControlSequenceOutputHandle[]
  requiredInputs: readonly ControlSequenceInputHandle[]
  visibleInputs: ControlSequenceInputHandle[]
  visibleOutputs: ControlSequenceOutputHandle[]
  parameterControlledInputs: readonly ControlSequenceInputHandle[]
  inputCategories: Record<InputCategory, ControlSequenceInputHandle[]>
  outputCategories: Record<OutputCategory, ControlSequenceOutputHandle[]>
  conditionalLabels: readonly ConditionalLabel<
    ControlSequenceInputHandle | ControlSequenceOutputHandle,
    Record<string, unknown>
  >[]
}

export type ComputedOutputs = Record<string, ComputeValue>

export interface BaseControlSequenceMetadata {
  instanceId: string
  label?: string
  handles: ControlSequenceHandles
  badgeLabel: string
  defaultLabel: string
  computedOutputs?: ComputedOutputs
  inputValues?: Record<string, unknown>
  parameters?: Record<string, unknown>
}

export abstract class BaseControlSequenceNode implements ControlSequenceNode {
  readonly id: string
  readonly category = NodeCategory.CONTROL_SEQUENCE
  readonly label: string
  readonly direction = NodeDirection.BIDIRECTIONAL

  readonly instanceId: string
  readonly badgeLabel: string
  readonly defaultLabel: string
  handles: ControlSequenceHandles

  protected messageBuffer: MessageBuffer<ControlSequenceInputHandle>
  protected stepSize: number = DEFAULT_STEP_SIZE
  private sendCallback?: SendCallback<ControlSequenceOutputHandle>
  private _computedOutputs?: ComputedOutputs
  private _inputValues: Record<string, unknown> = {}
  private _parameters: Record<string, unknown> = {}

  abstract readonly type: NodeType
  abstract readonly sequenceType: SequenceType

  get metadata(): BaseControlSequenceMetadata {
    return {
      instanceId: this.instanceId,
      label: this.label,
      handles: this.handles,
      badgeLabel: this.badgeLabel,
      defaultLabel: this.defaultLabel,
      computedOutputs: this._computedOutputs,
      inputValues: this._inputValues,
      parameters: this._parameters,
    }
  }

  constructor(config: BaseControlSequenceMetadata, id?: string) {
    this.id = id ?? generateInstanceId()
    this.instanceId = config.instanceId
    this.label = config.label ?? ''
    this.badgeLabel = config.badgeLabel
    this.defaultLabel = config.defaultLabel
    this.handles = {
      ...config.handles,
      visibleInputs: [...config.handles.visibleInputs],
      visibleOutputs: [...config.handles.visibleOutputs],
    }
    this._parameters = config.parameters ?? {}
    this.messageBuffer = createMessageBuffer<ControlSequenceInputHandle>()
  }

  getInputHandles(): readonly ControlSequenceInputHandle[] {
    return this.handles.allInputs
  }

  getOutputHandles(): readonly ControlSequenceOutputHandle[] {
    return this.handles.allOutputs
  }

  canConnectWith(target: DataNode): boolean {
    return target.direction !== NodeDirection.OUTPUT
  }

  setSendCallback(callback: SendCallback<ControlSequenceOutputHandle>): void {
    this.sendCallback = callback
  }

  private async send(
    message: Message,
    handle: ControlSequenceOutputHandle
  ): Promise<void> {
    if (this.sendCallback) {
      await this.sendCallback(message, this.id, handle)
    }
  }

  setVisibleInputs(inputs: ControlSequenceInputHandle[]): void {
    const missingRequired = this.handles.requiredInputs.filter(
      (h) => !inputs.includes(h)
    )
    if (missingRequired.length > 0) {
      throw new Error(
        `Cannot remove required inputs: ${missingRequired.join(', ')}`
      )
    }
    this.handles = { ...this.handles, visibleInputs: inputs }
  }

  setVisibleOutputs(outputs: ControlSequenceOutputHandle[]): void {
    this.handles = { ...this.handles, visibleOutputs: outputs }
  }

  setParameters(params: Record<string, unknown>): void {
    this._parameters = params
  }

  async receive(
    message: Message,
    handle: ControlSequenceInputHandle,
    fromNodeId: string
  ): Promise<void> {
    console.log(
      `🔧 [${this.sequenceType} ${this.id}] Received on ${handle} from ${fromNodeId}:`,
      message.payload
    )

    this.messageBuffer.set(handle, message)

    if (this.messageBuffer.hasAll(this.handles.requiredInputs)) {
      console.log(
        `✅ [${this.id}] All required inputs received, executing step...`
      )

      const inputs = this.messageBuffer.collectValues()
      this._inputValues = inputs
      const outputs = await this.executeStepApi(inputs)
      await this.emitOutputs(outputs)

      this.messageBuffer.clear()
    } else {
      console.log(`⏳ [${this.id}] Waiting for more inputs...`)
    }
  }

  protected abstract executeStepApi(
    inputs: Record<string, unknown>
  ): Promise<Record<string, unknown>>

  private async emitOutputs(outputs: Record<string, unknown>): Promise<void> {
    const computedOutputs: ComputedOutputs = {}

    for (const handle of this.handles.allOutputs) {
      const payload = toComputeValue(outputs[handle])
      if (payload) {
        computedOutputs[handle] = payload
        await this.send(
          {
            payload,
            _msgid: uuidv4(),
            timestamp: Date.now(),
            metadata: { source: this.id, type: this.type },
          },
          handle
        )
      }
    }

    this._computedOutputs = computedOutputs
  }

  reset(): void {
    this.messageBuffer.clear()
  }

  toSerializable(): Record<string, unknown> {
    return makeSerializable({
      id: this.id,
      type: this.type,
      category: this.category,
      label: this.label,
      metadata: {
        instanceId: this.instanceId,
        visibleInputs: this.handles.visibleInputs,
        visibleOutputs: this.handles.visibleOutputs,
      },
    })
  }

  async cleanup(): Promise<void> {
    await deleteFmu(this.instanceId)
  }
}
