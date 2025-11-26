import { useQuery } from '@tanstack/react-query'
import { getPropertiesForDeviceApiV1ProjectsProjectIdSystemsPropertiesGet } from '../generated'

export function usePropertiesQuery({
  projectId,
  deviceUri,
  bacnetObjectType,
}: {
  projectId: string | undefined
  deviceUri: string | undefined
  bacnetObjectType: string | undefined
}) {
  return useQuery({
    queryKey: ['properties', projectId, deviceUri, bacnetObjectType],
    queryFn: async () => {
      if (!projectId || !deviceUri || !bacnetObjectType) return []
      const response =
        await getPropertiesForDeviceApiV1ProjectsProjectIdSystemsPropertiesGet({
          path: { project_id: projectId },
          query: { deviceUri, bacnetObjectType },
        })
      return response.data || []
    },
    enabled: !!projectId && !!deviceUri && !!bacnetObjectType,
  })
}
