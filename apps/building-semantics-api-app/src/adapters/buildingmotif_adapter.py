"""BuildingMOTIF SDK adapter for ASHRAE 223P operations."""
from pathlib import Path
from typing import Any

from buildingmotif import BuildingMOTIF, get_building_motif
from buildingmotif.database.errors import TemplateNotFound
from buildingmotif.dataclasses import Library, Model, Template
from loguru import logger
from rdflib import Graph, Namespace
from sqlalchemy.exc import MultipleResultsFound, NoResultFound
from src.config.settings import Settings, get_settings

from .template_types import TemplateType

class BuildingMOTIFAdapter:
    """Adapter for BuildingMOTIF SDK integration."""

    _instance: "BuildingMOTIFAdapter | None" = None

    @classmethod
    def get_instance(
        cls, db_path: str = "data/buildingmotif.db", settings: "Settings | None" = None
    ) -> "BuildingMOTIFAdapter":
        """
        Get singleton instance of BuildingMOTIF adapter.

        Lazy initialization - creates instance on first call,
        returns cached instance on subsequent calls.

        Args:
            db_path: Database path (only used on first initialization)
            settings: Settings instance (optional, uses get_settings() if not provided)

        Returns:
            Singleton BuildingMOTIFAdapter instance
        """
        if cls._instance is None:
            cls._instance = cls(db_path, settings)
        return cls._instance

    def __init__(self, db_path: str = "data/buildingmotif.db", settings: "Settings | None" = None) -> None:
        """
        Initialize BuildingMOTIF SDK with SQLite persistence.

        Args:
            db_path: Path to SQLite database for RDF storage
            settings: Settings instance (optional, uses get_settings() if not provided)
        """

        if settings is None:
            settings = get_settings()

        self._settings = settings
        db_file = Path(db_path)
        db_file.parent.mkdir(parents=True, exist_ok=True)

        connection_string = f"sqlite:///{db_path}"
        self._bm = BuildingMOTIF(connection_string)
        self._bm.setup_tables()

        try:
            bm_instance = get_building_motif()
            if bm_instance is not self._bm:
                logger.warning("Multiple BuildingMOTIF instances detected")
        except Exception:
            logger.debug("BuildingMOTIF global instance not yet initialized")

        self._nrel_lib: Library | None = None
        self._load_nrel_templates()

        logger.info(f"BuildingMOTIF initialized with database: {db_path}")

    def _load_nrel_templates(self) -> None:
        """Load NREL ASHRAE 223P template library from local directory."""
        try:
            template_dir = Path(self._settings.buildingmotif_templates_path)

            if not template_dir.exists():
                raise FileNotFoundError(f"NREL template directory not found: {template_dir}")

            self._nrel_lib = Library.load(directory=str(template_dir))
            logger.info(f"NREL template library loaded from: {template_dir}")
        except Exception as e:
            logger.error(f"Failed to load NREL template library: {e}")
            raise RuntimeError(f"Failed to load NREL template library: {e}") from e

    def get_nrel_library(self) -> Library:
        """
        Get loaded NREL ASHRAE 223P template library.

        Returns:
            Library instance with NREL templates

        Raises:
            RuntimeError: If library not loaded
        """
        if self._nrel_lib is None:
            raise RuntimeError("NREL template library not loaded")
        return self._nrel_lib

    def get_template_by_name(self, template_name: TemplateType) -> Template:
        """
        Get template from NREL template library by name.

        Args:
            template_name: Template from DeviceTemplate, SystemTemplate, or PropertyTemplate enum

        Returns:
            Template instance

        Raises:
            KeyError: If template not found
        """
        library = self.get_nrel_library()
        try:
            template = library.get_template_by_name(template_name.value)
            logger.debug(f"Retrieved template: {template_name}")
            return template
        except (KeyError, TemplateNotFound) as e:
            logger.warning(f"Template not found: {template_name}")
            raise KeyError(f"Template not found: {template_name}") from e

    def list_templates(self) -> list[str]:
        """
        List all available template names in NREL template library.

        Returns:
            List of template names
        """
        library = self.get_nrel_library()
        templates = library.get_templates()
        template_names = [str(t.name) for t in templates]
        logger.debug(f"Found {len(template_names)} templates")
        return template_names

    def create_model(self, namespace: str) -> Model:
        """
        Create new RDF model with unique namespace.

        Args:
            namespace: Unique namespace URI (e.g., "urn:building/project-123")

        Returns:
            Model instance for RDF operations
        """
        ns = Namespace(namespace)
        model = Model.create(ns)
        logger.info(f"Created model with namespace: {namespace}")
        return model

    def get_or_create_model(self, namespace: str) -> Model:
        """
        Get existing model or create new one with proper exception handling.

        Args:
            namespace: Unique namespace URI (e.g., "urn:project:project-123")

        Returns:
            Model instance for RDF operations

        Raises:
            RuntimeError: If multiple models found with same name (database integrity issue)
        """
        bm = self.get_buildingmotif_instance()

        try:
            db_model = bm.table_connection.get_db_model_by_name(namespace)
            model = Model.load(id=db_model.id)
            logger.debug(f"Loaded model: {namespace} (ID: {db_model.id}, triples: {len(model.graph)})")
            return model
        except NoResultFound:
            ns = Namespace(namespace)
            model = Model.create(ns)
            bm.session.commit()
            logger.info(f"Created model: {namespace} (ID: {model.id})")
            return model
        except MultipleResultsFound as e:
            logger.error(f"Multiple models found for: {namespace}")
            raise RuntimeError(f"Database integrity error: multiple models with name '{namespace}'") from e

    def query_model(self, model: Model, sparql_query: str) -> list[dict[str, str]]:
        """
        Execute SPARQL query on RDF model.

        Args:
            model: Model to query
            sparql_query: SPARQL query string

        Returns:
            Query results as list of dictionaries with string values
        """
        results = model.graph.query(sparql_query)
        result_list = [
            {str(var): str(row[var]) for var in results.vars} for row in results
        ]
        logger.debug(f"Query returned {len(result_list)} results")
        return result_list

    def add_graph(self, model: Model, graph: Graph) -> None:
        """
        Add RDF graph to model.

        Args:
            model: Target model
            graph: RDF graph to add
        """
        model.add_graph(graph)
        logger.debug(f"Added {len(graph)} triples to model")

    def get_template_with_dependencies(self, template_name: TemplateType) -> Template:
        """
        Get template with all dependencies inlined into its graph.

        Args:
            template_name: Template from DeviceTemplate, SystemTemplate, or PropertyTemplate enum

        Returns:
            Template instance with inlined dependencies

        Raises:
            KeyError: If template not found
        """
        template = self.get_template_by_name(template_name)
        template.inline_dependencies()
        logger.debug(f"Inlined dependencies for template: {template_name}")
        return template

    def get_template_dependencies(self, template_name: TemplateType) -> list[str]:
        """
        Extract list of dependency template names from template.

        Args:
            template_name: Template from DeviceTemplate, SystemTemplate, or PropertyTemplate enum

        Returns:
            List of dependency template names (includes template itself)

        Raises:
            KeyError: If template not found
        """
        template = self.get_template_by_name(template_name)
        dependencies = template.get_dependencies()
        dependency_names = sorted([str(dep.dependency_template_name) for dep in dependencies])
        dependency_names.append(template_name.value)
        dependency_names = sorted(list(set(dependency_names)))
        logger.debug(f"Found {len(dependency_names)} dependencies for {template_name}")
        return dependency_names

    def get_template_metadata(self, template_name: TemplateType) -> dict[str, Any]:
        """
        Get comprehensive template metadata including dependencies.

        Args:
            template_name: Template from DeviceTemplate, SystemTemplate, or PropertyTemplate enum

        Returns:
            Dictionary with template metadata:
            - name: Template name
            - dependencies: List of dependency template names
            - triple_count: Number of RDF triples in expanded graph

        Raises:
            KeyError: If template not found
        """
        template = self.get_template_by_name(template_name)
        dependencies = self.get_template_dependencies(template_name)
        template.inline_dependencies()

        metadata = {
            "name": template_name.value,
            "dependencies": dependencies,
            "triple_count": len(template.body),
        }
        logger.debug(f"Extracted metadata for {template_name}: {len(dependencies)} deps, {len(template.body)} triples")
        return metadata

    def get_buildingmotif_instance(self) -> BuildingMOTIF:
        """
        Get underlying BuildingMOTIF instance.

        Returns:
            BuildingMOTIF instance
        """
        return self._bm
