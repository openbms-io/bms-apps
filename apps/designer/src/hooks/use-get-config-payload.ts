import { useQuery, UseQueryOptions } from '@tanstack/react-query'

import {
  getConfigPayloadApi,
  GetConfigPayload,
} from '@/lib/api/get-config-payload'
import { queryKeys } from '@/lib/query-client'

export function useGetConfigPayload(
  orgId: string | undefined,
  siteId: string | undefined,
  projectId: string | undefined,
  iotDeviceId: string | undefined,
  options?: Omit<UseQueryOptions<GetConfigPayload>, 'queryKey' | 'queryFn'>
) {
  return useQuery({
    queryKey: queryKeys.getConfigPayload(iotDeviceId || 'none'),
    queryFn: () =>
      getConfigPayloadApi.fetch({
        orgId: orgId!,
        siteId: siteId!,
        projectId: projectId!,
        iotDeviceId: iotDeviceId!,
      }),
    enabled: false,
    ...options,
  })
}
