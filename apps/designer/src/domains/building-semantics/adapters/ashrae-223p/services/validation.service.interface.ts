import type {
  BACnetPointData,
  DeviceType,
  ValidationResultDTO,
} from '../schemas'

/**
 * Validation Service Interface
 *
 * Validates 223P mappings against SHACL rules.
 * Epic 1: Mock validation (BACnet object type compatibility only)
 * Epic 3: Real SHACL engine validation with full 223P rules
 */
export interface IValidationService {
  /**
   * Validates a 223P mapping for a BACnet point.
   *
   * @param point - The BACnet point being mapped
   * @param deviceType - The selected 223P device type
   * @returns Validation result with errors and warnings
   *
   * @example
   * const result = service.validateMapping(
   *   { name: "ZoneTemp", objectType: "analog-input" },
   *   "Sensor"
   * );
   * // result.isValid = true
   *
   * @example
   * const result = service.validateMapping(
   *   { name: "ZoneTemp", objectType: "analog-input" },
   *   "Damper"
   * );
   * // result.isValid = false
   * // result.errors[0].message = "Damper requires AO/BO object type, found AI"
   */
  validateMapping(
    point: BACnetPointData,
    deviceType: DeviceType
  ): ValidationResultDTO
}
