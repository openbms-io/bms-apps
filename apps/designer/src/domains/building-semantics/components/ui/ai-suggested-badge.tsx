import { Sparkles } from 'lucide-react'

interface AiSuggestedBadgeProps {
  show: boolean
}

export function AiSuggestedBadge({ show }: AiSuggestedBadgeProps) {
  if (!show) return null
  return <Sparkles className="h-3 w-3 text-yellow-500" />
}
