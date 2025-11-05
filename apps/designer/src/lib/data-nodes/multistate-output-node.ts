import {
  NodeDirection,
  NodeType,
  DataNode,
  BacnetConfig,
} from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'
import { prepareMultistateProperties } from './bacnet-utils'
import { MqttBusManager } from '@/lib/mqtt/mqtt-bus'

export class MultistateOutputNode extends BaseBacnetNode {
  readonly objectType = 'multi-state-output' as const
  readonly type = NodeType.MULTISTATE_OUTPUT
  readonly direction = NodeDirection.INPUT

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

  canConnectWith(target: DataNode): boolean {
    return true
  }
}
