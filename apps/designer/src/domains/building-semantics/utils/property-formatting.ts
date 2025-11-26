import type { PropertyDto } from '../api/generated/types.gen'

/**
 * Get I/O direction indicator for property.
 *
 * Determines if property is an output (actuatable) or input (sensor).
 * Used for displaying direction in UI labels.
 *
 * @param property - Property DTO with isActuatable flag
 * @returns "[Output]" for actuatable properties, "[Input]" for sensors
 *
 * @example
 * getPropertyIOIndicator({ isActuatable: true, ... }) // "[Output]"
 * getPropertyIOIndicator({ isActuatable: false, ... }) // "[Input]"
 */
export function getPropertyIOIndicator(property: PropertyDto): string {
  return property.isActuatable ? '[Output]' : '[Input]'
}

/**
 * Format enumeration kind for display.
 *
 * Removes "EnumerationKind-" prefix and adds spaces before capital letters
 * to make technical enum names human-readable.
 *
 * @param enumKind - Raw enumeration kind from API
 * @returns Formatted enumeration kind or null if input is null/undefined
 *
 * @example
 * formatEnumerationKind('EnumerationKind-BinaryPV') // "Binary PV"
 * formatEnumerationKind('EnumerationKind-Reliability') // "Reliability"
 * formatEnumerationKind(null) // null
 * formatEnumerationKind(undefined) // null
 */
export function formatEnumerationKind(
  enumKind: string | null | undefined
): string | null {
  if (!enumKind) return null

  return enumKind
    .replace('EnumerationKind-', '')
    .replace(/([a-z])([A-Z])/g, '$1 $2')
    .trim()
}

/**
 * Get compact label with I/O indicator.
 *
 * Combines property label with I/O direction indicator for display in dropdowns.
 *
 * @param property - Property DTO with label and isActuatable
 * @returns Formatted label with I/O indicator
 *
 * @example
 * getPropertyCompactLabel({ label: 'Zone Temperature', isActuatable: false, ... })
 * // "Zone Temperature [Input]"
 *
 * getPropertyCompactLabel({ label: 'Damper Position', isActuatable: true, ... })
 * // "Damper Position [Output]"
 */
export function getPropertyCompactLabel(property: PropertyDto): string {
  const ioIndicator = getPropertyIOIndicator(property)
  return `${property.label} ${ioIndicator}`
}
