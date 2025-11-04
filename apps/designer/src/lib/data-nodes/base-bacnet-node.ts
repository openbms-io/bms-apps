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
  convertStatusFlagsToIndividualProperties,
} from '@/types/infrastructure'
import {
  BacnetProperties,
  getPropertyMetadata,
} from '@/types/bacnet-properties'
import { Message, SendCallback } from '@/lib/message-system/types'
import { v4 as uuidv4 } from 'uuid'
import {
  toComputeValueWithParsing,
  convertMultistatePresentValue,
} from './bacnet-utils'
import { makeSerializable } from '@/lib/workflow/serialization-utils'
import { Subscription } from 'rxjs'
import { MqttBusManager } from '@/lib/mqtt/mqtt-bus'
import { PointBulkPayload, ControllerPoint } from 'mqtt-topics'
import type { SemanticEquipment } from '@/domains/building-semantics/schemas'

export abstract class BaseBacnetNode implements BacnetInputOutput {
  // From BacnetConfig
  readonly pointId: string
  readonly objectId: number
  readonly supervisorId: string
  readonly controllerId: string
  discoveredProperties: BacnetProperties
  readonly name?: string
  readonly position?: { x: number; y: number }

  // 223P composite key for lookup
  readonly semanticMappingKey?: string

  // From DataNode
  readonly id: string
  readonly category = NodeCategory.BACNET
  readonly label: string
  private sendCallback?: SendCallback<BacnetOutputHandle>

  // MQTT live data
  private mqttSubscription?: Subscription
  private onDataChange: () => void

  // Subclasses must provide these
  abstract readonly objectType: BacnetConfig['objectType']
  abstract readonly type: NodeType
  abstract readonly direction: NodeDirection

  constructor(params: {
    config: BacnetConfig
    mqttBus: MqttBusManager
    onDataChange: () => void
    id?: string
    semanticMappingKey?: string
  }) {
    const { config, id, mqttBus, onDataChange } = params

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

    // 223P composite key
    this.semanticMappingKey = params.semanticMappingKey

    // DataNode properties
    this.id = id ?? generateInstanceId()
    this.label = config.name || ''

    // MQTT setup
    this.onDataChange = onDataChange
    this.subscribeToMqttBulk(mqttBus)
  }

  abstract canConnectWith(target: DataNode): boolean

  toSerializable() {
    const metadata: BacnetConfig & { semanticMappingKey?: string } = {
      pointId: this.pointId,
      objectType: this.objectType,
      objectId: this.objectId,
      supervisorId: this.supervisorId,
      controllerId: this.controllerId,
      name: this.name,
      discoveredProperties: this.discoveredProperties,
      position: this.position,
    }

    if (this.semanticMappingKey) {
      metadata.semanticMappingKey = this.semanticMappingKey
    }

    return makeSerializable({
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
        `[${this.id}] ${this.objectType} received write to ${handle}:`,
        message.payload,
        `from ${fromNodeId}`
      )

      // Update the property value locally for UI updates
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
      console.log(
        `[${this.id}] ${this.objectType} triggered from ${fromNodeId}`
      )

      const outputHandles = this.getOutputHandles()
      for (const propertyHandle of outputHandles) {
        const currentValue = this.discoveredProperties[propertyHandle]
        if (currentValue !== undefined) {
          const computeValue = toComputeValueWithParsing(currentValue)
          if (computeValue) {
            await this.send(
              {
                payload: computeValue,
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

  private subscribeToMqttBulk(mqttBus: MqttBusManager): void {
    this.mqttSubscription = mqttBus.pointBulkStream$.subscribe({
      next: (bulk: PointBulkPayload) => {
        const myPoint = bulk.points?.find(
          (p) => p.iotDevicePointId === this.pointId
        )

        if (myPoint) {
          this.updateFromMqtt(myPoint)
        }
      },
      error: (err) => {
        console.error(`MQTT error for ${this.id}:`, err)
      },
    })
  }

  private updateFromMqtt(point: ControllerPoint): void {
    const statusFlags = convertStatusFlagsToIndividualProperties({
      statusFlags: point.statusFlags ?? [],
    })

    const presentValue = convertMultistatePresentValue({
      presentValue:
        point.presentValue ?? this.discoveredProperties.presentValue,
      stateText: this.discoveredProperties.stateText,
    })

    this.discoveredProperties = {
      ...this.discoveredProperties,
      presentValue: presentValue,
      inAlarm: statusFlags.inAlarm,
      fault: statusFlags.fault,
      overridden: statusFlags.overridden,
      eventState: point.eventState || this.discoveredProperties.eventState,
      outOfService:
        point.outOfService ?? this.discoveredProperties.outOfService,
      reliability: point.reliability || this.discoveredProperties.reliability,
      units: point.units || this.discoveredProperties.units,
      minPresValue:
        point.minPresValue ?? this.discoveredProperties.minPresValue,
      maxPresValue:
        point.maxPresValue ?? this.discoveredProperties.maxPresValue,
      highLimit: point.highLimit ?? this.discoveredProperties.highLimit,
      lowLimit: point.lowLimit ?? this.discoveredProperties.lowLimit,
      resolution: point.resolution ?? this.discoveredProperties.resolution,
      covIncrement:
        point.covIncrement ?? this.discoveredProperties.covIncrement,
      timeDelay: point.timeDelay ?? this.discoveredProperties.timeDelay,
      timeDelayNormal:
        point.timeDelayNormal ?? this.discoveredProperties.timeDelayNormal,
      notificationClass:
        point.notificationClass ?? this.discoveredProperties.notificationClass,
      notifyType: point.notifyType || this.discoveredProperties.notifyType,
      deadband: point.deadband ?? this.discoveredProperties.deadband,
      limitEnable: point.limitEnable ?? this.discoveredProperties.limitEnable,
      eventEnable: point.eventEnable ?? this.discoveredProperties.eventEnable,
      ackedTransitions:
        point.ackedTransitions ?? this.discoveredProperties.ackedTransitions,
      eventTimeStamps:
        point.eventTimeStamps ?? this.discoveredProperties.eventTimeStamps,
      eventMessageTexts:
        point.eventMessageTexts ?? this.discoveredProperties.eventMessageTexts,
      eventMessageTextsConfig:
        point.eventMessageTextsConfig ??
        this.discoveredProperties.eventMessageTextsConfig,
      priorityArray:
        point.priorityArray ?? this.discoveredProperties.priorityArray,
      relinquishDefault:
        point.relinquishDefault ?? this.discoveredProperties.relinquishDefault,
    }

    this.onDataChange()
  }

  dispose(): void {
    this.mqttSubscription?.unsubscribe()
    this.mqttSubscription = undefined
  }
}
