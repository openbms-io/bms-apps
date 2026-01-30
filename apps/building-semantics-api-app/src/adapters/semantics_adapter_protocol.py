"""Protocol defining the contract for semantics adapters."""

from contextlib import contextmanager
from dataclasses import dataclass
from typing import Callable, Generator, Protocol

from rdflib import BNode, Graph, Literal, URIRef


# Type aliases for RDF triples
# -----------------------------
# RDFTriple: For adding triples - all components must have values (no wildcards)
RDFTriple = tuple[URIRef | BNode, URIRef, URIRef | Literal | BNode]

# TriplePattern: For removing triples - allows None as wildcard to match any value
# Example: (subject, None, None) removes ALL triples with that subject
# Example: (subject, predicate, None) removes all triples with that subject+predicate
TriplePattern = tuple[
    URIRef | BNode | None,
    URIRef | None,
    URIRef | Literal | BNode | None,
]


@dataclass
class TemplateInfo:
    """Template metadata returned by adapters."""

    name: str
    dependencies: list[str]
    triple_count: int


@dataclass
class ModelHandle:
    """Handle to an RDF model managed by the adapter."""

    namespace: str
    graph: Graph


@dataclass
class QueryResult:
    """SPARQL query result from adapter."""

    bindings: list[dict[str, str | None]]


@dataclass
class ValidationResult:
    """SHACL validation result from adapter."""

    conforms: bool
    report: str


class SemanticsAdapterProtocol(Protocol):
    """Protocol defining the contract for semantics adapters.

    Both BuildingMOTIFAdapter and BsitBobAdapter implement this protocol,
    allowing them to be used interchangeably via the factory.
    """

    @classmethod
    def get_instance(cls, db_path: str | None = None) -> "SemanticsAdapterProtocol":
        """Get singleton instance of the adapter."""
        ...

    def list_templates(self) -> list[str]:
        """List all available template names."""
        ...

    def get_template_info(self, template_name: str) -> TemplateInfo:
        """Get template metadata by name."""
        ...

    def create_model(self, namespace: str) -> ModelHandle:
        """Create a new RDF model with given namespace."""
        ...

    def get_or_create_model(self, namespace: str) -> ModelHandle:
        """Get existing model or create new one."""
        ...

    def add_triples(
        self, model: ModelHandle, triples: list[RDFTriple]
    ) -> None:
        """Add triples to a model atomically."""
        ...

    def remove_triples(self, model: ModelHandle, patterns: list[TriplePattern]) -> None:
        """
        Remove triples from a model atomically.

        Args:
            model: Target ModelHandle
            patterns: List of triple patterns to remove. Use None as wildcard
                      to match any value in that position.
                      Example: (subject, None, None) removes ALL triples with that subject.
        """
        ...

    def add_graph(self, model: ModelHandle, graph: Graph) -> None:
        """Add RDF graph to model atomically."""
        ...

    def query_model(self, model: ModelHandle, sparql: str) -> QueryResult:
        """Execute SPARQL query on model."""
        ...

    def serialize_model(self, model: ModelHandle, format: str = "turtle") -> str:
        """Serialize model to string."""
        ...

    def validate_model(self, model: ModelHandle) -> ValidationResult:
        """Validate model against SHACL shapes."""
        ...

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
        """
        ...

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
        ...
