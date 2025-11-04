/**
 * ASHRAE 223P Services - Public API
 *
 * Re-exports service interfaces and implementations from adapters/ashrae-223p/services.
 * These are adapter-specific implementations.
 */

export type { IBuildingMOTIFService } from '../adapters/ashrae-223p/services/interfaces/buildingmotif'
export {
  MockBuildingMOTIFService,
  mockBuildingMOTIFService,
} from '../adapters/ashrae-223p/services/mock-buildingmotif.service'

export type { IAISuggestionService } from '../adapters/ashrae-223p/services/interfaces/ai-suggestion'
export {
  MockAISuggestionService,
  mockAISuggestionService,
} from '../adapters/ashrae-223p/services/mock-ai-suggestion.service'

export type { ISpaceService } from '../adapters/ashrae-223p/services/space.service.interface'
export {
  MockSpaceService,
  mockSpaceService,
} from '../adapters/ashrae-223p/services/mock-space.service'

export type { IValidationService } from '../adapters/ashrae-223p/services/validation.service.interface'
export {
  MockValidationService,
  mockValidationService,
} from '../adapters/ashrae-223p/services/mock-validation.service'
