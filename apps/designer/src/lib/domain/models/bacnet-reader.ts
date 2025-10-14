import type { BacnetMetadata } from '@/types/bacnet-metadata'

export type BacnetReader = {
  id: string
  organizationId: string
  siteId: string
  iotDeviceId: string
  ipAddress: string
  port: number
  deviceId: number
  subnetMask: 8 | 16 | 24 | 28 | 30
  bbmdEnabled: boolean
  bbmdServerIp?: string
  name: string
  description?: string
  isActive: boolean
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
  subnetMask: 8 | 16 | 24 | 28 | 30
  bbmdEnabled: boolean
  bbmdServerIp?: string
  name: string
  description?: string
  isActive: boolean
  metadata?: BacnetMetadata
}

export type UpdateBacnetReader = {
  ipAddress?: string
  port?: number
  deviceId?: number
  subnetMask?: 8 | 16 | 24 | 28 | 30
  bbmdEnabled?: boolean
  bbmdServerIp?: string | null
  name?: string
  description?: string | null
  isActive?: boolean
  metadata?: BacnetMetadata | null
}
