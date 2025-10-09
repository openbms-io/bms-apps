import { NextRequest, NextResponse } from 'next/server'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'
import { type InsertBacnetReader } from '@/lib/db/schema'
import {
  BacnetReaderRouteParamsSchema,
  type BacnetReaderRouteParams,
} from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<BacnetReaderRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = BacnetReaderRouteParamsSchema.parse(await params)
    const { readerId } = validatedParams

    const reader = await bacnetReadersRepository.findById(readerId)

    if (!reader) {
      return NextResponse.json(
        { error: 'BACnet reader not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ reader })
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

    const reader = await bacnetReadersRepository.update(readerId, body)

    if (!reader) {
      return NextResponse.json(
        { error: 'BACnet reader not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ reader })
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
        { error: 'BACnet reader not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ success: true })
  } catch (error) {
    return handleApiError(error, 'delete BACnet reader')
  }
}
