/**
 * BACnet Key Utilities
 *
 * Centralized functions for constructing BACnet identifiers and composite keys
 * used for 223P mapping storage and lookup.
 *
 * These utilities ensure consistent key format across the application and provide
 * a single source of truth for BACnet addressing within the 223P domain.
 */

/**
 * Creates a BACnet device identifier string
 *
 * @param deviceId - The BACnet device ID number
 * @returns Device identifier in format "device,{deviceId}"
 *
 * @example
 * createDeviceIdentifier(123) // Returns: "device,123"
 */
export function createDeviceIdentifier(deviceId: number): string {
  return `device,${deviceId}`
}

/**
 * Creates a BACnet object identifier string
 *
 * @param objectType - The BACnet object type (e.g., "analog-input", "binary-output")
 * @param objectId - The BACnet object instance number
 * @returns Object identifier in format "{objectType},{objectId}"
 *
 * @example
 * createObjectIdentifier("analog-input", 1) // Returns: "analog-input,1"
 * createObjectIdentifier("binary-output", 5) // Returns: "binary-output,5"
 */
export function createObjectIdentifier(
  objectType: string,
  objectId: number
): string {
  return `${objectType},${objectId}`
}

/**
 * Creates a composite key for 223P mapping storage and lookup
 *
 * Combines device identifier and object identifier with a colon separator.
 * This format is used as the primary key in mappings API storage.
 *
 * @param deviceId - The BACnet device ID number
 * @param objectType - The BACnet object type (e.g., "analog-input", "binary-output")
 * @param objectId - The BACnet object instance number
 * @returns Composite key in format "device,{deviceId}:{objectType},{objectId}"
 *
 * @example
 * createCompositeKey(123, "analog-input", 1)
 * // Returns: "device,123:analog-input,1"
 *
 * @example
 * createCompositeKey(456, "binary-output", 5)
 * // Returns: "device,456:binary-output,5"
 */
export function createCompositeKey(
  deviceId: number,
  objectType: string,
  objectId: number
): string {
  const deviceIdentifier = createDeviceIdentifier(deviceId)
  const objectIdentifier = createObjectIdentifier(objectType, objectId)
  return `${deviceIdentifier}:${objectIdentifier}`
}
