import 'server-only'

import { eq, and } from 'drizzle-orm'
import { getDatabase } from '../client'
import {
  bacnetReaders,
  type BacnetReader,
  type InsertBacnetReader,
} from '../schema'
import { randomUUID } from 'crypto'

export class BacnetReadersRepository {
  private get db() {
    return getDatabase()
  }

  async findByDevice(
    orgId: string,
    siteId: string,
    iotDeviceId: string,
    includeDeleted = false
  ): Promise<BacnetReader[]> {
    const conditions = [
      eq(bacnetReaders.organization_id, orgId),
      eq(bacnetReaders.site_id, siteId),
      eq(bacnetReaders.iot_device_id, iotDeviceId),
    ]

    if (!includeDeleted) {
      conditions.push(eq(bacnetReaders.is_deleted, false))
    }

    const results = await this.db
      .select()
      .from(bacnetReaders)
      .where(and(...conditions))
      .all()

    return results.map((r) => ({
      ...r,
      description: r.description ?? undefined,
      bbmd_server_ip: r.bbmd_server_ip ?? undefined,
      metadata:
        typeof r.metadata === 'string' ? JSON.parse(r.metadata) : r.metadata,
    })) as BacnetReader[]
  }

  async findById(id: string): Promise<BacnetReader | null> {
    const result = await this.db
      .select()
      .from(bacnetReaders)
      .where(eq(bacnetReaders.id, id))
      .get()

    return result
      ? ({
          ...result,
          description: result.description ?? undefined,
          bbmd_server_ip: result.bbmd_server_ip ?? undefined,
          metadata:
            typeof result.metadata === 'string'
              ? JSON.parse(result.metadata)
              : result.metadata,
        } as BacnetReader)
      : null
  }

  async create(data: InsertBacnetReader): Promise<BacnetReader> {
    const id = randomUUID()
    const now = new Date().toISOString()

    const newReader = {
      ...data,
      id,
      description: data.description ?? undefined,
      bbmd_server_ip: data.bbmd_server_ip ?? undefined,
      created_at: now,
      updated_at: now,
    } as BacnetReader

    await this.db.insert(bacnetReaders).values(newReader).run()

    const result = await this.db
      .select()
      .from(bacnetReaders)
      .where(eq(bacnetReaders.id, id))
      .get()

    return {
      ...result!,
      description: result!.description ?? undefined,
      bbmd_server_ip: result!.bbmd_server_ip ?? undefined,
      metadata:
        typeof result!.metadata === 'string'
          ? JSON.parse(result!.metadata)
          : result!.metadata,
    } as BacnetReader
  }

  async update(
    id: string,
    data: Partial<InsertBacnetReader>
  ): Promise<BacnetReader | null> {
    const existing = await this.findById(id)
    if (!existing) return null

    const updateData: Record<string, unknown> = {
      ...data,
      description:
        data.description !== undefined ? data.description : undefined,
      bbmd_server_ip:
        data.bbmd_server_ip !== undefined ? data.bbmd_server_ip : undefined,
      updated_at: new Date().toISOString(),
    } as BacnetReader

    await this.db
      .update(bacnetReaders)
      .set(updateData)
      .where(eq(bacnetReaders.id, id))
      .run()

    return this.findById(id)
  }

  async delete(id: string): Promise<boolean> {
    const existed = await this.findById(id)
    if (!existed) return false

    await this.db.delete(bacnetReaders).where(eq(bacnetReaders.id, id)).run()
    return true
  }

  async verifyOwnership({
    id,
    orgId,
    siteId,
    iotDeviceId,
  }: {
    id: string
    orgId: string
    siteId: string
    iotDeviceId: string
  }): Promise<boolean> {
    const resource = await this.db
      .select()
      .from(bacnetReaders)
      .where(eq(bacnetReaders.id, id))
      .get()

    if (!resource) {
      return false
    }

    return (
      resource.organization_id === orgId &&
      resource.site_id === siteId &&
      resource.iot_device_id === iotDeviceId
    )
  }
}

export const bacnetReadersRepository = new BacnetReadersRepository()
