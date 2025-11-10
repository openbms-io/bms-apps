"""Integration tests for templates router."""
from fastapi.testclient import TestClient

from src.main import app

client = TestClient(app)


def test_get_templates_returns_501_not_implemented() -> None:
    """Test GET /api/v1/223p/templates returns 501 status."""
    response = client.get("/api/v1/223p/templates")
    assert response.status_code == 501
    assert response.json()["detail"] == "Not implemented"


def test_get_templates_endpoint_exists() -> None:
    """Test templates endpoint is registered in OpenAPI."""
    response = client.get("/openapi.json")
    assert response.status_code == 200

    openapi = response.json()
    assert "/api/v1/223p/templates" in openapi["paths"]
    assert "get" in openapi["paths"]["/api/v1/223p/templates"]


def test_templates_response_schema_in_openapi() -> None:
    """Test TemplatesResponseDTO is defined in OpenAPI schemas."""
    response = client.get("/openapi.json")
    openapi = response.json()

    assert "TemplatesResponseDTO" in openapi["components"]["schemas"]
    schema = openapi["components"]["schemas"]["TemplatesResponseDTO"]

    assert "systems" in schema["properties"]
    assert "spaceTypes" in schema["properties"]  # camelCase
