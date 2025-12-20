# Epic Technical Specification: G36 Reheat FMU POC

Date: 2025-11-26
Author: Amol
Epic ID: 1
Status: Draft

---

## Overview

This epic is a **POC to answer fundamental questions about FMU behavior** before designing the G36 Service architecture. The goal is to de-risk FMU integration by understanding how Modelica FMUs work in practice.

The G36 Reheat Terminal Unit Controller (`Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller`) from LBL's modelica-buildings library will be used for exploration.

**Architectural Decision:** G36 execution will live in a dedicated **G36 Service** (FastAPI), following the same pattern as Building Semantics API. This POC will inform the detailed service design.

## Objectives and Scope

### In Scope

- POC Python script to explore FMU behavior
- Answer 13 key questions about FMU state, lifecycle, and behavior
- FMU loading and execution using FMPy or PyFMI
- Document findings to inform service design

### Out of Scope (Separate Specs)

- G36 Service API design (Story 1.5 - separate spec)
- Designer node schema and UI (Stories 1.6-1.7 - separate spec)
- BACnet MQTT write integration (Epic 2)
- SHACL validation (Epic 3)
- Graph execution with scheduler (Epic 4)
- BOPTEST integration (Epic 5)

## System Architecture Alignment

### Target Architecture (Decided)

```
┌─────────────────────────────────────────────────────────────┐
│                    Designer App (Next.js)                   │
└─────────────┬───────────────────────────────────────────────┘
              │ HTTP/REST
              ↓
┌─────────────────────────────┐
│  G36 Service (FastAPI)      │
│  apps/g36-api-app/          │
│  - FMU lifecycle            │
│  - Step execution           │
│  - State management         │
└─────────────────────────────┘
```

### POC Location

```
apps/g36-api-app/
├── poc/
│   └── fmu_exploration.py   # POC script
├── requirements.txt
└── README.md                # Document findings
```

## POC Questions to Answer

### FMU Fundamentals

| #   | Question                                   | Impact on Design         |
| --- | ------------------------------------------ | ------------------------ |
| 1   | How are states managed in FMU?             | State persistence design |
| 2   | Do we need to save/restore FMU state?      | Crash recovery approach  |
| 3   | Is FMU always running once kicked off?     | Lifecycle model          |
| 4   | Is FMU a pure function (inputs → outputs)? | Simplifies if stateless  |

### FMU Practical Usage

| #   | Question                                                     | Impact on Design   |
| --- | ------------------------------------------------------------ | ------------------ |
| 5   | Which library works better - FMPy or PyFMI?                  | Dependency choice  |
| 6   | How to obtain/export G36 Reheat FMU from modelica-buildings? | Build vs download  |
| 7   | What's the FMU step time semantics? (real-time vs simulated) | Scheduler design   |
| 8   | Can we run multiple FMU instances concurrently?              | Multi-zone support |

### G36 Behavior Validation

| #   | Question                                                         | Impact on Design    |
| --- | ---------------------------------------------------------------- | ------------------- |
| 9   | Do G36 outputs (yDam, yVal) look reasonable given sample inputs? | Validates FMU works |
| 10  | Which G36 inputs are truly required vs optional in practice?     | Minimal config      |

### Performance

| #   | Question                                           | Impact on Design   |
| --- | -------------------------------------------------- | ------------------ |
| 11  | What's the FMU step execution time?                | API latency budget |
| 12  | Memory footprint per FMU instance?                 | Scaling limits     |
| 13  | Error handling - what happens with invalid inputs? | API error design   |

## Detailed Design

### POC Script

```python
# apps/g36-api-app/poc/fmu_exploration.py

"""
G36 Reheat FMU Exploration POC

Goal: Answer fundamental questions about FMU behavior
Output: Console logs and findings documented in README.md
"""

# 1. Load G36 Reheat FMU
# 2. Discover I/O variables
# 3. Set sample input values (hardcoded)
# 4. Step FMU
# 5. Print outputs to console
# 6. Explore state management
# 7. Test multiple instances
# 8. Document answers to all questions
```

### G36 Reheat I/O Reference

From LBL modelica-buildings `Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller`:

**Required Inputs (Real):**

| Input     | Description                  | Unit |
| --------- | ---------------------------- | ---- |
| TZon      | Measured room temperature    | K    |
| TCooSet   | Cooling setpoint             | K    |
| THeaSet   | Heating setpoint             | K    |
| TDis      | Discharge air temperature    | K    |
| VDis_flow | Primary discharge airflow    | m³/s |
| TSup      | AHU supply air temperature   | K    |
| TSupSet   | AHU supply air temp setpoint | K    |

**Required Inputs (Boolean):**

| Input | Description           |
| ----- | --------------------- |
| u1Fan | AHU supply fan status |

**Required Inputs (Integer):**

| Input   | Description         | Range |
| ------- | ------------------- | ----- |
| uOpeMod | Zone operation mode | 1-7   |

**Conditional Inputs:**

| Input     | Condition         | Description            |
| --------- | ----------------- | ---------------------- |
| ppmCO2Set | have_CO2Sen=true  | CO2 setpoint (ppm)     |
| ppmCO2    | have_CO2Sen=true  | Measured CO2 (ppm)     |
| u1HotPla  | heaCoi=WaterBased | Hot water plant status |

**Outputs (Real):**

| Output    | Description            | Range |
| --------- | ---------------------- | ----- |
| yDam      | Damper position        | 0-1   |
| yVal      | Heating valve position | 0-1   |
| VSet_flow | Airflow setpoint       | m³/s  |

**Outputs (Integer - Alarms):**

| Output        | Description                       |
| ------------- | --------------------------------- |
| yZonTemResReq | Zone temp reset request (0-3)     |
| yZonPreResReq | Zone pressure reset request (0-3) |
| yLowFloAla    | Low airflow alarm (0-2)           |

## Dependencies

### Python Dependencies

| Package | Version | Purpose                            |
| ------- | ------- | ---------------------------------- |
| `fmpy`  | latest  | FMU loading/execution (try first)  |
| `pyfmi` | latest  | Alternative FMU library (fallback) |

### FMU File

- **Source**: LBL modelica-buildings library
- **Model**: `Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller`
- **Format**: FMU 2.0 Co-Simulation
- **Obtaining**: Export from OpenModelica or download from releases (TBD in Story 1.1)

## Acceptance Criteria

### Story 1.1: FMU Loading POC

1. [ ] G36 Reheat FMU file obtained (export or download)
2. [ ] FMU loads successfully using FMPy or PyFMI
3. [ ] All FMU I/O variables discovered and printed
4. [ ] Document which library works better (Question #5)
5. [ ] Document how to obtain FMU (Question #6)

### Story 1.2: FMU State & Lifecycle Exploration

1. [ ] Answer: How are states managed in FMU? (Question #1)
2. [ ] Answer: Is FMU a pure function or stateful? (Question #4)
3. [ ] Answer: Does FMU keep running or is it step-on-demand? (Question #3)
4. [ ] Answer: Do we need to save/restore state? (Question #2)
5. [ ] Findings documented in README.md

### Story 1.3: FMU Execution & Validation

1. [ ] Set sample inputs (hardcoded values)
2. [ ] Step FMU and print outputs to console
3. [ ] Verify outputs (yDam, yVal) look reasonable (Question #9)
4. [ ] Test multiple steps with changing inputs
5. [ ] Answer: What's the step time semantics? (Question #7)
6. [ ] Answer: Which inputs are truly required? (Question #10)
7. [ ] Answer: Can we run multiple instances? (Question #8)
8. [ ] Capture step execution time (Question #11)
9. [ ] Capture memory footprint (Question #12)
10. [ ] Test invalid inputs - document behavior (Question #13)

### Story 1.4: Document POC Findings

1. [ ] All 13 POC questions answered in README.md
2. [ ] Recommendations for G36 Service design captured
3. [ ] Any blockers or concerns documented

## Risks and Assumptions

### Risks

| Risk                               | Likelihood | Impact | Mitigation                       |
| ---------------------------------- | ---------- | ------ | -------------------------------- |
| G36 FMU not available/exportable   | Medium     | High   | Contact LBL or build from source |
| FMPy/PyFMI compatibility issues    | Medium     | Medium | Try both libraries               |
| FMU has complex state requirements | Low        | Medium | POC will reveal                  |

### Assumptions

1. G36 Reheat FMU can be exported from modelica-buildings
2. FMPy or PyFMI supports FMU 2.0 Co-Simulation
3. FMU uses SI units (Kelvin, m³/s)

## Test Strategy

### Approach

- Manual testing via script execution
- Console output verification
- Document all findings in README.md

### Validation

- Outputs (yDam, yVal) should be in valid range (0-1)
- Control behavior should make sense (e.g., heating valve opens when TZon < THeaSet)
