import { BacnetProperties, type PresentValue } from '@/types/bacnet-properties'
import { ComputeValue } from '@/types/infrastructure'

/**
 * Prepares discovered properties for multistate objects by converting
 * stateText array to 1-based indexing per BACnet specification.
 *
 * BACnet multistate values are 1-indexed, so we add null at index 0
 * to allow direct array access: stateText[1] = first state
 *
 * @param properties - The discovered properties from BACnet device
 * @returns Properties with stateText converted to 1-based indexing
 */
export function prepareMultistateProperties(
  properties: BacnetProperties
): BacnetProperties {
  const prepared = { ...properties }

  // Convert stateText to 1-indexed if present
  if (
    Array.isArray(prepared.stateText) &&
    prepared.stateText.length > 0 &&
    prepared.stateText[0] !== null
  ) {
    // Add null at index 0 for BACnet 1-based indexing
    prepared.stateText = [null, ...prepared.stateText]

    // Convert presentValue from number to stateText during initialization
    if (prepared.presentValue !== undefined) {
      prepared.presentValue = convertMultistatePresentValue({
        presentValue: prepared.presentValue,
        stateText: prepared.stateText,
      })
    }
  }

  return prepared
}

/**
 * Convert multistate presentValue from numeric index to state text
 */
export function convertMultistatePresentValue({
  presentValue,
  stateText,
}: {
  presentValue: PresentValue | undefined
  stateText?: (string | null)[]
}): PresentValue | undefined {
  if (!stateText || stateText.length <= 1 || presentValue === undefined) {
    return presentValue
  }

  // Early return if not a numeric value
  if (typeof presentValue === 'boolean') {
    return presentValue
  }

  // Convert to number index
  const index =
    typeof presentValue === 'string' ? parseInt(presentValue) : presentValue

  // Return state text or fallback to presentValue
  return stateText[index] ?? presentValue
}

/**
 * Convert a raw value to ComputeValue with type metadata
 */
export function toComputeValue(value: unknown): ComputeValue | undefined {
  if (typeof value === 'number') {
    return { value, type: 'number' }
  }
  if (typeof value === 'boolean') {
    return { value, type: 'boolean' }
  }
  if (typeof value === 'string') {
    return { value, type: 'string' }
  }
  return undefined
}

/**
 * Convert ComputeValue to number for calculations
 */
export function toNumber(cv: ComputeValue): number {
  if (cv.type === 'number') {
    return cv.value as number
  }
  if (cv.type === 'boolean') {
    return cv.value ? 1 : 0
  }
  // String: try to parse, default to 0
  const parsed = Number(cv.value)
  return isNaN(parsed) ? 0 : parsed
}

/**
 * Convert ComputeValue to boolean for logic
 */
export function toBoolean(cv: ComputeValue): boolean {
  if (cv.type === 'boolean') {
    return cv.value as boolean
  }
  if (cv.type === 'number') {
    return (cv.value as number) !== 0
  }
  // String: check common boolean strings
  const str = (cv.value as string).toLowerCase()
  if (str === 'true' || str === 'active' || str === '1') return true
  if (str === 'false' || str === 'inactive' || str === '0') return false
  return Boolean(cv.value)
}
