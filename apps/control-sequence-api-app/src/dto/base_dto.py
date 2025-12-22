"""Generic base DTOs for control sequence API endpoints."""

from typing import Generic, TypeVar

from pydantic import BaseModel, Field

from src.adapters.sequence_type import SequenceType
from src.dto.common_dto import InputCategory, OutputCategory
from src.dto.reheat_constants import ReheatInputName, ReheatOutputName, ReheatParameterName
from src.models.reheat.enums import ParameterCategory
from src.utils.unit_conversion import AirflowUnit, TemperatureUnit

TParams = TypeVar("TParams", bound=BaseModel)
TOutputs = TypeVar("TOutputs", bound=BaseModel)

ParameterCategories = dict[ParameterCategory, list[str]]
InputCategories = dict[InputCategory, list[ReheatInputName]]
OutputCategories = dict[OutputCategory, list[ReheatOutputName]]
ParameterToRequiredInputs = dict[ReheatParameterName, list[ReheatInputName]]
ParameterToRequiredOutputs = dict[ReheatParameterName, list[ReheatOutputName]]


class CreateInstanceRequest(BaseModel, Generic[TParams]):
    """Request to create an instance with frontend-provided ID and optional parameters."""

    instance_id: str = Field(
        ...,
        description="The instance identifier (UUID) provided by frontend",
        json_schema_extra={"example": "550e8400-e29b-41d4-a716-446655440000"},
    )
    parameters: TParams | None = Field(
        default=None,
        description="Optional initial parameters. If not provided, defaults are used.",
    )


class InstanceResponseWithCategories(BaseModel, Generic[TParams]):
    """Response for GET/POST that includes categories for UI grouping."""

    model_config = {"populate_by_name": True}

    instance_id: str = Field(
        ...,
        serialization_alias="instanceId",
        description="The instance identifier (UUID)",
        json_schema_extra={"example": "550e8400-e29b-41d4-a716-446655440000"},
    )
    parameters: TParams = Field(
        ...,
        description="The parameters for this instance",
    )
    categories: ParameterCategories = Field(
        ...,
        description="Mapping of parameter categories to field names",
    )
    input_categories: InputCategories = Field(
        ...,
        serialization_alias="inputCategories",
        description="Mapping of input categories to input field names for UI grouping",
    )
    output_categories: OutputCategories = Field(
        ...,
        serialization_alias="outputCategories",
        description="Mapping of output categories to output field names for UI grouping",
    )
    parameter_to_required_inputs: ParameterToRequiredInputs = Field(
        ...,
        serialization_alias="parameterToRequiredInputs",
        description="Mapping of parameters to inputs that become required when enabled",
    )
    parameter_to_required_outputs: ParameterToRequiredOutputs = Field(
        ...,
        serialization_alias="parameterToRequiredOutputs",
        description="Mapping of parameters to outputs that become available when enabled",
    )


CreateInstanceResponse = InstanceResponseWithCategories
GetInstanceResponse = InstanceResponseWithCategories
UpdateInstanceResponse = InstanceResponseWithCategories


class UpdateParametersRequest(BaseModel, Generic[TParams]):
    """Request to update instance parameters. Generic over parameter type."""

    parameters: TParams = Field(
        ...,
        description="The updated parameters for this instance",
    )


class DeleteInstanceResponse(BaseModel):
    """Response after deleting an instance."""

    model_config = {"populate_by_name": True}

    instance_id: str = Field(
        ...,
        serialization_alias="instanceId",
        description="The deleted instance identifier",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    deleted: bool = Field(
        ...,
        description="Whether the instance was successfully deleted",
        json_schema_extra={"example": True},
    )


class ConvertParametersRequest(BaseModel, Generic[TParams]):
    """Request to convert parameters to target units."""

    model_config = {"populate_by_name": True}

    sequence_type: SequenceType = Field(
        ...,
        serialization_alias="sequenceType",
        description="The sequence type for parameter conversion",
    )
    parameters: TParams = Field(
        ...,
        description="Current parameters with source units",
    )
    target_temperature_unit: TemperatureUnit = Field(
        ...,
        serialization_alias="targetTemperatureUnit",
        description="Target temperature unit for conversion",
    )
    target_airflow_unit: AirflowUnit = Field(
        ...,
        serialization_alias="targetAirflowUnit",
        description="Target airflow unit for conversion",
    )


class ConvertParametersResponse(BaseModel, Generic[TParams]):
    """Response with converted parameters."""

    parameters: TParams = Field(
        ...,
        description="Parameters converted to target units",
    )


class DefaultsResponse(BaseModel, Generic[TParams]):
    """Response with default parameters."""

    parameters: TParams = Field(
        ...,
        description="Default parameters in SI units",
    )
