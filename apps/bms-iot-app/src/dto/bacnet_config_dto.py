from typing import Optional, Dict, List, Any, Union
from pydantic import BaseModel, Field

from src.dto.controller_point_dto import (
    LimitEnableDTO,
    EventTransitionBitsDTO,
    EventAlgorithmInhibitRefDTO,
)


class BacnetDiscoveredPropertiesDTO(BaseModel):
    """
    Transform discovered BACnet properties to match ControllerPoint format.

    IMPORTANT: ControllerPoint format comes from bacpypes3 library processing.
    We match that format exactly for consistency between discovery and monitoring.

    Transformations applied:
    - limitEnable: [1, 1] → {lowLimitEnable: true, highLimitEnable: true}
    - eventEnable: [1, 1, 1] → {toFault: true, toNormal: true, toOffnormal: true}
    - ackedTransitions: [0, 1, 0] → {toFault: false, toNormal: true, toOffnormal: false}
    - eventTimeStamps: [{"type": "dateTime", "value": "..."}, ...] → ["...", null, null]
    - priorityArray: [{"type": "real", "value": 0.0}, ...] → [0.0, null, ...]
    - outOfService: 0/1 → boolean
    - eventAlgorithmInhibit: 0/1 → boolean
    - eventDetectionEnable: 0/1 → boolean
    - reliabilityEvaluationInhibit: 0/1 → boolean

    Preserved as-is:
    - statusFlags: [0, 0, 0, 0]
    """

    # Core value
    objectIdentifier: Optional[List[Any]] = None
    objectName: Optional[str] = None
    presentValue: Optional[Union[str, int, float, bool]] = None
    objectType: Optional[str] = None
    description: Optional[str] = None

    # Health monitoring (same as ControllerPoint)
    statusFlags: Optional[List[int]] = None
    eventState: Optional[str] = None
    outOfService: Optional[bool] = None
    reliability: Optional[str] = None

    # Value limits (same as ControllerPoint)
    units: Optional[str] = None
    minPresValue: Optional[float] = None
    maxPresValue: Optional[float] = None
    highLimit: Optional[float] = None
    lowLimit: Optional[float] = None
    resolution: Optional[float] = None

    # Control properties (EXTRACT values from objects to match ControllerPoint)
    priorityArray: Optional[List[Optional[float]]] = Field(
        None, description="16-element array with nulls and float values"
    )
    relinquishDefault: Optional[Union[float, str]] = None

    # Notification configuration
    covIncrement: Optional[float] = None
    timeDelay: Optional[int] = None
    timeDelayNormal: Optional[int] = None
    notificationClass: Optional[int] = None
    notifyType: Optional[str] = None
    deadband: Optional[float] = None
    limitEnable: Optional[LimitEnableDTO] = None

    # Event properties (EXTRACT timestamp strings to match ControllerPoint)
    eventEnable: Optional[EventTransitionBitsDTO] = None
    ackedTransitions: Optional[EventTransitionBitsDTO] = None
    eventTimeStamps: Optional[List[Optional[str]]] = Field(
        None, description="3-element array of ISO 8601 timestamp strings"
    )
    eventMessageTexts: Optional[List[str]] = None
    eventMessageTextsConfig: Optional[List[str]] = None

    # Algorithm control
    eventDetectionEnable: Optional[bool] = None
    eventAlgorithmInhibitRef: Optional[EventAlgorithmInhibitRefDTO] = None
    eventAlgorithmInhibit: Optional[bool] = None
    reliabilityEvaluationInhibit: Optional[bool] = None

    # Binary/multistate specific
    activeText: Optional[str] = None
    inactiveText: Optional[str] = None
    numberOfStates: Optional[int] = None
    stateText: Optional[List[str]] = None

    @classmethod
    def from_dict(cls, properties: Dict[str, Any]) -> "BacnetDiscoveredPropertiesDTO":
        """
        Transform from DB format to ControllerPoint-compatible format.

        Matches the format produced by bacpypes3 library processing.
        """

        # Transform priorityArray: [{"type": "real", "value": 0.0}, ...] → [0.0, null, ...]
        priority_array = None
        if "priorityArray" in properties and properties["priorityArray"]:
            priority_array = []
            for item in properties["priorityArray"]:
                if item is None:
                    priority_array.append(None)
                elif isinstance(item, dict) and "value" in item:
                    priority_array.append(item["value"])
                else:
                    priority_array.append(None)

        # Transform eventTimeStamps: [{"type": "dateTime", "value": "..."}, ...] → ["...", null, null]
        # Convert all values to strings for consistency (dateTime, sequenceNumber, time)
        event_timestamps = None
        if "eventTimeStamps" in properties and properties["eventTimeStamps"]:
            event_timestamps = []
            for item in properties["eventTimeStamps"]:
                if item is None:
                    event_timestamps.append(None)
                elif isinstance(item, dict) and "value" in item:
                    # Convert to string for consistency across all timestamp types
                    event_timestamps.append(str(item["value"]))
                else:
                    event_timestamps.append(None)

        # Transform limitEnable: [1, 1] → {lowLimitEnable: true, highLimitEnable: true}
        limit_enable = None
        if "limitEnable" in properties and properties["limitEnable"]:
            arr = properties["limitEnable"]
            if isinstance(arr, list) and len(arr) >= 2:
                limit_enable = LimitEnableDTO(
                    lowLimitEnable=bool(arr[0]), highLimitEnable=bool(arr[1])
                )

        # Transform eventEnable: [1, 1, 1] → {toFault: true, toNormal: true, toOffnormal: true}
        event_enable = None
        if "eventEnable" in properties and properties["eventEnable"]:
            arr = properties["eventEnable"]
            if isinstance(arr, list) and len(arr) >= 3:
                event_enable = EventTransitionBitsDTO(
                    toFault=bool(arr[0]),
                    toNormal=bool(arr[1]),
                    toOffnormal=bool(arr[2]),
                )

        # Transform ackedTransitions: [0, 1, 0] → {toFault: false, toNormal: true, toOffnormal: false}
        acked_transitions = None
        if "ackedTransitions" in properties and properties["ackedTransitions"]:
            arr = properties["ackedTransitions"]
            if isinstance(arr, list) and len(arr) >= 3:
                acked_transitions = EventTransitionBitsDTO(
                    toFault=bool(arr[0]),
                    toNormal=bool(arr[1]),
                    toOffnormal=bool(arr[2]),
                )

        return cls(
            objectIdentifier=properties.get("objectIdentifier"),
            objectName=properties.get("objectName"),
            presentValue=properties.get("presentValue"),
            objectType=properties.get("objectType"),
            description=properties.get("description"),
            statusFlags=properties.get("statusFlags"),
            eventState=properties.get("eventState"),
            outOfService=(
                bool(properties["outOfService"])
                if "outOfService" in properties
                else None
            ),
            reliability=properties.get("reliability"),
            units=properties.get("units"),
            minPresValue=properties.get("minPresValue"),
            maxPresValue=properties.get("maxPresValue"),
            highLimit=properties.get("highLimit"),
            lowLimit=properties.get("lowLimit"),
            resolution=properties.get("resolution"),
            priorityArray=priority_array,
            relinquishDefault=properties.get("relinquishDefault"),
            covIncrement=properties.get("covIncrement"),
            timeDelay=properties.get("timeDelay"),
            timeDelayNormal=properties.get("timeDelayNormal"),
            notificationClass=properties.get("notificationClass"),
            notifyType=properties.get("notifyType"),
            deadband=properties.get("deadband"),
            limitEnable=limit_enable,
            eventEnable=event_enable,
            ackedTransitions=acked_transitions,
            eventTimeStamps=event_timestamps,
            eventMessageTexts=properties.get("eventMessageTexts"),
            eventMessageTextsConfig=properties.get("eventMessageTextsConfig"),
            eventDetectionEnable=(
                bool(properties["eventDetectionEnable"])
                if "eventDetectionEnable" in properties
                else None
            ),
            eventAlgorithmInhibit=(
                bool(properties["eventAlgorithmInhibit"])
                if "eventAlgorithmInhibit" in properties
                else None
            ),
            reliabilityEvaluationInhibit=(
                bool(properties["reliabilityEvaluationInhibit"])
                if "reliabilityEvaluationInhibit" in properties
                else None
            ),
            activeText=properties.get("activeText"),
            inactiveText=properties.get("inactiveText"),
            numberOfStates=properties.get("numberOfStates"),
            stateText=properties.get("stateText"),
        )
