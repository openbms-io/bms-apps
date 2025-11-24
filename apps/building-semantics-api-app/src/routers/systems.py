"""ASHRAE 223P System Instances router."""

from fastapi import APIRouter, Depends, HTTPException, Query, status
from loguru import logger

from ..controllers.devices_controller import DevicesController
from ..controllers.systems_controller import SystemsController
from ..dto.systems_dto import (
    CreateSystemRequestDTO,
    DeviceDTO,
    PropertyDTO,
    SystemInstanceDTO,
    SystemSummaryDTO,
)

router = APIRouter(
    prefix="/api/v1/projects/{project_id}/systems",
    tags=["ASHRAE 223P System Instances"],
)


def get_systems_controller() -> SystemsController:
    """Dependency injection for SystemsController."""
    return SystemsController()


def get_devices_controller() -> DevicesController:
    """Dependency injection for DevicesController."""
    return DevicesController()


@router.post(
    "",
    response_model=SystemInstanceDTO,
    status_code=status.HTTP_201_CREATED,
    summary="Create reusable system instance from template",
    description=(
        "Create a system instance from an ASHRAE 223P template using template.fill(). "
        "The system instance is reusable across multiple BACnet points. "
        "BuildingMOTIF auto-generates all URNs, user provides custom label only."
    ),
)
async def create_system(
    project_id: str,
    request: CreateSystemRequestDTO,
    controller: SystemsController = Depends(get_systems_controller),
) -> SystemInstanceDTO:
    """
    Create reusable system instance from ASHRAE 223P template.

    Args:
        project_id: Unique project identifier
        request: CreateSystemRequestDTO with template_id and label

    Returns:
        SystemInstanceDTO with system_uri, label, template_id, created

    Raises:
        HTTPException 404: If template not found
        HTTPException 500: If system creation fails
    """
    try:
        result = await controller.create_system(
            project_id=project_id,
            template_id=request.template_id,
            label=request.label,
        )
        return SystemInstanceDTO(**result)

    except KeyError as e:
        logger.warning(f"Template not found: {e}")
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail=f"Template not found: {str(e)}",
        )
    except Exception as e:
        logger.error(f"Failed to create system: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to create system: {str(e)}",
        )


@router.get(
    "",
    response_model=list[SystemSummaryDTO],
    summary="List all system instances in project",
    description="Retrieve all system instances for the specified project.",
)
async def list_systems(
    project_id: str,
    controller: SystemsController = Depends(get_systems_controller),
) -> list[SystemSummaryDTO]:
    """
    List all system instances in project.

    Args:
        project_id: Unique project identifier

    Returns:
        List of SystemSummaryDTO

    Raises:
        HTTPException 500: If listing fails
    """
    try:
        results = await controller.list_systems(project_id)
        return [SystemSummaryDTO(**result) for result in results]

    except Exception as e:
        logger.error(f"Failed to list systems: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to list systems: {str(e)}",
        )


@router.get(
    "/devices",
    response_model=list[DeviceDTO],
    summary="Get devices for system (cascading dropdown)",
    description=(
        "Get all devices within a system instance. "
        "Used for cascading dropdown: System → Device → Property. "
        "Supports arbitrary depth hierarchies (Equipment → Equipment → Device). "
        "Optionally filters by BACnet object type compatibility."
    ),
)
async def get_devices_for_system(
    project_id: str,
    system_uri: str = Query(..., alias="systemUri", description="System URI"),
    bacnet_object_type: str | None = Query(None, alias="bacnetObjectType", description="Optional BACnet object type for device filtering"),
    controller: DevicesController = Depends(get_devices_controller),
) -> list[DeviceDTO]:
    """
    Get devices for system instance (cascading dropdown).

    Args:
        project_id: Unique project identifier
        system_uri: System URI (query parameter)
        bacnet_object_type: Optional BACnet object type for filtering devices

    Returns:
        List of DeviceDTO

    Raises:
        HTTPException 500: If query fails
    """
    try:
        results = await controller.get_devices_for_system(
            project_id, system_uri, bacnet_object_type
        )
        return [DeviceDTO(**result) for result in results]

    except Exception as e:
        logger.error(f"Failed to get devices: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to get devices: {str(e)}",
        )


@router.get(
    "/properties",
    response_model=list[PropertyDTO],
    summary="Get properties for device (cascading dropdown + filtering)",
    description=(
        "Get all properties for a device within a system. "
        "Optionally filtered by BACnet object type for compatibility:\n"
        "- analog-input, binary-input → Observable only (is_actuatable: false)\n"
        "- analog-output, binary-output → Actuatable only (is_actuatable: true)\n"
        "- analog-value, binary-value → Both (no filter)"
    ),
)
async def get_properties_for_device(
    project_id: str,
    device_uri: str = Query(..., alias="deviceUri", description="Device URI"),
    bacnet_object_type: str | None = Query(
        None,
        alias="bacnetObjectType",
        description="BACnet object type for filtering (e.g., 'analog-input')",
    ),
    controller: DevicesController = Depends(get_devices_controller),
) -> list[PropertyDTO]:
    """
    Get properties for device (cascading dropdown + BACnet filtering).

    Args:
        project_id: Unique project identifier
        device_uri: Device URI (query parameter)
        bacnet_object_type: Optional BACnet object type for filtering

    Returns:
        List of PropertyDTO (filtered by BACnet object type if provided)

    Raises:
        HTTPException 500: If query fails
    """
    try:
        results = await controller.get_properties_for_device(
            project_id, device_uri, bacnet_object_type
        )
        properties = []
        for result in results:
            property_uri = result["property_uri"]
            label = result["label"]
            is_actuatable = result["is_actuatable"]

            # Type narrowing: these fields are guaranteed to be the correct types from the model
            assert isinstance(property_uri, str)
            assert isinstance(label, str)
            assert isinstance(is_actuatable, bool)

            class_uri_val = result.get("class_uri")
            property_type_val = result.get("property_type")
            quantity_kind_val = result.get("quantity_kind")
            unit_val = result.get("unit")
            medium_val = result.get("medium")
            enumeration_kind_val = result.get("enumeration_kind")

            properties.append(PropertyDTO(
                propertyUri=property_uri,
                label=label,
                isActuatable=is_actuatable,
                classUri=class_uri_val if isinstance(class_uri_val, str) else None,
                propertyType=property_type_val if isinstance(property_type_val, str) else None,  # type: ignore
                quantityKind=quantity_kind_val if isinstance(quantity_kind_val, str) else None,
                unit=unit_val if isinstance(unit_val, str) else None,
                medium=medium_val if isinstance(medium_val, str) else None,
                enumerationKind=enumeration_kind_val if isinstance(enumeration_kind_val, str) else None,
            ))

        return properties

    except Exception as e:
        logger.error(f"Failed to get properties: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to get properties: {str(e)}",
        )


@router.get(
    "/{system_id:path}",
    response_model=SystemInstanceDTO,
    summary="Get system instance details",
    description="Retrieve detailed information about a specific system instance.",
)
async def get_system(
    project_id: str,
    system_id: str,
    controller: SystemsController = Depends(get_systems_controller),
) -> SystemInstanceDTO:
    """
    Get system instance details.

    Args:
        project_id: Unique project identifier
        system_id: System URI

    Returns:
        SystemInstanceDTO

    Raises:
        HTTPException 404: If system not found
        HTTPException 500: If retrieval fails
    """
    try:
        result = await controller.get_system(project_id, system_id)

        if result is None:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail=f"System not found: {system_id}",
            )

        return SystemInstanceDTO(**result)

    except HTTPException:
        raise
    except Exception as e:
        logger.error(f"Failed to get system: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to get system: {str(e)}",
        )


@router.delete(
    "/{system_id:path}",
    status_code=status.HTTP_204_NO_CONTENT,
    summary="Delete system instance",
    description="Delete a system instance from the project.",
)
async def delete_system(
    project_id: str,
    system_id: str,
    controller: SystemsController = Depends(get_systems_controller),
) -> None:
    """
    Delete system instance.

    Args:
        project_id: Unique project identifier
        system_id: System URI

    Raises:
        HTTPException 404: If system not found
        HTTPException 500: If deletion fails
    """
    try:
        result = await controller.delete_system(project_id, system_id)

        if not result:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail=f"System not found: {system_id}",
            )

    except HTTPException:
        raise
    except Exception as e:
        logger.error(f"Failed to delete system: {e}")
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to delete system: {str(e)}",
        )
