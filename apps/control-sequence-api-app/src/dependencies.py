"""FastAPI dependency injection providers."""

from fastapi import Depends

from src.adapters.fmu_adapter import FmuAdapter
from src.controllers.vav_reheat_controller import VavReheatController
from src.repositories.reheat_repository import ReheatRepository


def get_reheat_repository() -> ReheatRepository:
    return ReheatRepository()


def get_fmu_adapter() -> FmuAdapter:
    return FmuAdapter.get_instance()


def get_vav_reheat_controller(
    adapter: FmuAdapter = Depends(get_fmu_adapter),
    repository: ReheatRepository = Depends(get_reheat_repository),
) -> VavReheatController:
    return VavReheatController(adapter, repository)
