import { useQuery } from '@tanstack/react-query'
import { getDevicesForSystemApiV1ProjectsProjectIdSystemsDevicesGet } from '../generated'

export function useDevicesQuery({
  projectId,
  systemUri,
  bacnetObjectType,
}: {
  projectId: string | undefined
  systemUri: string | undefined
  bacnetObjectType?: string
}) {
  return useQuery({
    queryKey: ['devices', projectId, systemUri, bacnetObjectType],
    queryFn: async () => {
      if (!projectId || !systemUri) return []
      const response =
        await getDevicesForSystemApiV1ProjectsProjectIdSystemsDevicesGet({
          path: { project_id: projectId },
          query: {
            systemUri,
            ...(bacnetObjectType && { bacnetObjectType }),
          },
        })
      return response.data || []
    },
    enabled: !!projectId && !!systemUri,
  })
}
