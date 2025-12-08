# Story 1.13: Health Router

Status: done

## Story

As a developer,
I want a health check endpoint that reports API status and active FMU instance count,
So that we can monitor API health and track resource usage.

## Acceptance Criteria

1. GET /api/v1/health endpoint returns status and active_instances count
2. Response includes service name and version
3. Response time <10ms
4. Endpoint documented in OpenAPI

## Tasks / Subtasks

- [x] Task 1: Create Health Router (AC: #1, #4)

  - [x] Create `src/routers/health_router.py`
  - [x] Add GET /api/v1/health endpoint
  - [x] Return HealthResponse with status, active_instances, service, version
  - [x] Add docstring for OpenAPI documentation

- [x] Task 2: Create Health DTOs (AC: #1)

  - [x] Create `src/dto/health_dto.py`
  - [x] Define HealthResponse model with fields: status, active_instances, service, version

- [x] Task 3: Integrate with FmuAdapter (AC: #1)

  - [x] Inject FmuAdapter dependency to get active instance count
  - [x] Use `len(adapter.list_instance_ids())` for active instance count

- [x] Task 4: Register Router in main.py (AC: #4)

  - [x] Import health_router in main.py
  - [x] Register with app.include_router(health_router)
  - [x] Remove existing /health endpoint in main.py

- [x] Task 5: Unit Tests (AC: #1-3)

  - [x] Create `tests/unit/test_routers/test_health_router.py`
  - [x] Test health endpoint returns correct structure
  - [x] Test active_instances reflects actual FMU instances
  - [x] Verify response time <10ms

- [x] Task 6: Integration Tests (AC: #1, #4)

  - [x] Add health endpoint test to integration tests
  - [x] Test health with 0 instances
  - [x] Test health with active instances
  - [x] Verify OpenAPI documentation includes health endpoint

## Dev Notes

### Current State

There's already a basic `/health` endpoint in main.py:

```python
@app.get("/health", tags=["Health"])
async def health_check() -> dict[str, str]:
    return {
        "status": "healthy",
        "service": "control-sequence-api",
        "version": "0.1.0",
    }
```

This needs to be:

1. Moved to `/api/v1/health` path
2. Enhanced with `active_instances` count from FmuAdapter
3. Migrated to a dedicated router for consistency

### Response Schema

Per Tech Spec Section 4.1:

```json
{
  "status": "healthy",
  "active_instances": 5
}
```

Enhanced version (maintaining existing fields):

```json
{
  "status": "healthy",
  "service": "control-sequence-api",
  "version": "0.1.0",
  "active_instances": 5
}
```

### Getting Instance Count

FmuAdapter already has `list_instance_ids()` method:

```python
def list_instance_ids(self) -> list[str]:
    return list(self._lifecycle_managers.keys())
```

Health endpoint can use:

```python
adapter = FmuAdapter.get_instance()
active_instances = len(adapter.list_instance_ids())
```

### Project Structure

Files to create:

- `apps/control-sequence-api-app/src/routers/health_router.py`
- `apps/control-sequence-api-app/src/dto/health_dto.py` (optional, can use inline)
- `apps/control-sequence-api-app/tests/unit/test_routers/test_health_router.py`

Files to modify:

- `apps/control-sequence-api-app/src/main.py` - Register health_router, remove inline endpoint

### References

- [Tech Spec Section 4.1 - Endpoints](../specs/control-sequence-api-tech-spec.md#41-endpoints)
- [Epics Story 1.13](../epics.md#story-113-health-router)
- [Existing main.py](../../../../apps/control-sequence-api-app/src/main.py)
- [Existing FmuAdapter](../../../../apps/control-sequence-api-app/src/adapters/fmu_adapter.py)

### Learnings from Previous Story

**From Story 1-11-g36-controller (Status: done)**

- **Router Pattern**: Use FastAPI Depends for dependency injection
- **DI Example**: `controller: G36ReheatController = Depends(get_g36_reheat_controller)`
- **Router Registration**: Use `app.include_router(router)` in main.py
- **FmuAdapter Access**: Use `FmuAdapter.get_instance()` singleton
- **OpenAPI**: Docstrings in route functions appear in /docs
- **Test Pattern**: Use FastAPI TestClient for integration tests

[Source: stories/story-1.11-g36-controller.md#Dev-Agent-Record]

## Dev Agent Record

### Context Reference

- [1-13-health-router.context.xml](./1-13-health-router.context.xml)

### Agent Model Used

Claude Opus 4.5 (claude-opus-4-5-20251101)

### Debug Log References

N/A - Implementation straightforward, no debugging needed.

### Completion Notes

**Completed:** 2025-12-08
**Definition of Done:** All acceptance criteria met, code reviewed, tests passing

### Completion Notes List

- Implemented GET /api/v1/health endpoint following existing router patterns from g36_router.py
- Created HealthResponse Pydantic model with status, service, version, active_instances fields
- Used FastAPI Depends() for FmuAdapter injection following established DI pattern
- Removed inline /health endpoint from main.py to avoid duplicate routes
- 9 unit tests covering response structure, active instance count, and <10ms performance
- 13 integration tests covering real FmuAdapter singleton, OpenAPI documentation
- All 362 tests pass (no regressions)

### File List

**Created:**

- `apps/control-sequence-api-app/src/dto/health_dto.py`
- `apps/control-sequence-api-app/src/routers/health_router.py`
- `apps/control-sequence-api-app/tests/unit/test_routers/__init__.py`
- `apps/control-sequence-api-app/tests/unit/test_routers/test_health_router.py`
- `apps/control-sequence-api-app/tests/integration/test_health_router.py`

**Modified:**

- `apps/control-sequence-api-app/src/main.py` (import health_router, register router, remove inline endpoint)
