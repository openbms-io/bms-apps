"""ASHRAE 223P Mappings router."""
from fastapi import APIRouter, Query

from ..dto.mappings_dto import MappingsResponseDTO, SaveMappingsRequestDTO

router = APIRouter(
    prefix="/api/v1/223p/mappings",
    tags=["ASHRAE 223P Mappings"],
)

# In-memory storage for mappings data (Phase 1 mock behavior)
# Dictionary keyed by projectId for multi-project support
_MAPPINGS_STORE: dict[str, MappingsResponseDTO] = {}


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
                                "spaceId": "urn:bms:PhysicalSpace:room-101",
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
    return _MAPPINGS_STORE.get(
        project_id,
        MappingsResponseDTO(projectId=project_id, mappings={})
    )


@router.post(
    "",
    response_model=MappingsResponseDTO,
    summary="Bulk save/replace all semantic mappings",
    description=(
        "Replaces all mappings for project with provided mappings. "
        "This is a complete replacement operation, not incremental update."
    ),
    responses={
        200: {
            "description": "Mappings saved successfully",
            "content": {
                "application/json": {
                    "example": {
                        "projectId": "proj-123",
                        "mappings": {
                            "device-1:ai-1": {
                                "equipmentTypeId": "urn:223p:VAVReheatTerminalUnit",
                                "deviceTypeId": "urn:223p:Damper",
                                "propertyId": "urn:223p:DamperPosition",
                                "spaceId": "urn:bms:PhysicalSpace:room-101",
                            }
                        },
                    }
                }
            },
        },
        422: {"description": "Validation error"},
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
    response = MappingsResponseDTO(
        projectId=request.project_id,
        mappings=request.mappings
    )
    _MAPPINGS_STORE[request.project_id] = response
    return response
