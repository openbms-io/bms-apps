# Story 2.13.1: Install Packages and Environment Configuration

Status: done

## Story

As a developer,
I want Vercel AI SDK and Mem0 packages installed with environment configuration,
so that the AI infrastructure dependencies are available for development.

## Acceptance Criteria

1. ✅ `ai`, `@ai-sdk/anthropic`, `@ai-sdk/openai`, and `mem0ai` packages are installed
2. ✅ `.env.template` updated with AI_PROVIDER, ANTHROPIC_API_KEY, OPENAI_API_KEY, MEM0_API_KEY, AI_MODEL
3. ✅ Environment variables have clear comments explaining usage
4. ✅ No NEXT*PUBLIC* prefix on any AI-related environment variables (server-side only)

## Tasks / Subtasks

- [x] Task 1: Install npm packages (AC: 1)

  - [x] Run `pnpm add ai @ai-sdk/anthropic @ai-sdk/openai mem0ai` in apps/designer
  - [x] Verify packages appear in package.json

- [x] Task 2: Update .env.template (AC: 2, 3, 4)
  - [x] Add AI_PROVIDER with default "anthropic"
  - [x] Add ANTHROPIC_API_KEY (conditional on AI_PROVIDER)
  - [x] Add OPENAI_API_KEY (conditional on AI_PROVIDER)
  - [x] Add MEM0_API_KEY (required)
  - [x] Add AI_MODEL (optional override)
  - [x] Add comments documenting each variable

## Dev Notes

### Package Versions

Install latest stable versions. As of spec creation:

- `ai` ^3.x (Vercel AI SDK core)
- `@ai-sdk/anthropic` ^0.x (Anthropic provider)
- `@ai-sdk/openai` ^0.x (OpenAI provider)
- `mem0ai` ^1.x (Mem0 Cloud SDK)

### Default Model Configuration

- Anthropic: `claude-3-5-sonnet-20241022`
- OpenAI: `gpt-4o`

### Project Structure Notes

- All AI packages installed in `apps/designer` only (not shared)
- Environment variables are server-side only (no NEXT*PUBLIC* prefix)
- Aligns with unified project structure for Next.js app configuration

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#3.1-Dependencies]
- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#3.2-Environment-Variables]

## Dev Agent Record

### Context Reference

- `docs/feature-development/ai-integration/stories/2-13-1-install-packages-and-env-config.context.xml`

### Agent Model Used

- Claude Opus 4.5 (claude-opus-4-5-20251101)

### Debug Log References

- N/A (no debug issues encountered)

### Completion Notes List

- Task 1: Installed packages via `pnpm add ai @ai-sdk/anthropic @ai-sdk/openai mem0ai`
  - `@ai-sdk/anthropic`: ^3.0.1
  - `@ai-sdk/openai`: ^3.0.1
  - `ai`: ^6.0.3
  - `mem0ai`: ^2.1.38
- Task 2: Updated .env.template with all required AI environment variables
  - AI_PROVIDER with default "anthropic"
  - ANTHROPIC_API_KEY, OPENAI_API_KEY, MEM0_API_KEY, AI_MODEL
  - Clear comments explaining usage and API key sources
  - No NEXT*PUBLIC* prefix (server-side only)

### File List

- `apps/designer/package.json` (modified - added AI dependencies)
- `apps/designer/.env.template` (modified - added AI environment variables)
