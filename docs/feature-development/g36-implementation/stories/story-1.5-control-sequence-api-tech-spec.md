# Story 1.5: Control Sequence API Tech Spec

## Story

**As a** developer,
**I want to** create a technical specification for the Control Sequence API,
**So that** we have a clear requirements-driven architecture document before implementation.

## Status

- **Epic**: 1 - G36 Reheat FMU Block Foundation
- **Status**: done
- **Priority**: P0 (Critical Path)
- **Estimate**: 4 hours

## Context

This story produces a tech spec document for the Control Sequence API service. The spec follows a requirements-first approach: define what the API needs to do, then derive the architecture and endpoints from those requirements.

The POC findings (Story 1.4) validated FMU integration. Now we need to design how the API will expose this functionality.

## Acceptance Criteria

- [x] Requirements documented (what the API must do)
- [x] Use cases defined (how clients will use the API)
- [x] MVC architecture defined (following building-semantics-api-app patterns)
- [x] API endpoints derived from requirements
- [x] Integration points defined (Designer integration, API documentation standards)
- [x] Implementation stories derived from tech spec

## Technical Requirements

### Tech Spec Structure

The output document should follow this structure:

```markdown
# Control Sequence API - Technical Specification

## 1. Requirements

### 1.1 Functional Requirements

- What must the API do?
- What operations does it support?

### 1.2 Non-Functional Requirements

- Performance (from POC: ~0.1ms per step)
- Scalability (multi-zone support)
- Recovery (simulation time persistence)

### 1.3 Constraints

- From POC findings (no native state persistence, must pre-validate inputs)

## 2. Use Cases

### UC1: [Use Case Name]

- Actor: [Who uses this]
- Trigger: [What starts this]
- Flow: [Step by step]
- Output: [What is returned]

## 3. Architecture

### 3.1 MVC Structure

- Follow building-semantics-api-app patterns exactly
- models/, controllers/, routers/, adapters/, dto/, config/

### 3.2 Component Responsibilities

- Each layer's responsibility

## 4. API Design

### 4.1 Endpoints

- Derived from use cases
- Request/Response schemas

### 4.2 Error Handling

- Error response format (match building-semantics-api-app)

## 5. Integration Points

### 5.1 Designer Integration

- How Designer will call the API

### 5.2 bms-iot-app Integration

- How it relates to existing BACnet/MQTT flows

## 6. Implementation Stories

- Derived from architecture sections
- Each story is a vertical slice
```

### Reference: building-semantics-api-app Patterns

| Pattern        | Location                                         | Description                 |
| -------------- | ------------------------------------------------ | --------------------------- |
| pyproject.toml | `apps/building-semantics-api-app/pyproject.toml` | Dependencies, tooling       |
| Settings       | `src/config/settings.py`                         | pydantic-settings with .env |
| Adapter        | `src/adapters/buildingmotif_adapter.py`          | External service wrapper    |
| Controller     | `src/controllers/`                               | Business logic layer        |
| Router         | `src/routers/`                                   | FastAPI endpoints           |
| DTO            | `src/dto/`                                       | Request/Response schemas    |
| Models         | `src/models/`                                    | Domain models               |

## Dependencies

- Story 1.4: Document POC Findings (completed)
- `apps/building-semantics-api-app/` - Reference implementation

## Test Strategy

- Review tech spec for completeness
- Verify requirements trace to use cases
- Verify use cases trace to API endpoints
- Ensure MVC structure matches building-semantics-api-app

## Definition of Done

1. Tech spec created at `specs/control-sequence-api-tech-spec.md`
2. Requirements section complete
3. Use cases defined
4. MVC architecture documented
5. API endpoints derived from use cases
6. Implementation stories listed
7. Tech spec reviewed and approved

## Dev Notes

### Input Documents

- `docs/feature-development/g36-implementation/specs/poc-findings.md`
- `docs/feature-development/g36-implementation/PRD.md`
- `apps/building-semantics-api-app/` (reference patterns)

### Output Artifacts

- `docs/feature-development/g36-implementation/specs/control-sequence-api-tech-spec.md`
- Updated `epics.md` with derived implementation stories

## Dev Agent Record

### Context Reference

- `docs/feature-development/g36-implementation/stories/story-1.5-control-sequence-api-tech-spec.context.xml`

### Completion Notes

**Completed:** 2025-12-02
**Definition of Done:** All acceptance criteria met, tech spec reviewed and approved

## Notes

- Requirements-first approach: define WHAT before HOW
- Follow building-semantics-api-app patterns exactly
- App will be renamed: g36-api-app → control-sequence-api-app
- Implementation stories come FROM the tech spec, not predefined
