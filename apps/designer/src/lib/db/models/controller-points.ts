import 'server-only'

import { eq, and, notInArray } from 'drizzle-orm'
import { getDatabase } from '../client'
import {
  controllerPoints,
  type ControllerPoint,
  type InsertControllerPoint,
} from '../schema'
import { randomUUID } from 'crypto'

export class ControllerPointsRepository {
  private get db() {
    return getDatabase()
  }

  async findByController(
    controllerId: string,
    includeDeleted = false
  ): Promise<ControllerPoint[]> {
    const conditions = [eq(controllerPoints.controller_id, controllerId)]

    if (!includeDeleted) {
      conditions.push(eq(controllerPoints.is_deleted, false))
    }

    const results = await this.db
      .select()
      .from(controllerPoints)
      .where(and(...conditions))
      .all()

    return results.map((r) => ({
      ...r,
      units: r.units ?? undefined,
      description: r.description ?? undefined,
      metadata:
        typeof r.metadata === 'string' ? JSON.parse(r.metadata) : r.metadata,
    })) as ControllerPoint[]
  }

  async findByDevice(
    orgId: string,
    siteId: string,
    iotDeviceId: string
  ): Promise<ControllerPoint[]> {
    const results = await this.db
      .select()
      .from(controllerPoints)
      .where(
        and(
          eq(controllerPoints.organization_id, orgId),
          eq(controllerPoints.site_id, siteId),
          eq(controllerPoints.iot_device_id, iotDeviceId)
        )
      )
      .all()

    return results.map((r) => ({
      ...r,
      units: r.units ?? undefined,
      description: r.description ?? undefined,
      metadata:
        typeof r.metadata === 'string' ? JSON.parse(r.metadata) : r.metadata,
    })) as ControllerPoint[]
  }

  async findById(id: string): Promise<ControllerPoint | null> {
    const result = await this.db
      .select()
      .from(controllerPoints)
      .where(eq(controllerPoints.id, id))
      .get()

    return result
      ? ({
          ...result,
          units: result.units ?? undefined,
          description: result.description ?? undefined,
          metadata:
            typeof result.metadata === 'string'
              ? JSON.parse(result.metadata)
              : result.metadata,
        } as ControllerPoint)
      : null
  }

  async create(data: InsertControllerPoint): Promise<ControllerPoint> {
    const id = randomUUID()
    const now = new Date().toISOString()

    const newPoint = {
      ...data,
      id,
      units: data.units ?? undefined,
      description: data.description ?? undefined,
      created_at: now,
      updated_at: now,
    }

    await this.db.insert(controllerPoints).values(newPoint).run()

    const result = await this.db
      .select()
      .from(controllerPoints)
      .where(eq(controllerPoints.id, id))
      .get()

    return {
      ...result!,
      units: result!.units ?? undefined,
      description: result!.description ?? undefined,
      metadata:
        typeof result!.metadata === 'string'
          ? JSON.parse(result!.metadata)
          : result!.metadata,
    } as ControllerPoint
  }

  async update(
    id: string,
    data: Partial<InsertControllerPoint>
  ): Promise<ControllerPoint | null> {
    const existing = await this.findById(id)
    if (!existing) return null

    const updateData: Record<string, unknown> = {
      ...data,
      units: data.units !== undefined ? data.units : undefined,
      description:
        data.description !== undefined ? data.description : undefined,
      updated_at: new Date().toISOString(),
    }

    await this.db
      .update(controllerPoints)
      .set(updateData)
      .where(eq(controllerPoints.id, id))
      .run()

    return this.findById(id)
  }

  async delete(id: string): Promise<boolean> {
    const existed = await this.findById(id)
    if (!existed) return false

    await this.db
      .delete(controllerPoints)
      .where(eq(controllerPoints.id, id))
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
      .from(controllerPoints)
      .where(eq(controllerPoints.id, id))
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

  async softDeleteNotInList(
    controllerId: string,
    pointIds: string[]
  ): Promise<void> {
    const conditions = [eq(controllerPoints.controller_id, controllerId)]

    if (pointIds.length > 0) {
      conditions.push(notInArray(controllerPoints.id, pointIds))
    }

    await this.db
      .update(controllerPoints)
      .set({
        is_deleted: true,
        updated_at: new Date().toISOString(),
      })
      .where(and(...conditions))
      .run()
  }

  async upsert(
    data: InsertControllerPoint & { id: string }
  ): Promise<ControllerPoint> {
    const now = new Date().toISOString()

    const upsertData = {
      ...data,
      is_deleted: false,
      updated_at: now,
      created_at: now,
    }

    await this.db
      .insert(controllerPoints)
      .values(upsertData)
      .onConflictDoUpdate({
        target: controllerPoints.id,
        set: {
          point_name: upsertData.point_name,
          point_type: upsertData.point_type,
          object_identifier: upsertData.object_identifier,
          instance_number: upsertData.instance_number,
          writable: upsertData.writable ?? false,
          units: upsertData.units,
          description: upsertData.description,
          metadata: upsertData.metadata ?? null,
          is_deleted: false,
          updated_at: now,
        },
      })
      .run()

    const result = await this.findById(data.id)
    return result!
  }
}

export const controllerPointsRepository = new ControllerPointsRepository()
