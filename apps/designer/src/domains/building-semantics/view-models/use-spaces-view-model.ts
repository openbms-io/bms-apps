import { useSpacesQuery } from '../api/queries/use-spaces-query'
import { mapSpacesDTOToViewModel } from './mappers/space-mapper'
import type { SpaceViewModel } from './types'

export function useSpacesViewModel(projectId: string | undefined): {
  spaces: SpaceViewModel[]
  physicalSpaces: SpaceViewModel[]
  domainSpaces: SpaceViewModel[]
  isLoading: boolean
  error: Error | undefined
} {
  const {
    data: spacesDTOs = [],
    isLoading,
    error,
  } = useSpacesQuery({ projectId })

  const spaces = mapSpacesDTOToViewModel(spacesDTOs)
  const physicalSpaces = spaces.filter((s) => s.type === 'PhysicalSpace')
  const domainSpaces = spaces.filter((s) => s.type === 'DomainSpace')

  return {
    spaces,
    physicalSpaces,
    domainSpaces,
    isLoading,
    error,
  }
}
