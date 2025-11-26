import { useMutation, useQueryClient } from '@tanstack/react-query'
import { createOrUpdateReferenceApiV1ProjectsProjectIdBacnetReferencesBacnetPointIdPut } from '../generated'
import type { BuildingSemanticsBacnetConfig } from '../../types'

interface SaveBacnetReferenceParams {
  projectId: string
  bacnetPointId: string
  propertyUri: string
  buildingSemanticsBacnetConfig: BuildingSemanticsBacnetConfig
}

export function useSaveBacnetReferenceMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    retry: false,
    mutationFn: async ({
      projectId,
      bacnetPointId,
      propertyUri,
      buildingSemanticsBacnetConfig,
    }: SaveBacnetReferenceParams) => {
      // Construct ASHRAE 223P BACnet identifiers from config
      // TODO: Move this logic to backend API.
      const deviceIdentifier = `device,${buildingSemanticsBacnetConfig.controllerDeviceId}`
      const objectIdentifier = `${buildingSemanticsBacnetConfig.objectType},${buildingSemanticsBacnetConfig.objectId}`
      const externalIdentifier = `${buildingSemanticsBacnetConfig.controllerIPAddress}:device,${buildingSemanticsBacnetConfig.controllerDeviceId}:${buildingSemanticsBacnetConfig.objectType},${buildingSemanticsBacnetConfig.objectId}`

      const response =
        await createOrUpdateReferenceApiV1ProjectsProjectIdBacnetReferencesBacnetPointIdPut(
          {
            path: {
              project_id: projectId,
              bacnet_point_id: bacnetPointId,
            },
            body: {
              propertyUri,
              deviceIdentifier,
              objectIdentifier,
              externalIdentifier,
            },
          }
        )

      if (response.error) {
        throw response.error
      }

      return response.data
    },
    onSuccess: (_, { projectId, bacnetPointId }) => {
      queryClient.invalidateQueries({
        queryKey: ['bacnetReference', projectId, bacnetPointId],
      })
      queryClient.invalidateQueries({
        queryKey: ['bacnetReferences', projectId],
      })
    },
  })
}
