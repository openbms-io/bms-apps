import { z } from 'zod'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
} from '../schemas'
import type { CreateIotDeviceController } from '@/lib/domain/models/iot-device-controller'

export { IotDeviceRouteParamsSchema, type IotDeviceRouteParams }

export const ControllerRouteParamsSchema = IotDeviceRouteParamsSchema.extend({
  controllerId: z.string().uuid('Invalid controller ID format'),
})

export type ControllerRouteParams = z.infer<typeof ControllerRouteParamsSchema>

export const CreateIotDeviceControllerRequestSchema = z.object({
  name: z.string().min(1),
  ipAddress: z.string().ip(),
  port: z.number().int().min(1).max(65535),
  deviceId: z.number().int().nonnegative(),
  networkNumber: z.number().int().nonnegative().optional(),
  macAddress: z.string().optional(),
  isActive: z.boolean().default(true),
  description: z.string().optional(),
  metadata: z.any().optional(),
}) satisfies z.ZodType<
  Omit<CreateIotDeviceController, 'organizationId' | 'siteId' | 'iotDeviceId'>
>
