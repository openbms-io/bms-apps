import { useMappingsQuery } from '../api/queries/use-mappings-query'
import { useTemplatesQuery } from '../api/queries/use-templates-query'
import { mapMappingsResponseToMap } from './mappers/mappings-mapper'

export function useMappingsViewModel({
  projectId,
}: {
  projectId: string | undefined
}) {
  const {
    data,
    isLoading: mappingsLoading,
    error,
  } = useMappingsQuery(projectId)
  const { data: templates, isLoading: templatesLoading } = useTemplatesQuery()

  const isLoading = mappingsLoading || templatesLoading

  const mappedData = data
    ? mapMappingsResponseToMap({ response: data, templates })
    : new Map()

  return {
    data: mappedData,
    isLoading,
    error,
  }
}
