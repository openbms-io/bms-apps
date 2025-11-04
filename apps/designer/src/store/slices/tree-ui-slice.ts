import { StateCreator } from 'zustand'
import { TreeNode } from '@/types/infrastructure'
import { IotDeviceController } from '@/lib/domain/models/iot-device-controller'
import { ControllerPoint } from '@/lib/domain/models/controller-point'
import type { Equipment223PDTO } from '@/domains/223p/schemas'
import { createCompositeKey } from '@/domains/223p/utils/bacnet-keys'

export interface TreeUISlice {
  // UI State only
  expandedNodes: Set<string>
  selectedPointId: string | null

  // UI Actions
  toggleNode: (nodeId: string) => void
  selectPoint: (pointId: string | null) => void
  expandAll: (allNodeIds: string[]) => void
  collapseAll: () => void

  // Tree transform with points support
  getTreeData: (
    controllers: IotDeviceController[],
    iotDevice: { id: string; name: string } | undefined,
    pointsByController: Record<string, ControllerPoint[]>,
    mappings223p: Map<string, Equipment223PDTO>
  ) => TreeNode[]
}

export const createTreeUISlice: StateCreator<
  TreeUISlice,
  [],
  [],
  TreeUISlice
> = (set, get) => ({
  expandedNodes: new Set(),
  selectedPointId: null,

  toggleNode: (nodeId) => {
    set((state) => {
      const expandedNodes = new Set(state.expandedNodes)
      if (expandedNodes.has(nodeId)) {
        expandedNodes.delete(nodeId)
      } else {
        expandedNodes.add(nodeId)
      }
      return { expandedNodes }
    })
  },

  selectPoint: (pointId) => {
    set({ selectedPointId: pointId })
  },

  expandAll: (allNodeIds: string[]) => {
    set({ expandedNodes: new Set(allNodeIds) })
  },

  collapseAll: () => {
    set({ expandedNodes: new Set() })
  },

  getTreeData: (
    controllers: IotDeviceController[],
    iotDevice: { id: string; name: string } | undefined,
    pointsByController: Record<string, ControllerPoint[]>,
    mappings223p: Map<string, Equipment223PDTO>
  ) => {
    const { expandedNodes } = get()

    if (!iotDevice) return []

    const supervisorNode: TreeNode = {
      id: iotDevice.id,
      type: 'supervisor',
      label: iotDevice.name,
      icon: '🖥️',
      depth: 0,
      hasChildren: controllers.length > 0,
      isExpanded: expandedNodes.has(iotDevice.id),
      data: {
        id: iotDevice.id,
        name: iotDevice.name,
        status: 'active' as const,
        controllers: [],
      },
      children: [],
    }

    if (supervisorNode.isExpanded) {
      controllers.forEach((controller) => {
        const points = pointsByController[controller.id] || []
        const hasPoints = points.length > 0

        const controllerNode: TreeNode = {
          id: controller.id,
          type: 'controller',
          label: controller.name,
          sublabel: `${controller.ipAddress}:${controller.port}`,
          icon: controller.isActive ? '🟢' : '🔴',
          depth: 1,
          hasChildren: hasPoints,
          isExpanded: expandedNodes.has(controller.id),
          data: {
            id: controller.id,
            supervisorId: iotDevice.id,
            ipAddress: controller.ipAddress,
            name: controller.name,
            status: controller.isActive
              ? ('connected' as const)
              : ('disconnected' as const),
            discoveredPoints: [],
          },
          children: [],
        }

        if (controllerNode.isExpanded && hasPoints) {
          points.forEach((point) => {
            // Find controller to get BACnet deviceId
            const controller = controllers.find(
              (c) => c.id === point.controllerId
            )

            // Construct composite key: "device,123:analog-input,1"
            const compositeKey = controller
              ? createCompositeKey(
                  controller.deviceId,
                  point.pointType,
                  point.instanceNumber
                )
              : null

            const mapping223p = compositeKey
              ? mappings223p.get(compositeKey)
              : undefined

            const pointNode: TreeNode = {
              id: point.id,
              type: 'point',
              label: point.pointName || '',
              sublabel: `${point.pointType} (${point.instanceNumber})`,
              icon: point.writable ? '✏️' : '📊',
              depth: 2,
              hasChildren: false,
              isExpanded: false,
              data: point,
              children: [],
              mapping223p,
            }

            controllerNode.children!.push(pointNode)
          })
        }

        supervisorNode.children!.push(controllerNode)
      })
    }

    return [supervisorNode]
  },
})
