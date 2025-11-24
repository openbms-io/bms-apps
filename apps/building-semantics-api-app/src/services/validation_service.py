"""Service for ASHRAE 223P SHACL validation using BuildingMOTIF."""
from buildingmotif.dataclasses import Model
from loguru import logger
from rdflib import Graph
from rdflib.namespace import SH

from src.config.settings import get_settings
from src.dto.validation_dto import ValidationResultDTO


class ValidationService:
    """Service for ASHRAE 223P SHACL validation using BuildingMOTIF."""

    @staticmethod
    def validate_model(model: Model) -> ValidationResultDTO:
        """
        Validate BuildingMOTIF model against 223P SHACL constraints.

        Args:
            model: BuildingMOTIF Model instance to validate

        Returns:
            ValidationResultDTO with validation results
        """
        settings = get_settings()

        # Skip validation if disabled in settings
        if not settings.enable_validation:
            logger.debug("SHACL validation disabled by settings - skipping")
            return ValidationResultDTO(isValid=True, errors=[], warnings=[])

        try:
            from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter

            logger.debug(f"Getting shapes for model with {len(model.graph)} triples")

            adapter = BuildingMOTIFAdapter.get_instance()
            s223_shapes = adapter.get_223p_shapes()
            unit_shapes = adapter.get_unit_shapes()
            qk_shapes = adapter.get_quantitykind_shapes()

            logger.debug(
                f"Starting Validation: Using 223P shapes ({len(s223_shapes.graph)} triples), "
                f"Unit shapes ({len(unit_shapes.graph)} triples), "
                f"and QuantityKind shapes ({len(qk_shapes.graph)} triples)"
            )

            ctx = model.validate([s223_shapes, unit_shapes, qk_shapes], error_on_missing_imports=False)
            logger.debug("Validation completed")

            if ctx.valid:
                logger.debug("Validation passed")
                return ValidationResultDTO(isValid=True, errors=[], warnings=[])

            errors = ValidationService._parse_validation_report(ctx.report_string)
            logger.debug(f"Validation failed with {len(errors)} errors")

            return ValidationResultDTO(isValid=False, errors=errors, warnings=[])

        except Exception as e:
            logger.error(f"Model validation failed: {e}")
            return ValidationResultDTO(
                isValid=False,
                errors=[f"Validation error: {str(e)}"],
                warnings=[]
            )

    @staticmethod
    def _parse_validation_report(report: str) -> list[str]:
        """
        Parse SHACL validation report into user-friendly error messages.

        Args:
            report: Raw SHACL validation report from BuildingMOTIF

        Returns:
            List of formatted error messages
        """
        try:
            report_graph = Graph()
            report_graph.parse(data=report, format="turtle")

            errors: list[str] = []

            query = """
                PREFIX sh: <http://www.w3.org/ns/shacl#>

                SELECT ?message ?severity ?path
                WHERE {
                    ?result a sh:ValidationResult .
                    OPTIONAL { ?result sh:resultMessage ?message }
                    OPTIONAL { ?result sh:resultSeverity ?severity }
                    OPTIONAL { ?result sh:resultPath ?path }
                }
            """

            results = report_graph.query(query)

            has_results = False
            for row in results:
                has_results = True
                severity = getattr(row, 'severity', None)
                severity_uri = str(severity) if severity else None
                is_violation = severity_uri and severity_uri.endswith("Violation")

                if is_violation or not severity_uri:
                    message_value = getattr(row, 'message', None)
                    message = str(message_value) if message_value else "Unknown validation error"
                    errors.append(message)

            if not errors and has_results:
                pass
            elif not errors and not has_results:
                errors.append("SHACL validation failed but no specific errors were reported")

            logger.debug(f"Parsed {len(errors)} errors from SHACL report")

            return errors

        except Exception as e:
            logger.error(f"Failed to parse SHACL validation report: {e}")
            return [f"Failed to parse validation report: {str(e)}"]
