import type { EnrichedBaCnetReferenceDto } from '../api/generated/types.gen'
import type { SemanticEquipment } from '../adapters/ashrae-223p/schemas'

/**
 * Transform BACnet reference to SemanticEquipment for tree display.
 *
 * Creates Map<bacnetPointId, SemanticEquipment> from enriched references.
 * This maintains compatibility with existing tree/badge components.
 */
export function transformBacnetReferencesToMap(
  references: EnrichedBaCnetReferenceDto[]
): Map<string, SemanticEquipment> {
  const map = new Map<string, SemanticEquipment>()

  for (const ref of references) {
    map.set(ref.bacnetPointId, {
      systemLabel: ref.systemLabel,
      deviceLabel: ref.deviceLabel,
      propertyLabel: ref.propertyLabel,
      systemTemplate: ref.systemTemplate,
    })
  }

  return map
}
