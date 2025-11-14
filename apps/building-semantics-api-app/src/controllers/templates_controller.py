"""Controller for ASHRAE 223P templates operations."""
from typing import Any, TypeAlias

from buildingmotif.dataclasses import Template
from loguru import logger

from ..adapters import BuildingMOTIFAdapter, DeviceTemplate, PropertyTemplate, SystemTemplate, TemplateType
from ..dto.templates_dto import DeviceType, TemplatePropertyDTO, TemplatesResponseDTO
from ..mappers.template_mapper import (
    is_device_template,
    is_property_template,
    to_property_dto,
    to_system_dto,
)

# Type alias for device templates with their property dependencies
DeviceWithProperties: TypeAlias = tuple[Template, list[Template]]


class TemplatesController:
    """Business logic for ASHRAE 223P templates operations."""

    def __init__(self) -> None:
        """Initialize controller with singleton BuildingMOTIF adapter."""
        self.adapter = BuildingMOTIFAdapter.get_instance()

    def _get_all_observable_properties(self) -> list[TemplatePropertyDTO]:
        """Get all observable property DTOs (is_actuatable=False).

        Returns:
            List of TemplatePropertyDTO for all observable properties
        """
        observable_props = []
        for prop_enum in PropertyTemplate:
            try:
                template = self.adapter.get_template_by_name(prop_enum)
                property_dto = to_property_dto(template)

                if not property_dto.is_actuatable:
                    observable_props.append(property_dto)
            except Exception as e:
                logger.warning(f"Failed to process property {prop_enum.value}: {e}")
                continue

        logger.debug(f"Found {len(observable_props)} observable properties")
        return observable_props

    def _load_properties_for_device(self, device_enum: DeviceTemplate) -> list[Template]:
        """Load property templates for a device.

        Args:
            device_enum: Device template enum

        Returns:
            List of property Template objects for this device
        """
        device_dep_names = self.adapter.get_template_dependencies(device_enum)
        property_templates = []

        for prop_name in device_dep_names:
            if is_property_template(prop_name):
                prop_template = self.adapter.get_template_by_name(PropertyTemplate(prop_name))
                property_templates.append(prop_template)

        return property_templates

    def _load_devices_with_properties(
        self, dependency_names: list[str]
    ) -> dict[str, DeviceWithProperties]:
        """Load device templates with their property dependencies.

        Args:
            dependency_names: List of dependency template names from a system

        Returns:
            Dictionary mapping device name to (device_template, property_templates) tuple
        """
        device_templates_with_props: dict[str, DeviceWithProperties] = {}

        for dep_name in dependency_names:
            if is_device_template(dep_name):
                device_template = self.adapter.get_template_by_name(DeviceTemplate(dep_name))
                property_templates = self._load_properties_for_device(DeviceTemplate(dep_name))
                device_templates_with_props[dep_name] = (device_template, property_templates)

        return device_templates_with_props

    async def get_all_templates(self) -> TemplatesResponseDTO:
        """
        Get complete hierarchical ASHRAE 223P template structure.

        Controller acts as mediator: fetches from adapter → passes to mappers → returns DTOs.

        Returns:
            TemplatesResponseDTO with systems (nested devices/properties) and space types

        Raises:
            Exception: If BuildingMOTIF fails to load templates
        """
        logger.info("Building complete ASHRAE 223P template hierarchy")

        # Build hierarchical system structure
        systems = []
        for system_enum in SystemTemplate:
            try:
                system_template = self.adapter.get_template_by_name(system_enum)
                dependency_names = self.adapter.get_template_dependencies(system_enum)

                # Load devices with their properties using helper method
                device_templates_with_props = self._load_devices_with_properties(dependency_names)

                # Pass to mapper to build DTO
                system_dto = to_system_dto(system_template, device_templates_with_props)
                systems.append(system_dto)

                logger.debug(f"Built system: {system_enum.value} with {len(device_templates_with_props)} devices")

            except Exception as e:
                logger.error(f"Failed to process system {system_enum.value}: {e}")
                # Continue processing other systems instead of failing completely
                continue

        # Build space types (simplified - would need actual space type templates)
        # For now, return empty list as space types aren't in the NREL device/system templates
        space_types = []

        # Second pass: Populate sensor devices with all observable properties
        all_observable_properties = self._get_all_observable_properties()

        for system in systems:
            for device in system.devices:
                if device.device_type == DeviceType.SENSOR:
                    device.properties = all_observable_properties
                    logger.debug(
                        f"Enriched sensor '{device.id}' with {len(all_observable_properties)} observable properties"
                    )

        logger.info(f"Template hierarchy complete: {len(systems)} systems, {len(space_types)} space types")

        return TemplatesResponseDTO(
            systems=systems,
            space_types=space_types,
        )

    async def list_all_templates(self) -> list[str]:
        """
        List all available ASHRAE 223P templates.

        Returns:
            List of template names
        """
        logger.info("Listing all ASHRAE 223P templates")
        templates = self.adapter.list_templates()
        return templates

    async def get_template_info(self, template_name: TemplateType) -> dict[str, str | None]:
        """
        Get detailed information about a template.

        Args:
            template_name: Template from DeviceTemplate, SystemTemplate, or PropertyTemplate enum

        Returns:
            Template metadata dictionary with name and description

        Raises:
            KeyError: If template not found
        """
        logger.info(f"Getting template info: {template_name}")
        template = self.adapter.get_template_by_name(template_name)

        return {
            "name": str(template.name),
            "description": str(template.description)
            if template.description
            else None,
        }

    async def get_template_dependencies(self, template_name: TemplateType) -> list[str]:
        """
        Get list of dependency template names for a given template.

        Args:
            template_name: Template from DeviceTemplate, SystemTemplate, or PropertyTemplate enum

        Returns:
            List of dependency template names

        Raises:
            KeyError: If template not found
        """
        logger.info(f"Getting template dependencies: {template_name}")
        return self.adapter.get_template_dependencies(template_name)

    async def get_template_metadata(self, template_name: TemplateType) -> dict[str, Any]:
        """
        Get comprehensive metadata for a template including dependencies.

        Args:
            template_name: Template from DeviceTemplate, SystemTemplate, or PropertyTemplate enum

        Returns:
            Dictionary with template metadata (name, dependencies, triple_count)

        Raises:
            KeyError: If template not found
        """
        logger.info(f"Getting template metadata: {template_name}")
        return self.adapter.get_template_metadata(template_name)
