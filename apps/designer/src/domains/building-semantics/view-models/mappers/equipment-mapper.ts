import type { SemanticEquipment } from '../../adapters/ashrae-223p/schemas'
import type { SpaceInstanceDto } from '../../api/generated'
import type { EquipmentViewModel } from '../types'

export function mapEquipmentDTOToViewModel({
  pointName,
  dto,
  spaces,
}: {
  pointName: string
  dto: SemanticEquipment | undefined
  spaces: SpaceInstanceDto[]
}): EquipmentViewModel | undefined {
  if (!dto) {
    return undefined
  }

  const physicalSpace = dto.physicalSpaceId
    ? spaces.find((s) => s.id === dto.physicalSpaceId)
    : undefined

  const domainSpaces =
    dto.domainSpaceIds
      ?.map((id) => spaces.find((s) => s.id === id))
      .filter((s): s is SpaceInstanceDto => s !== undefined) || []

  return {
    pointName,
    equipmentTypeId: dto.equipmentTypeId,
    deviceTypeId: dto.deviceTypeId,
    propertyId: dto.propertyId,
    propertyType: dto.propertyType,
    physicalSpaceLabel: physicalSpace?.label,
    domainSpaceLabels: domainSpaces.map((s) => s.label),
    hasMapping: true,
  }
}
