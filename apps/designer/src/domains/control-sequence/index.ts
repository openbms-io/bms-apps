/**
 * Control Sequence Domain - Public API
 *
 * This is the ONLY file external modules should import from.
 * All implementation details (api, generated) are internal.
 *
 * @module control-sequence
 */

// ============================================================================
// TYPES - Re-export from generated
// ============================================================================
export type {
  ReheatParameters,
  ReheatInputsRequest,
  ReheatOutputs,
  StepRequest,
  StepResponse,
  CreateInstanceResponseReheatParameters,
  GetInstanceResponseReheatParameters,
  UpdateInstanceResponseReheatParameters,
  DeleteInstanceResponse,
  ErrorResponse,
  HealthResponse,
  ValidationRequest,
  ValidationResponse,
} from './api/generated/types.gen'

// ============================================================================
// COMPONENTS (future - Phase 1B)
// ============================================================================
// export { G36ReheatBlock } from './components/g36-reheat-block'

// ============================================================================
// DO NOT EXPORT:
// - api/generated/* directly (use types above)
// - Internal implementation details
// ============================================================================
