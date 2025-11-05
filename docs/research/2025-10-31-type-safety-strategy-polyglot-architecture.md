# Technical Research: Type Safety Strategy for Polyglot Architecture

**Date:** 2025-10-31
**Prepared by:** Amol
**Project:** BMS Supervisor Controller
**Research Type:** Technology Stack Evaluation - Type Safety Strategy
**Status:** 🔖 **TECH DEBT** - To Address Post-BuildingMOTIF Integration

---

## Executive Summary

### Key Finding

The BMS Supervisor Controller's polyglot architecture (TypeScript frontend + Python backend services) faces type safety synchronization challenges as the project scales to include BuildingMOTIF (RDF/SHACL), AI integration, and FMU/Modelica services.

### Primary Recommendation

**Hybrid Type Safety Strategy (Option 9)**

- **Python APIs → OpenAPI → TypeScript** for API boundaries (BuildingMOTIF, BMS IoT App, future FMU)
- **Zod** for Designer-internal schemas (visual programming, UI state)
- **JSON Schema** for shared MQTT message contracts (cross-service communication)

### Key Benefits

- ✅ Reduces type drift between TypeScript and Python
- ✅ Sustainable for solo developer (clear boundaries, standard tools)
- ✅ Lowers cognitive load (each schema type has clear purpose)
- ✅ Preserves language-native idioms (Zod for TS, Pydantic for Python)

### Tech Debt Status

**Priority:** Medium
**Effort:** 2-3 weeks
**Timeline:** Address after BuildingMOTIF/223P integration (Phase 1-3)
**Risk if delayed:** Type drift, manual sync errors, increased maintenance burden

---

## 1. Current Stack Analysis

### Technology Inventory (Verified from Codebase)

**Frontend (Designer App):**

- Next.js 15.5 with Turbopack & React 19.1
- React Flow (@xyflow/react 12.8) for visual programming
- Drizzle ORM with SQLite (local) / Turso (remote)
- Zod for schema validation
- Zustand for state management
- MQTT.js for bidirectional communication
- shadcn/ui (Radix UI primitives)
- Tailwind CSS v4
- TanStack Query for async state
- 306 test files (Jest + React Testing Library)

**Backend (BMS IoT App):**

- Python 3.11+ with asyncio architecture
- Custom Actor Model (asyncio-based, not Pykka or Trio)
- BACnet: BAC0 (2025.06.10) + bacpypes3
- MQTT: paho-mqtt for pub/sub
- SQLModel for database (local SQLite)
- Pydantic 2.5 for DTOs and validation
- Typer for CLI
- Loguru for logging
- Comprehensive test coverage (800+ tests)

**Future Services (Planned):**

- BuildingMOTIF (Python FastAPI + RDF + SHACL validation)
- FMU/Modelica Runtime (Python + PyFMI)
- AI Integration Service (Python + LLM API)

**Shared Infrastructure:**

- MQTT Topics package (TypeScript + Python dual implementation)
- Monorepo: PNPM workspaces

### Current Type Safety Approach

**TypeScript Side:**

```typescript
// apps/designer/src/lib/schemas/nodes/types.ts
export const NodeTypeSchema = z.enum([
  "input.sensor",
  "logic.compare",
  "output.actuator",
  // ... 12 node types
]);

export type NodeType = z.infer<typeof NodeTypeSchema>;
```

**Python Side:**

```python
# apps/bms-iot-app/src/dto/controller_point_dto.py
class ControllerPointDTO(BaseModel):
    point_id: str
    node_type: str  # Should match NodeTypeSchema, but not enforced
    value_type: str
    # ...
```

**Problem:** Manual synchronization, no compile-time guarantees of compatibility.

### Architecture Flow

```
┌─────────────────────────────────────────────────────────────┐
│                    Designer (TypeScript)                    │
│  - Zod schemas (visual programming, UI validation)          │
│  - Manual sync with Python DTOs                             │
└──────────────────┬──────────────────────────────────────────┘
                   │ MQTT (JSON)
                   ↓
┌─────────────────────────────────────────────────────────────┐
│               BMS IoT App (Python asyncio)                  │
│  - Pydantic DTOs (message parsing, validation)              │
│  - Manual sync with TypeScript schemas                      │
└──────────────────┬──────────────────────────────────────────┘
                   │
      ┌────────────┼────────────┐
      ↓            ↓            ↓
┌──────────┐ ┌──────────┐ ┌──────────┐
│BuildingMOTIF│ │ FMU Service│ │AI Service│
│(FastAPI)    │ │(PyFMI)     │ │(LLM API) │
│Pydantic     │ │Pydantic    │ │Pydantic  │
└──────────┘ └──────────┘ └──────────┘
```

**Pain Point:** Each service boundary requires manual schema synchronization.

---

## 2. Research Objectives

### Technical Question

How should we maintain type safety and schema consistency across a TypeScript frontend and multiple Python backend services (BMS IoT, BuildingMOTIF, FMU, AI) for a solo developer?

### Project Context

- **Project:** BMS Supervisor Controller (brownfield, Phase 6/8)
- **Team:** Solo developer, TypeScript strong, willing to learn
- **Timeline:** Strategic planning (plan now, execute later)
- **Flexibility:** No backward compatibility required, big-bang rewrite acceptable

### New Capabilities Needed

1. **More complex visual programming features**

   - Nested flows, custom node types, advanced validation

2. **AI-powered ASHRAE 223P → BACnet point mapping**

   - LLM semantic analysis of BACnet metadata
   - Intelligent equipment template suggestions
   - Learning from user corrections

3. **G36 HVAC sequences via FMU (Functional Mock-up Interface)**
   - Modelica-based sequence simulation
   - Real-time validation of control logic
   - Integration with visual programming canvas

---

## 3. Requirements and Constraints

### Functional Requirements

**Must Enable:**

- Visual programming interface (drag-and-drop flow canvas)
- BACnet device discovery and monitoring
- Real-time MQTT communication
- Multi-tenancy (org → site → device hierarchy)
- Schema-driven validation (type-safe configurations)
- Actor-based concurrency for device monitoring
- ASHRAE 223P semantic tagging (BuildingMOTIF integration)
- G36 sequence blocks (FMU simulation)
- AI-assisted mapping (LLM integration)

### Non-Functional Requirements

**Focus Areas:**

1. **Maintainability**

   - Type safety across language boundaries
   - Clear separation of concerns
   - Testability (current: 306 TS tests, 800+ Python tests)
   - Self-documenting schemas

2. **Scalability**
   - Feature scalability (adding new capabilities without major refactoring)
   - Code scalability (codebase growing without becoming unmaintainable)
   - Team scalability (easier onboarding for future contributors)
   - Deployment scalability (simple deployment, monitoring)

**Not Current Focus:**

- Performance optimization (addressed separately)
- High availability / disaster recovery

### Technical Constraints

**Hard Requirements:**

1. **Python Required for Core Libraries**

   - BuildingMOTIF (Python-only RDF/SHACL library)
   - PyFMI (Python-only Modelica FMU runtime)
   - BAC0/bacpypes3 (Python-only BACnet libraries)
   - **Constraint:** Cannot migrate to TypeScript-only stack

2. **Integration Commitments**

   - BuildingMOTIF FastAPI (already spec'd: `/docs/specs/2025-10-24-buildingmotif-integration-spec.md`)
   - ASHRAE 223P mapping UI (already spec'd: `/docs/specs/2025-10-30-phase-1-223p-mapping-popup-spec.md`)
   - Schema direction: Pydantic → OpenAPI → TypeScript (documented in BuildingMOTIF spec)

3. **Team Constraints**

   - Solo developer (cognitive load is critical factor)
   - TypeScript expertise > Python expertise
   - Willing to learn new tools/patterns
   - Limited time for complex tooling setup

4. **Deployment Constraints**
   - Designer: Vercel (serverless Next.js)
   - BMS IoT App: Local/edge deployment (long-running Python process)
   - Future services: TBD (likely containerized)

### Top 3 Maintainability Concerns

**1. Multi-Language Complexity**

- Managing three Python services (BMS IoT, BuildingMOTIF, FMU)
- Type safety across language boundaries (Pydantic ↔ TypeScript)
- Testing complexity (Jest + pytest + integration tests)
- Manual schema synchronization burden

**2. Emerging Polyglot Architecture**

- Designer (Next.js/TypeScript)
- BMS IoT App (Python asyncio Actor model + BACnet)
- BuildingMOTIF (Python FastAPI + RDF/SHACL)
- Future FMU service (Python + Modelica)
- Future AI service (Python + LLM API)
- Schema synchronization challenges across 5 services

**3. Solo Developer Cognitive Load**

- Too many mental models: React Flow, asyncio Actors, MQTT, BACnet, RDF/SHACL, 223P ontology, FMU, AI integration
- Context switching between fundamentally different paradigms
- Maintenance burden across diverse tech stack
- Risk of burnout or development stagnation

---

## 4. Technology Options Evaluated

### Option 1: Current Approach (Zod + Pydantic Manual Sync)

**How it works:**

- Define schemas separately in each language
- Manually keep them in sync
- Runtime validation on both sides

**Example:**

```typescript
// TypeScript (Zod)
export const NodeTypeSchema = z.enum(["input.sensor", "output.actuator"]);
export type NodeType = z.infer<typeof NodeTypeSchema>;
```

```python
# Python (Pydantic)
class NodeType(str, Enum):
    INPUT_SENSOR = "input.sensor"
    OUTPUT_ACTUATOR = "output.actuator"
```

**Pros:**

- ✅ Native idioms (Zod for TS, Pydantic for Python)
- ✅ Full control over each side
- ✅ Best-in-class validation for each language
- ✅ No additional tooling required

**Cons:**

- ❌ Manual synchronization burden
- ❌ Type drift risk (easy to forget updates)
- ❌ Cognitive load maintaining two schema systems
- ❌ No compile-time guarantees of compatibility
- ❌ Scales poorly (3+ services = 3x maintenance)

**Verdict:** Current approach, unsustainable at scale.

---

### Option 2: OpenAPI as Single Source of Truth

**How it works:**

- Python FastAPI generates OpenAPI spec (from Pydantic)
- TypeScript generates types from OpenAPI spec
- Direction: **Python → OpenAPI → TypeScript**

**Tools:**

- `openapi-typescript` - Generate TS types from OpenAPI
- FastAPI automatic OpenAPI generation

**Example (from BuildingMOTIF spec):**

```bash
# Python defines schemas with Pydantic
# FastAPI auto-generates /openapi.json

# TypeScript consumes OpenAPI spec
npx openapi-typescript http://localhost:8000/openapi.json \
  -o src/lib/api/buildingmotif-types.ts
```

**Generated TypeScript:**

```typescript
// Auto-generated from OpenAPI
export interface Equipment {
  id: string;
  name: string;
  type: string;
  points: Point[];
}
```

**Pros:**

- ✅ Single source of truth (Pydantic models)
- ✅ Automatic TypeScript type generation
- ✅ Industry standard (OpenAPI 3.0)
- ✅ Works well for API boundaries
- ✅ Already planned for BuildingMOTIF integration
- ✅ Low maintenance (regenerate on API changes)

**Cons:**

- ❌ One-way flow (Python → TS only)
- ❌ Designer internal schemas (Zod) still separate
- ❌ No runtime validation on TS side (types only, need Zod for validation)
- ❌ Build-time dependency (need running server to generate types)
- ❌ Doesn't solve MQTT message contracts

**Verdict:** Excellent for API boundaries, incomplete solution for full stack.

---

### Option 3: JSON Schema as Single Source of Truth

**How it works:**

- Define schemas in JSON Schema format
- Generate both Zod and Pydantic from JSON Schema
- Direction: **JSON Schema → Zod + Pydantic**

**Tools:**

- `json-schema-to-zod` - Generate Zod from JSON Schema
- `datamodel-code-generator` - Generate Pydantic from JSON Schema

**Example:**

```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "title": "NodeType",
  "type": "string",
  "enum": ["input.sensor", "logic.compare", "output.actuator"]
}
```

**Generated Zod:**

```typescript
export const NodeTypeSchema = z.enum([
  "input.sensor",
  "logic.compare",
  "output.actuator",
]);
```

**Generated Pydantic:**

```python
class NodeType(str, Enum):
    INPUT_SENSOR = "input.sensor"
    LOGIC_COMPARE = "logic.compare"
    OUTPUT_ACTUATOR = "output.actuator"
```

**Pros:**

- ✅ True single source of truth
- ✅ Language-agnostic schema definition
- ✅ Bidirectional sync (one schema, two targets)
- ✅ Runtime validation on both sides
- ✅ Excellent for shared message contracts (MQTT)

**Cons:**

- ❌ JSON Schema is verbose and less ergonomic than Zod/Pydantic
- ❌ Loses language-specific features (Zod transforms, Pydantic validators)
- ❌ Build-time code generation required
- ❌ Another abstraction layer to learn
- ❌ Limited TypeScript inference (generated code less elegant)

**Verdict:** Best for shared message contracts (MQTT), overkill for internal schemas.

---

### Option 4: TypeScript-First with Python Codegen

**How it works:**

- Define schemas in TypeScript (Zod)
- Generate Python Pydantic from Zod schemas
- Direction: **Zod → Python**

**Tools:**

- `zod-to-json-schema` → `datamodel-code-generator`
- Custom codegen pipeline

**Pros:**

- ✅ TypeScript-native development (leverages your strength)
- ✅ Zod as single source of truth
- ✅ Runtime validation on both sides

**Cons:**

- ❌ Complex tooling pipeline (multi-step generation)
- ❌ Not common pattern (less community support)
- ❌ Python types feel "second-class"
- ❌ Build complexity (watch mode, regeneration triggers)
- ❌ Doesn't align with BuildingMOTIF spec (Pydantic → OpenAPI → TS)

**Verdict:** Interesting but fights against ecosystem grain (Python FastAPI expects Pydantic-first).

---

### Option 5: Protocol Buffers (Protobuf)

**How it works:**

- Define schemas in `.proto` files
- Generate TypeScript and Python types
- Direction: **Protobuf → TS + Python**

**Tools:**

- `protobuf.js` for TypeScript
- `protobuf` for Python
- `ts-proto` for better TypeScript experience

**Example:**

```protobuf
syntax = "proto3";

enum NodeType {
  INPUT_SENSOR = 0;
  LOGIC_COMPARE = 1;
  OUTPUT_ACTUATOR = 2;
}

message FlowNode {
  string id = 1;
  NodeType type = 2;
  string label = 3;
}
```

**Pros:**

- ✅ Battle-tested for polyglot architectures
- ✅ Compact binary serialization (performance benefit)
- ✅ Strong typing on both sides
- ✅ Works well with gRPC (if you need it later)
- ✅ Excellent tooling support

**Cons:**

- ❌ Not JSON (different paradigm from current MQTT/REST)
- ❌ More complex tooling setup
- ❌ Overkill for REST/MQTT JSON payloads
- ❌ Steeper learning curve
- ❌ Binary format harder to debug
- ❌ Doesn't align with BuildingMOTIF spec

**Verdict:** Overkill for this use case, better for high-performance gRPC services.

---

### Option 6: GraphQL Schema Definition Language (SDL)

**How it works:**

- Define schemas in GraphQL SDL
- Generate TypeScript types
- Use GraphQL for API communication
- Direction: **GraphQL SDL → TS + Python**

**Tools:**

- `graphql-code-generator` for TypeScript
- `strawberry` or `graphene` for Python

**Example:**

```graphql
enum NodeType {
  INPUT_SENSOR
  LOGIC_COMPARE
  OUTPUT_ACTUATOR
}

type FlowNode {
  id: ID!
  type: NodeType!
  label: String!
}
```

**Pros:**

- ✅ Single schema language
- ✅ Excellent TypeScript tooling
- ✅ Type-safe queries (no over-fetching)
- ✅ Introspection and documentation built-in

**Cons:**

- ❌ Requires GraphQL adoption (vs REST)
- ❌ Different paradigm from current MQTT/REST architecture
- ❌ Learning curve (GraphQL resolvers, query language)
- ❌ May be overkill for simple CRUD APIs
- ❌ Doesn't align with BuildingMOTIF spec (FastAPI/REST)

**Verdict:** Interesting for future, but too disruptive for current architecture.

---

### Option 7: TypeScript Monorepo with Python Type Stubs

**How it works:**

- Keep schemas in TypeScript (Zod)
- Generate Python type stubs (`.pyi`) from TypeScript
- Use mypy for static type checking
- Direction: **TypeScript → Python type stubs**

**Tools:**

- Custom TypeScript → Python stub generator
- `mypy` for type checking

**Example:**

```python
# Generated .pyi file
from typing import Literal

NodeType = Literal["input.sensor", "logic.compare", "output.actuator"]

class FlowNode:
    id: str
    type: NodeType
    label: str
```

**Pros:**

- ✅ TypeScript as source of truth
- ✅ Python gets type hints (static checking)
- ✅ Lightweight (stubs only, no runtime)

**Cons:**

- ❌ No runtime validation in Python (stubs ≠ Pydantic)
- ❌ Complex custom tooling required
- ❌ mypy checks don't prevent runtime errors
- ❌ Doesn't solve the actual problem (need runtime validation)

**Verdict:** Type stubs are insufficient, need runtime validation.

---

### Option 8: Unified Runtime (Deno/Bun for Python-like workloads) ❌

**How it works:**

- Migrate Python services to TypeScript runtime
- Use Deno or Bun for backend services
- Single language across stack
- Direction: **TypeScript everywhere**

**Tools:**

- Deno (TypeScript-first runtime)
- Bun (fast JS/TS runtime with Node.js compatibility)

**Pros:**

- ✅ Single language (eliminates multi-language complexity)
- ✅ Unified type system (TypeScript everywhere)
- ✅ Shared code between frontend/backend
- ✅ Fast runtimes (Deno/Bun performance)
- ✅ Native TypeScript support (no transpilation)

**Cons:**

- ❌ **DEALBREAKER: Cannot use BuildingMOTIF** (Python-only library, no TypeScript port)
- ❌ **DEALBREAKER: Cannot use PyFMI** (Python-only for Modelica FMU)
- ❌ **DEALBREAKER: BACnet libraries** (BAC0/bacpypes are Python-only)
- ❌ Major rewrite required (BMS IoT App is 800+ tests)
- ❌ Violates integration commitments (BuildingMOTIF spec requires Python)

**Verdict:** **REJECTED** - Core requirements mandate Python ecosystem.

---

### Option 9: Hybrid Approach (OpenAPI + Zod + JSON Schema) ⭐

**How it works:**

- **For API boundaries:** Python (Pydantic) → OpenAPI → TypeScript types
- **For Designer internal:** Zod schemas (manual, TypeScript-native)
- **For shared MQTT messages:** JSON Schema → Zod + Pydantic (generated)

**Strategy:**

```
BuildingMOTIF API    →  OpenAPI  →  TS types (generated)
BMS IoT App API      →  OpenAPI  →  TS types (generated)
Future FMU API       →  OpenAPI  →  TS types (generated)

Designer internal    →  Zod schemas (manual, ergonomic)

MQTT message contracts  →  JSON Schema  →  Zod + Pydantic (generated)
```

**Tools:**

- `openapi-typescript` for API clients
- Zod for internal TypeScript schemas
- `json-schema-to-zod` + `datamodel-code-generator` for MQTT

**Example Architecture:**

**1. API Boundary (BuildingMOTIF):**

```python
# BuildingMOTIF: apps/bms-buildingmotif/src/models/equipment.py
class Equipment(BaseModel):
    id: str
    name: str
    type: str
    points: list[Point]

# FastAPI auto-generates /openapi.json
```

```bash
# Designer: Generate TypeScript types
npx openapi-typescript http://localhost:8000/openapi.json \
  -o src/lib/api/buildingmotif-types.ts
```

```typescript
// Designer: Use generated types
import type { Equipment } from "@/lib/api/buildingmotif-types";

const equipment: Equipment = await fetch("/api/v1/equipment/eq_123").then((r) =>
  r.json(),
);
```

**2. Designer Internal (Zod):**

```typescript
// Designer: apps/designer/src/lib/schemas/nodes/types.ts
export const NodeTypeSchema = z.enum([
  "input.sensor",
  "logic.compare",
  "output.actuator",
]);

export type NodeType = z.infer<typeof NodeTypeSchema>;

// Use Zod for validation
const result = NodeTypeSchema.safeParse(userInput);
```

**3. MQTT Message Contracts (JSON Schema):**

```json
// packages/mqtt_topics/schemas/controller-point.json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "title": "ControllerPoint",
  "type": "object",
  "properties": {
    "point_id": { "type": "string" },
    "node_type": {
      "type": "string",
      "enum": ["input.sensor", "output.actuator"]
    },
    "value": { "type": "number" }
  },
  "required": ["point_id", "node_type", "value"]
}
```

```bash
# Generate Zod (TypeScript)
json-schema-to-zod schemas/controller-point.json > dist/controller-point.zod.ts

# Generate Pydantic (Python)
datamodel-codegen --input schemas/controller-point.json --output dto/controller_point.py
```

**Pros:**

- ✅ Pragmatic hybrid approach (right tool for right job)
- ✅ OpenAPI for API boundaries (industry standard, already planned)
- ✅ Zod for internal TypeScript (ergonomic, native)
- ✅ JSON Schema for truly shared types (MQTT contracts)
- ✅ Minimal cognitive overhead (clear boundaries)
- ✅ Sustainable for solo developer (standard tools)
- ✅ Aligns with BuildingMOTIF integration spec

**Cons:**

- ❌ Still multiple schema systems (but clearly separated by use case)
- ❌ Some manual maintenance (Designer internal schemas)
- ❌ Requires discipline (knowing which tool for which boundary)

**Verdict:** **RECOMMENDED** - Balances pragmatism with type safety.

---

## 5. Comparative Analysis

### Comparison Matrix

| Option                                  | Type Safety | Maintainability | Cognitive Load | Tooling Complexity | Alignment with Constraints        |
| --------------------------------------- | ----------- | --------------- | -------------- | ------------------ | --------------------------------- |
| 1. Current (Manual)                     | ⚠️ Low      | ⚠️ Low          | ⚠️ High        | ✅ Low             | ✅ Yes                            |
| 2. OpenAPI SSoT                         | ✅ High     | ✅ High         | ✅ Medium      | ✅ Low             | ✅ Yes (BuildingMOTIF)            |
| 3. JSON Schema SSoT                     | ✅ High     | ✅ Medium       | ⚠️ High        | ⚠️ Medium          | ✅ Yes                            |
| 4. TS-First Codegen                     | ✅ High     | ⚠️ Medium       | ⚠️ High        | ❌ High            | ⚠️ Conflicts with FastAPI         |
| 5. Protobuf                             | ✅ High     | ✅ High         | ⚠️ High        | ⚠️ Medium          | ⚠️ Overkill                       |
| 6. GraphQL SDL                          | ✅ High     | ✅ High         | ⚠️ High        | ⚠️ Medium          | ❌ Paradigm shift                 |
| 7. TS + Python Stubs                    | ⚠️ Medium   | ⚠️ Low          | ⚠️ Medium      | ⚠️ Medium          | ❌ No runtime validation          |
| 8. Deno/Bun Unified                     | ✅ High     | ✅ High         | ✅ Low         | ✅ Low             | ❌ **REJECTED** (Python required) |
| 9. Hybrid (OpenAPI + Zod + JSON Schema) | ✅ High     | ✅ High         | ✅ Medium      | ✅ Low             | ✅ Yes                            |

### Scoring by Priority

**For Solo Developer Maintainability:**

1. **Option 9 (Hybrid)**: 9/10 - Clear boundaries, standard tools
2. **Option 2 (OpenAPI)**: 8/10 - Excellent for APIs, incomplete for full stack
3. **Option 3 (JSON Schema)**: 7/10 - Good for shared contracts, verbose
4. **Option 8 (Unified Runtime)**: N/A - Rejected due to Python requirement
5. **Option 1 (Current)**: 4/10 - Unsustainable at scale

**For Type Safety:**

1. **Option 9 (Hybrid)**: 9/10 - Type-safe everywhere that matters
2. **Option 2 (OpenAPI)**: 8/10 - Strong for APIs
3. **Option 5 (Protobuf)**: 9/10 - Very strong, but overkill
4. **Option 3 (JSON Schema)**: 8/10 - Strong, but less ergonomic
5. **Option 1 (Current)**: 3/10 - Weak, manual sync

**For Cognitive Load Reduction:**

1. **Option 9 (Hybrid)**: 8/10 - Clear mental model, standard patterns
2. **Option 2 (OpenAPI)**: 7/10 - Simple, but incomplete
3. **Option 8 (Unified Runtime)**: N/A - Rejected
4. **Option 1 (Current)**: 3/10 - High mental burden
5. **Option 3 (JSON Schema)**: 5/10 - Additional abstraction layer

---

## 6. Trade-offs and Decision Factors

### Key Trade-offs

**Option 2 (OpenAPI) vs Option 9 (Hybrid):**

| Factor            | OpenAPI Only                         | Hybrid (OpenAPI + Zod + JSON Schema)   |
| ----------------- | ------------------------------------ | -------------------------------------- |
| API Boundaries    | ✅ Excellent (Python → OpenAPI → TS) | ✅ Excellent (same approach)           |
| Designer Internal | ❌ Manual Zod (no sync)              | ✅ Manual Zod (acknowledged, accepted) |
| MQTT Contracts    | ❌ Manual sync                       | ✅ JSON Schema (generated both sides)  |
| Tooling           | ✅ Simple (one tool)                 | ⚠️ Multiple tools (but standard)       |
| Mental Model      | ✅ Very simple                       | ✅ Clear boundaries                    |
| Completeness      | ❌ Incomplete solution               | ✅ Complete solution                   |

**Verdict:** Hybrid approach is more complete, worth the additional (minimal) complexity.

**Option 3 (JSON Schema) vs Option 9 (Hybrid):**

| Factor                 | JSON Schema SSoT                             | Hybrid                      |
| ---------------------- | -------------------------------------------- | --------------------------- |
| Single Source of Truth | ✅ Yes (JSON Schema for all)                 | ⚠️ No (but intentional)     |
| Ergonomics             | ❌ Verbose JSON Schema                       | ✅ Native Zod/Pydantic      |
| Language Features      | ❌ Loses Zod transforms, Pydantic validators | ✅ Preserves all features   |
| Use Case Fit           | ⚠️ Good for shared contracts only            | ✅ Right tool for right job |

**Verdict:** Hybrid preserves language-native ergonomics, which matters for solo developer productivity.

### Decision Priorities

**Top 3 Decision Factors (from requirements):**

1. **Maintainability** (highest priority)

   - Winner: Option 9 (Hybrid)
   - Clear boundaries reduce maintenance burden

2. **Cognitive Load Reduction**

   - Winner: Option 9 (Hybrid)
   - Standard tools, clear mental model

3. **Type Safety**
   - Winner: Option 9 (Hybrid)
   - Type-safe everywhere that matters (API boundaries + MQTT contracts)

### Weighted Analysis

**Scoring (0-10 scale):**

| Option         | Maintainability (40%) | Cognitive Load (30%) | Type Safety (20%) | Tooling (10%) | **Weighted Score** |
| -------------- | --------------------- | -------------------- | ----------------- | ------------- | ------------------ |
| 1. Current     | 4                     | 3                    | 3                 | 9             | **4.1**            |
| 2. OpenAPI     | 8                     | 7                    | 8                 | 9             | **7.8**            |
| 3. JSON Schema | 7                     | 5                    | 8                 | 7             | **6.7**            |
| 9. Hybrid      | 9                     | 8                    | 9                 | 8             | **8.6** ⭐         |

**Option 9 (Hybrid) wins decisively.**

---

## 7. Use Case Fit Analysis

### Match to Specific Use Case

**Your Architecture:**

- TypeScript-strong solo developer
- 4+ Python services (BMS IoT, BuildingMOTIF, FMU, AI)
- Mix of API calls (REST) and pub/sub messaging (MQTT)
- Maintainability and cognitive load are top concerns

**How Option 9 (Hybrid) Fits:**

**API Boundaries (REST):**

- BuildingMOTIF → FastAPI → OpenAPI → Designer TypeScript types ✅
- BMS IoT App → Future REST API → OpenAPI → Designer types ✅
- FMU Service → Future API → OpenAPI → Designer types ✅
- **Perfect Fit:** Industry standard, already planned in BuildingMOTIF spec

**Pub/Sub Messaging (MQTT):**

- Designer ↔ BMS IoT App → MQTT JSON payloads
- Shared message contracts → JSON Schema → Zod (TS) + Pydantic (Python) ✅
- **Perfect Fit:** True single source of truth for bidirectional messaging

**Designer Internal (Visual Programming):**

- React Flow nodes, Zustand state, form validation → Zod schemas ✅
- **Perfect Fit:** TypeScript-native, ergonomic, no synchronization needed

**Boundary Clarity:**

```
┌──────────────────────────────────────────────────────────┐
│                Designer (TypeScript)                     │
│  - Internal: Zod (manual, native TypeScript)            │
│  - API clients: Generated types (from OpenAPI)          │
│  - MQTT: Generated Zod (from JSON Schema)               │
└────────────┬───────────────────────────┬─────────────────┘
             │                           │
    REST API │                   MQTT    │
             ↓                           ↓
┌─────────────────────┐    ┌────────────────────────────┐
│  BuildingMOTIF      │    │    BMS IoT App             │
│  - Pydantic models  │    │    - Pydantic DTOs         │
│  - Auto OpenAPI     │    │    - Generated Pydantic    │
│                     │    │      (from JSON Schema)    │
└─────────────────────┘    └────────────────────────────┘
```

**No Dealbreakers:**

- ✅ Preserves Python ecosystem (BuildingMOTIF, PyFMI, BACnet)
- ✅ Aligns with BuildingMOTIF integration spec
- ✅ Works with current MQTT architecture
- ✅ Sustainable for solo developer

---

## 8. Real-World Evidence

### OpenAPI TypeScript Generation

**Production Usage:**

- Stripe API (TypeScript clients generated from OpenAPI)
- GitHub API (TypeScript SDK via OpenAPI)
- Twilio API (openapi-typescript in official docs)

**Community Feedback:**

- `openapi-typescript` (11k+ stars, actively maintained)
- Fast generation (~1s for most APIs)
- Excellent type inference in TypeScript

**Known Gotchas:**

- Requires running server to generate types (mitigated: commit generated files)
- Date serialization (OpenAPI strings → TS Date requires runtime parsing)
- Optional vs required fields (OpenAPI spec must be precise)

**Mitigation:**

- Generate types in CI/CD pipeline
- Commit generated files to git (versioned, diffable)
- Use FastAPI's strict Pydantic mode (explicit required fields)

### JSON Schema Code Generation

**Production Usage:**

- AWS SDK (JSON Schema → multiple language SDKs)
- AsyncAPI (message schemas → TypeScript + Python)

**Community Feedback:**

- `json-schema-to-zod` (2k+ stars, solid tool)
- `datamodel-code-generator` (2k+ stars, Pydantic official recommendation)

**Known Gotchas:**

- Generated Zod less elegant than hand-written (acceptable for shared contracts)
- Requires build step (mitigated: commit generated files)

**Mitigation:**

- Use JSON Schema only for MQTT contracts (limited scope)
- Version generated files (track changes in git)

### Zod for TypeScript

**Production Usage:**

- Vercel (tRPC uses Zod extensively)
- Clerk (auth library uses Zod for validation)
- Thousands of production apps

**Community Feedback:**

- 32k+ GitHub stars
- Excellent TypeScript inference
- Ergonomic API, minimal boilerplate

**No significant gotchas:** Well-established, stable library.

---

## 9. Recommendations

### Primary Recommendation: Hybrid Type Safety Strategy (Option 9)

**Strategy:**

1. **Python APIs → OpenAPI → TypeScript Types**

   - Use for: BuildingMOTIF API, BMS IoT App API (future), FMU Service API (future)
   - Tool: `openapi-typescript`
   - Benefit: Industry standard, automatic type generation
   - Example: `/docs/specs/2025-10-24-buildingmotif-integration-spec.md` (already planned)

2. **Zod for Designer-Internal Schemas**

   - Use for: Visual programming nodes, UI forms, Zustand state
   - Tool: Zod (manual schemas)
   - Benefit: TypeScript-native, ergonomic, no synchronization overhead
   - Example: `apps/designer/src/lib/schemas/nodes/types.ts`

3. **JSON Schema for MQTT Message Contracts**
   - Use for: Designer ↔ BMS IoT App MQTT messages
   - Tool: `json-schema-to-zod` + `datamodel-code-generator`
   - Benefit: Single source of truth for bidirectional messaging
   - Example: `packages/mqtt_topics/schemas/` (new)

**Why This Recommendation:**

✅ **Addresses Top 3 Concerns:**

1. **Multi-Language Complexity:** Clear boundaries (OpenAPI for APIs, JSON Schema for MQTT)
2. **Polyglot Architecture:** Standard patterns sustainable across 4+ services
3. **Cognitive Load:** Clear mental model (each schema type has specific purpose)

✅ **Fits Constraints:**

- Preserves Python ecosystem (BuildingMOTIF, PyFMI, BACnet)
- Aligns with existing BuildingMOTIF integration spec
- Sustainable for solo developer (standard tools, minimal setup)

✅ **Maintainable:**

- Type safety at boundaries (APIs, MQTT)
- Internal flexibility (Zod for Designer)
- Automated generation (reduces manual sync)

### Alternative Recommendation: OpenAPI-Only (Option 2)

**Strategy:**

1. **Python APIs → OpenAPI → TypeScript Types** (same as above)
2. **Zod for Designer-Internal Schemas** (manual, no sync)
3. **MQTT Messages:** Manual Pydantic + Manual Zod (current approach)

**When to Choose:**

- If JSON Schema tooling feels like overkill
- If MQTT contracts are simple and stable
- If you prefer simplicity over completeness

**Trade-off:**

- ⚠️ MQTT message contracts still manually synced
- ⚠️ Type drift risk for MQTT payloads

---

## 10. Architecture Decision Record (ADR)

### ADR-001: Hybrid Type Safety Strategy for Polyglot Architecture

**Status:** 🔖 **PROPOSED** (Tech Debt - To Address Post-BuildingMOTIF Integration)

**Date:** 2025-10-31

**Context:**

The BMS Supervisor Controller uses a polyglot architecture with TypeScript (Designer frontend) and multiple Python backend services (BMS IoT App, BuildingMOTIF, future FMU/AI services). As the system grows, maintaining type safety and schema consistency across language boundaries has become a maintainability concern for the solo developer.

**Current State:**

- Manual schema synchronization (Zod in TypeScript, Pydantic in Python)
- Type drift risk
- High cognitive load maintaining parallel schema systems
- No compile-time guarantees of cross-language compatibility

**Decision Drivers:**

1. Maintainability (highest priority)
2. Cognitive load reduction (solo developer)
3. Type safety across language boundaries
4. Alignment with existing commitments (BuildingMOTIF FastAPI integration)
5. Sustainable for 4+ services

**Considered Options:**

1. Current approach (manual sync) - **Rejected** (unsustainable)
2. OpenAPI SSoT - **Good** (incomplete solution)
3. JSON Schema SSoT - **Good** (verbose, loses language features)
4. TypeScript-first codegen - **Rejected** (conflicts with FastAPI)
5. Protobuf - **Rejected** (overkill)
6. GraphQL SDL - **Rejected** (paradigm shift)
7. TS + Python stubs - **Rejected** (no runtime validation)
8. Unified Runtime (Deno/Bun) - **Rejected** (cannot use BuildingMOTIF/PyFMI)
9. Hybrid (OpenAPI + Zod + JSON Schema) - **Selected**

**Decision:**

Adopt a **Hybrid Type Safety Strategy**:

1. **API Boundaries:** Python (Pydantic) → OpenAPI → TypeScript types (generated)
2. **Designer Internal:** Zod schemas (manual, TypeScript-native)
3. **MQTT Contracts:** JSON Schema → Zod + Pydantic (generated)

**Consequences:**

**Positive:**

- ✅ Type safety at critical boundaries (APIs, MQTT)
- ✅ Reduced type drift risk (automated generation)
- ✅ Sustainable for solo developer (standard tools, clear boundaries)
- ✅ Preserves language-native ergonomics (Zod for TS, Pydantic for Python)
- ✅ Aligns with BuildingMOTIF integration spec (Pydantic → OpenAPI)
- ✅ Clear mental model (each schema type has specific purpose)

**Negative:**

- ⚠️ Multiple schema systems (but intentional, with clear boundaries)
- ⚠️ Designer internal schemas still manual (accepted trade-off for ergonomics)
- ⚠️ Requires discipline (knowing which tool for which boundary)

**Neutral:**

- Additional tooling (`openapi-typescript`, `json-schema-to-zod`, `datamodel-code-generator`)
- Build-time generation step (mitigated: commit generated files)

**Implementation Notes:**

See Section 11 (Implementation Roadmap) for phased approach.

**References:**

- BuildingMOTIF Integration Spec: `/docs/specs/2025-10-24-buildingmotif-integration-spec.md`
- openapi-typescript: https://github.com/drwpow/openapi-typescript
- json-schema-to-zod: https://github.com/StefanTerdell/json-schema-to-zod
- datamodel-code-generator: https://github.com/koxudaxi/datamodel-code-generator

---

## 11. Implementation Roadmap

**Status:** Tech Debt - To Address Post-BuildingMOTIF Integration (Phase 1-3)

**Priority:** Medium
**Estimated Effort:** 2-3 weeks
**When:** After BuildingMOTIF/ASHRAE 223P mapping UI is complete

### Phase 1: OpenAPI Client Generation (BuildingMOTIF API)

**Duration:** 3-4 days

**Tasks:**

1. **Setup Tooling**

   ```bash
   cd apps/designer
   pnpm add -D openapi-typescript
   ```

2. **Create Generation Script**

   ```json
   // apps/designer/package.json
   {
     "scripts": {
       "generate:buildingmotif-types": "openapi-typescript http://localhost:8000/openapi.json -o src/lib/api/buildingmotif-types.ts"
     }
   }
   ```

3. **Generate Types**

   ```bash
   # Start BuildingMOTIF server
   cd apps/bms-buildingmotif
   uvicorn src.main:app --reload

   # Generate TypeScript types
   cd apps/designer
   pnpm generate:buildingmotif-types
   ```

4. **Create API Client Wrapper**

   ```typescript
   // apps/designer/src/lib/api/buildingmotif-client.ts
   import type { paths } from "./buildingmotif-types";

   export class BuildingMotifClient {
     async createEquipment(
       data: paths["/api/v1/equipment"]["post"]["requestBody"]["content"]["application/json"],
     ) {
       // Implementation
     }
   }
   ```

5. **Update Designer to Use Generated Types**
   - Replace manual type definitions with generated types
   - Update API calls to use typed client

**Success Criteria:**

- ✅ TypeScript types auto-generated from BuildingMOTIF OpenAPI spec
- ✅ Designer API calls are type-safe (compile-time errors for API changes)
- ✅ Zero manual type definitions for BuildingMOTIF API

### Phase 2: JSON Schema for MQTT Contracts

**Duration:** 4-5 days

**Tasks:**

1. **Create JSON Schema Definitions**

   ```bash
   mkdir -p packages/mqtt_topics/schemas
   ```

   ```json
   // packages/mqtt_topics/schemas/controller-point.json
   {
     "$schema": "http://json-schema.org/draft-07/schema#",
     "title": "ControllerPoint",
     "type": "object",
     "properties": {
       "point_id": { "type": "string" },
       "organization_id": { "type": "string" },
       "site_id": { "type": "string" },
       "device_id": { "type": "string" },
       "node_type": {
         "type": "string",
         "enum": ["input.sensor", "logic.compare", "output.actuator"]
       },
       "value": { "type": "number" },
       "timestamp": { "type": "string", "format": "date-time" }
     },
     "required": [
       "point_id",
       "organization_id",
       "site_id",
       "device_id",
       "node_type",
       "value"
     ]
   }
   ```

2. **Setup Code Generation**

   ```json
   // packages/mqtt_topics/package.json
   {
     "scripts": {
       "generate:zod": "json-schema-to-zod schemas/*.json -o src/generated/",
       "generate:pydantic": "datamodel-codegen --input schemas/ --output python/generated/"
     }
   }
   ```

3. **Generate TypeScript (Zod)**

   ```bash
   cd packages/mqtt_topics
   pnpm add -D json-schema-to-zod
   pnpm generate:zod
   ```

4. **Generate Python (Pydantic)**

   ```bash
   cd packages/mqtt_topics
   pip install datamodel-code-generator
   pnpm generate:pydantic
   ```

5. **Update MQTT Message Handlers**
   - Replace manual DTOs with generated schemas
   - Update validation logic to use generated Zod/Pydantic

**Success Criteria:**

- ✅ MQTT message schemas defined once (JSON Schema)
- ✅ Zod validation generated for TypeScript
- ✅ Pydantic models generated for Python
- ✅ Zero manual synchronization for MQTT contracts

### Phase 3: Consolidate Existing Zod Schemas

**Duration:** 2-3 days

**Tasks:**

1. **Audit Existing Schemas**

   ```bash
   cd apps/designer
   find src/lib/schemas -name "*.ts" -type f
   ```

2. **Identify Shared vs Internal**

   - Shared: MQTT messages → migrate to JSON Schema (Phase 2)
   - Internal: Visual programming, UI state → keep as Zod

3. **Document Schema Boundaries**

   ```markdown
   # Schema Decision Matrix

   | Schema Type         | Technology        | Location                              | Purpose                    |
   | ------------------- | ----------------- | ------------------------------------- | -------------------------- |
   | API Types           | OpenAPI → TS      | `src/lib/api/*-types.ts`              | Generated from Python APIs |
   | Internal Validation | Zod               | `src/lib/schemas/`                    | Designer-specific logic    |
   | MQTT Contracts      | JSON Schema → Zod | `packages/mqtt_topics/src/generated/` | Cross-service messaging    |
   ```

4. **Create Schema README**

   ```markdown
   // apps/designer/src/lib/schemas/README.md

   # Schema Organization

   ## Internal Schemas (Manual Zod)

   - Visual programming nodes (`nodes/`)
   - UI forms (`forms/`)
   - Zustand state (`state/`)

   ## Generated Schemas (Do Not Edit)

   - API types: `src/lib/api/*-types.ts` (from OpenAPI)
   - MQTT messages: See `packages/mqtt_topics`
   ```

**Success Criteria:**

- ✅ Clear schema boundaries documented
- ✅ Developers know which schemas to edit vs regenerate
- ✅ No confusion about schema sources

### Phase 4: Automation and CI/CD

**Duration:** 2-3 days

**Tasks:**

1. **Commit Generated Files**

   ```bash
   git add apps/designer/src/lib/api/buildingmotif-types.ts
   git add packages/mqtt_topics/src/generated/
   git commit -m "chore: add generated type files"
   ```

2. **Create Pre-commit Hook**

   ```bash
   # .husky/pre-commit
   #!/bin/sh

   # Regenerate types if Python schemas changed
   if git diff --cached --name-only | grep -q "apps/bms-buildingmotif/src/models/"; then
     echo "⚠️  Python schemas changed. Regenerate TypeScript types:"
     echo "  cd apps/designer && pnpm generate:buildingmotif-types"
     exit 1
   fi
   ```

3. **Add CI Check**

   ```yaml
   # .github/workflows/ci.yml
   - name: Check generated types are up-to-date
     run: |
       pnpm generate:buildingmotif-types
       git diff --exit-code apps/designer/src/lib/api/
   ```

4. **Update Developer Docs**

   ```markdown
   # CLAUDE.md - Add section:

   ## Type Safety Strategy

   ### API Types (Generated from OpenAPI)

   - **Don't edit**: `apps/designer/src/lib/api/*-types.ts`
   - **Regenerate**: `pnpm generate:buildingmotif-types`

   ### MQTT Contracts (Generated from JSON Schema)

   - **Edit**: `packages/mqtt_topics/schemas/*.json`
   - **Regenerate**: `cd packages/mqtt_topics && pnpm generate:zod && pnpm generate:pydantic`
   ```

**Success Criteria:**

- ✅ Generated files tracked in git (visible diffs)
- ✅ CI catches out-of-date generated types
- ✅ Developer workflow documented

### Total Effort Estimate

**Total Duration:** 2-3 weeks (11-15 days)

**Breakdown:**

- Phase 1: 3-4 days (OpenAPI generation)
- Phase 2: 4-5 days (JSON Schema for MQTT)
- Phase 3: 2-3 days (Consolidation)
- Phase 4: 2-3 days (Automation)

**When to Schedule:**

Priority: **Medium** (important but not urgent)

**Dependencies:**

- ✅ BuildingMOTIF integration spec complete
- ✅ ASHRAE 223P mapping UI complete (Phase 1)
- ✅ At least one MQTT contract finalized

**Trigger:** After Phase 3 of BuildingMOTIF integration (223P Integration complete)

---

## 12. Risk Mitigation

### Risk 1: Generated Types Out of Sync

**Scenario:** Python schemas change, TypeScript types not regenerated, runtime errors.

**Likelihood:** Medium
**Impact:** Medium (runtime errors in production)

**Mitigation:**

1. Commit generated files to git (visible diffs in PRs)
2. CI/CD check for out-of-date types
3. Pre-commit hook warns if Python schemas changed
4. Document regeneration process clearly

### Risk 2: JSON Schema Tooling Breaks

**Scenario:** `json-schema-to-zod` or `datamodel-code-generator` stops working or generates invalid code.

**Likelihood:** Low
**Impact:** High (blocks MQTT communication)

**Mitigation:**

1. Pin exact versions in package.json
2. Commit generated files (can continue working even if generation breaks)
3. Have manual fallback (write Zod/Pydantic manually if needed)
4. Limited scope (only MQTT contracts use JSON Schema)

### Risk 3: OpenAPI Generation Requires Running Server

**Scenario:** BuildingMOTIF server must be running to regenerate types, slows down development.

**Likelihood:** Medium
**Impact:** Low (developer inconvenience)

**Mitigation:**

1. Commit generated files (most dev work doesn't require regeneration)
2. Docker Compose for easy local BuildingMOTIF startup
3. Cache OpenAPI spec (regenerate only when schemas change)

### Risk 4: Multiple Schema Systems Cause Confusion

**Scenario:** Developer unsure which schema system to use for new feature.

**Likelihood:** Medium
**Impact:** Low (waste time, wrong choice)

**Mitigation:**

1. Clear documentation (Schema Decision Matrix)
2. README in schema directories
3. Code review checklist (verify correct schema choice)
4. Examples for each pattern

---

## 13. References and Resources

### Tools

**OpenAPI TypeScript Generation:**

- openapi-typescript: https://github.com/drwpow/openapi-typescript
- OpenAPI 3.0 Spec: https://swagger.io/specification/
- FastAPI OpenAPI Docs: https://fastapi.tiangolo.com/tutorial/metadata/

**JSON Schema Code Generation:**

- json-schema-to-zod: https://github.com/StefanTerdell/json-schema-to-zod
- datamodel-code-generator: https://github.com/koxudaxi/datamodel-code-generator
- JSON Schema Spec: https://json-schema.org/

**Validation Libraries:**

- Zod: https://github.com/colinhacks/zod
- Pydantic: https://docs.pydantic.dev/

### Documentation

**Project Specs:**

- BuildingMOTIF Integration Spec: `/docs/specs/2025-10-24-buildingmotif-integration-spec.md`
- ASHRAE 223P Mapping Popup Spec: `/docs/specs/2025-10-30-phase-1-223p-mapping-popup-spec.md`

**Community Resources:**

- "Generating TypeScript from OpenAPI" (LogRocket): https://blog.logrocket.com/generating-typescript-openapi/
- "Type-Safe MQTT with TypeScript and Pydantic" (Medium): Example patterns
- Stripe API TypeScript SDK (real-world OpenAPI example): https://github.com/stripe/stripe-node

### Comparative Articles

- "Protobuf vs JSON Schema" (AWS): When to use each
- "API-First Development with OpenAPI" (Swagger): Best practices
- "GraphQL vs REST" (Apollo): Trade-offs and decision factors

---

## 14. Appendices

### Appendix A: Example Generated Code

**OpenAPI → TypeScript (BuildingMOTIF):**

```typescript
// Generated: apps/designer/src/lib/api/buildingmotif-types.ts

export interface paths {
  "/api/v1/equipment": {
    get: {
      responses: {
        200: {
          content: {
            "application/json": Equipment[];
          };
        };
      };
    };
    post: {
      requestBody: {
        content: {
          "application/json": EquipmentCreate;
        };
      };
      responses: {
        201: {
          content: {
            "application/json": Equipment;
          };
        };
      };
    };
  };
}

export interface Equipment {
  id: string;
  name: string;
  type: string;
  points: Point[];
  validation_status: "valid" | "warning" | "error";
}

export interface EquipmentCreate {
  name: string;
  type: string;
  points: PointCreate[];
}
```

**JSON Schema → Zod (MQTT Contract):**

```typescript
// Generated: packages/mqtt_topics/src/generated/controller-point.zod.ts

import { z } from "zod";

export const ControllerPointSchema = z.object({
  point_id: z.string(),
  organization_id: z.string(),
  site_id: z.string(),
  device_id: z.string(),
  node_type: z.enum(["input.sensor", "logic.compare", "output.actuator"]),
  value: z.number(),
  timestamp: z.string().datetime(),
});

export type ControllerPoint = z.infer<typeof ControllerPointSchema>;
```

**JSON Schema → Pydantic (MQTT Contract):**

```python
# Generated: packages/mqtt_topics/python/generated/controller_point.py

from datetime import datetime
from enum import Enum
from pydantic import BaseModel

class NodeType(str, Enum):
    INPUT_SENSOR = "input.sensor"
    LOGIC_COMPARE = "logic.compare"
    OUTPUT_ACTUATOR = "output.actuator"

class ControllerPoint(BaseModel):
    point_id: str
    organization_id: str
    site_id: str
    device_id: str
    node_type: NodeType
    value: float
    timestamp: datetime
```

### Appendix B: Schema Decision Flowchart

```
┌─────────────────────────────────────┐
│ Need to define a schema/type?       │
└─────────────┬───────────────────────┘
              │
              ↓
    ┌─────────────────────┐
    │ What's the boundary? │
    └─────────┬───────────┘
              │
      ┌───────┼───────┐
      ↓       ↓       ↓
  ┌────┐  ┌────┐  ┌────┐
  │API │  │MQTT│  │UI  │
  └─┬──┘  └─┬──┘  └─┬──┘
    │       │       │
    ↓       ↓       ↓
┌────────────────────────────────┐
│ OpenAPI (Python → TS)          │ ← Use for REST APIs
│ - Define in Pydantic (Python)  │
│ - Generate TS types            │
└────────────────────────────────┘

┌────────────────────────────────┐
│ JSON Schema (TS ↔ Python)      │ ← Use for MQTT contracts
│ - Define in JSON Schema        │
│ - Generate Zod + Pydantic      │
└────────────────────────────────┘

┌────────────────────────────────┐
│ Zod (TypeScript only)          │ ← Use for Designer internal
│ - Define manually in Zod       │
│ - No sync needed               │
└────────────────────────────────┘
```

### Appendix C: Cost-Benefit Analysis

**Current Approach (Manual Sync):**

| Factor              | Cost                                | Benefit            |
| ------------------- | ----------------------------------- | ------------------ |
| Initial Setup       | $0 (already done)                   | Simple, no tooling |
| Ongoing Maintenance | High (manual sync, type drift risk) | None               |
| Developer Time      | 2-3 hours/week (sync, debugging)    | None               |
| Error Rate          | Medium (easy to forget updates)     | None               |

**Hybrid Approach (Recommended):**

| Factor              | Cost                               | Benefit                 |
| ------------------- | ---------------------------------- | ----------------------- |
| Initial Setup       | 2-3 weeks (one-time)               | Automated generation    |
| Ongoing Maintenance | Low (regenerate on schema change)  | Type safety             |
| Developer Time      | 10 min/week (regenerate if needed) | 2+ hours saved/week     |
| Error Rate          | Low (compile-time checks)          | Prevents runtime errors |

**ROI Calculation:**

- **Setup Cost:** 2-3 weeks (one-time investment)
- **Time Saved:** 2-3 hours/week (manual sync eliminated)
- **Break-even:** ~7-10 weeks
- **Annual Benefit:** 100+ hours saved, fewer production bugs

**Conclusion:** High ROI, justifies upfront investment.

---

## Document Information

**Workflow:** BMad Research Workflow - Technical Research v2.0
**Generated:** 2025-10-31
**Research Type:** Technology Stack Evaluation - Type Safety Strategy
**Status:** 🔖 **TECH DEBT** - Medium Priority
**Next Review:** After BuildingMOTIF Phase 1-3 completion

**Related Documents:**

- `/docs/specs/2025-10-24-buildingmotif-integration-spec.md`
- `/docs/specs/2025-10-30-phase-1-223p-mapping-popup-spec.md`
- `/docs/architecture.md` (outdated, not referenced)

**Tech Debt Tracking:**

- **Priority:** Medium (important for scalability, not blocking current work)
- **Effort:** 2-3 weeks
- **Trigger:** Completion of BuildingMOTIF Phase 3 (223P Integration)
- **Owner:** Amol (solo developer)

---

_This technical research report was generated using the BMad Method Research Workflow, combining systematic technology evaluation frameworks with real-time research and analysis._
