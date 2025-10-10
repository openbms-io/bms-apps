import type { BacnetMetadata } from '@/types/bacnet-metadata'

export type BacnetReader = {
  id: string
  organizationId: string
  siteId: string
  iotDeviceId: string
  ipAddress: string
  port: number
  deviceId: number
  networkNumber?: number
  macAddress?: string
  name: string
  description?: string
  isEnabled: boolean
  metadata?: BacnetMetadata
  createdAt: string
  updatedAt: string
}

export type CreateBacnetReader = {
  organizationId: string
  siteId: string
  iotDeviceId: string
  ipAddress: string
  port: number
  deviceId: number
  networkNumber?: number
  macAddress?: string
  name: string
  description?: string
  isEnabled?: boolean
  metadata?: BacnetMetadata
}

export type UpdateBacnetReader = {
  ipAddress?: string
  port?: number
  deviceId?: number
  networkNumber?: number | null
  macAddress?: string | null
  name?: string
  description?: string | null
  isEnabled?: boolean
  metadata?: BacnetMetadata | null
}
