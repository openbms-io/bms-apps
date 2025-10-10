import {
  useQuery,
  useMutation,
  UseQueryOptions,
  UseMutationOptions,
  useQueryClient,
} from '@tanstack/react-query'
import { IotDevice } from '@/lib/domain/models/iot-device'
import { iotDevicesApi } from '@/lib/api/iot-devices'
import { queryKeys } from '@/lib/query-client'

export function useIotDevice(
  orgId: string | undefined,
  siteId: string | undefined,
  projectId: string | undefined,
  id: string | undefined,
  options?: Omit<UseQueryOptions<IotDevice>, 'queryKey' | 'queryFn'>
): ReturnType<typeof useQuery<IotDevice>> {
  return useQuery({
    queryKey: queryKeys.iotDevices.detail(id || ''),
    queryFn: () => iotDevicesApi.get(orgId!, siteId!, projectId!, id!),
    enabled: !!id && !!orgId && !!siteId && !!projectId,
    refetchOnMount: true,
    ...options,
  })
}

type CreateIotDeviceParams = {
  orgId: string
  siteId: string
  projectId: string
  name: string
  description?: string
}

export function useCreateIotDeviceForProject(
  options?: UseMutationOptions<IotDevice, Error, CreateIotDeviceParams>
) {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: (params: CreateIotDeviceParams) =>
      iotDevicesApi.createForProject(params),
    onSuccess: (device, params) => {
      queryClient.invalidateQueries({ queryKey: queryKeys.iotDevices.all })
      queryClient.invalidateQueries({
        queryKey: queryKeys.projects.detail(params.projectId),
      })
    },
    ...options,
  })
}
