"""Integration tests for validating ASHRAE 223P template conformance.

These tests validate that all templates in the NREL library conform to
ASHRAE 223P SHACL shapes when instantiated.
"""
import pytest
from rdflib import Namespace

from buildingmotif.dataclasses import Model

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.adapters.template_types import DeviceTemplate, PropertyTemplate, SystemTemplate
from src.config.settings import get_settings
from src.services.validation_service import ValidationService

TEST_NS = Namespace("urn:test:template-validation:")

pytestmark = pytest.mark.skipif(
    not get_settings().enable_validation,
    reason="SHACL validation disabled. Set ENABLE_VALIDATION=true to run."
)


@pytest.fixture(scope="module")
def validation_adapter():
    """Get BuildingMOTIF adapter with validation enabled."""
    return BuildingMOTIFAdapter.get_instance()


def validate_template(adapter: BuildingMOTIFAdapter, template_enum):
    """Validate a template against 223P SHACL shapes."""
    raw_template = adapter.get_template_by_name(template_enum)
    inlined_template = raw_template.inline_dependencies()
    _bindings, filled_graph = inlined_template.fill(TEST_NS)

    test_model = Model.create(Namespace(f"urn:test:{template_enum.value}#"))
    test_model.graph += filled_graph

    result = ValidationService.validate_model(test_model)
    return result.isValid, result.errors


class TestDeviceTemplateConformance:
    """Test all device templates conform to 223P."""

    @pytest.mark.parametrize("device_template", list(DeviceTemplate))
    def test_device_template_conforms_to_223p(self, validation_adapter, device_template):
        """Each device template should validate against 223P shapes."""
        is_valid, errors = validate_template(validation_adapter, device_template)

        assert is_valid, (
            f"Device template '{device_template.value}' failed 223P validation:\n"
            + "\n".join(f"  - {e}" for e in errors)
        )


class TestSystemTemplateConformance:
    """Test all system templates conform to 223P."""

    @pytest.mark.parametrize("system_template", list(SystemTemplate))
    def test_system_template_conforms_to_223p(self, validation_adapter, system_template):
        """Each system template should validate against 223P shapes."""
        is_valid, errors = validate_template(validation_adapter, system_template)

        assert is_valid, (
            f"System template '{system_template.value}' failed 223P validation:\n"
            + "\n".join(f"  - {e}" for e in errors)
        )


class TestPropertyTemplateConformance:
    """Test all property templates conform to 223P."""

    @pytest.mark.parametrize("property_template", list(PropertyTemplate))
    def test_property_template_conforms_to_223p(self, validation_adapter, property_template):
        """Each property template should validate against 223P shapes."""
        is_valid, errors = validate_template(validation_adapter, property_template)

        assert is_valid, (
            f"Property template '{property_template.value}' failed 223P validation:\n"
            + "\n".join(f"  - {e}" for e in errors)
        )
