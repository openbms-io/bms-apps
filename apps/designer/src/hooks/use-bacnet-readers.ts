import {
  useQuery,
  useMutation,
  useQueryClient,
  UseQueryOptions,
  UseMutationOptions,
} from '@tanstack/react-query'
import {
  BacnetReader,
  CreateBacnetReader,
} from '@/lib/domain/models/bacnet-reader'
import { bacnetReadersApi } from '@/lib/api/bacnet-readers'
import { queryKeys } from '@/lib/query-client'

export function useBacnetReaders(
  orgId: string | undefined,
  siteId: string | undefined,
  projectId: string | undefined,
  iotDeviceId: string | undefined,
  options?: Omit<UseQueryOptions<BacnetReader[]>, 'queryKey' | 'queryFn'>
) {
  return useQuery({
    queryKey: queryKeys.bacnetReaders.list(iotDeviceId || 'none'),
    queryFn: () =>
      bacnetReadersApi.list({
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
  data: Omit<CreateBacnetReader, 'organizationId' | 'siteId' | 'iotDeviceId'>
}

export function useCreateBacnetReader(
  options?: UseMutationOptions<BacnetReader, Error, CreateParams>
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
      bacnetReadersApi.create({ orgId, siteId, projectId, iotDeviceId, data }),
    onSuccess: (_, { iotDeviceId }) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.bacnetReaders.list(iotDeviceId),
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
  readerId: string
}

export function useDeleteBacnetReader(
  options?: UseMutationOptions<void, Error, DeleteParams>
) {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({
      orgId,
      siteId,
      projectId,
      iotDeviceId,
      readerId,
    }: DeleteParams) =>
      bacnetReadersApi.delete({
        orgId,
        siteId,
        projectId,
        iotDeviceId,
        readerId,
      }),
    onSuccess: (_, { iotDeviceId }) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.bacnetReaders.list(iotDeviceId),
      })
    },
    ...options,
  })
}
