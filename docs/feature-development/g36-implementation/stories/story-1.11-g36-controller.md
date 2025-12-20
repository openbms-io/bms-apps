# Story 1.12: G36 Router & Endpoints

Status: done

## Story

As a developer,
I want all Reheat API endpoints implemented,
So that Designer can interact with the Control Sequence API.

## Acceptance Criteria

1. POST /api/v1/g36/reheat/instances (upsert - creates or recreates with provided params)
2. POST /api/v1/g36/reheat/instances/{instance_id}/step (execute step)
3. DELETE /api/v1/g36/instances/{instance_id} (delete - idempotent, sequence-agnostic)
4. All endpoints documented in OpenAPI
5. Integration tests for all endpoints
6. DTO-to-FMU mapping verified with unit tests (inputs, outputs, parameters, calculated parameters)

## Tasks / Subtasks

- [x] Task 1: Add FMU Variable Metadata to DTO Fields (AC: #6)

  - [x] Add `fmu_var` metadata to all ReheatInputs fields using Field json_schema_extra
  - [x] Add `fmu_var` metadata to all ReheatParameters fields
  - [x] Add `fmu_var` metadata to all ReheatOutputs fields
  - [x] Add `fmu_var` metadata to all ReheatCalculatedParameters fields
  - [x] Example: `flowHysteresis: float = Field(..., json_schema_extra={"fmu_var": "floHys_in"})`
  - [x] Metadata enables introspection-based validation without polluting field names

- [x] Task 2: Define Unit Conversion Strategy (AC: #1)

  - [x] **DECISION**: Unit fields live in nested DTOs (ReheatInputsRequest)
  - [x] Identify all unit types needed:
    - Temperature: Fahrenheit, Celsius (FMU uses Kelvin internally)
    - Airflow: CFM, L/s, m³/h (FMU uses m³/s internally)
  - [x] Define default units: Celsius for temp, m3/s for airflow
  - [x] Document which DTO fields require unit conversion
  - [x] Design conversion helpers: temp_in_kelvin(), airflow_in_m3_per_s()
  - [x] Unit tests for bidirectional conversions

- [x] Task 3: Create G36 Router (AC: #1-4)

  - [x] Create `src/routers/g36_router.py`
  - [x] Add POST /api/v1/g36/reheat/instances endpoint (upsert)
  - [x] Add POST /api/v1/g36/reheat/instances/{instance_id}/step endpoint
  - [x] Add DELETE /api/v1/g36/instances/{instance_id} endpoint (sequence-agnostic)
  - [x] Add docstrings for OpenAPI documentation
  - [x] Define request/response DTOs: CreateInstanceRequest, CreateInstanceResponse, StepRequest, StepResponse, DeleteInstanceResponse

- [x] Task 4: Create G36 Controller (AC: #1-3)

  - [x] Create `src/controllers/g36_controller.py`
  - [x] Implement G36ReheatController class with FmuAdapter dependency injection
  - [x] Implement async upsert_instance() - calls adapter upsert, returns CreateInstanceResponse
  - [x] Implement async step() - convert inputs, call adapter, return StepResponse
  - [x] Implement async delete_instance() - idempotent (success even if not found)
  - [x] Map adapter exceptions to HTTP errors per tech spec Section 4.3

- [x] Task 5: Extend FmuAdapter for Upsert (AC: #1)

  - [x] Add `async upsert_fmu_instance(instance_id, sequence_type, fmu_data)` method
  - [x] If instance exists: await terminate existing → create new with same instance_id
  - [x] If instance doesn't exist: create new
  - [x] FMPy has no native reset, so recreate is required for parameter changes
  - [x] UpsertResult dataclass returns instance_id and is_created flag
  - [x] Unit tests for upsert_fmu_instance (both create and recreate paths)

- [x] Task 6: Register Router in main.py (AC: #4)

  - [x] Import g36_router in main.py
  - [x] Register with app.include_router(g36_router)
  - [x] Verify endpoints appear in /docs

- [x] Task 7: Unit Tests for Controller (AC: #1-3)

  - [x] Create `tests/unit/test_controllers/test_g36_controller.py`
  - [x] Test upsert_instance creates new instance
  - [x] Test upsert_instance recreates existing instance with new params
  - [x] Test step success returns outputs
  - [x] Test step raises 400 for validation error
  - [x] Test step raises 404 if not found
  - [x] Test delete_instance success
  - [x] Test delete_instance idempotent (not found returns success)
  - [x] Mock FmuAdapter for unit tests

- [x] Task 8: Integration Tests for Router (AC: #5)

  - [x] Create `tests/integration/test_g36_router.py`
  - [x] Test POST /instances creates new instance
  - [x] Test POST /instances recreates existing instance (upsert)
  - [x] Test POST /instances/{id}/step returns outputs
  - [x] Test POST /instances/{id}/step returns 422 for invalid inputs
  - [x] Test POST /instances/{id}/step returns 404 for unknown
  - [x] Test DELETE /instances/{id} deletes instance
  - [x] Test DELETE /instances/{id} idempotent (not found returns success)
  - [x] No mocking - full end-to-end flow with actual FMU
  - [x] Use TestClient with real FmuAdapter and FMU file

- [x] Task 9: DTO-to-ReheatFMUData Field Completeness Tests (AC: #6)

  - [x] Create `tests/unit/test_dto_fmu_completeness.py`
  - [x] Use fmu_var metadata from Task 1 to validate mappings
  - [x] Test every field in ReheatInputs has a mapping in ReheatFMUData.input_variables
  - [x] Test every field in ReheatParameters has a mapping in ReheatFMUData.configuration_variables
  - [x] Test every field in ReheatOutputs has a mapping in ReheatFMUData.create_outputs
  - [x] Test every field in ReheatCalculatedParameters has a mapping in ReheatFMUData.create_calculated_parameters
  - [x] Use introspection to get DTO field names and verify each has FMU mapping
  - [x] Fail-fast: test fails if a DTO field is added without corresponding FMU mapping

## Dev Notes

### FMU Recreation Required for Parameter Changes

**Why recreate instead of reset?**

- FMPy/FMI 2.0 has `fmi2Reset` but it's not universally implemented by FMUs
- G36 Reheat FMU parameters are initialization parameters set during FMU setup
- To change parameters, the FMU must be terminated and recreated

### Upsert Instance with Caller-Provided instance_id

Current FmuAdapter generates UUID internally. For router, we need caller-provided instance_id with upsert semantics:

```python
async def upsert_fmu_instance(
    self,
    instance_id: str,
    sequence_type: SequenceType,
    fmu_data: FMUDataProtocol,
) -> bool:
    """Create or recreate FMU instance with caller-provided instance_id.

    Returns True if created new, False if recreated existing.
    """
    created = True
    if instance_id in self._lifecycle_managers:
        # Terminate existing before recreating
        await self._lifecycle_managers[instance_id].terminate()
        created = False

    lifecycle = FmuLifecycleManager(sequence_type, fmu_data)
    self._lifecycle_managers[instance_id] = lifecycle
    return created
```

### Upsert Semantics - Simple by Design

POST uses upsert semantics - creates if new, recreates if exists. This is simpler because:

- No 409/404 edge cases to handle
- No need to compare 55 parameters for equality
- Single endpoint for create and update
- Designer declares "I want this instance with these params" - always succeeds

### Architecture Pattern

Router → Controller → Adapter layering per tech spec Section 3.2:

```python
# Router: HTTP layer only
@router.post("/reheat/instances")
async def upsert_instance(
    request: UpsertInstanceRequest,
    controller: G36Controller = Depends(get_g36_controller)
) -> UpsertInstanceResponse:
    """Create or update an FMU instance for a Reheat Terminal Unit.

    Upsert semantics - creates if new, recreates with new params if exists.
    """
    return await controller.upsert_instance(request)
```

### Dependency Injection

Use FastAPI Depends for controller injection:

```python
def get_g36_controller() -> G36Controller:
    adapter = FmuAdapter.get_instance()
    return G36Controller(adapter)
```

### Error Mapping

Map adapter exceptions to HTTP responses per tech spec Section 4.3:

| Adapter Exception        | HTTP Status | Response                                 |
| ------------------------ | ----------- | ---------------------------------------- |
| FmuInstanceNotFoundError | 404         | `{"detail": "Instance {id} not found"}`  |
| FmuValidationError       | 400         | `{"detail": "Validation error: ..."}`    |
| FmuExecutionError        | 500         | `{"detail": "FMU execution error: ..."}` |

Controller handles exception mapping:

```python
def step(self, instance_id: str, request: StepRequest) -> StepResponse:
    try:
        inputs = ReheatInputs.from_request(request.inputs)
        fmu_data = ReheatFMUData(inputs=inputs)
        outputs = self._adapter.step(instance_id, fmu_data, request.stepSize)
        return StepResponse(
            instance_id=instance_id,
            outputs=ReheatFMUData.create_outputs(outputs)
        )
    except FmuInstanceNotFoundError:
        raise HTTPException(status_code=404, detail=f"Instance {instance_id} not found")
    except FmuValidationError as e:
        raise HTTPException(status_code=400, detail=str(e))
    except FmuExecutionError as e:
        raise HTTPException(status_code=500, detail=str(e))
```

### Endpoint Specifications

**POST /api/v1/g36/reheat/instances** (Upsert)

- Request: `UpsertInstanceRequest` (instance_id, parameters?)
- Response: `UpsertInstanceResponse` (instance_id, created: bool)
- Upsert: creates if new, recreates if exists
- created=True if new instance, created=False if recreated existing

**POST /api/v1/g36/reheat/instances/{instance_id}/step**

- Request: `StepRequest` (stepSize, inputs)
- Response: `StepResponse` (instance_id, outputs)
- 400 for validation errors, 404 if not found

**DELETE /api/v1/g36/instances/{instance_id}**

- Response: `DeleteInstanceResponse` (instance_id, deleted)
- Idempotent: returns success even if not found
- Note: sequence-agnostic path (no /reheat/)

### Project Structure

Files to create/modify:

- `apps/control-sequence-api-app/src/adapters/fmu_adapter.py` - Add upsert_fmu_instance method
- `apps/control-sequence-api-app/src/controllers/g36_controller.py` - Controller class
- `apps/control-sequence-api-app/src/routers/g36_router.py` - FastAPI router
- `apps/control-sequence-api-app/tests/unit/test_controllers/test_g36_controller.py` - Unit tests
- `apps/control-sequence-api-app/tests/integration/test_g36_router.py` - Integration tests

### Testing Standards

Per project TDD workflow:

1. Write failing test first
2. Implement to make test pass
3. Verify with pytest

For integration tests, use FastAPI TestClient:

```python
from fastapi.testclient import TestClient
from src.main import app

client = TestClient(app)

def test_upsert_creates_new_instance():
    response = client.post(
        "/api/v1/g36/reheat/instances",
        json={"instance_id": "test-1", "parameters": {"minAirflow": 0.3}}
    )
    assert response.status_code == 200
    assert response.json()["created"] == True

def test_upsert_recreates_existing_instance():
    # First upsert - creates
    client.post("/api/v1/g36/reheat/instances", json={"instance_id": "test-2"})
    # Second upsert - recreates with new params
    response = client.post(
        "/api/v1/g36/reheat/instances",
        json={"instance_id": "test-2", "parameters": {"minAirflow": 0.5}}
    )
    assert response.status_code == 200
    assert response.json()["created"] == False  # Recreated, not created
```

### References

- [Tech Spec Section 3.2 - Component Responsibilities](../specs/control-sequence-api-tech-spec.md#32-component-responsibilities)
- [Tech Spec Section 4.1 - Endpoints](../specs/control-sequence-api-tech-spec.md#41-endpoints)
- [Tech Spec Section 4.2 - Request/Response Schemas](../specs/control-sequence-api-tech-spec.md#42-requestresponse-schemas)
- [Tech Spec Section 4.3 - Error Handling](../specs/control-sequence-api-tech-spec.md#43-error-handling)
- [Tech Spec UC3 - Update FMU Instance](../specs/control-sequence-api-tech-spec.md#uc3-update-fmu-instance-parameters)
- [Existing fmu_adapter.py](../../../../apps/control-sequence-api-app/src/adapters/fmu_adapter.py)
- [Existing fmu_lifecycle.py](../../../../apps/control-sequence-api-app/src/adapters/fmu_lifecycle.py)
- [Existing reheat_dto.py](../../../../apps/control-sequence-api-app/src/dto/reheat_dto.py)
- [Existing reheat_fmu_data.py](../../../../apps/control-sequence-api-app/src/adapters/fmu_data/reheat_fmu_data.py)

### Learnings from Previous Story

**From Story 1-10-fmu-adapter-singleton (Status: done)**

- **FmuAdapter Singleton**: Use `FmuAdapter.get_instance()` at `src/adapters/fmu_adapter.py`
- **FMU Data Mapping**: Use `ReheatFMUData` at `src/adapters/fmu_data/reheat_fmu_data.py` for DTO-to-FMU variable mapping
- **Output Conversion**: Use `ReheatFMUData.create_outputs(values)` to convert FMU output dict to ReheatOutputs DTO
- **Custom Exceptions**: Use `FmuInstanceNotFoundError`, `FmuValidationError`, `FmuExecutionError` from `src/adapters/exceptions.py`
- **Per-Instance Locking**: FmuLifecycleManager handles asyncio.Lock per instance
- **Current Adapter Methods**:
  - `create_fmu_instance(sequence_type, fmu_data)` - returns auto-generated UUID instance_id
  - `update_fmu_instance(instance_id, fmu_data)` - sets inputs only (NOT parameters)
  - `step(instance_id, fmu_data, step_size)` - returns output dict
  - `delete_fmu_instance(instance_id)` - removes instance
  - `has_instance(instance_id)` - checks existence
- **Gap Identified**: Current adapter generates instance_id internally. Need `upsert_fmu_instance` with caller-provided instance_id.
- **Gap Identified**: Current `update_fmu_instance` only sets inputs, doesn't handle parameter changes. Upsert handles this by recreating.

[Source: stories/story-1.10-fmu-adapter-singleton.md#Dev-Agent-Record]

## Dev Agent Record

### Context Reference

- docs/feature-development/g36-implementation/stories/1-11-g36-controller.context.xml

### Agent Model Used

Claude Opus 4.5 (claude-opus-4-5-20251101)

### Debug Log References

N/A

### Completion Notes List

- All 9 tasks completed and verified
- 51 tests passing (22 DTO completeness + 13 controller unit + 16 router integration)
- All acceptance criteria satisfied:
  - AC1: POST /api/v1/g36/reheat/instances (upsert) implemented
  - AC2: POST /api/v1/g36/reheat/instances/{instance_id}/step implemented
  - AC3: DELETE /api/v1/g36/instances/{instance_id} (idempotent) implemented
  - AC4: All endpoints documented in OpenAPI (verified via integration tests)
  - AC5: Integration tests for all endpoints (16 tests)
  - AC6: DTO-to-FMU mapping verified with unit tests (22 tests)
- Unit conversion strategy: temperatureUnit and airflowUnit in ReheatInputsRequest
- FmuAdapter.upsert_fmu_instance() with UpsertResult dataclass

### File List

**Created:**

- `apps/control-sequence-api-app/src/controllers/g36_controller.py`
- `apps/control-sequence-api-app/src/routers/g36_router.py`
- `apps/control-sequence-api-app/tests/unit/test_controllers/test_g36_controller.py`
- `apps/control-sequence-api-app/tests/integration/test_g36_router.py`
- `apps/control-sequence-api-app/tests/unit/test_dto_fmu_completeness.py`

**Modified:**

- `apps/control-sequence-api-app/src/adapters/fmu_adapter.py` - Added upsert_fmu_instance(), UpsertResult
- `apps/control-sequence-api-app/src/dto/reheat_dto.py` - Added fmu_var metadata to all DTO fields
- `apps/control-sequence-api-app/src/main.py` - Registered g36_router
