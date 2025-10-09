import 'server-only'

import { eq, and } from 'drizzle-orm'
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

  async findByController(controllerId: string): Promise<ControllerPoint[]> {
    const results = await this.db
      .select()
      .from(controllerPoints)
      .where(eq(controllerPoints.controller_id, controllerId))
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
}

export const controllerPointsRepository = new ControllerPointsRepository()
