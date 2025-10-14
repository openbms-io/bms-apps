import { z } from 'zod'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
} from '../schemas'

export { IotDeviceRouteParamsSchema, type IotDeviceRouteParams }

export const ConfigRouteParamsSchema = IotDeviceRouteParamsSchema.extend({
  configId: z.string().uuid('Invalid config ID format'),
})

export type ConfigRouteParams = z.infer<typeof ConfigRouteParamsSchema>
