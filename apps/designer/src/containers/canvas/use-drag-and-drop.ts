import { useCallback } from 'react'
import type { ReactFlowInstance } from '@xyflow/react'
import type {
  SemanticEquipment,
  BACnetPointData,
  BACnetControllerData,
} from '@/domains/building-semantics'
import type { useSemanticMappingModal } from './use-semantic-mapping-modal'
import type { useNodeCreation } from './use-node-creation'

type ModalHandlers = ReturnType<typeof useSemanticMappingModal>
type NodeCreationHandlers = ReturnType<typeof useNodeCreation>

interface UseDragAndDropParams {
  reactFlowInstanceRef: React.RefObject<ReactFlowInstance | null>
  semanticMappings: Map<string, SemanticEquipment>
  modalHandlers: ModalHandlers
  nodeCreation: NodeCreationHandlers
}

export function useDragAndDrop({
  reactFlowInstanceRef,
  semanticMappings,
  modalHandlers,
  nodeCreation,
}: UseDragAndDropParams) {
  const handleDrop = useCallback(
    async (event: React.DragEvent<HTMLDivElement>) => {
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
          const { config, controller } = draggedData
          if (!controller || !config) return

          if (semanticMappings.has(config.pointId)) {
            await nodeCreation.createNode(draggedData, position)
            return
          }

          const bacnetPoint: BACnetPointData = {
            pointId: config.pointId,
            objectType: config.objectType,
            objectId: config.objectId,
            supervisorId: config.supervisorId,
            controllerId: config.controllerId,
            name: config.name,
            discoveredProperties: config.discoveredProperties,
          }

          const bacnetController: BACnetControllerData = {
            deviceId: controller.deviceId,
            ipAddress: controller.ipAddress,
          }

          modalHandlers.openModal(
            position,
            draggedData,
            bacnetPoint,
            bacnetController
          )
        } else {
          await nodeCreation.createNode(draggedData, position)
        }
      } catch (error) {
        console.error('Failed to handle drop:', error)
      }
    },
    [reactFlowInstanceRef, semanticMappings, modalHandlers, nodeCreation]
  )

  return { handleDrop }
}
