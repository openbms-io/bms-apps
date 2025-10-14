import { IotDeviceMapper } from './iot-device.mapper'
import type { CreateIotDevice, UpdateIotDevice } from '../models/iot-device'

describe('IotDeviceMapper', () => {
  describe('toDTO', () => {
    it('converts DB record to DTO (snake_case → camelCase)', () => {
      const dbIotDevice = {
        id: 'device_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        name: 'Test Device',
        description: 'A test device',
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = IotDeviceMapper.toDTO(dbIotDevice)

      expect(dto.id).toBe('device_123')
      expect(dto.organizationId).toBe('org_456')
      expect(dto.siteId).toBe('site_789')
      expect(dto.name).toBe('Test Device')
      expect(dto.description).toBe('A test device')
      expect(dto.createdAt).toBe('2025-01-01T00:00:00Z')
      expect(dto.updatedAt).toBe('2025-01-02T00:00:00Z')
    })

    it('converts null to undefined for description', () => {
      const dbIotDevice = {
        id: 'device_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        name: 'Test Device',
        description: null,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = IotDeviceMapper.toDTO(dbIotDevice)

      expect(dto.description).toBeUndefined()
    })
  })

  describe('toDbInsert', () => {
    it('converts DTO to DB insert (camelCase → snake_case)', () => {
      const createDto: CreateIotDevice = {
        organizationId: 'org_789',
        siteId: 'site_101',
        name: 'New Device',
        description: 'Device description',
      }
      const id = 'device_456'

      const dbInsert = IotDeviceMapper.toDbInsert(createDto, id)

      expect(dbInsert.id).toBe('device_456')
      expect(dbInsert.organization_id).toBe('org_789')
      expect(dbInsert.site_id).toBe('site_101')
      expect(dbInsert.name).toBe('New Device')
      expect(dbInsert.description).toBe('Device description')
      expect(dbInsert.created_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
      expect(dbInsert.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('handles optional description', () => {
      const createDto: CreateIotDevice = {
        organizationId: 'org_123',
        siteId: 'site_456',
        name: 'New Device',
      }
      const id = 'device_789'

      const dbInsert = IotDeviceMapper.toDbInsert(createDto, id)

      expect(dbInsert.description).toBeUndefined()
    })

    it('sets created_at and updated_at to same timestamp', () => {
      const createDto: CreateIotDevice = {
        organizationId: 'org_123',
        siteId: 'site_456',
        name: 'Test Device',
      }
      const id = 'device_999'

      const dbInsert = IotDeviceMapper.toDbInsert(createDto, id)

      expect(dbInsert.created_at).toBe(dbInsert.updated_at)
    })
  })

  describe('toDbUpdate', () => {
    it('converts DTO update to DB update (camelCase → snake_case)', () => {
      const updateDto: UpdateIotDevice = {
        name: 'Updated Device',
        description: 'Updated description',
      }

      const dbUpdate = IotDeviceMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Updated Device')
      expect(dbUpdate.description).toBe('Updated description')
      expect(dbUpdate.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('allows explicit null to clear description', () => {
      const updateDto: UpdateIotDevice = {
        description: null,
      }

      const dbUpdate = IotDeviceMapper.toDbUpdate(updateDto)

      expect(dbUpdate.description).toBeNull()
      expect(dbUpdate.updated_at).toBeDefined()
    })

    it('omits undefined fields from update', () => {
      const updateDto: UpdateIotDevice = {}

      const dbUpdate = IotDeviceMapper.toDbUpdate(updateDto)

      expect('name' in dbUpdate).toBe(false)
      expect('description' in dbUpdate).toBe(false)
      expect('updated_at' in dbUpdate).toBe(false)
    })

    it('updates only name without touching description', () => {
      const updateDto: UpdateIotDevice = {
        name: 'Changed Name',
      }

      const dbUpdate = IotDeviceMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Changed Name')
      expect('description' in dbUpdate).toBe(false)
      expect(dbUpdate.updated_at).toBeDefined()
    })
  })
})
