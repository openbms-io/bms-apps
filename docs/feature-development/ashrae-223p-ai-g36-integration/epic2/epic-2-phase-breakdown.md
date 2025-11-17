# Epic 2 Phase Breakdown - BuildingMOTIF API Integration

**Date:** 2025-11-06
**Epic:** Epic 2 - BuildingMOTIF API Integration
**Status:** Phase Planning
**Total Stories:** 15 stories across 4 phases

---

## Overview

This document breaks down Epic 2 into 4 distinct phases, each with clear objectives, deliverables, and success criteria. Phases must be completed sequentially, but stories within a phase can potentially be parallelized.

**Key Principle:** Interface-First Development

- Phase 0: Foundation (Designer cleanup + FastAPI scaffold)
- Phase 1: Interface validation with mock data
- Phase 2: Real BuildingMOTIF integration
- Phase 3: AI enhancement

---

## Phase 0: Foundation & Prerequisites

**Objective:** Set up complete foundation infrastructure and resolve technical debt before interface development

**Duration:** 2 stories (~1 day)

**Dependencies:** None (prerequisite for all other phases)

### Part A: Designer App Cleanup (Tech Debt)

**Story 2.0: Consolidate service naming and interfaces**

**Scope:**

- Rename 4 FastAPI-backed services to `I223P*Service` pattern:
  - `IBuildingMOTIFService` → `I223PTemplatesService`
  - `ISpaceService` → `I223PSpacesService`
  - `IValidationService` → `I223PValidationService`
  - Create new `I223PMappingsService` interface (extract from `semanticMappingsApi`)
- Keep `IAISuggestionService` unchanged (Designer-only, not FastAPI-backed)
- Remove `spaces223pApi` duplication (merge into `I223PSpacesService`)
- Update all imports across codebase:
  - 7 React Query hooks (1 unchanged: `useAISuggestionQuery`)
  - UI components
  - Service registrations
  - Mock implementations
- Update all tests
- Verify Epic 1 functionality preserved

**Files Affected:**

```
apps/designer/src/domains/building-semantics/
├── adapters/ashrae-223p/services/
│   ├── interfaces/
│   │   ├── buildingmotif.ts → templates.service.interface.ts (I223PTemplatesService)
│   │   ├── ai-suggestion.ts (unchanged)
│   ├── space.service.interface.ts → spaces.service.interface.ts (I223PSpacesService)
│   ├── validation.service.interface.ts (I223PValidationService)
│   └── (NEW) mappings.service.interface.ts (I223PMappingsService)
├── api/
│   ├── mappings.api.ts (refactor to use I223PMappingsService)
│   ├── spaces.api.ts (DELETE - merge into I223PSpacesService)
│   └── queries/ (update imports)
```

**Acceptance Criteria:**

- [ ] All 4 FastAPI services renamed to `I223P*Service`
- [ ] `I223PMappingsService` interface created with 6 methods
- [ ] `spaces223pApi` deleted, functionality in `I223PSpacesService`
- [ ] `IAISuggestionService` unchanged
- [ ] All imports updated (hooks, components, services)
- [ ] All tests pass
- [ ] Epic 1 UI functionality 100% preserved
- [ ] No breaking changes

**Effort Estimate:** ~3 hours

---

### Part B: FastAPI App Foundation (New Infrastructure)

**Story 2.1: Create building-semantics-api-app scaffolding**

**Scope:**

- Create `apps/building-semantics-api-app/` directory structure
- Setup `pyproject.toml` with dependencies:
  - FastAPI, Uvicorn
  - BuildingMOTIF SDK (not used yet, just dependency)
  - Pydantic v2
  - SQLAlchemy
  - python-dotenv
  - loguru
  - Test dependencies (pytest, httpx, pytest-asyncio)
  - Dev dependencies (mypy, black, ruff)
- Create basic project structure:
  ```
  apps/building-semantics-api-app/
  ├── src/
  │   ├── __init__.py
  │   ├── main.py                    # FastAPI app entry point
  │   ├── routers/
  │   │   ├── __init__.py
  │   │   ├── templates.py           # Empty router stub
  │   │   ├── spaces.py              # Empty router stub
  │   │   ├── mappings.py            # Empty router stub
  │   │   └── validation.py          # Empty router stub
  │   ├── services/
  │   │   ├── __init__.py            # Empty service stubs
  │   ├── adapters/
  │   │   ├── __init__.py
  │   │   └── buildingmotif_adapter.py  # Interface only (no implementation)
  │   ├── dto/
  │   │   └── __init__.py            # Empty DTO stubs
  │   ├── config/
  │   │   ├── __init__.py
  │   │   └── settings.py            # Basic settings from environment
  │   └── utils/
  │       ├── __init__.py
  │       └── error_handlers.py      # Exception mapping stubs
  ├── tests/
  │   ├── unit/
  │   └── integration/
  ├── pyproject.toml
  ├── .env.template
  ├── .gitignore
  └── README.md
  ```
- Implement `src/main.py`:
  - FastAPI app initialization
  - CORS middleware for Designer app (port 3003)
  - Health check endpoint: `GET /health`
  - Include router stubs (empty)
- Configure tooling:
  - mypy strict mode
  - black line length 88
  - ruff linting
  - pytest configuration
- Create `.env.template` with configuration variables
- Create `README.md` with setup instructions

**Acceptance Criteria:**

- [ ] Directory structure created
- [ ] `pyproject.toml` with all dependencies
- [ ] FastAPI server starts successfully: `pnpm building-semantics:run`
- [ ] Health check responds: `curl http://localhost:8000/health`
- [ ] Type checking passes: `pnpm building-semantics:typecheck`
- [ ] Linting passes: `pnpm building-semantics:lint`
- [ ] OpenAPI spec accessible: `http://localhost:8000/openapi.json`
- [ ] Swagger UI accessible: `http://localhost:8000/docs`
- [ ] `pnpm dev` starts all 3 services (BMS IoT, Semantics API, Designer)
- [ ] Logs show `[Semantics-API]` prefix

**Effort Estimate:** ~4-5 hours

---

### Phase 0 Success Criteria

**Overall Success:**

- [ ] All Designer app services follow consistent `I223P*Service` pattern
- [ ] All FastAPI-backed services have interfaces
- [ ] FastAPI app runs successfully on port 8000
- [ ] Health check endpoint responds
- [ ] Type checking passes with mypy strict mode
- [ ] All Epic 1 tests pass (zero regression)
- [ ] `pnpm dev` starts all 3 services successfully
- [ ] Development environment validated

**Why Phase 0 First:**

1. **Clean Designer interfaces** → Clean OpenAPI spec in Phase 1
2. **FastAPI scaffold ready** → Mock endpoints easy to add in Phase 1
3. **Tooling validated** (mypy, dev server) → No surprises later
4. **Technical debt cleared** → Focus on new features
5. **Development environment ready** → Parallel work possible

**Ready for Phase 1:**

- Designer interfaces clean and consistent
- FastAPI app structure ready
- OpenAPI spec generation available
- Mock endpoint implementation straightforward

---

## Phase 1: Interface-First Development & Validation

**Objective:** Define and validate API contract with mock data before BuildingMOTIF integration

**Duration:** 4 stories (~2-3 days)

**Dependencies:** Phase 0 complete

### Story 2.2: Design FastAPI OpenAPI specification

**Scope:**

- Define 5 endpoints across 3 services (simplified bulk operations approach):
  - **Templates Service** (1 endpoint):
    - GET `/api/v1/223p/templates` - Returns hierarchical structure with systems, devices, properties, and space types all nested (single response, no multiple lookups)
  - **Spaces Service** (2 endpoints):
    - GET `/api/v1/223p/spaces?projectId={id}` - List all spaces for project
    - POST `/api/v1/223p/spaces` - Create new space instance
  - **Mappings Service** (2 endpoints):
    - GET `/api/v1/223p/mappings?projectId={id}` - Get all mappings for project (bulk read)
    - POST `/api/v1/223p/mappings` - Bulk save/replace all mappings (complete replacement operation)
  - **Validation Service** (0 endpoints):
    - Router stub only - implementation deferred to Phase 2
- Create Pydantic request/response models matching Epic 1 DTOs
- Add OpenAPI tags for documentation
- Add descriptions and examples
- Generate OpenAPI JSON spec at `/openapi.json`

**Reference:**

- Epic 1 DTOs: `/apps/designer/src/domains/building-semantics/`
- Epic 1 interfaces: `I223PTemplatesService`, `I223PSpacesService`, `I223PMappingsService`, `I223PValidationService`

**Acceptance Criteria:**

- [ ] All 5 endpoints defined in OpenAPI spec
- [ ] Hierarchical templates response structure documented
- [ ] Bulk operations pattern documented for mappings
- [ ] Request/response schemas match Epic 1 DTO structure
- [ ] OpenAPI spec validates with `openapi-generator validate`
- [ ] Swagger UI displays all endpoints with documentation
- [ ] Examples included for complex schemas (especially nested templates)

**Effort Estimate:** ~6 hours

---

### Story 2.3: Generate TypeScript client from OpenAPI spec

**Scope:**

- Choose TypeScript client generator (openapi-generator or @hey-api/openapi-ts)
- Install generator as dev dependency in Designer app
- Add generation script to Designer package.json: `npm run generate:api-client`
- Configure generator:
  - Input: `http://localhost:8000/openapi.json`
  - Output: `/apps/designer/src/lib/api/generated/`
  - Generate TypeScript types + API client
- Integrate with Designer build process
- Add generated files to `.gitignore` (generate on build)
- Create wrapper service for generated client

**Acceptance Criteria:**

- [ ] TypeScript client generated from OpenAPI spec
- [ ] All 5 endpoints available as typed functions
- [ ] Hierarchical templates types properly nested
- [ ] Bulk operations types for mappings
- [ ] Request/response types generated
- [ ] TypeScript compiler validates types
- [ ] Generation script in Designer package.json
- [ ] Generated code excluded from git
- [ ] Wrapper service created for clean API

**Effort Estimate:** ~4 hours

---

### Story 2.4: Implement FastAPI service with mock data

**Scope:**

- Implement 5 endpoints returning static mock data:
  - **Templates endpoint**: Return hierarchical structure with nested systems, devices, properties, and space types
    - Complete ASHRAE 223P template hierarchy in single response
    - Systems with embedded devices
    - Devices with embedded properties
    - Space types list
  - **Spaces endpoints**: Use in-memory dictionary for create/list operations
    - List spaces for project
    - Create space instance
  - **Mappings endpoints**: Use in-memory dictionary for bulk operations
    - Get all mappings (keyed by point ID)
    - Bulk save/replace all mappings (complete replacement)
  - **Validation endpoint**: Router stub only (no implementation)
- No BuildingMOTIF SDK integration
- Focus on request/response format matching Epic 1
- Add basic error handling (404, 422, 500)
- Add logging for debugging

**Reference:**

- Epic 1 mock data: `/apps/designer/src/domains/building-semantics/adapters/ashrae-223p/services/*.mock.service.ts`

**Acceptance Criteria:**

- [ ] All 5 endpoints implemented (validation is stub only)
- [ ] Hierarchical templates structure properly nested
- [ ] Mock data matches Epic 1 structure
- [ ] Endpoints respond with correct HTTP status codes
- [ ] Bulk operations work in-memory (mappings)
- [ ] Create/list operations work in-memory (spaces)
- [ ] Integration tests pass (httpx test client)
- [ ] Swagger UI can call all endpoints

**Effort Estimate:** ~6 hours (reduced from ~8h due to fewer endpoints)

---

### Story 2.5: Integrate TypeScript client with Designer app

**Scope:**

- Create API service implementations using generated TypeScript client:
  - `Templates223PApiService` implements `I223PTemplatesService`
  - `Spaces223PApiService` implements `I223PSpacesService`
  - `Mappings223PApiService` implements `I223PMappingsService`
  - (Validation deferred to Phase 2)
- Update React Query hooks to use new API services:
  - `useTemplatesQuery()` - single hierarchical call
  - `useMappingsQuery()` - bulk read
  - `useSaveMappingsMutation()` - bulk save/replace (simplified from individual CRUD)
  - `useSpacesQuery()` - list spaces
  - `useCreateSpaceMutation()` - create space
- Keep `useAISuggestionQuery()` unchanged (Designer-only)
- Update service registration to use API implementations instead of mock
- Remove sessionStorage usage (mappings, spaces)
- Adapt UI to bulk operations pattern for mappings
- Test all Epic 1 UI flows with FastAPI backend

**Acceptance Criteria:**

- [ ] 3 API service classes created (templates, spaces, mappings)
- [ ] 5 React Query hooks updated (templates, mappings bulk, spaces)
- [ ] Bulk operations pattern working for mappings (replace individual CRUD)
- [ ] sessionStorage removed (mappings, spaces)
- [ ] All Epic 1 UI functionality works with FastAPI
- [ ] No UI component changes (or minimal to support bulk operations)
- [ ] Epic 1 tests pass (component tests)
- [ ] Manual testing: mapping workflow end-to-end

**Effort Estimate:** ~6 hours

---

### Phase 1 Success Criteria

**Overall Success:**

- [ ] OpenAPI spec generates valid TypeScript client
- [ ] Designer app successfully communicates with FastAPI mock endpoints (5 endpoints)
- [ ] All Epic 1 UI functionality preserved with mock API
- [ ] Minimal UI component changes (bulk operations pattern for mappings)
- [ ] Interface contract validated before BuildingMOTIF work
- [ ] No BuildingMOTIF SDK touched yet (cheap validation)
- [ ] Hierarchical templates response reduces client-side complexity
- [ ] Bulk operations pattern simplifies state management

**Why Interface-First:**

- **Validate contract early** with cheap mock data
- **Designer team can work in parallel** (API contract known)
- **Discover actual needs** before expensive BuildingMOTIF integration
- **Avoid building unused endpoints** - learn from usage
- **Iterate on interface cheaply** before RDF complexity

**Ready for Phase 2:**

- API contract validated
- TypeScript client working
- Designer app using FastAPI
- Ready to replace mock data with BuildingMOTIF SDK

---

## Phase 2: BuildingMOTIF SDK Integration

**Objective:** Replace mock data with real BuildingMOTIF SDK, implement RDF operations

**Duration:** 6 stories (~4-5 days)

**Dependencies:** Phase 1 complete

### Story 2.6: Setup BuildingMOTIF SDK infrastructure

**Scope:**

- Install BuildingMOTIF Python package
- Create `BuildingMOTIFAdapter` class:
  - Initialize BuildingMOTIF SDK
  - Configure SQLite database for RDF storage
  - Load ASHRAE 223P library
  - Provide methods for RDF operations
- Create service layer wrapper:
  - Adapter → Service → Router pattern
  - Hide RDF complexity from routers
- Test adapter with basic operations:
  - Load library
  - Query templates
  - Create/read RDF triples
- Add configuration for database path
- Update settings.py with BuildingMOTIF config

**Acceptance Criteria:**

- [ ] BuildingMOTIF SDK installed and importable
- [ ] `BuildingMOTIFAdapter` class implemented
- [ ] SQLite database created for RDF storage
- [ ] ASHRAE 223P library loaded successfully
- [ ] Unit tests for adapter pass (mock BuildingMOTIF)
- [ ] Integration test with real SDK passes
- [ ] No changes to FastAPI endpoints yet

**Effort Estimate:** ~6 hours

---

### Story 2.7: Implement `/api/v1/223p/templates` endpoint (1 hierarchical endpoint)

**Scope:**

- Replace mock data with BuildingMOTIF template queries
- Implement `TemplatesService`:
  - Query ASHRAE 223P templates from BuildingMOTIF
  - Parse YAML templates or query RDF graph for template hierarchy
  - Convert RDF data → nested Pydantic DTOs
  - Build hierarchical structure: systems → devices → properties
  - Include space types list
- Implement `from_rdf()` class methods on DTOs:
  - `SystemTypeDTO.from_rdf()` (with nested devices)
  - `DeviceTypeDTO.from_rdf()` (with nested properties)
  - `ObservablePropertyDTO.from_rdf()`
  - `SpaceTypeDTO.from_rdf()`
- Update endpoint:
  - GET `/api/v1/223p/templates` - Returns complete hierarchical structure
- Add error handling for BuildingMOTIF exceptions
- Write integration tests with real BuildingMOTIF
- Optimize for performance (caching if needed for large hierarchy)

**Acceptance Criteria:**

- [ ] Hierarchical templates endpoint returns real BuildingMOTIF data
- [ ] Complete nested structure: systems → devices → properties + space types
- [ ] DTOs match Epic 1 structure with proper nesting
- [ ] `from_rdf()` conversion methods implemented for all DTOs
- [ ] Error handling for BuildingMOTIF failures
- [ ] Performance acceptable for complete hierarchy (< 1s response time)
- [ ] Integration tests pass
- [ ] Designer app templates dropdown works with real hierarchical data

**Effort Estimate:** ~6-7 hours (same complexity, different structure)

---

### Story 2.8: Implement `/api/v1/223p/mappings` bulk endpoints (2 endpoints)

**Scope:**

- Implement `MappingsService` with BuildingMOTIF:
  - **Bulk Read**: Query RDF graph for all mappings in project, return as dictionary keyed by point ID
  - **Bulk Save**: Complete replacement operation - clear existing mappings, add all new mappings as RDF triples
- RDF triple patterns for semantic equipment:
  - equipment → hasDeviceType → device
  - equipment → monitors → property
  - equipment → locatedIn → space
- Update 2 endpoints to use BuildingMOTIF:
  - GET `/api/v1/223p/mappings?projectId={id}` - Bulk read all mappings
  - POST `/api/v1/223p/mappings` - Bulk save/replace all mappings
- Persist to SQLite via BuildingMOTIF
- Add transaction support for bulk operations (atomic replace)
- Optimize bulk queries for performance

**Acceptance Criteria:**

- [ ] Both bulk mapping endpoints use BuildingMOTIF SDK
- [ ] RDF triples stored in SQLite database
- [ ] Mappings persist across server restarts
- [ ] Bulk save operation is atomic (transaction-based clear + add)
- [ ] Bulk read returns dictionary keyed by point ID
- [ ] Performance acceptable for large mapping sets (100+ points)
- [ ] Integration tests pass (bulk operations)
- [ ] Designer app mapping workflow end-to-end works

**Effort Estimate:** ~5-6 hours (reduced from ~8h, simpler bulk operations)

---

### Story 2.9: Implement `/api/v1/223p/spaces` endpoints (2 endpoints)

**Scope:**

- Implement `SpacesService` with BuildingMOTIF:
  - **Create space**: Add space instance to RDF graph with type and label
  - **List spaces**: Query RDF graph for all spaces in project
- RDF triple patterns for spaces:
  - space → rdf:type → 223:PhysicalSpace (or specific space type)
  - space → rdfs:label → "label"
  - space → belongsToProject → projectId (for filtering)
- Update 2 endpoints to use BuildingMOTIF:
  - GET `/api/v1/223p/spaces?projectId={id}` - List all spaces
  - POST `/api/v1/223p/spaces` - Create space instance
- Persist to SQLite via BuildingMOTIF
- Note: Point-to-space relationships handled via mappings (Story 2.8)

**Acceptance Criteria:**

- [ ] Both space endpoints use BuildingMOTIF SDK
- [ ] Spaces stored as RDF triples with proper types
- [ ] List operation filters by projectId
- [ ] Create operation assigns unique space URIs
- [ ] Point-to-space relationships handled via mappings endpoint
- [ ] Integration tests pass
- [ ] Designer app space workflow works

**Effort Estimate:** ~4 hours (reduced from ~6h, fewer endpoints)

---

### Story 2.10: Implement `/api/v1/223p/validate` SHACL endpoint (1 endpoint - NEW)

**Note:** This is **full implementation**, not migration - validation was deferred in Phase 1.

**Scope:**

- Implement `ValidationService` with BuildingMOTIF:
  - Use BuildingMOTIF SHACL validation engine
  - Validate semantic equipment against ASHRAE 223P SHACL rules
  - Return validation errors/warnings with detailed messages
- Map SHACL results to Pydantic `ValidationResultDTO`:
  - `isValid: boolean`
  - `errors: string[]` - Constraint violations
  - `warnings: string[]` - Recommendations
- Implement POST `/api/v1/223p/validate` endpoint (new in Phase 2)
- Add validation rules for:
  - Device type compatibility with equipment type
  - Property compatibility with device type
  - Required 223P constraints (hasDeviceType, monitors, locatedIn)
- Handle validation input (mappings to validate)

**Acceptance Criteria:**

- [ ] Validation endpoint uses BuildingMOTIF SHACL engine
- [ ] Returns real 223P compliance results
- [ ] DTO matches Epic 1 structure
- [ ] Validation errors displayed in Designer UI
- [ ] Integration tests pass

**Effort Estimate:** ~4 hours

---

### Story 2.11: Error handling, retry logic, and integration tests

**Scope:**

- Implement comprehensive error handling:
  - BuildingMOTIF exceptions → HTTPException
  - User-friendly error messages
  - Appropriate HTTP status codes (404, 422, 500)
- Add retry logic for transient failures:
  - Database connection errors
  - RDF query timeouts
- Write end-to-end integration tests:
  - Designer → FastAPI → BuildingMOTIF flow
  - All 5 endpoints tested (templates, spaces x2, mappings x2, validation)
  - Bulk operations workflows tested
  - Hierarchical templates loading tested
  - Error scenarios tested
- Performance testing:
  - Hierarchical template loading time (< 1s)
  - Bulk mapping operations (100+ points)
  - Validation time

**Acceptance Criteria:**

- [ ] All BuildingMOTIF exceptions handled
- [ ] Retry logic for transient failures
- [ ] E2E integration tests pass (all 5 endpoints)
- [ ] Bulk operations performance tested
- [ ] Hierarchical templates performance tested
- [ ] Error messages user-friendly
- [ ] Performance acceptable (< 1s for templates, < 500ms for others)
- [ ] Epic 1 UI shows meaningful errors

**Effort Estimate:** ~6 hours (reduced from ~8h due to fewer endpoints)

---

### Phase 2 Success Criteria

**Overall Success:**

- [ ] All 5 endpoints use real BuildingMOTIF SDK
- [ ] Hierarchical templates reduce client complexity
- [ ] Bulk operations simplify state management
- [ ] RDF graphs persist in SQLite database
- [ ] SHACL validation returns real 223P compliance results
- [ ] Epic 1 UI works with real semantic tagging
- [ ] Integration tests pass
- [ ] Error handling robust
- [ ] Performance acceptable (< 1s for most operations)

**Why Incremental Integration:**

- **One service at a time** - easier to debug
- **Test after each story** - catch issues early
- **Epic 1 UI works throughout** - interface preserved
- **RDF complexity isolated** - adapter pattern

**Ready for Phase 3:**

- Real BuildingMOTIF templates available
- AI can use real 223P data as context

---

## Phase 3: AI Enhancement (LAST)

**Objective:** Replace mock AI suggestions with Vercel AI SDK + Mem0

**Duration:** 2 stories (~1-2 days)

**Dependencies:** Phase 2 complete

### Story 2.12: Setup Vercel AI SDK + Mem0 in Designer app

**Scope:**

- Install packages in Designer app:
  - Vercel AI SDK (`ai` package)
  - Mem0 for memory/context
- Configure AI provider (Claude or OpenAI)
- Setup Mem0 configuration:
  - Memory storage
  - Context retrieval
  - Learning from corrections
- Create `/apps/designer/src/lib/ai` structure:
  - `ai-client.ts` - Vercel AI SDK client
  - `memory-manager.ts` - Mem0 integration
  - `suggestion-engine.ts` - AI logic
- Add environment variables for API keys
- Test basic AI call (without BuildingMOTIF context)

**Acceptance Criteria:**

- [ ] Vercel AI SDK installed and configured
- [ ] Mem0 installed and configured
- [ ] AI client can make basic calls
- [ ] Memory manager stores/retrieves context
- [ ] Environment variables configured
- [ ] No FastAPI endpoint created (Designer-only)

**Effort Estimate:** ~4 hours

---

### Story 2.13: Implement AI suggestion logic using real BuildingMOTIF templates

**Scope:**

- Fetch real BuildingMOTIF templates from FastAPI:
  - GET `/api/223p/templates/systems`
  - GET `/api/223p/templates/devices`
  - GET `/api/223p/templates/properties`
- Use templates as AI context for suggestions
- Implement `AIService`:
  - Analyze BACnet point data
  - Provide templates as context to AI
  - Generate equipment type, device type, property suggestions
  - Use Mem0 to learn from user corrections
- Update `IAISuggestionService` implementation
- Replace Epic 1 mock logic with AI logic
- Keep interface unchanged (`suggestMapping()`)

**Acceptance Criteria:**

- [ ] AI suggestions use real ASHRAE 223P templates
- [ ] AI receives BACnet point data + templates as context
- [ ] Mem0 learns from user corrections (accept/reject/modify)
- [ ] Suggestion quality validated manually
- [ ] `useAISuggestionQuery()` hook works with AI service
- [ ] No FastAPI endpoint (Designer-only logic)
- [ ] AI suggestions improve over time with Mem0

**Effort Estimate:** ~6 hours

---

### Story 2.14: Advanced Tab - Triple Inspector

**⚠️ REQUIRES ARCHITECTURAL REFINEMENT BEFORE IMPLEMENTATION**

**Scope:**

- Add "Advanced" tab to mapping popup modal showing all RDF triples generated by `template.fill()`
- Display complete ASHRAE 223P semantic graph (20-50+ triples per mapping)
- Group triples into 6 categories:
  1. Type/Classification (rdf:type)
  2. Properties (qudt:hasQuantityKind, s223:hasMedium, s223:hasAspect)
  3. Connection/Topology (s223:contains, s223:connectedTo, s223:cnx)
  4. Function/Mapping (s223:mapsTo, s223:hasObservationLocation)
  5. Space (s223:locatedIn, s223:hasDomain)
  6. External Reference (bacnet:device-identifier, bacnet:object-identifier)
- Add copy functionality (Turtle, JSON-LD, composite key)
- **Currently only 5 fields returned** - this exposes full 95% of hidden semantic graph

**Architecture Decisions Required:**

1. **UI Display Format**: Tree view, table, graph visualization, or tabs?
2. **Data Transfer Method**: New endpoint, expand existing endpoint, or frontend-only simulation?
3. **Triple Categorization Logic**: Backend pre-grouped vs frontend categorization?
4. **Performance Strategy**: Lazy load, pagination, virtual scroll, or limit display?
5. **Serialization Format**: JSON array, Turtle string, JSON-LD, or mixed?

**Acceptance Criteria (Subject to Refinement):**

- [ ] Display all RDF triples from `template.fill()` calls
- [ ] Group by 6 categories with collapsible sections
- [ ] Real-time preview calling BuildingMOTIF `template.fill()`
- [ ] Copy as Turtle, JSON-LD, and composite key
- [ ] Preview generation < 500ms
- [ ] Handle 100+ triples without UI lag
- [ ] Color-coded predicates and proper formatting

**Effort Estimate:** ~10-16 hours (depends on architecture decisions)

**Status:** Backlog - needs architectural refinement before implementation

**Dependencies:**
- Story 2.6: BuildingMOTIF SDK Setup ✅
- Story 2.7: Templates Endpoint ✅
- Story 2.8: Mappings Endpoints ✅
- Architecture decisions: ❌ REQUIRED BEFORE IMPLEMENTATION

---

### Phase 3 Success Criteria

**Overall Success:**

- [ ] AI suggestions use real ASHRAE 223P templates as context
- [ ] AI learns from user corrections via Mem0
- [ ] Suggestion quality better than mock rules
- [ ] No FastAPI endpoint required
- [ ] Designer-only implementation

**Why AI Last:**

- **Not a blocker** - core functionality works without AI
- **Uses real data** - better context from BuildingMOTIF
- **Enhancement** - improves UX but not critical path
- **Can iterate** - easy to improve AI prompts later

**Epic 2 Complete:**

- Full BuildingMOTIF API integration
- Real semantic tagging operational
- AI-powered suggestions
- Zero Epic 1 UI changes

---

## Epic 2 Summary

### Total Scope

**15 stories across 4 phases:**

| Phase       | Stories | Duration         | Key Deliverable                                   |
| ----------- | ------- | ---------------- | ------------------------------------------------- |
| **Phase 0** | 2       | ~1 day           | Foundation: Designer cleanup + FastAPI scaffold   |
| **Phase 1** | 4       | ~2-3 days        | Interface validation with mock data (5 endpoints) |
| **Phase 2** | 6       | ~3-4 days        | BuildingMOTIF SDK integration (5 endpoints)       |
| **Phase 3** | 3       | ~2-3 days        | AI enhancement + Triple Inspector (needs refinement) |
| **Total**   | **15**  | **~2-2.5 weeks** | Full BuildingMOTIF integration + AI + Transparency |

### Story List

**Phase 0 (Foundation):**

- Story 2.0: Consolidate service naming (Designer - I223P\*Service)
- Story 2.1: Create FastAPI app scaffolding

**Phase 1 (Interface-First):**

- Story 2.2: Design OpenAPI specification
- Story 2.3: Generate TypeScript client
- Story 2.4: Implement mock data endpoints
- Story 2.5: Integrate TypeScript client with Designer

**Phase 2 (BuildingMOTIF Integration):**

- Story 2.6: Setup BuildingMOTIF SDK infrastructure
- Story 2.7: Implement templates endpoint (1 hierarchical)
- Story 2.8: Implement mappings endpoints (2 bulk operations)
- Story 2.9: Implement spaces endpoints (2)
- Story 2.10: Implement validation endpoint (1 - new implementation)
- Story 2.11: Error handling and integration tests

**Phase 3 (AI Enhancement + Transparency):**

- Story 2.12: Setup Vercel AI SDK + Mem0
- Story 2.13: Implement AI suggestion logic
- Story 2.14: Advanced Tab - Triple Inspector (⚠️ needs refinement)

### Critical Path

**Sequential Phases:**

```
Phase 0 → Phase 1 → Phase 2 → Phase 3
```

**Within Phase Parallelization:**

- Phase 1: Stories 2.3 and 2.4 can overlap (client gen + mock endpoints)
- Phase 2: Stories 2.7-2.10 can be parallelized if multiple developers

### Risk Mitigation

**Phase 0:**

- **Risk:** Technical debt blocks progress
- **Mitigation:** Clean foundation first, then move fast

**Phase 1:**

- **Risk:** Building wrong interface, wasting time on BuildingMOTIF
- **Mitigation:** Validate interface with mock data first, iterate cheaply

**Phase 2:**

- **Risk:** BuildingMOTIF SDK complexity, RDF learning curve
- **Mitigation:** Incremental integration (one service at a time), test after each story

**Phase 3:**

- **Risk:** AI doesn't improve suggestion quality
- **Mitigation:** AI last - core functionality works without it

### Success Metrics

**Phase 0 Success:**

- ✅ Designer interfaces clean and consistent
- ✅ FastAPI app runs, type checking passes
- ✅ Development environment validated

**Phase 1 Success:**

- ✅ OpenAPI spec generates TypeScript client
- ✅ Designer app calls FastAPI endpoints (5 endpoints)
- ✅ Epic 1 UI works with mock API
- ✅ Bulk operations pattern validated
- ✅ Hierarchical templates reduce complexity

**Phase 2 Success:**

- ✅ All 5 endpoints use BuildingMOTIF SDK
- ✅ Hierarchical templates from real RDF data
- ✅ Bulk operations with RDF persistence
- ✅ RDF persistence in SQLite
- ✅ Epic 1 UI works with real semantic tagging

**Phase 3 Success:**

- ✅ AI suggestions use real 223P templates
- ✅ Mem0 learns from user corrections
- ✅ Advanced tab displays complete RDF semantic graph (pending architecture decisions)

**Epic 2 Success:**

- ✅ Full BuildingMOTIF integration operational (5 endpoints)
- ✅ Minimal Epic 1 UI changes (bulk operations pattern)
- ✅ Simplified API design (hierarchical templates, bulk operations)
- ✅ AI-powered suggestions
- ✅ Full semantic graph transparency (95% of triples exposed)

---

## Next Steps

**Current Status:** Phase Planning Complete

**Next Actions:**

1. Review Phase 0 scope (Stories 2.0-2.1)
2. Generate detailed Story 2.0 (Designer cleanup)
3. Generate detailed Story 2.1 (FastAPI scaffold)
4. Review Phase 0 stories for approval
5. Implement Phase 0
6. Repeat for Phases 1-3

**Phase Approval Required:**

- Each phase reviewed before story generation
- Stories generated phase-by-phase
- Phase complete → Review → Next phase

---

**Document Status:** ✅ Complete
**Last Updated:** 2025-11-06
**Next Action:** Review Phase 0 scope, proceed to detailed story generation
