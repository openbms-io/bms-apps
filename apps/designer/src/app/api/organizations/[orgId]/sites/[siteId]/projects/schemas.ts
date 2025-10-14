import { z } from 'zod'
import { VersionedWorkflowConfigSchema } from '@/lib/workflow/config-schema'
// Import domain types (NOT database types)
import type {
  Project,
  CreateProject,
  UpdateProject,
} from '@/lib/domain/models/project'

// Re-export domain types for UI consumption
export type { Project, CreateProject, UpdateProject }

// Zod schemas ONLY for API request validation
export const CreateProjectRequestSchema = z.object({
  name: z
    .string()
    .min(1, 'Project name is required')
    .max(255, 'Project name too long'),
  description: z.string().optional(),
  workflowConfig: VersionedWorkflowConfigSchema.optional(),
})

export const UpdateProjectRequestSchema = z.object({
  name: z
    .string()
    .min(1, 'Project name is required')
    .max(255, 'Project name too long')
    .optional(),
  description: z.string().nullable().optional(),
  workflowConfig: VersionedWorkflowConfigSchema.optional(),
  iotDeviceId: z.string().uuid().nullable().optional(),
})

// Schema for project queries
export const ProjectQuerySchema = z.object({
  page: z
    .string()
    .nullish()
    .transform((val) => (val ? Number(val) : 1))
    .pipe(z.number().min(1)),
  limit: z
    .string()
    .nullish()
    .transform((val) => (val ? Number(val) : 20))
    .pipe(z.number().min(1).max(100)),
  search: z.string().nullish(),
  sort: z
    .enum(['name', 'created_at', 'updated_at'])
    .nullish()
    .default('updated_at'),
  order: z.enum(['asc', 'desc']).nullish().default('desc'),
})

export type ProjectQuery = z.infer<typeof ProjectQuerySchema>

// API response types
export type ProjectListResponse = {
  projects: Project[]
  total: number
  page: number
  limit: number
  pages: number
}

// Zod schemas for API response validation (used by API client)
const ProjectSchema = z.object({
  id: z.string(),
  siteId: z.string(),
  iotDeviceId: z.string().optional(),
  name: z.string(),
  description: z.string().optional(),
  workflowConfig: VersionedWorkflowConfigSchema.optional(),
  createdAt: z.string(),
  updatedAt: z.string(),
})

const ProjectListResponseDataSchema = z.object({
  projects: z.array(ProjectSchema),
  total: z.number(),
  page: z.number(),
  limit: z.number(),
  pages: z.number(),
})

export const ProjectsResponseSchema = z.object({
  success: z.boolean(),
  data: ProjectListResponseDataSchema.optional(),
  error: z.string().optional(),
})

export const ProjectResponseSchema = z.object({
  success: z.boolean(),
  project: ProjectSchema.optional(),
  error: z.string().optional(),
})
