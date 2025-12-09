"""Domain enums for G36 Reheat control sequence."""

from enum import IntEnum


class OperationMode(IntEnum):
    """G36 operation modes per ASHRAE Guideline 36 specification."""

    OCCUPIED = 1
    UNOCCUPIED = 2
    STANDBY = 3
    WARMUP = 4
    COOLDOWN = 5
    SETUP = 6
    SETBACK = 7


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
