import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceConfigsRepository } from '@/lib/db/models/iot-device-configs'
import { type InsertIotDeviceConfig } from '@/lib/db/schema'
import { ConfigRouteParamsSchema, type ConfigRouteParams } from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ConfigRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ConfigRouteParamsSchema.parse(await params)
    const { configId } = validatedParams

    const config = await iotDeviceConfigsRepository.findById(configId)

    if (!config) {
      return NextResponse.json(
        { error: 'Device config not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ config })
  } catch (error) {
    return handleApiError(error, 'fetch device config')
  }
}

export async function PUT(
  request: NextRequest,
  { params }: { params: Promise<ConfigRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ConfigRouteParamsSchema.parse(await params)
    const { configId } = validatedParams
    const body: Partial<InsertIotDeviceConfig> = await request.json()

    const config = await iotDeviceConfigsRepository.update(configId, body)

    if (!config) {
      return NextResponse.json(
        { error: 'Device config not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ config })
  } catch (error) {
    return handleApiError(error, 'update device config')
  }
}
