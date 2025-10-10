import { IotDeviceControllerMapper } from './iot-device-controller.mapper'
import type {
  CreateIotDeviceController,
  UpdateIotDeviceController,
} from '../models/iot-device-controller'
import type { BacnetMetadata } from '@/types/bacnet-metadata'

describe('IotDeviceControllerMapper', () => {
  describe('toDTO', () => {
    it('converts DB record to DTO (snake_case → camelCase)', () => {
      const metadata: BacnetMetadata = {
        manufacturer: 'Test',
        modelName: 'Model1',
      }

      const dbController = {
        id: 'ctrl_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        iot_device_id: 'device_101',
        ip_address: '192.168.1.100',
        port: 47808,
        device_id: 1001,
        network_number: 10,
        mac_address: '00:11:22:33:44:55',
        name: 'Test Controller',
        description: 'A test controller',
        is_enabled: true,
        metadata,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = IotDeviceControllerMapper.toDTO(dbController)

      expect(dto.id).toBe('ctrl_123')
      expect(dto.organizationId).toBe('org_456')
      expect(dto.siteId).toBe('site_789')
      expect(dto.iotDeviceId).toBe('device_101')
      expect(dto.ipAddress).toBe('192.168.1.100')
      expect(dto.port).toBe(47808)
      expect(dto.deviceId).toBe(1001)
      expect(dto.networkNumber).toBe(10)
      expect(dto.macAddress).toBe('00:11:22:33:44:55')
      expect(dto.name).toBe('Test Controller')
      expect(dto.description).toBe('A test controller')
      expect(dto.isEnabled).toBe(true)
      expect(dto.metadata).toEqual(metadata)
      expect(dto.createdAt).toBe('2025-01-01T00:00:00Z')
      expect(dto.updatedAt).toBe('2025-01-02T00:00:00Z')
    })

    it('converts null to undefined for optional fields', () => {
      const dbController = {
        id: 'ctrl_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        iot_device_id: 'device_101',
        ip_address: '192.168.1.100',
        port: 47808,
        device_id: 1001,
        network_number: null,
        mac_address: null,
        name: 'Test Controller',
        description: null,
        is_enabled: true,
        metadata: null,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = IotDeviceControllerMapper.toDTO(dbController)

      expect(dto.networkNumber).toBeUndefined()
      expect(dto.macAddress).toBeUndefined()
      expect(dto.description).toBeUndefined()
      expect(dto.metadata).toBeUndefined()
    })

    it('converts empty object metadata to undefined', () => {
      const dbController = {
        id: 'ctrl_123',
        organization_id: 'org_456',
        site_id: 'site_789',
        iot_device_id: 'device_101',
        ip_address: '192.168.1.100',
        port: 47808,
        device_id: 1001,
        network_number: null,
        mac_address: null,
        name: 'Test Controller',
        description: null,
        is_enabled: true,
        metadata: '{}' as const,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = IotDeviceControllerMapper.toDTO(dbController)

      expect(dto.metadata).toBeUndefined()
    })
  })

  describe('toDbInsert', () => {
    it('converts DTO to DB insert (camelCase → snake_case)', () => {
      const metadata: BacnetMetadata = {
        manufacturer: 'Test',
        modelName: 'Model1',
      }

      const createDto: CreateIotDeviceController = {
        organizationId: 'org_789',
        siteId: 'site_101',
        iotDeviceId: 'device_202',
        ipAddress: '192.168.1.101',
        port: 47809,
        deviceId: 1002,
        networkNumber: 20,
        macAddress: '11:22:33:44:55:66',
        name: 'New Controller',
        description: 'Controller description',
        isEnabled: false,
        metadata,
      }
      const id = 'ctrl_456'

      const dbInsert = IotDeviceControllerMapper.toDbInsert(createDto, id)

      expect(dbInsert.id).toBe('ctrl_456')
      expect(dbInsert.organization_id).toBe('org_789')
      expect(dbInsert.site_id).toBe('site_101')
      expect(dbInsert.iot_device_id).toBe('device_202')
      expect(dbInsert.ip_address).toBe('192.168.1.101')
      expect(dbInsert.port).toBe(47809)
      expect(dbInsert.device_id).toBe(1002)
      expect(dbInsert.network_number).toBe(20)
      expect(dbInsert.mac_address).toBe('11:22:33:44:55:66')
      expect(dbInsert.name).toBe('New Controller')
      expect(dbInsert.description).toBe('Controller description')
      expect(dbInsert.is_enabled).toBe(false)
      expect(dbInsert.metadata).toEqual(metadata)
      expect(dbInsert.created_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
      expect(dbInsert.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('handles optional fields', () => {
      const createDto: CreateIotDeviceController = {
        organizationId: 'org_123',
        siteId: 'site_456',
        iotDeviceId: 'device_789',
        ipAddress: '192.168.1.102',
        port: 47808,
        deviceId: 1003,
        name: 'New Controller',
      }
      const id = 'ctrl_789'

      const dbInsert = IotDeviceControllerMapper.toDbInsert(createDto, id)

      expect(dbInsert.network_number).toBeUndefined()
      expect(dbInsert.mac_address).toBeUndefined()
      expect(dbInsert.description).toBeUndefined()
      expect(dbInsert.is_enabled).toBe(true)
      expect(dbInsert.metadata).toBe('{}')
    })

    it('sets created_at and updated_at to same timestamp', () => {
      const createDto: CreateIotDeviceController = {
        organizationId: 'org_123',
        siteId: 'site_456',
        iotDeviceId: 'device_789',
        ipAddress: '192.168.1.103',
        port: 47808,
        deviceId: 1004,
        name: 'Test Controller',
      }
      const id = 'ctrl_999'

      const dbInsert = IotDeviceControllerMapper.toDbInsert(createDto, id)

      expect(dbInsert.created_at).toBe(dbInsert.updated_at)
    })
  })

  describe('toDbUpdate', () => {
    it('converts DTO update to DB update (camelCase → snake_case)', () => {
      const metadata: BacnetMetadata = {
        manufacturer: 'Updated',
        modelName: 'Model2',
      }

      const updateDto: UpdateIotDeviceController = {
        ipAddress: '192.168.1.104',
        port: 47810,
        deviceId: 1005,
        networkNumber: 30,
        macAddress: '22:33:44:55:66:77',
        name: 'Updated Controller',
        description: 'Updated description',
        isEnabled: true,
        metadata,
      }

      const dbUpdate = IotDeviceControllerMapper.toDbUpdate(updateDto)

      expect(dbUpdate.ip_address).toBe('192.168.1.104')
      expect(dbUpdate.port).toBe(47810)
      expect(dbUpdate.device_id).toBe(1005)
      expect(dbUpdate.network_number).toBe(30)
      expect(dbUpdate.mac_address).toBe('22:33:44:55:66:77')
      expect(dbUpdate.name).toBe('Updated Controller')
      expect(dbUpdate.description).toBe('Updated description')
      expect(dbUpdate.is_enabled).toBe(true)
      expect(dbUpdate.metadata).toEqual(metadata)
      expect(dbUpdate.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('allows explicit null to clear optional fields', () => {
      const updateDto: UpdateIotDeviceController = {
        networkNumber: null,
        macAddress: null,
        description: null,
        metadata: null,
      }

      const dbUpdate = IotDeviceControllerMapper.toDbUpdate(updateDto)

      expect(dbUpdate.network_number).toBeNull()
      expect(dbUpdate.mac_address).toBeNull()
      expect(dbUpdate.description).toBeNull()
      expect(dbUpdate.metadata).toBe('{}')
      expect(dbUpdate.updated_at).toBeDefined()
    })

    it('omits undefined fields from update', () => {
      const updateDto: UpdateIotDeviceController = {}

      const dbUpdate = IotDeviceControllerMapper.toDbUpdate(updateDto)

      expect('ip_address' in dbUpdate).toBe(false)
      expect('port' in dbUpdate).toBe(false)
      expect('device_id' in dbUpdate).toBe(false)
      expect('network_number' in dbUpdate).toBe(false)
      expect('mac_address' in dbUpdate).toBe(false)
      expect('name' in dbUpdate).toBe(false)
      expect('description' in dbUpdate).toBe(false)
      expect('is_enabled' in dbUpdate).toBe(false)
      expect('metadata' in dbUpdate).toBe(false)
      expect('updated_at' in dbUpdate).toBe(false)
    })

    it('updates only some fields without touching others', () => {
      const updateDto: UpdateIotDeviceController = {
        name: 'Changed Name',
        port: 48000,
      }

      const dbUpdate = IotDeviceControllerMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Changed Name')
      expect(dbUpdate.port).toBe(48000)
      expect('ip_address' in dbUpdate).toBe(false)
      expect('device_id' in dbUpdate).toBe(false)
      expect('description' in dbUpdate).toBe(false)
      expect(dbUpdate.updated_at).toBeDefined()
    })
  })
})
