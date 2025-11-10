"""ASHRAE 223P Templates router."""
from fastapi import APIRouter, HTTPException

from ..dto.templates_dto import TemplatesResponseDTO

router = APIRouter(
    prefix="/api/v1/223p/templates",
    tags=["ASHRAE 223P Templates"],
)


@router.get(
    "",
    response_model=TemplatesResponseDTO,
    summary="Get all ASHRAE 223P templates with hierarchical structure",
    description=(
        "Retrieve complete template hierarchy with systems, devices, properties, "
        "and space types with all relationships embedded. "
        "No separate lookups needed - everything in one response."
    ),
    responses={
        200: {
            "description": "Complete template structure",
            "content": {
                "application/json": {
                    "example": {
                        "systems": [
                            {
                                "id": "urn:223p:VAVReheatTerminalUnit",
                                "label": "VAV with Reheat",
                                "description": (
                                    "Variable air volume terminal unit "
                                    "with electric reheat coil"
                                ),
                                "devices": [
                                    {
                                        "id": "urn:223p:Damper",
                                        "label": "Damper",
                                        "description": "Air damper actuator",
                                        "properties": [
                                            {
                                                "id": "urn:223p:DamperPosition",
                                                "label": "Damper Position",
                                                "propertyType": "quantifiable",
                                                "description": (
                                                    "Damper actuator position "
                                                    "(0-100%)"
                                                ),
                                            }
                                        ],
                                    }
                                ],
                            }
                        ],
                        "spaceTypes": [
                            {
                                "id": "urn:223p:Office",
                                "label": "Office",
                                "description": "Individual office space",
                            }
                        ],
                    }
                }
            },
        },
        500: {"description": "Internal server error"},
    },
)
async def get_templates() -> TemplatesResponseDTO:
    """
    Get all ASHRAE 223P templates with hierarchical structure.

    Returns complete template hierarchy with systems, devices, properties,
    and space types with all relationships embedded.

    Returns:
        TemplatesResponseDTO with nested structure

    Raises:
        HTTPException: When operation fails
    """
    raise HTTPException(status_code=501, detail="Not implemented")
