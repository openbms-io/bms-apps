'use client'

import { useState, useCallback } from 'react'
import { TreeView } from '@/components/tree/tree-view'
import { TreeToolbar } from '@/components/tree/tree-toolbar'
import { useInfrastructureStore } from '@/store/use-infrastructure-store'
import { TreeNode as TreeNodeType, BacnetConfig } from '@/types/infrastructure'
import { DraggedPoint } from '@/store/slices/flow-slice'
import { Button } from '@/components/ui/button'
import { Plus, RefreshCw } from 'lucide-react'
import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogFooter,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog'
import { Input } from '@/components/ui/input'
import { Label } from '@/components/ui/label'
import { Switch } from '@/components/ui/switch'
import { LogicNodesSection } from '@/components/sidebar/logic-nodes-section'
import { ControlFlowSection } from '@/components/sidebar/control-flow-section'
import { CommandNodesSection } from '@/components/sidebar/command-nodes-section'
import { useCreateIotDeviceController } from '@/hooks/use-iot-device-controllers'
import { useProject } from '@/hooks/use-projects'
import { toast } from 'sonner'

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
  const [isAddDialogOpen, setIsAddDialogOpen] = useState(false)
  const [formData, setFormData] = useState({
    name: '',
    ipAddress: '',
    port: '47808',
    deviceId: '',
    networkNumber: '',
    macAddress: '',
    isActive: true,
  })
  const [searchValue, setSearchValue] = useState('')

  // Infrastructure store
  const {
    supervisors,
    selectedPointId,
    toggleNode,
    selectPoint,
    expandAll,
    collapseAll,
    getTreeData,
    addController,
    discoverPoints,
  } = useInfrastructureStore()

  const createMutation = useCreateIotDeviceController()

  // Get tree data
  const treeData = getTreeData()

  // Filter tree data based on search
  const filteredTreeData = searchValue
    ? filterTreeNodes(treeData, searchValue.toLowerCase())
    : treeData

  const handleDragStart = useCallback(
    (e: React.DragEvent, node: TreeNodeType) => {
      if (node.type === 'point' && node.data) {
        const draggedPoint: DraggedPoint = {
          type: 'bacnet-point',
          config: node.data as BacnetConfig,
          draggedFrom: 'controllers-tree',
        }

        e.dataTransfer.effectAllowed = 'copy'
        e.dataTransfer.setData('application/json', JSON.stringify(draggedPoint))
      }
    },
    []
  )

  const handleAddController = useCallback(
    async (e: React.FormEvent) => {
      e.preventDefault()

      const ipRegex = /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/
      if (!ipRegex.test(formData.ipAddress)) {
        toast.error('Invalid IP address format')
        return
      }

      const port = parseInt(formData.port)
      if (isNaN(port) || port < 1 || port > 65535) {
        toast.error('Port must be between 1 and 65535')
        return
      }

      const deviceId = parseInt(formData.deviceId)
      if (isNaN(deviceId) || deviceId < 0) {
        toast.error('Device ID must be a positive number')
        return
      }

      const networkNumber = formData.networkNumber
        ? parseInt(formData.networkNumber)
        : undefined
      if (
        networkNumber !== undefined &&
        (isNaN(networkNumber) || networkNumber < 0)
      ) {
        toast.error('Network number must be a positive number')
        return
      }

      if (!project?.iotDeviceId) {
        toast.error('No IoT device linked to this project')
        return
      }

      try {
        await createMutation.mutateAsync({
          orgId,
          siteId,
          projectId,
          iotDeviceId: project.iotDeviceId,
          data: {
            name: formData.name,
            ipAddress: formData.ipAddress,
            port,
            deviceId,
            networkNumber,
            macAddress: formData.macAddress || undefined,
            isActive: formData.isActive,
          },
        })

        toast.success('Controller added successfully')
        setFormData({
          name: '',
          ipAddress: '',
          port: '47808',
          deviceId: '',
          networkNumber: '',
          macAddress: '',
          isActive: true,
        })
        setIsAddDialogOpen(false)
      } catch (error) {
        toast.error(
          error instanceof Error ? error.message : 'Failed to add controller'
        )
      }
    },
    [formData, createMutation]
  )

  const handleRefreshAll = useCallback(async () => {
    // Refresh all controllers
    for (const supervisor of supervisors.values()) {
      for (const controller of supervisor.controllers) {
        await discoverPoints(supervisor.id, controller.id)
      }
    }
  }, [supervisors, discoverPoints])

  const handleContainerClick = useCallback(() => {
    selectPoint(null) // Clear selection when clicking empty areas
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
            onClick={handleRefreshAll}
            title="Refresh All"
          >
            <RefreshCw className="h-4 w-4" />
          </Button>
        </div>
      </div>

      <TreeToolbar
        onExpandAll={expandAll}
        onCollapseAll={collapseAll}
        searchValue={searchValue}
        onSearchChange={setSearchValue}
        showSearch={true}
      />

      {/* Scrollable container for TreeView and node sections */}
      <div className="flex-1 overflow-y-auto">
        <TreeView
          nodes={filteredTreeData}
          selectedNodeId={selectedPointId}
          onToggle={toggleNode}
          onSelect={selectPoint}
          isDraggable={true}
          onDragStart={handleDragStart}
          className="min-h-0"
        />

        <LogicNodesSection />
        <ControlFlowSection />
        <CommandNodesSection />
      </div>

      <Dialog open={isAddDialogOpen} onOpenChange={setIsAddDialogOpen}>
        <DialogContent className="max-w-md">
          <DialogHeader>
            <DialogTitle>Add New Controller</DialogTitle>
            <DialogDescription>
              Configure the BACnet controller settings.
            </DialogDescription>
          </DialogHeader>
          <form onSubmit={handleAddController}>
            <div className="grid gap-4 py-4">
              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="name" className="text-right">
                  Name *
                </Label>
                <Input
                  id="name"
                  value={formData.name}
                  onChange={(e) =>
                    setFormData({ ...formData, name: e.target.value })
                  }
                  placeholder="Main Controller"
                  className="col-span-3"
                  required
                />
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="ip-address" className="text-right">
                  IP Address *
                </Label>
                <Input
                  id="ip-address"
                  value={formData.ipAddress}
                  onChange={(e) =>
                    setFormData({ ...formData, ipAddress: e.target.value })
                  }
                  placeholder="192.168.1.100"
                  className="col-span-3"
                  required
                />
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="port" className="text-right">
                  Port *
                </Label>
                <Input
                  id="port"
                  type="number"
                  value={formData.port}
                  onChange={(e) =>
                    setFormData({ ...formData, port: e.target.value })
                  }
                  placeholder="47808"
                  className="col-span-3"
                  required
                />
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="device-id" className="text-right">
                  Device ID *
                </Label>
                <Input
                  id="device-id"
                  type="number"
                  value={formData.deviceId}
                  onChange={(e) =>
                    setFormData({ ...formData, deviceId: e.target.value })
                  }
                  placeholder="123456"
                  className="col-span-3"
                  required
                />
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="network-number" className="text-right">
                  Network Number
                </Label>
                <Input
                  id="network-number"
                  type="number"
                  value={formData.networkNumber}
                  onChange={(e) =>
                    setFormData({ ...formData, networkNumber: e.target.value })
                  }
                  placeholder="Optional"
                  className="col-span-3"
                />
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="mac-address" className="text-right">
                  MAC Address
                </Label>
                <Input
                  id="mac-address"
                  value={formData.macAddress}
                  onChange={(e) =>
                    setFormData({ ...formData, macAddress: e.target.value })
                  }
                  placeholder="Optional"
                  className="col-span-3"
                />
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="is-active" className="text-right">
                  Active
                </Label>
                <div className="col-span-3">
                  <Switch
                    id="is-active"
                    checked={formData.isActive}
                    onCheckedChange={(checked) =>
                      setFormData({ ...formData, isActive: checked })
                    }
                  />
                </div>
              </div>
            </div>
            <DialogFooter>
              <Button
                type="submit"
                disabled={
                  !formData.name ||
                  !formData.ipAddress ||
                  !formData.port ||
                  !formData.deviceId ||
                  createMutation.isPending
                }
              >
                {createMutation.isPending ? 'Adding...' : 'Add Controller'}
              </Button>
            </DialogFooter>
          </form>
        </DialogContent>
      </Dialog>
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
        isExpanded: filteredChildren.length > 0, // Auto-expand if has matching children
      })
    }

    return filtered
  }, [])
}
