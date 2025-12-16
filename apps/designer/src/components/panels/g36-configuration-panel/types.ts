import type {
  ReheatParameters,
  ParameterCategory,
  TemperatureUnit,
  AirflowUnit,
} from '@/domains/control-sequence/api/generated/types.gen'
import type {
  ControlSequenceInputHandle,
  SequenceType,
  DropdownFieldsMap,
} from '@/domains/control-sequence'
import type { DropdownOption } from '@/domains/control-sequence/terminal-units/reheat'

export type {
  ReheatParameters,
  ParameterCategory,
  TemperatureUnit,
  AirflowUnit,
}

export type { DropdownFieldsMap }

export interface G36ConfigurationPanelProps {
  instanceId: string
  sequenceType: SequenceType
  isOpen: boolean
  onClose: () => void
  onHandlesChange: (visibleInputs: ControlSequenceInputHandle[]) => void
  onSaveParameters: () => Promise<void>
}

export interface CategoryFieldsProps {
  category: ParameterCategory
  fields: string[]
  parameters: ReheatParameters
  onParameterChange: <K extends keyof ReheatParameters>(
    key: K,
    value: ReheatParameters[K]
  ) => void
  onUnitChange: (
    unitType: 'temperatureUnit' | 'airflowUnit',
    value: TemperatureUnit | AirflowUnit
  ) => void
  dropdownFields?: DropdownFieldsMap
}

export interface UnitSelectProps<T extends TemperatureUnit | AirflowUnit> {
  label: string
  value: T | undefined
  options: readonly UnitOption<T>[]
  onValueChange: (value: T) => void
}

export interface UnitOption<T extends string> {
  value: T
  label: string
}

export interface SensorToggleProps {
  field: keyof ReheatParameters
  label: string
  checked: boolean
  onCheckedChange: (checked: boolean) => void
}

export interface CollapsibleSectionProps {
  title: string
  defaultOpen?: boolean
  badge?: string
  children: React.ReactNode
}

export const TEMPERATURE_UNIT_OPTIONS: readonly UnitOption<TemperatureUnit>[] =
  [
    { value: 'K', label: 'Kelvin (K)' },
    { value: 'C', label: 'Celsius (°C)' },
    { value: 'F', label: 'Fahrenheit (°F)' },
  ] as const

export const AIRFLOW_UNIT_OPTIONS: readonly UnitOption<AirflowUnit>[] = [
  { value: 'm3/s', label: 'm³/s' },
  { value: 'cfm', label: 'CFM' },
  { value: 'L/s', label: 'L/s' },
  { value: 'm3/h', label: 'm³/h' },
] as const

export const BASIC_CATEGORIES: ParameterCategory[] = [
  'units',
  'features',
  'sensors',
]
