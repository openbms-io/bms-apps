import pytest

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatCalcParamVar, ReheatFMUData
from src.adapters.sequence_type import SequenceType
from src.dto.reheat_dto import ReheatInputs, ReheatParameters


class TestAllCalculatedParametersPresent:

    @pytest.mark.asyncio
    async def test_all_13_calculated_parameters_returned(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        expected_calc_params = [
            ReheatCalcParamVar.MIN_AIRFLOW,
            ReheatCalcParamVar.TEMP_HYSTERESIS,
            ReheatCalcParamVar.DAMPER_POSITION_HYSTERESIS,
            ReheatCalcParamVar.FLOW_HYSTERESIS,
            ReheatCalcParamVar.LOOP_HYSTERESIS,
            ReheatCalcParamVar.VALVE_POSITION_HYSTERESIS,
            ReheatCalcParamVar.HAS_CO2_SENSOR,
            ReheatCalcParamVar.HAS_HOT_WATER_COIL,
            ReheatCalcParamVar.HAS_OCCUPANCY_SENSOR,
            ReheatCalcParamVar.HAS_WINDOW_SENSOR,
            ReheatCalcParamVar.CONTROLLER_TYPE_DAMPER,
            ReheatCalcParamVar.CONTROLLER_TYPE_VALVE,
            ReheatCalcParamVar.VENTILATION_STANDARD,
        ]

        for calc_param in expected_calc_params:
            assert calc_param.value in outputs, f"Missing calc param: {calc_param}"


class TestMinAirflowCalculatedParameter:

    @pytest.mark.asyncio
    async def test_min_airflow_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.MIN_AIRFLOW], float)

    @pytest.mark.asyncio
    async def test_min_airflow_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatCalcParamVar.MIN_AIRFLOW] >= 0.0


class TestHysteresisCalculatedParameters:

    @pytest.mark.asyncio
    async def test_temp_hysteresis_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.TEMP_HYSTERESIS], float)

    @pytest.mark.asyncio
    async def test_temp_hysteresis_positive(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatCalcParamVar.TEMP_HYSTERESIS] >= 0.0

    @pytest.mark.asyncio
    async def test_damper_position_hysteresis_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.DAMPER_POSITION_HYSTERESIS], float)

    @pytest.mark.asyncio
    async def test_damper_position_hysteresis_bounded(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.DAMPER_POSITION_HYSTERESIS]
        assert 0.0 <= value <= 1.0

    @pytest.mark.asyncio
    async def test_flow_hysteresis_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.FLOW_HYSTERESIS], float)

    @pytest.mark.asyncio
    async def test_flow_hysteresis_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatCalcParamVar.FLOW_HYSTERESIS] >= 0.0

    @pytest.mark.asyncio
    async def test_loop_hysteresis_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.LOOP_HYSTERESIS], float)

    @pytest.mark.asyncio
    async def test_loop_hysteresis_non_negative(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs[ReheatCalcParamVar.LOOP_HYSTERESIS] >= 0.0

    @pytest.mark.asyncio
    async def test_valve_position_hysteresis_is_float(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.VALVE_POSITION_HYSTERESIS], float)

    @pytest.mark.asyncio
    async def test_valve_position_hysteresis_bounded(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.VALVE_POSITION_HYSTERESIS]
        assert 0.0 <= value <= 1.0


class TestBooleanCalculatedParameters:

    @pytest.mark.asyncio
    async def test_has_co2_sensor_is_bool_convertible(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.HAS_CO2_SENSOR]
        assert value in (True, False, 0, 1)

    @pytest.mark.asyncio
    async def test_has_hot_water_coil_is_bool_convertible(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.HAS_HOT_WATER_COIL]
        assert value in (True, False, 0, 1)

    @pytest.mark.asyncio
    async def test_has_occupancy_sensor_is_bool_convertible(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.HAS_OCCUPANCY_SENSOR]
        assert value in (True, False, 0, 1)

    @pytest.mark.asyncio
    async def test_has_window_sensor_is_bool_convertible(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.HAS_WINDOW_SENSOR]
        assert value in (True, False, 0, 1)


class TestEnumCalculatedParameters:

    @pytest.mark.asyncio
    async def test_controller_type_damper_is_int(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.CONTROLLER_TYPE_DAMPER], int)

    @pytest.mark.asyncio
    async def test_controller_type_damper_valid_range(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.CONTROLLER_TYPE_DAMPER]
        assert 1 <= value <= 4

    @pytest.mark.asyncio
    async def test_controller_type_valve_is_int(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.CONTROLLER_TYPE_VALVE], int)

    @pytest.mark.asyncio
    async def test_controller_type_valve_valid_range(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.CONTROLLER_TYPE_VALVE]
        assert 1 <= value <= 4

    @pytest.mark.asyncio
    async def test_ventilation_standard_is_int(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert isinstance(outputs[ReheatCalcParamVar.VENTILATION_STANDARD], int)

    @pytest.mark.asyncio
    async def test_ventilation_standard_valid_range(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        value = outputs[ReheatCalcParamVar.VENTILATION_STANDARD]
        assert 1 <= value <= 2
