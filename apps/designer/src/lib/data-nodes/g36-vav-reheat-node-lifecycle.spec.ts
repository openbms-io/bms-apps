import { G36VavReheatNode } from './g36-vav-reheat-node'
import * as client from '@/domains/control-sequence/api/client'

jest.mock('@/domains/control-sequence/api/client', () => ({
  createInstance: jest.fn(),
  deleteFmu: jest.fn(),
}))

const mockCreateInstance = client.createInstance as jest.Mock
const mockDeleteFmu = client.deleteFmu as jest.Mock

describe('G36VavReheatNode Lifecycle', () => {
  beforeEach(() => {
    jest.clearAllMocks()
    mockCreateInstance.mockResolvedValue({
      instanceId: 'mock-instance',
      parameters: {},
      categories: {},
      parameterToRequiredInputs: {
        hasCO2Sensor: ['co2Concentration', 'co2Setpoint'],
        hasHotWaterCoil: ['hotWaterPlantStatus'],
        hasOccupancySensor: ['occupancyStatus'],
        hasWindowSensor: ['windowStatus'],
      },
    })
    mockDeleteFmu.mockResolvedValue({
      deleted: true,
      instanceId: 'mock-instance',
    })
  })

  describe('creation calls API', () => {
    it('calls createInstance API when creating a new node', async () => {
      await G36VavReheatNode.create({
        label: 'Test Node',
        id: 'test-node-id',
      })

      expect(mockCreateInstance).toHaveBeenCalledTimes(1)
      expect(mockCreateInstance).toHaveBeenCalledWith(
        expect.objectContaining({
          instance_id: expect.any(String),
        })
      )
    })

    it('uses provided instanceId in API call', async () => {
      await G36VavReheatNode.create({
        instanceId: 'custom-instance-id',
        label: 'Test Node',
        id: 'test-node-id',
      })

      expect(mockCreateInstance).toHaveBeenCalledWith({
        instance_id: 'custom-instance-id',
      })
    })

    it('generates instanceId when not provided', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Test Node',
        id: 'test-node-id',
      })

      expect(node.instanceId).toBeDefined()
      expect(node.instanceId).not.toBe('')
      expect(mockCreateInstance).toHaveBeenCalledWith({
        instance_id: node.instanceId,
      })
    })
  })

  describe('cleanup calls API', () => {
    it('calls deleteFmu API when cleanup is called', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'cleanup-test-instance',
        label: 'Cleanup Test',
        id: 'cleanup-test-id',
      })

      await node.cleanup()

      expect(mockDeleteFmu).toHaveBeenCalledTimes(1)
      expect(mockDeleteFmu).toHaveBeenCalledWith('cleanup-test-instance')
    })

    it('propagates API errors during cleanup', async () => {
      mockDeleteFmu.mockRejectedValue(new Error('Delete failed'))

      const node = await G36VavReheatNode.create({
        instanceId: 'error-test-instance',
        label: 'Error Test',
        id: 'error-test-id',
      })

      await expect(node.cleanup()).rejects.toThrow('Delete failed')
    })
  })

  describe('full lifecycle', () => {
    it('creates backend instance on node creation and cleans up FMU on cleanup', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'lifecycle-test',
        label: 'Lifecycle Test',
        id: 'lifecycle-node-id',
      })

      expect(mockCreateInstance).toHaveBeenCalledWith({
        instance_id: 'lifecycle-test',
      })
      expect(mockDeleteFmu).not.toHaveBeenCalled()

      await node.cleanup()

      expect(mockDeleteFmu).toHaveBeenCalledWith('lifecycle-test')
    })
  })
})
