import { ProjectMapper } from './project.mapper'
import type { CreateProject, UpdateProject } from '../models/project'

describe('ProjectMapper', () => {
  describe('toDTO', () => {
    it('converts DB record to DTO (snake_case → camelCase)', () => {
      const dbProject = {
        id: 'proj_123',
        site_id: 'site_456',
        iot_device_id: 'iot_789',
        name: 'My Project',
        description: 'Test description',
        workflow_config:
          '{"schema_info":{"version":"1.0.0","compatibility":">=1.0.0","schema_name":"WorkflowConfig"},"data":{"nodes":[],"edges":[],"metadata":{}}}',
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = ProjectMapper.toDTO(dbProject)

      expect(dto.id).toBe('proj_123')
      expect(dto.siteId).toBe('site_456')
      expect(dto.iotDeviceId).toBe('iot_789')
      expect(dto.name).toBe('My Project')
      expect(dto.description).toBe('Test description')
      expect(dto.workflowConfig).toEqual({
        schema_info: {
          version: '1.0.0',
          compatibility: '>=1.0.0',
          schema_name: 'WorkflowConfig',
        },
        data: {
          nodes: [],
          edges: [],
          metadata: {},
        },
      })
      expect(dto.createdAt).toBe('2025-01-01T00:00:00Z')
      expect(dto.updatedAt).toBe('2025-01-02T00:00:00Z')
    })

    it('converts null to undefined for nullable fields', () => {
      const dbProject = {
        id: 'proj_123',
        site_id: 'site_456',
        iot_device_id: null,
        name: 'My Project',
        description: null,
        workflow_config: '{}',
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-01T00:00:00Z',
      }

      const dto = ProjectMapper.toDTO(dbProject)

      expect(dto.iotDeviceId).toBeUndefined()
      expect(dto.description).toBeUndefined()
    })

    it('parses workflow_config JSON string to object', () => {
      const dbProject = {
        id: 'proj_123',
        site_id: 'site_456',
        iot_device_id: null,
        name: 'My Project',
        description: null,
        workflow_config:
          '{"schema_info":{"version":"1.0.0","compatibility":">=1.0.0","schema_name":"WorkflowConfig"},"data":{"nodes":[{"id":"1"}],"edges":[],"metadata":{}}}',
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-01T00:00:00Z',
      }

      const dto = ProjectMapper.toDTO(dbProject)

      expect(dto.workflowConfig.data.nodes).toEqual([{ id: '1' }])
    })
  })

  describe('toDbInsert', () => {
    it('converts DTO to DB insert (camelCase → snake_case)', () => {
      const createDto: CreateProject = {
        siteId: 'site_123',
        name: 'New Project',
        description: 'Test',
        workflowConfig: {
          schema_info: {
            version: '1.0.0',
            compatibility: '>=1.0.0',
            schema_name: 'WorkflowConfig',
          },
          data: {
            nodes: [],
            edges: [],
            metadata: {},
          },
        },
      }

      const dbInsert = ProjectMapper.toDbInsert(createDto)

      expect(dbInsert.site_id).toBe('site_123')
      expect(dbInsert.name).toBe('New Project')
      expect(dbInsert.description).toBe('Test')
      expect(dbInsert.workflow_config).toBe(
        '{"schema_info":{"version":"1.0.0","compatibility":">=1.0.0","schema_name":"WorkflowConfig"},"data":{"nodes":[],"edges":[],"metadata":{}}}'
      )
    })

    it('handles optional fields correctly', () => {
      const createDto: CreateProject = {
        siteId: 'site_123',
        name: 'New Project',
      }

      const dbInsert = ProjectMapper.toDbInsert(createDto)

      expect(dbInsert.site_id).toBe('site_123')
      expect(dbInsert.name).toBe('New Project')
      expect(dbInsert.description).toBeUndefined()
      expect(dbInsert.workflow_config).toBeNull()
    })

    it('stringifies workflowConfig object to JSON', () => {
      const createDto: CreateProject = {
        siteId: 'site_123',
        name: 'New Project',
        workflowConfig: {
          schema_info: {
            version: '1.0.0',
            compatibility: '>=1.0.0',
            schema_name: 'WorkflowConfig',
          },
          data: {
            nodes: [{ id: '1', type: 'test' }],
            edges: [],
            metadata: {},
          },
        },
      }

      const dbInsert = ProjectMapper.toDbInsert(createDto)

      const parsed = JSON.parse(dbInsert.workflow_config)
      expect(parsed.data.nodes).toEqual([{ id: '1', type: 'test' }])
    })
  })

  describe('toDbUpdate', () => {
    it('converts DTO update to DB update (camelCase → snake_case)', () => {
      const updateDto: UpdateProject = {
        name: 'Updated Name',
        workflowConfig: {
          schema_info: {
            version: '1.0.0',
            compatibility: '>=1.0.0',
            schema_name: 'WorkflowConfig',
          },
          data: {
            nodes: [{ id: '1' }],
            edges: [],
            metadata: {},
          },
        },
      }

      const dbUpdate = ProjectMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Updated Name')
      expect(dbUpdate.workflow_config).toBe(
        '{"schema_info":{"version":"1.0.0","compatibility":">=1.0.0","schema_name":"WorkflowConfig"},"data":{"nodes":[{"id":"1"}],"edges":[],"metadata":{}}}'
      )
    })

    it('allows explicit null to clear fields', () => {
      const updateDto: UpdateProject = {
        description: null,
        iotDeviceId: null,
      }

      const dbUpdate = ProjectMapper.toDbUpdate(updateDto)

      expect(dbUpdate.description).toBeNull()
      expect(dbUpdate.iot_device_id).toBeNull()
    })

    it('omits undefined fields from update', () => {
      const updateDto: UpdateProject = {
        name: 'Updated',
        description: undefined,
      }

      const dbUpdate = ProjectMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Updated')
      expect('description' in dbUpdate).toBe(false)
    })

    it('handles all fields independently', () => {
      const updateDto: UpdateProject = {
        name: 'New Name',
        description: 'New Desc',
        iotDeviceId: 'iot_999',
        workflowConfig: {
          schema_info: {
            version: '1.0.0',
            compatibility: '>=1.0.0',
            schema_name: 'WorkflowConfig',
          },
          data: {
            nodes: [],
            edges: [],
            metadata: {},
          },
        },
      }

      const dbUpdate = ProjectMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('New Name')
      expect(dbUpdate.description).toBe('New Desc')
      expect(dbUpdate.iot_device_id).toBe('iot_999')
      expect(JSON.parse(dbUpdate.workflow_config!).data.nodes).toEqual([])
    })
  })
})
