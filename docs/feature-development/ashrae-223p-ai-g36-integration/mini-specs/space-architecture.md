# Space Architecture Mini-Spec

**Story:** 2.9a - Space Architecture Mini-Spec
**Epic:** Epic 2 - BuildingMOTIF API Integration (Descoped)
**Created:** 2025-11-17
**Descoped:** 2025-11-17
**Status:** OUT OF SCOPE for Epic 2 (Preserved for Future Epic)

---

**⚠️ DESCOPING NOTICE**

This mini-spec was descoped from Epic 2 on 2025-11-17 to focus Epic 2 on G36 validation essentials.

**Reason**: Space management complexity warrants dedicated epic (see ADR-001)
**Future Use**: Will be implementation guide for future "Space Management" epic
**Architecture Work Preserved**: All 1139 lines retained - no rework needed when prioritized
**Reference**: `epic2/adr-001-descope-spaces.md`

---

## 0. Background: Template vs Instance Level

**Critical Distinction:**

**Templates (Class-level):**

- Reusable patterns defined in YAML files
- Located: `libraries/ashrae/223p/nrel-templates/spaces.yml`
- Define structure and requirements
- Example: `hvac-space`, `hvac-zone` templates

**Instances (Instance-level):**

- Actual spaces in your building
- Created by evaluating templates with specific names/URIs
- Example: `zone_templ.evaluate({"name": BLDG["zone1"]})`
- **This is what Story 2.9 implements** - creating space instances

**Note:** Story 2.7 (Templates Endpoint) handles template retrieval. Story 2.9 handles instance creation.

---

## 1. Space Type Taxonomy

> Define all space types, relationships, and ASHRAE 223P compliance

### 1.1 PhysicalSpace (`s223:PhysicalSpace`)

**Definition:** The actual physical room/area with walls, floors, and ceiling (architectural concept)

**ASHRAE 223P URI:** `http://data.ashrae.org/standard223#PhysicalSpace`

**Characteristics:**

- Architectural concept (room, floor, building part)
- Physical boundaries and location
- Can contain other PhysicalSpaces (hierarchical: building → floor → room)
- **Most flexible** - NO required properties in SHACL

**Examples:**

- "Office 101" - a physical room
- "Mechanical Room 3" - equipment space
- "Floor 2" - a building level
- "Conference Room A" - meeting space

**Use Cases:**

- Represents actual physical locations in building
- Equipment installation location (via `hasPhysicalLocation`)
- Sensor mounting location
- Physical measurements (supply/exhaust air flow)

**Required Properties:**

- **NONE** - completely optional in ASHRAE 223P

**Optional Properties:**

- `rdfs:label` - Human-readable name
- `dcterms:identifier` - Unique identifier
- `s223:contains` - Contains other PhysicalSpaces (hierarchical)
- `s223:encloses` - Encloses DomainSpaces (inverse relationship)
- `s223:hasProperty` - Physical properties (e.g., supply air flow)

**Minimal Valid Example:**

```turtle
:room101 a s223:PhysicalSpace .  # No requirements!
```

**Conditional Constraints:**

- If `s223:contains` is used → must point to PhysicalSpace
- If `s223:encloses` is used → must point to DomainSpace

### 1.2 DomainSpace (`s223:DomainSpace`)

**Definition:** Functional space associated with a control domain (HVAC, Lighting, etc.) - represents the "conditioned space" from a system perspective

**ASHRAE 223P URI:** `http://data.ashrae.org/standard223#DomainSpace`

**Characteristics:**

- Functional/control space concept (semantic boundary for control systems)
- **Subclass of Connectable** - can have ConnectionPoints
- Can connect to equipment via ConnectionPoints
- Domain classification required (HVAC, Lighting, etc.)

**Examples:**

- "North HVAC Zone" - thermal control zone
- "Floor 2 Lighting Zone" - lighting control area
- "East Perimeter Zone" - temperature control region

**Use Cases:**

- Represents control zones for building systems
- Properties attachment (temperature, humidity) via `hasProperty`
- Equipment connections via ConnectionPoints
- Functional/semantic grouping independent of physical walls

**Required Properties (SHACL Violations):**

- `s223:hasDomain` - Exactly 1 domain (from 10 fixed options)

**Recommended Properties (Info severity):**

- Should be enclosed by PhysicalSpace (via inverse of `encloses`)

**Optional Properties:**

- `rdfs:label` - Human-readable name
- `dcterms:identifier` - Unique identifier
- `s223:hasProperty` - Domain properties (e.g., temperature, humidity)
- `s223:hasConnectionPoint` - Air inlets/outlets for equipment connections
- `s223:cnx` / `s223:connected` - Connections to equipment

**Domain Inference:**

- Domain can be inferred from enclosing Zone's domain

**Minimal Valid Example:**

```turtle
:space1 a s223:DomainSpace ;
    s223:hasDomain s223:Domain-HVAC .  # Only required property!
```

**Full Example with Properties:**

```turtle
:zone1space1 a s223:DomainSpace ;
    s223:hasDomain s223:Domain-HVAC ;
    s223:hasProperty :temp, :humidity ;
    s223:hasConnectionPoint :in, :out .
```

### 1.3 Zone (`s223:Zone`)

**Definition:** Logical grouping that contains one or more DomainSpaces with a specific domain classification

**ASHRAE 223P URI:** `http://data.ashrae.org/standard223#Zone`

**Characteristics:**

- Logical container for DomainSpaces
- Enforces domain consistency across contained DomainSpaces
- Hierarchical grouping mechanism

**Required Properties (SHACL Violations):**

- `s223:hasDomainSpace` - Minimum 1 DomainSpace
- `s223:hasDomain` - Exactly 1 domain

**Validation Rules:**

- Zone's domain **MUST** match all contained DomainSpaces' domains

**Domain Inference:**

- Domain can be inferred from:
  - Enclosing ZoneGroup's domain, OR
  - Contained DomainSpace's domain

**Minimal Valid Example:**

```turtle
:zone1 a s223:Zone ;
    s223:hasDomain s223:Domain-HVAC ;
    s223:hasDomainSpace :space1 .

:space1 a s223:DomainSpace ;
    s223:hasDomain s223:Domain-HVAC .  # Must match Zone!
```

**Status for Story 2.9:** TBD - Decide if Zone creation is in scope

### 1.4 The Relationship Between Space Types

**Hierarchy:**

```
Zone (Logical Grouping)
    │ hasDomainSpace
    ↓
DomainSpace (Functional)
    │ enclosed by (inverse of encloses)
    ↓
PhysicalSpace (Architectural)
```

**Key Principle:** Separation of architectural (physical) from functional (control) concerns

**Why This Separation?**

1. **One physical room, multiple domains:**

   - Same conference room can have HVAC, Lighting, Security DomainSpaces

2. **Different control zones in same physical space:**

   - Open office (1 PhysicalSpace) with North/South HVAC zones (2 DomainSpaces)

3. **Equipment location vs connection:**
   - Equipment `hasPhysicalLocation` → PhysicalSpace (where installed)
   - Equipment connects → DomainSpace (what it controls)

**Complete Example:**

```turtle
# DomainSpace - HVAC-controlled functional space
:zone1space1 a s223:DomainSpace ;
    s223:hasDomain s223:Domain-HVAC ;
    s223:hasProperty :temp, :humidity ;
    s223:hasConnectionPoint :in, :out .

# PhysicalSpace - actual physical room
:zone1space1-physical a s223:PhysicalSpace ;
    s223:encloses :zone1space1 ;
    s223:hasProperty :supply-flow, :exhaust-flow .

# Sensors physically in room, observe domain properties
:temp-sensor s223:hasPhysicalLocation :zone1space1-physical ;
             s223:observes :temp .  # temp is property of DomainSpace
```

---

## 2. UI Interaction Patterns

> Define how users interact with spaces in Designer app

### 2.1 Space Creation Flow

**Selected Approach:** **Option A - Single Form with Type Selector**

**Rationale:**

- Simpler UX - one entry point for all space creation
- Follows Story 2.8 pattern (single mapping modal)
- Easier to extend if Zone support added later
- Conditional field display keeps form clean

**Option A: Single Form with Type Selector**

**Flow:**

1. User clicks "Add Space" button
2. Modal opens with "Space Type" dropdown at top
3. User selects "Physical Space" or "Domain Space"
4. Form fields adjust dynamically based on selection
5. User fills in fields and clicks "Create"

**Dynamic Field Display:**

- **Physical Space selected**: Show only Label + Description (optional)
- **Domain Space selected**: Show Label + Domain Type (required) + Description (optional)

**Pros:**

- Single UI entry point (less cognitive load)
- Progressive disclosure (only show relevant fields)
- Consistent with Story 2.8 mapping modal pattern
- Extensible (can add Zone type later)

**Cons:**

- Slightly more clicks (select type first)
- Conditional rendering logic required

**Option B: Separate Buttons/Forms** (NOT selected)

**Flow:**

- "Create Physical Space" button → PhysicalSpace-specific modal
- "Create Domain Space" button → DomainSpace-specific modal

**Pros:**

- Fewer clicks for users who know what they want
- No conditional logic

**Cons:**

- More UI clutter (2 buttons)
- Doesn't follow Story 2.8 pattern
- Harder to extend (would need 3rd button for Zone)

### 2.2 Form Fields by Type

**PhysicalSpace Form:**

| Field        | Type             | Required | Validation                     | Description                              |
| ------------ | ---------------- | -------- | ------------------------------ | ---------------------------------------- |
| Space Type   | Dropdown (fixed) | Yes      | Must be "PhysicalSpace"        | Locked to "Physical Space" when selected |
| Label        | Text input       | Yes      | Min 1 char, max 255 chars      | Human-readable name (e.g., "Office 101") |
| Description  | Textarea         | No       | Max 1000 chars                 | Optional notes about the space           |
| Parent Space | Dropdown         | No       | Must be existing PhysicalSpace | For hierarchical containment (optional)  |

**DomainSpace Form:**

| Field       | Type             | Required | Validation                      | Description                                   |
| ----------- | ---------------- | -------- | ------------------------------- | --------------------------------------------- |
| Space Type  | Dropdown (fixed) | Yes      | Must be "DomainSpace"           | Locked to "Domain Space" when selected        |
| Label       | Text input       | Yes      | Min 1 char, max 255 chars       | Human-readable name (e.g., "North HVAC Zone") |
| Domain Type | Dropdown         | **Yes**  | Must be one of 10 fixed domains | HVAC, Lighting, Electrical, etc.              |
| Description | Textarea         | No       | Max 1000 chars                  | Optional notes about the zone                 |
| Enclosed By | Dropdown         | No       | Must be existing PhysicalSpace  | PhysicalSpace that encloses this DomainSpace  |

**Domain Type Dropdown Options:**

- HVAC (default)
- Lighting
- Electrical
- Fire
- Physical Security
- Plumbing
- Refrigeration
- Networking
- Occupancy
- Conveyance Systems

### 2.3 Space List Display

**Visual Indicators:**

| Space Type    | Icon               | Badge Color | Badge Text                 |
| ------------- | ------------------ | ----------- | -------------------------- |
| PhysicalSpace | 🏢 (building icon) | Blue        | "Physical"                 |
| DomainSpace   | ⚙️ (gear icon)     | Purple      | Domain name (e.g., "HVAC") |

**List Item Structure:**

```
[Icon] Space Label
       Badge: [Physical | HVAC | Lighting | ...]
       Description (if present)
```

**Filtering Options:**

- Filter by Space Type: All / Physical Spaces / Domain Spaces
- Filter by Domain: All / HVAC / Lighting / Electrical / ...
- Filter by Parent: All / Top-level / Children of [space]

**Sorting Options:**

- By Label (A-Z, Z-A) - default
- By Created Date (newest, oldest)
- By Type (Physical first, Domain first)

---

## 3. Domain Space Specifics

> Define valid domain types and their usage

### 3.1 The 10 Fixed Domain Classes

**Critical:** Domains are **fixed enumerated classes** in ASHRAE 223P - you cannot create custom domains.

**Parent Class:** `s223:EnumerationKind-Domain`

**All Available Domains:**

| UI Label           | ASHRAE 223P URI                 | Example Equipment                      | Use Case                           |
| ------------------ | ------------------------------- | -------------------------------------- | ---------------------------------- |
| HVAC               | `s223:Domain-HVAC`              | Fans, pumps, AHUs, VAV boxes           | Temperature/humidity control zones |
| Lighting           | `s223:Domain-Lighting`          | Luminaires, daylight sensors, shades   | Lighting control areas             |
| Electrical         | `s223:Domain-Electrical`        | Breaker panels, switchgear, generators | Electrical distribution zones      |
| Fire               | `s223:Domain-Fire`              | Smoke detectors, alarm systems         | Fire safety zones                  |
| Physical Security  | `s223:Domain-PhysicalSecurity`  | Access control, surveillance           | Security monitoring areas          |
| Plumbing           | `s223:Domain-Plumbing`          | Pipes, fixtures, water systems         | Water distribution zones           |
| Refrigeration      | `s223:Domain-Refrigeration`     | Chillers, cold storage                 | Refrigerated spaces                |
| Networking         | `s223:Domain-Networking`        | Network equipment, servers             | Network coverage areas             |
| Occupancy          | `s223:Domain-Occupancy`         | Occupancy sensors, people counters     | Occupancy tracking zones           |
| Conveyance Systems | `s223:Domain-ConveyanceSystems` | Elevators, escalators                  | Vertical transportation zones      |

**SHACL Enforcement:**

- Constraint requires `sh:class s223:EnumerationKind-Domain`
- Must pick exactly one domain per DomainSpace/Zone
- Cannot extend with custom domains (standardization for interoperability)

### 3.2 Domain Type Selection

**UI Component:** Dropdown (single-select)

**Required:** **YES** - Only for DomainSpace (SHACL violation if missing)

**Validation Rules:**

- Must be one of the 10 fixed domain URIs
- Cannot be null/empty for DomainSpace
- Not applicable for PhysicalSpace

**Default Value:** `s223:Domain-HVAC` (most common use case)

**UI Presentation:**

- Show human-readable labels (e.g., "HVAC", "Lighting")
- Store/send ASHRAE 223P URIs (e.g., `s223:Domain-HVAC`)

### 3.3 Multiple Domains for One Physical Space

**Pattern:** Create multiple DomainSpaces enclosed by same PhysicalSpace

**Example:**

```turtle
# Physical conference room
:conference-room-101 a s223:PhysicalSpace ;
    rdfs:label "Conference Room 101" .

# HVAC functional zone for this room
:conf-101-hvac a s223:DomainSpace ;
    s223:hasDomain s223:Domain-HVAC ;
    rdfs:label "Conference Room 101 HVAC Zone" .

# Lighting functional zone for same room
:conf-101-lighting a s223:DomainSpace ;
    s223:hasDomain s223:Domain-Lighting ;
    rdfs:label "Conference Room 101 Lighting Zone" .

# Physical space encloses both functional spaces
:conference-room-101 s223:encloses :conf-101-hvac, :conf-101-lighting .
```

### 3.4 Available Space Templates (From BuildingMOTIF)

**Current Limitation:** Only HVAC spaces have templates. While 223P supports 10 domains, templates exist only for HVAC.

| Template Name              | Creates                            | Domain          | Purpose                                  |
| -------------------------- | ---------------------------------- | --------------- | ---------------------------------------- |
| `hvac-space`               | DomainSpace + PhysicalSpace        | HVAC            | Complete space with both representations |
| `hvac-zone`                | Zone → DomainSpace → PhysicalSpace | HVAC            | Full hierarchy with explicit domain      |
| `hvac-zone-contains-space` | Zone → DomainSpace → PhysicalSpace | HVAC (inferred) | Zone with domain inheritance             |

**Note:** Story 2.7 handles template retrieval. Story 2.9 creates instances from templates (or directly).

---

## 4. Relationships & Hierarchy

> Define space-to-space and equipment-to-space relationships

### 4.1 Space-to-Space Relationships

**Decision for Story 2.9:** **Hierarchical** - ASHRAE 223P supports space containment

**Allowed Containment Rules:**

| Parent Type   | Can Contain   | Predicate             | Example                      | SHACL Constraint                  |
| ------------- | ------------- | --------------------- | ---------------------------- | --------------------------------- |
| PhysicalSpace | PhysicalSpace | `s223:contains`       | Floor contains Rooms         | If present, must be PhysicalSpace |
| PhysicalSpace | DomainSpace   | `s223:encloses`       | Room encloses HVAC Zone      | If present, must be DomainSpace   |
| Zone          | DomainSpace   | `s223:hasDomainSpace` | Zone contains DomainSpace(s) | Required, min 1                   |

**Not Allowed:**

- PhysicalSpace containing DomainSpace (use `encloses` instead)
- DomainSpace containing other spaces (DomainSpace is not a container)
- Zone containing PhysicalSpace directly (must go through DomainSpace)

**Hierarchical Example:**

```turtle
# Building → Floor → Room hierarchy (PhysicalSpace)
:building-1 a s223:PhysicalSpace ;
    s223:contains :floor-2 .

:floor-2 a s223:PhysicalSpace ;
    s223:contains :room-201, :room-202 .

# Room encloses functional zones (PhysicalSpace encloses DomainSpace)
:room-201 a s223:PhysicalSpace ;
    s223:encloses :room-201-hvac-zone .

:room-201-hvac-zone a s223:DomainSpace ;
    s223:hasDomain s223:Domain-HVAC .
```

### 4.2 Equipment-to-Space Relationships

**Key Principle:** Spaces don't "belong to" equipment - they are independent entities that equipment serves.

**From Story 2.8 Patterns:**

#### 4.2.1 Physical Location

**Predicate:** `s223:hasPhysicalLocation`

**Source:** Equipment, Sensors
**Target:** PhysicalSpace
**Cardinality:** 0..1 (optional, single)
**Meaning:** Where the equipment is physically installed

**Example:**

```turtle
:vav-1 s223:hasPhysicalLocation :ceiling-space .
:temp-sensor s223:hasPhysicalLocation :room-101 .
```

**From Story 2.8:** Equipment uses `s223:locatedIn` for PhysicalSpace references

#### 4.2.2 Functional Connections

**Predicate:** `s223:cnx` / `s223:connected` (via ConnectionPoints)

**Source:** Equipment ConnectionPoint
**Target:** DomainSpace ConnectionPoint
**Cardinality:** 0..\* (optional, multiple)
**Meaning:** Equipment connects to and serves this functional space

**Example:**

```turtle
# Equipment connects to DomainSpace via ConnectionPoints
:vav-1-outlet s223:cnx :duct-1 .
:duct-1 s223:connectsTo :room101-air-inlet .

# room101-air-inlet is a ConnectionPoint of the DomainSpace
:room101-hvac-zone s223:hasConnectionPoint :room101-air-inlet .
```

#### 4.2.3 Domain Reference (From Story 2.8)

**Predicate:** `s223:hasDomain`

**Source:** Equipment (in Story 2.8 mappings)
**Target:** DomainSpace
**Cardinality:** 0..\* (optional, multiple)
**Meaning:** Equipment serves multiple functional domains

**Example:**

```turtle
:equipment-1 s223:hasDomain :north-hvac-zone, :floor-2-lighting-zone .
```

**Note:** Story 2.8 uses `s223:hasDomain` for domain space IDs in mappings

#### 4.2.4 Typical Usage Pattern

**How Equipment Connects to Spaces:**

1. **Via ConnectionPoints and Connections:**

   ```python
   # Create duct connection from VAV to space
   vav1_to_zone1 = duct_templ.evaluate({
       "a": BLDG["VAV-1-out"],  # Equipment outlet ConnectionPoint
       "b": BLDG["zone1-in"]     # Space inlet ConnectionPoint
   })
   ```

2. **Equipment physically located in spaces:**

   ```turtle
   :vav-1 s223:hasPhysicalLocation :ceiling-space .
   ```

3. **Equipment serves multiple spaces:**
   - One AHU can serve multiple VAVs → multiple rooms
   - One VAV typically serves one space

**Sensors Observe Domain Properties but Located in Physical Space:**

```turtle
# Sensor physical location
:temp-sensor s223:hasPhysicalLocation :room-101 .

# Sensor observes property OF the DomainSpace
:temp-sensor s223:observes :room-101-hvac-temp .
:room-101-hvac-zone s223:hasProperty :room-101-hvac-temp .
```

---

## 5. API Contract

> Define request/response structures for spaces endpoints

### 5.1 POST /api/v1/223p/spaces

**Endpoint:** `POST /api/v1/223p/spaces`

**Purpose:** Create a new space instance (PhysicalSpace or DomainSpace)

**Request DTO:**

```typescript
interface CreateSpaceRequestDTO {
  projectId: string; // Required: Project to add space to
  spaceType: "PhysicalSpace" | "DomainSpace"; // Required: Type discriminator
  label: string; // Required: Human-readable name
  domainType?: string; // Required if spaceType === "DomainSpace"
  description?: string; // Optional: Notes about space
  parentSpaceId?: string; // Optional: For PhysicalSpace hierarchy
  enclosedById?: string; // Optional: For DomainSpace enclosure
}
```

**Response DTO:**

```typescript
interface SpaceInstanceDTO {
  id: string; // Generated space identifier (e.g., "urn:bms:Space:uuid")
  spaceTypeId: string; // ASHRAE 223P class URI (e.g., "s223:PhysicalSpace")
  label: string; // Human-readable name
  domainType?: string; // Domain URI (only for DomainSpace, e.g., "s223:Domain-HVAC")
  description?: string; // Optional notes
  parentSpaceId?: string; // Parent PhysicalSpace ID (if hierarchical)
  enclosedById?: string; // Enclosing PhysicalSpace ID (for DomainSpace)
  createdAt: string; // ISO 8601 timestamp
}
```

**Validation Rules:**

| Rule                                | Condition                                  | Error                                                   |
| ----------------------------------- | ------------------------------------------ | ------------------------------------------------------- |
| projectId required                  | Missing or empty                           | 422: "projectId is required"                            |
| spaceType required                  | Missing or not in enum                     | 422: "spaceType must be PhysicalSpace or DomainSpace"   |
| label required                      | Missing or empty                           | 422: "label is required"                                |
| label length                        | < 1 or > 255 chars                         | 422: "label must be 1-255 characters"                   |
| domainType required for DomainSpace | spaceType === "DomainSpace" && !domainType | 422: "domainType is required for DomainSpace"           |
| domainType valid                    | domainType not in 10 fixed domains         | 422: "domainType must be one of: s223:Domain-HVAC, ..." |
| parentSpaceId exists                | parentSpaceId provided but not found       | 404: "Parent space not found"                           |
| parentSpaceId type                  | parentSpaceId points to DomainSpace        | 422: "Parent space must be PhysicalSpace"               |
| enclosedById exists                 | enclosedById provided but not found        | 404: "Enclosing space not found"                        |
| enclosedById type                   | enclosedById points to DomainSpace         | 422: "Enclosing space must be PhysicalSpace"            |

**Error Responses:**

```typescript
// 400 Bad Request - Malformed JSON
{
  "error": "Bad Request",
  "message": "Invalid JSON in request body"
}

// 422 Unprocessable Entity - Validation failure
{
  "error": "Validation Error",
  "message": "domainType is required for DomainSpace",
  "field": "domainType"
}

// 500 Internal Server Error - BuildingMOTIF or RDF error
{
  "error": "Internal Server Error",
  "message": "Failed to create space instance"
}
```

**Example Request (PhysicalSpace):**

```json
{
  "projectId": "urn:bms:Project:abc123",
  "spaceType": "PhysicalSpace",
  "label": "Office 101",
  "description": "Corner office on first floor"
}
```

**Example Request (DomainSpace):**

```json
{
  "projectId": "urn:bms:Project:abc123",
  "spaceType": "DomainSpace",
  "label": "North HVAC Zone",
  "domainType": "s223:Domain-HVAC",
  "description": "Temperature control for north wing",
  "enclosedById": "urn:bms:Space:office101-id"
}
```

### 5.2 GET /api/v1/223p/spaces

**Endpoint:** `GET /api/v1/223p/spaces`

**Purpose:** Retrieve all spaces for a project with optional filtering

**Query Parameters:**

| Parameter  | Type   | Required | Description                   | Example                          | Default     |
| ---------- | ------ | -------- | ----------------------------- | -------------------------------- | ----------- |
| projectId  | string | **Yes**  | Filter by project             | `urn:bms:Project:abc123`         | -           |
| spaceType  | string | No       | Filter by type                | `PhysicalSpace` or `DomainSpace` | All types   |
| domainType | string | No       | Filter DomainSpaces by domain | `s223:Domain-HVAC`               | All domains |

**Response:**

```typescript
Array<SpaceInstanceDTO>;
```

**Sorting:**

- Default: By `label` ascending (A-Z)
- Future: Add `sort` query parameter if needed

**Pagination:**

- Not implemented in Story 2.9 (return all spaces)
- Future: Add `page` and `limit` parameters if performance requires

**Error Responses:**

```typescript
// 400 Bad Request - Missing required query parameter
{
  "error": "Bad Request",
  "message": "projectId query parameter is required"
}

// 404 Not Found - Project doesn't exist
{
  "error": "Not Found",
  "message": "Project not found"
}
```

**Example Request:**

```bash
GET /api/v1/223p/spaces?projectId=urn:bms:Project:abc123&spaceType=DomainSpace
```

**Example Response:**

```json
[
  {
    "id": "urn:bms:Space:space-1-uuid",
    "spaceTypeId": "s223:DomainSpace",
    "label": "North HVAC Zone",
    "domainType": "s223:Domain-HVAC",
    "description": "Temperature control for north wing",
    "enclosedById": "urn:bms:Space:office101-id",
    "createdAt": "2025-11-17T10:30:00Z"
  },
  {
    "id": "urn:bms:Space:space-2-uuid",
    "spaceTypeId": "s223:DomainSpace",
    "label": "South HVAC Zone",
    "domainType": "s223:Domain-HVAC",
    "createdAt": "2025-11-17T10:31:00Z"
  }
]
```

### 5.3 Consistency with Story 2.8

**URI Pattern:**

- Story 2.8 Equipment: `urn:bms:Equipment:{pointId}` (from BMS point ID)
- Story 2.9 Spaces: `urn:bms:Space:{uuid}` (generated UUID)

**External Project Relationship:**

- Story 2.8: Equipment uses external `project s223:hasPart equipment`
- Story 2.9: Spaces use external `project s223:contains space`

**Bulk Operations:**

- Story 2.8: POST accepts array, GET returns array
- Story 2.9: POST accepts single object (simpler), GET returns array

**DTO Field Naming:**

- Story 2.8: `equipmentTypeId`, `deviceTypeId` (ASHRAE URIs)
- Story 2.9: `spaceTypeId`, `domainType` (ASHRAE URIs)

---

## 6. RDF Patterns

> Define RDF triple patterns for each space type

### 6.1 PhysicalSpace RDF Pattern

**Minimal Valid Pattern:**

```turtle
@prefix s223: <http://data.ashrae.org/standard223#> .
@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .
@prefix dcterms: <http://purl.org/dc/terms/> .
@prefix bms: <urn:bms:> .

# Space instance (minimal - no required properties!)
bms:Space:uuid-office-101 a s223:PhysicalSpace ;
    rdfs:label "Office 101" ;
    dcterms:identifier "space-office-101" .

# Project relationship (external - separate graph)
bms:Project:abc123 s223:contains bms:Space:uuid-office-101 .
```

**Full Pattern with Hierarchy:**

```turtle
# Building level
bms:Space:uuid-building-1 a s223:PhysicalSpace ;
    rdfs:label "Main Building" ;
    dcterms:identifier "building-1" ;
    s223:contains bms:Space:uuid-floor-2 .

# Floor level
bms:Space:uuid-floor-2 a s223:PhysicalSpace ;
    rdfs:label "Floor 2" ;
    dcterms:identifier "floor-2" ;
    s223:contains bms:Space:uuid-office-101 .

# Room level
bms:Space:uuid-office-101 a s223:PhysicalSpace ;
    rdfs:label "Office 101" ;
    dcterms:identifier "office-101" ;
    dcterms:description "Corner office on first floor" ;
    s223:encloses bms:Space:uuid-office-101-hvac .

# Project relationship (external)
bms:Project:abc123 s223:contains bms:Space:uuid-building-1 .
```

**Required Triples:**

- `rdf:type s223:PhysicalSpace` (required)
- `rdfs:label` (recommended)
- `dcterms:identifier` (recommended)

**Optional Triples:**

- `dcterms:description` (optional notes)
- `s223:contains` (hierarchical containment)
- `s223:encloses` (encloses DomainSpace)

### 6.2 DomainSpace RDF Pattern

**Minimal Valid Pattern:**

```turtle
# Space instance (minimal - only domain required!)
bms:Space:uuid-hvac-north a s223:DomainSpace ;
    rdfs:label "North HVAC Zone" ;
    s223:hasDomain s223:Domain-HVAC ;
    dcterms:identifier "zone-hvac-north" .

# Project relationship (external)
bms:Project:abc123 s223:contains bms:Space:uuid-hvac-north .
```

**Full Pattern with Enclosure:**

```turtle
# PhysicalSpace encloses DomainSpace
bms:Space:uuid-office-101 a s223:PhysicalSpace ;
    rdfs:label "Office 101" ;
    s223:encloses bms:Space:uuid-office-101-hvac .

# DomainSpace - functional HVAC zone
bms:Space:uuid-office-101-hvac a s223:DomainSpace ;
    rdfs:label "Office 101 HVAC Zone" ;
    s223:hasDomain s223:Domain-HVAC ;
    dcterms:identifier "office-101-hvac" ;
    dcterms:description "Temperature control for Office 101" .

# Project relationship (external)
bms:Project:abc123 s223:contains bms:Space:uuid-office-101 .
bms:Project:abc123 s223:contains bms:Space:uuid-office-101-hvac .
```

**Required Triples:**

- `rdf:type s223:DomainSpace` (required)
- `s223:hasDomain` (required - exactly 1 domain URI)
- `rdfs:label` (recommended)
- `dcterms:identifier` (recommended)

**Optional Triples:**

- `dcterms:description` (optional notes)
- Inverse of `s223:encloses` (enclosing PhysicalSpace)

### 6.3 URI Generation Pattern

**Decision:** Unified space URIs with UUID suffix

**Format:** `urn:bms:Space:{uuid}`

**Why Unified:**

- Simpler than separate `PhysicalSpace` and `DomainSpace` URIs
- Type is explicit in RDF (`rdf:type`)
- Consistent with other BMS entities

**UUID Generation:**

- Python: `str(uuid.uuid4())`
- Format: `urn:bms:Space:550e8400-e29b-41d4-a716-446655440000`

**Consistency with Story 2.8:**

- Story 2.8 Equipment: `urn:bms:Equipment:{pointId}` (uses existing BMS point ID)
- Story 2.9 Spaces: `urn:bms:Space:{uuid}` (generates new UUID)
- Story 2.9 Projects: `urn:bms:Project:{projectId}` (from Designer app)

**Examples:**

```python
import uuid

# Generate space URIs
physical_space_uri = f"urn:bms:Space:{uuid.uuid4()}"
# Result: "urn:bms:Space:a1b2c3d4-e5f6-7890-abcd-ef1234567890"

domain_space_uri = f"urn:bms:Space:{uuid.uuid4()}"
# Result: "urn:bms:Space:b2c3d4e5-f6a7-8901-bcde-f12345678901"
```

### 6.4 SPARQL Query Examples

**Query 1: Get all spaces for a project**

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>

SELECT ?space ?type ?label ?domain
WHERE {
  bms:Project:abc123 s223:contains ?space .

  ?space rdf:type ?type ;
         rdfs:label ?label .

  OPTIONAL {
    ?space s223:hasDomain ?domain .
  }
}
ORDER BY ?label
```

**Query 2: Get only PhysicalSpaces**

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

SELECT ?space ?label
WHERE {
  bms:Project:abc123 s223:contains ?space .

  ?space a s223:PhysicalSpace ;
         rdfs:label ?label .
}
ORDER BY ?label
```

**Query 3: Get DomainSpaces filtered by domain**

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

SELECT ?space ?label ?domain
WHERE {
  bms:Project:abc123 s223:contains ?space .

  ?space a s223:DomainSpace ;
         rdfs:label ?label ;
         s223:hasDomain s223:Domain-HVAC .
}
ORDER BY ?label
```

**Query 4: Get space hierarchy (PhysicalSpace containment)**

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

SELECT ?parent ?parentLabel ?child ?childLabel
WHERE {
  bms:Project:abc123 s223:contains ?parent .

  ?parent a s223:PhysicalSpace ;
          rdfs:label ?parentLabel ;
          s223:contains ?child .

  ?child rdfs:label ?childLabel .
}
ORDER BY ?parentLabel ?childLabel
```

**Query 5: Get PhysicalSpace with enclosed DomainSpaces**

```sparql
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX bms: <urn:bms:>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

SELECT ?physicalSpace ?physLabel ?domainSpace ?domLabel ?domain
WHERE {
  bms:Project:abc123 s223:contains ?physicalSpace .

  ?physicalSpace a s223:PhysicalSpace ;
                 rdfs:label ?physLabel ;
                 s223:encloses ?domainSpace .

  ?domainSpace a s223:DomainSpace ;
               rdfs:label ?domLabel ;
               s223:hasDomain ?domain .
}
ORDER BY ?physLabel ?domLabel
```

### 6.5 Namespace Prefixes

**Standard Prefixes for Story 2.9:**

```python
PREFIXES = {
    "rdf": "http://www.w3.org/1999/02/22-rdf-syntax-ns#",
    "rdfs": "http://www.w3.org/2000/01/rdf-schema#",
    "s223": "http://data.ashrae.org/standard223#",
    "dcterms": "http://purl.org/dc/terms/",
    "bms": "urn:bms:"
}
```

**Usage in RDFLib (Python):**

```python
from rdflib import Namespace, Graph

S223 = Namespace("http://data.ashrae.org/standard223#")
BMS = Namespace("urn:bms:")
RDFS = Namespace("http://www.w3.org/2000/01/rdf-schema#")
DCTERMS = Namespace("http://purl.org/dc/terms/")

g = Graph()
g.bind("s223", S223)
g.bind("bms", BMS)
g.bind("rdfs", RDFS)
g.bind("dcterms", DCTERMS)
```

---

## 7. Decision Summary

> Quick reference for all key decisions

| Decision Point             | Selected Option                                                  | Rationale                                                                   |
| -------------------------- | ---------------------------------------------------------------- | --------------------------------------------------------------------------- |
| **Space Types to Support** | PhysicalSpace + DomainSpace (Story 2.9)<br>Zone support deferred | Start with core types, add Zone later if needed                             |
| **Hierarchical or Flat**   | **Hierarchical**                                                 | ASHRAE 223P supports containment, enables building/floor/room modeling      |
| **UI Creation Pattern**    | **Single form with type selector**                               | Consistent with Story 2.8, extensible, simpler UX                           |
| **Form Fields**            | Dynamic based on space type                                      | PhysicalSpace: Label + Description<br>DomainSpace: + Domain Type (required) |
| **Domain Type Options**    | 10 fixed ASHRAE 223P domains                                     | Cannot extend - standardization enforced by SHACL                           |
| **Default Domain**         | `s223:Domain-HVAC`                                               | Most common use case in BMS                                                 |
| **URI Format**             | `urn:bms:Space:{uuid}`                                           | Unified format, type in RDF, consistent with BMS namespace                  |
| **Project Relationship**   | External `project s223:contains space`                           | Same pattern as Story 2.8 equipment                                         |
| **Bulk Operations**        | POST single, GET array                                           | Simpler than Story 2.8 bulk POST                                            |
| **Validation**             | SHACL via BuildingMOTIF                                          | Leverage existing validation, enforce 223P compliance                       |
| **Hierarchy Predicates**   | `s223:contains` (PhysicalSpace)<br>`s223:encloses` (DomainSpace) | ASHRAE 223P standard predicates                                             |
| **Required Properties**    | PhysicalSpace: None<br>DomainSpace: `hasDomain` (exactly 1)      | Per ASHRAE 223P SHACL constraints                                           |
| **Template Usage**         | Direct RDF creation (not templates)                              | Spaces are simpler than equipment, no template complexity needed            |
| **Visual Indicators**      | 🏢 Blue for Physical<br>⚙️ Purple for Domain                     | Clear visual distinction in UI                                              |
| **Filtering**              | By type, domain, parent                                          | Essential for usability in large projects                                   |

---

## 8. Open Questions

> Track unresolved questions during spec development

### Resolved Questions

1. **Should we support Zone creation in Story 2.9?**

   - Status: **Resolved**
   - Decision: **No** - Focus on PhysicalSpace and DomainSpace. Zone support can be added in future story if needed.
   - Rationale: Zone adds complexity (hasDomainSpace + hasDomain requirements), and we don't have clear use case yet.

2. **Template-based or direct RDF creation?**

   - Status: **Resolved**
   - Decision: **Direct RDF creation** (not using BuildingMOTIF templates)
   - Rationale: Spaces are simpler than equipment. Only HVAC templates exist. Direct creation gives more flexibility.

3. **Unified URI format or type-specific URIs?**

   - Status: **Resolved**
   - Decision: **Unified** - `urn:bms:Space:{uuid}` for all space types
   - Rationale: Type is explicit in RDF triple. Simpler implementation.

4. **Should PhysicalSpace have required properties?**

   - Status: **Resolved**
   - Decision: **No** - ASHRAE 223P has zero required properties for PhysicalSpace
   - Rationale: Per SHACL validation, PhysicalSpace is the most flexible type.

5. **Can users create custom domains?**
   - Status: **Resolved**
   - Decision: **No** - Only 10 fixed ASHRAE 223P domains allowed
   - Rationale: SHACL constraint enforces `sh:class s223:EnumerationKind-Domain`. Standardization for interoperability.

### Open Questions

1. **Should we auto-create matching PhysicalSpace when creating DomainSpace?**

   - Status: **Open**
   - Options:
     - A: User creates PhysicalSpace first, then DomainSpace with `enclosedById`
     - B: Auto-create PhysicalSpace when creating DomainSpace (with same label)
     - C: Make it optional - DomainSpace can exist without PhysicalSpace
   - Recommendation: **Option A** - Explicit is better than implicit. User controls structure.

2. **Should hierarchy be enforced in UI (parent dropdown) or optional?**

   - Status: **Open**
   - Options:
     - A: Always require parent selection (forced hierarchy)
     - B: Make parent optional (allows top-level spaces)
   - Recommendation: **Option B** - Optional parent. User might start with single room, add building hierarchy later.

3. **Should we validate unique labels within project?**

   - Status: **Open**
   - Options:
     - A: Enforce unique labels per project (prevent "Office 101" duplicates)
     - B: Allow duplicate labels (user responsibility)
   - Recommendation: **Option B** - Labels are human-readable, identifiers are unique URIs. Multiple "Conference Room A" on different floors is valid.

4. **Should GET endpoint return hierarchy structure or flat list?**
   - Status: **Open**
   - Options:
     - A: Flat array (current spec)
     - B: Nested structure reflecting `contains` relationships
   - Recommendation: **Option A for Story 2.9** - Flat is simpler. Frontend can build tree from parent IDs. Future story can add `/spaces/tree` endpoint.

---

## 9. References

**ASHRAE 223P:**

- [ASHRAE 223P Ontology](https://data.ashrae.org/standard223)
- [BuildingMOTIF Documentation](https://buildingmotif.readthedocs.io/)

**Related Stories:**

- [Story 2.7: Templates Endpoint](../stories/2-7-implement-templates-endpoint.md)
- [Story 2.8: Mappings Endpoints](../stories/2-8-implement-mappings-endpoints.md)
- [Story 2.9: Spaces Endpoints](../stories/2-9-implement-spaces-endpoints.md) - Implementation

**Epic Documentation:**

- [Epic 2 Phase Breakdown](../epic2/epic-2-phase-breakdown.md)

---

## Approval

**Author:** Claude (Dev Agent - Amelia)
**Created:** 2025-11-17
**Status:** **PENDING REVIEW**
**Reviewed By:** Awaiting Amol review
**Approved Date:** Pending

**Sign-off:** Once approved, this mini-spec serves as the implementation guide for Story 2.9.

---

## Summary

This mini-spec provides comprehensive architectural guidance for Story 2.9 (Implement Spaces Endpoints) including:

✅ **Complete space type taxonomy** (PhysicalSpace, DomainSpace, Zone)
✅ **UI interaction patterns** (single form with type selector, dynamic fields)
✅ **10 fixed ASHRAE 223P domains** (HVAC, Lighting, etc.)
✅ **Hierarchical relationships** (contains, encloses)
✅ **API contract specification** (POST/GET endpoints, DTOs, validation)
✅ **RDF patterns and SPARQL queries** (minimal/full examples)
✅ **Decision summary** (15 key architectural decisions documented)
✅ **Open questions** (4 items flagged for Amol's input)

**Ready for:** Story 2.9 implementation once approved.
