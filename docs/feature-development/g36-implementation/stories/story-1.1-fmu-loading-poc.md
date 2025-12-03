# Story 1.1: FMU Loading POC

## Story

**As a** developer,
**I want to** load and execute a Modelica FMU in Python,
**So that** we validate the core FMU integration approach works.

## Status

- **Epic**: 1 - G36 Reheat FMU Block Foundation
- **Status**: Complete
- **Priority**: P0 (Critical Path)
- **Estimate**: 4 hours
- **Completed**: 2025-11-27

## Context

This is the first story in the G36 POC epic. The goal is to prove that we can load and interact with the G36 Reheat FMU from LBL's modelica-buildings library using Python. This story answers POC Questions #5 (Which library - FMPy or PyFMI?) and #6 (How to obtain/export G36 FMU?).

### Technical Context

- **Model**: `Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller`
- **Source**: LBL modelica-buildings library
- **Format**: FMU 2.0 Co-Simulation
- **Location**: `apps/g36-api-app/poc/`

## Acceptance Criteria

- [x] G36 Reheat FMU file obtained (export from OpenModelica or download from releases)
- [x] FMU loads successfully using FMPy or PyFMI
- [x] All FMU I/O variables discovered and printed to console
- [x] Document which library works better (POC Question #5)
- [x] Document how to obtain FMU file (POC Question #6)

## Technical Requirements

### FMU Acquisition

1. Research how to obtain G36 Reheat FMU:
   - Check LBL releases for pre-built FMUs
   - If not available, export from OpenModelica
   - Document the chosen approach

### Python Library Selection

1. Try FMPy first (simpler installation)
2. Fallback to PyFMI if FMPy doesn't work
3. Document pros/cons of each

### POC Script Structure

```
apps/g36-api-app/
├── poc/
│   └── fmu_exploration.py   # POC script
├── fmu/
│   └── <G36_Reheat.fmu>     # FMU file (gitignored)
├── requirements.txt
└── README.md
```

### Implementation Steps

1. Create `apps/g36-api-app/` directory structure
2. Add `requirements.txt` with `fmpy` (and optionally `pyfmi`)
3. Obtain G36 Reheat FMU file
4. Write `fmu_exploration.py` that:
   - Loads FMU file
   - Discovers and prints all input variables with types
   - Discovers and prints all output variables with types
   - Identifies causality (input/output/parameter)

### Expected I/O Variables (from tech spec)

**Required Inputs (Real):**

- TZon, TCooSet, THeaSet, TDis, VDis_flow, TSup, TSupSet

**Required Inputs (Boolean):**

- u1Fan

**Required Inputs (Integer):**

- uOpeMod

**Outputs (Real):**

- yDam, yVal, VSet_flow

## Dependencies

- None (first story)

## Test Strategy

- Manual testing via script execution
- Console output verification
- Script runs without errors

## Definition of Done

1. POC script runs successfully
2. FMU loads without errors
3. All I/O variables printed to console
4. Findings documented in README.md
5. Questions #5 and #6 answered

## Notes

- This is an exploration/POC story - prioritize learning over polish
- FMU file should be gitignored (document how to obtain in README)
- Focus on answering the POC questions, not production readiness
