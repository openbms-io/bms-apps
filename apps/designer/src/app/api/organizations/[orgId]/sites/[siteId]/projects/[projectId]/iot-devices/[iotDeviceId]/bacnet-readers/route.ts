import { NextRequest, NextResponse } from 'next/server'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'
import { type InsertBacnetReader } from '@/lib/db/schema'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
} from './schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { BacnetReaderMapper } from '@/lib/domain/mappers/bacnet-reader.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<IotDeviceRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = IotDeviceRouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId } = validatedParams

    const dbReaders = await bacnetReadersRepository.findByDevice(
      orgId,
      siteId,
      iotDeviceId
    )

    const data = {
      readers: dbReaders.map((db) =>
        BacnetReaderMapper.toDTO({
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

    const dbReader = await bacnetReadersRepository.create({
      ...body,
      organization_id: orgId,
      site_id: siteId,
      iot_device_id: iotDeviceId,
    })

    const data = {
      reader: BacnetReaderMapper.toDTO({
        ...dbReader,
        network_number: dbReader.network_number ?? null,
        mac_address: dbReader.mac_address ?? null,
        description: dbReader.description ?? null,
        metadata: dbReader.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data }, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create BACnet reader')
  }
}
