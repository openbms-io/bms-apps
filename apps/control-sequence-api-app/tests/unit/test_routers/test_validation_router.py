"""Unit tests for Validation Router.

Tests cover acceptance criteria from Story 1.14:
  AC1: POST /api/v1/g36/validate endpoint exists
  AC2: Endpoint returns stub response indicating always valid
"""

import pytest
from fastapi import FastAPI
from fastapi.testclient import TestClient

from src.routers.validation_router import router


@pytest.fixture
def app():
    app = FastAPI()
    app.include_router(router)
    return app


@pytest.fixture
def client(app):
    return TestClient(app)


class TestValidateEndpointResponse:

    def test_validate_returns_200_status(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        assert response.status_code == 200

    def test_validate_returns_valid_true(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        data = response.json()
        assert "valid" in data
        assert data["valid"] is True

    def test_validate_returns_empty_errors(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        data = response.json()
        assert "errors" in data
        assert isinstance(data["errors"], list)
        assert len(data["errors"]) == 0

    def test_validate_returns_stub_message(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={"graph": {"nodes": [], "edges": []}},
        )
        data = response.json()
        assert "message" in data
        assert "stub" in data["message"].lower()
        assert "Epic 3" in data["message"]


class TestValidateEndpointRequest:

    def test_validate_accepts_graph_with_nodes_and_edges(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={
                "graph": {
                    "nodes": [{"id": "node-1", "type": "g36-reheat"}],
                    "edges": [{"source": "node-1", "target": "node-2"}],
                }
            },
        )
        assert response.status_code == 200
        assert response.json()["valid"] is True

    def test_validate_accepts_empty_graph(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={"graph": {}},
        )
        assert response.status_code == 200
        assert response.json()["valid"] is True

    def test_validate_accepts_complex_graph(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={
                "graph": {
                    "nodes": [
                        {"id": "node-1", "type": "g36-reheat", "data": {"params": {}}},
                        {"id": "node-2", "type": "bacnet-reader", "data": {}},
                    ],
                    "edges": [
                        {"id": "edge-1", "source": "node-1", "target": "node-2"},
                    ],
                    "metadata": {"version": "1.0"},
                }
            },
        )
        assert response.status_code == 200
        assert response.json()["valid"] is True


class TestValidateEndpointErrorHandling:

    def test_validate_requires_graph_field(self, client):
        response = client.post(
            "/api/v1/g36/validate",
            json={},
        )
        assert response.status_code == 422
