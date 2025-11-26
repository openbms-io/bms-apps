import { useQuery } from '@tanstack/react-query'
import { listSystemsApiV1ProjectsProjectIdSystemsGet } from '../generated'

export function useSystemsQuery(projectId: string | undefined) {
  return useQuery({
    queryKey: ['systems', projectId],
    queryFn: async () => {
      if (!projectId) return []
      const response = await listSystemsApiV1ProjectsProjectIdSystemsGet({
        path: { project_id: projectId },
      })
      return response.data || []
    },
    enabled: !!projectId,
  })
}
