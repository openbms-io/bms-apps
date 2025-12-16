# Story 1B.2: G36 VAV Reheat Block UI Component

Status: done

## Story

As a building controls engineer,
I want to see the G36 VAV Reheat block on the canvas with I/O connectors,
So that I can wire it to BACnet points.

## Acceptance Criteria

1. G36 VAV Reheat block renders on canvas with distinct visual style
2. Input connectors visible and labeled (zoneTemperature, coolingSetpoint, etc.)
3. Output connectors visible and labeled (damperPosition, valvePosition, airflowSetpoint)
4. Block appears in palette under "Control Sequences" category
5. Drag-drop creates API instance via `POST /api/v1/g36/vav-reheat/instances`
6. Node stores returned `instance_id` in node data
7. Delete node calls `DELETE /api/v1/g36/vav-reheat/instances/{instance_id}`
8. Component tests pass

## Tasks / Subtasks

- [x] Task 1: Create Control Sequences sidebar section (AC: #4)

  - [x] Create `control-sequences-section.tsx` following `logic-nodes-section.tsx` pattern
  - [x] Add G36 VAV Reheat as draggable item with distinct icon
  - [x] Configure drag data: `type: 'control-sequence-node'`, `nodeType: 'g36-vav-reheat'`
  - [x] Add section to supervisors tab or create new tab in sidebar

- [x] Task 2: Add `addControlSequenceNode` to flow store (AC: #5, #6)

  - [x] Add `addControlSequenceNode` action to flow-slice.ts
  - [x] Generate UUID client-side for `instance_id`
  - [x] Call `POST /api/v1/g36/vav-reheat/instances` with `instance_id`
  - [x] On success: create React Flow node with instanceId in metadata
  - [x] On failure: show error toast, don't add node

- [x] Task 3: Update drag-and-drop handler (AC: #5)

  - [x] Add `control-sequence-node` case to `use-node-creation.ts`
  - [x] Call new `addControlSequenceNode` action

- [x] Task 4: Add node deletion API call (AC: #7)

  - [x] Hook into node deletion in flow store
  - [x] For control-sequence nodes, call `DELETE /api/v1/g36/vav-reheat/instances/{instance_id}`
  - [x] Fire-and-forget: don't block deletion on API response

- [x] Task 5: Add API client functions to control-sequence domain (AC: #5, #7)

  - [x] Create `api/client.ts` with `createInstance` and `deleteInstance` functions
  - [x] Use generated client from `api/generated/sdk.gen.ts`
  - [x] Export from domain index

- [x] Task 6: Write component tests (AC: #8)

  - [x] Test G36VavReheatNode renders with correct structure
  - [x] Test input handles render with labels
  - [x] Test output handles render with labels
  - [x] Test add/remove handle interactions
  - [x] Test ControlSequencesSection renders in sidebar
  - [x] Test drag data format is correct

- [x] Task 7: Write integration tests for API lifecycle (AC: #5, #7)
  - [x] Test addControlSequenceNode calls API and creates node on success
  - [x] Test addControlSequenceNode handles API error gracefully
  - [x] Test node deletion calls DELETE API

## Dev Notes

### Learnings from Previous Story

**From Story 1b-1-g36-reheat-node-type-io-schema (Status: done)**

- **UI Component Ready**: `G36VavReheatNode` already created at `src/components/nodes/g36-vav-reheat-node.tsx`
- **Factory Pattern**: Uses `createControlSequenceNodeUI()` from `control-sequence-node-ui.tsx`
- **Node Registered**: Already in `nodeTypes` registry at `src/components/nodes/index.ts`
- **Handle Config**: `REHEAT_ALL_INPUTS`, `REHEAT_ALL_OUTPUTS`, `REHEAT_REQUIRED_INPUTS` available from domain
- **Generated Types**: `CreateInstanceRequest` now available from `@/domains/control-sequence`
- **597 tests passing**: Designer test suite healthy

[Source: stories/story-1b.1-g36-vav-reheat-node-type-schema.md#Dev-Agent-Record]

### Architecture Patterns

**Sidebar Section Pattern** (from `logic-nodes-section.tsx`):

```typescript
const handleDragStart = (e: React.DragEvent) => {
  const dragData = {
    type: "control-sequence-node", // New type
    nodeType: "g36-vav-reheat",
    label: "G36 VAV Reheat",
    metadata: {},
    draggedFrom: "control-sequences-section",
  };
  e.dataTransfer.setData("application/json", JSON.stringify(dragData));
};
```

**Flow Store Pattern** (from `addLogicNode`):

```typescript
addControlSequenceNode: async (
  nodeType: NodeTypeString,
  label: string,
  position: XYPosition,
  metadata?: Record<string, unknown>,
) => {
  const instanceId = uuidv4();
  // Call API first
  const response = await createInstance({ instance_id: instanceId });
  // Then add node to canvas
  // ...
};
```

**API Client Pattern** (from building-semantics domain):

```typescript
// src/domains/control-sequence/api/client.ts
import { client } from "./generated/client.gen";
import type { CreateInstanceRequest } from "./generated/types.gen";

export async function createInstance(request: CreateInstanceRequest) {
  return client.POST("/api/v1/g36/vav-reheat/instances", {
    body: request,
  });
}
```

### Testing Standards

- Use Jest + React Testing Library for component tests
- Mock API calls using MSW or jest.mock()
- Test user interactions (drag, drop, delete)
- Verify React Flow node structure

### Project Structure Notes

**Files to create:**

- `src/components/sidebar/control-sequences-section.tsx`
- `src/domains/control-sequence/api/client.ts`

**Files to modify:**

- `src/store/slices/flow-slice.ts` - add `addControlSequenceNode`
- `src/containers/canvas/use-node-creation.ts` - handle new drag type
- `src/domains/control-sequence/index.ts` - export API client

### References

- [Tech Spec Section 5.2 - Flow 1](../specs/control-sequence-api-tech-spec.md#52-designer-integration)
- [Epic Story 1B.2](../epics.md#story-1b2-g36-vav-reheat-block-ui-component)
- [Generated API Types](../../../../apps/designer/src/domains/control-sequence/api/generated/types.gen.ts)

## Dev Agent Record

### Context Reference

- docs/feature-development/g36-implementation/stories/1b-2-g36-reheat-block-ui-component.context.xml

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List

## Change Log

| Date       | Change                      |
| ---------- | --------------------------- |
| 2025-12-15 | Story drafted from epics.md |
| 2025-12-16 | Implementation completed    |

## Senior Developer Review (AI)

### Reviewer

Claude Opus 4.5 (AI Code Review)

### Date

2025-12-16

### Outcome

**APPROVED** ✓

### Summary

Story 1B.2 successfully implements the G36 VAV Reheat block UI component with full drag-and-drop integration, API lifecycle management, and comprehensive test coverage. All 8 acceptance criteria are met and all 7 tasks (25 subtasks) are completed.

### Key Findings

**Strengths:**

1. Clean separation of concerns - sidebar, flow store, and API client are well-isolated
2. Follows established patterns (LogicNodesSection, addLogicNode) for consistency
3. Comprehensive test coverage (657 tests passing)
4. Fire-and-forget deletion pattern prevents blocking UI on API failures
5. UUID generation client-side allows optimistic UI updates

**Implementation Quality:**

- `control-sequences-section.tsx` - Follows sidebar section pattern with proper drag data format
- `flow-slice.ts` - `addControlSequenceNode` handles API-first creation with error handling
- `use-node-creation.ts` - Clean switch case for `control-sequence-node` type
- `api/client.ts` - Thin wrapper around generated SDK functions

### Acceptance Criteria Coverage

| AC# | Criterion                                                         | Status  | Evidence                                                       |
| --- | ----------------------------------------------------------------- | ------- | -------------------------------------------------------------- |
| 1   | G36 VAV Reheat block renders on canvas with distinct visual style | ✅ PASS | `G36VavReheatNode` renders with teal accent, proper handles    |
| 2   | Input connectors visible and labeled                              | ✅ PASS | 13 inputs with labels (zoneTemperature, coolingSetpoint, etc.) |
| 3   | Output connectors visible and labeled                             | ✅ PASS | 3 outputs (damperPosition, valvePosition, airflowSetpoint)     |
| 4   | Block appears in palette under "Control Sequences"                | ✅ PASS | `ControlSequencesSection` in sidebar with G36 VAV Reheat item  |
| 5   | Drag-drop creates API instance                                    | ✅ PASS | `addControlSequenceNode` calls `POST /instances`               |
| 6   | Node stores instance_id in node data                              | ✅ PASS | `instanceId` stored in node metadata                           |
| 7   | Delete node calls DELETE API                                      | ✅ PASS | `onNodesChange` handles deletion with `deleteInstance()`       |
| 8   | Component tests pass                                              | ✅ PASS | 657 tests passing across 67 suites                             |

### Task Completion Validation

| Task                         | Status      | Files                                                                 |
| ---------------------------- | ----------- | --------------------------------------------------------------------- |
| Task 1: Sidebar section      | ✅ Complete | `control-sequences-section.tsx`, `control-sequences-section.spec.tsx` |
| Task 2: Flow store action    | ✅ Complete | `flow-slice.ts`                                                       |
| Task 3: Drag-drop handler    | ✅ Complete | `use-node-creation.ts`                                                |
| Task 4: Node deletion API    | ✅ Complete | `flow-slice.ts` (onNodesChange)                                       |
| Task 5: API client functions | ✅ Complete | `api/client.ts`, `api/client.spec.ts`                                 |
| Task 6: Component tests      | ✅ Complete | `g36-vav-reheat-node.spec.ts`, `control-sequences-section.spec.tsx`   |
| Task 7: Integration tests    | ✅ Complete | `flow-slice.spec.ts`                                                  |

### Recommendations for Future Stories

1. Consider adding loading state indicator during API instance creation
2. Toast notification pattern is good - consider using for successful creation too
3. Step execution flow (message buffer pattern) is well-designed for next phase
