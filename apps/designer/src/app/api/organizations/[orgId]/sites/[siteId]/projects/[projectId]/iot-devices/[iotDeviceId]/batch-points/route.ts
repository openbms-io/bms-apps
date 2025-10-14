import { NextRequest, NextResponse } from 'next/server'
import { controllerPointsRepository } from '@/lib/db/models/controller-points'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { handleApiError } from '@/lib/api/error-handler'
import { ControllerPointMapper } from '@/lib/domain/mappers/controller-point.mapper'
import { z } from 'zod'

const RouteParamsSchema = z.object({
  orgId: z.string().startsWith('org_'),
  siteId: z.string().uuid(),
  projectId: z.string().uuid(),
  iotDeviceId: z.string().uuid(),
})

const QuerySchema = z.object({
  controllerIds: z.string().transform((val) => val.split(',')),
})

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
    console.log('Batch points route')
    const validatedParams = RouteParamsSchema.parse(await params)
    const { orgId, siteId, iotDeviceId } = validatedParams

    const { searchParams } = new URL(request.url)
    const controllerIdsParam = searchParams.get('controllerIds')

    if (!controllerIdsParam) {
      return NextResponse.json(
        { error: 'controllerIds query parameter required' },
        { status: 400 }
      )
    }

    const { controllerIds } = QuerySchema.parse({
      controllerIds: controllerIdsParam,
    })

    // Verify all controllers exist and have ownership
    for (const controllerId of controllerIds) {
      const controller =
        await iotDeviceControllersRepository.findById(controllerId)

      if (!controller) {
        return NextResponse.json(
          { error: `Controller not found: ${controllerId}` },
          { status: 404 }
        )
      }

      const isOwner = await iotDeviceControllersRepository.verifyOwnership({
        id: controllerId,
        orgId,
        siteId,
        iotDeviceId,
      })

      if (!isOwner) {
        return NextResponse.json({ error: 'Forbidden' }, { status: 403 })
      }
    }

    // Fetch points for all controllers
    const pointsByController: Record<
      string,
      ReturnType<typeof ControllerPointMapper.toDTO>[]
    > = {}

    for (const controllerId of controllerIds) {
      const dbPoints =
        await controllerPointsRepository.findByController(controllerId)
      pointsByController[controllerId] = dbPoints.map((db) =>
        ControllerPointMapper.toDTO({
          ...db,
          units: db.units ?? null,
          description: db.description ?? null,
          metadata: db.metadata ?? null,
        })
      )
    }

    return NextResponse.json({
      success: true,
      data: { pointsByController },
    })
  } catch (error) {
    return handleApiError(error, 'fetch controller points batch')
  }
}
