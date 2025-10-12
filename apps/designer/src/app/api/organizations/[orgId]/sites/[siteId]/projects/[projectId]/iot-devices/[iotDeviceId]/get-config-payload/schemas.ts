import { z } from 'zod'

export const GetConfigPayloadRouteParamsSchema = z.object({
  orgId: z.string(),
  siteId: z.string(),
  projectId: z.string(),
  iotDeviceId: z.string(),
})

export type GetConfigPayloadRouteParams = z.infer<
  typeof GetConfigPayloadRouteParamsSchema
>
