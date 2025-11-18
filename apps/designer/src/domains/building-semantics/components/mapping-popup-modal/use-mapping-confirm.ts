import { useCallback } from 'react'
import type { BACnetPointData, BACnetControllerData, SemanticEquipment } from '../../adapters/ashrae-223p/schemas'
import { useCreateEquipmentMapping } from '../../view-models/use-create-equipment-mapping'
import type { FormState } from './use-mapping-form-state'
import type { TemplateOption } from './use-template-options'
import {
  createCompositeKeyForPoint,
  createExternalReference,
  determinePropertyType,
} from './mapping-helpers'

export function useMappingConfirm(
  projectId: string,
  point: BACnetPointData | undefined,
  controller: BACnetControllerData | undefined,
  observableProperties: TemplateOption[]
) {
  const { execute: createMapping } = useCreateEquipmentMapping(projectId)

  const confirmMapping = useCallback(
    async (formData: FormState): Promise<SemanticEquipment | undefined> => {
      if (!point) return undefined

      const compositeKey = createCompositeKeyForPoint(point, controller)
      const propertyType = determinePropertyType(
        formData.observableProperty,
        observableProperties
      )

      const mapping = await createMapping({
        projectId,
        pointId: compositeKey,
        equipmentTypeId: formData.equipmentType,
        deviceTypeId: formData.deviceType,
        propertyId: formData.observableProperty,
        propertyType,
        physicalSpaceName: formData.physicalSpaceName,
        domainSpaceNames: formData.domainSpaceNames,
        externalReference: createExternalReference(point, controller),
      })

      return mapping
    },
    [point, controller, projectId, createMapping, observableProperties]
  )

  return { confirmMapping }
}
