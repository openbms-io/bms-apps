import { NodeType } from '@/types/infrastructure'

export interface SerializableNode {
  toSerializable(): Record<string, unknown>
}

export interface SerializedNodeData {
  readonly nodeType: string
  readonly serializedData: Record<string, unknown>
}

export function serializeNodeData(node: unknown): SerializedNodeData {
  if (isSerializableNode(node)) {
    const serialized = node.toSerializable()

    return {
      nodeType: serialized.type as string,
      serializedData: serialized,
    }
  }

  throw new Error(
    `Cannot serialize node: Node must implement SerializableNode interface`
  )
}

export function deserializeNodeData({
  nodeType,
  serializedData,
  nodeFactory,
}: {
  readonly nodeType: NodeType
  readonly serializedData: Record<string, unknown>
  readonly nodeFactory: (
    nodeType: NodeType,
    data: Record<string, unknown>
  ) => unknown
}): unknown {
  return nodeFactory(nodeType, serializedData)
}

function isSerializableNode(obj: unknown): obj is SerializableNode {
  return (
    obj !== null &&
    typeof obj === 'object' &&
    'toSerializable' in obj &&
    typeof (obj as SerializableNode).toSerializable === 'function'
  )
}
