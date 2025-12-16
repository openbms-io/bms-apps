'use client'

import { Label } from '@/components/ui/label'
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import type { TemperatureUnit, AirflowUnit, UnitOption } from '../types'

interface UnitSelectProps<T extends TemperatureUnit | AirflowUnit> {
  label: string
  value: T | undefined
  options: readonly UnitOption<T>[]
  onValueChange: (value: T) => void
}

export function UnitSelect<T extends TemperatureUnit | AirflowUnit>({
  label,
  value,
  options,
  onValueChange,
}: UnitSelectProps<T>) {
  return (
    <div className="space-y-2">
      <Label>{label}</Label>
      <Select value={value} onValueChange={(v) => onValueChange(v as T)}>
        <SelectTrigger>
          <SelectValue />
        </SelectTrigger>
        <SelectContent>
          {options.map((option) => (
            <SelectItem key={option.value} value={option.value}>
              {option.label}
            </SelectItem>
          ))}
        </SelectContent>
      </Select>
    </div>
  )
}
