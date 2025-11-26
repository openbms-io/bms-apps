"""Utility functions for label extraction and formatting."""

import re


def extract_label_from_uri(uri: str) -> str:
    """
    Extract human-readable label from URI.

    Converts URI slugs like "standby-hw-pump_db8e67fc" to "Standby Hw Pump".

    Args:
        uri: Entity URI (e.g., "urn:bms:standby-hw-pump_db8e67fc")

    Returns:
        Human-readable label (e.g., "Standby Hw Pump")
    """
    uri_str = str(uri)

    if ":" in uri_str:
        slug = uri_str.split(":")[-1]
    elif "/" in uri_str:
        slug = uri_str.split("/")[-1]
    else:
        slug = uri_str

    # Remove hash suffix (e.g., _db8e67fc)
    slug = re.sub(r'_[a-f0-9]{8}$', '', slug)

    # Replace hyphens and underscores with spaces
    slug = slug.replace('-', ' ').replace('_', ' ')

    # Capitalize each word
    return ' '.join(word.capitalize() for word in slug.split())


def get_label_or_extract(label_value: str | None, uri: str) -> str:
    """
    Return label if present, otherwise extract from URI.

    Args:
        label_value: Label from SPARQL query (may be None)
        uri: Entity URI to extract label from if label_value is missing

    Returns:
        Label string (either provided or extracted from URI)
    """
    if label_value is None:
        return extract_label_from_uri(uri)
    return label_value


def extract_label_from_uri_or_none(uri: str | None) -> str | None:
    """
    Extract label from URI, or return None if URI is None.

    Used for optional URI fields like quantity_kind, unit, medium.

    Args:
        uri: Optional entity URI

    Returns:
        Extracted label or None if URI is None
    """
    if uri is None:
        return None
    return extract_label_from_uri(uri)
