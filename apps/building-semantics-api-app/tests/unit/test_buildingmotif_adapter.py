"""Unit tests for BuildingMOTIF adapter."""
import pytest
from unittest.mock import Mock, patch

from src.adapters import BuildingMOTIFAdapter, DeviceTemplate, SystemTemplate


@pytest.fixture
def mock_buildingmotif():
    """Mock BuildingMOTIF SDK."""
    with patch("src.adapters.buildingmotif_adapter.BuildingMOTIF") as mock_bm:
        with patch("src.adapters.buildingmotif_adapter.Library") as mock_lib:
            with patch("src.adapters.buildingmotif_adapter.Path") as mock_path:
                mock_library = Mock()
                mock_lib.load.return_value = mock_library

                mock_path_instance = Mock()
                mock_path_instance.exists.return_value = True
                mock_path.return_value = mock_path_instance

                yield mock_bm, mock_library


def test_adapter_initialization(mock_buildingmotif) -> None:
    """Test adapter initializes BuildingMOTIF SDK."""
    mock_bm, mock_library = mock_buildingmotif

    adapter = BuildingMOTIFAdapter("test.db")

    mock_bm.assert_called_once_with("sqlite:///test.db")
    assert adapter.get_nrel_library() == mock_library


def test_get_template_by_name(mock_buildingmotif) -> None:
    """Test retrieving template by name with enum."""
    mock_bm, mock_library = mock_buildingmotif
    mock_template = Mock()
    mock_library.get_template_by_name.return_value = mock_template

    adapter = BuildingMOTIFAdapter("test.db")
    template = adapter.get_template_by_name(SystemTemplate.VAV_REHEAT)

    assert template == mock_template
    mock_library.get_template_by_name.assert_called_once_with("vav-reheat")


def test_get_template_not_found(mock_buildingmotif) -> None:
    """Test template not found raises exception."""
    mock_bm, mock_library = mock_buildingmotif
    mock_library.get_template_by_name.side_effect = KeyError("not found")

    adapter = BuildingMOTIFAdapter("test.db")

    with pytest.raises(KeyError):
        adapter.get_template_by_name(DeviceTemplate.DAMPER)


def test_list_templates(mock_buildingmotif) -> None:
    """Test listing all templates."""
    mock_bm, mock_library = mock_buildingmotif

    mock_template1 = Mock()
    mock_template1.name = "vav-reheat"
    mock_template2 = Mock()
    mock_template2.name = "damper"

    mock_library.get_templates.return_value = [mock_template1, mock_template2]

    adapter = BuildingMOTIFAdapter("test.db")
    templates = adapter.list_templates()

    assert templates == ["vav-reheat", "damper"]


def test_create_model(mock_buildingmotif) -> None:
    """Test creating RDF model."""
    mock_bm, mock_library = mock_buildingmotif

    with patch("src.adapters.buildingmotif_adapter.Model") as mock_model_class:
        mock_model = Mock()
        mock_model_class.create.return_value = mock_model

        adapter = BuildingMOTIFAdapter("test.db")
        model = adapter.create_model("urn:test:building/")

        assert model == mock_model
        mock_model_class.create.assert_called_once()


def test_query_model(mock_buildingmotif) -> None:
    """Test executing SPARQL query on model."""
    mock_bm, mock_library = mock_buildingmotif

    mock_model = Mock()
    mock_graph = Mock()
    mock_results = Mock()
    mock_results.vars = ["var1", "var2"]

    mock_row1 = {"var1": "value1", "var2": "value2"}
    mock_row2 = {"var1": "value3", "var2": "value4"}
    mock_results.__iter__ = Mock(return_value=iter([mock_row1, mock_row2]))

    mock_graph.query.return_value = mock_results
    mock_model.graph = mock_graph

    adapter = BuildingMOTIFAdapter("test.db")
    results = adapter.query_model(mock_model, "SELECT * WHERE { ?s ?p ?o }")

    assert len(results) == 2
    assert results[0] == {"var1": "value1", "var2": "value2"}
    assert results[1] == {"var1": "value3", "var2": "value4"}


def test_add_graph(mock_buildingmotif) -> None:
    """Test adding RDF graph to model."""
    mock_bm, mock_library = mock_buildingmotif

    mock_model = Mock()
    mock_graph = Mock()
    mock_graph.__len__ = Mock(return_value=10)

    adapter = BuildingMOTIFAdapter("test.db")
    adapter.add_graph(mock_model, mock_graph)

    mock_model.add_graph.assert_called_once_with(mock_graph)


def test_get_buildingmotif_instance(mock_buildingmotif) -> None:
    """Test getting underlying BuildingMOTIF instance."""
    mock_bm_instance, mock_library = mock_buildingmotif

    adapter = BuildingMOTIFAdapter("test.db")
    bm = adapter.get_buildingmotif_instance()

    assert bm == adapter.get_buildingmotif_instance()
