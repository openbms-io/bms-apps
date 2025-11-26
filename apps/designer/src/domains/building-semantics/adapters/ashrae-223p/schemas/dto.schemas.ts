import { z } from 'zod'
import { ValidationErrorCodeSchema } from './enum.schemas'

/**
 * ASHRAE 223P DTO Schemas
 *
 * Data Transfer Objects for BuildingMOTIF API integration.
 * All DTOs are defined as Zod schemas for runtime validation.
 * TypeScript types are derived using z.infer<typeof Schema>.
 *
 * IMPORTANT: These DTOs are "best guess" based on 223P ontology.
 * Epic 3 will refine structure based on actual BuildingMOTIF API responses.
 * UI components use ViewModels (not DTOs) to remain isolated from API changes.
 */

/**
 * BACnet External Reference DTO
 *
 * References a specific BACnet object on a BACnet device.
 * Maps 223P points to physical BACnet infrastructure.
 *
 * @example
 * {
 *   deviceIdentifier: "device,1001",
 *   deviceName: "VAV-2-01",
 *   objectIdentifier: "analog-input,1",
 *   objectName: "ZoneTemp",
 *   propertyIdentifier: "present-value",
 *   priorityForWriting: 8
 * }
 *
 * Epic 1: All fields optional (best guess structure)
 * Epic 3: Will match actual BuildingMOTIF API structure
 */
export const BACnetExternalReferenceDTOSchema = z
  .object({
    deviceIdentifier: z.string().optional(),
    deviceName: z.string().optional(),
    objectIdentifier: z.string().optional(),
    objectName: z.string().optional(),
    propertyIdentifier: z.string().optional(),
    propertyArrayIndex: z.number().optional(),
    priorityForWriting: z.number().min(1).max(16).optional(),
  })
  .transform((data) => ({
    ...data,
  }))

export type BACnetExternalReferenceDTO = z.infer<
  typeof BACnetExternalReferenceDTOSchema
>

/**
 * BACnet Point Data
 *
 * Point data passed from Designer domain to 223P domain.
 * Represents a BACnet point from device discovery.
 *
 * @example
 * {
 *   pointId: "550e8400-e29b-41d4-a716-446655440000",
 *   objectType: "analog-input",
 *   objectId: 1,
 *   supervisorId: "supervisor-1",
 *   controllerId: "controller-123",
 *   name: "VAV-2-01_ZoneTemp",
 *   discoveredProperties: {
 *     presentValue: 72.3,
 *     units: "degrees-fahrenheit",
 *     description: "Zone Temperature Sensor"
 *   }
 * }
 */
export interface BACnetPointData {
  pointId: string
  objectType: string
  objectId: number
  supervisorId: string
  controllerId: string
  name?: string
  discoveredProperties?: Record<string, unknown>
}

/**
 * BACnet Controller Data
 *
 * Controller data passed from Designer domain to 223P domain.
 * Contains minimal info needed for constructing BACnet deviceIdentifier.
 *
 * @example
 * {
 *   deviceId: 123,
 *   ipAddress: "192.168.1.100"
 * }
 */
export interface BACnetControllerData {
  deviceId: number // BACnet device ID
  ipAddress: string // Controller IP address
}

/**
 * Semantic Equipment for Tree Display
 *
 * Minimal semantic mapping data derived from EnrichedBACnetReferenceDTO.
 * Used to display semantic mapping badges in the BACnet device tree.
 *
 * @example
 * {
 *   systemLabel: "AHU-1 VAV System",
 *   deviceLabel: "VAV Box Sensor",
 *   propertyLabel: "Zone Temperature",
 *   systemTemplate: "vav-reheat"
 * }
 */
export const SemanticEquipmentSchema = z.object({
  systemLabel: z.string(),
  deviceLabel: z.string(),
  propertyLabel: z.string(),
  systemTemplate: z.string(),
})

export type SemanticEquipment = z.infer<typeof SemanticEquipmentSchema>

/**
 * Validation Error DTO
 *
 * Describes a single SHACL validation error or warning.
 * Used by ValidationResultDTO to report validation failures.
 *
 * @example
 * {
 *   field: "deviceType",
 *   message: "Actuator requires AO/BO object type, found AI",
 *   code: "INCOMPATIBLE_BACNET_TYPE",
 *   expectedType: "analog-output",
 *   actualType: "analog-input"
 * }
 */
export const ValidationErrorDTOSchema = z.object({
  field: z.string(),
  message: z.string(),
  code: ValidationErrorCodeSchema,
  expectedType: z.string().optional(),
  actualType: z.string().optional(),
})

export type ValidationErrorDTO = z.infer<typeof ValidationErrorDTOSchema>

/**
 * Validation Result DTO
 *
 * Result of SHACL validation for a 223P mapping.
 * Returns validation errors and warnings.
 *
 * @example
 * {
 *   isValid: false,
 *   errors: [
 *     {
 *       field: "deviceType",
 *       message: "Actuator requires AO/BO object type",
 *       code: "INCOMPATIBLE_BACNET_TYPE",
 *       expectedType: "analog-output",
 *       actualType: "analog-input"
 *     }
 *   ],
 *   warnings: []
 * }
 *
 * Epic 1: Mock validation (BACnet object type compatibility only)
 * Epic 3: Real SHACL engine validation with full 223P rules
 */
export const ValidationResultDTOSchema = z.object({
  isValid: z.boolean(),
  errors: z.array(ValidationErrorDTOSchema),
  warnings: z.array(ValidationErrorDTOSchema),
})

export type ValidationResultDTO = z.infer<typeof ValidationResultDTOSchema>
