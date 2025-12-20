/**
 * G36 VAV Reheat parameter dropdown options.
 *
 * These options provide human-readable labels for enum parameters
 * used in the configuration panel.
 */

export type DropdownOption<T> = {
  readonly value: T
  readonly label: string
}

type ControllerType = 1 | 2 | 3 | 4
type VentilationStandard = 1 | 2

export const CONTROLLER_TYPE_OPTIONS: readonly DropdownOption<ControllerType>[] =
  [
    { value: 1, label: 'P (Proportional)' },
    { value: 2, label: 'PI (Proportional-Integral)' },
    { value: 3, label: 'PD (Proportional-Derivative)' },
    { value: 4, label: 'PID (Full PID)' },
  ] as const

export const VENTILATION_STANDARD_OPTIONS: readonly DropdownOption<VentilationStandard>[] =
  [
    { value: 1, label: 'ASHRAE 62.1' },
    { value: 2, label: 'California Title 24' },
  ] as const

export const PERMIT_OCC_STANDBY_OPTIONS: readonly DropdownOption<boolean>[] = [
  { value: true, label: 'Enabled' },
  { value: false, label: 'Disabled' },
] as const

export const REHEAT_ENUM_FIELDS = {
  controllerTypeDamper: CONTROLLER_TYPE_OPTIONS,
  controllerTypeValve: CONTROLLER_TYPE_OPTIONS,
  ventilationStandard: VENTILATION_STANDARD_OPTIONS,
  permitOccStandby: PERMIT_OCC_STANDBY_OPTIONS,
} as const

export type ReheatEnumFieldName = keyof typeof REHEAT_ENUM_FIELDS
