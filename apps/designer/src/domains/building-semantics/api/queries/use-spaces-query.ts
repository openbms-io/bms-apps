import { useQuery } from '@tanstack/react-query'
import { listSpacesApiV1223pSpacesGet } from '../generated'

export function useSpacesQuery({
  projectId,
}: {
  projectId: string | undefined
}) {
  return useQuery({
    queryKey: ['spaces', projectId || 'none'],
    queryFn: async () => {
      if (!projectId) return undefined
      const response = await listSpacesApiV1223pSpacesGet({
        query: { projectId },
      })
      return response.data
    },
    enabled: !!projectId,
    retry: 3,
  })
}
