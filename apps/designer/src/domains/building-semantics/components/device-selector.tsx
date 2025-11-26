'use client'

import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import type { DeviceDto } from '../api/generated/types.gen'

interface DeviceSelectorProps {
  devices: DeviceDto[]
  selectedDeviceId?: string
  onDeviceSelect: (deviceUri: string) => void
  disabled?: boolean
  isLoading?: boolean
}

export function DeviceSelector({
  devices,
  selectedDeviceId,
  onDeviceSelect,
  disabled = false,
  isLoading = false,
}: DeviceSelectorProps) {
  return (
    <Select
      value={selectedDeviceId}
      onValueChange={onDeviceSelect}
      disabled={disabled || isLoading}
    >
      <SelectTrigger>
        <SelectValue
          placeholder={
            isLoading
              ? 'Loading devices...'
              : disabled
                ? 'Select a system first'
                : 'Select device...'
          }
        />
      </SelectTrigger>
      <SelectContent>
        {devices.map((device) => (
          <SelectItem key={device.deviceUri} value={device.deviceUri}>
            {device.label}
          </SelectItem>
        ))}
      </SelectContent>
    </Select>
  )
}
