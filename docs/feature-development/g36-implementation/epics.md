# G36 Visual Programming Blocks - Epic Breakdown

**Author:** Amol
**Date:** 2025-11-26
**Project Level:** 4
**Target Scale:** Enterprise BMS Platform Feature

---

## Overview

This document provides the detailed epic breakdown for G36 Visual Programming Blocks, expanding on the high-level epic list in the [PRD](./PRD.md).

Each epic includes:

- Expanded goal and value proposition
- Complete story breakdown with user stories
- Acceptance criteria for each story
- Story sequencing and dependencies

**Epic Sequencing Principles:**

- Epic 1 establishes foundational FMU integration with POC-first approach
- Subsequent epics build progressively, each delivering significant end-to-end value
- Stories within epics are vertically sliced and sequentially ordered
- No forward dependencies - each story builds only on previous work

---

## Epic 1: G36 Reheat FMU Block Foundation

**Goal:** Prove FMU integration works with a lightweight POC, build the backend Control Sequence API service, then integrate with Designer.

**Value:** De-risks the biggest unknown (Modelica FMU integration) before investing in UI development.

**Phases:**

- **Phase 1A**: POC & Backend Service (Python) - Current Focus
- **Phase 1B**: Designer Integration (TypeScript/React) - After Backend

---

## Phase 1A: POC & Backend Service

**App:** `control-sequence-api-app` (renamed from `g36-api-app`)

---

### Story 1.1: FMU Loading POC ✅

As a developer,
I want to load and execute a Modelica FMU in Python,
So that we validate the core FMU integration approach works.

**Acceptance Criteria:**

1. Load G36 Reheat FMU file using FMPy or PyFMI
2. Set sample input values (TZon, setpoints, etc.)
3. Step the FMU and read output values (yDam, yVal)
4. Document chosen library and approach
5. POC script runs successfully

**Prerequisites:** None

**Status:** Complete

---

### Story 1.2: FMU State & Lifecycle ✅

As a developer,
I want to understand FMU state management and lifecycle,
So that we know how to manage FMU instances in production.

**Acceptance Criteria:**

1. Document how states are managed in FMU
2. Determine if state save/restore is needed
3. Understand step-on-demand vs continuous execution
4. Verify FMU is a pure function of (inputs, simulation_time)

**Prerequisites:** Story 1.1

**Status:** Complete

---

### Story 1.3: FMU Execution & Validation ✅

As a developer,
I want to validate FMU execution behavior and performance,
So that we can design the API with confidence.

**Acceptance Criteria:**

1. Measure step execution time (~0.1ms)
2. Verify multiple concurrent instances work
3. Validate G36 outputs are reasonable
4. Test error handling with invalid inputs
5. Document memory footprint per instance

**Prerequisites:** Story 1.2

**Status:** Done

---

### Story 1.4: Document POC Findings ✅

As a developer,
I want to consolidate and document all POC findings,
So that we have a clear reference for G36 Service design decisions.

**Acceptance Criteria:**

1. All 13 POC questions answered in POC Findings spec
2. Recommendations for G36 Service design captured
3. Any blockers or concerns documented
4. Code examples for common patterns included
5. Architecture Decision Record (ADR) created

**Prerequisites:** Stories 1.1-1.3

**Status:** Review

**Output:** [POC Findings Spec](./specs/poc-findings.md)

---

### Story 1.5: Control Sequence API Tech Spec

As a developer,
I want a technical specification for the Control Sequence API,
So that implementation follows a clear, agreed-upon architecture.

**Acceptance Criteria:**

1. Service architecture defined
2. API design (REST and/or MQTT) specified
3. State management strategy documented
4. Integration points with bms-iot-app and Designer defined
5. Implementation stories derived from tech spec

**Prerequisites:** Story 1.4

**Output:** Architecture document with implementation story breakdown

---

### Story 1.6: Project Setup & Scaffolding

As a developer,
I want to set up the control-sequence-api-app project structure,
So that we have a foundation for implementing the API.

**Acceptance Criteria:**

1. pyproject.toml with dependencies (FastAPI, FMPy, pydantic-settings)
2. MVC folder structure: adapters/, config/, controllers/, dto/, models/, routers/
3. settings.py with pydantic-settings configuration
4. main.py with FastAPI app entry point
5. App runs with `uvicorn` and serves `/docs`

**Prerequisites:** Story 1.5

**Reference:** [Tech Spec Section 3](./specs/control-sequence-api-tech-spec.md#3-architecture)

---

### Story 1.7: Nginx Proxy Configuration

As a developer,
I want the control-sequence-api routed through the nginx proxy,
So that Designer can access the API through the unified gateway.

**Acceptance Criteria:**

1. Add `/control-sequence` location to nginx.conf.template
2. Add CONTROL_SEQUENCE_HOST and CONTROL_SEQUENCE_PORT to .env
3. Route `/control-sequence/*` → `http://${CONTROL_SEQUENCE_HOST}:${CONTROL_SEQUENCE_PORT}`
4. Update infra README with new service documentation
5. Verify proxy routing works with curl test

**Prerequisites:** Story 1.6

**Reference:** [infra/proxy/nginx.conf.template](../../infra/proxy/nginx.conf.template)

---

### Story 1.8: Reheat DTOs & Validation

As a developer,
I want Pydantic schemas for Reheat parameters, inputs, and outputs,
So that the API has type-safe request/response validation.

**Acceptance Criteria:**

1. ReheatParameters DTO with VCooMax, VHeaMax, VMin fields
2. ReheatInputs DTO with all FMU inputs (TZon, TCooSet, etc.) and Field validation
3. ReheatOutputs DTO with yDam, yVal, VSet_flow
4. Range validation (e.g., temps 250-350K)
5. Unit tests for DTO validation

**Prerequisites:** Story 1.7

**Reference:** [Tech Spec Section 4.2](./specs/control-sequence-api-tech-spec.md#42-requestresponse-schemas)

---

### Story 1.9: Schema Endpoint

As a developer,
I want a GET /schema endpoint that returns Reheat metadata,
So that Designer can dynamically render configuration panels.

**Acceptance Criteria:**

1. GET /api/v1/g36/reheat/schema endpoint
2. Returns parameters, inputs, outputs with defaults, ranges, units
3. Response matches tech spec schema format
4. OpenAPI documentation accurate

**Prerequisites:** Story 1.7

**Reference:** [Tech Spec Section 4.2](./specs/control-sequence-api-tech-spec.md#42-requestresponse-schemas)

---

### Story 1.10: FMU Adapter (Singleton)

As a developer,
I want an FMU adapter that manages FMU instance lifecycle,
So that the API can create, step, and delete FMU instances.

**Acceptance Criteria:**

1. fmu_adapter.py with singleton pattern
2. create_instance(instance_id, parameters) method
3. update_instance(instance_id, parameters) method (resets FMU)
4. step(instance_id, inputs, step_size) method
5. delete_instance(instance_id) method
6. Per-instance asyncio.Lock for thread safety
7. Lazy FMU loading with startup validation
8. Unit tests for adapter

**Prerequisites:** Story 1.7

**Reference:** [Tech Spec Section 3.4](./specs/control-sequence-api-tech-spec.md#34-key-design-decisions)

---

### Story 1.11: G36 Controller

As a developer,
I want a controller that orchestrates FMU adapter calls,
So that business logic is separated from routing.

**Acceptance Criteria:**

1. g36_controller.py with business logic
2. Validates inputs before calling adapter
3. Handles errors and returns appropriate responses
4. Unit tests for controller logic

**Prerequisites:** Story 1.10

**Reference:** [Tech Spec Section 3.2](./specs/control-sequence-api-tech-spec.md#32-component-responsibilities)

---

### Story 1.12: G36 Router & Endpoints

As a developer,
I want all Reheat API endpoints implemented,
So that Designer can interact with the Control Sequence API.

**Acceptance Criteria:**

1. POST /api/v1/g36/reheat/instances (create, idempotent)
2. PUT /api/v1/g36/reheat/instances/{instance_id} (update parameters)
3. POST /api/v1/g36/reheat/instances/{instance_id}/step (execute step)
4. DELETE /api/v1/g36/instances/{instance_id} (delete, sequence-agnostic)
5. All endpoints documented in OpenAPI
6. Integration tests for all endpoints

**Prerequisites:** Story 1.9, Story 1.11

**Reference:** [Tech Spec Section 4.1](./specs/control-sequence-api-tech-spec.md#41-endpoints)

---

### Story 1.13: Health Router

As a developer,
I want a health check endpoint,
So that we can monitor API status and active instance count.

**Acceptance Criteria:**

1. GET /api/v1/health endpoint
2. Returns status and active_instances count
3. Fast response (<10ms)

**Prerequisites:** Story 1.7

**Reference:** [Tech Spec Section 4.1](./specs/control-sequence-api-tech-spec.md#41-endpoints)

---

### Story 1.14: SHACL Validation Stub

As a developer,
I want a SHACL validation stub endpoint,
So that the API structure supports future validation without blocking Epic 1.

**Acceptance Criteria:**

1. POST /api/v1/g36/validate endpoint
2. Returns stub response (always valid)
3. Documented as "stub for future implementation"

**Prerequisites:** Story 1.7

**Reference:** [Tech Spec UC7](./specs/control-sequence-api-tech-spec.md#uc7-shacl-validation-stub)

---

### Story 1.15: API Documentation

As a developer,
I want clear API documentation in Swagger UI,
So that consumers understand how to use each endpoint.

**Acceptance Criteria:**

1. All endpoints have docstrings visible in /docs
2. Request/Response schemas include field descriptions
3. Examples provided for each endpoint
4. Error responses documented

**Prerequisites:** Story 1.12

**Reference:** [Tech Spec Section 5.3](./specs/control-sequence-api-tech-spec.md#53-api-documentation)

---

### Story 1.16: Designer OpenAPI Client Generation

As a developer,
I want TypeScript types and client generated from the API,
So that Designer can consume the API with type safety.

**Acceptance Criteria:**

1. Add generate:g36-client script to Designer package.json
2. Uses openapi-ts to generate from /openapi.json
3. Generated types in src/domains/g36/api/generated/
4. Types match Pydantic DTOs

**Prerequisites:** Story 1.12

**Reference:** [Tech Spec Section 5.1](./specs/control-sequence-api-tech-spec.md#51-openapi-schema-generation)

---

### Story 1.17: Unit & Integration Tests

As a developer,
I want comprehensive tests for the Control Sequence API,
So that we have confidence in the implementation.

**Acceptance Criteria:**

1. Unit tests for DTOs (validation edge cases)
2. Unit tests for adapter (mock FMU)
3. Unit tests for controller (mock adapter)
4. Integration tests for all endpoints (TestClient)
5. Tests run in CI

**Prerequisites:** Story 1.12

---

## Phase 1B: Designer Integration

**App:** `designer` (Next.js)

_Phase 1B starts after Phase 1A backend is complete._

---

### Story 1B.1: G36 Reheat Node Type & I/O Schema

As a developer,
I want to define the G36 Reheat node type and I/O schema in Designer,
So that the block structure matches the proven FMU interface.

**Acceptance Criteria:**

1. G36ReheatNode type added to schema
2. I/O connectors match FMU discovery (Story 1.2)
3. Types (Real/Boolean/Integer) match FMU
4. Schema tests pass

**Prerequisites:** Phase 1A complete

---

### Story 1B.2: G36 Reheat Block UI Component

As a building controls engineer,
I want to see the G36 Reheat block on the canvas with I/O connectors,
So that I can wire it to BACnet points.

**Acceptance Criteria:**

1. G36 Reheat block renders on canvas
2. I/O connectors visible and labeled
3. Block appears in palette under "Control Sequences"
4. Drag-drop works
5. Component tests pass

**Prerequisites:** Story 1B.1

---

### Story 1B.3: G36 Configuration Panel

As a building controls engineer,
I want to configure G36 block parameters,
So that I can customize the controller for my zone.

**Acceptance Criteria:**

1. Click opens configuration panel
2. Shows parameters: have_CO2Sen, heaCoi, design airflows
3. Conditional inputs appear/hide based on config
4. Uses existing side panel patterns

**Prerequisites:** Story 1B.1, Story 1B.2

---

## Epic 2: BACnet MQTT Write Integration

**Goal:** Implement BACnet writes via MQTT to enable actuator command outputs (yDam, yVal).

**Value:** Enables G36 outputs to control actual/simulated BACnet actuators.

**Estimated Stories:** 5-7

_Stories to be defined after Epic 1 completion._

---

## Epic 3: Two-Level Validation

**Goal:** Per-point automatic validation on wire + full SHACL validation via BuildingMOTIF on Run.

**Value:** Ensures semantic correctness of G36 block wiring before execution.

**Estimated Stories:** 6-8

_Stories to be defined after Epic 2 completion._

---

## Epic 4: Graph Execution with Scheduler

**Goal:** Run button triggers validation + graph execution; Scheduler node controls frequency.

**Value:** Enables complete end-to-end G36 control sequence execution.

**Estimated Stories:** 5-7

_Stories to be defined after Epic 3 completion._

---

## Epic 5: BOPTEST Integration Testing

**Goal:** End-to-end testing with `multizone_office_simple_air`; validate G36 with simulated building.

**Value:** Validates entire system works with realistic building simulation.

**Estimated Stories:** 4-6

_Stories to be defined after Epic 4 completion._

---

## Story Guidelines Reference

**Story Format:**

```
**Story [EPIC.N]: [Story Title]**

As a [user type],
I want [goal/desire],
So that [benefit/value].

**Acceptance Criteria:**
1. [Specific testable criterion]
2. [Another specific criterion]
3. [etc.]

**Prerequisites:** [Dependencies on previous stories, if any]
```

**Story Requirements:**

- **Vertical slices** - Complete, testable functionality delivery
- **Sequential ordering** - Logical progression within epic
- **No forward dependencies** - Only depend on previous work
- **AI-agent sized** - Completable in 2-4 hour focused session
- **Value-focused** - Integrate technical enablers into value-delivering stories

---

**For implementation:** Use the `create-story` workflow to generate individual story implementation plans from this epic breakdown.
