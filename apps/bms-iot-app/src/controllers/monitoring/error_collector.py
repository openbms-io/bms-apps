"""Error collection for monitoring operations."""

from typing import List, Dict, Any
from src.utils.logger import logger


class ErrorCollector:
    """Collects errors during monitoring and raises summary at end."""

    def __init__(self):
        self.errors: List[Dict[str, Any]] = []

    def collect(self, context: str, error: Exception, **metadata):
        """Collect an error with context and metadata.

        Args:
            context: Description of where error occurred
            error: The exception that occurred
            **metadata: Additional context (controller_id, point_id, etc.)
        """
        error_entry = {
            "context": context,
            "error": str(error),
            "error_type": type(error).__name__,
            **metadata,
        }
        self.errors.append(error_entry)
        logger.debug(f"Collected error: {context} - {error}")

    def has_errors(self) -> bool:
        """Check if any errors were collected."""
        return len(self.errors) > 0

    def get_error_count(self) -> int:
        """Get total number of errors collected."""
        return len(self.errors)

    def raise_if_errors(self):
        """Raise summary exception if any errors were collected."""
        if self.errors:
            summary = f"Monitoring completed with {len(self.errors)} failures"
            first_error = self.errors[0]
            logger.error(
                f"{summary}. First error: {first_error['context']} - {first_error['error']}"
            )
            logger.debug(f"All collected errors: {self.errors}")
            raise Exception(summary)
