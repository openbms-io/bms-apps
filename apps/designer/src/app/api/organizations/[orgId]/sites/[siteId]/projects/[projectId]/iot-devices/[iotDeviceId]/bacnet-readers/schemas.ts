import { z } from 'zod'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
} from '../schemas'
import type { CreateBacnetReader } from '@/lib/domain/models/bacnet-reader'

export { IotDeviceRouteParamsSchema, type IotDeviceRouteParams }

export const BacnetReaderRouteParamsSchema = IotDeviceRouteParamsSchema.extend({
  readerId: z.string().uuid('Invalid reader ID format'),
})

export type BacnetReaderRouteParams = z.infer<
  typeof BacnetReaderRouteParamsSchema
>

export const CreateBacnetReaderRequestSchema = z.object({
  name: z.string().min(1),
  ipAddress: z.string().ip(),
  port: z.number().int().min(1).max(65535),
  deviceId: z.number().int().nonnegative(),
  subnetMask: z.union([
    z.literal(8),
    z.literal(16),
    z.literal(24),
    z.literal(28),
    z.literal(30),
  ]),
  bbmdEnabled: z.boolean(),
  bbmdServerIp: z.string().ip().optional(),
  isActive: z.boolean(),
  description: z.string().optional(),
  metadata: z.any().optional(),
}) satisfies z.ZodType<
  Omit<CreateBacnetReader, 'organizationId' | 'siteId' | 'iotDeviceId'>
>
