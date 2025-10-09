import { sql } from 'drizzle-orm'
import { text, sqliteTable, index } from 'drizzle-orm/sqlite-core'
import { organizations } from './organizations'
import { sites } from './sites'

export const iotDevices = sqliteTable(
  'iot_devices',
  {
    id: text('id').primaryKey(),
    organization_id: text('organization_id')
      .notNull()
      .references(() => organizations.id, { onDelete: 'cascade' }),
    site_id: text('site_id')
      .notNull()
      .references(() => sites.id, { onDelete: 'cascade' }),
    name: text('name').notNull(),
    description: text('description'),
    created_at: text('created_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
    updated_at: text('updated_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
  },
  (table) => [
    index('idx_iot_devices_org_site').on(table.organization_id, table.site_id),
    index('idx_iot_devices_site').on(table.site_id),
  ]
)

export type IotDevice = typeof iotDevices.$inferSelect
export type InsertIotDevice = typeof iotDevices.$inferInsert
