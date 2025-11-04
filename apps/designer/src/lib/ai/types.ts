import type {
  SystemType,
  DeviceType,
  ObservableProperty,
  SpaceType,
} from '@/domains/223p/schemas'

export interface FieldRecommendation<T> {
  value: T
  confidence: number
  reasoning: string
  alternatives: Array<{
    value: T
    confidence: number
  }>
}

export interface SpaceRecommendation {
  id: string
  label: string
  type: SpaceType
}

export interface Equipment223PRecommendation {
  equipmentType: FieldRecommendation<SystemType>
  physicalSpace?: FieldRecommendation<SpaceRecommendation>
  domainSpaces?: FieldRecommendation<SpaceRecommendation>[]
  deviceType: FieldRecommendation<DeviceType>
  observableProperty: FieldRecommendation<ObservableProperty>
  overallConfidence: number
  autoFillSource?: string
}
