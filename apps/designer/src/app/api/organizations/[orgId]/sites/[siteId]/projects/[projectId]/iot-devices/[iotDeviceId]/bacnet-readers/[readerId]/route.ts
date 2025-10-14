import { NextRequest, NextResponse } from 'next/server'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'
import { type InsertBacnetReader } from '@/lib/db/schema'
import {
  BacnetReaderRouteParamsSchema,
  type BacnetReaderRouteParams,
} from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { BacnetReaderMapper } from '@/lib/domain/mappers/bacnet-reader.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<BacnetReaderRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = BacnetReaderRouteParamsSchema.parse(await params)
    const { readerId } = validatedParams

    const dbReader = await bacnetReadersRepository.findById(readerId)

    if (!dbReader) {
      return NextResponse.json(
        { success: false, error: 'BACnet reader not found' },
        { status: 404 }
      )
    }

    const data = {
      reader: BacnetReaderMapper.toDTO({
        ...dbReader,
        description: dbReader.description ?? null,
        metadata: dbReader.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'fetch BACnet reader')
  }
}

export async function PUT(
  request: NextRequest,
  { params }: { params: Promise<BacnetReaderRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = BacnetReaderRouteParamsSchema.parse(await params)
    const { readerId } = validatedParams
    const body: Partial<InsertBacnetReader> = await request.json()

    const dbReader = await bacnetReadersRepository.update(readerId, body)

    if (!dbReader) {
      return NextResponse.json(
        { success: false, error: 'BACnet reader not found' },
        { status: 404 }
      )
    }

    const data = {
      reader: BacnetReaderMapper.toDTO({
        ...dbReader,
        description: dbReader.description ?? null,
        metadata: dbReader.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'update BACnet reader')
  }
}

export async function DELETE(
  request: NextRequest,
  { params }: { params: Promise<BacnetReaderRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = BacnetReaderRouteParamsSchema.parse(await params)
    const { readerId } = validatedParams

    const success = await bacnetReadersRepository.delete(readerId)

    if (!success) {
      return NextResponse.json(
        { success: false, error: 'BACnet reader not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ success: true })
  } catch (error) {
    return handleApiError(error, 'delete BACnet reader')
  }
}
