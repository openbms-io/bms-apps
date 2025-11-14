"""Integration tests for spaces router."""
from fastapi.testclient import TestClient

from src.main import app

client = TestClient(app)


def test_list_spaces_returns_200_with_array() -> None:
    """Test GET /api/v1/223p/spaces accepts projectId query param and returns 200."""
    response = client.get("/api/v1/223p/spaces?projectId=proj-123")
    assert response.status_code == 200

    data = response.json()
    assert isinstance(data, list)
    assert len(data) > 0
    # Verify space structure
    for space in data:
        assert "id" in space
        assert "spaceTypeId" in space
        assert "label" in space
        assert "createdAt" in space


def test_list_spaces_requires_project_id() -> None:
    """Test GET /api/v1/223p/spaces requires projectId query parameter."""
    response = client.get("/api/v1/223p/spaces")
    assert response.status_code == 422  # Validation error


def test_create_space_returns_201_with_space_instance() -> None:
    """Test POST /api/v1/223p/spaces accepts CreateSpaceRequestDTO and returns 201."""
    request_data = {
        "projectId": "proj-123",
        "spaceTypeId": "urn:223p:Office",
        "label": "Room 101 - John's Office",
    }

    response = client.post("/api/v1/223p/spaces", json=request_data)
    assert response.status_code == 201

    data = response.json()
    assert "id" in data
    assert "spaceTypeId" in data
    assert "label" in data
    assert "createdAt" in data


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
