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

    let equipmentType = 'urn:ashrae:223p:VAVReheatTerminalUnit'
    let deviceType = 'urn:ashrae:223p:TemperatureSensor'
    let observableProperty = 'urn:ashrae:223p:AirTemperature'
    let equipmentConfidence = 85
    let deviceConfidence = 90
    let propertyConfidence = 88

    if (nameLower.includes('vav')) {
      equipmentType = 'urn:ashrae:223p:VAVReheatTerminalUnit'
      equipmentConfidence = 94

      if (nameLower.includes('temp')) {
        deviceType = 'urn:ashrae:223p:TemperatureSensor'
        observableProperty = 'urn:ashrae:223p:AirTemperature'
        propertyConfidence = 92
      } else if (nameLower.includes('damper')) {
        deviceType = 'urn:ashrae:223p:Damper'
        observableProperty = 'urn:ashrae:223p:DamperCommand'
        deviceConfidence = 93
        propertyConfidence = 91
      }
    } else if (nameLower.includes('ahu')) {
      equipmentType = 'urn:ashrae:223p:AirHandlingUnit'
      equipmentConfidence = 96

      if (nameLower.includes('supply')) {
        deviceType = 'urn:ashrae:223p:TemperatureSensor'
        observableProperty = 'urn:ashrae:223p:AirTemperature'
      } else if (nameLower.includes('fan')) {
        deviceType = 'urn:ashrae:223p:Fan'
        observableProperty = 'urn:ashrae:223p:VFDSpeed'
      }
    }

    return {
      equipmentTypeId: {
        id: equipmentType,
        confidence: equipmentConfidence,
        reasoning: `Pattern match on "${pointName}"`,
        alternatives: [
          { id: 'urn:ashrae:223p:AirHandlingUnit', confidence: 75 },
          { id: 'urn:ashrae:223p:ExhaustAirUnit', confidence: 65 },
        ],
      },
      deviceTypeId: {
        id: deviceType,
        confidence: deviceConfidence,
        reasoning: `Based on object type "${objectType}" and name pattern`,
        alternatives: [{ id: 'urn:ashrae:223p:Damper', confidence: 70 }],
      },
      propertyId: {
        id: observableProperty,
        confidence: propertyConfidence,
        reasoning: `Inferred from point name and device type`,
        alternatives: [
          { id: 'urn:ashrae:223p:RelativeHumidity', confidence: 60 },
        ],
      },
      overallConfidence: Math.round(
        (equipmentConfidence + deviceConfidence + propertyConfidence) / 3
      ),
    }
  }
}

export const mockAISuggestionService = new MockAISuggestionService()
