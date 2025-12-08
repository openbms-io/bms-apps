"""Sequence type definitions."""

from enum import StrEnum


class SequenceType(StrEnum):
    """Supported G36 sequence types."""

    REHEAT = "reheat"
    VAV = "vav"
    AHU = "ahu"
