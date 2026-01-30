"""Domain model for BACnet reference operations (SPARQL-based)."""

from loguru import logger
from rdflib import Literal, URIRef

from ..adapters.semantics_adapter_protocol import (
    ModelHandle,
    RDFTriple,
    SemanticsAdapterProtocol,
    TriplePattern,
)
from ..constants.namespaces import (
    BACNET,
    BMS_BACNET_INDEX,
    BMS_BACNET_INDEX_STRING,
    DCTERMS,
    RDF,
    S223,
    SPARQL_PREFIXES,
)
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

    def __init__(self, adapter: SemanticsAdapterProtocol) -> None:
        """
        Initialize BACnet references model.

        Args:
            adapter: Semantics adapter instance implementing SemanticsAdapterProtocol
        """
        self.adapter = adapter

    def _collect_old_reference_patterns(
        self,
        model: ModelHandle,
        bacnet_ref_uri: URIRef,
        property_uri_ref: URIRef,
    ) -> list[TriplePattern]:
        """
        Collect triple patterns to remove for updating an existing reference.

        Args:
            model: Model containing the graph
            bacnet_ref_uri: URI of the BACnet reference entity
            property_uri_ref: URI of the property being referenced

        Returns:
            List of triple patterns to remove (None = wildcard matching any value)
        """
        patterns: list[TriplePattern] = [
            (bacnet_ref_uri, BMS_BACNET_INDEX.mapsToProperty, None),  # Remove old index
            (bacnet_ref_uri, None, None),  # Delete old BACnetExternalReference entity
            (property_uri_ref, S223.hasExternalReference, None),  # Remove forward link
        ]

        # Find and remove any other old entities linked via hasExternalReference
        for ref_uri in list(model.graph.objects(property_uri_ref, S223.hasExternalReference)):
            patterns.append((ref_uri, None, None))
            logger.debug(f"Will remove existing BACnetExternalReference: {ref_uri}")

        return patterns

    def _build_reference_triples(
        self,
        bacnet_ref_uri: URIRef,
        property_uri_ref: URIRef,
        device_identifier: str,
        object_identifier: str,
        external_identifier: str,
    ) -> list[RDFTriple]:
        """
        Build triples for a new BACnet reference.

        Args:
            bacnet_ref_uri: URI for the new BACnet reference entity
            property_uri_ref: URI of the property being referenced
            device_identifier: BACnet device identifier
            object_identifier: BACnet object identifier
            external_identifier: External identifier with IP

        Returns:
            List of RDF triples to add
        """
        return [
            (bacnet_ref_uri, RDF.type, S223.BACnetExternalReference),
            (bacnet_ref_uri, BACNET["device-identifier"], Literal(device_identifier)),
            (bacnet_ref_uri, BACNET["object-identifier"], Literal(object_identifier)),
            (bacnet_ref_uri, DCTERMS.identifier, Literal(external_identifier)),
            (property_uri_ref, S223.hasExternalReference, bacnet_ref_uri),
            (bacnet_ref_uri, BMS_BACNET_INDEX.mapsToProperty, property_uri_ref),
        ]

    def _create_validation_fn(self, bacnet_point_id: str):
        """
        Create a validation function for atomic_update.

        Args:
            bacnet_point_id: ID for error messages

        Returns:
            Validation function that raises ValidationException on failure
        """
        def validate(model: ModelHandle) -> None:
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

        return validate

    def create_or_update_reference(
        self,
        project_id: str,
        bacnet_point_id: str,
        property_uri: str,
        device_identifier: str,
        object_identifier: str,
        external_identifier: str,
    ) -> dict[str, str]:
        """
        Create or update BACnet point → property URN reference with 223P-compliant external reference.

        Creates s223:BACnetExternalReference entity with device/object identifiers per ASHRAE 223P.
        If reference already exists, removes old reference and creates new one.
        Validates against ASHRAE 223P SHACL constraints before committing.

        Args:
            project_id: Unique project identifier
            bacnet_point_id: BACnet point identifier (UUID)
            property_uri: Property URI from system instance
            device_identifier: BACnet device identifier (e.g., "device,123")
            object_identifier: BACnet object identifier (e.g., "analog-input,1")
            external_identifier: External identifier with IP (e.g., "192.168.1.100:device,123:analog-input,1")

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

            property_uri_ref = URIRef(property_uri)
            bacnet_ref_uri = BMS_BACNET_INDEX[bacnet_point_id]

            # Build triples (business logic)
            patterns_to_remove = self._collect_old_reference_patterns(
                model, bacnet_ref_uri, property_uri_ref
            )
            triples_to_add = self._build_reference_triples(
                bacnet_ref_uri,
                property_uri_ref,
                device_identifier,
                object_identifier,
                external_identifier,
            )

            logger.debug(f"Creating BACnetExternalReference: {bacnet_ref_uri}")
            logger.debug(f"  device-identifier: {device_identifier}")
            logger.debug(f"  object-identifier: {object_identifier}")
            logger.debug(f"  external-identifier: {external_identifier}")
            logger.debug(f"  internal-index: {bacnet_ref_uri} → {property_uri}")

            # Atomic update with validation (persistence)
            self.adapter.atomic_update(
                model,
                add=triples_to_add,
                remove=patterns_to_remove,
                validate_fn=self._create_validation_fn(bacnet_point_id),
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
            {SPARQL_PREFIXES}

            SELECT ?property_uri ?property_label
                   ?device_uri ?device_label
                   ?system_uri ?system_label ?system_template
            WHERE {{
                <{BMS_BACNET_INDEX_STRING}{bacnet_point_id}> bms-bacnet:mapsToProperty ?property_uri .

                OPTIONAL {{ ?property_uri rdfs:label ?property_label . }}

                ?device_uri s223:hasProperty|s223:observes ?property_uri .
                OPTIONAL {{ ?device_uri rdfs:label ?device_label . }}

                ?system_uri s223:contains+ ?device_uri .
                ?system_uri bms:hasTemplateId ?system_template .
                ?system_uri rdfs:label ?system_label .
            }}
            """

            query_result = self.adapter.query_model(model, query)

            if not query_result.bindings:
                logger.warning(f"BACnet reference not found: {bacnet_point_id}")
                return None

            result = query_result.bindings[0]

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

            query = f"""
            {SPARQL_PREFIXES}

            SELECT ?bacnet_point_uri ?property_uri ?property_label
                   ?device_uri ?device_label
                   ?system_uri ?system_label ?system_template
            WHERE {{
                ?bacnet_point_uri bms-bacnet:mapsToProperty ?property_uri .
                FILTER (STRSTARTS(STR(?bacnet_point_uri), "{BMS_BACNET_INDEX_STRING}"))

                OPTIONAL {{ ?property_uri rdfs:label ?property_label . }}

                ?device_uri s223:hasProperty|s223:observes ?property_uri .
                OPTIONAL {{ ?device_uri rdfs:label ?device_label . }}

                ?system_uri s223:contains+ ?device_uri .
                ?system_uri bms:hasTemplateId ?system_template .
                ?system_uri rdfs:label ?system_label .
            }}
            ORDER BY ?bacnet_point_uri
            """

            query_result = self.adapter.query_model(model, query)

            references = []
            for result in query_result.bindings:
                bacnet_point_uri = str(result["bacnet_point_uri"])
                bacnet_point_id = bacnet_point_uri.replace(BMS_BACNET_INDEX_STRING, "")

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

            bacnet_ref_uri = BMS_BACNET_INDEX[bacnet_point_id]

            # Find property_uri from internal index
            property_uri = model.graph.value(bacnet_ref_uri, BMS_BACNET_INDEX.mapsToProperty)

            if property_uri is None:
                logger.warning(f"BACnet reference not found for deletion: {bacnet_point_id}")
                return False

            patterns_to_remove: list[TriplePattern] = [
                (bacnet_ref_uri, BMS_BACNET_INDEX.mapsToProperty, property_uri),
                (bacnet_ref_uri, None, None),  # Remove all triples with bacnet_ref_uri as subject
                (property_uri, S223.hasExternalReference, bacnet_ref_uri),
            ]

            logger.debug(f"Deleting BACnetExternalReference entity: {bacnet_ref_uri}")
            self.adapter.remove_triples(model, patterns_to_remove)

            logger.info(f"BACnet reference deleted: {bacnet_point_id}")
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
