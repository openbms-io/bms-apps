import type { IotDeviceController } from '../models/iot-device-controller'
import type { BacnetReader } from '../models/bacnet-reader'

export const GetConfigPayloadMapper = {
  toControllerDTO(controller: IotDeviceController) {
    return {
      id: controller.id,
      ipAddress: controller.ipAddress,
      port: controller.port,
      controllerDeviceId: controller.deviceId,
    }
  },

  toReaderDTO(reader: BacnetReader) {
    return {
      id: reader.id,
      ipAddress: reader.ipAddress,
      port: reader.port,
      deviceId: reader.deviceId,
      subnetMask: reader.subnetMask,
      bbmdEnabled: reader.bbmdEnabled,
      bbmdServerIp: reader.bbmdServerIp,
      isActive: reader.isActive,
    }
  },
}
