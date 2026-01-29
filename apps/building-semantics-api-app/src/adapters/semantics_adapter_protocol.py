"""Protocol defining the contract for semantics adapters."""

from dataclasses import dataclass
from typing import Protocol

from rdflib import Graph


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
        self, model: ModelHandle, triples: list[tuple[str, str, str]]
    ) -> None:
        """Add triples to a model."""
        ...

    def add_graph(self, model: ModelHandle, graph: Graph) -> None:
        """Add RDF graph to model."""
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
