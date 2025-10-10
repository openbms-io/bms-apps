import { z } from 'zod'
import type {
  IotDevice,
  CreateIotDevice,
  UpdateIotDevice,
} from '@/lib/domain/models/iot-device'

export type { IotDevice, CreateIotDevice, UpdateIotDevice }

export const ProjectRouteParamsSchema = z.object({
  orgId: z.string(),
  siteId: z.string(),
  projectId: z.string(),
})

export const IotDeviceRouteParamsSchema = ProjectRouteParamsSchema.extend({
  id: z.string(),
})

export const CreateIotDeviceRequestSchema = z.object({
  organizationId: z.string().uuid('Invalid organization ID format'),
  siteId: z.string().uuid('Invalid site ID format'),
  name: z
    .string()
    .min(1, 'IoT device name is required')
    .max(255, 'IoT device name too long'),
  description: z.string().optional(),
})

export const UpdateIotDeviceRequestSchema = z.object({
  name: z
    .string()
    .min(1, 'IoT device name is required')
    .max(255, 'IoT device name too long')
    .optional(),
  description: z.string().nullable().optional(),
})

export const CreateIotDeviceSchema = z.object({
  name: z.string().min(1, 'Name is required'),
  description: z.string().optional(),
})

export type ProjectRouteParams = z.infer<typeof ProjectRouteParamsSchema>
export type IotDeviceRouteParams = z.infer<typeof IotDeviceRouteParamsSchema>
export type CreateIotDeviceInput = z.infer<typeof CreateIotDeviceSchema>
