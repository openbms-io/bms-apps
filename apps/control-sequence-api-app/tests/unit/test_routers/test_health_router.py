"""Unit tests for Health Router.

Tests cover acceptance criteria from Story 1.13:
  AC1: GET /api/v1/health returns status and active_instances count
  AC2: Response includes service name and version
  AC3: Response time <10ms
"""

import time
from unittest.mock import MagicMock

import pytest
from fastapi import FastAPI
from fastapi.testclient import TestClient

from src.routers.health_router import get_fmu_adapter, router


@pytest.fixture
def mock_adapter():
    adapter = MagicMock()
    adapter.list_instance_ids.return_value = []
    return adapter


@pytest.fixture
def app_with_mock_adapter(mock_adapter):
    app = FastAPI()
    app.include_router(router)
    app.dependency_overrides[get_fmu_adapter] = lambda: mock_adapter
    return app


@pytest.fixture
def client(app_with_mock_adapter):
    return TestClient(app_with_mock_adapter)


class TestHealthEndpointResponse:

    def test_health_returns_200_status(self, client):
        response = client.get("/api/v1/health")
        assert response.status_code == 200

    def test_health_returns_status_field(self, client):
        response = client.get("/api/v1/health")
        data = response.json()
        assert "status" in data
        assert data["status"] == "healthy"

    def test_health_returns_active_instances_field(self, client):
        response = client.get("/api/v1/health")
        data = response.json()
        assert "active_instances" in data
        assert isinstance(data["active_instances"], int)

    def test_health_returns_service_name(self, client):
        response = client.get("/api/v1/health")
        data = response.json()
        assert "service" in data
        assert data["service"] == "control-sequence-api"

    def test_health_returns_version(self, client):
        response = client.get("/api/v1/health")
        data = response.json()
        assert "version" in data
        assert data["version"] == "0.1.0"


class TestHealthActiveInstances:

    def test_active_instances_zero_when_no_fmu_instances(
        self, client, mock_adapter
    ):
        mock_adapter.list_instance_ids.return_value = []
        response = client.get("/api/v1/health")
        data = response.json()
        assert data["active_instances"] == 0

    def test_active_instances_reflects_fmu_count(
        self, app_with_mock_adapter, mock_adapter
    ):
        mock_adapter.list_instance_ids.return_value = ["id-1", "id-2", "id-3"]
        client = TestClient(app_with_mock_adapter)
        response = client.get("/api/v1/health")
        data = response.json()
        assert data["active_instances"] == 3

    def test_active_instances_updates_dynamically(
        self, app_with_mock_adapter, mock_adapter
    ):
        client = TestClient(app_with_mock_adapter)

        mock_adapter.list_instance_ids.return_value = ["id-1"]
        response = client.get("/api/v1/health")
        assert response.json()["active_instances"] == 1

        mock_adapter.list_instance_ids.return_value = ["id-1", "id-2", "id-3", "id-4", "id-5"]
        response = client.get("/api/v1/health")
        assert response.json()["active_instances"] == 5


class TestHealthPerformance:

    def test_health_response_time_under_10ms(self, client):
        start = time.perf_counter()
        response = client.get("/api/v1/health")
        elapsed_ms = (time.perf_counter() - start) * 1000

        assert response.status_code == 200
        assert elapsed_ms < 10, f"Response time {elapsed_ms:.2f}ms exceeds 10ms threshold"
