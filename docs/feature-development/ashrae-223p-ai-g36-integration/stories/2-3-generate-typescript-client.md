# Story 2.3: Generate TypeScript Client from OpenAPI Specification

**Epic:** Epic 2 - BuildingMOTIF API Integration
**Phase:** Phase 1 - Interface-First Development & Validation
**Status:** pending
**Created:** 2025-11-06
**Complexity:** 2 (Small)
**Estimated Hours:** 2-3 hours

---

## User Story

**As a** developer,
**I want** a type-safe TypeScript client auto-generated from the OpenAPI specification,
**So that** the Designer app can call FastAPI endpoints with full type safety and contract validation.

---

## Context

**Problem:** Need type-safe API client in Designer app that matches FastAPI OpenAPI spec exactly.

**Solution:** Use `@hey-api/openapi-ts` to generate TypeScript client from `/openapi.json` endpoint with:

- Type-safe interfaces matching Pydantic DTOs (with camelCase fields)
- API client functions for all 5 endpoints
- Hierarchical template types
- Request/response validation
- Integration with Designer build process

**Why `@hey-api/openapi-ts`?**

- Modern TypeScript-first generator
- Generates fetch-based clients (no axios dependency)
- Excellent type inference
- Active maintenance
- Works with OpenAPI 3.1.0
- Respects camelCase from Pydantic aliases

**Alternative considered**: `openapi-typescript-codegen` - rejected (less active, axios dependency)

---

## Acceptance Criteria

### 1. ✅ `@hey-api/openapi-ts` Installed in Designer App

**Install generator:**

```bash
cd apps/designer
pnpm add -D @hey-api/openapi-ts
```

**Verify installation:**

```bash
pnpm list @hey-api/openapi-ts
```

**Expected:** Package installed in `devDependencies`

### 2. ✅ OpenAPI Client Generation Script Added

**Add to `apps/designer/package.json`:**

```json
{
  "scripts": {
    "generate:api-client": "openapi-ts --input http://localhost:8000/openapi.json --output ./src/domains/building-semantics/api/generated --client fetch"
  }
}
```

**Script breakdown:**

- `--input http://localhost:8000/openapi.json` - OpenAPI spec from running FastAPI server
- `--output ./src/domains/building-semantics/api/generated` - Output directory
- `--client fetch` - Use native fetch (no axios)

### 3. ✅ Generated Client Directory Structure

**Output location:**

```
apps/designer/src/domains/building-semantics/api/generated/
├── index.ts                          # Main export
├── types.gen.ts                      # All TypeScript types from Pydantic models
├── services.gen.ts                   # API service functions
└── core/                             # Runtime utilities
    ├── ApiError.ts
    ├── ApiRequestOptions.ts
    ├── ApiResult.ts
    ├── CancelablePromise.ts
    └── request.ts
```

### 4. ✅ Generated TypeScript Types Match Pydantic DTOs

**Hierarchical Template Types:**

```typescript
export interface TemplateProperty {
  id: string;
  label: string;
  propertyType: "quantifiable" | "enumerated";
  description?: string;
}

export interface TemplateDevice {
  id: string;
  label: string;
  description?: string;
  properties: TemplateProperty[];
}

export interface TemplateSystem {
  id: string;
  label: string;
  description?: string;
  devices: TemplateDevice[];
}

export interface SpaceType {
  id: string;
  label: string;
  description?: string;
}

export interface TemplatesResponse {
  systems: TemplateSystem[];
  spaceTypes: SpaceType[];
}
```

**Mapping Types:**

```typescript
export interface SemanticMapping {
  equipmentTypeId: string;
  deviceTypeId: string;
  propertyId: string;
  spaceId?: string;
}

export interface MappingsResponse {
  projectId: string;
  mappings: Record<string, SemanticMapping>;
}

export interface SaveMappingsRequest {
  projectId: string;
  mappings: Record<string, SemanticMapping>;
}
```

**Space Types:**

```typescript
export interface SpaceInstance {
  id: string;
  spaceTypeId: string;
  label: string;
  createdAt: string;
}

export interface CreateSpaceRequest {
  projectId: string;
  spaceTypeId: string;
  label: string;
}
```

### 5. ✅ Generated API Service Functions (5 Total)

**Templates Service (1 function):**

```typescript
export class TemplatesService {
  /**
   * Get all ASHRAE 223P templates with hierarchical structure
   * @returns TemplatesResponse
   * @throws ApiError
   */
  static async getTemplates(): Promise<TemplatesResponse>;
}
```

**Mappings Service (2 functions):**

```typescript
export class MappingsService {
  /**
   * Get all semantic mappings for project
   * @param projectId Project identifier
   * @returns MappingsResponse
   * @throws ApiError
   */
  static async getMappings(projectId: string): Promise<MappingsResponse>;

  /**
   * Bulk save/replace all semantic mappings
   * @param requestBody SaveMappingsRequest
   * @returns MappingsResponse
   * @throws ApiError
   */
  static async saveMappings(
    requestBody: SaveMappingsRequest,
  ): Promise<MappingsResponse>;
}
```

**Spaces Service (2 functions):**

```typescript
export class SpacesService {
  /**
   * List all space instances for project
   * @param projectId Project identifier
   * @returns SpaceInstance[]
   * @throws ApiError
   */
  static async listSpaces(projectId: string): Promise<SpaceInstance[]>;

  /**
   * Create new space instance
   * @param requestBody CreateSpaceRequest
   * @returns SpaceInstance
   * @throws ApiError
   */
  static async createSpace(
    requestBody: CreateSpaceRequest,
  ): Promise<SpaceInstance>;
}
```

### 6. ✅ API Base URL Configuration

**Create `apps/designer/src/domains/building-semantics/api/config.ts`:**

```typescript
export const API_BASE_URL =
  process.env.NEXT_PUBLIC_API_BASE_URL || "http://localhost:8000";

export const API_CONFIG = {
  baseUrl: API_BASE_URL,
  timeout: 30000, // 30 seconds
  headers: {
    "Content-Type": "application/json",
  },
};
```

**Add to `.env.local` (Designer):**

```bash
NEXT_PUBLIC_API_BASE_URL=http://localhost:8000
```

### 7. ✅ Integration with Designer Build Process

**Add pre-build step to `apps/designer/package.json`:**

```json
{
  "scripts": {
    "prebuild": "pnpm generate:api-client",
    "build": "next build"
  }
}
```

**Benefit:** Auto-generates client before production builds

### 8. ✅ `.gitignore` Updated for Generated Files

**Add to `apps/designer/.gitignore`:**

```
# Generated API client
src/domains/building-semantics/api/generated/
```

**Why ignore?**

- Generated code, not source code
- Regenerated on every build
- Prevents merge conflicts

### 9. ✅ Type Checking Passes with Generated Client

**Verification:**

```bash
cd apps/designer
pnpm generate:api-client
pnpm typecheck
```

**Expected:** No TypeScript errors

### 10. ✅ Generated Client Exports Accessible

**Verify imports work:**

```typescript
import type {
  TemplatesResponse,
  TemplateSystem,
  TemplateDevice,
  TemplateProperty,
  SpaceType,
  SemanticMapping,
  MappingsResponse,
  SaveMappingsRequest,
  SpaceInstance,
  CreateSpaceRequest,
} from "@/domains/building-semantics/api/generated";

import {
  TemplatesService,
  MappingsService,
  SpacesService,
} from "@/domains/building-semantics/api/generated";
```

**Expected:** All imports resolve correctly

---

## Verification Checklist

- [ ] `@hey-api/openapi-ts` installed in Designer app
- [ ] `generate:api-client` script added to package.json
- [ ] FastAPI server running: `pnpm building-semantics:run`
- [ ] Client generation successful: `pnpm generate:api-client`
- [ ] Generated directory structure correct
- [ ] All 9 type interfaces generated with camelCase fields
- [ ] All 5 API service functions generated
- [ ] API base URL configuration created
- [ ] `.gitignore` updated
- [ ] TypeScript compiles: `pnpm typecheck`
- [ ] Generated imports work in test file

---

## Implementation Guidance

### Step 1: Install Generator

```bash
cd apps/designer
pnpm add -D @hey-api/openapi-ts
```

### Step 2: Add Generation Script

**Update `apps/designer/package.json`:**

```json
{
  "scripts": {
    "generate:api-client": "openapi-ts --input http://localhost:8000/openapi.json --output ./src/domains/building-semantics/api/generated --client fetch",
    "prebuild": "pnpm generate:api-client"
  }
}
```

### Step 3: Start FastAPI Server

**Terminal 1:**

```bash
pnpm building-semantics:run
```

**Wait for:** Server running on `http://localhost:8000`

### Step 4: Generate Client

**Terminal 2:**

```bash
cd apps/designer
pnpm generate:api-client
```

**Expected output:**

```
✔ Loading OpenAPI specification from http://localhost:8000/openapi.json
✔ Generating TypeScript types
✔ Generating API services
✔ Writing files to src/domains/building-semantics/api/generated
✔ Done in 2.3s
```

### Step 5: Inspect Generated Files

**Check generated types:**

```bash
cat src/domains/building-semantics/api/generated/types.gen.ts
```

**Verify types present:**

- `TemplatesResponse` (hierarchical structure)
- `TemplateSystem`, `TemplateDevice`, `TemplateProperty`
- `SpaceType`
- `SemanticMapping`
- `MappingsResponse`, `SaveMappingsRequest`
- `SpaceInstance`, `CreateSpaceRequest`

**Verify camelCase fields:**

```bash
# Should find camelCase
grep "equipmentTypeId" src/domains/building-semantics/api/generated/types.gen.ts

# Should NOT find snake_case
grep "equipment_type_id" src/domains/building-semantics/api/generated/types.gen.ts
```

### Step 6: Create API Configuration

**Create `src/domains/building-semantics/api/config.ts`:**

```typescript
export const API_BASE_URL =
  process.env.NEXT_PUBLIC_API_BASE_URL || "http://localhost:8000";

export const API_CONFIG = {
  baseUrl: API_BASE_URL,
  timeout: 30000,
  headers: {
    "Content-Type": "application/json",
  },
};
```

### Step 7: Update `.gitignore`

**Add to `apps/designer/.gitignore`:**

```
# Generated API client
src/domains/building-semantics/api/generated/
```

### Step 8: Test Type Checking

```bash
pnpm typecheck
```

**Expected:** No errors

### Step 9: Create Test Import File (Verification)

**Create `src/domains/building-semantics/api/__test-imports.ts`:**

```typescript
import type {
  TemplatesResponse,
  TemplateSystem,
  TemplateDevice,
  TemplateProperty,
  SpaceType,
  SemanticMapping,
  MappingsResponse,
  SaveMappingsRequest,
  SpaceInstance,
  CreateSpaceRequest,
} from "./generated";

import { TemplatesService, MappingsService, SpacesService } from "./generated";

// Type checking verification (hierarchical structure)
const templatesResponse: TemplatesResponse = {
  systems: [
    {
      id: "urn:223p:VAVReheatTerminalUnit",
      label: "VAV with Reheat",
      description: "Test",
      devices: [
        {
          id: "urn:223p:Damper",
          label: "Damper",
          properties: [
            {
              id: "urn:223p:DamperPosition",
              label: "Damper Position",
              propertyType: "quantifiable",
            },
          ],
        },
      ],
    },
  ],
  spaceTypes: [
    {
      id: "urn:223p:Office",
      label: "Office",
    },
  ],
};

// Mapping types verification (camelCase)
const mapping: SemanticMapping = {
  equipmentTypeId: "urn:223p:VAVReheatTerminalUnit",
  deviceTypeId: "urn:223p:Damper",
  propertyId: "urn:223p:DamperPosition",
  spaceId: "urn:bms:PhysicalSpace:room-101",
};

const mappingsResponse: MappingsResponse = {
  projectId: "project-1",
  mappings: {
    "device-1:ai-1": mapping,
  },
};

// Space types verification
const spaceInstance: SpaceInstance = {
  id: "urn:bms:PhysicalSpace:room-101",
  spaceTypeId: "urn:223p:Office",
  label: "Room 101",
  createdAt: "2025-01-01T00:00:00Z",
};

// Service verification
async function testServices() {
  const templates = await TemplatesService.getTemplates();
  const mappings = await MappingsService.getMappings("project-1");
  await MappingsService.saveMappings({
    projectId: "project-1",
    mappings: {},
  });
  const spaces = await SpacesService.listSpaces("project-1");
  await SpacesService.createSpace({
    projectId: "project-1",
    spaceTypeId: "urn:223p:Office",
    label: "Room 101",
  });
}

export {};
```

**Run:**

```bash
pnpm typecheck
```

**Expected:** All types resolve correctly

---

## Technical Notes

### Why Auto-Generate Instead of Manual Types?

**Benefits:**

1. **Single source of truth:** OpenAPI spec drives both FastAPI and TypeScript
2. **Zero drift:** Types always match API contract
3. **Refactoring safety:** Change Pydantic model → regenerate → TypeScript errors show breaking changes
4. **Maintenance:** No manual type updates needed

**Workflow:**

```
Pydantic DTO (Python) → OpenAPI spec → TypeScript types (auto-generated)
```

### Generator Options Explained

**Command:**

```bash
openapi-ts --input URL --output DIR --client fetch
```

**Options:**

- `--input` - OpenAPI spec URL or file path
- `--output` - Output directory for generated code
- `--client fetch` - Use native fetch API (vs axios/xhr)
- `--exportCore false` - Skip core utilities (optional optimization)
- `--exportServices` - Service method generation style (default: class methods)

### File Naming Convention

**Generated files use `.gen.ts` suffix:**

- `types.gen.ts` - Generated types
- `services.gen.ts` - Generated services

**Why `.gen.ts`?**

- Clear visual indicator: "This file is generated"
- Easy to exclude from code reviews
- Prevents accidental manual edits

### camelCase Field Names

**Pydantic aliases → TypeScript camelCase (automatic):**

**Python:**

```python
equipment_type_id: str = Field(..., serialization_alias="equipmentTypeId")
```

**Generated TypeScript:**

```typescript
equipmentTypeId: string;
```

**No conversion needed in Designer!** Fields match JavaScript conventions.

### Hierarchical Type Structure

**Nested types work perfectly:**

```typescript
// Templates response contains nested structure
interface TemplatesResponse {
  systems: TemplateSystem[]; // Each system has...
}

interface TemplateSystem {
  devices: TemplateDevice[]; // Each device has...
}

interface TemplateDevice {
  properties: TemplateProperty[]; // Each property has...
}
```

**Usage in Designer:**

```typescript
const templates = await getTemplates();

// Navigate hierarchy naturally
const vavSystem = templates.systems[0];
const damper = vavSystem.devices[0];
const position = damper.properties[0];
```

### Integration with React Query (Story 2.5)

**Generated client provides building blocks:**

```typescript
import { TemplatesService } from "./generated";

// Story 2.5 will wrap with React Query
export function useTemplatesQuery() {
  return useQuery({
    queryKey: ["templates"],
    queryFn: () => TemplatesService.getTemplates(), // Generated function
  });
}
```

### Error Handling

**Generated client throws typed errors:**

```typescript
import { ApiError } from "./generated/core";

try {
  await TemplatesService.getTemplates();
} catch (error) {
  if (error instanceof ApiError) {
    console.error(`API Error: ${error.status} - ${error.message}`);
  }
}
```

### Development Workflow

**Typical flow:**

1. Start FastAPI server: `pnpm building-semantics:run`
2. Make changes to Pydantic DTOs or endpoints
3. Regenerate client: `pnpm generate:api-client`
4. TypeScript compiler shows type errors if contract changed
5. Update Designer code to match new contract

---

## Prerequisites

**Story Dependencies:**

- Story 2.0: Consolidate service naming (complete)
- Story 2.1: Create FastAPI app scaffolding (complete)
- Story 2.2: Design OpenAPI specification (complete)

**Reason:** Need `/openapi.json` endpoint accessible for generation.

---

## Dependencies

**Stories that depend on this:**

- Story 2.4: Implement mock endpoints (validates generated types work)
- Story 2.5: Integrate TypeScript client (uses generated services in React Query hooks)

---

## Definition of Done

- [ ] `@hey-api/openapi-ts` installed in Designer
- [ ] `generate:api-client` script added to package.json
- [ ] FastAPI server running
- [ ] Client generation runs successfully
- [ ] All 9 type interfaces generated with camelCase fields
- [ ] All 5 API functions generated
- [ ] API configuration file created
- [ ] `.gitignore` updated
- [ ] `prebuild` script added for auto-generation
- [ ] TypeScript compiles without errors
- [ ] Test import file verifies all types/services accessible
- [ ] Generated files in correct directory structure
- [ ] Code follows project conventions
- [ ] Files committed to git with message: "Epic 2 Story 2.3: Generate TypeScript client from simplified OpenAPI spec with camelCase fields"

---

## References

- **Tech Spec Review:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/tech-spec-review.md`
  - TypeScript conventions (lines 399-436)
- **Phase Breakdown:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/epic-2-phase-breakdown.md`
  - Phase 1: Story 2.3
- **Story 2.2:** Design OpenAPI specification (prerequisite)
- **@hey-api/openapi-ts Documentation:** https://github.com/hey-api/openapi-ts
- **FastAPI OpenAPI:** https://fastapi.tiangolo.com/advanced/extending-openapi/
