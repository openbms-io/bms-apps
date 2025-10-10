import type {
  ControllerPoint,
  CreateControllerPoint,
  UpdateControllerPoint,
} from '../models/controller-point'
import type { BacnetMetadata } from '@/types/bacnet-metadata'

type DbControllerPoint = {
  id: string
  organization_id: string
  site_id: string
  iot_device_id: string
  controller_id: string
  point_name: string
  point_type: string
  object_identifier: string
  instance_number: number
  writable: boolean
  units: string | null
  description: string | null
  metadata: BacnetMetadata | '{}' | null
  created_at: string
  updated_at: string
}

type DbInsertControllerPoint = {
  id: string
  organization_id: string
  site_id: string
  iot_device_id: string
  controller_id: string
  point_name: string
  point_type: string
  object_identifier: string
  instance_number: number
  writable?: boolean
  units?: string
  description?: string
  metadata?: BacnetMetadata | '{}'
  created_at: string
  updated_at: string
}

type DbUpdateControllerPoint = {
  point_name?: string
  point_type?: string
  object_identifier?: string
  instance_number?: number
  writable?: boolean
  units?: string | null
  description?: string | null
  metadata?: BacnetMetadata | '{}' | null
  updated_at?: string
}

export const ControllerPointMapper = {
  toDTO(db: DbControllerPoint): ControllerPoint {
    return {
      id: db.id,
      organizationId: db.organization_id,
      siteId: db.site_id,
      iotDeviceId: db.iot_device_id,
      controllerId: db.controller_id,
      pointName: db.point_name,
      pointType: db.point_type,
      objectIdentifier: db.object_identifier,
      instanceNumber: db.instance_number,
      writable: db.writable,
      units: db.units ?? undefined,
      description: db.description ?? undefined,
      metadata: db.metadata === '{}' ? undefined : db.metadata ?? undefined,
      createdAt: db.created_at,
      updatedAt: db.updated_at,
    }
  },

  toDbInsert(dto: CreateControllerPoint, id: string): DbInsertControllerPoint {
    const now = new Date().toISOString()
    return {
      id,
      organization_id: dto.organizationId,
      site_id: dto.siteId,
      iot_device_id: dto.iotDeviceId,
      controller_id: dto.controllerId,
      point_name: dto.pointName,
      point_type: dto.pointType,
      object_identifier: dto.objectIdentifier,
      instance_number: dto.instanceNumber,
      writable: dto.writable ?? false,
      units: dto.units,
      description: dto.description,
      metadata: dto.metadata ?? '{}',
      created_at: now,
      updated_at: now,
    }
  },

  toDbUpdate(dto: UpdateControllerPoint): Partial<DbUpdateControllerPoint> {
    const db: Partial<DbUpdateControllerPoint> = {}
    let hasUpdates = false

    if (dto.pointName !== undefined) {
      db.point_name = dto.pointName
      hasUpdates = true
    }

    if (dto.pointType !== undefined) {
      db.point_type = dto.pointType
      hasUpdates = true
    }

    if (dto.objectIdentifier !== undefined) {
      db.object_identifier = dto.objectIdentifier
      hasUpdates = true
    }

    if (dto.instanceNumber !== undefined) {
      db.instance_number = dto.instanceNumber
      hasUpdates = true
    }

    if (dto.writable !== undefined) {
      db.writable = dto.writable
      hasUpdates = true
    }

    if (dto.units !== undefined) {
      db.units = dto.units
      hasUpdates = true
    }

    if (dto.description !== undefined) {
      db.description = dto.description
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
