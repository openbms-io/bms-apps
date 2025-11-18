import type { IAISuggestionService } from './interfaces/ai-suggestion'
import type { BACnetPointData } from '../schemas'
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

    let equipmentType = 'vav-reheat'
    let deviceType = 'sensor'
    let observableProperty = 'air-temperature'
    let equipmentConfidence = 85
    let deviceConfidence = 90
    let propertyConfidence = 88

    if (nameLower.includes('vav')) {
      equipmentType = 'vav-reheat'
      equipmentConfidence = 94

      if (nameLower.includes('temp')) {
        deviceType = 'sensor'
        observableProperty = 'air-temperature'
        propertyConfidence = 92
      } else if (nameLower.includes('damper')) {
        deviceType = 'damper'
        observableProperty = 'damper-command'
        deviceConfidence = 93
        propertyConfidence = 91
      }
    } else if (nameLower.includes('ahu')) {
      equipmentType = 'makeup-air-unit'
      equipmentConfidence = 96

      if (nameLower.includes('supply')) {
        deviceType = 'sensor'
        observableProperty = 'air-temperature'
      } else if (nameLower.includes('fan')) {
        deviceType = 'fan'
        observableProperty = 'vfd-speed'
      }
    }

    return {
      equipmentTypeId: {
        id: equipmentType,
        confidence: equipmentConfidence,
        reasoning: `Pattern match on "${pointName}"`,
        alternatives: [
          { id: 'makeup-air-unit', confidence: 75 },
          { id: 'exhaust-air-unit', confidence: 65 },
        ],
      },
      deviceTypeId: {
        id: deviceType,
        confidence: deviceConfidence,
        reasoning: `Based on object type "${objectType}" and name pattern`,
        alternatives: [{ id: 'damper', confidence: 70 }],
      },
      propertyId: {
        id: observableProperty,
        confidence: propertyConfidence,
        reasoning: `Inferred from point name and device type`,
        alternatives: [{ id: 'relative-humidity', confidence: 60 }],
      },
      overallConfidence: Math.round(
        (equipmentConfidence + deviceConfidence + propertyConfidence) / 3
      ),
    }
  }
}

export const mockAISuggestionService = new MockAISuggestionService()
