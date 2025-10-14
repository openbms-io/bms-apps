import { NextRequest, NextResponse } from 'next/server'
import { controllerPointsRepository } from '@/lib/db/models/controller-points'
import { type InsertControllerPoint } from '@/lib/db/schema'
import {
  ControllerPointRouteParamsSchema,
  type ControllerPointRouteParams,
} from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'
import { ControllerPointMapper } from '@/lib/domain/mappers/controller-point.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ControllerPointRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerPointRouteParamsSchema.parse(await params)
    const { pointId } = validatedParams

    const dbPoint = await controllerPointsRepository.findById(pointId)

    if (!dbPoint) {
      return NextResponse.json(
        { success: false, error: 'Controller point not found' },
        { status: 404 }
      )
    }

    const data = {
      point: ControllerPointMapper.toDTO({
        ...dbPoint,
        units: dbPoint.units ?? null,
        description: dbPoint.description ?? null,
        metadata: dbPoint.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'fetch controller point')
  }
}

export async function PUT(
  request: NextRequest,
  { params }: { params: Promise<ControllerPointRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerPointRouteParamsSchema.parse(await params)
    const { pointId } = validatedParams
    const body: Partial<InsertControllerPoint> = await request.json()

    const dbPoint = await controllerPointsRepository.update(pointId, body)

    if (!dbPoint) {
      return NextResponse.json(
        { success: false, error: 'Controller point not found' },
        { status: 404 }
      )
    }

    const data = {
      point: ControllerPointMapper.toDTO({
        ...dbPoint,
        units: dbPoint.units ?? null,
        description: dbPoint.description ?? null,
        metadata: dbPoint.metadata ?? null,
      }),
    }

    return NextResponse.json({ success: true, data })
  } catch (error) {
    return handleApiError(error, 'update controller point')
  }
}

export async function DELETE(
  request: NextRequest,
  { params }: { params: Promise<ControllerPointRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerPointRouteParamsSchema.parse(await params)
    const { pointId } = validatedParams

    const success = await controllerPointsRepository.delete(pointId)

    if (!success) {
      return NextResponse.json(
        { success: false, error: 'Controller point not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ success: true })
  } catch (error) {
    return handleApiError(error, 'delete controller point')
  }
}
