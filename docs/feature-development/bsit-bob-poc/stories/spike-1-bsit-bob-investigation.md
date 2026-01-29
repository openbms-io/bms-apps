# Spike: BSIT-BOB Library Investigation

Status: done

## Story

As a **developer**,
I want to **investigate the BSIT-BOB library patterns and capabilities**,
so that **I can determine feasibility of replacing BuildingMOTIF adapter implementation**.

## Context

### Current State (BuildingMOTIF Adapter)

The existing `BuildingMOTIFAdapter` at `apps/building-semantics-api-app/src/adapters/buildingmotif_adapter.py` provides:

1. **Template Operations**: Load NREL ASHRAE 223P templates, get by name, list, dependencies
2. **Ontology Libraries**: 223P, QUDT (units/quantitykinds), loaded from TTL files
3. **Model Management**: Create/get RDF models with namespaces, SQLite persistence
4. **SHACL Validation**: ShapeCollections for 223P, Unit, QuantityKind validation
5. **Graph Operations**: SPARQL queries, add triples, transaction support
6. **Persistence**: SQLite with WAL mode for concurrent access

### Target State (BSIT-BOB)

BSIT-BOB (`~/Documents/ai-projects/bsit-bob`) offers:

1. **Direct Class Instantiation**: Python classes for Equipment, Sensors, Properties
2. **Built-in Namespaces**: S223, P223, QUDT, Brick, BACnet pre-configured
3. **Global Data Graph**: `data_graph` for RDF operations, `dump()` for serialization
4. **Domain Classes**: Pre-built HVAC equipment (AirHandlingUnit, VAV, Chiller, etc.)
5. **No Template Engine**: Direct Python class usage vs template instantiation
6. **In-Memory Graph**: No built-in persistence (needs external solution)

### Key Differences to Investigate

| Aspect          | BuildingMOTIF                   | BSIT-BOB                   |
| --------------- | ------------------------------- | -------------------------- |
| Model Creation  | Templates + bindings            | Direct class instantiation |
| Persistence     | Built-in SQLite                 | External (needs solution)  |
| Validation      | Built-in SHACL ShapeCollections | TBD - investigate options  |
| API Style       | Template-based                  | Pythonic classes           |
| Equipment Types | NREL templates                  | Python class hierarchy     |

## Acceptance Criteria

1. **Spike Goal Achieved**: Produce findings document with feasibility assessment
2. **Pattern Documentation**: Document BSIT-BOB usage patterns for our use cases
3. **Proof of Concept**: Create minimal working example replacing one BuildingMOTIF operation
4. **Gap Analysis**: Identify missing features that need custom implementation
5. **Decision Recorded**: Clear GO/NO-GO recommendation with rationale

## Tasks / Subtasks

- [ ] Task 1: Study BSIT-BOB core patterns (AC: #1, #2)

  - [ ] Read and understand `bob/core.py` (Node, NodeMetaclass, data_graph)
  - [ ] Understand namespace management and RDF triple creation
  - [ ] Document the `dump()` serialization flow
  - [ ] Study shorthand operators (>, >>, @, |) from tests

- [ ] Task 2: Map current BuildingMOTIF operations to BSIT-BOB (AC: #2, #4)

  - [ ] Map `get_template_by_name()` → BSIT-BOB class instantiation
  - [ ] Map `create_model()` → BSIT-BOB model namespace
  - [ ] Map `add_graph()` → data_graph operations
  - [ ] Map `query_model()` → rdflib SPARQL on BSIT-BOB graph
  - [ ] Identify unmapped operations (gap analysis)

- [ ] Task 3: Create proof of concept (AC: #3)

  - [ ] Create simple equipment model using BSIT-BOB
  - [ ] Serialize to Turtle format
  - [ ] Compare output with BuildingMOTIF equivalent
  - [ ] Document API differences

- [ ] Task 4: Investigate persistence options (AC: #4)

  - [ ] Evaluate rdflib store backends (SQLAlchemy, Berkeley DB)
  - [ ] Consider simple JSON-LD serialization approach
  - [ ] Assess SQLite integration feasibility

- [ ] Task 5: Investigate SHACL validation (AC: #4)

  - [ ] Check if BSIT-BOB has validation support
  - [ ] Evaluate pyshacl integration for validation
  - [ ] Compare with BuildingMOTIF ShapeCollection approach

- [ ] Task 6: Write findings document (AC: #1, #5)
  - [ ] Document feasibility assessment
  - [ ] List pros/cons of migration
  - [ ] Provide GO/NO-GO recommendation
  - [ ] Outline implementation approach if GO

## Dev Notes

### BSIT-BOB Source Reference

- Local checkout: `~/Documents/ai-projects/bsit-bob`
- Documentation: https://bsit-bob.readthedocs.io/en/latest/
- Key files to study:
  - `bob/core.py` - Node base class, data_graph, dump()
  - `bob/application.py` - Application classes (AHU, Chiller, etc.)
  - `bob/equipment/hvac/*.py` - HVAC equipment (VAV, Fan, Damper, etc.)
  - `bob/properties/*.py` - Property definitions (temperature, flow, etc.)
  - `bob/sensor/*.py` - Sensor definitions

### Current BuildingMOTIF Usage Points

Key files using BuildingMOTIF in `building-semantics-api-app`:

```
src/adapters/buildingmotif_adapter.py  - Main adapter (replacement target)
src/adapters/template_types.py         - Template enum definitions
src/routers/templates.py               - Template listing endpoint
src/routers/mappings.py                - SHACL validation + RDF creation
```

### Migration Strategy Consideration

Two approaches to evaluate:

1. **Adapter Pattern**: Create `BsitBobAdapter` with same interface as `BuildingMOTIFAdapter`
2. **Full Replacement**: Refactor callers to use BSIT-BOB classes directly

Spike should recommend which approach is more suitable.

### Project Structure Notes

- Spike outputs go to: `docs/feature-development/bsit-bob-poc/specs/`
- Expected artifact: `spike-findings.md`

### References

- [Source: apps/building-semantics-api-app/src/adapters/buildingmotif_adapter.py]
- [Source: ~/Documents/ai-projects/bsit-bob/bob/core.py]
- [Docs: https://bsit-bob.readthedocs.io/en/latest/getting-started.html]

## Dev Agent Record

### Context Reference

- `spike-1-bsit-bob-investigation.context.xml` (same directory)

### Agent Model Used

Claude Opus 4.5 (claude-opus-4-5-20251101)

### Debug Log References

<!-- To be filled during implementation -->

### Completion Notes List

- All 6 tasks completed successfully
- POC demonstrates BSIT-BOB can work alongside BuildingMOTIF
- Recommendation: **GO** - add BSIT-BOB as alternative adapter
- Common interface pattern: Both adapters implement `SemanticsAdapterProtocol`
- Future extensibility: Supports Brick protocol if required
- Findings document: `docs/feature-development/bsit-bob-poc/specs/spike-findings.md`

### File List

**NEW:**

- `docs/feature-development/bsit-bob-poc/specs/spike-findings.md` - Main findings document
- `docs/feature-development/bsit-bob-poc/specs/poc_bsit_bob_usage.py` - POC script
- `docs/feature-development/bsit-bob-poc/epics.md` - Epic definition
- `docs/feature-development/bsit-bob-poc/sprint-status.yaml` - Sprint tracking

## Change Log

| Date       | Author    | Change                                     |
| ---------- | --------- | ------------------------------------------ |
| 2025-12-30 | SM Agent  | Initial draft created                      |
| 2026-01-06 | SM Agent  | Context generated, marked ready-for-dev    |
| 2026-01-06 | Dev Agent | Spike completed, findings document created |
