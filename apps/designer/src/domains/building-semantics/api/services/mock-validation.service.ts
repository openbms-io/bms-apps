import type { IValidationService } from './validation.service.interface'
import type {
  BACnetPointData,
  DeviceType,
  ValidationResultDTO,
  ValidationErrorDTO,
} from '../../schemas'

/**
 * Mock Validation Service
 *
 * Validates BACnet object type compatibility with 223P device types.
 * Implements basic SHACL-like rules for Epic 1 demo.
 *
 * Validation Rules:
 * - Actuators (Damper, Valve, Fan, Pump) require AO/BO object types
 * - Sensors require AI/BI object types
 *
 * Epic 1: Use this service for all validation
 * Epic 3: Swap to ApiValidationService (real SHACL engine, zero UI changes)
 *
 * @example
 * const service = new MockValidationService();
 * const result = service.validateMapping(
 *   { name: "ZoneTemp", objectType: "analog-input" },
 *   "Sensor"
 * );
 * // result.isValid = true
 */
export class MockValidationService implements IValidationService {
  validateMapping(
    point: BACnetPointData,
    deviceType: DeviceType
  ): ValidationResultDTO {
    const errors: ValidationErrorDTO[] = []
    const objectType = point.objectType.toLowerCase()

    const isActuatorType = this.isActuator(deviceType)
    const isSensorType = this.isSensor(deviceType)

    if (isActuatorType) {
      if (!this.isOutputObjectType(objectType)) {
        errors.push({
          field: 'deviceType',
          message: `${deviceType} requires AO/BO object type, found ${this.formatObjectType(
            objectType
          )}`,
          code: 'INCOMPATIBLE_BACNET_TYPE',
          expectedType: 'analog-output or binary-output',
          actualType: objectType,
        })
      }
    }

    if (isSensorType) {
      if (!this.isInputObjectType(objectType)) {
        errors.push({
          field: 'deviceType',
          message: `${deviceType} requires AI/BI object type, found ${this.formatObjectType(
            objectType
          )}`,
          code: 'INCOMPATIBLE_BACNET_TYPE',
          expectedType: 'analog-input or binary-input',
          actualType: objectType,
        })
      }
    }

    return {
      isValid: errors.length === 0,
      errors,
      warnings: [],
    }
  }

  private isActuator(deviceType: DeviceType): boolean {
    const actuatorTypes = [
      'Damper',
      'Chilled Water Valve',
      'Hot Water Valve',
      'Fan',
      'Exhaust Fan',
      'Chilled Water Pump',
      'Hot Water Pump',
    ]
    return actuatorTypes.includes(deviceType)
  }

  private isSensor(deviceType: DeviceType): boolean {
    return deviceType === 'Sensor'
  }

  private isOutputObjectType(objectType: string): boolean {
    return objectType.includes('output')
  }

  private isInputObjectType(objectType: string): boolean {
    return objectType.includes('input')
  }

  private formatObjectType(objectType: string): string {
    const parts = objectType.split('-')
    return parts.map((part) => part.toUpperCase()).join('')
  }
}

export const mockValidationService = new MockValidationService()
