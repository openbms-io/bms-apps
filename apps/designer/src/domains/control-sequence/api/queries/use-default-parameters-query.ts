import { useQuery } from '@tanstack/react-query'
import { getDefaultParameters } from '../client'
import type { SequenceType } from '../generated/types.gen'

export function defaultParametersQueryKey(sequenceType: SequenceType) {
  return ['control-sequence', 'defaults', sequenceType] as const
}

export function useDefaultParametersQuery({
  sequenceType,
  enabled = true,
}: {
  sequenceType: SequenceType
  enabled?: boolean
}) {
  return useQuery({
    queryKey: defaultParametersQueryKey(sequenceType),
    queryFn: () => getDefaultParameters(sequenceType),
    enabled,
    staleTime: Infinity,
  })
}
