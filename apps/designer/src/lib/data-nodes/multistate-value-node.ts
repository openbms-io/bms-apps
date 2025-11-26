import {
  NodeDirection,
  NodeType,
  DataNode,
  BacnetConfig,
} from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'
import { prepareMultistateProperties } from './bacnet-utils'
import { MqttBusManager } from '@/lib/mqtt/mqtt-bus'

export class MultistateValueNode extends BaseBacnetNode {
  readonly objectType = 'multi-state-value' as const
  readonly type = NodeType.MULTISTATE_VALUE
  readonly direction = NodeDirection.BIDIRECTIONAL

  constructor(params: {
    config: BacnetConfig
    mqttBus: MqttBusManager
    onDataChange: () => void
    id?: string
    semanticMappingKey?: string
  }) {
    super(params)
    this.discoveredProperties = prepareMultistateProperties(
      params.config.discoveredProperties
    )
  }

  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  canConnectWith(_target: DataNode): boolean {
    return true
  }
}
