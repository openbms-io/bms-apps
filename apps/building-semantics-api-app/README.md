# Building Semantics API

FastAPI wrapper for BuildingMOTIF SDK - ASHRAE 223P semantic tagging for building management systems.

## Overview

This API provides semantic mapping services for BACnet points to ASHRAE 223P ontology templates, enabling semantic interoperability for building automation systems.

**Architecture**: FastAPI backend → BuildingMOTIF SDK → ASHRAE 223P ontology

## Prerequisites

- Python 3.11 or higher
- pip or your preferred Python package manager

## Installation

From the repository root:

```bash
# Install dependencies
pnpm building-semantics:install

# Or manually:
cd apps/building-semantics-api-app
pip install -e '.[test,dev]'
```

## Running the Server

From repository root:

```bash
# Start API server only
pnpm building-semantics:run

# Or start all services (BMS IoT + Semantics API + Designer)
pnpm dev
```

The API will be available at:

- **API**: http://localhost:8000
- **Swagger UI**: http://localhost:8000/docs
- **ReDoc**: http://localhost:8000/redoc
- **OpenAPI spec**: http://localhost:8000/openapi.json
- **Health check**: http://localhost:8000/health

## Development Commands

```bash
# Run tests
pnpm building-semantics:test

# Run tests with verbose output
pnpm building-semantics:test:verbose

# Type checking (mypy strict mode)
pnpm building-semantics:typecheck

# Linting (ruff)
pnpm building-semantics:lint

# Code formatting (black)
pnpm building-semantics:format
```

## Project Structure

```
apps/building-semantics-api-app/
├── src/
│   ├── main.py                    # FastAPI app entry point
│   ├── routers/                   # API endpoints
│   │   ├── templates.py           # ASHRAE 223P templates
│   │   ├── spaces.py              # Space instances
│   │   ├── mappings.py            # Semantic mappings
│   │   └── validation.py          # Validation services
│   ├── services/                  # Business logic layer
│   ├── adapters/                  # External service adapters
│   │   └── buildingmotif_adapter.py
│   ├── dto/                       # Data Transfer Objects
│   ├── config/                    # Configuration
│   │   └── settings.py
│   └── utils/                     # Utility functions
├── tests/
│   ├── unit/                      # Unit tests
│   └── integration/               # Integration tests
└── pyproject.toml                 # Dependencies and tooling
```

## Configuration

Create a `.env` file in the app directory (use `.env.template` as reference):

```bash
# API Configuration
API_HOST=0.0.0.0
API_PORT=8000
DEBUG=true

# BuildingMOTIF Configuration
BUILDINGMOTIF_DB_PATH=buildingmotif.db

# CORS Configuration
CORS_ORIGINS=["http://localhost:3003"]
```

## Development Phases

- **Phase 0** (Current): Infrastructure scaffolding
- **Phase 1**: Mock endpoint implementation for interface validation
- **Phase 2**: BuildingMOTIF SDK integration
- **Phase 3**: AI-enhanced semantic suggestions

## API Endpoints

### Health Check

```
GET /health
```

Returns service health status.

### ASHRAE 223P Services

**Templates** - `/api/223p/templates`
System, device, and property templates from ASHRAE 223P ontology.

**Spaces** - `/api/223p/spaces`
Building space instances and types.

**Mappings** - `/api/223p/mappings`
BACnet point to ASHRAE 223P template mappings.

**Validation** - `/api/223p/validate`
Semantic mapping validation services.

## Testing

The project follows TDD (Test-Driven Development):

```bash
# Run all tests
pnpm building-semantics:test

# Run specific test file
cd apps/building-semantics-api-app
pytest tests/integration/test_routers/test_health.py -v
```

## Code Quality

- **Type checking**: mypy in strict mode
- **Linting**: ruff
- **Formatting**: black (line length: 88)
- **Testing**: pytest with async support

## Integration with Designer App

The API is designed to work with the Designer frontend application:

- Designer runs on port **3003**
- API runs on port **8000**
- CORS is configured to allow Designer origin
- Both can be started together with `pnpm dev`

## License

See repository root for license information.
