import { useCallback } from 'react'
import { toast } from 'sonner'
import type { BACnetPointData, BACnetControllerData } from '../../adapters/ashrae-223p/schemas'
import { useSaveMappingsMutation } from '../../api/mutations/use-save-mappings-mutation'
import { useMappingsViewModel } from '../../view-models/use-mappings-view-model'
import { createCompositeKeyForPoint, filterOutMapping } from './mapping-helpers'

export function useMappingDelete(
  projectId: string,
  point: BACnetPointData | undefined,
  controller: BACnetControllerData | undefined
) {
  const { data: currentMappings } = useMappingsViewModel({ projectId })
  const saveMappings = useSaveMappingsMutation()

  const deleteMapping = useCallback(
    (onSuccess: () => void) => {
      if (!point?.pointId) {
        toast.error('Cannot delete: missing point ID')
        return
      }

      const compositeKey = createCompositeKeyForPoint(point, controller)
      const updatedMappings = filterOutMapping(currentMappings, compositeKey)

      saveMappings.mutate(
        {
          projectId,
          mappings: updatedMappings,
        },
        {
          onSuccess: () => {
            toast.success('223P mapping removed')
            onSuccess()
          },
          onError: (error) => {
            toast.error(
              error instanceof Error ? error.message : 'Failed to remove mapping'
            )
          },
        }
      )
    },
    [point, controller, projectId, currentMappings, saveMappings]
  )

  return { deleteMapping }
}
