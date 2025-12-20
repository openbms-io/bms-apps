import { renderHook, waitFor } from '@testing-library/react'
import { createHookWrapper } from '@test-utils/render'
import { useInstanceQuery, instanceQueryKey } from './use-instance-query'
import * as client from '../client'
import type { InstanceResponseWithCategoriesReheatParameters } from '../generated/types.gen'

jest.mock('../client')
const mockGetInstance = client.getInstance as jest.Mock

describe('useInstanceQuery', () => {
  beforeEach(() => {
    jest.clearAllMocks()
  })

  it('fetches instance data successfully', async () => {
    const mockData: InstanceResponseWithCategoriesReheatParameters = {
      instance_id: 'test-123',
      parameters: {
        temperatureUnit: 'C',
        airflowUnit: 'm3/s',
        minAirflow: 0.3,
      } as never,
      categories: {
        units: ['temperatureUnit', 'airflowUnit'],
        sensors: ['hasCO2Sensor'],
      },
    }
    mockGetInstance.mockResolvedValue(mockData)

    const { result } = renderHook(
      () => useInstanceQuery({ instanceId: 'test-123' }),
      { wrapper: createHookWrapper() }
    )

    await waitFor(() => expect(result.current.isSuccess).toBe(true))

    expect(mockGetInstance).toHaveBeenCalledWith({ instanceId: 'test-123' })
    expect(result.current.data?.instance_id).toBe('test-123')
    expect(result.current.data?.categories.units).toContain('temperatureUnit')
  })

  it('does not fetch when instanceId is empty', () => {
    renderHook(() => useInstanceQuery({ instanceId: '' }), {
      wrapper: createHookWrapper(),
    })

    expect(mockGetInstance).not.toHaveBeenCalled()
  })

  it('handles error responses', async () => {
    mockGetInstance.mockRejectedValue(new Error('Instance not found'))

    const { result } = renderHook(
      () => useInstanceQuery({ instanceId: 'invalid-id' }),
      { wrapper: createHookWrapper() }
    )

    await waitFor(() => expect(result.current.isError).toBe(true))
    expect(result.current.error?.message).toBe('Instance not found')
  })
})

describe('instanceQueryKey', () => {
  it('returns consistent query key structure', () => {
    const key = instanceQueryKey('test-123')
    expect(key).toEqual(['control-sequence', 'instance', 'test-123'])
  })
})
