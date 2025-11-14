"""Shared fixtures for integration tests."""
import pytest

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter


@pytest.fixture(scope="session")
def shared_adapter(tmp_path_factory):
    """
    Shared BuildingMOTIF adapter for all integration tests.

    Uses session scope to initialize once and reuse across all tests,
    avoiding repeated 30+ second ontology loading and database locking issues.
    """
    BuildingMOTIFAdapter._instance = None
    db_path = tmp_path_factory.mktemp("data") / "buildingmotif.db"
    adapter = BuildingMOTIFAdapter.get_instance(str(db_path))
    yield adapter
    BuildingMOTIFAdapter._instance = None
