import type { BACnetPointData, BACnetControllerData, SemanticEquipment } from '../../adapters/ashrae-223p/schemas'
import type { SemanticMappingDto } from '../../api/generated'
import {
  createCompositeKey,
  createDeviceIdentifier,
  createObjectIdentifier,
} from '../../utils/bacnet-keys'

export function createCompositeKeyForPoint(
  point: BACnetPointData,
  controller?: BACnetControllerData
): string {
  return controller
    ? createCompositeKey(controller.deviceId, point.objectType, point.objectId)
    : point.pointId
}

export function createExternalReference(
  point: BACnetPointData,
  controller?: BACnetControllerData
) {
  return {
    deviceIdentifier: controller
      ? createDeviceIdentifier(controller.deviceId)
      : undefined,
    objectIdentifier: createObjectIdentifier(point.objectType, point.objectId),
    objectName: point.name,
    propertyIdentifier: 'present-value' as const,
  }
}

export function determinePropertyType(
  propertyId: string,
  observableProperties: Array<{ value: string }>
): 'quantifiable' | 'enumerated' {
  return observableProperties.some((prop) => prop.value === propertyId)
    ? 'quantifiable'
    : 'enumerated'
}

export function filterOutMapping(
  currentMappings: Map<string, SemanticEquipment> | undefined,
  compositeKey: string
): Record<string, SemanticMappingDto> {
  const updatedMappings: Record<string, SemanticMappingDto> = {}

  currentMappings?.forEach((value, key) => {
    if (key !== compositeKey) {
      updatedMappings[key] = {
        equipmentTypeId: value.equipmentTypeId,
        deviceTypeId: value.deviceTypeId,
        propertyId: value.propertyId,
        domainSpaceIds: value.domainSpaceIds,
        physicalSpaceId: value.physicalSpaceId ?? null,
      }
    }
  })

  return updatedMappings
}
