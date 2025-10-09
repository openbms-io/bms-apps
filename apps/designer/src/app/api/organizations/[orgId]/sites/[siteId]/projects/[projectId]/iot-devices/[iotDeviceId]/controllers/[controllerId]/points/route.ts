import { NextRequest, NextResponse } from 'next/server'
import { controllerPointsRepository } from '@/lib/db/models/controller-points'
import { type InsertControllerPoint } from '@/lib/db/schema'
import {
  ControllerRouteParamsSchema,
  type ControllerRouteParams,
} from './schemas'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ControllerRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerRouteParamsSchema.parse(await params)
    const { controllerId } = validatedParams

    const points =
      await controllerPointsRepository.findByController(controllerId)

    return NextResponse.json({ points })
  } catch (error) {
    return handleApiError(error, 'fetch controller points')
  }
}

export async function POST(
  request: NextRequest,
  { params }: { params: Promise<ControllerRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerRouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId, controllerId } = validatedParams
    const body: Omit<
      InsertControllerPoint,
      'organization_id' | 'site_id' | 'iot_device_id' | 'controller_id'
    > = await request.json()

    const point = await controllerPointsRepository.create({
      ...body,
      organization_id: orgId,
      site_id: siteId,
      iot_device_id: iotDeviceId,
      controller_id: controllerId,
    })

    return NextResponse.json({ point }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create controller point')
  }
}
