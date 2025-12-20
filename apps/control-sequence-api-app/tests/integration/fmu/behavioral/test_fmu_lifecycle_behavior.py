import pytest

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData
from src.adapters.fmu_instance import FmuInstanceState
from src.adapters.sequence_type import SequenceType
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.parameters import ReheatParameters


class TestInstanceCreation:

    def test_create_instance_returns_uuid(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        assert instance_id is not None
        assert len(instance_id) == 36
        assert instance_id.count("-") == 4

    def test_create_instance_registers_in_adapter(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        assert fmu_adapter.has_instance(instance_id)

    def test_create_multiple_instances_unique_ids(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        id1 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id2 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id3 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        assert id1 != id2 != id3
        assert fmu_adapter.has_instance(id1)
        assert fmu_adapter.has_instance(id2)
        assert fmu_adapter.has_instance(id3)

    def test_list_instance_ids_returns_all(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        id1 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id2 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        ids = fmu_adapter.list_instance_ids()

        assert set(ids) == {id1, id2}


class TestStateTransitions:

    def test_new_instance_state_is_initialized(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        assert fmu_adapter.get_state(instance_id) == FmuInstanceState.INITIALIZED

    @pytest.mark.asyncio
    async def test_step_changes_state_to_running(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert fmu_adapter.get_state(instance_id) == FmuInstanceState.RUNNING

    @pytest.mark.asyncio
    async def test_multiple_steps_remain_running(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        for _ in range(5):
            await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert fmu_adapter.get_state(instance_id) == FmuInstanceState.RUNNING

    @pytest.mark.asyncio
    async def test_delete_removes_instance(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.delete_fmu_instance(instance_id)

        assert not fmu_adapter.has_instance(instance_id)

    @pytest.mark.asyncio
    async def test_full_lifecycle_initialized_running_terminated(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        assert fmu_adapter.get_state(instance_id) == FmuInstanceState.INITIALIZED

        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
        assert fmu_adapter.get_state(instance_id) == FmuInstanceState.RUNNING

        await fmu_adapter.step(instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
        assert fmu_adapter.get_state(instance_id) == FmuInstanceState.RUNNING

        await fmu_adapter.delete_fmu_instance(instance_id)
        assert not fmu_adapter.has_instance(instance_id)


class TestInstanceDeletion:

    @pytest.mark.asyncio
    async def test_delete_removes_from_adapter(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.delete_fmu_instance(instance_id)

        assert not fmu_adapter.has_instance(instance_id)
        assert instance_id not in fmu_adapter.list_instance_ids()

    @pytest.mark.asyncio
    async def test_delete_one_does_not_affect_others(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        id1 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id2 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.delete_fmu_instance(id1)

        assert not fmu_adapter.has_instance(id1)
        assert fmu_adapter.has_instance(id2)


class TestSequenceTypeTracking:

    def test_get_sequence_type_returns_reheat(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        assert fmu_adapter.get_sequence_type(instance_id) == SequenceType.VAV_REHEAT


class TestInstanceIsolation:

    @pytest.mark.asyncio
    async def test_instances_have_independent_time(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        id1 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id2 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.step(id1, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
        await fmu_adapter.step(id1, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
        await fmu_adapter.step(id2, fmu_data, step_size=30.0, sequence_type=SequenceType.VAV_REHEAT)

        assert fmu_adapter.get_current_time(id1) == 120.0
        assert fmu_adapter.get_current_time(id2) == 30.0

    @pytest.mark.asyncio
    async def test_instances_have_independent_states(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        id1 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id2 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.step(id1, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert fmu_adapter.get_state(id1) == FmuInstanceState.RUNNING
        assert fmu_adapter.get_state(id2) == FmuInstanceState.INITIALIZED

    @pytest.mark.asyncio
    async def test_instances_have_independent_outputs(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        hot_inputs = base_inputs.model_copy(update={"zoneTemperature": 300.15})
        cold_inputs = base_inputs.model_copy(update={"zoneTemperature": 290.15})

        hot_data = ReheatFMUData(inputs=hot_inputs, parameters=base_parameters)
        cold_data = ReheatFMUData(inputs=cold_inputs, parameters=base_parameters)

        id_hot = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, hot_data)
        id_cold = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, cold_data)

        for _ in range(5):
            outputs_hot = await fmu_adapter.step(id_hot, hot_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
            outputs_cold = await fmu_adapter.step(id_cold, cold_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)

        assert outputs_hot["yDam"] != outputs_cold["yDam"]
