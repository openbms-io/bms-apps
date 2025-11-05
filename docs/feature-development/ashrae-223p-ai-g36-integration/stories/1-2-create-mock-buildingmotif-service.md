# Story 1.2: Create Mock BuildingMOTIF Service

**Epic:** Epic 1 - 223P Mapping UI with Mock DTOs
**Status:** done
**Created:** 2025-11-02
**Completed:** 2025-11-02
**Complexity:** 2 (Small)
**Estimated Hours:** 2-3 hours

---

## User Story

**As a** developer,
**I want** a mock BuildingMOTIF service implementing the DTO interfaces,
**So that** UI components can be built without backend dependency.

---

## Acceptance Criteria

Reference: Tech Spec AC-2

### 1. ✅ MockBuildingMOTIFService Class Implements Interface

- Create `IBuildingMOTIFService` interface defining service contract
- Implement `MockBuildingMOTIFService` class
- Service returns Promises to match async API behavior (prepares for HTTP calls in Epic 3)

### 2. ✅ getTemplates() Returns Equipment Types

Returns 8 equipment types from NREL BuildingMOTIF systems.yml:

1. Makeup Air Unit
2. VAV Reheat Terminal Unit
3. Lab VAV Reheat Terminal Unit
4. Chilled Water System
5. Hot Water System
6. Process Chilled Water System
7. Exhaust Air Unit
8. Heat Recovery System

### 3. ✅ getDeviceTypes() Returns Device Types

Returns 18 device types from NREL BuildingMOTIF devices.yml:

**Air-side equipment:**

- Damper, Fan, Exhaust Fan, Filter

**Coils:**

- Chilled Water Coil, Hot Water Coil, Heat Recovery Coil

**Water-side equipment:**

- Chilled Water Valve, Hot Water Valve
- Chilled Water Pump, Hot Water Pump

**Sensors & monitoring:**

- Sensor

**Other equipment:**

- Evaporative Cooler, Heat Exchanger
- Fan Coil Unit, Unit Heater, Tank, Domestic Water Heater

### 4. ✅ getObservableProperties() Returns Properties

Returns 25+ properties from NREL BuildingMOTIF properties.yml:

**Quantifiable - Pressure:**

- static-pressure, low-static-pressure, water-static-pressure
- differential-pressure, water-differential-pressure

**Quantifiable - Temperature:**

- air-temperature, water-temperature

**Quantifiable - Flow:**

- air-flow, water-flow

**Quantifiable - Environmental:**

- relative-humidity

**Quantifiable - VFD Properties:**

- vfd-current, vfd-frequency, vfd-voltage, vfd-power, vfd-energy

**Quantifiable - BTU Meter:**

- BTU-Meter-energy, BTU-Meter-energy-rate
- BTU-Meter-water-flow, BTU-Meter-water-volume

**Enumerated - Status Properties:**

- run-status, flow-status, vfd-fault
- condensate-overflow, occupancy-override

### 5. ✅ Mock Data Loaded from JSON Files

- Mock data stored in `/domains/223p/mocks/buildingmotif-templates.json`
- JSON structure matches NREL BuildingMOTIF template format
- Service loads data synchronously (no network calls)

### 6. ✅ Service Returns Promises

- All methods return `Promise<T>` to match async API behavior
- Prepares for Epic 3 HTTP calls (easy swap to real API)
- Use `Promise.resolve()` for synchronous mock data

---

## Verification Checklist

- [ ] `IBuildingMOTIFService` interface defined
- [ ] `MockBuildingMOTIFService` implements interface
- [ ] Mock JSON file contains all templates (8 systems, 18 devices, 25+ properties)
- [ ] `getTemplates()` returns 8 equipment types
- [ ] `getDeviceTypes()` returns 18 device types
- [ ] `getObservableProperties()` returns 25+ properties
- [ ] All methods return Promises
- [ ] TypeScript compiles without errors
- [ ] Mock data matches NREL BuildingMOTIF structure

---

## Implementation Guidance

### File Structure

```
apps/designer/src/domains/223p/
├── services/
│   ├── buildingmotif.service.interface.ts  # IBuildingMOTIFService interface
│   └── mock-buildingmotif.service.ts       # MockBuildingMOTIFService implementation
└── mocks/
    └── buildingmotif-templates.json        # Template data
```

### Interface Definition

```typescript
// services/buildingmotif.service.interface.ts

import type { SystemType, DeviceType, ObservableProperty } from "../schemas";

/**
 * BuildingMOTIF Service Interface
 *
 * Defines contract for BuildingMOTIF API interaction.
 * Epic 1: Implemented by MockBuildingMOTIFService
 * Epic 3: Implemented by ApiBuildingMOTIFService (real HTTP calls)
 */
export interface IBuildingMOTIFService {
  /**
   * Get all available equipment types (systems)
   * @returns Array of system types from NREL templates
   */
  getTemplates(): Promise<SystemType[]>;

  /**
   * Get all available device types
   * @returns Array of device types from NREL templates
   */
  getDeviceTypes(): Promise<DeviceType[]>;

  /**
   * Get all available observable properties
   * @returns Array of observable properties from NREL templates
   */
  getObservableProperties(): Promise<ObservableProperty[]>;
}
```

### Mock Data Structure

```json
{
  "version": "0.10.0",
  "source": "NREL BuildingMOTIF",
  "templates": {
    "systems": [
      "Makeup Air Unit",
      "VAV Reheat Terminal Unit",
      "Lab VAV Reheat Terminal Unit",
      "Chilled Water System",
      "Hot Water System",
      "Process Chilled Water System",
      "Exhaust Air Unit",
      "Heat Recovery System"
    ],
    "devices": [
      "Damper",
      "Fan",
      "Exhaust Fan",
      "Filter",
      "Chilled Water Coil",
      "Hot Water Coil",
      "Heat Recovery Coil",
      "Chilled Water Valve",
      "Hot Water Valve",
      "Chilled Water Pump",
      "Hot Water Pump",
      "Sensor",
      "Evaporative Cooler",
      "Heat Exchanger",
      "Fan Coil Unit",
      "Unit Heater",
      "Tank",
      "Domestic Water Heater"
    ],
    "properties": {
      "quantifiable": [
        "static-pressure",
        "low-static-pressure",
        "water-static-pressure",
        "differential-pressure",
        "water-differential-pressure",
        "air-temperature",
        "water-temperature",
        "air-flow",
        "water-flow",
        "relative-humidity",
        "vfd-current",
        "vfd-frequency",
        "vfd-voltage",
        "vfd-power",
        "vfd-energy",
        "BTU-Meter-energy",
        "BTU-Meter-energy-rate",
        "BTU-Meter-water-flow",
        "BTU-Meter-water-volume"
      ],
      "enumerated": [
        "run-status",
        "flow-status",
        "vfd-fault",
        "condensate-overflow",
        "occupancy-override"
      ]
    }
  }
}
```

### Mock Service Implementation Pattern

```typescript
// services/mock-buildingmotif.service.ts

import type { IBuildingMOTIFService } from "./buildingmotif.service.interface";
import type { SystemType, DeviceType, ObservableProperty } from "../schemas";
import mockData from "../mocks/buildingmotif-templates.json";

/**
 * Mock BuildingMOTIF Service
 *
 * Returns static template data from JSON file.
 * No network calls - synchronous data wrapped in Promises.
 *
 * Epic 1: Use this service
 * Epic 3: Swap to ApiBuildingMOTIFService (zero UI changes)
 */
export class MockBuildingMOTIFService implements IBuildingMOTIFService {
  async getTemplates(): Promise<SystemType[]> {
    // Return mock data synchronously wrapped in Promise
    return Promise.resolve(mockData.templates.systems as SystemType[]);
  }

  async getDeviceTypes(): Promise<DeviceType[]> {
    return Promise.resolve(mockData.templates.devices as DeviceType[]);
  }

  async getObservableProperties(): Promise<ObservableProperty[]> {
    const { quantifiable, enumerated } = mockData.templates.properties;
    return Promise.resolve([
      ...quantifiable,
      ...enumerated,
    ] as ObservableProperty[]);
  }
}

// Export singleton instance
export const mockBuildingMOTIFService = new MockBuildingMOTIFService();
```

---

## Technical Notes

### Why Interface Pattern?

**Interface Segregation Principle:**

- UI components depend on `IBuildingMOTIFService` interface, not implementation
- Epic 3 swaps `MockBuildingMOTIFService` → `ApiBuildingMOTIFService` with zero UI changes
- Custom hooks handle the service selection (Story 1.9)

**Example:**

```typescript
// Epic 1: Use mock
const service: IBuildingMOTIFService = new MockBuildingMOTIFService();

// Epic 3: Use real API (same interface!)
const service: IBuildingMOTIFService = new ApiBuildingMOTIFService();
```

### Why Promises for Sync Data?

**Prepares for Epic 3:**

- Real API calls are async (HTTP fetch)
- Mock returns Promises to match async pattern
- No UI component changes needed in Epic 3

**Pattern:**

```typescript
// Epic 1: Sync data wrapped in Promise
async getTemplates(): Promise<SystemType[]> {
  return Promise.resolve(mockData.systems);
}

// Epic 3: Real HTTP call (same signature!)
async getTemplates(): Promise<SystemType[]> {
  const response = await fetch('/api/buildingmotif/templates');
  return response.json();
}
```

### NREL BuildingMOTIF Templates

Mock data based on:

- **systems.yml**: 8 equipment types
- **devices.yml**: 18 device types
- **properties.yml**: 25+ observable properties

Source: https://github.com/NREL/BuildingMOTIF (v0.10.0)

---

## Prerequisites

**Story 1.1** ✅ Complete

- Requires: `SystemType`, `DeviceType`, `ObservableProperty` types

---

## Dependencies

**Stories that depend on this:**

- Story 1.3: AI Suggestion Mock Engine (needs template data)
- Story 1.4: 223P Mapping Popup Modal (needs service for dropdowns)
- Story 1.5: Equipment Type Dropdown (needs getTemplates())

---

## Definition of Done

- [ ] `IBuildingMOTIFService` interface created
- [ ] `MockBuildingMOTIFService` class implements interface
- [ ] Mock JSON file with all template data created
- [ ] All 3 methods implemented (getTemplates, getDeviceTypes, getObservableProperties)
- [ ] TypeScript compiles without errors
- [ ] Service can be imported and used
- [ ] Code follows project conventions (no unnecessary comments)
- [ ] Files committed to git with descriptive commit message

---

## References

- **Tech Spec:** AC-2 (lines 2456-2495)
- **Story 1.1:** DTO interfaces and types
- **NREL BuildingMOTIF:** https://github.com/NREL/BuildingMOTIF
- **Architecture:** Service interface pattern (Tech Spec lines 494-515)
