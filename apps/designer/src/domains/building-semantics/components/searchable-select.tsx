'use client'

import { useState } from 'react'
import { Check, ChevronsUpDown } from 'lucide-react'
import { cn } from '@/lib/utils'
import { Button } from '@/components/ui/button'
import {
  Command,
  CommandEmpty,
  CommandGroup,
  CommandInput,
  CommandItem,
  CommandList,
} from '@/components/ui/command'
import {
  Popover,
  PopoverContent,
  PopoverTrigger,
} from '@/components/ui/popover'
import { ConfidenceIndicator } from './confidence-indicator'

interface SearchableSelectProps {
  value: string
  onValueChange: (value: string) => void
  options: string[]
  aiSuggestion?: {
    value: string
    confidence: number
  }
  autoFillHint?: string
  placeholder?: string
  emptyText?: string
  id?: string
}

export function SearchableSelect({
  value,
  onValueChange,
  options,
  aiSuggestion,
  autoFillHint,
  placeholder = 'Select...',
  emptyText = 'No results found.',
  id,
}: SearchableSelectProps) {
  const [open, setOpen] = useState(false)

  return (
    <div className="space-y-1">
      <Popover open={open} onOpenChange={setOpen}>
        <PopoverTrigger asChild>
          <Button
            id={id}
            variant="outline"
            role="combobox"
            aria-expanded={open}
            className="w-full justify-between"
          >
            {value || placeholder}
            <ChevronsUpDown className="ml-2 h-4 w-4 shrink-0 opacity-50" />
          </Button>
        </PopoverTrigger>
        <PopoverContent
          className="w-[--radix-popover-trigger-width] p-0"
          align="start"
          onWheel={(e) => {
            e.stopPropagation()
          }}
        >
          <Command>
            <CommandInput placeholder="Search..." />
            <CommandList>
              <CommandEmpty>{emptyText}</CommandEmpty>
              <CommandGroup>
                {options.map((option) => {
                  const isAiSuggestion = aiSuggestion?.value === option
                  const isSelected = value === option
                  return (
                    <CommandItem
                      key={option}
                      value={option}
                      onSelect={(currentValue) => {
                        onValueChange(currentValue)
                        setOpen(false)
                      }}
                      className={cn(isSelected && 'bg-accent')}
                    >
                      <Check
                        className={cn(
                          'mr-2 h-4 w-4',
                          isSelected ? 'opacity-100' : 'opacity-0'
                        )}
                      />
                      <span className="flex-1">{option}</span>
                      {isAiSuggestion && aiSuggestion && (
                        <ConfidenceIndicator
                          confidence={aiSuggestion.confidence}
                          showLabel={false}
                        />
                      )}
                    </CommandItem>
                  )
                })}
              </CommandGroup>
            </CommandList>
          </Command>
        </PopoverContent>
      </Popover>
      {autoFillHint && (
        <div className="text-xs text-muted-foreground flex items-center gap-1">
          <span>🔄</span>
          <span>{autoFillHint}</span>
        </div>
      )}
    </div>
  )
}
