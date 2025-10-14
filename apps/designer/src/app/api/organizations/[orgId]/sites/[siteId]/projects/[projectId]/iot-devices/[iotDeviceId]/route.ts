import { NextRequest, NextResponse } from 'next/server'
import { handleApiError } from '@/lib/api/error-handler'
import { iotDevicesRepository } from '@/lib/db/models/iot-devices'
import { IotDeviceMapper } from '@/lib/domain/mappers/iot-device.mapper'

interface RouteParams {
  params: Promise<{ iotDeviceId: string }>
}

export async function GET(
  request: NextRequest,
  { params }: RouteParams
): Promise<NextResponse> {
  try {
    const { iotDeviceId } = await params

    const dbIotDevice = await iotDevicesRepository.findById(iotDeviceId)

    if (!dbIotDevice) {
      return NextResponse.json(
        {
          success: false,
          error: 'IoT device not found',
        },
        { status: 404 }
      )
    }

    const data = {
      iotDevice: IotDeviceMapper.toDTO({
        ...dbIotDevice,
        description: dbIotDevice.description ?? null,
      }),
    }

    const response = {
      success: true,
      data,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch IoT device')
  }
}
