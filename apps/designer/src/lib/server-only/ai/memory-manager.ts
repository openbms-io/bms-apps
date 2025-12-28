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

export interface IMemoryClient {
  search(
    query: string,
    filters: Record<string, unknown>
  ): Promise<{ results: Array<{ memory: string; score: number }> }>
  add(
    messages: Array<{ role: string; content: string }>,
    options: Record<string, unknown>
  ): Promise<{ id: string }>
}

export function createMemoryClient(): IMemoryClient {
  const apiKey = process.env.MEM0_API_KEY
  if (!apiKey) {
    throw new Error('MEM0_API_KEY environment variable is required')
  }
  return new MemoryClient({ apiKey }) as IMemoryClient
}

export class MemoryManager {
  private readonly client: IMemoryClient
  private readonly formatter: IMappingMessageFormatter

  constructor(
    client: IMemoryClient,
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
    const filters: Record<string, unknown> = { user_id: orgId }

    if (projectId) {
      filters.metadata = { projectId }
    }

    const response = await this.client.search(query, filters)
    const duration = performance.now() - start
    console.log(`[Mem0] retrieveContext took ${duration.toFixed(0)}ms`)

    return {
      relevantMemories: (response.results || []).map((result) => ({
        text: result.memory,
        score: result.score,
      })),
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
