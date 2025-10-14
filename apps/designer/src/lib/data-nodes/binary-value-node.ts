import {
  DataNode,
  NodeCategory,
  NodeDirection,
  NodeType,
  BacnetConfig,
  BacnetInputOutput,
  generateInstanceId,
  BacnetInputHandle,
  BacnetOutputHandle,
} from '@/types/infrastructure'
import {
  BacnetProperties,
  getPropertyMetadata,
} from '@/types/bacnet-properties'
import { Message, SendCallback } from '@/lib/message-system/types'
import { v4 as uuidv4 } from 'uuid'
import { convertToComputeValue } from './bacnet-utils'
import { makeSerializable } from '@/lib/workflow/serialization-utils'

export class BinaryValueNode implements BacnetInputOutput {
  // From BacnetConfig
  readonly pointId: string
  readonly objectType = 'binary-value' as const
  readonly objectId: number
  readonly supervisorId: string
  readonly controllerId: string
  discoveredProperties: BacnetProperties
  readonly name?: string
  readonly position?: { x: number; y: number }

  // From DataNode
  readonly id: string
  readonly type = NodeType.BINARY_VALUE
  readonly category = NodeCategory.BACNET
  readonly label: string
  readonly direction = NodeDirection.BIDIRECTIONAL
  private sendCallback?: SendCallback<BacnetOutputHandle>

  constructor(config: BacnetConfig, id?: string) {
    // Copy all BacnetConfig properties
    this.pointId = config.pointId
    this.objectId = config.objectId
    this.supervisorId = config.supervisorId
    this.controllerId = config.controllerId
    this.discoveredProperties = {
      ...config.discoveredProperties,
    }
    this.name = config.name
    this.position = config.position

    // DataNode properties
    this.id = id ?? generateInstanceId() // Generate unique UUID for each instance
    this.label = config.name || ''
  }

  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  canConnectWith(target: DataNode): boolean {
    // Value nodes can connect bidirectionally
    return true
  }

  toSerializable() {
    const metadata: BacnetConfig = {
      pointId: this.pointId,
      objectType: this.objectType,
      objectId: this.objectId,
      supervisorId: this.supervisorId,
      controllerId: this.controllerId,
      name: this.name,
      discoveredProperties: this.discoveredProperties,
      position: this.position,
    }
    return makeSerializable<
      BacnetConfig,
      NodeType.BINARY_VALUE,
      NodeCategory.BACNET
    >({
      id: this.id,
      type: this.type,
      category: this.category,
      label: this.label,
      metadata,
    })
  }

  getInputHandles(): readonly BacnetInputHandle[] {
    const handles: BacnetInputHandle[] = []
    for (const [property, value] of Object.entries(this.discoveredProperties)) {
      if (value !== undefined) {
        const metadata = getPropertyMetadata(
          this.objectType,
          property as BacnetInputHandle
        )
        if (metadata?.writable) {
          handles.push(property as BacnetInputHandle)
        }
      }
    }
    return handles
  }

  getOutputHandles(): readonly BacnetOutputHandle[] {
    const handles: BacnetOutputHandle[] = []
    for (const [property, value] of Object.entries(this.discoveredProperties)) {
      if (value !== undefined) {
        const metadata = getPropertyMetadata(
          this.objectType,
          property as BacnetOutputHandle
        )
        if (metadata?.readable) {
          handles.push(property as BacnetOutputHandle)
        }
      }
    }
    return handles
  }

  // Message passing API implementation
  setSendCallback(callback: SendCallback<BacnetOutputHandle>): void {
    this.sendCallback = callback
  }

  private async send(
    message: Message,
    handle: BacnetOutputHandle
  ): Promise<void> {
    if (this.sendCallback) {
      await this.sendCallback(message, this.id, handle)
    }
  }

  async receive(
    message: Message,
    handle: BacnetInputHandle,
    fromNodeId: string
  ): Promise<void> {
    const inputHandles = this.getInputHandles()

    if (inputHandles.includes(handle)) {
      // Write to a writable property
      console.log(
        `🟢 [${this.id}] BinaryValue received write to ${handle}:`,
        message.payload,
        `from ${fromNodeId}`
      )

      // Update the property value locally for UI updates
      // NOTE: Currently focusing on top-level properties only. Nested properties are not spread correctly.
      this.discoveredProperties = {
        ...this.discoveredProperties,
        [handle]: message.payload,
      }

      // Send the updated value downstream
      await this.send(
        {
          payload: message.payload,
          _msgid: uuidv4(),
          timestamp: Date.now(),
        },
        handle
      )
    } else {
      // Trigger - send all readable property values
      console.log(`🟢 [${this.id}] BinaryValue triggered from ${fromNodeId}`)

      const outputHandles = this.getOutputHandles()
      for (const propertyHandle of outputHandles) {
        const currentValue = this.discoveredProperties[propertyHandle]
        if (currentValue !== undefined) {
          await this.send(
            {
              payload: convertToComputeValue(currentValue) || 0,
              _msgid: uuidv4(),
              timestamp: Date.now(),
            },
            propertyHandle
          )
        }
      }
    }
  }
}
