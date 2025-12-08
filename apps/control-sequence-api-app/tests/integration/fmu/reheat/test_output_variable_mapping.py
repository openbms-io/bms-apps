import pytest

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData, ReheatOutputVar
from src.adapters.sequence_type import SequenceType
from src.dto.reheat_dto import ReheatInputs, ReheatParameters


class TestAllOutputsPresent:

    @pytest.mark.asyncio
    async def test_all_15_outputs_returned(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        expected_outputs = [
            ReheatOutputVar.DAMPER_POSITION,
            ReheatOutputVar.VALVE_POSITION,
            ReheatOutputVar.AIRFLOW_SETPOINT,
            ReheatOutputVar.MIN_OA_AIRFLOW,
            ReheatOutputVar.ADJ_AREA_BREATHING_ZONE_FLOW,
            ReheatOutputVar.ADJ_POP_BREATHING_ZONE_FLOW,
            ReheatOutputVar.FLOW_SENSOR_ALARM,
            ReheatOutputVar.HEATING_VALVE_REQUEST,
            ReheatOutputVar.HOT_WATER_PLANT_REQUEST,
            ReheatOutputVar.LEAKING_DAMPER_ALARM,
            ReheatOutputVar.LEAKING_VALVE_ALARM,
            ReheatOutputVar.LOW_FLOW_ALARM,
            ReheatOutputVar.LOW_TEMP_ALARM,
            ReheatOutputVar.ZONE_PRESSURE_REQUEST,
            ReheatOutputVar.ZONE_TEMP_REQUEST,
        ]

        for output_var in expected_outputs:
            assert output_var.value in outputs, f"Missing output: {output_var}"


class TestDamperPositionOutput:

    @pytest.mark.asyncio
    async def test_damper_position_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.DAMPER_POSITION], float)

    @pytest.mark.asyncio
    async def test_damper_position_bounded_0_to_1(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        damper = outputs[ReheatOutputVar.DAMPER_POSITION]
        assert 0.0 <= damper <= 1.0


class TestValvePositionOutput:

    @pytest.mark.asyncio
    async def test_valve_position_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.VALVE_POSITION], float)

    @pytest.mark.asyncio
    async def test_valve_position_bounded_0_to_1(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        valve = outputs[ReheatOutputVar.VALVE_POSITION]
        assert 0.0 <= valve <= 1.0


class TestAirflowOutputs:

    @pytest.mark.asyncio
    async def test_airflow_setpoint_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatOutputVar.AIRFLOW_SETPOINT] >= 0.0

    @pytest.mark.asyncio
    async def test_min_oa_airflow_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatOutputVar.MIN_OA_AIRFLOW] >= 0.0

    @pytest.mark.asyncio
    async def test_adj_area_breathing_zone_flow_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatOutputVar.ADJ_AREA_BREATHING_ZONE_FLOW] >= 0.0

    @pytest.mark.asyncio
    async def test_adj_pop_breathing_zone_flow_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatOutputVar.ADJ_POP_BREATHING_ZONE_FLOW] >= 0.0


class TestAlarmOutputs:

    @pytest.mark.asyncio
    async def test_flow_sensor_alarm_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.FLOW_SENSOR_ALARM], int)

    @pytest.mark.asyncio
    async def test_leaking_damper_alarm_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.LEAKING_DAMPER_ALARM], int)

    @pytest.mark.asyncio
    async def test_leaking_valve_alarm_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.LEAKING_VALVE_ALARM], int)

    @pytest.mark.asyncio
    async def test_low_flow_alarm_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.LOW_FLOW_ALARM], int)

    @pytest.mark.asyncio
    async def test_low_temp_alarm_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.LOW_TEMP_ALARM], int)

    @pytest.mark.asyncio
    async def test_alarm_outputs_in_valid_range(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        alarm_outputs = [
            ReheatOutputVar.FLOW_SENSOR_ALARM,
            ReheatOutputVar.LEAKING_DAMPER_ALARM,
            ReheatOutputVar.LEAKING_VALVE_ALARM,
            ReheatOutputVar.LOW_FLOW_ALARM,
            ReheatOutputVar.LOW_TEMP_ALARM,
        ]

        for alarm in alarm_outputs:
            value = outputs[alarm.value]
            assert 0 <= value <= 4, f"{alarm} should be 0-4, got {value}"


class TestRequestOutputs:

    @pytest.mark.asyncio
    async def test_heating_valve_request_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.HEATING_VALVE_REQUEST], int)

    @pytest.mark.asyncio
    async def test_hot_water_plant_request_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.HOT_WATER_PLANT_REQUEST], int)

    @pytest.mark.asyncio
    async def test_zone_pressure_request_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.ZONE_PRESSURE_REQUEST], int)

    @pytest.mark.asyncio
    async def test_zone_temp_request_is_integer(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatOutputVar.ZONE_TEMP_REQUEST], int)

    @pytest.mark.asyncio
    async def test_request_outputs_in_valid_range(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        request_outputs = [
            ReheatOutputVar.HEATING_VALVE_REQUEST,
            ReheatOutputVar.HOT_WATER_PLANT_REQUEST,
            ReheatOutputVar.ZONE_PRESSURE_REQUEST,
            ReheatOutputVar.ZONE_TEMP_REQUEST,
        ]

        for request in request_outputs:
            value = outputs[request.value]
            assert 0 <= value <= 3, f"{request} should be 0-3, got {value}"
