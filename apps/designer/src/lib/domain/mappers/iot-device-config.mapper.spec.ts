import { IotDeviceConfigMapper } from './iot-device-config.mapper'
import type {
  CreateIotDeviceConfig,
  UpdateIotDeviceConfig,
} from '../models/iot-device-config'
import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'

describe('IotDeviceConfigMapper', () => {
  const mockConfigData: ValidatedWorkflowConfig = {
    schema_info: {
      version: '1.0.0',
      format: 'bms-flow-v1',
    },
    data: {
      nodes: [],
      edges: [],
    },
  }

  describe('toDTO', () => {
    it('converts DB record to DTO (snake_case → camelCase)', () => {
      const dbConfig = {
        id: 'config_123',
        project_id: 'project_456',
        organization_id: 'org_789',
        site_id: 'site_101',
        iot_device_id: 'device_202',
        config_data: mockConfigData,
        version: 2,
        is_active: true,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = IotDeviceConfigMapper.toDTO(dbConfig)

      expect(dto.id).toBe('config_123')
      expect(dto.projectId).toBe('project_456')
      expect(dto.organizationId).toBe('org_789')
      expect(dto.siteId).toBe('site_101')
      expect(dto.iotDeviceId).toBe('device_202')
      expect(dto.configData).toEqual(mockConfigData)
      expect(dto.version).toBe(2)
      expect(dto.isActive).toBe(true)
      expect(dto.createdAt).toBe('2025-01-01T00:00:00Z')
      expect(dto.updatedAt).toBe('2025-01-02T00:00:00Z')
    })
  })

  describe('toDbInsert', () => {
    it('converts DTO to DB insert (camelCase → snake_case)', () => {
      const createDto: CreateIotDeviceConfig = {
        projectId: 'project_303',
        organizationId: 'org_404',
        siteId: 'site_505',
        iotDeviceId: 'device_606',
        configData: mockConfigData,
        version: 3,
        isActive: false,
      }
      const id = 'config_456'

      const dbInsert = IotDeviceConfigMapper.toDbInsert(createDto, id)

      expect(dbInsert.id).toBe('config_456')
      expect(dbInsert.project_id).toBe('project_303')
      expect(dbInsert.organization_id).toBe('org_404')
      expect(dbInsert.site_id).toBe('site_505')
      expect(dbInsert.iot_device_id).toBe('device_606')
      expect(dbInsert.config_data).toEqual(mockConfigData)
      expect(dbInsert.version).toBe(3)
      expect(dbInsert.is_active).toBe(false)
      expect(dbInsert.created_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
      expect(dbInsert.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('handles optional fields with defaults', () => {
      const createDto: CreateIotDeviceConfig = {
        projectId: 'project_123',
        organizationId: 'org_456',
        siteId: 'site_789',
        iotDeviceId: 'device_101',
        configData: mockConfigData,
      }
      const id = 'config_789'

      const dbInsert = IotDeviceConfigMapper.toDbInsert(createDto, id)

      expect(dbInsert.version).toBe(1)
      expect(dbInsert.is_active).toBe(true)
    })

    it('sets created_at and updated_at to same timestamp', () => {
      const createDto: CreateIotDeviceConfig = {
        projectId: 'project_123',
        organizationId: 'org_456',
        siteId: 'site_789',
        iotDeviceId: 'device_101',
        configData: mockConfigData,
      }
      const id = 'config_999'

      const dbInsert = IotDeviceConfigMapper.toDbInsert(createDto, id)

      expect(dbInsert.created_at).toBe(dbInsert.updated_at)
    })
  })

  describe('toDbUpdate', () => {
    it('converts DTO update to DB update (camelCase → snake_case)', () => {
      const updateDto: UpdateIotDeviceConfig = {
        configData: mockConfigData,
        version: 4,
        isActive: true,
      }

      const dbUpdate = IotDeviceConfigMapper.toDbUpdate(updateDto)

      expect(dbUpdate.config_data).toEqual(mockConfigData)
      expect(dbUpdate.version).toBe(4)
      expect(dbUpdate.is_active).toBe(true)
      expect(dbUpdate.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('omits undefined fields from update', () => {
      const updateDto: UpdateIotDeviceConfig = {}

      const dbUpdate = IotDeviceConfigMapper.toDbUpdate(updateDto)

      expect('config_data' in dbUpdate).toBe(false)
      expect('version' in dbUpdate).toBe(false)
      expect('is_active' in dbUpdate).toBe(false)
      expect('updated_at' in dbUpdate).toBe(false)
    })

    it('updates only some fields without touching others', () => {
      const updateDto: UpdateIotDeviceConfig = {
        version: 5,
      }

      const dbUpdate = IotDeviceConfigMapper.toDbUpdate(updateDto)

      expect(dbUpdate.version).toBe(5)
      expect('config_data' in dbUpdate).toBe(false)
      expect('is_active' in dbUpdate).toBe(false)
      expect(dbUpdate.updated_at).toBeDefined()
    })
  })
})
