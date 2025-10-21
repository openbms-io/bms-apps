import { NodeDirection, NodeType, DataNode } from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'

export class BinaryOutputNode extends BaseBacnetNode {
  readonly objectType = 'binary-output' as const
  readonly type = NodeType.BINARY_OUTPUT
  readonly direction = NodeDirection.INPUT

  canConnectWith(source: DataNode): boolean {
    // Binary outputs accept input from logic/calculation nodes
    return source.direction !== NodeDirection.INPUT
  }
}
