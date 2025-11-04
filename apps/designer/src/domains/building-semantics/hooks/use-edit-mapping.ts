import { useState, useCallback } from 'react'
import type { IotDeviceController } from '@/lib/domain/models/iot-device-controller'
import type { ControllerPoint } from '@/lib/domain/models/controller-point'
import type {
  SemanticEquipment,
  BACnetPointData,
  BACnetControllerData,
} from '../adapters/ashrae-223p/schemas'
import { createCompositeKey } from '../utils/bacnet-keys'

interface EditMappingState {
  point: BACnetPointData | null
  controller: BACnetControllerData | null
  mapping: SemanticEquipment | null
  isOpen: boolean
}

export function useEditMapping(
  projectId: string,
  controllers: IotDeviceController[],
  pointsByController: Record<string, ControllerPoint[]>,
  semanticMappings: Map<string, SemanticEquipment>,
  iotDeviceId: string | undefined
) {
  const [editState, setEditState] = useState<EditMappingState>({
    point: null,
    controller: null,
    mapping: null,
    isOpen: false,
  })

  const openEdit = useCallback(
    (nodeId: string) => {
      if (!iotDeviceId) {
        console.error('Cannot open edit modal: iotDeviceId is undefined')
        return
      }

      let foundPoint: ControllerPoint | null = null
      let foundController: IotDeviceController | null = null

      for (const controller of controllers) {
        const points = pointsByController[controller.id] || []
        const point = points.find((p) => p.id === nodeId)
        if (point) {
          foundPoint = point
          foundController = controller
          break
        }
      }

      if (!foundPoint || !foundController) {
        console.error('Point or controller not found for edit')
        return
      }

      const compositeKey = createCompositeKey(
        foundController.deviceId,
        foundPoint.pointType,
        foundPoint.instanceNumber
      )
      const mapping = semanticMappings.get(compositeKey)

      if (!mapping) {
        console.error('Mapping not found for point')
        return
      }

      const pointData: BACnetPointData = {
        pointId: foundPoint.id,
        objectType: foundPoint.pointType,
        objectId: foundPoint.instanceNumber,
        supervisorId: iotDeviceId,
        controllerId: foundPoint.controllerId,
        name: foundPoint.pointName,
        discoveredProperties: foundPoint.metadata,
      }

      const controllerData: BACnetControllerData = {
        deviceId: foundController.deviceId,
        controllerId: foundController.id,
        name: foundController.name,
      }

      setEditState({
        point: pointData,
        controller: controllerData,
        mapping,
        isOpen: true,
      })
    },
    [controllers, pointsByController, semanticMappings, iotDeviceId]
  )

  const closeEdit = useCallback(() => {
    setEditState({
      point: null,
      controller: null,
      mapping: null,
      isOpen: false,
    })
  }, [])

  return { editState, openEdit, closeEdit }
}
