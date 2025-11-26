"""Unit tests for ValidationService."""
import pytest
from unittest.mock import Mock, patch
from rdflib import Graph

from src.services.validation_service import ValidationService
from src.dto.validation_dto import ValidationResultDTO
from src.config.settings import get_settings

# Skip validation tests when validation is disabled
pytestmark = pytest.mark.skipif(
    not get_settings().enable_validation,
    reason="Validation disabled in settings - tests require validation to be enabled"
)

SAMPLE_VALID_REPORT = """
@prefix sh: <http://www.w3.org/ns/shacl#> .
"""

SAMPLE_VIOLATION_REPORT = """
@prefix sh: <http://www.w3.org/ns/shacl#> .

_:result1 a sh:ValidationResult ;
    sh:resultMessage "Equipment type 'invalid-type' not found in ASHRAE 223P ontology" ;
    sh:resultSeverity sh:Violation .

_:result2 a sh:ValidationResult ;
    sh:resultMessage "Equipment must have at least one s223:contains relationship" ;
    sh:resultSeverity sh:Violation .
"""

SAMPLE_WARNING_REPORT = """
@prefix sh: <http://www.w3.org/ns/shacl#> .

_:result1 a sh:ValidationResult ;
    sh:resultMessage "This is just a warning" ;
    sh:resultSeverity sh:Warning .
"""


def test_validate_valid_equipment_mapping() -> None:
    """Test validation of valid RDF graph returns isValid=True."""
    graph = Graph()

    with patch("src.services.validation_service.Model") as mock_model_class:
        with patch("src.services.validation_service.BuildingMOTIFAdapter") as mock_adapter_class:
            mock_model = Mock()
            mock_model_class.create.return_value = mock_model
            mock_model.graph = Graph()

            mock_ctx = Mock()
            mock_ctx.valid = True
            mock_ctx.report_string = SAMPLE_VALID_REPORT
            mock_model.validate.return_value = mock_ctx

            mock_adapter = Mock()
            mock_adapter_class.get_instance.return_value = mock_adapter
            mock_lib = Mock()
            mock_adapter.get_nrel_library.return_value = mock_lib
            mock_shape_collection = Mock()
            mock_lib.get_shape_collection.return_value = mock_shape_collection

            result = ValidationService.validate_equipment_mapping(graph)

            assert isinstance(result, ValidationResultDTO)
            assert result.isValid is True
            assert result.errors == []
            assert result.warnings == []


def test_validate_invalid_equipment_type() -> None:
    """Test validation of graph with invalid equipment type returns errors."""
    graph = Graph()

    with patch("src.services.validation_service.Model") as mock_model_class:
        with patch("src.services.validation_service.BuildingMOTIFAdapter") as mock_adapter_class:
            mock_model = Mock()
            mock_model_class.create.return_value = mock_model
            mock_model.graph = Graph()

            mock_ctx = Mock()
            mock_ctx.valid = False
            mock_ctx.report_string = SAMPLE_VIOLATION_REPORT
            mock_model.validate.return_value = mock_ctx

            mock_adapter = Mock()
            mock_adapter_class.get_instance.return_value = mock_adapter
            mock_lib = Mock()
            mock_adapter.get_nrel_library.return_value = mock_lib
            mock_shape_collection = Mock()
            mock_lib.get_shape_collection.return_value = mock_shape_collection

            result = ValidationService.validate_equipment_mapping(graph)

            assert isinstance(result, ValidationResultDTO)
            assert result.isValid is False
            assert len(result.errors) == 2
            assert "Equipment type 'invalid-type' not found" in result.errors[0]
            assert "s223:contains relationship" in result.errors[1]


def test_validate_with_warnings_only() -> None:
    """Test validation with warnings (not violations) returns isValid=True."""
    graph = Graph()

    with patch("src.services.validation_service.Model") as mock_model_class:
        with patch("src.services.validation_service.BuildingMOTIFAdapter") as mock_adapter_class:
            mock_model = Mock()
            mock_model_class.create.return_value = mock_model
            mock_model.graph = Graph()

            mock_ctx = Mock()
            mock_ctx.valid = True
            mock_ctx.report_string = SAMPLE_WARNING_REPORT
            mock_model.validate.return_value = mock_ctx

            mock_adapter = Mock()
            mock_adapter_class.get_instance.return_value = mock_adapter
            mock_lib = Mock()
            mock_adapter.get_nrel_library.return_value = mock_lib
            mock_shape_collection = Mock()
            mock_lib.get_shape_collection.return_value = mock_shape_collection

            result = ValidationService.validate_equipment_mapping(graph)

            assert result.isValid is True
            assert result.errors == []


def test_validate_buildingmotif_exception() -> None:
    """Test validation handles BuildingMOTIF exceptions gracefully."""
    graph = Graph()

    with patch("src.services.validation_service.Model") as mock_model_class:
        with patch("src.services.validation_service.BuildingMOTIFAdapter") as mock_adapter_class:
            mock_model = Mock()
            mock_model_class.create.return_value = mock_model
            mock_model.graph = Graph()

            mock_adapter = Mock()
            mock_adapter_class.get_instance.return_value = mock_adapter
            mock_lib = Mock()
            mock_adapter.get_nrel_library.return_value = mock_lib
            mock_shape_collection = Mock()
            mock_lib.get_shape_collection.return_value = mock_shape_collection

            mock_model.validate.side_effect = Exception("BuildingMOTIF error")

            result = ValidationService.validate_equipment_mapping(graph)

            assert result.isValid is False
            assert len(result.errors) == 1
            assert "Validation error" in result.errors[0]
            assert "BuildingMOTIF error" in result.errors[0]


def test_parse_validation_report_extracts_error_messages() -> None:
    """Test _parse_validation_report extracts error messages from SHACL report."""
    errors = ValidationService._parse_validation_report(SAMPLE_VIOLATION_REPORT)

    assert len(errors) == 2
    assert "Equipment type 'invalid-type' not found" in errors[0]
    assert "s223:contains relationship" in errors[1]


def test_parse_validation_report_filters_warnings() -> None:
    """Test _parse_validation_report filters out warnings (sh:Warning severity)."""
    errors = ValidationService._parse_validation_report(SAMPLE_WARNING_REPORT)

    assert len(errors) == 0


def test_parse_validation_report_empty_report() -> None:
    """Test _parse_validation_report handles empty report gracefully."""
    errors = ValidationService._parse_validation_report(SAMPLE_VALID_REPORT)

    assert len(errors) == 1
    assert "no specific errors were reported" in errors[0]


def test_parse_validation_report_malformed_report() -> None:
    """Test _parse_validation_report handles malformed report gracefully."""
    malformed_report = "This is not valid Turtle syntax {{"

    errors = ValidationService._parse_validation_report(malformed_report)

    assert len(errors) == 1
    assert "Failed to parse validation report" in errors[0]


def test_validate_empty_graph() -> None:
    """Test validation of empty graph."""
    graph = Graph()

    with patch("src.services.validation_service.Model") as mock_model_class:
        with patch("src.services.validation_service.BuildingMOTIFAdapter") as mock_adapter_class:
            mock_model = Mock()
            mock_model_class.create.return_value = mock_model
            mock_model.graph = Graph()

            mock_ctx = Mock()
            mock_ctx.valid = True
            mock_ctx.report_string = SAMPLE_VALID_REPORT
            mock_model.validate.return_value = mock_ctx

            mock_adapter = Mock()
            mock_adapter_class.get_instance.return_value = mock_adapter
            mock_lib = Mock()
            mock_adapter.get_nrel_library.return_value = mock_lib
            mock_shape_collection = Mock()
            mock_lib.get_shape_collection.return_value = mock_shape_collection

            result = ValidationService.validate_equipment_mapping(graph)

            assert result.isValid is True
            assert result.errors == []


def test_parse_validation_report_missing_message() -> None:
    """Test _parse_validation_report handles results without messages."""
    report_without_message = """
    @prefix sh: <http://www.w3.org/ns/shacl#> .

    _:result1 a sh:ValidationResult ;
        sh:resultSeverity sh:Violation .
    """

    errors = ValidationService._parse_validation_report(report_without_message)

    assert len(errors) == 1
    assert "Unknown validation error" in errors[0]
