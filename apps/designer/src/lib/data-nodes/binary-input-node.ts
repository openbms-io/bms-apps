import { NodeDirection, NodeType, DataNode } from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'

export class BinaryInputNode extends BaseBacnetNode {
  readonly objectType = 'binary-input' as const
  readonly type = NodeType.BINARY_INPUT
  readonly direction = NodeDirection.BIDIRECTIONAL

  canConnectWith(target: DataNode): boolean {
    return target.direction !== NodeDirection.OUTPUT
  }
}
