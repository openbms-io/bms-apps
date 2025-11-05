const all = ['building-semantics'] as const

export const semanticQueryKeys = {
  all,

  mappings: {
    all: [...all, 'mappings'] as const,
    list: (projectId: string) =>
      [...all, 'mappings', 'list', projectId] as const,
    detail: (projectId: string, pointName: string) =>
      [...all, 'mappings', 'detail', projectId, pointName] as const,
  },

  spaces: {
    all: [...all, 'spaces'] as const,
    list: (projectId: string) => [...all, 'spaces', 'list', projectId] as const,
  },

  templates: {
    all: [...all, 'templates'] as const,
    equipmentTypes: () => [...all, 'templates', 'equipment'] as const,
    deviceTypes: () => [...all, 'templates', 'devices'] as const,
    observableProperties: () => [...all, 'templates', 'properties'] as const,
  },

  aiSuggestions: {
    all: [...all, 'ai-suggestions'] as const,
    detail: (pointId: string, projectId: string) =>
      [...all, 'ai-suggestions', 'detail', pointId, projectId] as const,
  },
} as const
