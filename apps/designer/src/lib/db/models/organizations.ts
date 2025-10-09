import 'server-only'

import { eq } from 'drizzle-orm'
import { getDatabase } from '../client'
import {
  organizations,
  type Organization,
  type InsertOrganization,
} from '../schema'
import { randomUUID } from 'crypto'

export class OrganizationsRepository {
  private get db() {
    return getDatabase()
  }

  async list(options?: {
    page?: number
    limit?: number
  }): Promise<Organization[]> {
    const page = options?.page ?? 1
    const limit = options?.limit ?? 100
    const offset = (page - 1) * limit

    const results = await this.db
      .select()
      .from(organizations)
      .limit(limit)
      .offset(offset)
      .all()

    return results
  }

  async findFirst(): Promise<Organization | null> {
    const result = await this.db.select().from(organizations).limit(1).get()

    return result ?? null
  }

  async findById(id: string): Promise<Organization | null> {
    const result = await this.db
      .select()
      .from(organizations)
      .where(eq(organizations.id, id))
      .get()

    return result ?? null
  }

  async create(name: string): Promise<Organization> {
    const id = `org_${randomUUID()}` // The clerk id uses org_ prefix. To keep it consistent, we use the same prefix.
    const now = new Date().toISOString()

    const newOrg: InsertOrganization = {
      id,
      name,
      created_at: now,
      updated_at: now,
    }

    await this.db.insert(organizations).values(newOrg).run()

    const result = await this.db
      .select()
      .from(organizations)
      .where(eq(organizations.id, id))
      .get()

    return result!
  }
}

export const organizationsRepository = new OrganizationsRepository()
