import 'server-only'

import {
  MemoryManager,
  createMemoryClient,
  type MappingRecord,
} from './memory-manager'
import {
  SuggestionEngine,
  createObjectGenerator,
  type StepSuggestion,
  type AIPointContext,
  type AICandidate,
  type StepType,
} from './suggestion-engine'

export interface IAISuggestionService {
  getSuggestion(params: {
    step: StepType
    orgId: string
    projectId?: string
    point: AIPointContext['point']
    candidates: AICandidate[]
    selectionContext?: { systemId?: string; deviceId?: string }
  }): Promise<StepSuggestion>

  confirmMapping(params: {
    orgId: string
    projectId?: string
    mapping: MappingRecord
  }): Promise<void>
}

export class AISuggestionService implements IAISuggestionService {
  private readonly memoryManager: MemoryManager
  private readonly suggestionEngine: SuggestionEngine

  constructor(
    memoryManager: MemoryManager,
    suggestionEngine: SuggestionEngine
  ) {
    this.memoryManager = memoryManager
    this.suggestionEngine = suggestionEngine
  }

  async getSuggestion({
    step,
    orgId,
    projectId,
    point,
    candidates,
    selectionContext,
  }: {
    step: StepType
    orgId: string
    projectId?: string
    point: AIPointContext['point']
    candidates: AICandidate[]
    selectionContext?: { systemId?: string; deviceId?: string }
  }): Promise<StepSuggestion> {
    const query = this.buildMemoryQuery(point)

    const memoryContext = await this.memoryManager.retrieveContext({
      orgId,
      query,
      projectId,
    })

    return this.suggestionEngine.generateStepSuggestion({
      step,
      point,
      candidates,
      memoryContext,
      selectionContext,
    })
  }

  async confirmMapping({
    orgId,
    projectId,
    mapping,
  }: {
    orgId: string
    projectId?: string
    mapping: MappingRecord
  }): Promise<void> {
    return this.memoryManager.storeMapping({
      orgId,
      mapping,
      projectId,
    })
  }

  private buildMemoryQuery(point: AIPointContext['point']): string {
    const parts = [point.name, point.objectType]

    if (point.description) {
      parts.push(point.description)
    }

    return parts.join(' ')
  }
}

export function createAISuggestionService(): IAISuggestionService {
  const memoryClient = createMemoryClient()
  const memoryManager = new MemoryManager(memoryClient)

  const objectGenerator = createObjectGenerator()
  const suggestionEngine = new SuggestionEngine(objectGenerator)

  return new AISuggestionService(memoryManager, suggestionEngine)
}
