# Story 2.13.4: Suggestion Engine with Vercel AI SDK

Status: done

## Story

As a developer,
I want a suggestion engine that uses Vercel AI SDK to generate step-specific mapping suggestions,
so that the AI can recommend system/device/property selections based on point metadata and memory context.

## Acceptance Criteria

1. ✅ `SuggestionEngine` class with `generateStepSuggestion` method
2. ✅ Accepts step type ('system' | 'device' | 'property'), point data, candidates, and memory context
3. ✅ Uses `generateObject()` from Vercel AI SDK with Zod schema
4. ✅ Returns `StepSuggestion` with selectedId, confidence, reasoning, alternatives
5. ✅ Builds step-specific system prompt with ASHRAE 223P context
6. ✅ Builds user prompt with rich point metadata (name, description, units, presentValue, stateText)
7. ✅ Unit tests cover all step types with mocked AI provider

## Tasks / Subtasks

- [x] Task 1: Create suggestion-engine.spec.ts (TDD) (AC: 1-7)

  - [x] Test generateStepSuggestion for 'system' step
  - [x] Test generateStepSuggestion for 'device' step
  - [x] Test generateStepSuggestion for 'property' step
  - [x] Test returns StepSuggestion structure
  - [x] Test includes memory context in prompt
  - [x] Test includes rich point metadata

- [x] Task 2: Create Zod schemas for AI response (AC: 4)

  - [x] Define StepSuggestionSchema
  - [x] Define alternatives array schema

- [x] Task 3: Implement suggestion-engine.ts (AC: 1-6)

  - [x] Export SuggestionEngine class
  - [x] Implement generateStepSuggestion with object destructuring
  - [x] Implement buildSystemPrompt for each step type
  - [x] Implement buildUserPrompt with Option D rich metadata
  - [x] Export createObjectGenerator factory function

- [x] Task 4: Update lib/server-only/ai/index.ts exports
  - [x] Export from suggestion-engine.ts

## Dev Notes

### File Locations

- Implementation: `apps/designer/src/lib/server-only/ai/suggestion-engine.ts`
- Tests: `apps/designer/src/lib/server-only/ai/suggestion-engine.spec.ts`

### Method Signature (with object destructuring)

```typescript
async function generateStepSuggestion({
  step,
  point,
  candidates,
  memoryContext,
  selectionContext,
}: {
  step: "system" | "device" | "property";
  point: AIPointContext["point"];
  candidates: string[];
  memoryContext: MemoryContext;
  selectionContext?: { systemId?: string; deviceId?: string };
}): Promise<StepSuggestion>;
```

### Point Metadata (Option D - Rich Metadata)

```typescript
interface AIPointContext {
  point: {
    name: string; // e.g., "VAV-2-01_ZoneTemp"
    objectType: string; // e.g., "analog-input"
    objectId: number;
    controllerId: string; // Pattern identification
    description?: string; // From discoveredProperties
    units?: string; // From discoveredProperties
    presentValue?: unknown; // From discoveredProperties
    stateText?: string[]; // For multistate objects
  };
}
```

### Step-Specific Prompts

- **System**: "Select the best ASHRAE 223P system template that matches this BACnet point"
- **Device**: "Select the best device type within the chosen system for this BACnet point"
- **Property**: "Select the best property (observable/actuatable) for this BACnet point"

### Project Structure Notes

- Server-only module in `lib/server-only/ai/` (not accessible from client)
- Uses Vercel AI SDK `generateObject()` for structured output
- Depends on ai-client.ts and memory-manager.ts from same directory

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#5.3-Suggestion-Engine]
- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#4.1-Context-Strategy]

## Dev Agent Record

### Context Reference

- N/A (story file was self-contained)

### Agent Model Used

- Claude Opus 4.5 (claude-opus-4-5-20251101)

### Debug Log References

- N/A (no debug issues encountered)

### Completion Notes List

- Used dependency injection pattern for IObjectGenerator interface
- createObjectGenerator() factory function creates real AI generator using Vercel AI SDK
- SuggestionEngine accepts IObjectGenerator via constructor
- Tests use mock generator implementing IObjectGenerator interface
- All 8 tests pass covering all step types and prompt content verification
- StepSuggestionSchema defined using Zod for structured AI output
- STEP_SYSTEM_PROMPTS map provides step-specific system instructions
- buildUserPrompt creates rich metadata prompt with point info, selection context, and memory
- Added AISuggestionService as orchestration layer combining MemoryManager + SuggestionEngine
- AISuggestionService.getSuggestion() handles memory retrieval + suggestion generation
- AISuggestionService.confirmMapping() handles storing confirmed mappings to Mem0
- createAISuggestionService() factory creates all dependencies
- Total: 32 tests pass across all AI modules

### File List

- `apps/designer/src/lib/server-only/ai/suggestion-engine.ts` (created)
- `apps/designer/src/lib/server-only/ai/suggestion-engine.spec.ts` (created)
- `apps/designer/src/lib/server-only/ai/ai-suggestion-service.ts` (created)
- `apps/designer/src/lib/server-only/ai/ai-suggestion-service.spec.ts` (created)
- `apps/designer/src/lib/server-only/ai/index.ts` (modified - added exports)
