import { renderHook, waitFor, act } from '@testing-library/react'
import { createHookWrapper } from '@test-utils/render'
import { useUpdateInstanceMutation } from './use-update-instance-mutation'
import * as client from '../client'
import type {
  InstanceResponseWithCategoriesReheatParameters,
  ReheatParameters,
} from '../generated/types.gen'

jest.mock('../client')
const mockUpdateInstance = client.updateInstance as jest.Mock

describe('useUpdateInstanceMutation', () => {
  beforeEach(() => {
    jest.clearAllMocks()
  })

  it('updates instance successfully', async () => {
    const mockResponse: InstanceResponseWithCategoriesReheatParameters = {
      instance_id: 'test-123',
      parameters: {
        temperatureUnit: 'F',
        airflowUnit: 'cfm',
        minAirflow: 0.5,
      } as ReheatParameters,
      categories: {
        units: ['temperatureUnit', 'airflowUnit'],
        sensors: ['hasCO2Sensor'],
      },
    }
    mockUpdateInstance.mockResolvedValue(mockResponse)

    const { result } = renderHook(() => useUpdateInstanceMutation(), {
      wrapper: createHookWrapper(),
    })

    await act(async () => {
      await result.current.mutateAsync({
        instanceId: 'test-123',
        parameters: { minAirflow: 0.5 } as ReheatParameters,
      })
    })

    expect(mockUpdateInstance).toHaveBeenCalledWith({
      instanceId: 'test-123',
      parameters: { minAirflow: 0.5 },
    })

    await waitFor(() => {
      expect(result.current.data?.parameters.minAirflow).toBe(0.5)
    })
  })

  it('handles error responses', async () => {
    mockUpdateInstance.mockRejectedValue(new Error('Update failed'))

    const { result } = renderHook(() => useUpdateInstanceMutation(), {
      wrapper: createHookWrapper(),
    })

    await act(async () => {
      try {
        await result.current.mutateAsync({
          instanceId: 'test-123',
          parameters: { minAirflow: 0.5 } as ReheatParameters,
        })
      } catch {
        // Expected to throw
      }
    })

    await waitFor(() => expect(result.current.isError).toBe(true))
    expect(result.current.error?.message).toBe('Update failed')
  })
})
