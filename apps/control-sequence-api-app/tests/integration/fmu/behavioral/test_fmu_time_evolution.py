import pytest

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData, ReheatOutputVar
from src.adapters.sequence_type import SequenceType
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.parameters import ReheatParameters


class TestTimeInitialization:

    def test_new_instance_starts_at_time_zero(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        assert fmu_adapter.get_current_time(instance_id) == 0.0


class TestTimeAdvancement:

    @pytest.mark.asyncio
    async def test_step_advances_time_by_step_size(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 60.0

    @pytest.mark.asyncio
    async def test_multiple_steps_accumulate_time(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)
        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)
        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 180.0

    @pytest.mark.asyncio
    async def test_variable_step_sizes_accumulate_correctly(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        await fmu_adapter.step(instance_id, fmu_data, step_size=30.0, sequence_type=SequenceType.REHEAT)
        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)
        await fmu_adapter.step(instance_id, fmu_data, step_size=120.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 210.0


class TestStepSizes:

    @pytest.mark.asyncio
    async def test_small_step_size_1_second(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=1.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 1.0
        assert outputs is not None

    @pytest.mark.asyncio
    async def test_medium_step_size_60_seconds(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 60.0
        assert outputs is not None

    @pytest.mark.asyncio
    async def test_large_step_size_300_seconds(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=300.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 300.0
        assert outputs is not None

    @pytest.mark.asyncio
    async def test_fractional_step_size(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=0.5, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 0.5
        assert outputs is not None


class TestLongSimulation:

    @pytest.mark.asyncio
    async def test_simulate_one_hour(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        for _ in range(60):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 3600.0
        assert outputs is not None

    @pytest.mark.asyncio
    async def test_outputs_remain_valid_after_many_steps(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        for _ in range(100):
            outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        damper = outputs[ReheatOutputVar.DAMPER_POSITION]
        valve = outputs[ReheatOutputVar.VALVE_POSITION]

        assert 0.0 <= damper <= 1.0
        assert 0.0 <= valve <= 1.0


class TestDynamicInputChanges:

    @pytest.mark.asyncio
    async def test_changing_inputs_during_simulation(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        for _ in range(5):
            await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        hot_inputs = base_inputs.model_copy(update={"zoneTemperature": 300.15})
        hot_data = ReheatFMUData(inputs=hot_inputs, parameters=base_parameters)

        for _ in range(5):
            outputs = await fmu_adapter.step(instance_id, hot_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 600.0
        assert outputs[ReheatOutputVar.DAMPER_POSITION] > 0.0

    @pytest.mark.asyncio
    async def test_alternating_heating_cooling_demand(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        hot_inputs = base_inputs.model_copy(update={"zoneTemperature": 300.15})
        cold_inputs = base_inputs.model_copy(update={"zoneTemperature": 290.15})

        hot_data = ReheatFMUData(inputs=hot_inputs, parameters=base_parameters)
        cold_data = ReheatFMUData(inputs=cold_inputs, parameters=base_parameters)

        for _ in range(5):
            await fmu_adapter.step(instance_id, hot_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        for _ in range(5):
            await fmu_adapter.step(instance_id, cold_data, step_size=60.0, sequence_type=SequenceType.REHEAT)

        assert fmu_adapter.get_current_time(instance_id) == 600.0


class TestUpdateWithoutStep:

    @pytest.mark.asyncio
    async def test_update_inputs_does_not_advance_time(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.REHEAT)
        time_before = fmu_adapter.get_current_time(instance_id)

        new_inputs = base_inputs.model_copy(update={"zoneTemperature": 298.15})
        new_data = ReheatFMUData(inputs=new_inputs, parameters=base_parameters)
        await fmu_adapter.update_fmu_instance(instance_id, new_data)

        time_after = fmu_adapter.get_current_time(instance_id)

        assert time_before == time_after == 60.0
