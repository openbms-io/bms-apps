import {
  createInstance,
  deleteInstance,
  deleteFmu,
  getInstance,
  stepInstance,
  updateInstance,
} from './client'
import * as generatedSdk from './generated/sdk.gen'

jest.mock('./generated/sdk.gen', () => ({
  createInstanceApiV1G36VavReheatInstancesPost: jest.fn(),
  deleteInstanceApiV1G36VavReheatInstancesInstanceIdDelete: jest.fn(),
  deleteFmuApiV1G36VavReheatInstancesInstanceIdFmuDelete: jest.fn(),
  getInstanceApiV1G36VavReheatInstancesInstanceIdGet: jest.fn(),
  stepApiV1G36VavReheatInstancesInstanceIdStepPost: jest.fn(),
  updateInstanceApiV1G36VavReheatInstancesInstanceIdPut: jest.fn(),
}))

const mockCreateInstance =
  generatedSdk.createInstanceApiV1G36VavReheatInstancesPost as jest.Mock
const mockDeleteInstance =
  generatedSdk.deleteInstanceApiV1G36VavReheatInstancesInstanceIdDelete as jest.Mock
const mockDeleteFmu =
  generatedSdk.deleteFmuApiV1G36VavReheatInstancesInstanceIdFmuDelete as jest.Mock
const mockGetInstance =
  generatedSdk.getInstanceApiV1G36VavReheatInstancesInstanceIdGet as jest.Mock
const mockStepInstance =
  generatedSdk.stepApiV1G36VavReheatInstancesInstanceIdStepPost as jest.Mock
const mockUpdateInstance =
  generatedSdk.updateInstanceApiV1G36VavReheatInstancesInstanceIdPut as jest.Mock

describe('Control Sequence API Client', () => {
  beforeEach(() => {
    jest.clearAllMocks()
  })

  describe('createInstance', () => {
    it('creates instance successfully', async () => {
      const mockResponse = {
        data: {
          instance_id: 'test-instance-123',
          parameters: {
            VMinCooMax: 1.0,
            VMinCooMin: 0.1,
          },
        },
        error: undefined,
      }
      mockCreateInstance.mockResolvedValue(mockResponse)

      const result = await createInstance({ instance_id: 'test-instance-123' })

      expect(mockCreateInstance).toHaveBeenCalledWith({
        body: { instance_id: 'test-instance-123' },
      })
      expect(result.instance_id).toBe('test-instance-123')
    })

    it('throws error on API error response', async () => {
      const mockResponse = {
        data: undefined,
        error: { detail: 'Instance already exists' },
      }
      mockCreateInstance.mockResolvedValue(mockResponse)

      await expect(
        createInstance({ instance_id: 'duplicate-id' })
      ).rejects.toThrow('Instance already exists')
    })

    it('throws generic error when detail is missing', async () => {
      const mockResponse = {
        data: undefined,
        error: {},
      }
      mockCreateInstance.mockResolvedValue(mockResponse)

      await expect(createInstance({ instance_id: 'test' })).rejects.toThrow(
        'Failed to create control sequence instance'
      )
    })
  })

  describe('deleteInstance', () => {
    it('deletes instance successfully', async () => {
      const mockResponse = {
        data: {
          instance_id: 'test-instance-123',
          deleted: true,
        },
        error: undefined,
      }
      mockDeleteInstance.mockResolvedValue(mockResponse)

      const result = await deleteInstance('test-instance-123')

      expect(mockDeleteInstance).toHaveBeenCalledWith({
        path: { instance_id: 'test-instance-123' },
      })
      expect(result.deleted).toBe(true)
      expect(result.instance_id).toBe('test-instance-123')
    })

    it('throws error on API error response', async () => {
      const mockResponse = {
        data: undefined,
        error: { detail: 'Instance not found' },
      }
      mockDeleteInstance.mockResolvedValue(mockResponse)

      await expect(deleteInstance('nonexistent-id')).rejects.toThrow(
        'Instance not found'
      )
    })

    it('throws generic error when detail is missing', async () => {
      const mockResponse = {
        data: undefined,
        error: {},
      }
      mockDeleteInstance.mockResolvedValue(mockResponse)

      await expect(deleteInstance('test')).rejects.toThrow(
        'Failed to delete control sequence instance'
      )
    })
  })

  describe('deleteFmu', () => {
    it('deletes FMU successfully while preserving DB parameters', async () => {
      const mockResponse = {
        data: {
          instance_id: 'test-instance-123',
          deleted: true,
        },
        error: undefined,
      }
      mockDeleteFmu.mockResolvedValue(mockResponse)

      const result = await deleteFmu('test-instance-123')

      expect(mockDeleteFmu).toHaveBeenCalledWith({
        path: { instance_id: 'test-instance-123' },
      })
      expect(result.deleted).toBe(true)
      expect(result.instance_id).toBe('test-instance-123')
    })

    it('returns deleted false when FMU does not exist', async () => {
      const mockResponse = {
        data: {
          instance_id: 'no-fmu-instance',
          deleted: false,
        },
        error: undefined,
      }
      mockDeleteFmu.mockResolvedValue(mockResponse)

      const result = await deleteFmu('no-fmu-instance')

      expect(result.deleted).toBe(false)
    })

    it('throws error on API error response', async () => {
      const mockResponse = {
        data: undefined,
        error: { detail: 'Server error' },
      }
      mockDeleteFmu.mockResolvedValue(mockResponse)

      await expect(deleteFmu('error-instance')).rejects.toThrow('Server error')
    })

    it('throws generic error when detail is missing', async () => {
      const mockResponse = {
        data: undefined,
        error: {},
      }
      mockDeleteFmu.mockResolvedValue(mockResponse)

      await expect(deleteFmu('test')).rejects.toThrow(
        'Failed to delete FMU instance'
      )
    })
  })

  describe('stepInstance', () => {
    const validStepRequest = {
      stepSize: 1.0,
      inputs: {
        zoneTemperature: 22.0,
        coolingSetpoint: 24.0,
        heatingSetpoint: 20.0,
        dischargeAirTemperature: 16.0,
        primaryAirflow: 0.3,
        supplyAirTemperature: 13.0,
        supplyAirTemperatureSetpoint: 12.0,
        fanStatus: true,
        operationMode: 'occupied' as const,
      },
    }

    it('executes step successfully', async () => {
      const mockResponse = {
        data: {
          instance_id: 'test-instance-123',
          outputs: {
            damperPosition: 0.5,
            valvePosition: 0.3,
            airflowSetpoint: 0.25,
          },
        },
        error: undefined,
      }
      mockStepInstance.mockResolvedValue(mockResponse)

      const result = await stepInstance('test-instance-123', validStepRequest)

      expect(mockStepInstance).toHaveBeenCalledWith({
        path: { instance_id: 'test-instance-123' },
        body: validStepRequest,
      })
      expect(result.instance_id).toBe('test-instance-123')
      expect(result.outputs.damperPosition).toBe(0.5)
      expect(result.outputs.valvePosition).toBe(0.3)
    })

    it('throws error on API error response', async () => {
      const mockResponse = {
        data: undefined,
        error: { detail: 'Instance not found' },
      }
      mockStepInstance.mockResolvedValue(mockResponse)

      await expect(
        stepInstance('nonexistent-id', validStepRequest)
      ).rejects.toThrow('Instance not found')
    })

    it('throws error with validation details', async () => {
      const mockResponse = {
        data: undefined,
        error: {
          detail:
            'zoneTemperature: 100.0 C is outside valid range [-23.1, 76.9] C',
        },
      }
      mockStepInstance.mockResolvedValue(mockResponse)

      await expect(
        stepInstance('test-instance', validStepRequest)
      ).rejects.toThrow('zoneTemperature')
    })

    it('throws generic error when detail is missing', async () => {
      const mockResponse = {
        data: undefined,
        error: {},
      }
      mockStepInstance.mockResolvedValue(mockResponse)

      await expect(stepInstance('test', validStepRequest)).rejects.toThrow(
        'Failed to execute control sequence step'
      )
    })
  })

  describe('getInstance', () => {
    it('gets instance successfully with categories', async () => {
      const mockResponse = {
        data: {
          instance_id: 'test-instance-123',
          parameters: {
            minAirflow: 0.3,
            maxCoolingAirflow: 1.5,
          },
          categories: {
            units: ['temperatureUnit', 'airflowUnit'],
            sensors: ['hasCO2Sensor', 'hasHotWaterCoil'],
          },
        },
        error: undefined,
      }
      mockGetInstance.mockResolvedValue(mockResponse)

      const result = await getInstance({ instanceId: 'test-instance-123' })

      expect(mockGetInstance).toHaveBeenCalledWith({
        path: { instance_id: 'test-instance-123' },
      })
      expect(result.instance_id).toBe('test-instance-123')
      expect(result.categories.units).toContain('temperatureUnit')
    })

    it('throws error on API error response', async () => {
      const mockResponse = {
        data: undefined,
        error: { detail: 'Instance not found' },
      }
      mockGetInstance.mockResolvedValue(mockResponse)

      await expect(
        getInstance({ instanceId: 'nonexistent-id' })
      ).rejects.toThrow('Instance not found')
    })

    it('throws generic error when detail is missing', async () => {
      const mockResponse = {
        data: undefined,
        error: {},
      }
      mockGetInstance.mockResolvedValue(mockResponse)

      await expect(getInstance({ instanceId: 'test' })).rejects.toThrow(
        'Failed to get control sequence instance'
      )
    })
  })

  describe('updateInstance', () => {
    it('updates instance successfully with categories', async () => {
      const mockResponse = {
        data: {
          instance_id: 'test-instance-123',
          parameters: {
            minAirflow: 0.5,
            maxCoolingAirflow: 2.0,
          },
          categories: {
            units: ['temperatureUnit', 'airflowUnit'],
            sensors: ['hasCO2Sensor', 'hasHotWaterCoil'],
          },
        },
        error: undefined,
      }
      mockUpdateInstance.mockResolvedValue(mockResponse)

      const result = await updateInstance({
        instanceId: 'test-instance-123',
        parameters: { minAirflow: 0.5, maxCoolingAirflow: 2.0 } as never,
      })

      expect(mockUpdateInstance).toHaveBeenCalledWith({
        path: { instance_id: 'test-instance-123' },
        body: { parameters: { minAirflow: 0.5, maxCoolingAirflow: 2.0 } },
      })
      expect(result.instance_id).toBe('test-instance-123')
      expect(result.parameters.minAirflow).toBe(0.5)
      expect(result.categories.units).toContain('temperatureUnit')
    })

    it('throws error on API error response', async () => {
      const mockResponse = {
        data: undefined,
        error: { detail: 'Instance not found' },
      }
      mockUpdateInstance.mockResolvedValue(mockResponse)

      await expect(
        updateInstance({
          instanceId: 'nonexistent-id',
          parameters: { minAirflow: 0.5 } as never,
        })
      ).rejects.toThrow('Instance not found')
    })

    it('throws generic error when detail is missing', async () => {
      const mockResponse = {
        data: undefined,
        error: {},
      }
      mockUpdateInstance.mockResolvedValue(mockResponse)

      await expect(
        updateInstance({
          instanceId: 'test',
          parameters: { minAirflow: 0.5 } as never,
        })
      ).rejects.toThrow('Failed to update control sequence instance')
    })
  })
})
