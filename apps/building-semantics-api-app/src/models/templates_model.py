"""Domain model for ASHRAE 223P template operations."""

from typing import TypeAlias

from buildingmotif.dataclasses import Template
from loguru import logger

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..adapters.template_types import DeviceTemplate, PropertyTemplate, SystemTemplate
from ..dto.templates_dto import DeviceType, SpaceTypeDTO, TemplatePropertyDTO, TemplatesResponseDTO
from ..mappers.template_mapper import (
    is_device_template,
    is_property_template,
    to_property_dto,
    to_system_dto,
)

DeviceWithProperties: TypeAlias = tuple[Template, list[Template]]


class TemplatesModel:
    """
    Domain model for template operations.

    Responsibilities:
    - Business logic for template hierarchy building
    - Property filtering and device loading
    - Template organization (systems → devices → properties)
    """

    def __init__(self, adapter: BuildingMOTIFAdapter) -> None:
        """
        Initialize templates model.

        Args:
            adapter: BuildingMOTIF adapter instance
        """
        self.adapter = adapter

    def get_all_templates(self) -> TemplatesResponseDTO:
        """
        Get complete hierarchical ASHRAE 223P template structure.

        Business logic:
        1. Load all system templates
        2. For each system, load devices with properties
        3. Build hierarchical structure
        4. Enrich sensors with observable properties

        Returns:
            TemplatesResponseDTO with systems and space types
        """
        logger.info("Building complete ASHRAE 223P template hierarchy")

        systems = []
        for system_enum in SystemTemplate:
            try:
                system_template = self.adapter.get_template_by_name(system_enum)
                dependency_names = self.adapter.get_template_dependencies(system_enum)

                device_templates_with_props = self._load_devices_with_properties(dependency_names)

                system_dto = to_system_dto(system_template, device_templates_with_props)
                systems.append(system_dto)

                logger.debug(f"Built system: {system_enum.value} with {len(device_templates_with_props)} devices")

            except Exception as e:
                logger.error(f"Failed to process system {system_enum.value}: {e}")
                continue

        space_types: list[SpaceTypeDTO] = []

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
            spaceTypes=space_types,
        )

    def _get_all_observable_properties(self) -> list[TemplatePropertyDTO]:
        """
        Get all observable property DTOs (is_actuatable=False).

        Business logic: Filter property templates that can be observed.

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
        """
        Load property templates for a device.

        Business logic: Get properties from device dependencies.

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
        """
        Load device templates with their property dependencies.

        Business logic: Build device hierarchy with nested properties.

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
