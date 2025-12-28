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

describe('POST /api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/ai/suggestions/confirm', () => {
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

  it('confirms mapping successfully', async () => {
    const mockService = createMockService()
    mockService.confirmMapping.mockResolvedValue(undefined)
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions/confirm', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        mapping: {
          pointPattern: 'VAV-*_ZoneTemp',
          controllerId: 'controller-123',
          step: 'system',
          selectedId: 'vav-reheat-system',
          wasOverridden: false,
        },
      }),
    }) as any

    const response = await POST(request, { params: createParams() })
    const json = await response.json()

    expect(response.status).toBe(200)
    expect(json.success).toBe(true)
  })

  it('passes path params to service', async () => {
    const mockService = createMockService()
    mockService.confirmMapping.mockResolvedValue(undefined)
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions/confirm', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        mapping: {
          pointPattern: 'VAV-*_ZoneTemp',
          controllerId: 'controller-123',
          step: 'system',
          selectedId: 'vav-reheat-system',
          wasOverridden: false,
        },
      }),
    }) as any

    await POST(request, { params: createParams() })

    expect(mockService.confirmMapping).toHaveBeenCalledWith(
      expect.objectContaining({
        orgId: 'org-123',
        projectId: 'proj-789',
      })
    )
  })

  it('passes wasOverridden flag to service', async () => {
    const mockService = createMockService()
    mockService.confirmMapping.mockResolvedValue(undefined)
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions/confirm', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        mapping: {
          pointPattern: 'AHU-*_SupplyFan',
          controllerId: 'controller-456',
          step: 'device',
          selectedId: 'supply-fan-device',
          wasOverridden: true,
        },
      }),
    }) as any

    await POST(request, { params: createParams() })

    expect(mockService.confirmMapping).toHaveBeenCalledWith(
      expect.objectContaining({
        mapping: expect.objectContaining({
          wasOverridden: true,
        }),
      })
    )
  })

  it('validates request with DTO schema', async () => {
    const request = new Request('http://localhost/api/ai/suggestions/confirm', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        mapping: {
          pointPattern: 'VAV-*_ZoneTemp',
          controllerId: 'controller-123',
          step: 'invalid-step',
          selectedId: 'vav-reheat-system',
          wasOverridden: false,
        },
      }),
    }) as any

    const response = await POST(request, { params: createParams() })

    expect(response.status).toBe(400)
  })

  it('returns 503 when Mem0 unavailable', async () => {
    const mockService = createMockService()
    mockService.confirmMapping.mockRejectedValue(
      new Error('MEM0_API_KEY environment variable is required')
    )
    mockCreateAISuggestionService.mockReturnValue(mockService)

    const request = new Request('http://localhost/api/ai/suggestions/confirm', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        mapping: {
          pointPattern: 'VAV-*_ZoneTemp',
          controllerId: 'controller-123',
          step: 'system',
          selectedId: 'vav-reheat-system',
          wasOverridden: false,
        },
      }),
    }) as any

    const response = await POST(request, { params: createParams() })
    const json = await response.json()

    expect(response.status).toBe(503)
    expect(json.success).toBe(false)
    expect(json.error).toBe('AI service unavailable')
  })
})
