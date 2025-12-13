"""G36 VAV Reheat control sequence router.

Route structure: /api/v1/g36/vav-reheat/...

Note: Each G36 sequence type (vav-reheat, vav-cooling-only, ahu, etc.) has its own
router file for type-safe DTOs and compile-time checking. New sequence types should
follow this pattern:
  - g36_vav_cooling_only_router.py → /api/v1/g36/vav-cooling-only/...
  - g36_ahu_router.py → /api/v1/g36/ahu/...
"""

from fastapi import APIRouter, Depends

from src.controllers.vav_reheat_controller import VavReheatController
from src.dependencies import get_vav_reheat_controller
from src.dto.base_dto import (
    CreateInstanceResponse,
    DeleteInstanceResponse,
    GetInstanceResponse,
    UpdateInstanceResponse,
    UpdateParametersRequest,
)
from src.dto.reheat_dto import StepRequest, StepResponse
from src.models.reheat.parameters import ReheatParameters

router = APIRouter(prefix="/api/v1/g36/vav-reheat", tags=["G36 VAV Reheat"])


@router.post("/instances", response_model=CreateInstanceResponse[ReheatParameters])
async def create_instance(
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> CreateInstanceResponse[ReheatParameters]:
    """Create a new VAV Reheat instance with auto-generated ID and default parameters.

    No request body required. Returns instance_id and default parameters.
    """
    return await controller.create_instance()


@router.get("/instances/{instance_id}", response_model=GetInstanceResponse[ReheatParameters])
async def get_instance(
    instance_id: str,
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> GetInstanceResponse[ReheatParameters]:
    """Get VAV Reheat instance parameters."""
    return await controller.get_instance(instance_id)


@router.put("/instances/{instance_id}", response_model=UpdateInstanceResponse[ReheatParameters])
async def update_instance(
    instance_id: str,
    request: UpdateParametersRequest[ReheatParameters],
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> UpdateInstanceResponse[ReheatParameters]:
    """Update VAV Reheat instance parameters."""
    return await controller.update_instance(instance_id, request)


@router.post("/instances/{instance_id}/step", response_model=StepResponse)
async def step(
    instance_id: str,
    request: StepRequest,
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> StepResponse:
    """Execute a simulation step on an FMU instance."""
    return await controller.step(instance_id, request)


@router.delete("/instances/{instance_id}", response_model=DeleteInstanceResponse)
async def delete_instance(
    instance_id: str,
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> DeleteInstanceResponse:
    """Delete an FMU instance (idempotent)."""
    return await controller.delete_instance(instance_id)
