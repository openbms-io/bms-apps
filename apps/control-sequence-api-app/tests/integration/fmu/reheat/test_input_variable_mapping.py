import pytest

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData, ReheatOutputVar
from src.adapters.sequence_type import SequenceType
from src.models.reheat.enums import OperationMode
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.parameters import ReheatParameters


class TestZoneTemperatureInput:

    @pytest.mark.asyncio
    async def test_zone_temp_in_comfort_range_minimal_action(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert ReheatOutputVar.DAMPER_POSITION in outputs
        assert ReheatOutputVar.VALVE_POSITION in outputs

    @pytest.mark.asyncio
    async def test_high_zone_temp_opens_damper(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        hot_inputs = base_inputs.model_copy(update={"zoneTemperature": 300.15})
        fmu_data = ReheatFMUData(inputs=hot_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(5):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] > 0.0

    @pytest.mark.asyncio
    async def test_low_zone_temp_opens_valve(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        cold_inputs = base_inputs.model_copy(update={"zoneTemperature": 291.15})
        fmu_data = ReheatFMUData(inputs=cold_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(5):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] > 0.0


class TestSetpointInputs:

    @pytest.mark.asyncio
    async def test_cooling_setpoint_below_zone_temp_triggers_cooling(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        cooling_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 296.15,
            "coolingSetpoint": 295.15,
        })
        fmu_data = ReheatFMUData(inputs=cooling_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(5):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] > 0.0

    @pytest.mark.asyncio
    async def test_heating_setpoint_above_zone_temp_triggers_heating(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        heating_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 292.15,
            "heatingSetpoint": 294.15,
        })
        fmu_data = ReheatFMUData(inputs=heating_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(5):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] > 0.0


class TestTemperatureInputs:

    @pytest.mark.asyncio
    async def test_discharge_air_temp_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"dischargeAirTemperature": 290.15})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_supply_air_temp_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"supplyAirTemperature": 288.15})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_supply_air_temp_setpoint_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"supplyAirTemperatureSetpoint": 284.15})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None


class TestAirflowInput:

    @pytest.mark.asyncio
    async def test_primary_airflow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"primaryAirflow": 0.5})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert ReheatOutputVar.AIRFLOW_SETPOINT in outputs


class TestCO2Inputs:

    @pytest.mark.asyncio
    async def test_co2_concentration_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"co2Concentration": 800.0})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_co2_setpoint_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"co2Setpoint": 900.0})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None


class TestOperationModeInput:

    @pytest.mark.asyncio
    async def test_all_operation_modes_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        for mode in OperationMode:
            mode_inputs = base_inputs.model_copy(update={"operationMode": mode})
            fmu_data = ReheatFMUData(inputs=mode_inputs, parameters=base_parameters)
            instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

            assert ReheatOutputVar.DAMPER_POSITION in outputs

            await fmu_adapter.delete_fmu_instance(instance_id)


class TestBooleanInputs:

    @pytest.mark.asyncio
    async def test_fan_status_off_reduces_damper(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fan_off_inputs = base_inputs.model_copy(update={"fanStatus": False})
        fmu_data = ReheatFMUData(inputs=fan_off_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] == pytest.approx(0.0, abs=0.05)

    @pytest.mark.asyncio
    async def test_hot_water_plant_status_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"hotWaterPlantStatus": False})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_occupancy_status_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"occupancyStatus": False})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_window_status_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"windowStatus": True})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_heating_off_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"heatingOff": True})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_all_boolean_inputs_true(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        all_true_inputs = base_inputs.model_copy(update={
            "fanStatus": True,
            "hotWaterPlantStatus": True,
            "occupancyStatus": True,
            "windowStatus": True,
            "heatingOff": True,
        })
        fmu_data = ReheatFMUData(inputs=all_true_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None


class TestOverrideInputs:

    @pytest.mark.asyncio
    async def test_override_damper_position_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"overrideDamperPosition": 1})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_override_flow_setpoint_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        inputs = base_inputs.model_copy(update={"overrideFlowSetpoint": 1})
        fmu_data = ReheatFMUData(inputs=inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs is not None
