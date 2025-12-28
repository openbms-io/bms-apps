'use client'

import { useState, useCallback } from 'react'
import { TreeView } from '@/components/tree/tree-view'
import { TreeToolbar } from '@/components/tree/tree-toolbar'
import { useTreeUIStore } from '@/store/use-tree-ui-store'
import { TreeNode as TreeNodeType } from '@/types/infrastructure'
import { Button } from '@/components/ui/button'
import { Plus, RefreshCw } from 'lucide-react'
import { LogicNodesSection } from '@/components/sidebar/logic-nodes-section'
import { ControlFlowSection } from '@/components/sidebar/control-flow-section'
import { CommandNodesSection } from '@/components/sidebar/command-nodes-section'
import { ControlSequencesSection } from '@/components/sidebar/control-sequences-section'
import {
  useIotDeviceControllers,
  useDeleteIotDeviceController,
} from '@/hooks/use-iot-device-controllers'
import { useProject } from '@/hooks/use-projects'
import { useIotDevice } from '@/hooks/use-iot-device'
import { useAllControllerPoints } from '@/hooks/use-all-controller-points'
import { useQueryClient } from '@tanstack/react-query'
import { queryKeys } from '@/lib/query-client'
import { AddControllerDialog } from '@/components/modals/add-controller-dialog'
import { BuildingSemanticsModal } from '@/domains/building-semantics'
import { useTemplatesQuery } from '@/domains/building-semantics/api'
import { useBacnetReferencesQuery } from '@/domains/building-semantics/api/queries/use-bacnet-references-query'
import { useGetConfigPayload } from '@/hooks/use-get-config-payload'
import { useFlowStore } from '@/store/use-flow-store'
import { CommandNameEnum } from 'mqtt-topics'
import { toast } from 'sonner'
import { buildConfigUploadPayload } from '@/store/slices/mqtt-slice'
import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogFooter,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog'
import { BacnetObjectType } from '@/types/infrastructure'
import { DraggedPoint } from '@/store/slices/flow-slice'
import { ControllerPoint } from '@/lib/domain/models/controller-point'
import { IotDeviceController } from '@/lib/domain/models/iot-device-controller'
import { convertPointToBacnetConfig, filterTreeNodes } from './utils'

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
  const { data: iotDevice } = useIotDevice(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId
  )
  const { data: controllers = [], isLoading } = useIotDeviceControllers(
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

  const { data: templates = [] } = useTemplatesQuery()
  const { data: semanticMappings = new Map() } =
    useBacnetReferencesQuery(projectId)

  const [mappingModalState, setMappingModalState] = useState<{
    isOpen: boolean
    bacnetPointId: string
    bacnetObjectType: BacnetObjectType
    pointLabel: string
    pointDescription?: string
    objectId: number
    controllerDeviceId: number
    controllerIPAddress: string
  } | null>(null)

  const queryClient = useQueryClient()
  const [isAddDialogOpen, setIsAddDialogOpen] = useState(false)
  const [searchValue, setSearchValue] = useState('')
  const [deleteDialogOpen, setDeleteDialogOpen] = useState(false)
  const [controllerToDelete, setControllerToDelete] = useState<{
    id: string
    name: string
  } | null>(null)

  const sendCommand = useFlowStore((s) => s.sendCommand)
  const { refetch: fetchPayload, isFetching } = useGetConfigPayload(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId
  )

  const { mutate: deleteController, isPending: isDeleting } =
    useDeleteIotDeviceController()

  const {
    selectedPointId,
    toggleNode,
    selectPoint,
    expandAll,
    collapseAll,
    getTreeData,
  } = useTreeUIStore()

  const treeData = getTreeData(
    controllers,
    iotDevice ? { id: iotDevice.id, name: iotDevice.name } : undefined,
    pointsByController,
    semanticMappings
  )

  const filteredTreeData = searchValue
    ? filterTreeNodes({
        nodes: treeData,
        searchTerm: searchValue.toLowerCase(),
      })
    : treeData

  const openMappingModal = useCallback(
    (nodeId: string) => {
      if (!project?.iotDeviceId) return

      let foundPoint: ControllerPoint | undefined
      let foundController: IotDeviceController | undefined

      for (const controller of controllers) {
        const points = pointsByController[controller.id] || []
        const point = points.find((p) => p.id === nodeId)
        if (point) {
          foundPoint = point
          foundController = controller
          break
        }
      }

      if (!foundPoint || !foundController) return

      setMappingModalState({
        isOpen: true,
        bacnetPointId: foundPoint.id,
        bacnetObjectType: foundPoint.pointType as BacnetObjectType,
        pointLabel: foundPoint.pointName || '',
        pointDescription: foundPoint.description,
        objectId: foundPoint.instanceNumber,
        controllerDeviceId: foundController.deviceId,
        controllerIPAddress: foundController.ipAddress,
      })
    },
    [controllers, pointsByController, project?.iotDeviceId]
  )

  const closeMappingModal = useCallback(() => {
    setMappingModalState(null)
  }, [])

  const handleDragStart = useCallback(
    (e: React.DragEvent, node: TreeNodeType) => {
      if (node.type === 'point' && node.data && project?.iotDeviceId) {
        const point = node.data as ControllerPoint
        const bacnetConfig = convertPointToBacnetConfig({
          point,
          iotDeviceId: project.iotDeviceId,
        })

        const controller = controllers.find((c) => c.id === point.controllerId)

        const draggedPoint: DraggedPoint = {
          type: 'bacnet-point',
          config: bacnetConfig,
          draggedFrom: 'controllers-tree',
          controller: controller
            ? {
                id: controller.id,
                name: controller.name,
                deviceId: controller.deviceId,
                ipAddress: controller.ipAddress,
              }
            : undefined,
        }

        e.dataTransfer.effectAllowed = 'copy'
        e.dataTransfer.setData('application/json', JSON.stringify(draggedPoint))
      }
    },
    [project?.iotDeviceId, controllers]
  )

  const handleExpandAll = useCallback(() => {
    const allNodeIds: string[] = []

    if (iotDevice) {
      allNodeIds.push(iotDevice.id)
      controllers.forEach((controller) => {
        allNodeIds.push(controller.id)
      })
    }

    expandAll(allNodeIds)
  }, [controllers, expandAll, iotDevice])

  const handleContainerClick = useCallback(() => {
    selectPoint(null)
  }, [selectPoint])

  const handleRefresh = async () => {
    if (!project?.iotDeviceId) return

    try {
      const { data: payload } = await fetchPayload()
      if (!payload) throw new Error('No payload received')

      const transformedPayload = buildConfigUploadPayload(payload)
      toast.success('Config discovery started')

      await sendCommand({
        command: CommandNameEnum.GET_CONFIG,
        payload: transformedPayload,
      })

      queryClient.invalidateQueries({
        queryKey: queryKeys.controllerPoints.batch(controllerIds),
      })

      toast.success('Config discovery completed', { duration: 5000 })
    } catch (error) {
      console.error('Refresh error:', error)
      toast.error('Failed to start discovery', { duration: 5000 })
    }
  }

  const handleDeleteClick = useCallback(
    (controllerId: string) => {
      const controller = controllers.find((c) => c.id === controllerId)
      if (controller) {
        setControllerToDelete({ id: controller.id, name: controller.name })
        setDeleteDialogOpen(true)
      }
    },
    [controllers]
  )

  const handleConfirmDelete = useCallback(() => {
    if (!controllerToDelete || !project?.iotDeviceId) return

    deleteController(
      {
        orgId,
        siteId,
        projectId,
        iotDeviceId: project.iotDeviceId,
        controllerId: controllerToDelete.id,
      },
      {
        onSuccess: () => {
          toast.success('Controller deleted successfully')
          setDeleteDialogOpen(false)
          setControllerToDelete(null)
        },
        onError: (error) => {
          toast.error(error.message || 'Failed to delete controller')
        },
      }
    )
  }, [controllerToDelete, deleteController, orgId, siteId, projectId, project])

  const handleMappingSaved = useCallback(() => {
    toast.success('BACnet reference saved successfully')
    closeMappingModal()
    queryClient.invalidateQueries({ queryKey: ['bacnet-references'] })
  }, [closeMappingModal, queryClient])

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
            onClick={handleRefresh}
            disabled={!project?.iotDeviceId || isFetching}
            title="Refresh Controllers"
          >
            <RefreshCw
              className={`h-4 w-4 ${isFetching ? 'animate-spin' : ''}`}
            />
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
            onDelete={handleDeleteClick}
            onAdd223PMapping={openMappingModal}
            onEdit223PMapping={openMappingModal}
            isDraggable={true}
            onDragStart={handleDragStart}
            className="min-h-0"
          />
        )}

        <LogicNodesSection />
        <ControlFlowSection />
        <CommandNodesSection />
        <ControlSequencesSection />
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

      <Dialog open={deleteDialogOpen} onOpenChange={setDeleteDialogOpen}>
        <DialogContent>
          <DialogHeader>
            <DialogTitle>Delete Controller</DialogTitle>
            <DialogDescription>
              Are you sure you want to delete &quot;{controllerToDelete?.name}
              &quot;? This will also delete all associated points. This action
              cannot be undone.
            </DialogDescription>
          </DialogHeader>
          <DialogFooter>
            <Button
              variant="outline"
              onClick={() => setDeleteDialogOpen(false)}
              disabled={isDeleting}
            >
              Cancel
            </Button>
            <Button
              variant="destructive"
              onClick={handleConfirmDelete}
              disabled={isDeleting}
            >
              {isDeleting ? 'Deleting...' : 'Delete'}
            </Button>
          </DialogFooter>
        </DialogContent>
      </Dialog>

      {mappingModalState && (
        <BuildingSemanticsModal
          orgId={orgId}
          siteId={siteId}
          projectId={projectId}
          open={mappingModalState.isOpen}
          bacnetPointId={mappingModalState.bacnetPointId}
          bacnetObjectType={mappingModalState.bacnetObjectType}
          buildingSemanticsBacnetConfig={{
            objectType: mappingModalState.bacnetObjectType,
            objectId: mappingModalState.objectId,
            controllerDeviceId: mappingModalState.controllerDeviceId,
            controllerIPAddress: mappingModalState.controllerIPAddress,
          }}
          pointLabel={mappingModalState.pointLabel}
          pointDescription={mappingModalState.pointDescription}
          templates={templates}
          onSaved={handleMappingSaved}
          onOpenChange={closeMappingModal}
        />
      )}
    </div>
  )
}
