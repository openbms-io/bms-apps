'use client'

import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import type { DeviceDto } from '../api/generated/types.gen'
import type { AISuggestion } from '../types/ai-suggestion'
import { AiSuggestedBadge } from './ui/ai-suggested-badge'
import { AISuggestionIndicatorTooltip } from './ai-suggestion-indicator-tooltip'

interface DeviceSelectorProps {
  devices: DeviceDto[]
  selectedDeviceId?: string
  onDeviceSelect: (deviceUri: string) => void
  disabled: boolean
  isLoading: boolean
  aiSuggestion?: AISuggestion
  isLoadingAi: boolean
  isLowConfidence: boolean
}

export function DeviceSelector({
  devices,
  selectedDeviceId,
  onDeviceSelect,
  disabled,
  isLoading,
  aiSuggestion,
  isLoadingAi,
  isLowConfidence,
}: DeviceSelectorProps) {
  const getPlaceholder = () => {
    if (isLoading) return 'Loading devices...'
    if (disabled) return 'Select a system first'
    return 'Select device...'
  }

  const isAiSuggestionSelected = selectedDeviceId === aiSuggestion?.selectedId

  return (
    <div className="space-y-2">
      <div className="flex items-center gap-2">
        <Select
          value={selectedDeviceId}
          onValueChange={onDeviceSelect}
          disabled={disabled || isLoading}
        >
          <SelectTrigger className="flex-1">
            <SelectValue placeholder={getPlaceholder()} />
          </SelectTrigger>
          <SelectContent>
            {devices.map((device) => {
              const isAiSuggested =
                device.deviceUri === aiSuggestion?.selectedId
              return (
                <SelectItem key={device.deviceUri} value={device.deviceUri}>
                  <div className="flex items-center gap-2">
                    <AiSuggestedBadge show={isAiSuggested} />
                    <span>{device.label}</span>
                  </div>
                </SelectItem>
              )
            })}
          </SelectContent>
        </Select>
        <AISuggestionIndicatorTooltip
          aiSuggestion={aiSuggestion}
          isLoading={isLoadingAi && !disabled}
          isSelected={isAiSuggestionSelected}
        />
      </div>

      {isLowConfidence && !selectedDeviceId && (
        <p className="text-xs text-amber-600">
          Low confidence match. Please verify your selection.
        </p>
      )}
    </div>
  )
}
