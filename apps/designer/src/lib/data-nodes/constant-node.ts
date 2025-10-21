import {
  DataNode,
  LogicNode,
  LogicOutputHandle,
  ComputeValue,
  NodeCategory,
  NodeType,
  NodeDirection,
  generateInstanceId,
} from '@/types/infrastructure'
import { Message, SendCallback } from '@/lib/message-system/types'
import { v4 as uuidv4 } from 'uuid'
import { makeSerializable } from '@/lib/workflow/serialization-utils'

export type ValueType = 'number' | 'boolean' | 'string'

export interface ConstantNodeMetadata {
  value: number | boolean | string
  valueType: ValueType
}

export class ConstantNode implements LogicNode<never, LogicOutputHandle> {
  readonly id: string
  readonly type = NodeType.CONSTANT
  readonly category = NodeCategory.LOGIC
  readonly label: string
  readonly direction = NodeDirection.OUTPUT

  private _metadata: ConstantNodeMetadata
  private sendCallback?: SendCallback<LogicOutputHandle>

  get metadata(): ConstantNodeMetadata {
    return this._metadata
  }

  get computedValue(): ComputeValue | undefined {
    return {
      value: this._metadata.value,
      type: this._metadata.valueType,
    }
  }

  constructor(
    label: string,
    value: number | boolean | string = 0,
    valueType: ValueType = 'number',
    id?: string
  ) {
    this.id = id ?? generateInstanceId()
    this.label = label
    this._metadata = { value, valueType }
  }

  getValue(): ComputeValue | undefined {
    return {
      value: this._metadata.value,
      type: this._metadata.valueType,
    }
  }

  canConnectWith(target: DataNode): boolean {
    return target.direction !== NodeDirection.OUTPUT
  }

  // Constants have no inputs
  getInputHandles(): readonly never[] {
    return [] as const
  }

  getOutputHandles(): readonly LogicOutputHandle[] {
    return ['output'] as const
  }

  setValue(value: number | boolean | string): void {
    this._metadata = { ...this._metadata, value }
  }

  setValueType(valueType: ValueType): void {
    let newValue: number | boolean | string
    switch (valueType) {
      case 'number':
        newValue = 0
        break
      case 'boolean':
        newValue = false
        break
      case 'string':
        newValue = ''
        break
    }

    this._metadata = { valueType, value: newValue }
  }

  setSendCallback(callback: SendCallback<LogicOutputHandle>): void {
    this.sendCallback = callback
  }

  private async send(
    message: Message,
    handle: LogicOutputHandle
  ): Promise<void> {
    if (this.sendCallback) {
      await this.sendCallback(message, this.id, handle)
    }
  }

  async receive(
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    _message: Message,
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    _handle: never,
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    _fromNodeId: string
  ): Promise<void> {
    await this.trigger()
  }

  private async trigger(): Promise<void> {
    const computeValue = this.getValue()
    if (computeValue !== undefined) {
      console.log(
        `🔢 [${this.id}] Triggered, sending constant value:`,
        computeValue
      )
      await this.send(
        {
          payload: computeValue,
          _msgid: uuidv4(),
          timestamp: Date.now(),
          metadata: { source: this.id, type: this.type },
        },
        'output'
      )
    }
  }

  toSerializable(): Record<string, unknown> {
    const metadata: ConstantNodeMetadata = {
      value: this._metadata.value,
      valueType: this._metadata.valueType,
    }

    return makeSerializable<
      ConstantNodeMetadata,
      NodeType.CONSTANT,
      NodeCategory.LOGIC
    >({
      id: this.id,
      type: this.type,
      category: this.category,
      label: this.label,
      metadata,
    })
  }
}
