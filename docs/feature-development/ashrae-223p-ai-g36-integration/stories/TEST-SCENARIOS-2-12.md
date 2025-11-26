# Test Scenarios for Story 2.12 - System Instances & BACnet References

## Purpose

This document provides comprehensive test scenarios for Dev agent to implement Story 2.12 deferred testing tasks (Tasks 1.5, 1.6, 2.5, 2.6).

**Target Files:**

- `apps/building-semantics-api-app/src/models/systems_model.py` (232 lines)
- `apps/building-semantics-api-app/src/models/bacnet_references_model.py` (367 lines)
- `apps/building-semantics-api-app/src/models/devices_model.py` (433 lines - read-only queries)

---

## File Structure

```
tests/
├── unit/
│   ├── test_models/
│   │   ├── test_systems_model.py          # NEW - Task 1.5
│   │   └── test_bacnet_references_model.py # NEW - Task 2.5
│   └── ...existing files...
└── integration/
    ├── test_systems_crud.py                # NEW - Task 1.6
    └── test_bacnet_references_crud.py      # NEW - Task 2.6
```

---

## Testing Patterns to Follow

### Unit Tests Pattern

**Reference:** `tests/unit/test_buildingmotif_adapter.py`, `tests/unit/test_services/test_validation_service.py`

**Key Principles:**

- Mock external dependencies (BuildingMOTIF SDK, Model, SPARQL queries)
- Test individual methods in isolation
- Test edge cases and error handling
- Arrange-Act-Assert pattern
- DO NOT MOCK SYSTEM UNDER TEST (only mock BuildingMOTIF dependencies)

**Example Structure:**

```python
import pytest
from unittest.mock import Mock, patch

@pytest.fixture
def mock_adapter():
    """Mock BuildingMOTIF adapter for isolated testing."""
    with patch("src.models.systems_model.BuildingMOTIFAdapter") as mock:
        mock_adapter = Mock()
        mock.get_instance.return_value = mock_adapter
        yield mock_adapter

def test_method_name_scenario(mock_adapter):
    """Test description."""
    # Arrange
    mock_model = Mock()
    mock_adapter.get_or_create_model.return_value = mock_model

    # Act
    result = SystemsModel(mock_adapter).create_system(...)

    # Assert
    assert result["system_uri"] == "expected_value"
    mock_adapter.get_or_create_model.assert_called_once()
```

### Integration Tests Pattern

**Reference:** `tests/integration/test_buildingmotif_integration.py`

**Key Principles:**

- Use real BuildingMOTIF adapter (shared_adapter fixture from conftest.py)
- Test end-to-end flows
- Verify data persists in RDF graph
- Use SPARQL queries to verify state
- Test with real ASHRAE 223P templates

**Example Structure:**

```python
from src.adapters import BuildingMOTIFAdapter

def test_method_name_end_to_end(shared_adapter: BuildingMOTIFAdapter):
    """Test description with real BuildingMOTIF."""
    # Arrange
    model = SystemsModel(shared_adapter)

    # Act
    result = model.create_system(...)

    # Assert - query RDF graph
    query = """
        PREFIX s223: <http://data.ashrae.org/standard223#>
        SELECT ?system WHERE { ?system a s223:System }
    """
    results = shared_adapter.query_model(...)
    assert len(results) == 1
```

---

## Task 1.5: Unit Tests for systems_model.py

**File:** `tests/unit/test_models/test_systems_model.py`

**Implementation File:** `src/models/systems_model.py:14-232`

### Test Scenarios

#### 1. create_system - Template Instantiation

**Acceptance Criteria:** Story 2.12 AC1 - "System instances created via template.fill()"

```python
def test_create_system_instantiates_template_via_fill(mock_adapter):
    """
    Test create_system calls template.fill() for instantiation.

    Verifies:
    - get_template_by_name called with correct template enum
    - template.fill() called with project model
    - Returns system_uri from filled template
    """
    # Arrange
    mock_template = Mock()
    mock_filled_graph = Mock()
    mock_template.fill.return_value = mock_filled_graph
    mock_adapter.get_template_by_name.return_value = mock_template

    # Mock filled graph has system URI
    mock_filled_graph.__iter__ = Mock(return_value=iter([
        ("urn:bldgmotif:vav-reheat-1", RDF.type, s223.System)
    ]))

    # Act
    result = SystemsModel(mock_adapter).create_system(
        project_id="test-project",
        template_id="http://data.ashrae.org/standard223#VAV-Reheat-System",
        label="VAV Box 101"
    )

    # Assert
    assert result["system_uri"].startswith("urn:bldgmotif:")
    mock_template.fill.assert_called_once()
```

#### 2. create_system - Metadata Addition

**Acceptance Criteria:** Story 2.12 AC1 - "Adds metadata: rdfs:label, bms:hasTemplateId, dcterms:created"

```python
def test_create_system_adds_required_metadata(mock_adapter):
    """
    Test create_system adds rdfs:label, bms:hasTemplateId, dcterms:created.

    Verifies:
    - Metadata triple added for label
    - Metadata triple added for template_id
    - Metadata triple added for creation timestamp
    - Model.graph.add() called with correct triples
    """
    # Mock template.fill() returns graph with system URI
    # Mock model.graph.add() calls
    # Assert add() called 3 times for metadata
```

#### 3. create_system - Template Not Found

```python
def test_create_system_raises_key_error_when_template_not_found(mock_adapter):
    """
    Test create_system raises KeyError when template_id not found.

    Verifies:
    - KeyError propagates from adapter.get_template_by_name()
    - Error message includes template_id
    """
```

#### 4. get_system - SPARQL Query Construction

**Acceptance Criteria:** Story 2.12 AC2 - "GET returns system with metadata"

```python
def test_get_system_constructs_sparql_query_correctly(mock_adapter):
    """
    Test get_system builds SPARQL query with system_uri.

    Verifies:
    - SPARQL query includes system_uri in WHERE clause
    - Queries for label, template_id, created metadata
    - adapter.query_model() called with correct query string
    """
    # Mock SPARQL query results
    mock_adapter.query_model.return_value = [{
        "label": "VAV Box 101",
        "template_id": "http://data.ashrae.org/standard223#VAV-Reheat-System",
        "created": "2025-01-15T10:30:00"
    }]

    # Act
    result = SystemsModel(mock_adapter).get_system(
        project_id="test-project",
        system_uri="urn:bldgmotif:vav-reheat-1"
    )

    # Assert
    assert result["label"] == "VAV Box 101"
    assert "urn:bldgmotif:vav-reheat-1" in mock_adapter.query_model.call_args[0][1]
```

#### 5. get_system - System Not Found

```python
def test_get_system_returns_none_when_system_not_found(mock_adapter):
    """
    Test get_system returns None when system_uri doesn't exist.

    Verifies:
    - Returns None when SPARQL query returns empty results
    - No exceptions raised
    """
```

#### 6. list_systems - Multiple Systems Ordering

**Acceptance Criteria:** Story 2.12 AC2 - "GET /systems returns list ordered by creation"

```python
def test_list_systems_orders_by_created_timestamp(mock_adapter):
    """
    Test list_systems returns systems ordered by dcterms:created.

    Verifies:
    - SPARQL query includes ORDER BY ?created
    - Returns list sorted chronologically
    """
    # Mock multiple systems with timestamps
    mock_adapter.query_model.return_value = [
        {"system_uri": "urn:sys1", "created": "2025-01-15T10:00:00"},
        {"system_uri": "urn:sys2", "created": "2025-01-15T09:00:00"},
    ]

    # Assert results maintain order
```

#### 7. list_systems - Empty Project

```python
def test_list_systems_returns_empty_list_for_new_project(mock_adapter):
    """
    Test list_systems returns [] when project has no systems.

    Verifies:
    - Returns empty list (not None)
    - No errors raised
    """
```

#### 8. delete_system - Triple Removal

**Acceptance Criteria:** Story 2.12 AC3 - "DELETE removes all triples"

```python
def test_delete_system_removes_all_related_triples(mock_adapter):
    """
    Test delete_system removes system and all connected triples.

    Verifies:
    - SPARQL CONSTRUCT query fetches all triples with system as subject
    - model.graph.remove() called for each triple
    - session.commit() called
    """
```

#### 9. delete_system - System Not Found

```python
def test_delete_system_returns_false_when_system_not_found(mock_adapter):
    """
    Test delete_system returns False when system_uri doesn't exist.

    Verifies:
    - Returns False (not raising exception)
    - No triples removed
    """
```

#### 10. URN Generation Consistency

```python
def test_create_system_generates_valid_buildingmotif_urns(mock_adapter):
    """
    Test create_system URNs follow BuildingMOTIF format.

    Verifies:
    - URN starts with "urn:bldgmotif:"
    - URN is unique per template.fill() call
    - No custom URN manipulation
    """
```

---

## Task 1.6: Integration Tests for systems_crud.py

**File:** `tests/integration/test_systems_crud.py`

**Implementation File:** `src/models/systems_model.py:14-232`

### Test Scenarios

#### 1. Create System → Verify in BuildingMOTIF

**Acceptance Criteria:** Story 2.12 AC1

```python
def test_create_system_persists_in_buildingmotif(shared_adapter: BuildingMOTIFAdapter):
    """
    Test created system persists in BuildingMOTIF database.

    End-to-end flow:
    1. Create system via SystemsModel.create_system()
    2. Query RDF graph directly via SPARQL
    3. Verify system URI, label, metadata exist
    """
    from src.models.systems_model import SystemsModel
    from src.adapters import SystemTemplate

    # Arrange
    model = SystemsModel(shared_adapter)

    # Act
    result = model.create_system(
        project_id="integration-test",
        template_id=str(SystemTemplate.VAV_REHEAT.value),
        label="Integration Test VAV"
    )

    # Assert - Query BuildingMOTIF directly
    query = """
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        PREFIX bms: <urn:bms:>
        PREFIX dcterms: <http://purl.org/dc/terms/>

        SELECT ?label ?template_id ?created
        WHERE {
            <{system_uri}> rdfs:label ?label .
            <{system_uri}> bms:hasTemplateId ?template_id .
            <{system_uri}> dcterms:created ?created .
        }
    """.format(system_uri=result["system_uri"])

    project_model = shared_adapter.get_or_create_model("urn:project:integration-test")
    sparql_results = shared_adapter.query_model(project_model, query)

    assert len(sparql_results) == 1
    assert sparql_results[0]["label"] == "Integration Test VAV"
    assert "VAV-Reheat-System" in sparql_results[0]["template_id"]
```

#### 2. Query Devices from System

**Acceptance Criteria:** Story 2.12 Phase 1 AC2 - "Cascading queries: System → Devices"

```python
def test_query_devices_from_created_system(shared_adapter: BuildingMOTIFAdapter):
    """
    Test querying devices from instantiated system.

    End-to-end flow:
    1. Create system (contains devices from template.fill())
    2. Query devices via DevicesModel.get_devices_for_system()
    3. Verify device URIs, labels returned
    """
    from src.models.systems_model import SystemsModel
    from src.models.devices_model import DevicesModel

    # Create system
    system_result = SystemsModel(shared_adapter).create_system(...)

    # Query devices
    devices = DevicesModel(shared_adapter).get_devices_for_system(
        project_id="integration-test",
        system_uri=system_result["system_uri"]
    )

    # Assert
    assert len(devices) > 0
    assert all("device_uri" in d for d in devices)
```

#### 3. Query Properties from Device in System

**Acceptance Criteria:** Story 2.12 Phase 1 AC2 - "Cascading queries: Device → Properties"

```python
def test_query_properties_from_device_in_system(shared_adapter: BuildingMOTIFAdapter):
    """
    Test querying properties from device within system.

    End-to-end flow:
    1. Create system
    2. Query first device
    3. Query properties via DevicesModel.get_properties_for_device()
    4. Verify property metadata (is_actuatable, class_uri, etc.)
    """
    # Create system → get devices → get properties
    # Verify property has: property_uri, label, template_id, is_actuatable
```

#### 4. Delete System → Verify Removal

**Acceptance Criteria:** Story 2.12 AC3

```python
def test_delete_system_removes_from_buildingmotif(shared_adapter: BuildingMOTIFAdapter):
    """
    Test deleted system no longer appears in queries.

    End-to-end flow:
    1. Create system
    2. Delete via SystemsModel.delete_system()
    3. Query for system → returns None
    4. Verify triples removed from graph
    """
    # Create → Delete → Verify
```

#### 5. Multiple Systems in Same Project

```python
def test_list_systems_returns_multiple_systems_ordered(shared_adapter: BuildingMOTIFAdapter):
    """
    Test creating and listing multiple systems in project.

    End-to-end flow:
    1. Create 3 systems with different templates
    2. List systems via SystemsModel.list_systems()
    3. Verify correct count and ordering by created timestamp
    """
```

#### 6. Create System with Lab VAV Reheat Template

```python
def test_create_system_with_lab_vav_reheat_template(shared_adapter: BuildingMOTIFAdapter):
    """
    Test system creation with LAB_VAV_REHEAT template.

    Verifies:
    - Different template enum works correctly
    - System contains lab-specific devices
    """
```

---

## Task 2.5: Unit Tests for bacnet_references_model.py

**File:** `tests/unit/test_models/test_bacnet_references_model.py`

**Implementation File:** `src/models/bacnet_references_model.py:15-367`

### Test Scenarios

#### 1. create_or_update_reference - BACnet → Property URN Mapping

**Acceptance Criteria:** Story 2.12 Phase 2 AC1 - "POST /bacnet-references creates reference"

```python
def test_create_reference_maps_bacnet_point_to_property_urn(mock_adapter):
    """
    Test creating BACnet reference links BACnet point to property URN.

    Verifies:
    - SPARQL INSERT adds bms:mapsTo triple
    - Adds bms:bacnetDeviceId, bms:bacnetObjectType, bms:bacnetObjectInstance
    - session.commit() called
    """
    # Mock adapter.get_or_create_model()
    # Mock model.graph.update() for SPARQL INSERT

    # Act
    BACnetReferencesModel(mock_adapter).create_or_update_reference(
        project_id="test",
        bacnet_point_id="device_123.analog-input_1",
        property_urn="urn:bldgmotif:vav-101-temp-sensor-1",
    )

    # Assert
    # Verify SPARQL INSERT includes bms:mapsTo triple
```

#### 2. create_or_update_reference - SHACL Validation

**Acceptance Criteria:** Story 2.12 Phase 2 AC1 - "Validates property exists before creating reference"

```python
def test_create_reference_validates_property_exists_via_shacl(mock_adapter):
    """
    Test create_or_update_reference validates property via SHACL before commit.

    Verifies:
    - ValidationService.validate_equipment_mapping() called
    - If validation fails → rollback and raise ValidationException
    - If validation passes → commit
    """
```

#### 3. create_or_update_reference - Validation Failure Rollback

```python
def test_create_reference_rolls_back_on_validation_failure(mock_adapter):
    """
    Test SHACL validation failure triggers rollback.

    Verifies:
    - ValidationException raised
    - model.graph changes reverted
    - Error message includes validation errors
    """
```

#### 4. get_reference - Enriched Data Query

**Acceptance Criteria:** Story 2.12 Phase 2 AC2 - "GET returns enriched reference data"

```python
def test_get_reference_returns_enriched_metadata(mock_adapter):
    """
    Test get_reference queries full System → Device → Property chain.

    Verifies:
    - SPARQL query uses s223:contains* for traversal
    - Returns: property_urn, label, system_uri, device_uri, template_id
    """
    # Mock SPARQL results with s223:contains chain
    mock_adapter.query_model.return_value = [{
        "property_urn": "urn:...",
        "property_label": "Zone Temp",
        "system_uri": "urn:...",
        "system_label": "VAV System",
        "device_uri": "urn:...",
        "device_label": "Temp Sensor",
    }]

    # Assert enriched data returned
```

#### 5. get_reference - Label Extraction from URI

```python
def test_get_reference_extracts_label_from_uri_when_missing(mock_adapter):
    """
    Test get_reference falls back to URI-based label extraction.

    Verifies:
    - When rdfs:label is None, extracts label from URN
    - Uses extract_label_from_uri() utility
    """
```

#### 6. get_all_references - Filtering by Project

```python
def test_get_all_references_filters_by_project_id(mock_adapter):
    """
    Test get_all_references returns only references for specified project.

    Verifies:
    - SPARQL query includes project model filter
    - Returns list of reference dicts
    """
```

#### 7. delete_reference - Triple Removal

**Acceptance Criteria:** Story 2.12 Phase 2 AC3 - "DELETE removes reference triples"

```python
def test_delete_reference_removes_all_bacnet_metadata(mock_adapter):
    """
    Test delete_reference removes bms:mapsTo and all BACnet metadata.

    Verifies:
    - SPARQL DELETE removes bms:mapsTo triple
    - Removes bms:bacnetDeviceId, bms:bacnetObjectType, bms:bacnetObjectInstance
    """
```

#### 8. validate_property_exists - ASK Query

```python
def test_validate_property_exists_uses_sparql_ask(mock_adapter):
    """
    Test validate_property_exists uses SPARQL ASK query.

    Verifies:
    - Returns True when property URN exists in graph
    - Returns False when property URN not found
    """
```

#### 9. Update Existing Reference

```python
def test_create_or_update_updates_existing_reference(mock_adapter):
    """
    Test create_or_update_reference updates existing BACnet point mapping.

    Verifies:
    - SPARQL DELETE removes old property_urn mapping
    - SPARQL INSERT adds new property_urn mapping
    """
```

#### 10. BACnet Point ID Format Validation

```python
def test_create_reference_accepts_valid_bacnet_point_id_format(mock_adapter):
    """
    Test create_or_update_reference accepts "device_id.object-type_instance" format.

    Verifies:
    - Parses "123.analog-input_1" correctly
    - Extracts device_id=123, object_type=analog-input, instance=1
    """
```

---

## Task 2.6: Integration Tests for bacnet_references_crud.py

**File:** `tests/integration/test_bacnet_references_crud.py`

**Implementation File:** `src/models/bacnet_references_model.py:15-367`

### Test Scenarios

#### 1. Create Reference → Verify in Graph

**Acceptance Criteria:** Story 2.12 Phase 2 AC1

```python
def test_create_bacnet_reference_persists_in_buildingmotif(shared_adapter: BuildingMOTIFAdapter):
    """
    Test BACnet reference persists in RDF graph.

    End-to-end flow:
    1. Create system (get property URN from it)
    2. Create BACnet reference via BACnetReferencesModel.create_or_update_reference()
    3. Query graph for bms:mapsTo triple
    4. Verify BACnet metadata exists
    """
    from src.models.systems_model import SystemsModel
    from src.models.bacnet_references_model import BACnetReferencesModel

    # Create system first
    system = SystemsModel(shared_adapter).create_system(...)

    # Get property URN from system (via devices query)
    # Create BACnet reference
    BACnetReferencesModel(shared_adapter).create_or_update_reference(
        project_id="integration-test",
        bacnet_point_id="device_42.analog-input_1",
        property_urn="urn:...",
    )

    # Query BuildingMOTIF directly
    query = """
        PREFIX bms: <urn:bms:>
        SELECT ?property_urn
        WHERE {
            ?bacnet_ref bms:mapsTo ?property_urn .
            ?bacnet_ref bms:bacnetDeviceId "42" .
        }
    """

    # Assert reference exists
```

#### 2. Get Reference with Full Metadata Chain

**Acceptance Criteria:** Story 2.12 Phase 2 AC2

```python
def test_get_bacnet_reference_returns_full_semantic_chain(shared_adapter: BuildingMOTIFAdapter):
    """
    Test get_reference returns System → Device → Property chain.

    End-to-end flow:
    1. Create system (contains devices and properties)
    2. Create BACnet reference for property
    3. Get reference via BACnetReferencesModel.get_reference()
    4. Verify returned data includes:
       - property_urn, property_label
       - device_uri, device_label
       - system_uri, system_label
       - template_id
    """
```

#### 3. SHACL Validation Rejects Invalid Property URN

**Acceptance Criteria:** Story 2.12 Phase 2 AC1

```python
def test_create_bacnet_reference_fails_shacl_validation_for_nonexistent_property(shared_adapter: BuildingMOTIFAdapter):
    """
    Test creating reference with invalid property URN fails validation.

    End-to-end flow:
    1. Attempt to create reference with non-existent property URN
    2. SHACL validation fails
    3. ValidationException raised
    4. Rollback occurs - reference not persisted
    """
    from src.models.exceptions import ValidationException

    with pytest.raises(ValidationException):
        BACnetReferencesModel(shared_adapter).create_or_update_reference(
            project_id="integration-test",
            bacnet_point_id="device_42.analog-input_1",
            property_urn="urn:nonexistent:property",
        )
```

#### 4. Delete Reference → Verify Removal

**Acceptance Criteria:** Story 2.12 Phase 2 AC3

```python
def test_delete_bacnet_reference_removes_from_graph(shared_adapter: BuildingMOTIFAdapter):
    """
    Test deleted BACnet reference no longer appears in queries.

    End-to-end flow:
    1. Create system and BACnet reference
    2. Delete via BACnetReferencesModel.delete_reference()
    3. Query for reference → None
    4. Verify bms:mapsTo triple removed
    """
```

#### 5. List All References in Project

```python
def test_get_all_bacnet_references_returns_project_references(shared_adapter: BuildingMOTIFAdapter):
    """
    Test listing all BACnet references in project.

    End-to-end flow:
    1. Create 2 systems with multiple properties
    2. Create 3 BACnet references for different properties
    3. List all via BACnetReferencesModel.get_all_references()
    4. Verify correct count and data
    """
```

#### 6. Update Existing Reference

```python
def test_update_bacnet_reference_changes_property_mapping(shared_adapter: BuildingMOTIFAdapter):
    """
    Test updating BACnet reference changes property URN mapping.

    End-to-end flow:
    1. Create reference pointing to property A
    2. Update reference to point to property B
    3. Query reference → returns property B
    4. Verify old property A mapping removed
    """
```

---

## Acceptance Criteria Traceability

### Story 2.12 Phase 1 (Systems CRUD)

| AC                                       | Test Coverage                               |
| ---------------------------------------- | ------------------------------------------- |
| AC1: System creation via template.fill() | Unit: Task 1.5 #1, Integration: Task 1.6 #1 |
| AC1: Metadata addition                   | Unit: Task 1.5 #2                           |
| AC2: GET system returns metadata         | Unit: Task 1.5 #4                           |
| AC2: List systems ordered by created     | Unit: Task 1.5 #6, Integration: Task 1.6 #5 |
| AC2: Cascading queries                   | Integration: Task 1.6 #2, #3                |
| AC3: DELETE removes all triples          | Unit: Task 1.5 #8, Integration: Task 1.6 #4 |

### Story 2.12 Phase 2 (BACnet References)

| AC                                  | Test Coverage                                   |
| ----------------------------------- | ----------------------------------------------- |
| AC1: POST creates reference         | Unit: Task 2.5 #1, Integration: Task 2.6 #1     |
| AC1: SHACL validation before commit | Unit: Task 2.5 #2, #3, Integration: Task 2.6 #3 |
| AC2: GET returns enriched data      | Unit: Task 2.5 #4, Integration: Task 2.6 #2     |
| AC3: DELETE removes reference       | Unit: Task 2.5 #7, Integration: Task 2.6 #4     |

---

## Running Tests

```bash
# Run all tests
pnpm bms-semantics:test

# Run unit tests only
PYTHONPATH=.:packages:apps/building-semantics-api-app python -m pytest apps/building-semantics-api-app/tests/unit/ -v

# Run integration tests only
PYTHONPATH=.:packages:apps/building-semantics-api-app python -m pytest apps/building-semantics-api-app/tests/integration/ -v

# Run specific test file
PYTHONPATH=.:packages:apps/building-semantics-api-app python -m pytest apps/building-semantics-api-app/tests/unit/test_models/test_systems_model.py -v
```

---

## Implementation Order (Recommended)

1. **Task 1.5 first** - Unit tests for systems_model.py (easier, mocked)
2. **Task 1.6 second** - Integration tests for systems CRUD (verify unit tests)
3. **Task 2.5 third** - Unit tests for bacnet_references_model.py
4. **Task 2.6 fourth** - Integration tests for BACnet references (full stack)
5. **Final verification** - Run full test suite, ensure all passing

---

## Key Testing Principles (from CLAUDE.md)

✅ **DO:**

- Write tests first, then verify implementation passes
- Mock external libraries (BuildingMOTIF SDK, Model, Library)
- DO NOT MOCK SYSTEM UNDER TEST (systems_model.py, bacnet_references_model.py)
- Test behavior, not logger functions
- Use Arrange-Act-Assert pattern
- Test edge cases and error handling

❌ **DON'T:**

- Don't add unnecessary comments (clear method names)
- Don't overengineer test setup
- Don't skip integration tests (verify persistence)
- Don't use `any` or `unknown` types

---

## Ready for Handoff to Dev Agent

This document provides:

- ✅ Complete test scenarios for all 4 tasks
- ✅ File structure and naming conventions
- ✅ Code examples following existing patterns
- ✅ Acceptance criteria traceability
- ✅ Implementation order recommendation
- ✅ TDD principles from CLAUDE.md

**Next Step:** Hand off to Dev agent with instruction to implement tests following TDD workflow.
