import { z } from 'zod'

/**
 * AI Point DTO Schema
 *
 * Rich point metadata for AI suggestion requests.
 * Contains all relevant BACnet point information for semantic mapping.
 */
export const AIPointDTOSchema = z.object({
  name: z.string(),
  objectType: z.string(),
  objectId: z.number(),
  controllerId: z.string(),
  description: z.string().optional(),
  units: z.string().optional(),
  presentValue: z.unknown().optional(),
  stateText: z.array(z.string()).optional(),
})

export type AIPointDTO = z.infer<typeof AIPointDTOSchema>

/**
 * AI Suggestion Request DTO Schema
 *
 * Request body for POST /api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/ai/suggestions
 * Note: orgId, siteId, projectId come from path params, not body
 */
export const AISuggestionRequestDTOSchema = z.object({
  step: z.enum(['system', 'device', 'property']),
  point: AIPointDTOSchema,
  candidates: z.array(z.string()).max(10),
  selectionContext: z
    .object({
      systemId: z.string().optional(),
      deviceId: z.string().optional(),
    })
    .optional(),
})

export type AISuggestionRequestDTO = z.infer<
  typeof AISuggestionRequestDTOSchema
>

/**
 * AI Suggestion Response DTO Schema
 *
 * Response body for POST /api/ai/suggestions
 */
export const AISuggestionResponseDTOSchema = z.object({
  success: z.boolean(),
  data: z
    .object({
      selectedId: z.string(),
      confidence: z.number().min(0).max(1),
      reasoning: z.string(),
      alternatives: z.array(
        z.object({
          id: z.string(),
          confidence: z.number().min(0).max(1),
        })
      ),
    })
    .optional(),
  error: z.string().optional(),
})

export type AISuggestionResponseDTO = z.infer<
  typeof AISuggestionResponseDTOSchema
>

/**
 * Mapping Record DTO Schema
 *
 * Record of a confirmed mapping decision for storage in Mem0.
 */
export const MappingRecordDTOSchema = z.object({
  pointPattern: z.string(),
  controllerId: z.string(),
  step: z.enum(['system', 'device', 'property']),
  selectedId: z.string(),
  wasOverridden: z.boolean(),
})

export type MappingRecordDTO = z.infer<typeof MappingRecordDTOSchema>

/**
 * AI Suggestion Confirm Request DTO Schema
 *
 * Request body for POST /api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/ai/suggestions/confirm
 * Note: orgId, siteId, projectId come from path params, not body
 */
export const AISuggestionConfirmRequestDTOSchema = z.object({
  mapping: MappingRecordDTOSchema,
})

export type AISuggestionConfirmRequestDTO = z.infer<
  typeof AISuggestionConfirmRequestDTOSchema
>
