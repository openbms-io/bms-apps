import { NodeDirection, NodeType, DataNode } from '@/types/infrastructure'
import { BaseBacnetNode } from './base-bacnet-node'

export class AnalogOutputNode extends BaseBacnetNode {
  readonly objectType = 'analog-output' as const
  readonly type = NodeType.ANALOG_OUTPUT
  readonly direction = NodeDirection.INPUT

  canConnectWith(source: DataNode): boolean {
    // Analog outputs accept input from logic/calculation nodes
    return source.direction !== NodeDirection.INPUT
  }
}
