"""Domain model for ASHRAE 223P system instance operations."""

from datetime import datetime

from buildingmotif.dataclasses import Model
from loguru import logger
from rdflib import Literal, URIRef

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..adapters.template_types import SystemTemplate
from ..constants.namespaces import BMS, DCTERMS, RDFS


class SystemsModel:
    """
    Domain model for system instance operations.

    Responsibilities:
    - System instance creation from templates using template.fill()
    - System metadata management (labels, template IDs, timestamps)
    - System CRUD operations (create, get, list, delete)
    - Single source of truth in RDF graph (no SQL tables)
    """

    def __init__(self, adapter: BuildingMOTIFAdapter) -> None:
        """
        Initialize systems model.

        Args:
            adapter: BuildingMOTIF adapter instance
        """
        self.adapter = adapter

    def create_system(
        self, project_id: str, template_id: str, label: str
    ) -> dict[str, str]:
        """
        Create reusable system instance from ASHRAE 223P template.

        Business logic (from Story 2-12 mini-spec Section 5.2):
        1. Load template WITH dependencies
        2. SINGLE fill - BuildingMOTIF generates all URNs
        3. Add user label + metadata (URNs remain unchanged)
        4. Save to BuildingMOTIF project model
        5. Return system URI and metadata

        Args:
            project_id: Unique project identifier
            template_id: System template enum value (e.g., "vav-reheat")
            label: User-provided custom label (e.g., "VAV-Floor3-Zone5")

        Returns:
            Dictionary with system_uri, label, template_id, created timestamp

        Raises:
            KeyError: If template not found
            RuntimeError: If system creation fails
        """
        logger.info(f"Creating system instance: template={template_id}, label={label}")

        try:
            system_template_enum = SystemTemplate(template_id)
            template = self.adapter.get_template_with_dependencies(system_template_enum)

            bindings, filled_graph = template.fill(BMS)
            system_uri = bindings["name"]

            filled_graph.set((system_uri, RDFS.label, Literal(label)))
            filled_graph.add(
                (system_uri, BMS.hasTemplateId, Literal(template_id))
            )
            created_timestamp = datetime.now().isoformat()
            filled_graph.add(
                (system_uri, DCTERMS.created, Literal(created_timestamp))
            )

            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            with self.adapter.transaction():
                model.graph += filled_graph

            logger.info(
                f"System created: {system_uri} (label={label}, template={template_id})"
            )

            return {
                "system_uri": str(system_uri),
                "label": label,
                "template_id": template_id,
                "created": created_timestamp,
            }

        except ValueError as e:
            logger.error(f"Invalid template ID: {template_id}")
            raise KeyError(f"Template not found: {template_id}") from e
        except Exception as e:
            logger.error(f"Failed to create system: {e}")
            raise RuntimeError(f"System creation failed: {e}") from e

    def get_system(self, project_id: str, system_uri: str) -> dict[str, str] | None:
        """
        Get system instance details from RDF graph.

        Args:
            project_id: Unique project identifier
            system_uri: System URI

        Returns:
            System metadata dict or None if not found
        """
        logger.debug(f"Retrieving system: {system_uri}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            query = f"""
            PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
            PREFIX bms: <urn:bms:>
            PREFIX dcterms: <http://purl.org/dc/terms/>

            SELECT ?label ?template_id ?created
            WHERE {{
                <{system_uri}> rdfs:label ?label ;
                               bms:hasTemplateId ?template_id ;
                               dcterms:created ?created .
            }}
            """

            results = self.adapter.query_model(model, query)

            if not results:
                logger.warning(f"System not found: {system_uri}")
                return None

            result = results[0]
            label = result["label"]
            template_id = result["template_id"]
            created = result["created"]

            assert isinstance(label, str)
            assert isinstance(template_id, str)
            assert isinstance(created, str)

            return {
                "system_uri": system_uri,
                "label": label,
                "template_id": template_id,
                "created": created,
            }

        except Exception as e:
            logger.error(f"Failed to get system: {e}")
            raise RuntimeError(f"System retrieval failed: {e}") from e

    def list_systems(self, project_id: str) -> list[dict[str, str]]:
        """
        List all system instances in project.

        Args:
            project_id: Unique project identifier

        Returns:
            List of system metadata dicts
        """
        logger.debug(f"Listing systems for project: {project_id}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            query = """
            PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
            PREFIX bms: <urn:bms:>
            PREFIX dcterms: <http://purl.org/dc/terms/>

            SELECT ?system_uri ?label ?template_id ?created
            WHERE {
                ?system_uri bms:hasTemplateId ?template_id ;
                           rdfs:label ?label ;
                           dcterms:created ?created .
            }
            ORDER BY ?created
            """

            results = self.adapter.query_model(model, query)

            systems = []
            for result in results:
                system_uri = result["system_uri"]
                label = result["label"]
                template_id = result["template_id"]
                created = result["created"]

                assert isinstance(system_uri, str)
                assert isinstance(label, str)
                assert isinstance(template_id, str)
                assert isinstance(created, str)

                systems.append({
                    "system_uri": system_uri,
                    "label": label,
                    "template_id": template_id,
                    "created": created,
                })

            logger.info(f"Found {len(systems)} systems in project {project_id}")
            return systems

        except Exception as e:
            logger.error(f"Failed to list systems: {e}")
            raise RuntimeError(f"System listing failed: {e}") from e

    def delete_system(self, project_id: str, system_uri: str) -> bool:
        """
        Delete system instance from RDF graph.

        Args:
            project_id: Unique project identifier
            system_uri: System URI to delete

        Returns:
            True if deleted, False if not found
        """
        logger.info(f"Deleting system: {system_uri}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            uri_ref = URIRef(system_uri)
            triples_to_remove = list(model.graph.triples((uri_ref, None, None)))

            if not triples_to_remove:
                logger.warning(f"System not found for deletion: {system_uri}")
                return False

            with self.adapter.transaction():
                for triple in triples_to_remove:
                    model.graph.remove(triple)

            logger.info(f"System deleted: {system_uri} ({len(triples_to_remove)} triples removed)")
            return True

        except Exception as e:
            logger.error(f"Failed to delete system: {e}")
            raise RuntimeError(f"System deletion failed: {e}") from e
