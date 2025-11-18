"""Shared fixtures for integration tests."""
import pytest

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.config.settings import Settings


@pytest.fixture(scope="session")
def shared_adapter(tmp_path_factory):
    """
    Shared BuildingMOTIF adapter for all integration tests.

    Uses session scope to initialize once and reuse across all tests,
    avoiding repeated 30+ second ontology loading and database locking issues.
    """
    BuildingMOTIFAdapter._instance = None
    db_path = tmp_path_factory.mktemp("data") / "buildingmotif.db"

    # Create test settings with correct template path (relative to project root)
    test_settings = Settings(
        buildingmotif_templates_path="apps/building-semantics-api-app/data/libraries/ashrae-223p-nrel"
    )

    adapter = BuildingMOTIFAdapter.get_instance(str(db_path), test_settings)
    yield adapter
    BuildingMOTIFAdapter._instance = None
