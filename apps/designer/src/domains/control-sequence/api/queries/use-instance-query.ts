import { useQuery } from '@tanstack/react-query'
import { getInstance } from '../client'

export const instanceQueryKey = (instanceId: string) =>
  ['control-sequence', 'instance', instanceId] as const

export function useInstanceQuery({ instanceId }: { instanceId: string }) {
  return useQuery({
    queryKey: instanceQueryKey(instanceId),
    queryFn: () => getInstance({ instanceId }),
    enabled: Boolean(instanceId),
    staleTime: 5 * 60 * 1000,
  })
}
