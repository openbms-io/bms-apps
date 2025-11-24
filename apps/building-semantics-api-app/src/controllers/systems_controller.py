"""Controller for ASHRAE 223P system instance operations."""

from loguru import logger

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..models.systems_model import SystemsModel


class SystemsController:
    """
    Business logic orchestration for ASHRAE 223P system instances.

    Delegates to model layer for business logic.
    """

    def __init__(self) -> None:
        """Initialize controller with systems model."""
        adapter = BuildingMOTIFAdapter.get_instance()
        self.model = SystemsModel(adapter)
        logger.debug("Systems controller initialized with model")

    async def create_system(
        self, project_id: str, template_id: str, label: str
    ) -> dict[str, str]:
        """
        Create reusable system instance from ASHRAE 223P template.

        Args:
            project_id: Unique project identifier
            template_id: System template enum value (e.g., "vav-reheat")
            label: User-provided custom label (e.g., "VAV-Floor3-Zone5")

        Returns:
            Dictionary with system_uri, label, template_id, created timestamp

        Raises:
            KeyError: If template not found
            RuntimeError: If system creation fails
        """
        try:
            result = self.model.create_system(project_id, template_id, label)
            logger.info(
                f"System created: {result['system_uri']} (label={label})"
            )
            return result

        except Exception as e:
            logger.error(f"Failed to create system: {e}")
            raise

    async def get_system(
        self, project_id: str, system_uri: str
    ) -> dict[str, str] | None:
        """
        Get system instance details from RDF graph.

        Args:
            project_id: Unique project identifier
            system_uri: System URI

        Returns:
            System metadata dict or None if not found
        """
        return self.model.get_system(project_id, system_uri)

    async def list_systems(self, project_id: str) -> list[dict[str, str]]:
        """
        List all system instances in project.

        Args:
            project_id: Unique project identifier

        Returns:
            List of system metadata dicts
        """
        return self.model.list_systems(project_id)

    async def delete_system(self, project_id: str, system_uri: str) -> bool:
        """
        Delete system instance from RDF graph.

        Args:
            project_id: Unique project identifier
            system_uri: System URI to delete

        Returns:
            True if deleted, False if not found
        """
        result = self.model.delete_system(project_id, system_uri)
        if result:
            logger.info(f"System deleted: {system_uri}")
        return result
