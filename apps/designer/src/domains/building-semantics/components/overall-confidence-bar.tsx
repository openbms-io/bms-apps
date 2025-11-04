interface OverallConfidenceBarProps {
  confidence: number
}

export function OverallConfidenceBar({
  confidence,
}: OverallConfidenceBarProps) {
  const color =
    confidence > 80
      ? 'bg-green-500'
      : confidence > 60
        ? 'bg-yellow-500'
        : 'bg-red-500'

  return (
    <div className="space-y-2">
      <div className="text-sm font-medium">
        Overall AI Confidence: {confidence}%
      </div>
      <div className="w-full bg-secondary rounded-full h-2">
        <div
          className={`${color} h-2 rounded-full transition-all`}
          style={{ width: `${confidence}%` }}
          role="progressbar"
          aria-valuenow={confidence}
          aria-valuemin={0}
          aria-valuemax={100}
          aria-label={`Overall AI confidence: ${confidence}%`}
        />
      </div>
    </div>
  )
}
