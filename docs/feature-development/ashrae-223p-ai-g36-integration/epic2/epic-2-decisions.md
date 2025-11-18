# Epic 2 Decisions - BuildingMOTIF API Integration

**Date:** 2025-11-05
**Phase:** Phase 1 - Task 1.1 Complete
**Status:** Decisions Approved

---

## Overview

This document captures key architectural and implementation decisions made for Epic 2 (BuildingMOTIF API Integration) after completing BuildingMOTIF SDK research.

---

## Decision 1: FastAPI Wrapper Service

**Status:** ✅ APPROVED

**Decision:** Create Python FastAPI wrapper service around BuildingMOTIF SDK

**Rationale:**

- BuildingMOTIF is a Python SDK, not a REST API
- Designer app (TypeScript) needs HTTP API for integration
- FastAPI provides OpenAPI spec generation (TypeScript client auto-generation)

**Implementation:**

- Python FastAPI service wrapping BuildingMOTIF SDK
- Runs on localhost during development
- Exposes REST endpoints matching Epic 1 mock interface

**Impact:**

- Adds 3-5 stories to Epic 2 scope
- Zero UI changes preserved (wrapper matches Epic 1 interface)

---

## Decision 2: Simplified JSON Interface

**Status:** ✅ APPROVED

**Decision:** Hide RDF complexity from TypeScript client, return simple JSON

**Rationale:**

- Epic 1 components expect simple DTO structures
- RDF graphs are BuildingMOTIF internal implementation detail
- Maintain Epic 1 interface contract

**Implementation:**

- FastAPI wrapper converts RDF graphs → JSON DTOs
- Epic 1 DTOs unchanged
- RDF complexity stays in Python wrapper

**Impact:**

- Included in wrapper service (no additional stories)
- Preserves Epic 1 interface contract

---

## Decision 3: AI Strategy - Vercel AI SDK + Mem0

**Status:** ✅ APPROVED - CUSTOM APPROACH

**Decision:** Use Vercel AI SDK + Mem0 integration in Designer app

**Chosen Approach:** Custom (not Option A or B from recommendations)

**Implementation:**

- **Location:** `/apps/designer/src/lib/ai`
- **Stack:** Vercel AI SDK + Mem0 for memory/context
- **Scope:** Lives in Designer app as library (not in FastAPI wrapper)
- **Phase:** Phase 3 (LAST) - after BuildingMOTIF integration complete

**Rationale:**

- Leverages Vercel AI SDK ecosystem
- Mem0 provides context/memory for better suggestions
- Keeps AI logic in Designer app (TypeScript)
- Can use real BuildingMOTIF templates as AI context

**Impact:**

- 2 stories in Phase 3 (last phase)
- AI becomes enhancement, not blocker

---

## Decision 4: Interface-First Development Approach

**Status:** ✅ APPROVED - CRITICAL CHANGE

**Decision:** Define and validate interface before implementing endpoints

**New Story Flow:**

1. Define FastAPI OpenAPI spec (interface contract)
2. Generate TypeScript client from OpenAPI spec
3. **FastAPI returns mock data first** (validate interface)
4. Integrate TypeScript client with Designer app (React Query hooks)
5. Discover which endpoints are actually needed through usage
6. Implement real BuildingMOTIF endpoints one by one

**Rationale:**

- Avoid building unused endpoints
- Validate contract early with mock data
- Iterate on interface before expensive BuildingMOTIF integration
- Designer app developers can work in parallel

**Impact:**

- Phase 1 (4 stories): Interface definition & validation
- Phase 2 (6 stories): Real BuildingMOTIF implementation
- Phase 3 (2 stories): AI integration

**Total:** 12 stories (interface-first approach)

---

## Decision 5: React Query Integration (Not Zero UI Changes)

**Status:** ✅ APPROVED - ACCEPTABLE

**Decision:** Designer app will use React Query hooks to call FastAPI

**Change from Epic 1:**

- **Epic 1:** Mock service used sessionStorage (synchronous)
- **Epic 2:** React Query hooks calling FastAPI endpoints (async HTTP)

**Rationale:**

- Real API requires HTTP calls
- React Query already used in Epic 1 for state management
- Minimal change (update query functions to call FastAPI instead of mock)

**Impact:**

- UI components unchanged (already use React Query hooks)
- Query functions updated to call FastAPI instead of mock service
- Acceptable deviation from "zero UI changes" goal

---

## Decision 6: Domain-Scoped API Paths

**Status:** ✅ APPROVED - CRITICAL ARCHITECTURE

**Decision:** API paths include domain for future extensibility

**URL Structure:**

```
/api/223p/templates          # ASHRAE 223P templates
/api/223p/devices            # ASHRAE 223P devices
/api/223p/properties         # ASHRAE 223P properties
/api/223p/mappings           # 223P mappings CRUD
/api/223p/validate           # 223P SHACL validation

Future extensibility:
/api/brick/templates         # Brick ontology templates
/api/haystack/tags           # Project Haystack tags
```

**Rationale:**

- Start with ASHRAE 223P (`/api/223p/*`)
- Design for future ontologies (Brick, Haystack, etc.)
- Clear separation of concerns
- Easy to add new domains without breaking existing paths

**Impact:**

- API path design includes domain prefix
- OpenAPI spec organized by domain
- Future-proof architecture

---

## Updated Epic 2 Scope

### Phase 1: Interface Definition & Validation (4 stories)

**Story 2.1:** Design FastAPI OpenAPI spec with domain-scoped paths (`/api/223p/*`)

- Define all endpoints with request/response schemas
- Include ASHRAE 223P DTO structures
- Generate OpenAPI JSON spec

**Story 2.2:** Generate TypeScript client from OpenAPI spec

- Use openapi-generator or similar tool
- Generate TypeScript types + API client
- Integrate with Designer app build process

**Story 2.3:** Implement FastAPI service with mock data endpoints

- FastAPI server with mock data (no BuildingMOTIF yet)
- Returns static ASHRAE 223P templates (systems.yml, devices.yml, properties.yml)
- Mock CRUD operations for mappings

**Story 2.4:** Integrate TypeScript client with Designer app (React Query hooks)

- Replace Epic 1 mock service calls with FastAPI client
- Update React Query hooks to use TypeScript client
- Validate interface contract with mock data

**Milestone:** Interface validated, Designer app calling FastAPI with mock data

---

### Phase 2: Real BuildingMOTIF Implementation (6 stories)

**Story 2.5:** Setup BuildingMOTIF SDK in FastAPI wrapper

- Install BuildingMOTIF Python package
- Load ASHRAE 223P library (systems.yml, devices.yml, properties.yml)
- Configure SQLite database for RDF storage

**Story 2.6:** Implement real `/api/223p/templates` endpoint

- Replace mock data with BuildingMOTIF template queries
- Parse YAML templates from BuildingMOTIF library
- Convert to JSON matching Epic 1 DTO structure

**Story 2.7:** Implement real `/api/223p/mappings` CRUD endpoints

- Create: Add RDF triples to BuildingMOTIF model
- Read: Query RDF graph for mappings
- Update: Modify RDF triples
- Delete: Remove RDF triples

**Story 2.8:** Implement real `/api/223p/validate` SHACL endpoint

- Use BuildingMOTIF SHACL validation engine
- Return validation errors/warnings matching Epic 1 DTO
- Validate 223P compliance rules

**Story 2.9:** Error handling & retry logic

- Handle BuildingMOTIF SDK exceptions
- Implement retry logic for transient failures
- User-friendly error messages

**Story 2.10:** Integration tests

- Test Designer app → FastAPI → BuildingMOTIF flow
- Validate Epic 1 components work with real API
- End-to-end semantic tagging workflow tests

**Milestone:** Full BuildingMOTIF integration working, real semantic tagging operational

---

### Phase 3: AI Integration (2 stories) - LAST

**Story 2.11:** Setup Vercel AI SDK + Mem0 in `/apps/designer/src/lib/ai`

- Install Vercel AI SDK + Mem0 packages
- Configure AI provider (Claude/OpenAI)
- Setup Mem0 for context/memory

**Story 2.12:** Implement AI suggestion logic using AI SDK

- Replace Epic 1 mock AI suggestions
- Use real BuildingMOTIF templates as AI context
- Mem0 for learning from user corrections

**Milestone:** AI-powered suggestions using real BuildingMOTIF templates

---

## Total Story Count

**12 stories:**

- Phase 1: 4 stories (Interface validation)
- Phase 2: 6 stories (BuildingMOTIF integration)
- Phase 3: 2 stories (AI enhancement)

**Original estimate:** 10-11 stories
**Updated:** 12 stories (interface-first approach adds 1-2 stories, but reduces risk)

---

## Missing Templates Decision

**Gap Identified:**

- Epic 1 Devices: 18 → BuildingMOTIF: 25 (missing 7)
- Epic 1 Properties: 24 → BuildingMOTIF: 26 (missing 2)

**Missing Devices:**

- vlv-dmp (valve-damper)
- HR-pump (heat recovery pump)
- belimo-energy-valve
- differential-sensor
- HRC-BTU-meter
- hot-water-system-BTU-meter
- chilled-water-system-BTU-meter

**Missing Properties:**

- vfd-speed
- vfd-feedback

**Decision:** DEFERRED

- Keep Epic 1 enums as-is (18 devices, 24 properties)
- Add missing templates on-demand when needed
- Focus on core BuildingMOTIF integration first

**Rationale:**

- Epic 1 covers essential devices/properties
- Missing templates are specialized (BTU meters, heat recovery)
- Can add later without breaking changes

---

## Architecture Summary

```
┌─────────────────────────────────────────────────────────────┐
│  Designer App (TypeScript/Next.js)                          │
│                                                              │
│  ┌────────────────────────────────────────────────────┐    │
│  │  /src/lib/ai                                       │    │
│  │  - Vercel AI SDK + Mem0                            │    │
│  │  - AI suggestion logic (Phase 3)                   │    │
│  └────────────────────────────────────────────────────┘    │
│                                                              │
│  ┌────────────────────────────────────────────────────┐    │
│  │  React Query Hooks                                 │    │
│  │  - useMappingsQuery()                              │    │
│  │  - useCreateMappingMutation()                      │    │
│  │  - useTemplatesQuery()                             │    │
│  └──────────────────┬─────────────────────────────────┘    │
│                     │ HTTP/JSON                             │
└─────────────────────┼─────────────────────────────────────┘
                      │
                      │ TypeScript API Client (generated)
                      │
┌─────────────────────▼─────────────────────────────────────┐
│  FastAPI Wrapper Service (Python)                         │
│                                                            │
│  Domain-Scoped Endpoints:                                 │
│  - /api/223p/templates                                    │
│  - /api/223p/devices                                      │
│  - /api/223p/properties                                   │
│  - /api/223p/mappings (CRUD)                              │
│  - /api/223p/validate                                     │
│                                                            │
│  Phase 1: Returns mock data                               │
│  Phase 2: Calls BuildingMOTIF SDK                         │
└─────────────────────┬─────────────────────────────────────┘
                      │ Python SDK
                      │
┌─────────────────────▼─────────────────────────────────────┐
│  BuildingMOTIF SDK (Python)                               │
│                                                            │
│  - ASHRAE 223P library (systems.yml, devices.yml, ...)   │
│  - RDF graph operations                                   │
│  - SHACL validation                                       │
│  - Template evaluation                                    │
└─────────────────────┬─────────────────────────────────────┘
                      │
┌─────────────────────▼─────────────────────────────────────┐
│  SQLite Database (RDF Graph Storage)                      │
└───────────────────────────────────────────────────────────┘
```

---

## Key Principles

1. **Interface-First Development**

   - Define contract before implementation
   - Validate with mock data
   - Iterate on interface cheaply

2. **Domain-Scoped Architecture**

   - `/api/223p/*` for ASHRAE 223P
   - Future: `/api/brick/*`, `/api/haystack/*`
   - Clear separation of concerns

3. **Incremental Integration**

   - Phase 1: Interface validation
   - Phase 2: BuildingMOTIF integration
   - Phase 3: AI enhancement

4. **Zero Breaking Changes**
   - Epic 1 components unchanged
   - React Query hooks updated (minimal change)
   - DTO structures preserved

---

## Next Steps

**Phase 1 Complete:**

- ✅ Task 1.1: BuildingMOTIF SDK Research
- ✅ Decisions documented

**Next Tasks:**

1. **Task 1.2:** Tech Spec Review (extract Epic 1 architecture)
2. **Task 1.3:** Generate Epic 2 stories (12 stories, interface-first)

---

**Document Status:** ✅ Complete
**Last Updated:** 2025-11-05
**Approved By:** Amol
**Next Action:** Proceed to Task 1.2 (Tech Spec Review)
