import { NextRequest, NextResponse } from 'next/server'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { type InsertIotDeviceController } from '@/lib/db/schema'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
} from './schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { IotDeviceControllerMapper } from '@/lib/domain/mappers/iot-device-controller.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<IotDeviceRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = IotDeviceRouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId } = validatedParams

    const dbControllers = await iotDeviceControllersRepository.findByDevice(
      orgId,
      siteId,
      iotDeviceId
    )

    const data = {
      controllers: dbControllers.map((db) =>
        IotDeviceControllerMapper.toDTO({
          ...db,
          network_number: db.network_number ?? null,
          mac_address: db.mac_address ?? null,
          description: db.description ?? null,
          metadata: db.metadata ?? null,
        })
      ),
    }

    return NextResponse.json({ success: true, data })
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

    const dbController = await iotDeviceControllersRepository.create({
      ...body,
      organization_id: orgId,
      site_id: siteId,
      iot_device_id: iotDeviceId,
    })

    const data = {
      controller: IotDeviceControllerMapper.toDTO({
        ...dbController,
        network_number: dbController.network_number ?? null,
        mac_address: dbController.mac_address ?? null,
        description: dbController.description ?? null,
        metadata: dbController.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create controller')
  }
}
