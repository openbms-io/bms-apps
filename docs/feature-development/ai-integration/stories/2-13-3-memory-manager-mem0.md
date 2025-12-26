# Story 2.13.3: Memory Manager with Mem0 Cloud Integration

Status: drafted

## Story

As a developer,
I want a memory manager that stores and retrieves organization-scoped mapping context from Mem0 Cloud,
so that the AI can learn from previous mapping decisions within an organization.

## Acceptance Criteria

1. ✅ `MemoryManager` class initializes Mem0 client with MEM0_API_KEY
2. ✅ `retrieveContext({ orgId, query, projectId })` searches org-scoped memories
3. ✅ `storeMapping({ orgId, mapping, projectId })` stores mapping decisions with org_id
4. ✅ Memory context includes pointPattern, controllerId, step, selectedId, wasOverridden
5. ✅ Memory retrieval returns relevantMemories array with text and score
6. ✅ Unit tests cover retrieval and storage with mocked Mem0 client

## Tasks / Subtasks

- [ ] Task 1: Create memory-manager.spec.ts (TDD) (AC: 1-6)

  - [ ] Test MemoryManager constructor initializes Mem0 client
  - [ ] Test retrieveContext calls client.search with org_id
  - [ ] Test retrieveContext returns MemoryContext structure
  - [ ] Test storeMapping calls client.add with org_id
  - [ ] Test storeMapping formats mapping as readable text
  - [ ] Test projectId metadata is included when provided

- [ ] Task 2: Implement memory-manager.ts (AC: 1-5)

  - [ ] Export MemoryManager class
  - [ ] Export MemoryContext interface
  - [ ] Export MappingRecord interface
  - [ ] Implement retrieveContext with object destructuring
  - [ ] Implement storeMapping with object destructuring
  - [ ] Export singleton memoryManager instance

- [ ] Task 3: Update lib/server-only/ai/index.ts exports
  - [ ] Export from memory-manager.ts

## Dev Notes

### File Locations

- Implementation: `apps/designer/src/lib/server-only/ai/memory-manager.ts`
- Tests: `apps/designer/src/lib/server-only/ai/memory-manager.spec.ts`

### Coding Conventions

Per project coding standards:

- Use object destructuring for function parameters
- Use camelCase for variables and functions
- Use PascalCase for interfaces

```typescript
// Correct - object destructuring
async function retrieveContext({
  orgId,
  query,
  projectId,
}: {
  orgId: string;
  query: string;
  projectId?: string;
}): Promise<MemoryContext>;

// Wrong - positional parameters
async function retrieveContext(
  orgId: string,
  query: string,
  projectId?: string,
);
```

### Memory Scoping

Memory is organization-scoped via `org_id` parameter to Mem0. This allows:

- Shared learning across all users in an organization
- Project-level filtering via metadata when needed
- Isolation between different organizations

### MappingRecord Structure

```typescript
interface MappingRecord {
  pointPattern: string; // e.g., "VAV-*_ZoneTemp"
  controllerId: string;
  step: "system" | "device" | "property";
  selectedId: string;
  wasOverridden: boolean; // True if user changed AI suggestion
}
```

### Project Structure Notes

- Server-only module in `lib/server-only/ai/` (not accessible from client)
- Singleton pattern for Mem0 client connection
- org_id scoping aligns with multi-tenant architecture

### References

- [Source: docs/feature-development/ai-integration/specs/vercel-ai-sdk-mem0-integration.md#5.2-Memory-Manager]
- [Source: docs/coding-standards.md#Type-System-Best-Practices]

## Dev Agent Record

### Context Reference

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List
