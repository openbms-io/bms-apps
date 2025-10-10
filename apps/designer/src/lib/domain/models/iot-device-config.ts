import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'

export type IotDeviceConfig = {
  id: string
  projectId: string
  organizationId: string
  siteId: string
  iotDeviceId: string
  configData: ValidatedWorkflowConfig
  version: number
  isActive: boolean
  createdAt: string
  updatedAt: string
}

export type CreateIotDeviceConfig = {
  projectId: string
  organizationId: string
  siteId: string
  iotDeviceId: string
  configData: ValidatedWorkflowConfig
  version?: number
  isActive?: boolean
}

export type UpdateIotDeviceConfig = {
  configData?: ValidatedWorkflowConfig
  version?: number
  isActive?: boolean
}
