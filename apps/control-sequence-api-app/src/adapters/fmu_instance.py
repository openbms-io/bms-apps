from dataclasses import dataclass, field
from enum import StrEnum
from typing import TYPE_CHECKING

from src.adapters.sequence_type import SequenceType

if TYPE_CHECKING:
    from fmpy.fmi2 import FMU2Slave
    from fmpy.model_description import ModelDescription


class FmuInstanceState(StrEnum):
    """State of an FMU instance lifecycle."""

    CREATED = "created"
    INITIALIZED = "initialized"
    RUNNING = "running"
    TERMINATED = "terminated"


@dataclass
class FmuInstance:
    """Represents a single FMU instance with its state and resources."""

    fmu: "FMU2Slave"
    model_description: "ModelDescription"
    unzip_dir: str
    current_time: float
    sequence_type: SequenceType
    value_refs: dict[str, int] = field(default_factory=dict)
    state: FmuInstanceState = FmuInstanceState.INITIALIZED
