import { NextResponse } from 'next/server'
import type { NextRequest } from 'next/server'
import { matchRoute, ResourceType } from './route-matcher'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { controllerPointsRepository } from '@/lib/db/models/controller-points'
import { iotDeviceConfigsRepository } from '@/lib/db/models/iot-device-configs'

export async function verifyResourceOwnership({
  request,
}: {
  request: NextRequest
}): Promise<NextResponse | null> {
  const routeParams = matchRoute({ pathname: request.nextUrl.pathname })

  if (!routeParams) {
    return null
  }

  const { resourceType, resourceId, orgId, siteId, iotDeviceId } = routeParams

  let isOwned = false

  switch (resourceType) {
    case ResourceType.BacnetReader:
      isOwned = await bacnetReadersRepository.verifyOwnership({
        id: resourceId,
        orgId,
        siteId,
        iotDeviceId,
      })
      break

    case ResourceType.Controller:
      isOwned = await iotDeviceControllersRepository.verifyOwnership({
        id: resourceId,
        orgId,
        siteId,
        iotDeviceId,
      })
      break

    case ResourceType.ControllerPoint:
      isOwned = await controllerPointsRepository.verifyOwnership({
        id: resourceId,
        orgId,
        siteId,
        iotDeviceId,
      })
      break

    case ResourceType.DeviceConfig:
      isOwned = await iotDeviceConfigsRepository.verifyOwnership({
        id: resourceId,
        orgId,
        siteId,
        iotDeviceId,
      })
      break
  }

  if (!isOwned) {
    return NextResponse.json({ error: 'Resource not found' }, { status: 404 })
  }

  return null
}
