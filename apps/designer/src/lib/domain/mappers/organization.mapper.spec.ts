import { OrganizationMapper } from './organization.mapper'
import type {
  CreateOrganization,
  UpdateOrganization,
} from '../models/organization'

describe('OrganizationMapper', () => {
  describe('toDTO', () => {
    it('converts DB record to DTO (snake_case → camelCase)', () => {
      const dbOrganization = {
        id: 'org_123',
        name: 'Test Organization',
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = OrganizationMapper.toDTO(dbOrganization)

      expect(dto.id).toBe('org_123')
      expect(dto.name).toBe('Test Organization')
      expect(dto.createdAt).toBe('2025-01-01T00:00:00Z')
      expect(dto.updatedAt).toBe('2025-01-02T00:00:00Z')
    })
  })

  describe('toDbInsert', () => {
    it('converts DTO to DB insert (camelCase → snake_case)', () => {
      const createDto: CreateOrganization = {
        name: 'New Organization',
      }
      const id = 'org_456'

      const dbInsert = OrganizationMapper.toDbInsert(createDto, id)

      expect(dbInsert.id).toBe('org_456')
      expect(dbInsert.name).toBe('New Organization')
      expect(dbInsert.created_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
      expect(dbInsert.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('sets created_at and updated_at to same timestamp', () => {
      const createDto: CreateOrganization = {
        name: 'Test Org',
      }
      const id = 'org_789'

      const dbInsert = OrganizationMapper.toDbInsert(createDto, id)

      expect(dbInsert.created_at).toBe(dbInsert.updated_at)
    })
  })

  describe('toDbUpdate', () => {
    it('converts DTO update to DB update (camelCase → snake_case)', () => {
      const updateDto: UpdateOrganization = {
        name: 'Updated Organization',
      }

      const dbUpdate = OrganizationMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Updated Organization')
      expect(dbUpdate.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('omits undefined fields from update', () => {
      const updateDto: UpdateOrganization = {}

      const dbUpdate = OrganizationMapper.toDbUpdate(updateDto)

      expect('name' in dbUpdate).toBe(false)
      expect('updated_at' in dbUpdate).toBe(false)
    })

    it('updates updated_at timestamp when name is provided', () => {
      const updateDto: UpdateOrganization = {
        name: 'Changed Name',
      }

      const dbUpdate = OrganizationMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Changed Name')
      expect(dbUpdate.updated_at).toBeDefined()
    })
  })
})
