'use client'

import { useCallback } from 'react'
import {
  ReactFlow,
  Controls,
  Background,
  BackgroundVariant,
  ReactFlowInstance,
  Node,
  Edge,
  Panel,
  EdgeTypes,
  OnNodesChange,
  OnEdgesChange,
  OnConnect,
} from '@xyflow/react'
import { PlayIcon } from 'lucide-react'
import '@xyflow/react/dist/style.css'

import { useFlowStore } from '@/store/use-flow-store'
import { nodeTypes } from '@/components/nodes'
import ControlFlowEdge from '@/components/edges/control-flow-edge'
import { Button } from '@/components/ui/button'
import { NotificationHandler } from './notification-handler'
import { EDGE_TYPES } from '@/types/edge-types'
import BidirectionalFlowEdge from '../edges/bidirectional-flow-edge'
import { SaveProjectButton } from './save-project-button'

const edgeTypes = {
  [EDGE_TYPES.CONTROL_FLOW]: ControlFlowEdge,
  [EDGE_TYPES.BIDIRECTIONAL_FLOW]: BidirectionalFlowEdge,
} satisfies EdgeTypes

interface FlowCanvasProps {
  reactFlowInstanceRef: React.RefObject<ReactFlowInstance | null>
  nodes: Node[]
  edges: Edge[]
  onNodesChange: OnNodesChange
  onEdgesChange: OnEdgesChange
  onConnect: OnConnect
  onDrop: (event: React.DragEvent<HTMLDivElement>) => void
  orgId: string
  siteId: string
  projectId: string
}

export function FlowCanvas({
  reactFlowInstanceRef,
  nodes,
  edges,
  onNodesChange,
  onEdgesChange,
  onConnect,
  onDrop,
  orgId,
  siteId,
  projectId,
}: FlowCanvasProps) {
  const removeNode = useFlowStore((state) => state.removeNode)
  const executeWithMessages = useFlowStore((state) => state.executeWithMessages)

  const onDragOver = useCallback((event: React.DragEvent) => {
    event.preventDefault()
    event.dataTransfer.dropEffect = 'copy'
  }, [])

  const onInit = useCallback(
    (instance: ReactFlowInstance) => {
      if (reactFlowInstanceRef) {
        reactFlowInstanceRef.current = instance
      }
    },
    [reactFlowInstanceRef]
  )

  const onNodeDelete = useCallback(
    (nodes: Node[]) => {
      nodes.forEach((node) => removeNode(node.id))
    },
    [removeNode]
  )

  return (
    <div className="w-full h-full bg-background">
      <NotificationHandler />

      <ReactFlow
        nodes={nodes}
        edges={edges}
        nodeTypes={nodeTypes}
        edgeTypes={edgeTypes}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onNodesDelete={onNodeDelete}
        onConnect={onConnect}
        onInit={onInit}
        onDragOver={onDragOver}
        onDrop={onDrop}
        fitView
        deleteKeyCode={['Delete', 'Backspace']}
        className="bg-background"
      >
        <Panel position="top-center" className="m-2">
          <div className="flex gap-2">
            <Button
              onClick={executeWithMessages}
              size="sm"
              className="flex items-center gap-2"
              variant="default"
            >
              <PlayIcon className="h-4 w-4" />
              Run
            </Button>

            <SaveProjectButton
              orgId={orgId}
              siteId={siteId}
              projectId={projectId}
            />
          </div>
        </Panel>
        <Controls
          className="bg-card border border-border"
          showZoom={true}
          showFitView={true}
          showInteractive={false}
        />
        <Background
          variant={BackgroundVariant.Dots}
          gap={20}
          size={1}
          color="hsl(var(--muted-foreground))"
          style={{
            opacity: 0.5,
          }}
        />
      </ReactFlow>
    </div>
  )
}
