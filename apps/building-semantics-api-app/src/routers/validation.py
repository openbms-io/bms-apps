"""ASHRAE 223P Validation router."""
from fastapi import APIRouter

router = APIRouter(
    prefix="/api/223p/validate",
    tags=["ASHRAE 223P Validation"],
)

# TODO: Implementation later when validating models via API and not only during saving.
