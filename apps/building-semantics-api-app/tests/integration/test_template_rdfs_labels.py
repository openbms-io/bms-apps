"""Integration tests to verify rdfs:label exists in ASHRAE 223P templates.

This test validates that templates have semantic labels embedded in RDF bodies,
eliminating the need for runtime URI-based label extraction.

Issue #65: Add rdfs:label to ASHRAE 223P templates
"""
import pytest

from src.adapters import BuildingMOTIFAdapter, SystemTemplate
from src.models.systems_model import SystemsModel
from src.models.devices_model import DevicesModel
from src.utils.label_utils import get_label_or_extract


def test_damper_device_has_rdfs_label(shared_adapter: BuildingMOTIFAdapter):
    """
    Test damper device template has rdfs:label in RDF body.

    When a damper is instantiated, it should have rdfs:label set,
    so SPARQL queries return the label directly (not null).
    """
    systems_model = SystemsModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="test-rdfs-labels-damper",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Test VAV for Damper"
    )

    project_model = shared_adapter.get_or_create_model("urn:project:test-rdfs-labels-damper")

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX s223: <http://data.ashrae.org/standard223#>

        SELECT ?device ?label
        WHERE {{
            <{system_result["system_uri"]}> s223:contains* ?device .
            ?device a s223:Damper .
            ?device rdfs:label ?label .
        }}
    """

    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) > 0, (
        "Expected damper to have rdfs:label in template. "
        "SPARQL returned no results, meaning label is missing from RDF body."
    )
    assert sparql_results[0]["label"] is not None
    assert len(sparql_results[0]["label"]) > 0


def test_vlv_dmp_device_has_rdfs_label(shared_adapter: BuildingMOTIFAdapter):
    """
    Test valve-damper (vlv-dmp) device template has rdfs:label.

    Used in lab-vav-reheat template.
    """
    systems_model = SystemsModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="test-rdfs-labels-vlvdmp",
        template_id=SystemTemplate.LAB_VAV_REHEAT.value,
        label="Test Lab VAV for Vlv-Dmp"
    )

    project_model = shared_adapter.get_or_create_model("urn:project:test-rdfs-labels-vlvdmp")

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX s223: <http://data.ashrae.org/standard223#>

        SELECT ?device ?label
        WHERE {{
            <{system_result["system_uri"]}> s223:contains* ?device .
            ?device a s223:Valve .
            ?device rdfs:label ?label .
        }}
    """

    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) > 0, (
        "Expected valve-damper to have rdfs:label in template. "
        "SPARQL returned no results, meaning label is missing from RDF body."
    )


def test_hot_water_coil_has_rdfs_label(shared_adapter: BuildingMOTIFAdapter):
    """
    Test hot-water-coil device template has rdfs:label.

    Used in both vav-reheat and lab-vav-reheat templates.
    """
    systems_model = SystemsModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="test-rdfs-labels-hwc",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Test VAV for Hot Water Coil"
    )

    project_model = shared_adapter.get_or_create_model("urn:project:test-rdfs-labels-hwc")

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX s223: <http://data.ashrae.org/standard223#>

        SELECT ?device ?label
        WHERE {{
            <{system_result["system_uri"]}> s223:contains* ?device .
            ?device a s223:HeatingCoil .
            ?device rdfs:label ?label .
        }}
    """

    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) > 0, (
        "Expected hot-water-coil to have rdfs:label in template. "
        "SPARQL returned no results, meaning label is missing from RDF body."
    )


def test_sensor_gets_label_from_uri_fallback(shared_adapter: BuildingMOTIFAdapter):
    """
    Test sensor device gets user-friendly label via URI fallback.

    Sensors use the generic sensor template (no static rdfs:label) and get
    descriptive labels extracted from their URI name (e.g., supply-air-temperature-sensor).
    """
    systems_model = SystemsModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="test-rdfs-labels-sensor",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Test VAV for Sensor"
    )

    project_model = shared_adapter.get_or_create_model("urn:project:test-rdfs-labels-sensor")

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX s223: <http://data.ashrae.org/standard223#>

        SELECT ?device
        WHERE {{
            <{system_result["system_uri"]}> s223:contains* ?device .
            ?device a s223:Sensor .
        }}
    """

    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) > 0, "Expected sensors to exist in system"

    for result in sparql_results:
        sensor_uri = result["device"]
        label = get_label_or_extract(None, sensor_uri)
        assert label is not None
        assert len(label) > 0
        assert "supply" in label.lower() or "sensor" in label.lower(), (
            f"Expected sensor URI to produce meaningful label, got: {label}"
        )


def test_property_has_rdfs_label(shared_adapter: BuildingMOTIFAdapter):
    """
    Test property templates have rdfs:label.

    Properties like damper-command, damper-feedback, static-pressure, etc.
    should have semantic labels in their RDF bodies.
    """
    systems_model = SystemsModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="test-rdfs-labels-property",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Test VAV for Property Labels"
    )

    project_model = shared_adapter.get_or_create_model("urn:project:test-rdfs-labels-property")

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX s223: <http://data.ashrae.org/standard223#>

        SELECT ?property ?label
        WHERE {{
            <{system_result["system_uri"]}> s223:contains* ?device .
            ?device s223:hasProperty ?property .
            ?property rdfs:label ?label .
        }}
    """

    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) > 0, (
        "Expected properties to have rdfs:label in template. "
        "SPARQL returned no results, meaning label is missing from RDF body."
    )


def test_non_sensor_devices_have_rdfs_label(shared_adapter: BuildingMOTIFAdapter):
    """
    Test that non-sensor devices return labels from RDF.

    Devices like dampers, coils, valves should have rdfs:label in their template.
    Sensors are excluded as they use URI fallback for user-friendly labels.
    """
    systems_model = SystemsModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="test-rdfs-labels-all",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Test VAV Complete"
    )

    project_model = shared_adapter.get_or_create_model("urn:project:test-rdfs-labels-all")

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX s223: <http://data.ashrae.org/standard223#>

        SELECT ?device ?label
        WHERE {{
            <{system_result["system_uri"]}> s223:contains* ?device .
            FILTER (str(?device) != "{system_result["system_uri"]}")
            FILTER NOT EXISTS {{ ?device a s223:Sensor }}
            OPTIONAL {{ ?device rdfs:label ?label . }}
        }}
    """

    sparql_results = shared_adapter.query_model(project_model, query)

    devices_without_labels = [
        r["device"] for r in sparql_results
        if r.get("label") is None
    ]

    assert len(devices_without_labels) == 0, (
        f"Found {len(devices_without_labels)} non-sensor devices without rdfs:label: "
        f"{devices_without_labels[:5]}..."
    )


def test_fallback_label_extraction_still_works(shared_adapter: BuildingMOTIFAdapter):
    """
    Test that get_label_or_extract works for sensors and edge cases.

    Sensors use URI fallback to get descriptive labels from their
    user-friendly names (e.g., supply-air-temperature-sensor).
    """
    result = get_label_or_extract(None, "urn:bms:supply-air-temperature-sensor_db8e67fc")
    assert result == "Supply Air Temperature Sensor"

    result = get_label_or_extract(None, "urn:bms:supply-air-flow-sensor_db8e67fc")
    assert result == "Supply Air Flow Sensor"

    result = get_label_or_extract(None, "urn:bms:supply-air-pressure-sensor_db8e67fc")
    assert result == "Supply Air Pressure Sensor"

    result_with_label = get_label_or_extract("Custom Label", "urn:bms:ignored-uri")
    assert result_with_label == "Custom Label"


def test_water_temperature_properties_have_distinct_labels(shared_adapter: BuildingMOTIFAdapter):
    """
    Test that water temperature properties in hot-water-coil have distinct labels.

    The hot-water-coil has two water temperature properties:
    - supply-water-temperature
    - return-water-temperature

    These should display as distinct labels, not both as "Water Temperature".
    """
    systems_model = SystemsModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="test-water-temp-labels",
        template_id=SystemTemplate.LAB_VAV_REHEAT.value,
        label="Test Lab VAV for Water Temp"
    )

    project_model = shared_adapter.get_or_create_model("urn:project:test-water-temp-labels")

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX s223: <http://data.ashrae.org/standard223#>

        SELECT ?property ?label
        WHERE {{
            <{system_result["system_uri"]}> s223:contains* ?device .
            ?device a s223:HeatingCoil .
            ?device s223:hasProperty ?property .
            OPTIONAL {{ ?property rdfs:label ?label . }}
        }}
    """

    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) >= 2, (
        f"Expected at least 2 properties on HeatingCoil, got {len(sparql_results)}"
    )

    labels = []
    for result in sparql_results:
        prop_uri = result["property"]
        rdfs_label = result.get("label")
        final_label = get_label_or_extract(rdfs_label, prop_uri)
        labels.append(final_label)

    supply_label = next((l for l in labels if "Supply Water Temperature" in l), None)
    return_label = next((l for l in labels if "Return Water Temperature" in l), None)

    assert supply_label is not None, (
        f"Expected a label containing 'Supply Water Temperature', got: {labels}"
    )
    assert return_label is not None, (
        f"Expected a label containing 'Return Water Temperature', got: {labels}"
    )
    assert supply_label != return_label, (
        f"Expected distinct labels, but supply and return labels are the same: {supply_label}"
    )
    assert len(set(labels)) == len(labels), (
        f"Expected distinct labels for water temperature properties, but got duplicates: {labels}"
    )
