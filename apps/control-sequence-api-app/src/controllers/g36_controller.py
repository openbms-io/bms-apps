"""G36 Reheat Controller for Reheat Terminal FMU operations."""

from fastapi import HTTPException

from src.adapters.exceptions import (
    FmuExecutionError,
    FmuInstanceNotFoundError,
    FmuValidationError,
)
from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData
from src.adapters.sequence_type import SequenceType
from src.dto.reheat_dto import (
    CreateInstanceRequest,
    CreateInstanceResponse,
    DeleteInstanceResponse,
    ReheatInputs,
    StepRequest,
    StepResponse,
)


class G36ReheatController:
    """Controller for G36 Reheat Terminal operations.

    Maps adapter exceptions to HTTP errors per tech spec Section 4.3.
    """

    def __init__(self, adapter: FmuAdapter) -> None:
        self._adapter = adapter

    async def upsert_instance(
        self,
        request: CreateInstanceRequest,
    ) -> CreateInstanceResponse:
        """Create or recreate an FMU instance."""
        try:
            inputs = ReheatInputs.from_request(request.inputs)
            fmu_data = ReheatFMUData(inputs=inputs, parameters=request.parameters)

            result = await self._adapter.upsert_fmu_instance(
                sequence_type=SequenceType.REHEAT,
                fmu_data=fmu_data,
                instance_id=request.instance_id,
            )

            return CreateInstanceResponse(
                instance_id=result.instance_id,
                created=result.is_created,
                parameters=request.parameters,
            )
        except FmuValidationError as e:
            raise HTTPException(status_code=400, detail=str(e)) from e
        except FmuExecutionError as e:
            raise HTTPException(status_code=500, detail=f"FMU execution error: {e}") from e

    async def step(
        self,
        instance_id: str,
        request: StepRequest,
    ) -> StepResponse:
        """Execute a simulation step on an FMU instance."""
        try:
            inputs = ReheatInputs.from_request(request.inputs)
            fmu_data = ReheatFMUData(inputs=inputs)
            outputs = await self._adapter.step(instance_id, fmu_data, request.stepSize)
            return StepResponse(
                instance_id=instance_id,
                outputs=ReheatFMUData.create_outputs(outputs),
            )
        except FmuInstanceNotFoundError:
            raise HTTPException(
                status_code=404,
                detail=f"Instance {instance_id} not found",
            ) from None
        except FmuValidationError as e:
            raise HTTPException(status_code=400, detail=str(e)) from e
        except FmuExecutionError as e:
            raise HTTPException(status_code=500, detail=f"FMU execution error: {e}") from e

    async def delete_instance(self, instance_id: str) -> DeleteInstanceResponse:
        """Delete an FMU instance (idempotent)."""
        was_existing = self._adapter.has_instance(instance_id)

        if was_existing:
            try:
                await self._adapter.delete_fmu_instance(instance_id)
            except FmuExecutionError as e:
                raise HTTPException(
                    status_code=500,
                    detail=f"FMU execution error: {e}",
                ) from e

        return DeleteInstanceResponse(
            instance_id=instance_id,
            deleted=was_existing,
        )
