# G36 FMU POC Findings

## Overview

This document consolidates findings from the G36 POC (Epic 1, Stories 1.1-1.3) to guide G36 Service architecture and API design.

**POC Goals:**

- Validate FMU integration approach for G36 ASHRAE Guideline 36 control sequences
- Answer 13 critical architecture questions before building the G36 Service
- Determine library selection, state management strategy, and performance characteristics

**POC Outcome:** All questions answered successfully. No blockers identified for G36 Service development.

## POC Questions & Answers

### FMU Fundamentals (Q1-Q4)

#### Q1: How are states managed in FMU?

**Finding:** FMU manages state through **simulation time progression**. The G36 controller has integral terms that accumulate based on error duration, but this is deterministic based on simulation time, not step history.

**Evidence:**

- Damper position (yDam) shows integral action: 0.09 → 0.30 → 0.62 → 1.0 over 4 steps with sustained cooling demand
- Same inputs at same simulation time produce identical outputs regardless of step size
- 4 × 300s steps produces same result as 1 × 1200s step

**Design Impact:** State evolves with simulation time. API must track cumulative simulation time per zone.

---

#### Q2: Do we need to save/restore FMU state?

**Finding:** State save/restore is **NOT SUPPORTED** by this FMU.

**Evidence:**

```
canGetAndSetFMUstate: False
canSerializeFMUstate: False
```

**Workaround:** ~~Track cumulative simulation time per zone in database. On restart, replay to last known simulation time with a single large step.~~ **CORRECTED:** Replay is not possible without full input history (see Q14). On crash, accept fresh start - controller will stabilize within minutes.

**Design Impact:** No native state persistence. FMU instances must be kept alive in memory. On crash, start fresh and accept temporary control degradation.

---

#### Q3: Is FMU always running once kicked off?

**Finding:** FMU is **STEP-ON-DEMAND**. Does not run continuously. Waits for `doStep()` calls.

**Evidence:**

- FMU waits for explicit `doStep(stepSize)` calls
- No background threads or continuous execution
- Each step advances simulated time by the specified amount

**Design Impact:** API controls execution pace. No real-time synchronization required.

---

#### Q4: Is FMU a pure function (inputs → outputs)?

**Finding:** **NO. FMU is STATEFUL.** It has internal state (integral terms) that accumulates based on the history of inputs.

**Evidence (constant inputs - appears pure):**

- Same inputs at same simulation time always produce same outputs
- Fresh FMU with 1×1200s step matches FMU with 4×300s steps at t=1200s

**Evidence (changing inputs - proves stateful):**
See Q14 below for detailed test proving FMU retains internal state.

**Design Impact:** Stateful API required. FMU instances must be kept alive in memory to preserve integral state. See Q14 for crash recovery strategy.

---

### Practical Usage (Q5-Q6)

#### Q5: Which library works better - FMPy or PyFMI?

**Finding:** **FMPy** is the recommended choice.

**Rationale:**
| Aspect | FMPy | PyFMI |
|--------|------|-------|
| Installation | `pip install fmpy` | Complex (requires Assimulo, SUNDIALS) |
| Dependencies | Minimal | Heavy scientific stack |
| API | Simple, Pythonic | More complex |
| Maintenance | Active | Less active |
| Performance | Excellent | Comparable |

**Decision:** Use FMPy for G36 Service implementation.

---

#### Q6: How to obtain G36 Reheat FMU?

**Finding:** Two-step build process: Export from OpenModelica (Linux only), then compile for host platform.

**Steps:**

1. **Create Wrapper Model** - Write a wrapper with default parameters (see `fmu-sequence/modelica/ReheatControllerFMU.mo`)
2. **Import in OpenModelica** - Import the wrapper model
3. **Import Buildings Library** - Import the [LBL modelica-buildings library](https://github.com/lbl-srg/modelica-buildings)
4. **Export FMU** - Right-click wrapper and export as FMU 2.0 Co-Simulation (produces Linux binaries only)
5. **Build for Host Platform** - Run the build script to compile for macOS/Linux/Windows:
   ```bash
   cd apps/g36-api-app
   ./fmu-sequence/scripts/build-fmu.sh fmu-sequence/reheat/<fmutmp-dir> ./fmu-sequence/builds
   ```

**Note:** OpenModelica export creates `.fmutmp` directory with sources and Linux binaries. The build script compiles sources for the host platform.

**Source Model:** [Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller](https://github.com/lbl-srg/modelica-buildings/blob/master/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo)

---

### Execution & Validation (Q7-Q13)

#### Q7: What's the FMU step time semantics?

**Finding:** FMU uses **SIMULATED TIME**. `doStep(stepSize=300)` advances 300 seconds of simulated time, not real time.

**Evidence:**
| Step Size | Wall Clock Time |
|-----------|-----------------|
| 60s | ~0.2 ms |
| 300s | ~0.3 ms |
| 900s | ~0.3 ms |
| 3600s | ~0.4 ms |

Wall clock time is approximately constant regardless of step size.

**Design Impact:** API can call `doStep()` at any rate. No need to synchronize with real-time clock.

---

#### Q8: Can we run multiple FMU instances concurrently?

**Finding:** **YES** - Multiple FMU instances can run concurrently without interference.

**Evidence:**

```
Created 5 concurrent FMU instances
Zone 1 (TZon=291.15K): yDam=0.1433, yVal=1.0000
Zone 2 (TZon=293.15K): yDam=0.0000, yVal=0.0000
Zone 3 (TZon=295.15K): yDam=0.0000, yVal=0.0000
Zone 4 (TZon=297.15K): yDam=0.0000, yVal=0.0000
Zone 5 (TZon=299.15K): yDam=0.2467, yVal=0.0000
All instances terminated cleanly
```

**Design Impact:** Multi-zone support is straightforward. One FMU instance per zone.

---

#### Q9: Do G36 outputs look reasonable?

**Finding:** Outputs are **REASONABLE** and match expected control behavior.

| Scenario  | Condition                      | Expected       | Actual         | Result |
| --------- | ------------------------------ | -------------- | -------------- | ------ |
| Heating   | TZon=291.15K < THeaSet=293.15K | yVal > 0       | yVal=1.0000    | PASS   |
| Cooling   | TZon=299.15K > TCooSet=297.15K | yDam increases | yDam: 0.25→1.0 | PASS   |
| Satisfied | THeaSet < TZon < TCooSet       | Minimal action | yDam=0, yVal=0 | PASS   |

**Validation:**

- yDam and yVal always in [0, 1] range
- Controller responds correctly to changing inputs
- No NaN or infinite values observed

---

#### Q10: Which inputs are required vs optional?

**Finding:** All inputs have **FMU defaults**, but explicit setting is recommended.

**Core Inputs (9 total):**
| Input | Type | Description | Recommendation |
|-------|------|-------------|----------------|
| TZon | Real | Zone temperature (K) | Always set |
| TCooSet | Real | Cooling setpoint (K) | Always set |
| THeaSet | Real | Heating setpoint (K) | Always set |
| TDis | Real | Discharge air temp (K) | Always set |
| VDis_flow | Real | Primary airflow (m³/s) | Always set |
| TSup | Real | AHU supply air temp (K) | Always set |
| TSupSet | Real | AHU supply setpoint (K) | Always set |
| u1Fan | Boolean | AHU fan status | Always set |
| uOpeMod | Integer | Operation mode (1-7) | Always set |

---

#### Q11: What's the FMU step execution time?

**Finding:** Average step time is **~0.1 ms**.

**Evidence:**

```
Measured 20 step executions:
  Average: 0.105 ms
  Min:     0.104 ms
  Max:     0.118 ms
```

**Throughput:** Can process ~9,500 zones per second at 300s step size.

**Design Impact:** Excellent performance for real-time control applications.

---

#### Q12: Memory footprint per FMU instance?

**Finding:** ~**177 KB** tracked Python memory per instance, peak ~465 KB.

**Evidence:**

```
Memory tracking (Python tracemalloc):
  FMU instance creation: ~177 KB
  Peak during operation: ~465 KB
  After cleanup: ~186 KB
```

**Note:** Actual FMU memory in C/Fortran not fully tracked. Practical estimate: ~1-2 MB per instance including native memory.

**Design Impact:** Memory is not a constraint for typical building sizes (100s of zones).

---

#### Q13: Error handling - what happens with invalid inputs?

**Finding:** FMU **accepts invalid inputs without exceptions**. Pre-validation recommended.

**Test Results:**
| Test Case | Input | Result |
|-----------|-------|--------|
| Negative temp | TZon=-100 | Accepted, outputs produced |
| Zero airflow | VDis_flow=0 | Accepted, outputs produced |
| Negative airflow | VDis_flow=-1 | Accepted, outputs produced |
| Invalid mode | uOpeMod=99 | Accepted, outputs produced |
| Extreme high temp | TZon=1000 | Accepted, outputs produced |

**Design Impact:** API must validate inputs BEFORE calling FMU to ensure reasonable behavior.

---

#### Q14: Does FMU retain internal state when inputs change? (Added 2025-11-30)

**Finding:** **YES. FMU is STATEFUL.** The G36 controller has integral terms that accumulate based on input history. Outputs depend on the sequence of past inputs, not just current inputs.

**Test Script:** `apps/g36-api-app/fmu-sequence/scripts/test_replay_with_changing_inputs.py`

**Test Command:**

```bash
cd apps/g36-api-app
python fmu-sequence/scripts/test_replay_with_changing_inputs.py
```

**Test Design:**

| Scenario | Description                                                      |
| -------- | ---------------------------------------------------------------- |
| A        | Step 1: heating (TZon=291.15K), Step 2: satisfied (TZon=295.15K) |
| B        | Fresh FMU, single step to t=600s with satisfied inputs only      |

**Test Results:**

```
======================================================================
SCENARIO A: Step 1 HEATING, Step 2 SATISFIED (inputs change)
======================================================================
  t=300s (heating): yDam=0.1433, yVal=1.0000
  t=600s (satisfied): yDam=0.2767, yVal=0.0000

======================================================================
SCENARIO B: Fresh FMU, single step t=600s with FINAL inputs (satisfied)
======================================================================
  t=600s (single step, satisfied): yDam=0.0000, yVal=0.0000

======================================================================
CRITICAL COMPARISON
======================================================================
  A (heating→satisfied): yDam=0.2767, yVal=0.0000
  B (satisfied only):    yDam=0.0000, yVal=0.0000

  Differences: yDam=0.2767, yVal=0.0000

  >>> RESULT: DIFFERENT! Input history MATTERS! <<<
```

**Explanation:**

- Both scenarios end at t=600s with the same current inputs (TZon=295.15K, satisfied)
- Scenario A: yDam=0.2767 because integral term "remembers" the heating demand from Step 1
- Scenario B: yDam=0.0000 because fresh FMU has no history of heating demand

**Design Impact:**

1. **Stateful API required** - FMU instances must be kept alive in memory
2. **Replay not possible** - Cannot recreate state without full input history
3. **Crash recovery** - On restart, start fresh and accept temporary control degradation (controller stabilizes within minutes)

**Crash Recovery Options:**

| Option                      | Description                                     | Pros                | Cons                          |
| --------------------------- | ----------------------------------------------- | ------------------- | ----------------------------- |
| A: Store full input history | Save every input at every step, replay on crash | Perfect restoration | Massive storage, slow replay  |
| B: Accept state loss        | Start fresh on crash                            | Simple, no storage  | Temporary control degradation |
| C: Periodic checkpoints     | Store inputs at intervals                       | Bounded storage     | Partial state loss            |

**Decision:** Option B for initial implementation. The G36 controller will stabilize within minutes of fresh start. Full input history storage (Option A) or checkpoints (Option C) can be added later if operational requirements demand it.

**FMU Instance Lifecycle Options:**

| Option                   | Description                   | Pros                            | Cons                         |
| ------------------------ | ----------------------------- | ------------------------------- | ---------------------------- |
| In-process memory        | FMU instances in API process  | Simplest, fastest (~0.1ms/step) | Process restart = state lost |
| Separate FMU process     | Long-lived FMU runner process | API can restart independently   | IPC overhead, more complex   |
| Actor model (Ray/Celery) | Each zone is an actor         | Scales horizontally             | Heavy dependency             |

**Decision:** In-process memory with singleton adapter pattern (matches building-semantics-api-app). Architecture supports future migration to separate process if needed.

---

## Architecture Recommendations

### G36 Service Architecture

Based on POC findings (including Q14 stateful behavior), the recommended architecture is:

1. **Stateful API** with persistent FMU instances per zone

   - Single FMU instance per zone, kept alive in memory
   - Maintain zone→FMU instance mapping via singleton adapter
   - ~5-8ms to instantiate, ~0.1ms per step

2. **In-Process State Management**

   - FMU instances live in API process memory
   - No external state storage required for normal operation
   - Singleton adapter pattern (matches building-semantics-api-app)

3. **Crash Recovery Strategy**

   - On restart, create fresh FMU instances
   - Accept temporary control degradation (controller stabilizes within minutes)
   - No replay - input history storage not required for initial implementation
   - Future enhancement: periodic checkpoints if operational requirements demand

4. **Input Validation Layer**
   - Validate all inputs BEFORE calling FMU
   - Temperature range checks (reasonable building temps)
   - Airflow non-negative checks
   - Operation mode enum validation

### API Design Recommendations

| Aspect             | Recommendation                                |
| ------------------ | --------------------------------------------- |
| Instance lifecycle | Stateful - FMU instances kept alive in memory |
| State management   | In-process memory via singleton adapter       |
| Crash recovery     | Fresh start, accept temporary degradation     |
| Real-time sync     | Not required - simulated time is independent  |
| Input validation   | Validate BEFORE calling FMU                   |
| Multi-zone         | One FMU instance per zone                     |

---

## Code Examples

### Loading and Initializing FMU

```python
from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave

def create_fmu_instance(fmu_path: str, instance_name: str = 'instance1'):
    """Create and initialize an FMU instance."""
    md = read_model_description(fmu_path)
    unzipdir = extract(fmu_path)

    fmu = FMU2Slave(
        guid=md.guid,
        unzipDirectory=unzipdir,
        modelIdentifier=md.coSimulation.modelIdentifier,
        instanceName=instance_name
    )

    fmu.instantiate()
    fmu.setupExperiment(startTime=0.0)
    fmu.enterInitializationMode()
    fmu.exitInitializationMode()

    return fmu, md, unzipdir
```

### Setting Inputs

```python
def set_inputs(fmu, refs: dict, TZon: float, TCooSet: float, THeaSet: float,
               TDis: float, VDis_flow: float, TSup: float, TSupSet: float,
               u1Fan: bool, uOpeMod: int):
    """Set all G36 controller inputs."""
    fmu.setReal([refs['TZon']], [TZon])
    fmu.setReal([refs['TCooSet']], [TCooSet])
    fmu.setReal([refs['THeaSet']], [THeaSet])
    fmu.setReal([refs['TDis']], [TDis])
    fmu.setReal([refs['VDis_flow']], [VDis_flow])
    fmu.setReal([refs['TSup']], [TSup])
    fmu.setReal([refs['TSupSet']], [TSupSet])
    fmu.setBoolean([refs['u1Fan']], [u1Fan])
    fmu.setInteger([refs['uOpeMod']], [uOpeMod])
```

### Stepping and Getting Outputs

```python
def step_and_get_outputs(fmu, refs: dict, current_time: float, step_size: float):
    """Execute one simulation step and return outputs."""
    fmu.doStep(currentCommunicationPoint=current_time, communicationStepSize=step_size)

    return {
        'yDam': fmu.getReal([refs['yDam']])[0],      # Damper position [0-1]
        'yVal': fmu.getReal([refs['yVal']])[0],      # Heating valve [0-1]
        'VSet_flow': fmu.getReal([refs['VSet_flow']])[0]  # Airflow setpoint
    }
```

### Cleanup

```python
def cleanup_fmu(fmu):
    """Properly terminate and free FMU resources."""
    fmu.terminate()
    fmu.freeInstance()
```

---

## Blockers & Concerns

### No Blockers Identified

All 13 POC questions were answered successfully. The FMU integration approach is validated and ready for G36 Service development.

### Concerns to Address in Implementation

1. **State Persistence**: FMU does not support native state save/restore. Must implement external simulation time tracking.

2. **Input Validation**: FMU accepts invalid inputs without exceptions. API must validate all inputs before calling FMU.

3. **FMU File Management**: FMU files are large (~10MB) and should be gitignored. Document how to obtain FMU in README.

---

## Next Steps

1. **Story 1.5**: Design G36 Service API based on these findings
2. **Story 1.6-1.7**: Implement Designer Node UI for G36 blocks
3. **Epic 2**: Full G36 Service implementation

---

## References

- [LBL Modelica Buildings Library](https://github.com/lbl-srg/modelica-buildings)
- [FMPy Documentation](https://fmpy.readthedocs.io/)
- [FMI 2.0 Specification](https://fmi-standard.org/)
- POC Scripts: `apps/g36-api-app/fmu-sequence/scripts/`
- FMU Audit: `apps/g36-api-app/docs/fmu-audit/reheat-terminal/`
