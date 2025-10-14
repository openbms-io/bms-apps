import { ControllerPoint } from '@/lib/domain/models/controller-point'
import { ApiResponse } from './utils'

export const controllerPointsApi = {
  async list({
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
  }): Promise<ControllerPoint[]> {
    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/controllers/${controllerId}/points`
    )
    const json: ApiResponse<{ points: ControllerPoint[] }> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch controller points')
    }

    return json.data.points
  },

  async listBatch({
    orgId,
    siteId,
    projectId,
    iotDeviceId,
    controllerIds,
  }: {
    orgId: string
    siteId: string
    projectId: string
    iotDeviceId: string
    controllerIds: string[]
  }): Promise<Record<string, ControllerPoint[]>> {
    if (controllerIds.length === 0) {
      return {}
    }

    const res = await fetch(
      `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/iot-devices/${iotDeviceId}/batch-points?controllerIds=${controllerIds.join(
        ','
      )}`
    )
    const json: ApiResponse<{
      pointsByController: Record<string, ControllerPoint[]>
    }> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch controller points')
    }

    return json.data.pointsByController
  },
}
