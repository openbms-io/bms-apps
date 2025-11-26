"""Integration tests for BACnetReferencesModel CRUD operations."""
import pytest
from rdflib import RDF

from src.adapters import BuildingMOTIFAdapter, SystemTemplate, DeviceTemplate, PropertyTemplate
from src.constants.namespaces import S223, BACNET, DCTERMS
from src.models.bacnet_references_model import BACnetReferencesModel
from src.models.systems_model import SystemsModel
from src.models.devices_model import DevicesModel
from src.models.exceptions import ValidationException


def _get_property_uri_from_system(
    shared_adapter: BuildingMOTIFAdapter,
    project_id: str,
    system_uri: str
) -> str:
    """Helper to get a property URI from a system using DevicesModel."""
    return _get_property_uris_from_system(shared_adapter, project_id, system_uri, limit=1)[0]


def _get_property_uris_from_system(
    shared_adapter: BuildingMOTIFAdapter,
    project_id: str,
    system_uri: str,
    limit: int = 1
) -> list[str]:
    """Helper to get multiple property URIs from a system using DevicesModel."""
    devices_model = DevicesModel(shared_adapter)

    devices = devices_model.get_devices_for_system(
        project_id=project_id,
        system_uri=system_uri
    )

    assert len(devices) > 0, "System should contain at least one device"

    property_uris = []
    for device in devices:
        properties = devices_model.get_properties_for_device(
            project_id=project_id,
            device_uri=device["device_uri"]
        )
        for prop in properties:
            property_uris.append(prop["property_uri"])
            if len(property_uris) >= limit:
                return property_uris

    assert len(property_uris) >= limit, f"System should contain at least {limit} properties"

    return property_uris[:limit]


def test_create_reference_persists_in_buildingmotif(shared_adapter: BuildingMOTIFAdapter):
    """
    Test created BACnet reference persists in BuildingMOTIF database.

    End-to-end flow:
    1. Create system with properties via SystemsModel
    2. Create BACnet reference via BACnetReferencesModel
    3. Query RDF graph directly via SPARQL
    4. Verify bms:mapsToProperty triple exists
    """
    systems_model = SystemsModel(shared_adapter)
    bacnet_model = BACnetReferencesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-bacnet-refs",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Test VAV for BACnet"
    )

    property_uri = _get_property_uri_from_system(
        shared_adapter,
        "integration-test-bacnet-refs",
        system_result["system_uri"]
    )

    reference_result = bacnet_model.create_or_update_reference(
        project_id="integration-test-bacnet-refs",
        bacnet_point_id="device_100.analog-input_1",
        property_uri=property_uri,
        device_identifier="device,100",
        object_identifier="analog-input,1",
        external_identifier="192.168.1.100:device,100:analog-input,1",
    )

    assert reference_result["bacnet_point_id"] == "device_100.analog-input_1"
    assert reference_result["property_uri"] == property_uri

    retrieved = bacnet_model.get_reference(
        project_id="integration-test-bacnet-refs",
        bacnet_point_id="device_100.analog-input_1"
    )

    assert retrieved is not None, "BACnet reference should exist"
    assert retrieved["property_uri"] == property_uri


def test_get_reference_returns_enriched_system_device_property_chain(shared_adapter: BuildingMOTIFAdapter):
    """
    Test get_reference returns full System → Device → Property chain.

    End-to-end flow:
    1. Create system with devices and properties
    2. Create BACnet reference
    3. Get reference via get_reference()
    4. Verify enriched metadata includes system, device, property URIs and labels
    """
    systems_model = SystemsModel(shared_adapter)
    bacnet_model = BACnetReferencesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-enriched-query",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV with Metadata"
    )

    property_uri = _get_property_uri_from_system(
        shared_adapter,
        "integration-test-enriched-query",
        system_result["system_uri"]
    )

    bacnet_model.create_or_update_reference(
        project_id="integration-test-enriched-query",
        bacnet_point_id="device_200.analog-input_5",
        property_uri=property_uri,
        device_identifier="device,200",
        object_identifier="analog-input,5",
        external_identifier="192.168.1.200:device,200:analog-input,5",
    )

    retrieved = bacnet_model.get_reference(
        project_id="integration-test-enriched-query",
        bacnet_point_id="device_200.analog-input_5"
    )

    assert retrieved is not None
    assert retrieved["bacnet_point_id"] == "device_200.analog-input_5"
    assert retrieved["property_uri"] == property_uri
    assert "property_label" in retrieved
    assert "device_uri" in retrieved
    assert "device_label" in retrieved
    assert "system_uri" in retrieved
    assert "system_label" in retrieved
    assert retrieved["system_uri"] == system_result["system_uri"]


def test_create_reference_rollback_on_validation_failure(shared_adapter: BuildingMOTIFAdapter):
    """
    Test failed validation rolls back graph changes.

    End-to-end flow:
    1. Create invalid reference (should fail validation)
    2. Query graph for bms:mapsToProperty triple
    3. Verify triple was NOT persisted (rollback successful)
    """
    bacnet_model = BACnetReferencesModel(shared_adapter)

    SystemsModel(shared_adapter).create_system(
        project_id="integration-test-rollback",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV for Rollback Test"
    )

    try:
        bacnet_model.create_or_update_reference(
            project_id="integration-test-rollback",
            bacnet_point_id="device_400.analog-input_1",
            property_uri="urn:invalid:property:rollback-test",
            device_identifier="device,400",
            object_identifier="analog-input,1",
            external_identifier="192.168.1.400:device,400:analog-input,1",
        )
    except ValidationException:
        pass

    retrieved = bacnet_model.get_reference(
        project_id="integration-test-rollback",
        bacnet_point_id="device_400.analog-input_1"
    )

    assert retrieved is None, "Invalid reference should NOT persist after rollback"


def test_get_all_references_returns_multiple_references(shared_adapter: BuildingMOTIFAdapter):
    """
    Test get_all_references returns all BACnet references in project.

    End-to-end flow:
    1. Create system with multiple properties
    2. Create 3 BACnet references
    3. Get all references via get_all_references()
    4. Verify all 3 references returned with metadata
    """
    systems_model = SystemsModel(shared_adapter)
    bacnet_model = BACnetReferencesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-list-refs",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV with Multiple References"
    )

    property_uris = _get_property_uris_from_system(
        shared_adapter,
        "integration-test-list-refs",
        system_result["system_uri"],
        limit=3
    )

    bacnet_model.create_or_update_reference(
        project_id="integration-test-list-refs",
        bacnet_point_id="device_500.analog-input_1",
        property_uri=property_uris[0],
        device_identifier="device,500",
        object_identifier="analog-input,1",
        external_identifier="192.168.1.500:device,500:analog-input,1",
    )

    bacnet_model.create_or_update_reference(
        project_id="integration-test-list-refs",
        bacnet_point_id="device_500.analog-input_2",
        property_uri=property_uris[1],
        device_identifier="device,500",
        object_identifier="analog-input,2",
        external_identifier="192.168.1.500:device,500:analog-input,2",
    )

    bacnet_model.create_or_update_reference(
        project_id="integration-test-list-refs",
        bacnet_point_id="device_500.analog-input_3",
        property_uri=property_uris[2],
        device_identifier="device,500",
        object_identifier="analog-input,3",
        external_identifier="192.168.1.500:device,500:analog-input,3",
    )

    all_references = bacnet_model.get_all_references(
        project_id="integration-test-list-refs"
    )

    assert len(all_references) >= 3
    bacnet_point_ids = [ref["bacnet_point_id"] for ref in all_references]
    assert "device_500.analog-input_1" in bacnet_point_ids
    assert "device_500.analog-input_2" in bacnet_point_ids
    assert "device_500.analog-input_3" in bacnet_point_ids

    for ref in all_references:
        assert "property_uri" in ref
        assert "property_label" in ref
        assert "system_uri" in ref


def test_update_existing_reference_replaces_property_uri(shared_adapter: BuildingMOTIFAdapter):
    """
    Test updating existing BACnet reference replaces property URI.

    End-to-end flow:
    1. Create BACnet reference with property A
    2. Update same BACnet point to property B
    3. Get reference
    4. Verify property B is mapped (not property A)
    """
    systems_model = SystemsModel(shared_adapter)
    bacnet_model = BACnetReferencesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-update-ref",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV for Update Test"
    )

    property_uris = _get_property_uris_from_system(
        shared_adapter,
        "integration-test-update-ref",
        system_result["system_uri"],
        limit=2
    )

    property_a = property_uris[0]
    property_b = property_uris[1]

    bacnet_model.create_or_update_reference(
        project_id="integration-test-update-ref",
        bacnet_point_id="device_600.analog-input_1",
        property_uri=property_a,
        device_identifier="device,600",
        object_identifier="analog-input,1",
        external_identifier="192.168.1.600:device,600:analog-input,1",
    )

    bacnet_model.create_or_update_reference(
        project_id="integration-test-update-ref",
        bacnet_point_id="device_600.analog-input_1",
        property_uri=property_b,
        device_identifier="device,600",
        object_identifier="analog-input,1",
        external_identifier="192.168.1.600:device,600:analog-input,1",
    )

    retrieved = bacnet_model.get_reference(
        project_id="integration-test-update-ref",
        bacnet_point_id="device_600.analog-input_1"
    )

    assert retrieved is not None
    assert retrieved["property_uri"] == property_b
    assert retrieved["property_uri"] != property_a, "Old property mapping should be removed"


def test_delete_reference_removes_from_buildingmotif(shared_adapter: BuildingMOTIFAdapter):
    """
    Test deleted BACnet reference no longer appears in queries.

    End-to-end flow:
    1. Create BACnet reference
    2. Delete via delete_reference()
    3. Query for reference → returns None
    4. Verify triple removed from graph
    """
    systems_model = SystemsModel(shared_adapter)
    bacnet_model = BACnetReferencesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-delete-ref",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV for Delete Test"
    )

    property_uri = _get_property_uri_from_system(
        shared_adapter,
        "integration-test-delete-ref",
        system_result["system_uri"]
    )

    bacnet_model.create_or_update_reference(
        project_id="integration-test-delete-ref",
        bacnet_point_id="device_700.analog-input_1",
        property_uri=property_uri,
        device_identifier="device,700",
        object_identifier="analog-input,1",
        external_identifier="192.168.1.700:device,700:analog-input,1",
    )

    retrieved = bacnet_model.get_reference(
        project_id="integration-test-delete-ref",
        bacnet_point_id="device_700.analog-input_1"
    )
    assert retrieved is not None

    deleted = bacnet_model.delete_reference(
        project_id="integration-test-delete-ref",
        bacnet_point_id="device_700.analog-input_1"
    )
    assert deleted is True

    retrieved_after = bacnet_model.get_reference(
        project_id="integration-test-delete-ref",
        bacnet_point_id="device_700.analog-input_1"
    )
    assert retrieved_after is None, "Reference triple should be removed from graph"


def test_validate_property_exists_returns_true_for_valid_property(shared_adapter: BuildingMOTIFAdapter):
    """
    Test validate_property_exists returns True for property in system.

    End-to-end flow:
    1. Create system with properties
    2. Call validate_property_exists() with valid property URI
    3. Verify returns True
    """
    systems_model = SystemsModel(shared_adapter)
    bacnet_model = BACnetReferencesModel(shared_adapter)

    system_result = systems_model.create_system(
        project_id="integration-test-validate-exists",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV for Validation Test"
    )

    property_uri = _get_property_uri_from_system(
        shared_adapter,
        "integration-test-validate-exists",
        system_result["system_uri"]
    )

    result = bacnet_model.validate_property_exists(
        project_id="integration-test-validate-exists",
        property_uri=property_uri
    )

    assert result is True


def test_validate_property_exists_returns_false_for_invalid_property(shared_adapter: BuildingMOTIFAdapter):
    """
    Test validate_property_exists returns False for non-existent property.

    End-to-end flow:
    1. Create system
    2. Call validate_property_exists() with invalid property URI
    3. Verify returns False
    """
    bacnet_model = BACnetReferencesModel(shared_adapter)

    SystemsModel(shared_adapter).create_system(
        project_id="integration-test-validate-not-exists",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV for Negative Validation Test"
    )

    result = bacnet_model.validate_property_exists(
        project_id="integration-test-validate-not-exists",
        property_uri="urn:invalid:property:does-not-exist"
    )

    assert result is False


def test_create_reference_creates_223p_compliant_bacnet_external_reference(shared_adapter: BuildingMOTIFAdapter):
    """
    Test that creating a BACnet reference creates a 223P-compliant s223:BACnetExternalReference.

    End-to-end flow:
    1. Create system with properties
    2. Create BACnet reference with device/object identifiers
    3. Query RDF graph directly for BACnetExternalReference entity
    4. Verify all required triples exist:
       - s223:BACnetExternalReference type
       - bacnet:device-identifier
       - bacnet:object-identifier
       - dcterms:identifier
       - s223:hasExternalReference link from property
    """
    systems_model = SystemsModel(shared_adapter)
    bacnet_model = BACnetReferencesModel(shared_adapter)

    # Create system with properties
    system_result = systems_model.create_system(
        project_id="integration-test-223p-structure",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV for 223P Test"
    )

    property_uri = _get_property_uri_from_system(
        shared_adapter,
        "integration-test-223p-structure",
        system_result["system_uri"]
    )

    # Create BACnet reference with metadata
    bacnet_model.create_or_update_reference(
        project_id="integration-test-223p-structure",
        bacnet_point_id="device_800.analog-input_1",
        property_uri=property_uri,
        device_identifier="device,800",
        object_identifier="analog-input,1",
        external_identifier="192.168.1.800:device,800:analog-input,1",
    )

    # Query RDF graph directly for verification
    model = shared_adapter.get_or_create_model("urn:project:integration-test-223p-structure")
    from rdflib import URIRef

    property_uri_ref = URIRef(property_uri)

    # Find the BACnetExternalReference linked to this property
    external_refs = list(model.graph.objects(property_uri_ref, S223.hasExternalReference))
    assert len(external_refs) == 1, "Property should have exactly one external reference"

    bacnet_ref_uri = external_refs[0]

    # Verify: BACnetExternalReference type
    ref_type = model.graph.value(bacnet_ref_uri, RDF.type)
    assert ref_type == S223.BACnetExternalReference, f"Expected s223:BACnetExternalReference, got {ref_type}"

    # Verify: bacnet:device-identifier
    device_id = model.graph.value(bacnet_ref_uri, BACNET["device-identifier"])
    assert device_id is not None, "device-identifier should be present"
    assert str(device_id) == "device,800", f"Expected 'device,800', got {device_id}"

    # Verify: bacnet:object-identifier
    object_id = model.graph.value(bacnet_ref_uri, BACNET["object-identifier"])
    assert object_id is not None, "object-identifier should be present"
    assert str(object_id) == "analog-input,1", f"Expected 'analog-input,1', got {object_id}"

    # Verify: dcterms:identifier (external identifier with IP)
    external_id = model.graph.value(bacnet_ref_uri, DCTERMS.identifier)
    assert external_id is not None, "external identifier should be present"
    assert str(external_id) == "192.168.1.800:device,800:analog-input,1", f"Expected full external identifier, got {external_id}"

    # Verify: Property links to external reference
    has_link = (property_uri_ref, S223.hasExternalReference, bacnet_ref_uri) in model.graph
    assert has_link, "Property should link to BACnetExternalReference via s223:hasExternalReference"
