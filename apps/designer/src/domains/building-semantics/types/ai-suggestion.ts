export interface AISuggestion {
  selectedId: string
  confidence: number
  reasoning: string
}

export function formatConfidence(confidence: number): string {
  return `${Math.round(confidence * 100)}%`
}
