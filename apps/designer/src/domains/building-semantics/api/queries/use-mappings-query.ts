import { useQuery, useMutation, useQueryClient } from '@tanstack/react-query'
import { semanticMappingsApi } from '../mappings.api'
import { semanticQueryKeys } from './query-keys'
import type { SemanticEquipment } from '../../schemas'

export function useMappingsQuery(projectId: string | undefined) {
  return useQuery({
    queryKey: semanticQueryKeys.mappings.list(projectId || 'none'),
    queryFn: () => semanticMappingsApi.listMappings(projectId!),
    enabled: !!projectId,
  })
}

export function useMappingQuery(
  projectId: string | undefined,
  pointId: string | undefined
) {
  return useQuery({
    queryKey: semanticQueryKeys.mappings.detail(
      projectId || 'none',
      pointId || ''
    ),
    queryFn: () => semanticMappingsApi.getMapping(projectId!, pointId!),
    enabled: !!projectId && !!pointId,
  })
}

export function useCreateMappingMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({
      projectId,
      pointId,
      mapping,
    }: {
      projectId: string
      pointId: string
      mapping: SemanticEquipment
    }) => semanticMappingsApi.createMapping(projectId, pointId, mapping),
    onSuccess: (_data, variables) => {
      queryClient.invalidateQueries({
        queryKey: semanticQueryKeys.mappings.list(variables.projectId),
      })
      queryClient.invalidateQueries({
        queryKey: semanticQueryKeys.mappings.detail(
          variables.projectId,
          variables.pointId
        ),
      })
    },
  })
}

export function useDeleteMappingMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({
      projectId,
      compositeKey,
    }: {
      projectId: string
      compositeKey: string
    }) => semanticMappingsApi.deleteMapping(projectId, compositeKey),
    onSuccess: (_data, variables) => {
      queryClient.invalidateQueries({
        queryKey: semanticQueryKeys.mappings.list(variables.projectId),
      })
    },
  })
}
