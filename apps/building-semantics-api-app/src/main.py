"""FastAPI application entry point."""
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from .config.settings import get_settings
from .routers import mappings, spaces, templates, validation

settings = get_settings()

app = FastAPI(
    title="Building Semantics API",
    description="FastAPI wrapper for BuildingMOTIF SDK - ASHRAE 223P semantic tagging",
    version="0.1.0",
    docs_url="/docs",
    redoc_url="/redoc",
    openapi_url="/openapi.json",
    root_path=settings.root_path,
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
app.include_router(mappings.router)
app.include_router(validation.router)


@app.get("/health", tags=["Health"])
async def health_check() -> dict[str, str]:
    """Health check endpoint."""
    return {
        "status": "healthy",
        "service": "building-semantics-api",
        "version": "0.1.0",
    }
