import { QueryClient } from '@tanstack/react-query'

export function createQueryClient(): QueryClient {
  return new QueryClient({
    defaultOptions: {
      queries: {
        staleTime: 5 * 60 * 1000,
        gcTime: 10 * 60 * 1000,
        retry: 3,
        retryDelay: (attemptIndex) => Math.min(1000 * 2 ** attemptIndex, 30000),
        refetchOnWindowFocus: process.env.NODE_ENV === 'production',
        refetchOnMount: false,
      },
      mutations: {
        retry: 2,
        retryDelay: 1000,
      },
    },
  })
}

type QueryParams = Record<string, string | number | boolean | undefined | null>

export const queryKeys = {
  organizations: {
    all: ['organizations'] as const,
    lists: () => [...queryKeys.organizations.all, 'list'] as const,
  },
  sites: {
    all: ['sites'] as const,
    byOrg: (orgId: string) => [...queryKeys.sites.all, 'org', orgId] as const,
  },
  projects: {
    all: ['projects'] as const,
    lists: () => [...queryKeys.projects.all, 'list'] as const,
    list: (params?: QueryParams) =>
      [...queryKeys.projects.lists(), params] as const,
    details: () => [...queryKeys.projects.all, 'detail'] as const,
    detail: (id: string) => [...queryKeys.projects.details(), id] as const,
  },
  iotDevices: {
    all: ['iotDevices'] as const,
    details: () => [...queryKeys.iotDevices.all, 'detail'] as const,
    detail: (id: string) => [...queryKeys.iotDevices.details(), id] as const,
  },
} as const
