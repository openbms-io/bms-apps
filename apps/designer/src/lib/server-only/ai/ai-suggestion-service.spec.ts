jest.mock('server-only', () => ({}))
jest.mock('ai', () => ({
  generateObject: jest.fn(),
}))
jest.mock('@ai-sdk/anthropic', () => ({
  createAnthropic: () => (model: string) => ({ provider: 'anthropic', model }),
}))
jest.mock('@ai-sdk/openai', () => ({
  createOpenAI: () => (model: string) => ({ provider: 'openai', model }),
}))

import {
  AISuggestionService,
  type IAISuggestionService,
} from './ai-suggestion-service'
import type {
  MemoryManager,
  MemoryContext,
  MappingRecord,
} from './memory-manager'
import type {
  SuggestionEngine,
  StepSuggestion,
  AIPointContext,
} from './suggestion-engine'

describe('AISuggestionService', () => {
  const createMockMemoryManager = (): jest.Mocked<MemoryManager> =>
    ({
      retrieveContext: jest.fn(),
      storeMapping: jest.fn(),
    }) as unknown as jest.Mocked<MemoryManager>

  const createMockSuggestionEngine = (): jest.Mocked<SuggestionEngine> =>
    ({
      generateStepSuggestion: jest.fn(),
    }) as unknown as jest.Mocked<SuggestionEngine>

  const createTestPoint = (): AIPointContext['point'] => ({
    name: 'VAV-2-01_ZoneTemp',
    objectType: 'analog-input',
    objectId: 1,
    controllerId: 'controller-1',
    description: 'Zone Temperature Sensor',
    units: 'degreesFahrenheit',
    presentValue: 72.5,
  })

  const createTestMemoryContext = (): MemoryContext => ({
    relevantMemories: [
      {
        text: 'Points matching VAV-*_ZoneTemp were mapped to VAV-Reheat system',
        score: 0.85,
      },
    ],
  })

  const createMockSuggestion = (): StepSuggestion => ({
    selectedId: 'vav-reheat-system',
    confidence: 0.92,
    reasoning: 'Based on point naming pattern and previous mappings',
    alternatives: [{ id: 'vav-cooling-only', confidence: 0.65 }],
  })

  beforeEach(() => {
    jest.clearAllMocks()
  })

  describe('getSuggestion', () => {
    it('retrieves memory context and generates suggestion', async () => {
      const mockMemoryManager = createMockMemoryManager()
      const mockSuggestionEngine = createMockSuggestionEngine()
      const service = new AISuggestionService(
        mockMemoryManager,
        mockSuggestionEngine
      )

      const memoryContext = createTestMemoryContext()
      const suggestion = createMockSuggestion()

      mockMemoryManager.retrieveContext.mockResolvedValue(memoryContext)
      mockSuggestionEngine.generateStepSuggestion.mockResolvedValue(suggestion)

      const result = await service.getSuggestion({
        step: 'system',
        orgId: 'org-123',
        point: createTestPoint(),
        candidates: ['vav-reheat-system', 'vav-cooling-only'],
      })

      expect(result).toEqual(suggestion)
      expect(mockMemoryManager.retrieveContext).toHaveBeenCalledWith({
        orgId: 'org-123',
        query: expect.stringContaining('VAV-2-01_ZoneTemp'),
        projectId: undefined,
      })
      expect(mockSuggestionEngine.generateStepSuggestion).toHaveBeenCalledWith({
        step: 'system',
        point: expect.objectContaining({ name: 'VAV-2-01_ZoneTemp' }),
        candidates: ['vav-reheat-system', 'vav-cooling-only'],
        memoryContext,
        selectionContext: undefined,
      })
    })

    it('includes projectId in memory retrieval when provided', async () => {
      const mockMemoryManager = createMockMemoryManager()
      const mockSuggestionEngine = createMockSuggestionEngine()
      const service = new AISuggestionService(
        mockMemoryManager,
        mockSuggestionEngine
      )

      mockMemoryManager.retrieveContext.mockResolvedValue({
        relevantMemories: [],
      })
      mockSuggestionEngine.generateStepSuggestion.mockResolvedValue(
        createMockSuggestion()
      )

      await service.getSuggestion({
        step: 'system',
        orgId: 'org-123',
        projectId: 'proj-456',
        point: createTestPoint(),
        candidates: ['candidate-1'],
      })

      expect(mockMemoryManager.retrieveContext).toHaveBeenCalledWith({
        orgId: 'org-123',
        query: expect.any(String),
        projectId: 'proj-456',
      })
    })

    it('passes selection context for device step', async () => {
      const mockMemoryManager = createMockMemoryManager()
      const mockSuggestionEngine = createMockSuggestionEngine()
      const service = new AISuggestionService(
        mockMemoryManager,
        mockSuggestionEngine
      )

      mockMemoryManager.retrieveContext.mockResolvedValue({
        relevantMemories: [],
      })
      mockSuggestionEngine.generateStepSuggestion.mockResolvedValue(
        createMockSuggestion()
      )

      await service.getSuggestion({
        step: 'device',
        orgId: 'org-123',
        point: createTestPoint(),
        candidates: ['device-1'],
        selectionContext: { systemId: 'selected-system' },
      })

      expect(mockSuggestionEngine.generateStepSuggestion).toHaveBeenCalledWith(
        expect.objectContaining({
          step: 'device',
          selectionContext: { systemId: 'selected-system' },
        })
      )
    })

    it('passes selection context for property step', async () => {
      const mockMemoryManager = createMockMemoryManager()
      const mockSuggestionEngine = createMockSuggestionEngine()
      const service = new AISuggestionService(
        mockMemoryManager,
        mockSuggestionEngine
      )

      mockMemoryManager.retrieveContext.mockResolvedValue({
        relevantMemories: [],
      })
      mockSuggestionEngine.generateStepSuggestion.mockResolvedValue(
        createMockSuggestion()
      )

      await service.getSuggestion({
        step: 'property',
        orgId: 'org-123',
        point: createTestPoint(),
        candidates: ['property-1'],
        selectionContext: {
          systemId: 'selected-system',
          deviceId: 'selected-device',
        },
      })

      expect(mockSuggestionEngine.generateStepSuggestion).toHaveBeenCalledWith(
        expect.objectContaining({
          step: 'property',
          selectionContext: {
            systemId: 'selected-system',
            deviceId: 'selected-device',
          },
        })
      )
    })

    it('builds query from point metadata', async () => {
      const mockMemoryManager = createMockMemoryManager()
      const mockSuggestionEngine = createMockSuggestionEngine()
      const service = new AISuggestionService(
        mockMemoryManager,
        mockSuggestionEngine
      )

      mockMemoryManager.retrieveContext.mockResolvedValue({
        relevantMemories: [],
      })
      mockSuggestionEngine.generateStepSuggestion.mockResolvedValue(
        createMockSuggestion()
      )

      const point = createTestPoint()
      await service.getSuggestion({
        step: 'system',
        orgId: 'org-123',
        point,
        candidates: ['candidate-1'],
      })

      expect(mockMemoryManager.retrieveContext).toHaveBeenCalledWith({
        orgId: 'org-123',
        query: expect.stringContaining('VAV-2-01_ZoneTemp'),
        projectId: undefined,
      })
      expect(mockMemoryManager.retrieveContext).toHaveBeenCalledWith({
        orgId: 'org-123',
        query: expect.stringContaining('analog-input'),
        projectId: undefined,
      })
      expect(mockMemoryManager.retrieveContext).toHaveBeenCalledWith({
        orgId: 'org-123',
        query: expect.stringContaining('Zone Temperature Sensor'),
        projectId: undefined,
      })
    })
  })

  describe('confirmMapping', () => {
    it('stores mapping via memory manager', async () => {
      const mockMemoryManager = createMockMemoryManager()
      const mockSuggestionEngine = createMockSuggestionEngine()
      const service = new AISuggestionService(
        mockMemoryManager,
        mockSuggestionEngine
      )

      mockMemoryManager.storeMapping.mockResolvedValue(undefined)

      const mapping: MappingRecord = {
        pointPattern: 'VAV-*_ZoneTemp',
        controllerId: 'controller-1',
        step: 'system',
        selectedId: 'vav-reheat-system',
        wasOverridden: false,
      }

      await service.confirmMapping({
        orgId: 'org-123',
        mapping,
      })

      expect(mockMemoryManager.storeMapping).toHaveBeenCalledWith({
        orgId: 'org-123',
        mapping,
        projectId: undefined,
      })
    })

    it('includes projectId when provided', async () => {
      const mockMemoryManager = createMockMemoryManager()
      const mockSuggestionEngine = createMockSuggestionEngine()
      const service = new AISuggestionService(
        mockMemoryManager,
        mockSuggestionEngine
      )

      mockMemoryManager.storeMapping.mockResolvedValue(undefined)

      const mapping: MappingRecord = {
        pointPattern: 'AHU-*_SupplyFan',
        controllerId: 'controller-2',
        step: 'device',
        selectedId: 'supply-fan-device',
        wasOverridden: true,
      }

      await service.confirmMapping({
        orgId: 'org-123',
        projectId: 'proj-789',
        mapping,
      })

      expect(mockMemoryManager.storeMapping).toHaveBeenCalledWith({
        orgId: 'org-123',
        mapping,
        projectId: 'proj-789',
      })
    })
  })
})
