import { StateCreator } from 'zustand'
import { TreeNode } from '@/types/infrastructure'
import { IotDeviceController } from '@/lib/domain/models/iot-device-controller'

export interface TreeUISlice {
  // UI State only
  expandedNodes: Set<string>
  selectedPointId: string | null

  // UI Actions
  toggleNode: (nodeId: string) => void
  selectPoint: (pointId: string | null) => void
  expandAll: (allNodeIds: string[]) => void
  collapseAll: () => void

  // Simple tree transform - just supervisors → controllers (no points yet)
  getTreeData: (
    controllers: IotDeviceController[],
    iotDevice: { id: string; name: string } | undefined
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
    iotDevice: { id: string; name: string } | undefined
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
        const controllerNode: TreeNode = {
          id: controller.id,
          type: 'controller',
          label: controller.name,
          sublabel: `${controller.ipAddress}:${controller.port}`,
          icon: controller.isActive ? '🟢' : '🔴',
          depth: 1,
          hasChildren: false, // No points yet
          isExpanded: false,
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

        supervisorNode.children!.push(controllerNode)
      })
    }

    return [supervisorNode]
  },
})
