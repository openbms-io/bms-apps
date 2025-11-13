"""Controller for ASHRAE 223P templates operations."""
from typing import Any

from loguru import logger

from ..adapters import BuildingMOTIFAdapter, TemplateType


class TemplatesController:
    """Business logic for ASHRAE 223P templates operations."""

    def __init__(self) -> None:
        """Initialize controller with singleton BuildingMOTIF adapter."""
        self.adapter = BuildingMOTIFAdapter.get_instance()

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
