'use client'

import { useRef, useCallback } from 'react'
import { FlowCanvas } from '@/components/canvas/flow-canvas'
import { MappingPopupModal } from '@/domains/223p/components'
import { useMappingsQuery } from '@/domains/223p/api/queries/use-mappings-query'
import { useCanvasOrchestration } from '@/hooks/use-canvas-orchestration'
import { useFlowStore } from '@/store/use-flow-store'
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

  const { data: mappings223p = new Map() } = useMappingsQuery(projectId)

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
  } = useCanvasOrchestration(projectId, reactFlowInstanceRef, mappings223p)

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
