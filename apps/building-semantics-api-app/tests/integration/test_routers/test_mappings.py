"""Integration tests for mappings router."""
from fastapi.testclient import TestClient

from src.adapters import BuildingMOTIFAdapter
from src.main import app

client = TestClient(app)


def test_get_mappings_returns_200_with_static_data(shared_adapter) -> None:
    """Test GET /api/v1/223p/mappings accepts projectId query param and returns 200."""
    BuildingMOTIFAdapter._instance = shared_adapter

    # Pre-create model to avoid database locking issues
    project_id = "proj-123"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    # Commit any pending database operations
    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

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


def test_post_mappings_returns_200_with_static_data(shared_adapter) -> None:
    """Test POST /api/v1/223p/mappings accepts SaveMappingsRequestDTO and returns 200."""
    BuildingMOTIFAdapter._instance = shared_adapter

    # Pre-create model to avoid database locking issues
    project_id = "proj-123"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    # Commit any pending database operations
    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    request_data = {
        "projectId": "proj-123",
        "mappings": {
            "device,1:analog-input,1": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
            }
        },
    }

    response = client.post("/api/v1/223p/mappings", json=request_data)
    assert response.status_code == 201

    data = response.json()
    assert "projectId" in data
    assert "mappings" in data
    # Verify endpoint saves data to RDF persistence (Story 2.8)
    assert isinstance(data["mappings"], dict)


def test_post_then_get_mappings_persists_data(shared_adapter) -> None:
    """Test POST saves data and GET retrieves the saved mappings."""
    BuildingMOTIFAdapter._instance = shared_adapter

    # Pre-create model and add to cache to avoid database operations during HTTP requests
    project_id = "test-proj-persistence"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    # Commit any pending database operations from model creation
    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    # Save mappings
    save_request = {
        "projectId": "test-proj-persistence",
        "mappings": {
            "device,123:analog-input,1": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
                "physicalSpaceId": None,
                "domainSpaceIds": None
            }
        }
    }

    post_response = client.post("/api/v1/223p/mappings", json=save_request)
    assert post_response.status_code == 201

    # Retrieve mappings
    get_response = client.get("/api/v1/223p/mappings?projectId=test-proj-persistence")
    assert get_response.status_code == 200

    data = get_response.json()
    assert data["projectId"] == "test-proj-persistence"
    assert "device,123:analog-input,1" in data["mappings"]
    # Verify perfect round-trip: template IDs match what we sent
    mapping = data["mappings"]["device,123:analog-input,1"]
    assert mapping["equipmentTypeId"] == "vav-reheat"
    assert mapping["deviceTypeId"] == "damper"
    assert mapping["propertyId"] == "damper-feedback"
    assert mapping["physicalSpaceId"] is None
    assert mapping["domainSpaceIds"] is None


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
    assert "physicalSpaceId" in schema["properties"]
    assert "domainSpaceIds" in schema["properties"]


def test_post_mapping_with_physical_space_only(shared_adapter) -> None:
    """Test POST with physical space only, GET retrieves it correctly."""
    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-physical-space"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    save_request = {
        "projectId": project_id,
        "mappings": {
            "device,200:analog-input,2": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
                "physicalSpaceId": "urn:bms:Space:room-101",
                "domainSpaceIds": None
            }
        }
    }

    post_response = client.post("/api/v1/223p/mappings", json=save_request)
    assert post_response.status_code == 201

    get_response = client.get(f"/api/v1/223p/mappings?projectId={project_id}")
    assert get_response.status_code == 200

    data = get_response.json()
    assert "device,200:analog-input,2" in data["mappings"]

    mapping = data["mappings"]["device,200:analog-input,2"]
    assert mapping["physicalSpaceId"] == "urn:bms:Space:room-101"
    assert mapping["domainSpaceIds"] is None


def test_post_mapping_with_domain_spaces_only(shared_adapter) -> None:
    """Test POST with domain spaces only, GET retrieves all of them."""
    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-domain-spaces"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    save_request = {
        "projectId": project_id,
        "mappings": {
            "device,300:analog-input,3": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
                "physicalSpaceId": None,
                "domainSpaceIds": [
                    "urn:bms:Zone:hvac-zone-1",
                    "urn:bms:Zone:hvac-zone-2",
                    "urn:bms:Zone:lighting-zone-1"
                ]
            }
        }
    }

    post_response = client.post("/api/v1/223p/mappings", json=save_request)
    assert post_response.status_code == 201

    get_response = client.get(f"/api/v1/223p/mappings?projectId={project_id}")
    assert get_response.status_code == 200

    data = get_response.json()
    assert "device,300:analog-input,3" in data["mappings"]

    mapping = data["mappings"]["device,300:analog-input,3"]
    assert mapping["physicalSpaceId"] is None
    assert mapping["domainSpaceIds"] is not None
    assert len(mapping["domainSpaceIds"]) == 3
    assert "urn:bms:Zone:hvac-zone-1" in mapping["domainSpaceIds"]
    assert "urn:bms:Zone:hvac-zone-2" in mapping["domainSpaceIds"]
    assert "urn:bms:Zone:lighting-zone-1" in mapping["domainSpaceIds"]


def test_post_mapping_with_both_physical_and_domain_spaces(shared_adapter) -> None:
    """Test POST with both physical and domain spaces, GET retrieves both correctly."""
    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-both-spaces"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    save_request = {
        "projectId": project_id,
        "mappings": {
            "device,400:analog-input,4": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
                "physicalSpaceId": "urn:bms:Space:room-202",
                "domainSpaceIds": [
                    "urn:bms:Zone:hvac-zone-3",
                    "urn:bms:Zone:lighting-zone-2"
                ]
            }
        }
    }

    post_response = client.post("/api/v1/223p/mappings", json=save_request)
    assert post_response.status_code == 201

    get_response = client.get(f"/api/v1/223p/mappings?projectId={project_id}")
    assert get_response.status_code == 200

    data = get_response.json()
    assert "device,400:analog-input,4" in data["mappings"]

    mapping = data["mappings"]["device,400:analog-input,4"]
    assert mapping["physicalSpaceId"] == "urn:bms:Space:room-202"
    assert mapping["domainSpaceIds"] is not None
    assert len(mapping["domainSpaceIds"]) == 2
    assert "urn:bms:Zone:hvac-zone-3" in mapping["domainSpaceIds"]
    assert "urn:bms:Zone:lighting-zone-2" in mapping["domainSpaceIds"]


def test_post_mapping_with_no_spaces(shared_adapter) -> None:
    """Test POST with no spaces, GET returns None/empty for both fields."""
    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-no-spaces"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    save_request = {
        "projectId": project_id,
        "mappings": {
            "device,500:analog-input,5": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
                "physicalSpaceId": None,
                "domainSpaceIds": None
            }
        }
    }

    post_response = client.post("/api/v1/223p/mappings", json=save_request)
    assert post_response.status_code == 201

    get_response = client.get(f"/api/v1/223p/mappings?projectId={project_id}")
    assert get_response.status_code == 200

    data = get_response.json()
    assert "device,500:analog-input,5" in data["mappings"]

    mapping = data["mappings"]["device,500:analog-input,5"]
    assert mapping["physicalSpaceId"] is None
    assert mapping["domainSpaceIds"] is None
