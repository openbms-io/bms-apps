# FMU Audit: G36 VAV Reheat Terminal Unit Controller

## FMU Identity

| Field           | Value                                                                                                                                                                                               |
| --------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Model**       | [Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller](https://github.com/lbl-srg/modelica-buildings/blob/master/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo) |
| **Source**      | LBL modelica-buildings library                                                                                                                                                                      |
| **Local FMU**   | `apps/g36-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu`                                                                                                                                      |
| **FMI Version** | 2.0 Co-Simulation                                                                                                                                                                                   |
| **Audit Date**  | 2025-11-27                                                                                                                                                                                          |

## Behavior Characteristics

### State Management

**Finding**: FMU manages state through **simulation time progression**. The G36 controller has integral terms that accumulate based on error duration, but this is deterministic based on simulation time, not step history.

**Evidence**:

- Damper position (yDam) shows integral action: 0.09 → 0.30 → 0.62 → 1.0 over 4 steps with sustained cooling demand
- Same inputs at same simulation time produce identical outputs regardless of step size
- 4 x 300s steps produces same result as 1 x 1200s step

### Pure Function Behavior

**Finding**: FMU is a **PURE FUNCTION of (inputs, simulation_time)**.

**Evidence**:

- Same inputs at same simulation time always produce same outputs
- Fresh FMU with single 1200s step matches FMU with 4 x 300s steps at t=1200s
- Outputs are deterministic and reproducible

### Execution Model

**Finding**: FMU is **STEP-ON-DEMAND**. Uses **SIMULATED TIME**, not real-time.

**Evidence**:

- `doStep(stepSize=300)` advances 300 seconds of simulated time
- Wall clock time is ~0.2-1.3ms regardless of step size (60s to 3600s)
- FMU waits for doStep() calls, does not run continuously

### State Persistence

**Finding**: State save/restore is **NOT SUPPORTED** by this FMU.

**Evidence**:

```
canGetAndSetFMUstate: False
canSerializeFMUstate: False
```

**Workaround**: Track cumulative simulation time per zone in database. On restart, replay to last known simulation time with single large step.

## FMU Capabilities

```
canGetAndSetFMUstate: False
canSerializeFMUstate: False
canHandleVariableCommunicationStepSize: True
canInterpolateInputs: True
maxOutputDerivativeOrder: 1
```

## I/O Summary

| Category          | Count | Examples                                               |
| ----------------- | ----- | ------------------------------------------------------ |
| Inputs (Real)     | 7     | TZon, TCooSet, THeaSet, TDis, VDis_flow, TSup, TSupSet |
| Inputs (Boolean)  | 1     | u1Fan                                                  |
| Inputs (Integer)  | 1     | uOpeMod (1-7)                                          |
| Outputs (Real)    | 3     | yDam (0-1), yVal (0-1), VSet_flow                      |
| Outputs (Integer) | 6     | yZonTemResReq, yZonPreResReq, yLowFloAla, etc.         |
| Parameters        | 42    | venStd, VAreBreZon_flow, VMin_flow, etc.               |

## Performance Metrics

| Operation                          | Time           |
| ---------------------------------- | -------------- |
| FMU instantiate + initialize       | ~5-8 ms        |
| doStep (any step size)             | ~0.2-0.4 ms    |
| Single instance pattern (10 steps) | ~286 ms total  |
| Fresh per call pattern (10 calls)  | ~57 ms total\* |

\*Fresh per call reuses extracted FMU directory, first call takes ~280ms to extract.

## API Design Implications

| Aspect             | Recommendation                                           |
| ------------------ | -------------------------------------------------------- |
| Instance lifecycle | Session-based (single instance per zone) for performance |
| State tracking     | Track simulation_time in database                        |
| Crash recovery     | Replay to last simulation_time on restart                |
| Real-time sync     | Not required - simulated time is independent             |

## POC Questions #7-13: Execution & Validation

### Q7: Step Time Semantics

**Finding**: FMU uses **SIMULATED TIME**. `doStep(stepSize=300)` advances 300 seconds of simulated time, not real time.

**Evidence**: Wall clock time is ~0.1-0.4ms regardless of step size (60s to 3600s). See Story 1.2 for full analysis.

### Q8: Multiple Concurrent Instances

**Finding**: **YES** - Multiple FMU instances can run concurrently without interference.

**Evidence**:

```
Created 5 concurrent FMU instances
Zone 1 (TZon=291.15K): yDam=0.1433, yVal=1.0000
Zone 2 (TZon=293.15K): yDam=0.0000, yVal=0.0000
Zone 3 (TZon=295.15K): yDam=0.0000, yVal=0.0000
Zone 4 (TZon=297.15K): yDam=0.0000, yVal=0.0000
Zone 5 (TZon=299.15K): yDam=0.2467, yVal=0.0000
All instances terminated cleanly
```

### Q9: G36 Output Validation

**Finding**: Outputs are **REASONABLE** and match expected control behavior.

| Scenario  | Condition                      | Expected       | Actual         | Result |
| --------- | ------------------------------ | -------------- | -------------- | ------ |
| Heating   | TZon=291.15K < THeaSet=293.15K | yVal > 0       | yVal=1.0000    | ✓ PASS |
| Cooling   | TZon=299.15K > TCooSet=297.15K | yDam increases | yDam: 0.25→1.0 | ✓ PASS |
| Satisfied | THeaSet < TZon < TCooSet       | Minimal action | yDam=0, yVal=0 | ✓ PASS |

**Validation**:

- yDam and yVal always in [0, 1] range
- Controller responds correctly to changing inputs
- No NaN or infinite values observed

### Q10: Required vs Optional Inputs

**Finding**: All inputs have **FMU defaults**, but explicit setting is recommended.

**Core Inputs (9 total)**:
| Input | Type | Default Behavior | Recommendation |
|-------|------|------------------|----------------|
| TZon | Real | Uses FMU default | Always set |
| TCooSet | Real | Uses FMU default | Always set |
| THeaSet | Real | Uses FMU default | Always set |
| TDis | Real | Uses FMU default | Always set |
| VDis_flow | Real | Uses FMU default | Always set |
| TSup | Real | Uses FMU default | Always set |
| TSupSet | Real | Uses FMU default | Always set |
| u1Fan | Boolean | Uses FMU default | Always set |
| uOpeMod | Integer | Uses FMU default | Always set |

### Q11: Step Execution Time

**Finding**: Average step time is **~0.1 ms**.

**Evidence**:

```
Measured 20 step executions:
  Average: 0.105 ms
  Min:     0.104 ms
  Max:     0.118 ms
```

**Throughput**: Can process ~9,500 zones per second at 300s step size.

### Q12: Memory Footprint

**Finding**: ~**177 KB** tracked Python memory per instance, peak ~465 KB.

**Evidence**:

```
Memory tracking (Python tracemalloc):
  FMU instance creation: ~177 KB
  Peak during operation: ~465 KB
  After cleanup: ~186 KB
```

**Note**: Actual FMU memory in C/Fortran not fully tracked. Practical estimate: ~1-2 MB per instance including native memory.

### Q13: Error Handling

**Finding**: FMU **accepts invalid inputs without exceptions**. Pre-validation recommended.

**Test Results**:
| Test Case | Input | Result |
|-----------|-------|--------|
| Negative temp | TZon=-100 | Accepted, outputs produced |
| Zero airflow | VDis_flow=0 | Accepted, outputs produced |
| Negative airflow | VDis_flow=-1 | Accepted, outputs produced |
| Invalid mode | uOpeMod=99 | Accepted, outputs produced |
| Extreme high temp | TZon=1000 | Accepted, outputs produced |

**Recommendation**: Validate inputs BEFORE calling FMU to ensure reasonable behavior.

## Test Scripts

### Story 1.2: Lifecycle Exploration (Q1-4)

```bash
python apps/g36-api-app/fmu-sequence/scripts/explore_lifecycle.py \
  apps/g36-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu
```

### Story 1.3: Execution Validation (Q7-13)

```bash
python apps/g36-api-app/fmu-sequence/scripts/validate_fmu_execution.py \
  apps/g36-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu
```
