import { useQuery } from '@tanstack/react-query'
import { getTemplatesApiV1223pTemplatesGet } from '../generated'

export function useTemplatesQuery() {
  return useQuery({
    queryKey: ['templates'],
    queryFn: async () => {
      const response = await getTemplatesApiV1223pTemplatesGet()
      return response.data?.systems ?? []
    },
    staleTime: 5 * 60 * 1000,
    retry: 3,
  })
}
