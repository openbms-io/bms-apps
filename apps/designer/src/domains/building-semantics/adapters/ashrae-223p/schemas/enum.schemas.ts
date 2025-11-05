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
 * System Types (Equipment Types)
 *
 * 8 equipment types from NREL BuildingMOTIF systems.yml
 * These represent top-level HVAC systems in ASHRAE 223P ontology.
 *
 * @example "VAV Reheat Terminal Unit"
 * @example "Chilled Water System"
 */
export const SystemTypeSchema = z.enum([
  'Makeup Air Unit',
  'VAV Reheat Terminal Unit',
  'Lab VAV Reheat Terminal Unit',
  'Chilled Water System',
  'Hot Water System',
  'Process Chilled Water System',
  'Exhaust Air Unit',
  'Heat Recovery System',
])

export type SystemType = z.infer<typeof SystemTypeSchema>

/**
 * Device Types
 *
 * 18 device types from NREL BuildingMOTIF devices.yml
 * Grouped by category: air-side, coils, water-side, sensors, other.
 *
 * @example "Sensor"
 * @example "Damper"
 * @example "Chilled Water Valve"
 */
export const DeviceTypeSchema = z.enum([
  // Air-side equipment
  'Damper',
  'Fan',
  'Exhaust Fan',
  'Filter',

  // Coils
  'Chilled Water Coil',
  'Hot Water Coil',
  'Heat Recovery Coil',

  // Water-side equipment
  'Chilled Water Valve',
  'Hot Water Valve',
  'Chilled Water Pump',
  'Hot Water Pump',

  // Sensors & monitoring
  'Sensor',

  // Other equipment
  'Evaporative Cooler',
  'Heat Exchanger',
  'Fan Coil Unit',
  'Unit Heater',
  'Tank',
  'Domestic Water Heater',
])

export type DeviceType = z.infer<typeof DeviceTypeSchema>

/**
 * Observable Properties
 *
 * 25+ properties from NREL BuildingMOTIF properties.yml
 * Includes both quantifiable (numeric) and enumerated (status) properties.
 *
 * @example "air-temperature" (quantifiable)
 * @example "run-status" (enumerated)
 */
export const ObservablePropertySchema = z.enum([
  // Quantifiable - Pressure
  'static-pressure',
  'low-static-pressure',
  'water-static-pressure',
  'differential-pressure',
  'water-differential-pressure',

  // Quantifiable - Temperature
  'air-temperature',
  'water-temperature',

  // Quantifiable - Flow
  'air-flow',
  'water-flow',

  // Quantifiable - Environmental
  'relative-humidity',

  // Quantifiable - VFD Properties
  'vfd-current',
  'vfd-frequency',
  'vfd-voltage',
  'vfd-power',
  'vfd-energy',

  // Quantifiable - BTU Meter
  'BTU-Meter-energy',
  'BTU-Meter-energy-rate',
  'BTU-Meter-water-flow',
  'BTU-Meter-water-volume',

  // Enumerated - Status Properties
  'run-status',
  'flow-status',
  'vfd-fault',
  'condensate-overflow',
  'occupancy-override',
])

export type ObservableProperty = z.infer<typeof ObservablePropertySchema>

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
