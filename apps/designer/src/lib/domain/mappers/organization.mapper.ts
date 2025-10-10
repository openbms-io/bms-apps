import type {
  Organization,
  CreateOrganization,
  UpdateOrganization,
} from '../models/organization'

type DbOrganization = {
  id: string
  name: string
  created_at: string
  updated_at: string
}

type DbInsertOrganization = {
  id: string
  name: string
  created_at: string
  updated_at: string
}

type DbUpdateOrganization = {
  name?: string
  updated_at?: string
}

export const OrganizationMapper = {
  toDTO(db: DbOrganization): Organization {
    return {
      id: db.id,
      name: db.name,
      createdAt: db.created_at,
      updatedAt: db.updated_at,
    }
  },

  toDbInsert(dto: CreateOrganization, id: string): DbInsertOrganization {
    const now = new Date().toISOString()
    return {
      id,
      name: dto.name,
      created_at: now,
      updated_at: now,
    }
  },

  toDbUpdate(dto: UpdateOrganization): Partial<DbUpdateOrganization> {
    const db: Partial<DbUpdateOrganization> = {}

    if (dto.name !== undefined) {
      db.name = dto.name
      db.updated_at = new Date().toISOString()
    }

    return db
  },
}
