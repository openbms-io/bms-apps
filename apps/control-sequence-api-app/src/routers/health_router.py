"""Health Router for API health check endpoint."""

from fastapi import APIRouter, Depends

from src.adapters.fmu_adapter import FmuAdapter
from src.dto.health_dto import HealthResponse

router = APIRouter(prefix="/api/v1", tags=["Health"])

SERVICE_NAME = "control-sequence-api"
SERVICE_VERSION = "0.1.0"


def get_fmu_adapter() -> FmuAdapter:
    return FmuAdapter.get_instance()


@router.get("/health", response_model=HealthResponse)
async def health_check(
    adapter: FmuAdapter = Depends(get_fmu_adapter),
) -> HealthResponse:
    """Check API health status and active FMU instance count.

    Returns the current health status of the API along with metrics
    about active FMU instances being managed.
    """
    return HealthResponse(
        status="healthy",
        service=SERVICE_NAME,
        version=SERVICE_VERSION,
        active_instances=len(adapter.list_instance_ids()),
    )
