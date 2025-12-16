"""Unit conversion helpers for control sequences."""

from enum import StrEnum

CELSIUS_TO_KELVIN_OFFSET = 273.15
FAHRENHEIT_TO_CELSIUS_OFFSET = 32
FAHRENHEIT_TO_CELSIUS_RATIO = 5 / 9
FAHRENHEIT_TO_KELVIN_DIFF = 5 / 9

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


def temp_diff_in_kelvin(value: float, unit: TemperatureUnit) -> float:
    """Convert temperature difference to Kelvin scale.

    For temperature differences (deltas), only scale matters, not offset:
    - Celsius diff = Kelvin diff (same scale)
    - Fahrenheit diff needs ratio conversion: ΔK = ΔF × 5/9
    """
    if unit == TemperatureUnit.KELVIN:
        return value
    if unit == TemperatureUnit.CELSIUS:
        return value
    return value * FAHRENHEIT_TO_KELVIN_DIFF


def airflow_in_m3_per_s(value: float, unit: AirflowUnit) -> float:
    """Convert airflow to m³/s."""
    if unit == AirflowUnit.M3_PER_S:
        return value
    if unit == AirflowUnit.CFM:
        return value * CFM_TO_M3_PER_S
    if unit == AirflowUnit.L_PER_S:
        return value * L_PER_S_TO_M3_PER_S
    return value * M3_PER_H_TO_M3_PER_S


def kelvin_to_unit(value: float, unit: TemperatureUnit) -> float:
    """Convert temperature from Kelvin to specified unit."""
    if unit == TemperatureUnit.KELVIN:
        return value
    celsius = value - CELSIUS_TO_KELVIN_OFFSET
    if unit == TemperatureUnit.CELSIUS:
        return celsius
    return celsius / FAHRENHEIT_TO_CELSIUS_RATIO + FAHRENHEIT_TO_CELSIUS_OFFSET


def kelvin_diff_to_unit(value: float, unit: TemperatureUnit) -> float:
    """Convert temperature difference from Kelvin scale to specified unit.

    For temperature differences (deltas), only scale matters, not offset:
    - Kelvin diff = Celsius diff (same scale)
    - Fahrenheit diff needs ratio conversion: ΔF = ΔK / (5/9)
    """
    if unit == TemperatureUnit.KELVIN:
        return value
    if unit == TemperatureUnit.CELSIUS:
        return value
    return value / FAHRENHEIT_TO_KELVIN_DIFF


def m3_per_s_to_airflow(value: float, unit: AirflowUnit) -> float:
    """Convert airflow from m³/s to specified unit."""
    if unit == AirflowUnit.M3_PER_S:
        return value
    if unit == AirflowUnit.CFM:
        return value / CFM_TO_M3_PER_S
    if unit == AirflowUnit.L_PER_S:
        return value / L_PER_S_TO_M3_PER_S
    return value / M3_PER_H_TO_M3_PER_S


# Temperature bounds in SI (Kelvin) - typical HVAC operating range
MIN_TEMP_KELVIN = 250.0  # -23°C / -9°F
MAX_TEMP_KELVIN = 350.0  # 77°C / 170°F


def get_temperature_bounds(unit: TemperatureUnit) -> tuple[float, float]:
    """Get valid temperature range for the given unit.

    Returns (min, max) tuple in the specified unit.
    Based on FMU valid range: 250K to 350K.
    """
    if unit == TemperatureUnit.KELVIN:
        return (MIN_TEMP_KELVIN, MAX_TEMP_KELVIN)
    if unit == TemperatureUnit.CELSIUS:
        return (
            MIN_TEMP_KELVIN - CELSIUS_TO_KELVIN_OFFSET,
            MAX_TEMP_KELVIN - CELSIUS_TO_KELVIN_OFFSET,
        )
    # Fahrenheit
    min_celsius = MIN_TEMP_KELVIN - CELSIUS_TO_KELVIN_OFFSET
    max_celsius = MAX_TEMP_KELVIN - CELSIUS_TO_KELVIN_OFFSET
    return (
        min_celsius / FAHRENHEIT_TO_CELSIUS_RATIO + FAHRENHEIT_TO_CELSIUS_OFFSET,
        max_celsius / FAHRENHEIT_TO_CELSIUS_RATIO + FAHRENHEIT_TO_CELSIUS_OFFSET,
    )
