import {
  IotDeviceController,
  CreateIotDeviceController,
} from '@/lib/domain/models/iot-device-controller'
import { ApiResponse } from './utils'

export const iotDeviceControllersApi = {
  async list({
    orgId,
    siteId,
    projectId,
    iotDeviceId,
  }: {
    orgId: string
    siteId: string
    projectId: string
    iotDeviceId: string
  }): Promise<IotDeviceController[]> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/controllers`
    )
    const json: ApiResponse<{ controllers: IotDeviceController[] }> =
      await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch controllers')
    }

    return json.data.controllers
  },

  async create({
    orgId,
    siteId,
    projectId,
    iotDeviceId,
    data,
  }: {
    orgId: string
    siteId: string
    projectId: string
    iotDeviceId: string
    data: Omit<
      CreateIotDeviceController,
      'organizationId' | 'siteId' | 'iotDeviceId'
    >
  }): Promise<IotDeviceController> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/controllers`,
      {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(data),
      }
    )
    const json: ApiResponse<{ controller: IotDeviceController }> =
      await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to create controller')
    }

    return json.data.controller
  },

  async delete({
    orgId,
    siteId,
    projectId,
    iotDeviceId,
    controllerId,
  }: {
    orgId: string
    siteId: string
    projectId: string
    iotDeviceId: string
    controllerId: string
  }): Promise<void> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/controllers/${controllerId}`,
      { method: 'DELETE' }
    )
    const json: { success: boolean; error?: string } = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to delete controller')
    }
  },
}
