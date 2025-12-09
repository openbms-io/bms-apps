"""SQLAlchemy model for control sequence instance persistence with history."""

from datetime import datetime
from enum import StrEnum
from typing import Any

from sqlalchemy import Boolean, DateTime, Index, String, func
from sqlalchemy.dialects.sqlite import JSON
from sqlalchemy.orm import Mapped, mapped_column, validates

from src.adapters.database_adapter import Base
from src.dto.reheat_dto import ReheatParameters


class SequenceType(StrEnum):
    """Supported control sequence types."""

    G36_VAV_REHEAT = "g36_vav_reheat"
    G36_VAV_COOLING_ONLY = "g36_vav_cooling_only"
    G36_AHU = "g36_ahu"
    CUSTOM = "custom"


class ControlSequenceInstanceModel(Base):
    """Database model for storing control sequence instance parameters.

    Maintains parameter history - each update creates a new record with is_active=True
    and sets previous record's is_active=False.

    Query active instance: WHERE instance_id = ? AND is_active = True
    Query history: WHERE instance_id = ? ORDER BY created_at DESC
    """

    __tablename__ = "control_sequence_instances"
    __table_args__ = (
        Index(
            "ix_unique_active_instance",
            "instance_id",
            unique=True,
            sqlite_where="is_active = 1",
        ),
    )

    id: Mapped[str] = mapped_column(String(36), primary_key=True)
    instance_id: Mapped[str] = mapped_column(String(255), nullable=False, index=True)
    sequence_type: Mapped[str] = mapped_column(String(50), nullable=False)
    parameters_json: Mapped[dict[str, Any]] = mapped_column(JSON, nullable=False)
    is_active: Mapped[bool] = mapped_column(Boolean, nullable=False, default=True)
    created_at: Mapped[datetime] = mapped_column(
        DateTime, server_default=func.now(), nullable=False
    )
    updated_at: Mapped[datetime] = mapped_column(
        DateTime, server_default=func.now(), onupdate=func.now(), nullable=False
    )

    @validates("parameters_json")
    def validate_parameters(self, key: str, value: dict[str, Any]) -> dict[str, Any]:
        """Validate parameters match sequence_type schema before DB write."""
        seq_type = SequenceType(self.sequence_type)
        match seq_type:
            case SequenceType.G36_VAV_REHEAT:
                ReheatParameters.model_validate(value)
            case SequenceType.G36_VAV_COOLING_ONLY:
                pass  # TODO: Add VAVParameters validation when implemented
            case SequenceType.G36_AHU:
                pass  # TODO: Add AHUParameters validation when implemented
            case SequenceType.CUSTOM:
                pass  # Custom sequences skip validation
        return value
