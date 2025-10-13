import { useQuery, UseQueryOptions } from '@tanstack/react-query'
import { ControllerPoint } from '@/lib/domain/models/controller-point'
import { controllerPointsApi } from '@/lib/api/controller-points'
import { queryKeys } from '@/lib/query-client'

export function useAllControllerPoints(
  orgId: string | undefined,
  siteId: string | undefined,
  projectId: string | undefined,
  iotDeviceId: string | undefined,
  controllerIds: string[],
  options?: Omit<
    UseQueryOptions<Record<string, ControllerPoint[]>>,
    'queryKey' | 'queryFn'
  >
) {
  return useQuery({
    queryKey: queryKeys.controllerPoints.batch(controllerIds),
    queryFn: () =>
      controllerPointsApi.listBatch({
        orgId: orgId!,
        siteId: siteId!,
        projectId: projectId!,
        iotDeviceId: iotDeviceId!,
        controllerIds,
      }),
    enabled:
      !!orgId &&
      !!siteId &&
      !!projectId &&
      !!iotDeviceId &&
      controllerIds.length > 0,
    ...options,
  })
}
