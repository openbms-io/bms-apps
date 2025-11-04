import { useQuery, useMutation, useQueryClient } from '@tanstack/react-query'
import { mappings223pApi } from '../mappings.api'
import { queryKeys223p } from './query-keys'
import type { Equipment223PDTO } from '../../schemas'

export function useMappingsQuery(projectId: string | undefined) {
  return useQuery({
    queryKey: queryKeys223p.mappings.list(projectId || 'none'),
    queryFn: () => mappings223pApi.listMappings(projectId!),
    enabled: !!projectId,
  })
}

export function useMappingQuery(
  projectId: string | undefined,
  pointId: string | undefined
) {
  return useQuery({
    queryKey: queryKeys223p.mappings.detail(projectId || 'none', pointId || ''),
    queryFn: () => mappings223pApi.getMapping(projectId!, pointId!),
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
      mapping: Equipment223PDTO
    }) => mappings223pApi.createMapping(projectId, pointId, mapping),
    onSuccess: (_data, variables) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys223p.mappings.list(variables.projectId),
      })
      queryClient.invalidateQueries({
        queryKey: queryKeys223p.mappings.detail(
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
    }) => mappings223pApi.deleteMapping(projectId, compositeKey),
    onSuccess: (_data, variables) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys223p.mappings.list(variables.projectId),
      })
    },
  })
}
