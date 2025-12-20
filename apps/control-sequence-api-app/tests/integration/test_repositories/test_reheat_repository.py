"""Integration tests for ReheatRepository with real SQLite database."""

import pytest
import pytest_asyncio

from src.models.reheat.enums import ControllerType, VentilationStandard
from src.models.reheat.parameters import ReheatParameters
from src.repositories.base import ControlSequenceInstanceData
from src.repositories.reheat_repository import ReheatInstanceData, ReheatRepository


@pytest_asyncio.fixture
async def reheat_repo(test_db):
    return ReheatRepository()


class TestReheatRepositorySave:

    @pytest.mark.asyncio
    async def test_save_returns_instance_with_id(self, reheat_repo: ReheatRepository):
        params = ReheatParameters()

        result = await reheat_repo.save("zone-1", params)

        assert isinstance(result, ControlSequenceInstanceData)
        assert result.instance_id == "zone-1"
        assert len(result.id) == 36  # UUID format
        assert result.parameters == params

    @pytest.mark.asyncio
    async def test_save_with_custom_parameters(self, reheat_repo: ReheatRepository):
        params = ReheatParameters(
            minAirflow=0.05,
            maxCoolingAirflow=2.0,
            controllerTypeDamper=ControllerType.PID,
            ventilationStandard=VentilationStandard.CALIFORNIA_TITLE_24,
        )

        result = await reheat_repo.save("zone-2", params)

        assert result.instance_id == "zone-2"
        assert result.parameters.minAirflow == 0.05
        assert result.parameters.controllerTypeDamper == ControllerType.PID

    @pytest.mark.asyncio
    async def test_save_overwrites_existing_active_instance(self, reheat_repo: ReheatRepository):
        params_v1 = ReheatParameters(minAirflow=0.1)
        params_v2 = ReheatParameters(minAirflow=0.2)

        result_v1 = await reheat_repo.save("zone-3", params_v1)
        result_v2 = await reheat_repo.save("zone-3", params_v2)

        assert result_v1.id != result_v2.id
        assert result_v2.parameters.minAirflow == 0.2


class TestReheatRepositoryGetActive:

    @pytest.mark.asyncio
    async def test_get_active_returns_none_for_nonexistent(self, reheat_repo: ReheatRepository):
        result = await reheat_repo.get_active("nonexistent-zone")

        assert result is None

    @pytest.mark.asyncio
    async def test_get_active_returns_instance(self, reheat_repo: ReheatRepository):
        params = ReheatParameters(
            minAirflow=0.2,
            maxCoolingAirflow=0.8,
            hasCO2Sensor=True,
        )
        saved = await reheat_repo.save("zone-4", params)

        result = await reheat_repo.get_active("zone-4")

        assert result is not None
        assert result.id == saved.id
        assert result.instance_id == "zone-4"
        assert result.parameters.minAirflow == 0.2
        assert result.parameters.maxCoolingAirflow == 0.8

    @pytest.mark.asyncio
    async def test_get_active_returns_none_after_delete(self, reheat_repo: ReheatRepository):
        params = ReheatParameters()
        await reheat_repo.save("zone-5", params)
        await reheat_repo.delete("zone-5")

        result = await reheat_repo.get_active("zone-5")

        assert result is None


class TestReheatRepositoryListActive:

    @pytest.mark.asyncio
    async def test_list_active_returns_empty_when_no_instances(self, reheat_repo: ReheatRepository):
        result = await reheat_repo.list_active()

        assert result == []

    @pytest.mark.asyncio
    async def test_list_active_returns_all_active_instances(self, reheat_repo: ReheatRepository):
        await reheat_repo.save("zone-a", ReheatParameters(minAirflow=0.1))
        await reheat_repo.save("zone-b", ReheatParameters(minAirflow=0.2))
        await reheat_repo.save("zone-c", ReheatParameters(minAirflow=0.3))

        result = await reheat_repo.list_active()

        assert len(result) == 3
        instance_ids = [r.instance_id for r in result]
        assert "zone-a" in instance_ids
        assert "zone-b" in instance_ids
        assert "zone-c" in instance_ids

    @pytest.mark.asyncio
    async def test_list_active_excludes_deleted_instances(self, reheat_repo: ReheatRepository):
        await reheat_repo.save("zone-d", ReheatParameters())
        await reheat_repo.save("zone-e", ReheatParameters())
        await reheat_repo.delete("zone-d")

        result = await reheat_repo.list_active()

        assert len(result) == 1
        assert result[0].instance_id == "zone-e"


class TestReheatRepositoryDelete:

    @pytest.mark.asyncio
    async def test_delete_returns_true_for_existing_instance(self, reheat_repo: ReheatRepository):
        await reheat_repo.save("zone-6", ReheatParameters())

        result = await reheat_repo.delete("zone-6")

        assert result is True

    @pytest.mark.asyncio
    async def test_delete_returns_false_for_nonexistent_instance(self, reheat_repo: ReheatRepository):
        result = await reheat_repo.delete("nonexistent-zone")

        assert result is False

    @pytest.mark.asyncio
    async def test_delete_is_soft_delete(self, reheat_repo: ReheatRepository):
        params = ReheatParameters(minAirflow=0.05)
        await reheat_repo.save("zone-7", params)

        await reheat_repo.delete("zone-7")

        active = await reheat_repo.get_active("zone-7")
        assert active is None


class TestReheatRepositoryHistoryTracking:

    @pytest.mark.asyncio
    async def test_multiple_saves_create_new_ids(self, reheat_repo: ReheatRepository):
        result1 = await reheat_repo.save("zone-8", ReheatParameters(minAirflow=0.1))
        result2 = await reheat_repo.save("zone-8", ReheatParameters(minAirflow=0.2))
        result3 = await reheat_repo.save("zone-8", ReheatParameters(minAirflow=0.3))

        assert result1.id != result2.id != result3.id
        assert result3.parameters.minAirflow == 0.3

    @pytest.mark.asyncio
    async def test_only_one_active_instance_per_id(self, reheat_repo: ReheatRepository):
        await reheat_repo.save("zone-9", ReheatParameters())
        await reheat_repo.save("zone-9", ReheatParameters())
        await reheat_repo.save("zone-9", ReheatParameters())

        result = await reheat_repo.list_active()
        zone_9_instances = [r for r in result if r.instance_id == "zone-9"]

        assert len(zone_9_instances) == 1


class TestReheatRepositoryValidation:

    @pytest.mark.asyncio
    async def test_retrieved_parameters_are_valid_pydantic_model(self, reheat_repo: ReheatRepository):
        original = ReheatParameters(
            controllerTypeDamper=ControllerType.PID,
            ventilationStandard=VentilationStandard.ASHRAE62_1,
            hasWindowSensor=True,
            hasOccupancySensor=True,
        )
        await reheat_repo.save("zone-11", original)

        result = await reheat_repo.get_active("zone-11")

        assert result is not None
        assert result.parameters.controllerTypeDamper == ControllerType.PID
        assert result.parameters.ventilationStandard == VentilationStandard.ASHRAE62_1
        assert result.parameters.hasWindowSensor is True
        assert result.parameters.hasOccupancySensor is True


class TestReheatRepositoryGetOrCreate:

    @pytest.mark.asyncio
    async def test_get_or_create_creates_when_not_exists(self, reheat_repo: ReheatRepository):
        params = ReheatParameters(minAirflow=0.15)

        result, created = await reheat_repo.get_or_create("new-zone", params)

        assert created is True
        assert result.instance_id == "new-zone"
        assert result.parameters.minAirflow == 0.15

    @pytest.mark.asyncio
    async def test_get_or_create_returns_existing_when_exists(self, reheat_repo: ReheatRepository):
        original_params = ReheatParameters(minAirflow=0.25)
        await reheat_repo.save("existing-zone", original_params)

        new_params = ReheatParameters(minAirflow=0.99)
        result, created = await reheat_repo.get_or_create("existing-zone", new_params)

        assert created is False
        assert result.instance_id == "existing-zone"
        assert result.parameters.minAirflow == 0.25

    @pytest.mark.asyncio
    async def test_get_or_create_idempotent_multiple_calls(self, reheat_repo: ReheatRepository):
        params = ReheatParameters(minAirflow=0.35)

        result1, created1 = await reheat_repo.get_or_create("idempotent-zone", params)
        result2, created2 = await reheat_repo.get_or_create("idempotent-zone", params)

        assert created1 is True
        assert created2 is False
        assert result1.id == result2.id
        assert result1.instance_id == result2.instance_id
