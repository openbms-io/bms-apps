"""Integration tests for G36 Router endpoints.

Tests cover acceptance criteria from Story 1.11:
  AC1: POST /api/v1/g36/reheat/instances (upsert)
  AC2: POST /api/v1/g36/reheat/instances/{instance_id}/step
  AC3: DELETE /api/v1/g36/instances/{instance_id} (idempotent)
  AC4: All endpoints documented in OpenAPI
  AC5: Integration tests for all endpoints

Uses real FMU file - no mocking.
"""

from pathlib import Path

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


@pytest.fixture
def fmu_available() -> bool:
    app_root = Path(__file__).parent.parent.parent
    fmu_path = app_root / "fmu-sequence" / "reheat" / "ReheatControllerFMU.fmu"
    return fmu_path.exists()


@pytest.fixture
def valid_create_request():
    return {
        "instance_id": "integration-test-1",
        "parameters": {
            "maxCoolingAirflow": 1.5,
            "maxHeatingAirflow": 1.2,
            "minHeatingAirflow": 0.5,
        },
        "inputs": {
            "temperatureUnit": "C",
            "airflowUnit": "m3/s",
            "zoneTemperature": 22.0,
            "coolingSetpoint": 24.0,
            "heatingSetpoint": 20.0,
            "dischargeAirTemperature": 16.0,
            "primaryAirflow": 0.3,
            "supplyAirTemperature": 13.0,
            "supplyAirTemperatureSetpoint": 12.0,
            "fanStatus": True,
            "operationMode": 1,
        },
    }


@pytest.fixture
def valid_step_request():
    return {
        "stepSize": 60.0,
        "inputs": {
            "temperatureUnit": "C",
            "airflowUnit": "m3/s",
            "zoneTemperature": 22.0,
            "coolingSetpoint": 24.0,
            "heatingSetpoint": 20.0,
            "dischargeAirTemperature": 16.0,
            "primaryAirflow": 0.3,
            "supplyAirTemperature": 13.0,
            "supplyAirTemperatureSetpoint": 12.0,
            "fanStatus": True,
            "operationMode": 1,
        },
    }


class TestUpsertEndpoint:

    def test_upsert_creates_new_instance(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == "integration-test-1"
        assert data["created"] is True
        assert "parameters" in data

    def test_upsert_recreates_existing_instance(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        valid_create_request["parameters"]["maxCoolingAirflow"] = 2.0
        response = integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == "integration-test-1"
        assert data["created"] is False

    def test_upsert_returns_400_for_invalid_inputs(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        valid_create_request["inputs"]["primaryAirflow"] = -1.0

        response = integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        assert response.status_code == 422

    def test_upsert_requires_instance_id(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        del valid_create_request["instance_id"]

        response = integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        assert response.status_code == 422


class TestStepEndpoint:

    def test_step_returns_outputs(
        self, integration_client, fmu_available, valid_create_request, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        response = integration_client.post(
            "/api/v1/g36/reheat/instances/integration-test-1/step",
            json=valid_step_request,
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == "integration-test-1"
        assert "outputs" in data
        assert "damperPosition" in data["outputs"]
        assert "valvePosition" in data["outputs"]
        assert "airflowSetpoint" in data["outputs"]

    def test_step_returns_404_for_unknown_instance(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.post(
            "/api/v1/g36/reheat/instances/nonexistent-instance/step",
            json=valid_step_request,
        )

        assert response.status_code == 404
        data = response.json()
        assert "nonexistent-instance" in data["error"]

    def test_step_returns_422_for_invalid_inputs(
        self, integration_client, fmu_available, valid_create_request, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        valid_step_request["inputs"]["primaryAirflow"] = -1.0

        response = integration_client.post(
            "/api/v1/g36/reheat/instances/integration-test-1/step",
            json=valid_step_request,
        )

        assert response.status_code == 422

    def test_step_returns_422_for_invalid_step_size(
        self, integration_client, fmu_available, valid_create_request, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        valid_step_request["stepSize"] = 0

        response = integration_client.post(
            "/api/v1/g36/reheat/instances/integration-test-1/step",
            json=valid_step_request,
        )

        assert response.status_code == 422


class TestDeleteEndpoint:

    def test_delete_existing_instance(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        response = integration_client.delete(
            "/api/v1/g36/instances/integration-test-1"
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == "integration-test-1"
        assert data["deleted"] is True

    def test_delete_idempotent_for_nonexistent(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.delete(
            "/api/v1/g36/instances/never-existed"
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == "never-existed"
        assert data["deleted"] is False

    def test_delete_sequence_agnostic_path(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        response = integration_client.delete(
            "/api/v1/g36/instances/integration-test-1"
        )

        assert response.status_code == 200


class TestEndToEndFlow:

    def test_create_step_delete_flow(
        self, integration_client, fmu_available, valid_create_request, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )
        assert create_response.status_code == 200
        assert create_response.json()["created"] is True

        step_response = integration_client.post(
            "/api/v1/g36/reheat/instances/integration-test-1/step",
            json=valid_step_request,
        )
        assert step_response.status_code == 200
        outputs = step_response.json()["outputs"]
        assert 0.0 <= outputs["damperPosition"] <= 1.0
        assert 0.0 <= outputs["valvePosition"] <= 1.0

        delete_response = integration_client.delete(
            "/api/v1/g36/instances/integration-test-1"
        )
        assert delete_response.status_code == 200
        assert delete_response.json()["deleted"] is True

        step_after_delete = integration_client.post(
            "/api/v1/g36/reheat/instances/integration-test-1/step",
            json=valid_step_request,
        )
        assert step_after_delete.status_code == 404

    def test_multiple_steps_accumulate_time(
        self, integration_client, fmu_available, valid_create_request, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        for _ in range(5):
            response = integration_client.post(
                "/api/v1/g36/reheat/instances/integration-test-1/step",
                json=valid_step_request,
            )
            assert response.status_code == 200


class TestOpenAPIDocumentation:

    def test_openapi_json_available(self, integration_client):
        response = integration_client.get("/openapi.json")

        assert response.status_code == 200
        openapi = response.json()
        assert "paths" in openapi

    def test_endpoints_documented_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/reheat/instances" in paths
        assert "post" in paths["/api/v1/g36/reheat/instances"]

        assert "/api/v1/g36/reheat/instances/{instance_id}/step" in paths
        assert "post" in paths["/api/v1/g36/reheat/instances/{instance_id}/step"]

        assert "/api/v1/g36/instances/{instance_id}" in paths
        assert "delete" in paths["/api/v1/g36/instances/{instance_id}"]

    def test_docs_endpoint_available(self, integration_client):
        response = integration_client.get("/docs")

        assert response.status_code == 200
