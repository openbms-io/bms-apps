"""Integration tests for spaces router."""
from fastapi.testclient import TestClient

from src.main import app

client = TestClient(app)


def test_list_spaces_returns_501_with_project_id_query() -> None:
    """Test GET /api/v1/223p/spaces accepts projectId query param and returns 501."""
    response = client.get("/api/v1/223p/spaces?projectId=proj-123")
    assert response.status_code == 501
    assert response.json()["detail"] == "Not implemented"


def test_list_spaces_requires_project_id() -> None:
    """Test GET /api/v1/223p/spaces requires projectId query parameter."""
    response = client.get("/api/v1/223p/spaces")
    assert response.status_code == 422  # Validation error


def test_create_space_returns_501_and_uses_201_status() -> None:
    """Test POST /api/v1/223p/spaces accepts CreateSpaceRequestDTO and returns 501."""
    request_data = {
        "projectId": "proj-123",
        "spaceTypeId": "urn:223p:Office",
        "label": "Room 101 - John's Office",
    }

    response = client.post("/api/v1/223p/spaces", json=request_data)

    # Even though it's not implemented, the endpoint is configured for 201
    # But since we raise 501, that takes precedence
    assert response.status_code == 501
    assert response.json()["detail"] == "Not implemented"


def test_spaces_schemas_in_openapi() -> None:
    """Test space DTOs are correctly defined in OpenAPI spec."""
    response = client.get("/openapi.json")
    openapi = response.json()

    assert "SpaceInstanceDTO" in openapi["components"]["schemas"]
    schema = openapi["components"]["schemas"]["SpaceInstanceDTO"]

    # Verify camelCase field names
    assert "spaceTypeId" in schema["properties"]
    assert "createdAt" in schema["properties"]

    # Verify CreateSpaceRequestDTO
    assert "CreateSpaceRequestDTO" in openapi["components"]["schemas"]
    create_schema = openapi["components"]["schemas"]["CreateSpaceRequestDTO"]
    assert "projectId" in create_schema["properties"]
    assert "spaceTypeId" in create_schema["properties"]
