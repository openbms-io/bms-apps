import 'server-only'

import { eq, and } from 'drizzle-orm'
import { getDatabase } from '../client'
import {
  iotDeviceControllers,
  controllerPoints,
  type IotDeviceController,
  type InsertIotDeviceController,
} from '../schema'
import { randomUUID } from 'crypto'

export class IotDeviceControllersRepository {
  private get db() {
    return getDatabase()
  }

  async findByDevice(
    orgId: string,
    siteId: string,
    iotDeviceId: string,
    includeDeleted = false
  ): Promise<IotDeviceController[]> {
    const conditions = [
      eq(iotDeviceControllers.organization_id, orgId),
      eq(iotDeviceControllers.site_id, siteId),
      eq(iotDeviceControllers.iot_device_id, iotDeviceId),
    ]

    if (!includeDeleted) {
      conditions.push(eq(iotDeviceControllers.is_deleted, false))
    }

    const results = await this.db
      .select()
      .from(iotDeviceControllers)
      .where(and(...conditions))
      .all()

    return results.map((r) => ({
      ...r,
      description: r.description ?? undefined,
      metadata:
        typeof r.metadata === 'string' ? JSON.parse(r.metadata) : r.metadata,
    })) as IotDeviceController[]
  }

  async findById(id: string): Promise<IotDeviceController | null> {
    const result = await this.db
      .select()
      .from(iotDeviceControllers)
      .where(eq(iotDeviceControllers.id, id))
      .get()

    return result
      ? ({
          ...result,
          description: result.description ?? undefined,
          metadata:
            typeof result.metadata === 'string'
              ? JSON.parse(result.metadata)
              : result.metadata,
        } as IotDeviceController)
      : null
  }

  async create(data: InsertIotDeviceController): Promise<IotDeviceController> {
    const id = randomUUID()
    const now = new Date().toISOString()

    const newController = {
      ...data,
      id,
      description: data.description ?? undefined,
      created_at: now,
      updated_at: now,
    }

    await this.db.insert(iotDeviceControllers).values(newController).run()

    const result = await this.db
      .select()
      .from(iotDeviceControllers)
      .where(eq(iotDeviceControllers.id, id))
      .get()

    return {
      ...result!,
      description: result!.description ?? undefined,
      metadata:
        typeof result!.metadata === 'string'
          ? JSON.parse(result!.metadata)
          : result!.metadata,
    } as IotDeviceController
  }

  async update(
    id: string,
    data: Partial<InsertIotDeviceController>
  ): Promise<IotDeviceController | null> {
    const existing = await this.findById(id)
    if (!existing) return null

    const updateData: Record<string, unknown> = {
      ...data,
      id,
      description:
        data.description !== undefined ? data.description : undefined,
      updated_at: new Date().toISOString(),
    }

    await this.db
      .update(iotDeviceControllers)
      .set(updateData)
      .where(eq(iotDeviceControllers.id, id))
      .run()

    return this.findById(id)
  }

  async delete(id: string): Promise<boolean> {
    const existed = await this.findById(id)
    if (!existed) return false
    if (existed.is_deleted) return false

    const now = new Date().toISOString()

    // Soft delete the controller
    await this.db
      .update(iotDeviceControllers)
      .set({ is_deleted: true, updated_at: now })
      .where(eq(iotDeviceControllers.id, id))
      .run()

    // Cascade soft delete to all controller points
    await this.db
      .update(controllerPoints)
      .set({ is_deleted: true, updated_at: now })
      .where(eq(controllerPoints.controller_id, id))
      .run()

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
      .from(iotDeviceControllers)
      .where(eq(iotDeviceControllers.id, id))
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

export const iotDeviceControllersRepository =
  new IotDeviceControllersRepository()
