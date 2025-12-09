"""Unit conversion helpers for control sequences."""

from enum import StrEnum

CELSIUS_TO_KELVIN_OFFSET = 273.15
FAHRENHEIT_TO_CELSIUS_OFFSET = 32
FAHRENHEIT_TO_CELSIUS_RATIO = 5 / 9

CFM_TO_M3_PER_S = 0.000471947
L_PER_S_TO_M3_PER_S = 0.001
M3_PER_H_TO_M3_PER_S = 1 / 3600


class TemperatureUnit(StrEnum):
    """Supported temperature units."""

    KELVIN = "K"
    CELSIUS = "C"
    FAHRENHEIT = "F"


class AirflowUnit(StrEnum):
    """Supported airflow units."""

    M3_PER_S = "m3/s"
    CFM = "cfm"
    L_PER_S = "L/s"
    M3_PER_H = "m3/h"


def temp_in_kelvin(value: float, unit: TemperatureUnit) -> float:
    """Convert temperature to Kelvin."""
    if unit == TemperatureUnit.KELVIN:
        return value
    if unit == TemperatureUnit.CELSIUS:
        return value + CELSIUS_TO_KELVIN_OFFSET
    fahrenheit_as_celsius = (
        (value - FAHRENHEIT_TO_CELSIUS_OFFSET) * FAHRENHEIT_TO_CELSIUS_RATIO
    )
    return fahrenheit_as_celsius + CELSIUS_TO_KELVIN_OFFSET


def airflow_in_m3_per_s(value: float, unit: AirflowUnit) -> float:
    """Convert airflow to m³/s."""
    if unit == AirflowUnit.M3_PER_S:
        return value
    if unit == AirflowUnit.CFM:
        return value * CFM_TO_M3_PER_S
    if unit == AirflowUnit.L_PER_S:
        return value * L_PER_S_TO_M3_PER_S
    return value * M3_PER_H_TO_M3_PER_S
