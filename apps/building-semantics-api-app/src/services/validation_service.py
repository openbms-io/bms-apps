"""Service for ASHRAE 223P SHACL validation using BuildingMOTIF."""
from buildingmotif import get_building_motif
from buildingmotif.dataclasses import Model
from loguru import logger
from rdflib import Graph, Namespace
from rdflib.namespace import SH

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.dto.validation_dto import ValidationResultDTO


class ValidationService:
    """Service for ASHRAE 223P SHACL validation using BuildingMOTIF."""

    @staticmethod
    def validate_equipment_mapping(graph: Graph) -> ValidationResultDTO:
        """
        Validate RDF graph against ASHRAE 223P SHACL constraints.

        Args:
            graph: RDF graph containing equipment instances to validate

        Returns:
            ValidationResultDTO with validation results
        """
        try:
            logger.debug(f"Validating graph with {len(graph)} triples")

            # Create temporary model from graph
            temp_model = Model.create(Namespace("urn:validation:temp"))
            for triple in graph:
                temp_model.graph.add(triple)

            # Get shape collection (already loaded in adapter)
            adapter = BuildingMOTIFAdapter.get_instance()
            nrel_lib = adapter.get_nrel_library()
            shape_collection = nrel_lib.get_shape_collection()

            # Validate using BuildingMOTIF Model API
            ctx = temp_model.validate([shape_collection])

            valid = ctx.valid
            report_string = ctx.report_string

            logger.debug(f"Validation result: valid={valid}")

            if valid:
                return ValidationResultDTO(
                    isValid=True,
                    errors=[],
                    warnings=[]
                )

            errors = ValidationService._parse_validation_report(report_string)

            logger.debug(f"Validation failed with {len(errors)} errors")

            return ValidationResultDTO(
                isValid=False,
                errors=errors,
                warnings=[]
            )

        except Exception as e:
            logger.error(f"SHACL validation failed: {e}")
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
                severity_uri = str(row.severity) if row.severity else None
                is_violation = severity_uri and severity_uri.endswith("Violation")

                if is_violation or not severity_uri:
                    message = str(row.message) if row.message else "Unknown validation error"
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
