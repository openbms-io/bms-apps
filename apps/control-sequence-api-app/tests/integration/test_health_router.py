"""Integration tests for Health Router endpoint.

Tests cover acceptance criteria from Story 1.13:
  AC1: GET /api/v1/health returns status and active_instances count
  AC2: Response includes service name and version
  AC3: Response time <10ms
  AC4: Endpoint documented in OpenAPI

Uses real FmuAdapter singleton - no mocking.
"""

import time

import pytest

from tests.conftest import create_reheat_instance


@pytest.fixture
def valid_step_request():
    return {
        "stepSize": 60.0,
        "inputs": {
            "zoneTemperature": 295.15,
            "coolingSetpoint": 297.15,
            "heatingSetpoint": 293.15,
            "dischargeAirTemperature": 289.15,
            "primaryAirflow": 0.3,
            "supplyAirTemperature": 286.15,
            "supplyAirTemperatureSetpoint": 285.15,
            "fanStatus": True,
            "operationMode": "occupied",
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
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 0

        created = create_reheat_instance(integration_client)
        instance_id = created["instanceId"]

        integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )

        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 1

    def test_health_reflects_deleted_instances(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        created = create_reheat_instance(integration_client)
        instance_id = created["instanceId"]

        integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )
        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 1

        integration_client.delete(f"/api/v1/g36/vav-reheat/instances/{instance_id}")

        response = integration_client.get("/api/v1/health")
        assert response.json()["active_instances"] == 0

    def test_health_reflects_multiple_instances(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        for _ in range(3):
            created = create_reheat_instance(integration_client)
            instance_id = created["instanceId"]
            integration_client.post(
                f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
                json=valid_step_request,
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
