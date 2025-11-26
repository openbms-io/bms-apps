"""BACnet References router."""

from fastapi import APIRouter, Depends, HTTPException, status
from loguru import logger

from ..controllers.bacnet_references_controller import BACnetReferencesController
from ..dto.bacnet_references_dto import (
    BACnetReferenceDTO,
    CreateBACnetReferenceRequestDTO,
    EnrichedBACnetReferenceDTO,
)
from ..models.exceptions import ValidationException

router = APIRouter(
    prefix="/api/v1/projects/{project_id}/bacnet-references",
    tags=["BACnet References"],
)


def get_bacnet_references_controller() -> BACnetReferencesController:
    """Dependency injection for BACnetReferencesController."""
    return BACnetReferencesController()


@router.put(
    "/{bacnet_point_id}",
    response_model=BACnetReferenceDTO,
    summary="Create or update BACnet reference with SHACL validation",
    description=(
        "Map a BACnet point to a specific property URN from a system instance. "
        "If reference already exists, it will be updated. "
        "Validates against ASHRAE 223P SHACL constraints before saving."
    ),
    responses={
        400: {
            "description": "SHACL validation failed or invalid property",
            "content": {
                "application/json": {
                    "examples": {
                        "validation_error": {
                            "summary": "SHACL validation error",
                            "value": {
                                "error": {
                                    "validationType": "SHACL",
                                    "isValid": False,
                                    "errors": ["Property type incompatible with BACnet object type"],
                                    "warnings": []
                                }
                            }
                        },
                        "property_not_found": {
                            "summary": "Property not found",
                            "value": {"error": "Property validation failed: Property not found in project"}
                        }
                    }
                }
            }
        }
    }
)
async def create_or_update_reference(
    project_id: str,
    bacnet_point_id: str,
    request: CreateBACnetReferenceRequestDTO,
    controller: BACnetReferencesController = Depends(get_bacnet_references_controller),
) -> BACnetReferenceDTO:
    """
    Create or update BACnet point → property URN reference with SHACL validation.

    Args:
        project_id: Unique project identifier
        bacnet_point_id: BACnet point identifier (e.g., "device123.analog-input-1")
        request: CreateBACnetReferenceRequestDTO with property_uri

    Returns:
        BACnetReferenceDTO with bacnet_point_id and property_uri

    Raises:
        HTTPException 400: If SHACL validation fails or property not found
        HTTPException 500: If reference creation fails
    """
    try:
        result = await controller.create_or_update_reference(
            project_id=project_id,
            bacnet_point_id=bacnet_point_id,
            property_uri=request.property_uri,
            device_identifier=request.device_identifier,
            object_identifier=request.object_identifier,
            external_identifier=request.external_identifier,
        )
        return BACnetReferenceDTO(**result)

    except ValidationException as e:
        logger.warning(f"SHACL validation failed: {e.errors}")
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail={
                "validationType": "SHACL",
                "isValid": False,
                "errors": e.errors,
                "warnings": e.warnings,
            },
        )
    except ValueError as e:
        logger.warning(f"Invalid property URI: {e}")
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"Property validation failed: {str(e)}",
        )
    except Exception as e:
        logger.error(f"Failed to create BACnet reference: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to create BACnet reference: {str(e)}",
        )


@router.get(
    "",
    response_model=list[EnrichedBACnetReferenceDTO],
    summary="List all BACnet references for project",
    description=(
        "Retrieve all BACnet references for a project with complete system → device → property chains. "
        "Returns enriched data including labels and template IDs for UI display."
    ),
)
async def list_references(
    project_id: str,
    controller: BACnetReferencesController = Depends(get_bacnet_references_controller),
) -> list[EnrichedBACnetReferenceDTO]:
    """
    Get all BACnet references for a project with enriched data.

    Args:
        project_id: Unique project identifier

    Returns:
        List of EnrichedBACnetReferenceDTO with complete chains

    Raises:
        HTTPException 500: If retrieval fails
    """
    try:
        results = await controller.get_all_references(project_id)
        return [EnrichedBACnetReferenceDTO(**result) for result in results]

    except Exception as e:
        logger.error(f"Failed to list BACnet references: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to list BACnet references: {str(e)}",
        )


@router.get(
    "/{bacnet_point_id}",
    response_model=EnrichedBACnetReferenceDTO,
    summary="Get BACnet reference with enriched data",
    description=(
        "Retrieve BACnet reference with complete system → device → property chain. "
        "Returns enriched data including labels and template IDs for UI display."
    ),
)
async def get_reference(
    project_id: str,
    bacnet_point_id: str,
    controller: BACnetReferencesController = Depends(get_bacnet_references_controller),
) -> EnrichedBACnetReferenceDTO:
    """
    Get BACnet reference with enriched data.

    Args:
        project_id: Unique project identifier
        bacnet_point_id: BACnet point identifier

    Returns:
        EnrichedBACnetReferenceDTO with complete chain

    Raises:
        HTTPException 404: If reference not found
        HTTPException 500: If retrieval fails
    """
    try:
        result = await controller.get_reference(project_id, bacnet_point_id)

        if result is None:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail=f"BACnet reference not found: {bacnet_point_id}",
            )

        return EnrichedBACnetReferenceDTO(**result)

    except HTTPException:
        raise
    except Exception as e:
        logger.error(f"Failed to get BACnet reference: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to get BACnet reference: {str(e)}",
        )


@router.delete(
    "/{bacnet_point_id}",
    status_code=status.HTTP_204_NO_CONTENT,
    summary="Delete BACnet reference",
    description="Remove BACnet point → property URN mapping.",
)
async def delete_reference(
    project_id: str,
    bacnet_point_id: str,
    controller: BACnetReferencesController = Depends(get_bacnet_references_controller),
) -> None:
    """
    Delete BACnet reference.

    Args:
        project_id: Unique project identifier
        bacnet_point_id: BACnet point identifier

    Raises:
        HTTPException 404: If reference not found
        HTTPException 500: If deletion fails
    """
    try:
        result = await controller.delete_reference(project_id, bacnet_point_id)

        if not result:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail=f"BACnet reference not found: {bacnet_point_id}",
            )

    except HTTPException:
        raise
    except Exception as e:
        logger.error(f"Failed to delete BACnet reference: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to delete BACnet reference: {str(e)}",
        )
