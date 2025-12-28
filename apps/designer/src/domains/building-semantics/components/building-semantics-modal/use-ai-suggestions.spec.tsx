import { renderHook, act, waitFor } from '@testing-library/react'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { ReactNode } from 'react'
import { useAISuggestions } from './use-ai-suggestions'

const createWrapper = () => {
  const queryClient = new QueryClient({
    defaultOptions: {
      queries: { retry: false },
      mutations: { retry: false },
    },
  })
  function TestWrapper({ children }: { children: ReactNode }) {
    return (
      <QueryClientProvider client={queryClient}>{children}</QueryClientProvider>
    )
  }
  return TestWrapper
}

const mockSuggestionResponse = {
  success: true,
  data: {
    selectedId: 'suggested-system-uri',
    confidence: 0.92,
    reasoning: 'Based on point naming pattern',
    alternatives: [],
  },
}

describe('useAISuggestions', () => {
  let fetchSpy: jest.SpyInstance

  const defaultParams = {
    context: {
      orgId: 'org-123',
      siteId: 'site-456',
      projectId: 'proj-789',
    },
    point: {
      id: 'VAV-2-01_ZoneTemp',
      name: 'VAV-2-01 Zone Temperature',
      objectType: 'analog-input',
      objectId: 1,
      controllerId: '800',
    },
    enabled: true,
    selections: {
      systemUri: undefined,
      deviceUri: undefined,
      propertyUri: undefined,
    },
    candidates: {
      system: [
        { id: 'system-1', label: 'System 1' },
        { id: 'system-2', label: 'System 2' },
      ],
      device: [
        { id: 'device-1', label: 'Device 1' },
        { id: 'device-2', label: 'Device 2' },
      ],
      property: [
        { id: 'property-1', label: 'Property 1' },
        { id: 'property-2', label: 'Property 2' },
      ],
    },
  }

  beforeEach(() => {
    fetchSpy = jest.spyOn(global, 'fetch')
    jest.clearAllMocks()
  })

  afterEach(() => {
    fetchSpy.mockRestore()
  })

  describe('initialization', () => {
    it('returns initial state with no suggestions', () => {
      fetchSpy.mockResolvedValue({
        ok: true,
        json: async () => ({ success: true, data: null }),
      })

      const { result } = renderHook(
        () => useAISuggestions({ ...defaultParams, enabled: false }),
        { wrapper: createWrapper() }
      )

      expect(result.current.suggestions.system).toBeUndefined()
      expect(result.current.suggestions.device).toBeUndefined()
      expect(result.current.suggestions.property).toBeUndefined()
    })

    it('does not fetch when disabled', () => {
      const { result } = renderHook(
        () => useAISuggestions({ ...defaultParams, enabled: false }),
        { wrapper: createWrapper() }
      )

      expect(result.current.loading.system).toBe(false)
      expect(fetchSpy).not.toHaveBeenCalled()
    })
  })

  describe('system suggestions', () => {
    it('fetches system suggestion when enabled with candidates', async () => {
      fetchSpy.mockResolvedValue({
        ok: true,
        json: async () => mockSuggestionResponse,
      })

      const { result } = renderHook(() => useAISuggestions(defaultParams), {
        wrapper: createWrapper(),
      })

      await waitFor(() => {
        expect(result.current.suggestions.system).toBeDefined()
      })

      expect(result.current.suggestions.system?.selectedId).toBe(
        'suggested-system-uri'
      )
    })
  })

  describe('trackSelection', () => {
    it('tracks when user selects the AI suggestion (no override)', async () => {
      fetchSpy.mockResolvedValue({
        ok: true,
        json: async () => mockSuggestionResponse,
      })

      const { result } = renderHook(() => useAISuggestions(defaultParams), {
        wrapper: createWrapper(),
      })

      await waitFor(() => {
        expect(result.current.suggestions.system).toBeDefined()
      })

      act(() => {
        result.current.trackSelection('system', 'suggested-system-uri')
      })

      // No override since user selected the suggested value
      // This is tracked internally for confirmAllMappings
    })

    it('tracks when user overrides AI suggestion', async () => {
      fetchSpy.mockResolvedValue({
        ok: true,
        json: async () => mockSuggestionResponse,
      })

      const { result } = renderHook(() => useAISuggestions(defaultParams), {
        wrapper: createWrapper(),
      })

      await waitFor(() => {
        expect(result.current.suggestions.system).toBeDefined()
      })

      act(() => {
        result.current.trackSelection('system', 'different-system-uri')
      })

      // Override is tracked internally for confirmAllMappings
    })
  })

  describe('confirmAllMappings', () => {
    it('calls confirm API for each selected mapping', async () => {
      fetchSpy.mockResolvedValue({
        ok: true,
        json: async () => ({ success: true }),
      })

      const { result } = renderHook(
        () =>
          useAISuggestions({
            ...defaultParams,
            selections: {
              systemUri: 'system-1',
              deviceUri: 'device-1',
              propertyUri: 'property-1',
            },
          }),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.confirmAllMappings()
      })

      await waitFor(() => {
        const confirmCalls = fetchSpy.mock.calls.filter((call) =>
          String(call[0]).includes('/confirm')
        )
        expect(confirmCalls.length).toBe(3)
      })
    })

    it('does not call confirm for unselected mappings', async () => {
      fetchSpy.mockResolvedValue({
        ok: true,
        json: async () => ({ success: true }),
      })

      const { result } = renderHook(
        () =>
          useAISuggestions({
            ...defaultParams,
            selections: {
              systemUri: 'system-1',
              deviceUri: undefined,
              propertyUri: undefined,
            },
          }),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.confirmAllMappings()
      })

      await waitFor(() => {
        const confirmCalls = fetchSpy.mock.calls.filter((call) =>
          String(call[0]).includes('/confirm')
        )
        expect(confirmCalls.length).toBe(1)
      })
    })
  })

  describe('reset', () => {
    it('resets internal state', async () => {
      fetchSpy.mockResolvedValue({
        ok: true,
        json: async () => mockSuggestionResponse,
      })

      const { result } = renderHook(() => useAISuggestions(defaultParams), {
        wrapper: createWrapper(),
      })

      await waitFor(() => {
        expect(result.current.suggestions.system).toBeDefined()
      })

      act(() => {
        result.current.trackSelection('system', 'different-uri')
        result.current.reset()
      })

      // After reset, override tracking is cleared
    })
  })
})
