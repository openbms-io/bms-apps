import type { IAISuggestionService } from './interfaces/ai-suggestion'
import type {
  BACnetPointData,
  SystemType,
  DeviceType,
  ObservableProperty,
} from '../schemas'
import type { Equipment223PRecommendation } from '@/lib/ai'

export class MockAISuggestionService implements IAISuggestionService {
  suggestMapping(point: BACnetPointData): Equipment223PRecommendation {
    return this.generateAIRecommendation(point)
  }

  private generateAIRecommendation(
    point: BACnetPointData
  ): Equipment223PRecommendation {
    const pointName = point.name || ''
    const nameLower = pointName.toLowerCase()
    const objectType = point.objectType.toLowerCase()

    let equipmentType: SystemType = 'VAV Reheat Terminal Unit'
    let deviceType: DeviceType = 'Sensor'
    let observableProperty: ObservableProperty = 'air-temperature'
    let equipmentConfidence = 85
    let deviceConfidence = 90
    let propertyConfidence = 88

    if (nameLower.includes('vav')) {
      equipmentType = 'VAV Reheat Terminal Unit'
      equipmentConfidence = 94

      if (nameLower.includes('temp')) {
        deviceType = 'Sensor'
        observableProperty = 'air-temperature'
        propertyConfidence = 92
      } else if (nameLower.includes('damper')) {
        deviceType = 'Damper'
        observableProperty = 'static-pressure'
        deviceConfidence = 93
        propertyConfidence = 91
      }
    } else if (nameLower.includes('ahu')) {
      equipmentType = 'Makeup Air Unit'
      equipmentConfidence = 96

      if (nameLower.includes('supply')) {
        deviceType = 'Sensor'
        observableProperty = 'air-temperature'
      } else if (nameLower.includes('fan')) {
        deviceType = 'Fan'
        observableProperty = 'vfd-frequency'
      }
    }

    return {
      equipmentType: {
        value: equipmentType,
        confidence: equipmentConfidence,
        reasoning: `Pattern match on "${pointName}"`,
        alternatives: [
          { value: 'Makeup Air Unit', confidence: 75 },
          { value: 'Exhaust Air Unit', confidence: 65 },
        ],
      },
      deviceType: {
        value: deviceType,
        confidence: deviceConfidence,
        reasoning: `Based on object type "${objectType}" and name pattern`,
        alternatives: [{ value: 'Damper', confidence: 70 }],
      },
      observableProperty: {
        value: observableProperty,
        confidence: propertyConfidence,
        reasoning: `Inferred from point name and device type`,
        alternatives: [{ value: 'relative-humidity', confidence: 60 }],
      },
      overallConfidence: Math.round(
        (equipmentConfidence + deviceConfidence + propertyConfidence) / 3
      ),
    }
  }
}

export const mockAISuggestionService = new MockAISuggestionService()
