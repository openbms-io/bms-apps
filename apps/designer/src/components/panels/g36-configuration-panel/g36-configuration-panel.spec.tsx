'use client'

import { screen, waitFor } from '@testing-library/react'
import { renderWithProviders as render } from '@test-utils/render'
import userEvent from '@testing-library/user-event'
import { G36ConfigurationPanel } from './g36-configuration-panel'
import * as client from '@/domains/control-sequence/api/client'
import {
  SequenceTypeMap,
  type InstanceResponseWithCategoriesReheatParameters,
} from '@/domains/control-sequence'

jest.mock('@/domains/control-sequence/api/client')
const mockClient = client as jest.Mocked<typeof client>

const mockInstanceResponse: InstanceResponseWithCategoriesReheatParameters = {
  instanceId: 'test-instance-123',
  parameters: {
    temperatureUnit: 'C',
    airflowUnit: 'cfm',
    hasCO2Sensor: false,
    hasHotWaterCoil: true,
    hasOccupancySensor: false,
    hasWindowSensor: false,
    minAirflow: 0.1,
    maxCoolingAirflow: 0.5,
  },
  categories: {
    units: ['temperatureUnit', 'airflowUnit'],
    sensors: [
      'hasCO2Sensor',
      'hasHotWaterCoil',
      'hasOccupancySensor',
      'hasWindowSensor',
    ],
    airflows: ['minAirflow', 'maxCoolingAirflow'],
  },
  inputCategories: {
    zoneTemperature: ['zoneTemperature', 'coolingSetpoint', 'heatingSetpoint'],
    zoneAirQuality: ['co2Concentration', 'co2Setpoint'],
    zoneSensors: ['occupancyStatus', 'windowStatus'],
    vavTerminal: ['dischargeAirTemperature', 'primaryAirflow'],
    ahu: ['supplyAirTemperature', 'supplyAirTemperatureSetpoint', 'fanStatus'],
    plant: ['hotWaterPlantStatus'],
    control: [
      'operationMode',
      'heatingOff',
      'overrideDamperPosition',
      'overrideFlowSetpoint',
    ],
  },
  outputCategories: {
    vavControl: ['damperPosition', 'valvePosition'],
    ahuRequests: [
      'heatingValveRequest',
      'zonePressureRequest',
      'zoneTempRequest',
    ],
    plantRequests: ['hotWaterPlantRequest'],
    alarms: [
      'flowSensorAlarm',
      'leakingDamperAlarm',
      'leakingValveAlarm',
      'lowFlowAlarm',
      'lowTempAlarm',
    ],
    monitoring: [
      'airflowSetpoint',
      'minOutdoorAirflow',
      'adjAreaBreathingZoneFlow',
      'adjPopBreathingZoneFlow',
    ],
  },
  parameterToRequiredInputs: {
    hasCO2Sensor: ['co2Concentration', 'co2Setpoint'],
    hasHotWaterCoil: ['hotWaterPlantStatus'],
    hasOccupancySensor: ['occupancyStatus'],
    hasWindowSensor: ['windowStatus'],
  },
  parameterToRequiredOutputs: {
    hasHotWaterCoil: [
      'heatingValveRequest',
      'hotWaterPlantRequest',
      'lowTempAlarm',
      'leakingValveAlarm',
    ],
  },
}

describe('G36ConfigurationPanel', () => {
  const defaultProps = {
    instanceId: 'test-instance-123',
    sequenceType: SequenceTypeMap.VAV_REHEAT,
    isOpen: true,
    onClose: jest.fn(),
    onHandlesChange: jest.fn(),
    onSaveParameters: jest.fn().mockResolvedValue(undefined),
  }

  beforeEach(() => {
    jest.clearAllMocks()
    mockClient.getInstance.mockResolvedValue(mockInstanceResponse)
    mockClient.updateInstance.mockResolvedValue(mockInstanceResponse)
  })

  describe('rendering', () => {
    it('renders panel title when open', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(
        await screen.findByText('G36 VAV Reheat Configuration')
      ).toBeInTheDocument()
    })

    it('displays instance ID badge', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      await waitFor(() => {
        expect(screen.getByText('test-ins...')).toBeInTheDocument()
      })
    })

    it('shows loading state initially', () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(document.querySelector('.animate-spin')).toBeInTheDocument()
    })

    it('returns null when not open', () => {
      const { container } = render(
        <G36ConfigurationPanel {...defaultProps} isOpen={false} />
      )

      expect(container.firstChild).toBeNull()
    })
  })

  describe('basic settings section', () => {
    it('displays basic settings section expanded by default', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(await screen.findByText('Basic Settings')).toBeInTheDocument()
    })

    it('renders temperature unit selector', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(await screen.findByText('Temperature Unit')).toBeInTheDocument()
    })

    it('renders airflow unit selector', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(await screen.findByText('Airflow Unit')).toBeInTheDocument()
    })

    it('renders sensor toggles', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(await screen.findByText('Has CO2 Sensor')).toBeInTheDocument()
      expect(await screen.findByText('Has Hot Water Coil')).toBeInTheDocument()
      expect(
        await screen.findByText('Has Occupancy Sensor')
      ).toBeInTheDocument()
      expect(await screen.findByText('Has Window Sensor')).toBeInTheDocument()
    })
  })

  describe('advanced settings section', () => {
    it('displays advanced settings section collapsed by default', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(await screen.findByText('Advanced Settings')).toBeInTheDocument()
    })

    it('shows param count badge', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      await waitFor(() => {
        expect(screen.getByText('2 params')).toBeInTheDocument()
      })
    })

    it('expands advanced settings on click', async () => {
      const user = userEvent.setup()
      render(<G36ConfigurationPanel {...defaultProps} />)

      const advancedButton = await screen.findByRole('button', {
        name: /advanced settings/i,
      })
      await user.click(advancedButton)

      expect(await screen.findByText('Min Airflow')).toBeInTheDocument()
    })
  })

  describe('save and cancel functionality', () => {
    it('renders save button', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(
        await screen.findByRole('button', { name: 'Save' })
      ).toBeInTheDocument()
    })

    it('renders cancel button', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      expect(
        await screen.findByRole('button', { name: 'Cancel' })
      ).toBeInTheDocument()
    })

    it('calls onClose when cancel is clicked', async () => {
      const user = userEvent.setup()
      const onClose = jest.fn()
      render(<G36ConfigurationPanel {...defaultProps} onClose={onClose} />)

      await screen.findByText('Basic Settings')
      const cancelButton = screen.getByRole('button', { name: 'Cancel' })
      await user.click(cancelButton)

      expect(onClose).toHaveBeenCalled()
    })

    it('calls updateInstance when save is clicked', async () => {
      const user = userEvent.setup()
      render(<G36ConfigurationPanel {...defaultProps} />)

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(mockClient.updateInstance).toHaveBeenCalledWith({
          instanceId: 'test-instance-123',
          parameters: expect.objectContaining({
            temperatureUnit: 'C',
            airflowUnit: 'cfm',
          }),
        })
      })
    })

    it('calls onHandlesChange and onClose after successful save', async () => {
      const user = userEvent.setup()
      const onClose = jest.fn()
      const onHandlesChange = jest.fn()
      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onClose={onClose}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalled()
        expect(onClose).toHaveBeenCalled()
      })
    })
  })

  describe('error state', () => {
    it('displays error message when fetch fails', async () => {
      mockClient.getInstance.mockRejectedValue(new Error('Network error'))
      render(<G36ConfigurationPanel {...defaultProps} />)

      await waitFor(() => {
        expect(
          screen.getByText(/failed to load parameters/i)
        ).toBeInTheDocument()
      })
    })
  })

  describe('sensor toggle and visible inputs', () => {
    it('computes visible inputs with only required inputs when no sensor enabled', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithNoSensors: InstanceResponseWithCategoriesReheatParameters =
        {
          ...mockInstanceResponse,
          parameters: {
            ...mockInstanceResponse.parameters,
            hasCO2Sensor: false,
            hasHotWaterCoil: false,
            hasOccupancySensor: false,
            hasWindowSensor: false,
          },
        }
      mockClient.getInstance.mockResolvedValue(responseWithNoSensors)
      mockClient.updateInstance.mockResolvedValue(responseWithNoSensors)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalledWith({
          visibleInputs: expect.arrayContaining([
            'zoneTemperature',
            'coolingSetpoint',
            'heatingSetpoint',
            'dischargeAirTemperature',
            'primaryAirflow',
            'supplyAirTemperature',
            'supplyAirTemperatureSetpoint',
            'fanStatus',
            'operationMode',
          ]),
          visibleOutputs: expect.any(Array),
          parameters: expect.any(Object),
        })
      })

      const callArg = onHandlesChange.mock.calls[0][0].visibleInputs
      expect(callArg).not.toContain('co2Concentration')
      expect(callArg).not.toContain('hotWaterPlantStatus')
    })

    it('adds CO2 inputs when hasCO2Sensor is enabled', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithCO2: InstanceResponseWithCategoriesReheatParameters = {
        ...mockInstanceResponse,
        parameters: {
          ...mockInstanceResponse.parameters,
          hasCO2Sensor: true,
          hasHotWaterCoil: false,
          hasOccupancySensor: false,
          hasWindowSensor: false,
        },
      }
      mockClient.getInstance.mockResolvedValue(responseWithCO2)
      mockClient.updateInstance.mockResolvedValue(responseWithCO2)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalledWith({
          visibleInputs: expect.arrayContaining([
            'co2Concentration',
            'co2Setpoint',
          ]),
          visibleOutputs: expect.any(Array),
          parameters: expect.any(Object),
        })
      })
    })

    it('adds hot water plant status when hasHotWaterCoil is enabled', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithHotWater: InstanceResponseWithCategoriesReheatParameters =
        {
          ...mockInstanceResponse,
          parameters: {
            ...mockInstanceResponse.parameters,
            hasCO2Sensor: false,
            hasHotWaterCoil: true,
            hasOccupancySensor: false,
            hasWindowSensor: false,
          },
        }
      mockClient.getInstance.mockResolvedValue(responseWithHotWater)
      mockClient.updateInstance.mockResolvedValue(responseWithHotWater)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalledWith({
          visibleInputs: expect.arrayContaining(['hotWaterPlantStatus']),
          visibleOutputs: expect.arrayContaining([
            'heatingValveRequest',
            'hotWaterPlantRequest',
            'lowTempAlarm',
            'leakingValveAlarm',
          ]),
          parameters: expect.any(Object),
        })
      })
    })

    it('adds all sensor inputs when multiple sensors are enabled', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithAllSensors: InstanceResponseWithCategoriesReheatParameters =
        {
          ...mockInstanceResponse,
          parameters: {
            ...mockInstanceResponse.parameters,
            hasCO2Sensor: true,
            hasHotWaterCoil: true,
            hasOccupancySensor: true,
            hasWindowSensor: true,
          },
        }
      mockClient.getInstance.mockResolvedValue(responseWithAllSensors)
      mockClient.updateInstance.mockResolvedValue(responseWithAllSensors)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalledWith({
          visibleInputs: expect.arrayContaining([
            'co2Concentration',
            'co2Setpoint',
            'hotWaterPlantStatus',
            'occupancyStatus',
            'windowStatus',
          ]),
          visibleOutputs: expect.arrayContaining([
            'heatingValveRequest',
            'hotWaterPlantRequest',
            'lowTempAlarm',
            'leakingValveAlarm',
          ]),
          parameters: expect.any(Object),
        })
      })
    })

    it('fetches instance on mount with correct instanceId', async () => {
      render(<G36ConfigurationPanel {...defaultProps} />)

      await waitFor(() => {
        expect(mockClient.getInstance).toHaveBeenCalledWith({
          instanceId: 'test-instance-123',
        })
      })
    })
  })

  describe('conditional outputs', () => {
    it('excludes hot water outputs when hasHotWaterCoil is disabled', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithNoHotWater: InstanceResponseWithCategoriesReheatParameters =
        {
          ...mockInstanceResponse,
          parameters: {
            ...mockInstanceResponse.parameters,
            hasHotWaterCoil: false,
          },
        }
      mockClient.getInstance.mockResolvedValue(responseWithNoHotWater)
      mockClient.updateInstance.mockResolvedValue(responseWithNoHotWater)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalled()
      })

      const callArg = onHandlesChange.mock.calls[0][0].visibleOutputs
      expect(callArg).not.toContain('heatingValveRequest')
      expect(callArg).not.toContain('hotWaterPlantRequest')
      expect(callArg).not.toContain('lowTempAlarm')
      expect(callArg).not.toContain('leakingValveAlarm')
    })

    it('always includes base outputs regardless of parameters', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithNoSensors: InstanceResponseWithCategoriesReheatParameters =
        {
          ...mockInstanceResponse,
          parameters: {
            ...mockInstanceResponse.parameters,
            hasCO2Sensor: false,
            hasHotWaterCoil: false,
            hasOccupancySensor: false,
            hasWindowSensor: false,
          },
        }
      mockClient.getInstance.mockResolvedValue(responseWithNoSensors)
      mockClient.updateInstance.mockResolvedValue(responseWithNoSensors)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalledWith({
          visibleOutputs: expect.arrayContaining([
            'damperPosition',
            'valvePosition',
            'airflowSetpoint',
            'zonePressureRequest',
            'zoneTempRequest',
            'flowSensorAlarm',
            'leakingDamperAlarm',
            'lowFlowAlarm',
            'minOutdoorAirflow',
            'adjAreaBreathingZoneFlow',
            'adjPopBreathingZoneFlow',
          ]),
          visibleInputs: expect.any(Array),
          parameters: expect.any(Object),
        })
      })
    })
  })

  describe('conditional inputs - individual sensors', () => {
    it('adds occupancy status input when hasOccupancySensor is enabled', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithOccupancy: InstanceResponseWithCategoriesReheatParameters =
        {
          ...mockInstanceResponse,
          parameters: {
            ...mockInstanceResponse.parameters,
            hasCO2Sensor: false,
            hasHotWaterCoil: false,
            hasOccupancySensor: true,
            hasWindowSensor: false,
          },
        }
      mockClient.getInstance.mockResolvedValue(responseWithOccupancy)
      mockClient.updateInstance.mockResolvedValue(responseWithOccupancy)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalledWith({
          visibleInputs: expect.arrayContaining(['occupancyStatus']),
          visibleOutputs: expect.any(Array),
          parameters: expect.any(Object),
        })
      })

      const callArg = onHandlesChange.mock.calls[0][0].visibleInputs
      expect(callArg).not.toContain('co2Concentration')
      expect(callArg).not.toContain('windowStatus')
    })

    it('adds window status input when hasWindowSensor is enabled', async () => {
      const user = userEvent.setup()
      const onHandlesChange = jest.fn()

      const responseWithWindow: InstanceResponseWithCategoriesReheatParameters =
        {
          ...mockInstanceResponse,
          parameters: {
            ...mockInstanceResponse.parameters,
            hasCO2Sensor: false,
            hasHotWaterCoil: false,
            hasOccupancySensor: false,
            hasWindowSensor: true,
          },
        }
      mockClient.getInstance.mockResolvedValue(responseWithWindow)
      mockClient.updateInstance.mockResolvedValue(responseWithWindow)

      render(
        <G36ConfigurationPanel
          {...defaultProps}
          onHandlesChange={onHandlesChange}
        />
      )

      await screen.findByText('Basic Settings')
      const saveButton = screen.getByRole('button', { name: 'Save' })
      await user.click(saveButton)

      await waitFor(() => {
        expect(onHandlesChange).toHaveBeenCalledWith({
          visibleInputs: expect.arrayContaining(['windowStatus']),
          visibleOutputs: expect.any(Array),
          parameters: expect.any(Object),
        })
      })

      const callArg = onHandlesChange.mock.calls[0][0].visibleInputs
      expect(callArg).not.toContain('co2Concentration')
      expect(callArg).not.toContain('occupancyStatus')
    })
  })
})
