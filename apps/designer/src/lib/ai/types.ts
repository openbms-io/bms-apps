import type { SpaceType } from '@/domains/building-semantics'

export interface FieldRecommendation<T> {
  id: T
  confidence: number
  reasoning: string
  alternatives: Array<{
    id: T
    confidence: number
  }>
}

export interface SpaceRecommendation {
  id: string
  label: string
  type: SpaceType
}

export interface Equipment223PRecommendation {
  equipmentTypeId: FieldRecommendation<string>
  physicalSpace?: FieldRecommendation<SpaceRecommendation>
  domainSpaces?: FieldRecommendation<SpaceRecommendation>[]
  deviceTypeId: FieldRecommendation<string>
  propertyId: FieldRecommendation<string>
  overallConfidence: number
}
