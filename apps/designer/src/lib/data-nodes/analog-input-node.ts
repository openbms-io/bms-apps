import { NodeDirection, NodeType, DataNode } from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'

export class AnalogInputNode extends BaseBacnetNode {
  readonly objectType = 'analog-input' as const
  readonly type = NodeType.ANALOG_INPUT
  readonly direction = NodeDirection.BIDIRECTIONAL

  canConnectWith(target: DataNode): boolean {
    return target.direction !== NodeDirection.OUTPUT
  }
}
