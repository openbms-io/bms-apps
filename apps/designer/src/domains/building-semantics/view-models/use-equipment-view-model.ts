import { useMappingsViewModel } from './use-mappings-view-model'
import { useSpacesQuery } from '../api/queries/use-spaces-query'
import { mapEquipmentDTOToViewModel } from './mappers/equipment-mapper'
import type { EquipmentViewModel } from './types'

export function useEquipmentViewModel(
  projectId: string | undefined,
  pointName: string | undefined
): {
  equipment: EquipmentViewModel | undefined
  isLoading: boolean
  error: Error | undefined
} {
  const {
    data: mappings,
    isLoading: mappingLoading,
    error: mappingError,
  } = useMappingsViewModel({ projectId })

  const { data: spaces = [], isLoading: spacesLoading } = useSpacesQuery({
    projectId,
  })

  const isLoading = mappingLoading || spacesLoading

  if (isLoading) {
    return { equipment: undefined, isLoading: true, error: undefined }
  }

  if (!projectId || !pointName) {
    return { equipment: undefined, isLoading: false, error: undefined }
  }

  const mapping = mappings?.get(pointName)

  const equipment = mapEquipmentDTOToViewModel({
    pointName,
    dto: mapping,
    spaces,
  })

  return {
    equipment,
    isLoading: false,
    error: mappingError,
  }
}
