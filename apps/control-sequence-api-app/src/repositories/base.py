"""Base repository components for control sequence instance persistence."""

from dataclasses import dataclass
from typing import Generic, TypeVar
from uuid import uuid4

from pydantic import BaseModel
from sqlalchemy import select
from sqlalchemy.exc import IntegrityError

from src.adapters.database_adapter import get_session
from src.models.control_sequence_instance_model import ControlSequenceInstanceModel
from src.models.control_sequence_instance_model import SequenceType

TParams = TypeVar("TParams", bound=BaseModel)


@dataclass
class ControlSequenceInstanceData(Generic[TParams]):
    """Internal data wrapper for control sequence instance."""

    id: str
    instance_id: str
    parameters: TParams


class ControlSequenceInstanceRepository(Generic[TParams]):
    """Generic repository for control sequence instances.

    Uses composition - configured via constructor with sequence_type and parameters_model.
    Not intended for direct use - use typed wrappers like ReheatRepository.
    """

    def __init__(self, sequence_type: SequenceType, parameters_model: type[TParams]):
        self._sequence_type = sequence_type
        self._parameters_model = parameters_model

    def _to_data(self, record: ControlSequenceInstanceModel) -> ControlSequenceInstanceData[TParams]:
        return ControlSequenceInstanceData(
            id=record.id,
            instance_id=record.instance_id,
            parameters=self._parameters_model.model_validate(record.parameters_json),
        )

    async def get_active(self, instance_id: str) -> ControlSequenceInstanceData[TParams] | None:
        """Get active instance by instance_id."""
        async with get_session() as session:
            result = await session.execute(
                select(ControlSequenceInstanceModel).where(
                    ControlSequenceInstanceModel.instance_id == instance_id,
                    ControlSequenceInstanceModel.sequence_type == self._sequence_type,
                    ControlSequenceInstanceModel.is_active == True,  # noqa: E712
                )
            )
            record = result.scalar_one_or_none()
            if not record:
                return None
            return self._to_data(record)

    async def list_active(self) -> list[ControlSequenceInstanceData[TParams]]:
        """List all active instances."""
        async with get_session() as session:
            result = await session.execute(
                select(ControlSequenceInstanceModel).where(
                    ControlSequenceInstanceModel.sequence_type == self._sequence_type,
                    ControlSequenceInstanceModel.is_active == True,  # noqa: E712
                )
            )
            return [self._to_data(r) for r in result.scalars().all()]

    async def create(self, parameters: TParams) -> ControlSequenceInstanceData[TParams]:
        """Create new instance with auto-generated ID. Returns created instance."""
        instance_id = str(uuid4())
        return await self.save(instance_id, parameters)

    async def get_or_create(
        self, instance_id: str, parameters: TParams
    ) -> tuple[ControlSequenceInstanceData[TParams], bool]:
        """Get existing instance or create new one. Returns (instance, created).

        Handles race conditions where concurrent requests try to create the same instance.
        """
        existing = await self.get_active(instance_id)
        if existing:
            return existing, False

        try:
            created = await self.save(instance_id, parameters)
            return created, True
        except IntegrityError:
            existing = await self.get_active(instance_id)
            if existing:
                return existing, False
            raise

    async def save(self, instance_id: str, parameters: TParams) -> ControlSequenceInstanceData[TParams]:
        """Save/update instance. Deactivates existing, creates new record. Returns saved instance."""
        async with get_session() as session:
            existing = await session.execute(
                select(ControlSequenceInstanceModel).where(
                    ControlSequenceInstanceModel.instance_id == instance_id,
                    ControlSequenceInstanceModel.sequence_type == self._sequence_type,
                    ControlSequenceInstanceModel.is_active == True,  # noqa: E712
                )
            )
            existing_record = existing.scalar_one_or_none()
            if existing_record:
                existing_record.is_active = False
                session.add(existing_record)

            new_record = ControlSequenceInstanceModel(
                id=str(uuid4()),
                instance_id=instance_id,
                sequence_type=self._sequence_type,
                parameters_json=parameters.model_dump(),
                is_active=True,
            )
            session.add(new_record)
            await session.commit()
            return self._to_data(new_record)

    async def delete(self, instance_id: str) -> bool:
        """Soft delete by setting is_active=False. Returns True if found."""
        async with get_session() as session:
            result = await session.execute(
                select(ControlSequenceInstanceModel).where(
                    ControlSequenceInstanceModel.instance_id == instance_id,
                    ControlSequenceInstanceModel.sequence_type == self._sequence_type,
                    ControlSequenceInstanceModel.is_active == True,  # noqa: E712
                )
            )
            record = result.scalar_one_or_none()
            if not record:
                return False
            record.is_active = False
            session.add(record)
            await session.commit()
            return True
