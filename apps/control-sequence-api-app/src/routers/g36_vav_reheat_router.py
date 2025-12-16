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
    CreateInstanceRequest,
    CreateInstanceResponse,
    DeleteInstanceResponse,
    GetInstanceResponse,
    UpdateInstanceResponse,
    UpdateParametersRequest,
)
from src.dto.common_dto import ErrorResponse
from src.dto.reheat_dto import ReheatParametersDTO, StepRequest, StepResponse
from src.models.reheat.parameters import ReheatParameters

router = APIRouter(prefix="/api/v1/g36/vav-reheat", tags=["G36 VAV Reheat"])


@router.post(
    "/instances",
    response_model=CreateInstanceResponse[ReheatParameters],
    response_model_by_alias=True,
    responses={
        200: {"description": "Instance created with default parameters (or existing returned)"},
        422: {"description": "Validation error in request body"},
        500: {"description": "Internal server error", "model": ErrorResponse},
    },
)
async def create_instance(
    request: CreateInstanceRequest[ReheatParametersDTO],
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> CreateInstanceResponse[ReheatParameters]:
    """Create a new VAV Reheat control sequence instance.

    Creates an FMU instance with default G36 parameters. The FMU is lazily
    instantiated on the first step() call.

    Idempotent: if instance_id already exists, returns the existing instance.

    Use this endpoint when:
    - Dragging a G36 Reheat block onto the Designer canvas
    - Reloading a saved project (idempotent creation)
    """
    return await controller.create_instance(request)


@router.get(
    "/instances/{instance_id}",
    response_model=GetInstanceResponse[ReheatParameters],
    response_model_by_alias=True,
    responses={
        200: {"description": "Instance parameters retrieved successfully"},
        404: {"description": "Instance not found", "model": ErrorResponse},
    },
)
async def get_instance(
    instance_id: str,
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> GetInstanceResponse[ReheatParameters]:
    """Retrieve VAV Reheat instance parameters.

    Returns the current configuration parameters for an existing instance.

    Use this endpoint when:
    - Loading parameters into the Designer configuration panel
    - Verifying current instance state
    """
    return await controller.get_instance(instance_id)


@router.put(
    "/instances/{instance_id}",
    response_model=UpdateInstanceResponse[ReheatParameters],
    response_model_by_alias=True,
    responses={
        200: {"description": "Instance parameters updated successfully"},
        404: {"description": "Instance not found", "model": ErrorResponse},
        422: {"description": "Validation error in request body"},
    },
)
async def update_instance(
    instance_id: str,
    request: UpdateParametersRequest[ReheatParametersDTO],
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> UpdateInstanceResponse[ReheatParameters]:
    """Update VAV Reheat instance parameters.

    Updates the configuration parameters for an existing instance.
    The FMU will be recreated with the new parameters on the next step() call.

    Use this endpoint when:
    - User modifies parameters in the Designer configuration panel
    - Applying parameter changes from external sources
    """
    return await controller.update_instance(instance_id, request)


@router.post(
    "/instances/{instance_id}/step",
    response_model=StepResponse,
    response_model_by_alias=True,
    responses={
        200: {"description": "Step executed successfully"},
        404: {"description": "Instance not found", "model": ErrorResponse},
        422: {"description": "Validation error in inputs"},
        500: {"description": "FMU execution error", "model": ErrorResponse},
    },
)
async def step(
    instance_id: str,
    request: StepRequest,
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> StepResponse:
    """Execute a simulation step on the G36 VAV Reheat control sequence.

    Advances the FMU simulation by the specified step size using provided inputs.
    The FMU is lazily instantiated on the first step() call for the instance.
    Returns computed outputs (damper position, valve position, airflow setpoint, etc.).

    Use this endpoint when:
    - Running the control sequence in the Designer execution loop
    - Testing the control sequence with specific inputs
    """
    return await controller.step(instance_id, request)


@router.delete(
    "/instances/{instance_id}",
    response_model=DeleteInstanceResponse,
    response_model_by_alias=True,
    responses={
        200: {"description": "Instance deleted (or already not found - idempotent)"},
    },
)
async def delete_instance(
    instance_id: str,
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> DeleteInstanceResponse:
    """Delete a VAV Reheat control sequence instance completely.

    Removes both the FMU runtime instance and the persisted DB parameters.
    This operation is idempotent - returns success even if instance doesn't exist.

    Use this endpoint when:
    - User explicitly deletes a G36 Reheat block from the Designer canvas
    """
    return await controller.delete_instance(instance_id)


@router.delete(
    "/instances/{instance_id}/fmu",
    response_model=DeleteInstanceResponse,
    response_model_by_alias=True,
    responses={
        200: {"description": "FMU runtime cleaned up (or already not found - idempotent)"},
    },
)
async def delete_fmu(
    instance_id: str,
    controller: VavReheatController = Depends(get_vav_reheat_controller),
) -> DeleteInstanceResponse:
    """Delete only the FMU runtime instance, preserving DB parameters.

    Frees FMU memory while keeping persisted parameters intact.
    This operation is idempotent - returns success even if FMU doesn't exist.

    Use this endpoint when:
    - Switching projects (cleanup without losing saved parameters)
    - Freeing memory for idle instances
    """
    return await controller.delete_fmu(instance_id)
