import pytest

from src.adapters.exceptions import FmuInstanceNotFoundError
from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData
from src.adapters.sequence_type import SequenceType
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.parameters import ReheatParameters


class TestInvalidInstanceId:

    @pytest.mark.asyncio
    async def test_step_with_nonexistent_id_creates_lazily(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        outputs = await fmu_adapter.step(
            "nonexistent-id", fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT
        )

        assert outputs is not None
        assert fmu_adapter.has_instance("nonexistent-id")

    @pytest.mark.asyncio
    async def test_delete_nonexistent_instance_idempotent_returns_false(
        self, fmu_adapter: FmuAdapter
    ):
        result = await fmu_adapter.delete_fmu_instance("nonexistent-id")
        assert result is False

    def test_get_current_time_nonexistent_raises_error(self, fmu_adapter: FmuAdapter):
        with pytest.raises(FmuInstanceNotFoundError):
            fmu_adapter.get_current_time("nonexistent-id")

    def test_get_state_nonexistent_raises_error(self, fmu_adapter: FmuAdapter):
        with pytest.raises(FmuInstanceNotFoundError):
            fmu_adapter.get_state("nonexistent-id")

    def test_get_sequence_type_nonexistent_raises_error(self, fmu_adapter: FmuAdapter):
        with pytest.raises(FmuInstanceNotFoundError):
            fmu_adapter.get_sequence_type("nonexistent-id")

    @pytest.mark.asyncio
    async def test_update_nonexistent_instance_raises_error(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        with pytest.raises(FmuInstanceNotFoundError):
            await fmu_adapter.update_fmu_instance("nonexistent-id", fmu_data)


class TestHasInstanceCheck:

    def test_has_instance_returns_false_for_nonexistent(self, fmu_adapter: FmuAdapter):
        result = fmu_adapter.has_instance("nonexistent-id")

        assert result is False

    def test_has_instance_returns_true_for_existing(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        result = fmu_adapter.has_instance(instance_id)

        assert result is True


class TestDeletedInstanceAccess:

    @pytest.mark.asyncio
    async def test_step_after_delete_recreates_instance(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.delete_fmu_instance(instance_id)
        assert not fmu_adapter.has_instance(instance_id)

        outputs = await fmu_adapter.step(
            instance_id, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT
        )

        assert outputs is not None
        assert fmu_adapter.has_instance(instance_id)

    @pytest.mark.asyncio
    async def test_get_time_after_delete_raises_error(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.delete_fmu_instance(instance_id)

        with pytest.raises(FmuInstanceNotFoundError):
            fmu_adapter.get_current_time(instance_id)

    @pytest.mark.asyncio
    async def test_get_state_after_delete_raises_error(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.delete_fmu_instance(instance_id)

        with pytest.raises(FmuInstanceNotFoundError):
            fmu_adapter.get_state(instance_id)


class TestZeroStepSize:

    @pytest.mark.asyncio
    async def test_zero_step_size_returns_current_outputs(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        outputs = await fmu_adapter.step(
            instance_id, fmu_data, step_size=0.0, sequence_type=SequenceType.VAV_REHEAT
        )

        assert outputs is not None
        assert fmu_adapter.get_current_time(instance_id) == 0.0


class TestEmptyAdapterOperations:

    def test_list_instance_ids_empty_initially(self, fmu_adapter: FmuAdapter):
        ids = fmu_adapter.list_instance_ids()

        assert ids == []

    def test_has_instance_empty_returns_false(self, fmu_adapter: FmuAdapter):
        result = fmu_adapter.has_instance("any-id")

        assert result is False


class TestDoubleDelete:

    @pytest.mark.asyncio
    async def test_delete_same_instance_twice_idempotent(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        first_delete = await fmu_adapter.delete_fmu_instance(instance_id)
        assert first_delete is True

        second_delete = await fmu_adapter.delete_fmu_instance(instance_id)
        assert second_delete is False


class TestConcurrentInstanceOperations:

    @pytest.mark.asyncio
    async def test_multiple_instances_do_not_interfere(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        id1 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id2 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)
        id3 = fmu_adapter.create_fmu_instance(SequenceType.VAV_REHEAT, fmu_data)

        await fmu_adapter.delete_fmu_instance(id2)

        assert fmu_adapter.has_instance(id1)
        assert not fmu_adapter.has_instance(id2)
        assert fmu_adapter.has_instance(id3)

        await fmu_adapter.step(id1, fmu_data, step_size=60.0, sequence_type=SequenceType.VAV_REHEAT)
        await fmu_adapter.step(id3, fmu_data, step_size=30.0, sequence_type=SequenceType.VAV_REHEAT)

        assert fmu_adapter.get_current_time(id1) == 60.0
        assert fmu_adapter.get_current_time(id3) == 30.0
