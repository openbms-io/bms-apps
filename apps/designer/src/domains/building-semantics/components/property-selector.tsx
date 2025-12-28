'use client'

import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import type { PropertyDto } from '../api/generated/types.gen'
import type { AISuggestion } from '../types/ai-suggestion'
import { AiSuggestedBadge } from './ui/ai-suggested-badge'
import { AISuggestionIndicatorTooltip } from './ai-suggestion-indicator-tooltip'
import {
  getPropertyCompactLabel,
  formatEnumerationKind,
} from '../utils/property-formatting'

interface PropertySelectorProps {
  properties: PropertyDto[]
  selectedPropertyId?: string
  onPropertySelect: (propertyUri: string) => void
  disabled: boolean
  isLoading: boolean
  bacnetObjectType?: string
  aiSuggestion?: AISuggestion
  isLoadingAi: boolean
  isLowConfidence: boolean
}

export function PropertySelector({
  properties,
  selectedPropertyId,
  onPropertySelect,
  disabled,
  isLoading,
  bacnetObjectType,
  aiSuggestion,
  isLoadingAi,
  isLowConfidence,
}: PropertySelectorProps) {
  const getPlaceholder = () => {
    if (isLoading) return 'Loading properties...'
    if (disabled) return 'Select a device first'
    if (bacnetObjectType) {
      return `Select property (${bacnetObjectType})...`
    }
    return 'Select property...'
  }

  const selectedProperty = properties.find(
    (p) => p.propertyUri === selectedPropertyId
  )

  const isAiSuggestionSelected = selectedPropertyId === aiSuggestion?.selectedId

  return (
    <div className="space-y-1.5">
      <div className="flex items-center gap-2">
        <Select
          value={selectedPropertyId}
          onValueChange={onPropertySelect}
          disabled={disabled || isLoading}
        >
          <SelectTrigger className="flex-1">
            <SelectValue placeholder={getPlaceholder()} />
          </SelectTrigger>
          <SelectContent>
            {properties.length === 0 && !isLoading ? (
              <div className="text-sm text-muted-foreground p-2">
                No compatible properties for {bacnetObjectType || 'this device'}
              </div>
            ) : (
              properties.map((property) => {
                const isAiSuggested =
                  property.propertyUri === aiSuggestion?.selectedId
                return (
                  <SelectItem
                    key={property.propertyUri}
                    value={property.propertyUri}
                  >
                    <div className="flex items-center gap-2">
                      <AiSuggestedBadge show={isAiSuggested} />
                      <span>{getPropertyCompactLabel(property)}</span>
                    </div>
                  </SelectItem>
                )
              })
            )}
          </SelectContent>
        </Select>
        <AISuggestionIndicatorTooltip
          aiSuggestion={aiSuggestion}
          isLoading={isLoadingAi && !disabled}
          isSelected={isAiSuggestionSelected}
        />
      </div>

      {isLowConfidence && !selectedPropertyId && (
        <p className="text-xs text-amber-600">
          Low confidence match. Please verify your selection.
        </p>
      )}

      {selectedProperty && (
        <div className="text-xs text-muted-foreground">
          {selectedProperty.propertyType === 'enumerated' &&
            selectedProperty.enumerationKind && (
              <span>
                State: {formatEnumerationKind(selectedProperty.enumerationKind)}
              </span>
            )}
          {selectedProperty.propertyType === 'quantifiable' &&
            selectedProperty.unit && <span>{selectedProperty.unit}</span>}
          {selectedProperty.medium && <span> • {selectedProperty.medium}</span>}
        </div>
      )}
    </div>
  )
}
