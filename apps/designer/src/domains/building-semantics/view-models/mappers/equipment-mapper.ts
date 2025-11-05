import type {
  SemanticEquipment,
  SpaceDTO,
} from '../../adapters/ashrae-223p/schemas'
import type { EquipmentViewModel } from '../types'

export function mapEquipmentDTOToViewModel(
  pointName: string,
  dto: SemanticEquipment | null,
  spaces: SpaceDTO[]
): EquipmentViewModel {
  if (!dto) {
    return {
      pointName,
      equipmentType: '',
      deviceType: '',
      observableProperty: '',
      propertyType: 'quantifiable',
      hasMapping: false,
    }
  }

  const physicalSpace = dto.physicalSpaceId
    ? spaces.find((s) => s.id === dto.physicalSpaceId)
    : undefined

  const domainSpaces =
    dto.domainSpaceIds
      ?.map((id) => spaces.find((s) => s.id === id))
      .filter((s): s is SpaceDTO => s !== undefined) || []

  return {
    pointName,
    equipmentType: dto.equipmentType,
    deviceType: dto.deviceType,
    observableProperty: dto.observableProperty,
    propertyType: dto.propertyType,
    physicalSpaceLabel: physicalSpace?.rdfsLabel,
    domainSpaceLabels: domainSpaces.map((s) => s.rdfsLabel),
    hasMapping: true,
  }
}
