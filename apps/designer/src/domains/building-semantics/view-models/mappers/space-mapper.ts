import type { SpaceDTO } from '../../adapters/ashrae-223p/schemas'
import type { SpaceViewModel } from '../types'

export function mapSpaceDTOToViewModel(dto: SpaceDTO): SpaceViewModel {
  return {
    id: dto.id,
    label: dto.rdfsLabel,
    type: dto.spaceType,
    pointCount: dto.pointIds.length,
    createdAt: new Date(dto.createdAt),
  }
}

export function mapSpacesDTOToViewModel(dtos: SpaceDTO[]): SpaceViewModel[] {
  return dtos.map(mapSpaceDTOToViewModel)
}
