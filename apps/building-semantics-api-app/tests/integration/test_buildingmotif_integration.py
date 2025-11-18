"""Integration tests with real BuildingMOTIF SDK."""
import tempfile
from pathlib import Path

import pytest
from rdflib import Graph, Literal, Namespace, RDF, RDFS

from src.adapters import BuildingMOTIFAdapter, DeviceTemplate, SystemTemplate


def test_database_file_created_at_correct_path(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test database file is created at specified path."""
    assert shared_adapter.get_buildingmotif_instance().db_uri.startswith("sqlite:///")


def test_real_nrel_template_library_loaded(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test NREL template library loads successfully."""
    library = shared_adapter.get_nrel_library()
    assert library is not None


def test_real_template_loading(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test template loading from NREL library."""
    template = shared_adapter.get_template_by_name(DeviceTemplate.DAMPER)
    assert template is not None
    assert template.name == "damper"


def test_real_template_not_found(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test template loading handles missing templates."""
    from buildingmotif.database.errors import TemplateNotFound

    with pytest.raises(TemplateNotFound):
        shared_adapter.get_nrel_library().get_template_by_name("non-existent-template")


def test_real_list_templates(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test listing templates from NREL library."""
    templates = shared_adapter.list_templates()
    assert isinstance(templates, list)
    assert len(templates) > 0
    assert "damper" in templates
    assert "fan" in templates


def test_real_model_creation(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test creating RDF model with real SDK."""
    model = shared_adapter.create_model("urn:test:model-creation/")
    assert model is not None


def test_model_persists_in_database(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test that created models persist in database."""
    model1 = shared_adapter.create_model("urn:test:persist1/")
    model2 = shared_adapter.create_model("urn:test:persist2/")

    assert model1 is not None
    assert model2 is not None


def test_database_persistence_across_adapter_instances(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test data persists across adapter recreations."""
    shared_adapter.create_model("urn:test:persisted-building/")

    library = shared_adapter.get_nrel_library()

    assert library is not None


def test_create_bacnet_point_with_semantic_relationship(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test creating BACnet point with ASHRAE 223P semantic relationships."""

    model = shared_adapter.create_model("urn:building:bacnet-single/")

    s223 = Namespace("http://data.ashrae.org/standard223#")
    building = Namespace("urn:building:test/")

    graph = Graph()
    graph.bind("s223", s223)
    graph.bind("building", building)

    point_uri = building["VAV-101-ZoneTemp"]
    graph.add((point_uri, RDF.type, s223.QuantifiableProperty))
    graph.add((point_uri, RDFS.label, Literal("Zone Temperature Sensor")))
    graph.add((point_uri, s223.hasValue, Literal(72.5)))

    shared_adapter.add_graph(model, graph)

    query = """
        PREFIX s223: <http://data.ashrae.org/standard223#>
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        SELECT ?point ?label ?value
        WHERE {
            ?point a s223:QuantifiableProperty .
            ?point rdfs:label ?label .
            ?point s223:hasValue ?value .
        }
    """
    results = shared_adapter.query_model(model, query)

    assert len(results) == 1
    assert "Zone Temperature Sensor" in results[0]["label"]
    assert "72.5" in results[0]["value"]


def test_create_multiple_bacnet_points_with_relationships(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test creating multiple BACnet points with hierarchical relationships."""

    model = shared_adapter.create_model("urn:building:bacnet-multiple/")

    s223 = Namespace("http://data.ashrae.org/standard223#")
    building = Namespace("urn:building:vav-system/")
    unit = Namespace("http://qudt.org/vocab/unit/")

    graph = Graph()
    graph.bind("s223", s223)
    graph.bind("building", building)
    graph.bind("unit", unit)

    vav_equipment = building["VAV-101"]
    graph.add((vav_equipment, RDF.type, s223.Equipment))
    graph.add((vav_equipment, RDFS.label, Literal("VAV Box 101")))

    zone_temp = building["VAV-101-ZoneTemp"]
    graph.add((zone_temp, RDF.type, s223.QuantifiableProperty))
    graph.add((zone_temp, RDFS.label, Literal("Zone Temperature")))
    graph.add((zone_temp, s223.hasValue, Literal(72.5)))
    graph.add((zone_temp, s223.hasUnit, unit.DEG_F))
    graph.add((vav_equipment, s223.hasProperty, zone_temp))

    zone_humidity = building["VAV-101-ZoneHumidity"]
    graph.add((zone_humidity, RDF.type, s223.QuantifiableProperty))
    graph.add((zone_humidity, RDFS.label, Literal("Zone Humidity")))
    graph.add((zone_humidity, s223.hasValue, Literal(45.0)))
    graph.add((zone_humidity, s223.hasUnit, unit.PERCENT))
    graph.add((vav_equipment, s223.hasProperty, zone_humidity))

    damper_position = building["VAV-101-DamperPosition"]
    graph.add((damper_position, RDF.type, s223.QuantifiableProperty))
    graph.add((damper_position, RDFS.label, Literal("Damper Position")))
    graph.add((damper_position, s223.hasValue, Literal(60.0)))
    graph.add((damper_position, s223.hasUnit, unit.PERCENT))
    graph.add((vav_equipment, s223.hasProperty, damper_position))

    heating_valve = building["VAV-101-HeatingValve"]
    graph.add((heating_valve, RDF.type, s223.QuantifiableProperty))
    graph.add((heating_valve, RDFS.label, Literal("Heating Valve Command")))
    graph.add((heating_valve, s223.hasValue, Literal(25.0)))
    graph.add((heating_valve, s223.hasUnit, unit.PERCENT))
    graph.add((vav_equipment, s223.hasProperty, heating_valve))

    shared_adapter.add_graph(model, graph)

    query = """
        PREFIX s223: <http://data.ashrae.org/standard223#>
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        SELECT ?equipment ?equipLabel ?point ?pointLabel ?value
        WHERE {
            ?equipment a s223:Equipment .
            ?equipment rdfs:label ?equipLabel .
            ?equipment s223:hasProperty ?point .
            ?point rdfs:label ?pointLabel .
            ?point s223:hasValue ?value .
        }
        ORDER BY ?pointLabel
    """
    results = shared_adapter.query_model(model, query)

    assert len(results) == 4
    assert all("VAV Box 101" in r["equipLabel"] for r in results)

    point_labels = [r["pointLabel"] for r in results]
    assert "Damper Position" in point_labels
    assert "Heating Valve Command" in point_labels
    assert "Zone Humidity" in point_labels
    assert "Zone Temperature" in point_labels


def test_template_instantiation_with_bacnet_points(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test creating ASHRAE 223P equipment with BACnet points using semantic model."""
    from rdflib import Graph, Literal, Namespace, RDF, RDFS

    model = shared_adapter.create_model("urn:building:template-test/")

    damper_template = shared_adapter.get_template_by_name(DeviceTemplate.DAMPER)
    assert damper_template is not None

    s223 = Namespace("http://data.ashrae.org/standard223#")
    building = Namespace("urn:building:ahu1/")
    unit = Namespace("http://qudt.org/vocab/unit/")

    graph = Graph()
    graph.bind("s223", s223)
    graph.bind("building", building)
    graph.bind("unit", unit)

    damper_uri = building["OA-Damper-1"]
    graph.add((damper_uri, RDF.type, s223.Damper))
    graph.add((damper_uri, RDFS.label, Literal("Outside Air Damper")))

    damper_position = building["OA-Damper-1-Position"]
    graph.add((damper_position, RDF.type, s223.QuantifiableProperty))
    graph.add((damper_position, RDFS.label, Literal("Outside Air Damper Position")))
    graph.add((damper_position, s223.hasValue, Literal(75.0)))
    graph.add((damper_position, s223.hasUnit, unit.PERCENT))
    graph.add((damper_uri, s223.hasProperty, damper_position))

    damper_command = building["OA-Damper-1-Command"]
    graph.add((damper_command, RDF.type, s223.QuantifiableProperty))
    graph.add((damper_command, RDFS.label, Literal("Outside Air Damper Command")))
    graph.add((damper_command, s223.hasValue, Literal(80.0)))
    graph.add((damper_command, s223.hasUnit, unit.PERCENT))
    graph.add((damper_uri, s223.hasProperty, damper_command))

    shared_adapter.add_graph(model, graph)

    query = """
        PREFIX s223: <http://data.ashrae.org/standard223#>
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        SELECT ?damper ?damperLabel ?point ?pointLabel ?value
        WHERE {
            ?damper a s223:Damper .
            OPTIONAL { ?damper rdfs:label ?damperLabel . }
            ?damper s223:hasProperty ?point .
            ?point rdfs:label ?pointLabel .
            ?point s223:hasValue ?value .
        }
        ORDER BY ?pointLabel
    """
    results = shared_adapter.query_model(model, query)

    assert len(results) == 2
    assert all("Outside Air Damper" in r.get("damperLabel", "") for r in results)

    point_labels = [r["pointLabel"] for r in results]
    assert "Outside Air Damper Command" in point_labels
    assert "Outside Air Damper Position" in point_labels


def test_get_template_with_dependencies_real(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test getting template with inlined dependencies using real SDK."""
    template = shared_adapter.get_template_with_dependencies(DeviceTemplate.DAMPER)

    assert template is not None
    assert template.name == "damper"
    assert len(template.body) > 0


def test_get_template_dependencies_damper(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test extracting dependencies from damper template."""
    dependencies = shared_adapter.get_template_dependencies(DeviceTemplate.DAMPER)

    assert isinstance(dependencies, list)
    assert "damper" in dependencies
    assert "damper-command" in dependencies or "damper-feedback" in dependencies


def test_get_template_dependencies_fan(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test extracting dependencies from fan template."""
    dependencies = shared_adapter.get_template_dependencies(DeviceTemplate.FAN)

    assert isinstance(dependencies, list)
    assert "fan" in dependencies
    assert len(dependencies) > 0


def test_get_template_dependencies_vav_reheat(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test extracting dependencies from complex system template."""
    dependencies = shared_adapter.get_template_dependencies(SystemTemplate.VAV_REHEAT)

    assert isinstance(dependencies, list)
    assert "vav-reheat" in dependencies
    assert len(dependencies) > 1


def test_template_metadata_complete(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test comprehensive metadata extraction."""
    metadata = shared_adapter.get_template_metadata(DeviceTemplate.DAMPER)

    assert metadata["name"] == "damper"
    assert isinstance(metadata["dependencies"], list)
    assert len(metadata["dependencies"]) > 0
    assert "triple_count" in metadata
    assert metadata["triple_count"] > 0


def test_relationship_extraction_consistency(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test relationship extraction is consistent across calls."""
    deps1 = shared_adapter.get_template_dependencies(DeviceTemplate.FAN)
    deps2 = shared_adapter.get_template_dependencies(DeviceTemplate.FAN)

    assert deps1 == deps2


def test_all_device_templates_have_dependencies(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test that device templates have at least themselves in dependencies."""
    test_templates = [
        DeviceTemplate.DAMPER,
        DeviceTemplate.FAN,
        DeviceTemplate.FILTER,
    ]

    for template in test_templates:
        dependencies = shared_adapter.get_template_dependencies(template)
        assert isinstance(dependencies, list)
        assert len(dependencies) > 0
        assert str(template.value) in dependencies
