"""Unit tests for mappings DTOs."""
import json

from src.dto.mappings_dto import (
    MappingsResponseDTO,
    SaveMappingsRequestDTO,
    SemanticMappingDTO,
)


def test_semantic_mapping_dto_uses_camelcase_aliases() -> None:
    """Test SemanticMappingDTO serializes with camelCase field names."""
    dto = SemanticMappingDTO(
        equipment_type_id="urn:223p:VAVReheatTerminalUnit",
        device_type_id="urn:223p:Damper",
        property_id="urn:223p:DamperPosition",
        physical_space_id="urn:bms:PhysicalSpace:room-101",
        domain_space_ids=["urn:bms:Zone:hvac-zone-1", "urn:bms:Zone:lighting-zone-1"],
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert "equipmentTypeId" in json_data
    assert "deviceTypeId" in json_data
    assert "propertyId" in json_data
    assert "physicalSpaceId" in json_data
    assert "domainSpaceIds" in json_data
    assert "equipment_type_id" not in json_data
    assert "device_type_id" not in json_data
    assert "physical_space_id" not in json_data
    assert "domain_space_ids" not in json_data


def test_mappings_response_dto_serializes_correctly() -> None:
    """Test MappingsResponseDTO with dict of mappings."""
    dto = MappingsResponseDTO(
        project_id="proj-123",
        mappings={
            "device-1:ai-1": SemanticMappingDTO(
                equipment_type_id="urn:223p:VAVReheatTerminalUnit",
                device_type_id="urn:223p:Damper",
                property_id="urn:223p:DamperPosition",
                physical_space_id=None,
                domain_space_ids=None,
            )
        },
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert "projectId" in json_data
    assert "project_id" not in json_data
    assert "device-1:ai-1" in json_data["mappings"]
    assert json_data["mappings"]["device-1:ai-1"]["equipmentTypeId"] == "urn:223p:VAVReheatTerminalUnit"


def test_save_mappings_request_dto_serializes_correctly() -> None:
    """Test SaveMappingsRequestDTO bulk save pattern."""
    dto = SaveMappingsRequestDTO(
        project_id="proj-123",
        mappings={
            "point-1": SemanticMappingDTO(
                equipment_type_id="urn:223p:System1",
                device_type_id="urn:223p:Device1",
                property_id="urn:223p:Property1",
            ),
            "point-2": SemanticMappingDTO(
                equipment_type_id="urn:223p:System2",
                device_type_id="urn:223p:Device2",
                property_id="urn:223p:Property2",
            ),
        },
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert "projectId" in json_data
    assert len(json_data["mappings"]) == 2
    assert "point-1" in json_data["mappings"]
    assert "point-2" in json_data["mappings"]
