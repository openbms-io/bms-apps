'use client'

import {
  Tooltip,
  TooltipContent,
  TooltipProvider,
  TooltipTrigger,
} from '@/components/ui/tooltip'
import type { AISuggestion } from '../types/ai-suggestion'
import { AiConfidenceBadge } from './ui/ai-confidence-badge'
import { AiLoadingIndicator } from './ui/ai-loading-indicator'

interface AISuggestionIndicatorTooltipProps {
  aiSuggestion?: AISuggestion
  isLoading?: boolean
  isSelected: boolean
}

export function AISuggestionIndicatorTooltip({
  aiSuggestion,
  isLoading = false,
  isSelected,
}: AISuggestionIndicatorTooltipProps) {
  if (isLoading) {
    return <AiLoadingIndicator />
  }

  if (!aiSuggestion || !isSelected) {
    return null
  }

  return (
    <TooltipProvider>
      <Tooltip>
        <TooltipTrigger asChild>
          <div>
            <AiConfidenceBadge confidence={aiSuggestion.confidence} />
          </div>
        </TooltipTrigger>
        <TooltipContent side="top" className="max-w-sm">
          <p className="text-sm">{aiSuggestion.reasoning}</p>
        </TooltipContent>
      </Tooltip>
    </TooltipProvider>
  )
}
