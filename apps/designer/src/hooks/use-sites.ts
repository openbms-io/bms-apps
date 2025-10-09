import { useQuery, UseQueryOptions } from '@tanstack/react-query'
import { Site } from '@/lib/db/schema'
import { sitesApi } from '@/lib/api/sites'
import { queryKeys } from '@/lib/query-client'

export function useSites(
  orgId: string | undefined,
  options?: Omit<UseQueryOptions<Site[]>, 'queryKey' | 'queryFn'>
): ReturnType<typeof useQuery<Site[]>> {
  return useQuery({
    queryKey: queryKeys.sites.byOrg(orgId || ''),
    queryFn: () => sitesApi.listByOrg(orgId!),
    enabled: !!orgId,
    ...options,
  })
}
