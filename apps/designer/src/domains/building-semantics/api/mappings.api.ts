import type { SemanticEquipment } from '../adapters/ashrae-223p/schemas'

const STORAGE_KEY_PREFIX = '223p-mappings-'

function getStorageKey(projectId: string): string {
  return `${STORAGE_KEY_PREFIX}${projectId}`
}

export const semanticMappingsApi = {
  async listMappings(
    projectId: string
  ): Promise<Map<string, SemanticEquipment>> {
    const key = getStorageKey(projectId)
    const stored = sessionStorage.getItem(key)

    if (!stored) return new Map()

    try {
      const data = JSON.parse(stored) as Record<string, SemanticEquipment>
      return new Map(Object.entries(data))
    } catch {
      return new Map()
    }
  },

  async getMapping(
    projectId: string,
    compositeKey: string
  ): Promise<SemanticEquipment | null> {
    const mappings = await this.listMappings(projectId)
    return mappings.get(compositeKey) || null
  },

  async createMapping(
    projectId: string,
    pointId: string,
    mapping: SemanticEquipment
  ): Promise<SemanticEquipment> {
    const mappings = await this.listMappings(projectId)

    const compositeKey = mapping.externalReference.compositeKey
    if (!compositeKey) {
      throw new Error(
        'Cannot create mapping: missing deviceIdentifier or objectIdentifier'
      )
    }

    mappings.set(compositeKey, mapping)

    const key = getStorageKey(projectId)
    const data = Object.fromEntries(mappings)
    sessionStorage.setItem(key, JSON.stringify(data))

    return mapping
  },

  async updateMapping(
    projectId: string,
    pointId: string,
    mapping: SemanticEquipment
  ): Promise<SemanticEquipment> {
    return this.createMapping(projectId, pointId, mapping)
  },

  async deleteMapping(projectId: string, compositeKey: string): Promise<void> {
    const mappings = await this.listMappings(projectId)
    mappings.delete(compositeKey)

    const key = getStorageKey(projectId)
    const data = Object.fromEntries(mappings)
    sessionStorage.setItem(key, JSON.stringify(data))
  },

  async clearAllMappings(projectId: string): Promise<void> {
    const key = getStorageKey(projectId)
    sessionStorage.removeItem(key)
  },
}
