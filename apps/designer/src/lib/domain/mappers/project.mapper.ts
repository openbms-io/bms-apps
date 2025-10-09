import type { Project, CreateProject, UpdateProject } from '../models/project'

type DbProject = {
  id: string
  site_id: string
  iot_device_id: string | null
  name: string
  description: string | null
  workflow_config: string | null
  created_at: string
  updated_at: string
}

type DbInsertProject = {
  site_id: string
  name: string
  description?: string
  workflow_config?: string | null
}

type DbUpdateProject = {
  name?: string
  description?: string | null
  workflow_config?: string | null
  iot_device_id?: string | null
}

export const ProjectMapper = {
  toDTO(db: DbProject): Project {
    return {
      id: db.id,
      siteId: db.site_id,
      iotDeviceId: db.iot_device_id ?? undefined,
      name: db.name,
      description: db.description ?? undefined,
      workflowConfig: db.workflow_config
        ? JSON.parse(db.workflow_config)
        : undefined,
      createdAt: db.created_at,
      updatedAt: db.updated_at,
    }
  },

  toDbInsert(dto: CreateProject): DbInsertProject {
    return {
      site_id: dto.siteId,
      name: dto.name,
      description: dto.description,
      workflow_config: dto.workflowConfig
        ? JSON.stringify(dto.workflowConfig)
        : null,
    }
  },

  toDbUpdate(dto: UpdateProject): Partial<DbUpdateProject> {
    const db: Partial<DbUpdateProject> = {}

    if (dto.name !== undefined) {
      db.name = dto.name
    }

    if (dto.description !== undefined) {
      db.description = dto.description
    }

    if (dto.iotDeviceId !== undefined) {
      db.iot_device_id = dto.iotDeviceId
    }

    if (dto.workflowConfig !== undefined) {
      db.workflow_config = dto.workflowConfig
        ? JSON.stringify(dto.workflowConfig)
        : null
    }

    return db
  },
}
