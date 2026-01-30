"""BuildingMOTIF SDK adapter for ASHRAE 223P operations."""
from contextlib import contextmanager
from pathlib import Path
from typing import Callable, Generator, TypedDict

from buildingmotif import BuildingMOTIF, get_building_motif
from buildingmotif.database.errors import TemplateNotFound
from buildingmotif.dataclasses import Library, Model, Template
from buildingmotif.dataclasses import ShapeCollection
from loguru import logger
from rdflib import Graph, Namespace, URIRef, Literal
from sqlalchemy.exc import MultipleResultsFound, NoResultFound

from src.config.settings import Settings, get_settings

from .semantics_adapter_protocol import (
    ModelHandle,
    QueryResult,
    RDFTriple,
    TemplateInfo,
    TriplePattern,
    ValidationResult,
)
from .template_types import TemplateType


class TemplateMetadata(TypedDict):
    """Template metadata structure (legacy, prefer TemplateInfo)."""

    name: str
    dependencies: list[str]
    triple_count: int

class BuildingMOTIFAdapter:
    """Adapter for BuildingMOTIF SDK integration."""

    _instance: "BuildingMOTIFAdapter | None" = None

    @classmethod
    def get_instance(
        cls, db_path: str | None = None, settings: Settings | None = None
    ) -> "BuildingMOTIFAdapter":
        """
        Get singleton instance of BuildingMOTIF adapter.

        Lazy initialization - creates instance on first call,
        returns cached instance on subsequent calls.

        Args:
            db_path: Database path (optional, defaults to settings.buildingmotif_db_path).
                     Should only be overridden in tests. Production code should use Settings.
            settings: Settings instance (optional, uses get_settings() if not provided)

        Returns:
            Singleton BuildingMOTIFAdapter instance
        """
        if cls._instance is None:
            if settings is None:
                settings = get_settings()

            if db_path is None:
                db_path = settings.buildingmotif_db_path

            cls._instance = cls(db_path, settings)
        return cls._instance

    def __init__(self, db_path: str, settings: Settings | None = None) -> None:
        """
        Initialize BuildingMOTIF SDK with SQLite persistence.

        Args:
            db_path: Path to SQLite database for RDF storage (required).
                     Use settings.buildingmotif_db_path for production.
            settings: Settings instance (optional, uses get_settings() if not provided)
        """
        if settings is None:
            settings = get_settings()

        self._settings = settings
        db_file = Path(db_path)
        db_file.parent.mkdir(parents=True, exist_ok=True)

        connection_string = f"sqlite:///{db_path}?check_same_thread=False"
        self._bm = BuildingMOTIF(connection_string, shacl_engine="topquadrant", log_level=20)

        self._configure_sqlite_for_concurrency()

        self._bm.setup_tables()

        try:
            bm_instance = get_building_motif()
            if bm_instance is not self._bm:
                logger.warning("Multiple BuildingMOTIF instances detected")
        except Exception:
            logger.debug("BuildingMOTIF global instance not yet initialized")

        self._nrel_lib: Library | None = None
        self._unit_lib: Library | None = None  # Used when should_use_qudt_all=False
        self._quantitykind_lib: Library | None = None  # Used when should_use_qudt_all=False
        self._qudt_lib: Library | None = None  # Used when should_use_qudt_all=True
        self._223p_lib: Library | None = None

        # Cached shapes (lazy loaded on first validation)
        self._223p_shapes: ShapeCollection | None = None
        self._unit_shapes: ShapeCollection | None = None
        self._qk_shapes: ShapeCollection | None = None

        self._load_nrel_templates()
        self._load_ontology_libraries()

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

    def _load_ontology_libraries(self) -> None:
        """Load 223P and QUDT ontology libraries (mode controlled by settings)."""
        # Skip loading ontology libraries if validation is disabled
        if not self._settings.enable_validation:
            logger.info("SHACL validation disabled - skipping ontology library loading")
            return

        try:
            s223_path = Path(self._settings.buildingmotif_223p_path)

            if not s223_path.exists():
                raise FileNotFoundError(f"223P ontology not found: {s223_path}")

            self._223p_lib = Library.load(ontology_graph=str(s223_path), overwrite=False, infer_templates=False)
            logger.info(f"223P library loaded from: {s223_path}")

            # Load QUDT based on flag
            if self._settings.should_use_qudt_all:
                # Mode 1: Combined qudt-all.ttl (slower init, fewer import warnings)
                qudt_path = Path(self._settings.buildingmotif_qudt_path)
                if not qudt_path.exists():
                    raise FileNotFoundError(f"QUDT ontology not found: {qudt_path}")

                self._qudt_lib = Library.load(ontology_graph=str(qudt_path), overwrite=False, infer_templates=False)
                logger.info(f"QUDT library (combined) loaded from: {qudt_path}")
            else:
                # Mode 2: Separate unit/quantitykind files (faster init, more import warnings)
                unit_path = Path(self._settings.buildingmotif_unit_path)
                qk_path = Path(self._settings.buildingmotif_quantity_kind_path)

                if not unit_path.exists():
                    raise FileNotFoundError(f"Unit ontology not found: {unit_path}")
                if not qk_path.exists():
                    raise FileNotFoundError(f"QuantityKind ontology not found: {qk_path}")

                self._unit_lib = Library.load(ontology_graph=str(unit_path), overwrite=False, infer_templates=False)
                self._quantitykind_lib = Library.load(ontology_graph=str(qk_path), overwrite=False, infer_templates=False)
                logger.info(f"Unit library loaded from: {unit_path}")
                logger.info(f"QuantityKind library loaded from: {qk_path}")

        except Exception as e:
            logger.error(f"Failed to load ontology libraries: {e}")
            raise RuntimeError(f"Failed to load ontology libraries: {e}") from e

    def _configure_sqlite_for_concurrency(self) -> None:
        """Configure SQLite for concurrent access via WAL mode."""
        try:
            from sqlalchemy import text

            with self._bm.engine.connect() as conn:
                result = conn.execute(text("PRAGMA journal_mode=WAL"))
                journal_mode = result.fetchone()[0]
                logger.info(f"SQLite journal mode: {journal_mode}")

        except Exception as e:
            logger.warning(f"Failed to configure SQLite WAL mode: {e}")

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

    def get_unit_library(self) -> Library:
        """
        Get loaded QUDT unit library (only available when should_use_qudt_all=False).

        Returns:
            Library instance with unit ontology

        Raises:
            RuntimeError: If library not loaded
        """
        if self._unit_lib is None:
            raise RuntimeError("Unit library not loaded (should_use_qudt_all may be True)")
        return self._unit_lib

    def get_quantitykind_library(self) -> Library:
        """
        Get loaded QUDT quantitykind library (only available when should_use_qudt_all=False).

        Returns:
            Library instance with quantitykind ontology

        Raises:
            RuntimeError: If library not loaded
        """
        if self._quantitykind_lib is None:
            raise RuntimeError("QuantityKind library not loaded (should_use_qudt_all may be True)")
        return self._quantitykind_lib

    def get_223p_library(self) -> Library:
        """
        Get loaded 223P ontology library.

        Returns:
            Library instance with 223P ontology

        Raises:
            RuntimeError: If library not loaded
        """
        if self._223p_lib is None:
            raise RuntimeError("223P library not loaded")
        return self._223p_lib

    def get_qudt_library(self) -> Library:
        """
        Get loaded QUDT ontology library (combined units + quantitykinds).

        Returns:
            Library instance with QUDT ontology

        Raises:
            RuntimeError: If library not loaded
        """
        if self._qudt_lib is None:
            raise RuntimeError("QUDT library not loaded")
        return self._qudt_lib

    def get_223p_shapes(self) -> ShapeCollection:
        """
        Get 223P SHACL shape collection for validation (lazy loaded).

        Returns:
            ShapeCollection with 223P validation shapes

        Raises:
            RuntimeError: If validation is disabled or library not loaded
        """
        if not self._settings.enable_validation:
            raise RuntimeError("SHACL validation is disabled (enable_validation=False). Enable it to use shape collections.")

        if self._223p_shapes is None:
            logger.debug("Lazy loading 223P shapes...")
            s223_lib = self.get_223p_library()
            self._223p_shapes = s223_lib.get_shape_collection()
            logger.debug(f"223P shapes loaded: {len(self._223p_shapes.graph)} triples")
        return self._223p_shapes

    def get_unit_shapes(self) -> ShapeCollection:
        """
        Get Unit SHACL shape collection for validation (lazy loaded).

        Returns:
            ShapeCollection with Unit validation shapes

        Raises:
            RuntimeError: If validation is disabled or library not loaded
        """
        if not self._settings.enable_validation:
            raise RuntimeError("SHACL validation is disabled (enable_validation=False). Enable it to use shape collections.")

        if self._unit_shapes is None:
            logger.debug("Lazy loading Unit shapes...")
            if self._settings.should_use_qudt_all:
                # Get from combined QUDT library
                qudt_lib = self.get_qudt_library()
                self._unit_shapes = qudt_lib.get_shape_collection()
            else:
                # Get from separate unit library
                unit_lib = self.get_unit_library()
                self._unit_shapes = unit_lib.get_shape_collection()
            logger.debug(f"Unit shapes loaded: {len(self._unit_shapes.graph)} triples")
        return self._unit_shapes

    def get_quantitykind_shapes(self) -> ShapeCollection:
        """
        Get QuantityKind SHACL shape collection for validation (lazy loaded).

        Returns:
            ShapeCollection with QuantityKind validation shapes

        Raises:
            RuntimeError: If validation is disabled or library not loaded
        """
        if not self._settings.enable_validation:
            raise RuntimeError("SHACL validation is disabled (enable_validation=False). Enable it to use shape collections.")

        if self._qk_shapes is None:
            logger.debug("Lazy loading QuantityKind shapes...")
            if self._settings.should_use_qudt_all:
                # Get from combined QUDT library (same as unit_shapes)
                qudt_lib = self.get_qudt_library()
                self._qk_shapes = qudt_lib.get_shape_collection()
            else:
                # Get from separate quantitykind library
                qk_lib = self.get_quantitykind_library()
                self._qk_shapes = qk_lib.get_shape_collection()
            logger.debug(f"QuantityKind shapes loaded: {len(self._qk_shapes.graph)} triples")
        return self._qk_shapes

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

    def create_model(self, namespace: str) -> ModelHandle:
        """
        Create new RDF model with unique namespace.

        Args:
            namespace: Unique namespace URI (e.g., "urn:building/project-123")

        Returns:
            ModelHandle for RDF operations
        """
        ns = Namespace(namespace)
        model = Model.create(ns)
        logger.info(f"Created model with namespace: {namespace}")
        return ModelHandle(namespace=namespace, graph=model.graph)

    def get_or_create_model(self, namespace: str) -> ModelHandle:
        """
        Get existing model or create new one with proper exception handling.

        Args:
            namespace: Unique namespace URI (e.g., "urn:project:project-123")

        Returns:
            ModelHandle for RDF operations

        Raises:
            RuntimeError: If multiple models found with same name (database integrity issue)
        """
        bm = self.get_buildingmotif_instance()

        try:
            db_model = bm.table_connection.get_db_model_by_name(namespace)
            model = Model.load(id=db_model.id)
            logger.debug(f"Loaded model: {namespace} (ID: {db_model.id}, triples: {len(model.graph)})")
            return ModelHandle(namespace=namespace, graph=model.graph)
        except NoResultFound:
            ns = Namespace(namespace)
            model = Model.create(ns)
            bm.session.commit()
            logger.info(f"Created model: {namespace} (ID: {model.id})")
            return ModelHandle(namespace=namespace, graph=model.graph)
        except MultipleResultsFound as e:
            logger.error(f"Multiple models found for: {namespace}")
            raise RuntimeError(f"Database integrity error: multiple models with name '{namespace}'") from e

    def query_model(self, model: ModelHandle, sparql_query: str) -> QueryResult:
        """
        Execute SPARQL query on RDF model.

        Args:
            model: ModelHandle to query
            sparql_query: SPARQL query string

        Returns:
            QueryResult with bindings as list of dictionaries.
            SPARQL OPTIONAL fields return None when missing.
        """
        results = model.graph.query(sparql_query)
        bindings = [
            {str(var): str(row[var]) if row[var] is not None else None for var in results.vars}
            for row in results
        ]
        logger.debug(f"Query returned {len(bindings)} results")
        return QueryResult(bindings=bindings)

    def add_graph(self, model: ModelHandle, graph: Graph) -> None:
        """
        Add RDF graph to model atomically.

        Args:
            model: Target ModelHandle
            graph: RDF graph to add
        """
        with self.atomic_context():
            for triple in graph:
                model.graph.add(triple)
        logger.debug(f"Added {len(graph)} triples to model")

    def add_triples(
        self, model: ModelHandle, triples: list[RDFTriple]
    ) -> None:
        """
        Add triples to a model atomically.

        Args:
            model: Target ModelHandle
            triples: List of RDF triples to add
        """
        with self.atomic_context():
            for triple in triples:
                model.graph.add(triple)
        logger.debug(f"Added {len(triples)} triples to model")

    def remove_triples(
        self, model: ModelHandle, patterns: list[TriplePattern]
    ) -> None:
        """
        Remove triples from a model atomically.

        Args:
            model: Target ModelHandle
            patterns: List of triple patterns to remove. Use None as wildcard
                      to match any value in that position.
                      Example: (subject, None, None) removes ALL triples with that subject.
        """
        with self.atomic_context():
            for pattern in patterns:
                model.graph.remove(pattern)
        logger.debug(f"Removed triples matching {len(patterns)} patterns from model")

    def atomic_update(
        self,
        model: ModelHandle,
        add: list[RDFTriple] | None = None,
        remove: list[TriplePattern] | None = None,
        validate_fn: Callable[[ModelHandle], None] | None = None,
    ) -> None:
        """
        Apply graph changes atomically with optional validation.

        Removes are applied before adds. If validate_fn is provided,
        it's called after changes but before commit. If validate_fn
        raises an exception, all changes are rolled back.

        Args:
            model: Target ModelHandle
            add: Triples to add (no wildcards allowed)
            remove: Triple patterns to remove (None = wildcard matching any value)
            validate_fn: Optional validation function called before commit.
                         Should raise exception if validation fails to trigger rollback.
        """
        with self.atomic_context():
            if remove:
                for pattern in remove:
                    model.graph.remove(pattern)
                logger.debug(f"Removed triples matching {len(remove)} patterns")

            if add:
                for triple in add:
                    model.graph.add(triple)
                logger.debug(f"Added {len(add)} triples")

            if validate_fn:
                validate_fn(model)

    def serialize_model(self, model: ModelHandle, format: str = "turtle") -> str:
        """
        Serialize model to string.

        Args:
            model: ModelHandle to serialize
            format: Output format (turtle, xml, json-ld, etc.)

        Returns:
            Serialized RDF as string
        """
        output = model.graph.serialize(format=format)
        logger.debug(f"Serialized model to {format}: {len(output)} chars")
        return output

    def validate_model(self, model: ModelHandle) -> ValidationResult:
        """
        Validate model against 223P SHACL shapes.

        Args:
            model: ModelHandle to validate

        Returns:
            ValidationResult with conforms status and report
        """
        try:
            shapes = self.get_223p_shapes()
            from pyshacl import validate

            conforms, _, results_text = validate(
                data_graph=model.graph,
                shacl_graph=shapes.graph,
            )
            return ValidationResult(conforms=conforms, report=results_text)
        except RuntimeError as e:
            return ValidationResult(conforms=False, report=str(e))

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
        inlined_template = template.inline_dependencies()
        logger.debug(f"Inlined dependencies for template: {template_name}")
        return inlined_template

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

    def get_template_info(self, template_name: str) -> TemplateInfo:
        """
        Get template metadata by name (protocol method).

        Args:
            template_name: Template name as string

        Returns:
            TemplateInfo with name, dependencies, and triple_count

        Raises:
            KeyError: If template not found
        """
        library = self.get_nrel_library()
        try:
            template = library.get_template_by_name(template_name)
        except (KeyError, TemplateNotFound) as e:
            raise KeyError(f"Template not found: {template_name}") from e

        dependencies = template.get_dependencies()
        dependency_names = sorted([str(dep.dependency_template_name) for dep in dependencies])
        dependency_names.append(template_name)
        dependency_names = sorted(list(set(dependency_names)))

        inlined_template = template.inline_dependencies()

        logger.debug(f"Template info for {template_name}: {len(dependency_names)} deps, {len(inlined_template.body)} triples")
        return TemplateInfo(
            name=template_name,
            dependencies=dependency_names,
            triple_count=len(inlined_template.body),
        )

    def get_template_metadata(self, template_name: TemplateType) -> TemplateMetadata:
        """
        Get comprehensive template metadata including dependencies (legacy method).

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
        inlined_template = template.inline_dependencies()

        metadata: TemplateMetadata = {
            "name": template_name.value,
            "dependencies": dependencies,
            "triple_count": len(inlined_template.body),
        }
        logger.debug(f"Extracted metadata for {template_name}: {len(dependencies)} deps, {len(inlined_template.body)} triples")
        return metadata

    def get_buildingmotif_instance(self) -> BuildingMOTIF:
        """
        Get underlying BuildingMOTIF instance.

        Returns:
            BuildingMOTIF instance
        """
        return self._bm

    @contextmanager
    def atomic_context(self) -> Generator[None, None, None]:
        """
        Context manager for complex atomic operations.

        Use when you need fine-grained control over multiple graph changes.
        All changes commit on success, rollback on exception.

        For simpler cases, prefer atomic_update() which handles
        add/remove/validate in a single call.

        Example:
            with adapter.atomic_context():
                model.graph.add(triple1)
                model.graph.remove(pattern)
                # Commits on successful exit
                # Rolls back if exception raised

        Yields:
            None

        Raises:
            Exception: Re-raises any exception after rollback
        """
        try:
            yield
            self._bm.session.commit()
            logger.debug("Transaction committed successfully")
        except Exception as e:
            self._bm.session.rollback()
            logger.error(f"Transaction rolled back: {e}")
            raise
