"""Domain model for ASHRAE 223P device and property query operations."""

import re

from buildingmotif.dataclasses import Model
from loguru import logger

from ..adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from ..utils.label_utils import (
    extract_label_from_uri_or_none,
    get_label_or_extract,
)
from ..utils.property_semantics import determine_property_type, is_actuatable


class DevicesModel:
    """
    Domain model for device and property query operations.

    Responsibilities:
    - Query devices from system instances (read-only)
    - Query properties from devices (read-only)
    - Support BACnet object type filtering for properties
    - Traverse arbitrary depth hierarchies (no hardcoded assumptions)
    """

    def __init__(self, adapter: BuildingMOTIFAdapter) -> None:
        """
        Initialize devices model.

        Args:
            adapter: BuildingMOTIF adapter instance
        """
        self.adapter = adapter

    def _query_properties(
        self, model: Model, device_uri: str, relationship: str
    ) -> list[dict[str, str | bool | None]]:
        """
        Query properties using specified ASHRAE 223P relationship.

        Args:
            model: BuildingMOTIF model
            device_uri: Device or sensor URI
            relationship: Either "s223:hasProperty" or "s223:observes"

        Returns:
            List of property dicts
        """
        query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
        PREFIX bms: <urn:bms:>
        PREFIX s223: <http://data.ashrae.org/standard223#>
        PREFIX qudt: <http://qudt.org/schema/qudt/>

        SELECT DISTINCT ?property_uri ?label ?role
                        ?class_uri ?quantity_kind ?unit ?medium ?enumeration_kind
        WHERE {{
            <{device_uri}> {relationship} ?property_uri .

            OPTIONAL {{ ?property_uri rdfs:label ?label . }}
            OPTIONAL {{ ?property_uri s223:hasRole ?role . }}
            OPTIONAL {{ ?property_uri rdf:type ?class_uri . }}
            OPTIONAL {{ ?property_uri qudt:hasQuantityKind ?quantity_kind . }}
            OPTIONAL {{ ?property_uri qudt:hasUnit ?unit . }}
            OPTIONAL {{ ?property_uri s223:ofMedium ?medium . }}
            OPTIONAL {{ ?property_uri s223:hasEnumerationKind ?enumeration_kind . }}
        }}
        ORDER BY ?property_uri
        """

        results = self.adapter.query_model(model, query)
        logger.debug(f"Found {len(results)} properties via {relationship}")

        return self._build_property_list(results)

    def _build_property_list(
        self, results: list[dict[str, str | None]]
    ) -> list[dict[str, str | bool | None]]:
        """
        Build property list from SPARQL query results.

        Extracts labels, handles None/null values, adds metadata.
        """
        properties: list[dict[str, str | bool | None]] = []

        for result in results:
            property_uri = result["property_uri"]
            label_value = result.get("label")
            role_value = result.get("role")

            assert isinstance(property_uri, str)

            final_label = get_label_or_extract(label_value, property_uri)

            is_actuatable_result = is_actuatable(
                result.get("class_uri"),
                role_value
            )

            properties.append({
                "property_uri": property_uri,
                "label": final_label,
                "is_actuatable": is_actuatable_result,
                "class_uri": result.get("class_uri"),
                "property_type": determine_property_type(result.get("class_uri")),
                "quantity_kind": extract_label_from_uri_or_none(result.get("quantity_kind")),
                "unit": extract_label_from_uri_or_none(result.get("unit")),
                "medium": extract_label_from_uri_or_none(result.get("medium")),
                "enumeration_kind": extract_label_from_uri_or_none(result.get("enumeration_kind")),
            })

        return properties

    def get_devices_for_system(
        self, project_id: str, system_uri: str, bacnet_object_type: str | None = None
    ) -> list[dict[str, str]]:
        """
        Get all devices for a system instance.

        Queries RDF graph for devices connected to system.
        Supports arbitrary depth hierarchies (Equipment → Equipment → Device).
        Optionally filters by BACnet object type compatibility.

        Args:
            project_id: Unique project identifier
            system_uri: System URI
            bacnet_object_type: Optional BACnet object type for device filtering

        Returns:
            List of device dicts with uri and label
        """
        logger.debug(f"Querying devices for system: {system_uri}, bacnet_type={bacnet_object_type}")

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            query = f"""
            PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
            PREFIX bms: <urn:bms:>
            PREFIX s223: <http://data.ashrae.org/standard223#>

            SELECT DISTINCT ?device_uri ?label
            WHERE {{
                <{system_uri}> s223:contains* ?device_uri .
                OPTIONAL {{ ?device_uri rdfs:label ?label . }}

                FILTER (str(?device_uri) != "{system_uri}")
            }}
            ORDER BY ?device_uri
            """

            results = self.adapter.query_model(model, query)

            devices = []
            for result in results:
                device_uri = result["device_uri"]
                label_value = result.get("label")

                assert isinstance(device_uri, str)

                final_label = get_label_or_extract(label_value, device_uri)

                devices.append({
                    "device_uri": device_uri,
                    "label": final_label,
                })

            if bacnet_object_type:
                devices = self._filter_devices_by_bacnet_type(
                    model, devices, bacnet_object_type
                )

            logger.info(f"Found {len(devices)} devices for system {system_uri}")
            return devices

        except Exception as e:
            logger.error(f"Failed to query devices: {e}")
            raise RuntimeError(f"Device query failed: {e}") from e

    def get_properties_for_device(
        self,
        project_id: str,
        device_uri: str,
        bacnet_object_type: str | None = None,
    ) -> list[dict[str, str | bool | None]]:
        """
        Get all properties for a device with ASHRAE 223P metadata.

        Supports both regular devices and sensors:
        - Regular devices (Damper, Pump, Fan): use s223:hasProperty
        - Sensors (Pressure-Sensor, Temp-Sensor): use s223:observes

        BACnet object type filtering (from Story 2-12):
        - analog-input, binary-input → Observable only (is_actuatable: false)
        - analog-output, binary-output → Actuatable only (is_actuatable: true)
        - analog-value, binary-value → Both (no filter)

        Args:
            project_id: Unique project identifier
            device_uri: Device or sensor URI
            bacnet_object_type: Optional BACnet object type for filtering

        Returns:
            List of property dicts with uri, label, is_actuatable,
            and metadata (class_uri, property_type, quantity_kind, unit, medium, enumeration_kind)
        """
        logger.debug(
            f"Querying properties for device: {device_uri}, bacnet_type={bacnet_object_type}"
        )

        try:
            model = self.adapter.get_or_create_model(f"urn:project:{project_id}")

            # Query both ASHRAE 223P relationships:
            # - s223:hasProperty for devices (Damper, Pump, Fan)
            # - s223:observes for sensors (Pressure-Sensor, Temp-Sensor)
            device_props = self._query_properties(model, device_uri, "s223:hasProperty")
            sensor_props = self._query_properties(model, device_uri, "s223:observes")

            all_properties = device_props + sensor_props

            if bacnet_object_type:
                all_properties = self._filter_device_properties_by_bacnet_type(
                    all_properties, bacnet_object_type
                )

            logger.info(
                f"Found {len(all_properties)} properties for device {device_uri}"
            )
            return all_properties

        except Exception as e:
            logger.error(f"Failed to query properties: {e}")
            raise RuntimeError(f"Property query failed: {e}") from e

    def _filter_device_properties_by_bacnet_type(
        self, properties: list[dict[str, str | bool | None]], bacnet_object_type: str
    ) -> list[dict[str, str | bool | None]]:
        """Filter device properties by BACnet object type compatibility."""
        filtered = [
            p for p in properties
            if self._is_compatible_with_bacnet_type(bacnet_object_type, bool(p["is_actuatable"]))
        ]
        logger.debug(f"Filtered properties: {len(filtered)}/{len(properties)} for {bacnet_object_type}")
        return filtered

    def _filter_devices_by_bacnet_type(
        self, model: Model, devices: list[dict[str, str]], bacnet_object_type: str
    ) -> list[dict[str, str]]:
        """Filter devices by checking if they have BACnet-compatible properties."""
        filtered_devices = []

        for device in devices:
            device_props = self._query_properties(model, device["device_uri"], "s223:hasProperty")
            sensor_props = self._query_properties(model, device["device_uri"], "s223:observes")

            has_compatible = any(
                self._is_compatible_with_bacnet_type(bacnet_object_type, bool(p["is_actuatable"]))
                for p in device_props + sensor_props
            )

            if has_compatible:
                filtered_devices.append(device)

        logger.debug(f"Filtered devices: {len(filtered_devices)}/{len(devices)} for {bacnet_object_type}")
        return filtered_devices

    def _is_compatible_with_bacnet_type(
        self, bacnet_object_type: str, is_actuatable: bool
    ) -> bool:
        """
        Check if property/device actuation matches BACnet object type.

        Args:
            bacnet_object_type: BACnet object type
            is_actuatable: Whether property is actuatable

        Returns:
            True if compatible, False otherwise
        """
        bacnet_type_lower = bacnet_object_type.lower()

        if bacnet_type_lower in ["analog-value", "binary-value"]:
            return True

        if bacnet_type_lower in ["analog-output", "binary-output"]:
            return is_actuatable

        if bacnet_type_lower in ["analog-input", "binary-input"]:
            return not is_actuatable

        logger.warning(f"Unknown BACnet object type: {bacnet_object_type}")
        return True
