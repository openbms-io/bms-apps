import type { Site, CreateSite, UpdateSite } from '../models/site'

type DbSite = {
  id: string
  organization_id: string
  name: string
  description: string | null
  created_at: string
  updated_at: string
}

type DbInsertSite = {
  id: string
  organization_id: string
  name: string
  description?: string
  created_at: string
  updated_at: string
}

type DbUpdateSite = {
  name?: string
  description?: string | null
  updated_at?: string
}

export const SiteMapper = {
  toDTO(db: DbSite): Site {
    return {
      id: db.id,
      organizationId: db.organization_id,
      name: db.name,
      description: db.description ?? undefined,
      createdAt: db.created_at,
      updatedAt: db.updated_at,
    }
  },

  toDbInsert(dto: CreateSite, id: string): DbInsertSite {
    const now = new Date().toISOString()
    return {
      id,
      organization_id: dto.organizationId,
      name: dto.name,
      description: dto.description,
      created_at: now,
      updated_at: now,
    }
  },

  toDbUpdate(dto: UpdateSite): Partial<DbUpdateSite> {
    const db: Partial<DbUpdateSite> = {}
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
