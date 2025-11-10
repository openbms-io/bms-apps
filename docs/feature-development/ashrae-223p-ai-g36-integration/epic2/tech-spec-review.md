# Epic 2 Tech Spec Review - Epic 1 Architecture Analysis

**Date:** 2025-11-06
**Updated:** 2025-11-09 (Phase 1 Simplification: 14 → 5 endpoints)
**Phase:** Phase 1 - Task 1.2
**Status:** Complete (Updated with Simplified Design)

---

## Overview

This document extracts the actual Epic 1 architecture from code to inform Epic 2 (BuildingMOTIF API Integration) implementation. All analysis based on actual implementation in `/apps/designer/src/domains/building-semantics`.

---

## Service Architecture Analysis

### Current State - Epic 1

Epic 1 implements **6 services** with **inconsistent patterns**:

#### ✅ Services WITH Interfaces (4)

1. **`IBuildingMOTIFService`** (`buildingmotif.ts`)
2. **`ISpaceService`** (`space.service.interface.ts`)
3. **`IValidationService`** (`validation.service.interface.ts`)
4. **`IAISuggestionService`** (`ai-suggestion.ts`) - Designer-only, NOT FastAPI

#### ❌ Services WITHOUT Interfaces (2)

5. **`semanticMappingsApi`** (`mappings.api.ts`) - Direct object export
6. **`spaces223pApi`** (`spaces.api.ts`) - Direct object export

---

## Naming Inconsistency Issue

**Problem Identified:**

- Mix of `I*Service` interfaces and direct API objects
- Only one service references the tool name (`IBuildingMOTIFService`)
- Inconsistent naming conventions

**Root Cause:**

- All **FastAPI services** are **ASHRAE 223P domain services**, not BuildingMOTIF services
- BuildingMOTIF is the **implementation detail** (Python SDK)
- Domain is **223P**, tool is **BuildingMOTIF**

**Impact:**

- Confusing architecture
- Inconsistent patterns across codebase
- Harder to maintain and extend

---

## Proposed Solution - `I223P*Service` Pattern

Consolidate **FastAPI-backed services** with **domain-prefixed interfaces**:

| Current Name            | Proposed Name                       | Scope         | Rationale                                   |
| ----------------------- | ----------------------------------- | ------------- | ------------------------------------------- |
| `IBuildingMOTIFService` | `I223PTemplatesService`             | FastAPI       | Domain (223P) + Responsibility (Templates)  |
| `ISpaceService`         | `I223PSpacesService`                | FastAPI       | Domain (223P) + Responsibility (Spaces)     |
| `semanticMappingsApi`   | `I223PMappingsService`              | FastAPI       | Add interface, domain prefix                |
| `spaces223pApi`         | _(merge with `I223PSpacesService`)_ | FastAPI       | Duplicate functionality                     |
| `IValidationService`    | `I223PValidationService`            | FastAPI       | Domain (223P) + Responsibility (Validation) |
| `IAISuggestionService`  | **NO CHANGE**                       | Designer-only | Stays in Designer app, calls `/lib/ai`      |

**AI Service Clarification:**

- `IAISuggestionService` remains **Designer-only**
- Calls `/apps/designer/src/lib/ai` (Vercel AI SDK + Mem0)
- **NOT part of FastAPI integration**
- Handled in Phase 3 (last phase) separately

**Benefits:**

- Clear domain ownership (`223P`)
- Consistent interface pattern (`I*Service`)
- Future extensibility (`IBrick*Service`, `IHaystack*Service`)
- Aligns with `/api/223p/*` URL structure

---

## Epic 1 Service Interfaces - Actual Code

### 1. `I223PTemplatesService` (was `IBuildingMOTIFService`)

**File:** `/adapters/ashrae-223p/services/interfaces/buildingmotif.ts`

**Interface (Simplified - Hierarchical Structure):**

```typescript
export interface I223PTemplatesService {
  getTemplates(): Promise<TemplatesResponse>;
}

interface TemplatesResponse {
  systems: TemplateSystem[]; // Equipment types with nested devices/properties
  spaceTypes: SpaceType[]; // ASHRAE 223P space types
}

interface TemplateSystem {
  id: string; // URN: "urn:223p:VAVReheatTerminalUnit"
  label: string;
  description?: string;
  devices: TemplateDevice[]; // Nested devices for this system
}

interface TemplateDevice {
  id: string; // URN: "urn:223p:Damper"
  label: string;
  description?: string;
  properties: TemplateProperty[]; // Nested properties for this device
}

interface TemplateProperty {
  id: string; // URN: "urn:223p:DamperPosition"
  label: string;
  propertyType: "quantifiable" | "enumerated" | "actuatable"; // camelCase
  description?: string;
}
```

**Current Implementation:**

- Mock: `buildingmotif.mock.service.ts` (returns hierarchical ASHRAE 223P templates)
- Storage: N/A (static data)

**FastAPI Endpoint (1 - Simplified from 3):**

```
GET /api/v1/223p/templates → getTemplates()
```

**Response Structure (camelCase fields from Pydantic aliases):**

```json
{
  "systems": [
    {
      "id": "urn:223p:VAVReheatTerminalUnit",
      "label": "VAV with Reheat",
      "devices": [
        {
          "id": "urn:223p:Damper",
          "label": "Damper",
          "properties": [
            {
              "id": "urn:223p:DamperPosition",
              "label": "Damper Position",
              "propertyType": "quantifiable"
            }
          ]
        }
      ]
    }
  ],
  "spaceTypes": [
    {
      "id": "urn:223p:Office",
      "label": "Office"
    }
  ]
}
```

**React Query Hooks:**

- `useTemplatesQuery()` - uses `TemplatesService.getTemplates()` (single hierarchical call)

---

### 2. `I223PSpacesService` (was `ISpaceService`)

**File:** `/adapters/ashrae-223p/services/space.service.interface.ts`

**Interface (Simplified - Essential CRUD Only):**

```typescript
export interface I223PSpacesService {
  listSpaces(projectId: string): Promise<SpaceInstance[]>;
  createSpace(request: CreateSpaceRequest): Promise<SpaceInstance>;
}

interface SpaceInstance {
  id: string; // URN: "urn:bms:Space:office-101"
  label: string; // "Office 101"
  spaceTypeId: string; // URN: "urn:223p:Office" (camelCase from Pydantic alias)
}

interface CreateSpaceRequest {
  projectId: string; // camelCase
  label: string; // camelCase
  spaceTypeId: string; // camelCase - from templates.spaceTypes
}
```

**Current Implementation:**

- Mock: `space.mock.service.ts`
- API: `spaces.api.ts` (sessionStorage: `223p-spaces:${projectId}`)

**FastAPI Endpoints (2 - Simplified from 4):**

```
GET  /api/v1/223p/spaces?projectId={id}  → listSpaces()
POST /api/v1/223p/spaces                 → createSpace()
```

**Removed Methods (not needed for Phase 1):**

- `searchSpace()` - Can filter client-side
- `addPointToSpace()` - Not needed for basic tagging workflow

**React Query Hooks:**

- `useSpacesQuery()` - uses `SpacesService.listSpaces()`
- `useCreateSpaceMutation()` - uses `SpacesService.createSpace()`

---

### 3. `I223PMappingsService` (was `semanticMappingsApi`)

**File:** `/api/mappings.api.ts`

**Interface (Simplified - Bulk Save Pattern):**

```typescript
export interface I223PMappingsService {
  getMappings(projectId: string): Promise<MappingsResponse>;
  saveMappings(request: SaveMappingsRequest): Promise<MappingsResponse>;
}

interface MappingsResponse {
  projectId: string; // camelCase from Pydantic alias
  mappings: SemanticMapping[];
}

interface SemanticMapping {
  pointId: string; // camelCase - "BACnet:Device1:AI-1"
  equipmentTypeId: string; // camelCase - URN: "urn:223p:VAVReheatTerminalUnit"
  deviceTypeId: string; // camelCase - URN: "urn:223p:Damper"
  propertyId: string; // camelCase - URN: "urn:223p:DamperPosition"
  spaceId?: string; // camelCase - URN: "urn:bms:Space:office-101"
}

interface SaveMappingsRequest {
  projectId: string; // camelCase
  mappings: SemanticMapping[]; // Full array - bulk save/replace
}
```

**Storage:** sessionStorage (`223p-mappings:${projectId}`)

**FastAPI Endpoints (2 - Simplified from 6):**

```
GET  /api/v1/223p/mappings?projectId={id}  → getMappings()
POST /api/v1/223p/mappings                 → saveMappings() (bulk save/replace)
```

**Removed Methods (replaced by bulk save):**

- `getMapping()` - Not needed, get all and filter client-side
- `createMapping()` - Use bulk save with added mapping
- `updateMapping()` - Use bulk save with updated mapping
- `deleteMapping()` - Use bulk save with filtered array
- `clearAllMappings()` - Use bulk save with empty array

**Bulk Save Pattern Benefits:**

- Simpler API surface (2 endpoints vs 6)
- Easier mock implementation (no state management)
- Phase 1 goal: Validate contract, not persistence
- Phase 2 will add real persistence anyway

**React Query Hooks:**

- `useMappingsQuery()` - uses `MappingsService.getMappings()`
- `useSaveMappingsMutation()` - uses `MappingsService.saveMappings()` (bulk pattern)

---

### 4. ~~`I223PValidationService`~~ (REMOVED - Not Needed)

**Status:** ❌ **REMOVED in Phase 1 Simplification**

**Reason:** Hierarchical template structure prevents invalid combinations

**How Validation Works Without Endpoint:**

1. User selects equipment type → UI shows only valid devices for that equipment
2. User selects device type → UI shows only valid properties for that device
3. **Impossible to create invalid combinations** - UI filtering based on hierarchical data

**Hierarchical Structure Replaces Validation:**

```typescript
// Equipment type selected
const selectedSystem = templates?.systems.find((s) => s.id === equipmentTypeId);
const validDevices = selectedSystem?.devices ?? []; // Only valid devices shown

// Device type selected
const selectedDevice = validDevices.find((d) => d.id === deviceTypeId);
const validProperties = selectedDevice?.properties ?? []; // Only valid properties shown
```

**Phase 2 Validation:**

- BuildingMOTIF SDK will provide SHACL validation during save
- Server-side validation before persistence
- No need for separate validation endpoint

**Epic 1 Implementation:**

- Mock: `validation.mock.service.ts` ❌ **No longer needed**

**FastAPI Endpoints:** None (0 - removed from 1)

**React Query Hooks:** None

---

### 5. `IAISuggestionService` (Designer-only, NO FastAPI)

**File:** `/adapters/ashrae-223p/services/interfaces/ai-suggestion.ts`

**Interface:**

```typescript
export interface IAISuggestionService {
  suggestMapping(point: BACnetPointData): Equipment223PRecommendation;
}
```

**Current Implementation:**

- Mock: `ai-suggestion.mock.service.ts` (rule-based suggestions)

**Epic 2 Implementation:**

- **NO FastAPI endpoint**
- Stays in Designer app
- Calls `/apps/designer/src/lib/ai` (Vercel AI SDK + Mem0)
- Handled in Phase 3 (last phase)

**React Query Hooks:**

- `useAISuggestionQuery()` - uses `aiSuggestionService.suggestMapping()`

**No rename needed** - not part of 223P API integration

---

## FastAPI Endpoint Summary

**Total: 5 endpoints across 3 services (Simplified from 14 endpoints across 4 services)**

| Service                      | Endpoints | Methods                                                                  | Change                     |
| ---------------------------- | --------- | ------------------------------------------------------------------------ | -------------------------- |
| `I223PTemplatesService`      | 1         | GET hierarchical templates (systems → devices → properties + spaceTypes) | 3 → 1                      |
| `I223PSpacesService`         | 2         | GET list, POST create                                                    | 4 → 2                      |
| `I223PMappingsService`       | 2         | GET mappings, POST bulk save/replace                                     | 6 → 2                      |
| ~~`I223PValidationService`~~ | ~~1~~     | ~~POST validate~~                                                        | ~~1 → 0 (removed)~~        |
| **Total**                    | **5**     |                                                                          | **14 → 5 (64% reduction)** |

**Design Principles Applied:**

- **YAGNI:** Only what's needed for Phase 1 contract validation
- **Hierarchical Data:** Single API call for templates with nested relationships
- **Bulk Operations:** Simpler API surface, easier mock implementation
- **UI Filtering:** Hierarchical structure prevents invalid combinations (no validation endpoint needed)

**Not included (Designer-only):**

- `IAISuggestionService` - No FastAPI endpoint, calls `/lib/ai` directly

---

## Phase 1 Design Simplification (2025-11-09)

**Original Design:** 14 endpoints with full CRUD operations
**Simplified Design:** 5 endpoints following YAGNI principle

### Key Simplifications

#### 1. Hierarchical Templates (3 → 1 endpoint)

**Before (3 separate calls):**

```typescript
GET /api/223p/templates/systems      → SystemType[]
GET /api/223p/templates/devices      → DeviceType[]
GET /api/223p/templates/properties   → ObservableProperty[]
```

**After (single hierarchical call):**

```typescript
GET /api/v1/223p/templates → {
  systems: [{
    id: "urn:223p:VAVReheatTerminalUnit",
    devices: [{
      id: "urn:223p:Damper",
      properties: [{
        id: "urn:223p:DamperPosition"
      }]
    }]
  }],
  spaceTypes: [...]
}
```

**Benefits:**

- Single API call loads all template data
- Eliminates need for 3 separate queries
- UI filters dynamically based on selections
- Impossible to create invalid combinations

#### 2. Bulk Mappings (6 → 2 endpoints)

**Before (individual CRUD):**

```typescript
GET    /api/223p/mappings?projectId={id}
GET    /api/223p/mappings/{key}
POST   /api/223p/mappings
PUT    /api/223p/mappings/{key}
DELETE /api/223p/mappings/{key}
DELETE /api/223p/mappings?projectId={id}
```

**After (bulk save/replace):**

```typescript
GET  /api/v1/223p/mappings?projectId={id} → { mappings: [...] }
POST /api/v1/223p/mappings                → { mappings: [...] }  // Full array
```

**Benefits:**

- Simpler API surface (2 endpoints vs 6)
- Easier mock implementation (no state management)
- Phase 1 goal: Validate contract, not functionality
- Phase 2 will add real persistence anyway

#### 3. Essential Spaces (4 → 2 endpoints)

**Before (full CRUD + search):**

```typescript
GET  /api/223p/spaces?projectId={id}
POST /api/223p/spaces
GET  /api/223p/spaces/search?label={label}
POST /api/223p/spaces/{id}/points
```

**After (essential CRUD only):**

```typescript
GET  /api/v1/223p/spaces?projectId={id}
POST /api/v1/223p/spaces
```

**Benefits:**

- Removed `searchSpace()` - can filter client-side
- Removed `addPointToSpace()` - not needed for basic tagging
- Focus on contract validation, not full feature set

#### 4. No Validation Endpoint (1 → 0)

**Removed:** `POST /api/223p/validate`

**Reason:** Hierarchical structure prevents invalid combinations

**How it works:**

```typescript
// Equipment type selected → only valid devices shown
const devices = selectedSystem?.devices ?? [];

// Device type selected → only valid properties shown
const properties = selectedDevice?.properties ?? [];
```

**Phase 2:** BuildingMOTIF SDK will provide server-side SHACL validation during save

### Design Principles Applied

1. **YAGNI (You Aren't Gonna Need It)**

   - Only what's needed for Phase 1 contract validation
   - Phase 2 will replace with BuildingMOTIF SDK anyway
   - Don't build what will be thrown away

2. **Hierarchical Data > Multiple Endpoints**

   - Single API call with nested structure
   - Client-side filtering reduces API complexity
   - Better performance (fewer round trips)

3. **Bulk Operations > Individual CRUD**

   - Simpler API surface
   - Easier mock implementation
   - Validates contract without state management

4. **UI Filtering > Server Validation**
   - Hierarchical structure makes invalid combinations impossible
   - No need for separate validation endpoint
   - Real validation in Phase 2 with BuildingMOTIF

### Result

- **64% reduction** in endpoints (14 → 5)
- **Simpler implementation** for Phase 1
- **Same functionality** for contract validation
- **Clean foundation** for Phase 2 BuildingMOTIF integration

---

## camelCase Serialization with Pydantic

**Pattern:** Explicit Pydantic serialization aliases for Python → JSON transformation

### Python Code (snake_case - PEP 8)

```python
from pydantic import BaseModel, Field, ConfigDict

class SemanticMappingDTO(BaseModel):
    """Semantic equipment mapping for a single BACnet point."""

    model_config = ConfigDict(populate_by_name=True)

    equipment_type_id: str = Field(
        ...,
        serialization_alias="equipmentTypeId",
        description="Equipment type URN from template"
    )
    device_type_id: str = Field(
        ...,
        serialization_alias="deviceTypeId",
        description="Device type URN from template"
    )
    property_id: str = Field(
        ...,
        serialization_alias="propertyId",
        description="Property URN from template"
    )
    space_id: str | None = Field(
        None,
        serialization_alias="spaceId",
        description="Space instance URN (optional)"
    )
```

### JSON API Response (camelCase - JavaScript convention)

```json
{
  "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit",
  "deviceTypeId": "urn:223p:Damper",
  "propertyId": "urn:223p:DamperPosition",
  "spaceId": "urn:bms:Space:office-101"
}
```

### TypeScript (camelCase - no runtime conversion needed)

```typescript
interface SemanticMapping {
  equipmentTypeId: string; // Already camelCase from API
  deviceTypeId: string;
  propertyId: string;
  spaceId?: string;
}

// Generated client handles serialization automatically
const response = await MappingsService.getMappings({
  projectId: "project-123",
});
console.log(response.mappings[0].equipmentTypeId); // ✅ Works directly
```

### Benefits

1. **Python follows PEP 8** - snake_case for identifiers
2. **JSON follows JavaScript conventions** - camelCase for fields
3. **Explicit and intentional** - no magic, clear aliases
4. **Type-safe** - Both Python and TypeScript enforce correctness
5. **No runtime conversion** - OpenAPI generator produces correct TypeScript types

### Why Explicit Aliases?

**Alternative:** Use Pydantic's `alias_generator` for automatic camelCase

```python
# NOT RECOMMENDED
class SemanticMappingDTO(BaseModel):
    model_config = ConfigDict(alias_generator=to_camel)  # Magic

    equipment_type_id: str  # Implicitly becomes equipmentTypeId
```

**Our Choice:** Explicit `serialization_alias`

```python
# RECOMMENDED
class SemanticMappingDTO(BaseModel):
    equipment_type_id: str = Field(..., serialization_alias="equipmentTypeId")  # Explicit
```

**Reasoning:**

- **Intentional** - Every alias is visible and deliberate
- **Searchable** - Can grep for "equipmentTypeId" in Python code
- **No magic** - No hidden transformations, easier to debug
- **Type-safe** - Explicit aliases catch typos at definition time

---

## URN Identifier Convention

**Format:** `urn:{domain}:{type}:{id}`

### URN Structure

**Templates (from ASHRAE 223P ontology):**

```
urn:223p:{TemplateName}

Examples:
- urn:223p:VAVReheatTerminalUnit  (System/Equipment Type)
- urn:223p:Damper                  (Device Type)
- urn:223p:DamperPosition          (Property Type)
- urn:223p:Office                  (Space Type)
```

**Instances (from BMS application):**

```
urn:bms:{ResourceType}:{instance-id}

Examples:
- urn:bms:Space:office-101
- urn:bms:Project:building-a
- urn:bms:Equipment:vav-101
```

### Field Naming Convention

**Always use `id` (not `urn`) for consistency**

**TypeScript:**

```typescript
interface TemplateSystem {
  id: string; // "urn:223p:VAVReheatTerminalUnit"
  label: string;
  devices: TemplateDevice[];
}

interface TemplateDevice {
  id: string; // "urn:223p:Damper"
  label: string;
  properties: TemplateProperty[];
}

interface SpaceInstance {
  id: string; // "urn:bms:Space:office-101"
  label: string;
  spaceTypeId: string; // "urn:223p:Office"
}
```

**Python (Pydantic DTOs):**

```python
class TemplateSystemDTO(BaseModel):
    id: str = Field(..., description="URN: urn:223p:{TemplateName}")
    label: str
    devices: list[TemplateDeviceDTO]

class SpaceInstanceDTO(BaseModel):
    id: str = Field(..., description="URN: urn:bms:Space:{id}")
    label: str
    space_type_id: str = Field(
        ...,
        serialization_alias="spaceTypeId",
        description="URN: urn:223p:{SpaceType}"
    )
```

### Why URNs?

1. **Globally unique** - No collisions between different resources
2. **Self-describing** - Format indicates source and type
3. **Namespace separation** - `223p` (ontology) vs `bms` (application)
4. **BuildingMOTIF compatible** - Phase 2 integration ready
5. **Semantic clarity** - Clear distinction between templates and instances

### Usage Examples

**Frontend filtering:**

```typescript
const selectedSystem = templates.systems.find(
  (s) => s.id === "urn:223p:VAVReheatTerminalUnit",
);

const mapping: SemanticMapping = {
  equipmentTypeId: "urn:223p:VAVReheatTerminalUnit",
  deviceTypeId: "urn:223p:Damper",
  propertyId: "urn:223p:DamperPosition",
  spaceId: "urn:bms:Space:office-101",
};
```

**Backend validation (Phase 2):**

```python
# Validate template URN from 223P ontology
if not equipment_type_id.startswith('urn:223p:'):
    raise ValueError(f"Invalid template URN: {equipment_type_id}")

# Validate instance URN from BMS application
if space_id and not space_id.startswith('urn:bms:Space:'):
    raise ValueError(f"Invalid space URN: {space_id}")
```

---

## Coding Standards for Epic 2

**Reference:** `/docs/coding-standards.md`

This section defines coding conventions for Epic 2 implementation, covering both FastAPI (Python) and Designer app (TypeScript) code.

### Python FastAPI Conventions

**Function Naming:**

- `snake_case` for all function names
- Async endpoints: `async def endpoint_name(...) -> ResponseType:`

**Type Hints:**

- Required for all function parameters and return types
- Use Python 3.11+ type syntax: `list[str]`, `dict[str, int]`

**Docstrings:**

- Required for all public functions using Google style
- Include Args, Returns, and Raises sections

**Code Formatting:**

- Line length: 88 characters (Black formatter)
- Indentation: 4 spaces
- Tools: Black (formatter), Ruff (linter), mypy (type checker)

**Example FastAPI Endpoint:**

```python
from fastapi import APIRouter, HTTPException
from typing import Optional

router = APIRouter(prefix="/api/223p")


@router.get("/templates/systems")
async def get_templates() -> list[SystemTypeDTO]:
    """
    Retrieve all ASHRAE 223P system templates from BuildingMOTIF.

    Returns:
        List of system template DTOs

    Raises:
        HTTPException: When BuildingMOTIF SDK fails
    """
    try:
        templates = await buildingmotif_service.get_systems()
        return [SystemTypeDTO.from_rdf(t) for t in templates]
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.post("/mappings")
async def create_mapping(
    request: CreateMappingRequest,
) -> SemanticEquipmentDTO:
    """
    Create a new semantic mapping for a BACnet point.

    Args:
        request: Mapping creation request with projectId, pointId, and equipment data

    Returns:
        Created semantic equipment DTO

    Raises:
        HTTPException: When validation fails or BuildingMOTIF operation fails
    """
    mapping = await mappings_service.create_mapping(
        project_id=request.project_id,
        point_id=request.point_id,
        equipment=request.equipment,
    )
    return SemanticEquipmentDTO.from_domain(mapping)
```

**Request/Response Models:**

```python
from pydantic import BaseModel, Field


class CreateMappingRequest(BaseModel):
    """Request model for creating semantic mapping."""

    project_id: str = Field(..., description="Project identifier")
    point_id: str = Field(..., description="BACnet point identifier")
    equipment: SemanticEquipmentInput = Field(..., description="Equipment data")


class SemanticEquipmentDTO(BaseModel):
    """Response model for semantic equipment."""

    equipment_type: str
    device_type: str
    observable_property: str
    space_id: Optional[str] = None
```

### TypeScript Designer App Conventions

**Function Naming:**

- `camelCase` for all function names
- Boolean functions: `is*` or `has*` prefix
- Event handlers: `handle*` prefix

**Type System:**

- Explicit return types required
- No `any` or `unknown` types - define explicit types
- Use object destructuring for multiple parameters
- Prefer `interface` over `type` for objects

**Async Operations:**

- Always use `async/await`, never raw Promises
- Include try/catch for error handling

**Code Formatting:**

- Indentation: 2 spaces
- No semicolons
- Single quotes
- Tools: ESLint, Prettier, TypeScript compiler

**Example Service Interface:**

```typescript
export interface I223PTemplatesService {
  getTemplates(): Promise<SystemType[]>;
  getDeviceTypes(): Promise<DeviceType[]>;
  getObservableProperties(): Promise<ObservableProperty[]>;
}
```

**Example API Service Implementation:**

```typescript
import type { SystemType, DeviceType, ObservableProperty } from "@/types/223p";

export class Templates223PApiService implements I223PTemplatesService {
  private readonly baseUrl = "/api/223p";

  async getTemplates(): Promise<SystemType[]> {
    try {
      const response = await fetch(`${this.baseUrl}/templates/systems`);
      if (!response.ok) {
        throw new Error(`Failed to fetch templates: ${response.statusText}`);
      }
      return await response.json();
    } catch (error) {
      console.error("Error fetching templates:", error);
      throw error;
    }
  }

  async getDeviceTypes(): Promise<DeviceType[]> {
    try {
      const response = await fetch(`${this.baseUrl}/templates/devices`);
      if (!response.ok) {
        throw new Error(`Failed to fetch device types: ${response.statusText}`);
      }
      return await response.json();
    } catch (error) {
      console.error("Error fetching device types:", error);
      throw error;
    }
  }

  async getObservableProperties(): Promise<ObservableProperty[]> {
    try {
      const response = await fetch(`${this.baseUrl}/templates/properties`);
      if (!response.ok) {
        throw new Error(`Failed to fetch properties: ${response.statusText}`);
      }
      return await response.json();
    } catch (error) {
      console.error("Error fetching properties:", error);
      throw error;
    }
  }
}
```

**Example React Query Hook:**

```typescript
import { useQuery } from "@tanstack/react-query";
import type { SystemType } from "@/types/223p";
import { templates223PService } from "@/services/223p";

interface UseTemplatesQueryOptions {
  enabled?: boolean;
}

export function useTemplatesQuery({
  enabled = true,
}: UseTemplatesQueryOptions = {}) {
  return useQuery<SystemType[], Error>({
    queryKey: ["223p", "templates", "systems"],
    queryFn: async (): Promise<SystemType[]> => {
      return await templates223PService.getTemplates();
    },
    enabled,
    staleTime: 5 * 60 * 1000, // 5 minutes
    cacheTime: 10 * 60 * 1000, // 10 minutes
  });
}
```

**Example Mutation Hook:**

```typescript
import { useMutation, useQueryClient } from "@tanstack/react-query";
import type { SemanticEquipment } from "@/types/223p";
import { mappings223PService } from "@/services/223p";

interface CreateMappingVariables {
  projectId: string;
  pointId: string;
  mapping: SemanticEquipment;
}

export function useCreateMappingMutation() {
  const queryClient = useQueryClient();

  return useMutation<SemanticEquipment, Error, CreateMappingVariables>({
    mutationFn: async ({
      projectId,
      pointId,
      mapping,
    }: CreateMappingVariables): Promise<SemanticEquipment> => {
      return await mappings223PService.createMapping({
        projectId,
        pointId,
        mapping,
      });
    },
    onSuccess: (data, variables) => {
      // Invalidate mappings query
      queryClient.invalidateQueries({
        queryKey: ["223p", "mappings", variables.projectId],
      });
    },
  });
}
```

### Common Principles

**Comments and Documentation:**

- Code should be self-documenting with clear naming
- Comments explain "why", not "what"
- Avoid unnecessary comments - use clear variable/function names instead

**Error Handling:**

- Handle errors explicitly, don't suppress them
- Log errors with context for debugging
- Fail fast with clear error messages

**Testing:**

- Python: `test_*.py` files using pytest
- TypeScript: `*.spec.ts` files using Jest
- Mock external dependencies, not the system under test

**Parameter Naming:**

- TypeScript: Use object destructuring for multiple parameters
- Python: Use keyword arguments for clarity

---

## FastAPI Foundation Work - Architecture and Patterns

### Project Structure and Location

**New Application:** `apps/building-semantics-api-app/`

**Directory Structure:**

```
apps/building-semantics-api-app/
├── src/
│   ├── __init__.py
│   ├── main.py                    # FastAPI app entry point
│   ├── routers/
│   │   ├── __init__.py
│   │   ├── templates.py           # /api/223p/templates/* routes
│   │   ├── spaces.py              # /api/223p/spaces/* routes
│   │   ├── mappings.py            # /api/223p/mappings/* routes
│   │   └── validation.py          # /api/223p/validate route
│   ├── services/
│   │   ├── __init__.py
│   │   ├── templates_service.py   # BuildingMOTIF templates wrapper
│   │   ├── spaces_service.py      # Space management logic
│   │   ├── mappings_service.py    # Mappings CRUD logic
│   │   └── validation_service.py  # SHACL validation wrapper
│   ├── adapters/
│   │   ├── __init__.py
│   │   └── buildingmotif_adapter.py  # BuildingMOTIF SDK integration
│   ├── dto/
│   │   ├── __init__.py
│   │   ├── templates_dto.py       # SystemType, DeviceType, Property DTOs
│   │   ├── spaces_dto.py          # SpaceDTO
│   │   ├── mappings_dto.py        # SemanticEquipment DTO
│   │   └── validation_dto.py      # ValidationResult DTO
│   ├── config/
│   │   ├── __init__.py
│   │   └── settings.py            # Configuration from environment
│   └── utils/
│       ├── __init__.py
│       └── error_handlers.py      # Exception mapping
├── tests/
│   ├── unit/
│   │   ├── test_services/
│   │   ├── test_dto/
│   │   └── test_adapters/
│   └── integration/
│       └── test_routers/
├── pyproject.toml
├── .env.template
├── .gitignore
└── README.md
```

### Dependencies Configuration

**File:** `apps/building-semantics-api-app/pyproject.toml`

```toml
[project]
name = "building-semantics-api-app"
version = "0.1.0"
description = "FastAPI wrapper for BuildingMOTIF SDK - ASHRAE 223P semantic tagging"
requires-python = ">=3.11"

dependencies = [
    "fastapi>=0.104.0",
    "uvicorn[standard]>=0.24.0",
    "buildingmotif>=2.0.0",     # BuildingMOTIF SDK
    "pydantic>=2.5.0",          # Validation
    "sqlalchemy>=2.0.0",        # RDF storage via BuildingMOTIF
    "python-dotenv>=1.0.0",     # Environment variables
    "loguru>=0.7.0",            # Logging
    "python-multipart>=0.0.6",  # Form data parsing
]

[project.optional-dependencies]
test = [
    "pytest>=7.4.0",
    "pytest-asyncio>=0.21.0",
    "httpx>=0.25.0",            # FastAPI test client
    "pytest-cov>=4.1.0",
    "pytest-mock>=3.11.1",
]
dev = [
    "mypy>=1.7.0",              # Type checking
    "black>=23.11.0",           # Code formatting
    "ruff>=0.1.6",              # Linting
]

[build-system]
requires = ["hatchling"]
build-backend = "hatchling.build"

[tool.black]
line-length = 88
target-version = ['py311']

[tool.mypy]
python_version = "3.11"
strict = true
warn_return_any = true
warn_unused_configs = true
disallow_untyped_defs = true
ignore_missing_imports = true

[tool.ruff]
target-version = "py311"
line-length = 88
select = ["E", "W", "F", "I", "B", "C4", "UP"]

[tool.pytest.ini_options]
testpaths = ["tests"]
python_files = ["test_*.py"]
addopts = "-ra -q --asyncio-mode=auto"
asyncio_mode = "auto"
```

### Architecture Layers

**1. Routers Layer** (`src/routers/`)

- FastAPI route handlers
- Request validation
- Response formatting
- HTTP status codes
- OpenAPI documentation

**2. Services Layer** (`src/services/`)

- Business logic
- BuildingMOTIF SDK wrapper
- Domain operations
- Error translation
- Transaction management

**3. Adapters Layer** (`src/adapters/`)

- BuildingMOTIF SDK integration
- RDF graph operations
- Template loading
- SHACL validation
- Database abstraction

**4. DTOs Layer** (`src/dto/`)

- Pydantic models for validation
- Request models
- Response models
- RDF → DTO conversion
- Epic 1 DTO structure preservation

**5. Config Layer** (`src/config/`)

- Environment variables
- BuildingMOTIF configuration
- Database settings
- CORS configuration

**6. Utils Layer** (`src/utils/`)

- Error handlers
- Logging utilities
- Common helpers

### BuildingMOTIF Integration Pattern

**Adapter Pattern Example:**

```python
from buildingmotif import BuildingMOTIF
from buildingmotif.dataclasses import Library
from typing import Optional


class BuildingMOTIFAdapter:
    """Adapter for BuildingMOTIF SDK integration."""

    def __init__(self, db_path: str = "buildingmotif.db"):
        """
        Initialize BuildingMOTIF SDK.

        Args:
            db_path: Path to SQLite database for RDF storage
        """
        self.bm = BuildingMOTIF(db_path)
        self._ashrae_223p_library: Optional[Library] = None

    def load_ashrae_223p_library(self) -> Library:
        """
        Load ASHRAE 223P library from BuildingMOTIF.

        Returns:
            ASHRAE 223P library with templates

        Raises:
            RuntimeError: When library loading fails
        """
        if self._ashrae_223p_library is None:
            try:
                # Load from BuildingMOTIF packaged libraries
                self._ashrae_223p_library = self.bm.load_library(
                    "ashrae/223p"
                )
            except Exception as e:
                raise RuntimeError(f"Failed to load 223P library: {e}")
        return self._ashrae_223p_library

    def get_system_templates(self) -> list[dict]:
        """
        Get all system (equipment type) templates.

        Returns:
            List of system template dictionaries
        """
        library = self.load_ashrae_223p_library()
        templates = []

        for template in library.get_templates():
            if template.template_type == "system":
                templates.append({
                    "id": template.id,
                    "name": template.name,
                    "description": template.description,
                })

        return templates
```

### DTO Conversion Pattern

**RDF → Domain → DTO Conversion:**

```python
from pydantic import BaseModel, Field
from typing import Optional


class SystemTypeDTO(BaseModel):
    """System (equipment) type DTO matching Epic 1 structure."""

    value: str = Field(..., description="System type identifier")
    label: str = Field(..., description="Human-readable label")
    description: Optional[str] = Field(
        None, description="System description"
    )

    @classmethod
    def from_rdf(cls, template: dict) -> "SystemTypeDTO":
        """
        Convert BuildingMOTIF template to DTO.

        Args:
            template: Template dictionary from BuildingMOTIF

        Returns:
            SystemTypeDTO instance
        """
        return cls(
            value=template["id"],
            label=template["name"],
            description=template.get("description"),
        )


class SemanticEquipmentDTO(BaseModel):
    """Semantic equipment mapping DTO matching Epic 1 structure."""

    equipment_type: str = Field(..., description="223P equipment type")
    device_type: str = Field(..., description="223P device type")
    observable_property: str = Field(..., description="223P property")
    space_id: Optional[str] = Field(None, description="Associated space ID")
    point_id: str = Field(..., description="BACnet point identifier")

    @classmethod
    def from_domain(cls, mapping: dict) -> "SemanticEquipmentDTO":
        """
        Convert domain mapping to DTO.

        Args:
            mapping: Domain mapping dictionary

        Returns:
            SemanticEquipmentDTO instance
        """
        return cls(
            equipment_type=mapping["equipment_type"],
            device_type=mapping["device_type"],
            observable_property=mapping["observable_property"],
            space_id=mapping.get("space_id"),
            point_id=mapping["point_id"],
        )
```

### Error Handling Pattern

**Exception Mapping:**

```python
from fastapi import HTTPException, status
from typing import Any


class BuildingMOTIFError(Exception):
    """Base exception for BuildingMOTIF operations."""
    pass


class TemplateNotFoundError(BuildingMOTIFError):
    """Raised when template is not found."""
    pass


class ValidationError(BuildingMOTIFError):
    """Raised when validation fails."""
    pass


def handle_buildingmotif_error(error: Exception) -> HTTPException:
    """
    Convert BuildingMOTIF exceptions to HTTP exceptions.

    Args:
        error: BuildingMOTIF exception

    Returns:
        HTTPException with appropriate status code
    """
    if isinstance(error, TemplateNotFoundError):
        return HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail=str(error),
        )
    elif isinstance(error, ValidationError):
        return HTTPException(
            status_code=status.HTTP_422_UNPROCESSABLE_ENTITY,
            detail=str(error),
        )
    else:
        return HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Internal server error: {str(error)}",
        )
```

### Router Organization Pattern

**Example Router:**

```python
from fastapi import APIRouter, HTTPException, Depends
from typing import Annotated

from ..dto.templates_dto import SystemTypeDTO, DeviceTypeDTO, PropertyDTO
from ..services.templates_service import TemplatesService
from ..utils.error_handlers import handle_buildingmotif_error

router = APIRouter(
    prefix="/api/223p/templates",
    tags=["ASHRAE 223P Templates"],
)


def get_templates_service() -> TemplatesService:
    """Dependency injection for templates service."""
    return TemplatesService()


@router.get(
    "/systems",
    response_model=list[SystemTypeDTO],
    summary="Get all ASHRAE 223P system templates",
)
async def get_system_templates(
    service: Annotated[TemplatesService, Depends(get_templates_service)],
) -> list[SystemTypeDTO]:
    """
    Retrieve all ASHRAE 223P system (equipment) templates.

    Returns:
        List of system template DTOs

    Raises:
        HTTPException: When BuildingMOTIF operation fails
    """
    try:
        return await service.get_system_templates()
    except Exception as e:
        raise handle_buildingmotif_error(e)


@router.get(
    "/devices",
    response_model=list[DeviceTypeDTO],
    summary="Get all ASHRAE 223P device templates",
)
async def get_device_templates(
    service: Annotated[TemplatesService, Depends(get_templates_service)],
) -> list[DeviceTypeDTO]:
    """
    Retrieve all ASHRAE 223P device templates.

    Returns:
        List of device template DTOs

    Raises:
        HTTPException: When BuildingMOTIF operation fails
    """
    try:
        return await service.get_device_templates()
    except Exception as e:
        raise handle_buildingmotif_error(e)
```

### Service Layer Pattern

**Example Service:**

```python
from typing import Optional

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..dto.templates_dto import SystemTypeDTO, DeviceTypeDTO


class TemplatesService:
    """Service for managing ASHRAE 223P templates."""

    def __init__(self):
        self.adapter = BuildingMOTIFAdapter()

    async def get_system_templates(self) -> list[SystemTypeDTO]:
        """
        Get all system templates from BuildingMOTIF.

        Returns:
            List of system template DTOs
        """
        templates = self.adapter.get_system_templates()
        return [SystemTypeDTO.from_rdf(t) for t in templates]

    async def get_device_templates(self) -> list[DeviceTypeDTO]:
        """
        Get all device templates from BuildingMOTIF.

        Returns:
            List of device template DTOs
        """
        templates = self.adapter.get_device_templates()
        return [DeviceTypeDTO.from_rdf(t) for t in templates]
```

### Testing Strategy

**Unit Test Example:**

```python
import pytest
from unittest.mock import Mock, patch

from src.services.templates_service import TemplatesService
from src.dto.templates_dto import SystemTypeDTO


@pytest.fixture
def mock_adapter():
    """Mock BuildingMOTIF adapter."""
    with patch(
        "src.services.templates_service.BuildingMOTIFAdapter"
    ) as mock:
        yield mock.return_value


@pytest.mark.asyncio
async def test_get_system_templates(mock_adapter):
    """Test getting system templates."""
    # Arrange
    mock_adapter.get_system_templates.return_value = [
        {
            "id": "vav-reheat",
            "name": "VAV with Reheat",
            "description": "Variable air volume with reheat",
        }
    ]

    service = TemplatesService()

    # Act
    result = await service.get_system_templates()

    # Assert
    assert len(result) == 1
    assert isinstance(result[0], SystemTypeDTO)
    assert result[0].value == "vav-reheat"
    assert result[0].label == "VAV with Reheat"
```

**Integration Test Example:**

```python
import pytest
from httpx import AsyncClient

from src.main import app


@pytest.mark.asyncio
async def test_get_system_templates_integration():
    """Test GET /api/223p/templates/systems endpoint."""
    async with AsyncClient(app=app, base_url="http://test") as client:
        response = await client.get("/api/223p/templates/systems")

    assert response.status_code == 200
    data = response.json()
    assert isinstance(data, list)
    assert len(data) > 0
    assert "value" in data[0]
    assert "label" in data[0]
```

### FastAPI Main Application

**File:** `apps/building-semantics-api-app/src/main.py`

```python
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from .routers import templates, spaces, mappings, validation
from .config.settings import get_settings

settings = get_settings()

app = FastAPI(
    title="Building Semantics API",
    description="FastAPI wrapper for BuildingMOTIF SDK - ASHRAE 223P",
    version="0.1.0",
    docs_url="/docs",
    redoc_url="/redoc",
    openapi_url="/openapi.json",
)

# CORS configuration for Designer app
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3003"],  # Designer app port
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Include routers
app.include_router(templates.router)
app.include_router(spaces.router)
app.include_router(mappings.router)
app.include_router(validation.router)


@app.get("/health", tags=["Health"])
async def health_check():
    """Health check endpoint."""
    return {"status": "healthy", "service": "building-semantics-api"}
```

### Development Setup

**Port Configuration:**

- Building Semantics API: `8000`
- Designer App: `3003`
- MQTT Proxy (Nginx): `3000`
- MQTT Broker (NanoMQ): `1883`

**Start Command:**

```bash
cd apps/building-semantics-api-app
PYTHONPATH=.:apps/building-semantics-api-app uvicorn src.main:app --reload --port 8000
```

**Integration with start-dev.sh:**

- Automatically starts with `pnpm dev`
- Captures PID for shutdown
- Logs prefixed with `[Semantics-API]`

### PNPM Scripts Integration

**Add to root `package.json`:**

```json
{
  "scripts": {
    "building-semantics:install": "cd apps/building-semantics-api-app && pip install -e '.[test,dev]'",
    "building-semantics:run": "cd apps/building-semantics-api-app && uvicorn src.main:app --reload --port 8000",
    "building-semantics:test": "cd apps/building-semantics-api-app && pytest tests/",
    "building-semantics:test:verbose": "cd apps/building-semantics-api-app && pytest tests/ -v",
    "building-semantics:typecheck": "cd apps/building-semantics-api-app && mypy src/",
    "building-semantics:lint": "cd apps/building-semantics-api-app && ruff check src/",
    "building-semantics:format": "cd apps/building-semantics-api-app && black src/ tests/"
  }
}
```

### Type Checking with mypy

**Configuration:**

```toml
[tool.mypy]
python_version = "3.11"
strict = true
warn_return_any = true
warn_unused_configs = true
disallow_untyped_defs = true
ignore_missing_imports = true
```

**Run type checking:**

```bash
pnpm building-semantics:typecheck
```

### OpenAPI Configuration

**Auto-generated OpenAPI spec:**

- URL: `http://localhost:8000/openapi.json`
- Swagger UI: `http://localhost:8000/docs`
- ReDoc: `http://localhost:8000/redoc`

**TypeScript Client Generation:**

- Use `openapi-generator` or `@hey-api/openapi-ts`
- Generate from `http://localhost:8000/openapi.json`
- Integrate into Designer build process (Story 2.2)

### Summary

**Foundation provides:**

- Complete FastAPI project structure
- BuildingMOTIF SDK integration patterns
- Type-safe DTO conversions
- Comprehensive error handling
- Test strategy (unit, integration, E2E)
- Type checking with mypy
- Development workflow integration
- OpenAPI specification generation

**Ready for Epic 2 implementation:**

- Story 2.1: OpenAPI spec design (pattern established)
- Story 2.2: TypeScript client generation (OpenAPI available)
- Story 2.3: Mock data endpoints (router pattern ready)
- Story 2.4: Designer integration (CORS + ports configured)
- Stories 2.5-2.10: BuildingMOTIF implementation (adapter pattern ready)

---

## React Query Hooks Analysis

**6 React Query hooks** (Simplified from 8 - removed 3, added 1):

| Hook                        | Service Called                         | Epic 2 Change                                           |
| --------------------------- | -------------------------------------- | ------------------------------------------------------- |
| `useTemplatesQuery()`       | `TemplatesService.getTemplates()`      | ✅ FastAPI: GET `/api/v1/223p/templates` (hierarchical) |
| `useMappingsQuery()`        | `MappingsService.getMappings()`        | ✅ FastAPI: GET `/api/v1/223p/mappings`                 |
| `useSaveMappingsMutation()` | `MappingsService.saveMappings()`       | ✅ FastAPI: POST `/api/v1/223p/mappings` (bulk save)    |
| `useSpacesQuery()`          | `SpacesService.listSpaces()`           | ✅ FastAPI: GET `/api/v1/223p/spaces`                   |
| `useCreateSpaceMutation()`  | `SpacesService.createSpace()`          | ✅ FastAPI: POST `/api/v1/223p/spaces`                  |
| `useAISuggestionQuery()`    | `aiSuggestionService.suggestMapping()` | ❌ NO CHANGE: Calls `/lib/ai` directly                  |

**Removed Hooks (replaced by simplified patterns):**

- ~~`useCreateMappingMutation()`~~ → Use `useSaveMappingsMutation()` with added mapping
- ~~`useUpdateMappingMutation()`~~ → Use `useSaveMappingsMutation()` with updated mapping
- ~~`useDeleteMappingMutation()`~~ → Use `useSaveMappingsMutation()` with filtered array

**Added Hook:**

- `useSaveMappingsMutation()` - Bulk save/replace pattern

**Summary:**

- **5 hooks** need FastAPI integration
- **1 hook** stays Designer-only (`useAISuggestionQuery`)
- **Total: 6 hooks** (down from 8)

---

## Storage Architecture - Epic 1 vs Epic 2

### Epic 1 (Current - sessionStorage)

```typescript
// Mappings
sessionStorage.setItem(`223p-mappings:${projectId}`, JSON.stringify(mappings));

// Spaces
sessionStorage.setItem(`223p-spaces:${projectId}`, JSON.stringify(spaces));

// Templates (static data)
// No storage - returned from mock service

// AI Suggestions (rule-based)
// No storage - computed on-the-fly
```

### Epic 2 (Target - FastAPI)

```typescript
// FastAPI-backed services
const mappings = await fetch(`/api/223p/mappings?projectId=${projectId}`);
const spaces = await fetch(`/api/223p/spaces?projectId=${projectId}`);
const templates = await fetch(`/api/223p/templates/systems`);
const validation = await fetch(`/api/223p/validate`, { method: "POST", body });

// Designer-only service (NO FastAPI)
const aiSuggestion = await aiLibrary.suggest(point); // Calls /lib/ai
```

**Backend Storage (FastAPI → BuildingMOTIF):**

- BuildingMOTIF uses **SQLite** for RDF graph storage
- SHACL validation rules from BuildingMOTIF library
- ASHRAE 223P templates from BuildingMOTIF YAML files

---

## Tech Debt - Story 2.0 Specification

### Story 2.0: Consolidate Service Naming and Interface Pattern

**Type:** Tech Debt (PREREQUISITE for Epic 2)

**Acceptance Criteria:**

1. **Create Missing Interface** - `I223PMappingsService`

   - Extract interface from `semanticMappingsApi` (6 methods)
   - Create mock implementation (`223p-mappings.mock.service.ts`)
   - Create API implementation (`223p-mappings.api.service.ts`)

2. **Rename FastAPI Services** with `I223P*Service` pattern (4 services):

   - `IBuildingMOTIFService` → `I223PTemplatesService`
   - `ISpaceService` → `I223PSpacesService`
   - `IValidationService` → `I223PValidationService`
   - _(NEW)_ `semanticMappingsApi` → `I223PMappingsService`

3. **NO CHANGE for Designer-only services**:

   - `IAISuggestionService` - Keep as-is (Designer-only, calls `/lib/ai`)

4. **Remove Duplication** - Merge `spaces223pApi` into `I223PSpacesService`

   - Delete `/api/spaces.api.ts`
   - Consolidate logic into `space.api.service.ts`

5. **Update All Imports** across codebase:

   - React Query hooks (7 hooks need updates, 1 unchanged)
   - UI components
   - Service registrations

6. **Update Tests** - All service tests pass with new names

7. **Update Documentation** - Epic 1 retrospective references

**Effort Estimate:** 2-3 hours

**Story File:** `story-2.0-consolidate-service-naming.md`

---

## File Structure - Epic 1 Implementation

```
apps/designer/src/domains/building-semantics/
├── adapters/ashrae-223p/
│   └── services/
│       ├── interfaces/
│       │   ├── buildingmotif.ts           → I223PTemplatesService (FastAPI)
│       │   └── ai-suggestion.ts           → IAISuggestionService (Designer-only)
│       ├── buildingmotif.mock.service.ts
│       ├── space.service.interface.ts     → I223PSpacesService (FastAPI)
│       ├── space.mock.service.ts
│       ├── validation.service.interface.ts → I223PValidationService (FastAPI)
│       ├── validation.mock.service.ts
│       └── ai-suggestion.mock.service.ts  (Designer-only)
├── api/
│   ├── mappings.api.ts                     → I223PMappingsService (FastAPI, NO INTERFACE)
│   ├── queries/
│   │   ├── use-mappings-query.ts
│   │   ├── use-templates-query.ts
│   │   ├── use-spaces-query.ts
│   │   └── use-ai-suggestion-query.ts     (Designer-only, NO CHANGE)
│   └── mutations/
│       ├── use-create-mapping-mutation.ts
│       ├── use-update-mapping-mutation.ts
│       ├── use-delete-mapping-mutation.ts
│       └── use-create-space-mutation.ts
└── view-models/
    └── mapping-popup.view-model.ts
```

---

## Key Architecture Patterns - Epic 1

### 1. **Service Interface Pattern**

```typescript
export interface I223PTemplatesService {
  getTemplates(): Promise<SystemType[]>;
}

// Mock implementation
export class TemplatesMockService implements I223PTemplatesService {
  async getTemplates(): Promise<SystemType[]> {
    return MOCK_SYSTEMS;
  }
}

// API implementation (Epic 2)
export class TemplatesApiService implements I223PTemplatesService {
  async getTemplates(): Promise<SystemType[]> {
    return fetch("/api/223p/templates/systems").then((r) => r.json());
  }
}
```

### 2. **Adapter Pattern** (`/adapters/ashrae-223p/`)

- Domain separation: 223P logic isolated
- Future extensibility: Add `/adapters/brick/`, `/adapters/haystack/`

### 3. **View Model Pattern**

- UI components use ViewModels, not DTOs directly
- Isolates UI from data layer changes

### 4. **React Query Hooks**

- Centralized data fetching
- Cache management
- Optimistic updates

---

## Epic 2 Changes Required

### Phase 1: Interface Validation (5 stories - Simplified Design)

**Story 2.0:** ✅ Consolidate service naming (PREREQUISITE)

- Rename 4 FastAPI services to `I223P*Service` pattern
- Create `I223PMappingsService` interface
- **NO CHANGE** to `IAISuggestionService`

**Story 2.1:** Create FastAPI app scaffolding

- Basic FastAPI setup with CORS
- Health endpoint
- Development integration with start-dev.sh

**Story 2.2:** Design OpenAPI specification

- **5 endpoints** across **3 services** (simplified from 14 across 4)
- Hierarchical templates (systems → devices → properties + spaceTypes)
- Bulk mappings save/replace (no individual CRUD)
- Essential spaces CRUD (list, create)
- camelCase serialization via Pydantic aliases
- URN identifier convention (`urn:223p:*`, `urn:bms:*`)
- Domain-scoped paths (`/api/v1/223p/*`)

**Story 2.3:** Generate TypeScript client

- Generate from OpenAPI spec
- **5 service functions** (TemplatesService, MappingsService, SpacesService)
- camelCase field verification
- Nested type structures
- Integrate with Designer build

**Story 2.4:** Implement mock endpoints

- **5 FastAPI endpoints** with static hierarchical data
- Mock hierarchical templates (VAV, AHU, FCU with nested devices/properties)
- Mock mappings (bulk pattern)
- Mock spaces (Office 101, Conference Room A)
- Explicit Pydantic aliases for camelCase serialization

**Story 2.5:** Integrate TypeScript client with Designer

- Update **5 React Query hooks** to call FastAPI
- Remove 3 obsolete hooks (individual mapping CRUD)
- Add 1 new hook (`useSaveMappingsMutation` for bulk save)
- **Keep 1 hook unchanged** (`useAISuggestionQuery` - Designer-only)
- Component updates for hierarchical filtering
- Replace sessionStorage with API calls
- Document Phase 1 limitations (static mock data)

### Phase 2: Real BuildingMOTIF Implementation (6 stories)

**Stories 2.5-2.10:** Implement real endpoints one by one

### Phase 3: AI Integration (2 stories)

**Stories 2.11-2.12:** Vercel AI SDK + Mem0 in `/apps/designer/src/lib/ai`

- **Designer-only** implementation
- No FastAPI endpoint
- `IAISuggestionService` calls `/lib/ai` directly

---

## Validation - Epic 1 DTOs Match BuildingMOTIF

✅ **Systems (Equipment Types)**: 8 templates

- Epic 1: `SystemType` enum (8 values)
- BuildingMOTIF: `systems.yml` (8 templates)
- **Match:** Perfect alignment

✅ **Devices**: 18 templates (Epic 1) vs 25 (BuildingMOTIF)

- Epic 1: `DeviceType` enum (18 values)
- BuildingMOTIF: `devices.yml` (25 templates)
- **Gap:** 7 missing devices (BTU meters, differential-sensor, etc.)
- **Decision:** Add on-demand when needed

✅ **Properties**: 24 templates (Epic 1) vs 26 (BuildingMOTIF)

- Epic 1: `ObservableProperty` enum (24 values)
- BuildingMOTIF: `properties.yml` (26 templates)
- **Gap:** 2 missing properties (vfd-speed, vfd-feedback)
- **Decision:** Add on-demand when needed

**Conclusion:** Epic 1 DTOs are **100% compatible** with BuildingMOTIF templates. Zero breaking changes required.

---

## Next Steps

**Task 1.2:** ✅ COMPLETE

**Task 1.3:** Generate Epic 2 Stories - ✅ COMPLETE (Simplified Design)

**Phase 1 Stories (2.0-2.5):** Interface validation - 5 stories + 1 tech debt

1. ✅ Story 2.0 - Consolidate service naming (tech debt prerequisite)
2. ✅ Story 2.1 - Create FastAPI app scaffolding
3. ✅ Story 2.2 - Design OpenAPI specification (5 endpoints, hierarchical, camelCase, URNs)
4. ✅ Story 2.3 - Generate TypeScript client (5 functions, camelCase fields)
5. ✅ Story 2.4 - Implement mock endpoints (hierarchical data, Pydantic aliases)
6. ✅ Story 2.5 - Integrate TypeScript client (5 hooks, bulk save pattern)

**Phase 2 Stories:** BuildingMOTIF SDK integration - TBD
**Phase 3 Stories:** AI integration (Designer-only) - TBD

**FastAPI Scope (Simplified):**

- **5 endpoints** across **3 services** (down from 14 across 4)
- Hierarchical templates
- Bulk mappings save/replace
- Essential spaces CRUD
- camelCase serialization via Pydantic aliases
- URN identifier convention

**Designer-only:** AI suggestions (Phase 3, no FastAPI endpoint)

---

**Document Status:** ✅ Complete (Updated 2025-11-09 with Simplified Design)
**Last Updated:** 2025-11-09
**Original:** 2025-11-06
**Updates:** Phase 1 simplification (14 → 5 endpoints), camelCase serialization, URN identifiers
