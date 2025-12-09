"""Database adapter for instance persistence using SQLAlchemy async."""

import contextlib
from pathlib import Path
from typing import AsyncIterator

from loguru import logger
from sqlalchemy import text
from sqlalchemy.ext.asyncio import (
    AsyncEngine,
    AsyncSession,
    async_sessionmaker,
    create_async_engine,
)
from sqlalchemy.orm import DeclarativeBase

from src.config.settings import get_settings


class Base(DeclarativeBase):
    """SQLAlchemy declarative base for models."""

    pass


_engine: AsyncEngine | None = None
_async_session: async_sessionmaker[AsyncSession] | None = None


def get_database_path() -> Path:
    """Get the database file path from settings."""
    settings = get_settings()
    db_path = Path(settings.database_path)
    db_path.parent.mkdir(parents=True, exist_ok=True)
    return db_path


def get_database_url() -> str:
    """Get the SQLite database URL."""
    db_path = get_database_path()
    return f"sqlite+aiosqlite:///{db_path}"


def get_engine() -> AsyncEngine:
    """Get or create the async database engine."""
    global _engine
    if _engine is None:
        _engine = create_async_engine(
            get_database_url(),
            connect_args={"timeout": 30, "check_same_thread": False},
            echo=False,
        )
    return _engine


def get_session_factory() -> async_sessionmaker[AsyncSession]:
    """Get the async session factory."""
    global _async_session
    if _async_session is None:
        engine = get_engine()
        _async_session = async_sessionmaker(
            engine,
            class_=AsyncSession,
            expire_on_commit=False,
        )
    return _async_session


@contextlib.asynccontextmanager
async def get_session() -> AsyncIterator[AsyncSession]:
    """Get an async database session as a context manager."""
    session_factory = get_session_factory()
    async with session_factory() as session:
        yield session


async def initialize_database() -> None:
    """Initialize the database with WAL mode and create tables."""
    engine = get_engine()

    async with engine.begin() as conn:
        await conn.execute(text("PRAGMA journal_mode=WAL;"))
        await conn.execute(text("PRAGMA synchronous=NORMAL;"))
        logger.info("Database WAL mode enabled")

        await conn.run_sync(Base.metadata.create_all)
        logger.info("Database tables created")


async def close_database() -> None:
    """Close the database connection."""
    global _engine, _async_session
    if _engine is not None:
        await _engine.dispose()
        _engine = None
        _async_session = None
        logger.info("Database connection closed")


def reset_database_state() -> None:
    """Reset database state for testing purposes."""
    global _engine, _async_session
    _engine = None
    _async_session = None
