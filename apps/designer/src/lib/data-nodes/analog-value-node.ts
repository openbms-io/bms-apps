import { NodeDirection, NodeType } from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'

export class AnalogValueNode extends BaseBacnetNode {
  readonly objectType = 'analog-value' as const
  readonly type = NodeType.ANALOG_VALUE
  readonly direction = NodeDirection.BIDIRECTIONAL

  canConnectWith(): boolean {
    return true
  }
}
