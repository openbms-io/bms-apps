import { NextRequest, NextResponse } from 'next/server'
import { controllerPointsRepository } from '@/lib/db/models/controller-points'
import { type InsertControllerPoint } from '@/lib/db/schema'
import {
  ControllerPointRouteParamsSchema,
  type ControllerPointRouteParams,
} from '../schemas'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<ControllerPointRouteParams> }
): Promise<NextResponse> {
  try {
    const validatedParams = ControllerPointRouteParamsSchema.parse(await params)
    const { pointId } = validatedParams

    const point = await controllerPointsRepository.findById(pointId)

    if (!point) {
      return NextResponse.json(
        { error: 'Controller point not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ point })
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

    const point = await controllerPointsRepository.update(pointId, body)

    if (!point) {
      return NextResponse.json(
        { error: 'Controller point not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ point })
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
        { error: 'Controller point not found' },
        { status: 404 }
      )
    }

    return NextResponse.json({ success: true })
  } catch (error) {
    return handleApiError(error, 'delete controller point')
  }
}
