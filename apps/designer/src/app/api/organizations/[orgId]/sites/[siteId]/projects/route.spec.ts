/**
 * @jest-environment node
 */

import { GET } from './route'
import { getDatabase, closeDatabase } from '@/lib/db/client'
import { organizations, sites, projects } from '@/lib/db/schema'

describe('GET /api/organizations/[orgId]/sites/[siteId]/projects', () => {
  const testOrgId = 'org_test-projects-123'
  const testSiteId1 = '00000000-0000-0000-0000-000000000001'
  const testSiteId2 = '00000000-0000-0000-0000-000000000002'

  beforeEach(async () => {
    const db = getDatabase()
    const now = new Date().toISOString()

    // Clean up
    await db.delete(projects).run()
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
      .values([
        {
          id: testSiteId1,
          organization_id: testOrgId,
          name: 'Test Site 1',
          description: null,
          created_at: now,
          updated_at: now,
        },
        {
          id: testSiteId2,
          organization_id: testOrgId,
          name: 'Test Site 2',
          description: null,
          created_at: now,
          updated_at: now,
        },
      ])
      .run()

    // Insert test projects
    await db
      .insert(projects)
      .values([
        {
          id: '00000000-0000-0000-0000-000000000010',
          site_id: testSiteId1,
          name: 'Project A in Site 1',
          description: null,
          iot_device_id: null,
          workflow_config: '{}',
          created_at: now,
          updated_at: now,
        },
        {
          id: '00000000-0000-0000-0000-000000000011',
          site_id: testSiteId1,
          name: 'Project B in Site 1',
          description: null,
          iot_device_id: null,
          workflow_config: '{}',
          created_at: now,
          updated_at: now,
        },
        {
          id: '00000000-0000-0000-0000-000000000020',
          site_id: testSiteId2,
          name: 'Project C in Site 2',
          description: null,
          iot_device_id: null,
          workflow_config: '{}',
          created_at: now,
          updated_at: now,
        },
      ])
      .run()
  })

  afterAll(() => {
    closeDatabase()
  })

  it('filters projects by siteId from path params', async () => {
    const mockRequest = new Request('http://localhost:3000/api/test')

    const response = await GET(mockRequest, {
      params: Promise.resolve({
        orgId: testOrgId,
        siteId: testSiteId1,
      }),
    })

    expect(response.status).toBe(200)

    const json = await response.json()
    expect(json.success).toBe(true)
    expect(json.data.projects).toHaveLength(2)
    expect(json.data.projects.every((p: any) => p.siteId === testSiteId1)).toBe(
      true
    )
    expect(json.data.projects.map((p: any) => p.name)).toEqual(
      expect.arrayContaining(['Project A in Site 1', 'Project B in Site 1'])
    )
  })

  it('returns only projects from requested site, not other sites', async () => {
    const mockRequest = new Request('http://localhost:3000/api/test')

    const response = await GET(mockRequest, {
      params: Promise.resolve({
        orgId: testOrgId,
        siteId: testSiteId2,
      }),
    })

    expect(response.status).toBe(200)

    const json = await response.json()
    expect(json.success).toBe(true)
    expect(json.data.projects).toHaveLength(1)
    expect(json.data.projects[0].siteId).toBe(testSiteId2)
    expect(json.data.projects[0].name).toBe('Project C in Site 2')
  })

  it('returns empty array when site has no projects', async () => {
    const emptySiteId = '00000000-0000-0000-0000-000000000999'
    const db = getDatabase()
    const now = new Date().toISOString()

    await db
      .insert(sites)
      .values({
        id: emptySiteId,
        organization_id: testOrgId,
        name: 'Empty Site',
        description: null,
        created_at: now,
        updated_at: now,
      })
      .run()

    const mockRequest = new Request('http://localhost:3000/api/test')

    const response = await GET(mockRequest, {
      params: Promise.resolve({
        orgId: testOrgId,
        siteId: emptySiteId,
      }),
    })

    expect(response.status).toBe(200)

    const json = await response.json()
    expect(json.success).toBe(true)
    expect(json.data.projects).toHaveLength(0)
  })
})
