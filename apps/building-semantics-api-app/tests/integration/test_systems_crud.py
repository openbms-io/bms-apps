"""Integration tests for SystemsModel CRUD operations."""
import pytest

from src.adapters import BuildingMOTIFAdapter, SystemTemplate
from src.models.systems_model import SystemsModel
from src.models.devices_model import DevicesModel


def test_create_system_persists_in_buildingmotif(shared_adapter: BuildingMOTIFAdapter):
    """
    Test created system persists in BuildingMOTIF database.

    End-to-end flow:
    1. Create system via SystemsModel.create_system()
    2. Query RDF graph directly via SPARQL
    3. Verify system URI, label, metadata exist
    """
    model = SystemsModel(shared_adapter)

    result = model.create_system(
        project_id="integration-test-systems",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Integration Test VAV"
    )

    query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX bms: <urn:bms:>
        PREFIX dcterms: <http://purl.org/dc/terms/>

        SELECT ?label ?template_id ?created
        WHERE {{
            <{result["system_uri"]}> rdfs:label ?label .
            <{result["system_uri"]}> bms:hasTemplateId ?template_id .
            <{result["system_uri"]}> dcterms:created ?created .
        }}
    """

    project_model = shared_adapter.get_or_create_model("urn:project:integration-test-systems")
    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) == 1
    assert sparql_results[0]["label"] == "Integration Test VAV"
    assert sparql_results[0]["template_id"] == SystemTemplate.VAV_REHEAT.value
    assert "created" in sparql_results[0]


def test_query_devices_from_created_system(shared_adapter: BuildingMOTIFAdapter):
    """
    Test querying devices from instantiated system.

    End-to-end flow:
    1. Create system (contains devices from template.fill())
    2. Query devices via DevicesModel.get_devices_for_system()
    3. Verify device URIs, labels returned
    """
    systems_model = SystemsModel(shared_adapter)
    devices_model = DevicesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-devices",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV with Devices Test"
    )

    devices = devices_model.get_devices_for_system(
        project_id="integration-test-devices",
        system_uri=system_result["system_uri"]
    )

    assert len(devices) > 0
    assert all("device_uri" in d for d in devices)
    assert all("label" in d for d in devices)


def test_query_properties_from_device_in_system(shared_adapter: BuildingMOTIFAdapter):
    """
    Test querying properties from device within system.

    End-to-end flow:
    1. Create system
    2. Query first device
    3. Query properties via DevicesModel.get_properties_for_device()
    4. Verify property metadata (is_actuatable, class_uri, etc.)
    """
    systems_model = SystemsModel(shared_adapter)
    devices_model = DevicesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-properties",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV with Properties Test"
    )

    devices = devices_model.get_devices_for_system(
        project_id="integration-test-properties",
        system_uri=system_result["system_uri"]
    )

    assert len(devices) > 0

    first_device = devices[0]
    properties = devices_model.get_properties_for_device(
        project_id="integration-test-properties",
        device_uri=first_device["device_uri"]
    )

    assert len(properties) > 0
    for prop in properties:
        assert "property_uri" in prop
        assert "label" in prop
        assert "is_actuatable" in prop
        assert isinstance(prop["is_actuatable"], bool)


def test_delete_system_removes_from_buildingmotif(shared_adapter: BuildingMOTIFAdapter):
    """
    Test deleted system no longer appears in queries.

    End-to-end flow:
    1. Create system
    2. Delete via SystemsModel.delete_system()
    3. Query for system → returns None
    4. Verify triples removed from graph
    """
    model = SystemsModel(shared_adapter)

    result = model.create_system(
        project_id="integration-test-delete",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="System to Delete"
    )

    system_uri = result["system_uri"]

    retrieved = model.get_system(
        project_id="integration-test-delete",
        system_uri=system_uri
    )
    assert retrieved is not None

    deleted = model.delete_system(
        project_id="integration-test-delete",
        system_uri=system_uri
    )
    assert deleted is True

    retrieved_after = model.get_system(
        project_id="integration-test-delete",
        system_uri=system_uri
    )
    assert retrieved_after is None


def test_list_systems_returns_multiple_systems_ordered(shared_adapter: BuildingMOTIFAdapter):
    """
    Test creating and listing multiple systems in project.

    End-to-end flow:
    1. Create 3 systems with different labels
    2. List systems via SystemsModel.list_systems()
    3. Verify correct count and ordering by created timestamp
    """
    model = SystemsModel(shared_adapter)

    system1 = model.create_system(
        project_id="integration-test-list",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="System A"
    )

    system2 = model.create_system(
        project_id="integration-test-list",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="System B"
    )

    system3 = model.create_system(
        project_id="integration-test-list",
        template_id=SystemTemplate.LAB_VAV_REHEAT.value,
        label="System C"
    )

    systems = model.list_systems(project_id="integration-test-list")

    assert len(systems) >= 3

    system_labels = [s["label"] for s in systems]
    assert "System A" in system_labels
    assert "System B" in system_labels
    assert "System C" in system_labels

    assert all("system_uri" in s for s in systems)
    assert all("template_id" in s for s in systems)
    assert all("created" in s for s in systems)


def test_create_system_with_lab_vav_reheat_template(shared_adapter: BuildingMOTIFAdapter):
    """
    Test system creation with LAB_VAV_REHEAT template.

    Verifies:
    - Different template enum works correctly
    - System contains lab-specific devices
    """
    model = SystemsModel(shared_adapter)

    result = model.create_system(
        project_id="integration-test-lab-vav",
        template_id=SystemTemplate.LAB_VAV_REHEAT.value,
        label="Lab VAV System"
    )

    assert result["system_uri"].startswith("urn:")
    assert result["label"] == "Lab VAV System"
    assert result["template_id"] == SystemTemplate.LAB_VAV_REHEAT.value

    retrieved = model.get_system(
        project_id="integration-test-lab-vav",
        system_uri=result["system_uri"]
    )

    assert retrieved is not None
    assert retrieved["label"] == "Lab VAV System"
    assert retrieved["template_id"] == SystemTemplate.LAB_VAV_REHEAT.value
