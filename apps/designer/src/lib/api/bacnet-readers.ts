import {
  BacnetReader,
  CreateBacnetReader,
} from '@/lib/domain/models/bacnet-reader'
import { ApiResponse } from './utils'

export const bacnetReadersApi = {
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
  }): Promise<BacnetReader[]> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/bacnet-readers`
    )
    const json: ApiResponse<{ readers: BacnetReader[] }> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch readers')
    }

    return json.data.readers
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
    data: Omit<CreateBacnetReader, 'organizationId' | 'siteId' | 'iotDeviceId'>
  }): Promise<BacnetReader> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/bacnet-readers`,
      {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(data),
      }
    )
    const json: ApiResponse<{ reader: BacnetReader }> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to create reader')
    }

    return json.data.reader
  },

  async delete({
    orgId,
    siteId,
    projectId,
    iotDeviceId,
    readerId,
  }: {
    orgId: string
    siteId: string
    projectId: string
    iotDeviceId: string
    readerId: string
  }): Promise<void> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/bacnet-readers/${readerId}`,
      { method: 'DELETE' }
    )
    const json: { success: boolean; error?: string } = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to delete reader')
    }
  },
}
