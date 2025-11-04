import { useMemo } from 'react'
import { useAISuggestionQuery } from '../api/queries/use-ai-suggestion-query'
import { useMappingsQuery } from '../api/queries/use-mappings-query'
import { useSpacesQuery } from '../api/queries/use-spaces-query'
import type {
  BACnetPointData,
  SemanticEquipment,
  SpaceDTO,
} from '../adapters/ashrae-223p/schemas'
import type {
  Equipment223PRecommendation,
  FieldRecommendation,
  SpaceRecommendation,
} from '@/lib/ai'

function extractDevicePrefix(pointName: string): string | null {
  const match = pointName.match(/^([A-Z]+-[\d-]+)/)
  return match ? match[1] : null
}

function findPreviousMappingFromSameDevice(
  point: BACnetPointData,
  existingMappings?: Map<string, SemanticEquipment>
): { mapping: SemanticEquipment; sourcePointId: string } | null {
  if (!existingMappings || !point.name) {
    return null
  }

  const currentDevicePrefix = extractDevicePrefix(point.name)
  if (!currentDevicePrefix) {
    return null
  }

  for (const [pointId, mapping] of existingMappings) {
    if (pointId === point.pointId) {
      continue
    }

    const mappedPointName = mapping.externalReference?.objectName
    if (!mappedPointName) {
      continue
    }

    const mappedDevicePrefix = extractDevicePrefix(mappedPointName)
    if (mappedDevicePrefix === currentDevicePrefix) {
      return { mapping, sourcePointId: pointId }
    }
  }

  return null
}

function resolvePhysicalSpace(
  spaceId: string,
  spaces?: SpaceDTO[]
): FieldRecommendation<SpaceRecommendation> | undefined {
  const space = spaces?.find((s) => s.id === spaceId)
  if (!space) return undefined

  return {
    value: { id: spaceId, label: space.rdfsLabel, type: space.spaceType },
    confidence: 100,
    reasoning: 'Auto-filled from previous mapping',
    alternatives: [],
  }
}

function resolveDomainSpaces(
  spaceIds: string[],
  spaces?: SpaceDTO[]
): FieldRecommendation<SpaceRecommendation>[] | undefined {
  const resolved = spaceIds
    .map((id) => {
      const space = spaces?.find((s) => s.id === id)
      if (!space) return null

      return {
        value: { id, label: space.rdfsLabel, type: space.spaceType },
        confidence: 100,
        reasoning: 'Auto-filled from previous mapping',
        alternatives: [],
      } as FieldRecommendation<SpaceRecommendation>
    })
    .filter((s): s is FieldRecommendation<SpaceRecommendation> => s !== null)

  return resolved.length > 0 ? resolved : undefined
}

function applyAutoFill(
  baseRecommendation: Equipment223PRecommendation,
  previousMapping: { mapping: SemanticEquipment; sourcePointId: string },
  spaces?: SpaceDTO[]
): Equipment223PRecommendation {
  return {
    ...baseRecommendation,
    equipmentType: {
      value: previousMapping.mapping.equipmentType,
      confidence: 100,
      reasoning: 'Auto-filled from previous point on same device',
      alternatives: [],
    },
    physicalSpace: previousMapping.mapping.physicalSpaceId
      ? resolvePhysicalSpace(previousMapping.mapping.physicalSpaceId, spaces)
      : baseRecommendation.physicalSpace,
    domainSpaces: previousMapping.mapping.domainSpaceIds
      ? resolveDomainSpaces(previousMapping.mapping.domainSpaceIds, spaces)
      : baseRecommendation.domainSpaces,
    autoFillSource: previousMapping.sourcePointId,
  }
}

export function useMappingSuggestionViewModel(
  projectId: string | undefined,
  point: BACnetPointData | null
) {
  const { data: aiSuggestion } = useAISuggestionQuery(projectId, point)
  const { data: mappings } = useMappingsQuery(projectId)
  const { data: spaces } = useSpacesQuery(projectId)

  return useMemo(() => {
    if (!aiSuggestion || !point) return null

    const previousMapping = findPreviousMappingFromSameDevice(point, mappings)

    if (previousMapping) {
      return applyAutoFill(aiSuggestion, previousMapping, spaces)
    }

    return aiSuggestion
  }, [aiSuggestion, point, mappings, spaces])
}
