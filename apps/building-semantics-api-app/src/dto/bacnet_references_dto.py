"""BACnet Reference DTOs."""

from pydantic import BaseModel, ConfigDict, Field


class CreateBACnetReferenceRequestDTO(BaseModel):
    """Request DTO for creating/updating BACnet reference."""

    model_config = ConfigDict(populate_by_name=True)

    property_uri: str = Field(
        ...,
        alias="propertyUri",
        description="Property URI from system instance to map to this BACnet point",
        examples=["urn:bms:property-abc123"],
    )


class BACnetReferenceDTO(BaseModel):
    """BACnet reference with basic mapping."""

    model_config = ConfigDict(populate_by_name=True)

    bacnet_point_id: str = Field(
        ...,
        alias="bacnetPointId",
        description="BACnet point identifier",
        examples=["device123.analog-input-1"],
    )
    property_uri: str = Field(
        ...,
        alias="propertyUri",
        description="Property URI this point maps to",
        examples=["urn:bms:property-abc123"],
    )


class EnrichedBACnetReferenceDTO(BaseModel):
    """Enriched BACnet reference with complete system → device → property chain."""

    model_config = ConfigDict(populate_by_name=True)

    bacnet_point_id: str = Field(
        ...,
        alias="bacnetPointId",
        description="BACnet point identifier",
    )
    property_uri: str = Field(
        ...,
        alias="propertyUri",
        description="Property URI",
    )
    property_label: str = Field(
        ...,
        alias="propertyLabel",
        description="Property label from template",
    )
    device_uri: str = Field(
        ...,
        alias="deviceUri",
        description="Device URI containing this property",
    )
    device_label: str = Field(
        ...,
        alias="deviceLabel",
        description="Device label from template",
    )
    system_uri: str = Field(
        ...,
        alias="systemUri",
        description="System URI containing this device",
    )
    system_label: str = Field(
        ...,
        alias="systemLabel",
        description="System label (user-provided)",
    )
    system_template: str = Field(
        ...,
        alias="systemTemplate",
        description="System template ID",
    )
