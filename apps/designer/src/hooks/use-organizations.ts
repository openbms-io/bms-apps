import { useQuery, UseQueryOptions } from '@tanstack/react-query'
import { Organization } from '@/lib/db/schema'
import { organizationsApi } from '@/lib/api/organizations'
import { queryKeys } from '@/lib/query-client'

export function useOrganizations(
  options?: Omit<UseQueryOptions<Organization[]>, 'queryKey' | 'queryFn'>
): ReturnType<typeof useQuery<Organization[]>> {
  return useQuery({
    queryKey: queryKeys.organizations.all,
    queryFn: () => organizationsApi.list(),
    ...options,
  })
}
