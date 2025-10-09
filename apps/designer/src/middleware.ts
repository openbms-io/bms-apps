import { NextResponse } from 'next/server'
import type { NextRequest } from 'next/server'
import { verifyResourceOwnership } from '@/lib/middleware/ownership'

export const runtime = 'nodejs'

export async function middleware(request: NextRequest): Promise<NextResponse> {
  const ownershipError = await verifyResourceOwnership({ request })

  if (ownershipError) {
    return ownershipError
  }

  return NextResponse.next()
}

export const config = {
  matcher: [
    '/api/organizations/:orgId/sites/:siteId/projects/:projectId/iot-devices/:iotDeviceId/bacnet-readers/:readerId/:path*',
    '/api/organizations/:orgId/sites/:siteId/projects/:projectId/iot-devices/:iotDeviceId/controllers/:controllerId/:path*',
    '/api/organizations/:orgId/sites/:siteId/projects/:projectId/iot-devices/:iotDeviceId/configs/:configId/:path*',
  ],
}
