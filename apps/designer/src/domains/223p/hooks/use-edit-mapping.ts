import { useState, useCallback } from 'react'
import type { IotDeviceController } from '@/lib/domain/models/iot-device-controller'
import type { ControllerPoint } from '@/lib/domain/models/controller-point'
import type {
  Equipment223PDTO,
  BACnetPointData,
  BACnetControllerData,
} from '../schemas'
import { createCompositeKey } from '../utils/bacnet-keys'

interface EditMappingState {
  point: BACnetPointData | null
  controller: BACnetControllerData | null
  mapping: Equipment223PDTO | null
  isOpen: boolean
}

export function useEditMapping(
  projectId: string,
  controllers: IotDeviceController[],
  pointsByController: Record<string, ControllerPoint[]>,
  mappings223p: Map<string, Equipment223PDTO>,
  iotDeviceId: string
) {
  const [editState, setEditState] = useState<EditMappingState>({
    point: null,
    controller: null,
    mapping: null,
    isOpen: false,
  })

  const openEdit = useCallback(
    (nodeId: string) => {
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
      const mapping = mappings223p.get(compositeKey)

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
    [controllers, pointsByController, mappings223p, iotDeviceId]
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
