import type {
  Project,
  CreateProject,
  UpdateProject,
  ProjectQuery,
  ProjectListResponse,
} from '@/app/api/organizations/[orgId]/sites/[siteId]/projects/schemas'
import {
  ProjectsResponseSchema,
  ProjectResponseSchema,
} from '@/app/api/organizations/[orgId]/sites/[siteId]/projects/schemas'
import { withRetry, handleResponse } from './utils'
import { VersionedWorkflowConfig } from '../workflow/serializer'

export const projectsApi = {
  async list({
    orgId,
    siteId,
    ...query
  }: {
    orgId: string
    siteId: string
  } & ProjectQuery): Promise<ProjectListResponse> {
    const searchParams = new URLSearchParams()

    if (query?.page) searchParams.set('page', query.page.toString())
    if (query?.limit) searchParams.set('limit', query.limit.toString())
    if (query?.search) searchParams.set('search', query.search)
    if (query?.sort) searchParams.set('sort', query.sort)
    if (query?.order) searchParams.set('order', query.order)

    const url = `/api/organizations/${orgId}/sites/${siteId}/projects${
      searchParams.toString() ? `?${searchParams}` : ''
    }`

    const result = await withRetry(async () => {
      const response = await fetch(url)
      return handleResponse(response)
    })

    const parsed = ProjectsResponseSchema.parse(result)

    if (!parsed.success || !parsed.data) {
      throw new Error(parsed.error || 'Failed to fetch projects')
    }

    return parsed.data
  },

  async get({
    orgId,
    siteId,
    projectId,
  }: {
    orgId: string
    siteId: string
    projectId: string
  }): Promise<Project> {
    const result = await withRetry(async () => {
      const response = await fetch(
        `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}`
      )
      return handleResponse(response)
    })

    const parsed = ProjectResponseSchema.parse(result)

    if (!parsed.success || !parsed.project) {
      throw new Error(parsed.error || 'Project not found')
    }

    return parsed.project as Project
  },

  async create({
    orgId,
    siteId,
    ...data
  }: { orgId: string; siteId: string } & CreateProject): Promise<Project> {
    const result = await withRetry(async () => {
      const response = await fetch(
        `/api/organizations/${orgId}/sites/${siteId}/projects`,
        {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify(data),
        }
      )
      return handleResponse(response)
    })
    const parsed = ProjectResponseSchema.parse(result)

    if (!parsed.success || !parsed.project) {
      throw new Error(parsed.error || 'Failed to create project')
    }

    return parsed.project as Project
  },

  async update({
    orgId,
    siteId,
    projectId,
    ...data
  }: {
    orgId: string
    siteId: string
    projectId: string
  } & UpdateProject): Promise<Project> {
    const result = await withRetry(async () => {
      const response = await fetch(
        `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}`,
        {
          method: 'PUT',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify(data),
        }
      )
      return handleResponse(response)
    })
    const parsed = ProjectResponseSchema.parse(result)

    if (!parsed.success || !parsed.project) {
      throw new Error(parsed.error || 'Failed to update project')
    }

    return parsed.project as Project
  },

  async delete({
    orgId,
    siteId,
    projectId,
  }: {
    orgId: string
    siteId: string
    projectId: string
  }): Promise<void> {
    const result = await withRetry(async () => {
      const response = await fetch(
        `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}`,
        { method: 'DELETE' }
      )
      return handleResponse(response)
    })
    const parsed = ProjectResponseSchema.parse(result)

    if (!parsed.success) {
      throw new Error(parsed.error || 'Failed to delete project')
    }
  },
}
