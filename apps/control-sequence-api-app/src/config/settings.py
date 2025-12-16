from functools import lru_cache
from pathlib import Path

from pydantic import Field
from pydantic_settings import BaseSettings, SettingsConfigDict

from src.adapters.sequence_type import SequenceType


class Settings(BaseSettings):
    model_config = SettingsConfigDict(env_file=".env", env_file_encoding="utf-8")

    api_host: str = "0.0.0.0"
    api_port: int = 8001
    debug: bool = True
    root_path: str = ""

    database_path: str = Field(
        default="apps/control-sequence-api-app/data/control-sequence.db",
        description="Path to SQLite database file for instance storage",
    )

    fmu_path_vav_reheat: str = Field(
        default="apps/control-sequence-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu",
        description="Path to VAV Reheat Terminal FMU file",
    )
    fmu_path_ahu: str | None = Field(
        default=None,
        description="Path to AHU FMU file",
    )

    cors_origins: list[str] = ["http://localhost:3000", "http://localhost:3003"]

    def get_fmu_path(self, sequence_type: SequenceType) -> Path | None:
        match sequence_type:
            case SequenceType.VAV_REHEAT:
                return Path(self.fmu_path_vav_reheat)
            case SequenceType.AHU:
                if self.fmu_path_ahu is None:
                    return None
                return Path(self.fmu_path_ahu)
            case _:
                return None


@lru_cache
def get_settings() -> Settings:
    return Settings()
