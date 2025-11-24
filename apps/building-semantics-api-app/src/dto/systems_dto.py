"""ASHRAE 223P System Instance DTOs."""

from typing import Literal

from pydantic import BaseModel, ConfigDict, Field


class CreateSystemRequestDTO(BaseModel):
    """Request DTO for creating system instance."""

    model_config = ConfigDict(populate_by_name=True)

    template_id: str = Field(
        ...,
        alias="templateId",
        description="System template ID (e.g., 'vav-reheat')",
        examples=["vav-reheat"],
    )
    label: str = Field(
        ...,
        description="User-provided custom label for this system instance",
        examples=["VAV-Floor3-Zone5"],
    )


class SystemInstanceDTO(BaseModel):
    """System instance with metadata."""

    model_config = ConfigDict(populate_by_name=True)

    system_uri: str = Field(
        ...,
        alias="systemUri",
        description="System URI (BuildingMOTIF auto-generated)",
        examples=["urn:bms:system-123"],
    )
    label: str = Field(
        ...,
        description="User-provided custom label",
        examples=["VAV-Floor3-Zone5"],
    )
    template_id: str = Field(
        ...,
        alias="templateId",
        description="Template ID used to create this system",
        examples=["vav-reheat"],
    )
    created: str = Field(
        ...,
        description="ISO 8601 creation timestamp",
        examples=["2025-11-19T15:00:00"],
    )


class SystemSummaryDTO(BaseModel):
    """Lightweight system summary for list views."""

    model_config = ConfigDict(populate_by_name=True)

    system_uri: str = Field(
        ...,
        alias="systemUri",
        description="System URI",
    )
    label: str = Field(
        ...,
        description="User-provided custom label",
    )
    template_id: str = Field(
        ...,
        alias="templateId",
        description="Template ID",
    )


class DeviceDTO(BaseModel):
    """Device within a system instance."""

    model_config = ConfigDict(populate_by_name=True)

    device_uri: str = Field(
        ...,
        alias="deviceUri",
        description="Device URI (BuildingMOTIF auto-generated)",
    )
    label: str = Field(
        ...,
        description="Device label from template",
        examples=["Damper"],
    )


class PropertyDTO(BaseModel):
    """Property within a device with ASHRAE 223P metadata."""

    model_config = ConfigDict(populate_by_name=True)

    property_uri: str = Field(
        ...,
        alias="propertyUri",
        description="Property URI (BuildingMOTIF auto-generated)",
    )
    label: str = Field(
        ...,
        description="Property label from template",
        examples=["Damper Position"],
    )
    is_actuatable: bool = Field(
        ...,
        alias="isActuatable",
        description="Whether property is actuatable (output) or observable (input)",
    )
    class_uri: str | None = Field(
        None,
        alias="classUri",
        description="ASHRAE 223P class URI",
        examples=["http://data.ashrae.org/standard223#QuantifiableObservableProperty"],
    )
    property_type: Literal["quantifiable", "enumerated"] | None = Field(
        None,
        alias="propertyType",
        description="Property type (quantifiable or enumerated)",
    )
    quantity_kind: str | None = Field(
        None,
        alias="quantityKind",
        description="QUDT quantity kind (e.g., 'Temperature', 'Pressure')",
        examples=["Temperature"],
    )
    unit: str | None = Field(
        None,
        description="QUDT unit (e.g., 'DEG_C', 'PSI')",
        examples=["DEG_C"],
    )
    medium: str | None = Field(
        None,
        description="s223 medium (e.g., 'Water', 'Air')",
        examples=["Water"],
    )
    enumeration_kind: str | None = Field(
        None,
        alias="enumerationKind",
        description="s223 enumeration kind (e.g., 'RunStatus') - for enumerated properties",
        examples=["RunStatus"],
    )
