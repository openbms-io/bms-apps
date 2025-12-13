"""Unit tests for VAV Reheat Controller.

Tests cover acceptance criteria from Story 1.15:
  AC1: POST /api/v1/g36/vav-reheat/instances (create with defaults)
  AC2: POST /api/v1/g36/vav-reheat/instances/{instance_id}/step
  AC3: DELETE /api/v1/g36/vav-reheat/instances/{instance_id} (idempotent)
"""

from unittest.mock import AsyncMock, MagicMock

import pytest
from fastapi import HTTPException

from src.adapters.exceptions import (
    FmuExecutionError,
    FmuValidationError,
)
from src.controllers.vav_reheat_controller import VavReheatController
from src.dto.base_dto import CreateInstanceResponse, DeleteInstanceResponse
from src.dto.reheat_dto import (
    OperationMode,
    ReheatInputsRequest,
    ReheatOutputs,
    StepRequest,
    StepResponse,
)
from src.models.reheat.parameters import ReheatParameters
from src.repositories.base import ControlSequenceInstanceData


def make_reheat_instance_data(
    instance_id: str,
    parameters: ReheatParameters,
    db_id: str = "db-row-id",
) -> ControlSequenceInstanceData[ReheatParameters]:
    return ControlSequenceInstanceData(
        id=db_id,
        instance_id=instance_id,
        parameters=parameters,
    )


@pytest.fixture
def mock_adapter():
    adapter = MagicMock()
    adapter.upsert_fmu_instance = AsyncMock()
    adapter.step = AsyncMock()
    adapter.delete_fmu_instance = AsyncMock()
    adapter.has_instance = MagicMock()
    return adapter


@pytest.fixture
def mock_repository():
    repository = MagicMock()
    repository.create = AsyncMock()
    repository.save = AsyncMock()
    repository.get_active = AsyncMock()
    repository.delete = AsyncMock()
    repository.list_active = AsyncMock()
    return repository


@pytest.fixture
def controller(mock_adapter, mock_repository):
    return VavReheatController(mock_adapter, mock_repository)


@pytest.fixture
def valid_inputs_request():
    return ReheatInputsRequest(
        zoneTemperature=22.0,
        coolingSetpoint=24.0,
        heatingSetpoint=20.0,
        dischargeAirTemperature=16.0,
        primaryAirflow=0.3,
        supplyAirTemperature=13.0,
        supplyAirTemperatureSetpoint=12.0,
        fanStatus=True,
        operationMode=OperationMode.OCCUPIED,
    )


@pytest.fixture
def step_request(valid_inputs_request):
    return StepRequest(stepSize=60.0, inputs=valid_inputs_request)


@pytest.fixture
def valid_fmu_outputs():
    return {
        "yDam": 0.75,
        "yVal": 0.0,
        "VSet_flow": 0.35,
        "VMinOA_flow": 0.1,
        "VAdjAreBreZon_flow": 0.0,
        "VAdjPopBreZon_flow": 0.0,
        "yFloSenAla": 0,
        "yHeaValResReq": 0,
        "yHotWatPlaReq": 0,
        "yLeaDamAla": 0,
        "yLeaValAla": 0,
        "yLowFloAla": 0,
        "yLowTemAla": 0,
        "yZonPreResReq": 0,
        "yZonTemResReq": 0,
    }


class TestCreateInstance:

    @pytest.mark.asyncio
    async def test_create_instance_returns_auto_generated_id(
        self, controller, mock_repository
    ):
        default_params = ReheatParameters()
        mock_repository.create.return_value = make_reheat_instance_data(
            instance_id="auto-generated-uuid",
            parameters=default_params,
        )

        response = await controller.create_instance()

        assert isinstance(response, CreateInstanceResponse)
        assert response.instance_id == "auto-generated-uuid"

    @pytest.mark.asyncio
    async def test_create_instance_returns_default_parameters(
        self, controller, mock_repository
    ):
        default_params = ReheatParameters()
        mock_repository.create.return_value = make_reheat_instance_data(
            instance_id="test-id",
            parameters=default_params,
        )

        response = await controller.create_instance()

        assert response.parameters == default_params
        assert response.parameters.minAirflow == 0.3
        assert response.parameters.maxCoolingAirflow == 1.5

    @pytest.mark.asyncio
    async def test_create_instance_calls_repository_create(
        self, controller, mock_repository
    ):
        default_params = ReheatParameters()
        mock_repository.create.return_value = make_reheat_instance_data(
            instance_id="test-id",
            parameters=default_params,
        )

        await controller.create_instance()

        mock_repository.create.assert_called_once()
        call_args = mock_repository.create.call_args[0]
        assert isinstance(call_args[0], ReheatParameters)

    @pytest.mark.asyncio
    async def test_create_instance_does_not_create_fmu_instance(
        self, controller, mock_adapter, mock_repository
    ):
        mock_repository.create.return_value = make_reheat_instance_data(
            instance_id="test-id",
            parameters=ReheatParameters(),
        )

        await controller.create_instance()

        mock_adapter.upsert_fmu_instance.assert_not_called()


class TestStep:

    @pytest.mark.asyncio
    async def test_step_returns_outputs(
        self, controller, mock_adapter, mock_repository, step_request, valid_fmu_outputs
    ):
        mock_repository.get_active.return_value = make_reheat_instance_data(
            instance_id="test-instance-1",
            parameters=ReheatParameters(),
        )
        mock_adapter.has_instance.return_value = True
        mock_adapter.step.return_value = valid_fmu_outputs

        response = await controller.step("test-instance-1", step_request)

        assert isinstance(response, StepResponse)
        assert response.instance_id == "test-instance-1"
        assert isinstance(response.outputs, ReheatOutputs)
        assert response.outputs.damperPosition == 0.75
        assert response.outputs.valvePosition == 0.0

    @pytest.mark.asyncio
    async def test_step_passes_sequence_type_for_lazy_creation(
        self, controller, mock_adapter, mock_repository, step_request, valid_fmu_outputs
    ):
        mock_repository.get_active.return_value = make_reheat_instance_data(
            instance_id="test-instance-1",
            parameters=ReheatParameters(),
        )
        mock_adapter.step.return_value = valid_fmu_outputs

        await controller.step("test-instance-1", step_request)

        call_kwargs = mock_adapter.step.call_args.kwargs
        assert call_kwargs.get("sequence_type") is not None

    @pytest.mark.asyncio
    async def test_step_raises_404_if_instance_not_in_db(
        self, controller, mock_repository, step_request
    ):
        mock_repository.get_active.return_value = None

        with pytest.raises(HTTPException) as exc_info:
            await controller.step("nonexistent", step_request)

        assert exc_info.value.status_code == 404
        assert "nonexistent" in exc_info.value.detail

    @pytest.mark.asyncio
    async def test_step_raises_400_for_validation_error(
        self, controller, mock_adapter, mock_repository, step_request
    ):
        mock_repository.get_active.return_value = make_reheat_instance_data(
            instance_id="test-instance-1",
            parameters=ReheatParameters(),
        )
        mock_adapter.has_instance.return_value = True
        mock_adapter.step.side_effect = FmuValidationError("Missing required input")

        with pytest.raises(HTTPException) as exc_info:
            await controller.step("test-instance-1", step_request)

        assert exc_info.value.status_code == 400
        assert "Missing required input" in exc_info.value.detail

    @pytest.mark.asyncio
    async def test_step_raises_500_for_execution_error(
        self, controller, mock_adapter, mock_repository, step_request
    ):
        mock_repository.get_active.return_value = make_reheat_instance_data(
            instance_id="test-instance-1",
            parameters=ReheatParameters(),
        )
        mock_adapter.has_instance.return_value = True
        mock_adapter.step.side_effect = FmuExecutionError("FMU step failed")

        with pytest.raises(HTTPException) as exc_info:
            await controller.step("test-instance-1", step_request)

        assert exc_info.value.status_code == 500
        assert "FMU execution error" in exc_info.value.detail


class TestDeleteInstance:

    @pytest.mark.asyncio
    async def test_delete_existing_instance_from_db_and_fmu(
        self, controller, mock_adapter, mock_repository
    ):
        mock_repository.delete.return_value = True
        mock_adapter.delete_fmu_instance.return_value = True

        response = await controller.delete_instance("test-instance-1")

        assert isinstance(response, DeleteInstanceResponse)
        assert response.instance_id == "test-instance-1"
        assert response.deleted is True
        mock_repository.delete.assert_called_once_with("test-instance-1")
        mock_adapter.delete_fmu_instance.assert_called_once_with("test-instance-1")

    @pytest.mark.asyncio
    async def test_delete_returns_true_if_only_db_had_instance(
        self, controller, mock_adapter, mock_repository
    ):
        mock_repository.delete.return_value = True
        mock_adapter.delete_fmu_instance.return_value = False

        response = await controller.delete_instance("test-instance-1")

        assert response.deleted is True

    @pytest.mark.asyncio
    async def test_delete_returns_true_if_only_fmu_had_instance(
        self, controller, mock_adapter, mock_repository
    ):
        mock_repository.delete.return_value = False
        mock_adapter.delete_fmu_instance.return_value = True

        response = await controller.delete_instance("test-instance-1")

        assert response.deleted is True

    @pytest.mark.asyncio
    async def test_delete_idempotent_returns_false_for_nonexistent(
        self, controller, mock_adapter, mock_repository
    ):
        mock_repository.delete.return_value = False
        mock_adapter.delete_fmu_instance.return_value = False

        response = await controller.delete_instance("nonexistent-instance")

        assert response.instance_id == "nonexistent-instance"
        assert response.deleted is False
