import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceConfigsRepository } from '@/lib/db/models/iot-device-configs'
import { type InsertIotDeviceConfig } from '@/lib/db/schema'
import { ConfigRouteParamsSchema, type ConfigRouteParams } from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { IotDeviceConfigMapper } from '@/lib/domain/mappers/iot-device-config.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ConfigRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ConfigRouteParamsSchema.parse(await params)
    const { configId } = validatedParams

    const dbConfig = await iotDeviceConfigsRepository.findById(configId)

    if (!dbConfig) {
      return NextResponse.json(
        { success: false, error: 'Device config not found' },
        { status: 404 }
      )
    }

    const data = {
      config: IotDeviceConfigMapper.toDTO(dbConfig),
    }

    return NextResponse.json({ success: true, data })
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

    const dbConfig = await iotDeviceConfigsRepository.update(configId, body)

    if (!dbConfig) {
      return NextResponse.json(
        { success: false, error: 'Device config not found' },
        { status: 404 }
      )
    }

    const data = {
      config: IotDeviceConfigMapper.toDTO(dbConfig),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'update device config')
  }
}
