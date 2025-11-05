# Phase 1: 223P Mapping Popup Design

**Created**: October 30, 2025
**Status**: Design Phase
**Parent Spec**: [BuildingMotif Integration Specification](./2025-10-24-buildingmotif-integration-spec.md)
**Duration**: 3-4 days

## Overview

Integration of ASHRAE 223P semantic mapping directly into the canvas workflow. When users interact with BACnet nodes on the canvas, a popup allows them to map points to 223P equipment models using BuildingMOTIF's template library.

## Key Design Principles

1. **Pre-filled from BACnet data**: Use discovered BACnet properties to intelligently pre-populate form fields
2. **AI-assisted mapping**: Optional AI feature analyzes BACnet metadata to suggest equipment and point roles
3. **BuildingMOTIF alignment**: Use exact template names and property types from BuildingMOTIF library
4. **Canvas-integrated**: No separate Equipment section—mapping happens directly on the visual canvas

## BuildingMOTIF Template Mappings

### Equipment Templates (8 types)

From `systems.yml`:

1. **makeup-air-unit** - Makeup Air Unit (https://www.youtube.com/watch?v=4l9SAR7VV_Y)
2. **vav-reheat** - VAV Reheat Unit
3. **lab-vav-reheat** - Lab VAV Reheat Unit
4. **exhaust-air-unit** - Exhaust Air Unit
5. **chilled-water-system** - Chilled Water System
6. **hot-water-system** - Hot Water System
7. **process-chilled-water-system** - Process Chilled Water System
8. **heat-recovery-system** - Heat Recovery System

### Device Templates (15 types)

From `devices.yml`:

1. **damper** - Damper (command, feedback, inlet/outlet)
2. **valve** - Valve (command, feedback, inlet/outlet)
3. **fan** - Fan (start command, motor status, VFD properties)
4. **filter** - Filter (differential pressure)
5. **heat-recovery-coil** - Heat Recovery Coil (air/water temps)
6. **chilled-water-coil** - Chilled Water Coil (air/water temps)
7. **hot-water-coil** - Hot Water Coil (water temps)
8. **chw-pump** - Chilled Water Pump (on/off, status, VFD)
9. **hw-pump** - Hot Water Pump (on/off, status, VFD)
10. **hr-pump** - Heat Recovery Pump (on/off, status, VFD)
11. **evaporative-cooler** - Evaporative Cooler (air temp, humidity)
12. **heat-exchanger** - Heat Exchanger (water temps, flow, pressure)
13. **fan-coil-unit** - Fan Coil Unit (temp, humidity, coils, fan)
14. **unit-heater** - Unit Heater (fan, heating coil)
15. **exhaust-fan** - Exhaust Fan (low static pressure sensor)

### Observable Properties (25 types)

From `properties.yml`:

1. Static Pressure
2. Low Static Pressure
3. Water Static Pressure
4. Differential Pressure
5. Water Differential Pressure
6. Air Temperature
7. Air Flow
8. Water Temperature
9. Water Flow
10. Run Status
11. Flow Status
12. Relative Humidity
13. VFD Current
14. VFD Frequency
15. VFD Voltage
16. VFD Power
17. VFD Energy
18. VFD Speed Feedback
19. VFD Fault
20. BTU Meter Energy
21. BTU Meter Energy Rate
22. BTU Meter Water Flow
23. BTU Meter Water Volume
24. Condensate Overflow
25. Occupancy Override

### Actuatable Properties (4 types)

1. Damper Command
2. Damper Feedback
3. Start Command
4. VFD Speed

## 223P Hierarchy

ASHRAE 223P follows a strict hierarchy that we must respect:

```
Building
  └─ Zones (Physical Spaces)
      └─ Equipment
          └─ Devices (Dampers, Valves, Coils, etc.)
              └─ Properties (Sensors, Actuators)
                  └─ External References (BACnet)
```

Key relationships:

- `s223:contains` - Building contains Zones, Zones contain Equipment
- `s223:hasConnectionPoint` - Equipment has connection points for topology
- `s223:cnx` - Connections between equipment
- `rdfs:label` - Human-readable names for all entities
- `s223:hasMedium` - Medium (Air, Water, Electricity) handled by templates
- `s223:hasExternalReference` - Link to physical BACnet controllers

## Popup Structure

### Section 1: BACnet Information (Read-Only)

Displays the source BACnet point information for user reference:

**Fields**:

- **Object Name**: `VAV-2-01_SAT`
- **Device ID**: `123`
- **Object Type**: `analogInput`
- **Object Instance**: `1`
- **Units**: `degreesFahrenheit`
- **Current Value**: `72.5°F` (if available)

**Purpose**: Show users exactly what BACnet point they're mapping to 223P

### Section 2: Zone Selection

**Field**: Zone Dropdown with autocomplete

**Options**:

- Select existing zone (e.g., "Floor 2 Conference Room", "Building South Wing")
- "Create New Zone" → prompts for zone name
- **Default**: "Unassigned Zone" (automatically created)

**Pre-fill Logic**:

- Parse BACnet object name for zone/floor hints:
  - "F2", "FL2", "Floor2" → "Floor 2"
  - "CONF", "Conference" → "Conference Room"
- Match against existing zones
- Default to "Unassigned Zone" if no match

**AI Enhancement**:

- Analyze multiple points to infer zone patterns
- Learn zone naming conventions from user

**BuildingMOTIF Template**: `hvac-space`

### Section 3: Equipment Selection

**Field**: Equipment Dropdown with autocomplete

**Options**:

- Select existing equipment in selected zone (e.g., "VAV-2-01", "AHU Main Floor")
- "Create New Equipment" → opens equipment creation fields

**Pre-fill Logic**:

- Extract equipment identifier from object name:
  - "VAV-2-01_SAT" → "VAV-2-01"
  - "AHU-1-SUPPLY-TEMP" → "AHU-1"
- Match against existing equipment in zone
- If no match, default to "Create New Equipment"

**AI Enhancement**:

- Group related points by common prefix
- Suggest equipment based on point collection

### Section 4: Equipment Details (If Creating New)

**4a. Equipment Name**

**Field**: Text input

**Pre-fill Logic**:

- Extract from BACnet object name: "VAV-2-01_SAT" → "VAV-2-01"
- If no clear identifier, suggest: "[Template] - Floor X"

**Validation**:

- Required field
- Must be unique within zone

**4b. Equipment Template**

**Field**: Dropdown with descriptions

**Options** (8 templates from `systems.yml`):

1. **VAV Reheat Unit** - Variable air volume terminal with reheat coil
2. **Makeup Air Unit** - Outside air handling with multiple stages
3. **Lab VAV Reheat Unit** - Laboratory VAV with valve damper
4. **Exhaust Air Unit** - Exhaust fan with pre-filter and heat recovery
5. **Chilled Water System** - Chilled water distribution with pumps
6. **Hot Water System** - Hot water distribution with pumps and heater
7. **Process Chilled Water System** - Process cooling water system
8. **Heat Recovery System** - Heat recovery with coils and pump

**Pre-fill Logic**:

- Parse object name for keywords:
  - "VAV" → VAV Reheat Unit
  - "AHU", "MAU" → Makeup Air Unit
  - "LAB", "LABVAV" → Lab VAV Reheat Unit
  - "EAU", "EXH", "EXHAUST" → Exhaust Air Unit
  - "CHW", "CHILLER" → Chilled Water System
  - "HW", "BOILER" → Hot Water System

**AI Enhancement**:

- Analyze object name + related points
- Consider building type and context
- Display confidence: "VAV Reheat Unit (AI: 95%)"

**Template Behavior**:

- Templates automatically create all required devices (dampers, coils, sensors)
- Templates set `s223:hasMedium` (e.g., VAV → Air, CHW → Water)
- Templates define connection points (inlet, outlet)
- Templates include standard sensors/actuators

**Example**: Selecting "VAV Reheat Unit" creates:

- Reheat coil device
- Damper device
- Supply air flow sensor
- Supply air temperature sensor
- Supply air pressure sensor
- Air inlet connection point
- Air outlet connection point

### Section 5: Point Mapping

**Field**: Template Sensor/Property Dropdown

**Label**: "This BACnet point represents:"

**Options** (filtered by selected template):

For **VAV Reheat Unit**:

- `sup-air-temp-sensor` - Supply Air Temperature Sensor
- `sup-air-flow-sensor` - Supply Air Flow Sensor
- `sup-air-pressure-sensor` - Supply Air Static Pressure Sensor
- `rhc` (Reheat Coil) properties:
  - Heating valve command
  - Heating valve feedback
- `dmp` (Damper) properties:
  - Damper position command
  - Damper position feedback

For **Chilled Water System**:

- CHW pump start/stop command
- CHW pump status
- CHW pump VFD speed
- Supply water temperature
- Return water temperature
- Differential pressure

**Pre-fill Logic**:

- Match BACnet object type + units to template sensors:
  - analogInput + degF + "SAT"/"SUPPLY" → sup-air-temp-sensor
  - analogInput + CFM → sup-air-flow-sensor
  - analogInput + pascals → sup-air-pressure-sensor
  - analogOutput + percent + "DAMPER" → damper position command

**AI Enhancement**:

- Semantic analysis of object name
- Consider equipment context
- Show confidence score

**External Reference**:
When point is mapped, store BACnet reference:

```turtle
:my_vav_sat_sensor a s223:Sensor ;
  rdfs:label "VAV-2-01 Supply Air Temperature Sensor" ;
  s223:hasExternalReference [
    a s223:BACnetReference ;
    s223:hasDeviceID "123" ;
    s223:hasObjectType "analogInput" ;
    s223:hasObjectInstance "1" ;
    s223:hasObjectName "VAV-2-01_SAT"
  ] .
```

### Section 6: Validation Status

**Field**: Read-only status indicator with icon

**Display**:

- ✅ **Valid**: "Mapping complete and valid"
- ⚠️ **Warning**: "Review recommended - [reason]"
- ❌ **Error**: "[specific issue]"

**Validation Rules**:

1. Zone must be selected (or use default)
2. Equipment must be selected or created
3. If creating equipment:
   - Name is required and unique
   - Template is required
4. Point mapping is required
5. BACnet reference is complete

**Examples**:

- ✅ "Ready to save - Zone: Floor 2, Equipment: VAV-2-01, Point: Supply Air Temp Sensor"
- ⚠️ "Using default 'Unassigned Zone' - consider specifying actual zone"
- ❌ "Equipment name 'VAV-2-01' already exists in zone 'Floor 2'"

## User Workflows

### Scenario 1: Single Point Mapping (Create New Equipment)

**Context**: User discovers BACnet point "VAV-2-01_SAT" (device 123, AI:1, 72.5°F)

**Flow**:

1. User drags BACnet point onto canvas from left sidebar
2. Node appears on canvas with "Map to 223P" button
3. User clicks "Map to 223P" → popup opens

**Popup Display**:

```
╔═══════════════════════════════════════════════════════╗
║ Map BACnet Point to ASHRAE 223P                      ║
╠═══════════════════════════════════════════════════════╣
║ BACnet Information (Read-Only)                       ║
║ ─────────────────────────────────────────────────    ║
║ Name: VAV-2-01_SAT                                    ║
║ Device: 123 | Type: analogInput | Instance: 1        ║
║ Units: degreesFahrenheit | Value: 72.5°F             ║
╠═══════════════════════════════════════════════════════╣
║ Zone                                                  ║
║ [Floor 2                        ▼] (AI: 90%)         ║
║                                                       ║
║ Equipment                                             ║
║ [Create New Equipment           ▼]                   ║
║                                                       ║
║ ┌─ Equipment Details ──────────────────────────────┐ ║
║ │ Name: [VAV-2-01                              ]   │ ║
║ │                                                   │ ║
║ │ Template: [VAV Reheat Unit    ▼] (AI: 95%)      │ ║
║ │                                                   │ ║
║ │ Creates:                                          │ ║
║ │ • Reheat coil, Damper                            │ ║
║ │ • Supply air temp/flow/pressure sensors          │ ║
║ │ • Medium: Air (automatic)                        │ ║
║ └───────────────────────────────────────────────────┘ ║
║                                                       ║
║ This BACnet point represents:                        ║
║ [Supply Air Temperature Sensor  ▼] (AI: 98%)        ║
║                                                       ║
║ ┌─ BACnet Reference ────────────────────────────────┐║
║ │ Stored as: s223:hasExternalReference             │║
║ │ • Device ID: 123                                 │║
║ │ • Object: analogInput:1                          │║
║ │ • Name: VAV-2-01_SAT                             │║
║ └──────────────────────────────────────────────────┘ ║
╠═══════════════════════════════════════════════════════╣
║ ✅ Ready to save                                     ║
║ Zone: Floor 2                                        ║
║ Equipment: VAV-2-01 (new)                            ║
║ Point: Supply Air Temperature Sensor                ║
╠═══════════════════════════════════════════════════════╣
║                          [Cancel]  [Save Mapping]    ║
╚═══════════════════════════════════════════════════════╝
```

4. User reviews pre-filled values (all fields populated by AI)
5. User clicks "Save Mapping"
6. Background: POST to BuildingMOTIF creates zone + equipment + sensor
7. Node updates with 223P badge: "VAV-2-01 | SAT Sensor"

**Result**:

- Zone "Floor 2" created (if new)
- Equipment "VAV-2-01" created with VAV Reheat template
- Supply air temp sensor linked to BACnet AI:1
- Node badge shows equipment + sensor role

### Scenario 2: Adding to Existing Equipment

**Context**: Equipment "VAV-2-01" already exists, user maps another point "VAV-2-01_SAF" (supply air flow)

**Flow**:

1. User drags "VAV-2-01_SAF" onto canvas
2. User clicks "Map to 223P"
3. Popup opens with pre-filled selections:

```
╔═══════════════════════════════════════════════════════╗
║ Map BACnet Point to ASHRAE 223P                      ║
╠═══════════════════════════════════════════════════════╣
║ BACnet Information (Read-Only)                       ║
║ ─────────────────────────────────────────────────────║
║ Name: VAV-2-01_SAF                                    ║
║ Device: 123 | Type: analogInput | Instance: 2        ║
║ Units: cubicFeetPerMinute | Value: 450 CFM           ║
╠═══════════════════════════════════════════════════════╣
║ Zone                                                  ║
║ [Floor 2                        ▼] ✓ (existing)      ║
║                                                       ║
║ Equipment                                             ║
║ [VAV-2-01                       ▼] ✓ (existing)      ║
║   Type: VAV Reheat Unit                              ║
║   Points: 1 mapped (SAT Sensor)                      ║
║                                                       ║
║ This BACnet point represents:                        ║
║ [Supply Air Flow Sensor         ▼] (AI: 96%)        ║
║                                                       ║
║ ┌─ Existing Equipment Points ──────────────────────┐ ║
║ │ ✓ Supply Air Temperature Sensor (mapped)         │ ║
║ │ ○ Supply Air Flow Sensor (mapping now)           │ ║
║ │ ○ Supply Air Pressure Sensor (unmapped)          │ ║
║ │ ○ Damper Position Command (unmapped)             │ ║
║ │ ○ Reheat Valve Command (unmapped)                │ ║
║ └──────────────────────────────────────────────────┘  ║
╠═══════════════════════════════════════════════════════╣
║ ✅ Ready to save                                     ║
║ Adding point to existing equipment VAV-2-01          ║
╠═══════════════════════════════════════════════════════╣
║                          [Cancel]  [Save Mapping]    ║
╚═══════════════════════════════════════════════════════╝
```

4. User clicks "Save Mapping"
5. Background: PUT to BuildingMOTIF adds sensor to existing equipment
6. Node updates with 223P badge: "VAV-2-01 | SAF Sensor"

**Result**:

- Existing equipment "VAV-2-01" now has 2 mapped sensors
- Progress indicator shows 2/5 points mapped

## Mock Data Structure (Phase 1)

### TypeScript Interfaces

```typescript
// Zone (Physical Space)
interface Zone223P {
  id: string; // "zone_floor_2" or IRI from BuildingMOTIF
  iri?: string; // "urn:building:zone:floor2" (Phase 2)
  name: string; // "Floor 2" or "Conference Room A"
  label: string; // rdfs:label value
  equipmentIds: string[]; // Equipment in this zone
  createdAt: string;
}

// Equipment Template
interface EquipmentTemplate223P {
  id: string; // "vav-reheat"
  name: string; // "VAV Reheat Unit"
  description: string; // "Variable air volume terminal with reheat coil"
  category: "equipment";
  medium: "Air" | "Water" | "Electricity"; // Auto-set by template
  sensors: TemplateSensor[]; // Sensors defined in template
  devices: TemplateDevice[]; // Devices defined in template
}

interface TemplateSensor {
  id: string; // "sup-air-temp-sensor"
  name: string; // "Supply Air Temperature Sensor"
  propertyType: string; // "air-temperature"
  objectType: "analogInput" | "binaryInput"; // Expected BACnet type
  units?: string; // Expected units (e.g., "degreesFahrenheit")
}

interface TemplateDevice {
  id: string; // "dmp" (damper), "rhc" (reheat coil)
  name: string; // "Damper", "Reheat Coil"
  deviceType: string; // "damper", "valve", "coil"
  actuators: TemplateActuator[];
  sensors: TemplateSensor[];
}

interface TemplateActuator {
  id: string; // "damper-position-command"
  name: string; // "Damper Position Command"
  propertyType: string; // "damper-command"
  objectType: "analogOutput" | "binaryOutput";
  units?: string; // "percent"
}

// Equipment Instance
interface Equipment223P {
  id: string; // "eq_vav_2_01" or IRI from BuildingMOTIF
  iri?: string; // "urn:building:equipment:vav-2-01" (Phase 2)
  zoneId: string; // Parent zone
  name: string; // "VAV-2-01" (user-provided)
  label: string; // rdfs:label value
  templateId: string; // "vav-reheat"
  templateName: string; // "VAV Reheat Unit"
  medium: string; // "Air" (from template)
  mappedPoints: Point223P[]; // BACnet points mapped to template sensors
  createdAt: string;
  validationStatus: "valid" | "warning" | "error";
}

// Point Mapping
interface Point223P {
  id: string; // "point_sat_123_1" or IRI from BuildingMOTIF
  iri?: string; // "urn:building:sensor:vav-2-01-sat" (Phase 2)
  bacnetNodeId: string; // Reference to canvas node
  equipmentId: string; // Parent equipment
  templateSensorId: string; // "sup-air-temp-sensor" (from template)
  sensorName: string; // "Supply Air Temperature Sensor"
  label: string; // rdfs:label: "VAV-2-01 Supply Air Temperature Sensor"
  bacnetReference: BACnetReference;
  createdAt: string;
}

interface BACnetReference {
  deviceId: number; // 123
  objectType: string; // "analogInput"
  objectInstance: number; // 1
  objectName: string; // "VAV-2-01_SAT"
  units?: string; // "degreesFahrenheit"
  description?: string; // "Supply air temperature for VAV 2-01"
}

// AI Suggestion
interface MappingSuggestion {
  zoneId?: string;
  zoneName?: string;
  equipmentId?: string; // If existing equipment
  equipmentName?: string;
  equipmentTemplate?: string; // If creating new
  templateSensorId: string;
  confidence: number; // 0-100
  reasoning: string; // AI explanation
}
```

## AI Integration (Phase 1 - Mock)

For Phase 1, create mock AI service that uses rule-based logic:

```typescript
// apps/designer/src/services/ashrae-223p-mapping-ai.ts

export interface MappingSuggestion {
  equipmentTemplate: string;
  deviceType: string;
  propertyType: string;
  propertyRole: string;
  units: string;
  confidence: number; // 0-100
  reasoning: string;
}

export function suggestMapping(bacnetNode: BacnetNodeData): MappingSuggestion {
  const objectName = bacnetNode.name.toLowerCase();
  const objectType = bacnetNode.objectType;
  const units = bacnetNode.discoveredProperties.units;

  // Equipment template from name
  let equipmentTemplate = "vav-reheat"; // default
  let confidence = 70;

  if (objectName.includes("ahu") || objectName.includes("mau")) {
    equipmentTemplate = "makeup-air-unit";
    confidence = 90;
  } else if (objectName.includes("vav")) {
    equipmentTemplate = "vav-reheat";
    confidence = 95;
  } else if (objectName.includes("exhaust") || objectName.includes("eau")) {
    equipmentTemplate = "exhaust-air-unit";
    confidence = 90;
  } else if (objectName.includes("chw")) {
    equipmentTemplate = "chilled-water-system";
    confidence = 85;
  } else if (objectName.includes("hw")) {
    equipmentTemplate = "hot-water-system";
    confidence = 85;
  }

  // Device type from object type + name
  let deviceType = "sensor";
  if (objectType === "analogOutput" || objectType === "binaryOutput") {
    if (objectName.includes("damper") || objectName.includes("dmp")) {
      deviceType = "damper";
    } else if (objectName.includes("valve") || objectName.includes("vlv")) {
      deviceType = "valve";
    } else if (objectName.includes("fan")) {
      deviceType = "fan";
    }
  }

  // Property type from units + name
  let propertyType = "air-temperature";
  if (units === "degreesFahrenheit" || units === "degreesCelsius") {
    propertyType = objectName.includes("water")
      ? "water-temperature"
      : "air-temperature";
  } else if (units === "pascals") {
    propertyType = objectName.includes("diff")
      ? "differential-pressure"
      : "static-pressure";
  } else if (units === "percentRelativeHumidity") {
    propertyType = "relative-humidity";
  } else if (units === "cubicFeetPerMinute") {
    propertyType = "air-flow";
  } else if (units === "percent" && deviceType === "damper") {
    propertyType = "damper-command";
  }

  // Property role from name
  const propertyRole = extractRole(objectName);

  return {
    equipmentTemplate,
    deviceType,
    propertyType,
    propertyRole,
    units: mapUnits(units),
    confidence,
    reasoning: `Based on object name "${bacnetNode.name}", type "${objectType}", and units "${units}"`,
  };
}

function extractRole(objectName: string): string {
  const name = objectName.toLowerCase();

  if (name.includes("sat") || name.includes("supply")) return "Supply Air";
  if (name.includes("rat") || name.includes("return")) return "Return Air";
  if (name.includes("zone") || name.includes("zn")) return "Zone";
  if (name.includes("oa") || name.includes("outside")) return "Outside Air";
  if (name.includes("discharge") || name.includes("disch")) return "Discharge";
  if (name.includes("inlet")) return "Inlet";
  if (name.includes("outlet")) return "Outlet";

  return "Unknown";
}

function mapUnits(bacnetUnits: string | undefined): string {
  if (!bacnetUnits) return "dimensionless";

  const unitMap: Record<string, string> = {
    degreesFahrenheit: "Fahrenheit",
    degreesCelsius: "Celsius",
    pascals: "Pascals",
    percent: "Percent",
    percentRelativeHumidity: "Percent",
    cubicFeetPerMinute: "CFM",
    gallonsPerMinute: "GPM",
    kilowatts: "Kilowatts",
    kilowattHours: "KilowattHours",
  };

  return unitMap[bacnetUnits] || bacnetUnits;
}

// Batch analysis for multiple points
export function suggestBatchMapping(bacnetNodes: BacnetNodeData[]): {
  equipment: {
    name: string;
    templateId: string;
    templateName: string;
    points: Array<{ nodeId: string; suggestion: MappingSuggestion }>;
  }[];
  confidence: number;
} {
  // Group by equipment identifier (e.g., "VAV-2-01")
  const groups = groupByEquipmentName(bacnetNodes);

  const equipment = groups.map((group) => {
    const suggestions = group.nodes.map((node) => ({
      nodeId: node.id,
      suggestion: suggestMapping(node),
    }));

    // Use most common equipment template
    const templateCounts = new Map<string, number>();
    suggestions.forEach((s) => {
      templateCounts.set(
        s.suggestion.equipmentTemplate,
        (templateCounts.get(s.suggestion.equipmentTemplate) || 0) + 1,
      );
    });

    const templateId = Array.from(templateCounts.entries()).sort(
      (a, b) => b[1] - a[1],
    )[0][0];

    return {
      name: group.name,
      templateId,
      templateName: getTemplateName(templateId),
      points: suggestions,
    };
  });

  // Calculate overall confidence
  const avgConfidence =
    equipment.reduce((sum, eq) => {
      const eqConfidence =
        eq.points.reduce((s, p) => s + p.suggestion.confidence, 0) /
        eq.points.length;
      return sum + eqConfidence;
    }, 0) / equipment.length;

  return { equipment, confidence: Math.round(avgConfidence) };
}

function groupByEquipmentName(
  nodes: BacnetNodeData[],
): Array<{ name: string; nodes: BacnetNodeData[] }> {
  const groups = new Map<string, BacnetNodeData[]>();

  nodes.forEach((node) => {
    // Extract equipment name (e.g., "VAV-2-01" from "VAV-2-01_SAT")
    const match = node.name.match(/^([A-Z]+-\d+-\d+)/i);
    const equipmentName = match ? match[1] : node.name;

    if (!groups.has(equipmentName)) {
      groups.set(equipmentName, []);
    }
    groups.get(equipmentName)!.push(node);
  });

  return Array.from(groups.entries()).map(([name, nodes]) => ({ name, nodes }));
}

function getTemplateName(templateId: string): string {
  const names: Record<string, string> = {
    "vav-reheat": "VAV Reheat Unit",
    "makeup-air-unit": "Makeup Air Unit",
    "lab-vav-reheat": "Lab VAV Reheat Unit",
    "exhaust-air-unit": "Exhaust Air Unit",
    "chilled-water-system": "Chilled Water System",
    "hot-water-system": "Hot Water System",
    "process-chilled-water-system": "Process Chilled Water System",
    "heat-recovery-system": "Heat Recovery System",
  };
  return names[templateId] || templateId;
}
```

## BuildingMOTIF Integration (Phase 2 Preview)

While Phase 1 uses mock data, here's how Phase 2 will integrate with BuildingMOTIF's Python API:

### API Request Flow

**Create Zone + Equipment + Point**:

```typescript
// Designer sends JSON to BuildingMOTIF FastAPI
const request = {
  zone: {
    name: "Floor 2",
    type: "hvac-space",
  },
  equipment: {
    name: "VAV-2-01",
    template: "vav-reheat",
    zone_name: "Floor 2",
  },
  point_mapping: {
    equipment_name: "VAV-2-01",
    template_sensor: "sup-air-temp-sensor",
    bacnet_reference: {
      device_id: 123,
      object_type: "analogInput",
      object_instance: 1,
      object_name: "VAV-2-01_SAT",
      units: "degreesFahrenheit",
    },
  },
};

// POST /api/v1/mappings
const response = await fetch("/api/v1/mappings", {
  method: "POST",
  body: JSON.stringify(request),
});
```

**BuildingMOTIF Python Backend**:

```python
# FastAPI endpoint
@app.post("/api/v1/mappings")
async def create_mapping(request: MappingRequest):
    # Initialize BuildingMOTIF
    bm = BuildingMOTIF("sqlite://")
    lib = Library.load(ontology=ASHRAE223)
    builder = GraphBuilder(bm)

    # Create zone if not exists
    zone = builder["hvac-space"](name=request.zone.name)

    # Create equipment using template
    equipment = builder[request.equipment.template](
        name=request.equipment.name
    )

    # Link equipment to zone
    zone.add_equipment(equipment)

    # Map BACnet point to template sensor
    sensor_key = request.point_mapping.template_sensor
    bacnet_ref = request.point_mapping.bacnet_reference

    # Set sensor external reference
    equipment[sensor_key] = f"{bacnet_ref.device_id}:{bacnet_ref.object_type}:{bacnet_ref.object_instance}"

    # Add BACnet metadata as RDF properties
    sensor = equipment.get_sensor(sensor_key)
    sensor.add_property("s223:hasExternalReference", {
        "device_id": bacnet_ref.device_id,
        "object_type": bacnet_ref.object_type,
        "object_instance": bacnet_ref.object_instance,
        "object_name": bacnet_ref.object_name
    })

    # Validate with SHACL
    validation = validate_223p(equipment)

    # Return IRIs and validation results
    return {
        "zone_iri": zone.iri,
        "equipment_iri": equipment.iri,
        "sensor_iri": sensor.iri,
        "zone_label": zone.label,
        "equipment_label": equipment.label,
        "sensor_label": sensor.label,
        "validation": validation
    }
```

**Designer Receives Response**:

```typescript
const response = {
  zone_iri: "urn:building:zone:floor2",
  equipment_iri: "urn:building:equipment:vav-2-01",
  sensor_iri: "urn:building:sensor:vav-2-01-sat",
  zone_label: "Floor 2",
  equipment_label: "VAV-2-01",
  sensor_label: "VAV-2-01 Supply Air Temperature Sensor",
  validation: {
    valid: true,
    errors: []
  }
}

// Store in Zustand with both IRI and display name
use223pStore.setState({
  zones: [{
    id: response.zone_iri,
    iri: response.zone_iri,
    name: "Floor 2",
    label: response.zone_label,
    equipmentIds: [response.equipment_iri]
  }],
  equipment: [{
    id: response.equipment_iri,
    iri: response.equipment_iri,
    zoneId: response.zone_iri,
    name: "VAV-2-01",
    label: response.equipment_label,
    templateId: "vav-reheat",
    mappedPoints: [response.sensor_iri]
  }],
  points: [{
    id: response.sensor_iri,
    iri: response.sensor_iri,
    equipmentId: response.equipment_iri,
    label: response.sensor_label,
    templateSensorId: "sup-air-temp-sensor",
    bacnetReference: { ... }
  }]
})

// Display to user: "VAV-2-01 | SAT Sensor" (extracted from labels)
```

### IRI Handling Pattern

**Storage**: Always store the full IRI as the ID
**Display**: Extract human-readable part for UI

```typescript
function extractDisplayName(iri: string, fallback: string): string {
  // "urn:building:equipment:vav-2-01" → "VAV-2-01"
  const parts = iri.split(':')
  const lastPart = parts[parts.length - 1]
  return lastPart.replace(/-/g, ' ').toUpperCase() || fallback
}

function extractFromLabel(label: string): string {
  // "VAV-2-01 Supply Air Temperature Sensor" → "SAT Sensor"
  // Use rdfs:label which is human-friendly
  return label
}

// Usage in UI
<Badge>
  {extractFromLabel(point.label)} {/* "SAT Sensor" */}
</Badge>
```

## Component Structure

```
apps/designer/src/
├── components/
│   ├── modals/
│   │   └── ashrae-223p-mapping-modal.tsx        # Main popup
│   ├── forms/
│   │   ├── zone-selector.tsx                    # Zone dropdown
│   │   ├── equipment-selector.tsx               # Equipment dropdown
│   │   ├── template-sensor-selector.tsx         # Template sensor dropdown
│   │   └── validation-status-display.tsx        # Status indicator
│   └── nodes/
│       └── bacnet-node-ui.tsx                   # Add "Map to 223P" button
├── services/
│   ├── buildingmotif-templates.ts               # Mock template service
│   ├── ashrae-223p-mapping-ai.ts                # Mock AI suggestions
│   └── ashrae-223p-validator.ts                 # Validation logic
├── store/
│   └── use-223p-store.ts                        # Zustand store for 223P data
└── types/
    └── ashrae-223p.ts                           # TypeScript types
```

## Implementation Tasks

### Task 1: Create Type Definitions

```bash
# Create types file
touch apps/designer/src/types/ashrae-223p.ts
```

**Contents**: All TypeScript interfaces (BuildingMotifTemplate, PropertyType, MappingSuggestion, Equipment223P, Point223P)

### Task 2: Create Mock Services

```bash
# Create services
touch apps/designer/src/services/buildingmotif-templates.ts
touch apps/designer/src/services/ashrae-223p-mapping-ai.ts
touch apps/designer/src/services/ashrae-223p-validator.ts
```

**Templates Service**: Return hardcoded BuildingMOTIF templates
**AI Service**: Rule-based suggestion logic
**Validator**: Check valid combinations

### Task 3: Create Zustand Store

```bash
touch apps/designer/src/store/use-223p-store.ts
```

**State**:

- `equipment: Equipment223P[]`
- `points: Point223P[]`
- Actions for add/update/delete

### Task 4: Create UI Components

```bash
# Create form components
mkdir -p apps/designer/src/components/forms
touch apps/designer/src/components/forms/equipment-selector.tsx
touch apps/designer/src/components/forms/device-type-selector.tsx
touch apps/designer/src/components/forms/property-selector.tsx
touch apps/designer/src/components/forms/validation-status-display.tsx
```

**Equipment Selector**: Dropdown with existing equipment + "Create New"
**Device Type Selector**: 15 device types from BuildingMOTIF
**Property Selector**: 29 properties, filtered by device type
**Validation Display**: Status indicator with messages

### Task 5: Create Main Modal

```bash
touch apps/designer/src/components/modals/ashrae-223p-mapping-modal.tsx
```

**Features**:

- Pre-fill all fields from BACnet data
- Call AI suggestion service
- Show confidence scores
- Real-time validation
- Save to Zustand store

### Task 6: Integrate with BACnet Node

**Modify**: `apps/designer/src/components/nodes/bacnet-node-ui.tsx`

**Add**:

- "Map to 223P" button
- 223P badge showing equipment assignment
- Open modal on button click

### Task 7: Write Tests

```bash
# Test files
touch apps/designer/src/services/__tests__/ashrae-223p-mapping-ai.test.ts
touch apps/designer/src/components/modals/__tests__/ashrae-223p-mapping-modal.test.tsx
```

**Test Coverage**:

- AI suggestion accuracy
- Validation rules
- Form pre-fill logic
- Modal interactions

## Success Criteria

- ✅ Popup opens when user clicks "Map to 223P" on BACnet node
- ✅ All fields pre-filled with intelligent suggestions
- ✅ BuildingMOTIF template names used consistently (8 equipment, 15 devices, 29 properties)
- ✅ Validation catches invalid combinations (Actuator with AI, Sensor with AO, etc.)
- ✅ User can create new equipment or add to existing
- ✅ Mock AI provides reasonable suggestions (70%+ confidence)
- ✅ Batch mapping groups points by equipment
- ✅ 223P data stored in Zustand store (local state, no backend)
- ✅ All components tested (unit + integration tests)
- ✅ No backend dependencies (Phase 1 uses mock data only)

## Next Steps (Phase 2)

- Replace mock templates with BuildingMOTIF API
- Replace rule-based AI with actual LLM integration
- Add SHACL validation via BuildingMOTIF backend
- Store equipment models in RDF graph (BuildingMOTIF database)
- Generate OpenAPI client from BuildingMOTIF FastAPI

## References

- [BuildingMOTIF NREL Templates](https://github.com/NREL/BuildingMOTIF/tree/develop/libraries/ashrae/223p/nrel-templates)
- [BuildingMOTIF Documentation](https://buildingmotif.readthedocs.io/)
- [ASHRAE 223P Overview](https://docs.open223.info/explanation/223_overview.html)
- [BuildingMOTIF Model Creation Tutorial](https://docs.open223.info/tutorials/model_creation_buildingmotif.html)
