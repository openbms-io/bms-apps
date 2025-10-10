/** @jest-environment node */

import { bacnetReadersRepository } from './bacnet-readers'
import { closeDatabase, getDatabase } from '../client'
import { bacnetReaders, organizations, sites, iotDevices } from '../schema'

describe('BacnetReadersRepository (SQLite + Drizzle)', () => {
  const testOrgId = 'test-org-123'
  const testSiteId = 'test-site-456'
  const testIotDeviceId = 'test-device-789'

  beforeEach(async () => {
    const db = getDatabase()
    await db.delete(bacnetReaders).run()
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
  })

  afterAll(() => {
    closeDatabase()
  })

  function expectIsoString(value: unknown): asserts value is string {
    expect(typeof value).toBe('string')
    expect(value).toMatch(/^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(\.\d{3})?Z$/)
    expect(() => new Date(value as string)).not.toThrow()
  }

  it('creates and reads back a BACnet reader with all fields', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.100',
      port: 47808,
      device_id: 1001,
      network_number: 2000,
      mac_address: '00:1A:2B:3C:4D:5E',
      name: 'Main Building Reader',
      description: 'Primary BACnet reader for main building',
      is_active: true,
      metadata: {
        status_flags: ['in_alarm'],
        event_state: 'normal',
        reliability: 'no_fault_detected',
      },
    })

    expect(created.id).toMatch(/[0-9a-fA-F-]{36}/)
    expect(created.organization_id).toBe(testOrgId)
    expect(created.site_id).toBe(testSiteId)
    expect(created.iot_device_id).toBe(testIotDeviceId)
    expect(created.ip_address).toBe('192.168.1.100')
    expect(created.port).toBe(47808)
    expect(created.device_id).toBe(1001)
    expect(created.network_number).toBe(2000)
    expect(created.mac_address).toBe('00:1A:2B:3C:4D:5E')
    expect(created.name).toBe('Main Building Reader')
    expect(created.description).toBe('Primary BACnet reader for main building')
    expect(created.is_active).toBe(true)
    expect(created.metadata).toEqual({
      status_flags: ['in_alarm'],
      event_state: 'normal',
      reliability: 'no_fault_detected',
    })
    expectIsoString(created.created_at)
    expectIsoString(created.updated_at)

    const fetched = await bacnetReadersRepository.findById(created.id)
    expect(fetched).not.toBeNull()
    expect(fetched!.id).toBe(created.id)
    expect(fetched!.ip_address).toBe('192.168.1.100')
    expect(fetched!.device_id).toBe(1001)
  })

  it('creates with minimal required fields and default values', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.101',
      device_id: 1002,
      name: 'Minimal Reader',
    })

    expect(created.name).toBe('Minimal Reader')
    expect(created.description).toBeUndefined()
    expect(created.network_number).toBeUndefined()
    expect(created.mac_address).toBeUndefined()
    expect(created.port).toBe(47808) // default
    expect(created.is_active).toBe(true) // default
    expect(created.metadata).toEqual({})

    const fetched = await bacnetReadersRepository.findById(created.id)
    expect(fetched!.description).toBeUndefined()
    expect(fetched!.network_number).toBeUndefined()
    expect(fetched!.mac_address).toBeUndefined()
  })

  it('updates reader properties and timestamps', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.102',
      device_id: 1003,
      name: 'Reader to Update',
      description: 'Original description',
    })

    await new Promise((r) => setTimeout(r, 5))

    const updated = await bacnetReadersRepository.update(created.id, {
      name: 'Updated Reader',
      description: null,
      is_active: false,
      metadata: {
        out_of_service: true,
      },
    })

    expect(updated).not.toBeNull()
    expect(updated!.id).toBe(created.id)
    expect(updated!.name).toBe('Updated Reader')
    expect(updated!.description).toBeUndefined()
    expect(updated!.is_active).toBe(false)
    expect(updated!.metadata).toEqual({ out_of_service: true })
    expect(new Date(updated!.updated_at).getTime()).toBeGreaterThan(
      new Date(created.updated_at).getTime()
    )
  })

  it('deletes reader successfully', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.103',
      device_id: 1004,
      name: 'Reader to Delete',
    })

    const deleted = await bacnetReadersRepository.delete(created.id)
    expect(deleted).toBe(true)

    const fetched = await bacnetReadersRepository.findById(created.id)
    expect(fetched).toBeNull()

    const deletedAgain = await bacnetReadersRepository.delete(created.id)
    expect(deletedAgain).toBe(false)
  })

  it('findByDevice returns readers scoped to org/site/device', async () => {
    const reader1 = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.104',
      device_id: 1005,
      name: 'Device Reader 1',
    })

    const reader2 = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.105',
      device_id: 1006,
      name: 'Device Reader 2',
    })

    const readers = await bacnetReadersRepository.findByDevice(
      testOrgId,
      testSiteId,
      testIotDeviceId
    )

    expect(readers).toHaveLength(2)
    const names = readers.map((r) => r.name).sort()
    expect(names).toEqual(['Device Reader 1', 'Device Reader 2'])

    const wrongDevice = await bacnetReadersRepository.findByDevice(
      testOrgId,
      testSiteId,
      'wrong-device'
    )
    expect(wrongDevice).toHaveLength(0)
  })

  it('findById returns null for non-existent reader', async () => {
    const result = await bacnetReadersRepository.findById(
      '00000000-0000-0000-0000-000000000000'
    )
    expect(result).toBeNull()
  })

  it('update returns null for non-existent reader', async () => {
    const result = await bacnetReadersRepository.update(
      '00000000-0000-0000-0000-000000000000',
      { name: 'Should not work' }
    )
    expect(result).toBeNull()
  })

  it('verifyOwnership returns true for correct owner', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.106',
      device_id: 1007,
      name: 'Ownership Test Reader',
    })

    const isOwner = await bacnetReadersRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(true)
  })

  it('verifyOwnership returns false for wrong org', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.107',
      device_id: 1008,
      name: 'Wrong Org Test',
    })

    const isOwner = await bacnetReadersRepository.verifyOwnership({
      id: created.id,
      orgId: 'wrong-org',
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for wrong site', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.108',
      device_id: 1009,
      name: 'Wrong Site Test',
    })

    const isOwner = await bacnetReadersRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: 'wrong-site',
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for wrong device', async () => {
    const created = await bacnetReadersRepository.create({
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      ip_address: '192.168.1.109',
      device_id: 1010,
      name: 'Wrong Device Test',
    })

    const isOwner = await bacnetReadersRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: 'wrong-device',
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for non-existent reader', async () => {
    const isOwner = await bacnetReadersRepository.verifyOwnership({
      id: '00000000-0000-0000-0000-000000000000',
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })
})
