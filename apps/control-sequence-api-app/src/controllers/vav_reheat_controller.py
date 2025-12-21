"""G36 VAV Reheat Controller for Reheat Terminal FMU operations."""

from fastapi import HTTPException
from pydantic import ValidationError

from loguru import logger

from src.adapters.exceptions import (
    FmuExecutionError,
    FmuValidationError,
)
from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData
from src.adapters.sequence_type import SequenceType
from src.dto.base_dto import (
    CreateInstanceRequest,
    CreateInstanceResponse,
    DeleteInstanceResponse,
    GetInstanceResponse,
    UpdateInstanceResponse,
    UpdateParametersRequest,
)
from src.dto.reheat_constants import INPUT_CATEGORIES, OUTPUT_CATEGORIES
from src.dto.reheat_dto import ReheatOutputsDTO, ReheatParametersDTO, StepRequest, StepResponse
from src.models.reheat.parameters import ReheatParameters
from src.repositories.reheat_repository import ReheatRepository
from src.services.parameter_converter import ParameterConverter

class VavReheatController:
    """Controller for G36 VAV Reheat Terminal operations.

    Maps adapter exceptions to HTTP errors per tech spec Section 4.3.
    """

    def __init__(self, adapter: FmuAdapter, repository: ReheatRepository) -> None:
        self._adapter = adapter
        self._repository = repository
        self._converter = ParameterConverter()

    async def _get_stored_or_404(self, instance_id: str):
        stored = await self._repository.get_active(instance_id)
        if stored is None:
            raise HTTPException(status_code=404, detail=f"Instance {instance_id} not found")
        return stored

    def _validate_and_convert_to_domain(self, dto: ReheatParametersDTO) -> ReheatParameters:
        """Validate DTO parameters and convert to domain model.

        Raises HTTPException 400 if validation fails.
        """
        try:
            self._converter.validate_parameters(dto)
        except ValueError as e:
            raise HTTPException(status_code=400, detail=str(e)) from e
        return dto.to_domain()

    async def create_instance(
        self, request: CreateInstanceRequest[ReheatParametersDTO]
    ) -> CreateInstanceResponse[ReheatParameters]:
        """Create a new instance with frontend-provided ID and optional parameters.

        Idempotent: if instance_id exists, returns existing instance.
        FMU instance is lazily created on first step() call.
        """
        params = (
            self._validate_and_convert_to_domain(request.parameters)
            if request.parameters
            else ReheatParameters()
        )
        instance, _ = await self._repository.get_or_create(
            request.instance_id, params
        )

        return CreateInstanceResponse(
            instance_id=instance.instance_id,
            parameters=instance.parameters,
            categories=ReheatParameters.get_categories(),
            input_categories=INPUT_CATEGORIES,
            output_categories=OUTPUT_CATEGORIES,
            parameter_to_required_inputs=ReheatParameters.get_parameter_to_required_inputs(),
            parameter_to_required_outputs=ReheatParameters.get_parameter_to_required_outputs(),
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
            categories=ReheatParameters.get_categories(),
            input_categories=INPUT_CATEGORIES,
            output_categories=OUTPUT_CATEGORIES,
            parameter_to_required_inputs=ReheatParameters.get_parameter_to_required_inputs(),
            parameter_to_required_outputs=ReheatParameters.get_parameter_to_required_outputs(),
        )

    async def update_instance(
        self,
        instance_id: str,
        request: UpdateParametersRequest[ReheatParametersDTO],
    ) -> UpdateInstanceResponse[ReheatParameters]:
        """Update instance parameters in DB. Recreates FMU if it exists."""
        await self._get_stored_or_404(instance_id)
        params = self._validate_and_convert_to_domain(request.parameters)
        saved = await self._repository.save(instance_id, params)

        # Delete FMU so next step() recreates it with new parameters
        await self._adapter.delete_fmu_instance(instance_id)

        return UpdateInstanceResponse(
            instance_id=saved.instance_id,
            parameters=saved.parameters,
            categories=ReheatParameters.get_categories(),
            input_categories=INPUT_CATEGORIES,
            output_categories=OUTPUT_CATEGORIES,
            parameter_to_required_inputs=ReheatParameters.get_parameter_to_required_inputs(),
            parameter_to_required_outputs=ReheatParameters.get_parameter_to_required_outputs(),
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
                sequence_type=SequenceType.VAV_REHEAT,
            )
            logger.info(f"step: FMU outputs: {outputs}")
            domain_outputs = ReheatFMUData.create_outputs(outputs)
            airflow_unit = stored.parameters.airflowUnit

            return StepResponse(
                instance_id=instance_id,
                outputs=ReheatOutputsDTO.from_domain(domain_outputs, airflow_unit),
            )
        except ValidationError as e:
            raise HTTPException(status_code=422, detail=e.errors()) from e
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

    async def delete_fmu(self, instance_id: str) -> DeleteInstanceResponse:
        """Delete only FMU runtime, preserving DB parameters (idempotent)."""
        fmu_deleted = await self._adapter.delete_fmu_instance(instance_id)

        return DeleteInstanceResponse(
            instance_id=instance_id,
            deleted=fmu_deleted,
        )
