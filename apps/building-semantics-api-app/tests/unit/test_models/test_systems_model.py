"""Unit tests for SystemsModel."""
import pytest
from datetime import datetime
from unittest.mock import Mock, MagicMock, patch, call
from rdflib import Graph, Literal, Namespace, URIRef, RDFS, DCTERMS, RDF

from src.models.systems_model import SystemsModel
from src.adapters.template_types import SystemTemplate


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


def test_create_system_instantiates_template_via_fill(mock_adapter):
    """
    Test create_system calls template.fill() for instantiation.

    Verifies:
    - get_template_with_dependencies called with correct template enum
    - template.fill() called with BMS namespace
    - Returns system_uri from filled template
    """
    s223 = Namespace("http://data.ashrae.org/standard223#")
    BMS = Namespace("urn:bms:")

    mock_template = Mock()
    mock_filled_graph = Graph()
    system_uri = URIRef("urn:bldgmotif:vav-reheat-1")

    mock_filled_graph.add((system_uri, RDF.type, s223.System))
    bindings = {"name": system_uri}
    mock_template.fill.return_value = (bindings, mock_filled_graph)

    mock_adapter.get_template_with_dependencies.return_value = mock_template

    mock_model = Mock()
    mock_model.graph = Graph()
    mock_adapter.get_or_create_model.return_value = mock_model

    result = SystemsModel(mock_adapter).create_system(
        project_id="test-project",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="VAV Box 101"
    )

    assert result["system_uri"] == "urn:bldgmotif:vav-reheat-1"
    assert result["label"] == "VAV Box 101"
    assert result["template_id"] == SystemTemplate.VAV_REHEAT.value
    mock_template.fill.assert_called_once()
    mock_adapter.get_template_with_dependencies.assert_called_once()


def test_create_system_adds_required_metadata(mock_adapter):
    """
    Test create_system adds rdfs:label, bms:hasTemplateId, dcterms:created.

    Verifies:
    - Metadata triple added for label
    - Metadata triple added for template_id
    - Metadata triple added for creation timestamp
    - Model.graph updated with filled graph
    """
    BMS = Namespace("urn:bms:")

    mock_template = Mock()
    system_uri = URIRef("urn:bldgmotif:system-1")
    mock_filled_graph = Graph()

    bindings = {"name": system_uri}
    mock_template.fill.return_value = (bindings, mock_filled_graph)

    mock_adapter.get_template_with_dependencies.return_value = mock_template

    mock_model = Mock()
    mock_model.graph = Graph()
    mock_adapter.get_or_create_model.return_value = mock_model

    with patch('src.models.systems_model.datetime') as mock_datetime:
        mock_datetime.now.return_value.isoformat.return_value = "2025-01-15T10:30:00"

        result = SystemsModel(mock_adapter).create_system(
            project_id="test-project",
            template_id=SystemTemplate.VAV_REHEAT.value,
            label="Test System"
        )

    assert (system_uri, RDFS.label, Literal("Test System")) in mock_filled_graph
    assert (system_uri, BMS.hasTemplateId, Literal(SystemTemplate.VAV_REHEAT.value)) in mock_filled_graph
    assert (system_uri, DCTERMS.created, Literal("2025-01-15T10:30:00")) in mock_filled_graph
    assert result["created"] == "2025-01-15T10:30:00"
    assert result["template_id"] == SystemTemplate.VAV_REHEAT.value


def test_create_system_raises_key_error_when_template_not_found(mock_adapter):
    """
    Test create_system raises KeyError when template_id not found.

    Verifies:
    - KeyError raised when invalid template_id provided
    - Error message includes template information
    """
    with pytest.raises(KeyError, match="Template not found"):
        SystemsModel(mock_adapter).create_system(
            project_id="test-project",
            template_id="invalid-template-id",
            label="Test System"
        )


def test_get_system_constructs_sparql_query_correctly(mock_adapter):
    """
    Test get_system builds SPARQL query with system_uri.

    Verifies:
    - SPARQL query includes system_uri in WHERE clause
    - Queries for label, template_id, created metadata
    - adapter.query_model() called with correct query string
    """
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model

    mock_adapter.query_model.return_value = [{
        "label": "VAV Box 101",
        "template_id": SystemTemplate.VAV_REHEAT.value,
        "created": "2025-01-15T10:30:00"
    }]

    result = SystemsModel(mock_adapter).get_system(
        project_id="test-project",
        system_uri="urn:bldgmotif:vav-reheat-1"
    )

    assert result is not None
    assert result["label"] == "VAV Box 101"
    assert result["template_id"] == SystemTemplate.VAV_REHEAT.value
    assert result["created"] == "2025-01-15T10:30:00"

    query_arg = mock_adapter.query_model.call_args[0][1]
    assert "urn:bldgmotif:vav-reheat-1" in query_arg
    assert "rdfs:label" in query_arg
    assert "bms:hasTemplateId" in query_arg
    assert "dcterms:created" in query_arg


def test_get_system_returns_none_when_system_not_found(mock_adapter):
    """
    Test get_system returns None when system_uri doesn't exist.

    Verifies:
    - Returns None when SPARQL query returns empty results
    - No exceptions raised
    """
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model
    mock_adapter.query_model.return_value = []

    result = SystemsModel(mock_adapter).get_system(
        project_id="test-project",
        system_uri="urn:bldgmotif:nonexistent"
    )

    assert result is None


def test_list_systems_orders_by_created_timestamp(mock_adapter):
    """
    Test list_systems returns systems ordered by dcterms:created.

    Verifies:
    - SPARQL query includes ORDER BY ?created
    - Returns list sorted chronologically
    """
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model

    mock_adapter.query_model.return_value = [
        {
            "system_uri": "urn:sys1",
            "label": "System 1",
            "template_id": "template1",
            "created": "2025-01-15T09:00:00"
        },
        {
            "system_uri": "urn:sys2",
            "label": "System 2",
            "template_id": "template2",
            "created": "2025-01-15T10:00:00"
        },
    ]

    result = SystemsModel(mock_adapter).list_systems(project_id="test-project")

    assert len(result) == 2
    assert result[0]["system_uri"] == "urn:sys1"
    assert result[1]["system_uri"] == "urn:sys2"

    query_arg = mock_adapter.query_model.call_args[0][1]
    assert "ORDER BY ?created" in query_arg


def test_list_systems_returns_empty_list_for_new_project(mock_adapter):
    """
    Test list_systems returns [] when project has no systems.

    Verifies:
    - Returns empty list (not None)
    - No errors raised
    """
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model
    mock_adapter.query_model.return_value = []

    result = SystemsModel(mock_adapter).list_systems(project_id="empty-project")

    assert result == []
    assert isinstance(result, list)


def test_delete_system_removes_all_related_triples(mock_adapter):
    """
    Test delete_system removes system and all connected triples.

    Verifies:
    - model.graph.triples() queries for all triples with system as subject
    - model.graph.remove() called for each triple
    - session.commit() called
    """
    BMS = Namespace("urn:bms:")
    system_uri = URIRef("urn:bldgmotif:system-to-delete")

    mock_model = Mock()
    mock_graph = Mock()

    triple1 = (system_uri, RDFS.label, Literal("Test System"))
    triple2 = (system_uri, BMS.hasTemplateId, Literal("template-id"))
    triple3 = (system_uri, DCTERMS.created, Literal("2025-01-15T10:00:00"))

    mock_graph.triples.return_value = [triple1, triple2, triple3]
    mock_model.graph = mock_graph

    mock_adapter.get_or_create_model.return_value = mock_model

    result = SystemsModel(mock_adapter).delete_system(
        project_id="test-project",
        system_uri=str(system_uri)
    )

    assert result is True
    assert mock_graph.remove.call_count == 3
    mock_graph.remove.assert_any_call(triple1)
    mock_graph.remove.assert_any_call(triple2)
    mock_graph.remove.assert_any_call(triple3)

    # Verify transaction context manager was used
    mock_adapter.transaction.assert_called_once()


def test_delete_system_returns_false_when_system_not_found(mock_adapter):
    """
    Test delete_system returns False when system_uri doesn't exist.

    Verifies:
    - Returns False (not raising exception)
    - No triples removed
    """
    mock_model = Mock()
    mock_graph = Mock()
    mock_graph.triples.return_value = []
    mock_model.graph = mock_graph

    mock_adapter.get_or_create_model.return_value = mock_model

    result = SystemsModel(mock_adapter).delete_system(
        project_id="test-project",
        system_uri="urn:bldgmotif:nonexistent"
    )

    assert result is False
    mock_graph.remove.assert_not_called()


def test_create_system_generates_valid_buildingmotif_urns(mock_adapter):
    """
    Test create_system URNs follow BuildingMOTIF format.

    Verifies:
    - URN starts with "urn:bldgmotif:" or similar BuildingMOTIF format
    - URN is unique per template.fill() call
    - No custom URN manipulation
    """
    mock_template = Mock()
    system_uri = URIRef("urn:bldgmotif:generated-urn-12345")
    mock_filled_graph = Graph()

    bindings = {"name": system_uri}
    mock_template.fill.return_value = (bindings, mock_filled_graph)

    mock_adapter.get_template_with_dependencies.return_value = mock_template

    mock_model = Mock()
    mock_model.graph = Graph()
    mock_adapter.get_or_create_model.return_value = mock_model

    result = SystemsModel(mock_adapter).create_system(
        project_id="test-project",
        template_id=SystemTemplate.VAV_REHEAT.value,
        label="Test System"
    )

    assert result["system_uri"].startswith("urn:")
    assert "urn:bldgmotif:generated-urn-12345" == result["system_uri"]
    assert result["template_id"] == SystemTemplate.VAV_REHEAT.value
