"""Integration tests for Parameters Router endpoints.

Tests cover:
  - POST /api/v1/parameters/convert - Unit conversion endpoint
  - GET /api/v1/parameters/defaults - Default parameters endpoint
"""

import pytest

from src.adapters.sequence_type import SequenceType


class TestConvertEndpoint:

    def test_convert_returns_200(self, integration_client):
        response = integration_client.post(
            "/api/v1/parameters/convert",
            json={
                "sequence_type": SequenceType.VAV_REHEAT,
                "parameters": {
                    "temperatureUnit": "K",
                    "airflowUnit": "m3/s",
                },
                "target_temperature_unit": "C",
                "target_airflow_unit": "cfm",
            },
        )
        assert response.status_code == 200

    def test_convert_changes_temperature_unit(self, integration_client):
        response = integration_client.post(
            "/api/v1/parameters/convert",
            json={
                "sequence_type": SequenceType.VAV_REHEAT,
                "parameters": {
                    "temperatureUnit": "K",
                    "airflowUnit": "m3/s",
                    "dischargeAirTempMin": 283.15,
                },
                "target_temperature_unit": "C",
                "target_airflow_unit": "m3/s",
            },
        )
        data = response.json()
        assert data["parameters"]["temperatureUnit"] == "C"
        assert data["parameters"]["dischargeAirTempMin"] == pytest.approx(10.0, rel=1e-6)

    def test_convert_changes_airflow_unit(self, integration_client):
        response = integration_client.post(
            "/api/v1/parameters/convert",
            json={
                "sequence_type": SequenceType.VAV_REHEAT,
                "parameters": {
                    "temperatureUnit": "K",
                    "airflowUnit": "m3/s",
                    "minAirflow": 0.471947,
                },
                "target_temperature_unit": "K",
                "target_airflow_unit": "cfm",
            },
        )
        data = response.json()
        assert data["parameters"]["airflowUnit"] == "cfm"
        assert data["parameters"]["minAirflow"] == pytest.approx(1000.0, rel=1e-3)

    def test_convert_both_units_simultaneously(self, integration_client):
        response = integration_client.post(
            "/api/v1/parameters/convert",
            json={
                "sequence_type": SequenceType.VAV_REHEAT,
                "parameters": {
                    "temperatureUnit": "K",
                    "airflowUnit": "m3/s",
                    "dischargeAirTempMin": 283.15,
                    "minAirflow": 0.3,
                },
                "target_temperature_unit": "C",
                "target_airflow_unit": "cfm",
            },
        )
        data = response.json()
        assert data["parameters"]["temperatureUnit"] == "C"
        assert data["parameters"]["airflowUnit"] == "cfm"
        assert data["parameters"]["dischargeAirTempMin"] == pytest.approx(10.0, rel=1e-6)
        assert data["parameters"]["minAirflow"] == pytest.approx(635.66, rel=1e-2)

    def test_convert_preserves_non_unit_parameters(self, integration_client):
        response = integration_client.post(
            "/api/v1/parameters/convert",
            json={
                "sequence_type": SequenceType.VAV_REHEAT,
                "parameters": {
                    "temperatureUnit": "K",
                    "airflowUnit": "m3/s",
                    "hasCO2Sensor": True,
                    "hasHotWaterCoil": False,
                    "coolingControllerGain": 0.5,
                },
                "target_temperature_unit": "C",
                "target_airflow_unit": "cfm",
            },
        )
        data = response.json()
        assert data["parameters"]["hasCO2Sensor"] is True
        assert data["parameters"]["hasHotWaterCoil"] is False
        assert data["parameters"]["coolingControllerGain"] == 0.5

    def test_convert_unknown_sequence_type_returns_422(self, integration_client):
        response = integration_client.post(
            "/api/v1/parameters/convert",
            json={
                "sequence_type": "unknown-type",
                "parameters": {
                    "temperatureUnit": "K",
                    "airflowUnit": "m3/s",
                },
                "target_temperature_unit": "C",
                "target_airflow_unit": "cfm",
            },
        )
        assert response.status_code == 422

    def test_convert_invalid_parameters_returns_422(self, integration_client):
        response = integration_client.post(
            "/api/v1/parameters/convert",
            json={
                "sequence_type": SequenceType.VAV_REHEAT,
                "parameters": {
                    "temperatureUnit": "invalid",
                },
                "target_temperature_unit": "C",
                "target_airflow_unit": "cfm",
            },
        )
        assert response.status_code == 422


class TestDefaultsEndpoint:

    def test_defaults_returns_200(self, integration_client):
        response = integration_client.get(
            "/api/v1/parameters/defaults",
            params={"sequenceType": SequenceType.VAV_REHEAT},
        )
        assert response.status_code == 200

    def test_defaults_returns_kelvin_temperature_unit(self, integration_client):
        response = integration_client.get(
            "/api/v1/parameters/defaults",
            params={"sequenceType": SequenceType.VAV_REHEAT},
        )
        data = response.json()
        assert data["parameters"]["temperatureUnit"] == "K"

    def test_defaults_returns_m3_per_s_airflow_unit(self, integration_client):
        response = integration_client.get(
            "/api/v1/parameters/defaults",
            params={"sequenceType": SequenceType.VAV_REHEAT},
        )
        data = response.json()
        assert data["parameters"]["airflowUnit"] == "m3/s"

    def test_defaults_returns_all_expected_fields(self, integration_client):
        response = integration_client.get(
            "/api/v1/parameters/defaults",
            params={"sequenceType": SequenceType.VAV_REHEAT},
        )
        data = response.json()
        params = data["parameters"]
        assert "hasCO2Sensor" in params
        assert "hasHotWaterCoil" in params
        assert "minAirflow" in params
        assert "dischargeAirTempMin" in params
        assert "coolingControllerGain" in params

    def test_defaults_unknown_sequence_type_returns_422(self, integration_client):
        response = integration_client.get(
            "/api/v1/parameters/defaults",
            params={"sequenceType": "unknown-type"},
        )
        assert response.status_code == 422

    def test_defaults_missing_sequence_type_returns_422(self, integration_client):
        response = integration_client.get("/api/v1/parameters/defaults")
        assert response.status_code == 422


class TestConvertEndpointOpenAPI:

    def test_convert_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        assert "/api/v1/parameters/convert" in openapi["paths"]
        assert "post" in openapi["paths"]["/api/v1/parameters/convert"]

    def test_defaults_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        assert "/api/v1/parameters/defaults" in openapi["paths"]
        assert "get" in openapi["paths"]["/api/v1/parameters/defaults"]
