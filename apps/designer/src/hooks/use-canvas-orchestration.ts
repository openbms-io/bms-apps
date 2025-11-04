import { useState, useCallback } from 'react'
import { useFlowStore } from '@/store/use-flow-store'
import type { ReactFlowInstance, XYPosition } from '@xyflow/react'
import type {
  Equipment223PDTO,
  BACnetPointData,
  BACnetControllerData,
} from '@/domains/building-semantics/schemas'
import type { DraggedPoint } from '@/store/slices/flow-slice'
import type { IotDeviceController } from '@/lib/domain/models/iot-device-controller'
import type { ControllerPoint } from '@/lib/domain/models/controller-point'
import { createCompositeKey } from '@/domains/building-semantics/utils/bacnet-keys'
import { useCreateSemanticModal } from '@/domains/building-semantics/hooks/use-create-semantic-modal'

export function useCanvasOrchestration(
  projectId: string,
  reactFlowInstanceRef: React.RefObject<ReactFlowInstance | null>,
  mappings223p: Map<string, Equipment223PDTO>,
  controllers: IotDeviceController[],
  pointsByController: Record<string, ControllerPoint[]>,
  iotDeviceId: string | undefined
) {
  const [pendingPosition, setPendingPosition] = useState<XYPosition | null>(
    null
  )
  const [pendingDraggedPoint, setPendingDraggedPoint] =
    useState<DraggedPoint | null>(null)

  const addNodeFromInfrastructure = useFlowStore(
    (s) => s.addNodeFromInfrastructure
  )
  const addLogicNode = useFlowStore((s) => s.addLogicNode)
  const addCommandNode = useFlowStore((s) => s.addCommandNode)
  const addControlFlowNode = useFlowStore((s) => s.addControlFlowNode)

  const { semanticModalState, openSemanticModal, closeSemanticModal } =
    useCreateSemanticModal(controllers, pointsByController, iotDeviceId)

  const handleDrop = useCallback(
    async (event: DragEvent) => {
      event.preventDefault()

      if (!reactFlowInstanceRef.current) {
        console.warn('React Flow instance not ready')
        return
      }

      if (!event.dataTransfer) {
        console.warn('No dataTransfer available')
        return
      }

      const data = event.dataTransfer.getData('application/json')
      if (!data) {
        console.warn('No drag data found')
        return
      }

      try {
        const draggedData = JSON.parse(data)
        const position = reactFlowInstanceRef.current.screenToFlowPosition({
          x: event.clientX,
          y: event.clientY,
        })

        if (
          draggedData.type === 'bacnet-point' &&
          draggedData.draggedFrom === 'controllers-tree'
        ) {
          // Check if point already has 223P mapping
          const { config, controller } = draggedData
          if (controller && config) {
            const compositeKey = createCompositeKey(
              controller.deviceId,
              config.objectType,
              config.objectId
            )
            const existingMapping = mappings223p.get(compositeKey)

            if (existingMapping) {
              // Skip modal - add node directly with existing mapping
              await addNodeFromInfrastructure(
                draggedData,
                position,
                existingMapping
              )
              return
            }
          }

          // No mapping found - open semantic modal
          setPendingPosition(position)
          setPendingDraggedPoint(draggedData)
          openSemanticModal(draggedData.config.pointId)
        } else if (
          draggedData.type === 'logic-node' &&
          draggedData.draggedFrom === 'logic-section'
        ) {
          await addLogicNode(
            draggedData.nodeType,
            draggedData.label,
            position,
            draggedData.metadata
          )
        } else if (
          draggedData.type === 'command-node' &&
          draggedData.draggedFrom === 'command-section'
        ) {
          await addCommandNode(
            draggedData.nodeType,
            draggedData.label,
            position,
            draggedData.metadata
          )
        } else if (
          draggedData.type === 'control-flow-node' &&
          draggedData.draggedFrom === 'control-flow-section'
        ) {
          await addControlFlowNode(
            draggedData.nodeType,
            draggedData.label,
            position,
            draggedData.metadata
          )
        } else {
          console.warn('Unknown drag type:', draggedData.type)
        }
      } catch (error) {
        console.error('Failed to handle drop:', error)
      }
    },
    [
      reactFlowInstanceRef,
      addNodeFromInfrastructure,
      addLogicNode,
      addCommandNode,
      addControlFlowNode,
      mappings223p,
      openSemanticModal,
    ]
  )

  const handle223PConfirm = useCallback(
    async (mapping: Equipment223PDTO) => {
      if (!pendingDraggedPoint || !pendingPosition) {
        closeSemanticModal()
        return
      }

      await addNodeFromInfrastructure(
        pendingDraggedPoint,
        pendingPosition,
        mapping
      )

      setPendingPosition(null)
      setPendingDraggedPoint(null)
      closeSemanticModal()
    },
    [
      pendingDraggedPoint,
      pendingPosition,
      addNodeFromInfrastructure,
      closeSemanticModal,
    ]
  )

  const handle223PSkip = useCallback(async () => {
    if (!pendingDraggedPoint || !pendingPosition) {
      closeSemanticModal()
      return
    }

    await addNodeFromInfrastructure(pendingDraggedPoint, pendingPosition)

    setPendingPosition(null)
    setPendingDraggedPoint(null)
    closeSemanticModal()
  }, [
    pendingDraggedPoint,
    pendingPosition,
    addNodeFromInfrastructure,
    closeSemanticModal,
  ])

  return {
    handleDrop,
    show223PModal: semanticModalState.isOpen,
    setShow223PModal: closeSemanticModal,
    modal223PPoint: semanticModalState.point,
    modal223PController: semanticModalState.controller,
    handle223PConfirm,
    handle223PSkip,
  }
}
