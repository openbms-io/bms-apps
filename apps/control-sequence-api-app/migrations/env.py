"""Alembic environment configuration for async SQLAlchemy migrations.

Migration Modes:
- Offline: Generates SQL scripts without database connection
- Online: Connects to database and executes migrations directly

How Migrations Work:
    1. Define SQLAlchemy models in src/models/ folder
    2. Import models in this file (env.py) so Alembic can detect them
    3. Run autogenerate to create migration from model changes
    4. Apply migration to update database schema

Common Commands (run from apps/control-sequence-api-app/):
    # Create a new migration (compares models to database)
    alembic revision --autogenerate -m "description of changes"

    # Apply all pending migrations (online mode)
    alembic upgrade head

    # Generate SQL without executing (offline mode)
    alembic upgrade head --sql > migration.sql

    # View current migration status
    alembic current

    # View migration history
    alembic history

    # Rollback one migration
    alembic downgrade -1
"""

import asyncio
import os
import sys
from logging.config import fileConfig

from alembic import context
from sqlalchemy import pool
from sqlalchemy.engine import Connection
from sqlalchemy.ext.asyncio import async_engine_from_config

project_root = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "..", "..", "..")
)
if project_root not in sys.path:
    sys.path.insert(0, project_root)

app_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if app_root not in sys.path:
    sys.path.insert(0, app_root)

from src.adapters.database_adapter import Base, get_database_url

# Import models so Alembic can detect schema changes for autogenerate
from src.models.control_sequence_instance_model import ControlSequenceInstanceModel

# Reference to prevent "unused import" linter warning
_ = ControlSequenceInstanceModel

config = context.config

config.set_main_option("sqlalchemy.url", get_database_url())

if config.config_file_name is not None:
    fileConfig(config.config_file_name)

target_metadata = Base.metadata


def run_migrations_offline() -> None:
    """Run migrations in offline mode.

    Generates SQL migration scripts without connecting to the database.
    Useful for reviewing SQL before execution or CI/CD pipelines.
    Usage: alembic upgrade head --sql > migration.sql
    """
    url = config.get_main_option("sqlalchemy.url")
    context.configure(
        url=url,
        target_metadata=target_metadata,
        literal_binds=True,
        dialect_opts={"paramstyle": "named"},
    )

    with context.begin_transaction():
        context.run_migrations()


def do_run_migrations(connection: Connection) -> None:
    context.configure(connection=connection, target_metadata=target_metadata)

    with context.begin_transaction():
        context.run_migrations()


async def run_async_migrations() -> None:
    """Create async engine and run migrations."""
    connectable = async_engine_from_config(
        config.get_section(config.config_ini_section, {}),
        prefix="sqlalchemy.",
        poolclass=pool.NullPool,
    )

    async with connectable.connect() as connection:
        await connection.run_sync(do_run_migrations)

    await connectable.dispose()


def run_migrations_online() -> None:
    """Run migrations in online mode.

    Connects to the database and executes migrations directly.
    This is the standard mode for development and production.
    Usage: alembic upgrade head
    """
    asyncio.run(run_async_migrations())


if context.is_offline_mode():
    run_migrations_offline()
else:
    run_migrations_online()
