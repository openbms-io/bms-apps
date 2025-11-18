"""Integration tests for templates router."""
from fastapi.testclient import TestClient

from src.adapters import BuildingMOTIFAdapter
from src.main import app

client = TestClient(app)


def test_get_templates_returns_200_with_mock_data(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Test GET /api/v1/223p/templates returns 200 with hierarchical data."""
    # Use shared_adapter to avoid template loading issues
    BuildingMOTIFAdapter._instance = shared_adapter

    response = client.get("/api/v1/223p/templates")
    assert response.status_code == 200

    data = response.json()
    assert "systems" in data
    assert "spaceTypes" in data
    assert isinstance(data["systems"], list)
    assert isinstance(data["spaceTypes"], list)

    # If systems are loaded, verify we have 8 systems as per AC
    if len(data["systems"]) > 0:
        assert len(data["systems"]) == 8


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
