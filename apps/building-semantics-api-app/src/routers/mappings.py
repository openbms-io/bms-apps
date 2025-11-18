"""ASHRAE 223P Mappings router."""
from fastapi import APIRouter, Query

from ..controllers.mappings_controller import MappingsController
from ..dto.mappings_dto import MappingsResponseDTO, SaveMappingsRequestDTO

router = APIRouter(
    prefix="/api/v1/223p/mappings",
    tags=["ASHRAE 223P Mappings"],
)


@router.get(
    "",
    response_model=MappingsResponseDTO,
    summary="Get all semantic mappings for project",
    description="Returns all semantic mappings as dictionary keyed by BACnet point ID.",
    responses={
        200: {
            "description": "All mappings for project",
            "content": {
                "application/json": {
                    "example": {
                        "projectId": "proj-123",
                        "mappings": {
                            "device-1:ai-1": {
                                "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit",
                                "deviceTypeId": "urn:223p:Damper",
                                "propertyId": "urn:223p:DamperPosition",
                                "physicalSpaceId": "urn:bms:PhysicalSpace:room-101",
                                "domainSpaceIds": ["urn:bms:Zone:hvac-1"],
                            }
                        },
                    }
                }
            },
        },
        500: {"description": "Internal server error"},
    },
)
async def get_mappings(
    project_id: str = Query(..., alias="projectId", description="Project identifier")
) -> MappingsResponseDTO:
    """
    Get all semantic mappings for project.

    Args:
        project_id: Project identifier

    Returns:
        MappingsResponseDTO with all mappings keyed by point ID

    Raises:
        HTTPException: When operation fails
    """
    controller = MappingsController()
    return await controller.get_mappings(project_id)


@router.post(
    "",
    response_model=MappingsResponseDTO,
    status_code=201,
    summary="Bulk save/replace all semantic mappings with SHACL validation",
    description=(
        "Replaces all mappings for project with provided mappings after validating against ASHRAE 223P SHACL constraints. "
        "This is a complete replacement operation, not incremental update. "
        "If any mapping fails SHACL validation, the entire operation is rejected (atomic transaction)."
    ),
    responses={
        201: {
            "description": "Mappings validated and saved successfully",
            "content": {
                "application/json": {
                    "example": {
                        "projectId": "proj-123",
                        "mappings": {
                            "device-1:ai-1": {
                                "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit",
                                "deviceTypeId": "urn:223p:Damper",
                                "propertyId": "urn:223p:DamperPosition",
                                "physicalSpaceId": "urn:bms:PhysicalSpace:room-101",
                                "domainSpaceIds": ["urn:bms:Zone:hvac-1"],
                            }
                        },
                    }
                }
            },
        },
        400: {
            "description": "SHACL validation failed - mappings do not comply with ASHRAE 223P constraints",
            "content": {
                "application/json": {
                    "example": {
                        "detail": {
                            "validationType": "SHACL",
                            "isValid": False,
                            "errors": [
                                "Equipment type 'invalid-type' not found in ASHRAE 223P ontology",
                                "Equipment must have at least one s223:contains relationship",
                            ],
                            "warnings": [],
                        }
                    }
                }
            },
        },
        422: {"description": "Request validation error (malformed request body)"},
        500: {"description": "Internal server error"},
    },
)
async def save_mappings(request: SaveMappingsRequestDTO) -> MappingsResponseDTO:
    """
    Bulk save/replace all mappings for project.

    Complete replacement operation - all existing mappings are replaced
    with the provided mappings.

    Args:
        request: SaveMappingsRequestDTO with projectId and mappings

    Returns:
        MappingsResponseDTO with saved mappings

    Raises:
        HTTPException: When operation fails
    """
    controller = MappingsController()
    return await controller.save_mappings(request)
