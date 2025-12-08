"""Validation Router for SHACL validation stub endpoint."""

from fastapi import APIRouter

from src.dto.validation_dto import ValidationRequest, ValidationResponse

router = APIRouter(prefix="/api/v1/g36", tags=["Validation"])

STUB_MESSAGE = (
    "Validation stub - always returns valid. "
    "Full SHACL validation planned for Epic 3."
)


@router.post("/validate", response_model=ValidationResponse)
async def validate_graph(request: ValidationRequest) -> ValidationResponse:
    """Validate a graph structure using SHACL shapes.

    **Stub for future SHACL implementation.**

    This endpoint currently returns valid=True for all inputs.
    Full SHACL-based graph validation will be implemented in Epic 3
    (Two-Level Validation) to validate:
    - Semantic correctness of G36 block wiring
    - Proper connections between node types
    - Required relationships and cardinalities

    Args:
        request: Graph data containing nodes and edges to validate

    Returns:
        ValidationResponse with valid=True and empty errors list
    """
    return ValidationResponse(
        valid=True,
        errors=[],
        message=STUB_MESSAGE,
    )
