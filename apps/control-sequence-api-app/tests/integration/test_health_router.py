"""Integration tests for Health Router endpoint.

Tests cover acceptance criteria from Story 1.13:
  AC1: GET /api/v1/health returns status and active_instances count
  AC2: Response includes service name and version
  AC3: Response time <10ms
  AC4: Endpoint documented in OpenAPI

Uses real FmuAdapter singleton - no mocking.
"""

import time
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
        "instance_id": "health-test-instance",
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


class TestHealthEndpoint:

    def test_health_returns_200(self, integration_client):
        response = integration_client.get("/api/v1/health")
        assert response.status_code == 200

    def test_health_returns_status_healthy(self, integration_client):
        response = integration_client.get("/api/v1/health")
        data = response.json()
        assert data["status"] == "healthy"

    def test_health_returns_active_instances_field(self, integration_client):
        response = integration_client.get("/api/v1/health")
        data = response.json()
        assert "active_instances" in data
        assert isinstance(data["active_instances"], int)

    def test_health_returns_service_name(self, integration_client):
        response = integration_client.get("/api/v1/health")
        data = response.json()
        assert data["service"] == "control-sequence-api"

    def test_health_returns_version(self, integration_client):
        response = integration_client.get("/api/v1/health")
        data = response.json()
        assert data["version"] == "0.1.0"


class TestHealthActiveInstancesIntegration:

    def test_health_shows_zero_instances_initially(self, integration_client):
        response = integration_client.get("/api/v1/health")
        data = response.json()
        assert data["active_instances"] == 0

    def test_health_reflects_created_instances(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 0

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )

        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 1

    def test_health_reflects_deleted_instances(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        integration_client.post(
            "/api/v1/g36/reheat/instances",
            json=valid_create_request,
        )
        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 1

        integration_client.delete("/api/v1/g36/instances/health-test-instance")

        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 0

    def test_health_reflects_multiple_instances(
        self, integration_client, fmu_available, valid_create_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        for i in range(3):
            request = valid_create_request.copy()
            request["instance_id"] = f"health-test-{i}"
            integration_client.post(
                "/api/v1/g36/reheat/instances",
                json=request,
            )

        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 3


class TestHealthPerformance:

    def test_health_response_time_under_10ms(self, integration_client):
        integration_client.get("/api/v1/health")

        start = time.perf_counter()
        response = integration_client.get("/api/v1/health")
        elapsed_ms = (time.perf_counter() - start) * 1000

        assert response.status_code == 200
        assert elapsed_ms < 10, f"Response time {elapsed_ms:.2f}ms exceeds 10ms threshold"


class TestHealthOpenAPIDocumentation:

    def test_health_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/health" in paths
        assert "get" in paths["/api/v1/health"]

    def test_health_endpoint_has_response_schema(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        health_path = openapi["paths"]["/api/v1/health"]["get"]
        assert "responses" in health_path
        assert "200" in health_path["responses"]

    def test_health_response_schema_has_required_fields(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema_ref = openapi["paths"]["/api/v1/health"]["get"]["responses"]["200"]["content"]["application/json"]["schema"]
        if "$ref" in schema_ref:
            schema_name = schema_ref["$ref"].split("/")[-1]
            schema = openapi["components"]["schemas"][schema_name]
        else:
            schema = schema_ref

        properties = schema.get("properties", {})
        assert "status" in properties
        assert "service" in properties
        assert "version" in properties
        assert "active_instances" in properties
