import 'server-only'

import { eq } from 'drizzle-orm'
import { getDatabase } from '../client'
import { sites, type Site, type InsertSite } from '../schema'
import { randomUUID } from 'crypto'

export class SitesRepository {
  private get db() {
    return getDatabase()
  }

  async listByOrganization(
    organizationId: string,
    options?: { page?: number; limit?: number }
  ): Promise<Site[]> {
    const page = options?.page ?? 1
    const limit = options?.limit ?? 100
    const offset = (page - 1) * limit

    const results = await this.db
      .select()
      .from(sites)
      .where(eq(sites.organization_id, organizationId))
      .limit(limit)
      .offset(offset)
      .all()

    return results.map((result) => ({
      ...result,
      description: result.description ?? undefined,
    }))
  }

  async findByOrgId(organizationId: string): Promise<Site | null> {
    const result = await this.db
      .select()
      .from(sites)
      .where(eq(sites.organization_id, organizationId))
      .limit(1)
      .get()

    return result
      ? {
          ...result,
          description: result.description ?? undefined,
        }
      : null
  }

  async findById(id: string): Promise<Site | null> {
    const result = await this.db
      .select()
      .from(sites)
      .where(eq(sites.id, id))
      .get()

    return result
      ? {
          ...result,
          description: result.description ?? undefined,
        }
      : null
  }

  async create(data: {
    organization_id: string
    name: string
    description?: string
  }): Promise<Site> {
    const id = randomUUID()
    const now = new Date().toISOString()

    const newSite: InsertSite = {
      id,
      organization_id: data.organization_id,
      name: data.name,
      description: data.description ?? undefined,
      created_at: now,
      updated_at: now,
    }

    await this.db.insert(sites).values(newSite).run()

    const result = await this.db
      .select()
      .from(sites)
      .where(eq(sites.id, id))
      .get()

    return {
      ...result!,
      description: result!.description ?? undefined,
    }
  }
}

export const sitesRepository = new SitesRepository()
