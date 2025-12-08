"""Unit tests for G36 Reheat Controller.

Tests cover acceptance criteria from Story 1.11:
  AC1: POST /api/v1/g36/reheat/instances (upsert)
  AC2: POST /api/v1/g36/reheat/instances/{instance_id}/step
  AC3: DELETE /api/v1/g36/instances/{instance_id} (idempotent)
"""

from unittest.mock import AsyncMock, MagicMock

import pytest
from fastapi import HTTPException

from src.adapters.exceptions import (
    FmuExecutionError,
    FmuInstanceNotFoundError,
    FmuValidationError,
)
from src.adapters.fmu_adapter import UpsertResult
from src.controllers.g36_controller import G36ReheatController
from src.dto.reheat_dto import (
    CreateInstanceRequest,
    CreateInstanceResponse,
    DeleteInstanceResponse,
    OperationMode,
    ReheatInputsRequest,
    ReheatOutputs,
    ReheatParameters,
    StepRequest,
    StepResponse,
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
def controller(mock_adapter):
    return G36ReheatController(mock_adapter)


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
def valid_parameters():
    return ReheatParameters()


@pytest.fixture
def create_request(valid_inputs_request, valid_parameters):
    return CreateInstanceRequest(
        instance_id="test-instance-1",
        inputs=valid_inputs_request,
        parameters=valid_parameters,
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


class TestUpsertInstance:

    @pytest.mark.asyncio
    async def test_upsert_creates_new_instance(
        self, controller, mock_adapter, create_request
    ):
        mock_adapter.upsert_fmu_instance.return_value = UpsertResult(
            instance_id="test-instance-1", is_created=True
        )

        response = await controller.upsert_instance(create_request)

        assert isinstance(response, CreateInstanceResponse)
        assert response.instance_id == "test-instance-1"
        assert response.created is True
        mock_adapter.upsert_fmu_instance.assert_called_once()

    @pytest.mark.asyncio
    async def test_upsert_recreates_existing_instance(
        self, controller, mock_adapter, create_request
    ):
        mock_adapter.upsert_fmu_instance.return_value = UpsertResult(
            instance_id="test-instance-1", is_created=False
        )

        response = await controller.upsert_instance(create_request)

        assert response.instance_id == "test-instance-1"
        assert response.created is False

    @pytest.mark.asyncio
    async def test_upsert_returns_parameters(
        self, controller, mock_adapter, create_request
    ):
        mock_adapter.upsert_fmu_instance.return_value = UpsertResult(
            instance_id="test-instance-1", is_created=True
        )

        response = await controller.upsert_instance(create_request)

        assert response.parameters == create_request.parameters

    @pytest.mark.asyncio
    async def test_upsert_raises_400_for_validation_error(
        self, controller, mock_adapter, create_request
    ):
        mock_adapter.upsert_fmu_instance.side_effect = FmuValidationError(
            "Invalid inputs"
        )

        with pytest.raises(HTTPException) as exc_info:
            await controller.upsert_instance(create_request)

        assert exc_info.value.status_code == 400
        assert "Invalid inputs" in exc_info.value.detail

    @pytest.mark.asyncio
    async def test_upsert_raises_500_for_execution_error(
        self, controller, mock_adapter, create_request
    ):
        mock_adapter.upsert_fmu_instance.side_effect = FmuExecutionError(
            "FMU init failed"
        )

        with pytest.raises(HTTPException) as exc_info:
            await controller.upsert_instance(create_request)

        assert exc_info.value.status_code == 500
        assert "FMU execution error" in exc_info.value.detail


class TestStep:

    @pytest.mark.asyncio
    async def test_step_returns_outputs(
        self, controller, mock_adapter, step_request, valid_fmu_outputs
    ):
        mock_adapter.step.return_value = valid_fmu_outputs

        response = await controller.step("test-instance-1", step_request)

        assert isinstance(response, StepResponse)
        assert response.instance_id == "test-instance-1"
        assert isinstance(response.outputs, ReheatOutputs)
        assert response.outputs.damperPosition == 0.75
        assert response.outputs.valvePosition == 0.0

    @pytest.mark.asyncio
    async def test_step_calls_adapter_with_converted_inputs(
        self, controller, mock_adapter, step_request, valid_fmu_outputs
    ):
        mock_adapter.step.return_value = valid_fmu_outputs

        await controller.step("test-instance-1", step_request)

        mock_adapter.step.assert_called_once()
        call_args = mock_adapter.step.call_args
        assert call_args[0][0] == "test-instance-1"
        assert call_args[0][2] == 60.0

    @pytest.mark.asyncio
    async def test_step_raises_404_for_not_found(
        self, controller, mock_adapter, step_request
    ):
        mock_adapter.step.side_effect = FmuInstanceNotFoundError("test-instance-1")

        with pytest.raises(HTTPException) as exc_info:
            await controller.step("test-instance-1", step_request)

        assert exc_info.value.status_code == 404
        assert "test-instance-1" in exc_info.value.detail
        assert "not found" in exc_info.value.detail

    @pytest.mark.asyncio
    async def test_step_raises_400_for_validation_error(
        self, controller, mock_adapter, step_request
    ):
        mock_adapter.step.side_effect = FmuValidationError("Missing required input")

        with pytest.raises(HTTPException) as exc_info:
            await controller.step("test-instance-1", step_request)

        assert exc_info.value.status_code == 400
        assert "Missing required input" in exc_info.value.detail

    @pytest.mark.asyncio
    async def test_step_raises_500_for_execution_error(
        self, controller, mock_adapter, step_request
    ):
        mock_adapter.step.side_effect = FmuExecutionError("FMU step failed")

        with pytest.raises(HTTPException) as exc_info:
            await controller.step("test-instance-1", step_request)

        assert exc_info.value.status_code == 500
        assert "FMU execution error" in exc_info.value.detail


class TestDeleteInstance:

    @pytest.mark.asyncio
    async def test_delete_existing_instance(self, controller, mock_adapter):
        mock_adapter.has_instance.return_value = True

        response = await controller.delete_instance("test-instance-1")

        assert isinstance(response, DeleteInstanceResponse)
        assert response.instance_id == "test-instance-1"
        assert response.deleted is True
        mock_adapter.delete_fmu_instance.assert_called_once_with("test-instance-1")

    @pytest.mark.asyncio
    async def test_delete_idempotent_for_nonexistent(self, controller, mock_adapter):
        mock_adapter.has_instance.return_value = False

        response = await controller.delete_instance("nonexistent-instance")

        assert response.instance_id == "nonexistent-instance"
        assert response.deleted is False
        mock_adapter.delete_fmu_instance.assert_not_called()

    @pytest.mark.asyncio
    async def test_delete_raises_500_for_execution_error(
        self, controller, mock_adapter
    ):
        mock_adapter.has_instance.return_value = True
        mock_adapter.delete_fmu_instance.side_effect = FmuExecutionError(
            "Termination failed"
        )

        with pytest.raises(HTTPException) as exc_info:
            await controller.delete_instance("test-instance-1")

        assert exc_info.value.status_code == 500
        assert "FMU execution error" in exc_info.value.detail
