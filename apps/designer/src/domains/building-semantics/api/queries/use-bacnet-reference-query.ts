import { useQuery } from '@tanstack/react-query'
import { getReferenceApiV1ProjectsProjectIdBacnetReferencesBacnetPointIdGet } from '../generated'

export function useBacnetReferenceQuery({
  projectId,
  bacnetPointId,
}: {
  projectId: string | undefined
  bacnetPointId: string | undefined
}) {
  return useQuery({
    queryKey: ['bacnetReference', projectId || 'none', bacnetPointId || 'none'],
    queryFn: async () => {
      if (!projectId || !bacnetPointId) return null
      const response =
        await getReferenceApiV1ProjectsProjectIdBacnetReferencesBacnetPointIdGet(
          {
            path: {
              project_id: projectId,
              bacnet_point_id: bacnetPointId,
            },
          }
        )
      return response.data ?? null
    },
    enabled: !!projectId && !!bacnetPointId,
    retry: (failureCount, error: { status?: number }) => {
      if (error?.status === 404) return false
      return failureCount < 3
    },
  })
}
