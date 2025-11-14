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
    # Verify endpoint saves data to in-memory store (Phase 1 mock behavior)
    assert isinstance(data["mappings"], dict)


def test_post_then_get_mappings_persists_data() -> None:
    """Test POST saves data and GET retrieves the saved mappings."""
    # Save mappings
    save_request = {
        "projectId": "test-proj-persistence",
        "mappings": {
            "point-abc-123": {
                "equipmentTypeId": "urn:ashrae:223p:VAVReheatTerminalUnit",
                "deviceTypeId": "urn:ashrae:223p:Damper",
                "propertyId": "urn:ashrae:223p:DamperCommand",
                "spaceId": None
            }
        }
    }

    post_response = client.post("/api/v1/223p/mappings", json=save_request)
    assert post_response.status_code == 200

    # Retrieve mappings
    get_response = client.get("/api/v1/223p/mappings?projectId=test-proj-persistence")
    assert get_response.status_code == 200

    data = get_response.json()
    assert data["projectId"] == "test-proj-persistence"
    assert "point-abc-123" in data["mappings"]
    assert data["mappings"]["point-abc-123"]["equipmentTypeId"] == "urn:ashrae:223p:VAVReheatTerminalUnit"
    assert data["mappings"]["point-abc-123"]["deviceTypeId"] == "urn:ashrae:223p:Damper"


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
