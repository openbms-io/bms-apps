'use client'

import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import type { PropertyDto } from '../api/generated/types.gen'
import {
  getPropertyCompactLabel,
  formatEnumerationKind,
} from '../utils/property-formatting'

interface PropertySelectorProps {
  properties: PropertyDto[]
  selectedPropertyId?: string
  onPropertySelect: (propertyUri: string) => void
  disabled?: boolean
  isLoading?: boolean
  bacnetObjectType?: string
}

export function PropertySelector({
  properties,
  selectedPropertyId,
  onPropertySelect,
  disabled = false,
  isLoading = false,
  bacnetObjectType,
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

  return (
    <div className="space-y-1.5">
      <Select
        value={selectedPropertyId}
        onValueChange={onPropertySelect}
        disabled={disabled || isLoading}
      >
        <SelectTrigger>
          <SelectValue placeholder={getPlaceholder()} />
        </SelectTrigger>
        <SelectContent>
          {properties.length === 0 && !isLoading ? (
            <div className="text-sm text-muted-foreground p-2">
              No compatible properties for {bacnetObjectType || 'this device'}
            </div>
          ) : (
            properties.map((property) => (
              <SelectItem
                key={property.propertyUri}
                value={property.propertyUri}
              >
                {getPropertyCompactLabel(property)}
              </SelectItem>
            ))
          )}
        </SelectContent>
      </Select>

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
