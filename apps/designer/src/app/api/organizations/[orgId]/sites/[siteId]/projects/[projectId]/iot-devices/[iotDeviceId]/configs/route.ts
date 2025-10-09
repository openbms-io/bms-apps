import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceConfigsRepository } from '@/lib/db/models/iot-device-configs'
import { type InsertIotDeviceConfig } from '@/lib/db/schema'
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

    const configs = await iotDeviceConfigsRepository.findByDevice(
      orgId,
      siteId,
      iotDeviceId
    )

    return NextResponse.json({ configs })
  } catch (error) {
    return handleApiError(error, 'fetch device configs')
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
      InsertIotDeviceConfig,
      'organization_id' | 'site_id' | 'iot_device_id'
    > = await request.json()

    const config = await iotDeviceConfigsRepository.create({
      ...body,
      organization_id: orgId,
      site_id: siteId,
      iot_device_id: iotDeviceId,
    })

    return NextResponse.json({ config }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create device config')
  }
}
