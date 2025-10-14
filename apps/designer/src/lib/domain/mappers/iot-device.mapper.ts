import type {
  IotDevice,
  CreateIotDevice,
  UpdateIotDevice,
} from '../models/iot-device'

type DbIotDevice = {
  id: string
  organization_id: string
  site_id: string
  name: string
  description: string | null
  created_at: string
  updated_at: string
}

type DbInsertIotDevice = {
  id: string
  organization_id: string
  site_id: string
  name: string
  description?: string
  created_at: string
  updated_at: string
}

type DbUpdateIotDevice = {
  name?: string
  description?: string | null
  updated_at?: string
}

export const IotDeviceMapper = {
  toDTO(db: DbIotDevice): IotDevice {
    return {
      id: db.id,
      organizationId: db.organization_id,
      siteId: db.site_id,
      name: db.name,
      description: db.description ?? undefined,
      createdAt: db.created_at,
      updatedAt: db.updated_at,
    }
  },

  toDbInsert(dto: CreateIotDevice, id: string): DbInsertIotDevice {
    const now = new Date().toISOString()
    return {
      id,
      organization_id: dto.organizationId,
      site_id: dto.siteId,
      name: dto.name,
      description: dto.description,
      created_at: now,
      updated_at: now,
    }
  },

  toDbUpdate(dto: UpdateIotDevice): Partial<DbUpdateIotDevice> {
    const db: Partial<DbUpdateIotDevice> = {}
    let hasUpdates = false

    if (dto.name !== undefined) {
      db.name = dto.name
      hasUpdates = true
    }

    if (dto.description !== undefined) {
      db.description = dto.description
      hasUpdates = true
    }

    if (hasUpdates) {
      db.updated_at = new Date().toISOString()
    }

    return db
  },
}
