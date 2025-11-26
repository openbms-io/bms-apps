"""Controller for ASHRAE 223P device and property query operations."""

from loguru import logger

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..models.devices_model import DevicesModel


class DevicesController:
    """
    Business logic orchestration for ASHRAE 223P devices and properties.

    Delegates to model layer for business logic.
    """

    def __init__(self) -> None:
        """Initialize controller with devices model."""
        adapter = BuildingMOTIFAdapter.get_instance()
        self.model = DevicesModel(adapter)
        logger.debug("Devices controller initialized with model")

    async def get_devices_for_system(
        self, project_id: str, system_uri: str, bacnet_object_type: str | None = None
    ) -> list[dict[str, str]]:
        """
        Get all devices for a system instance.

        Args:
            project_id: Unique project identifier
            system_uri: System URI
            bacnet_object_type: Optional BACnet object type for device filtering

        Returns:
            List of device dicts with uri, label, template_id
        """
        return self.model.get_devices_for_system(project_id, system_uri, bacnet_object_type)

    async def get_properties_for_device(
        self,
        project_id: str,
        device_uri: str,
        bacnet_object_type: str | None = None,
    ) -> list[dict[str, str | bool | None]]:
        """
        Get all properties for a device.

        Optionally filters by BACnet object type compatibility.

        Args:
            project_id: Unique project identifier
            device_uri: Device URI
            bacnet_object_type: Optional BACnet object type for filtering

        Returns:
            List of property dicts with uri, label, template_id, is_actuatable
        """
        return self.model.get_properties_for_device(
            project_id, device_uri, bacnet_object_type
        )
