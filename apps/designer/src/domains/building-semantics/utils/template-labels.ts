import type { TemplateSystemDto } from '../api/generated'

function getTemplateLabel({
  templates,
  urn,
  type,
}: {
  templates: TemplateSystemDto[] | undefined
  urn: string
  type: 'system' | 'device' | 'property'
}) {
  if (!templates) return urn

  if (type === 'system') {
    const system = templates.find((s) => s.id === urn)
    return system?.label ?? urn
  }

  if (type === 'device') {
    for (const system of templates) {
      const device = system.devices.find((d) => d.id === urn)
      if (device) return device.label
    }
    return urn
  }

  if (type === 'property') {
    for (const system of templates) {
      for (const device of system.devices) {
        const property = device.properties.find((p) => p.id === urn)
        if (property) return property.label
      }
    }
    return urn
  }

  return urn
}

export function getMappingLabels({
  templates,
  equipmentTypeUrn,
  deviceTypeUrn,
  propertyUrn,
}: {
  templates: TemplateSystemDto[] | undefined
  equipmentTypeUrn: string
  deviceTypeUrn: string
  propertyUrn: string
}) {
  return {
    equipment: getTemplateLabel({
      templates,
      urn: equipmentTypeUrn,
      type: 'system',
    }),
    device: getTemplateLabel({ templates, urn: deviceTypeUrn, type: 'device' }),
    property: getTemplateLabel({
      templates,
      urn: propertyUrn,
      type: 'property',
    }),
  }
}
