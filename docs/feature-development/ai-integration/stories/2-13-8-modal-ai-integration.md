# Story 2.13.8: Wire Up AI Suggestions in Building Semantics Modal

Status: drafted

## Story

As a user,
I want the Building Semantics Modal to show AI-powered suggestions for system, device, and property selections,
so that mapping BACnet points to ASHRAE 223P ontology is faster and more accurate.

## Acceptance Criteria

1. ✅ System selector shows AI suggestion when available
2. ✅ Device selector shows AI suggestion based on selected system
3. ✅ Property selector shows AI suggestion based on selected device
4. ✅ Loading states shown while AI is generating suggestions
5. ✅ "AI unavailable" message shown when API returns 503
6. ✅ User can override AI suggestions (manual selection still works)
7. ✅ Confirmed mappings are stored via confirm mutation
8. ✅ wasOverridden flag is set correctly when user changes AI suggestion

## Tasks / Subtasks

- [ ] Task 1: Update SystemSelector component (AC: 1, 4, 5, 6)

  - [ ] Call useSystemSuggestionQuery hook
  - [ ] Show loading indicator while fetching
  - [ ] Pre-select AI suggested system
  - [ ] Show "AI unavailable" badge if error
  - [ ] Allow user to change selection

- [ ] Task 2: Update DeviceSelector component (AC: 2, 4, 5, 6)

  - [ ] Call useDeviceSuggestionQuery with selected system
  - [ ] Show loading indicator while fetching
  - [ ] Pre-select AI suggested device
  - [ ] Track if user overrides AI suggestion

- [ ] Task 3: Update PropertySelector component (AC: 3, 4, 5, 6)

  - [ ] Call usePropertySuggestionQuery with selected device
  - [ ] Show loading indicator while fetching
  - [ ] Pre-select AI suggested property
  - [ ] Track if user overrides AI suggestion

- [ ] Task 4: Implement confirmation flow (AC: 7, 8)

  - [ ] On form submit, call useConfirmSuggestionMutation
  - [ ] Calculate wasOverridden for each step
  - [ ] Store all three mappings (system, device, property)

- [ ] Task 5: Add integration tests (AC: 1-8)
  - [ ] Test full flow with mocked API
  - [ ] Test AI unavailable scenario
  - [ ] Test user override scenario

## Dev Notes

### File Locations

- System Selector: `apps/designer/src/domains/building-semantics/components/system-selector.tsx`
- Modal: `apps/designer/src/domains/building-semantics/components/building-semantics-modal/index.tsx`
- Form Hook: `apps/designer/src/domains/building-semantics/components/building-semantics-modal/use-building-semantics-form.ts`

### UI Pattern for AI Suggestions

```tsx
// In selector components
function SystemSelector({ orgId, projectId, point, candidates }) {
  const { data, isLoading, isError } = useSystemSuggestionQuery({
    orgId,
    projectId,
    point,
    candidates,
  });

  // Pre-select AI suggestion when available
  useEffect(() => {
    if (data?.data?.selectedId && !userHasSelected) {
      setSelectedSystem(data.data.selectedId);
    }
  }, [data]);

  return (
    <Select value={selectedSystem} onValueChange={handleChange}>
      {isLoading && <Badge variant="secondary">AI thinking...</Badge>}
      {isError && <Badge variant="destructive">AI unavailable</Badge>}
      {data?.data && (
        <Badge variant="default">
          AI: {data.data.confidence * 100}% confident
        </Badge>
      )}
      {/* options */}
    </Select>
  );
}
```

### Override Tracking

```typescript
// In useBuildingSemanticsForm
const [aiSuggestions, setAiSuggestions] = useState({
  system: null,
  device: null,
  property: null,
});

const [userSelections, setUserSelections] = useState({
  system: null,
  device: null,
  property: null,
});

// On submit
const mappings = [
  {
    step: "system",
    selectedId: userSelections.system,
    wasOverridden: userSelections.system !== aiSuggestions.system,
  },
  // ... device, property
];
```

### Fallback Behavior

When AI is unavailable (503 response):

- Show "AI unavailable" badge
- User proceeds with manual selection
- No mock/fallback suggestions shown

### Project Structure Notes

- UI components in `domains/building-semantics/components/`
- Uses shadcn/ui Badge and Select components
- Follows existing selector component patterns

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#8-Modal-Integration]
- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#4.3-Self-Learning-Flow]

## Dev Agent Record

### Context Reference

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List
