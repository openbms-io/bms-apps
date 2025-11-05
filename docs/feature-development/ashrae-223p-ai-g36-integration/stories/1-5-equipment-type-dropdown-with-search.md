# Story 1.5: Equipment Type Dropdown with Search

**Epic:** Epic 1 - 223P Mapping UI with Mock DTOs
**Status:** done
**Created:** 2025-11-02
**Completed:** 2025-11-02
**Complexity:** 5 (Medium)
**Estimated Hours:** 3-4 hours

---

## User Story

**As a** BMS integrator,
**I want** to search and select equipment types in the mapping popup,
**So that** I can quickly find the correct type when AI suggestion is wrong.

---

## Acceptance Criteria

Reference: Tech Spec AC-5

### 1. ✅ Dropdown Content

- Displays all 8 equipment types from mock service
- Types listed in logical order (HVAC → water systems)

### 2. ✅ Search/Filter

- Type-to-filter: Typing "VAV" filters to "VAV Reheat Terminal Unit", "Lab VAV Reheat Terminal Unit"
- Search is case-insensitive
- Clear search button visible when text entered

### 3. ✅ AI Suggestion Highlight

- AI-suggested item marked with ✓ badge and confidence %
- Example: `✓ VAV Reheat Terminal Unit 95%`
- Badge color: Green (success variant)

### 4. ✅ Selection UX

- Currently selected item highlighted
- Dropdown closes on selection
- Selected value displayed in trigger button

### 5. ✅ Keyboard Navigation

- Arrow keys: Navigate list
- Enter: Select highlighted item
- ESC: Close dropdown without changing selection
- Tab: Move to next dropdown

### 6. ✅ Component

- Uses shadcn/ui `Combobox` component (or enhanced `Select`)
- Consistent styling with existing Designer app

---

## Verification Checklist

**Search Functionality:**

- [ ] Type "VAV" → list filters to 2 VAV types
- [ ] Type "water" → list filters to water systems
- [ ] Search is case-insensitive
- [ ] Clear button clears search and shows all types

**AI Suggestion:**

- [ ] AI-suggested item shows ✓ badge
- [ ] Confidence % displayed next to AI suggestion
- [ ] Badge color is green (success variant)

**Selection:**

- [ ] Click item → selects and closes dropdown
- [ ] Selected value shown in trigger button
- [ ] Can change selection after initial selection

**Keyboard Navigation:**

- [ ] Arrow keys navigate through filtered list
- [ ] Enter key selects highlighted item
- [ ] ESC key closes dropdown
- [ ] Tab key moves to next field

---

## Implementation Guidance

### File Structure

```
apps/designer/src/domains/223p/
└── components/
    └── searchable-select.tsx    # Reusable searchable dropdown
```

### Combobox vs Enhanced Select

**Option 1: shadcn/ui Combobox** (Recommended)

- Built-in search/filter functionality
- Better UX for searchable lists
- Uses Radix UI Popover + Command

**Option 2: Enhanced Select with filter**

- Add search input to existing Select
- Manually filter options
- More custom control

### Searchable Select Component

```typescript
// components/searchable-select.tsx

import { useState } from 'react';
import { Check, ChevronsUpDown } from 'lucide-react';
import { cn } from '@/lib/utils';
import { Button } from '@/components/ui/button';
import {
  Command,
  CommandEmpty,
  CommandGroup,
  CommandInput,
  CommandItem,
  CommandList,
} from '@/components/ui/command';
import {
  Popover,
  PopoverContent,
  PopoverTrigger,
} from '@/components/ui/popover';
import { ConfidenceIndicator } from './confidence-indicator';

interface SearchableSelectProps {
  value: string;
  onValueChange: (value: string) => void;
  options: string[];
  aiSuggestion?: {
    value: string;
    confidence: number;
  };
  placeholder?: string;
  emptyText?: string;
  id?: string;
}

export function SearchableSelect({
  value,
  onValueChange,
  options,
  aiSuggestion,
  placeholder = 'Select...',
  emptyText = 'No results found.',
  id,
}: SearchableSelectProps) {
  const [open, setOpen] = useState(false);

  return (
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
      <PopoverContent className="w-full p-0">
        <Command>
          <CommandInput placeholder="Search..." />
          <CommandList>
            <CommandEmpty>{emptyText}</CommandEmpty>
            <CommandGroup>
              {options.map((option) => {
                const isAiSuggestion = aiSuggestion?.value === option;
                return (
                  <CommandItem
                    key={option}
                    value={option}
                    onSelect={(currentValue) => {
                      onValueChange(currentValue === value ? '' : currentValue);
                      setOpen(false);
                    }}
                  >
                    <Check
                      className={cn(
                        'mr-2 h-4 w-4',
                        value === option ? 'opacity-100' : 'opacity-0'
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
                );
              })}
            </CommandGroup>
          </CommandList>
        </Command>
      </PopoverContent>
    </Popover>
  );
}
```

### Integration into Mapping Modal

```typescript
// Replace Select with SearchableSelect in mapping-popup-modal.tsx

<div className="space-y-2">
  <Label htmlFor="equipment-type">Equipment Type</Label>
  <SearchableSelect
    id="equipment-type"
    value={equipmentType}
    onValueChange={setEquipmentType}
    options={equipmentTypes}
    aiSuggestion={{
      value: suggestion.equipmentType.value,
      confidence: suggestion.equipmentType.confidence,
    }}
    placeholder="Select equipment type..."
    emptyText="No equipment types found."
  />
  {suggestion && (
    <ConfidenceIndicator
      confidence={suggestion.equipmentType.confidence}
    />
  )}
</div>
```

---

## Technical Notes

### shadcn/ui Command Component

The Combobox pattern uses:

- `Command` - cmdk library for command palette functionality
- `CommandInput` - Built-in search/filter
- `CommandItem` - List items with selection
- `Popover` - Dropdown positioning

Install if not available:

```bash
npx shadcn@latest add command
npx shadcn@latest add popover
```

### Search Algorithm

Command component provides built-in fuzzy search:

- Case-insensitive by default
- Matches anywhere in string
- Filters as user types

### AI Suggestion Badge

Display confidence % inline with item:

```tsx
<CommandItem>
  <Check /> {/* Selection indicator */}
  <span>VAV Reheat Terminal Unit</span>
  <ConfidenceIndicator confidence={95} showLabel={false} />
</CommandItem>
```

### Reusability

This `SearchableSelect` component can be reused for:

- Story 1.6: Device Type dropdown
- Story 1.6: Observable Property dropdown
- Future dropdowns in other features

---

## Prerequisites

**Story 1.4** ✅ Complete

- Requires: MappingPopupModal component

**Story 1.3** ✅ Complete

- Requires: AI suggestion service

**shadcn/ui components:**

- Command (needs installation)
- Popover (needs installation)
- Button (already installed)

---

## Dependencies

**Stories that depend on this:**

- Story 1.6: Device Type and Property Dropdowns (reuses SearchableSelect)

---

## Definition of Done

- [ ] SearchableSelect component created
- [ ] Command and Popover components installed (if needed)
- [ ] Search/filter functionality working
- [ ] AI suggestion highlighted with ✓ badge
- [ ] Confidence % displayed next to AI suggestion
- [ ] Keyboard navigation working (arrow keys, Enter, ESC)
- [ ] Integrated into MappingPopupModal for Equipment Type
- [ ] Selected value displayed in trigger button
- [ ] Clear search resets filter
- [ ] TypeScript compiles without errors
- [ ] Component follows shadcn/ui patterns
- [ ] Code follows project conventions
- [ ] Manual test with sample data successful
- [ ] Files committed to git with descriptive commit message

---

## References

- **Tech Spec:** AC-5 (lines 2596-2638)
- **Story 1.4:** 223P Mapping Popup Modal
- **shadcn/ui Combobox:** https://ui.shadcn.com/docs/components/combobox
- **shadcn/ui Command:** https://ui.shadcn.com/docs/components/command
