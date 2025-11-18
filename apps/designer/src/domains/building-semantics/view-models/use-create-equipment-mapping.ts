import { useSaveMappingsMutation } from '../api/mutations/use-save-mappings-mutation'
import { useMappingsViewModel } from './use-mappings-view-model'
import { useCreateSpaceMutation } from '../api/mutations/use-create-space-mutation'
import type { CreateMappingParams } from './types'
import {
  SemanticEquipmentSchema,
  type SemanticEquipment,
} from '../adapters/ashrae-223p/schemas'
import type { SemanticMappingDto } from '../api/generated'

export function useCreateEquipmentMapping(projectId: string | undefined) {
  const saveMappings = useSaveMappingsMutation()
  const { data: currentMappings } = useMappingsViewModel({ projectId })
  const createSpace = useCreateSpaceMutation()

  const execute = async (
    params: CreateMappingParams
  ): Promise<SemanticEquipment> => {
    let physicalSpaceId: string | undefined

    if (params.physicalSpaceName?.trim()) {
      const newSpace = await createSpace.mutateAsync({
        projectId: params.projectId,
        label: params.physicalSpaceName.trim(),
        spaceTypeId: 'urn:223p:PhysicalSpace',
      })
      physicalSpaceId = newSpace?.id
    }

    const mappingInput = {
      equipmentTypeId: params.equipmentTypeId,
      physicalSpaceId,
      domainSpaceIds: [],
      deviceTypeId: params.deviceTypeId,
      propertyId: params.propertyId,
      propertyType: params.propertyType,
      externalReference: {
        compositeKey: params.pointId,
        deviceIdentifier: params.externalReference.deviceIdentifier,
        objectIdentifier: params.externalReference.objectIdentifier,
        objectName: params.externalReference.objectName,
        propertyIdentifier: params.externalReference.propertyIdentifier,
      },
      schemaVersion: '223p-2023' as const,
    }

    const mapping = SemanticEquipmentSchema.parse(mappingInput)

    const newMappingDto: SemanticMappingDto = {
      equipmentTypeId: params.equipmentTypeId,
      deviceTypeId: params.deviceTypeId,
      propertyId: params.propertyId,
      spaceId: physicalSpaceId ?? null,
    }

    const currentMappingsRecord: Record<string, SemanticMappingDto> = {}
    if (currentMappings) {
      currentMappings.forEach((value, key) => {
        currentMappingsRecord[key] = {
          equipmentTypeId: value.equipmentTypeId,
          deviceTypeId: value.deviceTypeId,
          propertyId: value.propertyId,
          spaceId: value.physicalSpaceId ?? null,
        }
      })
    }

    currentMappingsRecord[params.pointId] = newMappingDto

    await saveMappings.mutateAsync({
      projectId: params.projectId,
      mappings: currentMappingsRecord,
    })

    return mapping
  }

  return {
    execute,
    isLoading: saveMappings.isPending || createSpace.isPending,
    error: saveMappings.error || createSpace.error,
  }
}
