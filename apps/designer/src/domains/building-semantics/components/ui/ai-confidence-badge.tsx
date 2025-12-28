import { Sparkles } from 'lucide-react'
import { formatConfidence } from '../../types/ai-suggestion'

interface AiConfidenceBadgeProps {
  confidence: number
}

export function AiConfidenceBadge({ confidence }: AiConfidenceBadgeProps) {
  return (
    <div className="flex items-center gap-1 cursor-help shrink-0">
      <Sparkles className="h-4 w-4 text-yellow-500" />
      <span className="text-sm text-yellow-600 font-medium">
        {formatConfidence(confidence)}
      </span>
    </div>
  )
}
