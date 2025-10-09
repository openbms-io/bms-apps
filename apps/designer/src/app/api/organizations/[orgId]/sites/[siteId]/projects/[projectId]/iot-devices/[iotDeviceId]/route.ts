import { NextRequest, NextResponse } from 'next/server'
import { handleApiError } from '@/lib/api/error-handler'
import { iotDevicesRepository } from '@/lib/db/models/iot-devices'

interface RouteParams {
  params: Promise<{ iotDeviceId: string }>
}

export async function GET(
  request: NextRequest,
  { params }: RouteParams
): Promise<NextResponse> {
  try {
    const { iotDeviceId } = await params

    const iotDevice = await iotDevicesRepository.findById(iotDeviceId)

    if (!iotDevice) {
      return NextResponse.json(
        {
          success: false,
          error: 'IoT device not found',
        },
        { status: 404 }
      )
    }

    const response = {
      success: true,
      iot_device: iotDevice,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch IoT device')
  }
}
