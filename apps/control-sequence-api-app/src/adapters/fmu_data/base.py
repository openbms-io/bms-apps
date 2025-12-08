"""Base types for FMU data containers."""

from dataclasses import dataclass
from enum import StrEnum
from typing import Protocol

from pydantic import BaseModel


class FmuDataType(StrEnum):
    """FMU variable data types for setter/getter selection."""

    REAL = "real"
    BOOLEAN = "boolean"
    INTEGER = "integer"


@dataclass(frozen=True, slots=True)
class FmuVariable:
    """A single FMU variable ready to write to FMU."""

    name: str
    value: float | bool | int

    @property
    def data_type(self) -> FmuDataType:
        # bool must be checked before int because bool is a subclass of int
        if isinstance(self.value, bool):
            return FmuDataType.BOOLEAN
        if isinstance(self.value, int):
            return FmuDataType.INTEGER
        return FmuDataType.REAL


@dataclass(frozen=True, slots=True)
class OutputSpec:
    """Specification for an FMU output variable."""

    name: str
    data_type: FmuDataType


class FMUDataProtocol(Protocol):
    """Protocol for FMU data containers."""

    @property
    def configuration_variables(self) -> list[FmuVariable]:
        """Configuration variables applied once at instance creation."""
        ...

    @property
    def input_variables(self) -> list[FmuVariable]:
        """Input variables written to FMU each step."""
        ...

    @staticmethod
    def output_variable_specs() -> list[OutputSpec]:
        """Output variable names and types to read from FMU."""
        ...

    @staticmethod
    def calculated_parameter_specs() -> list[OutputSpec]:
        """Calculated parameter specs to read from FMU (read-only after init)."""
        ...

    @staticmethod
    def create_outputs(values: dict[str, float | bool | int]) -> BaseModel:
        """Create output DTO from FMU values."""
        ...

    @staticmethod
    def create_calculated_parameters(values: dict[str, float | bool | int]) -> BaseModel:
        """Create calculated parameters DTO from FMU values."""
        ...

    @staticmethod
    def required_input_names() -> list[str]:
        """Required FMU input variable names."""
        ...
