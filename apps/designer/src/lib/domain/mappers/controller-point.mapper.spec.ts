import { ControllerPointMapper } from './controller-point.mapper'
import type {
  CreateControllerPoint,
  UpdateControllerPoint,
} from '../models/controller-point'
import type { BacnetMetadata } from '@/types/bacnet-metadata'

describe('ControllerPointMapper', () => {
  describe('toDTO', () => {
    it('converts DB record to DTO (snake_case → camelCase)', () => {
      const metadata: BacnetMetadata = {
        manufacturer: 'Test',
        modelName: 'Model1',
      }

      const dbPoint = {
        id: 'point_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        iot_device_id: 'device_101',
        controller_id: 'ctrl_202',
        point_name: 'Temperature Sensor',
        point_type: 'analogInput',
        object_identifier: 'AI:1',
        instance_number: 1,
        writable: false,
        units: 'degreesCelsius',
        description: 'Main temperature sensor',
        metadata,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = ControllerPointMapper.toDTO(dbPoint)

      expect(dto.id).toBe('point_123')
      expect(dto.organizationId).toBe('org_456')
      expect(dto.siteId).toBe('site_789')
      expect(dto.iotDeviceId).toBe('device_101')
      expect(dto.controllerId).toBe('ctrl_202')
      expect(dto.pointName).toBe('Temperature Sensor')
      expect(dto.pointType).toBe('analogInput')
      expect(dto.objectIdentifier).toBe('AI:1')
      expect(dto.instanceNumber).toBe(1)
      expect(dto.writable).toBe(false)
      expect(dto.units).toBe('degreesCelsius')
      expect(dto.description).toBe('Main temperature sensor')
      expect(dto.metadata).toEqual(metadata)
      expect(dto.createdAt).toBe('2025-01-01T00:00:00Z')
      expect(dto.updatedAt).toBe('2025-01-02T00:00:00Z')
    })

    it('converts null to undefined for optional fields', () => {
      const dbPoint = {
        id: 'point_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        iot_device_id: 'device_101',
        controller_id: 'ctrl_202',
        point_name: 'Test Point',
        point_type: 'binaryOutput',
        object_identifier: 'BO:2',
        instance_number: 2,
        writable: true,
        units: null,
        description: null,
        metadata: null,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = ControllerPointMapper.toDTO(dbPoint)

      expect(dto.units).toBeUndefined()
      expect(dto.description).toBeUndefined()
      expect(dto.metadata).toBeUndefined()
    })

    it('converts empty object metadata to undefined', () => {
      const dbPoint = {
        id: 'point_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        iot_device_id: 'device_101',
        controller_id: 'ctrl_202',
        point_name: 'Test Point',
        point_type: 'analogValue',
        object_identifier: 'AV:3',
        instance_number: 3,
        writable: false,
        units: null,
        description: null,
        metadata: '{}' as const,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = ControllerPointMapper.toDTO(dbPoint)

      expect(dto.metadata).toBeUndefined()
    })
  })

  describe('toDbInsert', () => {
    it('converts DTO to DB insert (camelCase → snake_case)', () => {
      const metadata: BacnetMetadata = {
        manufacturer: 'Test',
        modelName: 'Model1',
      }

      const createDto: CreateControllerPoint = {
        organizationId: 'org_789',
        siteId: 'site_101',
        iotDeviceId: 'device_202',
        controllerId: 'ctrl_303',
        pointName: 'Pressure Sensor',
        pointType: 'analogInput',
        objectIdentifier: 'AI:4',
        instanceNumber: 4,
        writable: false,
        units: 'pascals',
        description: 'Main pressure sensor',
        metadata,
      }
      const id = 'point_456'

      const dbInsert = ControllerPointMapper.toDbInsert(createDto, id)

      expect(dbInsert.id).toBe('point_456')
      expect(dbInsert.organization_id).toBe('org_789')
      expect(dbInsert.site_id).toBe('site_101')
      expect(dbInsert.iot_device_id).toBe('device_202')
      expect(dbInsert.controller_id).toBe('ctrl_303')
      expect(dbInsert.point_name).toBe('Pressure Sensor')
      expect(dbInsert.point_type).toBe('analogInput')
      expect(dbInsert.object_identifier).toBe('AI:4')
      expect(dbInsert.instance_number).toBe(4)
      expect(dbInsert.writable).toBe(false)
      expect(dbInsert.units).toBe('pascals')
      expect(dbInsert.description).toBe('Main pressure sensor')
      expect(dbInsert.metadata).toEqual(metadata)
      expect(dbInsert.created_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
      expect(dbInsert.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('handles optional fields', () => {
      const createDto: CreateControllerPoint = {
        organizationId: 'org_123',
        siteId: 'site_456',
        iotDeviceId: 'device_789',
        controllerId: 'ctrl_404',
        pointName: 'New Point',
        pointType: 'binaryInput',
        objectIdentifier: 'BI:5',
        instanceNumber: 5,
      }
      const id = 'point_789'

      const dbInsert = ControllerPointMapper.toDbInsert(createDto, id)

      expect(dbInsert.writable).toBe(false)
      expect(dbInsert.units).toBeUndefined()
      expect(dbInsert.description).toBeUndefined()
      expect(dbInsert.metadata).toBe('{}')
    })

    it('sets created_at and updated_at to same timestamp', () => {
      const createDto: CreateControllerPoint = {
        organizationId: 'org_123',
        siteId: 'site_456',
        iotDeviceId: 'device_789',
        controllerId: 'ctrl_404',
        pointName: 'Test Point',
        pointType: 'analogOutput',
        objectIdentifier: 'AO:6',
        instanceNumber: 6,
      }
      const id = 'point_999'

      const dbInsert = ControllerPointMapper.toDbInsert(createDto, id)

      expect(dbInsert.created_at).toBe(dbInsert.updated_at)
    })
  })

  describe('toDbUpdate', () => {
    it('converts DTO update to DB update (camelCase → snake_case)', () => {
      const metadata: BacnetMetadata = {
        manufacturer: 'Updated',
        modelName: 'Model2',
      }

      const updateDto: UpdateControllerPoint = {
        pointName: 'Updated Point',
        pointType: 'analogValue',
        objectIdentifier: 'AV:7',
        instanceNumber: 7,
        writable: true,
        units: 'meters',
        description: 'Updated description',
        metadata,
      }

      const dbUpdate = ControllerPointMapper.toDbUpdate(updateDto)

      expect(dbUpdate.point_name).toBe('Updated Point')
      expect(dbUpdate.point_type).toBe('analogValue')
      expect(dbUpdate.object_identifier).toBe('AV:7')
      expect(dbUpdate.instance_number).toBe(7)
      expect(dbUpdate.writable).toBe(true)
      expect(dbUpdate.units).toBe('meters')
      expect(dbUpdate.description).toBe('Updated description')
      expect(dbUpdate.metadata).toEqual(metadata)
      expect(dbUpdate.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('allows explicit null to clear optional fields', () => {
      const updateDto: UpdateControllerPoint = {
        units: null,
        description: null,
        metadata: null,
      }

      const dbUpdate = ControllerPointMapper.toDbUpdate(updateDto)

      expect(dbUpdate.units).toBeNull()
      expect(dbUpdate.description).toBeNull()
      expect(dbUpdate.metadata).toBe('{}')
      expect(dbUpdate.updated_at).toBeDefined()
    })

    it('omits undefined fields from update', () => {
      const updateDto: UpdateControllerPoint = {}

      const dbUpdate = ControllerPointMapper.toDbUpdate(updateDto)

      expect('point_name' in dbUpdate).toBe(false)
      expect('point_type' in dbUpdate).toBe(false)
      expect('object_identifier' in dbUpdate).toBe(false)
      expect('instance_number' in dbUpdate).toBe(false)
      expect('writable' in dbUpdate).toBe(false)
      expect('units' in dbUpdate).toBe(false)
      expect('description' in dbUpdate).toBe(false)
      expect('metadata' in dbUpdate).toBe(false)
      expect('updated_at' in dbUpdate).toBe(false)
    })

    it('updates only some fields without touching others', () => {
      const updateDto: UpdateControllerPoint = {
        pointName: 'Changed Name',
        writable: true,
      }

      const dbUpdate = ControllerPointMapper.toDbUpdate(updateDto)

      expect(dbUpdate.point_name).toBe('Changed Name')
      expect(dbUpdate.writable).toBe(true)
      expect('point_type' in dbUpdate).toBe(false)
      expect('object_identifier' in dbUpdate).toBe(false)
      expect('instance_number' in dbUpdate).toBe(false)
      expect('description' in dbUpdate).toBe(false)
      expect(dbUpdate.updated_at).toBeDefined()
    })
  })
})
