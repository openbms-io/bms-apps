"""Integration tests for MappingsModel database persistence."""
import pytest

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.config.settings import Settings
from src.dto.mappings_dto import SemanticMappingDTO
from src.models.mappings_model import MappingsModel


@pytest.fixture
def test_settings():
    """Test settings with correct template path."""
    return Settings(
        buildingmotif_templates_path="apps/building-semantics-api-app/data/libraries/ashrae-223p-nrel"
    )


def test_mappings_persist_across_adapter_restarts(tmp_path, test_settings):
    """Test mappings survive adapter restart (proves DB persistence)."""
    # Setup: Create adapter with persistent DB
    db_path = tmp_path / "test_persistence.db"
    BuildingMOTIFAdapter._instance = None
    adapter1 = BuildingMOTIFAdapter(str(db_path), test_settings)
    model1 = MappingsModel(adapter1)

    # Action 1: Save mappings using first adapter
    project_id = "test-project"
    mappings = {
        "device,100:analog-input,1": SemanticMappingDTO(
            equipment_type_id="vav-reheat",
            device_type_id="damper",
            property_id="damper-feedback",
            physical_space_id="urn:bms:Space:room-101",
            domain_space_ids=["urn:bms:Zone:hvac-1", "urn:bms:Zone:lighting-1"]
        )
    }
    model1.replace_all_mappings(project_id, mappings)

    # Simulate app restart: Destroy adapter, create new one
    del adapter1, model1
    BuildingMOTIFAdapter._instance = None

    # Action 2: Load from DB using new adapter
    adapter2 = BuildingMOTIFAdapter(str(db_path), test_settings)
    model2 = MappingsModel(adapter2)

    # Verify: Data persisted and matches exactly
    retrieved = model2.get_all_mappings(project_id)
    assert len(retrieved) == 1
    assert "device,100:analog-input,1" in retrieved

    mapping = retrieved["device,100:analog-input,1"]
    assert mapping.equipment_type_id == "vav-reheat"
    assert mapping.device_type_id == "damper"
    assert mapping.property_id == "damper-feedback"
    assert mapping.physical_space_id == "urn:bms:Space:room-101"
    assert mapping.domain_space_ids == ["urn:bms:Zone:hvac-1", "urn:bms:Zone:lighting-1"]


def test_multiple_mappings_persist_correctly(tmp_path, test_settings):
    """Test multiple mappings with different space configurations persist."""
    db_path = tmp_path / "test_multi.db"
    BuildingMOTIFAdapter._instance = None
    adapter1 = BuildingMOTIFAdapter(str(db_path), test_settings)
    model1 = MappingsModel(adapter1)

    project_id = "multi-project"
    mappings = {
        "device,200:analog-input,2": SemanticMappingDTO(
            equipment_type_id="vav-reheat",
            device_type_id="damper",
            property_id="damper-command",
            physical_space_id="urn:bms:Space:room-202",
            domain_space_ids=None
        ),
        "device,300:analog-input,3": SemanticMappingDTO(
            equipment_type_id="vav-reheat",
            device_type_id="damper",
            property_id="damper-feedback",
            physical_space_id=None,
            domain_space_ids=["urn:bms:Zone:hvac-2"]
        ),
        "device,400:analog-input,4": SemanticMappingDTO(
            equipment_type_id="vav-reheat",
            device_type_id="damper",
            property_id="damper-command",
            physical_space_id=None,
            domain_space_ids=None
        )
    }
    model1.replace_all_mappings(project_id, mappings)

    # Restart adapter
    del adapter1, model1
    BuildingMOTIFAdapter._instance = None

    adapter2 = BuildingMOTIFAdapter(str(db_path), test_settings)
    model2 = MappingsModel(adapter2)

    # Verify all mappings persisted with correct space configurations
    retrieved = model2.get_all_mappings(project_id)
    assert len(retrieved) == 3

    # Verify physical space only
    assert retrieved["device,200:analog-input,2"].physical_space_id == "urn:bms:Space:room-202"
    assert retrieved["device,200:analog-input,2"].domain_space_ids is None

    # Verify domain spaces only
    assert retrieved["device,300:analog-input,3"].physical_space_id is None
    assert retrieved["device,300:analog-input,3"].domain_space_ids == ["urn:bms:Zone:hvac-2"]

    # Verify no spaces
    assert retrieved["device,400:analog-input,4"].physical_space_id is None
    assert retrieved["device,400:analog-input,4"].domain_space_ids is None


def test_replace_mappings_overwrites_previous_data(tmp_path, test_settings):
    """Test replace operation clears old data and saves new data persistently."""
    db_path = tmp_path / "test_replace.db"
    BuildingMOTIFAdapter._instance = None
    adapter = BuildingMOTIFAdapter(str(db_path), test_settings)
    model = MappingsModel(adapter)

    project_id = "replace-project"

    # Save initial mappings
    initial_mappings = {
        "device,500:analog-input,5": SemanticMappingDTO(
            equipment_type_id="vav-reheat",
            device_type_id="damper",
            property_id="damper-feedback",
            physical_space_id=None,
            domain_space_ids=None
        )
    }
    model.replace_all_mappings(project_id, initial_mappings)

    # Replace with different mappings
    new_mappings = {
        "device,600:analog-input,6": SemanticMappingDTO(
            equipment_type_id="vav-reheat",
            device_type_id="damper",
            property_id="damper-command",
            physical_space_id="urn:bms:Space:room-303",
            domain_space_ids=["urn:bms:Zone:hvac-3"]
        )
    }
    model.replace_all_mappings(project_id, new_mappings)

    # Restart adapter
    del adapter, model
    BuildingMOTIFAdapter._instance = None

    adapter2 = BuildingMOTIFAdapter(str(db_path), test_settings)
    model2 = MappingsModel(adapter2)

    # Verify only new mappings exist (old ones were replaced)
    retrieved = model2.get_all_mappings(project_id)
    assert len(retrieved) == 1
    assert "device,500:analog-input,5" not in retrieved
    assert "device,600:analog-input,6" in retrieved
    assert retrieved["device,600:analog-input,6"].physical_space_id == "urn:bms:Space:room-303"
