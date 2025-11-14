import { useMemo } from 'react'
import { useAISuggestionQuery } from '../api/queries/use-ai-suggestion-query'
import type { BACnetPointData } from '../adapters/ashrae-223p/schemas'

export function useMappingSuggestionViewModel(
  projectId: string | undefined,
  point: BACnetPointData | undefined
) {
  const { data: aiSuggestion } = useAISuggestionQuery(projectId, point)

  return useMemo(() => {
    if (!aiSuggestion || !point) return undefined
    return aiSuggestion
  }, [aiSuggestion, point])
}
