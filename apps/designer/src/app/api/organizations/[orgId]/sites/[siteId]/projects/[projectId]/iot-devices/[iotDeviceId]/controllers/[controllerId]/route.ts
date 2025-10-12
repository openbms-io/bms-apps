import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { type InsertIotDeviceController } from '@/lib/db/schema'
import {
  ControllerRouteParamsSchema,
  type ControllerRouteParams,
} from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { IotDeviceControllerMapper } from '@/lib/domain/mappers/iot-device-controller.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ControllerRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerRouteParamsSchema.parse(await params)
    const { controllerId } = validatedParams

    const dbController =
      await iotDeviceControllersRepository.findById(controllerId)

    if (!dbController) {
      return NextResponse.json(
        { success: false, error: 'Controller not found' },
        { status: 404 }
      )
    }

    const data = {
      controller: IotDeviceControllerMapper.toDTO({
        ...dbController,
        description: dbController.description ?? null,
        metadata: dbController.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'fetch controller')
  }
}

export async function PUT(
  request: NextRequest,
  { params }: { params: Promise<ControllerRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerRouteParamsSchema.parse(await params)
    const { controllerId } = validatedParams
    const body: Partial<InsertIotDeviceController> = await request.json()

    const dbController = await iotDeviceControllersRepository.update(
      controllerId,
      body
    )

    if (!dbController) {
      return NextResponse.json(
        { success: false, error: 'Controller not found' },
        { status: 404 }
      )
    }

    const data = {
      controller: IotDeviceControllerMapper.toDTO({
        ...dbController,
        description: dbController.description ?? null,
        metadata: dbController.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'update controller')
  }
}

export async function DELETE(
  request: NextRequest,
  { params }: { params: Promise<ControllerRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerRouteParamsSchema.parse(await params)
    const { controllerId } = validatedParams

    const success = await iotDeviceControllersRepository.delete(controllerId)

    if (!success) {
      return NextResponse.json(
        { success: false, error: 'Controller not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ success: true })
  } catch (error) {
    return handleApiError(error, 'delete controller')
  }
}
