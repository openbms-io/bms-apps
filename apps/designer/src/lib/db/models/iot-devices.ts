import 'server-only'

import { eq, and } from 'drizzle-orm'
import { getDatabase } from '../client'
import { iotDevices, type IotDevice, type InsertIotDevice } from '../schema'
import { randomUUID } from 'crypto'

export class IotDevicesRepository {
  private get db() {
    return getDatabase()
  }

  async findById(id: string): Promise<IotDevice | null> {
    const result = await this.db
      .select()
      .from(iotDevices)
      .where(eq(iotDevices.id, id))
      .get()

    return result
      ? {
          ...result,
          description: result.description ?? null,
        }
      : null
  }

  async findBySite(orgId: string, siteId: string): Promise<IotDevice[]> {
    const results = await this.db
      .select()
      .from(iotDevices)
      .where(
        and(
          eq(iotDevices.organization_id, orgId),
          eq(iotDevices.site_id, siteId)
        )
      )
      .all()

    return results.map((r) => ({
      ...r,
      description: r.description ?? null,
    }))
  }

  async create(data: InsertIotDevice): Promise<IotDevice> {
    const id = randomUUID()
    const now = new Date().toISOString()

    const newDevice = {
      ...data,
      id,
      description: data.description ?? null,
      created_at: now,
      updated_at: now,
    }

    await this.db.insert(iotDevices).values(newDevice).run()

    const result = await this.db
      .select()
      .from(iotDevices)
      .where(eq(iotDevices.id, id))
      .get()

    return {
      ...result!,
      description: result!.description ?? null,
    }
  }

  async update(
    id: string,
    data: Partial<InsertIotDevice>
  ): Promise<IotDevice | null> {
    const existing = await this.findById(id)
    if (!existing) return null

    const updateData: Record<string, unknown> = {
      ...data,
      description: data.description ?? null,
      updated_at: new Date().toISOString(),
    }

    await this.db
      .update(iotDevices)
      .set(updateData)
      .where(eq(iotDevices.id, id))
      .run()

    return this.findById(id)
  }

  async delete(id: string): Promise<boolean> {
    const existed = await this.findById(id)
    if (!existed) return false

    await this.db.delete(iotDevices).where(eq(iotDevices.id, id)).run()
    return true
  }
}

export const iotDevicesRepository = new IotDevicesRepository()
