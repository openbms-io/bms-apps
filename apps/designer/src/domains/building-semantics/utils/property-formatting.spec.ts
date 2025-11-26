import {
  getPropertyIOIndicator,
  formatEnumerationKind,
  getPropertyCompactLabel,
} from './property-formatting'
import type { PropertyDto } from '../api/generated/types.gen'

describe('property-formatting', () => {
  describe('getPropertyIOIndicator', () => {
    it('should return [Output] for actuatable properties', () => {
      const property = {
        propertyUri: 'test',
        label: 'Test',
        isActuatable: true,
      } as PropertyDto

      expect(getPropertyIOIndicator(property)).toBe('[Output]')
    })

    it('should return [Input] for non-actuatable properties', () => {
      const property = {
        propertyUri: 'test',
        label: 'Test',
        isActuatable: false,
      } as PropertyDto

      expect(getPropertyIOIndicator(property)).toBe('[Input]')
    })
  })

  describe('formatEnumerationKind', () => {
    it('should format EnumerationKind-BinaryPV correctly', () => {
      expect(formatEnumerationKind('EnumerationKind-BinaryPV')).toBe(
        'Binary PV'
      )
    })

    it('should format EnumerationKind-Reliability correctly', () => {
      expect(formatEnumerationKind('EnumerationKind-Reliability')).toBe(
        'Reliability'
      )
    })

    it('should format EnumerationKind-StatusFlags correctly', () => {
      expect(formatEnumerationKind('EnumerationKind-StatusFlags')).toBe(
        'Status Flags'
      )
    })

    it('should handle string without EnumerationKind prefix', () => {
      expect(formatEnumerationKind('BinaryPV')).toBe('Binary PV')
    })

    it('should handle single word enums', () => {
      expect(formatEnumerationKind('EnumerationKind-Active')).toBe('Active')
    })

    it('should return null for null input', () => {
      expect(formatEnumerationKind(null)).toBeNull()
    })

    it('should return null for undefined input', () => {
      expect(formatEnumerationKind(undefined)).toBeNull()
    })

    it('should return null for empty string', () => {
      expect(formatEnumerationKind('')).toBeNull()
    })
  })

  describe('getPropertyCompactLabel', () => {
    it('should format sensor property with [Input] indicator', () => {
      const property = {
        propertyUri: 'test',
        label: 'Zone Temperature',
        isActuatable: false,
      } as PropertyDto

      expect(getPropertyCompactLabel(property)).toBe('Zone Temperature [Input]')
    })

    it('should format actuator property with [Output] indicator', () => {
      const property = {
        propertyUri: 'test',
        label: 'Damper Position',
        isActuatable: true,
      } as PropertyDto

      expect(getPropertyCompactLabel(property)).toBe('Damper Position [Output]')
    })

    it('should handle properties with special characters in label', () => {
      const property = {
        propertyUri: 'test',
        label: 'CO₂ Level',
        isActuatable: false,
      } as PropertyDto

      expect(getPropertyCompactLabel(property)).toBe('CO₂ Level [Input]')
    })

    it('should handle properties with numbers in label', () => {
      const property = {
        propertyUri: 'test',
        label: 'VAV-2-01 Airflow',
        isActuatable: false,
      } as PropertyDto

      expect(getPropertyCompactLabel(property)).toBe('VAV-2-01 Airflow [Input]')
    })
  })
})
