import { sql } from 'drizzle-orm'
import { text, sqliteTable, index } from 'drizzle-orm/sqlite-core'
import { sites } from './sites'
import { iotDevices } from './iot-devices'

export const projects = sqliteTable(
  'projects',
  {
    id: text('id').primaryKey(),
    site_id: text('site_id')
      .notNull()
      .references(() => sites.id, { onDelete: 'cascade' }),
    iot_device_id: text('iot_device_id').references(() => iotDevices.id, {
      onDelete: 'set null',
    }),
    name: text('name').notNull(),
    description: text('description'),
    workflow_config: text('workflow_config'),
    created_at: text('created_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
    updated_at: text('updated_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
  },
  (table) => [
    index('idx_projects_site_id').on(table.site_id),
    index('idx_projects_iot_device_id').on(table.iot_device_id),
    index('idx_projects_created_at').on(table.created_at),
    index('idx_projects_updated_at').on(table.updated_at),
  ]
)

// Export database types (explicitly prefixed with Db)
export type DbProject = typeof projects.$inferSelect
export type DbInsertProject = typeof projects.$inferInsert
export type DbUpdateProject = Partial<DbInsertProject>
