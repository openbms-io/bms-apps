import { useMutation, useQueryClient } from '@tanstack/react-query'
import { updateInstance } from '../client'
import { instanceQueryKey } from '../queries/use-instance-query'
import type { ReheatParameters } from '../generated/types.gen'

interface UpdateInstanceParams {
  instanceId: string
  parameters: ReheatParameters
}

export function useUpdateInstanceMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: ({ instanceId, parameters }: UpdateInstanceParams) =>
      updateInstance({ instanceId, parameters }),
    onSuccess: (data, { instanceId }) => {
      queryClient.setQueryData(instanceQueryKey(instanceId), data)
    },
  })
}
