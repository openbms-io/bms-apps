import { useState, useCallback } from 'react'
import type { IotDeviceController } from '@/lib/domain/models/iot-device-controller'
import type { ControllerPoint } from '@/lib/domain/models/controller-point'
import type { BACnetPointData, BACnetControllerData } from '../schemas'

interface CreateSemanticModalState {
  point: BACnetPointData | null
  controller: BACnetControllerData | null
  isOpen: boolean
}

export function useCreateSemanticModal(
  controllers: IotDeviceController[],
  pointsByController: Record<string, ControllerPoint[]>,
  iotDeviceId: string | undefined
) {
  const [state, setState] = useState<CreateSemanticModalState>({
    point: null,
    controller: null,
    isOpen: false,
  })

  const openSemanticModal = useCallback(
    (nodeId: string) => {
      if (!iotDeviceId) {
        console.error('Cannot open semantic modal: iotDeviceId is undefined')
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
        console.error('Point or controller not found')
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

      setState({
        point: pointData,
        controller: controllerData,
        isOpen: true,
      })
    },
    [controllers, pointsByController, iotDeviceId]
  )

  const closeSemanticModal = useCallback(() => {
    setState({
      point: null,
      controller: null,
      isOpen: false,
    })
  }, [])

  return {
    semanticModalState: state,
    openSemanticModal,
    closeSemanticModal,
  }
}
