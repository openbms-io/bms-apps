import { useMemo, useEffect, useState, useCallback } from 'react'
import {
  useSystemSuggestion,
  useDeviceSuggestion,
  usePropertySuggestion,
  useConfirmMapping,
} from '../../api/queries/use-ai-suggestion-query'
import type {
  AIPointDTO,
  AICandidate,
  StepType,
} from '../../adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas'

interface UseAISuggestionsParams {
  context: {
    orgId: string
    siteId: string
    projectId: string
  }
  point: {
    id: string
    name?: string
    description?: string
    objectType: string
    objectId: number
    controllerId: string
  }
  enabled: boolean
  selections: {
    systemUri?: string
    deviceUri?: string
    propertyUri?: string
  }
  candidates: {
    system: AICandidate[]
    device: AICandidate[]
    property: AICandidate[]
  }
}

interface SuggestionState {
  suggestedSystemUri?: string
  suggestedDeviceUri?: string
  suggestedPropertyUri?: string
  systemWasOverridden: boolean
  deviceWasOverridden: boolean
  propertyWasOverridden: boolean
}

const initialState: SuggestionState = {
  systemWasOverridden: false,
  deviceWasOverridden: false,
  propertyWasOverridden: false,
}

const CONFIDENCE_THRESHOLD = 0.8

export function useAISuggestions({
  context,
  point,
  enabled,
  selections,
  candidates,
}: UseAISuggestionsParams) {
  const { orgId, siteId, projectId } = context
  const {
    systemUri: selectedSystemUri,
    deviceUri: selectedDeviceUri,
    propertyUri: selectedPropertyUri,
  } = selections

  const [state, setState] = useState<SuggestionState>(initialState)

  const aiPoint: AIPointDTO | undefined = useMemo(() => {
    if (!enabled || !point.name) return undefined
    return {
      id: point.id,
      name: point.name,
      objectType: point.objectType,
      objectId: point.objectId,
      controllerId: point.controllerId,
      description: point.description,
    }
  }, [enabled, point])

  const systemQuery = useSystemSuggestion({
    orgId,
    siteId,
    projectId,
    point: aiPoint,
    candidates: candidates.system,
  })

  const deviceQuery = useDeviceSuggestion({
    orgId,
    siteId,
    projectId,
    point: aiPoint,
    candidates: candidates.device,
    systemId: selectedSystemUri,
  })

  const propertyQuery = usePropertySuggestion({
    orgId,
    siteId,
    projectId,
    point: aiPoint,
    candidates: candidates.property,
    systemId: selectedSystemUri,
    deviceId: selectedDeviceUri,
  })

  const confirmMutation = useConfirmMapping({ orgId, siteId, projectId })

  useEffect(() => {
    setState((prev) => {
      const updates: Partial<SuggestionState> = {}

      const systemUri = systemQuery.data?.data?.selectedId
      if (systemUri && !prev.suggestedSystemUri) {
        updates.suggestedSystemUri = systemUri
      }

      const deviceUri = deviceQuery.data?.data?.selectedId
      if (deviceUri && !prev.suggestedDeviceUri) {
        updates.suggestedDeviceUri = deviceUri
      }

      const propertyUri = propertyQuery.data?.data?.selectedId
      if (propertyUri && !prev.suggestedPropertyUri) {
        updates.suggestedPropertyUri = propertyUri
      }

      return Object.keys(updates).length > 0 ? { ...prev, ...updates } : prev
    })
  }, [systemQuery.data, deviceQuery.data, propertyQuery.data])

  const trackSelection = useCallback((step: StepType, selectedUri: string) => {
    setState((prev) => {
      if (step === 'system' && prev.suggestedSystemUri) {
        return {
          ...prev,
          systemWasOverridden: selectedUri !== prev.suggestedSystemUri,
        }
      }
      if (step === 'device' && prev.suggestedDeviceUri) {
        return {
          ...prev,
          deviceWasOverridden: selectedUri !== prev.suggestedDeviceUri,
        }
      }
      if (step === 'property' && prev.suggestedPropertyUri) {
        return {
          ...prev,
          propertyWasOverridden: selectedUri !== prev.suggestedPropertyUri,
        }
      }
      return prev
    })
  }, [])

  const confirmAllMappings = useCallback(async () => {
    const baseMapping = {
      pointPattern: point.id,
      controllerId: point.controllerId,
    }
    const promises: Promise<{ success: boolean }>[] = []

    if (selectedSystemUri) {
      promises.push(
        confirmMutation.mutateAsync({
          ...baseMapping,
          step: 'system',
          selectedId: selectedSystemUri,
          wasOverridden: state.systemWasOverridden,
        })
      )
    }
    if (selectedDeviceUri) {
      promises.push(
        confirmMutation.mutateAsync({
          ...baseMapping,
          step: 'device',
          selectedId: selectedDeviceUri,
          wasOverridden: state.deviceWasOverridden,
        })
      )
    }
    if (selectedPropertyUri) {
      promises.push(
        confirmMutation.mutateAsync({
          ...baseMapping,
          step: 'property',
          selectedId: selectedPropertyUri,
          wasOverridden: state.propertyWasOverridden,
        })
      )
    }

    await Promise.allSettled(promises)
  }, [
    point.id,
    point.controllerId,
    selectedSystemUri,
    selectedDeviceUri,
    selectedPropertyUri,
    state,
    confirmMutation,
  ])

  const reset = useCallback(() => {
    setState(initialState)
  }, [])

  const lowConfidence = useMemo(() => {
    const systemSuggestion = systemQuery.data?.data
    const deviceSuggestion = deviceQuery.data?.data
    const propertySuggestion = propertyQuery.data?.data

    return {
      system: systemSuggestion
        ? systemSuggestion.confidence < CONFIDENCE_THRESHOLD
        : false,
      device: deviceSuggestion
        ? deviceSuggestion.confidence < CONFIDENCE_THRESHOLD
        : false,
      property: propertySuggestion
        ? propertySuggestion.confidence < CONFIDENCE_THRESHOLD
        : false,
    }
  }, [systemQuery.data, deviceQuery.data, propertyQuery.data])

  return {
    suggestions: {
      system: systemQuery.data?.data,
      device: deviceQuery.data?.data,
      property: propertyQuery.data?.data,
    },
    loading: {
      system: systemQuery.isLoading,
      device: deviceQuery.isLoading,
      property: propertyQuery.isLoading,
    },
    lowConfidence,
    trackSelection,
    confirmAllMappings,
    reset,
  }
}
