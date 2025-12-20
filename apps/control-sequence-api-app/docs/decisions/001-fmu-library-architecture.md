# ADR-001: FMU Library Selection and Architecture Pattern

## Status

**Accepted** - 2025-11-27

## Context

The G36 API App needs to execute ASHRAE Guideline 36 control sequences using Functional Mock-up Units (FMUs). Key decisions required:

1. **Library Selection**: Choose between FMPy and PyFMI for FMU interaction
2. **Architecture Pattern**: Determine how to manage FMU instances and state
3. **State Persistence**: Handle crash recovery without native FMU state save/restore

### Constraints

- FMU source: LBL modelica-buildings library (G36 Reheat Terminal Controller)
- FMU format: FMI 2.0 Co-Simulation
- Target: Multi-zone building control (100s of zones)
- Performance: Real-time control response required

## Decision

### 1. Library: FMPy

**Choice:** Use FMPy over PyFMI

**Rationale:**

| Criterion     | FMPy                        | PyFMI                        |
| ------------- | --------------------------- | ---------------------------- |
| Installation  | Simple (`pip install fmpy`) | Complex (Assimulo, SUNDIALS) |
| Dependencies  | Minimal                     | Heavy scientific stack       |
| API           | Pythonic, intuitive         | More complex                 |
| Maintenance   | Actively maintained         | Less active                  |
| Performance   | ~0.1ms per step             | Comparable                   |
| Documentation | Good                        | Adequate                     |

FMPy provides equivalent functionality with significantly simpler setup and maintenance.

### 2. Architecture: Session-Based with Persistent Instances

**Choice:** Maintain one FMU instance per zone in memory

**Rationale:**

| Pattern        | Init Time   | Step Time | Memory | Complexity |
| -------------- | ----------- | --------- | ------ | ---------- |
| Fresh per call | ~5-8ms      | ~0.1ms    | Low    | Simple     |
| Session-based  | ~5-8ms once | ~0.1ms    | Higher | Moderate   |

Session-based is ~50x faster for repeated calls. Memory (~1-2 MB/zone) is acceptable for typical building sizes.

**Implementation:**

- Create FMU instance when zone is first accessed
- Maintain zone→FMU instance mapping in memory
- Track simulation_time per zone in database
- Cleanup instances on service shutdown

### 3. State Persistence: Simulation Time Tracking

**Choice:** Track simulation time externally; replay on recovery

**Rationale:**

The G36 Reheat FMU does not support native state save/restore:

```
canGetAndSetFMUstate: False
canSerializeFMUstate: False
```

However, POC findings confirm FMU is a pure function of (inputs, simulation_time). This enables deterministic recovery:

1. Store cumulative simulation_time per zone in database
2. On crash recovery, create fresh FMU instance
3. Replay to last recorded simulation_time with single large step
4. State is restored identically due to deterministic behavior

## Consequences

### Positive

- Simple installation and deployment (FMPy)
- Excellent performance (~0.1ms per step, ~9,500 zones/sec)
- Deterministic crash recovery via simulation time replay
- Multi-zone support with concurrent instances
- No complex state serialization required

### Negative

- Memory usage scales with zone count (~1-2 MB per zone)
- Must implement external simulation time tracking
- FMU file must be obtained separately (not in git)
- Input validation required (FMU accepts invalid inputs)

### Risks

1. **Memory pressure**: Mitigated by lazy instance creation and cleanup
2. **Recovery accuracy**: Mitigated by deterministic FMU behavior
3. **FMU compatibility**: Locked to specific FMU version; document in README

## References

- [POC Findings Spec](../../../docs/feature-development/g36-implementation/specs/poc-findings.md)
- [FMU Audit: Reheat Terminal](../fmu-audit/reheat-terminal/reheat-terminal-behavior.md)
- [FMPy Documentation](https://fmpy.readthedocs.io/)
- [LBL Modelica Buildings](https://github.com/lbl-srg/modelica-buildings)
