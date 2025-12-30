"""Integration test to verify BuildingMOTIF adapter thread safety configuration."""
from pathlib import Path
from tempfile import TemporaryDirectory


def test_buildingmotif_adapter_wal_mode():
    """
    Test that BuildingMOTIF adapter configures SQLite in WAL mode.

    WAL mode enables concurrent reads without blocking.
    """
    from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
    from src.config.settings import Settings

    with TemporaryDirectory() as temp_dir:
        db_path = Path(temp_dir) / "test_wal.db"
        settings = Settings(
            buildingmotif_db_path=str(db_path),
            enable_validation=False,
        )

        BuildingMOTIFAdapter._instance = None

        adapter = BuildingMOTIFAdapter.get_instance(db_path=str(db_path), settings=settings)

        with adapter._bm.engine.connect() as conn:
            result = conn.execute("PRAGMA journal_mode")
            journal_mode = result.fetchone()[0]

            assert journal_mode.lower() == "wal", f"Expected WAL mode, got: {journal_mode}"

        BuildingMOTIFAdapter._instance = None
