# Story 2.13.4: Suggestion Engine with Vercel AI SDK

Status: drafted

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

- [ ] Task 1: Create suggestion-engine.spec.ts (TDD) (AC: 1-7)

  - [ ] Test generateStepSuggestion for 'system' step
  - [ ] Test generateStepSuggestion for 'device' step
  - [ ] Test generateStepSuggestion for 'property' step
  - [ ] Test returns StepSuggestion structure
  - [ ] Test includes memory context in prompt
  - [ ] Test includes rich point metadata

- [ ] Task 2: Create Zod schemas for AI response (AC: 4)

  - [ ] Define StepSuggestionSchema
  - [ ] Define alternatives array schema

- [ ] Task 3: Implement suggestion-engine.ts (AC: 1-6)

  - [ ] Export SuggestionEngine class
  - [ ] Implement generateStepSuggestion with object destructuring
  - [ ] Implement buildSystemPrompt for each step type
  - [ ] Implement buildUserPrompt with Option D rich metadata
  - [ ] Export singleton suggestionEngine instance

- [ ] Task 4: Update lib/server-only/ai/index.ts exports
  - [ ] Export from suggestion-engine.ts

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

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List
