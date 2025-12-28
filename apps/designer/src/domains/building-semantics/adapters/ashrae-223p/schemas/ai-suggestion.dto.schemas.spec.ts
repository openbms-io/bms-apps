import {
  AIPointDTOSchema,
  AISuggestionRequestDTOSchema,
  AISuggestionResponseDTOSchema,
  AISuggestionConfirmRequestDTOSchema,
  type AISuggestionRequestDTO,
  type AISuggestionResponseDTO,
  type AISuggestionConfirmRequestDTO,
} from './ai-suggestion.dto.schemas'

describe('AI Suggestion DTO Schemas', () => {
  describe('AIPointDTOSchema', () => {
    it('validates point with required fields', () => {
      const point = {
        id: 'point-123',
        name: 'VAV-2-01_ZoneTemp',
        objectType: 'analog-input',
        objectId: 1,
        controllerId: 'controller-123',
      }

      const result = AIPointDTOSchema.safeParse(point)
      expect(result.success).toBe(true)
    })

    it('validates point with optional fields', () => {
      const point = {
        id: 'point-123',
        name: 'VAV-2-01_ZoneTemp',
        objectType: 'analog-input',
        objectId: 1,
        controllerId: 'controller-123',
        description: 'Zone Temperature Sensor',
        units: 'degreesFahrenheit',
        presentValue: 72.5,
        stateText: ['Off', 'On'],
      }

      const result = AIPointDTOSchema.safeParse(point)
      expect(result.success).toBe(true)
    })

    it('rejects point missing required fields', () => {
      const point = {
        name: 'VAV-2-01_ZoneTemp',
        objectType: 'analog-input',
      }

      const result = AIPointDTOSchema.safeParse(point)
      expect(result.success).toBe(false)
    })
  })

  describe('AISuggestionRequestDTOSchema', () => {
    it('validates request with required fields', () => {
      const request: AISuggestionRequestDTO = {
        step: 'system',
        point: {
          id: 'point-123',
          name: 'VAV-2-01_ZoneTemp',
          objectType: 'analog-input',
          objectId: 1,
          controllerId: 'controller-123',
        },
        candidates: [
          { id: 'vav-reheat-system', label: 'VAV Reheat System' },
          { id: 'vav-cooling-only', label: 'VAV Cooling Only' },
        ],
      }

      const result = AISuggestionRequestDTOSchema.safeParse(request)
      expect(result.success).toBe(true)
    })

    it('validates all step types', () => {
      const steps = ['system', 'device', 'property'] as const

      for (const step of steps) {
        const request = {
          step,
          point: {
            id: 'point-123',
            name: 'VAV-2-01_ZoneTemp',
            objectType: 'analog-input',
            objectId: 1,
            controllerId: 'controller-123',
          },
          candidates: [{ id: 'candidate-1', label: 'Candidate 1' }],
        }

        const result = AISuggestionRequestDTOSchema.safeParse(request)
        expect(result.success).toBe(true)
      }
    })

    it('validates request with selection context', () => {
      const request = {
        step: 'property',
        point: {
          id: 'point-123',
          name: 'VAV-2-01_ZoneTemp',
          objectType: 'analog-input',
          objectId: 1,
          controllerId: 'controller-123',
        },
        candidates: [{ id: 'property-1', label: 'Property 1' }],
        selectionContext: {
          systemId: 'selected-system',
          deviceId: 'selected-device',
        },
      }

      const result = AISuggestionRequestDTOSchema.safeParse(request)
      expect(result.success).toBe(true)
    })

    it('rejects invalid step type', () => {
      const request = {
        step: 'invalid',
        point: {
          id: 'point-123',
          name: 'VAV-2-01_ZoneTemp',
          objectType: 'analog-input',
          objectId: 1,
          controllerId: 'controller-123',
        },
        candidates: [{ id: 'candidate-1', label: 'Candidate 1' }],
      }

      const result = AISuggestionRequestDTOSchema.safeParse(request)
      expect(result.success).toBe(false)
    })

    it('rejects candidates array exceeding max 10', () => {
      const request = {
        step: 'system',
        point: {
          id: 'point-123',
          name: 'VAV-2-01_ZoneTemp',
          objectType: 'analog-input',
          objectId: 1,
          controllerId: 'controller-123',
        },
        candidates: Array(11).fill({ id: 'candidate', label: 'Candidate' }),
      }

      const result = AISuggestionRequestDTOSchema.safeParse(request)
      expect(result.success).toBe(false)
    })
  })

  describe('AISuggestionResponseDTOSchema', () => {
    it('validates successful response', () => {
      const response: AISuggestionResponseDTO = {
        success: true,
        data: {
          selectedId: 'vav-reheat-system',
          confidence: 0.92,
          reasoning: 'Based on point naming pattern',
          alternatives: [{ id: 'vav-cooling-only', confidence: 0.65 }],
        },
      }

      const result = AISuggestionResponseDTOSchema.safeParse(response)
      expect(result.success).toBe(true)
    })

    it('validates error response', () => {
      const response: AISuggestionResponseDTO = {
        success: false,
        error: 'AI service unavailable',
      }

      const result = AISuggestionResponseDTOSchema.safeParse(response)
      expect(result.success).toBe(true)
    })

    it('rejects confidence outside 0-1 range', () => {
      const response = {
        success: true,
        data: {
          selectedId: 'vav-reheat-system',
          confidence: 1.5,
          reasoning: 'Invalid confidence',
          alternatives: [],
        },
      }

      const result = AISuggestionResponseDTOSchema.safeParse(response)
      expect(result.success).toBe(false)
    })
  })

  describe('AISuggestionConfirmRequestDTOSchema', () => {
    it('validates confirm request', () => {
      const request: AISuggestionConfirmRequestDTO = {
        mapping: {
          pointPattern: 'VAV-*_ZoneTemp',
          controllerId: 'controller-123',
          step: 'system',
          selectedId: 'vav-reheat-system',
          wasOverridden: false,
        },
      }

      const result = AISuggestionConfirmRequestDTOSchema.safeParse(request)
      expect(result.success).toBe(true)
    })

    it('validates confirm request with wasOverridden true', () => {
      const request = {
        mapping: {
          pointPattern: 'AHU-*_SupplyFan',
          controllerId: 'controller-456',
          step: 'device',
          selectedId: 'supply-fan-device',
          wasOverridden: true,
        },
      }

      const result = AISuggestionConfirmRequestDTOSchema.safeParse(request)
      expect(result.success).toBe(true)
    })

    it('validates all step types in mapping', () => {
      const steps = ['system', 'device', 'property'] as const

      for (const step of steps) {
        const request = {
          mapping: {
            pointPattern: 'VAV-*_ZoneTemp',
            controllerId: 'controller-123',
            step,
            selectedId: 'selected-id',
            wasOverridden: false,
          },
        }

        const result = AISuggestionConfirmRequestDTOSchema.safeParse(request)
        expect(result.success).toBe(true)
      }
    })

    it('rejects invalid step in mapping', () => {
      const request = {
        mapping: {
          pointPattern: 'VAV-*_ZoneTemp',
          controllerId: 'controller-123',
          step: 'invalid',
          selectedId: 'selected-id',
          wasOverridden: false,
        },
      }

      const result = AISuggestionConfirmRequestDTOSchema.safeParse(request)
      expect(result.success).toBe(false)
    })
  })
})
