'use client'

import { useRef, useCallback } from 'react'
import { FlowCanvas } from '@/components/canvas/flow-canvas'
import { MappingPopupModal } from '@/domains/building-semantics/components'
import { useMappingsViewModel } from '@/domains/building-semantics/view-models/use-mappings-view-model'
import { useCanvasOrchestration } from '@/hooks/use-canvas-orchestration'
import { useFlowStore } from '@/store/use-flow-store'
import { useProject } from '@/hooks/use-projects'
import { useIotDeviceControllers } from '@/hooks/use-iot-device-controllers'
import { useAllControllerPoints } from '@/hooks/use-all-controller-points'
import type { ReactFlowInstance, Connection } from '@xyflow/react'

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

  const { data: project } = useProject({ orgId, siteId, projectId })
  const { data: controllers = [] } = useIotDeviceControllers(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId
  )

  const controllerIds = controllers.map((c) => c.id)
  const { data: pointsByController = {} } = useAllControllerPoints(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId,
    controllerIds
  )

  const { data: semanticMappings = new Map() } = useMappingsViewModel({
    projectId,
  })

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

  const {
    handleDrop,
    show223PModal,
    setShow223PModal,
    modal223PPoint,
    modal223PController,
    handle223PConfirm,
    handle223PSkip,
  } = useCanvasOrchestration(
    projectId,
    reactFlowInstanceRef,
    semanticMappings,
    controllers,
    pointsByController,
    project?.iotDeviceId
  )

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

      <MappingPopupModal
        projectId={projectId}
        open={show223PModal}
        point={modal223PPoint}
        controller={modal223PController}
        onConfirm={handle223PConfirm}
        onSkip={handle223PSkip}
        onOpenChange={setShow223PModal}
      />
    </>
  )
}
