import { renderHook, waitFor } from '@testing-library/react'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { useAllControllerPoints } from './use-all-controller-points'
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

describe('useAllControllerPoints', () => {
  beforeEach(() => {
    jest.clearAllMocks()
  })

  const mockPointsByController: Record<string, ControllerPoint[]> = {
    'controller-1': [
      {
        id: 'point-1',
        organizationId: 'org_test',
        siteId: 'site-1',
        iotDeviceId: 'iot-device-1',
        controllerId: 'controller-1',
        pointName: 'Temperature Sensor',
        pointType: 'analogInput',
        objectIdentifier: '["analog-input",0]',
        instanceNumber: 0,
        writable: false,
        units: 'degreesFahrenheit',
        createdAt: '2024-01-01T00:00:00Z',
        updatedAt: '2024-01-01T00:00:00Z',
      },
    ],
    'controller-2': [
      {
        id: 'point-2',
        organizationId: 'org_test',
        siteId: 'site-1',
        iotDeviceId: 'iot-device-1',
        controllerId: 'controller-2',
        pointName: 'Humidity Sensor',
        pointType: 'analogInput',
        objectIdentifier: '["analog-input",1]',
        instanceNumber: 1,
        writable: false,
        units: 'percent',
        createdAt: '2024-01-01T00:00:00Z',
        updatedAt: '2024-01-01T00:00:00Z',
      },
    ],
  }

  it('should fetch points for multiple controllers', async () => {
    mockControllerPointsApi.listBatch.mockResolvedValue(mockPointsByController)

    const { result } = renderHook(
      () =>
        useAllControllerPoints(
          'org_test',
          'site-1',
          'project-1',
          'iot-device-1',
          ['controller-1', 'controller-2']
        ),
      { wrapper: createWrapper() }
    )

    await waitFor(() => expect(result.current.isSuccess).toBe(true))

    expect(result.current.data).toEqual(mockPointsByController)
    expect(mockControllerPointsApi.listBatch).toHaveBeenCalledWith({
      orgId: 'org_test',
      siteId: 'site-1',
      projectId: 'project-1',
      iotDeviceId: 'iot-device-1',
      controllerIds: ['controller-1', 'controller-2'],
    })
  })

  it('should return empty object when controllerIds is empty', () => {
    mockControllerPointsApi.listBatch.mockResolvedValue({})

    const { result } = renderHook(
      () =>
        useAllControllerPoints(
          'org_test',
          'site-1',
          'project-1',
          'iot-device-1',
          []
        ),
      { wrapper: createWrapper() }
    )

    expect(result.current.isLoading).toBe(false)
    expect(result.current.data).toBeUndefined()
    expect(mockControllerPointsApi.listBatch).not.toHaveBeenCalled()
  })

  it('should not fetch when required params are undefined', () => {
    mockControllerPointsApi.listBatch.mockResolvedValue(mockPointsByController)

    const { result } = renderHook(
      () =>
        useAllControllerPoints(
          'org_test',
          undefined,
          'project-1',
          'iot-device-1',
          ['controller-1']
        ),
      { wrapper: createWrapper() }
    )

    expect(result.current.isLoading).toBe(false)
    expect(result.current.data).toBeUndefined()
    expect(mockControllerPointsApi.listBatch).not.toHaveBeenCalled()
  })

  it('should handle API errors', async () => {
    const errorMessage = 'Failed to fetch controller points'
    mockControllerPointsApi.listBatch.mockRejectedValue(new Error(errorMessage))

    const { result } = renderHook(
      () =>
        useAllControllerPoints(
          'org_test',
          'site-1',
          'project-1',
          'iot-device-1',
          ['controller-1']
        ),
      { wrapper: createWrapper() }
    )

    await waitFor(() => expect(result.current.isError).toBe(true))

    expect(result.current.error).toBeInstanceOf(Error)
    expect(result.current.error?.message).toBe(errorMessage)
  })
})
