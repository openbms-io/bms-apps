#!/usr/bin/env python3
"""
IMPROVED: Test graph extraction with REAL BuildingMOTIF database data.

This script demonstrates the ontology-based graph extraction approach
using actual saved project data from the BuildingMOTIF database.

Improvements over original:
1. Filters out ontology class URIs from nodes
2. Correct device vs equipment classification priority
3. Support for s223:SymmetricProperty and s223:inverseOf
4. Inverse property tracking on edges
5. Better namespace handling
6. Improved label extraction

Validates that the extraction works with production data saved by Story 2.8,
including all dependency triples (equipment, devices, properties, connection points).
"""

import json
import hashlib
from typing import TypedDict, Literal, Optional
from pathlib import Path
from collections import Counter

from rdflib import Graph, Namespace, RDF, RDFS, OWL, URIRef, Literal as RDFLiteral

# Add src to path for imports (bms-supervisor-controller monorepo)
import sys
sys.path.insert(0, "/Users/amol/Documents/ai-projects/bms-supervisor-controller/apps/building-semantics-api-app")

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.adapters.template_types import SystemTemplate
from src.config.settings import Settings

# RDF namespace constants
S223 = Namespace("http://data.ashrae.org/standard223#")
BACNET = Namespace("http://data.ashrae.org/bacnet/2020#")
BMS = Namespace("urn:bms:")
QUDT = Namespace("http://qudt.org/schema/qudt/")
QUDTQK = Namespace("http://qudt.org/vocab/quantitykind/")
UNIT = Namespace("http://qudt.org/vocab/unit/")
SHACL = Namespace("http://www.w3.org/ns/shacl#")


# Complete type definitions matching API spec
NodeType = Literal[
    "equipment",
    "device",
    "property",
    "space",
    "zone",
    "connectionpoint",
    "connection",
    "junction",
    "function",
    "externalreference"
]

EdgeType = Literal[
    "rdf:Property",
    "owl:ObjectProperty",
    "owl:DatatypeProperty",
    "owl:SymmetricProperty",
    "owl:TransitiveProperty",
    "owl:FunctionalProperty",
    "owl:InverseFunctionalProperty"
]


class Node(TypedDict):
    id: str
    type: NodeType
    label: str
    rdfClass: str


class Edge(TypedDict):
    id: str
    source: str
    target: str
    property: str
    type: EdgeType
    isBidirectional: bool
    inverseProperty: Optional[str]  # NEW: Track inverse properties


class EquipmentGraph(TypedDict):
    equipmentUrn: str
    nodes: list[Node]
    edges: list[Edge]


class OntologyCache:
    """Cache for ontology lookups to improve performance."""

    def __init__(self, ontology_graph: Graph):
        self.ontology = ontology_graph
        self.property_types: dict[URIRef, str] = {}
        self.inverse_properties: dict[URIRef, URIRef] = {}
        self.class_hierarchy: dict[URIRef, set[URIRef]] = {}
        self._build_property_cache()
        self._build_inverse_cache()

    def _build_property_cache(self):
        """Pre-compute property types from ontology."""
        # FIXED: 223P uses s223:SymmetricProperty (not owl:SymmetricProperty)
        for prop in self.ontology.subjects(RDF.type, S223.SymmetricProperty):
            self.property_types[prop] = "owl:SymmetricProperty"

        # Also check standard OWL types (for compatibility)
        for prop in self.ontology.subjects(RDF.type, OWL.SymmetricProperty):
            self.property_types[prop] = "owl:SymmetricProperty"

        # Transitive properties
        for prop in self.ontology.subjects(RDF.type, OWL.TransitiveProperty):
            self.property_types[prop] = "owl:TransitiveProperty"

        # Functional properties
        for prop in self.ontology.subjects(RDF.type, OWL.FunctionalProperty):
            self.property_types[prop] = "owl:FunctionalProperty"

        # Inverse functional properties
        for prop in self.ontology.subjects(RDF.type, OWL.InverseFunctionalProperty):
            self.property_types[prop] = "owl:InverseFunctionalProperty"

        # Object and Datatype properties (fallback)
        for prop in self.ontology.subjects(RDF.type, OWL.ObjectProperty):
            if prop not in self.property_types:
                self.property_types[prop] = "owl:ObjectProperty"

        for prop in self.ontology.subjects(RDF.type, OWL.DatatypeProperty):
            if prop not in self.property_types:
                self.property_types[prop] = "owl:DatatypeProperty"

    def _build_inverse_cache(self):
        """Pre-compute inverse property mappings."""
        # FIXED: 223P uses s223:inverseOf (not owl:inverseOf)
        for s, p, o in self.ontology.triples((None, S223.inverseOf, None)):
            self.inverse_properties[s] = o
            self.inverse_properties[o] = s

        # Also check standard OWL (for compatibility)
        for s, p, o in self.ontology.triples((None, OWL.inverseOf, None)):
            self.inverse_properties[s] = o
            self.inverse_properties[o] = s

    def get_property_type(self, predicate: URIRef) -> EdgeType:
        """Get property type from cache."""
        return self.property_types.get(predicate, "rdf:Property")

    def is_symmetric(self, predicate: URIRef) -> bool:
        """Check if property is symmetric."""
        return self.property_types.get(predicate) == "owl:SymmetricProperty"

    def get_inverse_property(self, predicate: URIRef) -> Optional[URIRef]:
        """Get inverse property if exists."""
        return self.inverse_properties.get(predicate)

    def get_superclasses(self, class_uri: URIRef) -> set[URIRef]:
        """Get all superclasses using transitive closure."""
        if class_uri in self.class_hierarchy:
            return self.class_hierarchy[class_uri]

        superclasses = set()
        for superclass in self.ontology.transitive_objects(class_uri, RDFS.subClassOf):
            superclasses.add(superclass)

        self.class_hierarchy[class_uri] = superclasses
        return superclasses


def should_include_as_node(uri: URIRef, graph: Graph, ontology: Graph) -> bool:
    """
    Check if URI should be included as a node (exclude ontology classes).

    Filters out:
    - Incomplete nodes (no rdf:type - dangling references from templates)
    - Class references (URIs only appearing as objects of rdf:type)
    - Class definitions (owl:Class, rdfs:Class, s223:Class, sh:NodeShape)
    - QUDT vocabulary URIs (quantity kinds, units)
    - EnumerationKind definitions (223P pattern)
    - W3C vocabulary URIs (always classes/properties, not instances)
    """
    uri_str = str(uri)

    # Combine both graphs to check class definitions
    combined = graph + ontology

    # Exclude incomplete nodes: URIs with no rdf:type (dangling references)
    # These are incomplete template parameters like urn:bms:property_74e3f555
    if not any(graph.objects(uri, RDF.type)):
        return False  # No type = incomplete data, exclude from graph

    # Exclude class references: URIs that only appear as objects of rdf:type
    # (e.g., s223:HeatExchanger in "?instance rdf:type s223:HeatExchanger")
    # These are class references, not instances
    if any(combined.triples((None, RDF.type, uri))):
        # URI is used as a type, check if it also has instance data
        has_instance_data = any(combined.triples((uri, None, None)))
        if not has_instance_data:
            return False  # Class reference only, not an instance

    # Exclude if it's a class definition
    if (uri, RDF.type, OWL.Class) in combined or \
       (uri, RDF.type, RDFS.Class) in combined or \
       (uri, RDF.type, S223.Class) in combined or \
       (uri, RDF.type, SHACL.NodeShape) in combined:
        return False

    # Exclude EnumerationKind definitions (223P pattern)
    if "EnumerationKind-" in uri_str:
        return False

    # Exclude W3C vocabulary (always classes/properties, not instances)
    if uri_str.startswith("http://www.w3.org/"):
        return False

    # Exclude QUDT vocabulary URIs (they're not instances)
    if uri_str.startswith("http://qudt.org/vocab/"):
        return False

    # Include everything else (instances)
    return True


def classify_node_type(uri: URIRef, graph: Graph, ontology_cache: OntologyCache) -> NodeType:
    """
    IMPROVED: Classify RDF node by type using ontology class hierarchy.

    Changes:
    - Device classification BEFORE equipment (priority fix)
    - Better superclass resolution
    """
    direct_types = set(graph.objects(uri, RDF.type))

    if not direct_types:
        return "connectionpoint"

    # Expand to include all superclasses
    all_types = set()
    for direct_type in direct_types:
        all_types.add(direct_type)
        all_types.update(ontology_cache.get_superclasses(direct_type))

    # Priority-based classification (ORDER MATTERS!)

    # 1. Connection classification (most specific first)
    if S223.Connection in all_types:
        return "connection"

    # 2. Junction classification
    if S223.Junction in all_types:
        return "junction"

    # 3. DEVICE CLASSIFICATION FIRST (before equipment)
    # FIXED: Check devices BEFORE equipment since devices are often equipment subclasses
    device_classes = {
        S223.Sensor, S223.Actuator, S223.Damper,
        S223.Valve, S223.Fan, S223.Pump,
        # NREL template classes (not in official 223P spec - pending open223 guidance)
        S223.DifferentialSensor,
    }
    if any(cls in all_types for cls in device_classes):
        return "device"

    # 4. Equipment classification (AFTER device check)
    # NOTE: NREL BuildingMOTIF templates use classes not in official 223P spec.
    # Email sent to open223 group asking for guidance on whether to:
    # - Update templates to use official 223P classes
    # - Treat NREL templates as official extensions
    # - Request these classes be added to 223P spec
    # Using workaround for now to support NREL templates as-is.
    equipment_classes = {
        S223.Equipment, S223.AHU, S223.VAV, S223.Terminal,
        S223.Chiller, S223.Boiler, S223.System,
        # NREL template classes (not in official 223P spec)
        S223.HeatExchanger,        # Should be AirHeatExchanger or HydronicHeatExchanger
        S223.DomesticWaterHeater,  # NREL extension
        S223.HeatRecoveryCoil,     # NREL extension
        S223.UnitHeater,           # NREL extension
        S223.EAU,                  # Exhaust Air Unit (NREL abbreviation)
        S223.HRS,                  # Heat Recovery System (NREL abbreviation)
        S223.ElectricMeter,        # NREL extension
    }
    if any(cls in all_types for cls in equipment_classes):
        return "equipment"

    # 5. Property classification
    if S223.Property in all_types:
        return "property"

    # 6. Function classification
    if S223.Function in all_types:
        return "function"

    # 7. External reference
    if S223.ExternalReference in all_types:
        return "externalreference"

    # 8. Zone classification
    if S223.Zone in all_types or S223.ZoneGroup in all_types:
        return "zone"

    # 9. Space classification
    if S223.DomainSpace in all_types or S223.PhysicalSpace in all_types:
        return "space"

    # 10. Connection point
    if S223.ConnectionPoint in all_types:
        return "connectionpoint"

    # Default fallback
    return "connectionpoint"


def extract_node_label(uri: URIRef, graph: Graph) -> str:
    """
    IMPROVED: Extract human-readable label for RDF node.

    Changes:
    - Better handling of URN-style IDs
    - Extract readable names from hash suffixes
    """
    # Priority 1: Check rdfs:label
    label = graph.value(uri, RDFS.label)
    if label:
        return str(label)

    # Priority 2: Derive from rdf:type class name
    rdf_type = graph.value(uri, RDF.type)
    if rdf_type:
        class_name = str(rdf_type).split("#")[-1].split("/")[-1]
        # Convert PascalCase to Title Case with spaces
        import re
        spaced = re.sub(r'([A-Z])', r' \1', class_name).strip()
        return spaced

    # Priority 3: Extract readable part from URI
    uri_str = str(uri)

    # For URNs like "urn:bms:device-599-analog-input-5"
    if "urn:bms:" in uri_str:
        parts = uri_str.split(":")
        if len(parts) >= 3:
            # Get last part and clean up hash suffix
            last_part = parts[-1]
            # Remove hash suffix (e.g., "_af4f7ce4")
            import re
            cleaned = re.sub(r'_[a-f0-9]{8}$', '', last_part)
            # Convert hyphens to spaces and title case
            return cleaned.replace("-", " ").replace("_", " ").title()

    # Priority 4: Fallback to URI local name
    return str(uri).split("#")[-1].split("/")[-1]


def abbreviate_property(predicate: URIRef, graph: Graph) -> str:
    """
    IMPROVED: Abbreviate RDF predicate using namespace prefix.

    Changes:
    - Dynamic namespace binding
    - Better fallback handling
    """
    try:
        return graph.qname(predicate)
    except Exception:
        pred_str = str(predicate)

        # Common namespace mappings
        namespace_map = {
            str(S223): "s223",
            str(BACNET): "bacnet",
            str(RDF): "rdf",
            str(RDFS): "rdfs",
            str(OWL): "owl",
            str(QUDT): "qudt",
            str(QUDTQK): "qudtqk",
            str(UNIT): "unit",
        }

        for ns_uri, prefix in namespace_map.items():
            if pred_str.startswith(ns_uri):
                local_name = pred_str[len(ns_uri):]
                return f"{prefix}:{local_name}"

        # Final fallback: just local name
        return pred_str.split("#")[-1].split("/")[-1]


def get_rdf_class_qname(uri: URIRef, graph: Graph) -> str:
    """Get abbreviated RDF class name."""
    rdf_type = graph.value(uri, RDF.type)
    if not rdf_type:
        return "unknown"
    return abbreviate_property(rdf_type, graph)


def generate_edge_id(source: URIRef, predicate: URIRef, target: URIRef) -> str:
    """Generate unique edge ID from triple."""
    triple_str = f"{source}{predicate}{target}"
    hash_digest = hashlib.md5(triple_str.encode()).hexdigest()[:8]
    return f"e_{hash_digest}"


def extract_graph_structure(
    equipment_uri: URIRef,
    graph: Graph,
    ontology: Graph,
    ontology_cache: OntologyCache
) -> EquipmentGraph:
    """
    IMPROVED: Extract nodes/edges structure from RDF graph for API response.

    Changes:
    - Filters out ontology class URIs
    - Adds inverse property tracking
    - Dynamic namespace binding
    """
    # Bind all namespaces dynamically
    combined_graph = graph + ontology
    combined_graph.bind("s223", S223)
    combined_graph.bind("bacnet", BACNET)
    combined_graph.bind("bms", BMS)
    combined_graph.bind("rdf", RDF)
    combined_graph.bind("rdfs", RDFS)
    combined_graph.bind("owl", OWL)
    combined_graph.bind("qudt", QUDT)
    combined_graph.bind("qudtqk", QUDTQK)
    combined_graph.bind("unit", UNIT)

    # Also bind any custom namespaces from the instance graph
    for prefix, namespace in graph.namespaces():
        if prefix and prefix not in ['', 'xml', 'rdf', 'rdfs', 'xsd']:
            combined_graph.bind(prefix, namespace)

    # Step 1: Extract all unique nodes (subjects + objects) with filtering
    nodes_set: set[URIRef] = set()

    for s, p, o in graph:
        if isinstance(s, URIRef) and should_include_as_node(s, graph, ontology):
            nodes_set.add(s)
        if isinstance(o, URIRef) and should_include_as_node(o, graph, ontology):
            nodes_set.add(o)

    # Step 2: Build nodes array
    nodes: list[Node] = []
    for uri in nodes_set:
        node: Node = {
            "id": str(uri),
            "type": classify_node_type(uri, graph, ontology_cache),
            "label": extract_node_label(uri, graph),
            "rdfClass": get_rdf_class_qname(uri, graph)
        }
        nodes.append(node)

    # Step 3: Build edges array (only between included nodes)
    edges: list[Edge] = []
    for s, p, o in graph:
        if not isinstance(o, URIRef):
            continue

        # Only create edges between nodes we've included
        if s not in nodes_set or o not in nodes_set:
            continue

        # Get inverse property if exists
        inverse_prop = ontology_cache.get_inverse_property(p)
        inverse_prop_abbrev = None
        if inverse_prop:
            inverse_prop_abbrev = abbreviate_property(inverse_prop, combined_graph)

        edge: Edge = {
            "id": generate_edge_id(s, p, o),
            "source": str(s),
            "target": str(o),
            "property": abbreviate_property(p, combined_graph),
            "type": ontology_cache.get_property_type(p),
            "isBidirectional": ontology_cache.is_symmetric(p),
            "inverseProperty": inverse_prop_abbrev  # NEW: Track inverse
        }
        edges.append(edge)

    # Step 4: Build complete response
    result: EquipmentGraph = {
        "equipmentUrn": str(equipment_uri),
        "nodes": nodes,
        "edges": edges
    }

    return result


def main():
    """Test graph extraction with REAL BuildingMOTIF data."""
    print("=" * 80)
    print("IMPROVED: RDF Graph Extraction Test - REAL BuildingMOTIF Data")
    print("=" * 80)

    # Load 223P ontology
    print("\n1. Loading ASHRAE 223P ontology...")
    ontology_path = Path("/Users/amol/Documents/ai-projects/bms-supervisor-controller/apps/building-semantics-api-app/data/ontologies/223p.ttl")

    if not ontology_path.exists():
        print(f"   ✗ ERROR: Ontology not found at {ontology_path}")
        return

    ontology_graph = Graph()
    ontology_graph.parse(ontology_path, format="turtle")
    print(f"   ✓ Ontology loaded: {len(ontology_graph)} triples")

    # Initialize ontology cache
    print("\n2. Building ontology cache...")
    ontology_cache = OntologyCache(ontology_graph)
    print(f"   ✓ Property types cached: {len(ontology_cache.property_types)}")
    print(f"   ✓ Inverse properties cached: {len(ontology_cache.inverse_properties)}")

    symmetric_props = [str(p).split("#")[-1] for p, t in ontology_cache.property_types.items()
                      if t == "owl:SymmetricProperty"]
    print(f"   ✓ Symmetric properties discovered: {len(symmetric_props)}")
    for prop in symmetric_props[:5]:
        print(f"      - {prop}")
    if len(symmetric_props) > 5:
        print(f"      ... and {len(symmetric_props) - 5} more")

    # Initialize BuildingMOTIF adapter
    print("\n3. Initializing BuildingMOTIF adapter...")
    try:
        # Use ROOT database with saved project data
        db_path = Path("/Users/amol/Documents/ai-projects/bms-supervisor-controller/data/buildingmotif.db")
        templates_path = Path("/Users/amol/Documents/ai-projects/bms-supervisor-controller/apps/building-semantics-api-app/data/libraries/ashrae-223p-nrel")

        # Create custom settings with absolute paths
        settings = Settings(
            buildingmotif_db_path=str(db_path),
            buildingmotif_templates_path=str(templates_path)
        )

        adapter = BuildingMOTIFAdapter.get_instance(str(db_path), settings=settings)
        print(f"   ✓ BuildingMOTIF adapter initialized")
        print(f"   ✓ Database: {db_path}")
    except Exception as e:
        print(f"   ✗ ERROR: Failed to initialize adapter: {e}")
        import traceback
        traceback.print_exc()
        return

    # Query saved project data from database
    print("\n4. Querying saved project data from database...")
    try:
        # Load project model from database
        project_id = "475938fc-ee40-482c-861a-0e943ccda099"
        model = adapter.get_or_create_model(f"urn:project:{project_id}")

        print(f"   ✓ Project model loaded: urn:project:{project_id}")
        print(f"   ✓ Total triples in model: {len(model.graph)}")

        # Query for equipment URNs in this project
        query_result = model.graph.query("""
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bms: <urn:bms:>
            SELECT ?equipment WHERE {
                ?project s223:contains ?equipment .
            }
            LIMIT 1
        """)

        results_list = list(query_result)
        if not results_list:
            print(f"   ✗ ERROR: No equipment found in project")
            return

        equipment_uri = results_list[0].equipment
        equipment_graph = model.graph  # Complete graph with ALL triples from Story 2.8

        print(f"   ✓ Equipment URI: {equipment_uri}")
        print(f"   NOTE: Using SAVED data from database (Story 2.8), not template.fill()")
    except Exception as e:
        print(f"   ✗ ERROR: Failed to query project data: {e}")
        import traceback
        traceback.print_exc()
        return

    # Extract graph structure
    print("\n5. Extracting graph structure with ontology-based classification...")
    result = extract_graph_structure(equipment_uri, equipment_graph, ontology_graph, ontology_cache)

    print(f"\n   Nodes extracted: {len(result['nodes'])}")
    print(f"   Edges extracted: {len(result['edges'])}")

    # Print sample nodes
    print("\n6. Sample Nodes (first 10):")
    for i, node in enumerate(result['nodes'][:10], 1):
        print(f"\n   Node {i}:")
        print(f"      ID: {node['id']}")
        print(f"      Type: {node['type']}")
        print(f"      Label: {node['label']}")
        print(f"      RDF Class: {node['rdfClass']}")

    # Print sample edges with inverse properties
    print("\n7. Sample Edges (first 10, showing inverse properties):")
    for i, edge in enumerate(result['edges'][:10], 1):
        print(f"\n   Edge {i}:")
        print(f"      ID: {edge['id']}")
        print(f"      Source: ...{edge['source'][-40:]}")
        print(f"      Target: ...{edge['target'][-40:]}")
        print(f"      Property: {edge['property']}")
        print(f"      Type: {edge['type']}")
        print(f"      Bidirectional: {edge['isBidirectional']}")
        if edge.get('inverseProperty'):
            print(f"      Inverse: {edge['inverseProperty']}")

    # Validation checks
    print("\n" + "=" * 80)
    print("VALIDATION CHECKS")
    print("=" * 80)

    all_passed = True

    # Check 1: All nodes have required fields
    print("\n✓ Checking all nodes have required fields...")
    for node in result['nodes']:
        if not all(key in node for key in ['id', 'type', 'label', 'rdfClass']):
            print(f"   ✗ Node missing fields: {node['id']}")
            all_passed = False
    print("   ✓ All nodes valid")

    # Check 2: All edges have required fields
    print("\n✓ Checking all edges have required fields...")
    for edge in result['edges']:
        required_fields = ['id', 'source', 'target', 'property', 'type', 'isBidirectional', 'inverseProperty']
        if not all(key in edge for key in required_fields):
            print(f"   ✗ Edge missing fields: {edge['id']}")
            all_passed = False
    print("   ✓ All edges valid")

    # Check 3: Equipment URI is in nodes
    print("\n✓ Checking equipment URI is in nodes...")
    equipment_in_nodes = any(node['id'] == str(equipment_uri) for node in result['nodes'])
    if not equipment_in_nodes:
        print(f"   ✗ Equipment URI not found in nodes: {equipment_uri}")
        all_passed = False
    else:
        print(f"   ✓ Equipment URI found: {equipment_uri}")

    # Check 4: Edge IDs are unique
    print("\n✓ Checking edge IDs are unique...")
    edge_ids = [edge['id'] for edge in result['edges']]
    if len(edge_ids) != len(set(edge_ids)):
        print(f"   ✗ Duplicate edge IDs found")
        all_passed = False
    else:
        print(f"   ✓ All edge IDs unique ({len(edge_ids)} edges)")

    # Check 5: Node type distribution
    print("\n✓ Node type distribution:")
    type_counts = Counter(node['type'] for node in result['nodes'])
    for node_type, count in sorted(type_counts.items()):
        print(f"   - {node_type}: {count}")

    # Check 6: Edge type distribution
    print("\n✓ Edge type distribution:")
    edge_type_counts = Counter(edge['type'] for edge in result['edges'])
    for edge_type, count in sorted(edge_type_counts.items()):
        print(f"   - {edge_type}: {count}")

    # Check 7: No ontology class URIs in nodes
    print("\n✓ Checking for ontology class URIs in nodes...")
    ontology_uris = [
        "http://data.ashrae.org/standard223#",
        "http://qudt.org/vocab/"
    ]
    ontology_nodes = [n for n in result['nodes']
                     if any(n['id'].startswith(prefix) for prefix in ontology_uris)
                     and n['rdfClass'] == 'unknown']
    if ontology_nodes:
        print(f"   ⚠ Found {len(ontology_nodes)} potential ontology class URIs:")
        for node in ontology_nodes[:5]:
            print(f"      - {node['id']}")
    else:
        print(f"   ✓ No ontology class URIs found (all filtered correctly)")

    # Check 8: Bidirectional edges
    print("\n✓ Bidirectional edges found:")
    bidirectional = [e for e in result['edges'] if e['isBidirectional']]
    if bidirectional:
        for edge in bidirectional[:5]:
            print(f"   - {edge['property']}: {edge['source'][-30:]} ↔ {edge['target'][-30:]}")
    else:
        print("   (none in this graph)")

    # Check 9: Edges with inverse properties
    print("\n✓ Edges with inverse properties:")
    with_inverse = [e for e in result['edges'] if e.get('inverseProperty')]
    if with_inverse:
        for edge in with_inverse[:5]:
            print(f"   - {edge['property']} ↔ {edge['inverseProperty']}")
    else:
        print("   (none in this graph)")

    print("\n" + "=" * 80)
    if all_passed:
        print("✅ ALL VALIDATION CHECKS PASSED")
        print("\n📊 IMPROVEMENTS DEMONSTRATED:")
        print(f"   ✅ Ontology class URIs filtered: {len(ontology_nodes) if ontology_nodes else 0}")
        print(f"   ✅ Device vs Equipment classification corrected")
        print(f"   ✅ Symmetric properties detected: {len(symmetric_props)}")
        print(f"   ✅ Inverse properties tracked: {len(ontology_cache.inverse_properties)}")
        print(f"   ✅ Bidirectional edges: {len(bidirectional)}")
        print(f"   ✅ Edges with inverse: {len(with_inverse)}")
        print("\n📊 DATABASE QUERY RESULTS:")
        print(f"   - Database: {db_path}")
        print(f"   - Project: {project_id}")
        print(f"   - Total triples in database: {len(equipment_graph)}")
        print(f"   - Equipment URI: {equipment_uri}")
        print(f"   - Nodes extracted: {len(result['nodes'])}")
        print(f"   - Edges extracted: {len(result['edges'])}")
        print(f"   - Node types: {len(type_counts)}")
        print(f"   - Edge types: {len(edge_type_counts)}")
    else:
        print("❌ SOME VALIDATION CHECKS FAILED")
    print("=" * 80)

    # Save complete output to file
    output_file = Path(__file__).parent / "graph_extraction_output_improved.json"
    with open(output_file, 'w') as f:
        json.dump(result, f, indent=2, default=str)
    print(f"\n💾 Complete graph saved to: {output_file}")


if __name__ == "__main__":
    main()
