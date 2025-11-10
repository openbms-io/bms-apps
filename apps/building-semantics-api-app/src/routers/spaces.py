"""ASHRAE 223P Spaces router."""
from fastapi import APIRouter, HTTPException, Query

from ..dto.spaces_dto import CreateSpaceRequestDTO, SpaceInstanceDTO

router = APIRouter(
    prefix="/api/v1/223p/spaces",
    tags=["ASHRAE 223P Spaces"],
)


@router.get(
    "",
    response_model=list[SpaceInstanceDTO],
    summary="List all space instances for project",
    description="Returns all space instances created for the specified project.",
    responses={
        200: {
            "description": "List of space instances",
            "content": {
                "application/json": {
                    "example": [
                        {
                            "id": "urn:bms:PhysicalSpace:room-101",
                            "spaceTypeId": "urn:223p:Office",
                            "label": "Room 101 - John's Office",
                            "createdAt": "2025-01-01T00:00:00Z",
                        }
                    ]
                }
            },
        },
        500: {"description": "Internal server error"},
    },
)
async def list_spaces(
    project_id: str = Query(..., alias="projectId", description="Project identifier")
) -> list[SpaceInstanceDTO]:
    """
    List all space instances for project.

    Args:
        project_id: Project identifier

    Returns:
        List of SpaceInstanceDTO

    Raises:
        HTTPException: When operation fails
    """
    raise HTTPException(status_code=501, detail="Not implemented")


@router.post(
    "",
    response_model=SpaceInstanceDTO,
    status_code=201,
    summary="Create new space instance",
    description="Creates a new space instance with specified type and label.",
    responses={
        201: {
            "description": "Space created successfully",
            "content": {
                "application/json": {
                    "example": {
                        "id": "urn:bms:PhysicalSpace:room-101",
                        "spaceTypeId": "urn:223p:Office",
                        "label": "Room 101 - John's Office",
                        "createdAt": "2025-01-01T00:00:00Z",
                    }
                }
            },
        },
        422: {"description": "Validation error"},
        500: {"description": "Internal server error"},
    },
)
async def create_space(request: CreateSpaceRequestDTO) -> SpaceInstanceDTO:
    """
    Create new space instance.

    Args:
        request: CreateSpaceRequestDTO with projectId, spaceTypeId, and label

    Returns:
        Created SpaceInstanceDTO

    Raises:
        HTTPException: When operation fails
    """
    raise HTTPException(status_code=501, detail="Not implemented")
