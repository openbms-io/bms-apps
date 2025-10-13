import type { BacnetMetadata } from '@/types/bacnet-metadata'

export type ControllerPoint = {
  id: string
  organizationId: string
  siteId: string
  iotDeviceId: string
  controllerId: string
  pointName?: string
  pointType: string
  objectIdentifier?: string
  instanceNumber: number
  writable: boolean
  units?: string
  description?: string
  metadata?: BacnetMetadata
  createdAt: string
  updatedAt: string
}

export type CreateControllerPoint = {
  organizationId: string
  siteId: string
  iotDeviceId: string
  controllerId: string
  pointName: string
  pointType: string
  objectIdentifier: string
  instanceNumber: number
  writable?: boolean
  units?: string
  description?: string
  metadata?: BacnetMetadata
}

export type UpdateControllerPoint = {
  pointName?: string
  pointType?: string
  objectIdentifier?: string
  instanceNumber?: number
  writable?: boolean
  units?: string | null
  description?: string | null
  metadata?: BacnetMetadata | null
}
