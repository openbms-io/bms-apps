/**
 * @jest-environment node
 */

import { GET } from './route'
import { getDatabase, closeDatabase } from '@/lib/db/client'
import {
  organizations,
  sites,
  iotDevices,
  iotDeviceControllers,
  controllerPoints,
} from '@/lib/db/schema'

describe('GET /api/.../controllers/[controllerId]/points', () => {
  const testOrgId = 'org_test-points-123'
  const testSiteId = '00000000-0000-0000-0000-000000000001'
  const testProjectId = '00000000-0000-0000-0000-000000000002'
  const testIotDeviceId = '00000000-0000-0000-0000-000000000003'
  const testControllerId = '00000000-0000-0000-0000-000000000004'

  beforeEach(async () => {
    const db = getDatabase()
    const now = new Date().toISOString()

    // Clean up
    await db.delete(controllerPoints).run()
    await db.delete(iotDeviceControllers).run()
    await db.delete(iotDevices).run()
    await db.delete(sites).run()
    await db.delete(organizations).run()

    // Setup test data
    await db
      .insert(organizations)
      .values({
        id: testOrgId,
        name: 'Test Org',
        created_at: now,
        updated_at: now,
      })
      .run()

    await db
      .insert(sites)
      .values({
        id: testSiteId,
        organization_id: testOrgId,
        name: 'Test Site',
        description: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    await db
      .insert(iotDevices)
      .values({
        id: testIotDeviceId,
        organization_id: testOrgId,
        site_id: testSiteId,
        name: 'Test IoT Device',
        description: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    await db
      .insert(iotDeviceControllers)
      .values({
        id: testControllerId,
        organization_id: testOrgId,
        site_id: testSiteId,
        iot_device_id: testIotDeviceId,
        ip_address: '192.168.1.100',
        port: 47808,
        device_id: 1001,
        name: 'Test Controller',
        description: null,
        is_active: true,
        metadata: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    // Insert test points
    await db
      .insert(controllerPoints)
      .values([
        {
          id: '00000000-0000-0000-0000-000000000010',
          organization_id: testOrgId,
          site_id: testSiteId,
          iot_device_id: testIotDeviceId,
          controller_id: testControllerId,
          point_name: 'Temperature Sensor',
          point_type: 'analogInput',
          object_identifier: '["analog-input",0]',
          instance_number: 0,
          writable: false,
          units: 'degreesFahrenheit',
          description: 'Room temperature',
          metadata: null,
          is_deleted: false,
          created_at: now,
          updated_at: now,
        },
        {
          id: '00000000-0000-0000-0000-000000000011',
          organization_id: testOrgId,
          site_id: testSiteId,
          iot_device_id: testIotDeviceId,
          controller_id: testControllerId,
          point_name: 'Humidity Sensor',
          point_type: 'analogInput',
          object_identifier: '["analog-input",1]',
          instance_number: 1,
          writable: false,
          units: 'percent',
          description: null,
          metadata: null,
          is_deleted: false,
          created_at: now,
          updated_at: now,
        },
        {
          id: '00000000-0000-0000-0000-000000000012',
          organization_id: testOrgId,
          site_id: testSiteId,
          iot_device_id: testIotDeviceId,
          controller_id: testControllerId,
          point_name: 'Deleted Point',
          point_type: 'analogInput',
          object_identifier: '["analog-input",2]',
          instance_number: 2,
          writable: false,
          units: null,
          description: null,
          metadata: null,
          is_deleted: true, // Soft deleted
          created_at: now,
          updated_at: now,
        },
      ])
      .run()
  })

  afterAll(() => {
    closeDatabase()
  })

  const mockParams = Promise.resolve({
    orgId: testOrgId,
    siteId: testSiteId,
    projectId: testProjectId,
    iotDeviceId: testIotDeviceId,
    controllerId: testControllerId,
  })

  it('should return points for controller', async () => {
    const request = {} as any
    const response = await GET(request, { params: mockParams })

    expect(response.status).toBe(200)
    const json = await response.json()

    expect(json.success).toBe(true)
    expect(json.data.points).toHaveLength(2) // Excludes soft-deleted
    expect(json.data.points[0].pointName).toBe('Temperature Sensor')
    expect(json.data.points[0].units).toBe('degreesFahrenheit')
    expect(json.data.points[1].pointName).toBe('Humidity Sensor')
  })

  it('should return empty array when controller has no points', async () => {
    const db = getDatabase()
    await db.delete(controllerPoints).run()

    const request = {} as any
    const response = await GET(request, { params: mockParams })

    const json = await response.json()
    expect(json.data.points).toEqual([])
  })

  it('should return 404 when controller does not exist', async () => {
    const invalidParams = Promise.resolve({
      orgId: testOrgId,
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
      controllerId: '99999999-9999-9999-9999-999999999999', // Valid UUID but not in DB
    })

    const request = {} as any
    const response = await GET(request, { params: invalidParams })

    expect(response.status).toBe(404)
    const json = await response.json()
    expect(json.error).toBe('Controller not found')
  })

  it('should return 403 when controller belongs to different org', async () => {
    const wrongOrgParams = Promise.resolve({
      orgId: 'org_different-org-456', // Valid org_ prefix but different org
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
      controllerId: testControllerId,
    })

    const request = {} as any
    const response = await GET(request, { params: wrongOrgParams })

    expect(response.status).toBe(403)
    const json = await response.json()
    expect(json.error).toBe('Forbidden')
  })

  it('should map DB fields to camelCase DTO', async () => {
    const request = {} as any
    const response = await GET(request, { params: mockParams })

    const json = await response.json()
    const point = json.data.points[0]

    // Check camelCase mapping
    expect(point.id).toBeDefined()
    expect(point.organizationId).toBe(testOrgId)
    expect(point.siteId).toBe(testSiteId)
    expect(point.iotDeviceId).toBe(testIotDeviceId)
    expect(point.controllerId).toBe(testControllerId)
    expect(point.pointName).toBeDefined()
    expect(point.pointType).toBeDefined()
    expect(point.objectIdentifier).toBeDefined()
    expect(point.instanceNumber).toBeDefined()
    expect(point.writable).toBeDefined()
    expect(point.createdAt).toBeDefined()
    expect(point.updatedAt).toBeDefined()

    // Check no snake_case leakage
    expect(point.organization_id).toBeUndefined()
    expect(point.point_name).toBeUndefined()
  })
})
