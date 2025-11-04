# BuildingMotif Integration Specification

**Created**: October 24, 2025
**Status**: Phase 0 Complete - Phases 1-6 Need Iteration
**Authors**: Development Team
**Last Updated**: October 30, 2025

## 1. Executive Summary

### 1.1 Purpose

Integrate BuildingMotif SDK to provide ASHRAE 223P semantic modeling and SHACL validation capabilities for the BMS Supervisor Controller. This will enable:

- **ASHRAE 223P semantic tagging** of BACnet devices and points
- **G36 guideline sequences** that depend on validated 223P models
- **SHACL validation** to ensure data quality and completeness
- **Separation of concerns**: Designer handles UI/mapping, BuildingMotif handles storage/validation

### 1.2 Key Principles

- **223P is independent**: Can create 223P models without G36 sequences
- **G36 depends on 223P**: G36 sequence blocks require 223P points to function
- **BuildingMotif is backend-only**: No UI, only API for 223P storage + G36 validation
- **Designer owns the UX**: All mapping and visual programming happens in Designer
- **G36 stored in Designer**: Sequences stored in project files, NOT in BuildingMotif
- **SHACL validation**: Both 223P and G36 validated using SHACL rules

### 1.3 Architecture Decision

Create a new **FastAPI microservice** (`apps/bms-buildingmotif/`) that wraps the BuildingMotif Python SDK and exposes RESTful APIs for the Designer frontend.

**Schema Direction**: Pydantic (FastAPI) → OpenAPI → TypeScript client stubs

### 1.4 Out of Scope

**ASHRAE 231P CDL/CXF** is explicitly out of scope for this integration:

- No Modelica CDL support
- No CXF JSON-LD format
- No energy simulation integration
- No formal verification
- May be added in future phases when standard matures and libraries exist

## 2. Refactoring Tasks (Phase 0 - Do First)

### 2.1 Move bms-schemas into Designer App

**Problem**: The `packages/bms-schemas/` package is only used by Designer app. It's not truly "shared" - the generated Python files are dead code never imported anywhere.

**Solution**: Move schema definitions into Designer app as internal schemas.

**Tasks**:

```bash
# 1. Move package
mv packages/bms-schemas apps/designer/src/lib/schemas

# 2. Update package.json imports in Designer
# Change: "bms-schemas" → "@/lib/schemas"

# 3. Remove from pnpm workspace
# Edit pnpm-workspace.yaml - remove bms-schemas

# 4. Update documentation
# CLAUDE.md, README.md - reflect schemas are Designer-internal
```

**Files to Update**:

- `apps/designer/package.json` - remove bms-schemas dependency
- `apps/designer/src/**/*.ts` - update imports
- `pnpm-workspace.yaml` - remove packages/bms-schemas
- `CLAUDE.md` - update schema documentation
- `README.md` - update architecture diagrams

### 2.2 Remove Unused Python Generation

**Problem**: bms-schemas generates Python files that are never used.

**Tasks**:

```bash
# 1. Remove Python files
rm -rf apps/designer/src/lib/schemas/python/

# 2. Remove Python generation scripts
# Delete generate:python from package.json
# Update generate-all.js to skip Python step

# 3. Remove Python dependencies
# Edit pyproject.toml - remove datamodel-code-generator

# 4. Fix/remove broken integration test
# Delete or rewrite integration-tests/test-e2e-schema.js
```

**Justification**: Designer is TypeScript-only. BuildingMotif will define its own Pydantic models independently.

## 3. Architecture Overview

### 3.1 System Components

```
┌─────────────────────────────────────────────────────────┐
│              Designer App (Next.js)                     │
│                                                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │  Feature 1: ASHRAE 223P Mapping                  │  │
│  │  - BACnet discovery                              │  │
│  │  - 223P equipment models (UI)                    │  │
│  │  - Point mapping forms                           │  │
│  │  - Independent of G36                            │  │
│  │  - Fetches from BuildingMotif                    │  │
│  └────────────────────┬─────────────────────────────┘  │
│                       │                                 │
│                       ↓                                 │
│  ┌──────────────────────────────────────────────────┐  │
│  │  Feature 2: G36 Sequence Blocks                  │  │
│  │  - Visual programming blocks                     │  │
│  │  - Special blocks (like AND, OR, etc.)           │  │
│  │  - Link to 223P points via dropdowns             │  │
│  │  - Requires 223P points to exist                 │  │
│  │  - STORED IN PROJECT FILES (not BuildingMotif)   │  │
│  └──────────────────────────────────────────────────┘  │
│                                                         │
│              TypeScript Client                          │
│           (Generated from OpenAPI)                      │
└───────────────────────────┬─────────────────────────────┘
                            │
                            │ REST API
                            ↓
┌─────────────────────────────────────────────────────────┐
│         BuildingMotif API (FastAPI)                     │
│                                                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │  BuildingMotif SDK Wrapper                       │  │
│  │  - Store 223P equipment models (RDF)             │  │
│  │  - SHACL validation (223P)                       │  │
│  │  - SHACL validation (G36 → 223P dependencies)    │  │
│  │  - NO G36 storage (validation only)              │  │
│  └──────────────────────────────────────────────────┘  │
│                                                         │
│                     Database                            │
│                  (RDF Graph Store)                      │
│                 (223P models only)                      │
└─────────────────────────────────────────────────────────┘
```

### 3.2 Data Flow

**Flow 1: Create 223P Mapping (Independent)**

```
1. User discovers BACnet devices (Designer)
2. User creates 223P equipment model via UI (Designer)
3. Designer → POST /api/v1/equipment (BuildingMotif)
4. BuildingMotif stores 223P in RDF graph
5. BuildingMotif → POST /api/v1/validate/223p (SHACL)
6. BuildingMotif → Designer (validation results)
7. Designer displays success/errors
```

**Flow 2: Create G36 Sequence (Requires 223P)**

```
1. User creates G36 VAV cooling block (Designer - visual)
2. User links G36 inputs to 223P points (Designer - dropdowns)
3. Designer stores sequence in project file (local JSON)
4. User clicks "Validate Sequence"
5. Designer → POST /api/v1/validate/g36 (BuildingMotif)
   - Sends G36 JSON + equipment_id
   - BuildingMotif converts G36 → temp RDF
   - BuildingMotif loads 223P RDF from database
   - BuildingMotif runs SHACL validation
   - BuildingMotif returns errors (does NOT store G36)
6. Designer displays validation results
7. If valid → enable deployment to BMS IoT App
```

**Key Difference**: G36 sequences are NEVER stored in BuildingMotif. Only validation happens on the backend.

### 3.3 Schema Pipeline Direction

**Designer Schemas (Internal)**:

```
Zod → TypeScript (no external sharing)
```

**BuildingMotif API**:

```
Pydantic → OpenAPI Spec → TypeScript Client Stubs
```

**Generation Command**:

```bash
cd apps/designer
npx openapi-typescript http://localhost:8000/openapi.json \
  -o src/lib/api/buildingmotif-types.ts
```

## 4. API Endpoints

### 4.1 Equipment & 223P Points

#### POST /api/v1/equipment

Create ASHRAE 223P equipment model.

**Request**:

```json
{
  "name": "VAV-101",
  "type": "VAV_Box",
  "location": "Floor 2, Zone A",
  "points": [
    {
      "name": "zone_temp",
      "type": "Sensor",
      "unit": "degreesFahrenheit",
      "bacnet": {
        "device_id": 123,
        "object_type": "analogInput",
        "object_instance": 1
      }
    },
    {
      "name": "damper_position",
      "type": "Sensor",
      "unit": "percent",
      "bacnet": {
        "device_id": 123,
        "object_type": "analogInput",
        "object_instance": 2
      }
    },
    {
      "name": "cooling_valve_command",
      "type": "Actuator",
      "unit": "percent",
      "bacnet": {
        "device_id": 123,
        "object_type": "analogOutput",
        "object_instance": 1
      }
    }
  ]
}
```

**Response** (201 Created):

```json
{
  "id": "eq_abc123",
  "name": "VAV-101",
  "type": "VAV_Box",
  "created_at": "2025-10-24T10:00:00Z",
  "validation_status": "pending"
}
```

#### GET /api/v1/equipment/{id}

Retrieve equipment model.

**Response** (200 OK):

```json
{
  "id": "eq_abc123",
  "name": "VAV-101",
  "type": "VAV_Box",
  "location": "Floor 2, Zone A",
  "points": [...],
  "validation_status": "valid",
  "last_validated": "2025-10-24T10:01:00Z"
}
```

#### PUT /api/v1/equipment/{id}

Update equipment model.

#### DELETE /api/v1/equipment/{id}

Delete equipment model.

#### POST /api/v1/equipment/{id}/points

Add points to existing equipment.

**Request**:

```json
{
  "points": [
    {
      "name": "zone_temp_setpoint",
      "type": "Setpoint",
      "unit": "degreesFahrenheit",
      "bacnet": {
        "device_id": 123,
        "object_type": "analogValue",
        "object_instance": 1
      }
    }
  ]
}
```

#### GET /api/v1/equipment/{id}/points

List all points for equipment.

### 4.2 Validation Endpoints

#### POST /api/v1/validate/223p

Validate ASHRAE 223P equipment model using SHACL.

**Request**:

```json
{
  "equipment_id": "eq_abc123"
}
```

**Response** (200 OK - Valid):

```json
{
  "valid": true,
  "equipment_id": "eq_abc123",
  "validated_at": "2025-10-24T10:03:00Z",
  "errors": []
}
```

**Response** (200 OK - Invalid):

```json
{
  "valid": false,
  "equipment_id": "eq_abc123",
  "validated_at": "2025-10-24T10:03:00Z",
  "errors": [
    {
      "severity": "error",
      "message": "Actuator point 'cooling_valve_command' must use Analog Output (AO), found Analog Input (AI)",
      "property": "points.cooling_valve_command.bacnet.object_type",
      "constraint": "sh:class"
    }
  ]
}
```

#### POST /api/v1/validate/g36

Validate G36 sequence references valid 223P points using SHACL.

**Important**: This endpoint does NOT store the G36 sequence. It only validates it against the 223P equipment model.

**How it works**:

1. Receives G36 sequence JSON from Designer
2. Converts G36 JSON → temporary RDF graph
3. Loads 223P equipment RDF from database
4. Runs SHACL validation (G36 + 223P graphs)
5. Returns validation results
6. Discards temporary G36 RDF (no storage)

**Request**:

```json
{
  "equipment_id": "eq_abc123",
  "g36_sequence": {
    "type": "g36.vav.cooling",
    "inputs": ["zone_temp", "zone_temp_setpoint", "damper_position"],
    "outputs": ["cooling_valve_command"]
  }
}
```

**Response** (200 OK - Valid):

```json
{
  "valid": true,
  "equipment_id": "eq_abc123",
  "validated_at": "2025-10-24T10:04:00Z",
  "errors": []
}
```

**Response** (200 OK - Invalid):

```json
{
  "valid": false,
  "equipment_id": "eq_abc123",
  "validated_at": "2025-10-24T10:04:00Z",
  "errors": [
    {
      "severity": "error",
      "message": "G36 sequence 'g36.vav.cooling' requires point 'zone_temp_setpoint' but it does not exist in equipment 'eq_abc123'",
      "property": "inputs",
      "constraint": "sh:exists"
    }
  ]
}
```

### 4.4 Discovery & Templates

#### GET /api/v1/templates/223p

List available ASHRAE 223P templates from BuildingMotif library.

**Response** (200 OK):

```json
{
  "templates": [
    {
      "id": "tpl_vav_box",
      "name": "VAV Box",
      "description": "Variable Air Volume terminal unit",
      "required_points": ["zone_temp", "damper_position", "cooling_valve"],
      "optional_points": ["zone_temp_setpoint", "occupancy"]
    },
    {
      "id": "tpl_ahu",
      "name": "Air Handling Unit",
      "description": "Central air handling unit",
      "required_points": ["supply_temp", "return_temp", "supply_fan"],
      "optional_points": ["outside_air_temp", "filter_status"]
    }
  ]
}
```

#### GET /api/v1/templates/g36

List available G36 sequence templates.

**Response** (200 OK):

```json
{
  "templates": [
    {
      "id": "g36_vav_cooling",
      "name": "VAV Cooling Sequence",
      "description": "G36 guideline VAV terminal cooling control",
      "required_inputs": ["zone_temp", "zone_temp_setpoint", "damper_position"],
      "required_outputs": ["cooling_valve_command"]
    }
  ]
}
```

## 5. Use Cases & User Stories

### 5.1 Use Case 1: Create 223P Mapping (Independent)

**Actor**: BMS Integrator
**Precondition**: BACnet devices discovered
**Goal**: Create semantic 223P model of building equipment

**Flow**:

1. User navigates to "Equipment" section in Designer
2. User clicks "Add Equipment"
3. User selects template "VAV Box" from 223P templates
4. User fills in equipment details:
   - Name: "VAV-101"
   - Location: "Floor 2, Zone A"
5. User maps BACnet points to 223P schema:
   - zone_temp → device:123, AI:1
   - damper_position → device:123, AI:2
   - cooling_valve_command → device:123, AO:1
6. User clicks "Save & Validate"
7. Designer sends POST /api/v1/equipment
8. BuildingMotif stores equipment in RDF graph
9. BuildingMotif validates with SHACL
10. Designer displays validation results:
    - ✅ "Equipment VAV-101 validated successfully"

**Alternate Flow (Validation Error)**:

9. SHACL validation fails: cooling_valve uses AI instead of AO
10. Designer displays error:
    - ❌ "Actuator must use Analog Output (AO), found Analog Input (AI)"
11. User corrects mapping: cooling_valve → AO:1
12. User clicks "Save & Validate" again
13. Validation passes

### 5.2 Use Case 2: Create G36 Sequence (Requires 223P)

**Actor**: Controls Engineer
**Precondition**: 223P equipment model exists and validated
**Goal**: Create G36 VAV cooling sequence

**Flow**:

1. User navigates to "Sequences" canvas in Designer
2. User drags "G36 VAV Cooling" block onto canvas
3. Designer shows configuration form:
   - Select Equipment: "VAV-101" (dropdown of validated equipment)
4. Designer populates available 223P points from selected equipment
5. User maps G36 inputs to 223P points (dropdowns):
   - zone_temp → VAV-101.zone_temp
   - zone_temp_setpoint → VAV-101.zone_temp_setpoint (Missing!)
   - damper_position → VAV-101.damper_position
6. Designer highlights missing point in red
7. User adds missing point to equipment:
   - Goes back to Equipment section
   - Adds "zone_temp_setpoint" point to VAV-101
8. Returns to Sequences canvas
9. User maps all inputs successfully
10. User clicks "Validate Sequence"
11. Designer sends POST /api/v1/g36/sequences
12. BuildingMotif validates G36 → 223P dependencies
13. Designer displays:
    - ✅ "G36 sequence validated successfully"
    - "Ready to deploy to BMS IoT App"

**Alternate Flow (Missing Required Points)**:

12. SHACL validation fails: G36 sequence missing required input
13. Designer displays error:
    - ❌ "G36 'vav.cooling' requires 'zone_temp_setpoint' but point not found"
14. User must add point to equipment first

## 6. Pseudo Test Cases (TDD)

### 6.1 Python Tests (BuildingMotif API)

```python
# apps/bms-buildingmotif/tests/test_equipment_api.py

import pytest
from fastapi.testclient import TestClient
from src.main import app

client = TestClient(app)


def test_create_223p_equipment_without_g36():
    """
    Test: Create standalone 223P equipment model
    Feature: Independent 223P mapping
    """
    equipment = {
        "name": "VAV-101",
        "type": "VAV_Box",
        "location": "Floor 2, Zone A",
        "points": [
            {
                "name": "zone_temp",
                "type": "Sensor",
                "unit": "degreesFahrenheit",
                "bacnet": {
                    "device_id": 123,
                    "object_type": "analogInput",
                    "object_instance": 1
                }
            },
            {
                "name": "damper_position",
                "type": "Sensor",
                "unit": "percent",
                "bacnet": {
                    "device_id": 123,
                    "object_type": "analogInput",
                    "object_instance": 2
                }
            },
            {
                "name": "cooling_valve_command",
                "type": "Actuator",
                "unit": "percent",
                "bacnet": {
                    "device_id": 123,
                    "object_type": "analogOutput",
                    "object_instance": 1
                }
            }
        ]
    }

    response = client.post("/api/v1/equipment", json=equipment)
    assert response.status_code == 201

    equipment_id = response.json()["id"]

    # Validate 223P model with SHACL
    validation = client.post("/api/v1/validate/223p", json={"equipment_id": equipment_id})
    assert validation.status_code == 200
    assert validation.json()["valid"] is True
    assert validation.json()["errors"] == []


def test_223p_validation_fails_bacnet_type_mismatch():
    """
    Test: SHACL catches BACnet object type mismatch
    Feature: 223P validation
    """
    equipment = {
        "name": "VAV-102",
        "type": "VAV_Box",
        "points": [
            {
                "name": "cooling_valve_command",
                "type": "Actuator",
                "unit": "percent",
                "bacnet": {
                    "device_id": 123,
                    "object_type": "analogInput",  # Wrong: should be analogOutput
                    "object_instance": 1
                }
            }
        ]
    }

    response = client.post("/api/v1/equipment", json=equipment)
    equipment_id = response.json()["id"]

    # SHACL validation should fail
    validation = client.post("/api/v1/validate/223p", json={"equipment_id": equipment_id})
    assert validation.status_code == 200
    assert validation.json()["valid"] is False
    assert len(validation.json()["errors"]) > 0
    assert "Actuator" in validation.json()["errors"][0]["message"]
    assert "analogOutput" in validation.json()["errors"][0]["message"]


def test_create_g36_sequence_with_valid_223p():
    """
    Test: Create G36 sequence referencing valid 223P points
    Feature: G36 depends on 223P
    """
    # Prerequisite: Create valid 223P equipment
    equipment = {
        "name": "VAV-103",
        "type": "VAV_Box",
        "points": [
            {"name": "zone_temp", "type": "Sensor", "unit": "degF",
             "bacnet": {"device_id": 123, "object_type": "analogInput", "object_instance": 1}},
            {"name": "zone_temp_setpoint", "type": "Setpoint", "unit": "degF",
             "bacnet": {"device_id": 123, "object_type": "analogValue", "object_instance": 1}},
            {"name": "damper_position", "type": "Sensor", "unit": "percent",
             "bacnet": {"device_id": 123, "object_type": "analogInput", "object_instance": 2}},
            {"name": "cooling_valve_command", "type": "Actuator", "unit": "percent",
             "bacnet": {"device_id": 123, "object_type": "analogOutput", "object_instance": 1}}
        ]
    }

    eq_response = client.post("/api/v1/equipment", json=equipment)
    equipment_id = eq_response.json()["id"]

    # Create G36 sequence
    g36_sequence = {
        "name": "VAV Cooling Sequence",
        "type": "g36.vav.cooling",
        "equipment_id": equipment_id,
        "inputs": [
            {"name": "zone_temp", "point_ref": "zone_temp"},
            {"name": "zone_temp_setpoint", "point_ref": "zone_temp_setpoint"},
            {"name": "damper_position", "point_ref": "damper_position"}
        ],
        "outputs": [
            {"name": "cooling_command", "point_ref": "cooling_valve_command"}
        ]
    }

    seq_response = client.post("/api/v1/g36/sequences", json=g36_sequence)
    assert seq_response.status_code == 201

    sequence_id = seq_response.json()["id"]

    # Validate G36 has all required 223P points
    validation = client.post("/api/v1/validate/g36", json={"sequence_id": sequence_id})
    assert validation.status_code == 200
    assert validation.json()["valid"] is True


def test_g36_validation_fails_missing_223p_points():
    """
    Test: G36 validation fails when required 223P points are missing
    Feature: G36 → 223P dependency validation
    """
    # Equipment missing "zone_temp_setpoint"
    equipment = {
        "name": "VAV-104",
        "type": "VAV_Box",
        "points": [
            {"name": "zone_temp", "type": "Sensor", "unit": "degF",
             "bacnet": {"device_id": 123, "object_type": "analogInput", "object_instance": 1}},
            {"name": "damper_position", "type": "Sensor", "unit": "percent",
             "bacnet": {"device_id": 123, "object_type": "analogInput", "object_instance": 2}}
            # Missing zone_temp_setpoint and cooling_valve_command
        ]
    }

    eq_response = client.post("/api/v1/equipment", json=equipment)
    equipment_id = eq_response.json()["id"]

    # Try to create G36 sequence that references missing points
    g36_sequence = {
        "type": "g36.vav.cooling",
        "equipment_id": equipment_id,
        "inputs": [
            {"name": "zone_temp", "point_ref": "zone_temp"},
            {"name": "zone_temp_setpoint", "point_ref": "zone_temp_setpoint"},  # Missing!
            {"name": "damper_position", "point_ref": "damper_position"}
        ],
        "outputs": [
            {"name": "cooling_command", "point_ref": "cooling_valve_command"}  # Missing!
        ]
    }

    seq_response = client.post("/api/v1/g36/sequences", json=g36_sequence)
    sequence_id = seq_response.json()["id"]

    # SHACL validation should fail
    validation = client.post("/api/v1/validate/g36", json={"sequence_id": sequence_id})
    assert validation.status_code == 200
    assert validation.json()["valid"] is False

    errors = validation.json()["errors"]
    assert len(errors) >= 2

    error_messages = [e["message"] for e in errors]
    assert any("zone_temp_setpoint" in msg for msg in error_messages)
    assert any("cooling_valve_command" in msg for msg in error_messages)


def test_complete_validation_end_to_end():
    """
    Test: Complete validation of 223P + G36 together
    Feature: Integrated validation
    """
    # Create complete valid equipment
    equipment = {
        "name": "VAV-105",
        "type": "VAV_Box",
        "points": [
            {"name": "zone_temp", "type": "Sensor", "unit": "degF",
             "bacnet": {"device_id": 123, "object_type": "analogInput", "object_instance": 1}},
            {"name": "zone_temp_setpoint", "type": "Setpoint", "unit": "degF",
             "bacnet": {"device_id": 123, "object_type": "analogValue", "object_instance": 1}},
            {"name": "damper_position", "type": "Sensor", "unit": "percent",
             "bacnet": {"device_id": 123, "object_type": "analogInput", "object_instance": 2}},
            {"name": "cooling_valve_command", "type": "Actuator", "unit": "percent",
             "bacnet": {"device_id": 123, "object_type": "analogOutput", "object_instance": 1}}
        ]
    }

    eq_response = client.post("/api/v1/equipment", json=equipment)
    equipment_id = eq_response.json()["id"]

    # Create complete valid G36 sequence
    g36_sequence = {
        "type": "g36.vav.cooling",
        "equipment_id": equipment_id,
        "inputs": [
            {"name": "zone_temp", "point_ref": "zone_temp"},
            {"name": "zone_temp_setpoint", "point_ref": "zone_temp_setpoint"},
            {"name": "damper_position", "point_ref": "damper_position"}
        ],
        "outputs": [
            {"name": "cooling_command", "point_ref": "cooling_valve_command"}
        ]
    }

    seq_response = client.post("/api/v1/g36/sequences", json=g36_sequence)
    sequence_id = seq_response.json()["id"]

    # Validate both together
    validation = client.post("/api/v1/validate/complete", json={
        "equipment_id": equipment_id,
        "sequence_id": sequence_id
    })

    assert validation.status_code == 200
    result = validation.json()
    assert result["valid"] is True
    assert result["223p_valid"] is True
    assert result["g36_valid"] is True
    assert result["errors"] == []


def test_get_223p_templates():
    """
    Test: Retrieve available 223P templates
    Feature: Template discovery
    """
    response = client.get("/api/v1/templates/223p")
    assert response.status_code == 200

    templates = response.json()["templates"]
    assert len(templates) > 0

    vav_template = next(t for t in templates if t["name"] == "VAV Box")
    assert "required_points" in vav_template
    assert "optional_points" in vav_template


def test_get_g36_templates():
    """
    Test: Retrieve available G36 sequence templates
    Feature: Template discovery
    """
    response = client.get("/api/v1/templates/g36")
    assert response.status_code == 200

    templates = response.json()["templates"]
    assert len(templates) > 0

    vav_cooling = next(t for t in templates if "vav.cooling" in t["id"])
    assert "required_inputs" in vav_cooling
    assert "required_outputs" in vav_cooling
```

### 6.2 TypeScript Tests (Designer Integration)

```typescript
// apps/designer/src/lib/api/__tests__/buildingmotif-client.test.ts

import { BuildingMotifClient } from "../buildingmotif-client";

describe("BuildingMotif API Integration", () => {
  const client = new BuildingMotifClient("http://localhost:8000");

  describe("223P Equipment Management", () => {
    it("should create and validate 223P equipment", async () => {
      const equipment = {
        name: "VAV-101",
        type: "VAV_Box",
        location: "Floor 2, Zone A",
        points: [
          {
            name: "zone_temp",
            type: "Sensor",
            unit: "degreesFahrenheit",
            bacnet: {
              device_id: 123,
              object_type: "analogInput",
              object_instance: 1,
            },
          },
        ],
      };

      const response = await client.createEquipment(equipment);
      expect(response.id).toBeDefined();

      const validation = await client.validate223P(response.id);
      expect(validation.valid).toBe(true);
    });

    it("should return validation errors for invalid equipment", async () => {
      const equipment = {
        name: "VAV-102",
        type: "VAV_Box",
        points: [
          {
            name: "cooling_valve",
            type: "Actuator",
            bacnet: {
              device_id: 123,
              object_type: "analogInput", // Wrong type
              object_instance: 1,
            },
          },
        ],
      };

      const response = await client.createEquipment(equipment);
      const validation = await client.validate223P(response.id);

      expect(validation.valid).toBe(false);
      expect(validation.errors).toHaveLength(1);
      expect(validation.errors[0].message).toContain("Actuator");
      expect(validation.errors[0].message).toContain("analogOutput");
    });
  });

  describe("G36 Sequence Management", () => {
    it("should create G36 sequence with valid 223P references", async () => {
      // Setup: Create equipment first
      const equipmentId = await createTestEquipment();

      const sequence = {
        name: "VAV Cooling",
        type: "g36.vav.cooling",
        equipment_id: equipmentId,
        inputs: [
          { name: "zone_temp", point_ref: "zone_temp" },
          { name: "zone_temp_setpoint", point_ref: "zone_temp_setpoint" },
          { name: "damper_position", point_ref: "damper_position" },
        ],
        outputs: [
          { name: "cooling_command", point_ref: "cooling_valve_command" },
        ],
      };

      const response = await client.createG36Sequence(sequence);
      expect(response.id).toBeDefined();

      const validation = await client.validateG36(response.id);
      expect(validation.valid).toBe(true);
    });

    it("should fail validation when 223P points are missing", async () => {
      // Setup: Create equipment with incomplete points
      const equipmentId = await createIncompleteEquipment();

      const sequence = {
        type: "g36.vav.cooling",
        equipment_id: equipmentId,
        inputs: [
          { name: "zone_temp", point_ref: "zone_temp" },
          { name: "zone_temp_setpoint", point_ref: "zone_temp_setpoint" }, // Missing!
        ],
      };

      const response = await client.createG36Sequence(sequence);
      const validation = await client.validateG36(response.id);

      expect(validation.valid).toBe(false);
      expect(
        validation.errors.some((e) => e.message.includes("zone_temp_setpoint")),
      ).toBe(true);
    });
  });

  describe("Template Discovery", () => {
    it("should retrieve 223P templates", async () => {
      const templates = await client.get223PTemplates();

      expect(templates.length).toBeGreaterThan(0);

      const vavTemplate = templates.find((t) => t.name === "VAV Box");
      expect(vavTemplate).toBeDefined();
      expect(vavTemplate?.required_points).toContain("zone_temp");
    });

    it("should retrieve G36 templates", async () => {
      const templates = await client.getG36Templates();

      expect(templates.length).toBeGreaterThan(0);

      const vavCooling = templates.find((t) => t.id.includes("vav.cooling"));
      expect(vavCooling).toBeDefined();
      expect(vavCooling?.required_inputs).toContain("zone_temp");
    });
  });
});
```

## 7. TypeScript Client Generation

### 7.1 Generate Client Stubs from OpenAPI

After the FastAPI server is running, generate TypeScript types:

```bash
cd apps/designer

# Generate types from OpenAPI spec
npx openapi-typescript http://localhost:8000/openapi.json \
  -o src/lib/api/buildingmotif-types.ts
```

### 7.2 Create Client Wrapper

```typescript
// apps/designer/src/lib/api/buildingmotif-client.ts

import type { paths } from "./buildingmotif-types";
import type {
  Equipment,
  G36Sequence,
  ValidationResult,
} from "./buildingmotif-types";

export class BuildingMotifClient {
  constructor(private baseUrl: string) {}

  async createEquipment(equipment: Equipment): Promise<{ id: string }> {
    const response = await fetch(`${this.baseUrl}/api/v1/equipment`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(equipment),
    });
    return response.json();
  }

  async validate223P(equipmentId: string): Promise<ValidationResult> {
    const response = await fetch(`${this.baseUrl}/api/v1/validate/223p`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ equipment_id: equipmentId }),
    });
    return response.json();
  }

  async createG36Sequence(sequence: G36Sequence): Promise<{ id: string }> {
    const response = await fetch(`${this.baseUrl}/api/v1/g36/sequences`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(sequence),
    });
    return response.json();
  }

  async validateG36(sequenceId: string): Promise<ValidationResult> {
    const response = await fetch(`${this.baseUrl}/api/v1/validate/g36`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ sequence_id: sequenceId }),
    });
    return response.json();
  }

  async get223PTemplates(): Promise<Array<Template223P>> {
    const response = await fetch(`${this.baseUrl}/api/v1/templates/223p`);
    const data = await response.json();
    return data.templates;
  }

  async getG36Templates(): Promise<Array<TemplateG36>> {
    const response = await fetch(`${this.baseUrl}/api/v1/templates/g36`);
    const data = await response.json();
    return data.templates;
  }
}
```

## 8. Implementation Phases

### Phase 0: Cleanup ✅ **COMPLETED**

**Goal**: Remove unused code and consolidate schemas

**Status**: ✅ **COMPLETED** (October 28, 2025)
**Actual Duration**: 1 day

**Tasks**:

- [x] Move `packages/bms-schemas/` → `apps/designer/src/lib/schemas/`
- [x] Update imports in Designer app (from `bms-schemas` to `@/lib/schemas`)
- [x] Remove from pnpm workspace
- [x] Delete Python generation scripts
- [x] Fix/remove broken integration tests
- [x] Update CLAUDE.md and README.md

**Success Criteria**:

- ✅ All Designer tests pass (37/37 schema tests)
- ✅ No broken imports
- ✅ Documentation reflects new structure
- ✅ Build succeeds (`pnpm build` works correctly)

**Notes**:

- Schemas placed in `src/lib/schemas/` instead of `src/schemas/` to follow Next.js best practices
- All imports updated to `@/lib/schemas` for consistency with existing Designer structure

---

### Phase 1: 223P UI with Mock Data (3-4 days) 🔄 **NEEDS ITERATION**

**Detailed Spec**: [Phase 1: 223P Mapping Popup Design](./2025-10-30-phase-1-223p-mapping-popup-spec.md)

**Goal**: Build and validate 223P mapping UX with mock data

**Focus**: Canvas-integrated 223P mapping popup with AI-assisted suggestions using BuildingMOTIF templates

**Tasks**:

- [ ] Create mock 223P template service
  - VAV Box template
  - AHU template
  - Boiler template
- [ ] Create mock validation service (returns success/errors)
- [ ] Build 223P Equipment Form UI:
  - Template selector dropdown
  - Equipment details (name, location, type)
  - Point mapping table (BACnet device/object → 223P point)
- [ ] Build Equipment List view
- [ ] Build Validation Results component
  - Success state display
  - Error state display with SHACL-like messages
- [ ] Store in local state/project JSON
- [ ] Write React component tests
- [ ] Create shadcn/ui components:
  - `<EquipmentForm />`
  - `<PointMappingTable />`
  - `<ValidationResults />`
  - `<EquipmentList />`

**Mock Data Examples**:

```typescript
const mock223PTemplates = [
  {
    id: "tpl_vav_box",
    name: "VAV Box",
    required_points: ["zone_temp", "damper_position", "cooling_valve"],
    optional_points: ["zone_temp_setpoint", "occupancy"],
  },
];

const mockValidationErrors = [
  {
    path: "points.cooling_valve",
    message: "Actuator must use Analog Output (AO), found Analog Input (AI)",
  },
];
```

**Success Criteria**:

- ✅ User can select 223P template
- ✅ User can map BACnet points to 223P schema
- ✅ Mock validation shows success/error states
- ✅ All UI components tested
- ✅ No backend dependencies

---

### Phase 2: 223P Backend Setup (3-4 days) 🔄 **NEEDS ITERATION**

**Goal**: Build BuildingMotif backend for 223P ONLY

**Focus**: ONLY 223P storage and validation, no G36

**Tasks**:

- [ ] Create `apps/bms-buildingmotif/` directory structure
- [ ] Setup `pyproject.toml` with dependencies:
  - FastAPI
  - BuildingMotif
  - rdflib (RDF handling)
  - pyshacl (SHACL validation)
  - Pydantic
  - uvicorn
- [ ] Setup FastAPI + BuildingMotif SDK
- [ ] Setup RDF graph storage (SQLite + RDFLib)
- [ ] Implement 223P endpoints:
  - `GET /api/v1/templates/223p` - List templates
  - `POST /api/v1/equipment` - Create equipment
  - `GET /api/v1/equipment` - List equipment
  - `GET /api/v1/equipment/{id}` - Get equipment
  - `PUT /api/v1/equipment/{id}` - Update equipment
  - `DELETE /api/v1/equipment/{id}` - Delete equipment
  - `POST /api/v1/validate/223p` - Validate 223P model
- [ ] Create SHACL shapes for 223P validation:
  - BACnet object type validation (Actuator → AO/BO)
  - Required points validation
  - Equipment hierarchy rules
- [ ] Implement SHACL validation service
- [ ] Add to pnpm workspace for unified commands
- [ ] Write Python unit tests (TDD)
- [ ] Write integration tests
- [ ] Generate OpenAPI spec

**File Structure**:

```
apps/bms-buildingmotif/
├── src/
│   ├── main.py                  # FastAPI entry
│   ├── routers/
│   │   ├── equipment.py         # 223P CRUD
│   │   ├── validation.py        # SHACL validation
│   │   └── templates.py         # Template discovery
│   ├── services/
│   │   ├── buildingmotif_service.py
│   │   └── shacl_engine.py      # SHACL wrapper
│   ├── models/
│   │   ├── equipment.py         # Pydantic 223P models
│   │   └── validation.py        # Validation request/response
│   ├── shapes/
│   │   └── 223p-shapes.ttl      # SHACL shapes for 223P
│   └── db/
│       └── rdf_store.py         # RDF graph storage
├── tests/
│   ├── test_equipment_api.py
│   └── test_shacl_engine.py
├── pyproject.toml
└── README.md
```

**SHACL Example** (`shapes/223p-shapes.ttl`):

```turtle
@prefix sh: <http://www.w3.org/ns/shacl#> .
@prefix s223: <http://data.ashrae.org/standard223#> .

# Actuator must use AO/BO
s223:ActuatorShape
    a sh:NodeShape ;
    sh:targetClass s223:Actuator ;
    sh:property [
        sh:path s223:hasBACnetObjectType ;
        sh:in ("analogOutput" "binaryOutput") ;
        sh:message "Actuator must use Analog Output or Binary Output" ;
    ] .
```

**Success Criteria**:

- ✅ FastAPI server runs
- ✅ 223P equipment stored in RDF graph
- ✅ SHACL validation works
- ✅ OpenAPI docs available at `/docs`
- ✅ All tests pass

---

### Phase 3: 223P Integration (2-3 days) 🔄 **NEEDS ITERATION**

**Goal**: Connect Designer UI to real BuildingMotif backend

**Focus**: ONLY 223P integration, no G36 yet

**Tasks**:

- [ ] Generate TypeScript client from OpenAPI:
  ```bash
  npx openapi-typescript http://localhost:8000/openapi.json \
    -o src/lib/api/buildingmotif-types.ts
  ```
- [ ] Create BuildingMotifClient wrapper service
- [ ] Replace mock 223P template service with API calls
- [ ] Replace mock validation service with API calls
- [ ] Update Equipment Form to call real API:
  - `POST /api/v1/equipment` on create
  - `PUT /api/v1/equipment/{id}` on update
  - `DELETE /api/v1/equipment/{id}` on delete
- [ ] Update Equipment List to fetch from API:
  - `GET /api/v1/equipment` for list
  - `GET /api/v1/equipment/{id}` for details
- [ ] Update Validation to call real API:
  - `POST /api/v1/validate/223p` for validation
- [ ] Display real SHACL errors in UI
- [ ] Add loading/error states
- [ ] Write integration tests (Designer → BuildingMotif)

**API Client Example**:

```typescript
class BuildingMotifClient {
  async create223PEquipment(data: Equipment223P): Promise<Equipment223P> {
    const response = await fetch("/api/v1/equipment", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(data),
    });
    return response.json();
  }

  async validate223P(equipmentId: string): Promise<ValidationResult> {
    const response = await fetch(`/api/v1/validate/223p`, {
      method: "POST",
      body: JSON.stringify({ equipment_id: equipmentId }),
    });
    return response.json();
  }
}
```

**Success Criteria**:

- ✅ UI calls real BuildingMotif API
- ✅ Real SHACL validation errors displayed
- ✅ Equipment stored in RDF graph
- ✅ All integration tests pass
- ✅ NO mock services remaining for 223P

---

### Phase 4: G36 UI with Mock Data (3-4 days) 🔄 **NEEDS ITERATION**

**Goal**: Build G36 control sequence UX with mock data

**Focus**: ONLY G36 visual blocks, no backend yet

**Tasks**:

- [ ] Create mock G36 template service:
  - VAV cooling sequence template
  - AHU economizer template
  - Boiler control template
- [ ] Create mock G36 validation service (returns success/errors)
- [ ] Build G36 visual blocks on canvas:
  - Drag-drop G36 blocks onto canvas
  - Link G36 block inputs to 223P points via dropdown
  - Configure G36 parameters (setpoints, constants)
  - Visual connection lines (G36 → 223P references)
- [ ] Build G36 Block Config UI:
  - Template selector dropdown
  - Input point dropdowns (populated from 223P equipment)
  - Output point dropdowns (populated from 223P equipment)
  - Parameter inputs (setpoints, thresholds)
- [ ] Build G36 Validation component:
  - Validate button
  - Success state display
  - Error display with SHACL-like messages
- [ ] Store G36 sequences in project JSON (local state)
- [ ] Write React component tests
- [ ] Create shadcn/ui components:
  - `<G36BlockNode />` - Visual block on canvas
  - `<G36ConfigPanel />` - Configure block
  - `<G36ValidationResults />` - Validation feedback
  - `<PointReferenceDropdown />` - Select 223P point

**Mock Data Examples**:

```typescript
const mockG36Templates = [
  {
    id: "tpl_vav_cooling",
    name: "VAV Cooling",
    required_inputs: ["zone_temp", "zone_temp_setpoint"],
    required_outputs: ["cooling_valve_command"],
    optional_inputs: ["occupancy", "outdoor_air_temp"],
  },
];

const mockG36ValidationErrors = [
  {
    path: "inputs.zone_temp",
    message: "Input must reference existing 223P point",
  },
];
```

**Project Storage (Designer)**:

```json
{
  "project": {
    "equipment_ids": ["eq_vav101", "eq_ahu01"],
    "sequences": [
      {
        "id": "seq1",
        "type": "g36.vav.cooling",
        "equipment_id": "eq_vav101",
        "inputs": {
          "zone_temp": { "point_id": "pid_zone_temp" },
          "zone_temp_setpoint": { "point_id": "pid_setpoint" }
        },
        "outputs": {
          "cooling_valve_command": { "point_id": "pid_valve" }
        },
        "validated": false
      }
    ]
  }
}
```

**Success Criteria**:

- ✅ User can drag G36 blocks onto canvas
- ✅ User can link G36 inputs/outputs to 223P points
- ✅ Mock validation shows success/error states
- ✅ All UI components tested
- ✅ No backend dependencies

---

### Phase 5: G36 Backend Validation (3-4 days) 🔄 **NEEDS ITERATION**

**Goal**: Implement G36 SHACL validation against 223P models

**Focus**: ONLY validation, NO storage (G36 stays in Designer)

**Key Architecture Decision**: G36 sequences are NOT stored in BuildingMotif. They are stored in Designer project files. BuildingMotif only validates them.

**Tasks**:

- [ ] Create SHACL shapes for G36 sequences:
  - G36 inputs must reference existing 223P points
  - G36 outputs must reference existing 223P points
  - VAV cooling requires specific points (zone_temp, cooling_valve, etc.)
  - AHU sequences require specific points
- [ ] Implement G36 JSON → RDF converter (temporary graph)
- [ ] Implement G36 validation service:
  - Convert G36 JSON → temp RDF
  - Load 223P equipment RDF from database
  - Merge graphs
  - Run SHACL validation
  - Parse and return errors
  - Discard temp G36 RDF (no storage!)
- [ ] Create G36 endpoints:
  - `GET /api/v1/templates/g36` - List G36 templates
  - `POST /api/v1/validate/g36` - Validate G36 sequence
- [ ] Write unit tests (TDD)
- [ ] Write integration tests

**SHACL Example** (`shapes/g36-shapes.ttl`):

```turtle
@prefix sh: <http://www.w3.org/ns/shacl#> .
@prefix g36: <https://yourdomain.com/g36#> .
@prefix s223: <http://data.ashrae.org/standard223#> .

# VAV Cooling requires specific points
g36:VAVCoolingShape
    a sh:NodeShape ;
    sh:targetClass g36:VAVCooling ;
    sh:property [
        sh:path g36:hasInput ;
        sh:qualifiedValueShape [
            sh:path s223:hasName ;
            sh:hasValue "zone_temp" ;
        ] ;
        sh:qualifiedMinCount 1 ;
        sh:message "VAV Cooling requires 'zone_temp' input" ;
    ] .
```

**G36 Validator Service**:

```python
class G36Validator:
    def validate_sequence(self, g36_json: dict, equipment_id: str):
        # 1. Convert G36 JSON → RDF (temporary)
        g36_graph = self._json_to_rdf(g36_json)

        # 2. Load 223P equipment (already RDF)
        equipment_graph = self._load_223p(equipment_id)

        # 3. SHACL validation
        conforms, results_graph, _ = validate(
            data_graph=g36_graph + equipment_graph,
            shacl_graph=self.shapes_graph
        )

        # 4. Return errors (discard temp RDF)
        return {"valid": conforms, "errors": [...]}
```

**Success Criteria**:

- ✅ G36 sequences validate against 223P
- ✅ SHACL catches missing point references
- ✅ All integration tests pass
- ✅ NO G36 storage in BuildingMotif (validation only)
- ✅ OpenAPI spec updated with G36 endpoints

---

### Phase 6: G36 Integration + BMS IoT Deployment (3-4 days) 🔄 **NEEDS ITERATION**

**Goal**: Connect G36 UI to backend and enable deployment to BMS IoT App

**Focus**: Complete integration + deployment pipeline

**Tasks**:

- [ ] Replace mock G36 services with real API calls
- [ ] Update G36 blocks to call validation API:
  - `POST /api/v1/validate/g36` on validate
  - Display real SHACL errors
- [ ] Design deployment payload format:
  - 223P equipment references (from BuildingMotif)
  - G36 sequences (from Designer project)
  - BACnet device mappings
- [ ] Create deployment endpoint in BMS IoT App:
  - `POST /api/deploy` - Deploy validated config
  - Accept 223P + G36 JSON
  - Store in BMS IoT App database
  - Execute control logic
- [ ] Implement deployment flow from Designer:
  - "Deploy" button (enabled only after validation passes)
  - Progress indicator
  - Deployment status tracking
  - Error handling
- [ ] Write end-to-end tests (Designer → BuildingMotif → BMS IoT App)
- [ ] Add deployment status page in Designer

**Deployment Flow**:

1. Designer validates 223P (BuildingMotif API)
2. Designer validates G36 against 223P (BuildingMotif API)
3. If valid → enable "Deploy" button
4. User clicks "Deploy to BMS IoT App"
5. Designer sends config → BMS IoT App
6. BMS IoT App executes BACnet control logic

**Deployment Payload Example**:

```json
{
  "equipment_ids": ["eq_vav101"],
  "sequences": [
    {
      "id": "seq1",
      "type": "g36.vav.cooling",
      "equipment_id": "eq_vav101",
      "inputs": {
        "zone_temp": { "point_id": "pid_zone_temp" }
      },
      "outputs": {
        "cooling_valve_command": { "point_id": "pid_valve" }
      },
      "validated": true,
      "validation_timestamp": "2025-10-28T10:00:00Z"
    }
  ]
}
```

**Success Criteria**:

- ✅ G36 UI calls real validation API
- ✅ Real SHACL errors displayed
- ✅ Validated configs deploy to BMS IoT App
- ✅ BMS IoT App executes G36 sequences
- ✅ End-to-end tests pass
- ✅ NO mock services remaining

---

## 9. Technical Considerations

### 9.1 Database Choice

**Option 1: GraphDB (RDF Native)**

- Pros: Native RDF support, SHACL built-in
- Cons: Complex setup, new technology

**Option 2: SQLite with RDFLib**

- Pros: Simple, lightweight, easy development
- Cons: Less performant for complex queries

**Recommendation**: Start with SQLite + RDFLib for Phase 1-3, migrate to GraphDB in production if needed.

### 9.2 SHACL Validation Strategy

Use BuildingMotif's built-in SHACL validation with custom rules:

```python
# Custom SHACL rule example
def validate_bacnet_object_type(point_type: str, bacnet_type: str) -> bool:
    """Validate BACnet object type matches 223P point type"""
    rules = {
        "Sensor": ["analogInput", "binaryInput"],
        "Actuator": ["analogOutput", "binaryOutput"],
        "Setpoint": ["analogValue"]
    }
    return bacnet_type in rules.get(point_type, [])
```

### 9.3 Error Handling

**API Errors**:

- 400 Bad Request: Invalid input data
- 404 Not Found: Equipment/sequence not found
- 422 Unprocessable Entity: SHACL validation failed
- 500 Internal Server Error: BuildingMotif SDK error

**Example Error Response**:

```json
{
  "valid": false,
  "errors": [
    {
      "severity": "error",
      "message": "Actuator must use Analog Output (AO), found Analog Input (AI)",
      "property": "points.cooling_valve.bacnet.object_type",
      "constraint": "sh:class",
      "suggested_fix": "Change object_type to 'analogOutput'"
    }
  ]
}
```

### 9.4 Performance Considerations

**Caching**:

- Cache 223P templates (rarely change)
- Cache G36 templates (rarely change)
- Invalidate cache on equipment/sequence updates

**Batch Validation**:

- Allow validating multiple equipment models at once
- Useful for bulk imports

## 10. Future Enhancements

### 10.1 Advanced SHACL Rules

- Cross-equipment validation
- System-level consistency checks
- Energy efficiency recommendations

### 10.2 G36 Library Expansion

- Additional G36 sequences (AHU, boiler, etc.)
- Custom sequence builder
- Sequence composition (reusable sub-sequences)

### 10.3 Visualization

- 223P equipment hierarchy visualization
- G36 sequence flow diagrams
- Dependency graphs (G36 → 223P → BACnet)

### 10.4 Import/Export

- Import existing 223P models (Turtle, JSON-LD)
- Export to industry formats
- Integration with external building ontologies

## 11. Risks & Mitigations

| Risk                                 | Impact | Mitigation                                               |
| ------------------------------------ | ------ | -------------------------------------------------------- |
| BuildingMotif SDK learning curve     | Medium | Start with simple examples, incremental complexity       |
| SHACL rules too strict               | High   | Make rules configurable, provide override option         |
| Performance issues with large models | Medium | Implement caching, optimize RDF queries                  |
| G36 → 223P mapping complexity        | High   | Start with simple sequences, build library incrementally |
| Breaking changes in BuildingMotif    | Medium | Pin version, monitor releases, test before upgrades      |

## 12. Success Metrics

**Phase 0** (Cleanup):

- ✅ bms-schemas moved to `apps/designer/src/lib/schemas/`
- ✅ All imports updated to `@/lib/schemas`
- ✅ Build succeeds (`pnpm build`)
- ✅ 37/37 schema tests passing

**Phase 1** (223P UI with Mock Data):

- ✅ User can select 223P template
- ✅ User can map BACnet points to 223P schema
- ✅ Mock validation shows success/error states
- ✅ All UI components tested

**Phase 2** (223P Backend Setup):

- ✅ FastAPI app running with health check
- ✅ OpenAPI docs accessible
- ✅ 223P equipment stored in RDF graph
- ✅ SHACL validation working for 223P
- ✅ 10+ unit tests passing

**Phase 3** (223P Integration):

- ✅ UI calls real BuildingMotif API
- ✅ Real SHACL validation errors displayed
- ✅ All integration tests pass

**Phase 4** (G36 UI with Mock Data):

- ✅ User can drag G36 blocks onto canvas
- ✅ User can link G36 inputs/outputs to 223P points
- ✅ Mock validation shows success/error states
- ✅ All UI components tested

**Phase 5** (G36 Backend Validation):

- ✅ G36 sequences validate against 223P
- ✅ SHACL catches missing point references
- ✅ All integration tests pass
- ✅ NO G36 storage (validation only)

**Phase 6** (G36 Integration + Deployment):

- ✅ G36 UI calls real validation API
- ✅ Validated configs deploy to BMS IoT App
- ✅ BMS IoT App executes G36 sequences
- ✅ End-to-end tests pass

## 13. References

- [BuildingMotif Documentation](https://buildingmotif.readthedocs.io/)
- [ASHRAE 223P Standard](https://open223.info/)
- [G36 Guideline](https://guideline36.com/)
- [SHACL Specification](https://www.w3.org/TR/shacl/)
- [FastAPI Documentation](https://fastapi.tiangolo.com/)
- [openapi-typescript](https://github.com/drwpow/openapi-typescript)
