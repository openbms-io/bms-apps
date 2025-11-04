import { useMappingQuery } from '../api/queries/use-mappings-query'
import { useSpacesQuery } from '../api/queries/use-spaces-query'
import { mapEquipmentDTOToViewModel } from './mappers/equipment-mapper'
import type { EquipmentViewModel } from './types'

export function useEquipmentViewModel(
  projectId: string | undefined,
  pointName: string | undefined
): {
  equipment: EquipmentViewModel | null
  isLoading: boolean
  error: Error | null
} {
  const {
    data: mapping,
    isLoading: mappingLoading,
    error: mappingError,
  } = useMappingQuery(projectId, pointName)

  const { data: spaces = [], isLoading: spacesLoading } =
    useSpacesQuery(projectId)

  const isLoading = mappingLoading || spacesLoading

  if (isLoading) {
    return { equipment: null, isLoading: true, error: null }
  }

  if (!projectId || !pointName) {
    return { equipment: null, isLoading: false, error: null }
  }

  const equipment = mapEquipmentDTOToViewModel(
    pointName,
    mapping ?? null,
    spaces
  )

  return {
    equipment,
    isLoading: false,
    error: mappingError,
  }
}
