import { useQuery, useMutation } from '@tanstack/react-query'
import { semanticQueryKeys } from './query-keys'
import type {
  AIPointDTO,
  AICandidate,
  StepType,
  MappingRecordDTO,
  AISuggestionResponseDTO,
} from '../../adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas'

interface BaseSuggestionParams {
  orgId: string
  siteId: string
  projectId: string
  point: AIPointDTO | undefined
  candidates: AICandidate[]
}

interface SystemSuggestionParams extends BaseSuggestionParams {}

interface DeviceSuggestionParams extends BaseSuggestionParams {
  systemId: string | undefined
}

interface PropertySuggestionParams extends BaseSuggestionParams {
  systemId: string | undefined
  deviceId: string | undefined
}

interface ConfirmMappingParams {
  orgId: string
  siteId: string
  projectId: string
}

interface FetchSuggestionParams {
  orgId: string
  siteId: string
  projectId: string
  step: StepType
  point: AIPointDTO
  candidates: AICandidate[]
  selectionContext?: { systemId?: string; deviceId?: string }
}

async function fetchSuggestion({
  orgId,
  siteId,
  projectId,
  step,
  point,
  candidates,
  selectionContext,
}: FetchSuggestionParams): Promise<AISuggestionResponseDTO> {
  const response = await fetch(
    `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/ai/suggestions`,
    {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        step,
        point,
        candidates,
        selectionContext,
      }),
    }
  )

  if (!response.ok) {
    throw new Error(`AI suggestion request failed: ${response.status}`)
  }

  return response.json()
}

interface ConfirmMappingApiParams {
  orgId: string
  siteId: string
  projectId: string
  mapping: MappingRecordDTO
}

async function confirmMappingApi({
  orgId,
  siteId,
  projectId,
  mapping,
}: ConfirmMappingApiParams): Promise<{ success: boolean }> {
  const response = await fetch(
    `/api/organizations/${orgId}/sites/${siteId}/projects/${projectId}/ai/suggestions/confirm`,
    {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ mapping }),
    }
  )

  if (!response.ok) {
    throw new Error(`Confirm mapping request failed: ${response.status}`)
  }

  return response.json()
}

export function useSystemSuggestion({
  orgId,
  siteId,
  projectId,
  point,
  candidates,
}: SystemSuggestionParams) {
  const pointId = point?.id ?? 'none'

  return useQuery({
    queryKey: semanticQueryKeys.aiSuggestions.step(
      'system',
      orgId,
      projectId,
      pointId
    ),
    queryFn: () =>
      fetchSuggestion({
        orgId,
        siteId,
        projectId,
        step: 'system',
        point: point!,
        candidates,
      }),
    enabled: !!point && candidates.length > 0,
    staleTime: 5 * 60 * 1000,
  })
}

export function useDeviceSuggestion({
  orgId,
  siteId,
  projectId,
  point,
  candidates,
  systemId,
}: DeviceSuggestionParams) {
  const pointId = point?.id ?? 'none'

  return useQuery({
    queryKey: semanticQueryKeys.aiSuggestions.step(
      'device',
      orgId,
      projectId,
      pointId
    ),
    queryFn: () =>
      fetchSuggestion({
        orgId,
        siteId,
        projectId,
        step: 'device',
        point: point!,
        candidates,
        selectionContext: { systemId },
      }),
    enabled: !!point && candidates.length > 0 && !!systemId,
    staleTime: 5 * 60 * 1000,
  })
}

export function usePropertySuggestion({
  orgId,
  siteId,
  projectId,
  point,
  candidates,
  systemId,
  deviceId,
}: PropertySuggestionParams) {
  const pointId = point?.id ?? 'none'

  return useQuery({
    queryKey: semanticQueryKeys.aiSuggestions.step(
      'property',
      orgId,
      projectId,
      pointId
    ),
    queryFn: () =>
      fetchSuggestion({
        orgId,
        siteId,
        projectId,
        step: 'property',
        point: point!,
        candidates,
        selectionContext: { systemId, deviceId },
      }),
    enabled: !!point && candidates.length > 0 && !!systemId && !!deviceId,
    staleTime: 5 * 60 * 1000,
  })
}

export function useConfirmMapping({
  orgId,
  siteId,
  projectId,
}: ConfirmMappingParams) {
  return useMutation({
    mutationKey: semanticQueryKeys.aiSuggestions.confirm(orgId, projectId),
    mutationFn: (mapping: MappingRecordDTO) =>
      confirmMappingApi({ orgId, siteId, projectId, mapping }),
  })
}
