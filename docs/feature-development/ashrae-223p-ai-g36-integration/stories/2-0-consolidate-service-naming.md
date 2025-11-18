# Story 2.0: Consolidate Service Naming and Interfaces

**Epic:** Epic 2 - BuildingMOTIF API Integration
**Phase:** Phase 0 - Foundation & Prerequisites
**Status:** ⚠️ **DO NOT IMPLEMENT** (Skipped - See deprecation notice)
**Created:** 2025-11-06
**Updated:** 2025-11-09 (Simplified: 4 → 3 services, mappings 6 → 2 methods, removed validation)
**Deprecated:** 2025-11-09 (Skipped in favor of direct Epic 1 → Phase 1 transition in Story 2.5)
**Complexity:** 2 (Small)
**Estimated Hours:** 2-3 hours

---

## ⚠️ DEPRECATION NOTICE

**This story is SKIPPED.**

**Reason:** Since breaking Epic 1 temporarily is acceptable (not in production), we're taking the simpler path:

- Skip the intermediate refactoring of Epic 1 services
- Story 2.5 will do the complete Epic 1 → Phase 1 transition in one step
- Less code churn, fewer bugs, faster completion

**What happens instead:**

- Stories 2.1-2.4 build FastAPI infrastructure (3 services, 5 endpoints)
- Story 2.5 does complete service swap (Epic 1 → generated TypeScript client)
- Story 2.5 includes all deletions from this story (AC #8 updated)

**Keep this file for reference:** Documents what Epic 1 services exist and why validation was removed.

---

## User Story

**As a** developer,
**I want** consistent service interface naming for all FastAPI-backed services,
**So that** the codebase has a clear pattern and OpenAPI spec generation is straightforward in Phase 1.

---

## Context

**Problem:** Epic 1 has inconsistent service naming patterns:

- ✅ Some services have interfaces: `IBuildingMOTIFService`, `ISpaceService`, `IValidationService`
- ❌ Some are direct API objects: `semanticMappingsApi`, `spaces223pApi`
- ❌ Only one references the tool: `IBuildingMOTIFService` (BuildingMOTIF is implementation detail)
- ❌ Duplication: Both `ISpaceService` and `spaces223pApi` exist

**Solution:** Consolidate all FastAPI-backed services to `I223P*Service` pattern:

- Domain prefix: `223P` (not tool name "BuildingMOTIF")
- Consistent interface pattern: `I*Service`
- Clear separation: FastAPI-backed vs Designer-only services

**Non-Goal:** `IAISuggestionService` stays unchanged (Designer-only, not FastAPI-backed)

---

## Acceptance Criteria

### 1. ✅ Rename 3 FastAPI-Backed Services to `I223P*Service`

**Template Service:**

- `IBuildingMOTIFService` → `I223PTemplatesService`
- File: `buildingmotif.ts` → `templates.service.interface.ts`
- Interface name updated
- Mock implementation updated: `buildingmotif.mock.service.ts` → `templates.mock.service.ts`

**Spaces Service:**

- `ISpaceService` → `I223PSpacesService`
- File: `space.service.interface.ts` → `spaces.service.interface.ts`
- Interface name updated
- Mock implementation updated: `space.mock.service.ts` → `spaces.mock.service.ts`

**Mappings Service (NEW):**

- Extract interface from `semanticMappingsApi`
- Create: `mappings.service.interface.ts` → `I223PMappingsService`
- Create mock implementation: `mappings.mock.service.ts`
- Create API implementation: `mappings.api.service.ts`
- 6 methods:
  - `listMappings(projectId: string): Promise<Map<string, SemanticEquipment>>`
  - `getMapping(projectId: string, compositeKey: string): Promise<SemanticEquipment | null>`
  - `createMapping(projectId: string, pointId: string, mapping: SemanticEquipment): Promise<SemanticEquipment>`
  - `updateMapping(projectId: string, pointId: string, mapping: SemanticEquipment): Promise<SemanticEquipment>`
  - `deleteMapping(projectId: string, compositeKey: string): Promise<void>`
  - `clearAllMappings(projectId: string): Promise<void>`

### 2. ✅ Remove Validation Service (Not Needed)

**`IValidationService` / `validation.mock.service.ts` - DELETE**

**Reason:** Hierarchical template structure prevents invalid combinations

- Equipment type selection → only valid devices shown (nested in template)
- Device type selection → only valid properties shown (nested in device)
- UI filtering makes invalid combinations impossible
- Any additional validation happens during 223P save in Phase 2 (BuildingMOTIF SDK)

**Files to delete:**

- `validation.service.interface.ts`
- `validation.mock.service.ts`

### 3. ✅ Keep `IAISuggestionService` Unchanged

- **NO changes** to `IAISuggestionService`
- Reason: Designer-only service (calls `/lib/ai`, not FastAPI)
- Not part of FastAPI integration
- Handled separately in Phase 3 (AI enhancement)

### 4. ✅ Remove Duplication - Delete `spaces223pApi`

- Delete: `/api/spaces.api.ts`
- Merge functionality into `I223PSpacesService` mock/API implementations
- Update imports to use `I223PSpacesService`

### 5. ✅ Update All Imports Across Codebase

**React Query Hooks (7 hooks need updates, 1 unchanged):**

- `useTemplatesQuery()` - update to use `I223PTemplatesService`
- `useMappingsQuery()` - update to use `I223PMappingsService`
- `useCreateMappingMutation()` - update to use `I223PMappingsService`
- `useUpdateMappingMutation()` - update to use `I223PMappingsService`
- `useDeleteMappingMutation()` - update to use `I223PMappingsService`
- `useSpacesQuery()` - update to use `I223PSpacesService`
- `useCreateSpaceMutation()` - update to use `I223PSpacesService`
- `useAISuggestionQuery()` - **NO CHANGE** (uses `IAISuggestionService`)

**UI Components:**

- Update imports in mapping popup modal
- Update imports in equipment type dropdown
- Update imports in left panel metadata badges
- Update imports in any other components using services

**Service Registrations:**

- Update dependency injection/service locator patterns
- Update mock service exports

### 6. ✅ Update All Tests

- Update test files for renamed services
- Update mock imports in tests
- Verify all tests pass
- No functional changes, only naming

### 7. ✅ Verify Epic 1 Functionality Preserved

- All Epic 1 UI flows work unchanged
- Mapping workflow end-to-end works
- Space management works
- Template selection works
- No breaking changes

---

## Verification Checklist

- [ ] All 3 FastAPI services renamed to `I223P*Service` pattern
- [ ] `I223PMappingsService` interface created with 6 methods
- [ ] Mock implementations exist for all 3 services
- [ ] Validation service deleted (not needed - hierarchical templates prevent invalid combinations)
- [ ] `spaces223pApi` deleted
- [ ] `IAISuggestionService` unchanged
- [ ] 7 React Query hooks updated (1 unchanged)
- [ ] All UI component imports updated
- [ ] All tests pass
- [ ] TypeScript compiles without errors
- [ ] Epic 1 UI functionality 100% preserved (manual testing)

---

## Implementation Guidance

### File Structure Changes

**Before:**

```
apps/designer/src/domains/building-semantics/
├── adapters/ashrae-223p/services/
│   ├── interfaces/
│   │   ├── buildingmotif.ts (IBuildingMOTIFService)
│   │   └── ai-suggestion.ts (IAISuggestionService)
│   ├── buildingmotif.mock.service.ts
│   ├── space.service.interface.ts (ISpaceService)
│   ├── space.mock.service.ts
│   ├── validation.service.interface.ts (IValidationService - NOT NEEDED)
│   └── validation.mock.service.ts (NOT NEEDED)
├── api/
│   ├── mappings.api.ts (semanticMappingsApi - NO INTERFACE)
│   └── spaces.api.ts (spaces223pApi - DUPLICATE)
```

**After:**

```
apps/designer/src/domains/building-semantics/
├── adapters/ashrae-223p/services/
│   ├── interfaces/
│   │   ├── templates.service.interface.ts (I223PTemplatesService)
│   │   ├── spaces.service.interface.ts (I223PSpacesService)
│   │   ├── mappings.service.interface.ts (I223PMappingsService - NEW)
│   │   └── ai-suggestion.ts (IAISuggestionService - UNCHANGED)
│   ├── templates.mock.service.ts
│   ├── spaces.mock.service.ts
│   ├── mappings.mock.service.ts (NEW)
│   └── mappings.api.service.ts (NEW - sessionStorage impl)
├── api/
│   └── (spaces.api.ts DELETED)
```

### Step-by-Step Implementation

**Step 1: Create `I223PMappingsService` Interface**

Create: `adapters/ashrae-223p/services/interfaces/mappings.service.interface.ts`

```typescript
import type { SemanticEquipment } from "../../../types/223p";

export interface I223PMappingsService {
  listMappings(projectId: string): Promise<Map<string, SemanticEquipment>>;

  getMapping(
    projectId: string,
    compositeKey: string,
  ): Promise<SemanticEquipment | null>;

  createMapping(
    projectId: string,
    pointId: string,
    mapping: SemanticEquipment,
  ): Promise<SemanticEquipment>;

  updateMapping(
    projectId: string,
    pointId: string,
    mapping: SemanticEquipment,
  ): Promise<SemanticEquipment>;

  deleteMapping(projectId: string, compositeKey: string): Promise<void>;

  clearAllMappings(projectId: string): Promise<void>;
}
```

**Step 2: Rename Templates Service**

Rename file: `buildingmotif.ts` → `templates.service.interface.ts`

```typescript
// Before
export interface IBuildingMOTIFService {
  getTemplates(): Promise<SystemType[]>;
  getDeviceTypes(): Promise<DeviceType[]>;
  getObservableProperties(): Promise<ObservableProperty[]>;
}

// After
export interface I223PTemplatesService {
  getTemplates(): Promise<SystemType[]>;
  getDeviceTypes(): Promise<DeviceType[]>;
  getObservableProperties(): Promise<ObservableProperty[]>;
}
```

**Step 3: Rename Spaces Service**

Update: `space.service.interface.ts` → `spaces.service.interface.ts`

```typescript
// Before
export interface ISpaceService {
  listSpaces(projectId: string): Promise<SpaceDTO[]>;
  createSpace(
    projectId: string,
    rdfsLabel: string,
    spaceType: string,
  ): Promise<SpaceDTO>;
  searchSpace(projectId: string, label: string): Promise<SpaceDTO | null>;
  addPointToSpace(
    projectId: string,
    spaceId: string,
    pointId: string,
  ): Promise<void>;
}

// After
export interface I223PSpacesService {
  listSpaces(projectId: string): Promise<SpaceDTO[]>;
  createSpace(
    projectId: string,
    rdfsLabel: string,
    spaceType: string,
  ): Promise<SpaceDTO>;
  searchSpace(projectId: string, label: string): Promise<SpaceDTO | null>;
  addPointToSpace(
    projectId: string,
    spaceId: string,
    pointId: string,
  ): Promise<void>;
}
```

**Step 4: Delete Validation Service (Not Needed)**

```bash
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/interfaces/validation.service.interface.ts
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/validation.mock.service.ts
```

**Reason:** Hierarchical template structure ensures only valid combinations are possible in UI.

**Step 5: Update React Query Hooks**

Example: `useTemplatesQuery()`

```typescript
// Before
import { buildingMOTIFService } from "../services";

export function useTemplatesQuery() {
  return useQuery({
    queryKey: ["templates"],
    queryFn: () => buildingMOTIFService.getTemplates(),
  });
}

// After
import { templates223PService } from "../services";

export function useTemplatesQuery() {
  return useQuery({
    queryKey: ["templates"],
    queryFn: () => templates223PService.getTemplates(),
  });
}
```

**Step 6: Delete `spaces223pApi`**

```bash
rm apps/designer/src/domains/building-semantics/api/spaces.api.ts
```

Update any imports to use `I223PSpacesService` instead.

**Step 7: Update Mock Service Implementations**

Rename and update class names:

- `BuildingMOTIFMockService` → `Templates223PMockService`
- `SpaceMockService` → `Spaces223PMockService`
- Create `Mappings223PMockService`

**Step 8: Create Mappings API Service**

Extract from `semanticMappingsApi` to `mappings.api.service.ts`:

```typescript
export class Mappings223PApiService implements I223PMappingsService {
  private readonly storageKey = (projectId: string) =>
    `223p-mappings:${projectId}`;

  async listMappings(
    projectId: string,
  ): Promise<Map<string, SemanticEquipment>> {
    // Move logic from semanticMappingsApi.listMappings
  }

  async getMapping(
    projectId: string,
    compositeKey: string,
  ): Promise<SemanticEquipment | null> {
    // Move logic from semanticMappingsApi.getMapping
  }

  // ... implement all 6 methods
}
```

**Step 9: Update Service Exports**

Update `services/index.ts` (or wherever services are exported):

```typescript
// Before
export { buildingMOTIFService } from "./buildingmotif.mock.service";
export { spaceService } from "./space.mock.service";
export { validationService } from "./validation.mock.service"; // DELETE

// After
export { templates223PService } from "./templates.mock.service";
export { spaces223PService } from "./spaces.mock.service";
export { mappings223PService } from "./mappings.api.service";
export { aiSuggestionService } from "./ai-suggestion.mock.service"; // UNCHANGED
```

---

## Technical Notes

### Why Domain Prefix (`223P`) Instead of Tool Name (`BuildingMOTIF`)?

**Domain:** ASHRAE 223P (semantic standard)
**Tool:** BuildingMOTIF (implementation detail)

**Benefits of `I223P*Service`:**

- Domain-focused naming
- BuildingMOTIF is internal implementation (could swap for another tool)
- Clear: "This service handles 223P domain logic"
- Future-proof: `/api/223p/*` paths match service naming

### Why Keep `IAISuggestionService` Unchanged?

**Designer-Only Service:**

- Lives in Designer app (`/lib/ai`)
- Calls Vercel AI SDK + Mem0 (Phase 3)
- **No FastAPI endpoint** needed
- Separate concern from 223P API integration

**FastAPI-Backed Services (3):**

- `I223PTemplatesService` → GET `/api/v1/223p/templates`
- `I223PSpacesService` → GET/POST `/api/v1/223p/spaces`
- `I223PMappingsService` → GET/POST `/api/v1/223p/mappings`

**Note:** Validation service removed - hierarchical templates prevent invalid combinations

### Testing Strategy

**Unit Tests:**

- Update imports to use new service names
- No logic changes, only naming
- All tests should pass unchanged

**Manual Testing:**

- Open Designer app
- Test mapping workflow end-to-end:
  1. Create new mapping (uses `I223PMappingsService`)
  2. Select equipment type (uses `I223PTemplatesService`)
  3. Select device and property (hierarchical filtering - no validation service needed)
  4. Assign to space (uses `I223PSpacesService`)
  5. AI suggestion (uses `IAISuggestionService` - unchanged)
- Verify all Epic 1 features work

---

## Prerequisites

**None** - This is the first story in Epic 2.

**But must preserve:** All Epic 1 functionality working.

---

## Dependencies

**Stories that depend on this:**

- Story 2.1: Create FastAPI app scaffolding (references clean interfaces)
- Story 2.2: Design OpenAPI specification (uses `I223P*Service` interfaces)
- All Phase 1 stories (interface-first development)

---

## Definition of Done

- [ ] All 3 FastAPI services renamed to `I223P*Service`
- [ ] `I223PMappingsService` interface created
- [ ] Mock implementations exist for all 3 services
- [ ] Validation service deleted (not needed)
- [ ] `spaces223pApi` deleted
- [ ] `IAISuggestionService` unchanged
- [ ] All imports updated (hooks, components, tests)
- [ ] All tests pass
- [ ] TypeScript compiles without errors
- [ ] Epic 1 UI functionality verified (manual testing)
- [ ] Code follows project conventions
- [ ] Files committed to git with message: "Epic 2 Story 2.0: Consolidate service naming to I223P\*Service pattern (3 services)"

---

## References

- **Tech Spec Review:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/tech-spec-review.md`
  - Section: "Tech Debt - Story 2.0 Specification" (lines 347-418)
- **Epic 2 Decisions:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/epic-2-decisions.md`
  - Decision 6: Domain-Scoped API Paths (lines 136-165)
- **Phase Breakdown:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/epic-2-phase-breakdown.md`
  - Phase 0: Story 2.0 (lines 32-102)
