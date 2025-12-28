# Story 2.13.5: API Routes and DTO Schemas

Status: drafted

## Story

As a developer,
I want API routes for AI suggestions with properly defined DTO schemas,
so that React components can request AI suggestions via HTTP endpoints.

## Acceptance Criteria

1. ✅ `AISuggestionRequestDTOSchema` validates step, orgId, projectId, point, candidates
2. ✅ `AISuggestionResponseDTOSchema` validates success, data (selectedId, confidence, reasoning, alternatives)
3. ✅ `AISuggestionConfirmRequestDTOSchema` validates orgId, projectId, mapping record
4. ✅ POST `/api/ai/suggestions` returns step suggestion from AI
5. ✅ POST `/api/ai/suggestions/confirm` stores confirmed mapping in Mem0
6. ✅ API returns 503 with "AI unavailable" message when AI/Mem0 is unavailable
7. ✅ Unit tests cover request validation and response structure

## Tasks / Subtasks

- [ ] Task 1: Create DTO schemas (TDD) (AC: 1-3)

  - [ ] Create ai-suggestion.dto.schemas.spec.ts with tests
  - [ ] Define AISuggestionRequestDTOSchema
  - [ ] Define AISuggestionResponseDTOSchema
  - [ ] Define AISuggestionConfirmRequestDTOSchema
  - [ ] Define AIPointDTOSchema for rich point metadata

- [ ] Task 2: Create /api/ai/suggestions route (TDD) (AC: 4, 6)

  - [ ] Create route.spec.ts with tests
  - [ ] Implement POST handler
  - [ ] Validate request with DTO schema
  - [ ] Call memoryManager.retrieveContext
  - [ ] Call suggestionEngine.generateStepSuggestion
  - [ ] Return 503 with message when AI unavailable

- [ ] Task 3: Create /api/ai/suggestions/confirm route (TDD) (AC: 5, 6)
  - [ ] Create route.spec.ts with tests
  - [ ] Implement POST handler
  - [ ] Validate request with DTO schema
  - [ ] Call memoryManager.storeMapping
  - [ ] Return 503 with message when Mem0 unavailable

## Dev Notes

### File Locations

- DTOs: `apps/designer/src/domains/building-semantics/adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas.ts`
- DTO Tests: `apps/designer/src/domains/building-semantics/adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas.spec.ts`
- Suggestions Route: `apps/designer/src/app/api/ai/suggestions/route.ts`
- Suggestions Route Tests: `apps/designer/src/app/api/ai/suggestions/route.spec.ts`
- Confirm Route: `apps/designer/src/app/api/ai/suggestions/confirm/route.ts`
- Confirm Route Tests: `apps/designer/src/app/api/ai/suggestions/confirm/route.spec.ts`

### Architecture

```
┌─────────────────────────────────────────────────────────────────────┐
│  Client (React Components)                                          │
│  └── React Query Hooks (domains/building-semantics/api/queries/)   │
└─────────────────────────────────────┬───────────────────────────────┘
                                      │ HTTP
                                      ▼
┌─────────────────────────────────────────────────────────────────────┐
│  API Routes (app/api/ai/suggestions/)                               │
│  └── Uses DTO schemas for request/response validation              │
└─────────────────────────────────────┬───────────────────────────────┘
                                      │ imports
                                      ▼
┌─────────────────────────────────────────────────────────────────────┐
│  Server-Only Modules (lib/server-only/ai/)                         │
│  ├── ai-client.ts (provider selection)                             │
│  ├── memory-manager.ts (Mem0 integration)                          │
│  └── suggestion-engine.ts (Vercel AI SDK)                          │
└─────────────────────────────────────────────────────────────────────┘
```

### DTO Schema Pattern (following existing conventions)

```typescript
import { z } from "zod";

// Request DTO
export const AISuggestionRequestDTOSchema = z.object({
  step: z.enum(["system", "device", "property"]),
  orgId: z.string(),
  projectId: z.string(),
  point: AIPointDTOSchema,
  candidates: z.array(z.string()).max(10),
  context: z
    .object({
      selectedSystemId: z.string().optional(),
      selectedDeviceId: z.string().optional(),
    })
    .optional(),
});

export type AISuggestionRequestDTO = z.infer<
  typeof AISuggestionRequestDTOSchema
>;

// Response DTO
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
        }),
      ),
    })
    .optional(),
  error: z.string().optional(),
});

export type AISuggestionResponseDTO = z.infer<
  typeof AISuggestionResponseDTOSchema
>;
```

### Fallback Behavior

When AI or Mem0 is unavailable:

- Return HTTP 503 (Service Unavailable)
- Response body: `{ success: false, error: "AI service unavailable" }`
- No mock fallback - user proceeds with manual selection

### Project Structure Notes

- DTOs in `domains/building-semantics/adapters/ashrae-223p/schemas/` (follows existing DTO pattern)
- API routes in `app/api/ai/` (Next.js App Router convention)
- Server-only imports from `lib/server-only/ai/`

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#5.4-API-Routes]
- [Source: docs/coding-standards.md#Zod-Schemas]

## Dev Agent Record

### Context Reference

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List
