import { camelToLabel } from '@/lib/utils'

// G36 sequences are parameterized - the same logical output can represent
// different physical actuators (e.g., valvePosition → hot water valve vs electric heater)
// depending on terminal unit configuration parameters like hasHotWaterCoil.
export interface ConditionalLabel<
  THandle extends string,
  TParams extends Record<string, unknown>,
> {
  handle: THandle
  parameter: keyof TParams
  whenTrue: string
  whenFalse: string
}

export function getHandleLabel<
  THandle extends string,
  TParams extends Record<string, unknown>,
>(
  handle: THandle,
  params: TParams,
  conditionalLabels: readonly ConditionalLabel<THandle, TParams>[]
): string {
  const override = conditionalLabels.find((c) => c.handle === handle)
  if (override) {
    return params[override.parameter] ? override.whenTrue : override.whenFalse
  }
  return camelToLabel(handle)
}
