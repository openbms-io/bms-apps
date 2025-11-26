"""ASHRAE 223P Space Instance DTOs."""
from pydantic import BaseModel, ConfigDict, Field


class SpaceInstanceDTO(BaseModel):
    """Space instance for a project."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(
        ...,
        description="Space instance URN",
        examples=["urn:bms:PhysicalSpace:room-101"],
    )
    space_type_id: str = Field(
        ...,
        alias="spaceTypeId",
        description="Space type URN from template",
    )
    label: str = Field(
        ..., description="Display name", examples=["Room 101 - John's Office"]
    )
    created_at: str = Field(
        ..., alias="createdAt", description="ISO 8601 timestamp"
    )


class CreateSpaceRequestDTO(BaseModel):
    """Request to create a new space instance."""

    model_config = ConfigDict(populate_by_name=True)

    project_id: str = Field(
        ..., alias="projectId", description="Project identifier"
    )
    space_type_id: str = Field(
        ...,
        alias="spaceTypeId",
        description="Space type URN from template",
    )
    label: str = Field(..., description="Display name for the space")
