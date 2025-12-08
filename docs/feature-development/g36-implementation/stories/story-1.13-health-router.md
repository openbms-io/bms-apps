# Story 1.13: Health Router

Status: ready-for-dev

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

- [ ] Task 1: Create Health Router (AC: #1, #4)

  - [ ] Create `src/routers/health_router.py`
  - [ ] Add GET /api/v1/health endpoint
  - [ ] Return HealthResponse with status, active_instances, service, version
  - [ ] Add docstring for OpenAPI documentation

- [ ] Task 2: Create Health DTOs (AC: #1)

  - [ ] Create `src/dto/health_dto.py` or add to common_dto.py
  - [ ] Define HealthResponse model with fields: status, active_instances, service, version

- [ ] Task 3: Integrate with FmuAdapter (AC: #1)

  - [ ] Inject FmuAdapter dependency to get active instance count
  - [ ] Use `len(adapter.list_instance_ids())` or add `instance_count()` method

- [ ] Task 4: Register Router in main.py (AC: #4)

  - [ ] Import health_router in main.py
  - [ ] Register with app.include_router(health_router)
  - [ ] Remove or deprecate existing /health endpoint in main.py

- [ ] Task 5: Unit Tests (AC: #1-3)

  - [ ] Create `tests/unit/test_routers/test_health_router.py`
  - [ ] Test health endpoint returns correct structure
  - [ ] Test active_instances reflects actual FMU instances
  - [ ] Verify response time <10ms

- [ ] Task 6: Integration Tests (AC: #1, #4)

  - [ ] Add health endpoint test to integration tests
  - [ ] Test health with 0 instances
  - [ ] Test health with active instances
  - [ ] Verify OpenAPI documentation includes health endpoint

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

(to be filled during implementation)

### Debug Log References

(to be filled during implementation)

### Completion Notes List

(to be filled during implementation)

### File List

(to be filled during implementation)
