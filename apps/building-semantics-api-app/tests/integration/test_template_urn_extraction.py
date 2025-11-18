"""Integration test for template.fill() approach for deterministic type extraction.

Tests that template.fill() generates complete graphs with all sub-components,
and that we can extract class URIs deterministically from the generated graphs.
"""

import pytest
from rdflib import URIRef, Namespace, RDF

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.adapters.template_types import SystemTemplate, DeviceTemplate, PropertyTemplate

S223 = Namespace("http://data.ashrae.org/standard223#")
BMS = Namespace("urn:bms:")


@pytest.mark.asyncio
async def test_fill_approach_generates_complete_graph(shared_adapter):
    """Test that template.fill() generates complete instantiated graphs.

    Verifies that fill() creates graphs with all sub-components (sensors,
    connection points, etc.) and proper type declarations.
    """
    adapter: BuildingMOTIFAdapter = shared_adapter

    # Get vav-reheat template (has TerminalUnit + sensors + connection points)
    template = adapter.get_template_by_name(SystemTemplate.VAV_REHEAT)

    # Use fill() to generate complete instantiated graph
    bindings, graph = template.fill(BMS)

    # Verify bindings contains 'name' and other parameters
    assert "name" in bindings
    auto_equipment_uri = bindings["name"]

    # Verify the auto-generated URN has correct type in graph
    equipment_type = graph.value(auto_equipment_uri, RDF.type)
    assert equipment_type == S223.TerminalUnit

    # Verify graph contains multiple triples (not just the type)
    assert len(graph) > 1

    # Verify graph has sub-components (sensors, connection points, etc.)
    # Check for s223:contains relationships
    contains_triples = list(graph.triples((auto_equipment_uri, S223.contains, None)))
    assert len(contains_triples) > 0, "Template should have s223:contains relationships"


@pytest.mark.asyncio
async def test_fill_approach_is_deterministic(shared_adapter):
    """Test that template.fill() produces deterministic class URIs across multiple runs.

    This verifies we consistently get TerminalUnit (main entity),
    not random sub-components like OutletConnectionPoint.
    """
    adapter: BuildingMOTIFAdapter = shared_adapter

    # Get vav-reheat template
    template = adapter.get_template_by_name(SystemTemplate.VAV_REHEAT)

    # Run fill() 20 times and verify class URI is consistent
    expected_type = None
    for i in range(20):
        bindings, graph = template.fill(BMS)
        auto_equipment_uri = bindings["name"]
        equipment_type = graph.value(auto_equipment_uri, RDF.type)

        if expected_type is None:
            expected_type = equipment_type
        else:
            assert equipment_type == expected_type, f"Iteration {i}: Got {equipment_type}, expected {expected_type}"

    # Verify the type is TerminalUnit
    assert expected_type == S223.TerminalUnit


@pytest.mark.asyncio
async def test_urn_substitution_preserves_structure(shared_adapter):
    """Test that substituting auto-generated URNs with custom URNs preserves graph structure.

    Simulates what mapping_mapper.py does: use fill() to generate graph,
    then substitute auto URN with custom URN.
    """
    adapter: BuildingMOTIFAdapter = shared_adapter

    # Get template and generate graph
    template = adapter.get_template_by_name(SystemTemplate.VAV_REHEAT)
    bindings, graph = template.fill(BMS)
    auto_equipment_uri = bindings["name"]

    # Custom URN (what we'll use in production)
    custom_equipment_uri = URIRef("urn:bms:Equipment:device-123-analog-input-1")

    # Substitute URN in all triples
    substituted_triples = []
    for s, p, o in graph:
        new_s = custom_equipment_uri if s == auto_equipment_uri else s
        new_o = custom_equipment_uri if o == auto_equipment_uri else o
        substituted_triples.append((new_s, p, new_o))

    # Verify custom URN has the same type
    custom_type = None
    for s, p, o in substituted_triples:
        if s == custom_equipment_uri and p == RDF.type:
            custom_type = o
            break

    assert custom_type == S223.TerminalUnit

    # Verify relationship count preserved
    original_contains_count = len(list(graph.triples((auto_equipment_uri, S223.contains, None))))
    substituted_contains_count = len([
        t for t in substituted_triples
        if t[0] == custom_equipment_uri and t[1] == S223.contains
    ])
    assert substituted_contains_count == original_contains_count


@pytest.mark.asyncio
async def test_fill_device_template_deterministic(shared_adapter):
    """Test that fill() works deterministically for device templates."""
    adapter: BuildingMOTIFAdapter = shared_adapter

    # Get damper template
    template = adapter.get_template_by_name(DeviceTemplate.DAMPER)

    # Run fill() 20 times and verify class URI is consistent
    expected_type = None
    for i in range(20):
        bindings, graph = template.fill(BMS)
        auto_device_uri = bindings["name"]
        device_type = graph.value(auto_device_uri, RDF.type)

        if expected_type is None:
            expected_type = device_type
        else:
            assert device_type == expected_type, f"Iteration {i}: Got {device_type}, expected {expected_type}"

    # Verify the type is Damper
    assert expected_type == S223.Damper


@pytest.mark.asyncio
async def test_fill_property_template_deterministic(shared_adapter):
    """Test that fill() works deterministically for property templates."""
    adapter: BuildingMOTIFAdapter = shared_adapter

    # Get damper-feedback template
    template = adapter.get_template_by_name(PropertyTemplate.DAMPER_FEEDBACK)

    # Run fill() 20 times and verify class URI is consistent
    expected_type = None
    for i in range(20):
        bindings, graph = template.fill(BMS)
        auto_property_uri = bindings["name"]
        property_type = graph.value(auto_property_uri, RDF.type)

        if expected_type is None:
            expected_type = property_type
        else:
            assert property_type == expected_type, f"Iteration {i}: Got {property_type}, expected {expected_type}"

    # Verify we get a valid S223 property type
    assert str(expected_type).startswith(str(S223))
