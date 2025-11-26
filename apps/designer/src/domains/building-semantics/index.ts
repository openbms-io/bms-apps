/**
 * Building Semantics Domain - Public API
 *
 * This is the ONLY file external modules should import from.
 * All implementation details (adapters, services) are internal.
 *
 * @module building-semantics
 */

// ============================================================================
// TYPES - Domain-agnostic semantic types
// ============================================================================
export type {
  SemanticEquipment,
  BACnetPointData,
  BACnetControllerData,
} from './types'

export type { SpaceType } from './adapters/ashrae-223p/schemas'

export type {
  SystemInstanceDto,
  SystemSummaryDto,
  DeviceDto,
  PropertyDto,
  BaCnetReferenceDto,
  EnrichedBaCnetReferenceDto,
  CreateSystemRequestDto,
  CreateBaCnetReferenceRequestDto,
  TemplateSystemDto,
} from './api/generated/types.gen'

// ============================================================================
// COMPONENTS - UI components for semantic mappings
// ============================================================================
export { SemanticBadge } from './components/semantic-badge'

// System-based mapping components (Story 2-12)
export { BuildingSemanticsModal } from './components/building-semantics-modal'
export { SystemSelector } from './components/system-selector'
export { SystemCreateModal } from './components/system-create-modal'
export { DeviceSelector } from './components/device-selector'
export { PropertySelector } from './components/property-selector'

// ============================================================================
// HOOKS - React hooks for semantic functionality
// ============================================================================

// ============================================================================
// QUERIES - React Query hooks for data fetching
// ============================================================================

// ============================================================================
// DO NOT EXPORT:
// - adapters/* (implementation details)
// - Internal schemas (adapter-specific)
// - Internal services (moved to adapter)
// - view-models/* (internal presentation logic)
// ============================================================================
