import { useCallback } from 'react'
import { useFlowStore } from '@/store/use-flow-store'
import type { XYPosition } from '@xyflow/react'
import type { DraggedPoint } from '@/store/slices/flow-slice'
import type { NodeTypeString } from '@/types/infrastructure'

type DraggedData = {
  type: string
  draggedFrom: string
  nodeType?: NodeTypeString
  label?: string
  metadata?: Record<string, unknown>
}

export function useNodeCreation() {
  const addNodeFromInfrastructure = useFlowStore(
    (s) => s.addNodeFromInfrastructure
  )
  const addLogicNode = useFlowStore((s) => s.addLogicNode)
  const addCommandNode = useFlowStore((s) => s.addCommandNode)
  const addControlFlowNode = useFlowStore((s) => s.addControlFlowNode)
  const addControlSequenceNode = useFlowStore((s) => s.addControlSequenceNode)
  const showError = useFlowStore((s) => s.showError)

  const createNode = useCallback(
    async (draggedData: DraggedData, position: XYPosition) => {
      try {
        if (
          draggedData.type === 'bacnet-point' &&
          draggedData.draggedFrom === 'controllers-tree'
        ) {
          await addNodeFromInfrastructure(draggedData as DraggedPoint, position)
        } else if (
          draggedData.type === 'logic-node' &&
          draggedData.draggedFrom === 'logic-section'
        ) {
          await addLogicNode(
            draggedData.nodeType!,
            draggedData.label!,
            position,
            draggedData.metadata
          )
        } else if (
          draggedData.type === 'command-node' &&
          draggedData.draggedFrom === 'command-section'
        ) {
          await addCommandNode(
            draggedData.nodeType!,
            draggedData.label!,
            position,
            draggedData.metadata
          )
        } else if (
          draggedData.type === 'control-flow-node' &&
          draggedData.draggedFrom === 'control-flow-section'
        ) {
          await addControlFlowNode(
            draggedData.nodeType!,
            draggedData.label!,
            position,
            draggedData.metadata
          )
        } else if (
          draggedData.type === 'control-sequence-node' &&
          draggedData.draggedFrom === 'control-sequences-section'
        ) {
          await addControlSequenceNode(
            draggedData.nodeType!,
            draggedData.label!,
            position,
            draggedData.metadata
          )
        } else {
          console.warn('Unknown drag type:', draggedData.type)
        }
      } catch (error) {
        showError(
          'Failed to create node',
          error instanceof Error ? error.message : 'Unknown error'
        )
      }
    },
    [
      addNodeFromInfrastructure,
      addLogicNode,
      addCommandNode,
      addControlFlowNode,
      addControlSequenceNode,
      showError,
    ]
  )

  return { createNode }
}
