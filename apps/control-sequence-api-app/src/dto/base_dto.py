"""Generic base DTOs for control sequence API endpoints."""

from typing import Generic, TypeVar

from pydantic import BaseModel, Field

TParams = TypeVar("TParams", bound=BaseModel)
TOutputs = TypeVar("TOutputs", bound=BaseModel)


class CreateInstanceResponse(BaseModel, Generic[TParams]):
    """Response after creating an instance. Generic over parameter type."""

    instance_id: str = Field(
        ...,
        description="The auto-generated instance identifier (UUID)",
        json_schema_extra={"example": "550e8400-e29b-41d4-a716-446655440000"},
    )
    parameters: TParams = Field(
        ...,
        description="The default parameters applied to this instance",
    )


class GetInstanceResponse(BaseModel, Generic[TParams]):
    """Response for GET /instances/{id}. Generic over parameter type."""

    instance_id: str = Field(
        ...,
        description="The instance identifier (UUID)",
        json_schema_extra={"example": "550e8400-e29b-41d4-a716-446655440000"},
    )
    parameters: TParams = Field(
        ...,
        description="The current parameters for this instance",
    )


class UpdateParametersRequest(BaseModel, Generic[TParams]):
    """Request to update instance parameters. Generic over parameter type."""

    parameters: TParams = Field(
        ...,
        description="The updated parameters for this instance",
    )


class UpdateInstanceResponse(BaseModel, Generic[TParams]):
    """Response after updating instance parameters. Generic over parameter type."""

    instance_id: str = Field(
        ...,
        description="The instance identifier (UUID)",
        json_schema_extra={"example": "550e8400-e29b-41d4-a716-446655440000"},
    )
    parameters: TParams = Field(
        ...,
        description="The updated parameters for this instance",
    )


class DeleteInstanceResponse(BaseModel):
    """Response after deleting an instance."""

    instance_id: str = Field(
        ...,
        description="The deleted instance identifier",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    deleted: bool = Field(
        ...,
        description="Whether the instance was successfully deleted",
        json_schema_extra={"example": True},
    )
