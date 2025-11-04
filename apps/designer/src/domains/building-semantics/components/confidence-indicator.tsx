import { Badge } from '@/components/ui/badge'

interface ConfidenceIndicatorProps {
  confidence: number
  showLabel?: boolean
}

export function ConfidenceIndicator({
  confidence,
  showLabel = true,
}: ConfidenceIndicatorProps) {
  const variant =
    confidence > 80 ? 'default' : confidence > 60 ? 'secondary' : 'destructive'
  const bgColor =
    confidence > 80
      ? 'bg-green-100 text-green-800 hover:bg-green-100'
      : confidence > 60
        ? 'bg-yellow-100 text-yellow-800 hover:bg-yellow-100'
        : ''

  return (
    <Badge
      variant={variant}
      className={`text-xs ${confidence > 60 ? bgColor : ''}`}
      aria-label={`AI confidence: ${confidence}%`}
    >
      {showLabel && 'AI: '}
      {confidence}%
    </Badge>
  )
}
