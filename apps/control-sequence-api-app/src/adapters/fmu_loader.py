"""FMU file loading utilities.

Handles lazy extraction and caching of FMU files.
"""

from typing import ClassVar

from fmpy import extract, read_model_description
from fmpy.model_description import ModelDescription

from src.adapters.exceptions import FmuInitializationError
from src.config.settings import get_settings


class FmuLoader:
    """Utility for loading and caching FMU files."""

    _cache: ClassVar[dict[str, tuple[ModelDescription, str]]] = {}

    @classmethod
    def load(cls, sequence_type: str) -> tuple[ModelDescription, str]:
        """Load FMU model description and extract to temp directory.

        Args:
            sequence_type: Type of sequence (e.g., "reheat", "vav", "ahu")

        Returns:
            Tuple of (ModelDescription, unzip_dir)

        Raises:
            FmuInitializationError: If FMU path not configured or file not found
        """
        if sequence_type in cls._cache:
            return cls._cache[sequence_type]

        settings = get_settings()
        fmu_path = settings.get_fmu_path(sequence_type)

        if fmu_path is None:
            raise FmuInitializationError(
                f"No FMU path configured for sequence type: {sequence_type}",
                sequence_type=sequence_type,
            )

        md = read_model_description(str(fmu_path))
        unzip_dir = extract(str(fmu_path))

        cls._cache[sequence_type] = (md, unzip_dir)
        return md, unzip_dir

    @classmethod
    def clear_cache(cls) -> None:
        """Clear the FMU cache (for testing)."""
        cls._cache.clear()

    @classmethod
    def build_value_refs(cls, md: ModelDescription) -> dict[str, int]:
        """Build mapping from variable name to value reference.

        Args:
            md: FMU model description

        Returns:
            Dict mapping variable name to its value reference
        """
        refs = {}
        for var in md.modelVariables:
            refs[var.name] = var.valueReference
        return refs
