# Story 2.13.2: AI Client with Multi-Provider Support

Status: review

## Story

As a developer,
I want an AI client wrapper that supports both Claude and OpenAI providers,
so that the AI provider can be switched via environment variable without code changes.

## Acceptance Criteria

1. ✅ `getProvider()` returns 'anthropic' by default when AI_PROVIDER not set
2. ✅ `getProvider()` returns 'openai' when AI_PROVIDER=openai
3. ✅ `getProvider()` throws error for invalid AI_PROVIDER values
4. ✅ `getAIModel()` uses Anthropic provider when AI_PROVIDER=anthropic
5. ✅ `getAIModel()` uses OpenAI provider when AI_PROVIDER=openai
6. ✅ `getAIModel()` requires AI_MODEL env var (throws if not set)
7. ✅ Unit tests cover all scenarios with mocked providers

## Tasks / Subtasks

- [x] Task 1: Create ai-client.spec.ts (TDD - write tests first) (AC: 1-7)

  - [x] Test getProvider() returns 'anthropic' by default
  - [x] Test getProvider() returns 'openai' when set
  - [x] Test getProvider() throws for invalid provider
  - [x] Test getAIModel() with anthropic provider
  - [x] Test getAIModel() with openai provider
  - [x] Test getAIModel() throws when AI_MODEL not set

- [x] Task 2: Implement ai-client.ts (AC: 1-6)

  - [x] Export getProvider() function
  - [x] Export getAIModel() function
  - [x] Export AIProvider type

- [x] Task 3: Create lib/server-only/ai/index.ts exports (AC: N/A)
  - [x] Create index.ts barrel file
  - [x] Export from ai-client.ts

## Dev Notes

### File Locations

- Implementation: `apps/designer/src/lib/server-only/ai/ai-client.ts`
- Tests: `apps/designer/src/lib/server-only/ai/ai-client.spec.ts`
- Exports: `apps/designer/src/lib/server-only/ai/index.ts`

### Architecture Note

This is a server-side only module. The AI client is used by API routes, NOT directly by React components. React components will use React Query hooks that call API endpoints.

### Testing Approach

Mock `@ai-sdk/anthropic` and `@ai-sdk/openai` packages in tests. Use jest.mock() to replace the createAnthropic and createOpenAI functions.

### Project Structure Notes

- Server-only module in `lib/server-only/ai/` (not accessible from client)
- Follows Next.js convention for server-side utilities
- No conflicts with existing `lib/ai/` types (those are shared types)

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#5.1-AI-Client]

## Dev Agent Record

### Context Reference

- N/A (story file was self-contained)

### Agent Model Used

- Claude Opus 4.5 (claude-opus-4-5-20251101)

### Debug Log References

- N/A (no debug issues encountered)

### Completion Notes List

- Task 1: Created comprehensive tests covering:
  - getProvider() with default, explicit anthropic, explicit openai, and invalid values
  - getAIModel() throws error when AI_MODEL not set
  - getAIModel() uses correct provider based on AI_PROVIDER env var
  - getAIModel() uses custom models from AI_MODEL env var
- Task 2: Implemented ai-client.ts with:
  - getProvider() - validates and returns AI provider
  - getAIModel() - creates AI model instance using Vercel AI SDK
  - AIProvider type export
  - AI_MODEL is required (no defaults - throws if not set)
- Task 3: Created index.ts barrel file exporting all public APIs
- Updated .env.template to mark AI_MODEL as required (from Story 2.13.1)

### File List

- `apps/designer/src/lib/server-only/ai/ai-client.ts` (created)
- `apps/designer/src/lib/server-only/ai/ai-client.spec.ts` (created)
- `apps/designer/src/lib/server-only/ai/index.ts` (created)
- `apps/designer/.env.template` (modified - AI_MODEL now required)
