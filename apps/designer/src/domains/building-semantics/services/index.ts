/**
 * ASHRAE 223P Services - Public API
 *
 * Re-exports service interfaces and implementations from adapters/ashrae-223p/services.
 * Designer-only services (not backed by FastAPI).
 */

export type { IAISuggestionService } from '../adapters/ashrae-223p/services/interfaces/ai-suggestion'
export {
  MockAISuggestionService,
  mockAISuggestionService,
} from '../adapters/ashrae-223p/services/mock-ai-suggestion.service'
