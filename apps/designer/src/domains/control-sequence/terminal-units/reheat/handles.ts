/**
 * G36 VAV Reheat handle definitions.
 *
 * These arrays are type-constrained using `satisfies` to ensure they match
 * the keys from the generated ReheatInputsRequest and ReheatOutputs types.
 *
 * TypeScript will error if any key is missing or misspelled.
 */

import type {
  InputCategory,
  ReheatInputsDto,
  ReheatOutputsDto,
} from '../../api/generated/types.gen'

type RequiredKeys<T> = {
  [K in keyof T]-?: undefined extends T[K] ? never : K
}[keyof T]

type OptionalKeys<T> = {
  [K in keyof T]-?: undefined extends T[K] ? K : never
}[keyof T]

export const REQUIRED_INPUTS = [
  'zoneTemperature',
  'coolingSetpoint',
  'heatingSetpoint',
  'dischargeAirTemperature',
  'primaryAirflow',
  'supplyAirTemperature',
  'supplyAirTemperatureSetpoint',
  'fanStatus',
  'operationMode',
] as const satisfies readonly RequiredKeys<ReheatInputsDto>[]

export const OPTIONAL_INPUTS = [
  'co2Concentration',
  'co2Setpoint',
  'hotWaterPlantStatus',
  'occupancyStatus',
  'windowStatus',
  'heatingOff',
  'overrideDamperPosition',
  'overrideFlowSetpoint',
] as const satisfies readonly OptionalKeys<ReheatInputsDto>[]

export const ALL_OUTPUTS = [
  'damperPosition',
  'valvePosition',
  'airflowSetpoint',
  'minOutdoorAirflow',
  'adjAreaBreathingZoneFlow',
  'adjPopBreathingZoneFlow',
  'flowSensorAlarm',
  'heatingValveRequest',
  'hotWaterPlantRequest',
  'leakingDamperAlarm',
  'leakingValveAlarm',
  'lowFlowAlarm',
  'lowTempAlarm',
  'zonePressureRequest',
  'zoneTempRequest',
] as const satisfies readonly (keyof ReheatOutputsDto)[]

export const ALL_INPUTS = [...REQUIRED_INPUTS, ...OPTIONAL_INPUTS] as const

export type ReheatInputHandle = (typeof ALL_INPUTS)[number]
export type ReheatOutputHandle = (typeof ALL_OUTPUTS)[number]
