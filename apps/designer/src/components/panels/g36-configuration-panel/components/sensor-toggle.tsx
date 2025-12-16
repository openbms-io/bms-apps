'use client'

import { Label } from '@/components/ui/label'
import { Switch } from '@/components/ui/switch'
import type { SensorToggleProps } from '../types'

export function SensorToggle({
  field,
  label,
  checked,
  onCheckedChange,
}: SensorToggleProps) {
  const fieldId = String(field)

  return (
    <div className="flex items-center justify-between">
      <Label htmlFor={fieldId}>{label}</Label>
      <Switch
        id={fieldId}
        checked={checked}
        onCheckedChange={onCheckedChange}
      />
    </div>
  )
}
