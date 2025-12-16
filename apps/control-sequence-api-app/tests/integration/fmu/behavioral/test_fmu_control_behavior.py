import pytest

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData, ReheatOutputVar
from src.adapters.sequence_type import SequenceType
from src.models.reheat.enums import OperationMode
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.parameters import ReheatParameters


class TestCoolingBehavior:

    @pytest.mark.asyncio
    async def test_zone_above_cooling_setpoint_opens_damper(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        hot_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 300.15,
            "coolingSetpoint": 297.15,
        })
        fmu_data = ReheatFMUData(inputs=hot_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] > 0.1

    @pytest.mark.asyncio
    async def test_larger_cooling_error_opens_damper_more(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        small_error_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 298.15,
            "coolingSetpoint": 297.15,
        })
        large_error_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 302.15,
            "coolingSetpoint": 297.15,
        })

        small_data = ReheatFMUData(inputs=small_error_inputs, parameters=base_parameters)
        large_data = ReheatFMUData(inputs=large_error_inputs, parameters=base_parameters)

        id_small = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, small_data)
        id_large = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, large_data)

        for _ in range(10):
            outputs_small = await fmu_adapter.step(id_small, small_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
            outputs_large = await fmu_adapter.step(id_large, large_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs_large[ReheatOutputVar.DAMPER_POSITION] > outputs_small[ReheatOutputVar.DAMPER_POSITION]

    @pytest.mark.asyncio
    async def test_cooling_mode_valve_stays_closed(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        hot_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 300.15,
            "coolingSetpoint": 297.15,
        })
        fmu_data = ReheatFMUData(inputs=hot_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] == pytest.approx(0.0, abs=0.01)


class TestHeatingBehavior:

    @pytest.mark.asyncio
    async def test_zone_below_heating_setpoint_opens_valve(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        cold_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 290.15,
            "heatingSetpoint": 293.15,
        })
        fmu_data = ReheatFMUData(inputs=cold_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] > 0.1

    @pytest.mark.asyncio
    async def test_larger_heating_error_opens_valve_more(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        small_error_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 292.15,
            "heatingSetpoint": 293.15,
        })
        large_error_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 288.15,
            "heatingSetpoint": 293.15,
        })

        small_data = ReheatFMUData(inputs=small_error_inputs, parameters=base_parameters)
        large_data = ReheatFMUData(inputs=large_error_inputs, parameters=base_parameters)

        id_small = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, small_data)
        id_large = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, large_data)

        for _ in range(10):
            outputs_small = await fmu_adapter.step(id_small, small_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
            outputs_large = await fmu_adapter.step(id_large, large_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs_large[ReheatOutputVar.VALVE_POSITION] >= outputs_small[ReheatOutputVar.VALVE_POSITION]


class TestDeadbandBehavior:

    @pytest.mark.asyncio
    async def test_zone_in_deadband_minimal_action(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        comfort_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 295.15,
            "coolingSetpoint": 297.15,
            "heatingSetpoint": 293.15,
        })
        fmu_data = ReheatFMUData(inputs=comfort_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] < 0.1


class TestFanStatusBehavior:

    @pytest.mark.asyncio
    async def test_fan_off_closes_damper(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fan_off_inputs = base_inputs.model_copy(update={"fanStatus": False})
        fmu_data = ReheatFMUData(inputs=fan_off_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] == pytest.approx(0.0, abs=0.05)

    @pytest.mark.asyncio
    async def test_fan_on_allows_damper_control(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        hot_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 300.15,
            "fanStatus": True,
        })
        fmu_data = ReheatFMUData(inputs=hot_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] > 0.0


class TestOperationModes:

    @pytest.mark.asyncio
    async def test_occupied_mode_normal_operation(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        occupied_inputs = base_inputs.model_copy(update={
            "operationMode": OperationMode.OCCUPIED,
            "zoneTemperature": 300.15,
        })
        fmu_data = ReheatFMUData(inputs=occupied_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] > 0.0

    @pytest.mark.asyncio
    async def test_unoccupied_mode_reduces_ventilation(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        occupied_inputs = base_inputs.model_copy(update={
            "operationMode": OperationMode.OCCUPIED,
        })
        unoccupied_inputs = base_inputs.model_copy(update={
            "operationMode": OperationMode.UNOCCUPIED,
        })

        occupied_data = ReheatFMUData(inputs=occupied_inputs, parameters=base_parameters)
        unoccupied_data = ReheatFMUData(inputs=unoccupied_inputs, parameters=base_parameters)

        id_occ = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, occupied_data)
        id_unocc = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, unoccupied_data)

        for _ in range(10):
            outputs_occ = await fmu_adapter.step(id_occ, occupied_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
            outputs_unocc = await fmu_adapter.step(id_unocc, unoccupied_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs_unocc[ReheatOutputVar.AIRFLOW_SETPOINT] <= outputs_occ[ReheatOutputVar.AIRFLOW_SETPOINT]


class TestOutputBounds:

    @pytest.mark.asyncio
    async def test_damper_position_never_exceeds_1(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        extreme_hot_inputs = base_inputs.model_copy(update={"zoneTemperature": 310.15})
        fmu_data = ReheatFMUData(inputs=extreme_hot_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(20):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] <= 1.0

    @pytest.mark.asyncio
    async def test_damper_position_never_below_0(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(20):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.DAMPER_POSITION] >= 0.0

    @pytest.mark.asyncio
    async def test_valve_position_never_exceeds_1(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        extreme_cold_inputs = base_inputs.model_copy(update={"zoneTemperature": 280.15})
        fmu_data = ReheatFMUData(inputs=extreme_cold_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(20):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] <= 1.0

    @pytest.mark.asyncio
    async def test_valve_position_never_below_0(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(20):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] >= 0.0


class TestAirflowSetpoint:

    @pytest.mark.asyncio
    async def test_airflow_setpoint_respects_max_cooling(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        max_flow = 0.8
        params = base_parameters.model_copy(update={"maxCoolingAirflow": max_flow})
        hot_inputs = base_inputs.model_copy(update={"zoneTemperature": 305.15})
        fmu_data = ReheatFMUData(inputs=hot_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(20):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.AIRFLOW_SETPOINT] <= max_flow + 0.01

    @pytest.mark.asyncio
    async def test_airflow_setpoint_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.AIRFLOW_SETPOINT] >= 0.0


class TestHeatingOffSignal:

    @pytest.mark.asyncio
    async def test_heating_off_prevents_valve_opening(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        cold_heating_off_inputs = base_inputs.model_copy(update={
            "zoneTemperature": 288.15,
            "heatingSetpoint": 293.15,
            "heatingOff": True,
        })
        fmu_data = ReheatFMUData(inputs=cold_heating_off_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(10):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs[ReheatOutputVar.VALVE_POSITION] == pytest.approx(0.0, abs=0.05)
