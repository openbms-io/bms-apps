import {
  useQuery,
  useMutation,
  useQueryClient,
  UseQueryOptions,
  UseMutationOptions,
} from '@tanstack/react-query'
import {
  IotDeviceController,
  CreateIotDeviceController,
} from '@/lib/domain/models/iot-device-controller'
import { iotDeviceControllersApi } from '@/lib/api/iot-device-controllers'
import { queryKeys } from '@/lib/query-client'

export function useIotDeviceControllers(
  orgId: string | undefined,
  siteId: string | undefined,
  projectId: string | undefined,
  iotDeviceId: string | undefined,
  options?: Omit<UseQueryOptions<IotDeviceController[]>, 'queryKey' | 'queryFn'>
) {
  return useQuery({
    queryKey: queryKeys.iotDeviceControllers.list(iotDeviceId || 'none'),
    queryFn: () =>
      iotDeviceControllersApi.list({
        orgId: orgId!,
        siteId: siteId!,
        projectId: projectId!,
        iotDeviceId: iotDeviceId!,
      }),
    enabled: !!orgId && !!siteId && !!projectId && !!iotDeviceId,
    ...options,
  })
}

type CreateParams = {
  orgId: string
  siteId: string
  projectId: string
  iotDeviceId: string
  data: Omit<
    CreateIotDeviceController,
    'organizationId' | 'siteId' | 'iotDeviceId'
  >
}

export function useCreateIotDeviceController(
  options?: UseMutationOptions<IotDeviceController, Error, CreateParams>
) {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({
      orgId,
      siteId,
      projectId,
      iotDeviceId,
      data,
    }: CreateParams) =>
      iotDeviceControllersApi.create({
        orgId,
        siteId,
        projectId,
        iotDeviceId,
        data,
      }),
    onSuccess: (_, { iotDeviceId }) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.iotDeviceControllers.list(iotDeviceId),
      })
    },
    ...options,
  })
}

type DeleteParams = {
  orgId: string
  siteId: string
  projectId: string
  iotDeviceId: string
  controllerId: string
}

export function useDeleteIotDeviceController(
  options?: UseMutationOptions<void, Error, DeleteParams>
) {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({
      orgId,
      siteId,
      projectId,
      iotDeviceId,
      controllerId,
    }: DeleteParams) =>
      iotDeviceControllersApi.delete({
        orgId,
        siteId,
        projectId,
        iotDeviceId,
        controllerId,
      }),
    onSuccess: (_, { iotDeviceId }) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.iotDeviceControllers.list(iotDeviceId),
      })
    },
    ...options,
  })
}
