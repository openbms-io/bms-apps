# Story 1.15: Parameter Storage & Instance Management

Status: done

## Story

As a developer,
I want persistent storage for G36 instance parameters,
So that configuration survives server restarts and new instances get sensible defaults.

## Acceptance Criteria

1. SQLite database stores instance parameters with `instance_id` as primary key
2. POST /reheat/instances creates instance with default parameters
3. GET /reheat/instances/{id} returns stored parameters
4. PUT /reheat/instances/{id} updates parameters only
5. Unit conversion moved to ReheatFMUData (store user units, convert at FMU boundary)
6. ReheatParameters and ReheatInputs moved from dto/ to models/
7. Unit tests for database adapter and instance model
8. Integration tests for new endpoints

## Tasks / Subtasks

- [x] Task 1: Create Database Adapter (AC: #1)

  - [x] Create `src/adapters/database_adapter.py`
  - [x] Use SQLAlchemy async with aiosqlite (pattern from bms-iot-app/sqlmodel_client.py)
  - [x] Implement `create_async_engine` with WAL mode
  - [x] Implement `get_session()` async context manager
  - [x] Implement `initialize_database()` for table creation
  - [x] Database file location: `data/g36.db`

- [x] Task 2: Create Domain Models (AC: #6)

  - [x] Create `src/models/reheat/` package with parameters, inputs, outputs, enums
  - [x] Move ReheatParameters from dto/ with unit fields (temperatureUnit, airflowUnit)
  - [x] Move ReheatInputs from dto/ with unit fields
  - [x] Keep ReheatOutputs in models/
  - [x] Add TemperatureUnit enum (CELSIUS, FAHRENHEIT, KELVIN)
  - [x] Add AirflowUnit enum (M3_PER_S, CFM, L_PER_S)
  - [x] Change temperature defaults from Kelvin to Celsius

- [x] Task 3: Create Repository Pattern (AC: #1)

  - [x] Create `src/repositories/base.py` with generic ControlSequenceRepository
  - [x] Create `src/repositories/reheat_repository.py` for ReheatParameters
  - [x] Fields: id (PK), instance_id (unique), parameters (JSON), created_at, updated_at
  - [x] Implement CRUD methods: create, get_active, save, delete, list_active

- [x] Task 4: Update ReheatFMUData with Unit Conversion (AC: #5)

  - [x] Add unit conversion to `src/adapters/fmu_data/reheat_fmu_data.py`
  - [x] Create `src/utils/unit_conversion.py` with temp_to_kelvin, airflow_to_m3_per_s
  - [x] Convert in `input_variables` property
  - [x] Convert in `configuration_variables` property

- [x] Task 5: Update DTOs for API Layer (AC: #2, #3, #4)

  - [x] Create `src/dto/base_dto.py` with generic CreateInstanceResponse, DeleteInstanceResponse
  - [x] Update `src/dto/reheat_dto.py` with StepRequest, StepResponse, UpdateParametersRequest
  - [x] Generic typing allows reuse across sequence types

- [x] Task 6: Update G36 Router Endpoints (AC: #2, #3, #4)

  - [x] Rename g36_router.py → g36_vav_reheat_router.py
  - [x] POST /api/v1/g36/vav-reheat/instances creates with auto-generated UUID
  - [x] GET /api/v1/g36/vav-reheat/instances/{instance_id} returns parameters
  - [x] PUT /api/v1/g36/vav-reheat/instances/{instance_id} updates params
  - [x] POST /api/v1/g36/vav-reheat/instances/{instance_id}/step executes FMU
  - [x] DELETE /api/v1/g36/vav-reheat/instances/{instance_id} idempotent delete
  - [x] Inject repository via FastAPI Depends

- [x] Task 7: Update main.py for Database Initialization (AC: #1)

  - [x] Import database_adapter
  - [x] Add lifespan event to initialize database
  - [x] Ensure WAL mode enabled on startup

- [x] Task 8: Unit Tests for Controller (AC: #7)

  - [x] Create `tests/unit/test_controllers/test_vav_reheat_controller.py`
  - [x] Test create instance with auto-generated ID
  - [x] Test step returns outputs
  - [x] Test delete idempotent behavior

- [x] Task 9: Integration Tests for Repository (AC: #7)

  - [x] Create `tests/integration/test_repositories/test_reheat_repository.py`
  - [x] Test create, get, save, delete, list operations
  - [x] Test soft delete with is_active flag

- [x] Task 10: Unit Tests for Unit Conversion (AC: #5, #7)

  - [x] Tests in `tests/unit/test_dto/test_dto_conversion.py`
  - [x] Test Celsius to Kelvin conversion
  - [x] Test Fahrenheit to Kelvin conversion
  - [x] Test CFM to m³/s conversion
  - [x] Test L/s to m³/s conversion

- [x] Task 11: Integration Tests for Endpoints (AC: #8)

  - [x] Create `tests/integration/test_vav_reheat_router.py`
  - [x] Test POST creates instance with defaults
  - [x] Test GET returns stored parameters
  - [x] Test PUT updates parameters only
  - [x] Test round-trip: POST → PUT → GET returns updated values
  - [x] Test DELETE removes instance
  - [x] Test step with lazy FMU creation

## Dev Notes

### Purpose

This story implements persistent storage for G36 instance parameters per ADR-001. Key decisions:

1. **Store user units** - DB preserves original values + unit preference
2. **Convert at FMU boundary** - ReheatFMUData handles all unit conversion
3. **Round-trip safe** - GET returns exactly what was PUT
4. **Defaults on creation** - New instances get sensible defaults (Celsius, m³/s)

### Architecture

```
API Layer                    Domain/Storage Layer         FMU Layer
─────────────────────────────────────────────────────────────────────
Router + DTOs            →   Models (stored)          →   ReheatFMUData
(request/response)           (ReheatParameters,           (converts to SI)
                             ReheatInputs)
```

### Database Pattern (from bms-iot-app)

```python
from sqlalchemy.ext.asyncio import AsyncSession, create_async_engine, async_sessionmaker
from sqlalchemy import text
import contextlib

DATABASE_URL = "sqlite+aiosqlite:///data/g36.db"

engine = create_async_engine(
    DATABASE_URL,
    connect_args={"timeout": 30, "check_same_thread": False},
)

async_session = async_sessionmaker(engine, class_=AsyncSession, expire_on_commit=False)

async def initialize_database():
    async with engine.begin() as conn:
        await conn.execute(text("PRAGMA journal_mode=WAL;"))
        await conn.execute(text("PRAGMA synchronous=NORMAL;"))
        # Create tables
        await conn.run_sync(Base.metadata.create_all)

@contextlib.asynccontextmanager
async def get_session():
    async with async_session() as session:
        yield session
```

### Test Fixture Pattern (from bms-iot-app/tests/conftest.py)

```python
import pytest_asyncio
from sqlalchemy import select

@pytest_asyncio.fixture(scope="session", autouse=True)
async def setup_database():
    """Initialize database tables before running tests."""
    engine = get_engine()
    async with engine.begin() as conn:
        await conn.run_sync(Base.metadata.create_all)
    await initialize_database()

@pytest_asyncio.fixture
async def cleanup_database():
    """Cleanup database before and after each test for isolation."""
    async def _cleanup():
        async with get_session() as session:
            result = await session.execute(select(G36InstanceTable))
            instances = result.scalars().all()
            for instance in instances:
                await session.delete(instance)
            await session.commit()

    await _cleanup()  # Before test
    yield
    await _cleanup()  # After test
```

### API Flow

```
1. POST /reheat/instances
   Body: { "instance_id": "zone-1" }
   → Creates DB record with ReheatParameters() defaults
   → Creates FMU instance with defaults
   → Returns { instance_id, parameters: defaults }

2. GET /reheat/instances/zone-1
   → Reads from DB
   → Returns { instance_id, parameters }

3. PUT /reheat/instances/zone-1
   Body: { "parameters": { "hasCO2Sensor": false, ... } }
   → Updates DB record
   → Recreates FMU with new params
   → Returns { instance_id, parameters }

4. POST /reheat/instances/zone-1/step
   Body: { "stepSize": 60, "inputs": { ... } }
   → ReheatFMUData converts inputs to SI
   → Executes FMU step
   → Returns { outputs }
```

### Unit Conversion in ReheatFMUData

```python
def temp_in_kelvin(value: float, unit: TemperatureUnit) -> float:
    match unit:
        case TemperatureUnit.KELVIN:
            return value
        case TemperatureUnit.CELSIUS:
            return value + 273.15
        case TemperatureUnit.FAHRENHEIT:
            return (value - 32) * 5/9 + 273.15

def airflow_in_m3_per_s(value: float, unit: AirflowUnit) -> float:
    match unit:
        case AirflowUnit.M3_PER_S:
            return value
        case AirflowUnit.CFM:
            return value * 0.000471947  # 1 CFM = 0.000471947 m³/s
        case AirflowUnit.L_PER_S:
            return value / 1000  # 1 L/s = 0.001 m³/s
```

### Files to Create

```
apps/control-sequence-api-app/
├── src/
│   ├── models/
│   │   ├── __init__.py
│   │   ├── reheat_models.py           # ReheatParameters, ReheatInputs, ReheatOutputs
│   │   └── g36_instance_model.py      # G36InstanceTable + CRUD
│   ├── adapters/
│   │   └── database_adapter.py        # SQLAlchemy async adapter
│   └── dto/
│       └── reheat_dto.py              # MODIFY: API DTOs only
└── data/
    └── g36.db                         # Created at runtime
```

### References

- [ADR-001: Parameter Storage Strategy](../specs/ADR-001-parameter-storage-strategy.md)
- [Tech Spec Section 4.1](../specs/control-sequence-api-tech-spec.md#41-endpoints)
- [bms-iot-app/sqlmodel_client.py](../../../../apps/bms-iot-app/src/network/sqlmodel_client.py)

### Learnings from Previous Story

**From Story 1.14 (Status: done)**

- **Router Pattern**: Use FastAPI Depends for dependency injection
- **DTO Pattern**: Create dedicated dto file with Pydantic models
- **Router Registration**: Use `app.include_router(router)` in main.py
- **Test Pattern**: Unit tests mock dependencies, integration tests use TestClient with real app
- **All 174 tests pass** - no regressions introduced

## Dev Agent Record

### Context Reference

- [1-15-parameter-storage-instance-management.context.xml](./1-15-parameter-storage-instance-management.context.xml)

### Agent Model Used

Claude Opus 4.5

### Completion Notes List

1. **Database Layer**: SQLite with async SQLAlchemy, WAL mode, repository pattern
2. **Lazy FMU Creation**: FMU instance created on first `step()` call, not on create
3. **Generic DTOs**: `CreateInstanceResponse[T]`, `DeleteInstanceResponse` in base_dto.py
4. **Unit Conversion**: Handled at FMU boundary in ReheatFMUData
5. **All 399 tests passing** (127 unit + 272 integration)

### File List

**New Files:**

- `src/adapters/database_adapter.py` - Async SQLAlchemy adapter with WAL mode
- `src/repositories/base.py` - Generic repository protocol
- `src/repositories/reheat_repository.py` - ReheatParameters repository
- `src/dto/base_dto.py` - Generic response DTOs
- `src/models/reheat/` - Domain models (parameters, inputs, outputs, enums, calculated_parameters)
- `src/utils/unit_conversion.py` - Temperature and airflow conversion
- `tests/unit/test_controllers/test_vav_reheat_controller.py`
- `tests/integration/test_repositories/test_reheat_repository.py`
- `tests/integration/test_vav_reheat_router.py` (renamed from test_g36_router.py)

**Modified:**

- `src/controllers/vav_reheat_controller.py` - Repository integration, lazy FMU creation
- `src/routers/g36_vav_reheat_router.py` - All CRUD endpoints
- `src/dependencies.py` - Repository injection
- `src/main.py` - Database initialization in lifespan
- `tests/conftest.py` - Shared fixtures (integration_client, fmu_available)

## Change Log

| Date       | Change                                           |
| ---------- | ------------------------------------------------ |
| 2025-12-08 | Story drafted from epics.md                      |
| 2025-12-12 | Story completed - all ACs met, 399 tests passing |
