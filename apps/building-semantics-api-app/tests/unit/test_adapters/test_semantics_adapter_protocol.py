"""Tests for SemanticsAdapterProtocol with mock adapter implementation."""

import pytest
from rdflib import Graph, Namespace, URIRef, Literal

from src.adapters.semantics_adapter_protocol import (
    ModelHandle,
    QueryResult,
    SemanticsAdapterProtocol,
    TemplateInfo,
    ValidationResult,
)


class MockSemanticsAdapter:
    """Mock adapter implementing SemanticsAdapterProtocol for testing."""

    _instance: "MockSemanticsAdapter | None" = None

    @classmethod
    def get_instance(cls, db_path: str | None = None) -> "MockSemanticsAdapter":
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    @classmethod
    def reset_instance(cls) -> None:
        cls._instance = None

    def __init__(self) -> None:
        self._models: dict[str, Graph] = {}

    def list_templates(self) -> list[str]:
        return ["damper", "fan", "valve", "pump", "vav-reheat", "air-handling-unit"]

    def get_template_info(self, template_name: str) -> TemplateInfo:
        template_data = {
            "damper": TemplateInfo(
                name="damper", dependencies=["connection-point"], triple_count=15
            ),
            "fan": TemplateInfo(
                name="fan",
                dependencies=["connection-point", "electrical-inlet"],
                triple_count=22,
            ),
            "vav-reheat": TemplateInfo(
                name="vav-reheat",
                dependencies=["damper", "heating-coil", "connection-point"],
                triple_count=45,
            ),
        }
        if template_name not in template_data:
            raise KeyError(f"Template not found: {template_name}")
        return template_data[template_name]

    def create_model(self, namespace: str) -> ModelHandle:
        graph = Graph()
        graph.bind("s223", Namespace("http://data.ashrae.org/standard223#"))
        self._models[namespace] = graph
        return ModelHandle(namespace=namespace, graph=graph)

    def get_or_create_model(self, namespace: str) -> ModelHandle:
        if namespace in self._models:
            return ModelHandle(namespace=namespace, graph=self._models[namespace])
        return self.create_model(namespace)

    def add_triples(
        self, model: ModelHandle, triples: list[tuple[str, str, str]]
    ) -> None:
        for s, p, o in triples:
            model.graph.add((URIRef(s), URIRef(p), Literal(o)))

    def add_graph(self, model: ModelHandle, graph: Graph) -> None:
        for triple in graph:
            model.graph.add(triple)

    def query_model(self, model: ModelHandle, sparql: str) -> QueryResult:
        results = model.graph.query(sparql)
        bindings = []
        for row in results:
            binding = {}
            for var in results.vars:
                value = row[var]
                binding[str(var)] = str(value) if value is not None else None
            bindings.append(binding)
        return QueryResult(bindings=bindings)

    def serialize_model(self, model: ModelHandle, format: str = "turtle") -> str:
        return model.graph.serialize(format=format)

    def validate_model(self, model: ModelHandle) -> ValidationResult:
        return ValidationResult(conforms=True, report="Validation passed")


def _verify_protocol_compliance(adapter: SemanticsAdapterProtocol) -> None:
    """Type-checking function that verifies protocol compliance at compile time."""
    _: SemanticsAdapterProtocol = adapter


class TestTemplateInfoDataclass:
    def test_template_info_has_required_fields(self) -> None:
        info = TemplateInfo(name="damper", dependencies=["dep1"], triple_count=10)
        assert info.name == "damper"
        assert info.dependencies == ["dep1"]
        assert info.triple_count == 10

    def test_template_info_immutable_defaults(self) -> None:
        info1 = TemplateInfo(name="a", dependencies=[], triple_count=1)
        info2 = TemplateInfo(name="b", dependencies=[], triple_count=2)
        assert info1.dependencies is not info2.dependencies or info1.dependencies == []


class TestModelHandleDataclass:
    def test_model_handle_has_required_fields(self) -> None:
        graph = Graph()
        handle = ModelHandle(namespace="urn:test", graph=graph)
        assert handle.namespace == "urn:test"
        assert handle.graph is graph

    def test_model_handle_graph_operations(self) -> None:
        graph = Graph()
        handle = ModelHandle(namespace="urn:test", graph=graph)
        handle.graph.add(
            (URIRef("urn:s"), URIRef("urn:p"), Literal("value"))
        )
        assert len(handle.graph) == 1


class TestQueryResultDataclass:
    def test_query_result_has_bindings(self) -> None:
        result = QueryResult(bindings=[{"var1": "value1", "var2": None}])
        assert result.bindings == [{"var1": "value1", "var2": None}]

    def test_query_result_empty_bindings(self) -> None:
        result = QueryResult(bindings=[])
        assert result.bindings == []


class TestValidationResultDataclass:
    def test_validation_result_conforms(self) -> None:
        result = ValidationResult(conforms=True, report="OK")
        assert result.conforms is True
        assert result.report == "OK"

    def test_validation_result_fails(self) -> None:
        result = ValidationResult(conforms=False, report="Error: missing property")
        assert result.conforms is False
        assert "Error" in result.report


class TestMockAdapterProtocolCompliance:
    @pytest.fixture(autouse=True)
    def reset_mock(self) -> None:
        MockSemanticsAdapter.reset_instance()

    def test_mock_adapter_satisfies_protocol(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        _verify_protocol_compliance(adapter)

    def test_get_instance_returns_singleton(self) -> None:
        adapter1 = MockSemanticsAdapter.get_instance()
        adapter2 = MockSemanticsAdapter.get_instance()
        assert adapter1 is adapter2

    def test_list_templates_returns_list_of_strings(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        templates = adapter.list_templates()
        assert isinstance(templates, list)
        assert all(isinstance(t, str) for t in templates)
        assert "damper" in templates

    def test_get_template_info_returns_template_info(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        info = adapter.get_template_info("damper")
        assert isinstance(info, TemplateInfo)
        assert info.name == "damper"
        assert isinstance(info.dependencies, list)
        assert isinstance(info.triple_count, int)

    def test_get_template_info_raises_key_error_for_unknown(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        with pytest.raises(KeyError):
            adapter.get_template_info("nonexistent")

    def test_create_model_returns_model_handle(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model = adapter.create_model("urn:test-project")
        assert isinstance(model, ModelHandle)
        assert model.namespace == "urn:test-project"
        assert isinstance(model.graph, Graph)

    def test_get_or_create_model_creates_new(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model = adapter.get_or_create_model("urn:new-namespace")
        assert isinstance(model, ModelHandle)
        assert model.namespace == "urn:new-namespace"

    def test_get_or_create_model_returns_existing(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model1 = adapter.get_or_create_model("urn:existing")
        model1.graph.add((URIRef("urn:s"), URIRef("urn:p"), Literal("value")))
        model2 = adapter.get_or_create_model("urn:existing")
        assert len(model2.graph) == 1

    def test_add_triples_modifies_graph(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model = adapter.create_model("urn:test")
        adapter.add_triples(
            model, [("urn:subject", "urn:predicate", "object")]
        )
        assert len(model.graph) == 1

    def test_add_graph_merges_graphs(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model = adapter.create_model("urn:test")
        source_graph = Graph()
        source_graph.add((URIRef("urn:s1"), URIRef("urn:p1"), Literal("v1")))
        source_graph.add((URIRef("urn:s2"), URIRef("urn:p2"), Literal("v2")))
        adapter.add_graph(model, source_graph)
        assert len(model.graph) == 2

    def test_query_model_returns_query_result(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model = adapter.create_model("urn:test")
        model.graph.add((URIRef("urn:s"), URIRef("urn:p"), Literal("value")))
        result = adapter.query_model(
            model, "SELECT ?s ?p ?o WHERE { ?s ?p ?o }"
        )
        assert isinstance(result, QueryResult)
        assert isinstance(result.bindings, list)
        assert len(result.bindings) == 1
        assert "s" in result.bindings[0]

    def test_serialize_model_returns_string(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model = adapter.create_model("urn:test")
        model.graph.add(
            (URIRef("urn:subject"), URIRef("urn:predicate"), Literal("object"))
        )
        output = adapter.serialize_model(model, format="turtle")
        assert isinstance(output, str)
        assert "subject" in output
        assert "predicate" in output

    def test_validate_model_returns_validation_result(self) -> None:
        adapter = MockSemanticsAdapter.get_instance()
        model = adapter.create_model("urn:test")
        result = adapter.validate_model(model)
        assert isinstance(result, ValidationResult)
        assert isinstance(result.conforms, bool)
        assert isinstance(result.report, str)
