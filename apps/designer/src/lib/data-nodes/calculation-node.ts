import {
  LogicNode,
  CalculationInputHandle,
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

export type CalculationOperation =
  | 'add'
  | 'subtract'
  | 'multiply'
  | 'divide'
  | 'average'

export class CalculationNode
  implements LogicNode<CalculationInputHandle, LogicOutputHandle>
{
  readonly id: string
  readonly type = NodeType.CALCULATION
  readonly category = NodeCategory.LOGIC
  readonly label: string
  readonly direction = NodeDirection.BIDIRECTIONAL
  readonly metadata: { operation: CalculationOperation }

  // Private internal state
  private _computedValue?: number
  private _inputValues: ComputeValue[] = []
  private sendCallback?: SendCallback<LogicOutputHandle>
  private messageBuffer: MessageBuffer<CalculationInputHandle>

  get computedValue(): number | undefined {
    return this._computedValue
  }

  get inputValues(): ComputeValue[] {
    return this._inputValues
  }

  constructor(label: string, operation: CalculationOperation, id?: string) {
    this.id = id || generateInstanceId()
    this.label = label
    this.metadata = { operation }
    this.messageBuffer = createMessageBuffer<CalculationInputHandle>()
  }

  getValue(): ComputeValue | undefined {
    if (this._computedValue === undefined) return undefined
    return {
      value: this._computedValue,
      type: 'number',
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

  private execute(inputs: ComputeValue[]): number {
    // Convert to numbers using helper
    const num1 = toNumber(inputs[0])
    const num2 = toNumber(inputs[1])

    let result: number
    switch (this.metadata.operation) {
      case 'add':
        result = num1 + num2
        break
      case 'subtract':
        result = num1 - num2
        break
      case 'multiply':
        result = num1 * num2
        break
      case 'divide':
        result = num2 !== 0 ? num1 / num2 : NaN
        break
      case 'average':
        result = (num1 + num2) / 2
        break
      default:
        result = NaN
    }

    this._inputValues = inputs
    this._computedValue = result
    return result
  }

  canConnectWith(target: DataNode): boolean {
    // Logic nodes can connect to other logic nodes or outputs
    // Cannot connect to pure input nodes
    return target.direction !== NodeDirection.OUTPUT
  }

  getInputHandles(): readonly CalculationInputHandle[] {
    return ['input1', 'input2'] as const
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
    handle: CalculationInputHandle,
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
      console.log(`✅ [${this.id}] All inputs received, processing...`)

      const inputs: ComputeValue[] = requiredHandles.map(
        (h) =>
          this.messageBuffer.get(h)?.payload ?? { value: 0, type: 'number' }
      )

      const result = this.execute(inputs)

      console.log(
        `🧮 [${this.id}] Computed:`,
        inputs[0],
        this.metadata.operation,
        inputs[1],
        '=',
        result
      )

      await this.send(
        {
          payload: { value: result, type: 'number' },
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
    const metadata: { operation: CalculationOperation } = this.metadata
    return makeSerializable<
      { operation: CalculationOperation },
      NodeType.CALCULATION,
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
