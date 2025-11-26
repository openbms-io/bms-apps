"""Property semantic analysis utilities for ASHRAE 223P.

Centralized logic for determining property types, actuation, and formatting.
"""
from typing import Literal

PropertyType = Literal["quantifiable", "enumerated"]


def determine_property_type(class_uri: str | None) -> PropertyType | None:
    """
    Determine if property is quantifiable or enumerated from class URI.

    Args:
        class_uri: ASHRAE 223P class URI

    Returns:
        "quantifiable", "enumerated", or None if class_uri is None

    Examples:
        >>> determine_property_type("http://data.ashrae.org/standard223#Temperature-Sensor")
        'quantifiable'
        >>> determine_property_type("http://data.ashrae.org/standard223#EnumeratedObservableProperty")
        'enumerated'
    """
    if not class_uri:
        return None

    class_str = str(class_uri)

    if "Enumerable" in class_str or "EnumeratedObservable" in class_str:
        return "enumerated"

    return "quantifiable"


def is_actuatable(class_uri: str | None, role_uri: str | None = None) -> bool:
    """
    Determine if property is actuatable using fallback strategy.

    Priority:
    1. Class hierarchy (canonical 223P) - check for "Actuatable" in class
    2. Role property (backup) - check for Role-Output
    3. Default to False if both missing

    Args:
        class_uri: ASHRAE 223P property class URI
        role_uri: Optional s223:hasRole URI

    Returns:
        True if actuatable (controllable), False if observable (read-only)

    Examples:
        >>> is_actuatable("http://data.ashrae.org/standard223#ActuatableProperty", None)
        True
        >>> is_actuatable(None, "http://data.ashrae.org/standard223#Role-Output")
        True
        >>> is_actuatable("http://data.ashrae.org/standard223#ObservableProperty", None)
        False
    """
    if class_uri and "Actuatable" in str(class_uri):
        return True

    if role_uri and str(role_uri) == "http://data.ashrae.org/standard223#Role-Output":
        return True

    return False


def format_template_label(template_name: str) -> str:
    """
    Convert template name to human-readable label.

    Args:
        template_name: Template name (e.g., "vav-reheat", "static-pressure")

    Returns:
        Formatted label (e.g., "VAV Reheat", "Static Pressure")

    Examples:
        >>> format_template_label("vav-reheat")
        'VAV Reheat'
        >>> format_template_label("static-pressure")
        'Static Pressure'
    """
    return template_name.replace("-", " ").title()
