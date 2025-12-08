# Story 1.9: Schema Endpoint

Status: skipped

## Decision Notes

**Skipped on 2025-12-04** - After analyzing Designer codebase patterns:

1. Designer uses hardcoded node UI components (CalculationNode, ScheduleNode, etc.)
2. OpenAPI-ts already generates TypeScript types from API DTOs at build time
3. Schema endpoint would only add value for dynamic form rendering (not currently used)
4. Epic 1 only has Reheat - static components are simpler and consistent

**Future consideration:** Add schema endpoint when multiple G36 sequence types (VAV, AHU) are added and dynamic form rendering is needed.

## Story

As a developer,
I want a GET /schema endpoint that returns Reheat metadata,
So that Designer can dynamically render configuration panels.

## Acceptance Criteria

1. GET /api/v1/g36/reheat/schema endpoint implemented
2. Returns parameters, inputs, outputs with defaults, ranges, units
3. Response matches tech spec schema format (Section 4.2)
4. OpenAPI documentation accurate with examples

## Tasks / Subtasks

- [ ] Task 1: Create Schema Response DTOs (AC: #2, #3)

  - [ ] Create `src/dto/schema_dto.py` file
  - [ ] Define FieldMetadata with type, default, min, max, unit, description
  - [ ] Define SchemaResponse with sequence_type, parameters, inputs, outputs
  - [ ] Add json_schema_extra with examples for OpenAPI

- [ ] Task 2: Create Schema Generation Logic (AC: #2)

  - [ ] Create `src/controllers/schema_controller.py`
  - [ ] Implement get_reheat_schema() that builds SchemaResponse from ReheatParameters, ReheatInputs, ReheatOutputs DTOs
  - [ ] Extract field metadata (defaults, ranges, units) from Pydantic Field definitions
  - [ ] Map internal field names to FMU names (e.g., zoneTemperature → TZon)

- [ ] Task 3: Create Schema Router (AC: #1)

  - [ ] Create `src/routers/schema_router.py`
  - [ ] Add GET /api/v1/g36/reheat/schema endpoint
  - [ ] Add docstring for Swagger documentation
  - [ ] Return SchemaResponse from controller

- [ ] Task 4: Register Router in main.py (AC: #1)

  - [ ] Import schema_router in main.py
  - [ ] Include router with /api/v1/g36 prefix

- [ ] Task 5: OpenAPI Documentation (AC: #4)

  - [ ] Verify /docs shows schema endpoint correctly
  - [ ] Verify response example matches tech spec format
  - [ ] Ensure all field metadata is visible in schema

- [ ] Task 6: Unit Tests (AC: #1, #2, #3)

  - [ ] Create `tests/unit/test_schema_dto.py`
  - [ ] Test SchemaResponse serialization
  - [ ] Test FieldMetadata with all field types
  - [ ] Create `tests/unit/test_schema_controller.py`
  - [ ] Test get_reheat_schema() returns correct structure
  - [ ] Test all parameters have defaults
  - [ ] Test all inputs have ranges where applicable
  - [ ] Test outputs have correct units

- [ ] Task 7: Integration Test (AC: #1, #3)
  - [ ] Create `tests/integration/test_schema_endpoint.py`
  - [ ] Test GET /api/v1/g36/reheat/schema returns 200
  - [ ] Test response structure matches tech spec
  - [ ] Test sequence_type is "reheat"

## Dev Notes

### Architecture Pattern

Follow MVC pattern per tech spec:

- **Router**: HTTP endpoint, request parsing, response formatting
- **Controller**: Business logic, schema generation
- **DTO**: Pydantic schemas for response validation

### Expected Response Format

Uses user-friendly API names as keys (consistent with Story 1.8 DTOs). FMU names included in descriptions for reference.

```json
{
  "sequenceType": "reheat",
  "parameters": {
    "maxCoolingAirflow": {
      "type": "float",
      "default": 0.5,
      "min": 0,
      "unit": "m³/s",
      "description": "Maximum cooling airflow in m³/s (FMU: VCooMax)"
    },
    "maxHeatingAirflow": { ... },
    "minAirflow": { ... }
  },
  "inputs": {
    "zoneTemperature": {
      "type": "float",
      "min": 250,
      "max": 350,
      "unit": "K",
      "description": "Zone temperature in Kelvin (FMU: TZon)"
    },
    ...
  },
  "outputs": {
    "damperPosition": {
      "type": "float",
      "min": 0,
      "max": 1,
      "description": "Damper position 0-1 normalized (FMU: yDam)"
    },
    ...
  }
}
```

### Field Name Mapping

The schema endpoint should use user-friendly API names (zoneTemperature, damperPosition) as keys, consistent with Story 1.8 DTOs. FMU names are included in the description field for reference.

| Schema Key (API Name)        | FMU Name (in description) |
| ---------------------------- | ------------------------- |
| maxCoolingAirflow            | VCooMax                   |
| maxHeatingAirflow            | VHeaMax                   |
| minAirflow                   | VMin                      |
| zoneTemperature              | TZon                      |
| coolingSetpoint              | TCooSet                   |
| heatingSetpoint              | THeaSet                   |
| dischargeAirTemperature      | TDis                      |
| primaryAirflow               | VDis_flow                 |
| supplyAirTemperature         | TSup                      |
| supplyAirTemperatureSetpoint | TSupSet                   |
| fanStatus                    | u1Fan                     |
| operationMode                | uOpeMod                   |
| damperPosition               | yDam                      |
| valvePosition                | yVal                      |
| airflowSetpoint              | VSet_flow                 |

### Project Structure

Files to create:

- `apps/control-sequence-api-app/src/dto/schema_dto.py` - Schema response DTOs
- `apps/control-sequence-api-app/src/controllers/schema_controller.py` - Schema generation logic
- `apps/control-sequence-api-app/src/routers/schema_router.py` - Schema endpoint
- `apps/control-sequence-api-app/tests/unit/test_schema_dto.py` - DTO tests
- `apps/control-sequence-api-app/tests/unit/test_schema_controller.py` - Controller tests
- `apps/control-sequence-api-app/tests/integration/test_schema_endpoint.py` - Integration tests

Files to modify:

- `apps/control-sequence-api-app/src/main.py` - Register router

### Testing Standards

Per project TDD workflow:

1. Write failing test first
2. Implement to make test pass
3. Verify with `pytest tests/ -v`

### References

- [Tech Spec Section 4.2 - Request/Response Schemas](../specs/control-sequence-api-tech-spec.md#42-requestresponse-schemas)
- [Tech Spec UC1 - Get Sequence Schema](../specs/control-sequence-api-tech-spec.md#uc1-get-sequence-schema)
- [Existing reheat_dto.py](../../../../apps/control-sequence-api-app/src/dto/reheat_dto.py)
- [Existing main.py](../../../../apps/control-sequence-api-app/src/main.py)

### Learnings from Previous Story

**From Story 1.8 (Status: done)**

Key patterns established:

- Used user-friendly camelCase field names in API DTOs (e.g., `zoneTemperature` instead of `TZon`)
- FMU mapping documented in field descriptions (e.g., "Zone temperature in Kelvin (FMU: TZon)")
- `__init__.py` kept empty per user request - imports use direct module paths
- Added `OperationMode` IntEnum for G36 operation modes
- Added `TemperatureUnit` enum with `temp_in_kelvin()` conversion function
- Separated API layer (`ReheatInputsRequest`) from internal FMU layer (`ReheatInputs`)
- Pydantic Field() with ge, le, description, json_schema_extra for validation and docs

The schema endpoint should leverage the existing DTO definitions and extract metadata from Field() definitions programmatically where possible.

[Source: stories/story-1-8-reheat-dtos-validation.md]

## Dev Agent Record

### Context Reference

- (to be created during implementation)

### Agent Model Used

(to be filled during implementation)

### Debug Log References

(to be filled during implementation)

### Completion Notes List

(to be filled during implementation)

### File List

(to be filled during implementation)
