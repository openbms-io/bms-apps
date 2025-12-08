"""Integration tests for Validation Router endpoint.

Tests cover acceptance criteria from Story 1.14:
  AC1: POST /api/v1/g36/validate endpoint exists
  AC2: Endpoint returns stub response indicating always valid
  AC3: Endpoint documented as "stub for future implementation" in OpenAPI

Uses real app instance - no mocking.
"""

import pytest
from fastapi.testclient import TestClient

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_loader import FmuLoader
from src.main import app


@pytest.fixture
def integration_client():
    FmuAdapter.reset_singleton()
    FmuLoader.clear_cache()
    with TestClient(app) as client:
        yield client
    FmuAdapter.reset_singleton()
    FmuLoader.clear_cache()


class TestValidateEndpoint:

    def test_validate_returns_200(self, integration_client):
        response = integration_client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        assert response.status_code == 200

    def test_validate_returns_valid_true(self, integration_client):
        response = integration_client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        data = response.json()
        assert data["valid"] is True

    def test_validate_returns_empty_errors(self, integration_client):
        response = integration_client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        data = response.json()
        assert data["errors"] == []

    def test_validate_returns_stub_message(self, integration_client):
        response = integration_client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        data = response.json()
        assert "stub" in data["message"].lower()


class TestValidateOpenAPIDocumentation:

    def test_validate_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/validate" in paths
        assert "post" in paths["/api/v1/g36/validate"]

    def test_validate_endpoint_has_response_schema(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        validate_path = openapi["paths"]["/api/v1/g36/validate"]["post"]
        assert "responses" in validate_path
        assert "200" in validate_path["responses"]

    def test_validate_endpoint_has_stub_description(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        validate_path = openapi["paths"]["/api/v1/g36/validate"]["post"]
        description = validate_path.get("description", "") or validate_path.get(
            "summary", ""
        )
        assert "stub" in description.lower() or "Stub" in description

    def test_validate_response_schema_has_required_fields(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema_ref = openapi["paths"]["/api/v1/g36/validate"]["post"]["responses"][
            "200"
        ]["content"]["application/json"]["schema"]
        if "$ref" in schema_ref:
            schema_name = schema_ref["$ref"].split("/")[-1]
            schema = openapi["components"]["schemas"][schema_name]
        else:
            schema = schema_ref

        properties = schema.get("properties", {})
        assert "valid" in properties
        assert "errors" in properties
        assert "message" in properties

    def test_validate_tagged_as_validation(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        validate_path = openapi["paths"]["/api/v1/g36/validate"]["post"]
        tags = validate_path.get("tags", [])
        assert "Validation" in tags
