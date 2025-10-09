import { z } from 'zod'

export const IotDeviceRouteParamsSchema = z.object({
  orgId: z.string().startsWith('org_', 'Organization ID must start with org_'),
  siteId: z.string().uuid('Invalid site ID format'),
  projectId: z.string().uuid('Invalid project ID format'),
  iotDeviceId: z.string().uuid('Invalid IoT device ID format'),
})

export const ConfigRouteParamsSchema = IotDeviceRouteParamsSchema.extend({
  configId: z.string().uuid('Invalid config ID format'),
})

export type IotDeviceRouteParams = z.infer<typeof IotDeviceRouteParamsSchema>
export type ConfigRouteParams = z.infer<typeof ConfigRouteParamsSchema>
