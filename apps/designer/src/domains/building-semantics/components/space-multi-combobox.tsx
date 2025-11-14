'use client'

import { useState, useEffect } from 'react'
import { Check, ChevronsUpDown, X } from 'lucide-react'
import { cn } from '@/lib/utils'
import { Button } from '@/components/ui/button'
import { Badge } from '@/components/ui/badge'
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
import type { SpaceViewModel } from '../view-models/types'

interface SpaceMultiComboBoxProps {
  value: string[]
  onValueChange: (value: string[]) => void
  spaces: SpaceViewModel[]
  aiSuggestions?: Array<{
    id: string
    confidence: number
  }>
  placeholder?: string
  id?: string
}

export function SpaceMultiComboBox({
  value,
  onValueChange,
  spaces,
  aiSuggestions,
  placeholder = 'Select spaces...',
  id,
}: SpaceMultiComboBoxProps) {
  const [open, setOpen] = useState(false)
  const [searchValue, setSearchValue] = useState('')

  const handleSelect = (selectedValue: string) => {
    const isAlreadySelected = value.includes(selectedValue)

    if (isAlreadySelected) {
      onValueChange(value.filter((v) => v !== selectedValue))
    } else {
      onValueChange([...value, selectedValue])
    }
  }

  const handleRemove = (valueToRemove: string) => {
    onValueChange(value.filter((v) => v !== valueToRemove))
  }

  const handleInputChange = (inputValue: string) => {
    setSearchValue(inputValue)
  }

  const filteredSpaces = spaces.filter((space) =>
    space.label.toLowerCase().includes(searchValue.toLowerCase())
  )

  const showCreateNew =
    searchValue.trim().length > 0 &&
    !filteredSpaces.some(
      (space) => space.label.toLowerCase() === searchValue.toLowerCase().trim()
    ) &&
    !value.includes(searchValue.trim())

  const getAISuggestionConfidence = (spaceName: string): number | undefined => {
    return aiSuggestions?.find((s) => s.id === spaceName)?.confidence
  }

  return (
    <div className="space-y-2">
      {value.length > 0 && (
        <div className="flex flex-wrap gap-2">
          {value.map((selectedValue) => {
            const aiConfidence = getAISuggestionConfidence(selectedValue)
            return (
              <Badge key={selectedValue} variant="secondary" className="gap-1">
                {selectedValue}
                {aiConfidence !== undefined && (
                  <ConfidenceIndicator
                    confidence={aiConfidence}
                    showLabel={false}
                  />
                )}
                <button
                  type="button"
                  onClick={() => handleRemove(selectedValue)}
                  className="ml-1 rounded-full outline-none ring-offset-background focus:ring-2 focus:ring-ring focus:ring-offset-2"
                >
                  <X className="h-3 w-3" />
                </button>
              </Badge>
            )
          })}
        </div>
      )}

      <Popover open={open} onOpenChange={setOpen}>
        <PopoverTrigger asChild>
          <Button
            id={id}
            variant="outline"
            role="combobox"
            aria-expanded={open}
            className="w-full justify-between"
          >
            {value.length === 0 ? placeholder : `${value.length} selected`}
            <ChevronsUpDown className="ml-2 h-4 w-4 shrink-0 opacity-50" />
          </Button>
        </PopoverTrigger>
        <PopoverContent
          className="w-[--radix-popover-trigger-width] p-0"
          align="start"
        >
          <Command>
            <CommandInput
              placeholder="Search or type new space..."
              value={searchValue}
              onValueChange={handleInputChange}
            />
            <CommandList>
              {filteredSpaces.length === 0 && !showCreateNew && (
                <CommandEmpty>
                  No spaces found. Type to create new.
                </CommandEmpty>
              )}
              {filteredSpaces.length > 0 && (
                <CommandGroup heading="Available spaces">
                  {filteredSpaces.map((space) => {
                    const isAiSuggestion = aiSuggestions?.some(
                      (s) => s.id === space.label
                    )
                    const aiConfidence = getAISuggestionConfidence(space.label)
                    const isSelected = value.includes(space.label)
                    const pointCount = space.pointCount

                    return (
                      <CommandItem
                        key={space.id}
                        value={space.label}
                        onSelect={handleSelect}
                      >
                        <Check
                          className={cn(
                            'mr-2 h-4 w-4',
                            isSelected ? 'opacity-100' : 'opacity-0'
                          )}
                        />
                        <div className="flex-1 flex items-center justify-between">
                          <span>{space.label}</span>
                          <span className="text-xs text-muted-foreground ml-2">
                            {pointCount} {pointCount === 1 ? 'point' : 'points'}
                          </span>
                        </div>
                        {isAiSuggestion && aiConfidence !== undefined && (
                          <ConfidenceIndicator
                            confidence={aiConfidence}
                            showLabel={false}
                          />
                        )}
                      </CommandItem>
                    )
                  })}
                </CommandGroup>
              )}
              {showCreateNew && (
                <CommandGroup heading="Create new">
                  <CommandItem
                    value={searchValue}
                    onSelect={handleSelect}
                    className="text-primary"
                  >
                    <span className="mr-2">+</span>
                    <span>Create &quot;{searchValue}&quot;</span>
                  </CommandItem>
                </CommandGroup>
              )}
            </CommandList>
          </Command>
        </PopoverContent>
      </Popover>
    </div>
  )
}
