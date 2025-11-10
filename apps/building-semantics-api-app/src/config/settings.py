"""Application settings from environment variables."""
from functools import lru_cache

from pydantic_settings import BaseSettings, SettingsConfigDict


class Settings(BaseSettings):
    """Application settings from environment variables."""

    model_config = SettingsConfigDict(env_file=".env", env_file_encoding="utf-8")

    api_host: str = "0.0.0.0"
    api_port: int = 8000
    debug: bool = True
    root_path: str = ""

    buildingmotif_db_path: str = "buildingmotif.db"

    cors_origins: list[str] = ["http://localhost:3003"]


@lru_cache
def get_settings() -> Settings:
    """Get cached settings instance."""
    return Settings()
