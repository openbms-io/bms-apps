"""Domain model for ASHRAE 223P mappings with transaction management."""

from contextlib import contextmanager
from typing import Generator, TypedDict

from loguru import logger
from rdflib import Graph, Literal, Namespace, RDF, URIRef

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..dto.mappings_dto import SemanticMappingDTO
from ..mappers.mapping_mapper import (
    create_equipment_uri,
    create_project_uri,
    to_equipment_rdf_triples,
    to_project_relationship_triples,
)

# RDF namespaces
S223 = Namespace("http://data.ashrae.org/standard223#")
BACNET = Namespace("http://data.ashrae.org/bacnet/2020#")
BMS = Namespace("urn:bms:")
DCTERMS = Namespace("http://purl.org/dc/terms/")


class CoreMappingData(TypedDict):
    """Core mapping data structure from SPARQL query."""
    equipment: str
    point_id: str
    equipment_type_id: str
    device_type_id: str
    property_id: str
    physical_space_id: str | None


class MappingsModel:
    """
    Domain model for semantic mappings with transaction support.

    Responsibilities:
    - Transaction boundaries (atomic operations)
    - Business rules validation
    - Aggregate root for mappings domain
    - All mappings-specific SPARQL queries and RDF operations
    """

    def __init__(self, adapter: BuildingMOTIFAdapter) -> None:
        """
        Initialize mappings model.

        Args:
            adapter: BuildingMOTIF adapter instance
        """
        self.adapter = adapter

    @contextmanager
    def transaction(self) -> Generator[None, None, None]:
        """
        Context manager for atomic mapping operations.

        Provides transaction semantics:
        - All operations succeed together, or
        - All operations rollback together

        Usage:
            with model.transaction():
                model._clear_all_triples(model)
                model._add_triples(model, triples)
                # Commits on success, rolls back on exception

        Yields:
            None

        Raises:
            Exception: Re-raises any exception after rollback
        """
        bm = self.adapter.get_buildingmotif_instance()

        # Start nested transaction (savepoint)
        savepoint = bm.session.begin_nested()

        try:
            yield  # Execute operations inside 'with' block

            # SUCCESS: Commit all operations
            bm.session.commit()
            logger.debug("Mapping transaction committed successfully")

        except Exception as e:
            # ERROR: Rollback to savepoint
            savepoint.rollback()
            bm.session.rollback()
            logger.error(f"Mapping transaction rolled back: {e}")
            raise

    def get_all_mappings(
        self, project_id: str
    ) -> dict[str, SemanticMappingDTO]:
        """
        Get all mappings for project (read operation - no transaction needed).

        Args:
            project_id: Project identifier

        Returns:
            Dictionary of mappings keyed by point ID
        """
        model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

        # Commit any pending database operations
        bm = self.adapter.get_buildingmotif_instance()
        bm.session.commit()

        # Get project graph with mappings-specific SPARQL
        graph = self._get_project_graph(project_id, model)

        # Extract mappings from graph
        return self._extract_mappings_from_graph(graph)

    def replace_all_mappings(
        self,
        project_id: str,
        mappings: dict[str, SemanticMappingDTO],
    ) -> None:
        """
        Replace all mappings for project (atomic operation).

        Uses transaction to ensure all-or-nothing semantics:
        1. Clear existing mappings
        2. Create project instance
        3. Add new mappings
        4. Commit (or rollback on error)

        Args:
            project_id: Project identifier
            mappings: New mappings to save

        Raises:
            Exception: If any operation fails (after rollback)
        """
        model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

        # Commit any pending database operations before transaction
        bm = self.adapter.get_buildingmotif_instance()
        bm.session.commit()

        # ATOMIC TRANSACTION: All-or-nothing
        with self.transaction():
            # Step 1: Clear all existing triples (simple reset)
            self._clear_all_triples(model)

            # Step 2: Create project instance
            self._create_project_instance(project_id, model)

            # Step 3: Add new mappings
            all_triples = self._prepare_mapping_triples(project_id, mappings)
            self._add_triples(model, all_triples)

            # Transaction auto-commits savepoint if successful

        # Final commit to persist all graph changes to database
        bm.session.commit()

        logger.info(f"Replaced {len(mappings)} mappings for project: {project_id}")

    def _get_equipment_triples(self, project_id: str, model) -> Graph:
        """
        Get equipment instance triples from project.

        Args:
            project_id: Project identifier
            model: RDF model to query

        Returns:
            RDF graph with equipment triples
        """
        project_uri = f"{BMS}Project:{project_id}"

        query = f"""
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bms: <urn:bms:>

            CONSTRUCT {{
                ?equipment ?equipmentP ?equipmentO .
            }}
            WHERE {{
                <{project_uri}> s223:contains ?equipment .
                ?equipment ?equipmentP ?equipmentO .
            }}
        """

        result_graph = model.graph.query(query).graph
        logger.debug(f"Retrieved {len(result_graph)} equipment triples for project: {project_id}")
        return result_graph

    def _get_device_triples(self, project_id: str, model) -> Graph:
        """
        Get device instance triples from project equipment.

        Args:
            project_id: Project identifier
            model: RDF model to query

        Returns:
            RDF graph with device triples
        """
        project_uri = f"{BMS}Project:{project_id}"

        query = f"""
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bms: <urn:bms:>

            CONSTRUCT {{
                ?device ?deviceP ?deviceO .
            }}
            WHERE {{
                <{project_uri}> s223:contains ?equipment .
                ?equipment s223:contains ?device .
                ?device ?deviceP ?deviceO .
            }}
        """

        result_graph = model.graph.query(query).graph
        logger.debug(f"Retrieved {len(result_graph)} device triples for project: {project_id}")
        return result_graph

    def _get_property_triples(self, project_id: str, model) -> Graph:
        """
        Get property instance triples from project devices.

        Args:
            project_id: Project identifier
            model: RDF model to query

        Returns:
            RDF graph with property triples
        """
        project_uri = f"{BMS}Project:{project_id}"

        query = f"""
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bms: <urn:bms:>

            CONSTRUCT {{
                ?property ?propertyP ?propertyO .
            }}
            WHERE {{
                <{project_uri}> s223:contains ?equipment .
                ?equipment s223:contains ?device .
                ?device s223:hasProperty ?property .
                ?property ?propertyP ?propertyO .
            }}
        """

        result_graph = model.graph.query(query).graph
        logger.debug(f"Retrieved {len(result_graph)} property triples for project: {project_id}")
        return result_graph

    def _get_bacnet_reference_triples(self, project_id: str, model) -> Graph:
        """
        Get BACnet external reference triples from project equipment.

        Args:
            project_id: Project identifier
            model: RDF model to query

        Returns:
            RDF graph with BACnet reference triples
        """
        project_uri = f"{BMS}Project:{project_id}"

        query = f"""
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bms: <urn:bms:>

            CONSTRUCT {{
                ?bacnetRef ?bacnetP ?bacnetO .
            }}
            WHERE {{
                <{project_uri}> s223:contains ?equipment .
                ?equipment s223:hasExternalReference ?bacnetRef .
                ?bacnetRef ?bacnetP ?bacnetO .
            }}
        """

        result_graph = model.graph.query(query).graph
        logger.debug(f"Retrieved {len(result_graph)} BACnet reference triples for project: {project_id}")
        return result_graph

    def _get_project_graph(self, project_id: str, model) -> Graph:
        """
        Get RDF graph for all equipment instances in project.

        Orchestrates focused SPARQL queries to extract:
        - Equipment instances
        - Device instances
        - Property instances
        - BACnet reference instances

        MOVED FROM: BuildingMOTIFAdapter.get_project_mappings()

        Args:
            project_id: Project identifier
            model: RDF model to query

        Returns:
            RDF graph with all equipment instances for project
        """
        model_size = len(model.graph)
        logger.debug(f"Querying model with {model_size} total triples for project: {project_id}")

        combined_graph = Graph()

        equipment_graph = self._get_equipment_triples(project_id, model)
        combined_graph += equipment_graph

        device_graph = self._get_device_triples(project_id, model)
        combined_graph += device_graph

        property_graph = self._get_property_triples(project_id, model)
        combined_graph += property_graph

        bacnet_graph = self._get_bacnet_reference_triples(project_id, model)
        combined_graph += bacnet_graph

        logger.debug(f"Retrieved {len(combined_graph)} total triples for project: {project_id}")
        return combined_graph

    def _create_project_instance(self, project_id: str, model) -> None:
        """
        Create project instance in RDF model.

        Adds bms:Project triples with dcterms:identifier.

        MOVED FROM: BuildingMOTIFAdapter.create_project_instance()

        Args:
            project_id: Project identifier
            model: RDF model to modify
        """
        project_uri = URIRef(f"{BMS}Project:{project_id}")

        triples = [
            (project_uri, RDF.type, BMS.Project),
            (project_uri, DCTERMS.identifier, Literal(project_id)),
        ]

        for triple in triples:
            model.graph.add(triple)

        logger.debug(f"Created project instance: {project_id}")

    def _clear_all_triples(self, model) -> None:
        """
        Clear all triples from model (simple reset).

        Since each project has isolated model, safe to clear everything.

        Args:
            model: RDF model to clear
        """
        model.graph.remove((None, None, None))
        logger.debug("Cleared all triples from model")

    def _add_triples(self, model, triples: list[tuple]) -> None:
        """
        Add RDF triples to model graph (bulk operation).

        Args:
            model: RDF model to modify
            triples: List of (subject, predicate, object) triples to add
        """
        for triple in triples:
            model.graph.add(triple)

        logger.debug(f"Added {len(triples)} triples to model")

    def _prepare_mapping_triples(
        self,
        project_id: str,
        mappings: dict[str, SemanticMappingDTO],
    ) -> list[tuple]:
        """
        Convert mappings DTOs to RDF triples (bulk preparation).

        Args:
            project_id: Project identifier
            mappings: Mappings to convert

        Returns:
            List of all RDF triples (equipment + project relationships)
        """
        all_triples = []
        equipment_uris = []

        logger.debug(f"Converting {len(mappings)} mappings to RDF triples")
        for point_id, mapping in mappings.items():
            logger.debug(f"Converting mapping for point_id: {point_id}")
            equipment_uri = create_equipment_uri(point_id)
            equipment_uris.append(equipment_uri)

            try:
                # Convert DTO to triples (requires adapter for template lookups)
                equipment_triples = to_equipment_rdf_triples(
                    equipment_uri, point_id, mapping, self.adapter
                )
                logger.debug(f"Generated {len(equipment_triples)} triples for {point_id}")
                all_triples.extend(equipment_triples)
            except Exception as e:
                logger.error(f"Failed to convert mapping for {point_id}: {e}", exc_info=True)
                raise

        # Add project relationship triples
        project_uri = create_project_uri(project_id)
        project_triples = to_project_relationship_triples(project_uri, equipment_uris)
        all_triples.extend(project_triples)

        logger.debug(f"Prepared {len(all_triples)} total triples for {len(mappings)} mappings")
        return all_triples

    def _query_core_mappings(self, graph: Graph) -> list[CoreMappingData]:
        """
        Query core mapping data without aggregation.

        Args:
            graph: RDF graph to query

        Returns:
            List of core mapping data dictionaries
        """
        query_result = graph.query(
            """
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bacnet: <http://data.ashrae.org/bacnet/2020#>
            PREFIX dcterms: <http://purl.org/dc/terms/>
            PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
            PREFIX bms: <urn:bms:>

            SELECT ?equipment ?pointId ?equipmentTemplateId ?deviceTemplateId ?propertyTemplateId ?physicalSpace
            WHERE {
                ?equipment bms:hasTemplateId ?equipmentTemplateId ;
                           s223:contains ?device ;
                           s223:hasExternalReference ?bacnetRef .

                ?device bms:hasTemplateId ?deviceTemplateId ;
                        s223:hasProperty ?property .

                ?property bms:hasTemplateId ?propertyTemplateId .

                ?bacnetRef rdf:type s223:BACnetExternalReference ;
                           dcterms:identifier ?pointId .

                OPTIONAL { ?equipment s223:locatedIn ?physicalSpace . }
            }
            """
        )

        core_mappings = []
        for row in query_result:
            core_mappings.append({
                "equipment": str(row.equipment),
                "point_id": str(row.pointId),
                "equipment_type_id": str(row.equipmentTemplateId),
                "device_type_id": str(row.deviceTemplateId),
                "property_id": str(row.propertyTemplateId),
                "physical_space_id": str(row.physicalSpace) if row.physicalSpace else None,
            })

        logger.debug(f"Queried {len(core_mappings)} core mappings")
        return core_mappings

    def _query_domain_spaces(self, graph: Graph) -> dict[str, list[str]]:
        """
        Query domain space relationships for equipment.

        Args:
            graph: RDF graph to query

        Returns:
            Dictionary mapping equipment URI to sorted list of domain space URIs
        """
        query_result = graph.query(
            """
            PREFIX s223: <http://data.ashrae.org/standard223#>
            PREFIX bms: <urn:bms:>

            SELECT ?equipment ?domainSpace
            WHERE {
                ?equipment s223:hasDomain ?domainSpace .
            }
            """
        )

        domain_map: dict[str, list[str]] = {}
        for row in query_result:
            equipment_uri = str(row.equipment)
            domain_space = str(row.domainSpace)

            if equipment_uri not in domain_map:
                domain_map[equipment_uri] = []

            domain_map[equipment_uri].append(domain_space)

        for equipment_uri in domain_map:
            domain_map[equipment_uri] = sorted(domain_map[equipment_uri])

        logger.debug(f"Queried domain spaces for {len(domain_map)} equipment instances")
        return domain_map

    def _extract_mappings_from_graph(
        self, graph: Graph
    ) -> dict[str, SemanticMappingDTO]:
        """
        Extract mappings from RDF graph using focused SPARQL queries.

        Orchestrates:
        - Core mapping data query (no aggregation)
        - Domain space relationships query

        Args:
            graph: RDF graph to query

        Returns:
            Dictionary of mappings keyed by point ID
        """
        core_mappings = self._query_core_mappings(graph)
        domain_map = self._query_domain_spaces(graph)

        mappings_dict: dict[str, SemanticMappingDTO] = {}

        for core in core_mappings:
            point_id = core["point_id"]
            equipment_uri = core["equipment"]

            domain_space_ids = domain_map.get(equipment_uri)

            mapping = SemanticMappingDTO(
                equipment_type_id=core["equipment_type_id"],
                device_type_id=core["device_type_id"],
                property_id=core["property_id"],
                physical_space_id=core["physical_space_id"],
                domain_space_ids=domain_space_ids,
            )

            mappings_dict[point_id] = mapping

        logger.debug(f"Extracted {len(mappings_dict)} mappings from graph")
        return mappings_dict
