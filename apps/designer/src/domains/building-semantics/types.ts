/**
 * Building Semantics Domain - Public Types
 *
 * These types define the domain's public API and are implementation-agnostic.
 * They can work with any semantic standard (223P, Brick, Haystack).
 *
 * @module building-semantics/types
 */

import type { BacnetConfig } from '@/types/infrastructure'

export type {
  SemanticEquipment,
  BACnetPointData,
  BACnetControllerData,
} from './adapters/ashrae-223p/schemas'

/**
 * Minimal BACnet configuration needed for building semantics API requests.
 *
 * Derived from BacnetConfig with additional controller fields.
 * Used to construct ASHRAE 223P BACnetExternalReference identifiers:
 * - deviceIdentifier: "device,{controllerDeviceId}"
 * - objectIdentifier: "{objectType},{objectId}"
 * - externalIdentifier: "{controllerIPAddress}:device,{controllerDeviceId}:{objectType},{objectId}"
 */
export type BuildingSemanticsBacnetConfig = Pick<
  BacnetConfig,
  'objectType' | 'objectId'
> & {
  controllerDeviceId: number // BACnet device instance number (e.g., 800) - from controller.deviceId
  controllerIPAddress: string // Controller IP address (e.g., "192.168.1.100") - from controller.ipAddress
}

// Future: Can add union types when multiple adapters exist
// Example:
// import type { ASHRAE223PEquipment } from './adapters/ashrae-223p/schemas'
// import type { BrickEquipment } from './adapters/brick/schemas'
// export type SemanticEquipment = ASHRAE223PEquipment | BrickEquipment
