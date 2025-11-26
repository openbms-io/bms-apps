# Story 2.9: Implement Spaces Endpoints

**Epic:** Epic 2 - BuildingMOTIF API Integration (Descoped)
**Phase:** Phase 2 - BuildingMOTIF SDK Integration
**Status:** out-of-scope
**Created:** 2025-11-17
**Descoped:** 2025-11-17
**Complexity:** 3 (Medium)
**Estimated Hours:** 4 hours
**Dependencies:** Story 2.9a (Space Architecture Mini-Spec) must be completed first

---

## ⚠️ OUT OF SCOPE - Descoped from Epic 2

**Date**: 2025-11-17
**Reason**: Space management complexity doesn't align with Epic 2 G36 validation focus
**Decision**: Moved to future "Space Management" epic
**Reference**: `epic2/adr-001-descope-spaces.md`

**Status**: Blocked by Story 2.9a descoping. Both stories moved to future Space Management epic.

**Architecture Work**: Implementation guidance available in `mini-specs/space-architecture.md` (1139 lines) when this epic is prioritized.

---

## User Story

**As a** backend developer and frontend developer,
**I want** the spaces endpoints to persist space instances in BuildingMOTIF's RDF graph storage,
**So that** physical and domain spaces can be created, queried, and referenced in equipment mappings with proper ASHRAE 223P semantic relationships.

---

## Context

### Prerequisite

**⚠️ Story 2.9a (Space Architecture Mini-Spec) must be completed before implementation.**

The mini-spec defines:

- Space type taxonomy (PhysicalSpace, DomainSpace, Zone)
- UI interaction patterns
- API contract specifications
- RDF relationship patterns

**Reference:** `mini-specs/space-architecture.md`

### Problem

Story 2.4 implemented spaces endpoints with in-memory storage (`MOCK_SPACES` in `src/data/mock_templates.py:15`). This approach:

- **Loses data on restart**: All spaces cleared when FastAPI server restarts
- **No RDF graph**: Can't query semantic relationships using BuildingMOTIF
- **Not production-ready**: Epic 2 Phase 2 goal is real persistence

### Solution

Replace mock data with BuildingMOTIF RDF graph persistence following the patterns established in Stories 2.7 (templates) and 2.8 (mappings):

```
GET/POST /api/v1/223p/spaces
        ↓
spaces_router.py
        ↓
SpacesController (mediator pattern)
        ↓
BuildingMOTIFAdapter (RDF operations)
        ↓
RDF Graph (SQLite via BuildingMOTIF)
```

### Architecture Pattern (from Stories 2.7 & 2.8)

**Router → Controller → Adapter** (no service layer)

- **Router**: HTTP request/response handling
- **Controller**: Business logic, orchestration (mediator)
- **Adapter**: BuildingMOTIF SDK operations (singleton)
- **Mapper**: Pure functions for RDF ↔ DTO conversion

### RDF Persistence Model

**Space instances (ASHRAE 223P-compliant):**

```turtle
# Physical Space
:space-office-101 a s223:PhysicalSpace ;
    rdfs:label "Office 101" ;
    dcterms:identifier "space-office-101" .

# Domain Space (thermal zone, lighting zone, etc.)
:zone-hvac-north a s223:DomainSpace ;
    rdfs:label "North HVAC Zone" ;
    s223:hasDomain s223:Domain-HVAC ;
    dcterms:identifier "zone-hvac-north" .

# Project relationship (external, as in Story 2.8)
:project-123 a bms:Project ;
    dcterms:identifier "proj-123" ;
    s223:contains :space-office-101 ;
    s223:contains :zone-hvac-north .
```

**Key RDF Patterns:**

- **Space types**: `s223:PhysicalSpace`, `s223:DomainSpace`
- **Labels**: `rdfs:label` for human-readable names
- **Identifiers**: `dcterms:identifier` for lookup keys
- **Project relationship**: `project s223:contains space` (external, not embedded)
- **Domain specification**: `s223:hasDomain` for domain spaces (HVAC, Lighting, etc.)

**URI Format:**

- Space: `urn:bms:Space:{spaceId}` or custom format
- Project: `urn:bms:Project:{projectId}`

---

## Acceptance Criteria

### 1. ✅ RDF triple persistence with BuildingMOTIF

- **Persistence**: Spaces stored as RDF triples in BuildingMOTIF's SQLite database
- **Space types**: Support both `s223:PhysicalSpace` and `s223:DomainSpace`
- **External project relationship**: `project s223:contains space` (not embedded in space)
- **URI format**: Consistent with Story 2.8 patterns
- **Labels and identifiers**: Use `rdfs:label` and `dcterms:identifier`

### 2. ✅ GET endpoint returns project-filtered spaces

```python
# GET /api/v1/223p/spaces?projectId=proj-123
# Query RDF graph for all space instances in project
# Convert to DTO list
[
    {
        "id": "space-office-101",
        "spaceTypeId": "s223:PhysicalSpace",
        "label": "Office 101",
        "domainType": null,  # Only for DomainSpace
        "createdAt": "2025-11-17T10:00:00Z"
    },
    {
        "id": "zone-hvac-north",
        "spaceTypeId": "s223:DomainSpace",
        "label": "North HVAC Zone",
        "domainType": "s223:Domain-HVAC",
        "createdAt": "2025-11-17T10:05:00Z"
    }
]
```

### 3. ✅ POST endpoint creates space instances

```python
# POST /api/v1/223p/spaces
{
    "projectId": "proj-123",
    "spaceTypeId": "s223:PhysicalSpace",  # or s223:DomainSpace
    "label": "Conference Room A",
    "domainType": null  # Required if spaceTypeId is DomainSpace
}

# Response
{
    "id": "space-conf-a",
    "spaceTypeId": "s223:PhysicalSpace",
    "label": "Conference Room A",
    "domainType": null,
    "createdAt": "2025-11-17T10:10:00Z"
}
```

### 4. ✅ Pure mapper functions for RDF ↔ DTO conversion

Create `src/mappers/space_mapper.py` with stateless functions:

```python
def to_space_dto(space_uri: URIRef, graph: Graph) -> SpaceInstanceDTO:
    """Convert RDF space instance to DTO (pure function)."""
    pass

def to_space_rdf_triples(
    space_uri: URIRef,
    space_dto: CreateSpaceRequestDTO
) -> list[tuple]:
    """
    Convert DTO to space RDF triples (pure function).

    Returns space instance triples.
    Does NOT include project relationship (see to_project_relationship_triples).
    """
    pass

def to_project_relationship_triples(
    project_uri: URIRef,
    space_uris: list[URIRef]
) -> list[tuple]:
    """
    Convert project contains relationships to RDF triples (pure function).

    Returns triples: project s223:contains space (for each space).
    """
    pass
```

### 5. ✅ SpacesController following Story 2.7/2.8 patterns

```python
class SpacesController:
    """Business logic for ASHRAE 223P spaces operations."""

    def __init__(self) -> None:
        self.adapter = BuildingMOTIFAdapter.get_instance()

    async def get_spaces(self, project_id: str) -> list[SpaceInstanceDTO]:
        """Get all spaces for project (mediator pattern)."""
        # Fetch RDF graph from adapter
        # Pass to mapper for conversion
        # Return DTOs
        pass

    async def create_space(
        self,
        request: CreateSpaceRequestDTO
    ) -> SpaceInstanceDTO:
        """Create new space instance."""
        # Generate unique space URI
        # Convert DTO to RDF triples (mapper)
        # Add triples via adapter
        # Add project relationship
        # Return DTO
        pass
```

### 6. ✅ Integration tests with session-scoped fixtures

- Use session-scoped `BuildingMOTIFAdapter` fixture (Story 2.7/2.8 pattern)
- Test GET: Create spaces → Query → Verify DTOs
- Test POST: Create space → Query RDF → Verify persistence
- Test project filtering: Create spaces in multiple projects → Query by project → Verify correct filtering
- Test empty project: GET with no spaces → Return empty list
- Test space types: Create both PhysicalSpace and DomainSpace → Verify correct types
- Test domain specification: Create DomainSpace with domain type → Verify `s223:hasDomain` triple

### 7. ✅ Performance optimization

- Batch RDF queries (avoid N+1 query problem)
- Use SPARQL queries with proper filters
- Test: 50 spaces query < 200ms

### 8. ✅ Designer app end-to-end workflow

- Create space via UI → POST endpoint
- Refresh page → GET endpoint → Spaces restored
- Assign space to equipment in mappings → Verify space reference persists
- Verify mock data removed (deleted `MOCK_SPACES` from `mock_templates.py`)

---

## Tasks / Subtasks

### Task 0: Remove mock data (AC: #8)

- [ ] **0.1**: Delete `MOCK_SPACES` from `src/data/mock_templates.py`
- [ ] **0.2**: Update docstring in `mock_templates.py` to note Story 2.9 completion
- [ ] **0.3**: Verify no other references to `MOCK_SPACES` in codebase

### Task 1: Create pure mapper functions (AC: #4)

- [ ] **1.1**: Create `src/mappers/space_mapper.py`
- [ ] **1.2**: Implement `to_space_dto(space_uri, graph) -> SpaceInstanceDTO`
  - Parse RDF triples for space
  - Extract type, label, domain (if DomainSpace)
  - Return DTO
- [ ] **1.3**: Implement `to_space_rdf_triples(space_uri, dto) -> list[tuple]`
  - Create `rdf:type` triple
  - Create `rdfs:label` triple
  - Create `dcterms:identifier` triple
  - If DomainSpace: create `s223:hasDomain` triple
- [ ] **1.4**: Implement `to_project_relationship_triples(project_uri, space_uris) -> list[tuple]`
  - Create `project s223:contains space` triples
- [ ] **1.5**: Write unit tests for all mapper functions
  - Test PhysicalSpace mapping
  - Test DomainSpace mapping
  - Test project relationship triples

### Task 2: Extend BuildingMOTIFAdapter for spaces (AC: #1)

- [ ] **2.1**: Add `get_project_spaces(project_id: str) -> Graph` method
  - SPARQL query: select all spaces where `project s223:contains space`
  - Return graph with space triples
- [ ] **2.2**: Add `create_space(project_id: str, space_dto: CreateSpaceRequestDTO) -> str` method
  - Generate unique space URI
  - Convert DTO to triples (via mapper)
  - Add space triples to graph
  - Add project relationship triple
  - Commit to database
  - Return space ID
- [ ] **2.3**: Write unit tests for adapter methods
  - Mock BuildingMOTIF operations
  - Test SPARQL query construction
  - Test triple addition

### Task 3: Implement SpacesController (AC: #5)

- [ ] **3.1**: Create `src/controllers/spaces_controller.py`
- [ ] **3.2**: Implement `get_spaces(project_id: str) -> list[SpaceInstanceDTO]`
  - Call `adapter.get_project_spaces(project_id)`
  - Convert graph to DTOs via mapper
  - Sort by created date or label
  - Return list
- [ ] **3.3**: Implement `create_space(request: CreateSpaceRequestDTO) -> SpaceInstanceDTO`
  - Validate space type
  - Call `adapter.create_space(project_id, dto)`
  - Query created space from graph
  - Convert to DTO via mapper
  - Return DTO
- [ ] **3.4**: Add error handling
  - Invalid space type → 422 Unprocessable Entity
  - Duplicate space ID → 409 Conflict
  - BuildingMOTIF errors → 500 Internal Server Error
- [ ] **3.5**: Write unit tests for controller
  - Mock adapter methods
  - Test successful flows
  - Test error cases

### Task 4: Update router endpoints (AC: #2, #3)

- [ ] **4.1**: Update `src/routers/spaces.py` GET endpoint
  - Remove mock data reference
  - Call `controller.get_spaces(project_id)`
  - Return list of DTOs
- [ ] **4.2**: Update `src/routers/spaces.py` POST endpoint
  - Remove mock data reference
  - Call `controller.create_space(request)`
  - Return created DTO
- [ ] **4.3**: Add request validation
  - Validate required fields
  - Validate space types
  - Validate domain type if DomainSpace

### Task 5: Write integration tests (AC: #6)

- [ ] **5.1**: Create `tests/integration/test_routers/test_spaces.py`
- [ ] **5.2**: Test GET endpoint
  - Create multiple spaces
  - Query via GET
  - Verify correct DTOs returned
- [ ] **5.3**: Test POST endpoint
  - Create space via POST
  - Query RDF graph directly
  - Verify triples persisted
- [ ] **5.4**: Test project filtering
  - Create spaces in 2 projects
  - Query project A
  - Verify only project A spaces returned
- [ ] **5.5**: Test empty project
  - Query project with no spaces
  - Verify empty list returned
- [ ] **5.6**: Test space types
  - Create PhysicalSpace
  - Create DomainSpace
  - Verify correct types in RDF
- [ ] **5.7**: Test domain specification
  - Create DomainSpace with `s223:Domain-HVAC`
  - Verify `s223:hasDomain` triple exists

### Task 6: Performance testing (AC: #7)

- [ ] **6.1**: Write performance test for GET endpoint
  ```python
  async def test_get_spaces_performance(shared_adapter):
      # Create 50 spaces
      # Time GET request
      assert query_time < 0.2  # < 200ms
  ```

### Task 7: Update Designer app (AC: #8)

- [ ] **7.1**: Verify TypeScript client already generated (Story 2.5)
- [ ] **7.2**: Test space creation via UI
  - Create space in modal
  - Verify POST endpoint called
  - Verify space appears in list
- [ ] **7.3**: Test space persistence
  - Create space
  - Refresh browser
  - Verify space restored from API
- [ ] **7.4**: Test space reference in mappings
  - Create space
  - Assign to equipment in mapping
  - Verify mapping persists with space reference

### Task 8: Update documentation (AC: All)

- [ ] **8.1**: Update `mock_templates.py` docstring
  - Note: Story 2.9 replaces mock spaces with RDF persistence
  - `MOCK_SPACES` deleted
- [ ] **8.2**: Update Epic 2 phase breakdown if needed
  - Document space RDF patterns
  - Already documented in epic breakdown

---

## Dev Notes

### Space Architecture Mini-Spec (REQUIRED)

**Story 2.9a must be completed before starting implementation.**

The mini-spec at `mini-specs/space-architecture.md` defines:

- Which space types to support (PhysicalSpace, DomainSpace, Zone?)
- UI patterns for space creation
- Domain type options and validation
- Space relationships (flat vs hierarchical)
- API contract (request/response DTOs)
- RDF triple patterns

**All implementation decisions must follow the mini-spec.**

### Architecture Alignment (from Stories 2.7 & 2.8)

**MVC Pattern:**

```
src/routers/spaces.py              # HTTP layer (request/response)
src/controllers/spaces_controller.py  # Business logic, orchestration
src/adapters/buildingmotif_adapter.py   # BuildingMOTIF SDK operations
src/mappers/space_mapper.py        # Pure RDF ↔ DTO conversion
```

**Key Decision:** No service layer - Controllers handle business logic directly.

### Learnings from Previous Story

**From Story 2.8: Implement Mappings Endpoints (Status: done)**

- **External Project Relationship Pattern**: Use `project s223:contains space` (not embedded in space instances)

  - Enables clean ASHRAE 223P export (spaces without project metadata)
  - Allows querying spaces by project via SPARQL
  - [Source: stories/2-8-implement-mappings-endpoints.md#Context]

- **Pure Mapper Functions**: Stateless RDF ↔ DTO conversion in `src/mappers/mapping_mapper.py`

  - Separate mapper for equipment triples and project relationship triples
  - Use same pattern for spaces: `to_space_rdf_triples()` and `to_project_relationship_triples()`
  - [Source: stories/2-8-implement-mappings-endpoints.md#AC-4]

- **BuildingMOTIF Model Persistence**: Use `bm.table_connection.get_db_model_by_name()` to load models

  - Catch `NoResultFound` to create new model
  - Call `bm.session.commit()` after `Model.create()` for persistence
  - Avoid model cache (Model.graph persists automatically via rdflib-sqlalchemy)
  - [Source: stories/2-8-implement-mappings-endpoints.md#Completion-Notes-2025-11-16]

- **SPARQL Query Patterns**: Decompose complex queries into focused CONSTRUCT/SELECT queries

  - Avoid nested OPTIONAL clauses
  - One query per responsibility
  - Explicit ordering with ORDER BY
  - [Source: stories/2-8-implement-mappings-endpoints.md#Completion-Notes-2025-11-16]

- **Session-Scoped Test Fixtures**: Reuse `BuildingMOTIFAdapter` singleton across tests

  - Avoid 30s+ ontology reload per test
  - Use unique project IDs for test isolation
  - Pattern at `tests/integration/conftest.py`
  - [Source: stories/2-8-implement-mappings-endpoints.md#Dev-Notes]

- **Type Safety**: Complete Python type hints (PEP 484)

  - Use `TypeAlias` for complex nested types
  - No `Any` types in production code
  - Specific return types (not generic `list` or `dict`)
  - [Source: stories/2-8-implement-mappings-endpoints.md#Dev-Notes]

- **Performance**: Batch operations, optimized SPARQL queries
  - Test: 104 tests passed in 23.86s
  - 100 mappings bulk save < 500ms
  - [Source: stories/2-8-implement-mappings-endpoints.md#Completion-Notes-2025-11-17]

**New Files Available from Story 2.8:**

- `src/mappers/mapping_mapper.py` - RDF mapping patterns to reference
- `src/controllers/mappings_controller.py` - Controller pattern example
- `tests/integration/test_routers/test_mappings.py` - Integration test patterns

### RDF Query Pattern (SPARQL)

**Query all spaces for project (using external relationship):**

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
PREFIX dcterms: <http://purl.org/dc/terms/>

SELECT ?space ?type ?label ?domain
WHERE {
  bms:project-123 s223:contains ?space .

  ?space rdf:type ?type ;
         rdfs:label ?label .

  OPTIONAL {
    ?space s223:hasDomain ?domain .
  }
}
```

**Create space triples:**

```python
# Physical Space
triples = [
    (space_uri, RDF.type, S223.PhysicalSpace),
    (space_uri, RDFS.label, Literal(label)),
    (space_uri, DCTERMS.identifier, Literal(space_id)),
]

# Domain Space (add domain type)
if space_type == "DomainSpace":
    triples.extend([
        (space_uri, RDF.type, S223.DomainSpace),
        (space_uri, S223.hasDomain, S223[domain_type]),
    ])

# Project relationship (separate)
project_triples = [
    (project_uri, S223.contains, space_uri)
]
```

### References

**Architecture:**

- [Space Architecture Mini-Spec](../mini-specs/space-architecture.md) - **REQUIRED** - Defines space types, UI patterns, API contract (Story 2.9a)

**Epic Documentation:**

- [Epic 2 Phase Breakdown](../epic2/epic-2-phase-breakdown.md#story-29) - Story 2.9 requirements
- [Story 2.7](./2-7-implement-templates-endpoint.md) - Controller/adapter patterns
- [Story 2.8](./2-8-implement-mappings-endpoints.md) - External project relationship pattern
- [Story 2.9a](./2-9a-space-architecture-mini-spec.md) - Space architecture decisions

**BuildingMOTIF:**

- [BuildingMOTIF Docs](https://buildingmotif.readthedocs.io/)
- [RDFLib Documentation](https://rdflib.readthedocs.io/) - RDF graph operations

**ASHRAE 223P:**

- [ASHRAE 223P Ontology](https://data.ashrae.org/standard223) - Space types and relationships

---

## Dev Agent Record

### Context Reference

<!-- Path(s) to story context XML will be added here by context workflow -->

### Agent Model Used

{{agent_model_name_version}}

### Debug Log References

### Completion Notes List

### File List
