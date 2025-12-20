from enum import StrEnum

from pydantic import BaseModel, Field


class InputCategory(StrEnum):
    """Categories for grouping control sequence inputs.

    Logical groupings based on G36 domain model.
    Reusable across G36 sequence types (VAV Reheat, Cooling Only, etc.)
    """

    ZONE_TEMPERATURE = "zoneTemperature"
    ZONE_AIR_QUALITY = "zoneAirQuality"
    ZONE_SENSORS = "zoneSensors"
    VAV_TERMINAL = "vavTerminal"
    AHU = "ahu"
    PLANT = "plant"
    CONTROL = "control"


class OutputCategory(StrEnum):
    """Categories for grouping control sequence outputs.

    Category names indicate destination for routing.
    Reusable across G36 sequence types (VAV Reheat, Cooling Only, etc.)
    """

    VAV_CONTROL = "vavControl"
    AHU_REQUESTS = "ahuRequests"
    PLANT_REQUESTS = "plantRequests"
    ALARMS = "alarms"
    VENTILATION_INFO = "ventilationInfo"


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
