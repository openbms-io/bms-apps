# Story 1.10: FMU Adapter Singleton

Status: ready-for-dev

## Story

As a developer,
I want an FMU adapter that manages FMU instance lifecycle,
So that the API can create, step, and delete FMU instances.

## Acceptance Criteria

1. fmu_adapter.py with singleton pattern
2. create_instance(instance_id, parameters) method
3. update_instance(instance_id, parameters) method (resets FMU)
4. step(instance_id, inputs, step_size) method
5. delete_instance(instance_id) method
6. Per-instance asyncio.Lock for thread safety
7. Lazy FMU loading with startup validation
8. Unit tests for adapter
9. Input completeness validation - verify ALL required inputs are provided before FMU step, throw descriptive error identifying missing inputs

## Tasks / Subtasks

- [ ] Task 1: Create FMU Instance Model (AC: #1)

  - [ ] Create `src/models/fmu_instance.py`
  - [ ] Define FmuInstance dataclass with fmu, model_description, unzip_dir, current_time, lock
  - [ ] Define FmuInstanceState enum (CREATED, INITIALIZED, RUNNING, TERMINATED)
  - [ ] Add value_references dict for input/output variable refs

- [ ] Task 2: Create FMU Adapter Singleton (AC: #1, #7)

  - [ ] Create `src/adapters/fmu_adapter.py`
  - [ ] Implement FmuAdapter class with singleton pattern
  - [ ] Add \_instances: dict[str, FmuInstance] for instance storage
  - [ ] Add \_fmu_cache: dict[str, tuple[ModelDescription, str]] for lazy FMU loading
  - [ ] Implement startup validation - verify FMU files exist
  - [ ] Lazy extract FMU on first use per sequence type

- [ ] Task 3: Implement create_instance() (AC: #2)

  - [ ] Create FMU instance using FMPy
  - [ ] Setup experiment with startTime=0.0
  - [ ] Enter/exit initialization mode
  - [ ] Store in \_instances dict with instance_id key
  - [ ] Handle idempotent create (return success if exists)
  - [ ] Apply parameters (VCooMax, VHeaMax, VMin) if provided

- [ ] Task 4: Implement update_instance() (AC: #3)

  - [ ] Terminate existing FMU instance
  - [ ] Create new FMU instance with new parameters
  - [ ] Preserve instance_id
  - [ ] Reset current_time to 0.0
  - [ ] Raise error if instance not found

- [ ] Task 5: Implement Input Validation (AC: #9)

  - [ ] Create validate_inputs() method
  - [ ] Get required input variable names from model description
  - [ ] Check ALL required inputs are provided in ReheatInputs
  - [ ] Raise descriptive ValidationError listing each missing input
  - [ ] Validate before any FMU operation in step()

- [ ] Task 6: Implement step() (AC: #4, #6, #9)

  - [ ] Acquire per-instance asyncio.Lock
  - [ ] Call validate_inputs() - fail fast with descriptive error
  - [ ] Set all inputs on FMU (map ReheatInputs fields to FMU variable refs)
  - [ ] Call fmu.doStep(current_time, step_size)
  - [ ] Update current_time += step_size
  - [ ] Read outputs (yDam, yVal, VSet_flow)
  - [ ] Return ReheatOutputs
  - [ ] Raise error if instance not found

- [ ] Task 7: Implement delete_instance() (AC: #5)

  - [ ] Terminate FMU instance
  - [ ] Free FMU resources
  - [ ] Remove from \_instances dict
  - [ ] Handle idempotent delete (success if not found)

- [ ] Task 8: Add Helper Methods

  - [ ] get_instance(instance_id) - returns FmuInstance or raises NotFound
  - [ ] list_instances() - returns list of instance_ids
  - [ ] get_active_count() - returns count of active instances

- [ ] Task 9: Unit Tests (AC: #8, #9)
  - [ ] Create `tests/unit/test_fmu_adapter.py`
  - [ ] Test singleton pattern (same instance returned)
  - [ ] Test create_instance with default parameters
  - [ ] Test create_instance with custom parameters
  - [ ] Test create_instance idempotent (duplicate create succeeds)
  - [ ] Test update_instance resets state
  - [ ] Test update_instance not found raises error
  - [ ] Test step returns valid outputs
  - [ ] Test step with missing inputs raises descriptive error
  - [ ] Test step validates ALL inputs before FMU call
  - [ ] Test step not found raises error
  - [ ] Test delete_instance removes instance
  - [ ] Test delete_instance idempotent (not found succeeds)
  - [ ] Test per-instance lock (concurrent steps serialized)
  - [ ] Mock FMPy for unit tests (no actual FMU needed)

## Dev Notes

### Architecture Pattern

Singleton adapter pattern per tech spec Section 3.4:

```python
class FmuAdapter:
    _instance: "FmuAdapter | None" = None
    _instances: dict[str, FmuInstance] = {}

    def __new__(cls) -> "FmuAdapter":
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance
```

### FMU Variable References

From POC findings, the FMU uses value references to identify variables:

```python
def _build_value_refs(self, md: ModelDescription) -> dict[str, int]:
    """Build mapping from variable name to value reference."""
    refs = {}
    for var in md.modelVariables:
        refs[var.name] = var.valueReference
    return refs
```

### Input/Output Mapping

Map ReheatInputs (API) to FMU variable names:

| ReheatInputs Field           | FMU Variable |
| ---------------------------- | ------------ |
| zoneTemperature              | TZon         |
| coolingSetpoint              | TCooSet      |
| heatingSetpoint              | THeaSet      |
| dischargeAirTemperature      | TDis         |
| primaryAirflow               | VDis_flow    |
| supplyAirTemperature         | TSup         |
| supplyAirTemperatureSetpoint | TSupSet      |
| fanStatus                    | u1Fan        |
| operationMode                | uOpeMod      |

Map FMU outputs to ReheatOutputs (API):

| FMU Variable | ReheatOutputs Field |
| ------------ | ------------------- |
| yDam         | damperPosition      |
| yVal         | valvePosition       |
| VSet_flow    | airflowSetpoint     |

### Input Completeness Validation

Critical: FMU accepts invalid/missing inputs silently (POC Q13). Must validate ALL inputs before step:

```python
def validate_inputs(self, inputs: ReheatInputs, instance: FmuInstance) -> None:
    """Validate all required inputs are provided."""
    required_inputs = ["TZon", "TCooSet", "THeaSet", "TDis", "VDis_flow",
                       "TSup", "TSupSet", "u1Fan", "uOpeMod"]

    missing = []
    for fmu_var in required_inputs:
        api_field = self._fmu_to_api_field(fmu_var)
        if getattr(inputs, api_field, None) is None:
            missing.append(fmu_var)

    if missing:
        raise ValidationError(
            f"Missing required FMU inputs: {', '.join(missing)}. "
            f"All 9 inputs must be provided for step execution."
        )
```

### Per-Instance Locking

Each instance has its own asyncio.Lock to allow parallel steps across different instances:

```python
@dataclass
class FmuInstance:
    fmu: FMU2Slave
    model_description: ModelDescription
    unzip_dir: str
    current_time: float
    lock: asyncio.Lock
    value_refs: dict[str, int]
```

### Lazy FMU Loading

Extract FMU only on first create for that sequence type:

```python
def _get_or_extract_fmu(self, sequence_type: str) -> tuple[ModelDescription, str]:
    if sequence_type not in self._fmu_cache:
        fmu_path = settings.get_fmu_path(sequence_type)
        md = read_model_description(fmu_path)
        unzip_dir = extract(fmu_path)
        self._fmu_cache[sequence_type] = (md, unzip_dir)
    return self._fmu_cache[sequence_type]
```

### Error Types

Define custom exceptions:

```python
class FmuInstanceNotFoundError(Exception):
    """Raised when instance_id does not exist."""
    pass

class FmuValidationError(Exception):
    """Raised when input validation fails."""
    pass

class FmuExecutionError(Exception):
    """Raised when FMU step fails."""
    pass
```

### Project Structure

Files to create:

- `apps/control-sequence-api-app/src/models/fmu_instance.py` - FmuInstance dataclass
- `apps/control-sequence-api-app/src/adapters/fmu_adapter.py` - Singleton adapter
- `apps/control-sequence-api-app/tests/unit/test_fmu_adapter.py` - Unit tests

### Testing Standards

Per project TDD workflow:

1. Write failing test first
2. Implement to make test pass
3. Verify with `pytest tests/ -v`

Mock FMPy for unit tests - no actual FMU file needed:

```python
@pytest.fixture
def mock_fmpy(mocker):
    mock_md = mocker.MagicMock()
    mock_md.modelVariables = [...]
    mocker.patch("fmpy.read_model_description", return_value=mock_md)
    mocker.patch("fmpy.extract", return_value="/tmp/fmu")
    # ... mock FMU2Slave
```

### References

- [Tech Spec Section 3.4 - Key Design Decisions](../specs/control-sequence-api-tech-spec.md#34-key-design-decisions)
- [POC Findings - Code Examples](../specs/poc-findings.md#code-examples)
- [POC Findings - Q13 Error Handling](../specs/poc-findings.md#q13-error-handling---what-happens-with-invalid-inputs)
- [Existing reheat_dto.py](../../../../apps/control-sequence-api-app/src/dto/reheat_dto.py)
- [Existing settings.py](../../../../apps/control-sequence-api-app/src/config/settings.py)

### Learnings from Previous Story

**From Story 1.8 (Status: done)**

Key patterns established:

- Separated API layer (`ReheatInputsRequest`) from internal FMU layer (`ReheatInputs`)
- ReheatInputs has all temperatures validated in Kelvin (250-350K)
- `ReheatInputs.from_request()` handles temperature unit conversion
- Use ReheatInputs (internal) for adapter, not ReheatInputsRequest (API)
- ReheatOutputs for step response (damperPosition, valvePosition, airflowSetpoint)

[Source: stories/story-1-8-reheat-dtos-validation.md]

## Dev Agent Record

### Context Reference

- [1-10-fmu-adapter-singleton.context.xml](./1-10-fmu-adapter-singleton.context.xml)

### Agent Model Used

(to be filled during implementation)

### Debug Log References

(to be filled during implementation)

### Completion Notes List

(to be filled during implementation)

### File List

(to be filled during implementation)
