/**
 * ASHRAE 223P Services - Public API
 *
 * Re-exports service interfaces and implementations from api/services.
 * Validation service stays here (UI-only, not swappable).
 */

export type { IBuildingMOTIFService } from '../api/services/interfaces/buildingmotif'
export {
  MockBuildingMOTIFService,
  mockBuildingMOTIFService,
} from '../api/services/mock-buildingmotif.service'

export type { IAISuggestionService } from '../api/services/interfaces/ai-suggestion'
export {
  MockAISuggestionService,
  mockAISuggestionService,
} from '../api/services/mock-ai-suggestion.service'

export type { ISpaceService } from '../api/services/space.service.interface'
export {
  MockSpaceService,
  mockSpaceService,
} from '../api/services/mock-space.service'

export type { IValidationService } from '../api/services/validation.service.interface'
export {
  MockValidationService,
  mockValidationService,
} from '../api/services/mock-validation.service'
