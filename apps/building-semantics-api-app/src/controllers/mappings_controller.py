"""Controller for ASHRAE 223P mappings operations."""

from fastapi import HTTPException, status
from loguru import logger

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..dto.mappings_dto import MappingsResponseDTO, SaveMappingsRequestDTO
from ..models.mappings_model import MappingsModel
from ..models.exceptions import ValidationException


class MappingsController:
    """
    Business logic for ASHRAE 223P point-to-semantic mappings.

    Orchestrates between HTTP layer (router) and domain layer (model).
    """

    def __init__(self) -> None:
        """Initialize controller with mappings model."""
        adapter = BuildingMOTIFAdapter.get_instance()
        self.model = MappingsModel(adapter)
        logger.debug("Controller initialized with model")

    async def get_mappings(self, project_id: str) -> MappingsResponseDTO:
        """
        Get all mappings for project.

        Delegates to model layer for business logic.

        Args:
            project_id: Project identifier

        Returns:
            MappingsResponseDTO with all mappings keyed by point ID
        """
        try:
            # Delegate to model
            mappings = self.model.get_all_mappings(project_id)

            logger.info(f"Retrieved {len(mappings)} mappings for project: {project_id}")
            return MappingsResponseDTO(projectId=project_id, mappings=mappings)

        except Exception as e:
            logger.error(f"Failed to get mappings for project {project_id}: {e}")
            raise

    async def save_mappings(self, request: SaveMappingsRequestDTO) -> MappingsResponseDTO:
        """
        Save mappings with inline SHACL validation.

        Delegates to model layer for business logic.
        Converts domain exceptions to HTTP exceptions.

        Args:
            request: SaveMappingsRequestDTO with projectId and mappings

        Returns:
            MappingsResponseDTO with saved mappings

        Raises:
            HTTPException(400): If SHACL validation fails
            HTTPException(500): If persistence fails
        """
        try:
            project_id = request.project_id

            # Delegate to model (business logic)
            self.model.replace_all_mappings_validated(project_id, request.mappings)

            logger.info(f"Saved {len(request.mappings)} mappings for project: {project_id}")
            return await self.get_mappings(project_id)

        except ValidationException as e:
            # Convert domain exception to HTTP 400
            raise HTTPException(
                status_code=status.HTTP_400_BAD_REQUEST,
                detail={
                    "validationType": "SHACL",
                    "isValid": False,
                    "errors": e.errors,
                    "warnings": e.warnings,
                },
            )

        except Exception as e:
            # System errors → HTTP 500
            logger.error(f"Failed to save mappings for project {project_id}: {e}")
            raise HTTPException(
                status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                detail=f"Failed to save mappings: {str(e)}",
            ) from e
