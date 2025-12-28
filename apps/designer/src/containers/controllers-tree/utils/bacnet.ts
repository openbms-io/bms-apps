import type { ControllerPoint } from '@/lib/domain/models/controller-point'
import {
  type BacnetConfig,
  type BacnetObjectType,
  convertStatusFlagsToIndividualProperties,
} from '@/types/infrastructure'

export function convertPointToBacnetConfig({
  point,
  iotDeviceId,
}: {
  point: ControllerPoint
  iotDeviceId: string
}): BacnetConfig {
  const statusFlags = convertStatusFlagsToIndividualProperties({
    statusFlags: point.metadata?.statusFlags,
  })

  return {
    pointId: point.id,
    objectType: point.pointType as BacnetObjectType,
    objectId: point.instanceNumber,
    supervisorId: iotDeviceId,
    controllerId: point.controllerId,
    discoveredProperties: {
      ...(point.metadata || {}),
      units: point.units ?? point.metadata?.units,
      description: point.description ?? point.metadata?.description,
      inAlarm: statusFlags.inAlarm,
      fault: statusFlags.fault,
      overridden: statusFlags.overridden,
      outOfService: statusFlags.outOfService,
    },
    name: point.pointName,
  }
}
