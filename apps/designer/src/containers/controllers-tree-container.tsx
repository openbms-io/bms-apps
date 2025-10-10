'use client'

import { useState, useCallback, useMemo } from 'react'
import { TreeView } from '@/components/tree/tree-view'
import { TreeToolbar } from '@/components/tree/tree-toolbar'
import { useTreeUIStore } from '@/store/use-tree-ui-store'
import { TreeNode as TreeNodeType } from '@/types/infrastructure'
import { Button } from '@/components/ui/button'
import { Plus, RefreshCw } from 'lucide-react'
import { LogicNodesSection } from '@/components/sidebar/logic-nodes-section'
import { ControlFlowSection } from '@/components/sidebar/control-flow-section'
import { CommandNodesSection } from '@/components/sidebar/command-nodes-section'
import { useIotDeviceControllers } from '@/hooks/use-iot-device-controllers'
import { useProject } from '@/hooks/use-projects'
import { AddControllerDialog } from '@/components/modals/add-controller-dialog'

interface ControllersTreeContainerProps {
  orgId: string
  siteId: string
  projectId: string
}

export function ControllersTreeContainer({
  orgId,
  siteId,
  projectId,
}: ControllersTreeContainerProps) {
  const { data: project } = useProject({ orgId, siteId, projectId })
  const { data: controllers = [], isLoading } = useIotDeviceControllers(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId
  )

  const [isAddDialogOpen, setIsAddDialogOpen] = useState(false)
  const [searchValue, setSearchValue] = useState('')

  // Tree UI Store
  const {
    selectedPointId,
    expandedNodes,
    toggleNode,
    selectPoint,
    expandAll,
    collapseAll,
    getTreeData,
  } = useTreeUIStore()

  // Transform controllers into tree structure
  const treeData = useMemo(
    () => getTreeData(controllers, project?.iotDeviceId || ''),
    [getTreeData, controllers, project?.iotDeviceId, expandedNodes]
  )

  // Filter tree data based on search
  const filteredTreeData = searchValue
    ? filterTreeNodes(treeData, searchValue.toLowerCase())
    : treeData

  const handleExpandAll = useCallback(() => {
    const allNodeIds: string[] = []

    if (project?.iotDeviceId) {
      allNodeIds.push(project.iotDeviceId)
      controllers.forEach((controller) => {
        allNodeIds.push(controller.id)
      })
    }

    expandAll(allNodeIds)
  }, [controllers, expandAll, project?.iotDeviceId])

  const handleContainerClick = useCallback(() => {
    selectPoint(null)
  }, [selectPoint])

  return (
    <div className="flex flex-col h-full" onClick={handleContainerClick}>
      <div className="flex items-center justify-between p-3 border-b">
        <h3 className="text-sm font-semibold">Controllers</h3>
        <div className="flex items-center gap-1">
          <Button
            variant="ghost"
            size="icon"
            className="h-7 w-7"
            onClick={() => setIsAddDialogOpen(true)}
            title="Add Controller"
          >
            <Plus className="h-4 w-4" />
          </Button>
          <Button
            variant="ghost"
            size="icon"
            className="h-7 w-7"
            onClick={() => {
              // TODO: Implement get_config via MQTT in Phase 2
              console.log('Refresh - will implement MQTT get_config')
            }}
            title="Refresh (Coming Soon)"
          >
            <RefreshCw className="h-4 w-4" />
          </Button>
        </div>
      </div>

      <TreeToolbar
        onExpandAll={handleExpandAll}
        onCollapseAll={collapseAll}
        searchValue={searchValue}
        onSearchChange={setSearchValue}
        showSearch={true}
      />

      <div className="flex-1 overflow-y-auto">
        {isLoading ? (
          <div className="flex items-center justify-center h-32">
            <div className="text-sm text-muted-foreground">
              Loading controllers...
            </div>
          </div>
        ) : (
          <TreeView
            nodes={filteredTreeData}
            selectedNodeId={selectedPointId}
            onToggle={toggleNode}
            onSelect={selectPoint}
            isDraggable={false} // No dragging until we have points
            className="min-h-0"
          />
        )}

        <LogicNodesSection />
        <ControlFlowSection />
        <CommandNodesSection />
      </div>

      {project?.iotDeviceId && (
        <AddControllerDialog
          open={isAddDialogOpen}
          onOpenChange={setIsAddDialogOpen}
          orgId={orgId}
          siteId={siteId}
          projectId={projectId}
          iotDeviceId={project.iotDeviceId}
        />
      )}
    </div>
  )
}

// Helper function to filter tree nodes
function filterTreeNodes(
  nodes: TreeNodeType[],
  searchTerm: string
): TreeNodeType[] {
  return nodes.reduce<TreeNodeType[]>((filtered, node) => {
    const nodeMatches =
      node.label.toLowerCase().includes(searchTerm) ||
      node.sublabel?.toLowerCase().includes(searchTerm)

    let filteredChildren: TreeNodeType[] = []
    if (node.children) {
      filteredChildren = filterTreeNodes(node.children, searchTerm)
    }

    if (nodeMatches || filteredChildren.length > 0) {
      filtered.push({
        ...node,
        children: filteredChildren,
        isExpanded: filteredChildren.length > 0,
      })
    }

    return filtered
  }, [])
}
