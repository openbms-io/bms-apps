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

// Enum types from 223P adapter (needed for AI types)
export type {
  SystemType,
  DeviceType,
  ObservableProperty,
  SpaceType,
} from './adapters/ashrae-223p/schemas'

// ============================================================================
// COMPONENTS - UI components for semantic mappings
// ============================================================================
export { MappingPopupModal } from './components/mapping-popup-modal'
export { SemanticBadge } from './components/semantic-badge'
export { PointContextCard } from './components/point-context-card'
export { ConfidenceIndicator } from './components/confidence-indicator'
export { OverallConfidenceBar } from './components/overall-confidence-bar'
export { SearchableSelect } from './components/searchable-select'
export { SpaceComboBox } from './components/space-combobox'
export { SpaceMultiComboBox } from './components/space-multi-combobox'

// ============================================================================
// HOOKS - React hooks for semantic functionality
// ============================================================================
export { useEditMapping } from './hooks/use-edit-mapping'
export { useCreateSemanticModal } from './hooks/use-create-semantic-modal'

// ============================================================================
// QUERIES - React Query hooks for data fetching
// ============================================================================
export { useMappingsQuery } from './api/queries/use-mappings-query'

// ============================================================================
// UTILITIES - Helper functions
// ============================================================================
export { createCompositeKey } from './utils/bacnet-keys'

// ============================================================================
// DO NOT EXPORT:
// - adapters/* (implementation details)
// - Internal schemas (adapter-specific)
// - Internal services (moved to adapter)
// - view-models/* (internal presentation logic)
// ============================================================================
