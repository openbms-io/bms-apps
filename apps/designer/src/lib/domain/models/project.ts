import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'

export type Project = {
  id: string
  siteId: string
  iotDeviceId?: string
  name: string
  description?: string
  workflowConfig?: ValidatedWorkflowConfig
  createdAt: string
  updatedAt: string
}

export type CreateProject = {
  siteId: string
  name: string
  description?: string
  workflowConfig?: ValidatedWorkflowConfig
}

export type UpdateProject = {
  name?: string
  description?: string | null
  workflowConfig?: ValidatedWorkflowConfig
  iotDeviceId?: string | null
}
