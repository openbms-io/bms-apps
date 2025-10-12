import { ApiResponse } from './utils'

export type GetConfigPayload = {
  urlToUploadConfig: string
  jwtToken: string
  iotDeviceControllers: Array<{
    id: string
    ipAddress: string
    port: number
    controllerDeviceId: number
  }>
  bacnetReaders: Array<{
    id: string
    ipAddress: string
    port: number
    deviceId: number
    subnetMask: number
    bbmdEnabled: boolean
    bbmdServerIp?: string
    isActive: boolean
  }>
}

export const getConfigPayloadApi = {
  async fetch({
    orgId,
    siteId,
    projectId,
    iotDeviceId,
  }: {
    orgId: string
    siteId: string
    projectId: string
    iotDeviceId: string
  }): Promise<GetConfigPayload> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/get-config-payload`
    )
    const json: ApiResponse<{ payload: GetConfigPayload }> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch config payload')
    }

    return json.data.payload
  },
}
