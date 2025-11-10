"""ASHRAE 223P Semantic Mappings DTOs with bulk operations pattern."""
from pydantic import BaseModel, ConfigDict, Field


class SemanticMappingDTO(BaseModel):
    """Semantic equipment mapping for a single BACnet point."""

    model_config = ConfigDict(populate_by_name=True)

    equipment_type_id: str = Field(
        ...,
        alias="equipmentTypeId",
        description="Equipment type URN from template",
    )
    device_type_id: str = Field(
        ...,
        alias="deviceTypeId",
        description="Device type URN from template",
    )
    property_id: str = Field(
        ..., alias="propertyId", description="Property URN from template"
    )
    space_id: str | None = Field(
        None, alias="spaceId", description="Space instance URN (optional)"
    )


class MappingsResponseDTO(BaseModel):
    """All semantic mappings for a project."""

    model_config = ConfigDict(populate_by_name=True)

    project_id: str = Field(
        ..., alias="projectId", description="Project identifier"
    )
    mappings: dict[str, SemanticMappingDTO] = Field(
        ..., description="Point ID -> semantic mapping"
    )


class SaveMappingsRequestDTO(BaseModel):
    """Request to bulk save/replace all mappings for a project."""

    model_config = ConfigDict(populate_by_name=True)

    project_id: str = Field(
        ..., alias="projectId", description="Project identifier"
    )
    mappings: dict[str, SemanticMappingDTO] = Field(
        ..., description="Point ID -> semantic mapping (replaces all existing)"
    )
