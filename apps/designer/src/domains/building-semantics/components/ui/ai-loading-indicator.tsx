import { Loader2 } from 'lucide-react'

export function AiLoadingIndicator() {
  return (
    <div className="flex items-center gap-1 text-muted-foreground shrink-0">
      <Loader2 className="h-4 w-4 animate-spin" />
    </div>
  )
}
