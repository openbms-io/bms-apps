import { NodeDirection, NodeType, DataNode } from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'

export class BinaryValueNode extends BaseBacnetNode {
  readonly objectType = 'binary-value' as const
  readonly type = NodeType.BINARY_VALUE
  readonly direction = NodeDirection.BIDIRECTIONAL

  canConnectWith(target: DataNode): boolean {
    return true
  }
}
