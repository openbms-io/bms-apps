"""Integration tests for mappings router."""
from fastapi.testclient import TestClient

from src.main import app

client = TestClient(app)


def test_get_mappings_returns_200_with_static_data() -> None:
    """Test GET /api/v1/223p/mappings accepts projectId query param and returns 200."""
    response = client.get("/api/v1/223p/mappings?projectId=proj-123")
    assert response.status_code == 200

    data = response.json()
    assert "projectId" in data
    assert "mappings" in data
    assert isinstance(data["mappings"], dict)


def test_get_mappings_requires_project_id() -> None:
    """Test GET /api/v1/223p/mappings requires projectId query parameter."""
    response = client.get("/api/v1/223p/mappings")
    assert response.status_code == 422  # Validation error


def test_post_mappings_returns_200_with_static_data() -> None:
    """Test POST /api/v1/223p/mappings accepts SaveMappingsRequestDTO and returns 200."""
    request_data = {
        "projectId": "proj-123",
        "mappings": {
            "device-1:ai-1": {
                "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit",
                "deviceTypeId": "urn:223p:Damper",
                "propertyId": "urn:223p:DamperPosition",
            }
        },
    }

    response = client.post("/api/v1/223p/mappings", json=request_data)
    assert response.status_code == 200

    data = response.json()
    assert "projectId" in data
    assert "mappings" in data
    # Verify endpoint ignores request body (Phase 1 behavior)
    assert isinstance(data["mappings"], dict)


def test_mappings_schemas_in_openapi() -> None:
    """Test mappings DTOs are correctly defined in OpenAPI spec."""
    response = client.get("/openapi.json")
    openapi = response.json()

    assert "SemanticMappingDTO" in openapi["components"]["schemas"]
    schema = openapi["components"]["schemas"]["SemanticMappingDTO"]

    # Verify camelCase field names
    assert "equipmentTypeId" in schema["properties"]
    assert "deviceTypeId" in schema["properties"]
    assert "propertyId" in schema["properties"]
    assert "spaceId" in schema["properties"]
