import { ComputeValue, MessageValue } from '@/types/infrastructure'

function isMessageValue(value: unknown): value is MessageValue {
  return (
    typeof value === 'number' ||
    typeof value === 'boolean' ||
    typeof value === 'string'
  )
}

/**
 * Convert a raw value to ComputeValue with type metadata
 */
export function toComputeValue(value: unknown): ComputeValue | undefined {
  if (!isMessageValue(value)) {
    return undefined
  }
  if (typeof value === 'number') {
    return { value, type: 'number' }
  }
  if (typeof value === 'boolean') {
    return { value, type: 'boolean' }
  }
  return { value, type: 'string' }
}

/**
 * Convert a raw value to ComputeValue with type metadata,
 * parsing numeric strings to numbers.
 *
 * Use this for BACnet data that may arrive as stringified numbers from MQTT.
 */
export function toComputeValueWithParsing(
  value: unknown
): ComputeValue | undefined {
  if (typeof value === 'number') {
    return { value, type: 'number' }
  }
  if (typeof value === 'boolean') {
    return { value, type: 'boolean' }
  }
  if (typeof value === 'string') {
    const trimmed = value.trim()
    if (trimmed !== '') {
      const parsed = Number(value)
      if (!isNaN(parsed)) {
        return { value: parsed, type: 'number' }
      }
    }
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
