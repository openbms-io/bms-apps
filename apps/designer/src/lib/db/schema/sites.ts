import { sql } from 'drizzle-orm'
import { text, sqliteTable, index } from 'drizzle-orm/sqlite-core'
import { organizations } from './organizations'

export const sites = sqliteTable(
  'sites',
  {
    id: text('id').primaryKey(),
    organization_id: text('organization_id')
      .notNull()
      .references(() => organizations.id, { onDelete: 'cascade' }),
    name: text('name').notNull(),
    description: text('description'),
    created_at: text('created_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
    updated_at: text('updated_at')
      .notNull()
      .default(sql`(strftime('%Y-%m-%dT%H:%M:%fZ', 'now'))`),
  },
  (table) => [index('idx_sites_organization_id').on(table.organization_id)]
)

type DrizzleSite = typeof sites.$inferSelect
type DrizzleNewSite = typeof sites.$inferInsert

export type Site = Omit<DrizzleSite, 'description'> & {
  description?: string | undefined
}

export type InsertSite = Omit<DrizzleNewSite, 'description'> & {
  description?: string | undefined
}
