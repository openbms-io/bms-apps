# Story 1.14: SHACL Validation Stub

Status: review

## Story

As a developer,
I want a SHACL validation stub endpoint,
So that the API structure supports future validation without blocking Epic 1.

## Acceptance Criteria

1. POST /api/v1/g36/validate endpoint exists
2. Endpoint returns stub response indicating always valid
3. Endpoint documented as "stub for future implementation" in OpenAPI

## Tasks / Subtasks

- [x] Task 1: Create Validation DTOs (AC: #2)

  - [x] Create `src/dto/validation_dto.py`
  - [x] Define ValidationRequest model (accepts graph data as dict/Any)
  - [x] Define ValidationResponse model with fields: valid (bool), errors (list), message (str)

- [x] Task 2: Create Validation Router (AC: #1, #3)

  - [x] Create `src/routers/validation_router.py`
  - [x] Add POST /api/v1/g36/validate endpoint
  - [x] Return ValidationResponse with valid=True, empty errors, message indicating stub
  - [x] Add docstring clearly marking endpoint as "Stub for future SHACL implementation"

- [x] Task 3: Register Router in main.py (AC: #1)

  - [x] Import validation_router in main.py
  - [x] Register with app.include_router(validation_router)

- [x] Task 4: Unit Tests (AC: #1-2)

  - [x] Create `tests/unit/test_routers/test_validation_router.py`
  - [x] Test validate endpoint returns 200
  - [x] Test response has valid=True
  - [x] Test response includes stub message

- [x] Task 5: Integration Tests (AC: #1, #3)

  - [x] Add validation endpoint test to integration tests
  - [x] Verify endpoint appears in OpenAPI documentation
  - [x] Verify endpoint docstring visible in /docs

## Dev Notes

### Purpose

This story creates a placeholder endpoint for SHACL validation. The full SHACL validation implementation is planned for Epic 3 (Two-Level Validation). This stub:

1. Establishes the API contract early
2. Allows Designer to integrate without blocking on full validation
3. Keeps the endpoint structure ready for future implementation

### Response Schema

Per Tech Spec UC7, the stub should return a validation result:

```json
{
  "valid": true,
  "errors": [],
  "message": "Validation stub - always returns valid. Full SHACL validation planned for Epic 3."
}
```

### Request Schema

The request can accept a generic graph structure. Since this is a stub, detailed validation of request structure is not required:

```json
{
  "graph": {
    "nodes": [...],
    "edges": [...]
  }
}
```

### Project Structure

Files to create:

- `apps/control-sequence-api-app/src/dto/validation_dto.py`
- `apps/control-sequence-api-app/src/routers/validation_router.py`
- `apps/control-sequence-api-app/tests/unit/test_routers/test_validation_router.py`

Files to modify:

- `apps/control-sequence-api-app/src/main.py` - Register validation_router

### References

- [Tech Spec UC7 - SHACL Validation Stub](../specs/control-sequence-api-tech-spec.md#uc7-shacl-validation-stub)
- [Tech Spec Endpoints Table](../specs/control-sequence-api-tech-spec.md#41-endpoints)
- [Epics Story 1.14](../epics.md#story-114-shacl-validation-stub)

### Learnings from Previous Story

**From Story 1-13-health-router (Status: done)**

- **Router Pattern**: Use FastAPI Depends for dependency injection (not needed here - no adapter dependency)
- **DTO Pattern**: Create dedicated dto file with Pydantic models
- **Router Registration**: Use `app.include_router(router)` in main.py
- **OpenAPI Docs**: Docstrings in route functions appear in /docs - critical for stub documentation
- **Test Pattern**: Unit tests mock dependencies, integration tests use TestClient with real app

[Source: stories/story-1.13-health-router.md#Dev-Agent-Record]

## Dev Agent Record

### Context Reference

- [1.14-shacl-validation-stub.context.xml](./1.14-shacl-validation-stub.context.xml)

### Agent Model Used

Claude Opus 4.5 (claude-opus-4-5-20251101)

### Debug Log References

N/A - Implementation straightforward, no debugging needed.

### Completion Notes List

- Implemented POST /api/v1/g36/validate endpoint following established router patterns from health_router.py
- Created ValidationRequest Pydantic model accepting generic graph structure (dict[str, Any])
- Created ValidationResponse Pydantic model with valid (bool), errors (list[str]), message (str) fields
- Stub returns valid=True with message explaining future Epic 3 implementation
- Docstring clearly documents endpoint as "Stub for future SHACL implementation"
- 8 unit tests covering response structure, request handling, and error validation
- 9 integration tests covering real app behavior and OpenAPI documentation verification
- All 174 tests pass (no regressions)
- Linting passes (ruff check)

### File List

**Created:**

- `apps/control-sequence-api-app/src/dto/validation_dto.py`
- `apps/control-sequence-api-app/src/routers/validation_router.py`
- `apps/control-sequence-api-app/tests/unit/test_routers/test_validation_router.py`
- `apps/control-sequence-api-app/tests/integration/test_validation_router.py`

**Modified:**

- `apps/control-sequence-api-app/src/main.py` (import validation_router, register router)
