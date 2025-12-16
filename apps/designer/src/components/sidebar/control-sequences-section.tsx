'use client'

import { useState } from 'react'
import { ChevronDown, ChevronRight, Thermometer } from 'lucide-react'
import { Button } from '@/components/ui/button'

interface DraggableSequenceItem {
  type: string
  label: string
  icon: React.ReactNode
  metadata?: Record<string, unknown>
}

function DraggableItem({ item }: { item: DraggableSequenceItem }) {
  const handleDragStart = (e: React.DragEvent) => {
    const dragData = {
      type: 'control-sequence-node',
      nodeType: item.type,
      label: item.label,
      metadata: item.metadata,
      draggedFrom: 'control-sequences-section',
    }
    e.dataTransfer.effectAllowed = 'copy'
    e.dataTransfer.setData('application/json', JSON.stringify(dragData))
  }

  return (
    <div
      draggable
      onDragStart={handleDragStart}
      className="flex items-center gap-2 px-3 py-2 text-sm hover:bg-accent cursor-move rounded-md"
    >
      {item.icon}
      <span>{item.label}</span>
    </div>
  )
}

export function ControlSequencesSection() {
  const [isExpanded, setIsExpanded] = useState(true)

  const g36Sequences: DraggableSequenceItem[] = [
    {
      type: 'g36-vav-reheat',
      label: 'G36 VAV Reheat',
      icon: <Thermometer className="w-4 h-4" />,
      metadata: {},
    },
  ]

  return (
    <div className="border-t">
      <Button
        variant="ghost"
        size="sm"
        className="w-full justify-start px-3 py-2"
        onClick={() => setIsExpanded(!isExpanded)}
      >
        {isExpanded ? (
          <ChevronDown className="w-4 h-4 mr-2" />
        ) : (
          <ChevronRight className="w-4 h-4 mr-2" />
        )}
        <span className="font-semibold">Control Sequences</span>
      </Button>

      {isExpanded && (
        <div className="px-2 py-1">
          <div className="text-xs text-muted-foreground px-3 py-1">
            ASHRAE G36
          </div>
          {g36Sequences.map((node) => (
            <DraggableItem key={`${node.type}-${node.label}`} item={node} />
          ))}
        </div>
      )}
    </div>
  )
}
