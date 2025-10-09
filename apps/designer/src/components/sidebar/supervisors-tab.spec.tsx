import { render, screen } from '@testing-library/react'
import { SupervisorsTab } from './supervisors-tab'
import { useProject } from '@/hooks/use-projects'
import { useIotDevice } from '@/hooks/use-iot-device'
import { useFlowStore } from '@/store/use-flow-store'

jest.mock('@/hooks/use-projects')
jest.mock('@/hooks/use-iot-device')
jest.mock('@/store/use-flow-store')

const mockUseProject = useProject as jest.MockedFunction<typeof useProject>
const mockUseIotDevice = useIotDevice as jest.MockedFunction<
  typeof useIotDevice
>
const mockUseFlowStore = useFlowStore as unknown as jest.Mock

describe('SupervisorsTab', () => {
  const defaultProps = {
    projectId: 'project-123',
  }

  const mockProject = {
    id: 'project-123',
    site_id: 'site-123',
    iot_device_id: 'device-456',
    name: 'Test Project',
    workflow_config: '{}',
    created_at: '2024-01-01T00:00:00Z',
    updated_at: '2024-01-01T00:00:00Z',
  }

  const mockIotDevice = {
    id: 'device-456',
    organization_id: 'org_test',
    site_id: 'site-123',
    name: 'Test IoT Device',
    description: 'Test device description',
    created_at: '2024-01-01T00:00:00Z',
    updated_at: '2024-01-01T00:00:00Z',
  }

  beforeEach(() => {
    mockUseFlowStore.mockImplementation((selector) => {
      const state = {
        connectionStatus: 'disconnected' as const,
        brokerHealth: {
          status: 'unknown' as const,
          lastHeartbeat: null,
          lastHeartbeatTimestamp: null,
        },
        lastError: undefined,
      }
      return selector(state)
    })
  })

  afterEach(() => {
    jest.clearAllMocks()
  })

  describe('Rendering States', () => {
    it('should show loading state while fetching data', () => {
      mockUseProject.mockReturnValue({
        data: undefined,
        isLoading: true,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: undefined,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.getByText('Loading...')).toBeInTheDocument()
    })

    it('should show "No IoT Device Linked" when project has no iot_device_id', () => {
      mockUseProject.mockReturnValue({
        data: { ...mockProject, iot_device_id: undefined },
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: undefined,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.getByText('No IoT Device Linked')).toBeInTheDocument()
      expect(
        screen.getByText(/Link an IoT device to this project/i)
      ).toBeInTheDocument()
    })

    it('should show iot device details when configured', () => {
      mockUseProject.mockReturnValue({
        data: mockProject,
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: mockIotDevice,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.getByText('Test IoT Device')).toBeInTheDocument()
      expect(screen.getByText('Test device description')).toBeInTheDocument()
      expect(screen.getByText('org_test')).toBeInTheDocument()
      expect(screen.getByText('site-123')).toBeInTheDocument()
      expect(screen.getByText('device-456')).toBeInTheDocument()
    })

    it('should not show description if iot device has none', () => {
      mockUseProject.mockReturnValue({
        data: mockProject,
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: { ...mockIotDevice, description: undefined },
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.queryByText('Description:')).not.toBeInTheDocument()
    })
  })

  describe('MQTT Status Display', () => {
    it('should show connection status badge for connected', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          connectionStatus: 'connected' as const,
          brokerHealth: {
            status: 'unknown' as const,
            lastHeartbeat: null,
            lastHeartbeatTimestamp: null,
          },
          lastError: undefined,
        }
        return selector(state)
      })

      mockUseProject.mockReturnValue({
        data: mockProject,
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: mockIotDevice,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.getByText('connected')).toBeInTheDocument()
    })

    it('should show broker health badge as healthy', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          connectionStatus: 'connected' as const,
          brokerHealth: {
            status: 'healthy' as const,
            lastHeartbeat: {
              cpu_usage_percent: 10.5,
              memory_usage_percent: 75.2,
              disk_usage_percent: 45.3,
              temperature_celsius: null,
              uptime_seconds: 666,
              load_average: 1.5,
              monitoring_status: 'active',
              mqtt_connection_status: 'connected',
              bacnet_connection_status: null,
              bacnet_devices_connected: null,
              bacnet_points_monitored: null,
              timestamp: Date.now() / 1000,
              organization_id: 'org_test',
              site_id: 'site-123',
              iot_device_id: 'device-456',
            },
            lastHeartbeatTimestamp: Date.now(),
          },
          lastError: undefined,
        }
        return selector(state)
      })

      mockUseProject.mockReturnValue({
        data: mockProject,
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: mockIotDevice,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.getByText('healthy')).toBeInTheDocument()
    })

    it('should display uptime in human-readable format', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          connectionStatus: 'connected' as const,
          brokerHealth: {
            status: 'healthy' as const,
            lastHeartbeat: {
              cpu_usage_percent: 10.5,
              memory_usage_percent: 75.2,
              disk_usage_percent: 45.3,
              temperature_celsius: null,
              uptime_seconds: 666,
              load_average: 1.5,
              monitoring_status: 'active',
              mqtt_connection_status: 'connected',
              bacnet_connection_status: null,
              bacnet_devices_connected: null,
              bacnet_points_monitored: null,
              timestamp: Date.now() / 1000,
              organization_id: 'org_test',
              site_id: 'site-123',
              iot_device_id: 'device-456',
            },
            lastHeartbeatTimestamp: Date.now(),
          },
          lastError: undefined,
        }
        return selector(state)
      })

      mockUseProject.mockReturnValue({
        data: mockProject,
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: mockIotDevice,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.getByText('11m 6s')).toBeInTheDocument()
    })

    it('should show "Waiting for heartbeat..." when connected but no data', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          connectionStatus: 'connected' as const,
          brokerHealth: {
            status: 'unknown' as const,
            lastHeartbeat: null,
            lastHeartbeatTimestamp: null,
          },
          lastError: undefined,
        }
        return selector(state)
      })

      mockUseProject.mockReturnValue({
        data: mockProject,
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: mockIotDevice,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(
        screen.getByText(/Waiting for heartbeat from supervisor/i)
      ).toBeInTheDocument()
    })

    it('should show error message when lastError exists', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          connectionStatus: 'error' as const,
          brokerHealth: {
            status: 'unhealthy' as const,
            lastHeartbeat: null,
            lastHeartbeatTimestamp: null,
          },
          lastError: 'Connection failed: timeout',
        }
        return selector(state)
      })

      mockUseProject.mockReturnValue({
        data: mockProject,
        isLoading: false,
      } as any)

      mockUseIotDevice.mockReturnValue({
        data: mockIotDevice,
        isLoading: false,
      } as any)

      render(<SupervisorsTab {...defaultProps} />)

      expect(screen.getByText('Connection failed: timeout')).toBeInTheDocument()
    })
  })
})
