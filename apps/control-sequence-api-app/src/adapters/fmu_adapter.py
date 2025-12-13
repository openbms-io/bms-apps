"""FMU Adapter singleton for managing FMU instances."""

import uuid
from dataclasses import dataclass

from src.adapters.exceptions import FmuInstanceNotFoundError
from src.adapters.fmu_data.base import FMUDataProtocol
from src.adapters.fmu_lifecycle import FmuLifecycleManager
from src.adapters.sequence_type import SequenceType
from src.adapters.fmu_instance import FmuInstanceState


@dataclass(frozen=True, slots=True)
class UpsertResult:
    """Result of upsert_fmu_instance operation."""

    instance_id: str
    is_created: bool


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
        return self._create_fmu_instance(sequence_type, fmu_data)

    def _create_fmu_instance(
        self,
        sequence_type: SequenceType,
        fmu_data: FMUDataProtocol,
        instance_id: str | None = None,
    ) -> str:
        """Internal: Create FMU instance with optional caller-provided instance_id."""
        if instance_id is None:
            instance_id = str(uuid.uuid4())
        lifecycle = FmuLifecycleManager(sequence_type, fmu_data)
        self._lifecycle_managers[instance_id] = lifecycle
        return instance_id

    async def upsert_fmu_instance(
        self,
        sequence_type: SequenceType,
        fmu_data: FMUDataProtocol,
        instance_id: str,
    ) -> UpsertResult:
        """Create or recreate FMU instance.

        If instance_id exists, terminates and recreates it.
        If instance_id doesn't exist, creates new instance.

        Returns UpsertResult with instance_id and is_created flag.

        Upsert semantics: FMPy has no native reset, so recreation is
        required for parameter changes.
        """
        is_created = instance_id not in self._lifecycle_managers

        if not is_created:
            await self._lifecycle_managers[instance_id].terminate()
            del self._lifecycle_managers[instance_id]

        self._create_fmu_instance(sequence_type, fmu_data, instance_id)
        return UpsertResult(instance_id=instance_id, is_created=is_created)

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
        step_size: float,
        sequence_type: SequenceType,
    ) -> dict[str, float | bool | int]:
        """Execute simulation step, creating FMU instance lazily if needed."""
        if instance_id not in self._lifecycle_managers:
            self._create_fmu_instance(sequence_type, fmu_data, instance_id)

        lifecycle = self._lifecycle_managers[instance_id]
        return await lifecycle.step(fmu_data, step_size)

    async def delete_fmu_instance(self, instance_id: str) -> bool:
        """Delete FMU instance (idempotent). Returns True if instance existed."""
        if instance_id not in self._lifecycle_managers:
            return False
        lifecycle = self._lifecycle_managers[instance_id]
        await lifecycle.terminate()
        del self._lifecycle_managers[instance_id]
        return True

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
