"""Controller for ASHRAE 223P spaces operations."""
from loguru import logger

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..dto.spaces_dto import CreateSpaceRequestDTO, SpaceInstanceDTO


class SpacesController:
    """Business logic for ASHRAE 223P space instances."""

    def __init__(self) -> None:
        """Initialize controller with singleton BuildingMOTIF adapter."""
        self.adapter = BuildingMOTIFAdapter.get_instance()

    async def list_spaces(self, project_id: str) -> list[SpaceInstanceDTO]:
        """
        List all spaces for a project.

        Args:
            project_id: Project identifier

        Returns:
            List of space instances
        """
        logger.info(f"Listing spaces for project: {project_id}")
        return []

    async def create_space(
        self, project_id: str, space_data: CreateSpaceRequestDTO
    ) -> SpaceInstanceDTO:
        """
        Create a new space instance.

        Args:
            project_id: Project identifier
            space_data: Space creation data (type, label, etc.)

        Returns:
            Created space instance
        """
        logger.info(f"Creating space for project: {project_id}")
        raise NotImplementedError("Space creation not yet implemented")
