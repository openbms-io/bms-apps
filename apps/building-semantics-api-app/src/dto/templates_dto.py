"""ASHRAE 223P Templates DTOs with hierarchical structure."""
from typing import Literal

from pydantic import BaseModel, ConfigDict, Field


class TemplatePropertyDTO(BaseModel):
    """Observable property template with hierarchical nesting."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(
        ..., description="Property URN", examples=["urn:223p:DamperPosition"]
    )
    label: str = Field(..., description="Human-readable label")
    property_type: Literal["quantifiable", "enumerated"] = Field(
        ..., alias="propertyType", description="Property type"
    )
    description: str | None = Field(None, description="Property description")


class TemplateDeviceDTO(BaseModel):
    """Device type template with nested properties."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(..., description="Device URN", examples=["urn:223p:Damper"])
    label: str = Field(..., description="Human-readable label")
    description: str | None = Field(None, description="Device description")
    properties: list[TemplatePropertyDTO] = Field(
        ..., description="Valid properties for this device"
    )


class TemplateSystemDTO(BaseModel):
    """System (equipment) type template with nested devices."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(
        ...,
        description="System URN",
        examples=["urn:223p:VAVReheatTerminalUnit"],
    )
    label: str = Field(..., description="Human-readable label")
    description: str | None = Field(None, description="System description")
    devices: list[TemplateDeviceDTO] = Field(
        ..., description="Valid devices for this system"
    )


class SpaceTypeDTO(BaseModel):
    """Space type template from ASHRAE 223P ontology."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(
        ..., description="Space type URN", examples=["urn:223p:Office"]
    )
    label: str = Field(..., description="Human-readable label")
    description: str | None = Field(None, description="Space type description")


class TemplatesResponseDTO(BaseModel):
    """Complete hierarchical template structure with all relationships."""

    model_config = ConfigDict(populate_by_name=True)

    systems: list[TemplateSystemDTO] = Field(
        ...,
        description=(
            "All ASHRAE 223P system templates with nested devices and properties"
        ),
    )
    space_types: list[SpaceTypeDTO] = Field(
        ...,
        alias="spaceTypes",
        description="All ASHRAE 223P space type templates",
    )
