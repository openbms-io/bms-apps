import asyncio
from pathlib import Path
from uuid import uuid4

import pytest
import pytest_asyncio
from fastapi.testclient import TestClient

from src.adapters.database_adapter import initialize_database, reset_database_state
from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_loader import FmuLoader
from src.models.reheat.enums import OperationMode
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.parameters import ReheatParameters
from src.utils.unit_conversion import TemperatureUnit
from src.main import app


def create_reheat_instance(
    client: TestClient,
    instance_id: str | None = None,
    parameters: dict | None = None,
) -> dict:
    """Helper to create a reheat instance with the new API that requires instance_id."""
    if instance_id is None:
        instance_id = str(uuid4())
    body: dict = {"instance_id": instance_id}
    if parameters is not None:
        body["parameters"] = parameters
    response = client.post(
        "/api/v1/g36/vav-reheat/instances",
        json=body,
    )
    return response.json()


@pytest.fixture
def client() -> TestClient:
    return TestClient(app)


@pytest.fixture
def integration_client():
    FmuAdapter.reset_singleton()
    FmuLoader.clear_cache()
    asyncio.run(initialize_database())
    reset_database_state()
    with TestClient(app) as client:
        yield client
    FmuAdapter.reset_singleton()
    FmuLoader.clear_cache()
    reset_database_state()


@pytest_asyncio.fixture
async def test_db(tmp_path: Path, monkeypatch):
    """Create a temporary test database for integration tests."""
    from src.adapters.database_adapter import close_database
    from src.config.settings import get_settings

    db_path = tmp_path / "test_control_sequence.db"
    reset_database_state()
    get_settings.cache_clear()
    monkeypatch.setenv("DATABASE_PATH", str(db_path))
    await initialize_database()
    yield db_path
    await close_database()
    reset_database_state()
    get_settings.cache_clear()


@pytest.fixture
def fmu_available() -> bool:
    app_root = Path(__file__).parent.parent
    fmu_path = app_root / "fmu-sequence" / "reheat" / "ReheatControllerFMU.fmu"
    return fmu_path.exists()


@pytest.fixture
def fmu_adapter(fmu_available: bool):
    if not fmu_available:
        pytest.skip("Reheat FMU not available")
    FmuAdapter.reset_singleton()
    FmuLoader.clear_cache()
    adapter = FmuAdapter.get_instance()
    yield adapter
    FmuAdapter.reset_singleton()
    FmuLoader.clear_cache()


@pytest.fixture
def base_inputs() -> ReheatInputs:
    return ReheatInputs(
        zoneTemperature=295.15,
        coolingSetpoint=297.15,
        heatingSetpoint=293.15,
        dischargeAirTemperature=286.15,
        primaryAirflow=0.3,
        supplyAirTemperature=286.15,
        supplyAirTemperatureSetpoint=285.15,
        co2Concentration=400.0,
        co2Setpoint=1000.0,
        fanStatus=True,
        operationMode=OperationMode.OCCUPIED,
        hotWaterPlantStatus=True,
        occupancyStatus=True,
        windowStatus=False,
        heatingOff=False,
        overrideDamperPosition=0,
        overrideFlowSetpoint=0,
    )


@pytest.fixture
def base_parameters() -> ReheatParameters:
    return ReheatParameters(temperatureUnit=TemperatureUnit.KELVIN)
