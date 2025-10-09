import { NextRequest, NextResponse } from 'next/server'
import { handleApiError } from '@/lib/api/error-handler'
import { projectsRepository } from '@/lib/db/models/projects'
import { ProjectRouteParamsSchema, CreateIotDeviceSchema } from './schemas'

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

    const iotDevice = await projectsRepository.createIotDeviceForProject({
      projectId: routeParams.projectId,
      orgId: routeParams.orgId,
      siteId: routeParams.siteId,
      name,
      description,
    })

    const response = {
      success: true,
      iot_device: iotDevice,
    }

    return NextResponse.json(response, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create IoT device')
  }
}
