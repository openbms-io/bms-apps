"""Parameters utility router for unit conversion and defaults.

Route structure: /api/v1/parameters/...

Generic endpoints that work across all sequence types.
"""

from fastapi import APIRouter, HTTPException, Query

from src.adapters.sequence_type import SequenceType
from src.dto.base_dto import (
    ConvertParametersRequest,
    ConvertParametersResponse,
    DefaultsResponse,
)
from src.dto.common_dto import ErrorResponse
from src.dto.reheat_dto import ReheatParametersDTO
from src.models.reheat.parameters import ReheatParameters
from src.services.parameter_converter import ParameterConverter

router = APIRouter(prefix="/api/v1/parameters", tags=["Parameters"])


@router.post(
    "/convert",
    response_model=ConvertParametersResponse[ReheatParametersDTO],
    responses={
        200: {"description": "Parameters converted successfully"},
        400: {"description": "Unknown sequence type", "model": ErrorResponse},
        422: {"description": "Validation error in request body"},
    },
)
async def convert_parameters(
    request: ConvertParametersRequest[ReheatParametersDTO],
) -> ConvertParametersResponse[ReheatParametersDTO]:
    """Convert parameters to target units.

    Stateless utility for converting parameter values between unit systems.
    Does not persist changes - use update_instance to save.

    Use this endpoint when:
    - User changes unit preference in the configuration panel
    - Converting parameters for display in different units
    """
    converter = ParameterConverter()
    try:
        converted = converter.convert_parameters(
            request.sequence_type,
            request.parameters,
            request.target_temperature_unit,
            request.target_airflow_unit,
        )
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e)) from e

    return ConvertParametersResponse(parameters=converted)


@router.get(
    "/defaults",
    response_model=DefaultsResponse[ReheatParameters],
    responses={
        200: {"description": "Default parameters returned"},
        400: {"description": "Unknown sequence type", "model": ErrorResponse},
    },
)
async def get_defaults(
    sequence_type: SequenceType = Query(
        ...,
        alias="sequenceType",
        description="Sequence type to get defaults for",
    ),
) -> DefaultsResponse[ReheatParameters]:
    """Get default parameters for a sequence type.

    Returns fresh default parameters in SI units (Kelvin, m³/s).

    Use this endpoint when:
    - User clicks "Reset to Defaults" button
    - Initializing a new instance with default values
    """
    if sequence_type == SequenceType.VAV_REHEAT:
        return DefaultsResponse(parameters=ReheatParameters())

    raise HTTPException(
        status_code=400,
        detail=f"Unknown sequence type: {sequence_type}",
    )
