"""
Test MQTT Serialization with BACnet Optional Properties.

This test suite validates the Phase 3 enhancements to the _serialize_point
function that added support for parsing JSON properties and structured
MQTT payload transmission.
"""

import json
from datetime import datetime, timezone
from unittest.mock import patch
from src.network.mqtt_command_dispatcher import _serialize_point
from src.models.controller_points import ControllerPointsModel


class TestMQTTSerializationOptionalProperties:
    """Test MQTT serialization with optional BACnet properties."""

    def test_serialize_point_with_basic_properties_only(self):
        """Test: Serialization with only basic required properties."""
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            present_value="22.5",
            units="degreesCelsius",
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        assert serialized["controllerIpAddress"] == "192.168.1.100"
        assert serialized["presentValue"] == "22.5"
        assert serialized["units"] == "degreesCelsius"

        # Optional properties should be None
        assert serialized["highLimit"] is None
        assert serialized["priorityArray"] is None
        assert serialized["eventEnable"] is None

    def test_serialize_point_with_status_flags_parsing(self):
        """Test: Status flags JSON array string to array conversion."""
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            status_flags="[0, 1, 1, 1]",  # BACnet StatusFlags: [IN_ALARM, FAULT, OVERRIDDEN, OUT_OF_SERVICE]
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Should parse JSON string to integer array
        assert serialized["statusFlags"] == [0, 1, 1, 1]

    def test_serialize_point_with_empty_status_flags(self):
        """Test: Empty or None status flags handling."""
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            status_flags=None,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)
        assert serialized["statusFlags"] is None

    def test_serialize_point_with_priority_array_json(self):
        """Test: Priority array JSON string parsing to structured data."""
        priority_array_json = json.dumps(
            [
                None,
                None,
                25.0,
                None,
                None,
                None,
                None,
                None,
                50.0,
                None,
                None,
                None,
                None,
                None,
                None,
                20.0,
            ]
        )

        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            priority_array=priority_array_json,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Should parse JSON string to structured data
        assert isinstance(serialized["priorityArray"], list)
        assert len(serialized["priorityArray"]) == 16
        assert serialized["priorityArray"][2] == 25.0
        assert serialized["priorityArray"][8] == 50.0
        assert serialized["priorityArray"][15] == 20.0
        assert serialized["priorityArray"][0] is None

    def test_serialize_point_with_limit_enable_json(self):
        """Test: Limit enable JSON string parsing to structured data."""
        limit_enable_json = json.dumps(
            {"lowLimitEnable": True, "highLimitEnable": False}
        )

        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            limit_enable=limit_enable_json,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Should parse JSON string to structured object
        assert isinstance(serialized["limitEnable"], dict)
        assert serialized["limitEnable"]["lowLimitEnable"] is True
        assert serialized["limitEnable"]["highLimitEnable"] is False

    def test_serialize_point_with_event_enable_json(self):
        """Test: Event enable JSON string parsing to structured data."""
        event_enable_json = json.dumps(
            {"toFault": True, "toNormal": True, "toOffnormal": False}
        )

        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            event_enable=event_enable_json,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Should parse JSON string to structured object
        assert isinstance(serialized["eventEnable"], dict)
        assert serialized["eventEnable"]["toFault"] is True
        assert serialized["eventEnable"]["toNormal"] is True
        assert serialized["eventEnable"]["toOffnormal"] is False

    def test_serialize_point_with_event_timestamps_json(self):
        """Test: Event timestamps JSON array parsing."""
        timestamps_json = json.dumps(
            ["2024-01-01T10:00:00Z", None, "2024-01-01T12:00:00Z"]
        )

        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            event_time_stamps=timestamps_json,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Should parse JSON string to array
        assert isinstance(serialized["eventTimeStamps"], list)
        assert len(serialized["eventTimeStamps"]) == 3
        assert serialized["eventTimeStamps"][0] == "2024-01-01T10:00:00Z"
        assert serialized["eventTimeStamps"][1] is None
        assert serialized["eventTimeStamps"][2] == "2024-01-01T12:00:00Z"

    def test_serialize_point_with_event_messages_json(self):
        """Test: Event message texts JSON array parsing."""
        messages_json = json.dumps(
            ["High alarm condition", "Normal operation", "Warning threshold"]
        )

        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            event_message_texts=messages_json,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Should parse JSON string to array
        assert isinstance(serialized["eventMessageTexts"], list)
        assert len(serialized["eventMessageTexts"]) == 3
        assert serialized["eventMessageTexts"][0] == "High alarm condition"
        assert serialized["eventMessageTexts"][1] == "Normal operation"
        assert serialized["eventMessageTexts"][2] == "Warning threshold"

    def test_serialize_point_with_object_property_reference_json(self):
        """Test: Object property reference JSON parsing."""
        ref_json = json.dumps(
            {
                "objectIdentifier": "analogInput:1",
                "propertyIdentifier": "presentValue",
                "arrayIndex": None,
            }
        )

        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            event_algorithm_inhibit_ref=ref_json,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Should parse JSON string to structured object
        assert isinstance(serialized["eventAlgorithmInhibitRef"], dict)
        assert (
            serialized["eventAlgorithmInhibitRef"]["objectIdentifier"]
            == "analogInput:1"
        )
        assert (
            serialized["eventAlgorithmInhibitRef"]["propertyIdentifier"]
            == "presentValue"
        )
        assert serialized["eventAlgorithmInhibitRef"]["arrayIndex"] is None

    def test_serialize_point_with_all_json_properties(self):
        """Test: Serialization with all JSON properties populated."""
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            priority_array=json.dumps([None] * 16),
            limit_enable=json.dumps({"lowLimitEnable": True, "highLimitEnable": True}),
            event_enable=json.dumps(
                {"toFault": True, "toNormal": True, "toOffnormal": True}
            ),
            acked_transitions=json.dumps(
                {"toFault": False, "toNormal": True, "toOffnormal": False}
            ),
            event_time_stamps=json.dumps([None, None, None]),
            event_message_texts=json.dumps(["", "", ""]),
            event_message_texts_config=json.dumps(["", "", ""]),
            event_algorithm_inhibit_ref=json.dumps(
                {"objectIdentifier": "test", "propertyIdentifier": "test"}
            ),
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # All JSON properties should be parsed to structured data
        assert isinstance(serialized["priorityArray"], list)
        assert isinstance(serialized["limitEnable"], dict)
        assert isinstance(serialized["eventEnable"], dict)
        assert isinstance(serialized["ackedTransitions"], dict)
        assert isinstance(serialized["eventTimeStamps"], list)
        assert isinstance(serialized["eventMessageTexts"], list)
        assert isinstance(serialized["eventMessageTextsConfig"], list)
        assert isinstance(serialized["eventAlgorithmInhibitRef"], dict)

    def test_serialize_point_with_invalid_json_properties(self):
        """Test: Graceful handling of invalid JSON in properties."""
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            priority_array="invalid json {{{",
            limit_enable="not json at all",
            event_enable=None,  # None should be handled gracefully
            created_at_unix_milli_timestamp=1704103200000,
        )

        with patch("src.utils.logger.logger.warning") as mock_warning:
            serialized = _serialize_point(point)

            # Should log warnings for invalid JSON
            assert mock_warning.call_count >= 2  # At least 2 invalid JSON strings

            # Invalid JSON should result in None values
            assert serialized["priorityArray"] is None
            assert serialized["limitEnable"] is None
            assert serialized["eventEnable"] is None

    def test_serialize_point_with_datetime_fields(self):
        """Test: Datetime fields are properly converted to ISO format."""
        now = datetime.now(timezone.utc)
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            created_at=now,
            updated_at=now,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Datetime fields should be ISO formatted strings
        assert isinstance(serialized["createdAt"], str)
        assert isinstance(serialized["updatedAt"], str)
        assert "T" in serialized["createdAt"]  # ISO format marker
        assert "T" in serialized["updatedAt"]  # ISO format marker

    def test_serialize_point_unix_timestamp_included(self):
        """Test: Unix millisecond timestamp is included in serialized data."""
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # Unix timestamp should be included for InfluxDB
        assert "createdAtUnixMilliTimestamp" in serialized
        # The computed field should now have the value we explicitly set
        timestamp_value = serialized["createdAtUnixMilliTimestamp"]
        assert timestamp_value == 1704103200000

    def test_serialize_point_with_mixed_properties(self):
        """Test: Serialization with mix of basic, health, and optional properties."""
        point = ControllerPointsModel(
            controller_ip_address="192.168.1.100",
            bacnet_object_type="analogValue",
            point_id=1,
            iot_device_point_id="test-point-id",
            controller_id="test-controller",
            controller_device_id="test-device",
            # Basic properties
            present_value="22.5",
            units="degreesCelsius",
            # Health properties
            status_flags="[0, 1, 1, 0]",  # BACnet StatusFlags: [IN_ALARM, FAULT, OVERRIDDEN, OUT_OF_SERVICE]
            event_state="normal",
            out_of_service=False,
            reliability="noFaultDetected",
            # Optional properties
            high_limit=30.0,
            low_limit=10.0,
            priority_array=json.dumps([None, None, 25.0]),
            event_detection_enable=True,
            created_at_unix_milli_timestamp=1704103200000,
        )

        serialized = _serialize_point(point)

        # All property types should be present and correctly formatted
        assert serialized["presentValue"] == "22.5"
        assert serialized["units"] == "degreesCelsius"
        assert serialized["statusFlags"] == [0, 1, 1, 0]
        assert serialized["eventState"] == "normal"
        assert serialized["outOfService"] is False
        assert serialized["reliability"] == "noFaultDetected"
        assert serialized["highLimit"] == 30.0
        assert serialized["lowLimit"] == 10.0
        assert isinstance(serialized["priorityArray"], list)
        assert serialized["eventDetectionEnable"] is True
