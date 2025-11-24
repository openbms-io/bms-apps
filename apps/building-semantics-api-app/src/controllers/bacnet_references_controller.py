"""Controller for BACnet reference operations."""

from loguru import logger

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..models.bacnet_references_model import BACnetReferencesModel
from ..models.exceptions import ValidationException


class BACnetReferencesController:
    """
    Business logic orchestration for BACnet references.

    Delegates to model layer for business logic.
    """

    def __init__(self) -> None:
        """Initialize controller with BACnet references model."""
        adapter = BuildingMOTIFAdapter.get_instance()
        self.model = BACnetReferencesModel(adapter)
        logger.debug("BACnet references controller initialized with model")

    async def create_or_update_reference(
        self,
        project_id: str,
        bacnet_point_id: str,
        property_uri: str,
    ) -> dict[str, str]:
        """
        Create or update BACnet point → property URN reference.

        Args:
            project_id: Unique project identifier
            bacnet_point_id: BACnet point identifier
            property_uri: Property URI from system instance

        Returns:
            Dictionary with bacnet_point_id and property_uri

        Raises:
            ValidationException: If SHACL validation fails
            ValueError: If property not found
            RuntimeError: If reference creation fails
        """
        if not self.model.validate_property_exists(project_id, property_uri):
            raise ValueError(f"Property not found in project: {property_uri}")

        # This may raise ValidationException - let it propagate to router
        return self.model.create_or_update_reference(
            project_id, bacnet_point_id, property_uri
        )

    async def get_reference(
        self, project_id: str, bacnet_point_id: str
    ) -> dict[str, str] | None:
        """
        Get BACnet reference with enriched data.

        Args:
            project_id: Unique project identifier
            bacnet_point_id: BACnet point identifier

        Returns:
            Enriched reference dict or None if not found
        """
        return self.model.get_reference(project_id, bacnet_point_id)

    async def get_all_references(self, project_id: str) -> list[dict[str, str]]:
        """
        Get all BACnet references for a project with enriched data.

        Args:
            project_id: Unique project identifier

        Returns:
            List of enriched reference dicts
        """
        return self.model.get_all_references(project_id)

    async def delete_reference(self, project_id: str, bacnet_point_id: str) -> bool:
        """
        Delete BACnet reference from RDF graph.

        Args:
            project_id: Unique project identifier
            bacnet_point_id: BACnet point identifier

        Returns:
            True if deleted, False if not found
        """
        result = self.model.delete_reference(project_id, bacnet_point_id)
        if result:
            logger.info(f"BACnet reference deleted: {bacnet_point_id}")
        return result
