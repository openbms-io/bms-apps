# ADR-002: Inline SHACL Validation in Mappings Endpoint

**Date**: 2025-11-17
**Status**: Accepted
**Context**: Story 2.10 - SHACL Validation Integration

---

## Decision

We will implement SHACL validation **inline** within the existing `POST /api/v1/223p/mappings` endpoint, rather than creating a separate `POST /api/v1/223p/validate` endpoint.

---

## Context

Story 2.10 was originally designed with a separate validation endpoint:

- Frontend: User clicks "Confirm" → Call `POST /validate` → If valid, call `POST /mappings`
- Backend: Two separate endpoints, each with SHACL validation logic

During sprint planning review, we reconsidered this architecture and identified a simpler approach:

- Frontend: User clicks "Confirm" → Call `POST /mappings` (validation happens automatically)
- Backend: One endpoint with inline validation before persistence

---

## Options Considered

### Option A: Separate Validation Endpoint (Original Design)

**Flow:**

```
Frontend: Click Confirm
  ↓
POST /api/v1/223p/validate
  → Run SHACL validation
  → Return { isValid, errors, warnings }
  ↓
If valid:
  POST /api/v1/223p/mappings
    → Persist to RDF
    → Return created mapping
```

**Pros:**

- Separation of concerns (validate vs persist)
- Can validate without persisting (dry-run capability)
- Could validate multiple mappings at once without side effects

**Cons:**

- Two API calls required (validate, then POST)
- More complex frontend flow
- Validation could be skipped (user error or intentional)
- Duplicate SHACL logic between endpoints
- More code to maintain
- Violates "DO NOT OVERENGINEER" principle

### Option B: Inline Validation (Selected)

**Flow:**

```
Frontend: Click Confirm
  ↓
POST /api/v1/223p/mappings
  → Run SHACL validation
  → If invalid: Return 400 with errors
  → If valid: Persist to RDF, return 201
```

**Pros:**

- ✅ **Simpler flow** - one click, one API call
- ✅ **Validation always happens** - cannot be skipped
- ✅ **Fail fast** - errors surface immediately on save attempt
- ✅ **No duplication** - SHACL logic in one place
- ✅ **Better UX** - user doesn't need "validate first, then save" mental model
- ✅ **Aligns with CLAUDE.md principles:**
  - "Fail Fast" - Surface issues immediately
  - "Prop Up Issues Faster" - Make problems visible quickly
  - "DO NOT OVERENGINEER" - Simple, direct implementations

**Cons:**

- Cannot validate without attempting to persist (but do we need this?)

---

## Decision Rationale

### 1. Alignment with Development Philosophy

From `CLAUDE.md`:

> **Fail Fast**: Surface issues immediately
> **Prop Up Issues Faster**: Make problems visible quickly
> **DO NOT OVERENGINEER**: Simple, direct implementations. Avoid premature abstractions. Minimal viable solutions that can evolve.

Inline validation embodies all three principles:

- Errors surface at the exact moment of save attempt (fail fast)
- User gets immediate feedback on what's wrong (prop up issues faster)
- One endpoint instead of two (do not overengineer)

### 2. User Experience

**Option A (Separate Endpoint):**

- User clicks "Confirm"
- Spinner appears ("Validating...")
- If valid, second spinner appears ("Saving...")
- Two network round-trips

**Option B (Inline Validation):**

- User clicks "Confirm"
- Spinner appears ("Saving...")
- Either succeeds or shows validation errors
- One network round-trip

Option B is simpler and faster.

### 3. Frontend Complexity

**Option A:**

```typescript
async function handleConfirm() {
  // Step 1: Validate
  const validationResult = await validateMapping(mapping);
  if (!validationResult.isValid) {
    showErrors(validationResult.errors);
    return;
  }

  // Step 2: Persist (if user didn't cancel)
  const created = await createMapping(mapping);
  showSuccess();
}
```

**Option B:**

```typescript
async function handleConfirm() {
  try {
    await createMapping(mapping); // Validates + persists
    showSuccess();
  } catch (error) {
    if (error.status === 400) {
      showErrors(error.detail.errors); // SHACL errors
    }
  }
}
```

Option B is 50% less code and removes the possibility of user confusion between validate and save steps.

### 4. Backend Implementation

Both options require the same `ValidationService` implementation. The only difference is where it's called:

**Option A:**

```python
# POST /api/v1/223p/validate
def validate_mapping(request):
    return validation_service.validate_equipment_mapping(request)

# POST /api/v1/223p/mappings
def create_mapping(request):
    # Validation logic duplicated or skipped?
    return mappings_service.create_equipment_mapping(request)
```

**Option B:**

```python
# POST /api/v1/223p/mappings
def create_mapping(request):
    # Validate first
    validation_result = validation_service.validate_equipment_mapping(request)
    if not validation_result.is_valid:
        raise HTTPException(status_code=400, detail=validation_result.errors)

    # Then persist
    return mappings_service.create_equipment_mapping(request)
```

Option B has validation logic in exactly one place, making it impossible to skip or get out of sync.

### 5. Do We Need Dry-Run Validation?

The only advantage of a separate validation endpoint is the ability to validate without persisting. But when would we use this?

**Scenarios considered:**

- ❌ **User wants to check if mapping is valid before saving** - This is what inline validation does automatically
- ❌ **Bulk validation of many mappings** - Not in Epic 2 scope
- ❌ **Pre-flight validation in UI** - Could be useful, but adds complexity and may confuse users
- ❌ **API testing** - Can test validation by sending invalid requests to POST /mappings (expect 400)

**Conclusion:** No compelling use case for dry-run validation in Epic 2 scope.

---

## Implementation Pattern

```python
from fastapi import APIRouter, HTTPException, status
from src.services.validation_service import ValidationService
from src.services.mappings_service import MappingsService
from src.dto.equipment_mapping_dto import CreateEquipmentMappingDTO

router = APIRouter()
validation_service = ValidationService()
mappings_service = MappingsService()

@router.post("/api/v1/223p/mappings", status_code=status.HTTP_201_CREATED)
def create_equipment_mapping(request: CreateEquipmentMappingDTO):
    """
    Create a new equipment mapping with inline SHACL validation.

    Validates the mapping against ASHRAE 223P SHACL constraints before persisting.
    If validation fails, returns 400 Bad Request with detailed error messages.
    """
    # Step 1: Validate with BuildingMOTIF SHACL engine
    validation_result = validation_service.validate_equipment_mapping(request)

    # Step 2: If invalid, return 400 with SHACL errors
    if not validation_result.is_valid:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail={
                "validationType": "SHACL",
                "errors": validation_result.errors,
                "warnings": validation_result.warnings
            }
        )

    # Step 3: If valid, persist to RDF and return created mapping
    mapping = mappings_service.create_equipment_mapping(request)
    return mapping
```

**Frontend Error Handling:**

```typescript
try {
  const mapping = await api.createEquipmentMapping(request);
  showSuccess("Mapping created successfully");
} catch (error) {
  if (error.status === 400 && error.detail?.validationType === "SHACL") {
    // Show SHACL validation errors in modal
    showValidationErrors(error.detail.errors, error.detail.warnings);
  } else {
    // Show generic error
    showError("Failed to create mapping");
  }
}
```

---

## Consequences

### Positive

- ✅ Simpler frontend code (one API call instead of two)
- ✅ Validation always happens (cannot be skipped)
- ✅ Faster user experience (one round-trip instead of two)
- ✅ Less backend code to maintain (one endpoint instead of two)
- ✅ No duplication of SHACL validation logic
- ✅ Follows fail-fast principle
- ✅ Aligns with CLAUDE.md development philosophy

### Negative

- ❌ Cannot validate without persisting (but no use case identified)
- ❌ If we later need dry-run validation, will require adding a separate endpoint

### Mitigations

- If dry-run validation becomes necessary in the future (e.g., bulk validation), we can add a `POST /api/v1/223p/validate` endpoint at that time
- The `ValidationService` is already isolated, so adding a separate endpoint would be a small change
- Following YAGNI (You Aren't Gonna Need It) principle - don't build features until they're needed

---

## Impact on Story 2.10

**Original Story 2.10:**

- Title: "Implement `/api/v1/223p/validate` SHACL endpoint"
- Scope: Create new validation endpoint
- Effort: ~4 hours

**Updated Story 2.10:**

- Title: "Implement SHACL Validation in Mappings Endpoint"
- Scope: Add inline validation to existing POST /mappings endpoint
- Effort: ~3 hours (reduced - no new endpoint)

---

## References

- **Story 2.10**: Implement SHACL Validation in Mappings Endpoint
- **Epic 2 Phase Breakdown**: `epic2/epic-2-phase-breakdown.md`
- **CLAUDE.md**: Project development philosophy (Fail Fast, DO NOT OVERENGINEER)
- **Related ADRs**:
  - ADR-001: Descope Space Management from Epic 2

---

## Approval

**Proposed by**: SM Agent (Bob), 2025-11-17
**Reviewed by**: Amol (Product Owner), 2025-11-17
**Approved by**: Amol, 2025-11-17

---

## Revision History

| Date       | Version | Changes                   |
| ---------- | ------- | ------------------------- |
| 2025-11-17 | 1.0     | Initial decision document |
