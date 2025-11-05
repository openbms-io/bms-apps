# Story 1.1: Define BuildingMOTIF DTO Interfaces

**Epic:** Epic 1 - 223P Mapping UI with Mock DTOs
**Status:** done
**Created:** 2025-11-02
**Completed:** 2025-11-02
**Complexity:** 2 (Small)
**Estimated Hours:** 2-3 hours
**Actual Hours:** 1 hour

---

## User Story

**As a** developer,
**I want** TypeScript interfaces for all BuildingMOTIF DTOs,
**So that** mock and real services share identical contracts.

---

## Acceptance Criteria

Reference: Tech Spec AC-1

### 1. ✅ DTO Interfaces Defined

- `Equipment223PDTO` interface with:

  - `equipmentType`: SystemType
  - `spaceId`: string (optional) - Space URN
  - `deviceType`: DeviceType
  - `observableProperty`: ObservableProperty
  - `propertyType`: 'quantifiable' | 'enumerated'
  - `externalReference`: BACnetExternalReferenceDTO
  - `schemaVersion`: '223p-2023'

- `SpaceDTO` interface with:

  - `id`: string (URN format: "urn:bms:PhysicalSpace:space-{uuid}")
  - `rdfsLabel`: string (display name)
  - `spaceType`: SpaceType ('PhysicalSpace' | 'DomainSpace')
  - `pointIds`: string[]
  - `createdAt`: Date

- `BACnetExternalReferenceDTO` interface with:

  - `deviceIdentifier`: string (optional) - "device,{device_id}"
  - `deviceName`: string (optional)
  - `objectIdentifier`: string (optional) - "{objectType},{objectId}"
  - `objectName`: string (optional)
  - `propertyIdentifier`: string (optional) - Default: "present-value"
  - `propertyArrayIndex`: number (optional)
  - `priorityForWriting`: number (optional, 1-16)

- `ValidationResultDTO` interface with:

  - `isValid`: boolean
  - `errors`: ValidationErrorDTO[]
  - `warnings`: ValidationErrorDTO[]

- `ValidationErrorDTO` interface with:
  - `field`: string
  - `message`: string
  - `code`: ValidationErrorCode
  - `expectedType`: string (optional)
  - `actualType`: string (optional)

### 2. ✅ ViewModel Interfaces Defined (UI layer - stable)

- `EquipmentViewModel` with flat structure for UI components
- `SpaceViewModel` for combo box display
- `AIRecommendationViewModel` for AI suggestions

### 3. ✅ Zod Schemas Created

All DTOs must have corresponding Zod schemas for runtime validation:

- `Equipment223PDTOSchema` with runtime validation
- `SpaceDTOSchema` with URN format validation
- `BACnetExternalReferenceDTOSchema` with all optional fields
- Enum schemas:
  - `SystemTypeSchema` (8 equipment types)
  - `DeviceTypeSchema` (18 device types)
  - `ObservablePropertySchema` (25+ properties)
  - `SpaceTypeSchema` (2 types)
  - `ValidationErrorCodeSchema`

### 4. ✅ Schema Version Management

- All DTOs include `schemaVersion: '223p-2023'` field
- Enables future migration tracking when 223P spec evolves

### 5. ✅ JSDoc Documentation

- All interfaces documented with:
  - Purpose and usage
  - Example values
  - Epic 3 migration notes
- DTOs marked as "flexible for Epic 3 refinement"
- ViewModels marked as "stable interface"

---

## Verification Checklist

- [ ] All DTO interfaces compile without TypeScript errors
- [ ] Zod schemas validate valid DTOs successfully
- [ ] Zod schemas reject invalid DTOs with clear error messages
- [ ] JSDoc comments visible in IDE autocomplete
- [ ] TypeScript types derived from Zod schemas using `z.infer`
- [ ] No duplicate type definitions (Zod schemas are single source of truth)

---

## Implementation Guidance

### File Structure

```
apps/designer/src/domains/223p/schemas/
├── dto.schemas.ts          # Main DTO schemas (Equipment, Space, Validation)
├── enum.schemas.ts         # Enum schemas (SystemType, DeviceType, etc.)
└── view-models.ts          # ViewModel TypeScript interfaces (UI-only)
```

### Architecture Pattern

**Zod-First Approach:**

1. Define Zod schema (single source of truth)
2. Derive TypeScript type using `z.infer<typeof Schema>`
3. Never manually maintain separate type definitions

**Example:**

```typescript
// ✅ CORRECT: Zod schema first, then derive type
export const Equipment223PDTOSchema = z.object({
  equipmentType: SystemTypeSchema,
  spaceId: z.string().optional(),
  deviceType: DeviceTypeSchema,
  observableProperty: ObservablePropertySchema,
  propertyType: z.enum(["quantifiable", "enumerated"]),
  externalReference: BACnetExternalReferenceDTOSchema,
  schemaVersion: z.literal("223p-2023"),
});

export type Equipment223PDTO = z.infer<typeof Equipment223PDTOSchema>;

// ❌ WRONG: Don't maintain separate interface
// interface Equipment223PDTO { ... }  // Types will drift!
```

### Enum Schemas (Reference from Tech Spec)

**SystemType (8 equipment types):**

```typescript
export const SystemTypeSchema = z.enum([
  "Makeup Air Unit",
  "VAV Reheat Terminal Unit",
  "Lab VAV Reheat Terminal Unit",
  "Chilled Water System",
  "Hot Water System",
  "Process Chilled Water System",
  "Exhaust Air Unit",
  "Heat Recovery System",
]);
```

**DeviceType (18 device types):**

```typescript
export const DeviceTypeSchema = z.enum([
  // Air-side equipment
  "Damper",
  "Fan",
  "Exhaust Fan",
  "Filter",
  // Coils
  "Chilled Water Coil",
  "Hot Water Coil",
  "Heat Recovery Coil",
  // Water-side equipment
  "Chilled Water Valve",
  "Hot Water Valve",
  "Chilled Water Pump",
  "Hot Water Pump",
  // Sensors & monitoring
  "Sensor",
  // Other equipment
  "Evaporative Cooler",
  "Heat Exchanger",
  "Fan Coil Unit",
  "Unit Heater",
  "Tank",
  "Domestic Water Heater",
]);
```

**ObservableProperty (25+ properties):**

```typescript
export const ObservablePropertySchema = z.enum([
  // Quantifiable - Pressure
  "static-pressure",
  "low-static-pressure",
  "water-static-pressure",
  "differential-pressure",
  "water-differential-pressure",
  // Quantifiable - Temperature
  "air-temperature",
  "water-temperature",
  // Quantifiable - Flow
  "air-flow",
  "water-flow",
  // Quantifiable - Environmental
  "relative-humidity",
  // Quantifiable - VFD Properties
  "vfd-current",
  "vfd-frequency",
  "vfd-voltage",
  "vfd-power",
  "vfd-energy",
  // Quantifiable - BTU Meter
  "BTU-Meter-energy",
  "BTU-Meter-energy-rate",
  "BTU-Meter-water-flow",
  "BTU-Meter-water-volume",
  // Enumerated - Status Properties
  "run-status",
  "flow-status",
  "vfd-fault",
  "condensate-overflow",
  "occupancy-override",
]);
```

**SpaceType (2 types):**

```typescript
export const SpaceTypeSchema = z.enum(["DomainSpace", "PhysicalSpace"]);
```

**ValidationErrorCode:**

```typescript
export const ValidationErrorCodeSchema = z.enum([
  "INCOMPATIBLE_BACNET_TYPE",
  "INVALID_PROPERTY_FOR_DEVICE",
  "MISSING_REQUIRED_FIELD",
  "SPACE_REQUIRED_FOR_SYSTEM",
]);
```

### ViewModel Interfaces (Stable - No Zod)

ViewModels are UI-only and don't need runtime validation. Use plain TypeScript interfaces:

```typescript
// apps/designer/src/domains/223p/schemas/view-models.ts

/**
 * Equipment ViewModel - Optimized for UI components
 * Stable interface - will NOT change in Epic 3
 */
export interface EquipmentViewModel {
  // Flattened structure for easy binding
  equipmentType: string;
  equipmentTypeLabel: string;
  spaceName?: string;
  spaceType?: string;
  deviceType: string;
  deviceTypeLabel: string;
  observableProperty: string;
  observablePropertyLabel: string;
  propertyType: "quantifiable" | "enumerated";

  // BACnet reference (flattened)
  bacnetDeviceName?: string;
  bacnetObjectName?: string;
  bacnetObjectType?: string;

  // Metadata
  hasValidation: boolean;
  schemaVersion: string;
}

/**
 * Space ViewModel - For combo box display
 */
export interface SpaceViewModel {
  id: string; // URN
  label: string; // Display name
  type: "PhysicalSpace" | "DomainSpace";
  pointCount: number; // Number of points using this space
}

/**
 * AI Recommendation ViewModel
 */
export interface AIRecommendationViewModel {
  equipmentType: string;
  equipmentTypeConfidence: number;
  spaceName?: string;
  spaceConfidence?: number;
  deviceType: string;
  deviceTypeConfidence: number;
  observableProperty: string;
  observablePropertyConfidence: number;
  overallConfidence: number;
  reasoning?: string;
}
```

---

## Technical Notes

### Why DTO/ViewModel Separation?

**DTOs (Data Transfer Objects):**

- Match API structure exactly
- Will change in Epic 3 when real BuildingMOTIF API is integrated
- Use Zod schemas for runtime validation
- Located in `domains/223p/schemas/dto.schemas.ts`

**ViewModels:**

- Optimized for UI component binding
- Flat structure (no nested objects)
- Will NOT change in Epic 3 (stable interface)
- Use plain TypeScript interfaces (no Zod)
- Located in `domains/223p/schemas/view-models.ts`

**Benefit:** Epic 3 API changes only affect mappers, not UI components.

### Epic 3 Migration Strategy

These DTOs are "best guess" based on ASHRAE 223P ontology. When Epic 3 integrates real BuildingMOTIF API:

1. **DTOs will change** based on actual API response structure
2. **Mappers will update** to transform new DTOs → existing ViewModels
3. **UI components unchanged** - they only consume ViewModels

Example of future change:

```typescript
// Epic 1: Flat structure (best guess)
export const Equipment223PDTOSchema = z.object({
  equipmentType: SystemTypeSchema,
  deviceType: DeviceTypeSchema,
  // ...
});

// Epic 3: May become nested graph (actual BuildingMOTIF response)
export const Equipment223PDTOSchema = z.object({
  uri: z.string(),
  rdfType: z.array(z.string()),
  hasDevice: z.array(DeviceDTOSchema),
  isLocationOf: z.array(z.string()),
  // ... actual RDF/JSON-LD structure
});
```

Mappers absorb this complexity, ViewModels stay flat and simple.

---

## Prerequisites

**None** - This is the first story in Epic 1.

---

## Dependencies

**Stories that depend on this:**

- Story 1.2: Create Mock BuildingMOTIF Service
- Story 1.3: AI Suggestion Mock Engine
- Story 1.7: SHACL Validation Mock
- Story 1.9: In-Memory State Management

---

## Definition of Done

- [ ] All DTO Zod schemas defined in `dto.schemas.ts`
- [ ] All enum Zod schemas defined in `enum.schemas.ts`
- [ ] All ViewModel interfaces defined in `view-models.ts`
- [ ] TypeScript compiles without errors
- [ ] All schemas have JSDoc documentation
- [ ] Zod validation tested manually (valid/invalid DTOs)
- [ ] Code follows project conventions (no comments unless explaining WHY)
- [ ] Files committed to git with descriptive commit message

---

## References

- **Tech Spec:** `/docs/feature-development/ashrae-223p-ai-g36-integration/tech-spec-epic-1.md` (AC-1, lines 2415-2454)
- **PRD:** FR001-FR008 requirements
- **Architecture:** DTO vs ViewModel layer (Tech Spec lines 63-108)
- **NREL BuildingMOTIF Templates:** https://github.com/NREL/BuildingMOTIF
