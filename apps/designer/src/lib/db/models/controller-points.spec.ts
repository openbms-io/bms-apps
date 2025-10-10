/** @jest-environment node */

import { controllerPointsRepository } from './controller-points'
import { closeDatabase, getDatabase } from '../client'
import {
  controllerPoints,
  iotDeviceControllers,
  organizations,
  sites,
  iotDevices,
} from '../schema'
import { randomUUID } from 'crypto'

describe('ControllerPointsRepository (SQLite + Drizzle)', () => {
  const testOrgId = 'test-org-123'
  const testSiteId = 'test-site-456'
  const testIotDeviceId = 'test-device-789'
  const testControllerId = 'test-controller-202'

  beforeEach(async () => {
    const db = getDatabase()
    await db.delete(controllerPoints).run()
    await db.delete(iotDeviceControllers).run()
    await db.delete(iotDevices).run()
    await db.delete(sites).run()
    await db.delete(organizations).run()

    const now = new Date().toISOString()

    await db
      .insert(organizations)
      .values({
        id: testOrgId,
        name: 'Test Organization',
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
        ip_address: '192.168.3.50',
        port: 47808,
        device_id: 3000,
        network_number: null,
        mac_address: null,
        name: 'Test Controller',
        description: null,
        is_active: true,
        metadata: '{}',
        created_at: now,
        updated_at: now,
      })
      .run()
  })

  afterAll(() => {
    closeDatabase()
  })

  function expectIsoString(value: unknown): asserts value is string {
    expect(typeof value).toBe('string')
    expect(value).toMatch(/^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(\.\d{3})?Z$/)
    expect(() => new Date(value as string)).not.toThrow()
  }

  it('creates and reads back a point with all fields', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'Zone1_Temperature',
      point_type: 'analogInput',
      object_identifier: 'analogInput:0',
      instance_number: 0,
      writable: false,
      units: 'degrees-fahrenheit',
      description: 'Zone 1 temperature sensor',
      metadata: {
        min_pres_value: 32,
        max_pres_value: 212,
        resolution: 0.1,
      },
      id: randomUUID(),
    })

    expect(created.id).toMatch(/[0-9a-fA-F-]{36}/)
    expect(created.organization_id).toBe(testOrgId)
    expect(created.site_id).toBe(testSiteId)
    expect(created.iot_device_id).toBe(testIotDeviceId)
    expect(created.controller_id).toBe(testControllerId)
    expect(created.point_name).toBe('Zone1_Temperature')
    expect(created.point_type).toBe('analogInput')
    expect(created.object_identifier).toBe('analogInput:0')
    expect(created.instance_number).toBe(0)
    expect(created.writable).toBe(false)
    expect(created.units).toBe('degrees-fahrenheit')
    expect(created.description).toBe('Zone 1 temperature sensor')
    expect(created.metadata).toEqual({
      min_pres_value: 32,
      max_pres_value: 212,
      resolution: 0.1,
    })
    expectIsoString(created.created_at)
    expectIsoString(created.updated_at)

    const fetched = await controllerPointsRepository.findById(created.id)
    expect(fetched).not.toBeNull()
    expect(fetched!.id).toBe(created.id)
    expect(fetched!.point_name).toBe('Zone1_Temperature')
  })

  it('creates with minimal required fields and default values', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'MinimalPoint',
      point_type: 'binaryOutput',
      object_identifier: 'binaryOutput:10',
      instance_number: 10,
      id: randomUUID(),
    })

    expect(created.point_name).toBe('MinimalPoint')
    expect(created.writable).toBe(false)
    expect(created.units).toBeUndefined()
    expect(created.description).toBeUndefined()
    expect(created.metadata).toEqual({})

    const fetched = await controllerPointsRepository.findById(created.id)
    expect(fetched!.units).toBeUndefined()
    expect(fetched!.description).toBeUndefined()
  })

  it('updates point properties and timestamps', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'PointToUpdate',
      point_type: 'analogValue',
      object_identifier: 'analogValue:5',
      instance_number: 5,
      description: 'Original description',
      units: 'celsius',
      id: randomUUID(),
    })

    await new Promise((r) => setTimeout(r, 5))

    const updated = await controllerPointsRepository.update(created.id, {
      point_name: 'UpdatedPoint',
      description: null,
      units: 'fahrenheit',
      writable: true,
      metadata: {
        cov_increment: 1.0,
        deadband: 0.5,
      },
    })

    expect(updated).not.toBeNull()
    expect(updated!.id).toBe(created.id)
    expect(updated!.point_name).toBe('UpdatedPoint')
    expect(updated!.description).toBeUndefined()
    expect(updated!.units).toBe('fahrenheit')
    expect(updated!.writable).toBe(true)
    expect(updated!.metadata).toEqual({
      cov_increment: 1.0,
      deadband: 0.5,
    })
    expect(new Date(updated!.updated_at).getTime()).toBeGreaterThan(
      new Date(created.updated_at).getTime()
    )
  })

  it('deletes point successfully', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'PointToDelete',
      point_type: 'binaryInput',
      object_identifier: 'binaryInput:20',
      instance_number: 20,
      description: null,
      id: randomUUID(),
    })

    const deleted = await controllerPointsRepository.delete(created.id)
    expect(deleted).toBe(true)

    const fetched = await controllerPointsRepository.findById(created.id)
    expect(fetched).toBeNull()

    const deletedAgain = await controllerPointsRepository.delete(created.id)
    expect(deletedAgain).toBe(false)
  })

  it('findByController returns all points for a controller', async () => {
    const point1 = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'ControllerPoint1',
      point_type: 'analogInput',
      object_identifier: 'analogInput:1',
      instance_number: 1,
      id: randomUUID(),
    })

    const point2 = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'ControllerPoint2',
      point_type: 'analogInput',
      object_identifier: 'analogInput:2',
      instance_number: 2,
      id: randomUUID(),
    })

    const points =
      await controllerPointsRepository.findByController(testControllerId)

    expect(points).toHaveLength(2)
    const names = points.map((p) => p.point_name).sort()
    expect(names).toEqual(['ControllerPoint1', 'ControllerPoint2'])

    const wrongController =
      await controllerPointsRepository.findByController('wrong-controller')
    expect(wrongController).toHaveLength(0)
  })

  it('findByDevice returns all points scoped to org/site/device', async () => {
    const point1 = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'DevicePoint1',
      point_type: 'analogInput',
      object_identifier: 'analogInput:3',
      instance_number: 3,
      id: randomUUID(),
    })

    const point2 = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'DevicePoint2',
      point_type: 'analogInput',
      object_identifier: 'analogInput:4',
      instance_number: 4,
      id: randomUUID(),
    })

    const points = await controllerPointsRepository.findByDevice(
      testOrgId,
      testSiteId,
      testIotDeviceId
    )

    expect(points).toHaveLength(2)
    const names = points.map((p) => p.point_name).sort()
    expect(names).toEqual(['DevicePoint1', 'DevicePoint2'])

    const wrongDevice = await controllerPointsRepository.findByDevice(
      testOrgId,
      testSiteId,
      'wrong-device'
    )
    expect(wrongDevice).toHaveLength(0)
  })

  it('findById returns null for non-existent point', async () => {
    const result = await controllerPointsRepository.findById(
      '00000000-0000-0000-0000-000000000000'
    )
    expect(result).toBeNull()
  })

  it('update returns null for non-existent point', async () => {
    const result = await controllerPointsRepository.update(
      '00000000-0000-0000-0000-000000000000',
      { point_name: 'Should not work' }
    )
    expect(result).toBeNull()
  })

  it('verifyOwnership returns true for correct owner', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'OwnershipTestPoint',
      point_type: 'analogInput',
      object_identifier: 'analogInput:100',
      instance_number: 100,
      id: randomUUID(),
    })

    const isOwner = await controllerPointsRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(true)
  })

  it('verifyOwnership returns false for wrong org', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'WrongOrgPoint',
      point_type: 'analogInput',
      object_identifier: 'analogInput:101',
      instance_number: 101,
      id: randomUUID(),
    })

    const isOwner = await controllerPointsRepository.verifyOwnership({
      id: created.id,
      orgId: 'wrong-org',
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for wrong site', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'WrongSitePoint',
      point_type: 'analogInput',
      object_identifier: 'analogInput:102',
      instance_number: 102,
      id: randomUUID(),
    })

    const isOwner = await controllerPointsRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: 'wrong-site',
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for wrong device', async () => {
    const created = await controllerPointsRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      controller_id: testControllerId,
      point_name: 'WrongDevicePoint',
      point_type: 'analogInput',
      object_identifier: 'analogInput:103',
      instance_number: 103,
      id: randomUUID(),
    })

    const isOwner = await controllerPointsRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: 'wrong-device',
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for non-existent point', async () => {
    const isOwner = await controllerPointsRepository.verifyOwnership({
      id: '00000000-0000-0000-0000-000000000000',
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })
})
