import {
  toComputeValue,
  toComputeValueWithParsing,
  toNumber,
  toBoolean,
} from './bacnet-utils'

describe('BACnet Utils', () => {
  describe('toComputeValue', () => {
    it('should convert number to ComputeValue', () => {
      expect(toComputeValue(1945.0)).toEqual({ value: 1945.0, type: 'number' })
      expect(toComputeValue(0)).toEqual({ value: 0, type: 'number' })
      expect(toComputeValue(-25.3)).toEqual({ value: -25.3, type: 'number' })
    })

    it('should convert boolean to ComputeValue', () => {
      expect(toComputeValue(true)).toEqual({ value: true, type: 'boolean' })
      expect(toComputeValue(false)).toEqual({ value: false, type: 'boolean' })
    })

    it('should convert string to ComputeValue without parsing', () => {
      expect(toComputeValue('1945.0')).toEqual({
        value: '1945.0',
        type: 'string',
      })
      expect(toComputeValue('hello')).toEqual({
        value: 'hello',
        type: 'string',
      })
      expect(toComputeValue('72.5')).toEqual({ value: '72.5', type: 'string' })
    })

    it('should return undefined for null/undefined', () => {
      expect(toComputeValue(null)).toBeUndefined()
      expect(toComputeValue(undefined)).toBeUndefined()
    })

    it('should return undefined for objects and arrays', () => {
      expect(toComputeValue({})).toBeUndefined()
      expect(toComputeValue([])).toBeUndefined()
      expect(toComputeValue([1, 2, 3])).toBeUndefined()
    })
  })

  describe('toComputeValueWithParsing', () => {
    it('should convert number to ComputeValue', () => {
      expect(toComputeValueWithParsing(1945.0)).toEqual({
        value: 1945.0,
        type: 'number',
      })
      expect(toComputeValueWithParsing(0)).toEqual({ value: 0, type: 'number' })
      expect(toComputeValueWithParsing(-25.3)).toEqual({
        value: -25.3,
        type: 'number',
      })
    })

    it('should parse numeric strings to number', () => {
      expect(toComputeValueWithParsing('1945.0')).toEqual({
        value: 1945.0,
        type: 'number',
      })
      expect(toComputeValueWithParsing('72.5')).toEqual({
        value: 72.5,
        type: 'number',
      })
      expect(toComputeValueWithParsing('0')).toEqual({
        value: 0,
        type: 'number',
      })
      expect(toComputeValueWithParsing('-25.3')).toEqual({
        value: -25.3,
        type: 'number',
      })
      expect(toComputeValueWithParsing('3.14159')).toEqual({
        value: 3.14159,
        type: 'number',
      })
    })

    it('should keep non-numeric strings as strings', () => {
      expect(toComputeValueWithParsing('hello')).toEqual({
        value: 'hello',
        type: 'string',
      })
      expect(toComputeValueWithParsing('Room 101')).toEqual({
        value: 'Room 101',
        type: 'string',
      })
      expect(toComputeValueWithParsing('123abc')).toEqual({
        value: '123abc',
        type: 'string',
      })
      expect(toComputeValueWithParsing('abc123')).toEqual({
        value: 'abc123',
        type: 'string',
      })
    })

    it('should handle empty and whitespace strings', () => {
      expect(toComputeValueWithParsing('')).toEqual({
        value: '',
        type: 'string',
      })
      expect(toComputeValueWithParsing('  ')).toEqual({
        value: '  ',
        type: 'string',
      })
      expect(toComputeValueWithParsing('\t')).toEqual({
        value: '\t',
        type: 'string',
      })
    })

    it('should handle whitespace around numbers', () => {
      expect(toComputeValueWithParsing('  42  ')).toEqual({
        value: 42,
        type: 'number',
      })
      expect(toComputeValueWithParsing('\t100\n')).toEqual({
        value: 100,
        type: 'number',
      })
    })

    it('should convert boolean to ComputeValue', () => {
      expect(toComputeValueWithParsing(true)).toEqual({
        value: true,
        type: 'boolean',
      })
      expect(toComputeValueWithParsing(false)).toEqual({
        value: false,
        type: 'boolean',
      })
    })

    it('should return undefined for null/undefined', () => {
      expect(toComputeValueWithParsing(null)).toBeUndefined()
      expect(toComputeValueWithParsing(undefined)).toBeUndefined()
    })

    it('should return undefined for objects and arrays', () => {
      expect(toComputeValueWithParsing({})).toBeUndefined()
      expect(toComputeValueWithParsing([])).toBeUndefined()
    })

    it('should handle scientific notation', () => {
      expect(toComputeValueWithParsing('1e3')).toEqual({
        value: 1000,
        type: 'number',
      })
      expect(toComputeValueWithParsing('1.5e-2')).toEqual({
        value: 0.015,
        type: 'number',
      })
    })
  })

  describe('toNumber', () => {
    it('should convert number ComputeValue to number', () => {
      expect(toNumber({ value: 42, type: 'number' })).toBe(42)
      expect(toNumber({ value: 0, type: 'number' })).toBe(0)
      expect(toNumber({ value: -15.5, type: 'number' })).toBe(-15.5)
    })

    it('should convert boolean ComputeValue to number', () => {
      expect(toNumber({ value: true, type: 'boolean' })).toBe(1)
      expect(toNumber({ value: false, type: 'boolean' })).toBe(0)
    })

    it('should parse numeric string ComputeValue', () => {
      expect(toNumber({ value: '123.45', type: 'string' })).toBe(123.45)
      expect(toNumber({ value: '0', type: 'string' })).toBe(0)
      expect(toNumber({ value: '-50', type: 'string' })).toBe(-50)
    })

    it('should return 0 for non-numeric string', () => {
      expect(toNumber({ value: 'hello', type: 'string' })).toBe(0)
      expect(toNumber({ value: '', type: 'string' })).toBe(0)
      expect(toNumber({ value: 'abc123', type: 'string' })).toBe(0)
    })
  })

  describe('toBoolean', () => {
    it('should convert boolean ComputeValue to boolean', () => {
      expect(toBoolean({ value: true, type: 'boolean' })).toBe(true)
      expect(toBoolean({ value: false, type: 'boolean' })).toBe(false)
    })

    it('should convert number ComputeValue to boolean', () => {
      expect(toBoolean({ value: 1, type: 'number' })).toBe(true)
      expect(toBoolean({ value: 0, type: 'number' })).toBe(false)
      expect(toBoolean({ value: -1, type: 'number' })).toBe(true)
      expect(toBoolean({ value: 100, type: 'number' })).toBe(true)
    })

    it('should parse boolean strings', () => {
      expect(toBoolean({ value: 'true', type: 'string' })).toBe(true)
      expect(toBoolean({ value: 'false', type: 'string' })).toBe(false)
      expect(toBoolean({ value: 'TRUE', type: 'string' })).toBe(true)
      expect(toBoolean({ value: 'FALSE', type: 'string' })).toBe(false)
    })

    it('should parse active/inactive strings', () => {
      expect(toBoolean({ value: 'active', type: 'string' })).toBe(true)
      expect(toBoolean({ value: 'inactive', type: 'string' })).toBe(false)
      expect(toBoolean({ value: 'ACTIVE', type: 'string' })).toBe(true)
      expect(toBoolean({ value: 'INACTIVE', type: 'string' })).toBe(false)
    })

    it('should parse numeric strings', () => {
      expect(toBoolean({ value: '1', type: 'string' })).toBe(true)
      expect(toBoolean({ value: '0', type: 'string' })).toBe(false)
    })

    it('should fallback to Boolean() for other strings', () => {
      expect(toBoolean({ value: 'hello', type: 'string' })).toBe(true)
      expect(toBoolean({ value: '', type: 'string' })).toBe(false)
    })
  })
})
