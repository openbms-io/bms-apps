import 'server-only'

import { MemoryClient } from 'mem0ai'
import { type StepType } from '@/domains/building-semantics/adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas'
import {
  MappingMessageFormatter,
  type IMappingMessageFormatter,
} from './mapping-message-formatter'

export interface MemoryContext {
  relevantMemories: Array<{
    text: string
    score: number
  }>
}

export interface MappingRecord {
  pointPattern: string
  controllerId: string
  step: StepType
  selectedId: string
  wasOverridden: boolean
}

export function createMemoryClient(): MemoryClient {
  const apiKey = process.env.MEM0_API_KEY
  if (!apiKey) {
    throw new Error('MEM0_API_KEY environment variable is required')
  }
  return new MemoryClient({ apiKey })
}

export class MemoryManager {
  private readonly client: MemoryClient
  private readonly formatter: IMappingMessageFormatter

  constructor(
    client: MemoryClient,
    formatter: IMappingMessageFormatter = new MappingMessageFormatter()
  ) {
    this.client = client
    this.formatter = formatter
  }

  async retrieveContext({
    orgId,
    query,
    projectId,
  }: {
    orgId: string
    query: string
    projectId?: string
  }): Promise<MemoryContext> {
    const start = performance.now()

    const memories = await this.client.search(query, {
      user_id: orgId,
      ...(projectId && { metadata: { projectId } }),
    })
    const duration = performance.now() - start
    console.log(`[Mem0] retrieveContext took ${duration.toFixed(0)}ms`)

    console.log(`[Mem0] retrieveContext found ${memories.length} results`)

    const relevantMemories = memories
      .filter((memory) => memory.memory !== undefined)
      .map((memory) => ({
        text: memory.memory,
        score: memory.score ?? 0,
      })) as MemoryContext['relevantMemories']

    return {
      relevantMemories,
    }
  }

  async storeMapping({
    orgId,
    mapping,
    projectId,
  }: {
    orgId: string
    mapping: MappingRecord
    projectId?: string
  }): Promise<void> {
    const message = this.formatter.formatMessage({ mapping })
    const metadata = this.formatter.formatMetadata({ mapping, projectId })

    await this.client.add([{ role: 'user', content: message }], {
      user_id: orgId,
      metadata,
    })
  }
}
