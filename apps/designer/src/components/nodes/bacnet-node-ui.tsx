'use client'

import { memo, useState, useMemo } from 'react'
import { Handle, Position, NodeProps } from '@xyflow/react'
import { Card } from '@/components/ui/card'
import { Badge } from '@/components/ui/badge'
import { Button } from '@/components/ui/button'
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu'
import { Plus, X, Info } from 'lucide-react'
import { PropertiesPanel } from './properties-panel'
import {
  getPropertyMetadata,
  BacnetProperties,
  StatusFlags,
} from '@/types/bacnet-properties'
import { BacnetNodeData } from '@/types/node-data-types'
import { useFlowStore } from '@/store/use-flow-store'

export const BacnetNodeUI = memo(({ data, id }: NodeProps) => {
  const typedData = data as BacnetNodeData
  const [showProperties, setShowProperties] = useState(false)

  // Subscribe to discoveredProperties from store for reactive updates
  const discoveredProperties = useFlowStore((state) => {
    const node = state.nodes.find((n) => n.id === id)
    return node?.data?.discoveredProperties ?? typedData.discoveredProperties
  }) as BacnetProperties

  // Local state for which properties to show in UI
  const [visibleProperties, setVisibleProperties] = useState<
    Set<keyof BacnetProperties>
  >(() => {
    // Start with presentValue and statusFlags if available
    const initial = new Set<keyof BacnetProperties>()
    if (discoveredProperties.presentValue !== undefined) {
      initial.add('presentValue')
    }
    if (discoveredProperties.statusFlags !== undefined) {
      initial.add('statusFlags')
    }
    return initial
  })

  // Get list of discovered properties that aren't visible
  const availableToAdd = useMemo(() => {
    const discovered = Object.keys(
      discoveredProperties
    ) as (keyof BacnetProperties)[]
    return discovered.filter((prop) => !visibleProperties.has(prop))
  }, [discoveredProperties, visibleProperties])

  // Add property to visible list
  const addProperty = (propertyName: keyof BacnetProperties) => {
    setVisibleProperties((prev) => new Set(prev).add(propertyName))
  }

  // Remove property from visible list
  const removeProperty = (propertyName: keyof BacnetProperties) => {
    setVisibleProperties((prev) => {
      const next = new Set(prev)
      next.delete(propertyName)
      return next
    })
  }

  return (
    <>
      <Card className="min-w-[200px] border-2">
        <div className="p-3">
          {/* Header with info button */}
          <div className="flex items-center justify-between mb-2">
            <span className="text-sm font-medium">{typedData.name}</span>
            <div className="flex items-center gap-1">
              <Badge variant="outline" className="text-xs">
                {typedData.objectType}
              </Badge>
              <Button
                size="icon"
                variant="ghost"
                className="h-6 w-6"
                onClick={(e) => {
                  e.stopPropagation() // Prevent node selection
                  setShowProperties(true)
                }}
                title="View all properties"
              >
                <Info className="h-3 w-3" />
              </Button>
            </div>
          </div>

          {/* Visible Properties */}
          <div className="space-y-2">
            {Array.from(visibleProperties).map((propertyName) => {
              const value = discoveredProperties[propertyName]
              const metadata = getPropertyMetadata(
                typedData.objectType,
                propertyName
              )

              if (value === undefined || !metadata) return null

              return (
                <div key={propertyName} className="relative group">
                  {/* Property row with handles */}
                  <div className="flex items-center gap-2">
                    {/* Input handle if writable */}
                    {metadata.writable && (
                      <Handle
                        type="target"
                        position={Position.Left}
                        id={propertyName}
                        className="!relative !top-auto !left-auto !transform-none w-2 h-2 bg-primary"
                        style={{ position: 'relative' }}
                      />
                    )}

                    {/* Property display */}
                    <div className="flex-1 text-xs">
                      <div className="text-muted-foreground">
                        {metadata.name}:
                      </div>
                      <div className="font-medium">
                        {propertyName === 'priorityArray' ? (
                          <PriorityArrayDropdown
                            value={
                              value as Array<{ type: string; value: number }>
                            }
                          />
                        ) : (
                          formatPropertyValue(propertyName, value, typedData)
                        )}
                      </div>
                    </div>

                    {/* Output handle if readable */}
                    {metadata.readable && (
                      <Handle
                        type="source"
                        position={Position.Right}
                        id={propertyName}
                        className="!relative !top-auto !right-auto !transform-none w-2 h-2 bg-primary"
                        style={{ position: 'relative' }}
                      />
                    )}

                    {/* Remove button */}
                    <Button
                      size="icon"
                      variant="ghost"
                      className="h-4 w-4 opacity-0 group-hover:opacity-100"
                      onClick={() => removeProperty(propertyName)}
                    >
                      <X className="h-3 w-3" />
                    </Button>
                  </div>
                </div>
              )
            })}
          </div>

          {/* Add Property Dropdown */}
          {availableToAdd.length > 0 && (
            <DropdownMenu>
              <DropdownMenuTrigger asChild>
                <Button
                  size="sm"
                  variant="ghost"
                  className="w-full mt-2 h-6 text-xs"
                >
                  <Plus className="h-3 w-3 mr-1" />
                  Add Property
                </Button>
              </DropdownMenuTrigger>
              <DropdownMenuContent>
                {availableToAdd.map((propertyName) => {
                  const metadata = getPropertyMetadata(
                    typedData.objectType,
                    propertyName
                  )
                  return (
                    <DropdownMenuItem
                      key={propertyName}
                      onClick={() => addProperty(propertyName)}
                    >
                      {metadata?.name || propertyName}
                    </DropdownMenuItem>
                  )
                })}
              </DropdownMenuContent>
            </DropdownMenu>
          )}
        </div>
      </Card>

      <PropertiesPanel
        isOpen={showProperties}
        onClose={() => setShowProperties(false)}
        node={typedData}
      />
    </>
  )
})

BacnetNodeUI.displayName = 'BacnetNodeUI'

function PriorityArrayDropdown({
  value,
}: {
  value: Array<{ type: string; value: number }>
}) {
  const activeCount = value.filter((slot) => slot.type !== 'null').length

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild>
        <button className="text-xs hover:underline cursor-pointer">
          {activeCount} active slot{activeCount !== 1 ? 's' : ''} ▼
        </button>
      </DropdownMenuTrigger>
      <DropdownMenuContent className="max-h-[300px] overflow-y-auto">
        {value.map((slot, index) => {
          const priority = index + 1
          const isActive = slot.type !== 'null'
          return (
            <DropdownMenuItem key={priority} className="text-xs font-mono">
              {isActive ? '✓' : '✗'} Priority {priority}:{' '}
              {isActive ? `${slot.value} (${slot.type})` : 'null'}
            </DropdownMenuItem>
          )
        })}
      </DropdownMenuContent>
    </DropdownMenu>
  )
}

function formatNumber(value: number | string): string {
  const num = typeof value === 'string' ? parseFloat(value) : value
  if (isNaN(num)) return String(value)
  return num.toFixed(2)
}

// Helper to format property values for display
function formatPropertyValue(
  propertyName: keyof BacnetProperties,
  value: BacnetProperties[keyof BacnetProperties],
  data: BacnetNodeData
): string {
  if (value === null || value === undefined) return 'N/A'

  // Handle StatusFlags specially
  if (propertyName === 'statusFlags' && typeof value === 'object') {
    const flags = value as StatusFlags
    const active = []
    if (flags.inAlarm) active.push('Alarm')
    if (flags.fault) active.push('Fault')
    if (flags.overridden) active.push('Override')
    if (flags.outOfService) active.push('OOS')
    return active.join(', ') || 'Normal'
  }

  // Handle stateText array display (skip null at index 0)
  if (propertyName === 'stateText' && Array.isArray(value)) {
    return value
      .filter((text) => text !== null) // Filter out null
      .map((text, i) => `${i + 1}: ${text}`)
      .join(', ')
  }

  // Handle multistate presentValue with stateText lookup
  if (
    propertyName === 'presentValue' &&
    data.objectType.includes('multistate') &&
    typeof value === 'number'
  ) {
    const stateText = data.discoveredProperties.stateText as
      | string[]
      | undefined
    if (stateText && stateText[value]) {
      return `${stateText[value]} (${value})`
    }
    return `State ${value}`
  }

  // Handle units if present (for non-multistate objects)
  if (
    propertyName === 'presentValue' &&
    !data.objectType.includes('multistate')
  ) {
    const units = data.discoveredProperties.units
    if (units) {
      const formattedValue = formatNumber(value as number | string)
      return `${formattedValue} ${units}`
    }
  }

  // Format numbers to 2 decimal places
  if (
    typeof value === 'number' ||
    (typeof value === 'string' && !isNaN(parseFloat(value as string)))
  ) {
    return formatNumber(value as number | string)
  }

  return String(value)
}
