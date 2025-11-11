import type { Equipment223PRecommendation } from '@/lib/ai'
import type { BACnetPointData, SemanticEquipment } from '../../schemas'

/**
 * AI Suggestion Service Interface
 *
 * Analyzes BACnet point metadata to suggest ASHRAE 223P semantic mappings.
 * Provides confidence scores and alternative suggestions.
 *
 * Epic 1: Implemented by MockAISuggestionService (pattern matching)
 * Epic 3: Implemented by ApiAISuggestionService (LLM-based)
 *
 * UI components depend on this interface, not the implementation.
 * This enables swapping mock → real API with zero UI changes.
 */
export interface IAISuggestionService {
  /**
   * Generate 223P mapping suggestions based on BACnet point metadata
   *
   * Analyzes point name, object type patterns to suggest:
   * - Equipment type (e.g., "VAV Reheat Terminal Unit")
   * - Device type (e.g., "Sensor", "Damper")
   * - Observable property (e.g., "air-temperature")
   *
   * Each suggestion includes confidence score (0-100) and reasoning.
   *
   * Epic 1: Pattern matching on point name
   * Epic 3: LLM-based inference
   *
   * @param point - BACnet point with name, objectType
   * @returns Recommendation with confidence scores and alternatives
   *
   * @example
   * const point = { name: "VAV-2-01_ZoneTemp", objectType: "analog-input" };
   * const suggestion = service.suggestMapping(point);
   * // suggestion.deviceType.value = "Sensor"
   * // suggestion.observableProperty.value = "air-temperature"
   */
  suggestMapping(point: BACnetPointData): Equipment223PRecommendation
}
