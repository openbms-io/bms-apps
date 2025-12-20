"""Validation endpoint DTOs for SHACL validation stub."""

from typing import Any

from pydantic import BaseModel, Field


class ValidationRequest(BaseModel):
    """Request model for graph validation.

    Accepts a generic graph structure. Since this is a stub endpoint,
    detailed validation of request structure is not required.
    """

    graph: dict[str, Any] = Field(description="Graph data containing nodes and edges")


class ValidationResponse(BaseModel):
    """Response model for validation result.

    Stub for future SHACL implementation - always returns valid=True.
    """

    valid: bool = Field(description="Whether the graph passed validation")
    errors: list[str] = Field(
        default_factory=list,
        description="List of validation errors (empty for stub)",
    )
    message: str = Field(description="Human-readable validation message")
