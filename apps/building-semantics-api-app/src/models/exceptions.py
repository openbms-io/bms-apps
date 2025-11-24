"""Domain exceptions for mappings operations."""


class ValidationException(Exception):
    """SHACL validation failed."""

    def __init__(self, errors: list[str], warnings: list[str] | None = None):
        self.errors = errors
        self.warnings = warnings or []
        super().__init__(f"SHACL validation failed: {errors}")
