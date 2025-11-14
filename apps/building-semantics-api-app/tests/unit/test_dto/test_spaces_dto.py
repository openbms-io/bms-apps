"""Unit tests for spaces DTOs."""
import json

from src.dto.spaces_dto import CreateSpaceRequestDTO, SpaceInstanceDTO


def test_space_instance_dto_uses_camelcase_aliases() -> None:
    """Test SpaceInstanceDTO serializes with camelCase field names."""
    dto = SpaceInstanceDTO(
        id="urn:bms:PhysicalSpace:room-101",
        space_type_id="urn:223p:Office",
        label="Room 101 - John's Office",
        created_at="2025-01-01T00:00:00Z",
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert "spaceTypeId" in json_data
    assert "createdAt" in json_data
    assert "space_type_id" not in json_data
    assert "created_at" not in json_data


def test_create_space_request_dto_uses_camelcase_aliases() -> None:
    """Test CreateSpaceRequestDTO serializes with camelCase field names."""
    dto = CreateSpaceRequestDTO(
        project_id="proj-123",
        space_type_id="urn:223p:Office",
        label="Room 101 - John's Office",
    )

    json_data = json.loads(dto.model_dump_json(by_alias=True))

    assert "projectId" in json_data
    assert "spaceTypeId" in json_data
    assert "project_id" not in json_data
    assert "space_type_id" not in json_data
