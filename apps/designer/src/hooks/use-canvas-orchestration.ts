import { useState, useCallback } from 'react'
import { useFlowStore } from '@/store/use-flow-store'
import type { ReactFlowInstance, XYPosition } from '@xyflow/react'
import type {
  Equipment223PDTO,
  BACnetPointData,
  BACnetControllerData,
} from '@/domains/223p/schemas'
import type { DraggedPoint } from '@/store/slices/flow-slice'
import { createCompositeKey } from '@/domains/223p/utils/bacnet-keys'

interface PendingDrop {
  draggedPoint: DraggedPoint
  position: XYPosition
}

export function useCanvasOrchestration(
  projectId: string,
  reactFlowInstanceRef: React.RefObject<ReactFlowInstance | null>,
  mappings223p: Map<string, Equipment223PDTO>
) {
  const [show223PModal, setShow223PModal] = useState(false)
  const [pendingDrop, setPendingDrop] = useState<PendingDrop | null>(null)

  const addNodeFromInfrastructure = useFlowStore(
    (s) => s.addNodeFromInfrastructure
  )
  const addLogicNode = useFlowStore((s) => s.addLogicNode)
  const addCommandNode = useFlowStore((s) => s.addCommandNode)
  const addControlFlowNode = useFlowStore((s) => s.addControlFlowNode)

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

          // No mapping found - open modal as usual
          setPendingDrop({ draggedPoint: draggedData, position })
          setShow223PModal(true)
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
    ]
  )

  const handle223PConfirm = useCallback(
    async (mapping: Equipment223PDTO) => {
      if (!pendingDrop) return

      await addNodeFromInfrastructure(
        pendingDrop.draggedPoint,
        pendingDrop.position,
        mapping
      )

      setShow223PModal(false)
      setPendingDrop(null)
    },
    [pendingDrop, addNodeFromInfrastructure]
  )

  const handle223PSkip = useCallback(async () => {
    if (!pendingDrop) return

    await addNodeFromInfrastructure(
      pendingDrop.draggedPoint,
      pendingDrop.position
    )

    setShow223PModal(false)
    setPendingDrop(null)
  }, [pendingDrop, addNodeFromInfrastructure])

  const getBACnetPointData = useCallback((): BACnetPointData | null => {
    if (!pendingDrop) return null

    const { config } = pendingDrop.draggedPoint
    const bacnetPointData = {
      pointId: config.pointId,
      objectType: config.objectType,
      objectId: config.objectId,
      supervisorId: config.supervisorId,
      controllerId: config.controllerId,
      name: config.name,
      discoveredProperties: config.discoveredProperties,
    }

    return bacnetPointData
  }, [pendingDrop])

  const getBACnetControllerData =
    useCallback((): BACnetControllerData | null => {
      if (!pendingDrop) return null

      const { controller } = pendingDrop.draggedPoint

      if (!controller) return null

      return {
        deviceId: controller.deviceId,
        controllerId: controller.id,
        name: controller.name,
      }
    }, [pendingDrop])

  return {
    handleDrop,
    show223PModal,
    setShow223PModal,
    modal223PPoint: getBACnetPointData(),
    modal223PController: getBACnetControllerData(),
    handle223PConfirm,
    handle223PSkip,
  }
}
