import { z } from 'zod'
import type {
  Organization,
  CreateOrganization,
  UpdateOrganization,
} from '@/lib/domain/models/organization'

export type { Organization, CreateOrganization, UpdateOrganization }

export const CreateOrganizationRequestSchema = z.object({
  name: z
    .string()
    .min(1, 'Organization name is required')
    .max(255, 'Organization name too long'),
})

export const UpdateOrganizationRequestSchema = z.object({
  name: z
    .string()
    .min(1, 'Organization name is required')
    .max(255, 'Organization name too long')
    .optional(),
})

export const OrganizationQuerySchema = z.object({
  page: z
    .string()
    .nullish()
    .transform((val) => (val ? Number(val) : 1))
    .pipe(z.number().min(1)),
  limit: z
    .string()
    .nullish()
    .transform((val) => (val ? Number(val) : 100))
    .pipe(z.number().min(1).max(100)),
})

export type OrganizationQuery = z.infer<typeof OrganizationQuerySchema>

export type OrganizationListResponse = {
  organizations: Organization[]
}
