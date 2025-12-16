import { BacnetProperties, type PresentValue } from '@/types/bacnet-properties'
export {
  toComputeValue,
  toComputeValueWithParsing,
  toNumber,
  toBoolean,
} from './compute-value-utils'

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
