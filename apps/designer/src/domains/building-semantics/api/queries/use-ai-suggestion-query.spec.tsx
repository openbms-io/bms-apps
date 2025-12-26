import { renderHook, waitFor } from '@testing-library/react'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { ReactNode } from 'react'
import {
  useSystemSuggestion,
  useDeviceSuggestion,
  usePropertySuggestion,
  useConfirmMapping,
} from './use-ai-suggestion-query'
import type { AIPointDTO } from '../../adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas'

const createWrapper = () => {
  const queryClient = new QueryClient({
    defaultOptions: {
      queries: {
        retry: false,
      },
    },
  })
  return ({ children }: { children: ReactNode }) => (
    <QueryClientProvider client={queryClient}>{children}</QueryClientProvider>
  )
}

const mockPoint: AIPointDTO = {
  name: 'VAV-2-01_ZoneTemp',
  objectType: 'analog-input',
  objectId: 1,
  controllerId: 'controller-123',
}

const mockSuggestionResponse = {
  success: true,
  data: {
    selectedId: 'vav-reheat-system',
    confidence: 0.92,
    reasoning: 'Based on point naming pattern',
    alternatives: [{ id: 'vav-cooling-only', confidence: 0.65 }],
  },
}

describe('AI Suggestion Query Hooks', () => {
  let fetchSpy: jest.SpyInstance

  beforeEach(() => {
    fetchSpy = jest.spyOn(global, 'fetch')
    jest.clearAllMocks()
  })

  afterEach(() => {
    fetchSpy.mockRestore()
  })

  describe('useSystemSuggestion', () => {
    it('is disabled when point is undefined', () => {
      const { result } = renderHook(
        () =>
          useSystemSuggestion({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
            point: undefined,
            candidates: ['candidate-1'],
          }),
        { wrapper: createWrapper() }
      )

      expect(result.current.isLoading).toBe(false)
      expect(result.current.fetchStatus).toBe('idle')
    })

    it('is disabled when candidates is empty', () => {
      const { result } = renderHook(
        () =>
          useSystemSuggestion({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
            point: mockPoint,
            candidates: [],
          }),
        { wrapper: createWrapper() }
      )

      expect(result.current.isLoading).toBe(false)
      expect(result.current.fetchStatus).toBe('idle')
    })

    it('calls API with correct parameters when enabled', async () => {
      fetchSpy.mockResolvedValueOnce({
        ok: true,
        json: async () => mockSuggestionResponse,
      })

      const { result } = renderHook(
        () =>
          useSystemSuggestion({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
            point: mockPoint,
            candidates: ['vav-reheat-system', 'vav-cooling-only'],
          }),
        { wrapper: createWrapper() }
      )

      await waitFor(() => expect(result.current.isSuccess).toBe(true))

      expect(fetchSpy).toHaveBeenCalledWith(
        '/api/organizations/org-123/sites/site-456/projects/proj-789/ai/suggestions',
        expect.objectContaining({
          method: 'POST',
          body: expect.stringContaining('"step":"system"'),
        })
      )
    })
  })

  describe('useDeviceSuggestion', () => {
    it('is disabled when systemId is undefined', () => {
      const { result } = renderHook(
        () =>
          useDeviceSuggestion({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
            point: mockPoint,
            candidates: ['candidate-1'],
            systemId: undefined,
          }),
        { wrapper: createWrapper() }
      )

      expect(result.current.isLoading).toBe(false)
      expect(result.current.fetchStatus).toBe('idle')
    })

    it('calls API with selection context when enabled', async () => {
      fetchSpy.mockResolvedValueOnce({
        ok: true,
        json: async () => mockSuggestionResponse,
      })

      const { result } = renderHook(
        () =>
          useDeviceSuggestion({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
            point: mockPoint,
            candidates: ['device-1'],
            systemId: 'selected-system',
          }),
        { wrapper: createWrapper() }
      )

      await waitFor(() => expect(result.current.isSuccess).toBe(true))

      expect(fetchSpy).toHaveBeenCalledWith(
        expect.any(String),
        expect.objectContaining({
          body: expect.stringContaining('"step":"device"'),
        })
      )

      const callBody = JSON.parse(fetchSpy.mock.calls[0][1].body)
      expect(callBody.selectionContext).toEqual({ systemId: 'selected-system' })
    })
  })

  describe('usePropertySuggestion', () => {
    it('is disabled when deviceId is undefined', () => {
      const { result } = renderHook(
        () =>
          usePropertySuggestion({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
            point: mockPoint,
            candidates: ['candidate-1'],
            systemId: 'system-1',
            deviceId: undefined,
          }),
        { wrapper: createWrapper() }
      )

      expect(result.current.isLoading).toBe(false)
      expect(result.current.fetchStatus).toBe('idle')
    })

    it('calls API with full selection context when enabled', async () => {
      fetchSpy.mockResolvedValueOnce({
        ok: true,
        json: async () => mockSuggestionResponse,
      })

      const { result } = renderHook(
        () =>
          usePropertySuggestion({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
            point: mockPoint,
            candidates: ['property-1'],
            systemId: 'selected-system',
            deviceId: 'selected-device',
          }),
        { wrapper: createWrapper() }
      )

      await waitFor(() => expect(result.current.isSuccess).toBe(true))

      const callBody = JSON.parse(fetchSpy.mock.calls[0][1].body)
      expect(callBody.step).toBe('property')
      expect(callBody.selectionContext).toEqual({
        systemId: 'selected-system',
        deviceId: 'selected-device',
      })
    })
  })

  describe('useConfirmMapping', () => {
    it('calls confirm API on mutation', async () => {
      fetchSpy.mockResolvedValueOnce({
        ok: true,
        json: async () => ({ success: true }),
      })

      const { result } = renderHook(
        () =>
          useConfirmMapping({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
          }),
        { wrapper: createWrapper() }
      )

      result.current.mutate({
        pointPattern: 'VAV-*_ZoneTemp',
        controllerId: 'controller-123',
        step: 'system',
        selectedId: 'vav-reheat-system',
        wasOverridden: false,
      })

      await waitFor(() => expect(result.current.isSuccess).toBe(true))

      expect(fetchSpy).toHaveBeenCalledWith(
        '/api/organizations/org-123/sites/site-456/projects/proj-789/ai/suggestions/confirm',
        expect.objectContaining({
          method: 'POST',
        })
      )
    })

    it('sends wasOverridden flag correctly', async () => {
      fetchSpy.mockResolvedValueOnce({
        ok: true,
        json: async () => ({ success: true }),
      })

      const { result } = renderHook(
        () =>
          useConfirmMapping({
            orgId: 'org-123',
            siteId: 'site-456',
            projectId: 'proj-789',
          }),
        { wrapper: createWrapper() }
      )

      result.current.mutate({
        pointPattern: 'AHU-*_SupplyFan',
        controllerId: 'controller-456',
        step: 'device',
        selectedId: 'supply-fan-device',
        wasOverridden: true,
      })

      await waitFor(() => expect(result.current.isSuccess).toBe(true))

      const callBody = JSON.parse(fetchSpy.mock.calls[0][1].body)
      expect(callBody.mapping.wasOverridden).toBe(true)
    })
  })
})
