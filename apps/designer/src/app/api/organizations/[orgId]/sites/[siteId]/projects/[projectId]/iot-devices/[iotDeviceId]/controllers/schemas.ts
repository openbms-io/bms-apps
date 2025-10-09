import { z } from 'zod'

export const IotDeviceRouteParamsSchema = z.object({
  orgId: z.string().startsWith('org_', 'Organization ID must start with org_'),
  siteId: z.string().uuid('Invalid site ID format'),
  projectId: z.string().uuid('Invalid project ID format'),
  iotDeviceId: z.string().uuid('Invalid IoT device ID format'),
})

export const ControllerRouteParamsSchema = IotDeviceRouteParamsSchema.extend({
  controllerId: z.string().uuid('Invalid controller ID format'),
})

export type IotDeviceRouteParams = z.infer<typeof IotDeviceRouteParamsSchema>
export type ControllerRouteParams = z.infer<typeof ControllerRouteParamsSchema>
