# Story 2.13.7: Pass orgId to Building Semantics Modal

Status: drafted

## Story

As a developer,
I want the Building Semantics Modal to receive orgId from its parent container,
so that AI suggestions can be scoped to the correct organization.

## Acceptance Criteria

1. ✅ `ControllersTreeContainer` passes `orgId` to `BuildingSemanticsModal`
2. ✅ `BuildingSemanticsModal` accepts `orgId` prop
3. ✅ `useBuildingSemanticsForm` hook receives `orgId` for AI calls
4. ✅ orgId is passed to AI suggestion hooks in the modal
5. ✅ Unit tests verify orgId propagation

## Tasks / Subtasks

- [ ] Task 1: Update ControllersTreeContainer (AC: 1)

  - [ ] Import orgId from appropriate context/store
  - [ ] Pass orgId prop to BuildingSemanticsModal

- [ ] Task 2: Update BuildingSemanticsModal props (AC: 2, 4)

  - [ ] Add orgId to BuildingSemanticsModalProps interface
  - [ ] Pass orgId to useBuildingSemanticsForm hook
  - [ ] Pass orgId to child components that need it

- [ ] Task 3: Update useBuildingSemanticsForm hook (AC: 3)

  - [ ] Accept orgId parameter
  - [ ] Pass orgId to AI suggestion hooks
  - [ ] Use orgId in confirmation mutation

- [ ] Task 4: Add unit tests (AC: 5)
  - [ ] Test orgId is passed through component hierarchy
  - [ ] Test AI hooks receive correct orgId

## Dev Notes

### File Locations

- Container: `apps/designer/src/containers/controllers-tree-container.tsx`
- Modal: `apps/designer/src/domains/building-semantics/components/building-semantics-modal/index.tsx`
- Form Hook: `apps/designer/src/domains/building-semantics/components/building-semantics-modal/use-building-semantics-form.ts`

### Implementation Pattern

```typescript
// ControllersTreeContainer.tsx
export function ControllersTreeContainer() {
  const orgId = useOrgId() // or from context/store

  return (
    <BuildingSemanticsModal
      orgId={orgId}
      // ... other props
    />
  )
}

// BuildingSemanticsModal props
interface BuildingSemanticsModalProps {
  orgId: string
  projectId: string
  point: BACnetPointData
  // ... existing props
}

// useBuildingSemanticsForm hook
export function useBuildingSemanticsForm({
  orgId,
  projectId,
  point,
}: {
  orgId: string
  projectId: string
  point: BACnetPointData
}) {
  // Pass orgId to AI hooks
  const systemSuggestion = useSystemSuggestionQuery({
    orgId,
    projectId,
    point: toAIPointDTO(point),
    candidates: systemCandidates,
  })

  // ...
}
```

### orgId Source

The orgId should come from the application's auth/organization context. Check existing patterns in the codebase for how orgId is accessed (likely via a React context or Zustand store).

### Project Structure Notes

- Follows prop drilling pattern for orgId (container → modal → hook)
- No new stores or contexts needed if orgId already available
- Aligns with existing component hierarchy in containers/

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#7-Modal-Integration]

## Dev Agent Record

### Context Reference

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List
