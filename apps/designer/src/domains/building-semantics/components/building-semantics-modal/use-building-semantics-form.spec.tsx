import { renderHook, waitFor, act } from '@testing-library/react'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { useBuildingSemanticsForm } from './use-building-semantics-form'
import * as BacnetReferenceQuery from '../../api/queries/use-bacnet-reference-query'
import * as SystemsQuery from '../../api/queries/use-systems-query'
import * as DevicesQuery from '../../api/queries/use-devices-query'
import * as PropertiesQuery from '../../api/queries/use-properties-query'
import * as SaveMutation from '../../api/mutations/use-save-bacnet-reference-mutation'

jest.mock('../../api/queries/use-bacnet-reference-query')
jest.mock('../../api/queries/use-systems-query')
jest.mock('../../api/queries/use-devices-query')
jest.mock('../../api/queries/use-properties-query')
jest.mock('../../api/mutations/use-save-bacnet-reference-mutation')
jest.mock('sonner', () => ({
  toast: {
    success: jest.fn(),
    error: jest.fn(),
  },
}))

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

describe('useBuildingSemanticsForm', () => {
  const mockOnSaved = jest.fn()
  const mockOnOpenChange = jest.fn()
  const mockMutate = jest.fn()

  const defaultParams = {
    projectId: 'project-123',
    bacnetPointId: 'point-abc',
    bacnetObjectType: 'analog-input',
    open: true,
    onSaved: mockOnSaved,
    onOpenChange: mockOnOpenChange,
  }

  const mockSystems = [
    { systemUri: 'sys-1', label: 'HVAC System 1' },
    { systemUri: 'sys-2', label: 'Lighting System' },
  ]

  const mockDevices = [
    { deviceUri: 'dev-1', label: 'VAV Box 1' },
    { deviceUri: 'dev-2', label: 'Temperature Sensor' },
  ]

  const mockProperties = [
    { propertyUri: 'prop-1', label: 'Zone Temperature' },
    { propertyUri: 'prop-2', label: 'Damper Position' },
  ]

  beforeEach(() => {
    jest.clearAllMocks()

    jest
      .spyOn(BacnetReferenceQuery, 'useBacnetReferenceQuery')
      .mockReturnValue({
        data: undefined,
      } as any)

    jest.spyOn(SystemsQuery, 'useSystemsQuery').mockReturnValue({
      data: mockSystems,
      isLoading: false,
    } as any)

    jest.spyOn(DevicesQuery, 'useDevicesQuery').mockReturnValue({
      data: mockDevices,
      isLoading: false,
    } as any)

    jest.spyOn(PropertiesQuery, 'usePropertiesQuery').mockReturnValue({
      data: mockProperties,
      isLoading: false,
    } as any)

    jest.spyOn(SaveMutation, 'useSaveBacnetReferenceMutation').mockReturnValue({
      mutate: mockMutate,
      isPending: false,
    } as any)
  })

  describe('Initial State', () => {
    it('should initialize with empty selections', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      expect(result.current.state.selectedSystemUri).toBeUndefined()
      expect(result.current.state.selectedDeviceUri).toBeUndefined()
      expect(result.current.state.selectedPropertyUri).toBeUndefined()
      expect(result.current.state.validationErrors).toEqual([])
      expect(result.current.state.showValidationModal).toBe(false)
    })

    it('should return systems data from query', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      expect(result.current.data.systems).toEqual(mockSystems)
    })

    it('should have form invalid initially', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      expect(result.current.validation.isFormValid).toBe(false)
    })
  })

  describe('Selection Actions', () => {
    it('should update selectedSystemUri when selectSystem is called', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectSystem('sys-1')
      })

      expect(result.current.state.selectedSystemUri).toBe('sys-1')
    })

    it('should clear device and property when selecting system', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      // Set all selections
      act(() => {
        result.current.actions.selectSystem('sys-1')
        result.current.actions.selectDevice('dev-1')
        result.current.actions.selectProperty('prop-1')
      })

      // Change system - should clear device and property
      act(() => {
        result.current.actions.selectSystem('sys-2')
      })

      expect(result.current.state.selectedSystemUri).toBe('sys-2')
      expect(result.current.state.selectedDeviceUri).toBeUndefined()
      expect(result.current.state.selectedPropertyUri).toBeUndefined()
    })

    it('should update selectedDeviceUri when selectDevice is called', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectDevice('dev-1')
      })

      expect(result.current.state.selectedDeviceUri).toBe('dev-1')
    })

    it('should clear property when selecting device', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      // Set all selections
      act(() => {
        result.current.actions.selectSystem('sys-1')
        result.current.actions.selectDevice('dev-1')
        result.current.actions.selectProperty('prop-1')
      })

      // Change device - should clear property
      act(() => {
        result.current.actions.selectDevice('dev-2')
      })

      expect(result.current.state.selectedSystemUri).toBe('sys-1')
      expect(result.current.state.selectedDeviceUri).toBe('dev-2')
      expect(result.current.state.selectedPropertyUri).toBeUndefined()
    })

    it('should update selectedPropertyUri when selectProperty is called', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectProperty('prop-1')
      })

      expect(result.current.state.selectedPropertyUri).toBe('prop-1')
    })
  })

  describe('Form Validation', () => {
    it('should be invalid with only system selected', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectSystem('sys-1')
      })

      expect(result.current.validation.isFormValid).toBe(false)
    })

    it('should be invalid with system and device selected', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectSystem('sys-1')
        result.current.actions.selectDevice('dev-1')
      })

      expect(result.current.validation.isFormValid).toBe(false)
    })

    it('should be valid when all three selections are made', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectSystem('sys-1')
        result.current.actions.selectDevice('dev-1')
        result.current.actions.selectProperty('prop-1')
      })

      expect(result.current.validation.isFormValid).toBe(true)
    })
  })

  describe('Local Systems Management', () => {
    it('should add local system and select it', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      const newSystem = { systemUri: 'sys-3', label: 'New System' }
      act(() => {
        result.current.actions.addLocalSystem(newSystem)
      })

      expect(result.current.data.systems).toContainEqual(newSystem)
      expect(result.current.state.selectedSystemUri).toBe('sys-3')
    })

    it('should merge local systems with API systems', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      const newSystem = { systemUri: 'sys-3', label: 'New System' }
      act(() => {
        result.current.actions.addLocalSystem(newSystem)
      })

      expect(result.current.data.systems).toHaveLength(3)
      expect(result.current.data.systems).toEqual([...mockSystems, newSystem])
    })

    it('should not duplicate systems that exist in API', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      // Add a local system
      const newSystem = { systemUri: 'sys-3', label: 'New System' }
      act(() => {
        result.current.actions.addLocalSystem(newSystem)
      })

      // Now simulate API returning the same system
      jest.spyOn(SystemsQuery, 'useSystemsQuery').mockReturnValue({
        data: [...mockSystems, newSystem],
        isLoading: false,
      } as any)

      const { result: result2 } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      // Should not have duplicates
      expect(result2.current.data.systems).toHaveLength(3)
    })
  })

  describe('Save Functionality', () => {
    it('should call mutate with correct parameters', async () => {
      mockMutate.mockImplementation((params, callbacks) => {
        callbacks?.onSuccess?.()
      })

      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectSystem('sys-1')
        result.current.actions.selectDevice('dev-1')
        result.current.actions.selectProperty('prop-1')
      })

      await act(async () => {
        await result.current.actions.handleSave()
      })

      expect(mockMutate).toHaveBeenCalledWith(
        {
          projectId: 'project-123',
          bacnetPointId: 'point-abc',
          propertyUri: 'prop-1',
        },
        expect.objectContaining({
          onSuccess: expect.any(Function),
          onError: expect.any(Function),
        })
      )
    })

    it('should call onSaved and onOpenChange on successful save', async () => {
      mockMutate.mockImplementation((params, callbacks) => {
        callbacks?.onSuccess?.()
      })

      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectProperty('prop-1')
      })

      await act(async () => {
        await result.current.actions.handleSave()
      })

      await waitFor(() => {
        expect(mockOnSaved).toHaveBeenCalled()
        expect(mockOnOpenChange).toHaveBeenCalledWith(false)
      })
    })

    it('should show validation errors on SHACL validation failure', async () => {
      const shaclError = {
        error: {
          validationType: 'SHACL',
          isValid: false,
          errors: ['Validation error 1', 'Validation error 2'],
          warnings: [],
        },
      }

      mockMutate.mockImplementation((params, callbacks) => {
        callbacks?.onError?.(shaclError)
      })

      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      act(() => {
        result.current.actions.selectProperty('prop-1')
      })

      await act(async () => {
        await result.current.actions.handleSave()
      })

      await waitFor(() => {
        expect(result.current.state.showValidationModal).toBe(true)
        expect(result.current.state.validationErrors.length).toBe(2)
        expect(result.current.state.validationErrors).toEqual([
          'Validation error 1',
          'Validation error 2',
        ])
      })
    })
  })

  describe('Validation Modal Management', () => {
    it('should hide validation modal when hideValidationModal is called', () => {
      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      // Simulate showing validation errors
      const shaclError = {
        error: {
          validationType: 'SHACL',
          isValid: false,
          errors: ['Validation error'],
          warnings: [],
        },
      }

      mockMutate.mockImplementation((params, callbacks) => {
        callbacks?.onError?.(shaclError)
      })

      act(() => {
        result.current.actions.selectProperty('prop-1')
        result.current.actions.handleSave()
      })

      // Now hide modal
      act(() => {
        result.current.actions.hideValidationModal()
      })

      expect(result.current.state.showValidationModal).toBe(false)
      expect(result.current.state.validationErrors).toEqual([])
    })
  })

  describe('Existing Reference Loading', () => {
    it('should pre-populate selections when existing reference exists and modal opens', () => {
      jest
        .spyOn(BacnetReferenceQuery, 'useBacnetReferenceQuery')
        .mockReturnValue({
          data: {
            systemUri: 'sys-1',
            deviceUri: 'dev-1',
            propertyUri: 'prop-1',
          },
        } as any)

      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      expect(result.current.state.selectedSystemUri).toBe('sys-1')
      expect(result.current.state.selectedDeviceUri).toBe('dev-1')
      expect(result.current.state.selectedPropertyUri).toBe('prop-1')
      expect(result.current.validation.isFormValid).toBe(true)
    })

    it('should reset form when modal opens with no existing reference', () => {
      const { result, rerender } = renderHook(
        ({ open }) => useBuildingSemanticsForm({ ...defaultParams, open }),
        {
          wrapper: createWrapper(),
          initialProps: { open: false },
        }
      )

      // Make some selections
      act(() => {
        result.current.actions.selectSystem('sys-1')
        result.current.actions.selectDevice('dev-1')
        result.current.actions.selectProperty('prop-1')
      })

      // Reopen modal
      rerender({ open: true })

      // Should reset (except localSystems)
      expect(result.current.state.selectedSystemUri).toBeUndefined()
      expect(result.current.state.selectedDeviceUri).toBeUndefined()
      expect(result.current.state.selectedPropertyUri).toBeUndefined()
    })
  })

  describe('Loading States', () => {
    it('should expose loading states from queries', () => {
      jest.spyOn(SystemsQuery, 'useSystemsQuery').mockReturnValue({
        data: [],
        isLoading: true,
      } as any)

      jest.spyOn(DevicesQuery, 'useDevicesQuery').mockReturnValue({
        data: [],
        isLoading: true,
      } as any)

      jest.spyOn(PropertiesQuery, 'usePropertiesQuery').mockReturnValue({
        data: [],
        isLoading: true,
      } as any)

      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      expect(result.current.loading.isLoadingSystems).toBe(true)
      expect(result.current.loading.isLoadingDevices).toBe(true)
      expect(result.current.loading.isLoadingProperties).toBe(true)
    })

    it('should expose saving state from mutation', () => {
      jest
        .spyOn(SaveMutation, 'useSaveBacnetReferenceMutation')
        .mockReturnValue({
          mutate: mockMutate,
          isPending: true,
        } as any)

      const { result } = renderHook(
        () => useBuildingSemanticsForm(defaultParams),
        { wrapper: createWrapper() }
      )

      expect(result.current.loading.isSaving).toBe(true)
    })
  })
})
