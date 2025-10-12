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
  subnet_mask: number
  bbmd_enabled: boolean
  bbmd_server_ip: string | null
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
  subnet_mask: number
  bbmd_enabled: boolean
  bbmd_server_ip?: string
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
  subnet_mask?: number
  bbmd_enabled?: boolean
  bbmd_server_ip?: string | null
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
      subnetMask: db.subnet_mask as 8 | 16 | 24 | 28 | 30,
      bbmdEnabled: db.bbmd_enabled,
      bbmdServerIp: db.bbmd_server_ip ?? undefined,
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
      subnet_mask: dto.subnetMask,
      bbmd_enabled: dto.bbmdEnabled,
      bbmd_server_ip: dto.bbmdServerIp,
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

    if (dto.subnetMask !== undefined) {
      db.subnet_mask = dto.subnetMask
      hasUpdates = true
    }

    if (dto.bbmdEnabled !== undefined) {
      db.bbmd_enabled = dto.bbmdEnabled
      hasUpdates = true
    }

    if (dto.bbmdServerIp !== undefined) {
      db.bbmd_server_ip = dto.bbmdServerIp
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
