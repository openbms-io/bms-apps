jest.mock('server-only', () => ({}))

import {
  MemoryManager,
  createMemoryClient,
  type IMemoryClient,
  type MappingRecord,
} from './memory-manager'

describe('MemoryManager', () => {
  const createMockClient = (): jest.Mocked<IMemoryClient> => ({
    search: jest.fn(),
    add: jest.fn(),
  })

  describe('retrieveContext', () => {
    it('calls client.search with org_id filter', async () => {
      const mockClient = createMockClient()
      mockClient.search.mockResolvedValue({
        results: [
          {
            memory:
              'Points matching VAV-*_ZoneTemp were mapped to VAV-Reheat system',
            score: 0.85,
          },
        ],
      })

      const manager = new MemoryManager(mockClient)
      const result = await manager.retrieveContext({
        orgId: 'org-123',
        query: 'VAV zone temperature mapping',
      })

      expect(mockClient.search).toHaveBeenCalledWith(
        'VAV zone temperature mapping',
        { user_id: 'org-123' }
      )
      expect(result).toEqual({
        relevantMemories: [
          {
            text: 'Points matching VAV-*_ZoneTemp were mapped to VAV-Reheat system',
            score: 0.85,
          },
        ],
      })
    })

    it('includes projectId in search filter when provided', async () => {
      const mockClient = createMockClient()
      mockClient.search.mockResolvedValue({ results: [] })

      const manager = new MemoryManager(mockClient)
      await manager.retrieveContext({
        orgId: 'org-123',
        query: 'test query',
        projectId: 'proj-456',
      })

      expect(mockClient.search).toHaveBeenCalledWith('test query', {
        user_id: 'org-123',
        metadata: { projectId: 'proj-456' },
      })
    })

    it('returns empty array when no memories found', async () => {
      const mockClient = createMockClient()
      mockClient.search.mockResolvedValue({ results: [] })

      const manager = new MemoryManager(mockClient)
      const result = await manager.retrieveContext({
        orgId: 'org-123',
        query: 'unknown query',
      })

      expect(result).toEqual({ relevantMemories: [] })
    })
  })

  describe('storeMapping', () => {
    it('calls client.add with formatted mapping text and org_id', async () => {
      const mockClient = createMockClient()
      mockClient.add.mockResolvedValue({ id: 'mem-new' })

      const manager = new MemoryManager(mockClient)
      const mapping: MappingRecord = {
        pointPattern: 'VAV-*_ZoneTemp',
        controllerId: 'controller-1',
        step: 'system',
        selectedId: 'vav-reheat-system',
        wasOverridden: false,
      }

      await manager.storeMapping({
        orgId: 'org-123',
        mapping,
      })

      expect(mockClient.add).toHaveBeenCalledWith(
        [
          {
            role: 'user',
            content:
              'Mapping decision: Points matching pattern "VAV-*_ZoneTemp" from controller "controller-1" were mapped to "vav-reheat-system" at step "system". AI suggestion was accepted.',
          },
        ],
        {
          user_id: 'org-123',
          metadata: {
            pointPattern: 'VAV-*_ZoneTemp',
            controllerId: 'controller-1',
            step: 'system',
            selectedId: 'vav-reheat-system',
            wasOverridden: false,
          },
        }
      )
    })

    it('includes wasOverridden=true in message when user overrode suggestion', async () => {
      const mockClient = createMockClient()
      mockClient.add.mockResolvedValue({ id: 'mem-new' })

      const manager = new MemoryManager(mockClient)
      const mapping: MappingRecord = {
        pointPattern: 'AHU-*_SupplyFan',
        controllerId: 'controller-2',
        step: 'device',
        selectedId: 'supply-fan-device',
        wasOverridden: true,
      }

      await manager.storeMapping({
        orgId: 'org-123',
        mapping,
      })

      expect(mockClient.add).toHaveBeenCalledWith(
        [
          {
            role: 'user',
            content:
              'Mapping decision: Points matching pattern "AHU-*_SupplyFan" from controller "controller-2" were mapped to "supply-fan-device" at step "device". User overrode AI suggestion.',
          },
        ],
        expect.objectContaining({
          user_id: 'org-123',
        })
      )
    })

    it('includes projectId in metadata when provided', async () => {
      const mockClient = createMockClient()
      mockClient.add.mockResolvedValue({ id: 'mem-new' })

      const manager = new MemoryManager(mockClient)
      const mapping: MappingRecord = {
        pointPattern: 'FCU-*_Valve',
        controllerId: 'controller-3',
        step: 'property',
        selectedId: 'valve-position',
        wasOverridden: false,
      }

      await manager.storeMapping({
        orgId: 'org-123',
        mapping,
        projectId: 'proj-789',
      })

      expect(mockClient.add).toHaveBeenCalledWith(expect.any(Array), {
        user_id: 'org-123',
        metadata: {
          pointPattern: 'FCU-*_Valve',
          controllerId: 'controller-3',
          step: 'property',
          selectedId: 'valve-position',
          wasOverridden: false,
          projectId: 'proj-789',
        },
      })
    })
  })
})

describe('createMemoryClient', () => {
  const originalEnv = process.env

  beforeEach(() => {
    process.env = { ...originalEnv }
  })

  afterAll(() => {
    process.env = originalEnv
  })

  it('throws error when MEM0_API_KEY not set', () => {
    delete process.env.MEM0_API_KEY

    expect(() => createMemoryClient()).toThrow(
      'MEM0_API_KEY environment variable is required'
    )
  })
})
