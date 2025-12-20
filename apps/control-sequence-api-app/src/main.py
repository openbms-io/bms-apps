from collections.abc import AsyncGenerator
from contextlib import asynccontextmanager
from pathlib import Path

from fastapi import FastAPI, HTTPException, Request
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
from loguru import logger

from .adapters.fmu_adapter import FmuAdapter
from .adapters.sequence_type import SequenceType
from .config.settings import get_settings
from .routers.g36_vav_reheat_router import router as g36_vav_reheat_router
from .routers.health_router import router as health_router
from .routers.parameters_router import router as parameters_router
from .routers.validation_router import router as validation_router

settings = get_settings()


@asynccontextmanager
async def lifespan(app: FastAPI) -> AsyncGenerator[None, None]:
    logger.info("=== Application Startup ===")

    vav_reheat_path = settings.get_fmu_path(SequenceType.VAV_REHEAT)
    if vav_reheat_path is not None:
        if not Path(vav_reheat_path).exists():
            logger.warning(f"FMU file not found at {vav_reheat_path}")
        else:
            logger.info(f"FMU file found at {vav_reheat_path}")

    FmuAdapter.get_instance()
    logger.info("FmuAdapter singleton initialized")

    yield

    logger.info("=== Application Shutdown ===")


app = FastAPI(
    title="Control Sequence API",
    description="FastAPI wrapper for G36 FMU control sequences",
    version="0.1.0",
    docs_url="/docs",
    redoc_url="/redoc",
    openapi_url="/openapi.json",
    root_path=settings.root_path,
    lifespan=lifespan,
)


@app.exception_handler(HTTPException)
async def http_exception_handler(request: Request, exc: HTTPException) -> JSONResponse:
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


app.include_router(g36_vav_reheat_router)
app.include_router(health_router)
app.include_router(parameters_router)
app.include_router(validation_router)
