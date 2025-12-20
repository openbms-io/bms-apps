# ADR-001: G36 Parameter Storage Strategy

**Status:** Accepted
**Date:** 2025-12-08
**Decision Makers:** Amol

## Context

G36 control sequences require persistent storage for parameters. Data must survive server restarts and provide sensible defaults for new instances.

## Decision

**Store G36 parameters in SQLite database, preserving user-selected units. Convert to SI at FMU execution boundary.**

### Architecture

```
API Layer                    Domain/Storage Layer         FMU Layer
─────────────────────────────────────────────────────────────────────
Router + DTOs            →   Models (stored)          →   ReheatFMUData
(request/response)           (ReheatParameters,           (converts to SI)
                             ReheatInputs)
```

| Layer  | Location             | Models                             | Purpose                        |
| ------ | -------------------- | ---------------------------------- | ------------------------------ |
| API    | `dto/`               | Request/Response DTOs              | API validation, OpenAPI schema |
| Domain | `models/`            | `ReheatParameters`, `ReheatInputs` | Business logic, stored in DB   |
| FMU    | `adapters/fmu_data/` | `ReheatFMUData`                    | Converts to SI for FMU         |

### Key Principles

1. **Store what user entered** - DB preserves original values + unit preference
2. **Convert at FMU boundary** - `ReheatFMUData` handles all unit conversion
3. **Round-trip safe** - GET returns exactly what was PUT
4. **Defaults on creation** - New instances get sensible defaults

## API Design

### Endpoints

| Method | Endpoint                      | Purpose              | Input                  | Output                        |
| ------ | ----------------------------- | -------------------- | ---------------------- | ----------------------------- |
| POST   | `/reheat/instances`           | Create with defaults | `{ instance_id }`      | `{ instance_id, parameters }` |
| GET    | `/reheat/instances/{id}`      | Get params           | -                      | `{ instance_id, parameters }` |
| PUT    | `/reheat/instances/{id}`      | Update params        | `{ parameters }`       | `{ instance_id, parameters }` |
| DELETE | `/instances/{id}`             | Delete instance      | -                      | `{ deleted: true }`           |
| POST   | `/reheat/instances/{id}/step` | Execute FMU          | `{ stepSize, inputs }` | `{ outputs }`                 |

### Flow

```
1. POST /reheat/instances
   Body: { "instance_id": "zone-1" }
   → Creates DB record with ReheatParameters() defaults
   → Creates FMU instance with defaults
   → Returns { instance_id, parameters: defaults }

2. PUT /reheat/instances/zone-1
   Body: { "parameters": { "hasCO2Sensor": false, ... } }
   → Updates DB record
   → Recreates FMU with new params
   → Returns { instance_id, parameters }

3. POST /reheat/instances/zone-1/step
   Body: { "stepSize": 60, "inputs": { live sensor data } }
   → ReheatFMUData converts inputs to SI
   → Executes FMU step
   → Returns { outputs }
```

### Data Separation

- **Parameters** (stored) - Configuration that persists (sensor flags, controller gains, setpoints)
- **Inputs** (runtime) - Live sensor readings passed at step time (not stored)

## Database Schema

```python
class G36InstanceTable(SQLModel, table=True):
    __tablename__ = "g36_instances"

    instance_id: str = Field(primary_key=True)
    sequence_type: str  # "reheat", future: "vav", "ahu"
    parameters: dict = Field(sa_type=JSON)  # ReheatParameters as dict
    created_at: datetime
    updated_at: datetime
```

## Model Changes Required

### ReheatParameters - Add Unit Fields

Move from `dto/reheat_dto.py` to `models/reheat_models.py`:

```python
class ReheatParameters(BaseModel):
    # Unit selection (stored with parameters)
    temperatureUnit: TemperatureUnit = Field(default=TemperatureUnit.CELSIUS)
    airflowUnit: AirflowUnit = Field(default=AirflowUnit.M3_PER_S)

    # Temperature fields - now in user's unit (default: Celsius)
    dischargeAirTempMin: float = Field(default=10.0)  # Was 283.15 K

    # Airflow fields - user's unit (default: m³/s)
    minAirflow: float = Field(default=0.3)

    # ... rest unchanged (dimensionless, time in seconds)
```

### ReheatInputs - Add Defaults

Move from `dto/reheat_dto.py` to `models/reheat_models.py`:

```python
class ReheatInputs(BaseModel):
    temperatureUnit: TemperatureUnit = Field(default=TemperatureUnit.CELSIUS)
    airflowUnit: AirflowUnit = Field(default=AirflowUnit.M3_PER_S)

    zoneTemperature: float = Field(default=22.0)  # Celsius
    coolingSetpoint: float = Field(default=24.0)
    heatingSetpoint: float = Field(default=20.0)
    dischargeAirTemperature: float = Field(default=16.0)
    primaryAirflow: float = Field(default=0.3)  # m³/s
    supplyAirTemperature: float = Field(default=13.0)
    supplyAirTemperatureSetpoint: float = Field(default=12.0)
    fanStatus: bool = Field(default=True)
    operationMode: OperationMode = Field(default=OperationMode.OCCUPIED)
    # ... other fields with defaults
```

### ReheatFMUData - Add Conversion

Move conversion logic to `ReheatFMUData`:

```python
@dataclass(frozen=True, slots=True)
class ReheatFMUData:
    inputs: ReheatInputs
    parameters: ReheatParameters | None = None

    @property
    def input_variables(self) -> list[FmuVariable]:
        i = self.inputs
        temp_unit = i.temperatureUnit
        airflow_unit = i.airflowUnit

        return [
            FmuVariable(ReheatInputVar.ZONE_TEMP,
                       temp_in_kelvin(i.zoneTemperature, temp_unit)),
            FmuVariable(ReheatInputVar.PRIMARY_AIRFLOW,
                       airflow_in_m3_per_s(i.primaryAirflow, airflow_unit)),
            # ...
        ]

    @property
    def configuration_variables(self) -> list[FmuVariable]:
        p = self.parameters
        temp_unit = p.temperatureUnit
        airflow_unit = p.airflowUnit

        return [
            FmuVariable(ReheatParameterVar.DISCHARGE_AIR_TEMP_MIN,
                       temp_in_kelvin(p.dischargeAirTempMin, temp_unit)),
            FmuVariable(ReheatParameterVar.MIN_AIRFLOW,
                       airflow_in_m3_per_s(p.minAirflow, airflow_unit)),
            # ...
        ]
```

## Implementation Tasks

1. **Create `models/reheat_models.py`** - Move `ReheatParameters`, `ReheatInputs` from dto
2. **Modify `ReheatParameters`** - Add `temperatureUnit`, `airflowUnit` fields; change temp defaults to Celsius
3. **Modify `ReheatInputs`** - Add defaults to all required fields; add unit fields
4. **Modify `ReheatFMUData`** - Add unit conversion in `input_variables` and `configuration_variables`
5. **Update `dto/reheat_dto.py`** - Keep only API request/response DTOs, import models
6. **Create database adapter** - SQLite with WAL mode
7. **Create `models/g36_instance_model.py`** - Domain model with CRUD + defaults
8. **Modify `g36_router.py`** - Split POST into POST (create) + PUT (update)

## Files to Modify/Create

```
apps/control-sequence-api-app/
├── src/
│   ├── models/
│   │   ├── reheat_models.py           # CREATE: ReheatParameters, ReheatInputs, ReheatOutputs
│   │   └── g36_instance_model.py      # CREATE: Instance CRUD + defaults
│   ├── dto/
│   │   └── reheat_dto.py              # MODIFY: Keep only API DTOs (requests/responses)
│   ├── adapters/
│   │   ├── fmu_data/
│   │   │   └── reheat_fmu_data.py     # MODIFY: Add unit conversion
│   │   └── database_adapter.py        # CREATE: SQLite adapter
│   └── routers/
│       └── g36_router.py              # MODIFY: POST/PUT separation
└── data/
    └── g36.db                         # Created at runtime
```

## Layer Responsibilities

| Layer                | Contains                                               | Responsibility                        |
| -------------------- | ------------------------------------------------------ | ------------------------------------- |
| `dto/`               | `CreateInstanceRequest`, `StepRequest`, `StepResponse` | API shape, OpenAPI docs               |
| `models/`            | `ReheatParameters`, `ReheatInputs`, `ReheatOutputs`    | Domain logic, validation, defaults    |
| `adapters/fmu_data/` | `ReheatFMUData`                                        | FMU variable mapping, unit conversion |
| `adapters/`          | `DatabaseAdapter`                                      | SQLite persistence                    |

## Alternatives Considered

### Option B: Store in SI Units

Convert to Kelvin/m³/s before storage, convert back on read.

- ❌ Rejected: User confusion ("I entered 22°C, why does GET return 295.15?")

### Option C: Dual Storage

Store both user units and SI values.

- ❌ Rejected: Data duplication, sync complexity

### Option D: Fixed Units (No Selection)

Always use Celsius + m³/s, no unit fields.

- ❌ Rejected: Less flexible for US users (CFM common)

## References

- Pattern: `apps/building-semantics-api-app/src/models/systems_model.py`
- Current ReheatParameters: `apps/control-sequence-api-app/src/dto/reheat_dto.py:80`
- Current ReheatInputs: `apps/control-sequence-api-app/src/dto/reheat_dto.py:554`
- ReheatFMUData: `apps/control-sequence-api-app/src/adapters/fmu_data/reheat_fmu_data.py`
