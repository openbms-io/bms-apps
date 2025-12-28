/**
 * @jest-environment node
 */

jest.mock('server-only', () => ({}))
jest.mock('ai', () => ({
  generateObject: jest.fn(),
}))
jest.mock('@ai-sdk/anthropic', () => ({
  createAnthropic: () => (model: string) => ({ provider: 'anthropic', model }),
}))
jest.mock('@ai-sdk/openai', () => ({
  createOpenAI: () => (model: string) => ({ provider: 'openai', model }),
}))
jest.mock('@/lib/server-only/ai', () => ({
  createAISuggestionService: jest.fn(),
}))

import { POST } from './route'
import type { IAISuggestionService } from '@/lib/server-only/ai'

const mockCreateAISuggestionService = jest.requireMock(
  '@/lib/server-only/ai'
).createAISuggestionService

describe('POST /api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/ai/suggestions', () => {
  const createMockService = (): jest.Mocked<IAISuggestionService> => ({
    getSuggestion: jest.fn(),
    confirmMapping: jest.fn(),
  })

  const createParams = () =>
    Promise.resolve({
      orgId: 'org-123',
      siteId: 'site-456',
      projectId: 'proj-789',
    })

  beforeEach(() => {
    jest.clearAllMocks()
  })

  it('returns suggestion on valid request', async () => {
    const mockService = createMockService()
    mockService.getSuggestion.mockResolvedValue({
      selectedId: 'vav-reheat-system',
      confidence: 0.92,
      reasoning: 'Based on point naming pattern',
      alternatives: [{ id: 'vav-cooling-only', confidence: 0.65 }],
    })
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
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
      }),
    }) as any

    const response = await POST(request, { params: createParams() })
    const json = await response.json()

    expect(response.status).toBe(200)
    expect(json.success).toBe(true)
    expect(json.data.selectedId).toBe('vav-reheat-system')
    expect(json.data.confidence).toBe(0.92)
  })

  it('passes path params to service', async () => {
    const mockService = createMockService()
    mockService.getSuggestion.mockResolvedValue({
      selectedId: 'vav-reheat-system',
      confidence: 0.92,
      reasoning: 'test',
      alternatives: [],
    })
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        step: 'system',
        point: {
          id: 'point-123',
          name: 'VAV-2-01_ZoneTemp',
          objectType: 'analog-input',
          objectId: 1,
          controllerId: 'controller-123',
        },
        candidates: [{ id: 'candidate-1', label: 'Candidate 1' }],
      }),
    }) as any

    await POST(request, { params: createParams() })

    expect(mockService.getSuggestion).toHaveBeenCalledWith(
      expect.objectContaining({
        orgId: 'org-123',
        projectId: 'proj-789',
      })
    )
  })

  it('validates request with DTO schema', async () => {
    const request = new Request('http://localhost/api/ai/suggestions', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        step: 'invalid-step',
        point: {
          id: 'point-123',
          name: 'VAV-2-01_ZoneTemp',
          objectType: 'analog-input',
          objectId: 1,
          controllerId: 'controller-123',
        },
        candidates: [{ id: 'candidate-1', label: 'Candidate 1' }],
      }),
    }) as any

    const response = await POST(request, { params: createParams() })

    expect(response.status).toBe(400)
  })

  it('passes selection context to service', async () => {
    const mockService = createMockService()
    mockService.getSuggestion.mockResolvedValue({
      selectedId: 'property-1',
      confidence: 0.88,
      reasoning: 'test',
      alternatives: [],
    })
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
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
      }),
    }) as any

    await POST(request, { params: createParams() })

    expect(mockService.getSuggestion).toHaveBeenCalledWith(
      expect.objectContaining({
        selectionContext: {
          systemId: 'selected-system',
          deviceId: 'selected-device',
        },
      })
    )
  })

  it('returns 503 when AI service unavailable', async () => {
    const mockService = createMockService()
    mockService.getSuggestion.mockRejectedValue(
      new Error('AI_MODEL environment variable is required')
    )
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        step: 'system',
        point: {
          id: 'point-123',
          name: 'VAV-2-01_ZoneTemp',
          objectType: 'analog-input',
          objectId: 1,
          controllerId: 'controller-123',
        },
        candidates: [{ id: 'candidate-1', label: 'Candidate 1' }],
      }),
    }) as any

    const response = await POST(request, { params: createParams() })
    const json = await response.json()

    expect(response.status).toBe(503)
    expect(json.success).toBe(false)
    expect(json.error).toBe('AI service unavailable')
  })
})
