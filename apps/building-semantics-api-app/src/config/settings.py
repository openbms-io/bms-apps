"""Application settings from environment variables."""
from functools import lru_cache

from pydantic import Field
from pydantic_settings import BaseSettings, SettingsConfigDict


class Settings(BaseSettings):
    """Application settings from environment variables."""

    model_config = SettingsConfigDict(env_file=".env", env_file_encoding="utf-8")

    api_host: str = "0.0.0.0"
    api_port: int = 8000
    debug: bool = True
    root_path: str = ""

    buildingmotif_db_path: str = Field(
        default="apps/building-semantics-api-app/data/buildingmotif.db",
        description="Path to BuildingMOTIF SQLite database for RDF storage",
    )
    buildingmotif_templates_path: str = Field(
        default="apps/building-semantics-api-app/data/libraries/ashrae-223p-nrel",
        description="Path to NREL template library directory",
    )
    buildingmotif_library_path: str | None = Field(
        default=None,
        description="Custom path to ASHRAE 223P library (optional, uses bundled NREL templates if not specified)",
    )
    buildingmotif_223p_path: str = Field(default="apps/building-semantics-api-app/data/libraries/ontologies/223p.ttl",
                                         description="Path to 223P ontology")
    buildingmotif_qudt_path: str = Field(default="apps/building-semantics-api-app/data/libraries/ontologies/qudt-all.ttl",
                                         description="Path to combined QUDT ontology (units + quantitykinds)")
    should_use_qudt_all: bool = Field(default=False,
                                      description="Use combined qudt-all.ttl (True) or separate unit/quantitykind files (False)")
    buildingmotif_quantity_kind_path: str = Field(default="apps/building-semantics-api-app/data/libraries/ontologies/quantitykind",
                                                   description="Path to QuantityKind library")
    buildingmotif_unit_path: str = Field(default="apps/building-semantics-api-app/data/libraries/ontologies/unit",
                                         description="Path to QUDT ontology library")

    enable_validation: bool = Field(
        default=False,
        description="Enable SHACL validation against 223P constraints (disabled by default for faster initialization)"
    )

    cors_origins: list[str] = ["http://localhost:3003"]


@lru_cache
def get_settings() -> Settings:
    """Get cached settings instance."""
    return Settings()
