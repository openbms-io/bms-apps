# Story 1.2: FMU State & Lifecycle Exploration

## Story

**As a** developer,
**I want to** understand FMU state management and lifecycle behavior,
**So that** we can design the G36 Service architecture correctly.

## Status

- **Epic**: 1 - G36 Reheat FMU Block Foundation
- **Status**: Complete
- **Priority**: P0 (Critical Path)
- **Estimate**: 3 hours
- **Completed**: 2025-11-27

## Context

This story explores how FMUs manage internal state and what their lifecycle looks like. Understanding this is critical for designing the G36 Service - we need to know if FMUs are stateless (pure functions) or stateful, and whether we need state persistence for crash recovery.

This story answers POC Questions #1-4:

1. How are states managed in FMU?
2. Do we need to save/restore FMU state?
3. Is FMU always running once kicked off?
4. Is FMU a pure function (inputs → outputs)?

## Acceptance Criteria

- [x] Answer: How are states managed in FMU? (Question #1)
- [x] Answer: Is FMU a pure function or stateful? (Question #4)
- [x] Answer: Does FMU keep running or is it step-on-demand? (Question #3)
- [x] Answer: Do we need to save/restore state? (Question #2)
- [x] Findings documented in README.md

## POC Answers

### Q1: How are states managed in FMU?

FMU manages state through **simulation time progression**. The G36 controller has integral terms that accumulate based on error duration, but this is deterministic based on simulation time, not step history.

### Q2: Do we need to save/restore FMU state?

State save/restore is **NOT SUPPORTED** by this FMU (canGetAndSetFMUstate=False). Alternative: track simulation time in database and replay on restart.

### Q3: Is FMU always running once kicked off?

FMU is **STEP-ON-DEMAND**. Uses **SIMULATED TIME**, not real-time. Wall clock time is ~0.2-1.3ms regardless of step size (60s to 3600s).

### Q4: Is FMU a pure function?

FMU is a **PURE FUNCTION of (inputs, simulation_time)**. Same inputs at same simulation time always produce same outputs. Fresh FMU with 1x1200s step matches FMU with 4x300s steps at t=1200s.

## Technical Requirements

### Experiments to Run

1. **State Persistence Test**

   - Set inputs, step FMU, observe outputs
   - Change inputs, step again - do outputs depend on history?
   - Reset FMU, same inputs - same outputs?

2. **Pure Function Test**

   - Same inputs at different simulation times - same outputs?
   - Does output depend only on current inputs or also on past inputs?

3. **Lifecycle Test**

   - What happens after FMU is instantiated?
   - Does FMU run continuously or wait for step calls?
   - What's the FMU state machine (instantiate → initialize → step → terminate)?

4. **State Save/Restore Test**
   - Can we get FMU internal state?
   - Can we serialize and restore state?
   - Is this needed for crash recovery?

### Expected Findings

Based on FMU 2.0 spec, likely findings:

- FMUs are typically **stateful** (internal state evolves with simulation time)
- G36 controller likely has **integral terms** that accumulate over time
- FMU is **step-on-demand** (not continuously running)
- State save/restore **may be supported** via `fmi2GetFMUstate`/`fmi2SetFMUstate`

## Dependencies

- Story 1.1: FMU Loading POC (FMU must be loadable)

## Test Strategy

- Manual testing via script execution
- Print state information to console
- Document observations

## Definition of Done

1. All 4 POC questions answered with evidence
2. Experiments documented with code and output
3. Findings added to README.md
4. Recommendations for G36 Service design documented

## File List

- `apps/g36-api-app/fmu-sequence/scripts/explore_lifecycle.py` - Created
- `apps/g36-api-app/docs/fmu-audit/reheat-terminal.md` - Created

## Notes

- These findings directly impact G36 Service architecture
- If FMU is stateful, we need to consider state persistence strategy
- If FMU is stateless, architecture is significantly simpler
- Focus on practical behavior, not theoretical FMU spec
