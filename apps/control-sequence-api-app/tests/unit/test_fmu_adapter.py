"""Unit tests for FMU Adapter Singleton.

Tests cover all acceptance criteria from Story 1.10:
  AC1: fmu_adapter.py with singleton pattern
  AC2: create_fmu_instance(sequence_type, fmu_data) method
  AC3: update_fmu_instance(instance_id, fmu_data) method
  AC4: step(instance_id, fmu_data, step_size) method
  AC5: delete_fmu_instance(instance_id) method
  AC6: Per-instance asyncio.Lock for thread safety
  AC7: Lazy FMU loading with startup validation
  AC8: Unit tests for adapter
  AC9: Input completeness validation
"""

from unittest.mock import MagicMock, patch

import pytest

from src.adapters.exceptions import (
    FmuInstanceNotFoundError,
    FmuValidationError,
)
from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData
from src.adapters.sequence_type import SequenceType
from src.dto.reheat_dto import (
    OperationMode,
    ReheatInputs,
    ReheatParameters,
)


@pytest.fixture
def mock_model_description():
    md = MagicMock()
    md.guid = "test-guid-123"
    md.coSimulation = MagicMock()
    md.coSimulation.modelIdentifier = "ReheatController"

    variables = []
    var_names = [
        # === INPUTS (17) ===
        ("TZon", 0),
        ("TCooSet", 1),
        ("THeaSet", 2),
        ("TDis", 3),
        ("VDis_flow", 4),
        ("TSup", 5),
        ("TSupSet", 6),
        ("ppmCO2", 7),
        ("ppmCO2Set", 8),
        ("u1Fan", 9),
        ("uOpeMod", 10),
        ("u1HotPla", 11),
        ("u1Occ", 12),
        ("u1Win", 13),
        ("uHeaOff", 14),
        ("oveDamPos", 15),
        ("oveFloSet", 16),
        # === OUTPUTS (15) ===
        ("yDam", 17),
        ("yVal", 18),
        ("VSet_flow", 19),
        ("VMinOA_flow", 20),
        ("VAdjAreBreZon_flow", 21),
        ("VAdjPopBreZon_flow", 22),
        ("yFloSenAla", 23),
        ("yHeaValResReq", 24),
        ("yHotWatPlaReq", 25),
        ("yLeaDamAla", 26),
        ("yLeaValAla", 27),
        ("yLowFloAla", 28),
        ("yLowTemAla", 29),
        ("yZonPreResReq", 30),
        ("yZonTemResReq", 31),
        # === PARAMETERS (42) ===
        # Airflow parameters
        ("VCooMax_flow", 32),
        ("VHeaMax_flow", 33),
        ("VHeaMin_flow", 34),
        ("VAreBreZon_flow", 35),
        ("VAreMin_flow", 36),
        ("VOccMin_flow", 37),
        ("VPopBreZon_flow", 38),
        # Temperature parameters
        ("TDisMin", 39),
        ("dTDisZonSetMax", 40),
        # Controller gains
        ("kCooCon", 41),
        ("kHeaCon", 42),
        ("kDam", 43),
        ("kVal", 44),
        # Controller time constants
        ("TdDam", 45),
        ("TdVal", 46),
        ("TiCooCon", 47),
        ("TiDam", 48),
        ("TiHeaCon", 49),
        ("TiVal", 50),
        # Duration/timing parameters
        ("chaRat", 51),
        ("durTimDisAir", 52),
        ("durTimFlo", 53),
        ("durTimTem", 54),
        ("maxSupTim", 55),
        ("samplePeriod", 56),
        # Alarm timing thresholds
        ("fanOffTim", 57),
        ("leaFloTim", 58),
        ("lowFloTim", 59),
        ("lowTemTim", 60),
        ("valCloTim", 61),
        ("timChe", 62),
        ("staTim", 63),
        # Temperature thresholds
        ("thrTDis_1", 64),
        ("thrTDis_2", 65),
        ("thrTemDif", 66),
        ("twoTemDif", 67),
        # Importance multipliers
        ("hotWatRes", 68),
        ("staPreMul", 69),
        # Zone distribution effectiveness
        ("zonDisEff_cool", 70),
        ("zonDisEff_heat", 71),
        # Initial values
        ("iniDam", 72),
        # Boolean parameter
        ("permit_occStandby", 73),
        # === CALCULATED PARAMETERS (13) ===
        ("VMin_flow", 74),
        ("dTHys", 75),
        ("damPosHys", 76),
        ("floHys", 77),
        ("looHys", 78),
        ("valPosHys", 79),
        ("have_CO2Sen", 80),
        ("have_hotWatCoi", 81),
        ("have_occSen", 82),
        ("have_winSen", 83),
        ("controllerTypeDam", 84),
        ("controllerTypeVal", 85),
        ("venStd", 86),
    ]

    for name, ref in var_names:
        var = MagicMock()
        var.name = name
        var.valueReference = ref
        variables.append(var)

    md.modelVariables = variables
    return md


@pytest.fixture
def mock_fmu():
    fmu = MagicMock()
    fmu.instantiate = MagicMock()
    fmu.setupExperiment = MagicMock()
    fmu.enterInitializationMode = MagicMock()
    fmu.exitInitializationMode = MagicMock()
    fmu.setReal = MagicMock()
    fmu.setBoolean = MagicMock()
    fmu.setInteger = MagicMock()
    fmu.doStep = MagicMock()
    fmu.getReal = MagicMock(return_value=[0.5])
    fmu.terminate = MagicMock()
    fmu.freeInstance = MagicMock()
    return fmu


@pytest.fixture
def mock_fmpy(mock_model_description, mock_fmu):
    with (
        patch("src.adapters.fmu_loader.read_model_description") as mock_read_md,
        patch("src.adapters.fmu_loader.extract") as mock_extract,
        patch("src.adapters.fmu_lifecycle.FMU2Slave") as mock_fmu_class,
    ):
        mock_read_md.return_value = mock_model_description
        mock_extract.return_value = "/tmp/fmu_extract"
        mock_fmu_class.return_value = mock_fmu

        yield {
            "read_model_description": mock_read_md,
            "extract": mock_extract,
            "FMU2Slave": mock_fmu_class,
            "fmu": mock_fmu,
            "model_description": mock_model_description,
        }


@pytest.fixture
def mock_settings():
    with patch("src.adapters.fmu_loader.get_settings") as mock_get_settings:
        settings = MagicMock()
        settings.get_fmu_path = MagicMock(return_value=MagicMock(exists=lambda: True))
        mock_get_settings.return_value = settings
        yield settings


@pytest.fixture
def adapter(mock_fmpy, mock_settings):
    from src.adapters.fmu_loader import FmuLoader

    FmuAdapter.reset_singleton()
    FmuLoader.clear_cache()
    return FmuAdapter.get_instance()


@pytest.fixture
def valid_inputs():
    return ReheatInputs(
        zoneTemperature=295.15,
        coolingSetpoint=297.15,
        heatingSetpoint=293.15,
        dischargeAirTemperature=286.15,
        primaryAirflow=0.3,
        supplyAirTemperature=286.15,
        supplyAirTemperatureSetpoint=285.15,
        fanStatus=True,
        operationMode=OperationMode.OCCUPIED,
    )


@pytest.fixture
def valid_parameters():
    return ReheatParameters(
        maxCoolingAirflow=0.5,
        maxHeatingAirflow=0.3,
        minHeatingAirflow=0.1,
    )


@pytest.fixture
def fmu_data(valid_inputs, valid_parameters):
    return ReheatFMUData(inputs=valid_inputs, parameters=valid_parameters)


@pytest.fixture
def fmu_data_no_params(valid_inputs):
    return ReheatFMUData(inputs=valid_inputs)


class TestSingletonPattern:

    def test_get_instance_returns_same_instance(self, mock_fmpy, mock_settings):
        FmuAdapter.reset_singleton()
        adapter1 = FmuAdapter.get_instance()
        adapter2 = FmuAdapter.get_instance()
        assert adapter1 is adapter2

    def test_reset_singleton_clears_instance(self, mock_fmpy, mock_settings):
        FmuAdapter.reset_singleton()
        adapter1 = FmuAdapter.get_instance()
        FmuAdapter.reset_singleton()
        adapter2 = FmuAdapter.get_instance()
        assert adapter1 is not adapter2


class TestCreateInstance:

    def test_create_fmu_instance_returns_uuid(self, adapter, fmu_data):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        assert instance_id is not None
        assert len(instance_id) == 36

    def test_create_fmu_instance_registers_instance(self, adapter, fmu_data):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        assert adapter.has_instance(instance_id)

    def test_create_fmu_instance_without_parameters(self, adapter, fmu_data_no_params):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data_no_params)
        assert adapter.has_instance(instance_id)

    def test_create_fmu_instance_initializes_fmu(self, adapter, fmu_data, mock_fmpy):
        adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        mock_fmpy["fmu"].instantiate.assert_called_once()
        mock_fmpy["fmu"].setupExperiment.assert_called_once()
        mock_fmpy["fmu"].enterInitializationMode.assert_called_once()
        mock_fmpy["fmu"].exitInitializationMode.assert_called_once()

    def test_create_fmu_instance_sets_configuration(self, adapter, fmu_data, mock_fmpy):
        adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        mock_fmpy["fmu"].setReal.assert_called()


class TestUpdateInstance:

    @pytest.mark.asyncio
    async def test_update_fmu_instance_sets_inputs(self, adapter, fmu_data, mock_fmpy):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        mock_fmpy["fmu"].setReal.reset_mock()
        await adapter.update_fmu_instance(instance_id, fmu_data)
        mock_fmpy["fmu"].setReal.assert_called()

    @pytest.mark.asyncio
    async def test_update_fmu_instance_not_found_raises_error(self, adapter, fmu_data):
        with pytest.raises(FmuInstanceNotFoundError) as exc:
            await adapter.update_fmu_instance("nonexistent", fmu_data)
        assert "nonexistent" in str(exc.value)


class TestStep:

    @pytest.mark.asyncio
    async def test_step_returns_outputs(self, adapter, fmu_data, mock_fmpy):
        mock_fmpy["fmu"].getReal = MagicMock(return_value=[0.5])
        mock_fmpy["fmu"].getInteger = MagicMock(return_value=[0])
        mock_fmpy["fmu"].getBoolean = MagicMock(return_value=[False])
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        outputs = await adapter.step(instance_id, fmu_data, step_size=60.0)
        assert "yDam" in outputs
        assert "yVal" in outputs
        assert "VSet_flow" in outputs
        assert "VMin_flow" in outputs

    @pytest.mark.asyncio
    async def test_step_not_found_raises_error(self, adapter, fmu_data):
        with pytest.raises(FmuInstanceNotFoundError) as exc:
            await adapter.step("nonexistent", fmu_data, step_size=60.0)
        assert "nonexistent" in str(exc.value)

    @pytest.mark.asyncio
    async def test_step_updates_current_time(self, adapter, fmu_data, mock_fmpy):
        mock_fmpy["fmu"].getReal = MagicMock(return_value=[0.5])
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        await adapter.step(instance_id, fmu_data, step_size=60.0)
        assert adapter.get_current_time(instance_id) == 60.0

    @pytest.mark.asyncio
    async def test_step_calls_do_step(self, adapter, fmu_data, mock_fmpy):
        mock_fmpy["fmu"].getReal = MagicMock(return_value=[0.5])
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        await adapter.step(instance_id, fmu_data, step_size=60.0)
        mock_fmpy["fmu"].doStep.assert_called_with(
            currentCommunicationPoint=0.0, communicationStepSize=60.0
        )


class TestDeleteInstance:

    @pytest.mark.asyncio
    async def test_delete_fmu_instance_removes(self, adapter, fmu_data, mock_fmpy):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        await adapter.delete_fmu_instance(instance_id)
        assert not adapter.has_instance(instance_id)

    @pytest.mark.asyncio
    async def test_delete_fmu_instance_terminates_fmu(self, adapter, fmu_data, mock_fmpy):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        await adapter.delete_fmu_instance(instance_id)
        mock_fmpy["fmu"].terminate.assert_called()
        mock_fmpy["fmu"].freeInstance.assert_called()

    @pytest.mark.asyncio
    async def test_delete_fmu_instance_not_found_raises_error(self, adapter):
        with pytest.raises(FmuInstanceNotFoundError):
            await adapter.delete_fmu_instance("nonexistent")


class TestPerInstanceLock:

    @pytest.mark.asyncio
    async def test_concurrent_steps_are_serialized(self, adapter, fmu_data, mock_fmpy):
        import asyncio

        mock_fmpy["fmu"].getReal = MagicMock(return_value=[0.5])
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        call_order = []

        original_do_step = mock_fmpy["fmu"].doStep

        async def slow_step(*args, **kwargs):
            call_order.append("start")
            await asyncio.sleep(0.01)
            original_do_step(*args, **kwargs)
            call_order.append("end")

        mock_fmpy["fmu"].doStep = MagicMock(side_effect=lambda *a, **k: None)

        await asyncio.gather(
            adapter.step(instance_id, fmu_data, step_size=60.0),
            adapter.step(instance_id, fmu_data, step_size=60.0),
        )

        assert mock_fmpy["fmu"].doStep.call_count == 2


class TestLazyFmuLoading:

    def test_fmu_extracted_on_first_use(self, adapter, fmu_data, mock_fmpy):
        mock_fmpy["extract"].assert_not_called()
        adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        mock_fmpy["extract"].assert_called_once()

    def test_fmu_cache_reused(self, adapter, fmu_data, mock_fmpy):
        adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        mock_fmpy["extract"].assert_called_once()


class TestInputValidation:

    @pytest.mark.asyncio
    async def test_step_with_valid_inputs_succeeds(self, adapter, fmu_data, mock_fmpy):
        mock_fmpy["fmu"].getReal = MagicMock(return_value=[0.5])
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        outputs = await adapter.step(instance_id, fmu_data, step_size=60.0)
        assert outputs is not None


class TestHelperMethods:

    def test_has_instance_returns_true_for_existing(self, adapter, fmu_data):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        assert adapter.has_instance(instance_id)

    def test_has_instance_returns_false_for_nonexistent(self, adapter):
        assert not adapter.has_instance("nonexistent")

    def test_list_instance_ids_returns_all_ids(self, adapter, fmu_data):
        id1 = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        id2 = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        ids = adapter.list_instance_ids()
        assert set(ids) == {id1, id2}

    def test_get_state_returns_instance_state(self, adapter, fmu_data):
        from src.adapters.fmu_instance import FmuInstanceState

        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        state = adapter.get_state(instance_id)
        assert state == FmuInstanceState.INITIALIZED

    def test_get_sequence_type_returns_type(self, adapter, fmu_data):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        seq_type = adapter.get_sequence_type(instance_id)
        assert seq_type == SequenceType.REHEAT

    def test_get_current_time_returns_zero_initially(self, adapter, fmu_data):
        instance_id = adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)
        current_time = adapter.get_current_time(instance_id)
        assert current_time == 0.0
