from pathlib import Path

import pytest
from fastapi.testclient import TestClient

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_loader import FmuLoader
from src.dto.reheat_dto import OperationMode, ReheatInputs, ReheatParameters
from src.main import app


@pytest.fixture
def client() -> TestClient:
    return TestClient(app)


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
    return ReheatParameters()
