import json
from typing import Optional
from pydantic import BaseModel, Field

from src.models.controller_points import ControllerPointsModel
from src.utils.logger import logger


class LimitEnableDTO(BaseModel):
    """BACnet LimitEnable bit structure."""

    lowLimitEnable: bool
    highLimitEnable: bool


class EventTransitionBitsDTO(BaseModel):
    """BACnet EventTransitionBits structure (used for eventEnable and ackedTransitions)."""

    toFault: bool
    toNormal: bool
    toOffnormal: bool


class EventAlgorithmInhibitRefDTO(BaseModel):
    """BACnet ObjectPropertyReference structure."""

    objectIdentifier: str
    propertyIdentifier: str
    arrayIndex: Optional[int] = None


class ControllerPointDTO(BaseModel):
    """
    Type-safe DTO for controller points in camelCase format.

    Used for:
    - MQTT publishing (publish_point_bulk)
    - API responses
    - TimescaleDB uploads

    Converts from ControllerPointsModel (snake_case database) to camelCase API format.
    """

    # Core identification fields
    id: Optional[int] = None
    controllerId: str
    controllerIpAddress: str
    controllerPort: int
    bacnetObjectType: str  # Converted from enum to string
    pointId: int
    iotDevicePointId: str
    controllerDeviceId: str

    # Value and metadata
    units: Optional[str] = None
    presentValue: Optional[str] = None
    isUploaded: bool = False

    # Timestamps
    createdAt: str  # ISO 8601 format
    updatedAt: str  # ISO 8601 format
    createdAtUnixMilliTimestamp: int

    # Health monitoring fields
    statusFlags: Optional[list[int]] = None  # Parsed from JSON: [0, 1, 0, 1]
    eventState: Optional[str] = None
    outOfService: Optional[bool] = None
    reliability: Optional[str] = None

    # Value limit properties
    minPresValue: Optional[float] = None
    maxPresValue: Optional[float] = None
    highLimit: Optional[float] = None
    lowLimit: Optional[float] = None
    resolution: Optional[float] = None

    # Control properties
    priorityArray: Optional[list[Optional[float]]] = Field(
        None, description="16-element array with nulls and float values"
    )
    relinquishDefault: Optional[float] = None

    # Notification configuration
    covIncrement: Optional[float] = None
    timeDelay: Optional[int] = None
    timeDelayNormal: Optional[int] = None
    notificationClass: Optional[int] = None
    notifyType: Optional[str] = None
    deadband: Optional[float] = None
    limitEnable: Optional[LimitEnableDTO] = None

    # Event properties
    eventEnable: Optional[EventTransitionBitsDTO] = None
    ackedTransitions: Optional[EventTransitionBitsDTO] = None
    eventTimeStamps: Optional[list[Optional[str]]] = Field(
        None, description="3-element array of ISO 8601 timestamp strings or nulls"
    )
    eventMessageTexts: Optional[list[str]] = Field(
        None, description="3-element array of message strings"
    )
    eventMessageTextsConfig: Optional[list[str]] = Field(
        None, description="3-element array of config strings"
    )

    # Algorithm control
    eventDetectionEnable: Optional[bool] = None
    eventAlgorithmInhibitRef: Optional[EventAlgorithmInhibitRefDTO] = None
    eventAlgorithmInhibit: Optional[bool] = None
    reliabilityEvaluationInhibit: Optional[bool] = None

    # Error tracking
    errorInfo: Optional[str] = None

    @classmethod
    def from_model(cls, point: ControllerPointsModel) -> "ControllerPointDTO":
        """
        Convert ControllerPointsModel (snake_case database) to ControllerPointDTO (camelCase API).

        Handles:
        - snake_case → camelCase conversion
        - JSON string parsing for complex fields
        - Enum → string conversion
        - datetime → ISO 8601 string conversion
        """

        # Parse JSON fields with error handling
        def parse_json_field(field_value: Optional[str], field_name: str):
            """Parse JSON string field, return None if invalid."""
            if not field_value:
                return None
            try:
                return json.loads(field_value)
            except (json.JSONDecodeError, TypeError) as e:
                logger.warning(f"Failed to parse {field_name}: {field_value} - {e}")
                return None

        # Parse status_flags: "[0, 1, 0, 1]" → [0, 1, 0, 1]
        status_flags = parse_json_field(point.status_flags, "status_flags")

        # Parse priority_array: "[null, null, 50.0, ...]" → [None, None, 50.0, ...]
        priority_array = parse_json_field(point.priority_array, "priority_array")

        # Parse limit_enable: '{"lowLimitEnable": true, ...}' → LimitEnableDTO
        limit_enable_data = parse_json_field(point.limit_enable, "limit_enable")
        limit_enable = (
            LimitEnableDTO(**limit_enable_data) if limit_enable_data else None
        )

        # Parse event_enable: '{"toFault": true, ...}' → EventTransitionBitsDTO
        event_enable_data = parse_json_field(point.event_enable, "event_enable")
        event_enable = (
            EventTransitionBitsDTO(**event_enable_data) if event_enable_data else None
        )

        # Parse acked_transitions: '{"toFault": false, ...}' → EventTransitionBitsDTO
        acked_transitions_data = parse_json_field(
            point.acked_transitions, "acked_transitions"
        )
        acked_transitions = (
            EventTransitionBitsDTO(**acked_transitions_data)
            if acked_transitions_data
            else None
        )

        # Parse event_time_stamps: '["2024-01-01T10:00:00Z", null, ...]' → list
        event_time_stamps = parse_json_field(
            point.event_time_stamps, "event_time_stamps"
        )

        # Parse event_message_texts: '["High alarm", "Normal", "Warning"]' → list
        event_message_texts = parse_json_field(
            point.event_message_texts, "event_message_texts"
        )

        # Parse event_message_texts_config: '["", "", ""]' → list
        event_message_texts_config = parse_json_field(
            point.event_message_texts_config, "event_message_texts_config"
        )

        # Parse event_algorithm_inhibit_ref: '{"objectIdentifier": "analogInput:1", ...}' → DTO
        event_algorithm_inhibit_ref_data = parse_json_field(
            point.event_algorithm_inhibit_ref, "event_algorithm_inhibit_ref"
        )
        event_algorithm_inhibit_ref = (
            EventAlgorithmInhibitRefDTO(**event_algorithm_inhibit_ref_data)
            if event_algorithm_inhibit_ref_data
            else None
        )

        # Convert datetime to ISO 8601 strings
        created_at_iso = point.created_at.isoformat() if point.created_at else ""
        updated_at_iso = point.updated_at.isoformat() if point.updated_at else ""

        # Convert BacnetObjectTypeEnum to string
        bacnet_object_type_str = (
            point.bacnet_object_type.value
            if hasattr(point.bacnet_object_type, "value")
            else str(point.bacnet_object_type)
        )

        return cls(
            # Core fields
            id=point.id,
            controllerId=point.controller_id,
            controllerIpAddress=point.controller_ip_address,
            controllerPort=point.controller_port,
            bacnetObjectType=bacnet_object_type_str,
            pointId=point.point_id,
            iotDevicePointId=point.iot_device_point_id,
            controllerDeviceId=point.controller_device_id,
            # Value and metadata
            units=point.units,
            presentValue=point.present_value,
            isUploaded=point.is_uploaded,
            # Timestamps
            createdAt=created_at_iso,
            updatedAt=updated_at_iso,
            createdAtUnixMilliTimestamp=point.created_at_unix_milli_timestamp,
            # Health fields
            statusFlags=status_flags,
            eventState=point.event_state,
            outOfService=point.out_of_service,
            reliability=point.reliability,
            # Value limits
            minPresValue=point.min_pres_value,
            maxPresValue=point.max_pres_value,
            highLimit=point.high_limit,
            lowLimit=point.low_limit,
            resolution=point.resolution,
            # Control properties
            priorityArray=priority_array,
            relinquishDefault=point.relinquish_default,
            # Notification config
            covIncrement=point.cov_increment,
            timeDelay=point.time_delay,
            timeDelayNormal=point.time_delay_normal,
            notificationClass=point.notification_class,
            notifyType=point.notify_type,
            deadband=point.deadband,
            limitEnable=limit_enable,
            # Event properties
            eventEnable=event_enable,
            ackedTransitions=acked_transitions,
            eventTimeStamps=event_time_stamps,
            eventMessageTexts=event_message_texts,
            eventMessageTextsConfig=event_message_texts_config,
            # Algorithm control
            eventDetectionEnable=point.event_detection_enable,
            eventAlgorithmInhibitRef=event_algorithm_inhibit_ref,
            eventAlgorithmInhibit=point.event_algorithm_inhibit,
            reliabilityEvaluationInhibit=point.reliability_evaluation_inhibit,
            # Error tracking
            errorInfo=point.error_info,
        )
