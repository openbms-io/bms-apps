"""
Test ControllerPointDTO conversion from ControllerPointsModel.

Tests TDD approach:
1. Test basic field conversion (snake_case → camelCase)
2. Test JSON parsing for complex fields
3. Test None handling
4. Test enum conversion
5. Test datetime conversion
"""

import json
from datetime import datetime, timezone


from src.dto import (
    ControllerPointDTO,
    LimitEnableDTO,
    EventTransitionBitsDTO,
    EventAlgorithmInhibitRefDTO,
)
from src.models.controller_points import ControllerPointsModel
from src.models.bacnet_types import BacnetObjectTypeEnum


class TestNestedDTOs:
    """Test nested DTO structures."""

    def test_limit_enable_dto_creation(self):
        """Test: LimitEnableDTO accepts boolean values."""
        dto = LimitEnableDTO(lowLimitEnable=True, highLimitEnable=False)

        assert dto.lowLimitEnable is True
        assert dto.highLimitEnable is False

    def test_event_transition_bits_dto_creation(self):
        """Test: EventTransitionBitsDTO accepts boolean values."""
        dto = EventTransitionBitsDTO(toFault=True, toNormal=False, toOffnormal=True)

        assert dto.toFault is True
        assert dto.toNormal is False
        assert dto.toOffnormal is True

    def test_event_algorithm_inhibit_ref_dto_creation(self):
        """Test: EventAlgorithmInhibitRefDTO with all fields."""
        dto = EventAlgorithmInhibitRefDTO(
            objectIdentifier="analogInput:1",
            propertyIdentifier="presentValue",
            arrayIndex=5,
        )

        assert dto.objectIdentifier == "analogInput:1"
        assert dto.propertyIdentifier == "presentValue"
        assert dto.arrayIndex == 5

    def test_event_algorithm_inhibit_ref_dto_without_array_index(self):
        """Test: EventAlgorithmInhibitRefDTO with optional arrayIndex."""
        dto = EventAlgorithmInhibitRefDTO(
            objectIdentifier="analogValue:10", propertyIdentifier="outOfService"
        )

        assert dto.objectIdentifier == "analogValue:10"
        assert dto.propertyIdentifier == "outOfService"
        assert dto.arrayIndex is None


class TestControllerPointDTOBasicConversion:
    """Test basic field conversion from ControllerPointsModel."""

    def test_from_model_basic_fields(self):
        """Test: Basic field conversion from snake_case to camelCase."""
        model = ControllerPointsModel(
            id=1,
            controller_id="ctrl-123",
            controller_ip_address="192.168.1.100",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_INPUT,
            point_id=42,
            iot_device_point_id="point-uuid-456",
            controller_device_id="device-789",
            units="degrees-celsius",
            present_value="23.5",
            is_uploaded=False,
            created_at=datetime(2024, 1, 1, 10, 0, 0, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, 12, 0, 0, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704103200000,
        )

        dto = ControllerPointDTO.from_model(model)

        # Core fields
        assert dto.id == 1
        assert dto.controllerId == "ctrl-123"
        assert dto.controllerIpAddress == "192.168.1.100"
        assert dto.controllerPort == 47808
        assert dto.bacnetObjectType == "analogInput"
        assert dto.pointId == 42
        assert dto.iotDevicePointId == "point-uuid-456"
        assert dto.controllerDeviceId == "device-789"

        # Value fields
        assert dto.units == "degrees-celsius"
        assert dto.presentValue == "23.5"
        assert dto.isUploaded is False

        # Timestamps
        assert dto.createdAt == "2024-01-01T10:00:00+00:00"
        assert dto.updatedAt == "2024-01-01T12:00:00+00:00"
        assert dto.createdAtUnixMilliTimestamp == 1704103200000

    def test_from_model_enum_conversion(self):
        """Test: BacnetObjectTypeEnum is converted to string."""
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_OUTPUT,
            point_id=10,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.bacnetObjectType == "analogOutput"
        assert isinstance(dto.bacnetObjectType, str)


class TestControllerPointDTOJSONParsing:
    """Test JSON string parsing for complex fields."""

    def test_status_flags_parsing(self):
        """Test: status_flags JSON string is parsed to list[int]."""
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            status_flags="[0, 1, 0, 1]",  # JSON string
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.statusFlags == [0, 1, 0, 1]
        assert isinstance(dto.statusFlags, list)

    def test_status_flags_none(self):
        """Test: None status_flags remains None."""
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            status_flags=None,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.statusFlags is None

    def test_priority_array_parsing(self):
        """Test: priority_array JSON string is parsed to list."""
        priority_array_json = json.dumps([None, None, 50.0] + [None] * 13)
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            priority_array=priority_array_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.priorityArray is not None
        assert len(dto.priorityArray) == 16
        assert dto.priorityArray[2] == 50.0
        assert dto.priorityArray[0] is None

    def test_limit_enable_parsing(self):
        """Test: limit_enable JSON string is parsed to LimitEnableDTO."""
        limit_enable_json = json.dumps(
            {"lowLimitEnable": True, "highLimitEnable": False}
        )
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            limit_enable=limit_enable_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.limitEnable is not None
        assert isinstance(dto.limitEnable, LimitEnableDTO)
        assert dto.limitEnable.lowLimitEnable is True
        assert dto.limitEnable.highLimitEnable is False

    def test_event_enable_parsing(self):
        """Test: event_enable JSON string is parsed to EventTransitionBitsDTO."""
        event_enable_json = json.dumps(
            {"toFault": True, "toNormal": False, "toOffnormal": True}
        )
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            event_enable=event_enable_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.eventEnable is not None
        assert isinstance(dto.eventEnable, EventTransitionBitsDTO)
        assert dto.eventEnable.toFault is True
        assert dto.eventEnable.toNormal is False
        assert dto.eventEnable.toOffnormal is True

    def test_acked_transitions_parsing(self):
        """Test: acked_transitions JSON string is parsed to EventTransitionBitsDTO."""
        acked_transitions_json = json.dumps(
            {"toFault": False, "toNormal": True, "toOffnormal": False}
        )
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            acked_transitions=acked_transitions_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.ackedTransitions is not None
        assert isinstance(dto.ackedTransitions, EventTransitionBitsDTO)
        assert dto.ackedTransitions.toFault is False
        assert dto.ackedTransitions.toNormal is True

    def test_event_time_stamps_parsing(self):
        """Test: event_time_stamps JSON string is parsed to list."""
        event_time_stamps_json = json.dumps(
            ["2024-01-01T10:00:00+00:00", None, "2024-01-01T12:00:00+00:00"]
        )
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            event_time_stamps=event_time_stamps_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.eventTimeStamps is not None
        assert len(dto.eventTimeStamps) == 3
        assert dto.eventTimeStamps[0] == "2024-01-01T10:00:00+00:00"
        assert dto.eventTimeStamps[1] is None
        assert dto.eventTimeStamps[2] == "2024-01-01T12:00:00+00:00"

    def test_event_message_texts_parsing(self):
        """Test: event_message_texts JSON string is parsed to list."""
        event_message_texts_json = json.dumps(
            ["High alarm", "Normal condition", "Warning"]
        )
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            event_message_texts=event_message_texts_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.eventMessageTexts == ["High alarm", "Normal condition", "Warning"]

    def test_event_algorithm_inhibit_ref_parsing(self):
        """Test: event_algorithm_inhibit_ref JSON string is parsed to DTO."""
        ref_json = json.dumps(
            {
                "objectIdentifier": "analogInput:5",
                "propertyIdentifier": "presentValue",
                "arrayIndex": 3,
            }
        )
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            event_algorithm_inhibit_ref=ref_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.eventAlgorithmInhibitRef is not None
        assert isinstance(dto.eventAlgorithmInhibitRef, EventAlgorithmInhibitRefDTO)
        assert dto.eventAlgorithmInhibitRef.objectIdentifier == "analogInput:5"
        assert dto.eventAlgorithmInhibitRef.propertyIdentifier == "presentValue"
        assert dto.eventAlgorithmInhibitRef.arrayIndex == 3


class TestControllerPointDTOInvalidJSON:
    """Test handling of invalid JSON strings."""

    def test_invalid_json_returns_none(self):
        """Test: Invalid JSON string returns None instead of raising error."""
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            status_flags="invalid json {",  # Invalid JSON
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.statusFlags is None


class TestControllerPointDTOOptionalFields:
    """Test handling of optional fields."""

    def test_all_optional_fields_none(self):
        """Test: All optional fields can be None."""
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)

        # Health fields
        assert dto.statusFlags is None
        assert dto.eventState is None
        assert dto.outOfService is None
        assert dto.reliability is None

        # Optional properties
        assert dto.minPresValue is None
        assert dto.priorityArray is None
        assert dto.limitEnable is None
        assert dto.eventEnable is None

    def test_partial_optional_fields(self):
        """Test: Some optional fields populated, others None."""
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
            # Only some fields
            min_pres_value=10.0,
            max_pres_value=100.0,
            event_state="normal",
        )

        dto = ControllerPointDTO.from_model(model)

        assert dto.minPresValue == 10.0
        assert dto.maxPresValue == 100.0
        assert dto.eventState == "normal"
        assert dto.priorityArray is None
        assert dto.limitEnable is None


class TestControllerPointDTOSerialization:
    """Test DTO serialization to dict (model_dump)."""

    def test_model_dump_produces_camel_case(self):
        """Test: model_dump() produces camelCase keys."""
        model = ControllerPointsModel(
            id=1,
            controller_id="ctrl-123",
            controller_ip_address="192.168.1.100",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_INPUT,
            point_id=42,
            iot_device_point_id="point-uuid",
            controller_device_id="device-id",
            status_flags="[0, 1, 0, 1]",
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)
        data = dto.model_dump()

        # Verify camelCase keys
        assert "controllerId" in data
        assert "controllerIpAddress" in data
        assert "bacnetObjectType" in data
        assert "pointId" in data
        assert "iotDevicePointId" in data
        assert "statusFlags" in data

        # Verify NO snake_case keys
        assert "controller_id" not in data
        assert "controller_ip_address" not in data
        assert "point_id" not in data

    def test_model_dump_nested_objects_serialized(self):
        """Test: Nested DTOs are serialized to dicts."""
        limit_enable_json = json.dumps(
            {"lowLimitEnable": True, "highLimitEnable": False}
        )
        model = ControllerPointsModel(
            controller_id="ctrl-1",
            controller_ip_address="192.168.1.1",
            controller_port=47808,
            bacnet_object_type=BacnetObjectTypeEnum.ANALOG_VALUE,
            point_id=1,
            iot_device_point_id="point-1",
            controller_device_id="device-1",
            limit_enable=limit_enable_json,
            created_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            updated_at=datetime(2024, 1, 1, tzinfo=timezone.utc),
            created_at_unix_milli_timestamp=1704067200000,
        )

        dto = ControllerPointDTO.from_model(model)
        data = dto.model_dump()

        # limitEnable should be a dict, not a DTO instance
        assert isinstance(data["limitEnable"], dict)
        assert data["limitEnable"]["lowLimitEnable"] is True
        assert data["limitEnable"]["highLimitEnable"] is False
