/**
 * Building Semantics Domain - Public Types
 *
 * These types define the domain's public API and are implementation-agnostic.
 * They can work with any semantic standard (223P, Brick, Haystack).
 *
 * @module building-semantics/types
 */

// Re-export from ASHRAE 223P adapter (current implementation)
export type {
  SemanticEquipment,
  BACnetPointData,
  BACnetControllerData,
} from './adapters/ashrae-223p/schemas'

// Future: Can add union types when multiple adapters exist
// Example:
// import type { ASHRAE223PEquipment } from './adapters/ashrae-223p/schemas'
// import type { BrickEquipment } from './adapters/brick/schemas'
// export type SemanticEquipment = ASHRAE223PEquipment | BrickEquipment
