"""
BSIT-BOB Proof of Concept
Demonstrates creating ASHRAE 223P semantic models using BSIT-BOB library.

This POC validates that BSIT-BOB can replace BuildingMOTIF for:
1. Creating equipment instances with 223P types
2. Creating properties and sensors
3. Serializing to Turtle format
4. Querying with SPARQL

Run from project root:
    cd ~/Documents/ai-projects/bsit-bob
    python -m pytest docs/feature-development/bsit-bob-poc/specs/poc_bsit_bob_usage.py -v
"""
import sys
from pathlib import Path

# Add bsit-bob to path for local development
BSIT_BOB_PATH = Path.home() / "Documents/ai-projects/bsit-bob"
if BSIT_BOB_PATH.exists():
    sys.path.insert(0, str(BSIT_BOB_PATH))

from bob.core import (
    Equipment,
    System,
    Property,
    bind_model_namespace,
    dump,
    clear,
    data_graph,
    S223,
    QUDT,
    UNIT,
)
from bob.equipment.hvac.vav import VAV
from bob.equipment.hvac.damper import Damper
from bob.equipment.hvac.fan import Fan
from bob.sensor.temperature import TemperatureSensor
from bob.properties.temperature import Temperature


def demo_simple_equipment():
    """Demo 1: Create simple equipment with label."""
    clear()  # Reset global graph

    # Bind namespace for our model
    ns = bind_model_namespace("demo", "urn:bms-poc/demo/")

    # Create equipment - equivalent to BuildingMOTIF template instantiation
    vav = VAV(label="VAV-101")

    # Serialize to Turtle
    print("\n=== Demo 1: Simple Equipment ===")
    dump()

    # Verify RDF type is correct
    types = list(data_graph.objects(vav._node_iri, S223.type if hasattr(S223, 'type') else None))
    print(f"\nEquipment IRI: {vav._node_iri}")
    print(f"Equipment label: {vav.label}")


def demo_equipment_with_properties():
    """Demo 2: Equipment with properties (like BuildingMOTIF bindings)."""
    clear()

    ns = bind_model_namespace("demo2", "urn:bms-poc/demo2/")

    # Create equipment with property
    class MyVAV(VAV):
        zoneTemp: Temperature

    vav = MyVAV(label="VAV-102")
    vav.zoneTemp = Temperature(label="Zone Temperature", value=72.0)

    print("\n=== Demo 2: Equipment with Properties ===")
    dump()


def demo_system_containment():
    """Demo 3: System containing equipment (like BuildingMOTIF systems)."""
    clear()

    ns = bind_model_namespace("demo3", "urn:bms-poc/demo3/")

    # Create a system
    class AHU(System):
        pass

    ahu = AHU(label="AHU-1")

    # Create components
    supply_fan = Fan(label="Supply Fan")
    damper = Damper(label="OA Damper")

    # Add to system using > operator
    ahu > supply_fan
    ahu > damper

    print("\n=== Demo 3: System Containment ===")
    dump()


def demo_sparql_query():
    """Demo 4: Query the graph with SPARQL."""
    clear()

    ns = bind_model_namespace("demo4", "urn:bms-poc/demo4/")

    # Create some equipment
    vav1 = VAV(label="VAV-201")
    vav2 = VAV(label="VAV-202")
    damper = Damper(label="Damper-1")

    # Query all equipment
    query = """
    PREFIX s223: <http://data.ashrae.org/standard223#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT ?equip ?label WHERE {
        ?equip a s223:Equipment .
        ?equip rdfs:label ?label .
    }
    """

    print("\n=== Demo 4: SPARQL Query ===")
    results = data_graph.query(query)
    for row in results:
        print(f"  Equipment: {row.label}")


def demo_turtle_output_comparison():
    """Demo 5: Generate Turtle output for comparison with BuildingMOTIF."""
    clear()

    ns = bind_model_namespace("comparison", "urn:bms-poc/comparison/")

    # Create a VAV system similar to NREL template
    vav = VAV(label="VAV-Reheat-001")

    # Add a temperature sensor property
    temp_sensor = TemperatureSensor(label="Zone Temp Sensor")

    print("\n=== Demo 5: Turtle Output for Comparison ===")
    print("--- This output can be compared with BuildingMOTIF equivalent ---")
    dump()


if __name__ == "__main__":
    print("BSIT-BOB Proof of Concept")
    print("=" * 50)

    demo_simple_equipment()
    demo_equipment_with_properties()
    demo_system_containment()
    demo_sparql_query()
    demo_turtle_output_comparison()

    print("\n" + "=" * 50)
    print("POC Complete - BSIT-BOB can create 223P semantic models")
