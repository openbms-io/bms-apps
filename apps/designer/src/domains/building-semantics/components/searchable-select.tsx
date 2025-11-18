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

interface SearchableSelectOption {
  value: string
  label: string
  metadata?: {
    quantityKind?: string | null
    unit?: string | null
    medium?: string | null
  }
}

interface SearchableSelectProps {
  value: string
  onValueChange: (value: string) => void
  options: SearchableSelectOption[]
  aiSuggestion?: {
    id: string
    confidence: number
  }
  placeholder?: string
  emptyText?: string
  id?: string
  disabled?: boolean
}

export function SearchableSelect({
  value,
  onValueChange,
  options,
  aiSuggestion,
  disabled = false,
  placeholder = 'Select...',
  emptyText = 'No results found.',
  id,
}: SearchableSelectProps) {
  const [open, setOpen] = useState(false)
  const selectedOption = options.find((opt) => opt.value === value)
  const displayValue = selectedOption?.label || placeholder

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
            disabled={disabled}
          >
            {displayValue}
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
                {options.map((option, index) => {
                  const isAiSuggestion = aiSuggestion?.id === option.value
                  const isSelected = value === option.value
                  return (
                    <CommandItem
                      key={`${index}-${option.value}`}
                      value={option.label}
                      onSelect={() => {
                        onValueChange(option.value)
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
                      <div className="flex-1 flex items-center gap-2">
                        <span>{option.label}</span>
                        {option.metadata && (
                          <div className="flex items-center gap-1 text-xs text-muted-foreground">
                            {option.metadata.quantityKind && (
                              <span className="px-1.5 py-0.5 bg-muted rounded">
                                {option.metadata.quantityKind}
                              </span>
                            )}
                            {option.metadata.unit && (
                              <span className="px-1.5 py-0.5 bg-muted rounded">
                                {option.metadata.unit}
                              </span>
                            )}
                            {option.metadata.medium && (
                              <span className="px-1.5 py-0.5 bg-muted rounded text-blue-600">
                                {option.metadata.medium}
                              </span>
                            )}
                          </div>
                        )}
                      </div>
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
    </div>
  )
}
