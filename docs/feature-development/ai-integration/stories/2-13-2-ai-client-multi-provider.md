# Story 2.13.2: AI Client with Multi-Provider Support

Status: drafted

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
6. ✅ `getAIModel()` uses AI_MODEL env var when set, otherwise uses provider default
7. ✅ Unit tests cover all scenarios with mocked providers

## Tasks / Subtasks

- [ ] Task 1: Create ai-client.spec.ts (TDD - write tests first) (AC: 1-7)

  - [ ] Test getProvider() returns 'anthropic' by default
  - [ ] Test getProvider() returns 'openai' when set
  - [ ] Test getProvider() throws for invalid provider
  - [ ] Test getAIModel() with anthropic provider
  - [ ] Test getAIModel() with openai provider
  - [ ] Test getAIModel() uses custom model from AI_MODEL

- [ ] Task 2: Implement ai-client.ts (AC: 1-6)

  - [ ] Export getProvider() function
  - [ ] Export getAIModel() function
  - [ ] Export AIProvider type
  - [ ] Define DEFAULT_MODELS constant

- [ ] Task 3: Create lib/server-only/ai/index.ts exports (AC: N/A)
  - [ ] Create index.ts barrel file
  - [ ] Export from ai-client.ts

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

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List
