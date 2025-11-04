# Tech Debt Refactor: 223p → building-semantics Domain

**Status:** 📋 Planned
**Priority:** High
**Estimated Time:** 2-3 hours
**Breaking Changes:** No (internal refactor only)

---

## Overview

### Why This Refactor?

**Problem:** ASHRAE 223P implementation details are leaking across the entire application.

**Current Issues:**

- 27+ files import from `@/domains/223p`
- Core infrastructure types reference `223P` (e.g., `Equipment223PDTO`, `mapping223p`)
- App is tightly coupled to 223P standard
- Hard to add alternative semantic standards (Brick, Haystack)

**Architectural Goals:**

1. **Clean Domain Boundaries:** Hide 223P as implementation detail
2. **Future-Proof:** Easy to add Brick/Haystack adapters
3. **Better Naming:** Use semantic/equipment terminology, not "223P"
4. **Separation of Concerns:** App works with semantic concepts, not 223P specifics

### What Changes?

**Directory Rename:**

```
domains/223p/ → domains/building-semantics/
```

**Type Renames:**

```
Equipment223PDTO      → SemanticEquipment
mapping223p           → semanticMapping
mapping223pKey        → semanticMappingKey
Point223PBadge        → SemanticBadge
```

**Import Changes:**

```typescript
// Before
import { Equipment223PDTO } from "@/domains/223p/schemas";

// After
import { SemanticEquipment } from "@/domains/building-semantics";
```

---

## Type Mapping Reference

| Old Name                  | New Name                       | Location                 |
| ------------------------- | ------------------------------ | ------------------------ |
| `Equipment223PDTO`        | `SemanticEquipment`            | types                    |
| `mapping223p`             | `semanticMapping`              | infrastructure.ts field  |
| `mapping223pKey`          | `semanticMappingKey`           | node-data-types.ts field |
| `Point223PBadge`          | `SemanticBadge`                | component                |
| `@/domains/223p`          | `@/domains/building-semantics` | all imports              |
| `'223p'` (query key)      | `'building-semantics'`         | React Query              |
| `223p-mappings` (storage) | `semantic-mappings`            | sessionStorage           |

---

## Atomic Refactor Steps

Each step is atomic and leaves the app compilable. After each step, run verification commands.

### Step 1: Rename Directory (Preserve Git History)

**Action:**

```bash
cd apps/designer/src/domains
git mv 223p building-semantics
git status
```

**Why First:** Git tracks the rename, preserving file history. All imports still reference old path, so app still compiles.

**Verification:**

```bash
# Directory structure check
ls -la apps/designer/src/domains/building-semantics

# Git status should show rename
git status

# TypeScript should NOT compile yet (imports broken)
cd apps/designer
pnpm typecheck  # Expected: Errors (can't find @/domains/223p)
```

**Rollback:**

```bash
git mv domains/building-semantics domains/223p
```

---

### Step 2: Update All Import Paths

**Action:** Find and replace across entire codebase:

```
Find:    @/domains/223p
Replace: @/domains/building-semantics
```

**Files Affected (27 files):**

**Core Infrastructure (2):**

- `types/infrastructure.ts`
- `types/node-data-types.ts`

**State Management (2):**

- `store/slices/flow-slice.ts`
- `store/slices/tree-ui-slice.ts`

**Containers (2):**

- `containers/controllers-tree-container.tsx`
- `containers/canvas/flow-canvas-container.tsx`

**Components (2):**

- `components/nodes/bacnet-node-ui.tsx`
- `components/tree/tree-node.tsx`

**Domain Library (3):**

- `lib/data-nodes/base-bacnet-node.ts`
- `lib/ai/types.ts`
- `lib/workflow/serializer.ts`

**Hooks (1):**

- `hooks/use-canvas-orchestration.ts`

**Other (3):**

- `lib/workflow/config-schema.ts`
- `lib/data-nodes/factory.ts`
- `app/test-223p-modal/page.tsx`

**Domain Files (~12 files):**

- All files inside `domains/building-semantics/` that reference own domain

**Verification:**

```bash
cd apps/designer
pnpm typecheck  # Should PASS - all imports resolved
```

**Rollback:**

```bash
# Revert all import changes
git checkout .
```

**Commit:**

```bash
git add .
git commit -m "refactor: rename 223p domain to building-semantics"
```

---

### Step 3: Rename Public Type - Equipment223PDTO → SemanticEquipment

**Action:**

**3.1 Update Domain Type Export:**

File: `domains/building-semantics/schemas/dto.schemas.ts`

```typescript
// Add export alias at bottom of file
export type SemanticEquipment = Equipment223PDTO;
```

**3.2 Update Domain Index:**

File: `domains/building-semantics/index.ts`

```typescript
// Export new name
export type { SemanticEquipment } from "./schemas/dto.schemas";
// Keep old name temporarily for gradual migration
export type { Equipment223PDTO } from "./schemas/dto.schemas";
```

**3.3 Find and Replace Across Codebase:**

```
Find:    Equipment223PDTO
Replace: SemanticEquipment
```

**Files to Update (~15 files):**

- `types/infrastructure.ts`
- `store/slices/flow-slice.ts`
- `store/slices/tree-ui-slice.ts`
- `containers/controllers-tree-container.tsx`
- `lib/data-nodes/base-bacnet-node.ts`
- `lib/ai/types.ts`
- `app/test-223p-modal/page.tsx`
- And all domain internal files

**Example Changes:**

**types/infrastructure.ts:**

```typescript
// Before
import type { Equipment223PDTO } from "@/domains/building-semantics";

export interface TreeNode {
  mapping223p?: Equipment223PDTO;
}

// After
import type { SemanticEquipment } from "@/domains/building-semantics";

export interface TreeNode {
  mapping223p?: SemanticEquipment;
}
```

**Verification:**

```bash
cd apps/designer
pnpm typecheck  # Should PASS
```

**Commit:**

```bash
git add .
git commit -m "refactor: rename Equipment223PDTO to SemanticEquipment"
```

---

### Step 4: Rename Field - mapping223p → semanticMapping

**Action:** Find and replace field names:

```
Find:    mapping223p
Replace: semanticMapping
```

**Files to Update (~10 files):**

- `types/infrastructure.ts` (TreeNode interface)
- `store/slices/flow-slice.ts`
- `store/slices/tree-ui-slice.ts`
- `lib/workflow/serializer.ts`
- And domain internal files

**Example Changes:**

**types/infrastructure.ts:**

```typescript
// Before
export interface TreeNode {
  mapping223p?: SemanticEquipment;
}

// After
export interface TreeNode {
  semanticMapping?: SemanticEquipment;
}
```

**store/slices/flow-slice.ts:**

```typescript
// Before
const mapping = mappings.get(createCompositeKey(data));
if (mapping) {
  data.mapping223p = mapping;
}

// After
const mapping = mappings.get(createCompositeKey(data));
if (mapping) {
  data.semanticMapping = mapping;
}
```

**Verification:**

```bash
cd apps/designer
pnpm typecheck  # Should PASS
```

**Commit:**

```bash
git add .
git commit -m "refactor: rename mapping223p field to semanticMapping"
```

---

### Step 5: Rename Field - mapping223pKey → semanticMappingKey

**Action:** Find and replace field name:

```
Find:    mapping223pKey
Replace: semanticMappingKey
```

**Files to Update (~3 files):**

- `types/node-data-types.ts` (BacnetNodeData interface)
- Files that reference this field

**Example Changes:**

**types/node-data-types.ts:**

```typescript
// Before
export interface BacnetNodeData extends BacnetInputOutput, BaseNodeData {
  category: NodeCategory.BACNET;
  mapping223pKey?: string;
}

// After
export interface BacnetNodeData extends BacnetInputOutput, BaseNodeData {
  category: NodeCategory.BACNET;
  semanticMappingKey?: string;
}
```

**Verification:**

```bash
cd apps/designer
pnpm typecheck  # Should PASS
```

**Commit:**

```bash
git add .
git commit -m "refactor: rename mapping223pKey to semanticMappingKey"
```

---

### Step 6: Rename Component - Point223PBadge → SemanticBadge

**Action:**

**6.1 Rename Component File:**

```bash
cd apps/designer/src/domains/building-semantics/components
git mv point-223p-badge.tsx semantic-badge.tsx
```

**6.2 Update Component Name Inside File:**

File: `domains/building-semantics/components/semantic-badge.tsx`

```typescript
// Before
export function Point223PBadge({ ... }) {

// After
export function SemanticBadge({ ... }) {
```

**6.3 Update Component Export:**

File: `domains/building-semantics/components/index.ts`

```typescript
// Before
export { Point223PBadge } from "./point-223p-badge";

// After
export { SemanticBadge } from "./semantic-badge";
```

**6.4 Update All Imports:**

File: `components/tree/tree-node.tsx`

```typescript
// Before
import { Point223PBadge } from "@/domains/building-semantics/components/point-223p-badge";

// After
import { SemanticBadge } from "@/domains/building-semantics";
```

**6.5 Update All Usage:**

```typescript
// Before
<Point223PBadge mapping={mapping} />

// After
<SemanticBadge mapping={mapping} />
```

**Verification:**

```bash
cd apps/designer
pnpm typecheck  # Should PASS
pnpm run dev     # Should render without errors
```

**Commit:**

```bash
git add .
git commit -m "refactor: rename Point223PBadge to SemanticBadge"
```

---

### Step 7: Update Storage and Query Keys

**Action:** Update runtime string keys (not TypeScript types).

**7.1 Update React Query Keys:**

Find files using `'223p'` query key:

```bash
grep -r "'223p'" domains/building-semantics/api/queries/
```

File: `domains/building-semantics/api/queries/query-keys.ts`

```typescript
// Before
export const mappingKeys = {
  all: ["223p", "mappings"] as const,
  // ...
};

// After
export const mappingKeys = {
  all: ["building-semantics", "mappings"] as const,
  // ...
};
```

**7.2 Update sessionStorage Keys:**

Find files using `'223p-mappings'` storage key:

```bash
grep -r "223p-mappings" domains/building-semantics/
```

Example locations:

- `domains/building-semantics/api/mappings.api.ts`
- Any sessionStorage.setItem/getItem calls

```typescript
// Before
const STORAGE_KEY = "223p-mappings";

// After
const STORAGE_KEY = "semantic-mappings";
```

**Verification:**

```bash
cd apps/designer
pnpm typecheck      # Should PASS
pnpm run dev        # Should run
# Open DevTools → Application → Session Storage
# Verify new key "semantic-mappings" is used
```

**Note:** Old `223p-mappings` data will be orphaned. Acceptable since no backward compatibility needed.

**Commit:**

```bash
git add .
git commit -m "refactor: update storage and query keys to use semantic naming"
```

---

### Step 8: Cleanup and Organize Internal Structure (Optional)

**Action:** Move 223P-specific implementation to adapter subdirectory.

**8.1 Create Adapter Structure:**

```bash
cd apps/designer/src/domains/building-semantics
mkdir -p adapters/ashrae-223p
```

**8.2 Move 223P-Specific Code:**

```bash
# Move schemas (contains 223P-specific enums)
git mv schemas adapters/ashrae-223p/

# Move services (BuildingMOTIF, AI suggestion)
git mv api/services adapters/ashrae-223p/services

# Move mocks
git mv mocks adapters/ashrae-223p/mocks
```

**8.3 Update Internal Imports:**

Files that imported from `./schemas` now import from `./adapters/ashrae-223p/schemas`.

**8.4 Update Domain Index (Clean Public API):**

File: `domains/building-semantics/index.ts`

```typescript
// PUBLIC API - What other modules can import

// Types
export type { SemanticEquipment, SemanticMapping } from "./types";

// Hooks
export { useMappingsQuery } from "./api/queries/use-mappings-query";
export { useCreateEquipmentMapping } from "./view-models/use-create-equipment-mapping";
export { useEditMapping } from "./hooks/use-edit-mapping";

// Components
export { MappingPopupModal } from "./components/mapping-popup-modal";
export { SemanticBadge } from "./components/semantic-badge";

// Utils (only if needed externally)
export { createCompositeKey } from "./utils/bacnet-keys";

// DO NOT export:
// - Internal schemas (adapters/ashrae-223p/schemas)
// - Internal services (adapters/ashrae-223p/services)
// - Implementation details
```

**Verification:**

```bash
cd apps/designer
pnpm typecheck  # Should PASS

# Verify no external imports from adapters/
grep -r "from '@/domains/building-semantics/adapters" src/ | grep -v "domains/building-semantics"
# Should return nothing (no external dependencies on adapters/)
```

**Commit:**

```bash
git add .
git commit -m "refactor: organize 223P implementation into adapter subdirectory"
```

---

### Step 9: Rename Test Page (Optional)

**Action:**

```bash
cd apps/designer/src/app
git mv test-223p-modal test-semantic-modal
```

Update route in Next.js navigation if needed.

**Verification:**

```bash
cd apps/designer
pnpm run dev
# Visit http://localhost:3000/test-semantic-modal
```

**Commit:**

```bash
git add .
git commit -m "refactor: rename test-223p-modal to test-semantic-modal"
```

---

## Final Verification Checklist

After completing all steps:

### TypeScript Compilation

```bash
cd apps/designer
pnpm typecheck
```

**Expected:** ✅ No errors

### Code Search Verification

```bash
# Search for old naming (should find nothing in code, only docs/comments)
cd apps/designer/src

# Should find NOTHING (or only comments)
grep -r "223p" . --include="*.ts" --include="*.tsx" | grep -v "ASHRAE 223P" | grep -v "//"

# Should find NOTHING
grep -r "Equipment223PDTO" .

# Should find NOTHING
grep -r "mapping223pKey" .

# Should find NOTHING
grep -r "Point223PBadge" .

# Should find NOTHING
grep -r "@/domains/223p" .
```

### Runtime Testing

```bash
pnpm run dev
```

**Manual Tests:**

1. ✅ Drag BACnet point to canvas → semantic modal opens
2. ✅ Confirm mapping → badge appears in tree
3. ✅ Badge shows equipment info on hover
4. ✅ Refresh page → mappings persist (sessionStorage)
5. ✅ Edit mapping from tree → modal opens with existing values
6. ✅ DevTools → Session Storage → `semantic-mappings` key exists

### Test Suite (if exists)

```bash
pnpm test
```

**Expected:** All tests pass

---

## Files Affected Summary

### Core Infrastructure (2 files)

- `types/infrastructure.ts` - TreeNode.semanticMapping
- `types/node-data-types.ts` - BacnetNodeData.semanticMappingKey

### State Management (2 files)

- `store/slices/flow-slice.ts`
- `store/slices/tree-ui-slice.ts`

### Containers (2 files)

- `containers/controllers-tree-container.tsx`
- `containers/canvas/flow-canvas-container.tsx`

### Components (2 files)

- `components/nodes/bacnet-node-ui.tsx`
- `components/tree/tree-node.tsx`

### Domain Library (5 files)

- `lib/data-nodes/base-bacnet-node.ts`
- `lib/ai/types.ts`
- `lib/workflow/serializer.ts`
- `lib/workflow/config-schema.ts`
- `lib/data-nodes/factory.ts`

### Hooks (1 file)

- `hooks/use-canvas-orchestration.ts`

### Test Pages (1 file)

- `app/test-223p-modal/page.tsx`

### Domain Files (~40 files)

- Entire `domains/building-semantics/` directory

**Total:** ~57 files

---

## Rollback Strategy

If at any step something breaks:

### Per-Step Rollback

```bash
# Undo uncommitted changes
git checkout .

# Or undo last commit
git reset --soft HEAD~1
```

### Full Rollback (All Steps)

```bash
# Reset to before refactor started
git log --oneline | head -20  # Find commit before refactor
git reset --hard <commit-hash>
```

### Partial Rollback (Keep Some Steps)

```bash
# Interactive rebase to pick/drop specific commits
git rebase -i HEAD~9  # 9 = number of refactor commits
```

---

## Success Criteria

✅ All TypeScript compilation passes
✅ No references to old naming in code
✅ App runs without runtime errors
✅ Semantic mapping workflow still works
✅ Storage keys use new naming
✅ Git history preserved (git mv used)
✅ Clean domain boundaries (no adapter imports outside domain)
✅ Public API clearly defined in domain index.ts

---

## Next Steps After Refactor

1. **Update Documentation:**

   - Update README references from 223P to building-semantics
   - Update architecture diagrams
   - Update developer onboarding docs

2. **Add Future Adapters:**

   - `adapters/brick/` for Brick schema
   - `adapters/haystack/` for Haystack tagging
   - Feature flag to switch between adapters

3. **Add Tests:**
   - Unit tests for domain public API
   - Integration tests for adapter implementations
   - E2E tests for semantic workflow

---

## Notes

- **No Backward Compatibility Needed:** We're in feature development
- **User-Facing Text:** Can still mention "ASHRAE 223P" in UI/docs
- **Git History:** Using `git mv` preserves file history
- **Atomic Commits:** Each step is a separate, revertible commit
- **Compile After Each Step:** TypeScript catches all breaking changes immediately

---

**Last Updated:** 2025-11-04
**Author:** Amol
**Status:** 📋 Ready to Execute
