import { useQuery } from '@tanstack/react-query'
import { listReferencesApiV1ProjectsProjectIdBacnetReferencesGet } from '../generated'
import { transformBacnetReferencesToMap } from '../../utils/bacnet-to-semantic-mapping'

export function useBacnetReferencesQuery(projectId: string | undefined) {
  return useQuery({
    queryKey: ['bacnetReferences', projectId || 'none'],
    queryFn: async () => {
      if (!projectId) return new Map()
      const response =
        await listReferencesApiV1ProjectsProjectIdBacnetReferencesGet({
          path: {
            project_id: projectId,
          },
        })
      return transformBacnetReferencesToMap(response.data || [])
    },
    enabled: !!projectId,
    retry: 3,
  })
}
