"""FastAPI application entry point."""
from collections.abc import AsyncGenerator
from contextlib import asynccontextmanager

from fastapi import FastAPI, HTTPException, Request
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
from loguru import logger

from .adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from .config.settings import get_settings
from .routers import bacnet_references, spaces, systems, templates, validation

settings = get_settings()


@asynccontextmanager
async def lifespan(app: FastAPI) -> AsyncGenerator[None, None]:
    """
    Lifespan context manager for application startup and shutdown.

    Eagerly initializes BuildingMOTIF adapter at startup to:
    1. Validate configuration and fail fast if misconfigured
    2. Load templates and ontologies before accepting requests
    3. Configure SQLite WAL mode for concurrent access
    """
    logger.info("=== Application Startup ===")
    logger.info("Initializing BuildingMOTIF adapter...")

    adapter = BuildingMOTIFAdapter.get_instance()
    validation_status = "enabled" if adapter._settings.enable_validation else "disabled"
    logger.info(f"✓ BuildingMOTIF adapter ready (validation={validation_status})")

    yield

    logger.info("=== Application Shutdown ===")


app = FastAPI(
    title="Building Semantics API",
    description="FastAPI wrapper for BuildingMOTIF SDK - ASHRAE 223P semantic tagging",
    version="0.1.0",
    docs_url="/docs",
    redoc_url="/redoc",
    openapi_url="/openapi.json",
    root_path=settings.root_path,
    lifespan=lifespan,
)


@app.exception_handler(HTTPException)
async def http_exception_handler(request: Request, exc: HTTPException) -> JSONResponse:
    """Custom exception handler to return {error: message} instead of {detail: message}."""
    return JSONResponse(
        status_code=exc.status_code,
        content={"error": exc.detail},
    )

app.add_middleware(
    CORSMiddleware,
    allow_origins=settings.cors_origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(templates.router)
app.include_router(spaces.router)
app.include_router(systems.router)
app.include_router(bacnet_references.router)
app.include_router(validation.router)


@app.get("/health", tags=["Health"])
async def health_check() -> dict[str, str]:
    """Health check endpoint."""
    return {
        "status": "healthy",
        "service": "building-semantics-api",
        "version": "0.1.0",
    }
