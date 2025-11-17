"""Unit tests for mapping mapper functions."""
from unittest.mock import Mock, MagicMock
from rdflib import URIRef, Literal, Namespace, RDF

import pytest

from src.dto.mappings_dto import SemanticMappingDTO
from src.mappers.mapping_mapper import (
    create_equipment_uri,
    create_device_uri,
    create_property_uri,
    create_bacnet_ref_uri,
    create_project_uri,
    to_equipment_rdf_triples,
    to_project_relationship_triples,
)

S223 = Namespace("http://data.ashrae.org/standard223#")
BACNET = Namespace("http://data.ashrae.org/bacnet/2020#")
BMS = Namespace("urn:bms:")
DCTERMS = Namespace("http://purl.org/dc/terms/")


def test_create_equipment_uri():
    """Test equipment URI creation from point ID."""
    point_id = "device,123:analog-input,1"
    uri = create_equipment_uri(point_id)

    assert isinstance(uri, URIRef)
    assert str(uri) == "urn:bms:Equipment:device-123-analog-input-1"


def test_create_device_uri():
    """Test device URI creation from point ID."""
    point_id = "device,123:analog-input,1"
    uri = create_device_uri(point_id)

    assert isinstance(uri, URIRef)
    assert str(uri) == "urn:bms:Device:device-123-analog-input-1"


def test_create_property_uri():
    """Test property URI creation from point ID."""
    point_id = "device,123:analog-input,1"
    uri = create_property_uri(point_id)

    assert isinstance(uri, URIRef)
    assert str(uri) == "urn:bms:Property:device-123-analog-input-1"


def test_create_bacnet_ref_uri():
    """Test BACnet reference URI creation from point ID."""
    point_id = "device,123:analog-input,1"
    uri = create_bacnet_ref_uri(point_id)

    assert isinstance(uri, URIRef)
    assert str(uri) == "urn:bms:BACnetRef:device-123-analog-input-1"


def test_create_project_uri():
    """Test project URI creation from project ID."""
    project_id = "proj-123"
    uri = create_project_uri(project_id)

    assert isinstance(uri, URIRef)
    assert str(uri) == "urn:bms:Project:proj-123"


def test_to_project_relationship_triples():
    """Test project relationship triples generation."""
    project_uri = URIRef("urn:bms:Project:proj-123")
    equipment_uris = [
        URIRef("urn:bms:Equipment:eq-1"),
        URIRef("urn:bms:Equipment:eq-2"),
    ]

    triples = to_project_relationship_triples(project_uri, equipment_uris)

    assert len(triples) == 2
    assert (project_uri, S223.contains, equipment_uris[0]) in triples
    assert (project_uri, S223.contains, equipment_uris[1]) in triples


def test_to_equipment_rdf_triples_basic():
    """Test equipment RDF triples generation with mocked adapter."""
    from rdflib import Graph

    # Mock adapter and templates
    mock_adapter = Mock()

    # Create mock graphs that template.evaluate() will return
    equipment_uri = create_equipment_uri("device,123:analog-input,1")
    device_uri = create_device_uri("device,123:analog-input,1")
    property_uri = create_property_uri("device,123:analog-input,1")

    # Mock equipment graph
    equipment_graph = Graph()
    equipment_graph.add((equipment_uri, RDF.type, S223.TerminalUnit))

    # Mock device graph
    device_graph = Graph()
    device_graph.add((device_uri, RDF.type, S223.Damper))

    # Mock property graph
    property_graph = Graph()
    property_graph.add((property_uri, RDF.type, S223.DamperPosition))

    # Mock template objects
    mock_equipment_template = Mock()
    mock_equipment_template.name = "vav-reheat"
    # fill() returns (bindings, graph) tuple
    mock_equipment_template.fill = Mock(return_value=({"name": equipment_uri}, equipment_graph))

    mock_device_template = Mock()
    mock_device_template.name = "damper"
    # fill() returns (bindings, graph) tuple
    mock_device_template.fill = Mock(return_value=({"name": device_uri}, device_graph))

    mock_property_template = Mock()
    mock_property_template.name = "damper-feedback"
    # fill() returns (bindings, graph) tuple
    mock_property_template.fill = Mock(return_value=({"name": property_uri}, property_graph))

    # Configure mock adapter to return templates
    def get_template_side_effect(template_enum):
        from src.adapters.template_types import SystemTemplate, DeviceTemplate, PropertyTemplate
        if isinstance(template_enum, SystemTemplate):
            return mock_equipment_template
        elif isinstance(template_enum, DeviceTemplate):
            return mock_device_template
        elif isinstance(template_enum, PropertyTemplate):
            return mock_property_template

    mock_adapter.get_template_by_name.side_effect = get_template_side_effect

    # Create mapping DTO
    mapping = SemanticMappingDTO(
        equipment_type_id="vav-reheat",
        device_type_id="damper",
        property_id="damper-feedback",
        physical_space_id=None,
        domain_space_ids=None,
    )

    # Test
    equipment_uri = create_equipment_uri("device,123:analog-input,1")
    point_id = "device,123:analog-input,1"

    triples = to_equipment_rdf_triples(equipment_uri, point_id, mapping, mock_adapter)

    # Verify triples were generated
    assert len(triples) > 0

    # Verify expected triples exist
    device_uri = create_device_uri(point_id)
    property_uri = create_property_uri(point_id)
    bacnet_ref_uri = create_bacnet_ref_uri(point_id)

    # Check equipment type triple
    assert (equipment_uri, RDF.type, S223.TerminalUnit) in triples
    # Check equipment contains device
    assert (equipment_uri, S223.contains, device_uri) in triples
    # Check device type triple
    assert (device_uri, RDF.type, S223.Damper) in triples
    # Check property type triple
    assert (property_uri, RDF.type, S223.DamperPosition) in triples
    # Check BACnet reference
    assert (bacnet_ref_uri, RDF.type, S223.BACnetExternalReference) in triples
    assert (bacnet_ref_uri, DCTERMS.identifier, Literal("device,123:analog-input,1")) in triples

    # Verify adapter was called 3 times (equipment, device, property)
    assert mock_adapter.get_template_by_name.call_count == 3


def test_point_id_parsing():
    """Test point ID parsing logic."""
    point_id = "device,123:analog-input,1"

    # Simple split (no parsing logic needed)
    device_id, object_id = point_id.split(":")

    assert device_id == "device,123"
    assert object_id == "analog-input,1"

    # Verify format matches bacnet: property format
    assert device_id.startswith("device,")
    assert "," in object_id


def test_extract_class_uri_from_instantiated_template():
    """Test extracting class URI from template instantiated with specific URN.

    This verifies that template.evaluate() + SPARQL query gives deterministic results
    by querying for the specific URN's type, not iterating all triples.
    """
    from buildingmotif.dataclasses import Template
    from rdflib import Graph, URIRef, Namespace, RDF

    # Mock template body simulating vav-reheat template structure
    S223 = Namespace("http://data.ashrae.org/standard223#")
    P = Namespace("urn:___param___#")

    # Create a graph representing the template body
    template_graph = Graph()
    template_graph.add((P.name, RDF.type, S223.TerminalUnit))  # Main entity
    template_graph.add((P["air-in"], RDF.type, S223.InletConnectionPoint))  # Sub-component
    template_graph.add((P["air-out"], RDF.type, S223.OutletConnectionPoint))  # Sub-component
    template_graph.add((P.name, S223.contains, P.device))

    # Mock template with evaluate method
    mock_template = Mock(spec=Template)
    mock_template.name = "vav-reheat"
    mock_template.body = template_graph

    # Simulate template.evaluate() by replacing P:name with actual URN
    equipment_uri = URIRef("urn:bms:Equipment:device-123-analog-input-1")

    # Create instantiated graph (what evaluate() would return)
    instantiated_graph = Graph()
    instantiated_graph.add((equipment_uri, RDF.type, S223.TerminalUnit))
    instantiated_graph.add((URIRef("urn:bms:air-in"), RDF.type, S223.InletConnectionPoint))
    instantiated_graph.add((URIRef("urn:bms:air-out"), RDF.type, S223.OutletConnectionPoint))

    mock_template.evaluate = Mock(return_value=instantiated_graph)

    # Test: Query for the specific URN's type
    query = f"""
        PREFIX s223: <http://data.ashrae.org/standard223#>
        SELECT ?type WHERE {{
            <{equipment_uri}> a ?type .
            FILTER(STRSTARTS(STR(?type), "http://data.ashrae.org/standard223#"))
        }}
    """

    result = instantiated_graph.query(query)
    types = [str(row.type) for row in result]

    # Verify: We get exactly TerminalUnit (the main entity), not connection points
    assert len(types) == 1
    assert types[0] == str(S223.TerminalUnit)
    assert str(S223.InletConnectionPoint) not in types
    assert str(S223.OutletConnectionPoint) not in types

    # Verify this is deterministic - run multiple times
    for _ in range(10):
        result = instantiated_graph.query(query)
        types = [str(row.type) for row in result]
        assert types[0] == str(S223.TerminalUnit)
