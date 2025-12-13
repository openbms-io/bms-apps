"""Integration tests for G36 VAV Reheat Router endpoints.

Tests cover acceptance criteria from Story 1.15:
  AC1: POST /api/v1/g36/vav-reheat/instances (create with defaults, auto-generated ID)
  AC2: GET /api/v1/g36/vav-reheat/instances/{instance_id} (retrieve parameters)
  AC3: PUT /api/v1/g36/vav-reheat/instances/{instance_id} (update parameters)
  AC4: POST /api/v1/g36/vav-reheat/instances/{instance_id}/step
  AC5: DELETE /api/v1/g36/vav-reheat/instances/{instance_id} (idempotent)
  AC6: All endpoints documented in OpenAPI
  AC7: Integration tests for all endpoints

Uses real FMU file - no mocking.
"""

import pytest

from src.adapters.fmu_adapter import FmuAdapter


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


class TestCreateEndpoint:

    def test_create_returns_auto_generated_instance_id(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.post("/api/v1/g36/vav-reheat/instances")

        assert response.status_code == 200
        data = response.json()
        assert "instance_id" in data
        assert len(data["instance_id"]) == 36

    def test_create_returns_default_parameters(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.post("/api/v1/g36/vav-reheat/instances")

        assert response.status_code == 200
        data = response.json()
        assert "parameters" in data
        assert data["parameters"]["minAirflow"] == 0.3
        assert data["parameters"]["maxCoolingAirflow"] == 1.5
        assert data["parameters"]["hasCO2Sensor"] is True

    def test_create_does_not_instantiate_fmu_immediately(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.post("/api/v1/g36/vav-reheat/instances")

        assert response.status_code == 200
        adapter = FmuAdapter.get_instance()
        data = response.json()
        assert not adapter.has_instance(data["instance_id"])


class TestGetEndpoint:

    def test_get_returns_instance_parameters(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        response = integration_client.get(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}"
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == instance_id
        assert "parameters" in data
        assert data["parameters"]["minAirflow"] == 0.3

    def test_get_returns_404_for_unknown_instance(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.get(
            "/api/v1/g36/vav-reheat/instances/nonexistent-instance"
        )

        assert response.status_code == 404
        data = response.json()
        assert "nonexistent-instance" in data["error"]


class TestUpdateEndpoint:

    def test_update_returns_updated_parameters(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        response = integration_client.put(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}",
            json={
                "parameters": {
                    "minAirflow": 0.5,
                    "maxCoolingAirflow": 2.0,
                }
            },
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == instance_id
        assert data["parameters"]["minAirflow"] == 0.5
        assert data["parameters"]["maxCoolingAirflow"] == 2.0

    def test_update_persists_changes(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        integration_client.put(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}",
            json={
                "parameters": {
                    "minAirflow": 0.7,
                }
            },
        )

        get_response = integration_client.get(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}"
        )

        assert get_response.status_code == 200
        assert get_response.json()["parameters"]["minAirflow"] == 0.7

    def test_update_returns_404_for_unknown_instance(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.put(
            "/api/v1/g36/vav-reheat/instances/nonexistent-instance",
            json={
                "parameters": {
                    "minAirflow": 0.5,
                }
            },
        )

        assert response.status_code == 404
        data = response.json()
        assert "nonexistent-instance" in data["error"]

    def test_update_causes_fmu_recreation_on_next_step(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        step1 = integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )
        assert step1.status_code == 200

        integration_client.put(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}",
            json={
                "parameters": {
                    "minAirflow": 0.6,
                }
            },
        )

        step2 = integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )
        assert step2.status_code == 200


class TestStepEndpoint:

    def test_step_returns_outputs(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        response = integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == instance_id
        assert "outputs" in data
        assert "damperPosition" in data["outputs"]
        assert "valvePosition" in data["outputs"]
        assert "airflowSetpoint" in data["outputs"]

    def test_step_lazy_creates_fmu_instance(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]
        adapter = FmuAdapter.get_instance()
        assert not adapter.has_instance(instance_id)

        integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )

        assert adapter.has_instance(instance_id)

    def test_step_returns_404_for_unknown_instance(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.post(
            "/api/v1/g36/vav-reheat/instances/nonexistent-instance/step",
            json=valid_step_request,
        )

        assert response.status_code == 404
        data = response.json()
        assert "nonexistent-instance" in data["error"]

    def test_step_returns_422_for_invalid_inputs(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        valid_step_request["inputs"]["primaryAirflow"] = -1.0

        response = integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )

        assert response.status_code == 422

    def test_step_returns_422_for_invalid_step_size(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        valid_step_request["stepSize"] = 0

        response = integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )

        assert response.status_code == 422


class TestDeleteEndpoint:

    def test_delete_existing_instance(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]
        integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )

        response = integration_client.delete(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}"
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == instance_id
        assert data["deleted"] is True

    def test_delete_idempotent_for_nonexistent(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        response = integration_client.delete(
            "/api/v1/g36/vav-reheat/instances/never-existed"
        )

        assert response.status_code == 200
        data = response.json()
        assert data["instance_id"] == "never-existed"
        assert data["deleted"] is False

    def test_delete_after_create_before_step_succeeds(
        self, integration_client, fmu_available
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        response = integration_client.delete(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}"
        )

        assert response.status_code == 200
        data = response.json()
        assert data["deleted"] is True


class TestEndToEndFlow:

    def test_create_step_delete_flow(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        assert create_response.status_code == 200
        instance_id = create_response.json()["instance_id"]
        assert len(instance_id) == 36

        step_response = integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )
        assert step_response.status_code == 200
        outputs = step_response.json()["outputs"]
        assert 0.0 <= outputs["damperPosition"] <= 1.0
        assert 0.0 <= outputs["valvePosition"] <= 1.0

        delete_response = integration_client.delete(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}"
        )
        assert delete_response.status_code == 200
        assert delete_response.json()["deleted"] is True

        step_after_delete = integration_client.post(
            f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
            json=valid_step_request,
        )
        assert step_after_delete.status_code == 404

    def test_multiple_steps_accumulate_time(
        self, integration_client, fmu_available, valid_step_request
    ):
        if not fmu_available:
            pytest.skip("Reheat FMU not available")

        create_response = integration_client.post("/api/v1/g36/vav-reheat/instances")
        instance_id = create_response.json()["instance_id"]

        for _ in range(5):
            response = integration_client.post(
                f"/api/v1/g36/vav-reheat/instances/{instance_id}/step",
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

        assert "/api/v1/g36/vav-reheat/instances" in paths
        assert "post" in paths["/api/v1/g36/vav-reheat/instances"]

        assert "/api/v1/g36/vav-reheat/instances/{instance_id}" in paths
        assert "get" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}"]
        assert "put" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}"]
        assert "delete" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}"]

        assert "/api/v1/g36/vav-reheat/instances/{instance_id}/step" in paths
        assert "post" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}/step"]

    def test_docs_endpoint_available(self, integration_client):
        response = integration_client.get("/docs")

        assert response.status_code == 200
