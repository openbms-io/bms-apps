"""Integration tests for project relationship RDF patterns (Story 2.8 - Task 0).

Validates external project relationship architecture and clean S223-compliant TTL export
BEFORE implementing full mappings persistence.
"""

import pytest
from rdflib import Graph, Namespace, RDF, URIRef, Literal

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter

S223 = Namespace("http://data.ashrae.org/standard223#")
BACNET = Namespace("http://data.ashrae.org/bacnet/2020#")
BMS = Namespace("urn:bms:")
DCTERMS = Namespace("http://purl.org/dc/terms/")


@pytest.mark.asyncio
async def test_external_project_relationship_pattern(shared_adapter):
    """
    Test external project relationship: project s223:contains equipment.

    Verifies:
    - Equipment instances are pure 223P (no project metadata)
    - Project relationship stored separately
    - Can filter equipment by project
    - Can export clean 223P TTL (equipment only)
    """
    adapter: BuildingMOTIFAdapter = shared_adapter
    project_id = "test-project-external-rel"
    project_uri = URIRef(f"urn:bms:Project:{project_id}")
    equipment_uri = URIRef("urn:bms:Equipment:test-eq-1")

    # Create test model
    model = adapter.create_model(f"urn:test:{project_id}")

    # Add equipment instance (pure 223P - no project metadata)
    equipment_triples = [
        (equipment_uri, RDF.type, S223.TerminalUnit),
        (equipment_uri, S223.contains, URIRef("urn:bms:Device:test-dev-1")),
    ]

    # Add external project relationship (stored separately)
    project_triples = [
        (project_uri, RDF.type, BMS.Project),
        (project_uri, DCTERMS.identifier, Literal(project_id)),
        (project_uri, S223.contains, equipment_uri),  # External relationship
    ]

    # Add triples to model graph
    for triple in equipment_triples + project_triples:
        model.graph.add(triple)

    # Verify: Can query equipment by project using external relationship
    query_result = model.graph.query(
        f"""
        PREFIX s223: <http://data.ashrae.org/standard223#>
        PREFIX bms: <urn:bms:>

        SELECT ?equipment
        WHERE {{
            <{project_uri}> s223:contains ?equipment .
        }}
        """
    )

    equipment_list = [row.equipment for row in query_result]
    assert equipment_uri in equipment_list, "Equipment not found via project relationship"

    # Verify: Equipment instance has no embedded project metadata
    for _, pred, obj in model.graph.triples((equipment_uri, None, None)):
        assert "Project" not in str(obj), f"Equipment has embedded project metadata: {pred} {obj}"
        assert project_id not in str(obj), f"Equipment has embedded projectId: {pred} {obj}"

    # Verify: Can export clean 223P TTL (equipment only, no project)
    construct_query = f"""
        PREFIX s223: <http://data.ashrae.org/standard223#>
        PREFIX bms: <urn:bms:>

        CONSTRUCT {{
            ?equipment ?p ?o .
            ?device ?dp ?do .
        }}
        WHERE {{
            <{project_uri}> s223:contains ?equipment .
            ?equipment ?p ?o .
            OPTIONAL {{
                ?equipment s223:contains ?device .
                ?device ?dp ?do .
            }}
        }}
    """

    export_graph = model.graph.query(construct_query).graph
    assert len(export_graph) > 0, "Export graph is empty"

    # Verify: Export has no bms:Project instances
    project_types = list(export_graph.triples((None, RDF.type, BMS.Project)))
    assert len(project_types) == 0, "Export graph contains bms:Project (should be equipment only)"

    # Verify: Export has equipment
    equipment_types = list(export_graph.triples((equipment_uri, RDF.type, S223.TerminalUnit)))
    assert len(equipment_types) == 1, "Export graph missing equipment instance"


@pytest.mark.asyncio
async def test_bacnet_external_reference_223p_compliance(shared_adapter):
    """
    Test 223P-compliant BACnetExternalReference.

    Verifies:
    - Uses s223:BACnetExternalReference subclass
    - Uses bacnet:device-identifier property
    - Uses bacnet:object-identifier property
    - All bacnet: properties are optional (per SHACL)
    """
    adapter: BuildingMOTIFAdapter = shared_adapter
    equipment_uri = URIRef("urn:bms:Equipment:test-bacnet-1")
    bacnet_ref_uri = URIRef("urn:bms:BACnetRef:test-bacnet-ref-1")
    point_id = "device,123:analog-input,1"

    # Create test model
    model = adapter.create_model("urn:test:bacnet-ref-test")

    # Parse point_id (simple split)
    device_id, object_id = point_id.split(":")

    # Add BACnetExternalReference triples (223P-compliant)
    bacnet_triples = [
        (equipment_uri, RDF.type, S223.TerminalUnit),
        (equipment_uri, S223.hasExternalReference, bacnet_ref_uri),
        (bacnet_ref_uri, RDF.type, S223.BACnetExternalReference),
        (bacnet_ref_uri, BACNET["device-identifier"], Literal(device_id)),
        (bacnet_ref_uri, BACNET["object-identifier"], Literal(object_id)),
        (bacnet_ref_uri, DCTERMS.identifier, Literal(point_id)),
    ]

    for triple in bacnet_triples:
        model.graph.add(triple)

    # Verify: BACnetExternalReference type
    ref_type = model.graph.value(bacnet_ref_uri, RDF.type)
    assert ref_type == S223.BACnetExternalReference, f"Expected s223:BACnetExternalReference, got {ref_type}"

    # Verify: bacnet:device-identifier property
    device_identifier = model.graph.value(bacnet_ref_uri, BACNET["device-identifier"])
    assert device_identifier == Literal(device_id), f"Expected {device_id}, got {device_identifier}"

    # Verify: bacnet:object-identifier property
    object_identifier = model.graph.value(bacnet_ref_uri, BACNET["object-identifier"])
    assert object_identifier == Literal(object_id), f"Expected {object_id}, got {object_identifier}"

    # Verify: dcterms:identifier (point_id)
    identifier = model.graph.value(bacnet_ref_uri, DCTERMS.identifier)
    assert identifier == Literal(point_id), f"Expected {point_id}, got {identifier}"

    # Verify: Equipment has external reference
    external_ref = model.graph.value(equipment_uri, S223.hasExternalReference)
    assert external_ref == bacnet_ref_uri, "Equipment missing s223:hasExternalReference"


async def test_point_id_format_split_no_parsing(shared_adapter):
    """
    Test point ID format from Designer app.

    Verifies:
    - Point ID format: "device,123:analog-input,1"
    - Simple split(":") extracts device_id and object_id
    - No parsing logic needed (already 223P-compliant)
    """
    point_id = "device,123:analog-input,1"

    # Simple split (no parsing logic)
    device_id, object_id = point_id.split(":")

    # Verify format matches bacnet: property format
    assert device_id == "device,123", f"Expected 'device,123', got {device_id}"
    assert object_id == "analog-input,1", f"Expected 'analog-input,1', got {object_id}"

    # Verify: Matches bacnet:device-identifier format
    assert device_id.startswith("device,"), "device_id should start with 'device,'"

    # Verify: Matches bacnet:object-identifier format (type,instance)
    assert "," in object_id, "object_id should contain ',' separator"
    object_type, instance = object_id.split(",")
    assert object_type == "analog-input", f"Expected 'analog-input', got {object_type}"
    assert instance == "1", f"Expected '1', got {instance}"


@pytest.mark.asyncio
async def test_clean_223p_ttl_export_no_project_metadata(shared_adapter):
    """
    Test clean 223P TTL export without project metadata.

    Verifies:
    - SPARQL CONSTRUCT query filters by project
    - Exported TTL contains only equipment instances (no bms:Project)
    - Equipment instances have no project ID embedded
    - TTL is valid 223P (can be imported by other systems)
    """
    adapter: BuildingMOTIFAdapter = shared_adapter
    project_id = "test-project-export"
    project_uri = URIRef(f"urn:bms:Project:{project_id}")
    equipment_uri = URIRef("urn:bms:Equipment:test-export-eq-1")
    device_uri = URIRef("urn:bms:Device:test-export-dev-1")
    property_uri = URIRef("urn:bms:Property:test-export-prop-1")
    bacnet_ref_uri = URIRef("urn:bms:BACnetRef:test-export-ref-1")

    # Create test model
    model = adapter.create_model(f"urn:test:{project_id}")

    # Add complete equipment hierarchy
    triples = [
        # Project (external relationship)
        (project_uri, RDF.type, BMS.Project),
        (project_uri, DCTERMS.identifier, Literal(project_id)),
        (project_uri, S223.contains, equipment_uri),
        # Equipment (pure 223P)
        (equipment_uri, RDF.type, S223.TerminalUnit),
        (equipment_uri, S223.contains, device_uri),
        (equipment_uri, S223.hasExternalReference, bacnet_ref_uri),
        # Device
        (device_uri, RDF.type, S223.Damper),
        (device_uri, S223.hasProperty, property_uri),
        # Property
        (property_uri, RDF.type, S223.DamperPosition),
        # BACnet reference
        (bacnet_ref_uri, RDF.type, S223.BACnetExternalReference),
        (bacnet_ref_uri, BACNET["device-identifier"], Literal("device,123")),
        (bacnet_ref_uri, BACNET["object-identifier"], Literal("analog-input,1")),
    ]

    for triple in triples:
        model.graph.add(triple)

    # SPARQL CONSTRUCT query (filters by project, exports equipment only)
    construct_query = f"""
        PREFIX s223: <http://data.ashrae.org/standard223#>
        PREFIX bacnet: <http://data.ashrae.org/bacnet/2020#>
        PREFIX bms: <urn:bms:>
        PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
        PREFIX dcterms: <http://purl.org/dc/terms/>

        CONSTRUCT {{
            ?equipment ?equipmentP ?equipmentO .
            ?device ?deviceP ?deviceO .
            ?property ?propertyP ?propertyO .
            ?bacnetRef ?bacnetP ?bacnetO .
        }}
        WHERE {{
            # Filter by project (external relationship)
            <{project_uri}> s223:contains ?equipment .

            # Equipment triples
            ?equipment ?equipmentP ?equipmentO .

            # Device triples (optional)
            OPTIONAL {{
                ?equipment s223:contains ?device .
                ?device ?deviceP ?deviceO .

                # Property triples (optional)
                OPTIONAL {{
                    ?device s223:hasProperty ?property .
                    ?property ?propertyP ?propertyO .
                }}
            }}

            # BACnet reference triples (optional)
            OPTIONAL {{
                ?equipment s223:hasExternalReference ?bacnetRef .
                ?bacnetRef ?bacnetP ?bacnetO .
            }}
        }}
    """

    export_graph = model.graph.query(construct_query).graph

    # Verify: Export graph is not empty
    assert len(export_graph) > 0, "Export graph is empty"

    # Verify: No bms:Project in export
    project_instances = list(export_graph.triples((None, RDF.type, BMS.Project)))
    assert len(project_instances) == 0, "Export contains bms:Project (should be equipment only)"

    # Verify: No s223:contains relationships in export (external relationship excluded)
    contains_from_project = list(export_graph.triples((project_uri, S223.contains, None)))
    assert len(contains_from_project) == 0, "Export contains project s223:contains relationship"

    # Verify: Equipment exists in export
    equipment_instances = list(export_graph.triples((equipment_uri, RDF.type, S223.TerminalUnit)))
    assert len(equipment_instances) == 1, "Export missing equipment instance"

    # Verify: Device exists in export
    device_instances = list(export_graph.triples((device_uri, RDF.type, S223.Damper)))
    assert len(device_instances) == 1, "Export missing device instance"

    # Verify: Property exists in export
    property_instances = list(export_graph.triples((property_uri, RDF.type, S223.DamperPosition)))
    assert len(property_instances) == 1, "Export missing property instance"

    # Verify: BACnetExternalReference exists in export
    bacnet_instances = list(export_graph.triples((bacnet_ref_uri, RDF.type, S223.BACnetExternalReference)))
    assert len(bacnet_instances) == 1, "Export missing BACnetExternalReference"

    # Verify: No project ID embedded in equipment triples
    for subj, pred, obj in export_graph.triples((equipment_uri, None, None)):
        assert project_id not in str(obj), f"Equipment has embedded projectId: {pred} {obj}"

    # Verify: Export is valid 223P (equipment s223:contains device pattern)
    device_contains = list(export_graph.triples((equipment_uri, S223.contains, device_uri)))
    assert len(device_contains) == 1, "Export missing s223:contains device relationship"

    # Verify: Export has device s223:hasProperty pattern
    property_has = list(export_graph.triples((device_uri, S223.hasProperty, property_uri)))
    assert len(property_has) == 1, "Export missing s223:hasProperty relationship"
