import type { SpaceInstanceDto } from '../../api/generated'
import type { SpaceViewModel } from '../types'

export function mapSpaceDTOToViewModel(dto: SpaceInstanceDto): SpaceViewModel {
  return {
    id: dto.id,
    label: dto.label,
    type: dto.spaceTypeId.includes('Physical')
      ? 'PhysicalSpace'
      : 'DomainSpace',
    pointCount: 0,
    createdAt: new Date(dto.createdAt),
  }
}

export function mapSpacesDTOToViewModel(
  dtos: SpaceInstanceDto[]
): SpaceViewModel[] {
  return dtos.map(mapSpaceDTOToViewModel)
}
