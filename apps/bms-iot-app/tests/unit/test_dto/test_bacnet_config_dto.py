from src.dto.bacnet_config_dto import BacnetDiscoveredPropertiesDTO


class TestBacnetDiscoveredPropertiesDTO:
    """Test BacnetDiscoveredPropertiesDTO transformations to match ControllerPoint format."""

    def test_from_dict_basic_fields(self):
        """Test basic field pass-through."""
        properties = {
            "objectName": "test_sensor",
            "presentValue": 23.5,
            "units": "degrees-celsius",
            "statusFlags": [0, 0, 0, 0],
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.objectName == "test_sensor"
        assert dto.presentValue == 23.5
        assert dto.units == "degrees-celsius"
        assert dto.statusFlags == [0, 0, 0, 0]

    def test_from_dict_priority_array_extraction(self):
        """Test priorityArray extracts values from objects to match ControllerPoint format."""
        properties = {
            "priorityArray": [
                {"type": "real", "value": 0.0},
                None,
                {"type": "real", "value": 50.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 0.0},
                {"type": "real", "value": 19.6},
            ]
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.priorityArray is not None
        assert len(dto.priorityArray) == 16
        assert dto.priorityArray[0] == 0.0
        assert dto.priorityArray[1] is None
        assert dto.priorityArray[2] == 50.0
        assert dto.priorityArray[15] == 19.6

    def test_from_dict_event_timestamps_extraction(self):
        """Test eventTimeStamps extracts string values from objects to match ControllerPoint format."""
        properties = {
            "eventTimeStamps": [
                {"type": "dateTime", "value": "2025-10-21T12:02:44.71"},
                {"type": "dateTime", "value": "2025-10-21T12:02:44.71"},
                None,
            ]
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.eventTimeStamps is not None
        assert len(dto.eventTimeStamps) == 3
        assert dto.eventTimeStamps[0] == "2025-10-21T12:02:44.71"
        assert dto.eventTimeStamps[1] == "2025-10-21T12:02:44.71"
        assert dto.eventTimeStamps[2] is None

    def test_from_dict_event_timestamps_with_sequence_number(self):
        """Test eventTimeStamps handles sequenceNumber type (for devices without RTC)."""
        properties = {
            "eventTimeStamps": [
                {"type": "sequenceNumber", "value": 12345},
                None,
                None,
            ]
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.eventTimeStamps is not None
        assert dto.eventTimeStamps[0] == "12345"  # Converted to string
        assert dto.eventTimeStamps[1] is None

    def test_from_dict_limit_enable_transformation(self):
        """Test limitEnable array → object transformation."""
        properties = {"limitEnable": [1, 1]}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.limitEnable is not None
        assert dto.limitEnable.lowLimitEnable is True
        assert dto.limitEnable.highLimitEnable is True

    def test_from_dict_limit_enable_mixed_values(self):
        """Test limitEnable with mixed enable/disable values."""
        properties = {"limitEnable": [1, 0]}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.limitEnable is not None
        assert dto.limitEnable.lowLimitEnable is True
        assert dto.limitEnable.highLimitEnable is False

    def test_from_dict_event_enable_transformation(self):
        """Test eventEnable array → object transformation."""
        properties = {"eventEnable": [1, 1, 0]}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.eventEnable is not None
        assert dto.eventEnable.toFault is True
        assert dto.eventEnable.toNormal is True
        assert dto.eventEnable.toOffnormal is False

    def test_from_dict_event_enable_all_enabled(self):
        """Test eventEnable with all transitions enabled."""
        properties = {"eventEnable": [1, 1, 1]}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.eventEnable is not None
        assert dto.eventEnable.toFault is True
        assert dto.eventEnable.toNormal is True
        assert dto.eventEnable.toOffnormal is True

    def test_from_dict_acked_transitions_transformation(self):
        """Test ackedTransitions array → object transformation."""
        properties = {"ackedTransitions": [0, 1, 0]}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.ackedTransitions is not None
        assert dto.ackedTransitions.toFault is False
        assert dto.ackedTransitions.toNormal is True
        assert dto.ackedTransitions.toOffnormal is False

    def test_from_dict_out_of_service_boolean_conversion(self):
        """Test outOfService 0/1 → boolean conversion."""
        # Test 0 → False
        dto1 = BacnetDiscoveredPropertiesDTO.from_dict({"outOfService": 0})
        assert dto1.outOfService is False

        # Test 1 → True
        dto2 = BacnetDiscoveredPropertiesDTO.from_dict({"outOfService": 1})
        assert dto2.outOfService is True

    def test_from_dict_all_boolean_conversions(self):
        """Test all 0/1 → boolean conversions."""
        properties = {
            "eventDetectionEnable": 1,
            "eventAlgorithmInhibit": 0,
            "reliabilityEvaluationInhibit": 1,
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.eventDetectionEnable is True
        assert dto.eventAlgorithmInhibit is False
        assert dto.reliabilityEvaluationInhibit is True

    def test_from_dict_binary_multistate_fields(self):
        """Test binary and multistate specific fields."""
        properties = {
            "activeText": "ON",
            "inactiveText": "OFF",
            "numberOfStates": 3,
            "stateText": ["Low", "Medium", "High"],
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.activeText == "ON"
        assert dto.inactiveText == "OFF"
        assert dto.numberOfStates == 3
        assert dto.stateText == ["Low", "Medium", "High"]

    def test_from_dict_value_limit_properties(self):
        """Test value limit properties pass through correctly."""
        properties = {
            "minPresValue": 12.1,
            "maxPresValue": 42.1,
            "highLimit": 37.1,
            "lowLimit": 17.1,
            "resolution": 0.1,
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.minPresValue == 12.1
        assert dto.maxPresValue == 42.1
        assert dto.highLimit == 37.1
        assert dto.lowLimit == 17.1
        assert dto.resolution == 0.1

    def test_from_dict_notification_properties(self):
        """Test notification configuration properties."""
        properties = {
            "covIncrement": 0.9,
            "timeDelay": 305,
            "timeDelayNormal": 586,
            "notificationClass": 2,
            "notifyType": "alarm",
            "deadband": 0.5,
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.covIncrement == 0.9
        assert dto.timeDelay == 305
        assert dto.timeDelayNormal == 586
        assert dto.notificationClass == 2
        assert dto.notifyType == "alarm"
        assert dto.deadband == 0.5

    def test_from_dict_event_message_texts(self):
        """Test event message texts arrays."""
        properties = {
            "eventMessageTexts": [
                "High alarm condition detected",
                "Normal operating condition",
                "Warning: approaching limits",
            ],
            "eventMessageTextsConfig": ["", "", ""],
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.eventMessageTexts == [
            "High alarm condition detected",
            "Normal operating condition",
            "Warning: approaching limits",
        ]
        assert dto.eventMessageTextsConfig == ["", "", ""]

    def test_from_dict_missing_optional_fields(self):
        """Test that missing optional fields result in None values."""
        properties = {"objectName": "minimal_sensor"}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.objectName == "minimal_sensor"
        assert dto.units is None
        assert dto.limitEnable is None
        assert dto.eventEnable is None
        assert dto.priorityArray is None
        assert dto.eventTimeStamps is None

    def test_serialization_exclude_none(self):
        """Test model_dump excludes None values."""
        properties = {"objectName": "test", "presentValue": 10.0}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)
        serialized = dto.model_dump(exclude_none=True)

        assert "objectName" in serialized
        assert "presentValue" in serialized
        assert "units" not in serialized  # Should be excluded (None)
        assert "limitEnable" not in serialized  # Should be excluded (None)

    def test_serialization_matches_controller_point_format(self):
        """Test complete serialization matches ControllerPoint format from bacpypes3."""
        properties = {
            "objectName": "floor1_temperature",
            "presentValue": 20.1,
            "units": "degrees-celsius",
            "statusFlags": [0, 0, 0, 0],
            "outOfService": 0,
            "limitEnable": [1, 1],
            "eventEnable": [1, 1, 1],
            "ackedTransitions": [0, 1, 0],
            "priorityArray": [{"type": "real", "value": 0.0}, None]
            + [{"type": "real", "value": 0.0}] * 13
            + [{"type": "real", "value": 19.4}],
            "eventTimeStamps": [
                {"type": "dateTime", "value": "2025-10-21T12:02:44.71"},
                {"type": "dateTime", "value": "2025-10-21T12:02:44.71"},
                None,
            ],
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)
        serialized = dto.model_dump(exclude_none=True)

        # Verify matches ControllerPoint format
        assert serialized["objectName"] == "floor1_temperature"
        assert serialized["outOfService"] is False  # boolean not 0/1
        assert serialized["limitEnable"]["lowLimitEnable"] is True  # object
        assert serialized["limitEnable"]["highLimitEnable"] is True
        assert serialized["eventEnable"]["toFault"] is True  # object
        assert serialized["eventEnable"]["toNormal"] is True
        assert serialized["eventEnable"]["toOffnormal"] is True
        assert serialized["ackedTransitions"]["toFault"] is False  # object
        assert serialized["priorityArray"][0] == 0.0  # flat array of values
        assert serialized["priorityArray"][1] is None
        assert serialized["priorityArray"][15] == 19.4
        assert (
            serialized["eventTimeStamps"][0] == "2025-10-21T12:02:44.71"
        )  # string values
        assert serialized["eventTimeStamps"][2] is None

    def test_from_dict_relinquish_default_numeric(self):
        """Test relinquishDefault with numeric value."""
        properties = {"relinquishDefault": 22.1}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.relinquishDefault == 22.1

    def test_from_dict_relinquish_default_string(self):
        """Test relinquishDefault with string value (for binary objects)."""
        properties = {"relinquishDefault": "inactive"}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.relinquishDefault == "inactive"

    def test_from_dict_health_monitoring_fields(self):
        """Test all health monitoring fields."""
        properties = {
            "statusFlags": [0, 1, 0, 1],
            "eventState": "offnormal",
            "outOfService": 0,
            "reliability": "no-fault-detected",
        }

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.statusFlags == [0, 1, 0, 1]
        assert dto.eventState == "offnormal"
        assert dto.outOfService is False
        assert dto.reliability == "no-fault-detected"

    def test_from_dict_object_identifier_tuple(self):
        """Test objectIdentifier as tuple."""
        properties = {"objectIdentifier": ["analog-value", 10]}

        dto = BacnetDiscoveredPropertiesDTO.from_dict(properties)

        assert dto.objectIdentifier == ["analog-value", 10]

    def test_from_dict_present_value_types(self):
        """Test presentValue with different types."""
        # Numeric
        dto1 = BacnetDiscoveredPropertiesDTO.from_dict({"presentValue": 23.5})
        assert dto1.presentValue == 23.5

        # String (for binary/multistate)
        dto2 = BacnetDiscoveredPropertiesDTO.from_dict({"presentValue": "active"})
        assert dto2.presentValue == "active"

        # Boolean
        dto3 = BacnetDiscoveredPropertiesDTO.from_dict({"presentValue": True})
        assert dto3.presentValue is True
