class FmuInstanceNotFoundError(Exception):
    """Raised when instance_id does not exist."""

    def __init__(self, instance_id: str):
        self.instance_id = instance_id
        super().__init__(f"FMU instance not found: {instance_id}")


class FmuValidationError(Exception):
    """Raised when input validation fails."""

    def __init__(self, message: str, missing_inputs: list[str] | None = None):
        self.missing_inputs = missing_inputs or []
        super().__init__(message)


class FmuExecutionError(Exception):
    """Raised when FMU step fails."""

    def __init__(self, message: str, instance_id: str | None = None):
        self.instance_id = instance_id
        super().__init__(message)


class FmuInitializationError(Exception):
    """Raised when FMU initialization fails."""

    def __init__(self, message: str, sequence_type: str | None = None):
        self.sequence_type = sequence_type
        super().__init__(message)
