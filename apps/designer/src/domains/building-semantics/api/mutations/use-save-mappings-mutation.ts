import { useMutation, useQueryClient } from '@tanstack/react-query'
import { saveMappingsApiV1223pMappingsPost } from '../generated'
import type { SemanticMappingDto } from '../generated'

interface SaveMappingsParams {
  projectId: string
  mappings: Record<string, SemanticMappingDto>
}

export function useSaveMappingsMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: async ({ projectId, mappings }: SaveMappingsParams) => {
      const response = await saveMappingsApiV1223pMappingsPost({
        body: {
          projectId,
          mappings,
        },
      })
      return response.data
    },
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({ queryKey: ['mappings', projectId] })
    },
    retry: 3,
  })
}
