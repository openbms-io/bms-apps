# Story 2.13.6: React Query Hooks for AI Suggestions

Status: drafted

## Story

As a developer,
I want React Query hooks that call the AI suggestion API endpoints,
so that React components can easily request AI suggestions with proper caching and loading states.

## Acceptance Criteria

1. ✅ `useSystemSuggestionQuery` hook calls `/api/ai/suggestions` with step='system'
2. ✅ `useDeviceSuggestionQuery` hook calls `/api/ai/suggestions` with step='device'
3. ✅ `usePropertySuggestionQuery` hook calls `/api/ai/suggestions` with step='property'
4. ✅ `useConfirmSuggestionMutation` hook calls `/api/ai/suggestions/confirm`
5. ✅ Hooks use query keys following existing semanticQueryKeys pattern
6. ✅ Hooks handle loading, error, and success states
7. ✅ Unit tests cover all hooks with mocked fetch

## Tasks / Subtasks

- [ ] Task 1: Update semanticQueryKeys (AC: 5)

  - [ ] Add aiSuggestions.system key
  - [ ] Add aiSuggestions.device key
  - [ ] Add aiSuggestions.property key

- [ ] Task 2: Create step-based suggestion hooks (TDD) (AC: 1-3, 6)

  - [ ] Create use-ai-suggestion-query.spec.ts tests
  - [ ] Implement useSystemSuggestionQuery
  - [ ] Implement useDeviceSuggestionQuery
  - [ ] Implement usePropertySuggestionQuery
  - [ ] Each hook accepts params object with orgId, projectId, point, candidates, context

- [ ] Task 3: Create confirmation mutation hook (TDD) (AC: 4, 6)

  - [ ] Add test for useConfirmSuggestionMutation
  - [ ] Implement mutation hook
  - [ ] Mutation accepts orgId, projectId, mapping record

- [ ] Task 4: Update or remove existing mock hook (AC: N/A)
  - [ ] Update useAISuggestionQuery to use new API
  - [ ] Remove mock-ai-suggestion.service.ts dependency

## Dev Notes

### File Locations

- Hooks: `apps/designer/src/domains/building-semantics/api/queries/use-ai-suggestion-query.ts`
- Tests: `apps/designer/src/domains/building-semantics/api/queries/use-ai-suggestion-query.spec.ts`
- Query Keys: `apps/designer/src/domains/building-semantics/api/queries/semantic-query-keys.ts`

### Hook Signatures (following project conventions)

```typescript
// System suggestion hook
export function useSystemSuggestionQuery({
  orgId,
  projectId,
  point,
  candidates,
  enabled = true,
}: {
  orgId: string;
  projectId: string;
  point: AIPointDTO;
  candidates: string[];
  enabled?: boolean;
}) {
  return useQuery({
    queryKey: semanticQueryKeys.aiSuggestions.system(
      orgId,
      projectId,
      point.name,
    ),
    queryFn: () =>
      fetchSuggestion({ step: "system", orgId, projectId, point, candidates }),
    enabled: enabled && !!orgId && !!projectId && !!point,
  });
}

// Device suggestion hook
export function useDeviceSuggestionQuery({
  orgId,
  projectId,
  point,
  candidates,
  selectedSystemId,
  enabled = true,
}: {
  orgId: string;
  projectId: string;
  point: AIPointDTO;
  candidates: string[];
  selectedSystemId: string;
  enabled?: boolean;
}) {
  return useQuery({
    queryKey: semanticQueryKeys.aiSuggestions.device(
      orgId,
      projectId,
      point.name,
      selectedSystemId,
    ),
    queryFn: () =>
      fetchSuggestion({
        step: "device",
        orgId,
        projectId,
        point,
        candidates,
        context: { selectedSystemId },
      }),
    enabled: enabled && !!orgId && !!projectId && !!point && !!selectedSystemId,
  });
}

// Property suggestion hook
export function usePropertySuggestionQuery({
  orgId,
  projectId,
  point,
  candidates,
  selectedSystemId,
  selectedDeviceId,
  enabled = true,
}: {
  orgId: string;
  projectId: string;
  point: AIPointDTO;
  candidates: string[];
  selectedSystemId: string;
  selectedDeviceId: string;
  enabled?: boolean;
}) {
  return useQuery({
    queryKey: semanticQueryKeys.aiSuggestions.property(
      orgId,
      projectId,
      point.name,
      selectedDeviceId,
    ),
    queryFn: () =>
      fetchSuggestion({
        step: "property",
        orgId,
        projectId,
        point,
        candidates,
        context: { selectedSystemId, selectedDeviceId },
      }),
    enabled: enabled && !!orgId && !!projectId && !!point && !!selectedDeviceId,
  });
}

// Confirmation mutation
export function useConfirmSuggestionMutation() {
  return useMutation({
    mutationFn: ({ orgId, projectId, mapping }: ConfirmSuggestionParams) =>
      confirmSuggestion({ orgId, projectId, mapping }),
  });
}
```

### Query Keys Pattern

```typescript
export const semanticQueryKeys = {
  // ... existing keys
  aiSuggestions: {
    all: ["ai-suggestions"] as const,
    system: (orgId: string, projectId: string, pointName: string) =>
      [
        ...semanticQueryKeys.aiSuggestions.all,
        "system",
        orgId,
        projectId,
        pointName,
      ] as const,
    device: (
      orgId: string,
      projectId: string,
      pointName: string,
      systemId: string,
    ) =>
      [
        ...semanticQueryKeys.aiSuggestions.all,
        "device",
        orgId,
        projectId,
        pointName,
        systemId,
      ] as const,
    property: (
      orgId: string,
      projectId: string,
      pointName: string,
      deviceId: string,
    ) =>
      [
        ...semanticQueryKeys.aiSuggestions.all,
        "property",
        orgId,
        projectId,
        pointName,
        deviceId,
      ] as const,
  },
};
```

### Project Structure Notes

- Hooks in `domains/building-semantics/api/queries/` (follows existing pattern)
- Query keys in same directory for consistency
- Client-side only - calls API routes, no direct AI SDK usage

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#6-React-Query-Integration]
- [Existing: apps/designer/src/domains/building-semantics/api/queries/use-ai-suggestion-query.ts]

## Dev Agent Record

### Context Reference

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List
