/**
 * ASHRAE 223P Schemas - Public API
 *
 * Exports all schemas, DTOs, and ViewModels for 223P domain.
 * Use this index for all imports outside the schemas directory.
 */

// Enum Schemas and Types
export {
  SystemTypeSchema,
  DeviceTypeSchema,
  ObservablePropertySchema,
  SpaceTypeSchema,
  ConnectionPointTypeSchema,
  BacnetObjectTypeSchema,
  ValidationErrorCodeSchema,
  type SystemType,
  type DeviceType,
  type ObservableProperty,
  type SpaceType,
  type ConnectionPointType,
  type BacnetObjectType,
  type ValidationErrorCode,
} from './enum.schemas'

// DTO Schemas and Types
export {
  BACnetExternalReferenceDTOSchema,
  SpaceDTOSchema,
  SemanticEquipmentSchema,
  ValidationErrorDTOSchema,
  ValidationResultDTOSchema,
  type BACnetExternalReferenceDTO,
  type BACnetPointData,
  type BACnetControllerData,
  type SpaceDTO,
  type SemanticEquipment,
  type ValidationErrorDTO,
  type ValidationResultDTO,
} from './dto.schemas'
