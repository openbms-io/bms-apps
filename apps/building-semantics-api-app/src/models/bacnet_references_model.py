"""Domain model for BACnet reference operations (SPARQL-based)."""

from loguru import logger
from rdflib import BNode, Literal, URIRef

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..constants.namespaces import BACNET, BMS
from ..services.validation_service import ValidationService
from ..utils.label_utils import get_label_or_extract
from .exceptions import ValidationException


class BACnetReferencesModel:
    """
    Domain model for BACnet reference operations.

    Responsibilities:
    - Create/update BACnet point → property URN references
    - Query enriched reference data (system → device → property chain)
    - Delete BACnet references
    - All data stored in RDF graph (no SQL tables)
    """

    def __init__(self, adapter: BuildingMOTIFAdapter) -> None:
        """
        Initialize BACnet references model.

        Args:
            adapter: BuildingMOTIF adapter instance
        """
        self.adapter = adapter

    def create_or_update_reference(
        self,
        project_id: str,
        bacnet_point_id: str,
        property_uri: str,
    ) -> dict[str, str]:
        """
        Create or update BACnet point → property URN reference.

        Stores reference as RDF triple in BuildingMOTIF graph.
        If reference already exists, updates it.
        Validates against ASHRAE 223P SHACL constraints before committing.

        Args:
            project_id: Unique project identifier
            bacnet_point_id: BACnet point identifier (e.g., "device123.analog-input-1")
            property_uri: Property URI from system instance

        Returns:
            Dictionary with bacnet_point_id and property_uri

        Raises:
            ValidationException: If SHACL validation fails
            RuntimeError: If reference creation fails
        """
        logger.info(
            f"Creating BACnet reference: {bacnet_point_id} → {property_uri}"
        )

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            bacnet_point_uri = URIRef(f"{BACNET}{bacnet_point_id}")
            property_uri_ref = URIRef(property_uri)

            with self.adapter.transaction():
                existing_refs = list(
                    model.graph.triples((bacnet_point_uri, BMS.mapsToProperty, None))
                )
                for triple in existing_refs:
                    model.graph.remove(triple)
                    logger.debug(f"Removed existing reference: {triple}")

                model.graph.add(
                    (bacnet_point_uri, BMS.mapsToProperty, property_uri_ref)
                )

                # SHACL validation BEFORE commit
                logger.debug("Validating BACnet reference against SHACL constraints")
                validation_result = ValidationService.validate_model(model)

                if not validation_result.isValid:
                    logger.warning(
                        f"SHACL validation failed for reference {bacnet_point_id}: {validation_result.errors}"
                    )
                    raise ValidationException(
                        errors=validation_result.errors,
                        warnings=validation_result.warnings
                    )

            logger.info(f"BACnet reference created/updated and validated: {bacnet_point_id}")

            return {
                "bacnet_point_id": bacnet_point_id,
                "property_uri": property_uri,
            }

        except ValidationException:
            raise
        except Exception as e:
            logger.error(f"Failed to create BACnet reference: {e}")
            raise RuntimeError(f"BACnet reference creation failed: {e}") from e

    def get_reference(
        self, project_id: str, bacnet_point_id: str
    ) -> dict[str, str] | None:
        """
        Get BACnet reference with enriched data.

        Queries RDF graph to get property URI and traces back to:
        - Property label and template
        - Device label and template
        - System label and template

        Args:
            project_id: Unique project identifier
            bacnet_point_id: BACnet point identifier

        Returns:
            Enriched reference dict or None if not found
        """
        logger.debug(f"Getting BACnet reference: {bacnet_point_id}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            query = f"""
            PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
            PREFIX bms: <urn:bms:>
            PREFIX s223: <http://data.ashrae.org/standard223#>

            SELECT ?property_uri ?property_label
                   ?device_uri ?device_label
                   ?system_uri ?system_label ?system_template
            WHERE {{
                <urn:bacnet:{bacnet_point_id}> bms:mapsToProperty ?property_uri .

                OPTIONAL {{ ?property_uri rdfs:label ?property_label . }}

                ?device_uri s223:hasProperty|s223:observes ?property_uri .
                OPTIONAL {{ ?device_uri rdfs:label ?device_label . }}

                ?system_uri s223:contains+ ?device_uri .
                ?system_uri bms:hasTemplateId ?system_template .
                ?system_uri rdfs:label ?system_label .
            }}
            """

            results = self.adapter.query_model(model, query)

            if not results:
                logger.warning(f"BACnet reference not found: {bacnet_point_id}")
                return None

            result = results[0]

            property_uri = result["property_uri"]
            device_uri = result["device_uri"]
            system_uri = result["system_uri"]
            system_label = result["system_label"]
            system_template = result["system_template"]

            assert isinstance(property_uri, str)
            assert isinstance(device_uri, str)
            assert isinstance(system_uri, str)
            assert isinstance(system_label, str)
            assert isinstance(system_template, str)

            property_label = get_label_or_extract(
                result.get("property_label"), property_uri
            )
            device_label = get_label_or_extract(
                result.get("device_label"), device_uri
            )

            return {
                "bacnet_point_id": bacnet_point_id,
                "property_uri": property_uri,
                "property_label": property_label,
                "device_uri": device_uri,
                "device_label": device_label,
                "system_uri": system_uri,
                "system_label": system_label,
                "system_template": system_template,
            }

        except Exception as e:
            logger.error(f"Failed to get BACnet reference: {e}")
            raise RuntimeError(f"BACnet reference retrieval failed: {e}") from e

    def get_all_references(self, project_id: str) -> list[dict[str, str]]:
        """
        Get all BACnet references for a project with enriched data.

        Queries RDF graph to get all BACnet point → property mappings
        and enriches each with system → device → property chain.

        Args:
            project_id: Unique project identifier

        Returns:
            List of enriched reference dicts
        """
        logger.debug(f"Getting all BACnet references for project: {project_id}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            query = """
            PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
            PREFIX bms: <urn:bms:>
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bacnet: <urn:bacnet:>

            SELECT ?bacnet_point_uri ?property_uri ?property_label
                   ?device_uri ?device_label
                   ?system_uri ?system_label ?system_template
            WHERE {
                ?bacnet_point_uri bms:mapsToProperty ?property_uri .
                FILTER (STRSTARTS(STR(?bacnet_point_uri), "urn:bacnet:"))

                OPTIONAL { ?property_uri rdfs:label ?property_label . }

                ?device_uri s223:hasProperty|s223:observes ?property_uri .
                OPTIONAL { ?device_uri rdfs:label ?device_label . }

                ?system_uri s223:contains+ ?device_uri .
                ?system_uri bms:hasTemplateId ?system_template .
                ?system_uri rdfs:label ?system_label .
            }
            ORDER BY ?bacnet_point_uri
            """

            results = self.adapter.query_model(model, query)

            references = []
            for result in results:
                bacnet_point_uri = str(result["bacnet_point_uri"])
                bacnet_point_id = bacnet_point_uri.replace("urn:bacnet:", "")

                property_uri = result["property_uri"]
                device_uri = result["device_uri"]
                system_uri = result["system_uri"]
                system_label = result["system_label"]
                system_template = result["system_template"]

                assert isinstance(property_uri, str)
                assert isinstance(device_uri, str)
                assert isinstance(system_uri, str)
                assert isinstance(system_label, str)
                assert isinstance(system_template, str)

                property_label = get_label_or_extract(
                    result.get("property_label"), property_uri
                )
                device_label = get_label_or_extract(
                    result.get("device_label"), device_uri
                )

                references.append({
                    "bacnet_point_id": bacnet_point_id,
                    "property_uri": property_uri,
                    "property_label": property_label,
                    "device_uri": device_uri,
                    "device_label": device_label,
                    "system_uri": system_uri,
                    "system_label": system_label,
                    "system_template": system_template,
                })

            logger.info(f"Found {len(references)} BACnet references for project {project_id}")
            return references

        except Exception as e:
            logger.error(f"Failed to get all BACnet references: {e}")
            raise RuntimeError(f"BACnet references retrieval failed: {e}") from e

    def delete_reference(self, project_id: str, bacnet_point_id: str) -> bool:
        """
        Delete BACnet reference from RDF graph.

        Args:
            project_id: Unique project identifier
            bacnet_point_id: BACnet point identifier

        Returns:
            True if deleted, False if not found
        """
        logger.info(f"Deleting BACnet reference: {bacnet_point_id}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            bacnet_point_uri = URIRef(f"{BACNET}{bacnet_point_id}")
            triples_to_remove = list(
                model.graph.triples((bacnet_point_uri, BMS.mapsToProperty, None))
            )

            if not triples_to_remove:
                logger.warning(
                    f"BACnet reference not found for deletion: {bacnet_point_id}"
                )
                return False

            with self.adapter.transaction():
                for triple in triples_to_remove:
                    model.graph.remove(triple)

            logger.info(
                f"BACnet reference deleted: {bacnet_point_id} ({len(triples_to_remove)} triples)"
            )
            return True

        except Exception as e:
            logger.error(f"Failed to delete BACnet reference: {e}")
            raise RuntimeError(f"BACnet reference deletion failed: {e}") from e

    def validate_property_exists(
        self, project_id: str, property_uri: str
    ) -> bool:
        """
        Validate that property URI exists in project RDF graph.

        Args:
            project_id: Unique project identifier
            property_uri: Property URI to validate

        Returns:
            True if property exists, False otherwise
        """
        logger.debug(f"Validating property exists: {property_uri}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            query = f"""
            ASK {{
                <{property_uri}> ?p ?o .
            }}
            """

            result = model.graph.query(query)
            exists = bool(result)

            if not exists:
                logger.warning(f"Property not found in project: {property_uri}")

            return exists

        except Exception as e:
            logger.error(f"Failed to validate property: {e}")
            return False
