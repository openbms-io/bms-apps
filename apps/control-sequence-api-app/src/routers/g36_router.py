"""G36 Router for Reheat Terminal API endpoints."""

from fastapi import APIRouter, Depends

from src.adapters.fmu_adapter import FmuAdapter
from src.controllers.g36_controller import G36ReheatController
from src.dto.reheat_dto import (
    CreateInstanceRequest,
    CreateInstanceResponse,
    DeleteInstanceResponse,
    StepRequest,
    StepResponse,
)

router = APIRouter(prefix="/api/v1/g36", tags=["G36"])


def get_g36_reheat_controller() -> G36ReheatController:
    adapter = FmuAdapter.get_instance()
    return G36ReheatController(adapter)


@router.post("/reheat/instances", response_model=CreateInstanceResponse)
async def upsert_instance(
    request: CreateInstanceRequest,
    controller: G36ReheatController = Depends(get_g36_reheat_controller),
) -> CreateInstanceResponse:
    """Create or update an FMU instance for a Reheat Terminal Unit.

    Upsert semantics - creates if new, recreates with new params if exists.
    """
    return await controller.upsert_instance(request)


@router.post("/reheat/instances/{instance_id}/step", response_model=StepResponse)
async def step(
    instance_id: str,
    request: StepRequest,
    controller: G36ReheatController = Depends(get_g36_reheat_controller),
) -> StepResponse:
    """Execute a simulation step on an FMU instance."""
    return await controller.step(instance_id, request)


@router.delete("/instances/{instance_id}", response_model=DeleteInstanceResponse)
async def delete_instance(
    instance_id: str,
    controller: G36ReheatController = Depends(get_g36_reheat_controller),
) -> DeleteInstanceResponse:
    """Delete an FMU instance (idempotent, sequence-agnostic)."""
    return await controller.delete_instance(instance_id)
