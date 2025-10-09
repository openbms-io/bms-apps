import { NextRequest, NextResponse } from 'next/server'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'
import { type InsertBacnetReader } from '@/lib/db/schema'
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

    const readers = await bacnetReadersRepository.findByDevice(
      orgId,
      siteId,
      iotDeviceId
    )

    return NextResponse.json({ readers })
  } catch (error) {
    return handleApiError(error, 'fetch BACnet readers')
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
      InsertBacnetReader,
      'organization_id' | 'site_id' | 'iot_device_id'
    > = await request.json()

    const reader = await bacnetReadersRepository.create({
      ...body,
      organization_id: orgId,
      site_id: siteId,
      iot_device_id: iotDeviceId,
    })

    return NextResponse.json({ reader }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create BACnet reader')
  }
}
