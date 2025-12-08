"""Health endpoint DTOs."""

from pydantic import BaseModel, Field


class HealthResponse(BaseModel):
    """Health check response with API status and FMU instance metrics."""

    status: str = Field(description="API health status")
    service: str = Field(description="Service name")
    version: str = Field(description="Service version")
    active_instances: int = Field(
        ge=0,
        description="Number of active FMU instances",
    )
