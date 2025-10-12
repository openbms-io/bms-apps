import { sql } from 'drizzle-orm'
import { text, integer, sqliteTable, index } from 'drizzle-orm/sqlite-core'
import { organizations } from './organizations'
import { sites } from './sites'
import { iotDevices } from './iot-devices'
import type { BacnetMetadata } from '@/types/bacnet-metadata'

export const bacnetReaders = sqliteTable(
  'bacnet_readers',
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

    // BACnet configuration
    ip_address: text('ip_address').notNull(),
    port: integer('port').notNull().default(47808),
    device_id: integer('device_id').notNull(),
    subnet_mask: integer('subnet_mask').notNull().default(24),
    bbmd_enabled: integer('bbmd_enabled', { mode: 'boolean' })
      .notNull()
      .default(false),
    bbmd_server_ip: text('bbmd_server_ip'),

    // Metadata
    name: text('name').notNull(),
    description: text('description'),
    is_active: integer('is_active', { mode: 'boolean' })
      .notNull()
      .default(true),
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
    index('idx_bacnet_readers_org_site_device').on(
      table.organization_id,
      table.site_id,
      table.iot_device_id
    ),
    index('idx_bacnet_readers_device').on(table.iot_device_id),
    index('idx_bacnet_readers_deleted').on(table.is_deleted),
  ]
)

export type BacnetReader = typeof bacnetReaders.$inferSelect
export type InsertBacnetReader = typeof bacnetReaders.$inferInsert
