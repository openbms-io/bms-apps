import type {
  BacnetReader,
  CreateBacnetReader,
  UpdateBacnetReader,
} from '../models/bacnet-reader'
import type { BacnetMetadata } from '@/types/bacnet-metadata'

type DbBacnetReader = {
  id: string
  organization_id: string
  site_id: string
  iot_device_id: string
  ip_address: string
  port: number
  device_id: number
  network_number: number | null
  mac_address: string | null
  name: string
  description: string | null
  is_active: boolean
  metadata: BacnetMetadata | '{}' | null
  created_at: string
  updated_at: string
}

type DbInsertBacnetReader = {
  id: string
  organization_id: string
  site_id: string
  iot_device_id: string
  ip_address: string
  port: number
  device_id: number
  network_number?: number
  mac_address?: string
  name: string
  description?: string
  is_active: boolean
  metadata?: BacnetMetadata | '{}'
  created_at: string
  updated_at: string
}

type DbUpdateBacnetReader = {
  ip_address?: string
  port?: number
  device_id?: number
  network_number?: number | null
  mac_address?: string | null
  name?: string
  description?: string | null
  is_active?: boolean
  metadata?: BacnetMetadata | '{}' | null
  updated_at?: string
}

export const BacnetReaderMapper = {
  toDTO(db: DbBacnetReader): BacnetReader {
    return {
      id: db.id,
      organizationId: db.organization_id,
      siteId: db.site_id,
      iotDeviceId: db.iot_device_id,
      ipAddress: db.ip_address,
      port: db.port,
      deviceId: db.device_id,
      networkNumber: db.network_number ?? undefined,
      macAddress: db.mac_address ?? undefined,
      name: db.name,
      description: db.description ?? undefined,
      isActive: db.is_active,
      metadata: db.metadata === '{}' ? undefined : db.metadata ?? undefined,
      createdAt: db.created_at,
      updatedAt: db.updated_at,
    }
  },

  toDbInsert(dto: CreateBacnetReader, id: string): DbInsertBacnetReader {
    const now = new Date().toISOString()
    return {
      id,
      organization_id: dto.organizationId,
      site_id: dto.siteId,
      iot_device_id: dto.iotDeviceId,
      ip_address: dto.ipAddress,
      port: dto.port,
      device_id: dto.deviceId,
      network_number: dto.networkNumber,
      mac_address: dto.macAddress,
      name: dto.name,
      description: dto.description,
      is_active: dto.isActive,
      metadata: dto.metadata ?? '{}',
      created_at: now,
      updated_at: now,
    }
  },

  toDbUpdate(dto: UpdateBacnetReader): Partial<DbUpdateBacnetReader> {
    const db: Partial<DbUpdateBacnetReader> = {}
    let hasUpdates = false

    if (dto.ipAddress !== undefined) {
      db.ip_address = dto.ipAddress
      hasUpdates = true
    }

    if (dto.port !== undefined) {
      db.port = dto.port
      hasUpdates = true
    }

    if (dto.deviceId !== undefined) {
      db.device_id = dto.deviceId
      hasUpdates = true
    }

    if (dto.networkNumber !== undefined) {
      db.network_number = dto.networkNumber
      hasUpdates = true
    }

    if (dto.macAddress !== undefined) {
      db.mac_address = dto.macAddress
      hasUpdates = true
    }

    if (dto.name !== undefined) {
      db.name = dto.name
      hasUpdates = true
    }

    if (dto.description !== undefined) {
      db.description = dto.description
      hasUpdates = true
    }

    if (dto.isActive !== undefined) {
      db.is_active = dto.isActive
      hasUpdates = true
    }

    if (dto.metadata !== undefined) {
      db.metadata = dto.metadata ?? '{}'
      hasUpdates = true
    }

    if (hasUpdates) {
      db.updated_at = new Date().toISOString()
    }

    return db
  },
}
