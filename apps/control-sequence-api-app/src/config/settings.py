from functools import lru_cache
from pathlib import Path

from pydantic import Field
from pydantic_settings import BaseSettings, SettingsConfigDict


class Settings(BaseSettings):
    model_config = SettingsConfigDict(env_file=".env", env_file_encoding="utf-8")

    api_host: str = "0.0.0.0"
    api_port: int = 8001
    debug: bool = True
    root_path: str = ""

    fmu_path_reheat: str = Field(
        default="apps/control-sequence-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu",
        description="Path to Reheat Terminal FMU file",
    )
    fmu_path_vav: str | None = Field(
        default=None,
        description="Path to VAV FMU file",
    )
    fmu_path_ahu: str | None = Field(
        default=None,
        description="Path to AHU FMU file",
    )

    cors_origins: list[str] = ["http://localhost:3000", "http://localhost:3003"]

    def get_fmu_path(self, sequence_type: str) -> Path | None:
        path_str = getattr(self, f"fmu_path_{sequence_type}", None)
        if path_str is None:
            return None
        return Path(path_str)


@lru_cache
def get_settings() -> Settings:
    return Settings()
