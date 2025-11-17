import { useReducer, useEffect } from 'react'
import type { SemanticEquipment } from '../../adapters/ashrae-223p/schemas'

export interface FormState {
  equipmentType: string
  deviceType: string
  observableProperty: string
  physicalSpaceName: string
  domainSpaceNames: string[]
  isSpaceSectionOpen: boolean
}

type FormAction =
  | { type: 'INITIALIZE'; payload: Partial<FormState> }
  | { type: 'USER_SET_EQUIPMENT_TYPE'; payload: string }
  | { type: 'USER_SET_DEVICE_TYPE'; payload: string }
  | { type: 'USER_SET_OBSERVABLE_PROPERTY'; payload: string }
  | { type: 'SET_PHYSICAL_SPACE'; payload: string }
  | { type: 'SET_DOMAIN_SPACES'; payload: string[] }
  | { type: 'TOGGLE_SPACE_SECTION' }

const initialState: FormState = {
  equipmentType: '',
  deviceType: '',
  observableProperty: '',
  physicalSpaceName: '',
  domainSpaceNames: [],
  isSpaceSectionOpen: true,
}

function formReducer(state: FormState, action: FormAction): FormState {
  switch (action.type) {
    case 'INITIALIZE':
      return { ...state, ...action.payload }

    case 'USER_SET_EQUIPMENT_TYPE':
      return {
        ...state,
        equipmentType: action.payload,
        deviceType: '',
        observableProperty: '',
      }

    case 'USER_SET_DEVICE_TYPE':
      return {
        ...state,
        deviceType: action.payload,
        observableProperty: '',
      }

    case 'USER_SET_OBSERVABLE_PROPERTY':
      return {
        ...state,
        observableProperty: action.payload,
      }

    case 'SET_PHYSICAL_SPACE':
      return {
        ...state,
        physicalSpaceName: action.payload,
      }

    case 'SET_DOMAIN_SPACES':
      return {
        ...state,
        domainSpaceNames: action.payload,
      }

    case 'TOGGLE_SPACE_SECTION':
      return {
        ...state,
        isSpaceSectionOpen: !state.isSpaceSectionOpen,
      }

    default:
      return state
  }
}

interface MappingSuggestion {
  equipmentTypeId: { id: string; confidence: number }
  deviceTypeId: { id: string; confidence: number }
  propertyId: { id: string; confidence: number }
  physicalSpace?: { id: { label: string }; confidence: number }
  domainSpaces?: Array<{ id: { label: string }; confidence: number }>
  overallConfidence: number
}

export function useMappingFormState(
  open: boolean,
  existingMapping?: SemanticEquipment,
  suggestion?: MappingSuggestion
) {
  const [state, dispatch] = useReducer(formReducer, initialState)

  useEffect(() => {
    if (!open) return

    if (existingMapping) {
      dispatch({
        type: 'INITIALIZE',
        payload: {
          equipmentType: existingMapping.equipmentTypeId,
          deviceType: existingMapping.deviceTypeId,
          observableProperty: existingMapping.propertyId,
          physicalSpaceName: existingMapping.physicalSpaceId || '',
          domainSpaceNames: existingMapping.domainSpaceIds || [],
        },
      })
    } else if (suggestion) {
      dispatch({
        type: 'INITIALIZE',
        payload: {
          equipmentType: suggestion.equipmentTypeId.id,
          deviceType: suggestion.deviceTypeId.id,
          observableProperty: suggestion.propertyId.id,
          physicalSpaceName: suggestion.physicalSpace?.id.label || '',
          domainSpaceNames: suggestion.domainSpaces?.map((ds) => ds.id.label) || [],
        },
      })
    }
  }, [open, existingMapping, suggestion])

  return {
    state,
    setEquipmentType: (value: string) =>
      dispatch({ type: 'USER_SET_EQUIPMENT_TYPE', payload: value }),
    setDeviceType: (value: string) =>
      dispatch({ type: 'USER_SET_DEVICE_TYPE', payload: value }),
    setObservableProperty: (value: string) =>
      dispatch({ type: 'USER_SET_OBSERVABLE_PROPERTY', payload: value }),
    setPhysicalSpaceName: (value: string) =>
      dispatch({ type: 'SET_PHYSICAL_SPACE', payload: value }),
    setDomainSpaceNames: (value: string[]) =>
      dispatch({ type: 'SET_DOMAIN_SPACES', payload: value }),
    toggleSpaceSection: () => dispatch({ type: 'TOGGLE_SPACE_SECTION' }),
  }
}
