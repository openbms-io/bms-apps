import type {
  IotDeviceConfig,
  CreateIotDeviceConfig,
  UpdateIotDeviceConfig,
} from '../models/iot-device-config'
import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'

type DbIotDeviceConfig = {
  id: string
  project_id: string
  organization_id: string
  site_id: string
  iot_device_id: string
  config_data: ValidatedWorkflowConfig
  version: number
  is_active: boolean
  created_at: string
  updated_at: string
}

type DbInsertIotDeviceConfig = {
  id: string
  project_id: string
  organization_id: string
  site_id: string
  iot_device_id: string
  config_data: ValidatedWorkflowConfig
  version?: number
  is_active?: boolean
  created_at: string
  updated_at: string
}

type DbUpdateIotDeviceConfig = {
  config_data?: ValidatedWorkflowConfig
  version?: number
  is_active?: boolean
  updated_at?: string
}

export const IotDeviceConfigMapper = {
  toDTO(db: DbIotDeviceConfig): IotDeviceConfig {
    return {
      id: db.id,
      projectId: db.project_id,
      organizationId: db.organization_id,
      siteId: db.site_id,
      iotDeviceId: db.iot_device_id,
      configData: db.config_data,
      version: db.version,
      isActive: db.is_active,
      createdAt: db.created_at,
      updatedAt: db.updated_at,
    }
  },

  toDbInsert(dto: CreateIotDeviceConfig, id: string): DbInsertIotDeviceConfig {
    const now = new Date().toISOString()
    return {
      id,
      project_id: dto.projectId,
      organization_id: dto.organizationId,
      site_id: dto.siteId,
      iot_device_id: dto.iotDeviceId,
      config_data: dto.configData,
      version: dto.version ?? 1,
      is_active: dto.isActive ?? true,
      created_at: now,
      updated_at: now,
    }
  },

  toDbUpdate(dto: UpdateIotDeviceConfig): Partial<DbUpdateIotDeviceConfig> {
    const db: Partial<DbUpdateIotDeviceConfig> = {}
    let hasUpdates = false

    if (dto.configData !== undefined) {
      db.config_data = dto.configData
      hasUpdates = true
    }

    if (dto.version !== undefined) {
      db.version = dto.version
      hasUpdates = true
    }

    if (dto.isActive !== undefined) {
      db.is_active = dto.isActive
      hasUpdates = true
    }

    if (hasUpdates) {
      db.updated_at = new Date().toISOString()
    }

    return db
  },
}
