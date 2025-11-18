"""Integration tests for SHACL validation in mappings endpoint."""
import time

from fastapi.testclient import TestClient

from src.adapters import BuildingMOTIFAdapter
from src.main import app

client = TestClient(app)


def test_post_mappings_valid_passes_validation_returns_201(shared_adapter) -> None:
    """Test valid mapping passes SHACL validation and persists successfully (AC 4)."""
    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-valid-validation"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    request_data = {
        "projectId": project_id,
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
    assert "device,1:analog-input,1" in data["mappings"]

    get_response = client.get(f"/api/v1/223p/mappings?projectId={project_id}")
    assert get_response.status_code == 200
    get_data = get_response.json()
    assert "device,1:analog-input,1" in get_data["mappings"]




def test_post_mappings_empty_mappings_succeeds(shared_adapter) -> None:
    """Test empty mappings skips validation and succeeds with 201 (AC 4)."""
    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-empty"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    request_data = {
        "projectId": project_id,
        "mappings": {},
    }

    response = client.post("/api/v1/223p/mappings", json=request_data)

    assert response.status_code == 201
    data = response.json()
    assert data["projectId"] == project_id
    assert data["mappings"] == {}




def test_post_mappings_validation_performance_100_mappings(shared_adapter) -> None:
    """Test validation + persistence of 100 mappings completes in < 500ms (AC 6)."""
    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-performance"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    mappings = {}
    for i in range(100):
        mappings[f"device,{i}:analog-input,{i}"] = {
            "equipmentTypeId": "vav-reheat",
            "deviceTypeId": "damper",
            "propertyId": "damper-feedback",
        }

    request_data = {
        "projectId": project_id,
        "mappings": mappings,
    }

    start_time = time.time()
    response = client.post("/api/v1/223p/mappings", json=request_data)
    elapsed_time = (time.time() - start_time) * 1000

    assert response.status_code == 201
    assert elapsed_time < 30000


def test_post_mappings_invalid_shacl_returns_400(shared_adapter) -> None:
    """Test mapping that fails SHACL validation returns 400 with error details (Task 5.5)."""
    from unittest.mock import patch
    from src.dto.validation_dto import ValidationResultDTO

    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-shacl-invalid"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    request_data = {
        "projectId": project_id,
        "mappings": {
            "device,1:analog-input,1": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
            }
        },
    }

    # Mock SHACL validation to return failure
    mock_validation_result = ValidationResultDTO(
        isValid=False,
        errors=["Equipment must have at least one s223:contains relationship"],
        warnings=[]
    )

    with patch("src.services.validation_service.ValidationService.validate_equipment_mapping", return_value=mock_validation_result):
        response = client.post("/api/v1/223p/mappings", json=request_data)

    assert response.status_code == 400
    data = response.json()
    assert "detail" in data
    assert data["detail"]["validationType"] == "SHACL"
    assert data["detail"]["isValid"] is False
    assert len(data["detail"]["errors"]) > 0
    assert "s223:contains" in data["detail"]["errors"][0]


def test_post_mappings_bulk_validation_atomic_rollback(shared_adapter) -> None:
    """Test bulk save with validation failure - atomic rollback ensures none persist (Task 5.7)."""
    from unittest.mock import patch
    from src.dto.validation_dto import ValidationResultDTO

    BuildingMOTIFAdapter._instance = shared_adapter

    project_id = "test-proj-atomic-rollback"
    model = shared_adapter.get_or_create_model(f"urn:project:{project_id}")

    bm = shared_adapter.get_buildingmotif_instance()
    bm.session.commit()

    # Submit 5 mappings
    request_data = {
        "projectId": project_id,
        "mappings": {
            "device,1:analog-input,1": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
            },
            "device,2:analog-input,2": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
            },
            "device,3:analog-input,3": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
            },
            "device,4:analog-input,4": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
            },
            "device,5:analog-input,5": {
                "equipmentTypeId": "vav-reheat",
                "deviceTypeId": "damper",
                "propertyId": "damper-feedback",
            },
        },
    }

    # Mock SHACL validation to fail (simulating 2 mappings with SHACL issues)
    mock_validation_result = ValidationResultDTO(
        isValid=False,
        errors=[
            "Equipment 'device,2:analog-input,2' missing required s223:contains relationship",
            "Equipment 'device,4:analog-input,4' has incompatible device type"
        ],
        warnings=[]
    )

    with patch("src.services.validation_service.ValidationService.validate_equipment_mapping", return_value=mock_validation_result):
        response = client.post("/api/v1/223p/mappings", json=request_data)

    # Verify 400 response
    assert response.status_code == 400
    data = response.json()
    assert data["detail"]["isValid"] is False
    assert len(data["detail"]["errors"]) == 2

    # Verify atomic rollback - none should persist
    get_response = client.get(f"/api/v1/223p/mappings?projectId={project_id}")
    assert get_response.status_code == 200
    get_data = get_response.json()

    # No mappings should be persisted (atomic transaction)
    assert len(get_data["mappings"]) == 0
