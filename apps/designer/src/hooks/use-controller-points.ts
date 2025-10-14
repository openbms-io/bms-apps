import { useQuery, UseQueryOptions } from '@tanstack/react-query'
import { ControllerPoint } from '@/lib/domain/models/controller-point'
import { controllerPointsApi } from '@/lib/api/controller-points'
import { queryKeys } from '@/lib/query-client'

export function useControllerPoints(
  orgId: string | undefined,
  siteId: string | undefined,
  projectId: string | undefined,
  iotDeviceId: string | undefined,
  controllerId: string | undefined,
  options?: Omit<UseQueryOptions<ControllerPoint[]>, 'queryKey' | 'queryFn'>
) {
  return useQuery({
    queryKey: queryKeys.controllerPoints.list(controllerId || 'none'),
    queryFn: () =>
      controllerPointsApi.list({
        orgId: orgId!,
        siteId: siteId!,
        projectId: projectId!,
        iotDeviceId: iotDeviceId!,
        controllerId: controllerId!,
      }),
    enabled:
      !!orgId && !!siteId && !!projectId && !!iotDeviceId && !!controllerId,
    ...options,
  })
}
