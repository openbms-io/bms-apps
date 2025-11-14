"""ASHRAE 223P Template Types from NREL Library."""
from enum import Enum


class DeviceTemplate(str, Enum):
    """Device templates from NREL ASHRAE 223P library."""

    # Air handling devices
    DAMPER = "damper"
    VALVE_DAMPER = "vlv-dmp"
    FAN = "fan"
    EXHAUST_FAN = "exhaust-fan"
    FILTER = "filter"

    # Coils
    HEAT_RECOVERY_COIL = "heat-recovery-coil"
    CHILLED_WATER_COIL = "chilled-water-coil"
    HOT_WATER_COIL = "hot-water-coil"

    # Pumps
    CHW_PUMP = "chw-pump"
    HW_PUMP = "hw-pump"
    HR_PUMP = "HR-pump"

    # Valves
    CHW_VALVE = "chw-valve"
    HW_VALVE = "hw-valve"
    BELIMO_ENERGY_VALVE = "belimo-energy-valve"

    # Sensors
    SENSOR = "sensor"
    DIFFERENTIAL_SENSOR = "differential-sensor"

    # Equipment
    EVAPORATIVE_COOLER = "evaporative-cooler"
    TANK = "tank"
    HEAT_EXCHANGER = "heat-exchanger"
    FCU = "fcu"
    UNIT_HEATER = "unit-heater"
    DOMESTIC_WATER_HEATER = "domestic-water-heater"

    # Meters
    HRC_BTU_METER = "HRC-BTU-meter"
    HOT_WATER_SYSTEM_BTU_METER = "hot-water-system-BTU-meter"
    CHILLED_WATER_SYSTEM_BTU_METER = "chilled-water-system-BTU-meter"


class SystemTemplate(str, Enum):
    """System templates from NREL ASHRAE 223P library."""

    MAKEUP_AIR_UNIT = "makeup-air-unit"
    VAV_REHEAT = "vav-reheat"
    LAB_VAV_REHEAT = "lab-vav-reheat"
    CHILLED_WATER_SYSTEM = "chilled-water-system"
    HOT_WATER_SYSTEM = "hot-water-system"
    EXHAUST_AIR_UNIT = "exhaust-air-unit"
    HEAT_RECOVERY_SYSTEM = "heat-recovery-system"
    PROCESS_CHILLED_WATER_SYSTEM = "process-chilled-water-system"


class PropertyTemplate(str, Enum):
    """Property templates from NREL ASHRAE 223P library."""

    # Pressure properties
    STATIC_PRESSURE = "static-pressure"
    LOW_STATIC_PRESSURE = "low-static-pressure"
    WATER_STATIC_PRESSURE = "water-static-pressure"
    DIFFERENTIAL_PRESSURE = "differential-pressure"
    WATER_DIFFERENTIAL_PRESSURE = "water-differential-pressure"

    # Damper properties
    DAMPER_COMMAND = "damper-command"
    DAMPER_FEEDBACK = "damper-feedback"

    # Temperature properties
    AIR_TEMPERATURE = "air-temperature"
    WATER_TEMPERATURE = "water-temperature"

    # Flow properties
    AIR_FLOW = "air-flow"
    WATER_FLOW = "water-flow"
    FLOW_STATUS = "flow-status"

    # Control properties
    START_COMMAND = "start-command"
    RUN_STATUS = "run-status"

    # Environmental properties
    RELATIVE_HUMIDITY = "relative-humidity"

    # VFD properties
    VFD_CURRENT = "vfd-current"
    VFD_FREQUENCY = "vfd-frequency"
    VFD_VOLTAGE = "vfd-voltage"
    VFD_POWER = "vfd-power"
    VFD_ENERGY = "vfd-energy"
    VFD_SPEED = "vfd-speed"
    VFD_FEEDBACK = "vfd-feedback"
    VFD_FAULT = "vfd-fault"

    # BTU Meter properties
    BTU_METER_ENERGY = "BTU-Meter-energy"
    BTU_METER_ENERGY_RATE = "BTU-Meter-energy-rate"
    BTU_METER_WATER_FLOW = "BTU-Meter-water-flow"
    BTU_METER_WATER_VOLUME = "BTU-Meter-water-volume"

    # Status properties
    CONDENSATE_OVERFLOW = "condensate-overflow"
    OCCUPANCY_OVERRIDE = "occupancy-override"


TemplateType = DeviceTemplate | SystemTemplate | PropertyTemplate


__all__ = [
    "DeviceTemplate",
    "SystemTemplate",
    "PropertyTemplate",
    "TemplateType",
]
