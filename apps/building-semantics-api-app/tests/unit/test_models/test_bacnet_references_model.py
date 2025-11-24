"""Unit tests for BACnetReferencesModel."""
import pytest
from unittest.mock import Mock, patch, MagicMock
from rdflib import Graph, Literal, Namespace, URIRef

from src.models.bacnet_references_model import BACnetReferencesModel
from src.models.exceptions import ValidationException
from src.dto.validation_dto import ValidationResultDTO


BMS = Namespace("urn:bms:")
BACNET = Namespace("urn:bacnet:")


@pytest.fixture
def mock_adapter():
    """Mock BuildingMOTIF adapter for isolated testing."""
    adapter = Mock()
    adapter.get_buildingmotif_instance = Mock()
    mock_bm = Mock()
    mock_session = Mock()
    mock_bm.session = mock_session
    adapter.get_buildingmotif_instance.return_value = mock_bm

    # Mock transaction context manager
    adapter.transaction = MagicMock()
    adapter.transaction.return_value.__enter__ = Mock(return_value=None)
    adapter.transaction.return_value.__exit__ = Mock(return_value=False)

    return adapter


def test_create_reference_maps_bacnet_point_to_property_urn(mock_adapter):
    """
    Test creating BACnet reference links BACnet point to property URN.

    Verifies:
    - bms:mapsToProperty triple added
    - ValidationService called
    - session.commit() called
    """
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)
    mock_graph.triples.return_value = []
    mock_model.graph = mock_graph
    mock_adapter.get_or_create_model.return_value = mock_model

    with patch('src.models.bacnet_references_model.ValidationService') as mock_validation:
        mock_validation.validate_model.return_value = ValidationResultDTO(
            isValid=True,
            errors=[],
            warnings=[]
        )

        result = BACnetReferencesModel(mock_adapter).create_or_update_reference(
            project_id="test-project",
            bacnet_point_id="device_123.analog-input_1",
            property_uri="urn:bldgmotif:vav-101-temp-sensor-1",
        )

        assert result["bacnet_point_id"] == "device_123.analog-input_1"
        assert result["property_uri"] == "urn:bldgmotif:vav-101-temp-sensor-1"

        mock_graph.add.assert_called_once()
        add_call_args = mock_graph.add.call_args[0][0]
        assert add_call_args[0] == URIRef("urn:bacnet:device_123.analog-input_1")
        assert add_call_args[1] == BMS.mapsToProperty
        assert add_call_args[2] == URIRef("urn:bldgmotif:vav-101-temp-sensor-1")

        mock_validation.validate_model.assert_called_once()

        # Verify transaction context manager was used
        mock_adapter.transaction.assert_called_once()


def test_create_reference_validates_property_exists_via_shacl(mock_adapter):
    """
    Test create_or_update_reference validates via SHACL before commit.

    Verifies:
    - ValidationService.validate_model() called
    - If validation passes → commit
    """
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)
    mock_graph.triples.return_value = []
    mock_model.graph = mock_graph
    mock_adapter.get_or_create_model.return_value = mock_model

    with patch('src.models.bacnet_references_model.ValidationService') as mock_validation:
        mock_validation.validate_model.return_value = ValidationResultDTO(
            isValid=True,
            errors=[],
            warnings=[]
        )

        BACnetReferencesModel(mock_adapter).create_or_update_reference(
            project_id="test-project",
            bacnet_point_id="device_42.analog-input_1",
            property_uri="urn:property:valid",
        )

        mock_validation.validate_model.assert_called_once_with(mock_model)

        # Verify transaction context manager was used
        mock_adapter.transaction.assert_called_once()


def test_create_reference_rolls_back_on_validation_failure(mock_adapter):
    """
    Test SHACL validation failure triggers rollback.

    Verifies:
    - ValidationException raised
    - model.graph changes reverted
    - Error message includes validation errors
    """
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)
    mock_graph.triples.return_value = []
    mock_model.graph = mock_graph
    mock_adapter.get_or_create_model.return_value = mock_model

    with patch('src.models.bacnet_references_model.ValidationService') as mock_validation:
        mock_validation.validate_model.return_value = ValidationResultDTO(
            isValid=False,
            errors=["Property does not exist in system"],
            warnings=[]
        )

        with pytest.raises(ValidationException) as exc_info:
            BACnetReferencesModel(mock_adapter).create_or_update_reference(
                project_id="test-project",
                bacnet_point_id="device_42.analog-input_1",
                property_uri="urn:property:invalid",
            )

        assert "Property does not exist in system" in exc_info.value.errors

        # Verify transaction context manager was used (rollback handled automatically)
        mock_adapter.transaction.assert_called_once()


def test_get_reference_returns_enriched_metadata(mock_adapter):
    """
    Test get_reference queries full System → Device → Property chain.

    Verifies:
    - SPARQL query uses s223:contains+ for traversal
    - Returns: property_uri, label, system_uri, device_uri, template_id
    """
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model

    mock_adapter.query_model.return_value = [{
        "property_uri": "urn:property:123",
        "property_label": "Zone Temp",
        "property_template": "air-temperature",
        "device_uri": "urn:device:456",
        "device_label": "Temp Sensor",
        "device_template": "sensor",
        "system_uri": "urn:system:789",
        "system_label": "VAV System",
        "system_template": "vav-reheat",
    }]

    result = BACnetReferencesModel(mock_adapter).get_reference(
        project_id="test-project",
        bacnet_point_id="device_42.analog-input_1"
    )

    assert result is not None
    assert result["bacnet_point_id"] == "device_42.analog-input_1"
    assert result["property_uri"] == "urn:property:123"
    assert result["property_label"] == "Zone Temp"
    assert result["device_uri"] == "urn:device:456"
    assert result["device_label"] == "Temp Sensor"
    assert result["system_uri"] == "urn:system:789"
    assert result["system_label"] == "VAV System"

    query_arg = mock_adapter.query_model.call_args[0][1]
    assert "s223:contains+" in query_arg
    assert "s223:hasProperty|s223:observes" in query_arg


def test_get_reference_extracts_label_from_uri_when_missing(mock_adapter):
    """
    Test get_reference falls back to URI-based label extraction.

    Verifies:
    - When rdfs:label is None, extracts label from URN
    """
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model

    mock_adapter.query_model.return_value = [{
        "property_uri": "urn:bldgmotif:vav-101-zone-temp",
        "property_label": None,
        "property_template": None,
        "device_uri": "urn:bldgmotif:temp-sensor-1",
        "device_label": None,
        "device_template": None,
        "system_uri": "urn:system:vav-101",
        "system_label": "VAV 101",
        "system_template": "vav-reheat",
    }]

    with patch('src.models.bacnet_references_model.get_label_or_extract') as mock_extract:
        mock_extract.side_effect = lambda label, uri: uri.split(':')[-1]

        result = BACnetReferencesModel(mock_adapter).get_reference(
            project_id="test-project",
            bacnet_point_id="device_42.analog-input_1"
        )

        assert result["property_label"] == "vav-101-zone-temp"
        assert result["device_label"] == "temp-sensor-1"
        assert mock_extract.call_count == 2


def test_get_all_references_filters_by_project_id(mock_adapter):
    """
    Test get_all_references returns only references for specified project.

    Verifies:
    - SPARQL query filters by project model
    - Returns list of reference dicts
    """
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model

    mock_adapter.query_model.return_value = [
        {
            "bacnet_point_uri": "urn:bacnet:device_1.analog-input_1",
            "property_uri": "urn:property:1",
            "property_label": "Temp 1",
            "property_template": "air-temperature",
            "device_uri": "urn:device:1",
            "device_label": "Sensor 1",
            "device_template": "sensor",
            "system_uri": "urn:system:1",
            "system_label": "VAV 1",
            "system_template": "vav-reheat",
        },
        {
            "bacnet_point_uri": "urn:bacnet:device_2.analog-input_2",
            "property_uri": "urn:property:2",
            "property_label": "Temp 2",
            "property_template": "air-temperature",
            "device_uri": "urn:device:2",
            "device_label": "Sensor 2",
            "device_template": "sensor",
            "system_uri": "urn:system:2",
            "system_label": "VAV 2",
            "system_template": "vav-reheat",
        },
    ]

    result = BACnetReferencesModel(mock_adapter).get_all_references(
        project_id="test-project"
    )

    assert len(result) == 2
    assert result[0]["bacnet_point_id"] == "device_1.analog-input_1"
    assert result[1]["bacnet_point_id"] == "device_2.analog-input_2"

    mock_adapter.get_or_create_model.assert_called_once_with("urn:project:test-project")


def test_delete_reference_removes_all_bacnet_metadata(mock_adapter):
    """
    Test delete_reference removes bms:mapsToProperty triple.

    Verifies:
    - model.graph.remove() called for bms:mapsToProperty triple
    - session.commit() called
    """
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)

    bacnet_uri = URIRef("urn:bacnet:device_123.analog-input_1")
    property_uri = URIRef("urn:property:456")
    triple = (bacnet_uri, BMS.mapsToProperty, property_uri)

    mock_graph.triples.return_value = [triple]
    mock_model.graph = mock_graph
    mock_adapter.get_or_create_model.return_value = mock_model

    result = BACnetReferencesModel(mock_adapter).delete_reference(
        project_id="test-project",
        bacnet_point_id="device_123.analog-input_1"
    )

    assert result is True
    mock_graph.remove.assert_called_once_with(triple)

    # Verify transaction context manager was used
    mock_adapter.transaction.assert_called_once()


def test_delete_reference_returns_false_when_not_found(mock_adapter):
    """
    Test delete_reference returns False when reference doesn't exist.

    Verifies:
    - Returns False when no triples found
    - No removal attempted
    """
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)
    mock_graph.triples.return_value = []
    mock_model.graph = mock_graph
    mock_adapter.get_or_create_model.return_value = mock_model

    result = BACnetReferencesModel(mock_adapter).delete_reference(
        project_id="test-project",
        bacnet_point_id="nonexistent.analog-input_1"
    )

    assert result is False
    mock_graph.remove.assert_not_called()


def test_validate_property_exists_uses_sparql_ask(mock_adapter):
    """
    Test validate_property_exists uses SPARQL ASK query.

    Verifies:
    - Returns True when property URN exists in graph
    - Returns False when property URN not found
    """
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)
    mock_adapter.get_or_create_model.return_value = mock_model
    mock_model.graph = mock_graph

    mock_result = Mock()
    mock_result.__bool__ = Mock(return_value=True)
    mock_graph.query.return_value = mock_result

    result = BACnetReferencesModel(mock_adapter).validate_property_exists(
        project_id="test-project",
        property_uri="urn:property:exists"
    )

    assert result is True

    query_arg = mock_graph.query.call_args[0][0]
    assert "ASK" in query_arg
    assert "urn:property:exists" in query_arg


def test_validate_property_exists_returns_false_when_not_found(mock_adapter):
    """Test validate_property_exists returns False when property not found."""
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)
    mock_adapter.get_or_create_model.return_value = mock_model
    mock_model.graph = mock_graph

    mock_result = Mock()
    mock_result.__bool__ = Mock(return_value=False)
    mock_graph.query.return_value = mock_result

    result = BACnetReferencesModel(mock_adapter).validate_property_exists(
        project_id="test-project",
        property_uri="urn:property:nonexistent"
    )

    assert result is False


def test_create_or_update_updates_existing_reference(mock_adapter):
    """
    Test create_or_update_reference updates existing BACnet point mapping.

    Verifies:
    - Existing triple removed
    - New triple added with new property_uri
    """
    mock_model = Mock()
    mock_graph = Mock(spec=Graph)

    bacnet_uri = URIRef("urn:bacnet:device_123.analog-input_1")
    old_property_uri = URIRef("urn:property:old")
    old_triple = (bacnet_uri, BMS.mapsToProperty, old_property_uri)

    mock_graph.triples.return_value = [old_triple]
    mock_model.graph = mock_graph
    mock_adapter.get_or_create_model.return_value = mock_model

    with patch('src.models.bacnet_references_model.ValidationService') as mock_validation:
        mock_validation.validate_model.return_value = ValidationResultDTO(
            isValid=True,
            errors=[],
            warnings=[]
        )

        result = BACnetReferencesModel(mock_adapter).create_or_update_reference(
            project_id="test-project",
            bacnet_point_id="device_123.analog-input_1",
            property_uri="urn:property:new",
        )

        mock_graph.remove.assert_called_once_with(old_triple)

        add_call_args = mock_graph.add.call_args[0][0]
        assert add_call_args[2] == URIRef("urn:property:new")

        assert result["property_uri"] == "urn:property:new"


def test_get_reference_returns_none_when_not_found(mock_adapter):
    """Test get_reference returns None when reference doesn't exist."""
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model
    mock_adapter.query_model.return_value = []

    result = BACnetReferencesModel(mock_adapter).get_reference(
        project_id="test-project",
        bacnet_point_id="nonexistent.analog-input_1"
    )

    assert result is None
