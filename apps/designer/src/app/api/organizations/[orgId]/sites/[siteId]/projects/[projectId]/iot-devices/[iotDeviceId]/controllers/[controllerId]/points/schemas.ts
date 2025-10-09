import { z } from 'zod'

export const ControllerRouteParamsSchema = z.object({
  orgId: z.string().startsWith('org_', 'Organization ID must start with org_'),
  siteId: z.string().uuid('Invalid site ID format'),
  projectId: z.string().uuid('Invalid project ID format'),
  iotDeviceId: z.string().uuid('Invalid IoT device ID format'),
  controllerId: z.string().uuid('Invalid controller ID format'),
})

export const ControllerPointRouteParamsSchema =
  ControllerRouteParamsSchema.extend({
    pointId: z.string().uuid('Invalid point ID format'),
  })

export type ControllerRouteParams = z.infer<typeof ControllerRouteParamsSchema>
export type ControllerPointRouteParams = z.infer<
  typeof ControllerPointRouteParamsSchema
>
