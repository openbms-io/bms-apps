# Story 1.15: Parameter Storage & Instance Management

Status: ready-for-dev

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

- [ ] Task 1: Create Database Adapter (AC: #1)

  - [ ] Create `src/adapters/database_adapter.py`
  - [ ] Use SQLAlchemy async with aiosqlite (pattern from bms-iot-app/sqlmodel_client.py)
  - [ ] Implement `create_async_engine` with WAL mode
  - [ ] Implement `get_session()` async context manager
  - [ ] Implement `initialize_database()` for table creation
  - [ ] Database file location: `data/g36.db`

- [ ] Task 2: Create Domain Models (AC: #6)

  - [ ] Create `src/models/reheat_models.py`
  - [ ] Move ReheatParameters from dto/ with unit fields (temperatureUnit, airflowUnit)
  - [ ] Move ReheatInputs from dto/ with unit fields
  - [ ] Keep ReheatOutputs in models/
  - [ ] Add TemperatureUnit enum (CELSIUS, FAHRENHEIT, KELVIN)
  - [ ] Add AirflowUnit enum (M3_PER_S, CFM, L_PER_S)
  - [ ] Change temperature defaults from Kelvin to Celsius

- [ ] Task 3: Create Instance Table Model (AC: #1)

  - [ ] Create `src/models/g36_instance_model.py`
  - [ ] Define G36InstanceTable SQLAlchemy model
  - [ ] Fields: instance_id (PK), sequence_type, parameters (JSON), created_at, updated_at
  - [ ] Implement CRUD methods: create, get, update, delete, list

- [ ] Task 4: Update ReheatFMUData with Unit Conversion (AC: #5)

  - [ ] Add unit conversion to `src/adapters/fmu_data/reheat_fmu_data.py`
  - [ ] Create `temp_in_kelvin(value, unit)` helper
  - [ ] Create `airflow_in_m3_per_s(value, unit)` helper
  - [ ] Convert in `input_variables` property
  - [ ] Convert in `configuration_variables` property

- [ ] Task 5: Update DTOs for API Layer (AC: #2, #3, #4)

  - [ ] Update `src/dto/reheat_dto.py` to import models from models/
  - [ ] Create CreateInstanceRequest (instance_id only)
  - [ ] Create CreateInstanceResponse (instance_id + parameters)
  - [ ] Create UpdateParametersRequest (parameters only)
  - [ ] Create GetInstanceResponse (instance_id + parameters)

- [ ] Task 6: Update G36 Router Endpoints (AC: #2, #3, #4)

  - [ ] Modify POST /api/v1/g36/reheat/instances to create with defaults
  - [ ] Add GET /api/v1/g36/reheat/instances/{instance_id}
  - [ ] Modify PUT /api/v1/g36/reheat/instances/{instance_id} to update params only
  - [ ] Inject database adapter via FastAPI Depends
  - [ ] Store parameters in DB, then create/update FMU instance

- [ ] Task 7: Update main.py for Database Initialization (AC: #1)

  - [ ] Import database_adapter
  - [ ] Add startup event to initialize database
  - [ ] Ensure WAL mode enabled on startup

- [ ] Task 8: Unit Tests for Database Adapter (AC: #7)

  - [ ] Create `tests/unit/test_adapters/test_database_adapter.py`
  - [ ] Test engine creation with WAL mode
  - [ ] Test session context manager
  - [ ] Test database initialization

- [ ] Task 9: Unit Tests for Instance Model (AC: #7)

  - [ ] Create `tests/unit/test_models/test_g36_instance_model.py`
  - [ ] Test create instance with defaults
  - [ ] Test get instance
  - [ ] Test update instance parameters
  - [ ] Test delete instance

- [ ] Task 10: Unit Tests for Unit Conversion (AC: #5, #7)

  - [ ] Create `tests/unit/test_adapters/test_reheat_fmu_data_conversion.py`
  - [ ] Test Celsius to Kelvin conversion
  - [ ] Test Fahrenheit to Kelvin conversion
  - [ ] Test CFM to m³/s conversion
  - [ ] Test L/s to m³/s conversion

- [ ] Task 11: Integration Tests for Endpoints (AC: #8)

  - [ ] Create `tests/integration/test_instance_management.py`
  - [ ] Test POST creates instance with defaults
  - [ ] Test GET returns stored parameters
  - [ ] Test PUT updates parameters only
  - [ ] Test round-trip: POST → PUT → GET returns updated values
  - [ ] Test DELETE removes instance

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

(To be filled after implementation)

### Debug Log References

(To be filled after implementation)

### Completion Notes List

(To be filled after implementation)

### File List

(To be filled after implementation)

## Change Log

| Date       | Change                      |
| ---------- | --------------------------- |
| 2025-12-08 | Story drafted from epics.md |
