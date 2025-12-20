"""Repository for G36 VAV Reheat control sequence instances."""

from src.models.control_sequence_instance_model import SequenceType
from src.models.reheat.parameters import ReheatParameters
from src.repositories.base import ControlSequenceInstanceData, ControlSequenceInstanceRepository

ReheatInstanceData = ControlSequenceInstanceData[ReheatParameters]


class ReheatRepository:
    """Repository for G36 VAV Reheat instances.

    Typed wrapper around ControlSequenceInstanceRepository that returns ReheatInstanceData.
    """

    def __init__(self) -> None:
        self._repo = ControlSequenceInstanceRepository(SequenceType.G36_VAV_REHEAT, ReheatParameters)

    async def get_active(self, instance_id: str) -> ReheatInstanceData | None:
        """Get active instance by instance_id."""
        return await self._repo.get_active(instance_id)

    async def list_active(self) -> list[ReheatInstanceData]:
        """List all active instances."""
        return await self._repo.list_active()

    async def create(self, parameters: ReheatParameters) -> ReheatInstanceData:
        """Create new instance with auto-generated ID. Returns created instance."""
        return await self._repo.create(parameters)

    async def get_or_create(
        self, instance_id: str, parameters: ReheatParameters
    ) -> tuple[ReheatInstanceData, bool]:
        """Get existing instance or create new one. Returns (instance, created)."""
        return await self._repo.get_or_create(instance_id, parameters)

    async def save(self, instance_id: str, parameters: ReheatParameters) -> ReheatInstanceData:
        """Save/update instance. Deactivates existing, creates new record. Returns saved instance."""
        return await self._repo.save(instance_id, parameters)

    async def delete(self, instance_id: str) -> bool:
        """Soft delete by setting is_active=False. Returns True if found."""
        return await self._repo.delete(instance_id)
