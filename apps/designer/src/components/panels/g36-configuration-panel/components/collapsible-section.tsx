'use client'

import { useState } from 'react'
import { ChevronDown, ChevronRight } from 'lucide-react'
import {
  Collapsible,
  CollapsibleContent,
  CollapsibleTrigger,
} from '@/components/ui/collapsible'
import { Badge } from '@/components/ui/badge'
import type { CollapsibleSectionProps } from '../types'

export function CollapsibleSection({
  title,
  defaultOpen = false,
  badge,
  children,
}: CollapsibleSectionProps) {
  const [isOpen, setIsOpen] = useState(defaultOpen)

  return (
    <Collapsible open={isOpen} onOpenChange={setIsOpen}>
      <CollapsibleTrigger className="flex items-center gap-2 w-full text-left font-medium text-sm py-2 hover:bg-muted/50 rounded px-2 -mx-2">
        {isOpen ? (
          <ChevronDown className="h-4 w-4" />
        ) : (
          <ChevronRight className="h-4 w-4" />
        )}
        {title}
        {badge && (
          <Badge variant="secondary" className="text-xs ml-auto">
            {badge}
          </Badge>
        )}
      </CollapsibleTrigger>
      <CollapsibleContent className="pl-6 pt-2 space-y-4">
        {children}
      </CollapsibleContent>
    </Collapsible>
  )
}
