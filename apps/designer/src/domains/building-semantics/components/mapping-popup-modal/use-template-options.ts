import { useMemo } from 'react'
import type { TemplatesResponseDto } from '../../api/generated'

export interface TemplateOption {
  value: string
  label: string
  metadata?: {
    quantityKind?: string | null
    unit?: string | null
    medium?: string | null
  }
}

export interface TemplateOptions {
  equipmentTypes: TemplateOption[]
  deviceTypes: TemplateOption[]
  observableProperties: TemplateOption[]
}

export function useTemplateOptions(
  templates: TemplatesResponseDto | undefined,
  equipmentType: string,
  deviceType: string
): TemplateOptions {
  return useMemo(() => {
    const equipmentTypes: TemplateOption[] =
      templates?.systems.map((s) => ({
        value: s.id,
        label: s.label,
      })) ?? []

    const selectedSystem = templates?.systems.find((s) => s.id === equipmentType)

    const deviceTypes: TemplateOption[] =
      selectedSystem?.devices.map((d) => ({
        value: d.id,
        label: d.label,
      })) ?? []

    const selectedDevice = selectedSystem?.devices.find((d) => d.id === deviceType)

    const observableProperties: TemplateOption[] =
      selectedDevice?.properties.map((p) => ({
        value: p.id,
        label: p.label,
        metadata: {
          quantityKind: p.quantityKind,
          unit: p.unit,
          medium: p.medium,
        },
      })) ?? []

    return {
      equipmentTypes,
      deviceTypes,
      observableProperties,
    }
  }, [templates, equipmentType, deviceType])
}
