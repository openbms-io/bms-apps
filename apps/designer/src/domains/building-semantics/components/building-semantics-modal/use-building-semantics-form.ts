import { useReducer, useEffect } from 'react'
import { toast } from 'sonner'
import type { SystemSummaryDto } from '../../api/generated/types.gen'
import type { BuildingSemanticsBacnetConfig } from '../../types'
import { useBacnetReferenceQuery } from '../../api/queries/use-bacnet-reference-query'
import { useSystemsQuery } from '../../api/queries/use-systems-query'
import { useDevicesQuery } from '../../api/queries/use-devices-query'
import { usePropertiesQuery } from '../../api/queries/use-properties-query'
import { useSaveBacnetReferenceMutation } from '../../api/mutations/use-save-bacnet-reference-mutation'
import { isShaclValidationError, extractShaclErrors } from '../../api/types'

interface FormState {
  selectedSystemUri?: string
  selectedDeviceUri?: string
  selectedPropertyUri?: string
  localSystems: SystemSummaryDto[]
  validationErrors: string[]
  showValidationModal: boolean
}

type FormAction =
  | { type: 'SELECT_SYSTEM'; payload: string }
  | { type: 'SELECT_DEVICE'; payload: string }
  | { type: 'SELECT_PROPERTY'; payload: string }
  | { type: 'ADD_LOCAL_SYSTEM'; payload: SystemSummaryDto }
  | { type: 'RESET_FORM' }
  | {
      type: 'LOAD_EXISTING_REFERENCE'
      payload: { systemUri: string; deviceUri: string; propertyUri: string }
    }
  | { type: 'SHOW_VALIDATION_ERRORS'; payload: string[] }
  | { type: 'HIDE_VALIDATION_ERRORS' }

const initialState: FormState = {
  selectedSystemUri: undefined,
  selectedDeviceUri: undefined,
  selectedPropertyUri: undefined,
  localSystems: [],
  validationErrors: [],
  showValidationModal: false,
}

function formReducer(state: FormState, action: FormAction): FormState {
  switch (action.type) {
    case 'SELECT_SYSTEM':
      return {
        ...state,
        selectedSystemUri: action.payload,
        selectedDeviceUri: undefined,
        selectedPropertyUri: undefined,
      }

    case 'SELECT_DEVICE':
      return {
        ...state,
        selectedDeviceUri: action.payload,
        selectedPropertyUri: undefined,
      }

    case 'SELECT_PROPERTY':
      return {
        ...state,
        selectedPropertyUri: action.payload,
      }

    case 'ADD_LOCAL_SYSTEM':
      return {
        ...state,
        localSystems: [...state.localSystems, action.payload],
        selectedSystemUri: action.payload.systemUri,
      }

    case 'RESET_FORM':
      return {
        ...initialState,
        localSystems: state.localSystems,
      }

    case 'LOAD_EXISTING_REFERENCE':
      return {
        ...state,
        selectedSystemUri: action.payload.systemUri,
        selectedDeviceUri: action.payload.deviceUri,
        selectedPropertyUri: action.payload.propertyUri,
      }

    case 'SHOW_VALIDATION_ERRORS':
      return {
        ...state,
        validationErrors: action.payload,
        showValidationModal: true,
      }

    case 'HIDE_VALIDATION_ERRORS':
      return {
        ...state,
        validationErrors: [],
        showValidationModal: false,
      }

    default:
      return state
  }
}

interface UseBuildingSemanticsFormParams {
  projectId: string
  bacnetPointId: string
  bacnetObjectType: string
  buildingSemanticsBacnetConfig: BuildingSemanticsBacnetConfig
  open: boolean
  onSaved: () => void
  onOpenChange: (open: boolean) => void
}

export function useBuildingSemanticsForm({
  projectId,
  bacnetPointId,
  bacnetObjectType,
  buildingSemanticsBacnetConfig,
  open,
  onSaved,
  onOpenChange,
}: UseBuildingSemanticsFormParams) {
  const [state, dispatch] = useReducer(formReducer, initialState)

  const { data: existingReference } = useBacnetReferenceQuery({
    projectId,
    bacnetPointId,
  })

  const { data: systemsFromApi = [], isLoading: isLoadingSystems } =
    useSystemsQuery(projectId)

  const { data: devices = [], isLoading: isLoadingDevices } = useDevicesQuery({
    projectId,
    systemUri: state.selectedSystemUri,
    bacnetObjectType,
  })

  const { data: properties = [], isLoading: isLoadingProperties } =
    usePropertiesQuery({
      projectId,
      deviceUri: state.selectedDeviceUri,
      bacnetObjectType,
    })

  const saveMutation = useSaveBacnetReferenceMutation()

  useEffect(() => {
    if (open && existingReference) {
      dispatch({
        type: 'LOAD_EXISTING_REFERENCE',
        payload: {
          systemUri: existingReference.systemUri,
          deviceUri: existingReference.deviceUri,
          propertyUri: existingReference.propertyUri,
        },
      })
    } else if (open) {
      dispatch({ type: 'RESET_FORM' })
    }
  }, [open, existingReference])

  const systems = [
    ...systemsFromApi,
    ...state.localSystems.filter(
      (local) =>
        !systemsFromApi.some((api) => api.systemUri === local.systemUri)
    ),
  ]

  const isFormValid = Boolean(
    state.selectedSystemUri &&
      state.selectedDeviceUri &&
      state.selectedPropertyUri
  )

  const selectSystem = (uri: string) => {
    dispatch({ type: 'SELECT_SYSTEM', payload: uri })
  }

  const selectDevice = (uri: string) => {
    dispatch({ type: 'SELECT_DEVICE', payload: uri })
  }

  const selectProperty = (uri: string) => {
    dispatch({ type: 'SELECT_PROPERTY', payload: uri })
  }

  const addLocalSystem = (system: SystemSummaryDto) => {
    dispatch({ type: 'ADD_LOCAL_SYSTEM', payload: system })
  }

  const hideValidationModal = () => {
    dispatch({ type: 'HIDE_VALIDATION_ERRORS' })
  }

  const handleSave = async () => {
    if (!state.selectedPropertyUri) {
      toast.error('Please select a property')
      return
    }

    saveMutation.mutate(
      {
        projectId,
        bacnetPointId,
        propertyUri: state.selectedPropertyUri,
        buildingSemanticsBacnetConfig,
      },
      {
        onSuccess: () => {
          toast.success('BACnet reference saved successfully')
          onSaved()
          onOpenChange(false)
        },
        onError: (error) => {
          if (isShaclValidationError(error)) {
            const errors = extractShaclErrors(error)
            dispatch({ type: 'SHOW_VALIDATION_ERRORS', payload: errors })
          } else {
            toast.error('Failed to save BACnet reference', {
              description:
                error instanceof Error ? error.message : 'Unknown error',
            })
          }
        },
      }
    )
  }

  return {
    state: {
      selectedSystemUri: state.selectedSystemUri,
      selectedDeviceUri: state.selectedDeviceUri,
      selectedPropertyUri: state.selectedPropertyUri,
      validationErrors: state.validationErrors,
      showValidationModal: state.showValidationModal,
    },
    actions: {
      selectSystem,
      selectDevice,
      selectProperty,
      addLocalSystem,
      hideValidationModal,
      handleSave,
    },
    data: {
      systems,
      devices,
      properties,
    },
    validation: {
      isFormValid,
    },
    loading: {
      isLoadingSystems,
      isLoadingDevices,
      isLoadingProperties,
      isSaving: saveMutation.isPending,
    },
  }
}
