# Story 1B.1: G36 VAV Reheat Node Type & Schema

Status: done

## Story

As a developer,
I want to define the G36 VAV Reheat node type in Designer,
So that the block structure matches the Control Sequence API interface.

## Acceptance Criteria

1. `g36-vav-reheat` node type added to Designer node registry
2. Node data uses generated types from `@/domains/control-sequence` (no manual schema duplication)
3. Input handles derived from `ReheatInputsRequest` generated type
4. Output handles derived from `ReheatOutputs` generated type
5. Node type registration tests pass

## Tasks / Subtasks

- [x] Task 1: Create G36 VAV Reheat node type definition (AC: #1, #2)

  - [x] Define node type using React Flow's `Node<T>` with generated types
  - [x] Node data extends generated types: `{ instance_id: string }`
  - [x] Import types directly from `@/domains/control-sequence`
  - [x] Add to control-sequence domain exports

- [x] Task 2: Define input handles from generated type (AC: #3)

  - [x] Use `ReheatInputsRequest` fields as input handle definitions
  - [x] Map field names to handle IDs (zoneTemperature, coolingSetpoint, etc.)
  - [x] Configure handle positions on left side of node
  - [x] Required vs optional inputs from generated type's optional fields

- [x] Task 3: Define output handles from generated type (AC: #4)

  - [x] Use `ReheatOutputs` fields as output handle definitions
  - [x] Map field names to handle IDs (damperPosition, valvePosition, airflowSetpoint, etc.)
  - [x] Configure handle positions on right side of node

- [x] Task 4: Register node type in Designer (AC: #1)

  - [x] Add `g36-vav-reheat` to node type registry
  - [x] Configure node category as "Control Sequences"
  - [x] Set default node dimensions
  - [x] Register React Flow node component mapping

- [x] Task 5: Write node type tests (AC: #5)

  - [x] Test node type registration exists
  - [x] Test node data type compatibility with generated types
  - [x] Test handle definitions match generated type fields

- [x] Task 6: Update Backend API to require instanceId from frontend (AC: #2)
  - [x] Modify POST `/api/v1/g36/vav-reheat/instances` to require `instanceId` in request body
  - [x] Make creation idempotent: if `instanceId` exists, return existing instance (200 OK)
  - [x] Update OpenAPI spec and regenerate TypeScript client

## Dev Notes

### Architecture Decision

**Use generated types directly.** No manual Zod schema duplication. The types from `types.gen.ts` are the source of truth, derived from the Python Pydantic DTOs via OpenAPI.

### Node Data Type

```typescript
import type { Node } from "@xyflow/react";
import type {
  ReheatInputsRequest,
  ReheatOutputs,
} from "@/domains/control-sequence";

// Node data only needs instance_id - parameters fetched from API
interface G36VavReheatNodeData {
  instance_id: string;
}

type G36VavReheatNode = Node<G36VavReheatNodeData, "g36-vav-reheat">;
```

### Handle Derivation Strategy

Derive handles at runtime or build time from the generated type keys:

```typescript
// Input handles from ReheatInputsRequest
const inputHandles = Object.keys({} as ReheatInputsRequest).map((key) => ({
  id: key,
  type: "target" as const,
  position: Position.Left,
}));

// Output handles from ReheatOutputs
const outputHandles = Object.keys({} as ReheatOutputs).map((key) => ({
  id: key,
  type: "source" as const,
  position: Position.Right,
}));
```

Or define explicitly for better control over ordering and labels.

### Generated Types Available

From Story 1.17, available in `@/domains/control-sequence`:

- `ReheatInputsRequest` - 17 input fields (9 required, 8 optional)
- `ReheatOutputs` - 14 output fields
- `ReheatParameters` - 50+ configurable parameters
- `StepRequest`, `StepResponse` - API request/response types

### Learnings from Previous Story

**From Story 1-17-designer-openapi-client (Status: done)**

- **Generated Types Ready**: All types available at `@/domains/control-sequence`
- **Domain Structure**: index.ts exports types, api/config.ts has client setup
- **No Schema Duplication**: Use generated types directly, don't recreate with Zod
- **542 tests passing**: Designer test suite healthy

[Source: stories/story-1.17-designer-openapi-client.md#Dev-Agent-Record]

### References

- [Tech Spec Section 5.2](../specs/control-sequence-api-tech-spec.md#52-designer-integration)
- [Epic Story 1B.1](../epics.md#story-1b1-g36-vav-reheat-node-type--schema)
- [Generated Types](../../../../apps/designer/src/domains/control-sequence/api/generated/types.gen.ts)

## Dev Agent Record

### Context Reference

- [1b-1-g36-reheat-node-type-io-schema.context.xml](./1b-1-g36-reheat-node-type-io-schema.context.xml)

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List

## Change Log

| Date       | Change                      |
| ---------- | --------------------------- |
| 2025-12-13 | Story drafted from epics.md |
