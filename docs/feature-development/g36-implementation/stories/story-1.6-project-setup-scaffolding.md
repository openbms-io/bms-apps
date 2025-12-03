# Story 1.6: Project Setup & Scaffolding

Status: done

## Story

As a developer,
I want to set up the control-sequence-api-app project structure,
so that we have a foundation for implementing the Control Sequence API.

## Acceptance Criteria

1. pyproject.toml with dependencies (FastAPI, FMPy, pydantic-settings, uvicorn)
2. MVC folder structure created: src/adapters/, src/config/, src/controllers/, src/dto/, src/models/, src/routers/
3. settings.py with pydantic-settings configuration (FMU paths, API host/port)
4. main.py with FastAPI app entry point and lifespan handler
5. App runs with `uvicorn` and serves `/docs` (Swagger UI)
6. Tests folder structure: tests/unit/, tests/integration/

## Tasks / Subtasks

- [x] Task 1: Create pyproject.toml (AC: #1)

  - [x] Add FastAPI, uvicorn dependencies
  - [x] Add FMPy dependency
  - [x] Add pydantic-settings dependency
  - [x] Add pytest, pytest-asyncio for testing
  - [x] Configure project metadata
  - [x] Add mypy, black, ruff dev dependencies

- [x] Task 2: Create MVC folder structure (AC: #2)

  - [x] Create src/adapters/ with **init**.py
  - [x] Create src/config/ with **init**.py
  - [x] Create src/controllers/ with **init**.py
  - [x] Create src/dto/ with **init**.py
  - [x] Create src/models/ with **init**.py
  - [x] Create src/routers/ with **init**.py

- [x] Task 3: Implement settings.py (AC: #3)

  - [x] Create Settings class with pydantic-settings
  - [x] Add API_HOST, API_PORT settings
  - [x] Add FMU_PATH_REHEAT setting with default path
  - [x] Add get_fmu_path() helper method
  - [x] Support .env file loading

- [x] Task 4: Implement main.py (AC: #4, #5)

  - [x] Create FastAPI app instance
  - [x] Add lifespan context manager for startup/shutdown
  - [x] Add FMU path validation at startup
  - [x] Configure CORS middleware
  - [x] Add placeholder health router

- [x] Task 5: Create test folder structure (AC: #6)

  - [x] Create tests/unit/ folder
  - [x] Create tests/integration/ folder
  - [x] Create tests/conftest.py with fixtures

- [x] Task 6: Verify app runs (AC: #5)
  - [x] Run uvicorn and verify /docs loads
  - [x] Verify settings load from environment

## Dev Notes

### Architecture Patterns

Follow building-semantics-api-app patterns exactly:

- pydantic-settings for configuration
- FastAPI lifespan for startup/shutdown hooks
- MVC structure with clear layer separation

### Configuration

Environment variables (from tech spec Section 3.3):
| Variable | Default | Description |
|----------|---------|-------------|
| `API_HOST` | `0.0.0.0` | API bind address |
| `API_PORT` | `8001` | API port |
| `FMU_PATH_REHEAT` | `apps/g36-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu` | Reheat FMU path |

### Key Design Decisions

- Lazy FMU loading: Startup validates files exist, extract on first use
- Port 8001 to avoid conflict with building-semantics-api (8000)

### Project Structure Notes

```
apps/control-sequence-api-app/
├── pyproject.toml
├── src/
│   ├── __init__.py
│   ├── main.py
│   ├── adapters/
│   │   └── __init__.py
│   ├── config/
│   │   ├── __init__.py
│   │   └── settings.py
│   ├── controllers/
│   │   └── __init__.py
│   ├── dto/
│   │   └── __init__.py
│   ├── models/
│   │   └── __init__.py
│   └── routers/
│       └── __init__.py
└── tests/
    ├── __init__.py
    ├── conftest.py
    ├── unit/
    │   └── __init__.py
    └── integration/
        └── __init__.py
```

### References

- [Tech Spec Section 3.1 - MVC Structure](./specs/control-sequence-api-tech-spec.md#31-mvc-structure)
- [Tech Spec Section 3.3 - Configuration](./specs/control-sequence-api-tech-spec.md#33-configuration)
- [building-semantics-api-app settings.py](../../apps/building-semantics-api-app/src/config/settings.py)

### Learnings from Previous Story

**From Story 1.5 (Status: done)**

- Tech spec created at `specs/control-sequence-api-tech-spec.md` - use as authoritative reference
- Follow building-semantics-api-app patterns exactly
- App name: control-sequence-api-app (renamed from g36-api-app)

[Source: stories/story-1.5-control-sequence-api-tech-spec.md#Dev-Agent-Record]

## Dev Agent Record

### Context Reference

- [story-1.6-project-setup-scaffolding.context.xml](./story-1.6-project-setup-scaffolding.context.xml)

### Agent Model Used

Claude Opus 4

### Debug Log References

### Completion Notes List

- Renamed `apps/g36-api-app` to `apps/control-sequence-api-app` per tech spec constraint C8
- FMU path updated to `apps/control-sequence-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu`
- Added pnpm scripts in root package.json: `control-sequence:install`, `control-sequence:run`, `control-sequence:test`, etc.
- Updated `scripts/setup-python-venvs.js` to include control-sequence-api-app venv setup
- Health endpoint at `/health` returns service name "control-sequence-api"

### File List

- `apps/control-sequence-api-app/pyproject.toml` - Project dependencies and configuration
- `apps/control-sequence-api-app/src/__init__.py`
- `apps/control-sequence-api-app/src/main.py` - FastAPI app entry point with lifespan handler
- `apps/control-sequence-api-app/src/adapters/__init__.py`
- `apps/control-sequence-api-app/src/config/__init__.py`
- `apps/control-sequence-api-app/src/config/settings.py` - pydantic-settings configuration
- `apps/control-sequence-api-app/src/controllers/__init__.py`
- `apps/control-sequence-api-app/src/dto/__init__.py`
- `apps/control-sequence-api-app/src/models/__init__.py`
- `apps/control-sequence-api-app/src/routers/__init__.py`
- `apps/control-sequence-api-app/tests/__init__.py`
- `apps/control-sequence-api-app/tests/conftest.py` - Test fixtures
- `apps/control-sequence-api-app/tests/unit/__init__.py`
- `apps/control-sequence-api-app/tests/integration/__init__.py`
- `package.json` - Added control-sequence scripts
- `scripts/setup-python-venvs.js` - Added control-sequence-api-app to venv setup
