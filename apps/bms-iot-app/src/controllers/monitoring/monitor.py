"""BACnet monitoring module using bacpypes."""

import uuid
from typing import Dict, List, Optional, Any
from src.models.bacnet_types import (
    convert_point_type_to_bacnet_object_type,
    get_point_types,
)
from src.utils.utils import extract_property_dict_camel

# import BAC0
from src.models.bacnet_wrapper_manager import (
    bacnet_wrapper_manager,
)
from src.actors.messages.message_type import BacnetReaderConfig

# from src.simulator.bacnet_simulator_config import READ_CONFIG
from src.models.bacnet_config import BacnetDeviceInfo, insert_bacnet_config_json
from src.models.bacnet_config import get_latest_bacnet_config_json_as_list
from src.utils.logger import logger
from src.utils.performance import performance_metrics
from src.models.bacnet_wrapper import BACnetWrapper


class BACnetMonitor:
    def __init__(self):
        """Initialize the BACnet monitor."""
        pass

    async def initialize(self) -> None:
        """Initialize the BACnet monitor (compatibility method for actor)."""
        # No-op since initialization now happens in initialize_bacnet_readers()
        # This method exists for backward compatibility with bacnet_monitoring_actor.py
        pass

    async def initialize_bacnet_readers(
        self, reader_configs: List[BacnetReaderConfig]
    ) -> None:
        """Initialize BACnet wrapper manager with reader configurations."""
        logger.info(f"Initializing {len(reader_configs)} BACnet readers")

        # Simple call - wrapper manager handles all internal cleanup automatically
        await bacnet_wrapper_manager.initialize_readers(reader_configs)

        # Get actual count of successfully initialized readers
        actual_initialized_count = len(bacnet_wrapper_manager.get_all_wrappers())
        logger.info(
            f"Successfully initialized BACnet wrapper manager with {actual_initialized_count} active readers"
        )

    # IS THIS METHOD NEEDED?
    async def discover_devices(self, device_address_list: List[str]):
        """Discover BACnet devices on the network using all available wrappers."""
        devices: List[Dict] = []

        # Get all available wrappers
        all_wrappers = bacnet_wrapper_manager.get_all_wrappers()

        for wrapper_id, wrapper in all_wrappers.items():
            logger.info(f"Discovering devices using wrapper {wrapper.instance_id}")
            for address in device_address_list:
                try:
                    who_is_devices = await wrapper.who_is(address=address)
                    logger.info(
                        f"Wrapper {wrapper.instance_id} found devices at {address}: {who_is_devices}"
                    )
                    for device in who_is_devices:
                        device_instance, device_id = device.iAmDeviceIdentifier
                        device_info = {
                            "iam_device_identifier": device.iAmDeviceIdentifier,
                            "vendor_id": device.vendorID,
                            "device_id": device_id,
                            "address": device.pduSource,
                            "discovered_by_reader": wrapper.instance_id,  # Track which wrapper found this device
                        }
                        devices.append(device_info)
                except Exception as e:
                    logger.error(
                        f"Wrapper {wrapper.instance_id} failed to discover devices at {address}: {e}"
                    )
                    continue

        logger.info(f"Total devices discovered: {len(devices)}")
        return devices

    def display_device_info(self, device_id: int):
        """Display information about a specific device."""
        pass

    async def get_object_list(self, controller_ip_address: str, device_id: int):
        """Get a list of objects for a specific device."""
        # Get wrapper for this operation
        wrapper = await bacnet_wrapper_manager.get_wrapper_for_operation()
        if not wrapper:
            raise RuntimeError("No BACnet wrapper available for operation")

        object_list = await wrapper.read_object_list(controller_ip_address, device_id)
        logger.info(f"Object list: {object_list}")

        return object_list

    def display_object_info(self, device_id: int, object_type: str, object_id: int):
        """Display information about a specific object."""
        pass

    async def monitor_objects(self, device_id: int, interval: int):
        """Monitor all objects of a specific device."""
        pass

    @performance_metrics("monitor_all_devices")
    async def monitor_all_devices(self):
        """Monitor all devices and their objects on the network using available wrappers."""
        from src.controllers.monitoring.error_collector import ErrorCollector
        from src.controllers.monitoring.controller_monitor import ControllerMonitor

        logger.info("STARTED: Monitoring all devices")

        # Initialize error collector
        error_collector = ErrorCollector()

        # Get controllers from the database
        controllers = await get_latest_bacnet_config_json_as_list()
        if not controllers:
            logger.warning("No controllers found in the database")
            return

        # Log available wrappers
        all_wrappers = bacnet_wrapper_manager.get_all_wrappers()
        logger.info(f"Starting monitoring with {len(all_wrappers)} available wrappers")

        # Log wrapper utilization before starting
        if all_wrappers:
            utilization_info = await bacnet_wrapper_manager.get_utilization_info()
            logger.info(f"Wrapper utilization before monitoring: {utilization_info}")

        for controller in controllers:
            # Get wrapper for this controller's bulk operation
            wrapper = await bacnet_wrapper_manager.get_wrapper_for_operation()
            if not wrapper:
                logger.error(
                    f"No wrapper available for controller {controller.controller_ip_address}"
                )
                error_collector.collect(
                    context="Wrapper availability",
                    error=Exception("No wrapper available"),
                    controller_id=controller.controller_id,
                    controller_ip=controller.controller_ip_address,
                )
                continue

            # Create ControllerMonitor and monitor this controller
            controller_monitor = ControllerMonitor(controller, error_collector)
            await controller_monitor.monitor_controller(wrapper)

        # Log wrapper utilization after monitoring
        if all_wrappers:
            utilization_info = await bacnet_wrapper_manager.get_utilization_info()
            logger.info(f"Wrapper utilization after monitoring: {utilization_info}")

        logger.info("FINISHED: Monitoring all devices")

        # Raise if any errors were collected during monitoring
        error_collector.raise_if_errors()

    async def stop_monitor(self):
        """Stop the BAC0 application"""
        # The original stop logic would go here
        logger.info("Stopping BAC0 core (if running)...")

    def is_point_type(self, obj_data):
        point_type = get_point_types()
        obj_type, point_id = obj_data

        # We check what type of object it is and if it is a point type we return true.
        # Its from bacpypes.object and not clear what messages we can send to it.
        if obj_type.asn1 in point_type:
            return True
        return False

    async def fetch_from_bacnet_network_and_save_config(
        self, iotDeviceControllers: List[dict]
    ):
        """Fetch and save a configuration from the BACnet network into the database."""
        logger.info(
            f"Fetching and saving config for iotDeviceControllers: {iotDeviceControllers}"
        )
        bacnet_device_infos = await self.fetch_config(iotDeviceControllers)
        logger.info(f"Bacnet device infos: {len(bacnet_device_infos)}")

        # Validate that we discovered at least one controller
        if len(bacnet_device_infos) == 0:
            raise Exception(
                f"Failed to discover any controllers from {len(iotDeviceControllers)} configured controller(s). "
                "Check BACnet network connectivity and controller configuration."
            )

        await insert_bacnet_config_json(bacnet_device_infos)
        logger.info("Bacnet device infos saved to database")

    async def fetch_config(self, iotDeviceControllers: List[dict]):
        devices: List[Dict] = []

        # Get all available wrappers
        all_wrappers = bacnet_wrapper_manager.get_all_wrappers()

        for iotDeviceController in iotDeviceControllers:
            controller_ip_address = iotDeviceController["ipAddress"]
            controller_device_id = iotDeviceController["controllerDeviceId"]
            controller_id = iotDeviceController["id"]
            logger.info(
                f"Fetching config for controller: {controller_ip_address} {controller_device_id} {controller_id}"
            )

            # Try each wrapper until one succeeds or all fail
            device_found = False
            for wrapper_id, wrapper in all_wrappers.items():
                try:
                    logger.info(
                        f"Trying to discover controller {controller_ip_address} using wrapper {wrapper.instance_id}"
                    )
                    who_is_devices = await wrapper.who_is(controller_ip_address)

                    if not who_is_devices:
                        logger.info(
                            f"No devices found at {controller_ip_address} using wrapper {wrapper.instance_id}"
                        )
                        continue

                    for device in who_is_devices:
                        device_instance, device_id = device.iAmDeviceIdentifier
                        object_list = await wrapper.read_object_list(
                            ip=controller_ip_address, device_id=device_id
                        )
                        logger.info(
                            f"controller_ip_address: {controller_ip_address}, device_id: {device_id}, Object list: {object_list}"
                        )

                        filtered_object_list = object_list
                        filtered_object_list = [
                            obj for obj in object_list if self.is_point_type(obj)
                        ]
                        filtered_object_list_mapped = await self._map_and_enrich_object_list(
                            controller_id=controller_id,
                            controller_ip_address=controller_ip_address,
                            filtered_object_list=filtered_object_list,
                            wrapper=wrapper,  # Pass the wrapper for property reading
                        )

                        device_info = {
                            "vendor_id": device.vendorID,
                            "device_id": device_id,
                            "controller_ip_address": controller_ip_address,
                            "controller_device_id": device_id,  # This is redundant, adding it for clarity due to too many ids.
                            "controller_id": controller_id,
                            "object_list": filtered_object_list_mapped,
                            "configured_by_reader": wrapper.instance_id,  # Track which wrapper was used
                        }

                        devices.append(device_info)
                        device_found = True
                        logger.info(
                            f"Successfully configured controller {controller_ip_address} using wrapper {wrapper.instance_id}"
                        )
                        break  # Found device, no need to try other wrappers

                    if device_found:
                        break  # Successfully found device with this wrapper

                except Exception as e:
                    logger.error(
                        f"Wrapper {wrapper.instance_id} failed to fetch config for controller {controller_ip_address}: {e}"
                    )
                    continue

            if not device_found:
                logger.error(
                    f"Failed to configure controller {controller_ip_address} with any available wrapper"
                )

        logger.info(f"Devices: {len(devices)}")
        bacnet_device_infos = [BacnetDeviceInfo(**device) for device in devices]
        logger.info(f"Bacnet device infos: {len(bacnet_device_infos)}")
        return bacnet_device_infos

    async def _map_and_enrich_object_list(
        self,
        controller_id: str,
        controller_ip_address: str,
        filtered_object_list,
        wrapper: Optional[BACnetWrapper] = None,
    ):
        filtered_object_list_mapped: List[Dict[str, Any]] = [
            {
                "type": (
                    lambda bacnet_type: (
                        bacnet_type.value if bacnet_type is not None else None
                    )
                )(convert_point_type_to_bacnet_object_type(obj_type.asn1)),
                "point_id": point_id,
                # Deterministically generate a uuid for the iot device point
                # using the controller_id and point_id
                "iot_device_point_id": str(
                    uuid.uuid5(uuid.NAMESPACE_URL, f"{controller_id}-{point_id}")
                ),
            }
            for obj_type, point_id in filtered_object_list
        ]

        # Wrapper must be provided - fail fast if not
        if wrapper is None:
            raise ValueError(
                "Wrapper is required for mapping and enriching object list"
            )
        wrapper_to_use = wrapper

        for obj in filtered_object_list_mapped:
            object_type = obj["type"]
            point_id = obj["point_id"]
            logger.info(
                f"Reading properties for object_type: {object_type}, point_id: {point_id}"
            )

            # Skip if type or point_id is None
            if object_type is None or point_id is None:
                obj["properties"] = {}
                logger.warning(
                    "Missing object_type or point_id, skipping property read"
                )
                continue

            # Ensure object_type is string and point_id is int
            if not isinstance(object_type, str) or not isinstance(point_id, int):
                obj["properties"] = {}
                logger.warning(
                    f"Invalid object_type: {object_type} or point_id: {point_id} format, skipping property read"
                )
                continue

            try:
                properties = await wrapper_to_use.read_all_properties(
                    device_ip=controller_ip_address,
                    object_type=object_type,
                    object_id=point_id,
                )

                # NOTE: We cannot use BacnetHealthProcessor, since the object_list keys are used by
                # src/controllers/monitoring/controller_monitor.py
                # These keys are utilized for querying the controller points properties.
                # We will for now map the optional properties structure in the DTO layer.
                properties_dict = extract_property_dict_camel(properties)
                obj["properties"] = properties_dict

            except Exception as e:
                logger.error(
                    f"Failed to get properties for {object_type} {point_id}: {e}"
                )
                obj["properties"] = {}  # Set empty properties on failure

        return filtered_object_list_mapped
