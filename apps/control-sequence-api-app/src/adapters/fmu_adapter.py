"""FMU Adapter singleton for managing FMU instances."""

import uuid

from src.adapters.exceptions import FmuInstanceNotFoundError
from src.adapters.fmu_data.base import FMUDataProtocol
from src.adapters.fmu_lifecycle import FmuLifecycleManager
from src.adapters.sequence_type import SequenceType
from src.adapters.fmu_instance import FmuInstanceState


class FmuAdapter:
    """Singleton adapter for managing FMU instances.

    Thread Safety: get_instance() must be called during server startup
    (in FastAPI lifespan) before accepting concurrent requests. This ensures
    the singleton is created in a single-threaded context, avoiding race conditions.
    """

    _singleton: "FmuAdapter | None" = None

    def __init__(self) -> None:
        self._lifecycle_managers: dict[str, FmuLifecycleManager] = {}

    @classmethod
    def get_instance(cls) -> "FmuAdapter":
        """Get the singleton FmuAdapter instance.

        Must be called during server startup (lifespan) to ensure thread-safe
        initialization before concurrent requests arrive.
        """
        if cls._singleton is None:
            cls._singleton = cls()
        return cls._singleton

    @classmethod
    def reset_singleton(cls) -> None:
        cls._singleton = None

    def create_fmu_instance(
        self,
        sequence_type: SequenceType,
        fmu_data: FMUDataProtocol,
    ) -> str:
        """Create a new FMU instance.

        Note: This method performs blocking I/O (FMU loading/instantiation).
        Typically completes in <100ms. Use asyncio.to_thread() if called
        from async context where blocking is unacceptable.
        """
        lifecycle = FmuLifecycleManager(sequence_type, fmu_data)
        instance_id = str(uuid.uuid4())
        self._lifecycle_managers[instance_id] = lifecycle
        return instance_id

    async def update_fmu_instance(
        self,
        instance_id: str,
        fmu_data: FMUDataProtocol,
    ) -> None:
        lifecycle = self._get_lifecycle(instance_id)
        await lifecycle.set_inputs(fmu_data)

    async def step(
        self,
        instance_id: str,
        fmu_data: FMUDataProtocol,
        step_size: float = 1.0,
    ) -> dict[str, float | bool | int]:
        lifecycle = self._get_lifecycle(instance_id)
        return await lifecycle.step(fmu_data, step_size)

    async def delete_fmu_instance(self, instance_id: str) -> None:
        lifecycle = self._get_lifecycle(instance_id)
        await lifecycle.terminate()
        del self._lifecycle_managers[instance_id]

    def has_instance(self, instance_id: str) -> bool:
        return instance_id in self._lifecycle_managers

    def list_instance_ids(self) -> list[str]:
        return list(self._lifecycle_managers.keys())

    def get_state(self, instance_id: str) -> FmuInstanceState:
        return self._get_lifecycle(instance_id).state

    def get_sequence_type(self, instance_id: str) -> SequenceType:
        return self._get_lifecycle(instance_id).sequence_type

    def get_current_time(self, instance_id: str) -> float:
        return self._get_lifecycle(instance_id).current_time

    def _get_lifecycle(self, instance_id: str) -> FmuLifecycleManager:
        if instance_id not in self._lifecycle_managers:
            raise FmuInstanceNotFoundError(instance_id)
        return self._lifecycle_managers[instance_id]
