"""Unit tests for settings configuration."""
import pytest

from src.config.settings import Settings, get_settings


def test_settings_default_values() -> None:
    """Test settings have correct default values."""
    settings = Settings()

    assert settings.api_host == "0.0.0.0"
    assert settings.api_port == 8000
    assert settings.debug is True
    assert settings.buildingmotif_db_path == "buildingmotif.db"
    assert settings.cors_origins == ["http://localhost:3003"]


def test_get_settings_returns_settings_instance() -> None:
    """Test get_settings returns Settings instance."""
    settings = get_settings()
    assert isinstance(settings, Settings)


def test_get_settings_is_cached() -> None:
    """Test get_settings returns same instance (cached)."""
    settings1 = get_settings()
    settings2 = get_settings()
    assert settings1 is settings2
