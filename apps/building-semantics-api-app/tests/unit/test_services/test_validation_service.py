"""Unit tests for ValidationService."""
from src.services.validation_service import ValidationService

SAMPLE_VALID_REPORT = """
@prefix sh: <http://www.w3.org/ns/shacl#> .
"""

SAMPLE_VIOLATION_REPORT = """
@prefix sh: <http://www.w3.org/ns/shacl#> .
@prefix ex: <http://example.org/> .

_:result1 a sh:ValidationResult ;
    sh:focusNode ex:equipment-1 ;
    sh:resultMessage "Equipment type 'invalid-type' not found in ASHRAE 223P ontology" ;
    sh:resultSeverity sh:Violation ;
    sh:resultPath ex:hasType .

_:result2 a sh:ValidationResult ;
    sh:focusNode ex:equipment-2 ;
    sh:resultMessage "Equipment must have at least one s223:contains relationship" ;
    sh:resultSeverity sh:Violation .
"""

SAMPLE_WARNING_REPORT = """
@prefix sh: <http://www.w3.org/ns/shacl#> .
@prefix ex: <http://example.org/> .

_:result1 a sh:ValidationResult ;
    sh:focusNode ex:device-1 ;
    sh:resultMessage "This is just a warning" ;
    sh:resultSeverity sh:Warning .
"""


def test_parse_validation_report_extracts_error_messages() -> None:
    """Test _parse_validation_report extracts error messages with focus node and path."""
    errors, warnings = ValidationService._parse_validation_report(SAMPLE_VIOLATION_REPORT)

    assert len(errors) == 2
    assert "equipment-1" in errors[0]
    assert "Equipment type 'invalid-type' not found" in errors[0]
    assert "(path:" in errors[0]
    assert "equipment-2" in errors[1]
    assert "s223:contains relationship" in errors[1]
    assert len(warnings) == 0


def test_parse_validation_report_captures_warnings() -> None:
    """Test _parse_validation_report captures warnings separately with focus node."""
    errors, warnings = ValidationService._parse_validation_report(SAMPLE_WARNING_REPORT)

    assert len(errors) == 0
    assert len(warnings) == 1
    assert "device-1" in warnings[0]
    assert "This is just a warning" in warnings[0]


def test_parse_validation_report_empty_report() -> None:
    """Test _parse_validation_report handles empty report gracefully."""
    errors, warnings = ValidationService._parse_validation_report(SAMPLE_VALID_REPORT)

    assert len(errors) == 1
    assert "no specific errors were reported" in errors[0]
    assert len(warnings) == 0


def test_parse_validation_report_malformed_report() -> None:
    """Test _parse_validation_report handles malformed report gracefully."""
    malformed_report = "This is not valid Turtle syntax {{"

    errors, warnings = ValidationService._parse_validation_report(malformed_report)

    assert len(errors) == 1
    assert "Failed to parse validation report" in errors[0]
    assert len(warnings) == 0


def test_parse_validation_report_missing_message() -> None:
    """Test _parse_validation_report handles results without messages."""
    report_without_message = """
    @prefix sh: <http://www.w3.org/ns/shacl#> .

    _:result1 a sh:ValidationResult ;
        sh:resultSeverity sh:Violation .
    """

    errors, warnings = ValidationService._parse_validation_report(report_without_message)

    assert len(errors) == 1
    assert "Unknown validation error" in errors[0]
    assert len(warnings) == 0
