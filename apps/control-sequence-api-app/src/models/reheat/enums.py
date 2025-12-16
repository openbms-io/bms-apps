"""Domain enums for G36 Reheat control sequence."""

from enum import IntEnum, StrEnum


class OperationMode(IntEnum):
    """G36 operation modes per ASHRAE Guideline 36 specification.

    Values correspond to FMU input requirements (1-7).
    """

    OCCUPIED = 1
    UNOCCUPIED = 2
    STANDBY = 3
    WARMUP = 4
    COOLDOWN = 5
    SETUP = 6
    SETBACK = 7


class OperationModeStr(StrEnum):
    """G36 operation modes as string enum for API inputs."""

    OCCUPIED = "occupied"
    UNOCCUPIED = "unoccupied"
    STANDBY = "standby"
    WARMUP = "warmup"
    COOLDOWN = "cooldown"
    SETUP = "setup"
    SETBACK = "setback"


OPERATION_MODE_STR_TO_INT: dict[OperationModeStr, OperationMode] = {
    OperationModeStr.OCCUPIED: OperationMode.OCCUPIED,
    OperationModeStr.UNOCCUPIED: OperationMode.UNOCCUPIED,
    OperationModeStr.STANDBY: OperationMode.STANDBY,
    OperationModeStr.WARMUP: OperationMode.WARMUP,
    OperationModeStr.COOLDOWN: OperationMode.COOLDOWN,
    OperationModeStr.SETUP: OperationMode.SETUP,
    OperationModeStr.SETBACK: OperationMode.SETBACK,
}


class VentilationStandard(IntEnum):
    """Ventilation standard selection."""

    ASHRAE62_1 = 1
    CALIFORNIA_TITLE_24 = 2


class ControllerType(IntEnum):
    """Controller type for damper/valve control."""

    P = 1
    PI = 2
    PD = 3
    PID = 4


class OverrideMode(IntEnum):
    """Override mode for damper position and flow setpoint."""

    NO_OVERRIDE = 0
    OVERRIDE_ACTIVE = 1


class ParameterCategory(StrEnum):
    """Categories for grouping ReheatParameters in UI."""

    UNITS = "units"
    SENSORS = "sensors"
    FEATURES = "features"
    AIRFLOWS = "airflows"
    CONTROLLER_GAINS = "controllerGains"
    TIMING = "timing"
    THRESHOLDS = "thresholds"
    HYSTERESIS = "hysteresis"
