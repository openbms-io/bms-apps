import { NextRequest, NextResponse } from 'next/server'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'
import {
  IotDeviceRouteParamsSchema,
  type IotDeviceRouteParams,
  CreateBacnetReaderRequestSchema,
} from './schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { BacnetReaderMapper } from '@/lib/domain/mappers/bacnet-reader.mapper'
import { randomUUID } from 'crypto'

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

    const body = await request.json()
    const dto = CreateBacnetReaderRequestSchema.parse(body)

    const createDto = {
      ...dto,
      organizationId: orgId,
      siteId: siteId,
      iotDeviceId: iotDeviceId,
    }

    const dbInsert = BacnetReaderMapper.toDbInsert(createDto, randomUUID())

    const dbReader = await bacnetReadersRepository.create(dbInsert)

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
