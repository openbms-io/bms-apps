/** @jest-environment node */

import { randomUUID } from 'crypto'

import { getDatabase, closeDatabase } from './client'
import { projects, sites, organizations } from './schema'
import { eq } from 'drizzle-orm'

describe('Database Client (SQLite + Drizzle)', () => {
  afterAll(() => {
    // Ensure DB connection is closed and file handles released
    closeDatabase()
  })

  it('loads .env.test and uses test database path', () => {
    expect(process.env.NODE_ENV).toBe('test')
    expect(process.env.DATABASE_PATH).toBe('designer-test.db')
  })

  it('initializes database and runs migrations (projects table exists)', async () => {
    const db = getDatabase()

    // Selecting from the projects table should not throw if migrations ran
    const rows = await db.select().from(projects).limit(1).all()
    expect(Array.isArray(rows)).toBe(true)
  })

  it('projects table can be queried (no seed assumption)', async () => {
    const db = getDatabase()

    const all = await db.select().from(projects).all()
    expect(Array.isArray(all)).toBe(true)
    // If any rows exist, basic shape sanity
    for (const p of all) {
      expect(typeof p.id).toBe('string')
      expect(typeof p.name).toBe('string')
    }
  })

  it('supports insert and readback for projects', async () => {
    const db = getDatabase()

    const org_id = randomUUID()
    const site_id = randomUUID()
    const id = randomUUID()
    const name = 'Test Project'
    const now = new Date().toISOString()

    // Set up required hierarchy
    await db
      .insert(organizations)
      .values({
        id: org_id,
        name: 'Test Org',
        created_at: now,
        updated_at: now,
      })
      .run()

    await db
      .insert(sites)
      .values({
        id: site_id,
        organization_id: org_id,
        name: 'Test Site',
        description: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    // Insert minimal row (defaults for created_at/updated_at, workflow_config is null)
    await db.insert(projects).values({ id, name, site_id }).run()

    const fetched = await db
      .select()
      .from(projects)
      .where(eq(projects.id, id))
      .get()

    expect(fetched).toBeTruthy()
    expect(fetched?.id).toBe(id)
    expect(fetched?.name).toBe(name)
    // Defaults are applied for timestamps
    expect(typeof fetched?.created_at).toBe('string')
    expect(typeof fetched?.updated_at).toBe('string')
    // workflow_config is null when not provided
    expect(fetched?.workflow_config).toBeNull()
  })
})
