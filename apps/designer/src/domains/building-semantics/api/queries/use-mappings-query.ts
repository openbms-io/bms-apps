import { useQuery } from '@tanstack/react-query'
import { getMappingsApiV1223pMappingsGet } from '../generated'

export function useMappingsQuery(projectId: string | undefined) {
  return useQuery({
    queryKey: ['mappings', projectId || 'none'],
    queryFn: async () => {
      if (!projectId) return undefined
      const response = await getMappingsApiV1223pMappingsGet({
        query: { projectId },
      })
      return response.data
    },
    enabled: !!projectId,
    retry: 3,
  })
}
