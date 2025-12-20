import { useMutation } from '@tanstack/react-query'
import { convertParameters } from '../client'
import type {
  AirflowUnit,
  ReheatParameters,
  SequenceType,
  TemperatureUnit,
} from '../generated/types.gen'

interface ConvertParametersParams {
  sequenceType: SequenceType
  parameters: ReheatParameters
  targetTemperatureUnit: TemperatureUnit
  targetAirflowUnit: AirflowUnit
}

export function useConvertParametersMutation() {
  return useMutation({
    mutationFn: ({
      sequenceType,
      parameters,
      targetTemperatureUnit,
      targetAirflowUnit,
    }: ConvertParametersParams) =>
      convertParameters({
        sequenceType,
        parameters,
        targetTemperatureUnit,
        targetAirflowUnit,
      }),
  })
}
