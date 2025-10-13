import { NextRequest, NextResponse } from 'next/server'

import { handleApiError } from '@/lib/api/error-handler'
import { decodeJWT } from '@/lib/jwt'
import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { controllerPointsRepository } from '@/lib/db/models/controller-points'
import { ConfigUploadSchema } from './schemas'
import type { BacnetMetadata } from '@/types/bacnet-metadata'

// analogOutput -> analog-output.
// We use kebab-case for point types everywhere in code.
function normalizePointType(pointType: string): string {
  return pointType.replace(/([a-z])([A-Z])/g, '$1-$2').toLowerCase()
}

export async function POST(request: NextRequest): Promise<NextResponse> {
  try {
    console.log('Received config upload request')
    // 1. Extract and validate JWT (jwtVerify validates signature, expiration, format)
    const authHeader = request.headers.get('authorization')
    if (!authHeader?.startsWith('Bearer ')) {
      return NextResponse.json(
        { error: 'Missing authorization header' },
        { status: 401 }
      )
    }

    const token = authHeader.substring(7)
    const jwtPayload = await decodeJWT(token) // This validates the JWT

    if (jwtPayload.scope !== 'upload-config') {
      console.warn('Invalid token scope')
      return NextResponse.json(
        { error: 'Invalid token scope' },
        { status: 403 }
      )
    }

    // 2. Parse and validate request body
    const body = await request.json()
    console.log('Config upload received body JSON', JSON.stringify(body))

    const validated = ConfigUploadSchema.parse(body)

    // 3. Extract IDs from JWT (not from body)
    const organization_id = jwtPayload.orgId
    const site_id = jwtPayload.siteId
    const iot_device_id = jwtPayload.iotDeviceId

    // 4. Process each config item (controller)
    for (const cfg of validated.config) {
      // Verify controller exists and validate it matches expected values
      const existingController = await iotDeviceControllersRepository.findById(
        cfg.controller_id
      )

      if (!existingController) {
        return NextResponse.json(
          {
            error: 'Controller not found',
            details: {
              controller_id: cfg.controller_id,
              message: 'Controller must be created by user before discovery',
            },
          },
          { status: 404 }
        )
      }

      // Validate that IoT device is not trying to change user-set values
      if (existingController.ip_address !== cfg.controller_ip_address) {
        return NextResponse.json(
          {
            error:
              'Logical error: IoT device attempted to change controller IP address',
            details: {
              controller_id: cfg.controller_id,
              expected: existingController.ip_address,
              received: cfg.controller_ip_address,
            },
          },
          { status: 400 }
        )
      }

      // Update only the device_id from discovery
      await iotDeviceControllersRepository.update(cfg.controller_id, {
        device_id: cfg.device_id,
      })

      // Get IDs of points in current config
      const configPointIds = cfg.object_list.map(
        (obj) => obj.iot_device_point_id
      )

      // Soft delete points not in current config
      await controllerPointsRepository.softDeleteNotInList(
        cfg.controller_id,
        configPointIds
      )

      // Upsert each point (will restore if previously deleted)
      for (const obj of cfg.object_list) {
        await controllerPointsRepository.upsert({
          id: obj.iot_device_point_id,
          organization_id: organization_id,
          site_id: site_id,
          iot_device_id: iot_device_id,
          controller_id: cfg.controller_id,
          point_name: obj.properties.objectName,
          point_type: normalizePointType(obj.type),
          object_identifier: JSON.stringify(obj.properties.objectIdentifier),
          instance_number: obj.point_id,
          writable: obj.properties.outOfService === 0,
          units: obj.properties.units || undefined,
          description: obj.properties.description || undefined,
          metadata: obj.properties
            ? (obj.properties as BacnetMetadata)
            : undefined,
        })
      }
    }

    // 5. Return success
    const data = {
      uploadedAt: new Date().toISOString(),
      controllersProcessed: validated.config.length,
      pointsProcessed: validated.config.reduce(
        (sum, c) => sum + c.object_list.length,
        0
      ),
    }

    console.log('Successfully uploaded config')
    return NextResponse.json({ success: true, data }, { status: 200 })
  } catch (error) {
    console.error('Error uploading config', error)
    return handleApiError(error, 'upload config')
  }
}
