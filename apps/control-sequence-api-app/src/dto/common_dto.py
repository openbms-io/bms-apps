from pydantic import BaseModel, Field


class ErrorResponse(BaseModel):
    """Standard error response for API errors."""

    error: str = Field(
        ...,
        description="Error type or code",
        json_schema_extra={"example": "NOT_FOUND"},
    )
    detail: str = Field(
        ...,
        description="Detailed error message",
        json_schema_extra={"example": "Instance 'reheat-zone-1' not found"},
    )


class HealthResponse(BaseModel):
    """Health check response with service status."""

    status: str = Field(
        ...,
        description="Service health status",
        json_schema_extra={"example": "healthy"},
    )
    active_instances: int = Field(
        ...,
        description="Number of active FMU instances",
        json_schema_extra={"example": 3},
    )
