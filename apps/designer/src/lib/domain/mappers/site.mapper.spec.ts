import { SiteMapper } from './site.mapper'
import type { CreateSite, UpdateSite } from '../models/site'

describe('SiteMapper', () => {
  describe('toDTO', () => {
    it('converts DB record to DTO (snake_case → camelCase)', () => {
      const dbSite = {
        id: 'site_123',
        organization_id: 'org_456',
        name: 'Test Site',
        description: 'A test site',
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = SiteMapper.toDTO(dbSite)

      expect(dto.id).toBe('site_123')
      expect(dto.organizationId).toBe('org_456')
      expect(dto.name).toBe('Test Site')
      expect(dto.description).toBe('A test site')
      expect(dto.createdAt).toBe('2025-01-01T00:00:00Z')
      expect(dto.updatedAt).toBe('2025-01-02T00:00:00Z')
    })

    it('converts null to undefined for description', () => {
      const dbSite = {
        id: 'site_123',
        organization_id: 'org_456',
        name: 'Test Site',
        description: null,
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-02T00:00:00Z',
      }

      const dto = SiteMapper.toDTO(dbSite)

      expect(dto.description).toBeUndefined()
    })
  })

  describe('toDbInsert', () => {
    it('converts DTO to DB insert (camelCase → snake_case)', () => {
      const createDto: CreateSite = {
        organizationId: 'org_789',
        name: 'New Site',
        description: 'Site description',
      }
      const id = 'site_456'

      const dbInsert = SiteMapper.toDbInsert(createDto, id)

      expect(dbInsert.id).toBe('site_456')
      expect(dbInsert.organization_id).toBe('org_789')
      expect(dbInsert.name).toBe('New Site')
      expect(dbInsert.description).toBe('Site description')
      expect(dbInsert.created_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
      expect(dbInsert.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('handles optional description', () => {
      const createDto: CreateSite = {
        organizationId: 'org_123',
        name: 'New Site',
      }
      const id = 'site_789'

      const dbInsert = SiteMapper.toDbInsert(createDto, id)

      expect(dbInsert.description).toBeUndefined()
    })

    it('sets created_at and updated_at to same timestamp', () => {
      const createDto: CreateSite = {
        organizationId: 'org_123',
        name: 'Test Site',
      }
      const id = 'site_999'

      const dbInsert = SiteMapper.toDbInsert(createDto, id)

      expect(dbInsert.created_at).toBe(dbInsert.updated_at)
    })
  })

  describe('toDbUpdate', () => {
    it('converts DTO update to DB update (camelCase → snake_case)', () => {
      const updateDto: UpdateSite = {
        name: 'Updated Site',
        description: 'Updated description',
      }

      const dbUpdate = SiteMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Updated Site')
      expect(dbUpdate.description).toBe('Updated description')
      expect(dbUpdate.updated_at).toMatch(
        /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}/
      )
    })

    it('allows explicit null to clear description', () => {
      const updateDto: UpdateSite = {
        description: null,
      }

      const dbUpdate = SiteMapper.toDbUpdate(updateDto)

      expect(dbUpdate.description).toBeNull()
      expect(dbUpdate.updated_at).toBeDefined()
    })

    it('omits undefined fields from update', () => {
      const updateDto: UpdateSite = {}

      const dbUpdate = SiteMapper.toDbUpdate(updateDto)

      expect('name' in dbUpdate).toBe(false)
      expect('description' in dbUpdate).toBe(false)
      expect('updated_at' in dbUpdate).toBe(false)
    })

    it('updates only name without touching description', () => {
      const updateDto: UpdateSite = {
        name: 'Changed Name',
      }

      const dbUpdate = SiteMapper.toDbUpdate(updateDto)

      expect(dbUpdate.name).toBe('Changed Name')
      expect('description' in dbUpdate).toBe(false)
      expect(dbUpdate.updated_at).toBeDefined()
    })
  })
})
