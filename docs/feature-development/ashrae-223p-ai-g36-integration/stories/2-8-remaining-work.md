# Story 2.8: Remaining Work Summary

**Story:** Implement Mappings Endpoints with Real Persistence
**Status:** In Progress (Backend 100% Done, Tests 80% Done)
**Generated:** 2025-11-15
**Test Status:** 95/95 passing (28 unit + 67 integration)

---

## ✅ COMPLETED Work

### Backend Implementation (100% Complete)

**Task 0: Validation Tests** ✅
- test_external_project_relationship_pattern
- test_bacnet_external_reference_223p_compliance
- test_point_id_format_split_no_parsing
- test_clean_223p_ttl_export_no_project_metadata

**Task 1: Pure Mapper Functions** ✅
- Created `src/mappers/mapping_mapper.py`
- Implemented `to_equipment_rdf_triples()`
- Implemented `to_project_relationship_triples()`
- Added URI helper functions
- Added RDF namespace constants

**Task 2: MappingsModel** ✅ (refactored from adapter)
- Created `src/models/mappings_model.py`
- Implemented `get_all_mappings()` method
- Implemented `replace_all_mappings()` with atomic transaction
- Added `transaction()` context manager
- Moved SPARQL queries from adapter to model

**Task 3: MappingsController** ✅
- Created `src/controllers/mappings_controller.py`
- Implemented `get_mappings()` - delegates to model
- Implemented `save_mappings()` - delegates to model
- Added error handling with logging

**Task 4: Update Router** ✅
- Updated `src/routers/mappings.py`
- Uses MappingsController
- Removed `_MAPPINGS_STORE` in-memory dict

**Task 5: Integration Tests** ✅ (partial - 6/9 tests)
- test_get_mappings_returns_200_with_static_data
- test_get_mappings_requires_project_id
- test_post_mappings_returns_200_with_static_data
- test_post_then_get_mappings_persists_data (roundtrip)
- test_post_mapping_with_physical_space_only
- test_post_mapping_with_domain_spaces_only
- test_post_mapping_with_both_physical_and_domain_spaces
- test_post_mapping_with_no_spaces
- test_mappings_schemas_in_openapi

**Architecture Evolution** ✅
- Original: Router → Controller → Adapter
- Implemented: Router → Controller → Model → Adapter
- Model layer handles business logic and transactions
- Adapter is pure BuildingMOTIF SDK wrapper

---

## 🔴 REMAINING Work

### HIGH PRIORITY: Missing Integration Tests (AC #3, #7)

#### Test 1: Atomic Transaction Rollback
**File:** `tests/integration/test_routers/test_mappings.py`
**Purpose:** Verify atomic transaction rolls back on error (AC #3)

```python
def test_atomic_transaction_rollback(shared_adapter) -> None:
    """
    Test atomic transaction rolls back on error.

    Verifies:
    - Save initial mappings successfully
    - Attempt to save invalid mappings (trigger error)
    - Verify original mappings still exist (no partial updates)
    - Verify atomic all-or-nothing semantics
    """
    # Implementation needed
    pass
```

**Acceptance Criteria:**
- If save_mappings() fails, previous mappings must remain unchanged
- No partial updates allowed
- Transaction must use begin_nested() → commit or rollback

---

#### Test 2: Bulk Replace Clears Old Mappings
**File:** `tests/integration/test_routers/test_mappings.py`
**Purpose:** Verify replace_all_mappings() clears old data (AC #3)

```python
def test_bulk_replace_clears_old_mappings(shared_adapter) -> None:
    """
    Test bulk replace operation clears existing mappings.

    Verifies:
    - Save initial mappings (point-1, point-2)
    - Save NEW mappings (point-3, point-4) - different pointIds
    - GET mappings - verify ONLY new mappings exist
    - Verify old mappings (point-1, point-2) were cleared
    """
    # Implementation needed
    pass
```

**Acceptance Criteria:**
- replace_all_mappings() must clear ALL existing triples first
- Only new mappings should exist after save
- Clear operation must use `model.graph.remove((None, None, None))`

---

#### Test 3: Performance Test (100+ Mappings)
**File:** `tests/integration/test_routers/test_mappings.py`
**Purpose:** Verify performance targets (AC #7)

```python
def test_performance_100_mappings(shared_adapter) -> None:
    """
    Test performance with 100+ mappings.

    Verifies:
    - Bulk save 100 mappings < 500ms
    - Bulk read 100 mappings < 300ms
    - No N+1 query problems
    - Batch RDF operations working
    """
    import time

    # Create 100 test mappings
    mappings = {}
    for i in range(100):
        point_id = f"device,{i}:analog-input,{i}"
        mappings[point_id] = SemanticMappingDTO(
            equipment_type_id="vav-reheat",
            device_type_id="damper",
            property_id="damper-feedback",
            physical_space_id=None,
            domain_space_ids=None,
        )

    # Test save performance
    request = SaveMappingsRequestDTO(
        project_id=f"perf-test-{uuid.uuid4()}",
        mappings=mappings
    )

    start = time.time()
    response = client.post("/api/v1/223p/mappings", json=request.model_dump(by_alias=True))
    save_duration = time.time() - start

    assert response.status_code == 200
    assert save_duration < 0.5  # < 500ms

    # Test read performance
    start = time.time()
    response = client.get(f"/api/v1/223p/mappings?projectId={request.project_id}")
    read_duration = time.time() - start

    assert response.status_code == 200
    assert read_duration < 0.3  # < 300ms
    assert len(response.json()["mappings"]) == 100
```

**Acceptance Criteria:**
- 100 mappings bulk save < 500ms
- 100 mappings bulk read < 300ms
- Must use batch SPARQL operations (avoid N+1)

---

### MEDIUM PRIORITY: Frontend Verification (AC #8)

#### Task 6.2: Test Bulk Save Mutation Hook
**Location:** Designer app
**Action:** Manual test of `useSaveMappingsMutation()`

**Test Steps:**
1. Open Designer app at http://localhost:3000
2. Navigate to mappings interface
3. Select equipment → device → property
4. Click "Save Mappings"
5. Verify POST request to `/api/v1/223p/mappings`
6. Verify response status 200
7. Check browser network tab for request payload

**Expected:**
- Mutation hook calls correct endpoint
- Bulk POST with all mappings
- Success feedback shown to user

---

#### Task 6.4: End-to-End Workflow Test
**Location:** Designer app
**Action:** Manual end-to-end test

**Test Steps:**
1. Create new project in Designer
2. Add 3-5 point mappings
3. Click "Save Mappings" → Verify success message
4. **Close browser tab completely**
5. Reopen Designer app → Navigate to same project
6. Verify all mappings restored from API (not sessionStorage)
7. Edit one mapping
8. Click "Save Mappings" again
9. Refresh page → Verify edit persisted

**Expected:**
- Mappings persist across browser sessions
- No sessionStorage usage (all persistence via API)
- Edit workflow works correctly

---

### LOW PRIORITY: Documentation Updates

#### Task 7.1: Update mock_templates.py Docstring
**File:** Unknown location - need to find file
**Action:** Add note about Story 2.8

```python
"""
Mock templates for testing.

Note: Story 2.8 replaced in-memory mappings (_MAPPINGS_STORE)
with RDF persistence via MappingsModel. MOCK_MAPPINGS removed.
"""
```

---

#### Task 7.2: Update Epic 2 Tech Spec
**File:** `docs/feature-development/ashrae-223p-ai-g36-integration/epic2/tech-spec-review.md`
**Action:** Document Model layer architecture

**Content to Add:**

```markdown
### Model Layer Pattern (Story 2.8 Refactoring)

**Architecture Evolution:**
- **Original**: Router → Controller → Adapter
- **Refactored**: Router → Controller → Model → Adapter

**Responsibilities:**

| Layer | Responsibilities |
|-------|-----------------|
| Router | HTTP request/response, validation |
| Controller | Orchestration, error handling |
| **Model** | **Business logic, transactions, SPARQL queries** |
| Adapter | Pure BuildingMOTIF SDK wrapper |

**Benefits:**
- Clean separation of concerns
- Transaction management centralized in model
- Adapter simplified (generic SDK operations only)
- Testable business logic (model can be unit tested)
- Follows Domain-Driven Design principles

**Implementation:**
- `src/models/mappings_model.py` - Mappings business logic
- `src/models/templates_model.py` - Templates business logic
- Both follow same pattern for consistency
```

---

## 📋 Summary Checklist

### To Complete Story 2.8:

- [ ] **Add 3 integration tests** (HIGH)
  - [ ] test_atomic_transaction_rollback()
  - [ ] test_bulk_replace_clears_old_mappings()
  - [ ] test_performance_100_mappings()

- [ ] **Frontend verification** (MEDIUM)
  - [ ] Manual test bulk save mutation hook
  - [ ] End-to-end workflow test (save → close → reopen)
  - [ ] Document results

- [ ] **Documentation** (LOW)
  - [ ] Update mock_templates.py docstring
  - [ ] Update Epic 2 tech spec with Model layer

- [ ] **Mark story complete**
  - [ ] Update story.md task checkboxes
  - [ ] Run /workflow-status to verify
  - [ ] Mark story status as "ready-for-review"

---

## ✅ Story Context XML Updated

The Story Context XML has been updated with:

1. ✅ Status changed from "drafted" to "in-progress"
2. ✅ Task 2 updated: "BuildingMOTIFAdapter" → "MappingsModel"
3. ✅ Architecture constraint updated: added Model layer
4. ✅ Interfaces section updated: replaced adapter methods with model methods
5. ✅ Added MappingsModel artifact to code artifacts section

**File:** `docs/feature-development/ashrae-223p-ai-g36-integration/stories/2-8-implement-mappings-endpoints.context.xml`

---

## 🎯 Next Steps

1. **Run tests** to confirm 95/95 still passing after context updates
2. **Add 3 missing integration tests** (estimated 1-2 hours)
3. **Frontend manual testing** (estimated 30 minutes)
4. **Update documentation** (estimated 30 minutes)
5. **Mark story complete** and request code review

**Estimated Time to Complete:** 2-3 hours
