export type GetConfigPayload = {
  urlToUploadConfig: string
  jwtToken: string
  iotDeviceControllers: Array<{
    id: string
    ipAddress: string
    port: number
    deviceId: number
    networkNumber?: number
    macAddress?: string
  }>
  bacnetReaders: Array<{
    id: string
    ipAddress: string
    port: number
    deviceId: number
    networkNumber?: number
    macAddress?: string
    isActive: boolean
  }>
}
