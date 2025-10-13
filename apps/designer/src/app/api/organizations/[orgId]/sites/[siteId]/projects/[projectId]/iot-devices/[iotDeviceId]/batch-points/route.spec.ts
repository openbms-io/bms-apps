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

describe('GET /api/.../controllers/points (batch)', () => {
  const testOrgId = 'org_test-points-batch'
  const testSiteId = '00000000-0000-0000-0000-000000000001'
  const testProjectId = '00000000-0000-0000-0000-000000000002'
  const testIotDeviceId = '00000000-0000-0000-0000-000000000003'
  const testControllerId1 = '00000000-0000-0000-0000-000000000004'
  const testControllerId2 = '00000000-0000-0000-0000-000000000005'

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

    // Controller 1
    await db
      .insert(iotDeviceControllers)
      .values({
        id: testControllerId1,
        organization_id: testOrgId,
        site_id: testSiteId,
        iot_device_id: testIotDeviceId,
        ip_address: '192.168.1.100',
        port: 47808,
        device_id: 1001,
        name: 'Controller 1',
        description: null,
        is_active: true,
        metadata: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    // Controller 2
    await db
      .insert(iotDeviceControllers)
      .values({
        id: testControllerId2,
        organization_id: testOrgId,
        site_id: testSiteId,
        iot_device_id: testIotDeviceId,
        ip_address: '192.168.1.101',
        port: 47808,
        device_id: 1002,
        name: 'Controller 2',
        description: null,
        is_active: true,
        metadata: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    // Points for controller 1
    await db
      .insert(controllerPoints)
      .values([
        {
          id: '00000000-0000-0000-0000-000000000010',
          organization_id: testOrgId,
          site_id: testSiteId,
          iot_device_id: testIotDeviceId,
          controller_id: testControllerId1,
          point_name: 'Temp Sensor 1',
          point_type: 'analogInput',
          object_identifier: '["analog-input",0]',
          instance_number: 0,
          writable: false,
          units: 'degreesFahrenheit',
          description: null,
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
          controller_id: testControllerId1,
          point_name: 'Humidity Sensor 1',
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
      ])
      .run()

    // Points for controller 2
    await db
      .insert(controllerPoints)
      .values([
        {
          id: '00000000-0000-0000-0000-000000000020',
          organization_id: testOrgId,
          site_id: testSiteId,
          iot_device_id: testIotDeviceId,
          controller_id: testControllerId2,
          point_name: 'Temp Sensor 2',
          point_type: 'analogInput',
          object_identifier: '["analog-input",0]',
          instance_number: 0,
          writable: false,
          units: 'degreesCelsius',
          description: null,
          metadata: null,
          is_deleted: false,
          created_at: now,
          updated_at: now,
        },
      ])
      .run()
  })

  afterAll(() => {
    closeDatabase()
  })

  it('should fetch points for multiple controllers', async () => {
    const request = new Request(
      `http://localhost/api?controllerIds=${testControllerId1},${testControllerId2}`
    ) as any

    const mockParams = Promise.resolve({
      orgId: testOrgId,
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
    })

    const response = await GET(request, { params: mockParams })
    const json = await response.json()

    expect(response.status).toBe(200)
    expect(json.success).toBe(true)
    expect(json.data.pointsByController[testControllerId1]).toHaveLength(2)
    expect(json.data.pointsByController[testControllerId2]).toHaveLength(1)
    expect(json.data.pointsByController[testControllerId1][0].pointName).toBe(
      'Temp Sensor 1'
    )
    expect(json.data.pointsByController[testControllerId2][0].pointName).toBe(
      'Temp Sensor 2'
    )
  })

  it('should return empty arrays for controllers with no points', async () => {
    const db = getDatabase()
    await db.delete(controllerPoints).run()

    const request = new Request(
      `http://localhost/api?controllerIds=${testControllerId1},${testControllerId2}`
    ) as any

    const mockParams = Promise.resolve({
      orgId: testOrgId,
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
    })

    const response = await GET(request, { params: mockParams })
    const json = await response.json()

    expect(response.status).toBe(200)
    expect(json.data.pointsByController[testControllerId1]).toEqual([])
    expect(json.data.pointsByController[testControllerId2]).toEqual([])
  })

  it('should return 400 when controllerIds query param missing', async () => {
    const request = new Request('http://localhost/api') as any
    const mockParams = Promise.resolve({
      orgId: testOrgId,
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
    })

    const response = await GET(request, { params: mockParams })
    const json = await response.json()

    expect(response.status).toBe(400)
    expect(json.error).toBe('controllerIds query parameter required')
  })

  it('should return 404 when any controller does not exist', async () => {
    const request = new Request(
      `http://localhost/api?controllerIds=${testControllerId1},99999999-9999-9999-9999-999999999999`
    ) as any

    const mockParams = Promise.resolve({
      orgId: testOrgId,
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
    })

    const response = await GET(request, { params: mockParams })
    const json = await response.json()

    expect(response.status).toBe(404)
    expect(json.error).toContain('Controller not found')
  })

  it('should return 403 when controller belongs to different org', async () => {
    const request = new Request(
      `http://localhost/api?controllerIds=${testControllerId1}`
    ) as any

    const wrongOrgParams = Promise.resolve({
      orgId: 'org_different-org-456',
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
    })

    const response = await GET(request, { params: wrongOrgParams })
    const json = await response.json()

    expect(response.status).toBe(403)
    expect(json.error).toBe('Forbidden')
  })

  it('should map DB fields to camelCase DTO', async () => {
    const request = new Request(
      `http://localhost/api?controllerIds=${testControllerId1}`
    ) as any

    const mockParams = Promise.resolve({
      orgId: testOrgId,
      siteId: testSiteId,
      projectId: testProjectId,
      iotDeviceId: testIotDeviceId,
    })

    const response = await GET(request, { params: mockParams })
    const json = await response.json()

    const point = json.data.pointsByController[testControllerId1][0]

    // Check camelCase mapping
    expect(point.id).toBeDefined()
    expect(point.organizationId).toBe(testOrgId)
    expect(point.siteId).toBe(testSiteId)
    expect(point.iotDeviceId).toBe(testIotDeviceId)
    expect(point.controllerId).toBe(testControllerId1)
    expect(point.pointName).toBeDefined()
    expect(point.pointType).toBeDefined()

    // Check no snake_case leakage
    expect(point.organization_id).toBeUndefined()
    expect(point.point_name).toBeUndefined()
  })
})
