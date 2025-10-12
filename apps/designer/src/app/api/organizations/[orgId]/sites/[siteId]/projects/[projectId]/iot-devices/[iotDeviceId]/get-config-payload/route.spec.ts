/**
 * @jest-environment node
 */

import { GET } from './route'
import { decodeJWT } from '@/lib/jwt'

jest.mock('@/lib/db/models/iot-device-controllers', () => ({
  iotDeviceControllersRepository: {
    findByDevice: jest.fn(),
  },
}))

jest.mock('@/lib/db/models/bacnet-readers', () => ({
  bacnetReadersRepository: {
    findByDevice: jest.fn(),
  },
}))

import { iotDeviceControllersRepository } from '@/lib/db/models/iot-device-controllers'
import { bacnetReadersRepository } from '@/lib/db/models/bacnet-readers'

describe('GET /api/.../get-config-payload', () => {
  const mockParams = Promise.resolve({
    orgId: 'org_123',
    siteId: 'site_456',
    projectId: 'proj_789',
    iotDeviceId: 'device_abc',
  })

  beforeEach(() => {
    process.env.NEXT_PUBLIC_API_URL = 'http://localhost:3000'
    process.env.JWT_SECRET = 'test-secret-key-minimum-32-characters-long'
    jest.clearAllMocks()
  })

  it('should return complete payload with JWT and data from DB', async () => {
    const mockControllers = [
      {
        id: 'ctrl_1',
        ip_address: '192.168.1.101',
        port: 47808,
        device_id: 1001,
        organization_id: 'org_123',
        site_id: 'site_456',
        iot_device_id: 'device_abc',
        name: 'Controller 1',
        is_active: true,
        metadata: {},
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-01T00:00:00Z',
      },
    ]

    const mockReaders = [
      {
        id: 'reader_1',
        ip_address: '192.168.1.100',
        port: 47808,
        device_id: 2001,
        organization_id: 'org_123',
        site_id: 'site_456',
        iot_device_id: 'device_abc',
        name: 'Reader 1',
        is_active: true,
        metadata: {},
        created_at: '2025-01-01T00:00:00Z',
        updated_at: '2025-01-01T00:00:00Z',
      },
    ]

    ;(
      iotDeviceControllersRepository.findByDevice as jest.Mock
    ).mockResolvedValue(mockControllers)
    ;(bacnetReadersRepository.findByDevice as jest.Mock).mockResolvedValue(
      mockReaders
    )

    const request = {} as any
    const response = await GET(request, { params: mockParams })

    expect(response.status).toBe(200)
    const json = await response.json()

    expect(json.success).toBe(true)
    expect(json.data.payload.urlToUploadConfig).toBe(
      'http://localhost:3000/api/webhook/iot-device-config-upload'
    )
    expect(json.data.payload.jwtToken).toBeDefined()
    expect(json.data.payload.iotDeviceControllers).toHaveLength(1)
    expect(json.data.payload.bacnetReaders).toHaveLength(1)
  })

  it('should return empty arrays when no controllers/readers exist', async () => {
    ;(
      iotDeviceControllersRepository.findByDevice as jest.Mock
    ).mockResolvedValue([])
    ;(bacnetReadersRepository.findByDevice as jest.Mock).mockResolvedValue([])

    const request = {} as any
    const response = await GET(request, { params: mockParams })

    const json = await response.json()
    expect(json.data.payload.iotDeviceControllers).toEqual([])
    expect(json.data.payload.bacnetReaders).toEqual([])
  })

  it('should generate valid JWT with correct claims', async () => {
    ;(
      iotDeviceControllersRepository.findByDevice as jest.Mock
    ).mockResolvedValue([])
    ;(bacnetReadersRepository.findByDevice as jest.Mock).mockResolvedValue([])

    const request = {} as any
    const response = await GET(request, { params: mockParams })

    const json = await response.json()
    const decoded = await decodeJWT(json.data.payload.jwtToken)

    expect(decoded.orgId).toBe('org_123')
    expect(decoded.siteId).toBe('site_456')
    expect(decoded.iotDeviceId).toBe('device_789') // From global jose mock
    expect(decoded.scope).toBe('upload-config')
  })
})
