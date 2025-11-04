import { useCreateMappingMutation } from '../api/queries/use-mappings-query'
import {
  useCreateSpaceMutation,
  useAddPointToSpaceMutation,
} from '../api/queries/use-spaces-query'
import { spaces223pApi } from '../api/spaces.api'
import type { CreateMappingParams } from './types'
import { SemanticEquipmentSchema, type SemanticEquipment } from '../schemas'

export function useCreateEquipmentMapping() {
  const createMapping = useCreateMappingMutation()
  const createSpace = useCreateSpaceMutation()
  const addPointToSpace = useAddPointToSpaceMutation()

  const execute = async (
    params: CreateMappingParams
  ): Promise<SemanticEquipment> => {
    let physicalSpaceId: string | undefined
    const domainSpaceIds: string[] = []

    if (params.physicalSpaceName?.trim()) {
      const existingSpace = await spaces223pApi.searchSpace(
        params.projectId,
        params.physicalSpaceName
      )

      if (existingSpace) {
        physicalSpaceId = existingSpace.id
        await addPointToSpace.mutateAsync({
          projectId: params.projectId,
          spaceId: existingSpace.id,
          pointId: params.pointId,
        })
      } else {
        const newSpace = await createSpace.mutateAsync({
          projectId: params.projectId,
          rdfsLabel: params.physicalSpaceName.trim(),
          spaceType: 'PhysicalSpace',
        })
        physicalSpaceId = newSpace.id
        await addPointToSpace.mutateAsync({
          projectId: params.projectId,
          spaceId: newSpace.id,
          pointId: params.pointId,
        })
      }
    }

    if (params.domainSpaceNames) {
      for (const domainSpaceName of params.domainSpaceNames) {
        if (domainSpaceName.trim()) {
          const existingSpace = await spaces223pApi.searchSpace(
            params.projectId,
            domainSpaceName
          )

          if (existingSpace) {
            domainSpaceIds.push(existingSpace.id)
            await addPointToSpace.mutateAsync({
              projectId: params.projectId,
              spaceId: existingSpace.id,
              pointId: params.pointId,
            })
          } else {
            const newSpace = await createSpace.mutateAsync({
              projectId: params.projectId,
              rdfsLabel: domainSpaceName.trim(),
              spaceType: 'DomainSpace',
            })
            domainSpaceIds.push(newSpace.id)
            await addPointToSpace.mutateAsync({
              projectId: params.projectId,
              spaceId: newSpace.id,
              pointId: params.pointId,
            })
          }
        }
      }
    }

    const mappingInput = {
      equipmentType: params.equipmentType as never,
      physicalSpaceId,
      domainSpaceIds: domainSpaceIds.length > 0 ? domainSpaceIds : undefined,
      deviceType: params.deviceType as never,
      observableProperty: params.observableProperty as never,
      propertyType: params.propertyType,
      externalReference: {
        deviceIdentifier: params.externalReference.deviceIdentifier,
        deviceName: params.externalReference.deviceName,
        objectIdentifier: params.externalReference.objectIdentifier,
        objectName: params.externalReference.objectName,
        propertyIdentifier: params.externalReference.propertyIdentifier,
        propertyArrayIndex: params.externalReference.propertyArrayIndex,
        priorityForWriting: params.externalReference.priorityForWriting,
      },
      schemaVersion: '223p-2023' as const,
    }

    const mapping = SemanticEquipmentSchema.parse(mappingInput)

    const result = await createMapping.mutateAsync({
      projectId: params.projectId,
      pointId: params.pointId,
      mapping,
    })

    return result
  }

  return {
    execute,
    isLoading:
      createMapping.isPending ||
      createSpace.isPending ||
      addPointToSpace.isPending,
    error: createMapping.error || createSpace.error || addPointToSpace.error,
  }
}
