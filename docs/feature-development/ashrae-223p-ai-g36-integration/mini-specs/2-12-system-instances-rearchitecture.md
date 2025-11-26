# Mini-Spec 2.12: System Instances & BACnet References Re-Architecture

**Status**: Draft
**Epic**: 2 - ASHRAE 223P Semantic Mapping
**Story**: TBD
**Author**: Claude + Amol
**Date**: 2025-01-19

## Overview

Re-architect template loading, system instance creation, and BACnet point mapping to support:

- ✅ Proper ASHRAE 223P terminology (System, not Equipment)
- ✅ Reusable system instances across multiple BACnet points
- ✅ Prefilled devices/properties from templates via `template.fill()`
- ✅ Clean separation between templates and instances
- ✅ Single source of truth: BuildingMOTIF RDF graph (no SQL tables)
- ✅ No migration (fresh start)

---

## 1. Current Problems

### 1.1 Wrong Terminology

- Frontend calls it "Equipment" → Should be "System" (matches ASHRAE 223P SystemTemplate)

### 1.2 Hardcoded 3-Level Hierarchy

```python
# mapping_mapper.py:194-199 - WRONG!
triples.extend([
    (equipment_uri, S223.contains, device_uri),     # Hardcoded!
    (device_uri, S223.hasProperty, property_uri),
])
```

**Problem**: Breaks when HeatExchanger (Equipment-level) used as "device":

- Creates: `Equipment → Equipment` (invalid!)
- Should support: `Equipment → Equipment → Device` (nested)

### 1.3 Three Separate Template Fills

```python
# WRONG - ignores template dependencies!
equipment_graph = equipment_template.fill(BMS)
device_graph = device_template.fill(BMS)
property_graph = property_template.fill(BMS)
```

**Problem**: Redundant fills when template already has dependencies inlined

### 1.4 No Instance Reuse

- User selects templates for EVERY BACnet point
- Same system (e.g., "VAV-Floor3-Zone5") recreated multiple times
- No way to prefill devices/properties

---

## 2. UX Flow (New)

### Goal

For each BACnet point, map to a Property through 3-step cascading selection.

### Step 1: Select/Create System Instance

**Option A: Select Existing System**

- Dropdown/search shows existing system instances for this project
- Display format: `"{label}" ({templateId})`
  - Example: `"VAV-Floor3-Zone5 (VAV Reheat Terminal Unit)"`
- Selecting loads prefilled devices/properties for that system

**Option B: Create New System**

- Button: **"Create New System"**
- Opens modal with:
  - **Template Dropdown**: Shows available System templates
    - Example: "VAV Reheat Terminal Unit", "Makeup Air Unit"
  - **Label Input**: Custom name for this system instance
    - Example: "VAV-Floor3-Zone5"
  - **Preview**: Shows devices/properties that will be created (from template)
- On save:
  - Backend calls `template.fill()` to instantiate complete system
  - Saves to BuildingMOTIF RDF graph for this project
  - Returns `systemId` (URN format)
  - System now available for reuse across multiple BACnet points

### Step 2: Select Device (from chosen System)

- Dropdown shows devices prefilled from template when system was created
- Display format: `"{label}" ({templateId})`
  - Example: `"Damper (damper)"`, `"Reheat Coil (heating-coil)"`
- Disabled until systemId selected

### Step 3: Select Property (from chosen Device)

- Dropdown shows properties prefilled from template when system was created
- **Filtered by BACnet object type** (analog-input, analog-output, etc.)
- Display format: `"{label}" ({templateId})`
  - Example: `"Damper Position (damper-position)"`, `"Heating Command (heating-command)"`
- Disabled until deviceId selected

### Result

```
BACnet Point: device,123:analog-input,1
    ├─ Property: Damper Position (urn:buildingmotif:prop-xxx111)
    ├─ Device: Damper (urn:buildingmotif:device-aaa111)
    └─ System: VAV-Floor3-Zone5 (urn:buildingmotif:abc123-def456-ghi789)
```

**Saved as RDF Triple**:

```turtle
urn:buildingmotif:prop-xxx111 s223:hasExternalReference urn:bms:bacnet-ref-input-1
```

---

## 3. API Specification

**Base Path**: `/api/v1/223p`

### 3.1 Templates (Existing - Browse Only)

```
GET /223p/templates
```

**Description**: List available System templates to create instances from
**Response**:

```json
{
  "systems": [
    {
      "id": "vav-reheat",
      "label": "VAV Reheat Terminal Unit",
      "classUri": "http://data.ashrae.org/standard223#TerminalUnit",
      "description": "Variable air volume terminal unit with reheat coil",
      "devices": [
        {
          "id": "damper",
          "label": "Damper",
          "properties": [
            {
              "id": "damper-position",
              "label": "Damper Position",
              "isActuatable": true
            }
          ]
        }
      ]
    }
  ]
}
```

### 3.2 System Instance Management

#### Create System Instance

```
POST /projects/{projectId}/systems
```

**Request**:

```json
{
  "templateId": "vav-reheat",
  "label": "VAV-Floor3-Zone5"
}
```

**Response**:

```json
{
  "systemId": "urn:buildingmotif:abc123-def456-ghi789",
  "projectId": "uuid",
  "templateId": "vav-reheat",
  "label": "VAV-Floor3-Zone5",
  "created": "2025-01-19T12:00:00Z",
  "devices": [
    {
      "deviceId": "urn:buildingmotif:device-aaa111",
      "templateId": "damper",
      "label": "Damper",
      "properties": [
        {
          "propertyId": "urn:buildingmotif:prop-xxx111",
          "templateId": "damper-position",
          "label": "Damper Position",
          "isActuatable": true
        }
      ]
    }
  ]
}
```

**Process**:

1. Load System template with dependencies
2. Call `template.fill(BMS)` → generates complete RDF graph with auto-generated URNs
3. Add user's custom label as `rdfs:label` property to the system entity
4. Add metadata: `bms:hasTemplateId`, `dcterms:created`
5. Save to BuildingMOTIF project model (`urn:project:{projectId}`)
6. Query graph to build structured DTO with devices/properties
7. Return structured DTO

#### List Systems

```
GET /projects/{projectId}/systems
```

**Response**:

```json
{
  "systems": [
    {
      "systemId": "urn:buildingmotif:abc123-def456-ghi789",
      "templateId": "vav-reheat",
      "label": "VAV-Floor3-Zone5",
      "deviceCount": 3,
      "created": "2025-01-19T12:00:00Z"
    }
  ]
}
```

#### Get System Details

```
GET /projects/{projectId}/systems/{systemId}
```

**Response**: Same as POST response (full system with devices/properties)

#### Delete System

```
DELETE /projects/{projectId}/systems/{systemId}
```

**Response**: `204 No Content`
**Error**: `409 Conflict` if BACnet references exist for this system

### 3.3 System Structure Queries (For UI Cascading Dropdowns)

#### Get Devices

```
GET /projects/{projectId}/systems/{systemId}/devices
```

**Description**: Get devices for a system (Step 2 dropdown data)

**Response**:

```json
{
  "devices": [
    {
      "deviceId": "urn:buildingmotif:device-aaa111",
      "templateId": "damper",
      "label": "Damper"
    },
    {
      "deviceId": "urn:buildingmotif:device-bbb222",
      "templateId": "heating-coil",
      "label": "Reheat Coil"
    }
  ]
}
```

#### Get Properties (with BACnet Filtering)

```
GET /projects/{projectId}/systems/{systemId}/devices/{deviceId}/properties?bacnetObjectType=analog-input
```

**Description**: Get properties for a device (Step 3 dropdown data), filtered by BACnet object type

**Query Parameters**:

- `bacnetObjectType` (optional): Filter by BACnet object type
  - `analog-input`, `binary-input` → Observable properties only (`isActuatable: false`)
  - `analog-output`, `binary-output` → Actuatable properties only (`isActuatable: true`)
  - `analog-value`, `binary-value` → Both (no filter)
  - Omitted → No filter (all properties)

**Response**:

```json
{
  "properties": [
    {
      "propertyId": "urn:buildingmotif:prop-xxx111",
      "templateId": "damper-position",
      "label": "Damper Position",
      "isActuatable": true
    },
    {
      "propertyId": "urn:buildingmotif:prop-xxx222",
      "templateId": "damper-feedback",
      "label": "Damper Feedback",
      "isActuatable": false
    }
  ]
}
```

**Filtering Logic**:

```python
def filter_properties_by_bacnet_type(properties, bacnet_object_type):
    if bacnet_object_type in ['analog-input', 'binary-input']:
        # Input points → Observable properties only
        return [p for p in properties if not p.is_actuatable]

    elif bacnet_object_type in ['analog-output', 'binary-output']:
        # Output points → Actuatable properties only
        return [p for p in properties if p.is_actuatable]

    elif bacnet_object_type in ['analog-value', 'binary-value']:
        # Value points → Both observable and actuatable
        return properties

    else:
        # Unknown or omitted → No filter
        return properties
```

### 3.4 BACnet References (Replaces Mappings)

#### Create/Update BACnet Reference

```
PUT /projects/{projectId}/bacnet-references/{bacnetPointId}
```

**Request**:

```json
{
  "systemId": "urn:buildingmotif:abc123-def456-ghi789",
  "deviceId": "urn:buildingmotif:device-aaa111",
  "propertyId": "urn:buildingmotif:prop-xxx111"
}
```

**Response**:

```json
{
  "bacnetPointId": "device,123:analog-input,1",
  "property": {
    "id": "urn:buildingmotif:prop-xxx111",
    "templateId": "damper-position",
    "label": "Damper Position",
    "isActuatable": true
  },
  "device": {
    "id": "urn:buildingmotif:device-aaa111",
    "templateId": "damper",
    "label": "Damper"
  },
  "system": {
    "id": "urn:buildingmotif:abc123-def456-ghi789",
    "templateId": "vav-reheat",
    "label": "VAV-Floor3-Zone5"
  }
}
```

**Process**:

1. Load BuildingMOTIF project model
2. Validate `propertyId` exists in system graph
3. Create BACnet external reference URN
4. Add RDF triple: `property s223:hasExternalReference bacnetRef`
5. Add BACnet metadata triples
6. Query graph for enriched response

#### Get BACnet Reference

```
GET /projects/{projectId}/bacnet-references/{bacnetPointId}
```

**Response**: Same as PUT response

**SPARQL Query**:

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX dcterms: <http://purl.org/dc/terms/>

SELECT ?property ?device ?system WHERE {
  ?bacnetRef dcterms:identifier "device,123:analog-input,1" .
  ?property s223:hasExternalReference ?bacnetRef .
  ?device s223:hasProperty ?property .
  ?system s223:contains ?device .
}
```

#### Delete BACnet Reference

```
DELETE /projects/{projectId}/bacnet-references/{bacnetPointId}
```

**Response**: `204 No Content`

**Process**:

1. Find property with this BACnet reference (SPARQL)
2. Remove `s223:hasExternalReference` triple
3. Remove BACnet metadata triples

---

## 4. Data Model (RDF-Only)

### 4.1 Single Source of Truth

**All data stored in BuildingMOTIF project model**: `urn:project:{projectId}`

**No SQL tables!** Pure RDF graph storage.

### 4.2 System Instance RDF Example

**Note**: All URNs below are auto-generated by BuildingMOTIF's `template.fill()`. Frontend treats these as opaque identifiers and uses `rdfs:label` for display.

```turtle
# System (auto-generated URN by BuildingMOTIF)
urn:buildingmotif:abc123-def456-ghi789 rdf:type s223:TerminalUnit .
urn:buildingmotif:abc123-def456-ghi789 rdfs:label "VAV-Floor3-Zone5" .
urn:buildingmotif:abc123-def456-ghi789 bms:hasTemplateId "vav-reheat" .
urn:buildingmotif:abc123-def456-ghi789 dcterms:created "2025-01-19T12:00:00Z" .
urn:buildingmotif:abc123-def456-ghi789 s223:contains urn:buildingmotif:device-aaa111 .
urn:buildingmotif:abc123-def456-ghi789 s223:contains urn:buildingmotif:device-bbb222 .

# Device 1: Damper (auto-generated URN)
urn:buildingmotif:device-aaa111 rdf:type s223:Damper .
urn:buildingmotif:device-aaa111 rdfs:label "Damper" .
urn:buildingmotif:device-aaa111 bms:hasTemplateId "damper" .
urn:buildingmotif:device-aaa111 s223:hasProperty urn:buildingmotif:prop-xxx111 .
urn:buildingmotif:device-aaa111 s223:hasProperty urn:buildingmotif:prop-xxx222 .

# Property 1: Damper Position (Actuatable, auto-generated URN)
urn:buildingmotif:prop-xxx111 rdf:type s223:DamperPosition .
urn:buildingmotif:prop-xxx111 rdfs:label "Damper Position" .
urn:buildingmotif:prop-xxx111 bms:hasTemplateId "damper-position" .
urn:buildingmotif:prop-xxx111 s223:hasExternalReference urn:bms:bacnet-ref-output-1 .

# Property 2: Damper Feedback (Observable, auto-generated URN)
urn:buildingmotif:prop-xxx222 rdf:type s223:DamperFeedback .
urn:buildingmotif:prop-xxx222 rdfs:label "Damper Feedback" .
urn:buildingmotif:prop-xxx222 bms:hasTemplateId "damper-feedback" .
urn:buildingmotif:prop-xxx222 s223:hasExternalReference urn:bms:bacnet-ref-input-1 .

# BACnet External Reference 1 (Output)
urn:bms:bacnet-ref-output-1 rdf:type s223:BACnetExternalReference .
urn:bms:bacnet-ref-output-1 bacnet:device-identifier "device,123" .
urn:bms:bacnet-ref-output-1 bacnet:object-identifier "analog-output,1" .
urn:bms:bacnet-ref-output-1 dcterms:identifier "device,123:analog-output,1" .

# BACnet External Reference 2 (Input)
urn:bms:bacnet-ref-input-1 rdf:type s223:BACnetExternalReference .
urn:bms:bacnet-ref-input-1 bacnet:device-identifier "device,123" .
urn:bms:bacnet-ref-input-1 bacnet:object-identifier "analog-input,1" .
urn:bms:bacnet-ref-input-1 dcterms:identifier "device,123:analog-input,1" .

# Device 2: Reheat Coil (auto-generated URN)
urn:buildingmotif:device-bbb222 rdf:type s223:HeatingCoil .
urn:buildingmotif:device-bbb222 rdfs:label "Reheat Coil" .
urn:buildingmotif:device-bbb222 bms:hasTemplateId "heating-coil" .
urn:buildingmotif:device-bbb222 s223:hasProperty urn:buildingmotif:prop-yyy111 .
```

### 4.3 Querying Examples

#### Find All Systems in Project

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>

SELECT ?system ?label ?templateId WHERE {
  ?system a s223:Equipment .
  ?system rdfs:label ?label .
  ?system bms:hasTemplateId ?templateId .
}
```

#### Find Devices for System

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>

SELECT ?device ?label WHERE {
  <urn:buildingmotif:abc123-def456-ghi789> s223:contains ?device .
  ?device rdfs:label ?label .
}
```

#### Find Properties for Device (Filtered)

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>

SELECT ?property ?label ?templateId WHERE {
  <urn:buildingmotif:device-aaa111> s223:hasProperty ?property .
  ?property rdfs:label ?label .
  ?property bms:hasTemplateId ?templateId .

  # Filter: Observable properties only (for analog-input)
  FILTER NOT EXISTS {
    ?property a s223:ActuatableProperty .
  }
}
```

#### Find Property by BACnet Point

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX dcterms: <http://purl.org/dc/terms/>

SELECT ?property ?device ?system WHERE {
  ?bacnetRef dcterms:identifier "device,123:analog-input,1" .
  ?property s223:hasExternalReference ?bacnetRef .
  ?device s223:hasProperty ?property .
  ?system s223:contains ?device .
}
```

---

## 5. Template Instantiation Strategy

### 5.1 Current (Wrong) ❌

```python
# mapping_mapper.py:158-199
def to_equipment_rdf_triples(...):
    # THREE separate fills - redundant!
    equipment_bindings, equipment_graph = equipment_template.fill(BMS)
    device_bindings, device_graph = device_template.fill(BMS)
    property_bindings, property_graph = property_template.fill(BMS)

    # Manual linking - hardcoded hierarchy!
    triples.extend([
        (equipment_uri, S223.contains, device_uri),  # Wrong for nested Equipment
        (device_uri, S223.hasProperty, property_uri),
        (property_uri, S223.hasExternalReference, bacnet_ref_uri),
    ])
```

**Problems**:

1. Three separate fills ignore template dependencies
2. Hardcoded 3-level hierarchy (Equipment → Device → Property)
3. Breaks when HeatExchanger (Equipment) used as "device"
4. URIs based on BACnet point ID, not semantic classification

### 5.2 Proposed (Right) ✅

#### When Creating System Instance

```python
# SystemsModel.create_system()
def create_system(self, project_id: str, template_id: str, label: str):
    # 1. Load template WITH dependencies inlined
    template = adapter.get_template_with_dependencies(SystemTemplate(template_id))

    # 2. SINGLE fill - dependencies auto-instantiate, BuildingMOTIF generates URNs
    bindings, filled_graph = template.fill(BMS)
    system_uri = bindings["name"]  # Auto-generated URN from BuildingMOTIF

    # 3. Add user label + metadata (URNs remain unchanged!)
    filled_graph.add((system_uri, RDFS.label, Literal(label)))
    filled_graph.add((system_uri, BMS.hasTemplateId, Literal(template_id)))
    filled_graph.add((system_uri, DCTERMS.created, Literal(datetime.now().isoformat())))

    # 4. Save to BuildingMOTIF project model
    model = adapter.get_or_create_model(f"urn:project:{project_id}")
    model.graph += filled_graph

    # 5. Extract DTO from graph and return
    return build_system_dto(filled_graph, system_uri)
```

**Key Points**:

- ✅ BuildingMOTIF auto-generates all URNs (system, devices, properties)
- ✅ URNs are opaque identifiers - never parsed or constructed by our code
- ✅ User label stored as `rdfs:label` property (queryable via SPARQL)
- ✅ Frontend receives URNs as strings, sends them back unchanged (stateless REST)
- ✅ No URN substitution logic needed (~150 lines saved!)

#### When Creating BACnet Reference

```python
# BACnetReferencesModel.create_or_update_reference()
def create_or_update_reference(
    self, project_id, bacnet_point_id, system_id, device_id, property_id
):
    # 1. Load existing system instance graph
    model = adapter.get_or_create_model(f"urn:project:{project_id}")

    # 2. Validate property exists in system (SPARQL)
    property_uri = URIRef(property_id)
    validation_query = f"""
        PREFIX s223: <http://data.ashrae.org/standard223#>
        ASK {{
            <{device_id}> s223:hasProperty <{property_id}> .
            <{system_id}> s223:contains <{device_id}> .
        }}
    """
    if not model.graph.query(validation_query).askAnswer:
        raise ValueError(f"Property {property_id} not found in system {system_id}")

    # 3. Create BACnet external reference URN
    bacnet_ref_uri = create_bacnet_ref_uri(bacnet_point_id)

    # 4. Add ONLY the external reference triple (rest already exists!)
    model.graph.add((property_uri, S223.hasExternalReference, bacnet_ref_uri))

    # 5. Add BACnet reference metadata triples
    device_id_part, object_id_part = bacnet_point_id.split(":")
    model.graph.add((bacnet_ref_uri, RDF.type, S223.BACnetExternalReference))
    model.graph.add((bacnet_ref_uri, BACNET["device-identifier"], Literal(device_id_part)))
    model.graph.add((bacnet_ref_uri, BACNET["object-identifier"], Literal(object_id_part)))
    model.graph.add((bacnet_ref_uri, DCTERMS.identifier, Literal(bacnet_point_id)))

    # 6. Query graph for enriched response (SPARQL)
    return build_reference_dto(model.graph, property_uri, bacnet_ref_uri)
```

---

## 6. Frontend Changes

### 6.1 Terminology Updates

**Rename Everywhere**:

- ❌ "Equipment" → ✅ "System"
- Update: DTOs, types, component names, labels, tooltips, documentation

**Examples**:

```typescript
// Before
interface EquipmentMapping {
  equipmentTypeId: string;
  deviceTypeId: string;
  propertyId: string;
}

// After
interface BACnetReference {
  systemId: string; // URN of system instance
  deviceId: string; // URN of device
  propertyId: string; // URN of property
}
```

### 6.2 New Components

#### 1. SystemSelector Component

```typescript
interface SystemSelectorProps {
  projectId: string;
  value: string | null; // systemId URN
  onChange: (systemId: string) => void;
}

// Features:
// - Dropdown/search of existing systems
// - "Create New" button → opens SystemCreateModal
// - Display: "{label} ({templateId})"
```

#### 2. SystemCreateModal Component

```typescript
interface SystemCreateModalProps {
  projectId: string;
  onCreated: (systemId: string) => void;
}

// Features:
// - Template dropdown (from GET /223p/templates)
// - Label input field
// - Preview of devices/properties (from template metadata)
// - Calls POST /projects/{projectId}/systems
```

#### 3. DeviceSelector Component

```typescript
interface DeviceSelectorProps {
  projectId: string;
  systemId: string; // Selected system URN
  value: string | null; // deviceId URN
  onChange: (deviceId: string) => void;
}

// Features:
// - Loads from GET /projects/{projectId}/systems/{systemId}/devices
// - Disabled until systemId selected
// - Display: "{label} ({templateId})"
```

#### 4. PropertySelector Component

```typescript
interface PropertySelectorProps {
  projectId: string;
  systemId: string;
  deviceId: string; // Selected device URN
  bacnetObjectType: string; // e.g., "analog-input"
  value: string | null; // propertyId URN
  onChange: (propertyId: string) => void;
}

// Features:
// - Loads from GET /projects/{projectId}/systems/{systemId}/devices/{deviceId}/properties?bacnetObjectType={type}
// - Automatically filtered by BACnet object type
// - Disabled until deviceId selected
// - Display: "{label} ({templateId})"
```

### 6.3 Updated Flow UI

**BACnet Point Mapping Row**:

```tsx
<div className="mapping-row">
  <span>{bacnetPointId}</span>
  <Badge>{bacnetObjectType}</Badge>

  <SystemSelector
    projectId={projectId}
    value={systemId}
    onChange={setSystemId}
  />

  <DeviceSelector
    projectId={projectId}
    systemId={systemId}
    value={deviceId}
    onChange={setDeviceId}
    disabled={!systemId}
  />

  <PropertySelector
    projectId={projectId}
    systemId={systemId}
    deviceId={deviceId}
    bacnetObjectType={bacnetObjectType}
    value={propertyId}
    onChange={setPropertyId}
    disabled={!deviceId}
  />

  <Button onClick={handleSave}>Save</Button>
</div>
```

**On Save**:

```typescript
// All URN IDs are opaque strings from component state
await client.PUT("/projects/{projectId}/bacnet-references/{bacnetPointId}", {
  body: {
    systemId: "urn:buildingmotif:abc123-def456-ghi789", // From state
    deviceId: "urn:buildingmotif:device-aaa111", // From state
    propertyId: "urn:buildingmotif:prop-xxx111", // From state
  },
});
```

---

## 7. Backend Architecture

### 7.1 New Components

#### File: `src/models/systems_model.py`

```python
class SystemsModel:
    """Domain model for System instance operations."""

    def create_system(
        self, project_id: str, template_id: str, label: str
    ) -> SystemInstanceDTO

    def get_systems(self, project_id: str) -> list[SystemSummaryDTO]

    def get_system(self, project_id: str, system_id: str) -> SystemInstanceDTO

    def delete_system(self, project_id: str, system_id: str) -> None
```

#### File: `src/models/devices_model.py`

```python
class DevicesModel:
    """Domain model for device query operations (read-only)."""

    def get_devices(self, project_id: str, system_id: str) -> list[DeviceDTO]

    def get_properties(
        self,
        project_id: str,
        system_id: str,
        device_id: str,
        bacnet_object_type: str | None = None
    ) -> list[PropertyDTO]
```

#### File: `src/models/bacnet_references_model.py`

```python
class BACnetReferencesModel:
    """Domain model for BACnet reference operations."""

    def create_or_update_reference(
        self,
        project_id: str,
        bacnet_point_id: str,
        system_id: str,
        device_id: str,
        property_id: str,
    ) -> BACnetReferenceDTO

    def get_reference(
        self, project_id: str, bacnet_point_id: str
    ) -> BACnetReferenceDTO

    def delete_reference(
        self, project_id: str, bacnet_point_id: str
    ) -> None
```

#### File: `src/controllers/systems_controller.py`

```python
class SystemsController:
    """Business logic orchestration for System instances."""
    # Delegates to SystemsModel
```

#### File: `src/controllers/devices_controller.py`

```python
class DevicesController:
    """Business logic orchestration for device/property queries."""
    # Delegates to DevicesModel
```

#### File: `src/controllers/bacnet_references_controller.py`

```python
class BACnetReferencesController:
    """Business logic orchestration for BACnet references."""
    # Delegates to BACnetReferencesModel
```

#### File: `src/routers/systems.py`

```python
router = APIRouter(prefix="/api/v1/223p/projects/{projectId}/systems")

# System CRUD endpoints (uses systems_controller)
@router.post("")
async def create_system(...)

@router.get("")
async def get_systems(...)

@router.get("/{systemId}")
async def get_system(...)

@router.delete("/{systemId}")
async def delete_system(...)

# Device query endpoints (uses devices_controller)
@router.get("/{systemId}/devices")
async def get_devices(...)

@router.get("/{systemId}/devices/{deviceId}/properties")
async def get_properties(..., bacnetObjectType: str | None = None)
```

#### File: `src/routers/bacnet_references.py`

```python
router = APIRouter(prefix="/api/v1/223p/projects/{projectId}/bacnet-references")

@router.put("/{bacnetPointId}")
async def put_reference(...)

@router.get("/{bacnetPointId}")
async def get_reference(...)

@router.delete("/{bacnetPointId}")
async def delete_reference(...)
```

### 7.2 DTOs

#### File: `src/dto/systems_dto.py`

```python
class CreateSystemRequest(BaseModel):
    templateId: str
    label: str

class SystemSummaryDTO(BaseModel):
    systemId: str  # URN
    templateId: str
    label: str
    deviceCount: int
    created: str

class SystemInstanceDTO(BaseModel):
    systemId: str  # URN
    projectId: str
    templateId: str
    label: str
    created: str
    devices: list[DeviceDTO]

class DeviceDTO(BaseModel):
    deviceId: str  # URN
    templateId: str
    label: str
    properties: list[PropertyDTO]

class PropertyDTO(BaseModel):
    propertyId: str  # URN
    templateId: str
    label: str
    isActuatable: bool
```

#### File: `src/dto/bacnet_references_dto.py`

```python
class CreateBACnetReferenceRequest(BaseModel):
    systemId: str
    deviceId: str
    propertyId: str

class BACnetReferenceDTO(BaseModel):
    bacnetPointId: str
    property: PropertyInfoDTO
    device: DeviceInfoDTO
    system: SystemInfoDTO

class PropertyInfoDTO(BaseModel):
    id: str  # URN
    templateId: str
    label: str
    isActuatable: bool

class DeviceInfoDTO(BaseModel):
    id: str  # URN
    templateId: str
    label: str

class SystemInfoDTO(BaseModel):
    id: str  # URN
    templateId: str
    label: str
```

### 7.3 Deprecate Old Components (Phase 0)

**DEPRECATE** (rename with `_deprecated.py` suffix):

- ⚠️ `src/mappers/mapping_mapper.py` → `mapping_mapper_deprecated.py`
- ⚠️ `src/models/mappings_model.py` → `mappings_model_deprecated.py`
- ⚠️ `src/routers/mappings.py` → `mappings_deprecated.py`
- ⚠️ `src/dto/mappings_dto.py` → `mappings_dto_deprecated.py`
- ⚠️ `src/controllers/mappings_controller.py` → `mappings_controller_deprecated.py`

**Purpose**: Keep old implementation for reference during new development. Delete after new code is stable (Phase 5+).

---

## 8. Migration Strategy

### Fresh Start (No Migration)

**DEPRECATE & CLEAN**:

- ⚠️ Rename old mapping code with `_deprecated.py` suffix (see section 7.3)
- ⚠️ Comment out old mapping endpoints in API
- ❌ Clear BuildingMOTIF database (or delete project models)
- ❌ Remove all imports/references to deprecated code from active codebase

**START FRESH**:

- ✅ New RDF-based system instances
- ✅ New BACnet references in RDF
- ✅ Clean API design

**Users must re-create**:

- System instances (from templates)
- BACnet point mappings (using new UI)

**Justification**:

- No production data yet
- Clean architecture > backwards compatibility
- Faster development (no migration code)

---

## 9. Implementation Phases

### Phase 0: Deprecation & Clean Slate

- [ ] Rename `mappings.py` → `mappings_deprecated.py`
- [ ] Rename `mappings_model.py` → `mappings_model_deprecated.py`
- [ ] Rename `mappings_controller.py` → `mappings_controller_deprecated.py`
- [ ] Rename `mapping_mapper.py` → `mapping_mapper_deprecated.py`
- [ ] Rename `mappings_dto.py` → `mappings_dto_deprecated.py`
- [ ] Remove all imports/references to deprecated code from active codebase
- [ ] Comment out old mapping endpoints in OpenAPI spec
- [ ] Add deprecation notice at top of each deprecated file
- [ ] Clear BuildingMOTIF database (or delete project models)

**Goal**: Clean workspace for new implementation, old code available for reference.

### Phase 1: Backend Systems (RDF-only)

- [ ] Create `systems_model.py` with `template.fill()` instantiation
- [ ] Add label metadata to filled graphs (rdfs:label, bms:hasTemplateId, dcterms:created)
- [ ] Create `systems_controller.py`
- [ ] Create `devices_model.py` with SPARQL queries for devices/properties
- [ ] Create `devices_controller.py`
- [ ] Create `systems.py` router + DTOs (uses both systems_controller and devices_controller)
- [ ] Unit tests for instantiation logic
- [ ] Integration tests (create system → verify in BuildingMOTIF)

### Phase 2: Backend BACnet References (SPARQL queries)

- [ ] Create `bacnet_references_model.py` (SPARQL-based)
- [ ] Create `bacnet_references_controller.py`
- [ ] Create `bacnet_references.py` router + DTOs
- [ ] Implement BACnet object type filtering
- [ ] Unit tests for SPARQL queries
- [ ] Integration tests (create reference → verify in graph)

### Phase 3: Frontend Components

- [ ] Rename Equipment → System (global find/replace)
- [ ] Create `SystemSelector` component
- [ ] Create `SystemCreateModal` component
- [ ] Create `DeviceSelector` component (cascading)
- [ ] Create `PropertySelector` component (cascading + filtering)
- [ ] Update mapping flow UI
- [ ] Generate API clients from OpenAPI spec

### Phase 4: Testing & Cleanup

- [ ] E2E tests (create system → map point → query)
- [ ] SHACL validation on system creation (optional)
- [ ] Error handling and user feedback
- [ ] Performance optimization (SPARQL query caching)
- [ ] Update documentation
- [ ] **Delete all `*_deprecated.py` files** (after new implementation is stable and tested)

---

## 10. Success Criteria

✅ User can create reusable system instances from templates
✅ System instances prefill devices/properties automatically
✅ Cascading dropdowns: System → Device → Property
✅ Properties filtered by BACnet object type (input/output/value)
✅ BACnet point maps to specific property URN
✅ Correct ASHRAE 223P terminology (System, not Equipment)
✅ Single `template.fill()` per system (not per mapping)
✅ All data in RDF graph (no SQL tables)
✅ No hardcoded hierarchy assumptions
✅ Supports nested equipment (Equipment → Equipment → Device)
✅ Clean API design (project-scoped, RESTful)
✅ Old mapping code deleted (no technical debt)

---

## 11. Open Questions

### 11.1 URN Strategy (RESOLVED)

**Decision**: Use BuildingMOTIF auto-generated URNs + `rdfs:label` properties

**Rationale**:

1. ✅ **Standard RDF practice**: URIs are opaque identifiers, labels are properties
2. ✅ **No collision risk**: BuildingMOTIF ensures uniqueness
3. ✅ **Simpler implementation**: No custom URN generation or substitution logic (~150 lines saved)
4. ✅ **Stateless REST**: Frontend treats URNs as opaque strings, queries use labels
5. ✅ **SPARQL-based queries**: All queries filter by `rdfs:label`, not URN patterns

**Example URNs** (auto-generated by BuildingMOTIF):

- System: `urn:buildingmotif:abc123-def456-ghi789`
- Device: `urn:buildingmotif:device-aaa111`
- Property: `urn:buildingmotif:prop-xxx111`

**Labels stored as RDF properties**:

```turtle
urn:buildingmotif:abc123-def456-ghi789 rdfs:label "VAV-Floor3-Zone5" .
urn:buildingmotif:device-aaa111 rdfs:label "Damper" .
urn:buildingmotif:prop-xxx111 rdfs:label "Damper Position" .
```

**Frontend usage**:

- Receives URNs as strings from API responses
- Displays `label` field (not URN)
- Sends URNs back unchanged in requests (stateless REST)

### 11.2 System Instance Lifecycle

**Decisions**:

- Keep instances even if no BACnet references (reusable library)
- Labels editable, URNs immutable after creation
- Instances are snapshots (don't auto-update from template changes)

### 11.3 Validation

**Recommendation**: SHACL validation on system creation (fail fast)

- Validate against 223P shapes
- Report errors to user immediately

---

## 12. References

- [ASHRAE 223P Standard](http://data.ashrae.org/standard223)
- [BuildingMOTIF Documentation](https://buildingmotif.readthedocs.io)
- [RDFLib Documentation](https://rdflib.readthedocs.io)
- [SPARQL 1.1 Query Language](https://www.w3.org/TR/sparql11-query/)
