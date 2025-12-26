import 'server-only'

import { MemoryClient } from 'mem0ai'

export interface MemoryContext {
  relevantMemories: Array<{
    text: string
    score: number
  }>
}

export interface MappingRecord {
  pointPattern: string
  controllerId: string
  step: 'system' | 'device' | 'property'
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

  constructor(client: IMemoryClient) {
    this.client = client
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
    const filters: Record<string, unknown> = { org_id: orgId }

    if (projectId) {
      filters.metadata = { projectId }
    }

    const response = await this.client.search(query, filters)

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
    const overrideText = mapping.wasOverridden
      ? 'User overrode AI suggestion.'
      : 'AI suggestion was accepted.'

    const message = `Mapping decision: Points matching pattern "${mapping.pointPattern}" from controller "${mapping.controllerId}" were mapped to "${mapping.selectedId}" at step "${mapping.step}". ${overrideText}`

    const metadata: Record<string, unknown> = {
      pointPattern: mapping.pointPattern,
      controllerId: mapping.controllerId,
      step: mapping.step,
      selectedId: mapping.selectedId,
      wasOverridden: mapping.wasOverridden,
    }

    if (projectId) {
      metadata.projectId = projectId
    }

    await this.client.add([{ role: 'user', content: message }], {
      org_id: orgId,
      metadata,
    })
  }
}
