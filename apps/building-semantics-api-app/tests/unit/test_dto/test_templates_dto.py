"""Unit tests for templates DTOs."""
import json

from src.dto.templates_dto import (
    SpaceTypeDTO,
    TemplateDeviceDTO,
    TemplatePropertyDTO,
    TemplatesResponseDTO,
    TemplateSystemDTO,
)


def test_template_property_dto_serializes_with_camelcase() -> None:
    """Test TemplatePropertyDTO uses camelCase for propertyType."""
    dto = TemplatePropertyDTO(
        id="urn:223p:DamperPosition",
        label="Damper Position",
        property_type="quantifiable",
        description="Test property",
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert "propertyType" in json_data
    assert json_data["propertyType"] == "quantifiable"
    assert "property_type" not in json_data


def test_templates_response_dto_serializes_with_camelcase() -> None:
    """Test TemplatesResponseDTO uses camelCase for spaceTypes."""
    dto = TemplatesResponseDTO(
        systems=[
            TemplateSystemDTO(
                id="urn:223p:TestSystem",
                label="Test System",
                devices=[
                    TemplateDeviceDTO(
                        id="urn:223p:TestDevice",
                        label="Test Device",
                        properties=[
                            TemplatePropertyDTO(
                                id="urn:223p:TestProperty",
                                label="Test Property",
                                property_type="quantifiable",
                            )
                        ],
                    )
                ],
            )
        ],
        space_types=[
            SpaceTypeDTO(id="urn:223p:Office", label="Office", description="Test")
        ],
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert "spaceTypes" in json_data
    assert "space_types" not in json_data
    assert len(json_data["spaceTypes"]) == 1


def test_hierarchical_structure_preserved() -> None:
    """Test nested structure is preserved in serialization."""
    dto = TemplatesResponseDTO(
        systems=[
            TemplateSystemDTO(
                id="urn:223p:VAVReheatTerminalUnit",
                label="VAV with Reheat",
                devices=[
                    TemplateDeviceDTO(
                        id="urn:223p:Damper",
                        label="Damper",
                        properties=[
                            TemplatePropertyDTO(
                                id="urn:223p:DamperPosition",
                                label="Damper Position",
                                property_type="quantifiable",
                            )
                        ],
                    )
                ],
            )
        ],
        space_types=[],
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert len(json_data["systems"]) == 1
    system = json_data["systems"][0]
    assert len(system["devices"]) == 1
    device = system["devices"][0]
    assert len(device["properties"]) == 1
    assert device["properties"][0]["propertyType"] == "quantifiable"
