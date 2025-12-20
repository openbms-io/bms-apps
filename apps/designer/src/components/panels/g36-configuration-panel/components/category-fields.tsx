'use client'

import { Input } from '@/components/ui/input'
import { Label } from '@/components/ui/label'
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import { UnitSelect } from './unit-select'
import { SensorToggle } from './sensor-toggle'
import {
  type CategoryFieldsProps,
  type TemperatureUnit,
  type AirflowUnit,
  TEMPERATURE_UNIT_OPTIONS,
  AIRFLOW_UNIT_OPTIONS,
} from '../types'
import type { ReheatParameters } from '@/domains/control-sequence'
import type { DropdownOption } from '@/domains/control-sequence/terminal-units/reheat'
import { camelToLabel } from '@/lib/utils'

function NumericTextInputField({
  field,
  label,
  value,
  onValueChange,
}: {
  field: string
  label: string
  value: number | undefined
  onValueChange: (value: number | undefined) => void
}) {
  return (
    <div className="grid grid-cols-2 gap-2 items-center">
      <Label htmlFor={field} className="text-sm">
        {label}
      </Label>
      <Input
        id={field}
        type="number"
        step="any"
        value={value ?? ''}
        onChange={(e) => {
          const val = e.target.value
          onValueChange(val === '' ? undefined : Number(val))
        }}
        className="h-8"
      />
    </div>
  )
}

function DropdownField<T extends number | boolean>({
  field,
  label,
  value,
  options,
  onValueChange,
}: {
  field: string
  label: string
  value: T | undefined
  options: readonly DropdownOption<T>[]
  onValueChange: (value: T) => void
}) {
  return (
    <div className="grid grid-cols-2 gap-2 items-center">
      <Label htmlFor={field} className="text-sm">
        {label}
      </Label>
      <Select
        value={value?.toString()}
        onValueChange={(val) => {
          const option = options.find((opt) => opt.value.toString() === val)
          if (option) onValueChange(option.value)
        }}
      >
        <SelectTrigger id={field} className="h-8">
          <SelectValue placeholder="Select..." />
        </SelectTrigger>
        <SelectContent>
          {options.map((opt) => (
            <SelectItem key={opt.value.toString()} value={opt.value.toString()}>
              {opt.label}
            </SelectItem>
          ))}
        </SelectContent>
      </Select>
    </div>
  )
}

export function CategoryFields({
  category,
  fields,
  parameters,
  onParameterChange,
  onUnitChange,
  dropdownFields,
}: CategoryFieldsProps) {
  if (category === 'units') {
    return (
      <div className="space-y-4">
        {fields.includes('temperatureUnit') && (
          <UnitSelect<TemperatureUnit>
            label="Temperature Unit"
            value={parameters.temperatureUnit}
            options={TEMPERATURE_UNIT_OPTIONS}
            onValueChange={(value) => onUnitChange('temperatureUnit', value)}
          />
        )}
        {fields.includes('airflowUnit') && (
          <UnitSelect<AirflowUnit>
            label="Airflow Unit"
            value={parameters.airflowUnit}
            options={AIRFLOW_UNIT_OPTIONS}
            onValueChange={(value) => onUnitChange('airflowUnit', value)}
          />
        )}
      </div>
    )
  }

  if (category === 'sensors') {
    return (
      <div className="space-y-4">
        {fields.map((field) => (
          <SensorToggle
            key={field}
            field={field as keyof typeof parameters}
            label={camelToLabel(field)}
            checked={Boolean(parameters[field as keyof typeof parameters])}
            onCheckedChange={(checked) =>
              onParameterChange(field as keyof typeof parameters, checked)
            }
          />
        ))}
      </div>
    )
  }

  return (
    <div className="space-y-3">
      {fields.map((field) => {
        const dropdownOptions = dropdownFields?.[field]
        if (dropdownOptions) {
          return (
            <DropdownField
              key={field}
              field={field}
              label={camelToLabel(field)}
              value={
                parameters[field as keyof ReheatParameters] as
                  | number
                  | boolean
                  | undefined
              }
              options={dropdownOptions}
              onValueChange={(value) =>
                onParameterChange(field as keyof ReheatParameters, value)
              }
            />
          )
        }
        return (
          <NumericTextInputField
            key={field}
            field={field}
            label={camelToLabel(field)}
            value={
              parameters[field as keyof ReheatParameters] as number | undefined
            }
            onValueChange={(value) =>
              onParameterChange(field as keyof ReheatParameters, value)
            }
          />
        )
      })}
    </div>
  )
}
