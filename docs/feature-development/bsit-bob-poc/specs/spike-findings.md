# BSIT-BOB Spike Findings

**Date:** 2026-01-06
**Status:** Complete
**Recommendation:** **GO** - Add BSIT-BOB as alternative adapter alongside BuildingMOTIF

---

## Executive Summary

This spike investigated the BSIT-BOB library as an **additional adapter option** for the building-semantics-api-app. After thorough analysis and proof-of-concept testing, we recommend adding BSIT-BOB while keeping BuildingMOTIF as an option.

**Approach:** Both adapters will implement a common `SemanticsAdapterProtocol` interface, allowing runtime switching via configuration. This enables:

- Gradual migration without breaking existing functionality
- A/B testing between implementations
- Fallback to BuildingMOTIF if needed

**Key Finding:** BSIT-BOB provides a more Pythonic, simpler API for ASHRAE 223P semantic modeling while maintaining full RDF compatibility. All critical BuildingMOTIF operations can be mapped to BSIT-BOB equivalents.

---

## Feasibility Assessment

### 1. Core Patterns Comparison

| Aspect               | BuildingMOTIF                        | BSIT-BOB                          |
| -------------------- | ------------------------------------ | --------------------------------- |
| **Model Creation**   | Template instantiation with bindings | Direct Python class instantiation |
| **API Style**        | Template engine                      | Pythonic classes                  |
| **Learning Curve**   | Moderate (template syntax)           | Low (standard Python)             |
| **Type Safety**      | Runtime via bindings                 | Static via type hints             |
| **RDF Output**       | Turtle/JSON-LD                       | Turtle/JSON-LD (via dump())       |
| **Persistence**      | Built-in SQLite                      | External (rdflib-sqlalchemy)      |
| **SHACL Validation** | Built-in ShapeCollection             | External (pyshacl)                |

### 2. Proof of Concept Results

**All POC tests passed:**

1. **Equipment Creation:** `Damper(label="x")` produces valid 223P RDF
2. **System Containment:** `system > equipment` correctly adds `s223:hasMember`
3. **SPARQL Query:** `data_graph.query(sparql)` returns correct results
4. **Turtle Serialization:** `dump()` produces valid Turtle output
5. **Persistence:** Both file-based (Turtle/JSON-LD) and SQLite work
6. **SHACL Validation:** pyshacl integration successful

---

## Equipment Templates in BSIT-BOB

### Available Equipment Classes

BSIT-BOB provides two hierarchies of equipment:

#### 1. Equipment Classes (with Connection Points)

Located in `bob/equipment/hvac/`:

| Class                | Module               | Connection Points                                            |
| -------------------- | -------------------- | ------------------------------------------------------------ |
| `AirHandlingUnit`    | `airhandlingunit.py` | airInlet, airOutlet                                          |
| `Damper`             | `damper.py`          | airInlet, airOutlet                                          |
| `Fan`                | `fan.py`             | airInlet, airOutlet, electricalInlet                         |
| `Pump`               | `pump.py`            | fluidInlet, fluidOutlet                                      |
| `Valve`              | `valve.py`           | fluidInlet, fluidOutlet                                      |
| `Chiller`            | `chiller.py`         | chilledWaterSupply, chilledWaterReturn                       |
| `Boiler`             | `boiler.py`          | hotWaterSupply, hotWaterReturn                               |
| `Coil`               | `coil.py`            | airInlet, airOutlet, fluidInlet, fluidOutlet                 |
| `HeatExchanger`      | `heatexchanger.py`   | primaryInlet, primaryOutlet, secondaryInlet, secondaryOutlet |
| `SingleDuctTerminal` | `vav.py`             | airInlet, airOutlet                                          |
| `Filter`             | `filter.py`          | airInlet, airOutlet                                          |
| `Humidifier`         | `humidifier.py`      | airInlet, airOutlet                                          |

#### 2. Application Classes (Type Markers)

Located in `bob/application.py`:

| Class                | IRI                                               | Parent       |
| -------------------- | ------------------------------------------------- | ------------ |
| `AirHandlingUnit`    | `P223:Application-AirHandlingUnit`                | Node         |
| `Boiler`             | `P223:Application-Boiler`                         | Node         |
| `Chiller`            | `P223:Application-Chiller`                        | Node         |
| `CoolingTower`       | `P223:Application-CoolingTower`                   | Node         |
| `HeatPump`           | `P223:Application-HeatPump`                       | Node         |
| `TerminalUnit`       | `P223:Application-TerminalUnit`                   | Node         |
| `SingleDuctTerminal` | `P223:TerminalUnitApplication-SingleDuctTerminal` | TerminalUnit |
| `FanCoilUnit`        | `P223:TerminalUnitApplication-FanCoilUnit`        | TerminalUnit |
| `FanPoweredTerminal` | `P223:TerminalUnitApplication-FanPoweredTerminal` | TerminalUnit |

### Creating Equipment (Template Equivalent)

**BuildingMOTIF Approach:**

```python
template = adapter.get_template_by_name(DeviceTemplate.DAMPER)
model = adapter.create_model("urn:my-project/")
template.evaluate({"label": "OA-Damper-101"})
```

**BSIT-BOB Approach:**

```python
from bob.core import bind_model_namespace, clear
from bob.equipment.hvac.damper import Damper

clear()
bind_model_namespace('project', 'urn:my-project/')
damper = Damper(label='OA-Damper-101')
```

### Creating Custom Equipment Types

When a pre-built class doesn't exist, create custom equipment:

```python
from bob.core import Equipment, S223
from bob.connections.air import AirInletConnectionPoint, AirOutletConnectionPoint

class HeatRecoveryWheel(Equipment):
    _class_iri = S223.HeatExchanger  # Use appropriate 223P type
    supplyAirInlet: AirInletConnectionPoint
    supplyAirOutlet: AirOutletConnectionPoint
    exhaustAirInlet: AirInletConnectionPoint
    exhaustAirOutlet: AirOutletConnectionPoint

# Use it
hrw = HeatRecoveryWheel(label="HRW-1")
```

### Creating VAV Terminal Units

```python
from bob.equipment.hvac.vav import SingleDuctTerminal
from bob.equipment.hvac.damper import Damper
from bob.equipment.hvac.coil import ReheatCoil

class VAVReheat(SingleDuctTerminal):
    """VAV box with reheat coil."""
    pass

vav = VAVReheat(label="VAV-101")
# VAV automatically has airInlet, airOutlet from SingleDuctTerminal
```

### Creating AHU Systems

```python
from bob.core import System
from bob.equipment.hvac.airhandlingunit import AirHandlingUnit
from bob.equipment.hvac.fan import Fan
from bob.equipment.hvac.damper import Damper
from bob.equipment.hvac.coil import CoolingCoil, HeatingCoil
from bob.equipment.hvac.filter import Filter

class MyAHU(System):
    """Custom AHU with specific components."""
    pass

# Create AHU system
ahu = MyAHU(label="AHU-1")

# Add components using > operator
ahu > Filter(label="Pre-Filter")
ahu > Damper(label="OA-Damper")
ahu > CoolingCoil(label="Cooling-Coil")
ahu > HeatingCoil(label="Heating-Coil")
ahu > Fan(label="Supply-Fan")

# Connect components using >> operator
oa_damper.airOutlet >> filter.airInlet
filter.airOutlet >> cooling_coil.airInlet
cooling_coil.airOutlet >> heating_coil.airInlet
heating_coil.airOutlet >> fan.airInlet
```

---

## Template Mapping Strategy

### Proposed Mapping

| TemplateType (BuildingMOTIF) | BSIT-BOB Class            | Module                               |
| ---------------------------- | ------------------------- | ------------------------------------ |
| `DeviceTemplate.DAMPER`      | `Damper`                  | `bob.equipment.hvac.damper`          |
| `DeviceTemplate.FAN`         | `Fan`                     | `bob.equipment.hvac.fan`             |
| `DeviceTemplate.VALVE`       | `Valve`                   | `bob.equipment.hvac.valve`           |
| `DeviceTemplate.PUMP`        | `Pump`                    | `bob.equipment.hvac.pump`            |
| `DeviceTemplate.FILTER`      | `Filter`                  | `bob.equipment.hvac.filter`          |
| `DeviceTemplate.SENSOR`      | `TemperatureSensor`, etc. | `bob.sensor.*`                       |
| `SystemTemplate.VAV_REHEAT`  | `SingleDuctTerminal`      | `bob.equipment.hvac.vav`             |
| `SystemTemplate.AHU`         | `AirHandlingUnit`         | `bob.equipment.hvac.airhandlingunit` |
| `SystemTemplate.CHILLER`     | `Chiller`                 | `bob.equipment.hvac.chiller`         |
| `SystemTemplate.BOILER`      | `Boiler`                  | `bob.equipment.hvac.boiler`          |

### Template Mapping Implementation

```python
from enum import Enum
from typing import Type
from bob.core import Equipment

TEMPLATE_CLASS_MAP: dict[str, Type[Equipment]] = {
    "damper": Damper,
    "fan": Fan,
    "valve": Valve,
    "pump": Pump,
    "filter": Filter,
    "vav-reheat": SingleDuctTerminal,
    "air-handling-unit": AirHandlingUnit,
    "chiller": Chiller,
    "boiler": Boiler,
}

def get_equipment_class(template_name: str) -> Type[Equipment]:
    """Get BSIT-BOB equipment class for template name."""
    if template_name not in TEMPLATE_CLASS_MAP:
        raise KeyError(f"Unknown template: {template_name}")
    return TEMPLATE_CLASS_MAP[template_name]

def create_equipment(template_name: str, label: str, **kwargs) -> Equipment:
    """Create equipment instance from template name."""
    equipment_class = get_equipment_class(template_name)
    return equipment_class(label=label, **kwargs)
```

---

## Gap Analysis

### Gaps Identified

| Gap                     | Impact | Mitigation                                   |
| ----------------------- | ------ | -------------------------------------------- |
| **No built-in SQLite**  | Medium | Use rdflib-sqlalchemy (already installed)    |
| **No ShapeCollection**  | Low    | Use pyshacl directly (already installed)     |
| **Template mapping**    | Low    | Create TemplateType → Class mapping          |
| **Different namespace** | Low    | `bob:` namespace instead of project-specific |

### Features Already Available

- [x] ASHRAE 223P types (s223:Equipment, s223:System, etc.)
- [x] Connection points (inlet/outlet)
- [x] Media types (Fluid-Air, Constituent-Electricity)
- [x] QUDT units integration
- [x] SPARQL query support
- [x] Turtle/JSON-LD serialization
- [x] Schema graph with SHACL shapes

---

## Recommendation: GO

We recommend **adding** BSIT-BOB as an alternative adapter for the following reasons:

1. **All critical operations are mappable** with low-medium complexity
2. **POC demonstrates full functionality** for our use cases
3. **Simpler, more Pythonic API** reduces maintenance burden
4. **Dependencies already installed** (rdflib, pyshacl, rdflib-sqlalchemy)
5. **Architecture principle:** "Libraries are implementation details that can be swapped"
6. **Risk mitigation:** Keeping BuildingMOTIF allows rollback if issues arise
7. **Common interface:** Both adapters implement same protocol for easy switching
8. **Future extensibility:** Supports Brick protocol if required in the future (BSIT-BOB has built-in Brick namespace support)

---

## Implementation Approach

### Architecture: Common Interface Pattern

Both adapters will implement a common `SemanticsAdapterProtocol` interface, enabling:

- Easy switching between implementations via configuration
- Parallel running during migration
- Consistent API for routers regardless of backend

```python
from typing import Protocol, Any
from rdflib import Graph

class SemanticsAdapterProtocol(Protocol):
    """Protocol defining the contract for semantics adapters."""

    @classmethod
    def get_instance(cls, db_path: str | None = None) -> "SemanticsAdapterProtocol":
        """Get singleton instance."""
        ...

    def list_templates(self) -> list[str]:
        """List all available templates/equipment types."""
        ...

    def get_template_by_name(self, template_name: str) -> Any:
        """Get template or equipment class by name."""
        ...

    def create_model(self, namespace: str) -> Any:
        """Create a new RDF model with given namespace."""
        ...

    def add_triples(self, model: Any, triples: list[tuple]) -> None:
        """Add triples to a model."""
        ...

    def query_model(self, model: Any, sparql: str) -> list[dict]:
        """Execute SPARQL query on model."""
        ...

    def serialize_model(self, model: Any, format: str = "turtle") -> str:
        """Serialize model to string."""
        ...

    def validate_model(self, model: Any) -> tuple[bool, str]:
        """Validate model against SHACL shapes. Returns (conforms, report)."""
        ...
```

### Phase 1: Define Common Interface

1. Create `src/adapters/semantics_adapter_protocol.py` with `SemanticsAdapterProtocol`
2. Update `BuildingMOTIFAdapter` to implement the protocol
3. Write interface tests that both adapters must pass

### Phase 2: Create BsitBobAdapter

1. Create `src/adapters/bsit_bob_adapter.py`
2. Implement `SemanticsAdapterProtocol`
3. Wrap BSIT-BOB graph operations
4. Integrate rdflib-sqlalchemy for persistence

### Phase 3: Template Mapping

1. Create TemplateType → BSIT-BOB class mapping
2. Map DeviceTemplate values to Equipment subclasses
3. Map PropertyTemplate values to Property subclasses

### Phase 4: Validation Integration

1. Integrate pyshacl for SHACL validation
2. Load 223P shapes from existing ontology files
3. Implement `validate_model()` method

### Phase 5: Adapter Factory

1. Create `src/adapters/factory.py`
2. Add `use_bsit_bob` setting to Settings
3. Factory returns appropriate adapter based on config

### Phase 6: Testing & Migration

1. Run interface tests against both adapters
2. Add adapter-specific edge case tests
3. Full cutover after validation

---

## Estimated Effort

| Phase                     | Effort       |
| ------------------------- | ------------ |
| Phase 1: Define Interface | 1 day        |
| Phase 2: BsitBobAdapter   | 2-3 days     |
| Phase 3: Template Mapping | 1-2 days     |
| Phase 4: Validation       | 1 day        |
| Phase 5: Adapter Factory  | 0.5 days     |
| Phase 6: Testing          | 1-2 days     |
| **Total**                 | **6-9 days** |

---

## References

- BSIT-BOB Source: `~/Documents/ai-projects/bsit-bob`
- BSIT-BOB Docs: https://bsit-bob.readthedocs.io/en/latest/
- BuildingMOTIF Adapter: `apps/building-semantics-api-app/src/adapters/buildingmotif_adapter.py`
- POC Script: `docs/feature-development/bsit-bob-poc/specs/poc_bsit_bob_usage.py`
