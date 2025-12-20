# Control Sequence API - Technical Specification

> **Status**: Draft
> **Version**: 0.1
> **Date**: 2025-11-30
> **Story**: 1.5 - Control Sequence API Tech Spec

## 1. Requirements

### 1.1 Functional Requirements

| ID   | Requirement                               | Notes                                                                                                           |
| ---- | ----------------------------------------- | --------------------------------------------------------------------------------------------------------------- |
| FR1  | Create FMU instance with parameters       | Idempotent. Called on drag-drop or project reload.                                                              |
| FR2  | Update FMU instance parameters            | Resets FMU with new parameters.                                                                                 |
| FR3  | Execute G36 control sequence step         | Step size provided by caller. Instance must exist.                                                              |
| FR4  | Delete FMU instance by `instance_id`      | Called when Designer deletes node. Idempotent.                                                                  |
| FR5  | Accept sequence-specific input schema     | Each G36 sequence type (Reheat, VAV, AHU) has its own typed input schema. Epic 1: Reheat only.                  |
| FR6  | Return sequence-specific output schema    | Each sequence type has typed outputs. Reheat: yDam, yVal, VSet_flow.                                            |
| FR7  | Accept sequence-specific parameter schema | Each sequence type has configurable parameters. Reheat: VCooMax, VHeaMax, VMin, etc.                            |
| FR8  | Validate inputs at runtime (Type + Range) | Pydantic type checks + range validation (e.g., temps 250-350K, airflow ≥0, uOpeMod 1-7).                        |
| FR9  | SHACL validation endpoint (stub)          | Design-time validation for graph structure. Out of scope - stub only for Epic 1.                                |
| FR10 | Support multiple concurrent FMU instances | One FMU instance per `instance_id`. Instances are independent.                                                  |
| FR11 | Health check endpoint                     | Returns API status, active instance count.                                                                      |
| FR12 | OpenAPI schema generation                 | Pydantic DTOs in API, TypeScript types auto-generated via `openapi-ts`. Matches building-semantics-api pattern. |

### 1.2 Non-Functional Requirements

| ID   | Requirement         | Target          | Source                                   |
| ---- | ------------------- | --------------- | ---------------------------------------- |
| NFR1 | Step execution time | <1ms per step   | POC Q11 (~0.1ms)                         |
| NFR2 | Memory per instance | <2MB            | POC Q12 (~1-2MB)                         |
| NFR3 | Instance capacity   | 500+ concurrent | NFR1×NFR2                                |
| NFR4 | API response time   | <10ms p95       | Web API SLA                              |
| NFR5 | Startup time        | <5s             | FMU instance creation ~5-8ms × instances |

### 1.3 Constraints

| ID  | Constraint                                    | Implication                                                             | Source     |
| --- | --------------------------------------------- | ----------------------------------------------------------------------- | ---------- |
| C1  | FMU is stateful (integral terms)              | Must keep FMU instances alive in memory                                 | POC Q14    |
| C2  | No native state persistence                   | Cannot save/restore FMU state                                           | POC Q2     |
| C3  | FMU accepts invalid inputs silently           | Must validate ALL inputs before FMU call                                | POC Q13    |
| C4  | Crash recovery = fresh start                  | Accept temporary control degradation                                    | POC Q14    |
| C5  | In-process memory                             | Process restart loses all instance state                                | POC Q14    |
| C6  | FMU file required at startup                  | ~10MB file must be present                                              | POC Q6     |
| C7  | Follow building-semantics-api-app patterns    | MVC structure, adapter pattern                                          | Story req  |
| C8  | Project name: `control-sequence-api-app`      | Rename from g36-api-app                                                 | Discussion |
| C9  | API path prefix: `/api/v1/g36/`               | Match building-semantics-api pattern                                    | Discussion |
| C10 | API operates on caller-provided `instance_id` | Globally unique across ALL sequence types. No zone/node concept in API. | Discussion |
| C11 | Support multiple G36 sequence types           | Terminal units, VAV, AHU, etc.                                          | Discussion |

## 2. Use Cases

### ~~UC1: Get Sequence Schema~~ (SKIPPED)

> **Decision:** Use OpenAPI-generated types instead of runtime schema endpoint.
> Designer uses hardcoded node UI components and openapi-ts generates TypeScript types at build time.
> Add schema endpoint later if dynamic form rendering is needed for multiple G36 types.

- ~~**Actor:** Designer~~
- ~~**Trigger:** User drags G36 block onto canvas OR opens config panel~~
- ~~**Flow:**~~
  ~~1. Caller requests schema for sequence type (e.g., "reheat")~~
  ~~2. API returns parameters, inputs, and outputs with metadata (defaults, ranges, units)~~
- ~~**Output:** Schema with types, defaults, ranges, units, descriptions~~

### UC2: Create FMU Instance

- **Actor:** Designer
- **Trigger:** User drags G36 block onto canvas OR reloads saved project
- **Flow:**
  1. Caller sends create request with `instance_id` and optional `parameters`
  2. If `instance_id` exists → return success (idempotent, no-op)
  3. If `instance_id` doesn't exist → create FMU instance with params (or defaults)
  4. Return success
- **Output:** Success with `instance_id`

### UC3: Update FMU Instance Parameters

- **Actor:** Designer
- **Trigger:** User changes parameters in configuration panel
- **Flow:**
  1. Caller sends update request with `instance_id` and new `parameters`
  2. API terminates existing FMU instance
  3. API creates new FMU instance with new parameters
  4. Return success
- **Output:** Success (FMU reset with new parameters)

### UC4: Execute Control Sequence Step

- **Actor:** Designer
- **Trigger:** Scheduled interval or manual request
- **Precondition:** Instance exists (created via UC2)
- **Flow:**
  1. Caller sends step request with `instance_id`, `step_size`, and inputs
  2. API validates inputs (type + range)
  3. Set inputs on FMU
  4. Execute `doStep(step_size)`
  5. Read outputs from FMU
  6. Return outputs to caller
- **Output:** Sequence-specific outputs (e.g., yDam, yVal, VSet_flow for Reheat)

### UC5: Delete FMU Instance

- **Actor:** Designer
- **Trigger:** User deletes node from canvas
- **Flow:**
  1. Caller sends delete request with `instance_id`
  2. API terminates FMU instance and frees resources
  3. Returns success
- **Output:** Success (idempotent - success even if not found)

### UC6: Health Check

- **Actor:** Operations/Monitoring
- **Trigger:** Periodic health probe
- **Flow:**
  1. Caller requests health status
  2. API returns status and metrics
- **Output:** API status, active instance count

### UC7: SHACL Validation (Stub)

- **Actor:** Designer
- **Trigger:** User clicks save/run
- **Flow:**
  1. Caller sends graph for validation
  2. API returns stub response (always valid for Epic 1)
- **Output:** Validation result (stubbed)

## 3. Architecture

### 3.1 MVC Structure

```
control-sequence-api-app/
├── src/
│   ├── adapters/           # External service wrappers
│   │   └── fmu_adapter.py  # Singleton FMU instance manager
│   ├── config/             # Settings, environment
│   │   └── settings.py     # pydantic-settings
│   ├── controllers/        # Business logic
│   │   └── g36_controller.py
│   ├── dto/                # Request/Response schemas
│   │   ├── reheat_dto.py   # Reheat Terminal inputs/outputs
│   │   └── common_dto.py   # Health, error responses
│   ├── models/             # Domain models
│   │   └── fmu_instance.py # FMU instance wrapper
│   ├── routers/            # FastAPI endpoints
│   │   ├── g36_router.py   # /api/v1/g36/...
│   │   └── health_router.py
│   └── main.py             # FastAPI app entry
├── tests/
│   ├── unit/
│   └── integration/
└── pyproject.toml
```

### 3.2 Component Responsibilities

| Layer           | Responsibility                                                  |
| --------------- | --------------------------------------------------------------- |
| **Routers**     | HTTP endpoint definitions, request parsing, response formatting |
| **Controllers** | Business logic, orchestrates adapter calls, validation          |
| **Adapters**    | FMU lifecycle management (singleton pattern), wraps FMPy        |
| **DTOs**        | Pydantic schemas for request/response validation                |
| **Models**      | Domain models (FMU instance wrapper)                            |
| **Config**      | Environment settings, FMU file paths                            |

### 3.3 Configuration

FMU file paths configured via environment variables using pydantic-settings (matches building-semantics-api-app pattern).

```python
class Settings(BaseSettings):
    model_config = SettingsConfigDict(env_file=".env", env_file_encoding="utf-8")

    api_host: str = "0.0.0.0"
    api_port: int = 8001

    # FMU paths per sequence type (prefix-based pattern)
    fmu_path_reheat: str = Field(
        default="apps/g36-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu",
        description="Path to Reheat Terminal FMU file"
    )
    fmu_path_vav: str | None = Field(default=None, description="Path to VAV FMU file")
    fmu_path_ahu: str | None = Field(default=None, description="Path to AHU FMU file")

    def get_fmu_path(self, sequence_type: str) -> str | None:
        return getattr(self, f"fmu_path_{sequence_type}", None)
```

**Environment Variables:**
| Variable | Default | Description |
|----------|---------|-------------|
| `API_HOST` | `0.0.0.0` | API bind address |
| `API_PORT` | `8001` | API port |
| `FMU_PATH_REHEAT` | `apps/g36-api-app/fmu-sequence/builds/ReheatControllerFMU.fmu` | Reheat Terminal FMU |
| `FMU_PATH_VAV` | None | VAV FMU (future) |
| `FMU_PATH_AHU` | None | AHU FMU (future) |

### 3.4 Key Design Decisions

| Decision                            | Rationale                                                                                    |
| ----------------------------------- | -------------------------------------------------------------------------------------------- |
| Singleton FMU Adapter               | Manages all FMU instances in-process memory (C1, C5)                                         |
| Sequence-specific DTOs              | Type safety per G36 sequence type (FR3, FR4, C11)                                            |
| Controller validates before adapter | FMU accepts invalid inputs silently (C3)                                                     |
| Prefix-based FMU paths              | Each sequence type explicit, type-safe, self-documenting (C6)                                |
| Per-instance asyncio.Lock           | Concurrent step calls on same instance serialized. Different instances can step in parallel. |
| Lazy FMU loading                    | Startup validates files exist. Extract on first use per sequence type. Scales to many FMUs.  |

## 4. API Design

### 4.1 Endpoints

| Method  | Path                                              | Description                                                  | UC      |
| ------- | ------------------------------------------------- | ------------------------------------------------------------ | ------- |
| ~~GET~~ | ~~`/api/v1/g36/reheat/schema`~~                   | ~~Get Reheat schema~~ - SKIPPED: Use OpenAPI-generated types | ~~UC1~~ |
| POST    | `/api/v1/g36/reheat/instances`                    | Create FMU instance with parameters                          | UC2     |
| PUT     | `/api/v1/g36/reheat/instances/{instance_id}`      | Update instance parameters (resets FMU)                      | UC3     |
| POST    | `/api/v1/g36/reheat/instances/{instance_id}/step` | Execute Reheat Terminal step                                 | UC4     |
| DELETE  | `/api/v1/g36/instances/{instance_id}`             | Delete FMU instance (sequence-agnostic)                      | UC5     |
| GET     | `/api/v1/health`                                  | Health check                                                 | UC6     |
| POST    | `/api/v1/g36/validate`                            | SHACL validation (stub)                                      | UC7     |

### 4.2 Request/Response Schemas

#### ~~GET `/api/v1/g36/reheat/schema`~~ (SKIPPED)

> Schema endpoint skipped. Use OpenAPI-generated types from `/openapi.json` instead.

#### POST `/api/v1/g36/reheat/instances`

**Request:**

```json
{
  "instance_id": "string",
  "parameters": {
    "VCooMax": 0.5,
    "VHeaMax": 0.3,
    "VMin": 0.1
  }
}
```

**Response (200):**

```json
{
  "instance_id": "string",
  "created": true
}
```

#### PUT `/api/v1/g36/reheat/instances/{instance_id}`

**Request:**

```json
{
  "parameters": {
    "VCooMax": 0.6,
    "VHeaMax": 0.4,
    "VMin": 0.1
  }
}
```

**Response (200):**

```json
{
  "instance_id": "string",
  "updated": true
}
```

#### POST `/api/v1/g36/reheat/instances/{instance_id}/step`

**Request:**

```json
{
  "step_size": 300.0, // Simulation time in seconds (FMI 2.0 standard). Example: 300.0 = 5 minutes
  "inputs": {
    "TZon": 295.15,
    "TCooSet": 297.15,
    "THeaSet": 293.15,
    "TDis": 286.15,
    "VDis_flow": 0.1,
    "TSup": 286.15,
    "TSupSet": 285.15,
    "u1Fan": true,
    "uOpeMod": 1
  }
}
```

**Response (200):**

```json
{
  "instance_id": "string",
  "outputs": {
    "yDam": 0.5,
    "yVal": 0.0,
    "VSet_flow": 0.15
  }
}
```

#### DELETE `/api/v1/g36/instances/{instance_id}`

**Response (200):**

```json
{
  "instance_id": "string",
  "deleted": true
}
```

#### GET `/api/v1/health`

**Response (200):**

```json
{
  "status": "healthy",
  "active_instances": 5
}
```

### 4.3 Error Handling

| Status | Condition                            | Response                                                                   |
| ------ | ------------------------------------ | -------------------------------------------------------------------------- |
| 400    | Invalid input (validation failed)    | `{"error": "validation_error", "detail": "TZon must be between 250-350K"}` |
| 404    | Instance not found (for step/update) | `{"error": "not_found", "detail": "Instance abc-123 not found"}`           |
| 500    | FMU execution error                  | `{"error": "fmu_error", "detail": "..."}`                                  |

## 5. Integration Points

### 5.1 OpenAPI Schema Generation

**Pattern:** Same as building-semantics-api-app

**Flow:**

1. Define Pydantic DTOs in `control-sequence-api-app/src/dto/`
2. FastAPI auto-generates OpenAPI spec at `/openapi.json`
3. Run `openapi-ts` to generate TypeScript types + client
4. Designer imports generated types directly as node data model

**Structure:**

```
apps/control-sequence-api-app/
├── src/dto/
│   └── reheat_dto.py                # Pydantic SOURCE (parameters, inputs, outputs)

apps/designer/
├── src/domains/g36/api/
│   └── generated/
│       ├── types.gen.ts             # AUTO-GENERATED types
│       ├── sdk.gen.ts               # AUTO-GENERATED client
│       └── client.gen.ts
```

**Designer package.json script:**

```json
"generate:g36-client": "openapi-ts --input http://localhost:8001/openapi.json --output ./src/domains/g36/api/generated --client @hey-api/client-fetch"
```

**Designer uses generated types directly as node data model:**

```typescript
// Auto-generated from openapi-ts - NO manual redefinition needed
import {
  ReheatParameters,
  ReheatInputs,
  ReheatOutputs,
  ReheatSchemaResponse,
} from "@/domains/g36/api/generated";

// G36 node uses generated types directly
class G36ReheatNode {
  readonly instance_id: string;
  parameters: ReheatParameters; // From generated types
  inputs: ReheatInputs; // From generated types
  outputs: ReheatOutputs; // From generated types
}
```

**Schema endpoint for runtime metadata:**

```
GET /api/v1/g36/reheat/schema
```

Returns defaults, ranges, units for dynamic form rendering. Types come from generated code, metadata comes from schema endpoint.

### 5.2 Designer Integration

#### Flow 1: New Node (Drag G36 Reheat onto canvas)

| Step | Designer Action                                | API Call                                                   |
| ---- | ---------------------------------------------- | ---------------------------------------------------------- |
| 1    | User drags G36 Reheat from palette             | -                                                          |
| 2    | Designer creates API instance (gets defaults)  | `POST /api/v1/g36/vav-reheat/instances`                    |
| 3    | API returns `instance_id` + default parameters | -                                                          |
| 4    | Designer stores `instance_id` in node data     | -                                                          |
| 5    | Node appears on canvas with input/output ports | -                                                          |
| 6    | User opens config panel                        | `GET /api/v1/g36/vav-reheat/instances/{instance_id}`       |
| 7    | User changes parameters, clicks Save           | `PUT /api/v1/g36/vav-reheat/instances/{instance_id}`       |
| 8    | User runs flow                                 | `POST /api/v1/g36/vav-reheat/instances/{instance_id}/step` |
| 9    | User deletes node                              | `DELETE /api/v1/g36/vav-reheat/instances/{instance_id}`    |

#### Flow 2: Saved Node (Reload project)

| Step | Designer Action                                | API Call                                                   |
| ---- | ---------------------------------------------- | ---------------------------------------------------------- |
| 1    | User opens saved project                       | -                                                          |
| 2    | Designer loads nodes from project file         | -                                                          |
| 3    | For each G36 node, Designer has: `instance_id` | -                                                          |
| 4    | Designer fetches parameters from API           | `GET /api/v1/g36/vav-reheat/instances/{instance_id}`       |
| 5    | Node appears on canvas with fetched parameters | -                                                          |
| 6    | User runs flow                                 | `POST /api/v1/g36/vav-reheat/instances/{instance_id}/step` |

#### What Designer persists in project file:

```json
{
  "nodes": [
    {
      "id": "node-123",
      "type": "g36-vav-reheat",
      "position": { "x": 100, "y": 200 },
      "data": {
        "instance_id": "abc-456-def"
      }
    }
  ]
}
```

#### Key Points:

- **instance_id must be globally unique** - Use UUID. Shared namespace across all sequence types (Reheat, VAV, AHU).
- **API is source of truth for parameters** - Designer only stores `instance_id`, fetches parameters from API
- **Parameters persisted in SQLite** - Survive API restarts (Story 1.15)
- **Create returns defaults** - POST response includes `instance_id` and default `parameters`
- **Delete is sequence-agnostic** - Single endpoint works because instance_id is globally unique

**Data Flow:**

```
Designer Node → (instance_id, inputs) → Control Sequence API → (outputs) → Designer Node
                                              ↓
                                        SQLite (parameters)
```

**Designer Responsibilities:**

- Store `instance_id` in node data (only identifier needed)
- Call `POST /instances` on drag-drop to create instance
- Call `GET /instances/{id}` to fetch parameters for config panel
- Call `PUT /instances/{id}` to save parameter changes
- Call `DELETE /instances/{id}` when node is deleted
- Provide `step_size` from flow configuration
- Map BACnet sensor values to G36 inputs
- Map G36 outputs to BACnet write commands
- Use generated types from `openapi-ts` as node data model

**API Responsibilities:**

- Generate `instance_id` (UUID) on create
- Persist parameters in SQLite database
- Return parameters on GET requests
- Manage FMU lifecycle (lazy instantiation on first step)

### 5.3 API Documentation

**Requirements:**

- FastAPI auto-generates OpenAPI/Swagger docs at `/docs`
- All endpoints must have clear docstrings visible in Swagger UI
- Request/Response schemas must include field descriptions and examples
- Input validation constraints (ranges, types) visible in schema documentation

**Documentation Standards:**

| Element         | Requirement                                   |
| --------------- | --------------------------------------------- |
| Endpoint        | Description of what it does, when to use it   |
| Request fields  | Type, description, valid range, example value |
| Response fields | Type, description, example value              |
| Error responses | When each error occurs, how to resolve        |

**Example Docstring Style:**

```python
@router.post("/reheat/instances")
async def create_instance(request: CreateInstanceRequest) -> CreateInstanceResponse:
    """
    Create a new FMU instance for a Reheat Terminal Unit.

    Idempotent - returns success if instance already exists.
    Call this when dragging a G36 block onto canvas or reloading a project.
    """
```

**Pydantic Schema Example:**

```python
class ReheatInputs(BaseModel):
    TZon: float = Field(
        ...,
        ge=250, le=350,
        description="Zone temperature in Kelvin",
        json_schema_extra={"example": 295.15}
    )
```

## 6. Implementation Stories

| Story   | Description                        | Scope                                                                |
| ------- | ---------------------------------- | -------------------------------------------------------------------- |
| 2.1     | Project Setup & Scaffolding        | pyproject.toml, MVC folders, settings, main.py                       |
| 2.2     | Reheat DTOs & Validation           | Pydantic schemas for parameters, inputs, outputs with Field metadata |
| ~~2.3~~ | ~~Schema Endpoint~~                | ~~GET /schema~~ - SKIPPED: Use OpenAPI-generated types instead       |
| 2.4     | FMU Adapter (Singleton)            | fmu_adapter.py - create, update, step, delete FMU instances          |
| 2.5     | G36 Controller                     | g36_controller.py - business logic, orchestrates adapter             |
| 2.6     | G36 Router & Endpoints             | g36_router.py - all Reheat endpoints (create, update, step, delete)  |
| 2.7     | Health Router                      | health_router.py - health check endpoint                             |
| 2.8     | SHACL Validation Stub              | validate endpoint - stub returning always valid                      |
| 2.9     | API Documentation                  | Docstrings, Field descriptions, Swagger polish                       |
| 2.10    | Designer OpenAPI Client Generation | Add generate:g36-client script, generate types + client              |
| 2.11    | Unit & Integration Tests           | Tests for adapter, controller, router, DTOs                          |
