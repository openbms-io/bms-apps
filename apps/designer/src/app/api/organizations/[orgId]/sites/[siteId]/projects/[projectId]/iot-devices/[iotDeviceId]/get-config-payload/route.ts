import { NextRequest, NextResponse } from 'next/server'
import { handleApiError } from '@/lib/api/error-handler'
import { GetConfigPayloadRouteParamsSchema } from './schemas'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'
import { IotDeviceControllerMapper } from '@/lib/domain/mappers/iot-device-controller.mapper'
import { BacnetReaderMapper } from '@/lib/domain/mappers/bacnet-reader.mapper'
import { GetConfigPayloadMapper } from '@/lib/domain/mappers/get-config-payload.mapper'
import { buildIOTDeviceJWTPayload, encodeJWT } from '@/lib/jwt'

export async function GET(
  request: NextRequest,
  {
    params,
  }: {
    params: Promise<{
      orgId: string
      siteId: string
      projectId: string
      iotDeviceId: string
    }>
  }
): Promise<NextResponse> {
  try {
    const routeParams = GetConfigPayloadRouteParamsSchema.parse(await params)

    // Fetch controllers (excluding soft-deleted)
    const dbControllers = await iotDeviceControllersRepository.findByDevice(
      routeParams.orgId,
      routeParams.siteId,
      routeParams.iotDeviceId,
      false
    )

    // Fetch readers (excluding soft-deleted)
    const dbReaders = await bacnetReadersRepository.findByDevice(
      routeParams.orgId,
      routeParams.siteId,
      routeParams.iotDeviceId,
      false
    )

    // Convert DB entities to DTOs
    const controllers = dbControllers.map((c) =>
      GetConfigPayloadMapper.toControllerDTO(IotDeviceControllerMapper.toDTO(c))
    )
    const readers = dbReaders.map((r) =>
      GetConfigPayloadMapper.toReaderDTO(BacnetReaderMapper.toDTO(r))
    )

    // Generate JWT (10 min expiry)
    const jwtPayload = buildIOTDeviceJWTPayload({
      orgId: routeParams.orgId,
      siteId: routeParams.siteId,
      iotDeviceId: routeParams.iotDeviceId,
    })
    const jwtToken = await encodeJWT(jwtPayload, '10m')

    // Build webhook URL
    const baseUrl = process.env.NEXT_PUBLIC_API_URL || 'http://localhost:3000'
    const urlToUploadConfig = `${baseUrl}/api/webhook/iot-device-config-upload`

    const data = {
      payload: {
        urlToUploadConfig,
        jwtToken,
        iotDeviceControllers: controllers,
        bacnetReaders: readers,
      },
    }

    return NextResponse.json({ success: true, data }, { status: 200 })
  } catch (error) {
    return handleApiError(error, 'generate get-config payload')
  }
}
