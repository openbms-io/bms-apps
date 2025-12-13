"""G36 VAV Reheat Controller for Reheat Terminal FMU operations."""

from fastapi import HTTPException

from src.adapters.exceptions import (
    FmuExecutionError,
    FmuValidationError,
)
from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData
from src.adapters.sequence_type import SequenceType
from src.dto.base_dto import (
    CreateInstanceResponse,
    DeleteInstanceResponse,
    GetInstanceResponse,
    UpdateInstanceResponse,
    UpdateParametersRequest,
)
from src.dto.reheat_dto import StepRequest, StepResponse
from src.models.reheat.parameters import ReheatParameters
from src.repositories.reheat_repository import ReheatRepository


class VavReheatController:
    """Controller for G36 VAV Reheat Terminal operations.

    Maps adapter exceptions to HTTP errors per tech spec Section 4.3.
    """

    def __init__(self, adapter: FmuAdapter, repository: ReheatRepository) -> None:
        self._adapter = adapter
        self._repository = repository

    async def _get_stored_or_404(self, instance_id: str):
        stored = await self._repository.get_active(instance_id)
        if stored is None:
            raise HTTPException(status_code=404, detail=f"Instance {instance_id} not found")
        return stored

    async def create_instance(self) -> CreateInstanceResponse[ReheatParameters]:
        """Create a new instance with auto-generated ID and default parameters.

        POST /instances takes no body. Backend generates UUID and uses default params.
        FMU instance is lazily created on first step() call.
        """
        default_params = ReheatParameters()
        saved = await self._repository.create(default_params)

        return CreateInstanceResponse(
            instance_id=saved.instance_id,
            parameters=saved.parameters,
        )

    async def get_instance(
        self,
        instance_id: str,
    ) -> GetInstanceResponse[ReheatParameters]:
        """Get instance parameters from DB."""
        stored = await self._get_stored_or_404(instance_id)
        return GetInstanceResponse(
            instance_id=stored.instance_id,
            parameters=stored.parameters,
        )

    async def update_instance(
        self,
        instance_id: str,
        request: UpdateParametersRequest[ReheatParameters],
    ) -> UpdateInstanceResponse[ReheatParameters]:
        """Update instance parameters in DB. Recreates FMU if it exists."""
        await self._get_stored_or_404(instance_id)
        saved = await self._repository.save(instance_id, request.parameters)

        # Delete FMU so next step() recreates it with new parameters
        await self._adapter.delete_fmu_instance(instance_id)

        return UpdateInstanceResponse(
            instance_id=saved.instance_id,
            parameters=saved.parameters,
        )

    async def step(
        self,
        instance_id: str,
        request: StepRequest,
    ) -> StepResponse:
        """Execute a simulation step on an FMU instance."""
        try:
            stored = await self._get_stored_or_404(instance_id)
            inputs = request.inputs.to_domain()
            fmu_data = ReheatFMUData(inputs=inputs, parameters=stored.parameters)

            outputs = await self._adapter.step(
                instance_id,
                fmu_data,
                request.stepSize,
                sequence_type=SequenceType.REHEAT,
            )
            return StepResponse(
                instance_id=instance_id,
                outputs=ReheatFMUData.create_outputs(outputs),
            )
        except FmuValidationError as e:
            raise HTTPException(status_code=400, detail=str(e)) from e
        except FmuExecutionError as e:
            raise HTTPException(status_code=500, detail=f"FMU execution error: {e}") from e

    async def delete_instance(self, instance_id: str) -> DeleteInstanceResponse:
        """Delete an instance from DB and FMU (idempotent)."""
        db_deleted = await self._repository.delete(instance_id)
        fmu_deleted = await self._adapter.delete_fmu_instance(instance_id)

        return DeleteInstanceResponse(
            instance_id=instance_id,
            deleted=db_deleted or fmu_deleted,
        )
