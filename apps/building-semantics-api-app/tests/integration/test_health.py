"""Integration tests for health endpoint."""
import pytest
from fastapi.testclient import TestClient

from src.main import app

client = TestClient(app)


def test_health_check_returns_200() -> None:
    """Test health check endpoint returns 200 OK."""
    response = client.get("/health")
    assert response.status_code == 200


def test_health_check_returns_expected_json() -> None:
    """Test health check returns expected JSON structure."""
    response = client.get("/health")
    data = response.json()

    assert data["status"] == "healthy"
    assert data["service"] == "building-semantics-api"
    assert data["version"] == "0.1.0"


def test_health_check_content_type() -> None:
    """Test health check returns JSON content type."""
    response = client.get("/health")
    assert "application/json" in response.headers["content-type"]
