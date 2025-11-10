# Story 2.4: Implement FastAPI Mock Endpoints with Hierarchical Data

**Epic:** Epic 2 - BuildingMOTIF API Integration
**Phase:** Phase 1 - Interface-First Development & Validation
**Status:** pending
**Created:** 2025-11-06
**Complexity:** 2 (Small)
**Estimated Hours:** 2-3 hours

---

## User Story

**As a** developer,
**I want** all 5 FastAPI endpoints implemented with realistic hierarchical mock data,
**So that** I can validate the API contract with the Designer app before BuildingMOTIF integration.

---

## Context

**Problem:** Need working API endpoints for Designer app integration testing without BuildingMOTIF complexity.

**Solution:** Implement all 5 endpoints with **static hierarchical data**:

- Realistic ASHRAE 223P templates with nested structure (8 systems, each with devices and properties)
- Static mappings and spaces (no actual storage)
- Proper HTTP status codes (200, 201)
- camelCase JSON output via Pydantic aliases
- No BuildingMOTIF SDK yet

**Simplified Approach (YAGNI):**

- All endpoints return static data
- No storage needed
- No actual CRUD operations (Phase 2 will replace entirely)
- Just validate OpenAPI contract works

**Interface-First Validation:**

- Designer app can call real endpoints
- Verify request/response contracts match
- Test React Query integration
- Validate TypeScript client works end-to-end
- Phase 2 will replace with BuildingMOTIF (no migration needed)

---

## Acceptance Criteria

### 1. ✅ Templates Endpoint - Hierarchical Static Data

**Implementation location:** `src/routers/templates.py`

**Mock data source:** Static nested structure with realistic ASHRAE 223P templates

**GET `/api/v1/223p/templates`**

```python
async def get_templates() -> TemplatesResponseDTO:
    """Return hierarchical ASHRAE 223P templates with nested structure."""
    return MOCK_TEMPLATES  # Static data, hierarchical
```

**Expected response (sample):**

```json
{
  "systems": [
    {
      "id": "urn:223p:VAVReheatTerminalUnit",
      "label": "VAV with Reheat",
      "description": "Variable air volume terminal unit with electric reheat coil",
      "devices": [
        {
          "id": "urn:223p:Damper",
          "label": "Damper",
          "description": "Air damper actuator",
          "properties": [
            {
              "id": "urn:223p:DamperPosition",
              "label": "Damper Position",
              "propertyType": "quantifiable",
              "description": "Damper actuator position (0-100%)"
            },
            {
              "id": "urn:223p:AirFlowRate",
              "label": "Air Flow Rate",
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
      "label": "Office",
      "description": "Individual office space"
    }
  ]
}
```

### 2. ✅ Mappings Endpoints - Static Bulk Data

**Implementation location:** `src/routers/mappings.py`

**Static Data:** Predefined mappings dictionary

**GET `/api/v1/223p/mappings?projectId={id}` - Returns 200**

```python
async def get_mappings(project_id: str = Query(..., alias="projectId")) -> MappingsResponseDTO:
    """List all mappings (ignores projectId, returns static data)."""
    return MOCK_MAPPINGS
```

**POST `/api/v1/223p/mappings` - Returns 200**

```python
async def save_mappings(request: SaveMappingsRequestDTO) -> MappingsResponseDTO:
    """Save mappings (ignores request, returns static data)."""
    return MOCK_MAPPINGS
```

**Expected response (sample):**

```json
{
  "projectId": "mock-project",
  "mappings": {
    "device-1:ai-1": {
      "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit",
      "deviceTypeId": "urn:223p:Damper",
      "propertyId": "urn:223p:DamperPosition",
      "spaceId": "urn:bms:PhysicalSpace:room-101"
    },
    "device-1:ai-2": {
      "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit",
      "deviceTypeId": "urn:223p:Sensor",
      "propertyId": "urn:223p:Temperature-Sensor",
      "spaceId": "urn:bms:PhysicalSpace:room-101"
    }
  }
}
```

### 3. ✅ Spaces Endpoints - Static List

**Implementation location:** `src/routers/spaces.py`

**Static Data:** Predefined array of space instances

**GET `/api/v1/223p/spaces?projectId={id}` - Returns 200**

```python
async def list_spaces(project_id: str = Query(..., alias="projectId")) -> list[SpaceInstanceDTO]:
    """List all spaces (ignores projectId, returns static data)."""
    return MOCK_SPACES
```

**POST `/api/v1/223p/spaces` - Returns 201**

```python
@router.post("", response_model=SpaceInstanceDTO, status_code=201)
async def create_space(request: CreateSpaceRequestDTO) -> SpaceInstanceDTO:
    """Create space (ignores request, returns first static space)."""
    return MOCK_SPACES[0]
```

**Expected response (sample):**

```json
[
  {
    "id": "urn:bms:PhysicalSpace:room-101",
    "spaceTypeId": "urn:223p:Office",
    "label": "Room 101 - John's Office",
    "createdAt": "2025-01-01T00:00:00Z"
  },
  {
    "id": "urn:bms:PhysicalSpace:conf-room-a",
    "spaceTypeId": "urn:223p:ConferenceRoom",
    "label": "Conference Room A",
    "createdAt": "2025-01-01T00:00:00Z"
  }
]
```

### 4. ✅ Mock Data Constants File

**Create:** `src/data/mock_templates.py`

**Purpose:** Single file with all hierarchical ASHRAE 223P template data

**Content (simplified - expand during implementation):**

```python
"""Mock ASHRAE 223P templates for Phase 1 testing.

This file contains static hierarchical template data with embedded relationships.
All DTOs use explicit Pydantic aliases (snake_case → camelCase in JSON).
"""

from ..dto.templates_dto import (
    TemplatesResponseDTO,
    TemplateSystemDTO,
    TemplateDeviceDTO,
    TemplatePropertyDTO,
    SpaceTypeDTO
)
from ..dto.mappings_dto import SemanticMappingDTO, MappingsResponseDTO
from ..dto.spaces_dto import SpaceInstanceDTO

# Hierarchical template mock data with full nesting (8 systems)
MOCK_TEMPLATES = TemplatesResponseDTO(
    systems=[
        TemplateSystemDTO(
            id="urn:223p:VAVReheatTerminalUnit",
            label="VAV with Reheat",
            description="Variable air volume terminal unit with electric reheat coil",
            devices=[
                TemplateDeviceDTO(
                    id="urn:223p:Damper",
                    label="Damper",
                    description="Air damper actuator",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:223p:DamperPosition",
                            label="Damper Position",
                            property_type="quantifiable",
                            description="Damper actuator position (0-100%)"
                        ),
                        TemplatePropertyDTO(
                            id="urn:223p:AirFlowRate",
                            label="Air Flow Rate",
                            property_type="quantifiable"
                        )
                    ]
                ),
                TemplateDeviceDTO(
                    id="urn:223p:Sensor",
                    label="Temperature Sensor",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:223p:Temperature-Sensor",
                            label="Air Temperature",
                            property_type="quantifiable"
                        )
                    ]
                )
            ]
        ),
        # Add 7 more systems with nested devices and properties...
    ],
    space_types=[
        SpaceTypeDTO(
            id="urn:223p:Office",
            label="Office",
            description="Individual office space"
        ),
        SpaceTypeDTO(
            id="urn:223p:ConferenceRoom",
            label="Conference Room"
        ),
        # Add 5-8 more space types...
    ]
)

# Mock mappings (bulk format)
MOCK_MAPPINGS = MappingsResponseDTO(
    project_id="mock-project",
    mappings={
        "device-1:ai-1": SemanticMappingDTO(
            equipment_type_id="urn:223p:VAVReheatTerminalUnit",
            device_type_id="urn:223p:Damper",
            property_id="urn:223p:DamperPosition",
            space_id="urn:bms:PhysicalSpace:room-101"
        ),
        "device-1:ai-2": SemanticMappingDTO(
            equipment_type_id="urn:223p:VAVReheatTerminalUnit",
            device_type_id="urn:223p:Sensor",
            property_id="urn:223p:Temperature-Sensor",
            space_id="urn:bms:PhysicalSpace:room-101"
        )
    }
)

# Mock space instances
MOCK_SPACES: list[SpaceInstanceDTO] = [
    SpaceInstanceDTO(
        id="urn:bms:PhysicalSpace:room-101",
        space_type_id="urn:223p:Office",
        label="Room 101 - John's Office",
        created_at="2025-01-01T00:00:00Z"
    ),
    SpaceInstanceDTO(
        id="urn:bms:PhysicalSpace:conf-room-a",
        space_type_id="urn:223p:ConferenceRoom",
        label="Conference Room A",
        created_at="2025-01-01T00:00:00Z"
    )
]
```

_Note: Expand systems list to 8 total with realistic nested devices and properties during implementation_

### 5. ✅ All Endpoints Return Correct Status Codes

**Status codes:**

- Templates GET: 200
- Mappings GET: 200, POST: 200
- Spaces GET: 200, POST: 201

**Verification:**

```bash
# Start server
pnpm building-semantics:run

# Test templates (200)
curl -i http://localhost:8000/api/v1/223p/templates  # 200 OK

# Test mappings (200)
curl -i "http://localhost:8000/api/v1/223p/mappings?projectId=test"  # 200 OK
curl -i -X POST http://localhost:8000/api/v1/223p/mappings -H "Content-Type: application/json" -d '{"projectId":"test","mappings":{}}'  # 200 OK

# Test spaces (200, 201)
curl -i "http://localhost:8000/api/v1/223p/spaces?projectId=test"  # 200 OK
curl -i -X POST http://localhost:8000/api/v1/223p/spaces -H "Content-Type: application/json" -d '{"projectId":"test","spaceTypeId":"urn:223p:Office","label":"Room 101"}'  # 201 Created
```

**Expected:** All return correct status codes

### 6. ✅ camelCase JSON Output Verified

**Verification:**

```bash
# Test that response uses camelCase
curl http://localhost:8000/api/v1/223p/mappings?projectId=test | jq

# Should see camelCase fields
{
  "projectId": "test",
  "mappings": {
    "device-1:ai-1": {
      "equipmentTypeId": "...",
      "deviceTypeId": "...",
      "propertyId": "...",
      "spaceId": "..."
    }
  }
}
```

**Expected:** JSON uses camelCase, not snake_case

### 7. ✅ Swagger UI Works

**Verification:** Open `http://localhost:8000/docs`

**Expected:**

- All 5 endpoints visible
- "Try it out" works for all endpoints
- Static data returned
- camelCase in response preview

### 8. ✅ Type Checking and Linting Pass

**Verification:**

```bash
pnpm building-semantics:typecheck  # mypy
pnpm building-semantics:lint        # ruff
```

**Expected:** No errors

---

## Verification Checklist

- [ ] All 5 endpoints implemented (return data, not 501)
- [ ] Templates endpoint returns hierarchical structure (8 systems with nested devices/properties)
- [ ] Mappings endpoints return static data with camelCase fields
- [ ] Spaces endpoints return static data with proper status codes (200, 201)
- [ ] Mock data constants file created (`src/data/mock_templates.py`)
- [ ] Proper status codes returned (200, 201)
- [ ] camelCase JSON verified manually
- [ ] Swagger UI displays all endpoints
- [ ] "Try it out" in Swagger works for all endpoints
- [ ] Type checking passes (mypy)
- [ ] Linting passes (ruff)
- [ ] No storage code
- [ ] No CRUD logic (just return static data)

---

## Implementation Guidance

### Overview: Simplified Static Data Approach

**Key Principle:** All endpoints return static data. No storage, no state, no CRUD logic.

**File Structure:**

```
src/
├── data/
│   └── mock_templates.py        # All static data (hierarchical)
├── routers/
│   ├── templates.py              # Return MOCK_TEMPLATES
│   ├── mappings.py               # Return MOCK_MAPPINGS
│   └── spaces.py                 # Return MOCK_SPACES
```

### Step 1: Create Mock Data Constants

**Create `src/data/mock_templates.py`:**

- All static data in one file
- Hierarchical structure (systems → devices → properties)
- MOCK_TEMPLATES (8 systems), MOCK_MAPPINGS (2-3), MOCK_SPACES (2-3)

### Step 2: Implement Templates Router (Simple)

**Update `src/routers/templates.py`:**

```python
from fastapi import APIRouter
from ..dto.templates_dto import TemplatesResponseDTO
from ..data.mock_templates import MOCK_TEMPLATES

router = APIRouter(
    prefix="/api/v1/223p/templates",
    tags=["ASHRAE 223P Templates"],
)

@router.get("", response_model=TemplatesResponseDTO)
async def get_templates() -> TemplatesResponseDTO:
    """Get all ASHRAE 223P templates with hierarchical structure."""
    return MOCK_TEMPLATES
```

### Step 3: Implement Mappings Router (Simplified)

**Update `src/routers/mappings.py`:**

```python
from fastapi import APIRouter, Query
from ..dto.mappings_dto import MappingsResponseDTO, SaveMappingsRequestDTO
from ..data.mock_templates import MOCK_MAPPINGS

router = APIRouter(
    prefix="/api/v1/223p/mappings",
    tags=["ASHRAE 223P Mappings"],
)

@router.get("", response_model=MappingsResponseDTO)
async def get_mappings(
    project_id: str = Query(..., alias="projectId")
) -> MappingsResponseDTO:
    """Get all mappings (ignores projectId, returns static data)."""
    return MOCK_MAPPINGS

@router.post("", response_model=MappingsResponseDTO)
async def save_mappings(request: SaveMappingsRequestDTO) -> MappingsResponseDTO:
    """Bulk save mappings (ignores request, returns static data)."""
    return MOCK_MAPPINGS
```

### Step 4: Implement Spaces Router (Simplified)

**Update `src/routers/spaces.py`:**

```python
from fastapi import APIRouter, Query
from ..dto.spaces_dto import SpaceInstanceDTO, CreateSpaceRequestDTO
from ..data.mock_templates import MOCK_SPACES

router = APIRouter(
    prefix="/api/v1/223p/spaces",
    tags=["ASHRAE 223P Spaces"],
)

@router.get("", response_model=list[SpaceInstanceDTO])
async def list_spaces(
    project_id: str = Query(..., alias="projectId")
) -> list[SpaceInstanceDTO]:
    """List all spaces (ignores projectId, returns static data)."""
    return MOCK_SPACES

@router.post("", response_model=SpaceInstanceDTO, status_code=201)
async def create_space(request: CreateSpaceRequestDTO) -> SpaceInstanceDTO:
    """Create space (ignores request, returns first static space)."""
    return MOCK_SPACES[0]
```

### Step 5: Test Endpoints

**Start server:**

```bash
pnpm building-semantics:run
```

**Test templates (200):**

```bash
curl http://localhost:8000/api/v1/223p/templates | jq
```

**Test mappings (200):**

```bash
curl "http://localhost:8000/api/v1/223p/mappings?projectId=test" | jq
```

**Test spaces (200, 201):**

```bash
curl "http://localhost:8000/api/v1/223p/spaces?projectId=test" | jq
curl -X POST http://localhost:8000/api/v1/223p/spaces \
  -H "Content-Type: application/json" \
  -d '{"projectId":"test","spaceTypeId":"urn:223p:Office","label":"Room 101"}' | jq
```

### Step 6: Verify Swagger UI

Open: `http://localhost:8000/docs`

Test "Try it out" for all 5 endpoints

### Step 7: Verify camelCase Output

```bash
# Check templates response
curl http://localhost:8000/api/v1/223p/templates | jq '.systems[0].devices[0].properties[0]'

# Should see camelCase:
{
  "id": "urn:223p:DamperPosition",
  "label": "Damper Position",
  "propertyType": "quantifiable",    # ✓ camelCase
  "description": "..."
}
```

### Step 8: Run Type Checking

```bash
pnpm building-semantics:typecheck
pnpm building-semantics:lint
```

**Expected:** No errors

---

## Technical Notes

### Why Static Data Only? (YAGNI Principle)

**Phase 1 Goal:** Validate OpenAPI contract works end-to-end

**What We Need:**

- ✅ OpenAPI spec generates correctly
- ✅ TypeScript client generates from spec
- ✅ Designer app can call all 5 endpoints
- ✅ Request/response types match
- ✅ camelCase JSON works

**What We DON'T Need:**

- ❌ Working CRUD operations (Phase 2 will replace entirely)
- ❌ Storage (Phase 2 uses BuildingMOTIF DB)
- ❌ State management (Phase 2 uses BuildingMOTIF)
- ❌ Complex logic (Phase 2 uses BuildingMOTIF SDK)

**Savings:** ~5-6 hours of implementation time

**Phase 2:** Complete replacement with BuildingMOTIF SDK (no migration needed)

### Mock Data Realism

**ASHRAE 223P templates must be realistic:**

- Use actual 223P terminology
- Equipment types from 223P ontology
- Device types from 223P vocabulary
- Observable properties from 223P standard
- Hierarchical relationships match ontology

**Why?**

- Designer UI displays these to users
- Must match BuildingMOTIF library templates
- Phase 2 replacement seamless

### Hierarchical Structure Benefits

**Single API call gets everything:**

```typescript
const templates = await getTemplates();

// Navigate naturally
const vavSystem = templates.systems.find((s) => s.id.includes("VAV"));
const damper = vavSystem.devices.find((d) => d.id.includes("Damper"));
const position = damper.properties.find((p) => p.id.includes("Position"));
```

**No separate lookups needed!**

### camelCase via Pydantic Aliases

**Automatic conversion:**

```python
# Python DTO
equipment_type_id: str = Field(..., serialization_alias="equipmentTypeId")

# JSON output
{"equipmentTypeId": "urn:223p:VAVReheatTerminalUnit"}

# TypeScript (auto-generated)
interface SemanticMapping {
  equipmentTypeId: string  // ✓ Matches
}
```

**No manual conversion in Designer!**

### Phase 1 Behavior: Request Data Ignored

**Important for testing:**

All POST endpoints in Phase 1 **ignore request body** and return static responses:

**Example - POST `/api/v1/223p/mappings`:**

- Receives: Full mappings object
- Ignores: All request data
- Returns: MOCK_MAPPINGS (static)

**Why This Approach?**

- Phase 1 goal: Validate OpenAPI contract (types match, endpoints work)
- Not Phase 1 goal: Functional CRUD operations
- Phase 2: BuildingMOTIF SDK will handle requests properly

**Testing Strategy:**

- ✅ Verify endpoint is reachable (200/201 status)
- ✅ Verify response matches expected DTO structure
- ✅ Verify TypeScript types align with JSON
- ❌ Don't expect data to reflect request (will be static)
- ❌ Don't expect persistence across calls

---

## Prerequisites

**Story Dependencies:**

- Story 2.0: Consolidate service naming (complete)
- Story 2.1: Create FastAPI app scaffolding (complete)
- Story 2.2: Design OpenAPI specification (complete)
- Story 2.3: Generate TypeScript client (complete)

**Reason:** Need router stubs and DTOs defined.

---

## Dependencies

**Stories that depend on this:**

- Story 2.5: Integrate TypeScript client (needs working endpoints to call)

---

## Definition of Done

- [ ] All 5 endpoints implemented with static data (not 501)
- [ ] Templates endpoint returns hierarchical ASHRAE 223P data (8 systems)
- [ ] Mappings endpoints return static data with camelCase fields
- [ ] Spaces endpoints return static data with proper status codes
- [ ] Mock data constants file created (`src/data/mock_templates.py`)
- [ ] Proper status codes (200, 201)
- [ ] camelCase JSON verified
- [ ] No storage code
- [ ] No CRUD logic
- [ ] Swagger UI accessible and functional
- [ ] "Try it out" works for all endpoints
- [ ] Type checking passes (mypy)
- [ ] Linting passes (ruff)
- [ ] Server starts without errors
- [ ] Code follows project conventions
- [ ] Files committed to git with message: "Epic 2 Story 2.4: Implement FastAPI mock endpoints with hierarchical static data"

---

## References

- **Tech Spec Review:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/tech-spec-review.md`
  - Coding Standards Python (lines 308-397)
- **Phase Breakdown:** `/docs/feature-development/ashrae-223p-ai-g36-integration/epic2/epic-2-phase-breakdown.md`
  - Phase 1: Story 2.4
- **Story 2.2:** OpenAPI specification with endpoint definitions
- **ASHRAE 223P:** https://github.com/NREL/BuildingMOTIF/tree/develop/libraries/ashrae/223p
