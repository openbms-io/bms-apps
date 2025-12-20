"""Sequence type definitions."""

from enum import StrEnum


class SequenceType(StrEnum):
    """Supported G36 sequence types."""

    VAV_REHEAT = "vav-reheat"
    AHU = "ahu"
