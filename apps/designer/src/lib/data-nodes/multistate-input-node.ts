import {
  NodeDirection,
  NodeType,
  DataNode,
  BacnetConfig,
} from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'
import { prepareMultistateProperties } from './bacnet-utils'
import { MqttBusManager } from '@/lib/mqtt/mqtt-bus'

export class MultistateInputNode extends BaseBacnetNode {
  readonly objectType = 'multi-state-input' as const
  readonly type = NodeType.MULTISTATE_INPUT
  readonly direction = NodeDirection.BIDIRECTIONAL

  constructor(params: {
    config: BacnetConfig
    mqttBus: MqttBusManager
    onDataChange: () => void
    id?: string
  }) {
    super(params)
    // Override discoveredProperties with 1-based indexing for multistate
    this.discoveredProperties = prepareMultistateProperties(
      params.config.discoveredProperties
    )
  }

  canConnectWith(target: DataNode): boolean {
    return target.direction !== NodeDirection.OUTPUT
  }
}
