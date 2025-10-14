import { NextRequest, NextResponse } from 'next/server'
import { handleApiError } from '@/lib/api/error-handler'
import { projectsRepository } from '@/lib/db/models/projects'
import { ProjectRouteParamsSchema, CreateIotDeviceSchema } from './schemas'
import { IotDeviceMapper } from '@/lib/domain/mappers/iot-device.mapper'

export async function POST(
  request: NextRequest,
  {
    params,
  }: { params: Promise<{ orgId: string; siteId: string; projectId: string }> }
): Promise<NextResponse> {
  try {
    const routeParams = ProjectRouteParamsSchema.parse(await params)
    const body = await request.json()
    const { name, description } = CreateIotDeviceSchema.parse(body)

    const dbIotDevice = await projectsRepository.createIotDeviceForProject({
      projectId: routeParams.projectId,
      orgId: routeParams.orgId,
      siteId: routeParams.siteId,
      name,
      description,
    })

    const data = {
      iotDevice: IotDeviceMapper.toDTO({
        ...dbIotDevice,
        description: dbIotDevice.description ?? null,
      }),
    }

    const response = {
      success: true,
      data,
    }

    return NextResponse.json(response, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create IoT device')
  }
}
