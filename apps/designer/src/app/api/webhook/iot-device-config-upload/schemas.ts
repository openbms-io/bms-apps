import { z } from 'zod'

export const BacnetObjectPropertiesSchema = z
  .object({
    objectIdentifier: z.array(z.any()).optional(),
    objectName: z.string().optional(),
    presentValue: z.union([z.number(), z.string()]).optional(),
    objectType: z.string().optional(),
    description: z.string().optional(),
    statusFlags: z.string().optional(),
    units: z.string().optional(),
  })
  .passthrough() // Allow additional properties

export const BacnetObjectSchema = z.object({
  type: z.string(),
  point_id: z.number(),
  iot_device_point_id: z.string(),
  properties: BacnetObjectPropertiesSchema,
})

export const ConfigItemSchema = z.object({
  vendor_id: z.number(),
  device_id: z.number(),
  controller_id: z.string(),
  controller_ip_address: z.string(),
  object_list: z.array(BacnetObjectSchema),
})

export const ConfigUploadSchema = z.object({
  config: z.array(ConfigItemSchema),
})

export type ConfigUpload = z.infer<typeof ConfigUploadSchema>
export type ConfigItem = z.infer<typeof ConfigItemSchema>
export type BacnetObject = z.infer<typeof BacnetObjectSchema>
