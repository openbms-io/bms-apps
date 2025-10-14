"""Controller monitoring - handles single controller operations."""

import json
from typing import Optional, List, Dict
from bacpypes3.apdu import AbortPDU

from src.utils.logger import logger
from src.models.controller_points import (
    insert_controller_point,
    bulk_insert_controller_points,
)
from src.utils.bacnet_health_processor import BACnetHealthProcessor
from src.controllers.monitoring.error_collector import ErrorCollector
from src.models.bacnet_wrapper import BACnetWrapper
from src.models.controller_points import ControllerPointsModel
from src.models.bacnet_config import BacnetDeviceInfo

# TODO: We should get this from the config.
from src.config.config import DEFAULT_CONTROLLER_PORT


class ControllerMonitor:
    """Monitors all points for a single controller."""

    def __init__(self, controller: BacnetDeviceInfo, error_collector: ErrorCollector):
        """
        Initialize controller monitor.

        Args:
            controller: Controller configuration
            error_collector: Shared error collector
        """
        self.controller = controller
        self.error_collector = error_collector

    async def monitor_controller(self, wrapper: BACnetWrapper):
        """
        Monitor this controller - MOVED AS IS from monitor.py lines 224-423.

        Args:
            wrapper: BACnet wrapper to use for operations
        """
        # Build bulk read request for all points on this controller
        point_requests = []
        point_metadata = {}  # Store metadata for each point

        for each_object in self.controller.object_list:
            units = (
                getattr(each_object.properties, "units", None)
                if each_object.properties
                else None
            )

            # Get available properties based on configuration
            object_properties_dict = None
            if hasattr(each_object, "properties") and each_object.properties:
                # Convert properties object to dict if needed
                if hasattr(each_object.properties, "__dict__"):
                    object_properties_dict = each_object.properties.__dict__
                elif isinstance(each_object.properties, dict):
                    object_properties_dict = each_object.properties
                else:
                    logger.info(
                        f"Unknown properties type: {type(each_object.properties)}"
                    )

            # Only read properties that are available for this object
            properties_to_read = self.get_available_device_properties(
                object_properties_dict
            )
            logger.info(
                f"Reading device properties for {each_object.iot_device_point_id}, {each_object.type}, {each_object.point_id}: {properties_to_read}"
            )
            if len(properties_to_read) == 1 and properties_to_read[0] == "presentValue":
                logger.warning(
                    f"No additional device properties to read for {each_object.iot_device_point_id}, {each_object.type}, {each_object.point_id}"
                )

            # Add to bulk request
            point_requests.append(
                {
                    "object_type": each_object.type,
                    "object_id": each_object.point_id,
                    "properties": properties_to_read,
                }
            )

            # Store metadata for processing results later
            object_key = f"{each_object.type}:{each_object.point_id}"
            point_metadata[object_key] = {
                "iot_device_point_id": each_object.iot_device_point_id,
                "units": units,
                "object": each_object,
            }

        if not point_requests:
            logger.warning(
                f"No points to read for controller {self.controller.controller_ip_address}"
            )
            return

        try:
            # Execute bulk read for all points on this controller
            logger.info(
                f"Executing bulk read for {len(point_requests)} points on controller {self.controller.controller_ip_address}"
            )
            bulk_results = await wrapper.read_multiple_points(
                device_ip=self.controller.controller_ip_address,
                point_requests=point_requests,
            )

            # Collect all successful points for bulk insertion
            controller_points_to_insert = []
            fallback_points = []

            # Process results for each point
            for object_key, raw_properties in bulk_results.items():
                if object_key not in point_metadata:
                    logger.warning(f"Received result for unknown point: {object_key}")
                    continue

                metadata = point_metadata[object_key]
                each_object = metadata["object"]
                units = metadata["units"]

                try:
                    if raw_properties:  # Non-empty result
                        # Extract present value
                        present_value = raw_properties.get("presentValue")

                        logger.info(
                            f"Read value for {metadata['iot_device_point_id']} using wrapper {wrapper.instance_id}: {raw_properties}"
                        )

                        # Process health properties (including optional BACnet properties)
                        health_data = (
                            BACnetHealthProcessor.process_all_health_properties(
                                raw_properties
                            )
                        )
                        # Process optional BACnet properties
                        optional_properties = (
                            BACnetHealthProcessor.process_all_optional_properties(
                                raw_properties
                            )
                        )
                        # Merge health and optional properties
                        health_data.update(optional_properties)
                        logger.debug(f"Health data: {health_data}")

                        # Create controller point with health data for bulk insert
                        controller_point = self._create_controller_point_model(
                            iot_device_point_id=metadata["iot_device_point_id"],
                            controller_id=self.controller.controller_id,
                            point_id=each_object.point_id,
                            bacnet_object_type=each_object.type,
                            present_value=(
                                str(present_value)
                                if present_value is not None
                                else None
                            ),
                            controller_ip_address=self.controller.controller_ip_address,
                            controller_device_id=self.controller.device_id,
                            units=units,
                            all_properties_data=health_data,
                        )
                        controller_points_to_insert.append(controller_point)
                    else:
                        # Empty result - add to fallback list
                        logger.warning(
                            f"Empty bulk read result for {metadata['iot_device_point_id']}, will attempt individual fallback"
                        )
                        fallback_points.append((each_object, units))

                except Exception as e:
                    logger.debug(
                        f"Failed to process bulk read result for {metadata['iot_device_point_id']}: {e}"
                    )
                    # Add to fallback list
                    fallback_points.append((each_object, units))

            # Bulk insert all successful controller points
            if controller_points_to_insert:
                try:
                    logger.info(
                        f"Bulk inserting {len(controller_points_to_insert)} controller points for {self.controller.controller_ip_address}"
                    )
                    await bulk_insert_controller_points(controller_points_to_insert)
                    logger.info(
                        f"Successfully bulk inserted {len(controller_points_to_insert)} points for controller {self.controller.controller_ip_address}"
                    )
                except Exception as bulk_insert_error:
                    logger.error(
                        f"Bulk insert failed for controller {self.controller.controller_ip_address}: {bulk_insert_error}"
                    )
                    # Fallback to individual inserts for these points
                    for point in controller_points_to_insert:
                        try:
                            await insert_controller_point(point)
                        except Exception as individual_error:
                            logger.error(
                                f"Individual insert fallback also failed for point {point.iot_device_point_id}: {individual_error}"
                            )

            # Handle fallback individual reads for failed bulk read points
            for each_object, units in fallback_points:
                await self._fallback_individual_read(wrapper, each_object, units)

        except (Exception, AbortPDU) as e:
            logger.warning(
                f"Bulk read failed for controller {self.controller.controller_ip_address}: {e}"
            )
            logger.info(
                f"Falling back to individual reads for {len(point_requests)} points"
            )

            # Fallback to individual reads for all points on this controller
            # Note: Could potentially optimize this with bulk collection + bulk insert too,
            # but keeping individual for fallback simplicity since bulk read already failed
            for request in point_requests:
                object_key = f"{request['object_type']}:{request['object_id']}"
                if object_key in point_metadata:
                    metadata = point_metadata[object_key]
                    await self._fallback_individual_read(
                        wrapper, metadata["object"], metadata["units"]
                    )
            logger.info(
                f"Completed: Fallback individual reads for {len(point_requests)} points"
            )

    async def _fallback_individual_read(
        self, wrapper: BACnetWrapper, each_object: ControllerPointsModel, units: str
    ):
        """
        Fallback to individual point reading when bulk read fails.
        MOVED AS IS from monitor.py lines 432-538.

        Args:
            wrapper: BACnet wrapper to use for reading
            each_object: Point object to read
            units: Units for the point
        """

        try:
            # Get available properties based on configuration
            object_properties_dict = None
            if hasattr(each_object, "properties") and each_object.properties:
                # Convert properties object to dict if needed
                if hasattr(each_object.properties, "__dict__"):
                    object_properties_dict = each_object.properties.__dict__
                elif isinstance(each_object.properties, dict):
                    object_properties_dict = each_object.properties

            # Only read properties that are available for this object
            properties_to_read = self.get_available_device_properties(
                object_properties_dict
            )

            raw_properties = await wrapper.read_properties(
                device_ip=self.controller.controller_ip_address,
                object_type=each_object.type,
                object_id=each_object.point_id,
                properties=properties_to_read,
            )

            # Extract present value
            present_value = raw_properties.get("presentValue")

            logger.info(
                f"Individual fallback read value for {each_object.iot_device_point_id} using wrapper {wrapper.instance_id}: {raw_properties}"
            )

            # Process health properties (including optional BACnet properties)
            health_data = BACnetHealthProcessor.process_all_health_properties(
                raw_properties
            )
            # Process optional BACnet properties
            optional_properties = BACnetHealthProcessor.process_all_optional_properties(
                raw_properties
            )
            # Merge health and optional properties
            health_data.update(optional_properties)
            logger.debug(f"Health data: {health_data}")

            # Create controller point with health data
            controller_point = self._create_controller_point_model(
                iot_device_point_id=each_object.iot_device_point_id,
                controller_id=self.controller.controller_id,
                point_id=each_object.point_id,
                bacnet_object_type=each_object.type,
                present_value=(
                    str(present_value) if present_value is not None else None
                ),
                controller_ip_address=self.controller.controller_ip_address,
                controller_device_id=self.controller.device_id,
                units=units,
                all_properties_data=health_data,
            )
            await insert_controller_point(controller_point)

        except (Exception, AbortPDU) as e:
            logger.debug(
                f"Wrapper {wrapper.instance_id} failed to read properties for {each_object.iot_device_point_id}: {e}"
            )
            # Try fallback with present value only
            try:
                logger.info(
                    f"Attempting to wrapper.read_present_value for {each_object.iot_device_point_id} using wrapper {wrapper.instance_id}"
                )
                read_value = await wrapper.read_present_value(
                    self.controller.controller_ip_address,
                    each_object.type,
                    each_object.point_id,
                )
                logger.info(
                    f"Fallback read value from wrapper {wrapper.instance_id}: {read_value}"
                )
                # Create fallback controller point with error info
                error_info = json.dumps(
                    {
                        "error_class": "monitor.py",
                        "error_code": f"Failed to read properties with health properties. Falling back to present value only. Error: {e}",
                    }
                )
                controller_point = self._create_controller_point_model(
                    iot_device_point_id=each_object.iot_device_point_id,
                    controller_id=self.controller.controller_id,
                    point_id=each_object.point_id,
                    bacnet_object_type=each_object.type,
                    present_value=str(read_value),
                    controller_ip_address=self.controller.controller_ip_address,
                    controller_device_id=self.controller.device_id,
                    units=units,
                    all_properties_data=None,  # No properties data on fallback
                    error_info=error_info,
                )
                await insert_controller_point(controller_point)
            except (Exception, AbortPDU) as fallback_error:
                logger.error(
                    f"Wrapper {wrapper.instance_id} fallback also failed for {each_object.iot_device_point_id}: {fallback_error}"
                )
                # ONLY CHANGE: Collect error instead of raising
                self.error_collector.collect(
                    context="Point fallback read",
                    error=fallback_error,
                    controller_id=self.controller.controller_id,
                    point_id=each_object.iot_device_point_id,
                    controller_ip=self.controller.controller_ip_address,
                )

    def get_available_device_properties(
        self, object_properties: Optional[dict]
    ) -> List[str]:
        """Get list of available device properties based on stored configuration.
        Includes both health monitoring properties and device configuration properties.

        Args:
            object_properties: Dictionary of properties from BACnet configuration

        Returns:
            List of property names that are available for this object
        """

        # Always try to read presentValue as it's essential
        available = ["presentValue"]

        if not object_properties:
            # If no properties info, return minimal set
            logger.debug(
                "No properties configuration available, using minimal property set"
            )
            return available

        # Device properties to check (health monitoring + device configuration properties)
        monitorable_properties = [
            # Existing health properties
            "statusFlags",
            "eventState",
            "outOfService",
            "reliability",
            # Value limit properties
            "minPresValue",
            "maxPresValue",
            "highLimit",
            "lowLimit",
            "resolution",
            # Control properties
            "priorityArray",
            "relinquishDefault",
            # Notification configuration
            "covIncrement",
            "timeDelay",
            "timeDelayNormal",
            "notificationClass",
            "notifyType",
            "deadband",
            "limitEnable",
            # Event properties
            "eventEnable",
            "ackedTransitions",
            "eventTimeStamps",
            "eventMessageTexts",
            "eventMessageTextsConfig",
            # Algorithm control properties
            "eventDetectionEnable",
            "eventAlgorithmInhibitRef",
            "eventAlgorithmInhibit",
            "reliabilityEvaluationInhibit",
        ]

        # Only add properties that exist in the configuration
        for prop in monitorable_properties:
            if prop in object_properties:
                # Check if the property is not null (some objects have statusFlags: null)
                if object_properties[prop] is not None:
                    available.append(prop)
                else:
                    logger.debug(
                        f"Property {prop} exists but is null in configuration, skipping"
                    )
            else:
                logger.debug(f"Property {prop} not found in object configuration")

        logger.info(f"Available properties to read: {available}")
        return available

    def _create_controller_point_model(
        self,
        iot_device_point_id: str,
        controller_id: str,
        point_id: int,
        bacnet_object_type: str,
        present_value: Optional[str],
        controller_ip_address: str,
        controller_device_id: str,
        units: Optional[str],
        all_properties_data: Optional[Dict] = None,
        error_info: Optional[str] = None,
    ) -> ControllerPointsModel:
        """
        Helper method to create ControllerPointsModel with all optional properties.

        Args:
            iot_device_point_id: IOT device point identifier
            controller_id: Controller identifier
            point_id: Point identifier
            bacnet_object_type: BACnet object type
            present_value: Present value as string
            controller_ip_address: Controller IP address
            controller_device_id: Controller device ID
            units: Units for the point
            all_properties_data: Dictionary containing all health and optional properties
            error_info: Error information if fallback occurred

        Returns:
            ControllerPointsModel instance with all parameters set
        """
        # Use empty dict if no all_properties_data provided (fallback case)
        all_properties_data = all_properties_data or {}

        return ControllerPointsModel(
            iot_device_point_id=iot_device_point_id,
            controller_id=controller_id,
            point_id=point_id,
            bacnet_object_type=bacnet_object_type,
            present_value=present_value,
            controller_ip_address=controller_ip_address,
            controller_device_id=controller_device_id,
            controller_port=DEFAULT_CONTROLLER_PORT,
            units=units,
            is_uploaded=False,
            # Health properties
            status_flags=all_properties_data.get("status_flags"),
            event_state=all_properties_data.get("event_state"),
            out_of_service=all_properties_data.get("out_of_service"),
            reliability=all_properties_data.get("reliability"),
            error_info=error_info or all_properties_data.get("error_info"),
            # Value Limit Properties
            min_pres_value=all_properties_data.get("min_pres_value"),
            max_pres_value=all_properties_data.get("max_pres_value"),
            high_limit=all_properties_data.get("high_limit"),
            low_limit=all_properties_data.get("low_limit"),
            resolution=all_properties_data.get("resolution"),
            # Control Properties
            priority_array=all_properties_data.get("priority_array"),
            relinquish_default=all_properties_data.get("relinquish_default"),
            # Notification Configuration Properties
            cov_increment=all_properties_data.get("cov_increment"),
            time_delay=all_properties_data.get("time_delay"),
            time_delay_normal=all_properties_data.get("time_delay_normal"),
            notification_class=all_properties_data.get("notification_class"),
            notify_type=all_properties_data.get("notify_type"),
            deadband=all_properties_data.get("deadband"),
            limit_enable=all_properties_data.get("limit_enable"),
            # Event Properties
            event_enable=all_properties_data.get("event_enable"),
            acked_transitions=all_properties_data.get("acked_transitions"),
            event_time_stamps=all_properties_data.get("event_time_stamps"),
            event_message_texts=all_properties_data.get("event_message_texts"),
            event_message_texts_config=all_properties_data.get(
                "event_message_texts_config"
            ),
            # Algorithm Control Properties
            event_detection_enable=all_properties_data.get("event_detection_enable"),
            event_algorithm_inhibit_ref=all_properties_data.get(
                "event_algorithm_inhibit_ref"
            ),
            event_algorithm_inhibit=all_properties_data.get("event_algorithm_inhibit"),
            reliability_evaluation_inhibit=all_properties_data.get(
                "reliability_evaluation_inhibit"
            ),
        )
