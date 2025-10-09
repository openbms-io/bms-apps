import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { type InsertIotDeviceController } from '@/lib/db/schema'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
} from './schemas'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<IotDeviceRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = IotDeviceRouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId } = validatedParams

    const controllers = await iotDeviceControllersRepository.findByDevice(
      orgId,
      siteId,
      iotDeviceId
    )

    return NextResponse.json({ controllers })
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
    const body: Omit<
      InsertIotDeviceController,
      'organization_id' | 'site_id' | 'iot_device_id'
    > = await request.json()

    const controller = await iotDeviceControllersRepository.create({
      ...body,
      organization_id: orgId,
      site_id: siteId,
      iot_device_id: iotDeviceId,
    })

    return NextResponse.json({ controller }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create controller')
  }
}
