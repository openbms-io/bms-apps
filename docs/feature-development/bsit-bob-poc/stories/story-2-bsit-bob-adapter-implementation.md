# Story 2: BSIT-BOB Adapter Implementation

Status: ready-for-dev

## Prerequisites

- **Depends on**: Spike 1 - BSIT-BOB Library Investigation (GO recommendation confirmed)
- **Spike Findings**: Available at `docs/feature-development/bsit-bob-poc/specs/spike-findings.md`
- **POC Script**: Available at `docs/feature-development/bsit-bob-poc/specs/poc_bsit_bob_usage.py`

## Story

As a **developer**,
I want to **add BSIT-BOB as an alternative adapter alongside BuildingMOTIF**,
so that **the building semantics API has a more Pythonic, maintainable library option with future Brick protocol support**.

## Context

### Scope

This story implements the BSIT-BOB adapter based on spike findings. Key constraints:

1. **Keep Interface**: Maintain the same public interface as `BuildingMOTIFAdapter`
2. **Preserve Functionality**: All current features must continue working
3. **No Breaking Changes**: API endpoints remain unchanged
4. **Backward Compatible**: Existing data/models must still be accessible

### What This Story Does NOT Do

- Does NOT remove BuildingMOTIF completely (can coexist during transition)
- Does NOT change the REST API contract
- Does NOT require frontend changes

## Acceptance Criteria

1. **Common Interface Defined**: `SemanticsAdapterProtocol` in `semantics_adapter_protocol.py` with concrete return types (compile-time type safety)
2. **Models Refactored**: All domain models (`TemplatesModel`, `DevicesModel`, `SystemsModel`, `BACnetReferencesModel`) accept `SemanticsAdapterProtocol` instead of concrete `BuildingMOTIFAdapter`
3. **BsitBobAdapter Created**: New adapter class implementing `SemanticsAdapterProtocol`
4. **BuildingMOTIFAdapter Updated**: Existing adapter updated to implement `SemanticsAdapterProtocol`
5. **Template Operations**: List templates, get template by name works with BSIT-BOB equipment classes
6. **Model Creation**: Create RDF models using `bind_model_namespace()` and `data_graph`
7. **SQLite Persistence**: Models persist to SQLite database via rdflib-sqlalchemy store
8. **Graph Serialization**: Export models to Turtle format using `dump()`
9. **SHACL Validation**: Validate models against 223P shapes using pyshacl
10. **Configuration Switch**: Settings flag + factory to choose between adapters
11. **Interface Tests Pass**: Common test suite with mock data passes for both adapters

## Tasks / Subtasks

- [ ] Task 0: Define protocol and refactor models to use interface (AC: #1, #2, #4)

  - [ ] Create `src/adapters/semantics_adapter_protocol.py` with `SemanticsAdapterProtocol`
  - [ ] Define concrete return types: `TemplateInfo`, `ModelHandle`, `QueryResult`, `ValidationResult`
  - [ ] Define methods with concrete types (not `Any`): `get_instance()`, `list_templates()`, `get_template_by_name()`, `create_model()`, `add_triples()`, `query_model()`, `serialize_model()`, `validate_model()`
  - [ ] Update `TemplatesModel` to accept `SemanticsAdapterProtocol` instead of `BuildingMOTIFAdapter`
  - [ ] Update `DevicesModel` to accept `SemanticsAdapterProtocol` instead of `BuildingMOTIFAdapter`
  - [ ] Update `SystemsModel` to accept `SemanticsAdapterProtocol` instead of `BuildingMOTIFAdapter`
  - [ ] Update `BACnetReferencesModel` to accept `SemanticsAdapterProtocol` instead of `BuildingMOTIFAdapter`
  - [ ] Update `BuildingMOTIFAdapter` to implement `SemanticsAdapterProtocol`
  - [ ] Write interface tests with mock data that verify return type shapes

- [ ] Task 1: Create BsitBobAdapter class (AC: #3)

  - [ ] Create `src/adapters/bsit_bob_adapter.py`
  - [ ] Implement `SemanticsAdapterProtocol`
  - [ ] Add singleton pattern with `get_instance(db_path)`
  - [ ] Initialize with `clear()`, `bind_model_namespace()`, `data_graph`

- [ ] Task 2: Implement template mapping (AC: #5)

  - [ ] Create `TEMPLATE_CLASS_MAP` dict mapping template names to BSIT-BOB classes
  - [ ] Map: `damper` → `Damper`, `fan` → `Fan`, `valve` → `Valve`, `pump` → `Pump`
  - [ ] Map: `vav-reheat` → `SingleDuctTerminal`, `air-handling-unit` → `AirHandlingUnit`
  - [ ] Implement `list_templates()` and `get_template_by_name()`

- [ ] Task 3: Implement model operations (AC: #6, #7)

  - [ ] Implement `create_model()` using `bind_model_namespace()`
  - [ ] Implement `add_triples()` using `data_graph.add()`
  - [ ] Implement `query_model()` using `data_graph.query(sparql)`
  - [ ] Configure rdflib-sqlalchemy store for SQLite persistence
  - [ ] Implement `save_model()` to persist graph to SQLite
  - [ ] Implement `load_model()` to restore graph from SQLite

- [ ] Task 4: Implement serialization (AC: #8)

  - [ ] Implement `serialize_model()` using BSIT-BOB `dump()`
  - [ ] Support formats: turtle, json-ld
  - [ ] Ensure namespace prefixes (s223, qudt, unit) match current output

- [ ] Task 5: Implement SHACL validation (AC: #9)

  - [ ] Integrate pyshacl for validation
  - [ ] Load 223P shapes from `schema_graph`
  - [ ] Implement `validate_model()` returning `ValidationResult(conforms, report)`

- [ ] Task 6: Add configuration switch and factory (AC: #10)

  - [ ] Add `use_bsit_bob: bool` setting to Settings class
  - [ ] Create `src/adapters/factory.py` with `get_semantics_adapter()`
  - [ ] Factory returns appropriate adapter based on config

- [ ] Task 7: Integration testing (AC: #11)
  - [ ] Run interface tests against both adapters
  - [ ] Add BSIT-BOB-specific edge case tests
  - [ ] Verify existing integration tests pass
  - [ ] Document any behavioral differences

## Dev Notes

### Architecture Decision (from Spike Findings)

**Common Interface Pattern**: Both adapters implement `SemanticsAdapterProtocol`:

```python
from typing import Protocol, Any
from rdflib import Graph

class SemanticsAdapterProtocol(Protocol):
    """Protocol defining the contract for semantics adapters."""

    @classmethod
    def get_instance(cls, db_path: str | None = None) -> "SemanticsAdapterProtocol":
        ...

    def list_templates(self) -> list[str]:
        ...

    def get_template_by_name(self, template_name: str) -> Any:
        ...

    def create_model(self, namespace: str) -> Any:
        ...

    def add_triples(self, model: Any, triples: list[tuple]) -> None:
        ...

    def query_model(self, model: Any, sparql: str) -> list[dict]:
        ...

    def serialize_model(self, model: Any, format: str = "turtle") -> str:
        ...

    def validate_model(self, model: Any) -> tuple[bool, str]:
        ...
```

### Template Class Mapping (from Spike Findings)

| Template Name       | BSIT-BOB Class       | Module                               |
| ------------------- | -------------------- | ------------------------------------ |
| `damper`            | `Damper`             | `bob.equipment.hvac.damper`          |
| `fan`               | `Fan`                | `bob.equipment.hvac.fan`             |
| `valve`             | `Valve`              | `bob.equipment.hvac.valve`           |
| `pump`              | `Pump`               | `bob.equipment.hvac.pump`            |
| `filter`            | `Filter`             | `bob.equipment.hvac.filter`          |
| `vav-reheat`        | `SingleDuctTerminal` | `bob.equipment.hvac.vav`             |
| `air-handling-unit` | `AirHandlingUnit`    | `bob.equipment.hvac.airhandlingunit` |
| `chiller`           | `Chiller`            | `bob.equipment.hvac.chiller`         |
| `boiler`            | `Boiler`             | `bob.equipment.hvac.boiler`          |

### Key BSIT-BOB Patterns

```python
from bob.core import bind_model_namespace, data_graph, dump, clear

# Initialize
clear()
ns = bind_model_namespace('project', 'urn:my-project/')

# Create equipment
damper = Damper(label='OA-Damper-101')

# System containment (> operator)
ahu = AHU(label='AHU-1')
ahu > damper  # Adds s223:hasMember relationship

# Connection (>> operator)
damper.airOutlet >> fan.airInlet  # Connects via s223:connectsThrough

# Serialize
turtle_output = dump()  # Returns Turtle string

# Query
results = data_graph.query(sparql)
```

### Persistence Strategy (Confirmed)

Use **rdflib-sqlalchemy** for SQLite persistence (already installed as dependency).

### Project Structure

Files to create/modify:

```
apps/building-semantics-api-app/
├── src/
│   ├── adapters/
│   │   ├── semantics_adapter_protocol.py  # NEW - SemanticsAdapterProtocol
│   │   ├── bsit_bob_adapter.py            # NEW - BsitBobAdapter
│   │   ├── factory.py                     # NEW - get_semantics_adapter()
│   │   └── buildingmotif_adapter.py       # MODIFY - implement protocol
│   └── config/
│       └── settings.py                    # MODIFY - add use_bsit_bob flag
└── tests/
    ├── unit/
    │   └── test_adapters/
    │       ├── test_semantics_adapter_protocol.py  # NEW - interface tests
    │       └── test_bsit_bob_adapter.py            # NEW - BSIT-BOB specific tests
    └── integration/
        └── test_adapter_parity.py                  # NEW - both adapters same behavior
```

### References

- [Source: apps/building-semantics-api-app/src/adapters/buildingmotif_adapter.py]
- [Spike Findings: docs/feature-development/bsit-bob-poc/specs/spike-findings.md]
- [POC Script: docs/feature-development/bsit-bob-poc/specs/poc_bsit_bob_usage.py]
- [BSIT-BOB Docs: https://bsit-bob.readthedocs.io/en/latest/]
- [BSIT-BOB Source: ~/Documents/ai-projects/bsit-bob]

## Dev Agent Record

### Context Reference

- `docs/feature-development/bsit-bob-poc/stories/1-2-bsit-bob-adapter-implementation.context.xml`

### Agent Model Used

<!-- To be filled by dev agent -->

### Debug Log References

<!-- To be filled during implementation -->

### Completion Notes List

<!-- To be filled upon completion -->

### File List

<!-- To be filled: NEW, MODIFIED, DELETED files -->

## Change Log

| Date       | Author    | Change                                                                                                          |
| ---------- | --------- | --------------------------------------------------------------------------------------------------------------- |
| 2025-12-30 | SM Agent  | Initial draft created                                                                                           |
| 2026-01-06 | SM Agent  | Updated based on spike findings: added common interface task, updated template mapping, added BSIT-BOB patterns |
| 2026-01-08 | SM Agent  | Added SQLite persistence AC, marked ready-for-dev                                                               |
| 2026-01-08 | Dev Agent | Generated context with concrete return types, mock data approach                                                |
