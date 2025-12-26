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
  SuggestionEngine,
  type StepSuggestion,
  type AIPointContext,
  type IObjectGenerator,
} from './suggestion-engine'
import type { MemoryContext } from './memory-manager'

describe('SuggestionEngine', () => {
  const createMockGenerator = (): jest.Mocked<IObjectGenerator> => ({
    generate: jest.fn(),
  })

  const createTestPoint = (
    overrides?: Partial<AIPointContext['point']>
  ): AIPointContext['point'] => ({
    name: 'VAV-2-01_ZoneTemp',
    objectType: 'analog-input',
    objectId: 1,
    controllerId: 'controller-1',
    description: 'Zone Temperature Sensor',
    units: 'degreesFahrenheit',
    presentValue: 72.5,
    ...overrides,
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
    reasoning:
      'Based on point naming pattern VAV-*_ZoneTemp and previous mappings',
    alternatives: [
      { id: 'vav-cooling-only', confidence: 0.65 },
      { id: 'fcu-2pipe', confidence: 0.45 },
    ],
  })

  beforeEach(() => {
    jest.clearAllMocks()
  })

  describe('generateStepSuggestion', () => {
    it('generates suggestion for system step', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)
      const mockResult = createMockSuggestion()

      mockGenerator.generate.mockResolvedValue(mockResult)

      const result = await engine.generateStepSuggestion({
        step: 'system',
        point: createTestPoint(),
        candidates: ['vav-reheat-system', 'vav-cooling-only', 'fcu-2pipe'],
        memoryContext: createTestMemoryContext(),
      })

      expect(result).toEqual(mockResult)
      expect(mockGenerator.generate).toHaveBeenCalled()
    })

    it('generates suggestion for device step', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)
      const mockResult: StepSuggestion = {
        selectedId: 'zone-temperature-sensor',
        confidence: 0.88,
        reasoning: 'Analog input with temperature units matches sensor device',
        alternatives: [{ id: 'discharge-air-sensor', confidence: 0.55 }],
      }

      mockGenerator.generate.mockResolvedValue(mockResult)

      const result = await engine.generateStepSuggestion({
        step: 'device',
        point: createTestPoint(),
        candidates: ['zone-temperature-sensor', 'discharge-air-sensor'],
        memoryContext: createTestMemoryContext(),
        selectionContext: { systemId: 'vav-reheat-system' },
      })

      expect(result).toEqual(mockResult)
      expect(mockGenerator.generate).toHaveBeenCalled()
    })

    it('generates suggestion for property step', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)
      const mockResult: StepSuggestion = {
        selectedId: 'observes-zone-air-temperature',
        confidence: 0.95,
        reasoning: 'Temperature sensor observes zone air temperature',
        alternatives: [
          { id: 'observes-supply-air-temperature', confidence: 0.35 },
        ],
      }

      mockGenerator.generate.mockResolvedValue(mockResult)

      const result = await engine.generateStepSuggestion({
        step: 'property',
        point: createTestPoint(),
        candidates: [
          'observes-zone-air-temperature',
          'observes-supply-air-temperature',
        ],
        memoryContext: createTestMemoryContext(),
        selectionContext: {
          systemId: 'vav-reheat-system',
          deviceId: 'zone-temperature-sensor',
        },
      })

      expect(result).toEqual(mockResult)
      expect(mockGenerator.generate).toHaveBeenCalled()
    })

    it('returns StepSuggestion structure with required fields', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)
      const mockResult = createMockSuggestion()

      mockGenerator.generate.mockResolvedValue(mockResult)

      const result = await engine.generateStepSuggestion({
        step: 'system',
        point: createTestPoint(),
        candidates: ['candidate-1'],
        memoryContext: { relevantMemories: [] },
      })

      expect(result).toHaveProperty('selectedId')
      expect(result).toHaveProperty('confidence')
      expect(result).toHaveProperty('reasoning')
      expect(result).toHaveProperty('alternatives')
      expect(typeof result.selectedId).toBe('string')
      expect(typeof result.confidence).toBe('number')
      expect(typeof result.reasoning).toBe('string')
      expect(Array.isArray(result.alternatives)).toBe(true)
    })

    it('includes memory context in AI prompt', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)
      const memoryContext: MemoryContext = {
        relevantMemories: [
          {
            text: 'Previous mapping: VAV-*_ZoneTemp -> vav-reheat',
            score: 0.9,
          },
        ],
      }

      mockGenerator.generate.mockResolvedValue(createMockSuggestion())

      await engine.generateStepSuggestion({
        step: 'system',
        point: createTestPoint(),
        candidates: ['vav-reheat-system'],
        memoryContext,
      })

      expect(mockGenerator.generate).toHaveBeenCalledWith(
        expect.objectContaining({
          prompt: expect.stringContaining(
            'Previous mapping: VAV-*_ZoneTemp -> vav-reheat'
          ),
        })
      )
    })

    it('includes rich point metadata in AI prompt', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)
      const point = createTestPoint({
        name: 'AHU-1_SupplyFanStatus',
        objectType: 'binary-input',
        description: 'Supply Fan Running Status',
        units: 'noUnits',
        stateText: ['Off', 'On'],
      })

      mockGenerator.generate.mockResolvedValue(createMockSuggestion())

      await engine.generateStepSuggestion({
        step: 'system',
        point,
        candidates: ['ahu-system'],
        memoryContext: { relevantMemories: [] },
      })

      expect(mockGenerator.generate).toHaveBeenCalledWith(
        expect.objectContaining({
          prompt: expect.stringContaining('AHU-1_SupplyFanStatus'),
        })
      )
      expect(mockGenerator.generate).toHaveBeenCalledWith(
        expect.objectContaining({
          prompt: expect.stringContaining('binary-input'),
        })
      )
      expect(mockGenerator.generate).toHaveBeenCalledWith(
        expect.objectContaining({
          prompt: expect.stringContaining('Supply Fan Running Status'),
        })
      )
    })

    it('includes selection context for device step', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)

      mockGenerator.generate.mockResolvedValue(createMockSuggestion())

      await engine.generateStepSuggestion({
        step: 'device',
        point: createTestPoint(),
        candidates: ['sensor-device'],
        memoryContext: { relevantMemories: [] },
        selectionContext: { systemId: 'selected-system-id' },
      })

      expect(mockGenerator.generate).toHaveBeenCalledWith(
        expect.objectContaining({
          prompt: expect.stringContaining('selected-system-id'),
        })
      )
    })

    it('includes selection context for property step', async () => {
      const mockGenerator = createMockGenerator()
      const engine = new SuggestionEngine(mockGenerator)

      mockGenerator.generate.mockResolvedValue(createMockSuggestion())

      await engine.generateStepSuggestion({
        step: 'property',
        point: createTestPoint(),
        candidates: ['property-1'],
        memoryContext: { relevantMemories: [] },
        selectionContext: {
          systemId: 'selected-system',
          deviceId: 'selected-device',
        },
      })

      expect(mockGenerator.generate).toHaveBeenCalledWith(
        expect.objectContaining({
          prompt: expect.stringContaining('selected-system'),
        })
      )
      expect(mockGenerator.generate).toHaveBeenCalledWith(
        expect.objectContaining({
          prompt: expect.stringContaining('selected-device'),
        })
      )
    })
  })
})
