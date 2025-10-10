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
  networkNumber: z.number().int().nonnegative().optional(),
  macAddress: z.string().optional(),
  isActive: z.boolean().default(true),
  description: z.string().optional(),
  metadata: z.any().optional(),
}) satisfies z.ZodType<
  Omit<CreateBacnetReader, 'organizationId' | 'siteId' | 'iotDeviceId'>
>
