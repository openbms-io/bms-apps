import { IotDevice } from '@/lib/domain/models/iot-device'

interface ApiResponse<T> {
  success: boolean
  error?: string
  data?: {
    iotDevice: T
  }
}

export const iotDevicesApi = {
  async get(
    orgId: string,
    siteId: string,
    projectId: string,
    id: string
  ): Promise<IotDevice> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${id}`
    )
    const json: ApiResponse<IotDevice> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch IoT device')
    }

    if (!json.data?.iotDevice) {
      throw new Error('IoT device not found in response')
    }

    return json.data.iotDevice
  },

  async createForProject(params: {
    orgId: string
    siteId: string
    projectId: string
    name: string
    description?: string
  }): Promise<IotDevice> {
    const res = await fetch(
      `/api/organizations/${params.orgId}/sites/${params.siteId}/projects/${params.projectId}/iot-devices`,
      {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          name: params.name,
          description: params.description,
        }),
      }
    )
    const json: ApiResponse<IotDevice> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to create IoT device')
    }

    if (!json.data?.iotDevice) {
      throw new Error('IoT device not found in response')
    }

    return json.data.iotDevice
  },
}
