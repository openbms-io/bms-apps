import { useQuery, useMutation, useQueryClient } from '@tanstack/react-query'
import { spaces223pApi } from '../spaces.api'
import { queryKeys223p } from './query-keys'
import type { SpaceType } from '../../schemas'

export function useSpacesQuery(projectId: string | undefined) {
  return useQuery({
    queryKey: queryKeys223p.spaces.list(projectId || 'none'),
    queryFn: () => spaces223pApi.listSpaces(projectId!),
    enabled: !!projectId,
  })
}

export function useCreateSpaceMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({
      projectId,
      rdfsLabel,
      spaceType,
    }: {
      projectId: string
      rdfsLabel: string
      spaceType: SpaceType
    }) => spaces223pApi.createSpace(projectId, rdfsLabel, spaceType),
    onSuccess: (_data, variables) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys223p.spaces.list(variables.projectId),
      })
    },
  })
}

export function useAddPointToSpaceMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({
      projectId,
      spaceId,
      pointId,
    }: {
      projectId: string
      spaceId: string
      pointId: string
    }) => spaces223pApi.addPointToSpace(projectId, spaceId, pointId),
    onSuccess: (_data, variables) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys223p.spaces.list(variables.projectId),
      })
    },
  })
}
