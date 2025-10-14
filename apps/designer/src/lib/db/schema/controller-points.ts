import { sql } from 'drizzle-orm'
import { text, integer, sqliteTable, index } from 'drizzle-orm/sqlite-core'
import { organizations } from './organizations'
import { sites } from './sites'
import { iotDevices } from './iot-devices'
import { iotDeviceControllers } from './iot-device-controllers'
import type { BacnetMetadata } from '@/types/bacnet-metadata'

export const controllerPoints = sqliteTable(
  'controller_points',
  {
    id: text('id').primaryKey(),
    organization_id: text('organization_id')
      .notNull()
      .references(() => organizations.id, { onDelete: 'cascade' }),
    site_id: text('site_id')
      .notNull()
      .references(() => sites.id, { onDelete: 'cascade' }),
    iot_device_id: text('iot_device_id')
      .notNull()
      .references(() => iotDevices.id, { onDelete: 'cascade' }),
    controller_id: text('controller_id')
      .notNull()
      .references(() => iotDeviceControllers.id, { onDelete: 'cascade' }),

    // BACnet point configuration
    point_name: text('point_name'),
    point_type: text('point_type').notNull(), // e.g., 'analog-input', 'binary-output' (kebab-case)
    object_identifier: text('object_identifier'),
    instance_number: integer('instance_number').notNull(),

    // Properties
    writable: integer('writable', { mode: 'boolean' }).notNull().default(false),
    units: text('units'),
    description: text('description'),

    // Metadata for additional BACnet properties
    metadata: text('metadata', { mode: 'json' }).$type<BacnetMetadata>(),

    // Soft delete
    is_deleted: integer('is_deleted', { mode: 'boolean' })
      .notNull()
      .default(false),

    // Timestamps
    created_at: text('created_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
    updated_at: text('updated_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
  },
  (table) => [
    index('idx_points_controller').on(table.controller_id),
    index('idx_points_org_site_device').on(
      table.organization_id,
      table.site_id,
      table.iot_device_id
    ),
    index('idx_points_deleted').on(table.is_deleted),
  ]
)

export type ControllerPoint = typeof controllerPoints.$inferSelect
export type InsertControllerPoint = typeof controllerPoints.$inferInsert
