import {
  LogicNode,
  ComparisonInputHandle,
  LogicOutputHandle,
  ComputeValue,
  NodeCategory,
  NodeType,
  NodeDirection,
  generateInstanceId,
  DataNode,
} from '@/types/infrastructure'
import { Message, SendCallback } from '@/lib/message-system/types'
import {
  createMessageBuffer,
  MessageBuffer,
} from '@/lib/message-system/message-buffer'
import { v4 as uuidv4 } from 'uuid'
import { makeSerializable } from '@/lib/workflow/serialization-utils'
import { toNumber } from './utils/bacnet-utils'

export type ComparisonOperation =
  | 'equals'
  | 'greater'
  | 'less'
  | 'greater-equal'
  | 'less-equal'

export class ComparisonNode
  implements LogicNode<ComparisonInputHandle, LogicOutputHandle>
{
  readonly id: string
  readonly type = NodeType.COMPARISON
  readonly category = NodeCategory.LOGIC
  readonly label: string
  readonly direction = NodeDirection.BIDIRECTIONAL
  readonly metadata: { operation: ComparisonOperation }

  // Private internal state
  private _computedValue?: boolean
  private _inputValues: ComputeValue[] = []
  private sendCallback?: SendCallback<LogicOutputHandle>
  private messageBuffer: MessageBuffer<ComparisonInputHandle>

  // Public getters for UI access
  get computedValue(): boolean | undefined {
    return this._computedValue
  }

  get inputValues(): ComputeValue[] {
    return this._inputValues
  }

  constructor(label: string, operation: ComparisonOperation, id?: string) {
    this.id = id || generateInstanceId()
    this.label = label
    this.metadata = { operation }
    this.messageBuffer = createMessageBuffer<ComparisonInputHandle>()
  }

  getValue(): ComputeValue | undefined {
    if (this._computedValue === undefined) return undefined
    return {
      value: this._computedValue,
      type: 'boolean',
    }
  }

  getInputValues(): ComputeValue[] {
    return this._inputValues
  }

  reset(): void {
    this._computedValue = undefined
    this._inputValues = []
    this.messageBuffer.clear()
  }

  private execute(inputs: ComputeValue[]): boolean {
    const v1 = inputs[0]
    const v2 = inputs[1]

    if (v1 === undefined || v2 === undefined) {
      this._inputValues = inputs
      this._computedValue = false
      return false
    }

    const num1 = toNumber(v1)
    const num2 = toNumber(v2)

    let result: boolean
    switch (this.metadata.operation) {
      case 'equals':
        result = num1 === num2
        break
      case 'greater':
        result = num1 > num2
        break
      case 'less':
        result = num1 < num2
        break
      case 'greater-equal':
        result = num1 >= num2
        break
      case 'less-equal':
        result = num1 <= num2
        break
      default:
        result = false
    }

    this._inputValues = inputs
    this._computedValue = result
    return result
  }

  canConnectWith(target: DataNode): boolean {
    // Logic nodes can connect to other logic nodes or outputs
    return target.direction !== NodeDirection.OUTPUT
  }

  getInputHandles(): readonly ComparisonInputHandle[] {
    return ['value1', 'value2'] as const
  }

  getOutputHandles(): readonly LogicOutputHandle[] {
    return ['output'] as const
  }

  // Message passing API implementation
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
    message: Message,
    handle: ComparisonInputHandle,
    fromNodeId: string
  ): Promise<void> {
    console.log(
      `📥 [${this.id}] Received on ${handle}:`,
      message.payload,
      `from ${fromNodeId}`
    )

    this.messageBuffer.set(handle, message)

    const requiredHandles = this.getInputHandles()

    if (this.messageBuffer.hasAll(requiredHandles)) {
      console.log(
        `✅ [${this.id}] All inputs received, processing comparison...`
      )

      const inputs: ComputeValue[] = requiredHandles.map(
        (h) =>
          this.messageBuffer.get(h)?.payload ?? { value: 0, type: 'number' }
      )

      const result = this.execute(inputs)

      console.log(
        `🔍 [${this.id}] Compared:`,
        inputs[0],
        `(${typeof inputs[0]})`,
        this.metadata.operation,
        inputs[1],
        `(${typeof inputs[1]})`,
        '=',
        result
      )
      console.log(
        `🔍 [${this.id}] Raw comparison: ${inputs[0]} === ${inputs[1]} = ${
          inputs[0] === inputs[1]
        }`
      )

      await this.send(
        {
          payload: { value: result, type: 'boolean' },
          _msgid: uuidv4(),
          timestamp: Date.now(),
          metadata: { source: this.id, operation: this.metadata.operation },
        },
        'output'
      )

      this.messageBuffer.clear()
    } else {
      console.log(`⏳ [${this.id}] Waiting for more inputs...`)
    }
  }

  toSerializable(): Record<string, unknown> {
    const metadata: { operation: ComparisonOperation } = this.metadata
    return makeSerializable<
      { operation: ComparisonOperation },
      NodeType.COMPARISON,
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
