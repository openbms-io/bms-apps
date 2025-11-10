"""ASHRAE 223P Validation router."""
from fastapi import APIRouter

router = APIRouter(
    prefix="/api/223p/validate",
    tags=["ASHRAE 223P Validation"],
)

# Endpoints will be added in Story 2.4 (Phase 1)
