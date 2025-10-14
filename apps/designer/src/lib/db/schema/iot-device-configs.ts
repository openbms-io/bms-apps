import { sql } from 'drizzle-orm'
import { text, integer, sqliteTable, index } from 'drizzle-orm/sqlite-core'
import { organizations } from './organizations'
import { sites } from './sites'
import { iotDevices } from './iot-devices'
import { projects } from './projects'
import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'

export const iotDeviceConfigs = sqliteTable(
  'iot_device_configs',
  {
    id: text('id').primaryKey(),
    project_id: text('project_id')
      .notNull()
      .references(() => projects.id, { onDelete: 'cascade' }),
    organization_id: text('organization_id')
      .notNull()
      .references(() => organizations.id, { onDelete: 'cascade' }),
    site_id: text('site_id')
      .notNull()
      .references(() => sites.id, { onDelete: 'cascade' }),
    iot_device_id: text('iot_device_id')
      .notNull()
      .references(() => iotDevices.id, { onDelete: 'cascade' }),

    // Configuration data
    config_data: text('config_data', { mode: 'json' })
      .$type<ValidatedWorkflowConfig>()
      .notNull(),
    version: integer('version').notNull().default(1),
    is_active: integer('is_active', { mode: 'boolean' })
      .notNull()
      .default(true),

    // Timestamps
    created_at: text('created_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
    updated_at: text('updated_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
  },
  (table) => [
    index('idx_configs_device').on(table.iot_device_id),
    index('idx_configs_org_site_device').on(
      table.organization_id,
      table.site_id,
      table.iot_device_id
    ),
  ]
)

export type IotDeviceConfig = typeof iotDeviceConfigs.$inferSelect
export type InsertIotDeviceConfig = typeof iotDeviceConfigs.$inferInsert
