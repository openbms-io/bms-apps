import 'server-only'

import { eq, and, desc } from 'drizzle-orm'
import { getDatabase } from '../client'
import {
  iotDeviceConfigs,
  type IotDeviceConfig,
  type InsertIotDeviceConfig,
} from '../schema'
import { randomUUID } from 'crypto'

export class IotDeviceConfigsRepository {
  private get db() {
    return getDatabase()
  }

  async findByDevice(
    orgId: string,
    siteId: string,
    iotDeviceId: string
  ): Promise<IotDeviceConfig[]> {
    return await this.db
      .select()
      .from(iotDeviceConfigs)
      .where(
        and(
          eq(iotDeviceConfigs.organization_id, orgId),
          eq(iotDeviceConfigs.site_id, siteId),
          eq(iotDeviceConfigs.iot_device_id, iotDeviceId)
        )
      )
      .orderBy(desc(iotDeviceConfigs.created_at))
      .all()
  }

  async findLatestByDevice(
    orgId: string,
    siteId: string,
    iotDeviceId: string
  ): Promise<IotDeviceConfig | null> {
    const result = await this.db
      .select()
      .from(iotDeviceConfigs)
      .where(
        and(
          eq(iotDeviceConfigs.organization_id, orgId),
          eq(iotDeviceConfigs.site_id, siteId),
          eq(iotDeviceConfigs.iot_device_id, iotDeviceId),
          eq(iotDeviceConfigs.is_active, true)
        )
      )
      .orderBy(desc(iotDeviceConfigs.created_at))
      .limit(1)
      .get()

    return result || null
  }

  async findById(id: string): Promise<IotDeviceConfig | null> {
    const result = await this.db
      .select()
      .from(iotDeviceConfigs)
      .where(eq(iotDeviceConfigs.id, id))
      .get()

    return result || null
  }

  async create(data: InsertIotDeviceConfig): Promise<IotDeviceConfig> {
    const id = randomUUID()
    const now = new Date().toISOString()

    const newConfig = {
      ...data,
      id,
      created_at: now,
      updated_at: now,
    }

    await this.db.insert(iotDeviceConfigs).values(newConfig).run()

    const result = await this.db
      .select()
      .from(iotDeviceConfigs)
      .where(eq(iotDeviceConfigs.id, id))
      .get()

    return result!
  }

  async update(
    id: string,
    data: Partial<InsertIotDeviceConfig>
  ): Promise<IotDeviceConfig | null> {
    const existing = await this.findById(id)
    if (!existing) return null

    const updateData: Record<string, unknown> = {
      ...data,
      updated_at: new Date().toISOString(),
    }

    await this.db
      .update(iotDeviceConfigs)
      .set(updateData)
      .where(eq(iotDeviceConfigs.id, id))
      .run()

    return this.findById(id)
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
      .from(iotDeviceConfigs)
      .where(eq(iotDeviceConfigs.id, id))
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

export const iotDeviceConfigsRepository = new IotDeviceConfigsRepository()
