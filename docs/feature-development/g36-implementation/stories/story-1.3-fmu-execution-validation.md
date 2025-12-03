# Story 1.3: FMU Execution & Validation

## Story

**As a** developer,
**I want to** execute the G36 FMU with sample inputs and validate outputs,
**So that** we confirm the FMU works correctly and understand performance characteristics.

## Status

- **Epic**: 1 - G36 Reheat FMU Block Foundation
- **Status**: done
- **Priority**: P0 (Critical Path)
- **Estimate**: 4 hours

## Context

This story validates that the G36 Reheat FMU produces reasonable control outputs given sample inputs. It also explores practical usage patterns like step timing, multiple instances, and error handling.

This story answers POC Questions #7-13:

- #7: What's the FMU step time semantics?
- #8: Can we run multiple FMU instances concurrently?
- #9: Do G36 outputs look reasonable?
- #10: Which inputs are truly required vs optional?
- #11: What's the FMU step execution time?
- #12: Memory footprint per FMU instance?
- #13: Error handling - what happens with invalid inputs?

## Acceptance Criteria

- [x] Set sample inputs (hardcoded values)
- [x] Step FMU and print outputs to console
- [x] Verify outputs (yDam, yVal) look reasonable (Question #9)
- [x] Test multiple steps with changing inputs
- [x] Answer: What's the step time semantics? (Question #7)
- [x] Answer: Which inputs are truly required? (Question #10)
- [x] Answer: Can we run multiple instances? (Question #8)
- [x] Capture step execution time (Question #11)
- [x] Capture memory footprint (Question #12)
- [x] Test invalid inputs - document behavior (Question #13)
- [x] Document Q7-13 findings in `apps/g36-api-app/docs/fmu-audit/reheat-terminal/`

## Technical Requirements

### Sample Input Values

Use realistic values in SI units (Kelvin for temps, m³/s for airflow):

```python
sample_inputs = {
    # Required Real inputs
    "TZon": 295.15,        # 22°C room temp
    "TCooSet": 297.15,     # 24°C cooling setpoint
    "THeaSet": 293.15,     # 20°C heating setpoint
    "TDis": 286.15,        # 13°C discharge air
    "VDis_flow": 0.1,      # 0.1 m³/s primary airflow
    "TSup": 286.15,        # 13°C AHU supply air
    "TSupSet": 285.15,     # 12°C AHU supply setpoint

    # Required Boolean inputs
    "u1Fan": True,         # AHU fan running

    # Required Integer inputs
    "uOpeMod": 1,          # Occupied mode
}
```

### Validation Scenarios

1. **Heating Scenario**

   - TZon < THeaSet (room too cold)
   - Expected: yVal > 0 (heating valve opens)

2. **Cooling Scenario**

   - TZon > TCooSet (room too warm)
   - Expected: yDam increases

3. **Satisfied Scenario**
   - THeaSet < TZon < TCooSet
   - Expected: Minimal control action

### Performance Measurements

```python
import time
import tracemalloc

# Step execution time
start = time.perf_counter()
fmu.doStep(...)
step_time = time.perf_counter() - start

# Memory footprint
tracemalloc.start()
# ... create FMU instance
current, peak = tracemalloc.get_traced_memory()
```

### Multi-Instance Test

```python
# Test concurrent instances
instances = []
for i in range(5):
    fmu = load_fmu(...)
    instances.append(fmu)

# Step all instances
for fmu in instances:
    fmu.doStep(...)
```

### Error Handling Tests

```python
# Test invalid inputs
test_cases = [
    {"TZon": None},           # None value
    {"TZon": -100},           # Impossible temperature
    {"uOpeMod": 99},          # Invalid mode
    {"VDis_flow": -1.0},      # Negative airflow
]

for inputs in test_cases:
    try:
        fmu.setInputs(inputs)
        fmu.doStep(...)
    except Exception as e:
        print(f"Input {inputs}: {type(e).__name__}: {e}")
```

### Expected Outputs

**Real Outputs:**
| Output | Description | Expected Range |
|--------|-------------|----------------|
| yDam | Damper position | 0.0 - 1.0 |
| yVal | Heating valve position | 0.0 - 1.0 |
| VSet_flow | Airflow setpoint | > 0 m³/s |

**Validation Criteria:**

- yDam and yVal should be within [0, 1]
- Control response should match scenario (heating/cooling/satisfied)
- No NaN or infinite values

## Dependencies

- Story 1.1: FMU Loading POC
- Story 1.2: FMU State & Lifecycle (understanding step behavior)

## Test Strategy

- Manual testing via script execution
- Console output for all scenarios
- Timing measurements printed to console
- Error behavior documented

## Definition of Done

1. All sample scenarios executed successfully
2. Outputs validated as reasonable
3. Performance metrics captured (execution time, memory)
4. Multi-instance test passed
5. Error handling behavior documented
6. All 7 POC questions (#7-13) answered
7. Findings added to README.md

## Dev Agent Record

### Context Reference

- `docs/feature-development/g36-implementation/stories/story-1.3-fmu-execution-validation.context.xml`

### Completion Notes

- Created `apps/g36-api-app/fmu-sequence/scripts/validate_fmu_execution.py` with 9 experiments
- All POC Questions #7-13 answered and documented
- Key findings: FMU uses simulated time, supports concurrent instances, ~0.1ms step time, ~177KB memory
- Documentation added to `apps/g36-api-app/docs/fmu-audit/reheat-terminal/reheat-terminal-behavior.md`

### File List

- `apps/g36-api-app/fmu-sequence/scripts/validate_fmu_execution.py` (created)
- `apps/g36-api-app/docs/fmu-audit/reheat-terminal/reheat-terminal-behavior.md` (updated)

## Notes

- Focus on G36 control behavior validation, not UI or integration
- Use hardcoded values - no BOPTEST integration in this POC
- Print all outputs to console for manual verification
- Document any unexpected behavior or edge cases
