'use client'

import { useRef, useCallback } from 'react'
import { FlowCanvas } from '@/components/canvas/flow-canvas'
import { BuildingSemanticsModal } from '@/domains/building-semantics'
import {
  useTemplatesQuery,
  useBacnetReferencesQuery,
} from '@/domains/building-semantics/api'
import { useSemanticMappingModal } from './use-semantic-mapping-modal'
import { useNodeCreation } from './use-node-creation'
import { useDragAndDrop } from './use-drag-and-drop'
import { useFlowStore } from '@/store/use-flow-store'
import type { ReactFlowInstance, Connection } from '@xyflow/react'
import type { BacnetObjectType } from '@/types/infrastructure'

interface FlowCanvasContainerProps {
  orgId: string
  siteId: string
  projectId: string
}

export function FlowCanvasContainer({
  orgId,
  siteId,
  projectId,
}: FlowCanvasContainerProps) {
  const reactFlowInstanceRef = useRef<ReactFlowInstance | null>(null)

  const nodes = useFlowStore((s) => s.nodes)
  const edges = useFlowStore((s) => s.edges)
  const onNodesChange = useFlowStore((s) => s.onNodesChange)
  const onEdgesChange = useFlowStore((s) => s.onEdgesChange)
  const connectNodes = useFlowStore((s) => s.connectNodes)

  const { data: templates = [] } = useTemplatesQuery()
  const { data: semanticMappings = new Map() } =
    useBacnetReferencesQuery(projectId)

  const onConnect = useCallback(
    (params: Connection) => {
      if (params.source && params.target) {
        connectNodes(
          params.source,
          params.target,
          params.sourceHandle,
          params.targetHandle
        )
      }
    },
    [connectNodes]
  )

  const modalHandlers = useSemanticMappingModal()
  const nodeCreation = useNodeCreation()
  const { handleDrop } = useDragAndDrop({
    reactFlowInstanceRef,
    semanticMappings,
    modalHandlers,
    nodeCreation,
  })

  const handleModalConfirm = useCallback(async () => {
    if (!modalHandlers.pendingDraggedPoint || !modalHandlers.pendingPosition) {
      modalHandlers.closeModal()
      return
    }

    await nodeCreation.createNode(
      modalHandlers.pendingDraggedPoint,
      modalHandlers.pendingPosition
    )
    modalHandlers.closeModal()
  }, [modalHandlers, nodeCreation])

  const handleModalSkip = useCallback(async () => {
    if (!modalHandlers.pendingDraggedPoint || !modalHandlers.pendingPosition) {
      modalHandlers.closeModal()
      return
    }

    await nodeCreation.createNode(
      modalHandlers.pendingDraggedPoint,
      modalHandlers.pendingPosition
    )
    modalHandlers.closeModal()
  }, [modalHandlers, nodeCreation])

  return (
    <>
      <FlowCanvas
        reactFlowInstanceRef={reactFlowInstanceRef}
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onConnect={onConnect}
        onDrop={handleDrop}
        orgId={orgId}
        siteId={siteId}
        projectId={projectId}
      />

      {modalHandlers.bacnetPoint && modalHandlers.bacnetController && (
        <BuildingSemanticsModal
          projectId={projectId}
          open={modalHandlers.isOpen}
          bacnetPointId={modalHandlers.bacnetPoint.pointId}
          bacnetObjectType={modalHandlers.bacnetPoint.objectType}
          buildingSemanticsBacnetConfig={{
            objectType: modalHandlers.bacnetPoint
              .objectType as BacnetObjectType,
            objectId: modalHandlers.bacnetPoint.objectId,
            controllerDeviceId: modalHandlers.bacnetController.deviceId,
            controllerIPAddress: modalHandlers.bacnetController.ipAddress,
          }}
          pointLabel={modalHandlers.bacnetPoint.name}
          templates={templates}
          onSaved={handleModalConfirm}
          onSkip={handleModalSkip}
          onOpenChange={modalHandlers.setIsOpen}
        />
      )}
    </>
  )
}
