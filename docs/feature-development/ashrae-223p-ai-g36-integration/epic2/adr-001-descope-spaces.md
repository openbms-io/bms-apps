# ADR-001: Descope Space Management from Epic 2

**Date**: 2025-11-17
**Status**: Accepted
**Deciders**: Amol (Product Owner), Claude (Dev Agent)

---

## Context

Epic 2 (BuildingMOTIF API Integration) originally included Stories 2.9/2.9a for implementing ASHRAE 223P space management (Zone, DomainSpace, PhysicalSpace). During Story 2.9a architecture planning, significant complexity emerged around:

1. **UI Organization**: Spaces require separate UI grouping from equipment
2. **Template Integration**: BuildingMOTIF space templates create multiple interconnected entities
3. **Tree Visualization**: Hierarchical space relationships need complex tree view
4. **Equipment Relationships**: Equipment-to-space linking adds workflow complexity

**Epic 2 Original Goal** (from `epic2/epic-2-phase-breakdown.md`):

> "BuildingMOTIF API Integration - Replace Epic 1 mock services with real BuildingMOTIF SDK integration"

**Epic 2 Purpose** (from `epic2/epic-2-decisions.md`):

> "Create Python FastAPI wrapper around BuildingMOTIF SDK to enable G36 validation"

**Project Goal** (from context):

> "The goal of using 223P is help with G36 validation"

---

## Decision

**We will descope space management (Stories 2.9/2.9a) from Epic 2 and move it to a future "Space Management" epic.**

---

## Rationale

### 1. G36 Validation Doesn't Require Spaces

**What G36 Validation Needs:**

- ✅ **Equipment types** (VAV, AHU, Fan, etc.) - Story 2.8 provides this
- ✅ **Device types** (sensors, actuators, setpoints) - Story 2.8 provides this
- ✅ **Observable properties** (temperature, pressure, flow) - Story 2.8 provides this
- ✅ **SHACL validation** - Story 2.10 will provide this
- ❌ **Spaces** (PhysicalSpace, DomainSpace, Zone) - NOT required for G36 validation

**G36 Sequences Validate Against:**

- Control loop configuration (equipment + sensors + actuators)
- Parameter bounds (min/max values)
- Connection types (sensor → input port, actuator → output port)

**Spaces are optional metadata** for G36 validation.

### 2. Space Management Is a Separate Domain

**Epic 2 Stories Review:**

| Story     | Purpose                 | Requires Spaces?                          |
| --------- | ----------------------- | ----------------------------------------- |
| 2.1-2.6   | BuildingMOTIF SDK setup | ❌ No                                     |
| 2.7       | Templates endpoint      | ❌ No (equipment templates only)          |
| 2.8       | Equipment mappings      | ⚠️ Has `hasDomain` field (can be removed) |
| 2.9/2.9a  | Space management        | ✅ Yes (THE ENTIRE POINT)                 |
| 2.10      | Validation endpoint     | ❌ No                                     |
| 2.11      | Error handling          | ❌ No                                     |
| 2.12-2.13 | AI suggestions          | ❌ No (uses equipment templates)          |
| 2.14      | Triple inspector        | ❌ No                                     |

**Finding**: Only Stories 2.9/2.9a require spaces. Story 2.8 has `hasDomain` field but it's not essential.

**Spaces introduce different concerns:**

- **Equipment domain**: Control systems, I/O mapping, G36 validation
- **Space domain**: Building architecture, facilities management, occupancy zones

These are **orthogonal concerns** that can be developed independently.

### 3. Complexity Doesn't Match Epic 2 Scope

**Story 2.9a Architecture Exploration Revealed:**

**UI Complexity:**

- Need separate "Spaces" tab (vs current equipment-focused UI)
- Tree view visualization (hierarchical relationships)
- Three different space types with different forms
- Multiple relationship types (contains, encloses, hasDomainSpace)

**Backend Complexity:**

- Three entity types with different SHACL constraints
- Hierarchical queries (parent-child relationships)
- Template evaluation creates multiple entities at once (hvac-zone → Zone + DomainSpace + PhysicalSpace)
- Validation of containment rules (what can contain what)

**Integration Complexity:**

- Equipment-to-space linking (`hasDomain` property)
- Template-based discovery (suggest spaces based on equipment)
- Inline creation from Equipment tab (cross-tab workflows)
- Bi-directional references (equipment → space, space → equipment)

**Comparison to Story 2.8 (Equipment Mappings):**

- Story 2.8: Single entity type (Equipment), flat list, direct RDF creation
- Story 2.9: Three entity types, hierarchical tree, template-based creation + manual creation

**Estimated Effort:**

- Story 2.8 (Equipment): ~4 hours actual
- Stories 2.9/2.9a (Spaces): ~15-20 hours estimated (4x-5x complexity)

Spaces deserve their own epic.

### 4. Focus Epic 2 on Core BuildingMOTIF Integration

**Epic 2 Phases** (from `epic2/epic-2-phase-breakdown.md`):

- **Phase 0**: Foundation (FastAPI scaffolding) ✅ Done
- **Phase 1**: Mock endpoints for interface validation ✅ Done
- **Phase 2**: Real BuildingMOTIF integration (Templates 2.7, Mappings 2.8) ✅ Done
- **Phase 3**: AI enhancement (Stories 2.12-2.13) ⏳ Backlog

**With spaces removed, Epic 2 becomes:**

- ✅ BuildingMOTIF SDK integrated
- ✅ Equipment templates available
- ✅ Equipment mappings working
- ✅ Epic 1 UI works with real data
- ⏳ Validation endpoint (Story 2.10)
- ⏳ AI suggestions using real templates
- ⏳ Triple inspector for debugging

**This is a complete, cohesive epic focused on "BuildingMOTIF integration for G36 validation".**

### 5. Mini-Spec Work Not Wasted

**Story 2.9a produced comprehensive architecture:**

- 1139-line mini-spec document
- 15 architectural decisions documented
- Complete space type taxonomy (PhysicalSpace, DomainSpace, Zone)
- UI interaction patterns designed
- API contract specified (POST/GET endpoints, DTOs, validation)
- RDF patterns and SPARQL queries documented
- 5 resolved questions + 4 open questions flagged

**This work is preserved** in `mini-specs/space-architecture.md` for future Space Management epic.

**Value retained:**

- No rework needed when spaces are implemented
- Clear requirements already defined
- Architecture decisions already made
- Can start implementation immediately when prioritized

---

## Consequences

### Positive

✅ **Epic 2 scope is clear and focused**: BuildingMOTIF integration for G36 validation
✅ **Reduced complexity**: Spaces won't complicate Epic 2 stories
✅ **Faster delivery**: Epic 2 can complete sooner without space management
✅ **Better separation of concerns**: Equipment (control) vs Spaces (architecture) domains decoupled
✅ **Architecture work preserved**: Mini-spec ready for future Space Management epic
✅ **G36 validation unblocked**: All required components available (equipment types, validation)

### Negative

⚠️ **Story 2.8 has partial space references**: `hasDomain` field exists in equipment mappings

- **Mitigation**: Remove `hasDomain` from Story 2.8 DTOs and UI in this descoping work
- **Rollback effort**: ~1 hour to update Story 2.8 documentation and note field removal

⚠️ **Equipment-to-space relationship deferred**: Can't link equipment to DomainSpaces yet

- **Mitigation**: Not needed for G36 validation
- **Future**: Space Management epic will add `hasDomain` back when spaces are implemented

⚠️ **Stories 2.9/2.9a marked out-of-scope**: May look like "incomplete epic"

- **Mitigation**: Clear documentation of descoping rationale (this ADR)
- **Status update**: Stories marked `out-of-scope` with reference to future Space Management epic

### Neutral

↔️ **Template endpoint (Story 2.7) doesn't return space templates**: Only equipment templates

- **Current state**: Story 2.7 already focused on equipment templates
- **Future**: Space templates can be added to templates endpoint in Space Management epic

↔️ **BuildingMOTIF SDK space capabilities unused**: SDK supports spaces, but we don't expose them yet

- **Current state**: SDK installed and working for equipment
- **Future**: Same SDK used for spaces when Space Management epic is implemented

---

## Changes Required

### Story 2.8 Rollback

**File**: `stories/2-8-implement-mappings-endpoints.md`

**Changes**:

- Add section "2025-11-17: Spaces Descoped from Epic 2"
- Note: `hasDomain` field removed from equipment mapping DTOs
- Note: Equipment type and device type mappings remain (needed for G36)
- Status remains `done` but with partial rollback documented

**Frontend**:

- Remove "Domain Space" dropdown from equipment mapping modal
- Remove `hasDomain` from CreateEquipmentMappingDTO
- Remove `domainSpaceIds` from EquipmentInstanceDTO

**Backend**:

- Remove `hasDomain` from POST request DTO
- Remove `domainSpaceIds` from GET response DTO
- Remove DomainSpace RDF triple creation from mappings endpoint

### Stories 2.9/2.9a Descoping

**Files**:

- `stories/2-9a-space-architecture-mini-spec.md`
- `stories/2-9-implement-spaces-endpoints.md`

**Changes**:

- Status: `ready-for-review`/`drafted` → `out-of-scope`
- Add header:
  ```
  **OUT OF SCOPE - Descoped from Epic 2**
  **Date**: 2025-11-17
  **Reason**: Space management complexity doesn't align with Epic 2 G36 validation focus
  **Future**: Moved to future "Space Management" epic (see GitHub issue)
  **Reference**: ADR-001
  ```

### Sprint Status Update

**File**: `sprint-status.yaml`

**Changes**:

```yaml
2-8-implement-mappings-endpoints: done # Partial rollback: hasDomain field removed (2025-11-17)
2-9a-space-architecture-mini-spec: out-of-scope # Descoped - See ADR-001
2-9-implement-spaces-endpoints: out-of-scope # Descoped - See ADR-001
```

### Mini-Spec Preservation

**File**: `mini-specs/space-architecture.md`

**Changes**:

- Add header:
  ```
  **STATUS**: OUT OF SCOPE for Epic 2 (Preserved for Future Epic)
  **Created**: 2025-11-17
  **Descoped**: 2025-11-17
  **Reason**: Space management warrants dedicated epic (see ADR-001)
  **Future Use**: Will be implementation guide for Space Management epic
  ```
- Keep all content intact (1139 lines)

### Documentation Updates

**New file**: `epic2/adr-001-descope-spaces.md` (this document)

**New GitHub issue**: "Epic: ASHRAE 223P Space Management" (user will create manually)

---

## Alternatives Considered

### Alternative 1: Keep Spaces in Epic 2

**Rejected**: Would delay Epic 2 completion by 2-3 weeks, adds complexity unrelated to G36 validation

### Alternative 2: Implement Minimal Spaces (PhysicalSpace Only)

**Rejected**: Incomplete solution - DomainSpace is the primary equipment relationship, PhysicalSpace alone doesn't provide value

### Alternative 3: Defer All Space-Related Work (Including Story 2.8 `hasDomain`)

**Accepted (in part)**: Story 2.8 keeps equipment type and device type mappings, but removes `hasDomain` field

---

## Review

### Stories Remaining in Epic 2

- 2.1-2.6: BuildingMOTIF SDK setup ✅ Done
- 2.7: Templates endpoint ✅ Done
- 2.8: Equipment mappings (revised - no spaces) ✅ Done (with rollback)
- 2.10: Validation endpoint ⏳ Backlog
- 2.11: Error handling ⏳ Backlog
- 2.12-2.13: AI suggestions ⏳ Backlog
- 2.14: Triple inspector ⏳ Backlog

**Total**: 11 stories (was 13, removed 2)

### Epic 2 Goal Achievement

✅ **BuildingMOTIF SDK integrated** (Stories 2.1-2.6)
✅ **Real templates available** (Story 2.7)
✅ **Real equipment mappings** (Story 2.8)
✅ **Epic 1 UI works with real data** (Phase 2 complete)
⏳ **Validation enabled** (Story 2.10)
⏳ **AI uses real templates** (Stories 2.12-2.13)

**Epic 2 goal preserved**: BuildingMOTIF integration for G36 validation

---

## References

- **Epic 2 Phase Breakdown**: `epic2/epic-2-phase-breakdown.md`
- **Epic 2 Decisions**: `epic2/epic-2-decisions.md`
- **Space Architecture Mini-Spec**: `mini-specs/space-architecture.md`
- **Story 2.8**: `stories/2-8-implement-mappings-endpoints.md`
- **Story 2.9a**: `stories/2-9a-space-architecture-mini-spec.md`
- **Story 2.9**: `stories/2-9-implement-spaces-endpoints.md`
- **Sprint Status**: `sprint-status.yaml`
