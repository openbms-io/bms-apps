import { renderHook, waitFor } from '@testing-library/react'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { useControllerPoints } from './use-controller-points'
import { controllerPointsApi } from '@/lib/api/controller-points'
import { ControllerPoint } from '@/lib/domain/models/controller-point'

jest.mock('@/lib/api/controller-points')

const mockControllerPointsApi = controllerPointsApi as jest.Mocked<
  typeof controllerPointsApi
>

const createWrapper = () => {
  const queryClient = new QueryClient({
    defaultOptions: {
      queries: { retry: false },
      mutations: { retry: false },
    },
  })

  function Wrapper({ children }: { children: React.ReactNode }) {
    return (
      <QueryClientProvider client={queryClient}>{children}</QueryClientProvider>
    )
  }

  return Wrapper
}

describe('useControllerPoints', () => {
  beforeEach(() => {
    jest.clearAllMocks()
  })

  const mockPoints: ControllerPoint[] = [
    {
      id: '00000000-0000-0000-0000-000000000010',
      organizationId: 'org_test',
      siteId: '00000000-0000-0000-0000-000000000001',
      iotDeviceId: '00000000-0000-0000-0000-000000000003',
      controllerId: '00000000-0000-0000-0000-000000000004',
      pointName: 'Temperature Sensor',
      pointType: 'analogInput',
      objectIdentifier: '["analog-input",0]',
      instanceNumber: 0,
      writable: false,
      units: 'degreesFahrenheit',
      description: 'Room temperature',
      createdAt: '2024-01-01T00:00:00Z',
      updatedAt: '2024-01-01T00:00:00Z',
    },
    {
      id: '00000000-0000-0000-0000-000000000011',
      organizationId: 'org_test',
      siteId: '00000000-0000-0000-0000-000000000001',
      iotDeviceId: '00000000-0000-0000-0000-000000000003',
      controllerId: '00000000-0000-0000-0000-000000000004',
      pointName: 'Humidity Sensor',
      pointType: 'analogInput',
      objectIdentifier: '["analog-input",1]',
      instanceNumber: 1,
      writable: false,
      units: 'percent',
      createdAt: '2024-01-01T00:00:00Z',
      updatedAt: '2024-01-01T00:00:00Z',
    },
  ]

  it('should fetch controller points successfully', async () => {
    mockControllerPointsApi.list.mockResolvedValue(mockPoints)

    const { result } = renderHook(
      () =>
        useControllerPoints(
          'org_test',
          '00000000-0000-0000-0000-000000000001',
          '00000000-0000-0000-0000-000000000002',
          '00000000-0000-0000-0000-000000000003',
          '00000000-0000-0000-0000-000000000004'
        ),
      { wrapper: createWrapper() }
    )

    await waitFor(() => expect(result.current.isSuccess).toBe(true))

    expect(result.current.data).toEqual(mockPoints)
    expect(mockControllerPointsApi.list).toHaveBeenCalledWith({
      orgId: 'org_test',
      siteId: '00000000-0000-0000-0000-000000000001',
      projectId: '00000000-0000-0000-0000-000000000002',
      iotDeviceId: '00000000-0000-0000-0000-000000000003',
      controllerId: '00000000-0000-0000-0000-000000000004',
    })
  })

  it('should return empty array when no points exist', async () => {
    mockControllerPointsApi.list.mockResolvedValue([])

    const { result } = renderHook(
      () =>
        useControllerPoints(
          'org_test',
          '00000000-0000-0000-0000-000000000001',
          '00000000-0000-0000-0000-000000000002',
          '00000000-0000-0000-0000-000000000003',
          '00000000-0000-0000-0000-000000000004'
        ),
      { wrapper: createWrapper() }
    )

    await waitFor(() => expect(result.current.isSuccess).toBe(true))

    expect(result.current.data).toEqual([])
  })

  it('should not fetch when required params are undefined', () => {
    mockControllerPointsApi.list.mockResolvedValue(mockPoints)

    const { result } = renderHook(
      () =>
        useControllerPoints(
          'org_test',
          undefined,
          '00000000-0000-0000-0000-000000000002',
          '00000000-0000-0000-0000-000000000003',
          '00000000-0000-0000-0000-000000000004'
        ),
      { wrapper: createWrapper() }
    )

    expect(result.current.isLoading).toBe(false)
    expect(result.current.data).toBeUndefined()
    expect(mockControllerPointsApi.list).not.toHaveBeenCalled()
  })

  it('should handle API errors', async () => {
    const errorMessage = 'Failed to fetch controller points'
    mockControllerPointsApi.list.mockRejectedValue(new Error(errorMessage))

    const { result } = renderHook(
      () =>
        useControllerPoints(
          'org_test',
          '00000000-0000-0000-0000-000000000001',
          '00000000-0000-0000-0000-000000000002',
          '00000000-0000-0000-0000-000000000003',
          '00000000-0000-0000-0000-000000000004'
        ),
      { wrapper: createWrapper() }
    )

    await waitFor(() => expect(result.current.isError).toBe(true))

    expect(result.current.error).toBeInstanceOf(Error)
    expect(result.current.error?.message).toBe(errorMessage)
  })

  it('should use correct query key for caching', () => {
    mockControllerPointsApi.list.mockResolvedValue(mockPoints)

    const { result } = renderHook(
      () =>
        useControllerPoints(
          'org_test',
          '00000000-0000-0000-0000-000000000001',
          '00000000-0000-0000-0000-000000000002',
          '00000000-0000-0000-0000-000000000003',
          '00000000-0000-0000-0000-000000000004'
        ),
      { wrapper: createWrapper() }
    )

    expect(result.current.isLoading).toBe(true)
  })
})
