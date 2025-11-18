'use client'

import { useState, useEffect } from 'react'
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
import type { SpaceViewModel } from '../view-models/types'

interface SpaceComboBoxProps {
  value: string
  onValueChange: (value: string) => void
  spaces: SpaceViewModel[]
  aiSuggestion?: {
    id: string
    confidence: number
  }
  placeholder?: string
  id?: string
}

export function SpaceComboBox({
  value,
  onValueChange,
  spaces,
  aiSuggestion,
  placeholder = 'Select or type space name...',
  id,
}: SpaceComboBoxProps) {
  const [open, setOpen] = useState(false)
  const [searchValue, setSearchValue] = useState('')

  useEffect(() => {
    if (value) {
      setSearchValue(value)
    }
  }, [value])

  const handleSelect = (selectedValue: string) => {
    onValueChange(selectedValue)
    setSearchValue(selectedValue)
    setOpen(false)
  }

  const handleInputChange = (inputValue: string) => {
    setSearchValue(inputValue)
    onValueChange(inputValue)
  }

  const filteredSpaces = spaces.filter((space) =>
    space.label.toLowerCase().includes(searchValue.toLowerCase())
  )

  const showCreateNew =
    searchValue.trim().length > 0 &&
    !filteredSpaces.some(
      (space) => space.label.toLowerCase() === searchValue.toLowerCase().trim()
    )

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
                <CommandGroup heading="Recently used spaces">
                  {filteredSpaces.map((space) => {
                    const isAiSuggestion = aiSuggestion?.id === space.label
                    const isSelected = value === space.label
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
