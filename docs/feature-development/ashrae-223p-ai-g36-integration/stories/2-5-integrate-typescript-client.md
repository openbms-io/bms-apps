# Story 2.5: Integrate TypeScript Client with Designer App

**Epic:** Epic 2 - BuildingMOTIF API Integration
**Phase:** Phase 1 - Interface-First Development & Validation
**Status:** ready-for-dev
**Context:** [2-5-integrate-typescript-client.context.xml](./2-5-integrate-typescript-client.context.xml)
**Created:** 2025-11-06
**Updated:** 2025-11-09 (Simplified: 9 → 5 hooks, bulk save, hierarchical templates)
**Complexity:** 3 (Medium)
**Estimated Hours:** 4-6 hours

---

## User Story

**As a** developer,
**I want** React Query hooks updated to use the simplified TypeScript client,
**So that** the Designer app calls FastAPI endpoints with hierarchical templates and bulk operations.

---

## Context

**Problem:** Epic 1 uses sessionStorage for all semantic data. Phase 1 needs to validate OpenAPI contract with real API calls.

**Solution:** Update to 5 React Query hooks using simplified client:

- Single hierarchical templates query (systems → devices → properties nested)
- Bulk mappings save/replace (no individual CRUD)
- Space instance management (create, list)
- Keep hook interfaces compatible where possible
- Remove sessionStorage dependencies

**Phase 1 Scope:**

- **Goal:** Validate OpenAPI contract works end-to-end
- **Data:** Static mock data (replaced in Phase 2 with BuildingMOTIF SDK)
- **No Persistence:** Mock endpoints return static data (ignore saves)
- **UI Testing:** Verify dropdowns, selections, and bulk save workflow

**Migration Strategy:**

- Replace 9 hooks with 5 simplified hooks
- Remove individual mapping CRUD (use bulk save)
- Handle hierarchical template structure
- Test contract validation workflow

**Non-Goal:** `useAISuggestionQuery` unchanged (Designer-only, no FastAPI)

---

## Acceptance Criteria

### 1. ✅ Update `useTemplatesQuery` Hook (Hierarchical)

**File:** `apps/designer/src/domains/223p/api/queries/use-templates-query.ts`

**Before (Epic 1 - multiple calls):**

```typescript
// Separate queries for systems, devices, properties
export function useTemplatesQuery() {
  return useQuery({
    queryKey: ["templates"],
    queryFn: () => buildingMotifMockService.getTemplates(),
  });
}
```

**After (Phase 1 - single hierarchical call):**

```typescript
import { useQuery } from "@tanstack/react-query";
import { TemplatesService, type TemplatesResponse } from "../generated";

export function useTemplatesQuery() {
  return useQuery({
    queryKey: ["templates"],
    queryFn: async () => {
      const response = await TemplatesService.getTemplates();
      return response;
    },
    staleTime: 5 * 60 * 1000, // 5 minutes (templates rarely change)
  });
}

// Response structure (hierarchical):
// {
//   systems: [
//     {
//       id: "urn:223p:VAVReheatTerminalUnit",
//       label: "VAV with Reheat",
//       devices: [
//         {
//           id: "urn:223p:Damper",
//           label: "Damper",
//           properties: [
//             {
//               id: "urn:223p:DamperPosition",
//               label: "Damper Position",
//               propertyType: "quantifiable"  // camelCase from Pydantic alias
//             }
//           ]
//         }
//       ]
//     }
//   ],
//   spaceTypes: [...]  // camelCase from Pydantic alias
// }
```

**Component Usage:**

```typescript
function MappingPopup() {
  const { data: templates } = useTemplatesQuery();

  // Filter devices for selected system
  const selectedSystem = templates?.systems.find(
    (s) => s.id === equipmentTypeId,
  );
  const availableDevices = selectedSystem?.devices ?? [];

  // Filter properties for selected device
  const selectedDevice = selectedSystem?.devices.find(
    (d) => d.id === deviceTypeId,
  );
  const availableProperties = selectedDevice?.properties ?? [];
}
```

**Verification:**

- Equipment type dropdown displays ASHRAE 223P systems (camelCase fields)
- Device dropdown filters based on selected system
- Property dropdown filters based on selected device
- Single API call loads all template data
- No TypeScript errors

### 2. ✅ Update `useMappingsQuery` Hook (Bulk Pattern)

**File:** `apps/designer/src/domains/223p/api/queries/use-mappings-query.ts`

**Before (Epic 1 - sessionStorage):**

```typescript
export function useMappingsQuery(projectId: string) {
  return useQuery({
    queryKey: ["mappings", projectId],
    queryFn: () => semanticMappingsApi.listMappings(projectId),
  });
}
```

**After (Phase 1 - FastAPI):**

```typescript
import { useQuery } from "@tanstack/react-query";
import { MappingsService, type MappingsResponse } from "../generated";

export function useMappingsQuery(projectId: string) {
  return useQuery({
    queryKey: ["mappings", projectId],
    queryFn: async () => {
      const response = await MappingsService.getMappings({ projectId });
      return response;
    },
    enabled: !!projectId,
  });
}

// Response structure:
// {
//   projectId: "project-123",
//   mappings: [
//     {
//       pointId: "BACnet:Device1:AI-1",
//       equipmentTypeId: "urn:223p:VAVReheatTerminalUnit",  // camelCase
//       deviceTypeId: "urn:223p:Damper",                    // camelCase
//       propertyId: "urn:223p:DamperPosition",              // camelCase
//       spaceId: "urn:bms:Space:office-101"                 // camelCase
//     }
//   ]
// }
```

**Verification:**

- Mappings table displays existing mappings (mock data)
- Badge counts show correct numbers
- camelCase field names work correctly
- Query key includes projectId for cache invalidation

### 3. ✅ Create `useSaveMappingsMutation` Hook (Bulk Save)

**File:** `apps/designer/src/domains/223p/api/mutations/use-save-mappings-mutation.ts`

**New implementation (replaces create/update/delete mutations):**

```typescript
import { useMutation, useQueryClient } from "@tanstack/react-query";
import {
  MappingsService,
  type SaveMappingsRequest,
  type MappingsResponse,
} from "../generated";

interface SaveMappingsParams {
  projectId: string;
  mappings: Array<{
    pointId: string;
    equipmentTypeId: string;
    deviceTypeId: string;
    propertyId: string;
    spaceId?: string;
  }>;
}

export function useSaveMappingsMutation() {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: async ({ projectId, mappings }: SaveMappingsParams) => {
      const request: SaveMappingsRequest = {
        projectId, // camelCase
        mappings, // camelCase
      };
      return await MappingsService.saveMappings({ requestBody: request });
    },
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({ queryKey: ["mappings", projectId] });
    },
  });
}
```

**Component Usage Pattern:**

```typescript
function MappingTable() {
  const { data: mappingsData } = useMappingsQuery(projectId);
  const saveMappings = useSaveMappingsMutation();

  // Add new mapping to local state
  const handleAddMapping = (newMapping) => {
    const updatedMappings = [...(mappingsData?.mappings ?? []), newMapping];
    saveMappings.mutate({ projectId, mappings: updatedMappings });
  };

  // Remove mapping from local state
  const handleDeleteMapping = (pointId) => {
    const updatedMappings =
      mappingsData?.mappings.filter((m) => m.pointId !== pointId) ?? [];
    saveMappings.mutate({ projectId, mappings: updatedMappings });
  };

  // Update mapping in local state
  const handleUpdateMapping = (pointId, updates) => {
    const updatedMappings =
      mappingsData?.mappings.map((m) =>
        m.pointId === pointId ? { ...m, ...updates } : m,
      ) ?? [];
    saveMappings.mutate({ projectId, mappings: updatedMappings });
  };
}
```

**Verification:**

- Bulk save mutation accepts array of mappings
- Optimistic UI updates work correctly
- Cache invalidation triggers refetch
- camelCase fields serialize correctly

**Phase 1 Limitation:**

- Mock endpoint ignores request and returns static data
- Validates contract, but doesn't persist changes

### 4. ✅ Update `useSpacesQuery` Hook

**File:** `apps/designer/src/domains/223p/api/queries/use-spaces-query.ts`

**Before (Epic 1 - sessionStorage):**

```typescript
export function useSpacesQuery(projectId: string) {
  return useQuery({
    queryKey: ["spaces", projectId],
    queryFn: () => spaceService.listSpaces(projectId),
  });
}
```

**After (Phase 1 - FastAPI):**

```typescript
import { useQuery } from "@tanstack/react-query";
import { SpacesService, type SpaceInstance } from "../generated";

export function useSpacesQuery(projectId: string) {
  return useQuery({
    queryKey: ["spaces", projectId],
    queryFn: async () => {
      return await SpacesService.listSpaces({ projectId });
    },
    enabled: !!projectId,
  });
}

// Response structure:
// [
//   {
//     id: "urn:bms:Space:office-101",
//     label: "Office 101",
//     spaceTypeId: "urn:223p:Office"  // camelCase from Pydantic alias
//   }
// ]
```

**Verification:**

- Space dropdown shows created spaces (mock data)
- camelCase fields work correctly

**Phase 1 Limitation:**

- Returns static mock data (Office 101, Conference Room A)

### 5. ✅ Update `useCreateSpaceMutation` Hook

**File:** `apps/designer/src/domains/223p/api/mutations/use-create-space-mutation.ts`

**Before (Epic 1 - sessionStorage):**

```typescript
export function useCreateSpaceMutation() {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: ({ projectId, label, spaceType }) =>
      spaceService.createSpace(projectId, label, spaceType),
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({ queryKey: ["spaces", projectId] });
    },
  });
}
```

**After (Phase 1 - FastAPI):**

```typescript
import { useMutation, useQueryClient } from "@tanstack/react-query";
import {
  SpacesService,
  type CreateSpaceRequest,
  type SpaceInstance,
} from "../generated";

interface CreateSpaceParams {
  projectId: string;
  label: string;
  spaceTypeId: string; // URN from template space types
}

export function useCreateSpaceMutation() {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: async ({
      projectId,
      label,
      spaceTypeId,
    }: CreateSpaceParams) => {
      const request: CreateSpaceRequest = {
        projectId, // camelCase
        label, // camelCase
        spaceTypeId, // camelCase
      };
      return await SpacesService.createSpace({ requestBody: request });
    },
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({ queryKey: ["spaces", projectId] });
    },
  });
}
```

**Component Usage:**

```typescript
function CreateSpaceButton() {
  const { data: templates } = useTemplatesQuery();
  const createSpace = useCreateSpaceMutation();

  const handleCreateSpace = () => {
    createSpace.mutate({
      projectId: "project-123",
      label: "Office 102",
      spaceTypeId: "urn:223p:Office", // From templates.spaceTypes
    });
  };
}
```

**Verification:**

- Create space button sends correct request
- Space types come from templates query
- camelCase fields serialize correctly

**Phase 1 Limitation:**

- Mock endpoint ignores request and returns static data
- Validates contract, not actual space creation

### 6. ✅ Keep `useAISuggestionQuery` Unchanged

**File:** `apps/designer/src/domains/223p/api/queries/use-ai-suggestion-query.ts`

**No changes needed:**

- Designer-only service
- Calls `/lib/ai` route (not FastAPI)
- Mem0 + Vercel AI SDK integration
- Phase 3 enhancement

### 7. ✅ Remove Obsolete Hooks

**Delete these files:**

- `use-device-types-query.ts` (nested in hierarchical templates)
- `use-observable-properties-query.ts` (nested in hierarchical templates)
- `use-create-mapping-mutation.ts` (replaced by bulk save)
- `use-update-mapping-mutation.ts` (replaced by bulk save)
- `use-delete-mapping-mutation.ts` (replaced by bulk save)

**Reason:** Simplified to 5 hooks matching 5 endpoints

### 8. ✅ Remove Old Epic 1 Service Files

**Delete Service Implementations:**

- `buildingmotif.mock.service.ts` (replaced by FastAPI)
- `space.mock.service.ts` (replaced by FastAPI)
- `mappings.api.service.ts` (sessionStorage, replaced by FastAPI)
- `validation.mock.service.ts` (replaced by hierarchical template filtering)

**Delete Service Interfaces:**

- `interfaces/buildingmotif.ts` (IBuildingMOTIFService)
- `interfaces/space.service.interface.ts` (ISpaceService)
- `interfaces/validation.service.interface.ts` (IValidationService)
- `interfaces/mappings.service.interface.ts` (if exists from Epic 1)

**Keep (Designer-only services - not FastAPI-backed):**

- `ai-suggestion.mock.service.ts`
- `interfaces/ai-suggestion.ts` (IAISuggestionService)

**Why Remove Validation Service?**

Hierarchical template structure makes validation service unnecessary:

- Equipment type selection → only valid devices shown (nested in template)
- Device type selection → only valid properties shown (nested in device)
- UI filtering prevents invalid combinations at selection time
- Any additional 223P validation happens during save in Phase 2 (BuildingMOTIF SDK)

### 9. ✅ API Configuration for Generated Client

**Create:** `apps/designer/src/domains/223p/api/config.ts`

```typescript
import { OpenAPI } from "./generated";

// Configure generated client base URL
OpenAPI.BASE =
  process.env.NEXT_PUBLIC_SEMANTICS_API_URL || "http://localhost:8000";
OpenAPI.TIMEOUT = 30000; // 30 seconds

// Optional: Add request interceptor for authentication (future Phase 2)
OpenAPI.interceptors = {
  request: async (config) => {
    // Add auth headers here if needed in Phase 2
    return config;
  },
};
```

**Import in:** `apps/designer/src/app/layout.tsx`

```typescript
import "@/domains/223p/api/config"; // Initialize API client
```

**Add to `.env.local`:**

```bash
NEXT_PUBLIC_SEMANTICS_API_URL=http://localhost:8000
```

### 10. ✅ Error Handling and Loading States

**Update hooks with error handling:**

**Example: `useTemplatesQuery` with retry and error handling**

```typescript
export function useTemplatesQuery() {
  return useQuery({
    queryKey: ["templates"],
    queryFn: async () => {
      try {
        return await TemplatesService.getTemplates();
      } catch (error) {
        console.error("Failed to fetch templates:", error);
        throw error; // React Query will handle retry/error state
      }
    },
    retry: 3, // Retry failed requests 3 times
    staleTime: 5 * 60 * 1000, // 5 minutes (templates rarely change)
  });
}
```

**Components handle states:**

```typescript
function MappingPopup() {
  const { data: templates, isLoading, isError, error } = useTemplatesQuery()

  if (isLoading) return <Spinner />
  if (isError) return <ErrorMessage error={error} />

  return <MappingForm templates={templates} />
}
```

### 11. ✅ End-to-End Testing Workflow

**Manual test:**

1. Start all services: `./scripts/start-dev.sh`
2. Open Designer: `http://localhost:3000`
3. Test mapping workflow:
   - Select equipment type from hierarchical templates
   - Devices filter based on selected equipment type
   - Properties filter based on selected device type
   - Select space from space instances
   - Click save (bulk save mutation)
   - Verify mapping displays in table (mock data)
   - Reload page → mappings still show (from mock API, not persisted)

**Expected:** All operations call FastAPI endpoints, UI workflow validates contract

**Phase 1 Reality:**

- Mock endpoints return static data
- Saves don't persist (validates contract only)
- Phase 2 will replace with BuildingMOTIF SDK for real persistence

---

## Phase 1 Limitations

### Static Mock Data Behavior

**Templates Endpoint:**

- Returns 3 hardcoded ASHRAE 223P systems with nested devices/properties
- Same data every request
- No filtering or customization

**Mappings Endpoint:**

- GET returns 2 hardcoded mappings (ignores projectId)
- POST accepts request but returns same static mappings
- No persistence across server restarts
- Validates contract, not functionality

**Spaces Endpoint:**

- GET returns 2 hardcoded spaces (Office 101, Conference Room A)
- POST accepts request but returns same static spaces
- No persistence

### Why This Is Acceptable for Phase 1

**Goal:** Validate OpenAPI contract works end-to-end

- ✅ Verify TypeScript client generates correctly
- ✅ Verify request/response serialization (camelCase aliases)
- ✅ Verify hierarchical template structure works
- ✅ Verify bulk save pattern works
- ✅ Verify UI workflow completes without errors

**Not Goal:** Functional persistence (Phase 2 with BuildingMOTIF SDK)

### What Phase 2 Will Add

- Real BuildingMOTIF SDK integration
- Template loading from ASHRAE 223P ontology
- Persistent storage for mappings and spaces
- Graph database for semantic relationships
- Template inference and validation
- Building model export (Brick, 223P, Haystack)

---

## Verification Checklist

- [ ] 5 hooks implemented using generated TypeScript client
- [ ] `useAISuggestionQuery` unchanged (Designer-only)
- [ ] 4 obsolete hooks removed (device types, observable properties, individual mapping CRUD)
- [ ] Old Epic 1 service implementations removed (buildingmotif, space, mappings, validation)
- [ ] Old Epic 1 service interfaces removed (4 interfaces deleted, ai-suggestion kept)
- [ ] API configuration file created
- [ ] API client initialized in app entry point
- [ ] Error handling implemented for all hooks
- [ ] TypeScript compiles without errors
- [ ] Designer app starts successfully
- [ ] Equipment type dropdown loads hierarchical templates
- [ ] Device dropdown filters based on selected equipment type
- [ ] Property dropdown filters based on selected device
- [ ] Bulk save mutation accepts array of mappings
- [ ] Create space mutation works
- [ ] Spaces dropdown loads from FastAPI
- [ ] camelCase fields serialize correctly (Pydantic aliases)
- [ ] URN identifiers use `id` field name (not `urn`)
- [ ] No console errors during workflow
- [ ] Network tab shows API calls to `localhost:8000`
- [ ] Phase 1 limitation documented (static mock data)

---

## Implementation Guidance

### Step 1: Configure API Client

**Create `src/domains/223p/api/config.ts`:**

```typescript
import { OpenAPI } from "./generated";

OpenAPI.BASE =
  process.env.NEXT_PUBLIC_SEMANTICS_API_URL || "http://localhost:8000";
OpenAPI.TIMEOUT = 30000;
```

**Import in `src/app/layout.tsx`:**

```typescript
import "@/domains/223p/api/config";
```

**Add to `.env.local`:**

```bash
NEXT_PUBLIC_SEMANTICS_API_URL=http://localhost:8000
```

### Step 2: Update Templates Hook (Hierarchical)

**Update `useTemplatesQuery.ts`:**

```typescript
import { useQuery } from "@tanstack/react-query";
import { TemplatesService } from "../generated";

export function useTemplatesQuery() {
  return useQuery({
    queryKey: ["templates"],
    queryFn: () => TemplatesService.getTemplates(),
    staleTime: 5 * 60 * 1000, // 5 minutes
  });
}
```

**Delete obsolete hooks:**

- `useDeviceTypesQuery.ts`
- `useObservablePropertiesQuery.ts`

### Step 3: Update Components for Hierarchical Templates

**Before (separate queries):**

```typescript
function MappingPopup() {
  const { data: systems } = useTemplatesQuery();
  const { data: devices } = useDeviceTypesQuery();
  const { data: properties } = useObservablePropertiesQuery();
}
```

**After (nested filtering):**

```typescript
function MappingPopup() {
  const { data: templates } = useTemplatesQuery();

  const selectedSystem = templates?.systems.find(
    (s) => s.id === equipmentTypeId,
  );
  const devices = selectedSystem?.devices ?? [];

  const selectedDevice = devices.find((d) => d.id === deviceTypeId);
  const properties = selectedDevice?.properties ?? [];
}
```

### Step 4: Replace Individual CRUD with Bulk Save

**Delete:**

- `useCreateMappingMutation.ts`
- `useUpdateMappingMutation.ts`
- `useDeleteMappingMutation.ts`

**Create `useSaveMappingsMutation.ts`:**

```typescript
import { useMutation, useQueryClient } from "@tanstack/react-query";
import { MappingsService, type SaveMappingsRequest } from "../generated";

export function useSaveMappingsMutation() {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: async ({ projectId, mappings }) => {
      return await MappingsService.saveMappings({
        requestBody: { projectId, mappings },
      });
    },
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({ queryKey: ["mappings", projectId] });
    },
  });
}
```

**Update components to use bulk pattern:**

```typescript
function MappingTable() {
  const { data } = useMappingsQuery(projectId);
  const saveMappings = useSaveMappingsMutation();

  const handleAdd = (newMapping) => {
    const updated = [...(data?.mappings ?? []), newMapping];
    saveMappings.mutate({ projectId, mappings: updated });
  };
}
```

### Step 5: Update Spaces Hooks

**Update `useSpacesQuery.ts`:**

```typescript
import { useQuery } from "@tanstack/react-query";
import { SpacesService } from "../generated";

export function useSpacesQuery(projectId: string) {
  return useQuery({
    queryKey: ["spaces", projectId],
    queryFn: () => SpacesService.listSpaces({ projectId }),
    enabled: !!projectId,
  });
}
```

**Update `useCreateSpaceMutation.ts`:**

```typescript
import { useMutation, useQueryClient } from "@tanstack/react-query";
import { SpacesService, type CreateSpaceRequest } from "../generated";

export function useCreateSpaceMutation() {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: async ({ projectId, label, spaceTypeId }) => {
      return await SpacesService.createSpace({
        requestBody: { projectId, label, spaceTypeId },
      });
    },
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({ queryKey: ["spaces", projectId] });
    },
  });
}
```

### Step 6: Remove Old Epic 1 Services

**Delete Service Implementations:**

```bash
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/buildingmotif.mock.service.ts
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/space.mock.service.ts
rm apps/designer/src/domains/building-semantics/api/mappings.api.service.ts
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/validation.mock.service.ts
```

**Delete Service Interfaces:**

```bash
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/interfaces/buildingmotif.ts
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/interfaces/space.service.interface.ts
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/interfaces/validation.service.interface.ts
# If exists:
rm apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/interfaces/mappings.service.interface.ts
```

**Keep (Designer-only):**

- `ai-suggestion.mock.service.ts`
- `interfaces/ai-suggestion.ts`

### Step 7: Test End-to-End

**Start all services:**

```bash
./scripts/start-dev.sh
```

**Test workflow:**

1. Open Designer: `http://localhost:3000`
2. Open mapping popup
3. Select equipment type (hierarchical dropdown)
4. Select device type (filtered by equipment)
5. Select property (filtered by device)
6. Create new space (space type from template)
7. Select created space
8. Save mapping (bulk save)
9. Verify mapping in table
10. Reload page → mapping still shows (from mock API)

**Check FastAPI logs:**

```
[Semantics-API] INFO:     "GET /api/v1/223p/templates HTTP/1.1" 200 OK
[Semantics-API] INFO:     "POST /api/v1/223p/mappings HTTP/1.1" 200 OK
```

### Step 8: Verify camelCase Serialization

**Check network tab:**

- Request body uses camelCase: `{ "projectId": "...", "equipmentTypeId": "..." }`
- Response body uses camelCase: `{ "spaceTypes": [...], "propertyType": "..." }`

**Check TypeScript types:**

```typescript
interface SemanticMapping {
  equipmentTypeId: string; // ✅ camelCase
  deviceTypeId: string; // ✅ camelCase
  propertyId: string; // ✅ camelCase
  spaceId?: string; // ✅ camelCase
}
```

---

## Technical Notes

### Hierarchical Template Benefits

**Single API call:**

- Epic 1: 3 separate queries (systems, devices, properties)
- Phase 1: 1 query with nested structure
- Reduces network overhead
- Simplifies component logic

**Dynamic filtering:**

```typescript
// Equipment type selected → filter devices
const devices = selectedSystem?.devices ?? [];

// Device type selected → filter properties
const properties = selectedDevice?.properties ?? [];
```

**Impossible to create invalid combinations:**

- UI only shows valid device types for selected equipment
- UI only shows valid properties for selected device
- No validation endpoint needed

### Bulk Save Pattern

**Why bulk instead of individual CRUD?**

- Phase 1 goal: Validate contract, not functionality
- Simpler mock endpoint implementation
- Phase 2 will have real persistence anyway
- Reduces API surface area (5 endpoints vs 14)

**Implementation:**

```typescript
// Add mapping: send full array
const updated = [...existingMappings, newMapping];
saveMappings.mutate({ projectId, mappings: updated });

// Delete mapping: send filtered array
const updated = existingMappings.filter((m) => m.pointId !== deletedId);
saveMappings.mutate({ projectId, mappings: updated });
```

### React Query Caching Strategy

**Aggressive caching for templates:**

```typescript
staleTime: 5 * 60 * 1000; // 5 minutes
```

**Why?**

- Templates rarely change (static in Phase 1)
- Large payload (hierarchical structure)
- Reduces unnecessary API calls

**Fresh data for CRUD:**

```typescript
// No staleTime → always fresh
queryClient.invalidateQueries({ queryKey: ["mappings", projectId] });
```

### camelCase Serialization with Pydantic

**Python code (snake_case):**

```python
equipment_type_id: str = Field(..., serialization_alias="equipmentTypeId")
```

**JSON API (camelCase):**

```json
{ "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit" }
```

**TypeScript (camelCase):**

```typescript
interface SemanticMapping {
  equipmentTypeId: string;
}
```

**No conversion needed in TypeScript** - Pydantic handles serialization

### Error Handling Strategy

**React Query handles:**

- Automatic retry (3 attempts)
- Error state management
- Loading state management

**Components display:**

- Spinner during loading
- Error message on failure
- Data when successful

**Example:**

```typescript
function MappingPopup() {
  const { data, isLoading, isError, error } = useTemplatesQuery()

  if (isLoading) return <Spinner />
  if (isError) return <Alert variant="destructive">{error.message}</Alert>

  return <MappingForm templates={data} />
}
```

---

## Prerequisites

**Story Dependencies:**

- ~~Story 2.0: Consolidate service naming~~ - **SKIPPED** (breaking Epic 1 is acceptable)
- Story 2.1: Create FastAPI app scaffolding (complete)
- Story 2.2: Design OpenAPI specification (complete - 3 services, 5 endpoints)
- Story 2.3: Generate TypeScript client (complete - 5 functions)
- Story 2.4: Implement mock endpoints (complete - hierarchical data)

**Reason:** Need working FastAPI endpoints and generated TypeScript client with hierarchical structure.

**Note:** Story 2.0 was skipped - this story does the complete Epic 1 → Phase 1 transition in one step (breaking is acceptable).

---

## Dependencies

**Stories that depend on this:**

**None** - This completes Phase 1.

**Next phase:** Phase 2 (BuildingMOTIF SDK integration) - replaces mock data with real semantic engine

---

## Definition of Done

- [ ] 5 hooks implemented using TypeScript client
- [ ] 4 obsolete hooks removed (device types, observable properties, individual CRUD)
- [ ] API configuration file created
- [ ] API client initialized in app
- [ ] Old Epic 1 service implementations removed (buildingmotif, space, mappings, validation)
- [ ] Old Epic 1 service interfaces removed (4 interfaces deleted, ai-suggestion kept)
- [ ] TypeScript compiles without errors
- [ ] Designer app starts successfully
- [ ] Hierarchical templates load via single API call
- [ ] Dropdowns filter correctly (equipment → devices → properties)
- [ ] Bulk save mutation works
- [ ] Create space mutation works
- [ ] Spaces dropdown loads from FastAPI
- [ ] camelCase fields serialize correctly
- [ ] URN identifiers use `id` field name
- [ ] Network tab shows API calls to FastAPI
- [ ] No sessionStorage usage for 223P data
- [ ] Phase 1 limitations documented
- [ ] End-to-end workflow tested manually
- [ ] No console errors
- [ ] Code follows project conventions
- [ ] Files committed to git with message: "Epic 2 Story 2.5: Integrate TypeScript client with simplified 5-endpoint design"

---

## References

- **Story 2.2:** Design OpenAPI Specification (5 endpoints, hierarchical templates, Pydantic aliases)
- **Story 2.3:** Generate TypeScript client (5 functions, camelCase fields)
- **Story 2.4:** Implement mock endpoints (hierarchical mock data)
- **Tech Spec Review:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/tech-spec-review.md`
- **Phase Breakdown:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/epic-2-phase-breakdown.md`
- **React Query Documentation:** https://tanstack.com/query/latest
