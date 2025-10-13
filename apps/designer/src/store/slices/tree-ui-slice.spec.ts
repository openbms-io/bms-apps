import { createTreeUISlice, TreeUISlice } from './tree-ui-slice'
import { IotDeviceController } from '@/lib/domain/models/iot-device-controller'
import { ControllerPoint } from '@/lib/domain/models/controller-point'

describe('tree-ui-slice', () => {
  let slice: TreeUISlice

  beforeEach(() => {
    const set = (fn: any) => {
      const updates = typeof fn === 'function' ? fn(slice) : fn
      Object.assign(slice, updates)
    }
    const get = () => slice
    slice = createTreeUISlice(set, get, undefined as any)
  })

  const mockIotDevice = {
    id: 'iot-device-1',
    name: 'Test IoT Device',
  }

  const mockControllers: IotDeviceController[] = [
    {
      id: 'controller-1',
      organizationId: 'org_test',
      siteId: 'site-1',
      iotDeviceId: 'iot-device-1',
      ipAddress: '192.168.1.100',
      port: 47808,
      deviceId: 1001,
      name: 'Controller 1',
      isActive: true,
      createdAt: '2024-01-01T00:00:00Z',
      updatedAt: '2024-01-01T00:00:00Z',
    },
    {
      id: 'controller-2',
      organizationId: 'org_test',
      siteId: 'site-1',
      iotDeviceId: 'iot-device-1',
      ipAddress: '192.168.1.101',
      port: 47808,
      deviceId: 1002,
      name: 'Controller 2',
      isActive: false,
      createdAt: '2024-01-01T00:00:00Z',
      updatedAt: '2024-01-01T00:00:00Z',
    },
  ]

  const mockPoints: Record<string, ControllerPoint[]> = {
    'controller-1': [
      {
        id: 'point-1',
        organizationId: 'org_test',
        siteId: 'site-1',
        iotDeviceId: 'iot-device-1',
        controllerId: 'controller-1',
        pointName: 'Temperature Sensor',
        pointType: 'analogInput',
        objectIdentifier: '["analog-input",0]',
        instanceNumber: 0,
        writable: false,
        units: 'degreesFahrenheit',
        description: 'Room temperature',
        createdAt: '2024-01-01T00:00:00Z',
        updatedAt: '2024-01-01T00:00:00Z',
      },
      {
        id: 'point-2',
        organizationId: 'org_test',
        siteId: 'site-1',
        iotDeviceId: 'iot-device-1',
        controllerId: 'controller-1',
        pointName: 'Humidity Sensor',
        pointType: 'analogInput',
        objectIdentifier: '["analog-input",1]',
        instanceNumber: 1,
        writable: false,
        units: 'percent',
        createdAt: '2024-01-01T00:00:00Z',
        updatedAt: '2024-01-01T00:00:00Z',
      },
    ],
    'controller-2': [],
  }

  describe('toggleNode', () => {
    it('should expand node when collapsed', () => {
      expect(slice.expandedNodes.has('node-1')).toBe(false)

      slice.toggleNode('node-1')

      expect(slice.expandedNodes.has('node-1')).toBe(true)
    })

    it('should collapse node when expanded', () => {
      slice.expandedNodes.add('node-1')

      slice.toggleNode('node-1')

      expect(slice.expandedNodes.has('node-1')).toBe(false)
    })
  })

  describe('selectPoint', () => {
    it('should select point by id', () => {
      slice.selectPoint('point-1')

      expect(slice.selectedPointId).toBe('point-1')
    })

    it('should deselect when null is passed', () => {
      slice.selectedPointId = 'point-1'

      slice.selectPoint(null)

      expect(slice.selectedPointId).toBeNull()
    })
  })

  describe('expandAll', () => {
    it('should expand all provided node ids', () => {
      const nodeIds = ['node-1', 'node-2', 'node-3']

      slice.expandAll(nodeIds)

      nodeIds.forEach((id) => {
        expect(slice.expandedNodes.has(id)).toBe(true)
      })
    })
  })

  describe('collapseAll', () => {
    it('should collapse all nodes', () => {
      slice.expandedNodes.add('node-1')
      slice.expandedNodes.add('node-2')

      slice.collapseAll()

      expect(slice.expandedNodes.size).toBe(0)
    })
  })

  describe('getTreeData', () => {
    it('should return empty array when no iotDevice', () => {
      const result = slice.getTreeData(mockControllers, undefined, {})

      expect(result).toEqual([])
    })

    it('should create supervisor node with collapsed controllers', () => {
      const result = slice.getTreeData(mockControllers, mockIotDevice, {})

      expect(result).toHaveLength(1)
      expect(result[0].id).toBe('iot-device-1')
      expect(result[0].type).toBe('supervisor')
      expect(result[0].label).toBe('Test IoT Device')
      expect(result[0].hasChildren).toBe(true)
      expect(result[0].children).toEqual([])
    })

    it('should expand supervisor and show controllers when expanded', () => {
      slice.expandedNodes.add('iot-device-1')

      const result = slice.getTreeData(mockControllers, mockIotDevice, {})

      expect(result[0].isExpanded).toBe(true)
      expect(result[0].children).toHaveLength(2)
      expect(result[0].children![0].id).toBe('controller-1')
      expect(result[0].children![0].label).toBe('Controller 1')
      expect(result[0].children![1].id).toBe('controller-2')
    })

    it('should show controller with points when expanded', () => {
      slice.expandedNodes.add('iot-device-1')
      slice.expandedNodes.add('controller-1')

      const result = slice.getTreeData(
        mockControllers,
        mockIotDevice,
        mockPoints
      )

      const controller = result[0].children![0]
      expect(controller.hasChildren).toBe(true)
      expect(controller.isExpanded).toBe(true)
      expect(controller.children).toHaveLength(2)
      expect(controller.children![0].type).toBe('point')
      expect(controller.children![0].label).toBe('Temperature Sensor')
      expect(controller.children![1].label).toBe('Humidity Sensor')
    })

    it('should show controller without points when controller has no points', () => {
      slice.expandedNodes.add('iot-device-1')
      slice.expandedNodes.add('controller-2')

      const result = slice.getTreeData(
        mockControllers,
        mockIotDevice,
        mockPoints
      )

      const controller = result[0].children![1]
      expect(controller.hasChildren).toBe(false)
      expect(controller.isExpanded).toBe(true) // Expanded but no children
      expect(controller.children).toEqual([])
    })

    it('should include point details in tree node data', () => {
      slice.expandedNodes.add('iot-device-1')
      slice.expandedNodes.add('controller-1')

      const result = slice.getTreeData(
        mockControllers,
        mockIotDevice,
        mockPoints
      )

      const pointNode = result[0].children![0].children![0]
      expect(pointNode.type).toBe('point')
      expect(pointNode.data).toEqual(mockPoints['controller-1'][0])
      expect(pointNode.sublabel).toBe('analogInput (0)')
      expect(pointNode.depth).toBe(2)
    })
  })
})
