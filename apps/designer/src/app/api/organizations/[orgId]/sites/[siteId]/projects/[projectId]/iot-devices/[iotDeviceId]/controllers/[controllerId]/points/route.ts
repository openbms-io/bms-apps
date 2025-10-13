import { NextRequest, NextResponse } from 'next/server'
import { controllerPointsRepository } from '@/lib/db/models/controller-points'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { type InsertControllerPoint } from '@/lib/db/schema'
import {
  ControllerRouteParamsSchema,
  type ControllerRouteParams,
} from './schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { ControllerPointMapper } from '@/lib/domain/mappers/controller-point.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ControllerRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerRouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId, controllerId } = validatedParams

    // Verify controller exists and ownership
    const controller =
      await iotDeviceControllersRepository.findById(controllerId)

    if (!controller) {
      return NextResponse.json(
        { error: 'Controller not found' },
        { status: 404 }
      )
    }

    const isOwner = await iotDeviceControllersRepository.verifyOwnership({
      id: controllerId,
      orgId,
      siteId,
      iotDeviceId,
    })

    if (!isOwner) {
      return NextResponse.json({ error: 'Forbidden' }, { status: 403 })
    }

    const dbPoints =
      await controllerPointsRepository.findByController(controllerId)

    const data = {
      points: dbPoints.map((db) =>
        ControllerPointMapper.toDTO({
          ...db,
          units: db.units ?? null,
          description: db.description ?? null,
          metadata: db.metadata ?? null,
        })
      ),
    }

    return NextResponse.json({ success: true, data })
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

    const dbPoint = await controllerPointsRepository.create({
      ...body,
      organization_id: orgId,
      site_id: siteId,
      iot_device_id: iotDeviceId,
      controller_id: controllerId,
    })

    const data = {
      point: ControllerPointMapper.toDTO({
        ...dbPoint,
        units: dbPoint.units ?? null,
        description: dbPoint.description ?? null,
        metadata: dbPoint.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create controller point')
  }
}
