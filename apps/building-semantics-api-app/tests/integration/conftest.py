"""Shared fixtures for integration tests."""
import pytest

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.config.settings import Settings


@pytest.fixture(scope="session")
def shared_adapter(tmp_path_factory):
    """BuildingMOTIF adapter with isolated database per xdist worker."""
    BuildingMOTIFAdapter._instance = None

    db_path = tmp_path_factory.mktemp("data") / "buildingmotif.db"

    test_settings = Settings(
        buildingmotif_templates_path="apps/building-semantics-api-app/data/libraries/ashrae-223p-nrel",
        enable_validation=True,
    )
    adapter = BuildingMOTIFAdapter(str(db_path), test_settings)
    yield adapter
    BuildingMOTIFAdapter._instance = None
