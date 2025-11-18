import { z } from 'zod'

/**
 * ASHRAE 223P Enum Schemas
 *
 * All enums are defined as Zod schemas (single source of truth).
 * TypeScript types are derived using z.infer<typeof Schema>.
 *
 * Based on NREL BuildingMOTIF v0.10.0 templates:
 * - systems.yml (8 equipment types)
 * - devices.yml (18 device types)
 * - properties.yml (25+ observable properties)
 * - spaces.yml (2 space types)
 */

/**
 * Space Types
 *
 * 2 space types from ASHRAE 223P ontology.
 * - PhysicalSpace: Actual rooms/zones (e.g., "Room 201")
 * - DomainSpace: Logical groupings (e.g., "3rd Floor HVAC Zone")
 *
 * @example "PhysicalSpace"
 * @example "DomainSpace"
 */
export const SpaceTypeSchema = z.enum(['DomainSpace', 'PhysicalSpace'])

export type SpaceType = z.infer<typeof SpaceTypeSchema>

/**
 * Connection Point Types
 *
 * Used for G36 integration (Epic 2).
 * Defines inlet/outlet ports on devices.
 *
 * @example "air-in"
 * @example "water-out"
 */
export const ConnectionPointTypeSchema = z.enum([
  'air-in',
  'air-out',
  'water-in',
  'water-out',
  'in',
  'out',
])

export type ConnectionPointType = z.infer<typeof ConnectionPointTypeSchema>

/**
 * BACnet Object Types
 *
 * Standard BACnet object types used in building automation.
 * Reused from existing codebase types.
 *
 * @example "analog-input"
 * @example "binary-output"
 */
export const BacnetObjectTypeSchema = z.enum([
  'analog-input',
  'analog-output',
  'analog-value',
  'binary-input',
  'binary-output',
  'binary-value',
  'multi-state-input',
  'multi-state-output',
  'multi-state-value',
])

export type BacnetObjectType = z.infer<typeof BacnetObjectTypeSchema>

/**
 * Validation Error Codes
 *
 * Error codes for SHACL validation failures.
 * Used in ValidationErrorDTO.
 *
 * @example "INCOMPATIBLE_BACNET_TYPE"
 */
export const ValidationErrorCodeSchema = z.enum([
  'INCOMPATIBLE_BACNET_TYPE',
  'INVALID_PROPERTY_FOR_DEVICE',
  'MISSING_REQUIRED_FIELD',
  'SPACE_REQUIRED_FOR_SYSTEM',
])

export type ValidationErrorCode = z.infer<typeof ValidationErrorCodeSchema>
