import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
  CreateIotDeviceControllerRequestSchema,
} from './schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { IotDeviceControllerMapper } from '@/lib/domain/mappers/iot-device-controller.mapper'
import { randomUUID } from 'crypto'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<IotDeviceRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = IotDeviceRouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId } = validatedParams

    const dbControllers = await iotDeviceControllersRepository.findByDevice(
      orgId,
      siteId,
      iotDeviceId
    )

    const data = {
      controllers: dbControllers.map((db) =>
        IotDeviceControllerMapper.toDTO({
          ...db,
          description: db.description ?? null,
          metadata: db.metadata ?? null,
        })
      ),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'fetch controllers')
  }
}

export async function POST(
  request: NextRequest,
  { params }: { params: Promise<IotDeviceRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = IotDeviceRouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId } = validatedParams

    const body = await request.json()
    const dto = CreateIotDeviceControllerRequestSchema.parse(body)

    const createDto = {
      ...dto,
      organizationId: orgId,
      siteId: siteId,
      iotDeviceId: iotDeviceId,
    }

    const dbInsert = IotDeviceControllerMapper.toDbInsert(
      createDto,
      randomUUID()
    )

    const dbController = await iotDeviceControllersRepository.create(dbInsert)

    const data = {
      controller: IotDeviceControllerMapper.toDTO({
        ...dbController,
        description: dbController.description ?? null,
        metadata: dbController.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create controller')
  }
}
