import { z } from 'zod'
import type { Site, CreateSite, UpdateSite } from '@/lib/domain/models/site'

export type { Site, CreateSite, UpdateSite }

export const CreateSiteRequestSchema = z.object({
  organizationId: z.string().uuid('Invalid organization ID format'),
  name: z
    .string()
    .min(1, 'Site name is required')
    .max(255, 'Site name too long'),
  description: z.string().optional(),
})

export const UpdateSiteRequestSchema = z.object({
  name: z
    .string()
    .min(1, 'Site name is required')
    .max(255, 'Site name too long')
    .optional(),
  description: z.string().nullable().optional(),
})

export const SiteQuerySchema = z.object({
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

export type SiteQuery = z.infer<typeof SiteQuerySchema>

export type SiteListResponse = {
  sites: Site[]
}
