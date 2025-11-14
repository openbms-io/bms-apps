"""ASHRAE 223P Templates DTOs with hierarchical structure."""
from enum import Enum
from typing import Literal

from pydantic import BaseModel, ConfigDict, Field


class DeviceType(str, Enum):
    """Device type enum for UI behavior."""

    SENSOR = "sensor"
    OTHER = "other"


class TemplatePropertyDTO(BaseModel):
    """Observable property template with hierarchical nesting and metadata."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(
        ...,
        description="Template name (e.g., 'water-temperature')",
        examples=["water-temperature"],
    )
    label: str = Field(..., description="Human-readable label")
    class_uri: str = Field(
        ...,
        alias="classUri",
        description="ASHRAE 223P class URI",
        examples=["http://data.ashrae.org/standard223#QuantifiableObservableProperty"],
    )
    property_type: Literal["quantifiable", "enumerated"] = Field(
        ..., alias="propertyType", description="Property type"
    )
    quantity_kind: str | None = Field(
        None,
        alias="quantityKind",
        description="QUDT quantity kind (e.g., 'Temperature', 'Pressure')",
    )
    unit: str | None = Field(
        None,
        description="QUDT unit (e.g., 'DEG_C', 'PSI')",
    )
    medium: str | None = Field(
        None,
        description="s223 medium (e.g., 'Water', 'Air') - optional",
    )
    enumeration_kind: str | None = Field(
        None,
        alias="enumerationKind",
        description="s223 enumeration kind (e.g., 'RunStatus') - only for enumerated properties",
    )
    is_actuatable: bool = Field(
        ...,
        alias="isActuatable",
        description="Observable (false) vs Actuatable (true)",
    )
    description: str | None = Field(None, description="Property description")


class TemplateDeviceDTO(BaseModel):
    """Device type template with nested properties and UI metadata."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(
        ...,
        description="Template name (e.g., 'damper')",
        examples=["damper"],
    )
    label: str = Field(..., description="Human-readable label")
    class_uri: str = Field(
        ...,
        alias="classUri",
        description="ASHRAE 223P class URI",
        examples=["http://data.ashrae.org/standard223#Damper"],
    )
    device_type: DeviceType = Field(
        ...,
        alias="deviceType",
        description="Device type for UI behavior (sensor vs other)",
    )
    description: str | None = Field(None, description="Device description")
    properties: list[TemplatePropertyDTO] = Field(
        ..., description="Valid properties for this device"
    )


class TemplateSystemDTO(BaseModel):
    """System (equipment) type template with nested devices and class URI."""

    model_config = ConfigDict(populate_by_name=True)

    id: str = Field(
        ...,
        description="Template name (e.g., 'vav-reheat')",
        examples=["vav-reheat"],
    )
    label: str = Field(..., description="Human-readable label")
    class_uri: str = Field(
        ...,
        alias="classUri",
        description="ASHRAE 223P class URI",
        examples=["http://data.ashrae.org/standard223#TerminalUnit"],
    )
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
