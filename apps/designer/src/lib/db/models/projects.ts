import 'server-only'

import { eq, like, or, and, asc, desc } from 'drizzle-orm'
import { getDatabase } from '../client'
import {
  projects,
  type DbProject,
  type DbInsertProject,
  type DbUpdateProject,
} from '../schema'
import { randomUUID } from 'crypto'
import { iotDevicesRepository } from './iot-devices'
import type { IotDevice } from '../schema'

type ProjectQuery = {
  page?: number
  limit?: number
  search?: string | null
  sort?: 'name' | 'created_at' | 'updated_at' | null
  order?: 'asc' | 'desc' | null
}

type ProjectListResponse = {
  projects: DbProject[]
  total: number
  page: number
  limit: number
  pages: number
}

export class ProjectsRepository {
  private get db() {
    return getDatabase()
  }

  // Create a new project
  async create(
    data: Omit<DbInsertProject, 'id' | 'created_at' | 'updated_at'>
  ): Promise<DbProject> {
    const id = randomUUID()
    const now = new Date().toISOString()

    const newProject = {
      id,
      ...data,
      created_at: now,
      updated_at: now,
    }

    // Insert then fetch by id to keep compatibility across drivers
    await this.db.insert(projects).values(newProject).run()

    const result = await this.db
      .select()
      .from(projects)
      .where(eq(projects.id, id))
      .get()

    return result!
  }

  async findById(id: string): Promise<DbProject | null> {
    const result = await this.db
      .select()
      .from(projects)
      .where(eq(projects.id, id))
      .limit(1)
      .get()

    return result ?? null
  }

  // Update project
  async update(
    id: string,
    data: Partial<DbUpdateProject>
  ): Promise<DbProject | null> {
    const existing = await this.findById(id)
    if (!existing) return null

    const updateData = {
      ...data,
      updated_at: new Date().toISOString(),
    }

    await this.db
      .update(projects)
      .set(updateData)
      .where(eq(projects.id, id))
      .run()

    return this.findById(id)
  }

  // Delete project
  async delete(id: string): Promise<boolean> {
    // Check existence first for consistent behavior
    const existed = await this.exists(id)
    if (!existed) return false

    await this.db.delete(projects).where(eq(projects.id, id)).run()
    return true
  }

  // List projects with pagination and search
  async list({
    siteId,
    page = 1,
    limit = 20,
    search,
    sort = 'updated_at',
    order = 'desc',
  }: { siteId: string } & Partial<ProjectQuery>): Promise<ProjectListResponse> {
    const offset = (page - 1) * limit

    // Build where clause for siteId and search
    const conditions = [eq(projects.site_id, siteId)]

    if (search) {
      conditions.push(
        or(
          like(projects.name, `%${search}%`),
          like(projects.description, `%${search}%`)
        )
      )
    }

    const whereClause = and(...conditions)

    // Build order clause
    const validSorts = ['name', 'created_at', 'updated_at'] as const
    type ValidSort = (typeof validSorts)[number]
    const isValidSort = (s: string | null): s is ValidSort =>
      s !== null && validSorts.includes(s as ValidSort)
    const sortColumn = isValidSort(sort) ? sort : 'updated_at'
    const orderFn = order === 'asc' ? asc : desc
    const orderClause = orderFn(projects[sortColumn])

    // Get total count
    const totalQuery = this.db.select().from(projects).where(whereClause)
    const totalRows = await totalQuery.all()
    const total = totalRows.length

    // Get paginated results
    const projectsList = await this.db
      .select()
      .from(projects)
      .where(whereClause)
      .orderBy(orderClause)
      .limit(limit)
      .offset(offset)
      .all()

    const pages = Math.ceil(total / limit)

    return {
      projects: projectsList,
      total,
      page,
      limit,
      pages,
    }
  }

  // Check if project exists
  async exists(id: string): Promise<boolean> {
    const result = await this.db
      .select()
      .from(projects)
      .where(eq(projects.id, id))
      .get()

    return !!result
  }

  // Get project count
  async count(): Promise<number> {
    const rows = await this.db.select().from(projects).all()
    return rows.length
  }

  // Search projects by name
  async searchByName(name: string): Promise<DbProject[]> {
    return await this.db
      .select()
      .from(projects)
      .where(like(projects.name, `%${name}%`))
      .orderBy(asc(projects.name))
      .all()
  }

  async createIotDeviceForProject({
    projectId,
    orgId,
    siteId,
    name,
    description,
  }: {
    projectId: string
    orgId: string
    siteId: string
    name: string
    description?: string
  }): Promise<IotDevice> {
    const project = await this.findById(projectId)
    if (!project) {
      throw new Error('Project not found')
    }

    if (project.iot_device_id) {
      throw new Error('Project already has an IoT device')
    }

    const iotDevice = await iotDevicesRepository.create({
      id: randomUUID(),
      organization_id: orgId,
      site_id: siteId,
      name,
      description,
    })

    await this.update(projectId, {
      iot_device_id: iotDevice.id,
    })

    return iotDevice
  }
}

// Export singleton instance
export const projectsRepository = new ProjectsRepository()
