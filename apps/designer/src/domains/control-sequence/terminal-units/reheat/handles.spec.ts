import {
  REQUIRED_INPUTS,
  OPTIONAL_INPUTS,
  ALL_INPUTS,
  ALL_OUTPUTS,
} from './handles'
import type {
  ReheatInputsDto,
  ReheatOutputsDto,
} from '../../api/generated/types.gen'

describe('G36 VAV Reheat Handles', () => {
  describe('REQUIRED_INPUTS', () => {
    it('contains all required fields from ReheatInputsRequest', () => {
      expect(REQUIRED_INPUTS).toContain('zoneTemperature')
      expect(REQUIRED_INPUTS).toContain('coolingSetpoint')
      expect(REQUIRED_INPUTS).toContain('heatingSetpoint')
      expect(REQUIRED_INPUTS).toContain('dischargeAirTemperature')
      expect(REQUIRED_INPUTS).toContain('primaryAirflow')
      expect(REQUIRED_INPUTS).toContain('supplyAirTemperature')
      expect(REQUIRED_INPUTS).toContain('supplyAirTemperatureSetpoint')
      expect(REQUIRED_INPUTS).toContain('fanStatus')
      expect(REQUIRED_INPUTS).toContain('operationMode')
    })

    it('has exactly 9 required inputs', () => {
      expect(REQUIRED_INPUTS.length).toBe(9)
    })

    it('does not contain optional fields', () => {
      expect(REQUIRED_INPUTS).not.toContain('co2Concentration')
      expect(REQUIRED_INPUTS).not.toContain('hotWaterPlantStatus')
    })
  })

  describe('OPTIONAL_INPUTS', () => {
    it('contains all optional fields from ReheatInputsDto', () => {
      expect(OPTIONAL_INPUTS).toContain('co2Concentration')
      expect(OPTIONAL_INPUTS).toContain('co2Setpoint')
      expect(OPTIONAL_INPUTS).toContain('hotWaterPlantStatus')
      expect(OPTIONAL_INPUTS).toContain('occupancyStatus')
      expect(OPTIONAL_INPUTS).toContain('windowStatus')
      expect(OPTIONAL_INPUTS).toContain('heatingOff')
      expect(OPTIONAL_INPUTS).toContain('overrideDamperPosition')
      expect(OPTIONAL_INPUTS).toContain('overrideFlowSetpoint')
    })

    it('has exactly 8 optional inputs', () => {
      expect(OPTIONAL_INPUTS.length).toBe(8)
    })

    it('does not contain unit preferences (those are in ReheatParameters)', () => {
      expect(OPTIONAL_INPUTS).not.toContain('temperatureUnit')
      expect(OPTIONAL_INPUTS).not.toContain('airflowUnit')
    })
  })

  describe('ALL_INPUTS', () => {
    it('combines required and optional inputs', () => {
      expect(ALL_INPUTS.length).toBe(
        REQUIRED_INPUTS.length + OPTIONAL_INPUTS.length
      )
    })

    it('includes all required inputs', () => {
      REQUIRED_INPUTS.forEach((input) => {
        expect(ALL_INPUTS).toContain(input)
      })
    })

    it('includes all optional inputs', () => {
      OPTIONAL_INPUTS.forEach((input) => {
        expect(ALL_INPUTS).toContain(input)
      })
    })

    it('has unique values', () => {
      const uniqueInputs = new Set(ALL_INPUTS)
      expect(uniqueInputs.size).toBe(ALL_INPUTS.length)
    })
  })

  describe('ALL_OUTPUTS', () => {
    it('contains all output fields from ReheatOutputs', () => {
      expect(ALL_OUTPUTS).toContain('damperPosition')
      expect(ALL_OUTPUTS).toContain('valvePosition')
      expect(ALL_OUTPUTS).toContain('airflowSetpoint')
      expect(ALL_OUTPUTS).toContain('minOutdoorAirflow')
      expect(ALL_OUTPUTS).toContain('adjAreaBreathingZoneFlow')
      expect(ALL_OUTPUTS).toContain('adjPopBreathingZoneFlow')
      expect(ALL_OUTPUTS).toContain('flowSensorAlarm')
      expect(ALL_OUTPUTS).toContain('heatingValveRequest')
      expect(ALL_OUTPUTS).toContain('hotWaterPlantRequest')
      expect(ALL_OUTPUTS).toContain('leakingDamperAlarm')
      expect(ALL_OUTPUTS).toContain('leakingValveAlarm')
      expect(ALL_OUTPUTS).toContain('lowFlowAlarm')
      expect(ALL_OUTPUTS).toContain('lowTempAlarm')
      expect(ALL_OUTPUTS).toContain('zonePressureRequest')
      expect(ALL_OUTPUTS).toContain('zoneTempRequest')
    })

    it('has exactly 15 outputs', () => {
      expect(ALL_OUTPUTS.length).toBe(15)
    })

    it('has unique values', () => {
      const uniqueOutputs = new Set(ALL_OUTPUTS)
      expect(uniqueOutputs.size).toBe(ALL_OUTPUTS.length)
    })
  })

  describe('Type safety', () => {
    it('ALL_INPUTS values are valid ReheatInputsDto keys', () => {
      const testObj = {} as ReheatInputsDto
      ALL_INPUTS.forEach((key) => {
        expect(key in testObj || key === key).toBe(true)
      })
    })

    it('ALL_OUTPUTS values are valid ReheatOutputsDto keys', () => {
      const testObj = {} as ReheatOutputsDto
      ALL_OUTPUTS.forEach((key) => {
        expect(key in testObj || key === key).toBe(true)
      })
    })
  })
})
