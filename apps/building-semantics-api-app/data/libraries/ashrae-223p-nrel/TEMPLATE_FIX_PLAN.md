# 223P Template Fix Plan

**Created**: 2025-11-20
**Updated**: 2025-11-21
**Goal**: Fix NREL 223P templates to generate fully SHACL-compliant models
**Status**: In Progress - ConnectionPoint Fixes

---

## 🎯 Current Validation Status (2025-11-21)

### ✅ Passing System Templates (2/8)

1. **vav-reheat** - PASSING (0 errors) ✅

   - Fixed: Added `equipment: "name"` to system-level connection points (systems.yml lines 128-131)

2. **lab-vav-reheat** - PASSING (0 errors) ✅
   - Fixed typo: `s223:maspTo` → `s223:mapsTo` (systems.yml line 226)
   - Fixed: Added `equipment: "name"` to system-level connection points (systems.yml lines 236-238)

### ❌ Failing System Templates

- **makeup-air-unit** - FAILING (8 errors) - DEFERRED
  - 4 ConnectionPoint errors (missing `isConnectionPointOf`)
  - 3 Connection errors (duct connectivity issues)
  - 1 Contains error (equipment containment)
  - **Status**: Complex template, investigating after other templates pass

### 🔄 Not Yet Tested (6/8)

- chilled-water-system
- hot-water-system
- exhaust-air-unit
- heat-recovery-system
- process-chilled-water-system

### 📝 Base Template Fixes Applied

#### connections.yml

- Added `equipment` parameter to all 4 connection point templates (air/water inlet/outlet)
- Added `equipment: "name"` to all 21 junction connection points (lines 94-135)

#### devices.yml

- **heat-exchanger**: Added `equipment: "name"` to 4 water connection points (lines 434, 436, 438, 440)
- **exhaust-fan**: Added `equipment: "name"` to air connection points (lines 610, 612)
- **chilled-water-coil**: Changed `s223:cnx` → `s223:hasConnectionPoint` (line 123)

#### Infrastructure

- **Ontology Loading**: Split QUDT into separate unit + quantitykind libraries (buildingmotif_adapter.py)
- **Settings**: Added paths for 223p, unit, quantitykind ontologies (settings.py)

---

## Error Analysis (From Validation Report)

### Total Errors: ~250 violations

#### Error Breakdown by Type

| Error Type                                             | Count | Severity | Fix Priority |
| ------------------------------------------------------ | ----- | -------- | ------------ |
| Missing QuantityKind (`qudt:hasQuantityKind`)          | ~110  | High     | 1            |
| Duplicate/Missing Units (`qudt:hasUnit`)               | ~40   | Medium   | 2            |
| Missing EnumerationKind (`s223:hasEnumerationKind`)    | ~8    | High     | 1            |
| Orphaned ConnectionPoints (`s223:isConnectionPointOf`) | ~3    | Medium   | 3            |
| Invalid `s223:contains` relationship                   | ~1    | Low      | 4            |

### Sample Error Messages

```
'Value must be an instance of ns2:QuantityKind'
's223: A `QuantifiableProperty` shall be associated with a `QuantityKind` using the relation `hasQuantityKind`.'
's223: A `QuantifiableProperty` can be associated with at most one `Unit` using the relation `hasUnit`.'
's223: An `EnumerableProperty` shall be associated with exactly one `EnumerationKind` using the relation `hasEnumerationKind`.'
's223: A `ConnectionPoint` shall be associated with exactly one `Connectable` using the relation `isConnectionPointOf`.'
```

---

## Template Audit Results

### properties.yml ✅ **COMPLETE!**

**Total Templates**: 25
**Have QuantityKind** (for Quantifiable): 19/19 ✅
**Have EnumerationKind** (for Enumerable): 6/6 ✅

**Audit Result**: ✅ **ALL property templates have required metadata!**

- All QuantifiableProperty templates have `qudt:hasQuantityKind`
- All EnumerableProperty templates have `s223:hasEnumerationKind`
- `start-command` and `run-status` are Enumerable (not Quantifiable) - correctly have EnumerationKind ✅

### devices.yml ✅ Good

- Uses property templates via dependencies (not inline)
- 24 property references
- No inline property definitions found ✅

### systems.yml - To Investigate

- [ ] Check for inline property definitions
- [ ] Verify all properties come from templates
- [ ] Check dependency resolution

### connections.yml - To Investigate

- [ ] Check ConnectionPoint back-references
- [ ] Verify `s223:isConnectionPointOf` relationships

### spaces.yml - To Investigate

- [ ] Check for any inline properties
- [ ] Verify template usage

---

## Root Cause Hypothesis

The errors are likely NOT from template definitions themselves (properties.yml is mostly complete).

**Possible Causes**:

1. **Template dependencies not being inlined** - When `template.fill()` is called, nested dependencies may not include metadata
2. **Duplicate property creation** - Same property created multiple times with conflicting Units
3. **Missing dependency declarations** - Device/system templates not declaring property dependencies

---

## Fix Plan

### Phase 1: Fix Template Definitions ✅ **COMPLETE!**

#### 1.1 Audit Property Templates

- [x] Audit all 25 property templates ✅
- [x] Verify QuantifiableProperty templates have QuantityKind ✅ 19/19
- [x] Verify EnumerableProperty templates have EnumerationKind ✅ 6/6
- **Result**: NO fixes needed - all templates are complete!

### Phase 2: Verify Template Dependencies ⬜ NOT STARTED

#### 2.1 Audit System Templates

- [ ] Check `vav-reheat` system template
- [ ] Check `hot-water-system` template
- [ ] Verify all reference property templates with `dependencies:` section
- [ ] Look for inline property definitions (should be none)

#### 2.2 Audit Device Templates

- [ ] Check damper template
- [ ] Check fan template
- [ ] Check pump template
- [ ] Verify property references use templates

### Phase 3: Test Template Fill Process ⬜ NOT STARTED

#### 3.1 Create Test Script

```python
# Test that template.inline_dependencies().fill() includes all metadata
template = adapter.get_template_with_dependencies(SystemTemplate.VAV_REHEAT)
bindings, graph = template.fill(BMS)

# Query graph for properties
properties = graph.query("""
    SELECT ?prop ?qk ?unit WHERE {
        ?prop a s223:QuantifiableProperty .
        OPTIONAL { ?prop qudt:hasQuantityKind ?qk }
        OPTIONAL { ?prop qudt:hasUnit ?unit }
    }
""")

# Assert all have QuantityKind
for row in properties:
    assert row.qk is not None, f"Property {row.prop} missing QuantityKind"
```

#### 3.2 Fix Dependency Resolution

- [ ] If test fails, investigate BuildingMOTIF dependency inlining
- [ ] Check if `inline_dependencies()` includes property template bodies
- [ ] May need to manually inline property templates

### Phase 4: Fix ConnectionPoint Issues ⬜ NOT STARTED

#### 4.1 Audit connections.yml

- [ ] Review all ConnectionPoint templates
- [ ] Ensure each has `s223:isConnectionPointOf` back-reference
- [ ] Check if this should be in template or added during fill

#### 4.2 Fix Orphaned ConnectionPoints

- [ ] Add missing back-references
- [ ] Test with system instantiation

### Phase 5: Fix Duplicate Unit Issues ⬜ NOT STARTED

#### 5.1 Identify Duplicates

- [ ] Parse SHACL report for "at most one Unit" errors
- [ ] Find which properties have multiple Units
- [ ] Check if from template or runtime duplication

#### 5.2 Fix Duplicates

- [ ] Remove duplicate Unit declarations
- [ ] Ensure each property template has exactly 0 or 1 Unit

---

## Testing Strategy

### Test 1: Individual Property Templates ⬜

Create test that instantiates each property template individually:

```python
for property_name in ["air-temperature", "damper-command", ...]:
    template = library.get_template_by_name(property_name)
    _, graph = template.fill(BMS)

    # Validate property has required metadata
    assert_has_quantity_kind(graph)
    assert_has_unit_if_quantifiable(graph)
```

### Test 2: System Template Full Stack ⬜

Create VAV system and validate full model:

```python
system_uri = systems_model.create_system("test-project", "vav-reheat", "TestVAV")
model = adapter.get_or_create_model("urn:project:test-project")

# Should pass 223P SHACL validation
result = ValidationService.validate_model(model)
assert result.isValid, f"Validation failed: {result.errors}"
```

### Test 3: Property Metadata Completeness ⬜

Query all properties in generated model:

```python
properties = model.graph.query("""
    SELECT ?prop ?type ?qk ?unit ?ek WHERE {
        ?prop a ?type .
        FILTER(STRSTARTS(STR(?type), "http://data.ashrae.org/standard223#"))
        OPTIONAL { ?prop qudt:hasQuantityKind ?qk }
        OPTIONAL { ?prop qudt:hasUnit ?unit }
        OPTIONAL { ?prop s223:hasEnumerationKind ?ek }
    }
""")

# Check metadata requirements based on type
for row in properties:
    if "Quantifiable" in str(row.type):
        assert row.qk, f"{row.prop} missing QuantityKind"
    if "Enumerable" in str(row.type):
        assert row.ek, f"{row.prop} missing EnumerationKind"
```

---

## Progress Tracking

### Milestone 1: Template Definitions Fixed

- [ ] properties.yml: 2 missing QuantityKind fixed
- [ ] All templates validated individually
- **Target**: All templates produce valid properties in isolation

### Milestone 2: Dependency Resolution Verified

- [ ] Template dependencies audit complete
- [ ] inline_dependencies() tested and working
- **Target**: Full system instantiation includes all property metadata

### Milestone 3: Full Validation Passing

- [ ] Zero QuantityKind errors
- [ ] Zero EnumerationKind errors
- [ ] Zero ConnectionPoint errors
- **Target**: 223P SHACL validation passes

### Milestone 4: G36 Validation Ready

- [ ] Can write G36 223P shapes
- [ ] Templates produce predictable, queryable structures
- **Target**: Ready for G36 sequence validation

---

## Notes & Decisions

### 2025-11-20

- **Phase 1 Complete**: All 25 property templates validated ✅
- 0 templates missing required metadata
- Initial assumption was wrong - templates are NOT the problem
- **Confirmed**: Root cause is dependency resolution or runtime instantiation
- **Next**: Test `inline_dependencies()` behavior with actual system creation

### Questions to Resolve

- [ ] Does BuildingMOTIF's `inline_dependencies()` include property template bodies?
- [ ] Are ConnectionPoint back-references template or runtime responsibility?
- [ ] Why are duplicate Units appearing if templates only define one each?

---

## Quick Reference

### Required Metadata by Property Type

| Property Type                  | Required                  | Optional                        |
| ------------------------------ | ------------------------- | ------------------------------- |
| QuantifiableObservableProperty | `qudt:hasQuantityKind`    | `qudt:hasUnit`, `s223:ofMedium` |
| QuantifiableActuatableProperty | `qudt:hasQuantityKind`    | `qudt:hasUnit`, `s223:ofMedium` |
| EnumerableProperty             | `s223:hasEnumerationKind` | `s223:ofMedium`                 |

### Common QuantityKind Values

- `quantitykind:Temperature`
- `quantitykind:Pressure`
- `quantitykind:VolumeFlowRate`
- `quantitykind:DimensionlessRatio` (for %)
- `quantitykind:Angle` (for damper position in degrees)

### Common EnumerationKind Values

- `s223:EnumerationKind-OnOff`
- `s223:EnumerationKind-Occupancy`
- `s223:EnumerationKind-Binary`
