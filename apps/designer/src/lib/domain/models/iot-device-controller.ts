import type { BacnetMetadata } from '@/types/bacnet-metadata'

export type IotDeviceController = {
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
  isActive: boolean
  metadata?: BacnetMetadata
  createdAt: string
  updatedAt: string
}

export type CreateIotDeviceController = {
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
  isActive: boolean
  metadata?: BacnetMetadata
}

export type UpdateIotDeviceController = {
  ipAddress?: string
  port?: number
  deviceId?: number
  networkNumber?: number | null
  macAddress?: string | null
  name?: string
  description?: string | null
  isActive?: boolean
  metadata?: BacnetMetadata | null
}
