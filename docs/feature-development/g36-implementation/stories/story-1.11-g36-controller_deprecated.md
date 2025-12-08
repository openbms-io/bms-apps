# Story 1.11: G36 Controller

Status: ready-for-dev

## Story

As a developer,
I want a controller that orchestrates FMU adapter calls,
So that business logic is separated from routing.

## Acceptance Criteria

1. g36_controller.py with business logic layer
2. Validates inputs before calling adapter
3. Handles errors and returns appropriate responses
4. Unit tests for controller logic

## Tasks / Subtasks

- [ ] Task 1: Create G36 Controller Class (AC: #1)

  - [ ] Create `src/controllers/g36_controller.py`
  - [ ] Implement G36Controller class
  - [ ] Inject FmuAdapter dependency (use singleton)
  - [ ] Define controller methods matching use cases

- [ ] Task 2: Implement create_instance() (AC: #1, #3)

  - [ ] Method signature: `create_instance(instance_id: str, sequence_type: SequenceType, parameters: ReheatParameters | None) -> CreateInstanceResponse`
  - [ ] Call FmuAdapter.create_instance()
  - [ ] Handle FmuExecutionError, return appropriate response
  - [ ] Return CreateInstanceResponse with instance_id and created flag

- [ ] Task 3: Implement update_instance() (AC: #1, #3)

  - [ ] Method signature: `update_instance(instance_id: str, parameters: ReheatParameters) -> UpdateInstanceResponse`
  - [ ] Call FmuAdapter.update_instance()
  - [ ] Handle FmuInstanceNotFoundError → raise HTTPException 404
  - [ ] Return UpdateInstanceResponse with instance_id and updated flag

- [ ] Task 4: Implement step() (AC: #1, #2, #3)

  - [ ] Method signature: `step(instance_id: str, inputs: ReheatInputs, step_size: float) -> StepResponse`
  - [ ] Validate inputs using ReheatFMUData (required input completeness)
  - [ ] Call FmuAdapter.step()
  - [ ] Handle FmuInstanceNotFoundError → raise HTTPException 404
  - [ ] Handle FmuValidationError → raise HTTPException 400 with detail
  - [ ] Handle FmuExecutionError → raise HTTPException 500
  - [ ] Return StepResponse with instance_id and ReheatOutputs

- [ ] Task 5: Implement delete_instance() (AC: #1, #3)

  - [ ] Method signature: `delete_instance(instance_id: str) -> DeleteInstanceResponse`
  - [ ] Call FmuAdapter.delete_instance()
  - [ ] Idempotent - success even if not found
  - [ ] Return DeleteInstanceResponse with instance_id and deleted flag

- [ ] Task 6: Create Response DTOs (AC: #3)

  - [ ] Create `src/dto/response_dto.py` (or add to common_dto.py)
  - [ ] CreateInstanceResponse: instance_id, created (bool)
  - [ ] UpdateInstanceResponse: instance_id, updated (bool)
  - [ ] StepResponse: instance_id, outputs (ReheatOutputs)
  - [ ] DeleteInstanceResponse: instance_id, deleted (bool)

- [ ] Task 7: Unit Tests (AC: #4)

  - [ ] Create `tests/unit/test_g36_controller.py`
  - [ ] Test create_instance success
  - [ ] Test create_instance idempotent (duplicate returns success)
  - [ ] Test update_instance success
  - [ ] Test update_instance not found raises 404
  - [ ] Test step success returns outputs
  - [ ] Test step with invalid inputs raises 400
  - [ ] Test step not found raises 404
  - [ ] Test delete_instance success
  - [ ] Test delete_instance idempotent (not found returns success)
  - [ ] Mock FmuAdapter for unit tests

## Dev Notes

### Architecture Pattern

Controller layer per tech spec Section 3.2 - orchestrates adapter calls and handles error mapping:

```python
class G36Controller:
    def __init__(self, fmu_adapter: FmuAdapter | None = None):
        self._adapter = fmu_adapter or FmuAdapter()

    async def create_instance(
        self,
        instance_id: str,
        sequence_type: SequenceType,
        parameters: ReheatParameters | None = None
    ) -> CreateInstanceResponse:
        # Business logic + error handling
        pass
```

### Error Mapping

Map adapter exceptions to HTTP responses:

| Adapter Exception        | HTTP Status | Response                                                      |
| ------------------------ | ----------- | ------------------------------------------------------------- |
| FmuInstanceNotFoundError | 404         | `{"error": "not_found", "detail": "Instance {id} not found"}` |
| FmuValidationError       | 400         | `{"error": "validation_error", "detail": "..."}`              |
| FmuExecutionError        | 500         | `{"error": "fmu_error", "detail": "..."}`                     |

### Input Validation

Controller validates inputs before adapter call. Use ReheatFMUData to verify all required inputs:

```python
async def step(self, instance_id: str, inputs: ReheatInputs, step_size: float) -> StepResponse:
    # ReheatFMUData validates completeness when constructing input_variables
    fmu_data = ReheatFMUData(inputs=inputs)
    required_names = ReheatFMUData.required_input_names()

    # FmuAdapter.step() handles the actual FMU interaction
    outputs = await self._adapter.step(instance_id, fmu_data, step_size)
    return StepResponse(instance_id=instance_id, outputs=outputs)
```

### Project Structure

Files to create:

- `apps/control-sequence-api-app/src/controllers/g36_controller.py` - Controller class
- `apps/control-sequence-api-app/src/dto/response_dto.py` - Response DTOs
- `apps/control-sequence-api-app/tests/unit/test_g36_controller.py` - Unit tests

### Testing Standards

Per project TDD workflow:

1. Write failing test first
2. Implement to make test pass
3. Verify with `pnpm control-sequence:test`

Mock FmuAdapter for unit tests:

```python
@pytest.fixture
def mock_adapter(mocker):
    adapter = mocker.MagicMock(spec=FmuAdapter)
    adapter.create_instance = mocker.AsyncMock(return_value=None)
    adapter.step = mocker.AsyncMock(return_value=mock_outputs)
    return adapter
```

### References

- [Tech Spec Section 3.2 - Component Responsibilities](../specs/control-sequence-api-tech-spec.md#32-component-responsibilities)
- [Tech Spec Section 4.3 - Error Handling](../specs/control-sequence-api-tech-spec.md#43-error-handling)
- [Existing fmu_adapter.py](../../../../apps/control-sequence-api-app/src/adapters/fmu_adapter.py)
- [Existing exceptions.py](../../../../apps/control-sequence-api-app/src/adapters/exceptions.py)
- [Existing reheat_dto.py](../../../../apps/control-sequence-api-app/src/dto/reheat_dto.py)

### Learnings from Previous Story

**From Story 1-10-fmu-adapter-singleton (Status: done)**

- **New Adapter Layer Created**: Use `FmuAdapter` singleton at `src/adapters/fmu_adapter.py` - supports create_instance(), update_instance(), step(), delete_instance()
- **FMU Data Mapping**: Use `ReheatFMUData` at `src/adapters/fmu_data/reheat_fmu_data.py` for clean DTO-to-FMU variable mapping
- **Custom Exceptions**: Use `FmuInstanceNotFoundError`, `FmuValidationError`, `FmuExecutionError` from `src/adapters/exceptions.py`
- **Per-Instance Locking**: FmuAdapter handles asyncio.Lock per instance - controller doesn't need to manage concurrency
- **55 Parameters Verified**: All ReheatParameters (55), ReheatInputs (17), ReheatOutputs (15) are 1:1 mapped with FMU variables
- **Testing Setup**: Unit tests at `tests/unit/test_fmu_adapter.py` - follow patterns established there

[Source: stories/story-1.10-fmu-adapter-singleton.md#Dev-Agent-Record]

## Dev Agent Record

### Context Reference

- [story-1.11-g36-controller.context.xml](./story-1.11-g36-controller.context.xml)

### Agent Model Used

(to be filled during implementation)

### Debug Log References

(to be filled during implementation)

### Completion Notes List

(to be filled during implementation)

### File List

(to be filled during implementation)
