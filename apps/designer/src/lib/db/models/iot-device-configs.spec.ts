/** @jest-environment node */

import { iotDeviceConfigsRepository } from './iot-device-configs'
import { closeDatabase, getDatabase } from '../client'
import {
  iotDeviceConfigs,
  organizations,
  sites,
  iotDevices,
  projects,
} from '../schema'
import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'

describe('IotDeviceConfigsRepository (SQLite + Drizzle)', () => {
  const testOrgId = 'test-org-123'
  const testSiteId = 'test-site-456'
  const testIotDeviceId = 'test-device-789'
  const testProjectId = 'test-project-101'

  const mockWorkflowConfig: ValidatedWorkflowConfig = {
    nodes: [
      {
        id: 'node-1',
        type: 'constant',
        position: { x: 0, y: 0 },
        data: { label: 'Test Node', value: 42, valueType: 'number' },
      },
    ],
    edges: [],
    metadata: {
      version: '1.0.0',
      createdAt: new Date().toISOString(),
      updatedAt: new Date().toISOString(),
    },
  }

  beforeEach(async () => {
    const db = getDatabase()
    await db.delete(iotDeviceConfigs).run()
    await db.delete(projects).run()
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
      .insert(projects)
      .values({
        id: testProjectId,
        site_id: testSiteId,
        iot_device_id: testIotDeviceId,
        name: 'Test Project',
        description: null,
        workflow_config: '{}',
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

  it('creates and reads back a config with workflow data', async () => {
    const created = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
      is_active: true,
    })

    expect(created.id).toMatch(/[0-9a-fA-F-]{36}/)
    expect(created.organization_id).toBe(testOrgId)
    expect(created.site_id).toBe(testSiteId)
    expect(created.iot_device_id).toBe(testIotDeviceId)
    expect(created.config_data).toEqual(mockWorkflowConfig)
    expect(created.version).toBe(1)
    expect(created.is_active).toBe(true)
    expectIsoString(created.created_at)
    expectIsoString(created.updated_at)

    const fetched = await iotDeviceConfigsRepository.findById(created.id)
    expect(fetched).not.toBeNull()
    expect(fetched!.id).toBe(created.id)
    expect(fetched!.config_data).toEqual(mockWorkflowConfig)
  })

  it('creates with default values', async () => {
    const created = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
    })

    expect(created.version).toBe(1)
    expect(created.is_active).toBe(true)
  })

  it('updates config properties and timestamps', async () => {
    const created = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
      is_active: true,
    })

    await new Promise((r) => setTimeout(r, 5))

    const updatedWorkflowConfig: ValidatedWorkflowConfig = {
      nodes: [
        {
          id: 'node-2',
          type: 'constant',
          position: { x: 100, y: 100 },
          data: { label: 'Updated Node', value: 84, valueType: 'number' },
        },
      ],
      edges: [],
      metadata: {
        version: '2.0.0',
        createdAt: new Date().toISOString(),
        updatedAt: new Date().toISOString(),
      },
    }

    const updated = await iotDeviceConfigsRepository.update(created.id, {
      config_data: updatedWorkflowConfig,
      version: 2,
      is_active: false,
    })

    expect(updated).not.toBeNull()
    expect(updated!.id).toBe(created.id)
    expect(updated!.config_data).toEqual(updatedWorkflowConfig)
    expect(updated!.version).toBe(2)
    expect(updated!.is_active).toBe(false)
    expect(new Date(updated!.updated_at).getTime()).toBeGreaterThan(
      new Date(created.updated_at).getTime()
    )
  })

  it('findByDevice returns all configs ordered by created_at desc', async () => {
    const config1 = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
      is_active: false,
    })

    await new Promise((r) => setTimeout(r, 10))

    const config2 = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 2,
      is_active: true,
    })

    const configs = await iotDeviceConfigsRepository.findByDevice(
      testOrgId,
      testSiteId,
      testIotDeviceId
    )

    expect(configs).toHaveLength(2)
    expect(configs[0].id).toBe(config2.id)
    expect(configs[1].id).toBe(config1.id)

    const wrongDevice = await iotDeviceConfigsRepository.findByDevice(
      testOrgId,
      testSiteId,
      'wrong-device'
    )
    expect(wrongDevice).toHaveLength(0)
  })

  it('findLatestByDevice returns only active config', async () => {
    const config1 = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
      is_active: false,
    })

    await new Promise((r) => setTimeout(r, 10))

    const config2 = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 2,
      is_active: true,
    })

    await new Promise((r) => setTimeout(r, 10))

    const config3 = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 3,
      is_active: true,
    })

    const latest = await iotDeviceConfigsRepository.findLatestByDevice(
      testOrgId,
      testSiteId,
      testIotDeviceId
    )

    expect(latest).not.toBeNull()
    expect(latest!.id).toBe(config3.id)
    expect(latest!.version).toBe(3)
    expect(latest!.is_active).toBe(true)
  })

  it('findLatestByDevice returns null when no active config exists', async () => {
    await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
      is_active: false,
    })

    const latest = await iotDeviceConfigsRepository.findLatestByDevice(
      testOrgId,
      testSiteId,
      testIotDeviceId
    )

    expect(latest).toBeNull()
  })

  it('findById returns null for non-existent config', async () => {
    const result = await iotDeviceConfigsRepository.findById(
      '00000000-0000-0000-0000-000000000000'
    )
    expect(result).toBeNull()
  })

  it('update returns null for non-existent config', async () => {
    const result = await iotDeviceConfigsRepository.update(
      '00000000-0000-0000-0000-000000000000',
      { version: 99 }
    )
    expect(result).toBeNull()
  })

  it('verifyOwnership returns true for correct owner', async () => {
    const created = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
    })

    const isOwner = await iotDeviceConfigsRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(true)
  })

  it('verifyOwnership returns false for wrong org', async () => {
    const created = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
    })

    const isOwner = await iotDeviceConfigsRepository.verifyOwnership({
      id: created.id,
      orgId: 'wrong-org',
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for wrong site', async () => {
    const created = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
    })

    const isOwner = await iotDeviceConfigsRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: 'wrong-site',
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for wrong device', async () => {
    const created = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
    })

    const isOwner = await iotDeviceConfigsRepository.verifyOwnership({
      id: created.id,
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: 'wrong-device',
    })

    expect(isOwner).toBe(false)
  })

  it('verifyOwnership returns false for non-existent config', async () => {
    const isOwner = await iotDeviceConfigsRepository.verifyOwnership({
      id: '00000000-0000-0000-0000-000000000000',
      orgId: testOrgId,
      siteId: testSiteId,
      iotDeviceId: testIotDeviceId,
    })

    expect(isOwner).toBe(false)
  })

  it('supports multiple active configs for different devices', async () => {
    const testIotDevice2 = 'test-device-999'
    const testProject2 = 'test-project-102'
    const db = getDatabase()
    const now = new Date().toISOString()

    await db
      .insert(iotDevices)
      .values({
        id: testIotDevice2,
        organization_id: testOrgId,
        site_id: testSiteId,
        name: 'Test IoT Device 2',
        description: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    await db
      .insert(projects)
      .values({
        id: testProject2,
        site_id: testSiteId,
        iot_device_id: testIotDevice2,
        name: 'Test Project 2',
        description: null,
        workflow_config: '{}',
        created_at: now,
        updated_at: now,
      })
      .run()

    const config1 = await iotDeviceConfigsRepository.create({
      project_id: testProjectId,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDeviceId,
      config_data: mockWorkflowConfig,
      version: 1,
      is_active: true,
    })

    const config2 = await iotDeviceConfigsRepository.create({
      project_id: testProject2,
      organization_id: testOrgId,
      site_id: testSiteId,
      iot_device_id: testIotDevice2,
      config_data: mockWorkflowConfig,
      version: 1,
      is_active: true,
    })

    const latest1 = await iotDeviceConfigsRepository.findLatestByDevice(
      testOrgId,
      testSiteId,
      testIotDeviceId
    )

    const latest2 = await iotDeviceConfigsRepository.findLatestByDevice(
      testOrgId,
      testSiteId,
      testIotDevice2
    )

    expect(latest1!.id).toBe(config1.id)
    expect(latest2!.id).toBe(config2.id)
  })
})
