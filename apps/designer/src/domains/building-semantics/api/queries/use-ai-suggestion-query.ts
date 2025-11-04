import { useQuery } from '@tanstack/react-query'
import { mockAISuggestionService } from '../services'
import { semanticQueryKeys } from './query-keys'
import type { BACnetPointData } from '../../schemas'

export function useAISuggestionQuery(
  projectId: string | undefined,
  point: BACnetPointData | null
) {
  return useQuery({
    queryKey: semanticQueryKeys.aiSuggestions.detail(
      point?.pointId ?? 'none',
      projectId ?? 'none'
    ),
    queryFn: () => mockAISuggestionService.suggestMapping(point!),
    enabled: !!point && !!projectId,
    staleTime: 5 * 60 * 1000,
  })
}
