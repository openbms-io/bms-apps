import { z } from 'zod'

export const ProjectRouteParamsSchema = z.object({
  orgId: z.string(),
  siteId: z.string(),
  projectId: z.string(),
})

export const IotDeviceRouteParamsSchema = ProjectRouteParamsSchema.extend({
  id: z.string(),
})

export const CreateIotDeviceSchema = z.object({
  name: z.string().min(1, 'Name is required'),
  description: z.string().optional(),
})

export type ProjectRouteParams = z.infer<typeof ProjectRouteParamsSchema>
export type IotDeviceRouteParams = z.infer<typeof IotDeviceRouteParamsSchema>
export type CreateIotDeviceInput = z.infer<typeof CreateIotDeviceSchema>
