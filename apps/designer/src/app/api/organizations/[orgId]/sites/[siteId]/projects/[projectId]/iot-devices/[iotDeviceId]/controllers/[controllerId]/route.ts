import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { type InsertIotDeviceController } from '@/lib/db/schema'
import {
  ControllerRouteParamsSchema,
  type ControllerRouteParams,
} from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ControllerRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerRouteParamsSchema.parse(await params)
    const { controllerId } = validatedParams

    const controller =
      await iotDeviceControllersRepository.findById(controllerId)

    if (!controller) {
      return NextResponse.json(
        { error: 'Controller not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ controller })
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

    const controller = await iotDeviceControllersRepository.update(
      controllerId,
      body
    )

    if (!controller) {
      return NextResponse.json(
        { error: 'Controller not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ controller })
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
        { error: 'Controller not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ success: true })
  } catch (error) {
    return handleApiError(error, 'delete controller')
  }
}
