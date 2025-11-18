import type {
  MappingsResponseDto,
  SemanticMappingDto,
  TemplatesResponseDto,
} from '../../api/generated'
import type { SemanticEquipment } from '../../adapters/ashrae-223p/schemas'

export function mapMappingsResponseToMap({
  response,
  templates,
}: {
  response: MappingsResponseDto
  templates: TemplatesResponseDto | undefined
}): Map<string, SemanticEquipment> {
  const map = new Map<string, SemanticEquipment>()

  if (!response.mappings) return map

  const mappingsRecord = response.mappings

  Object.entries(mappingsRecord).forEach(([pointId, mapping]) => {
    map.set(
      pointId,
      mapSemanticMappingToEquipment({ mapping, pointId, templates })
    )
  })

  return map
}

function mapSemanticMappingToEquipment({
  mapping,
  pointId,
  templates,
}: {
  mapping: SemanticMappingDto
  pointId: string
  templates: TemplatesResponseDto | undefined
}): SemanticEquipment {
  const propertyType = lookupPropertyType(mapping.propertyId, templates)

  /*
  TODO:
  - domainSpaceIds - Requires BuildingMOTIF functional space associations
  - connectionPoints - Requires BuildingMOTIF connection point ontology
  - externalReference.deviceIdentifier/objectIdentifier/objectName - Requires BACnet device discovery
  **/
  return {
    equipmentTypeId: mapping.equipmentTypeId,
    deviceTypeId: mapping.deviceTypeId,
    propertyId: mapping.propertyId,
    propertyType: propertyType ?? 'quantifiable',
    physicalSpaceId: mapping.physicalSpaceId ?? undefined,
    domainSpaceIds: mapping.domainSpaceIds ?? undefined,
    connectionPoints: undefined,
    externalReference: {
      compositeKey: pointId,
      deviceIdentifier: undefined,
      objectIdentifier: undefined,
      objectName: undefined,
      propertyIdentifier: 'present-value',
    },
    schemaVersion: '223p-2023',
  }
}

function lookupPropertyType(
  propertyId: string,
  templates: TemplatesResponseDto | undefined
): 'quantifiable' | 'enumerated' | undefined {
  if (!templates) return undefined

  for (const system of templates.systems) {
    for (const device of system.devices) {
      const property = device.properties.find((p) => p.id === propertyId)
      if (property) {
        return property.propertyType
      }
    }
  }

  return undefined
}
