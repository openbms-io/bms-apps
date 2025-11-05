# Epic Technical Specification: 223P Mapping UI with Mock DTOs

Date: 2025-11-01
Author: Amol
Epic ID: 1
Status: Final

---

## Overview

This epic delivers the complete user experience for AI-assisted ASHRAE 223P semantic mapping, implemented entirely with mock services to validate the workflow integration hypothesis with BMS integrators before investing in backend infrastructure. The core value proposition is demonstrating that embedding semantic tagging into the existing BACnet point discovery workflow (proactive popup during drag-and-drop) reduces adoption friction enough to achieve the target 90% time reduction (5 minutes → 30 seconds per point).

The implementation focuses on 12 stories spanning DTO interfaces, mock BuildingMOTIF service, AI suggestion engine, 223P mapping popup with four dropdown selectors (Equipment Type, Space, Device Type, Observable Property), SHACL validation feedback, visual badge indicators, and in-memory state management. All components are built using shadcn/ui, React Flow, and Zustand, maintaining consistency with the existing Designer app architecture. No persistence layer is included - this is purely an in-memory demo optimized for LinkedIn showcase and alpha testing with 5+ integrators.

## Objectives and Scope

**In Scope:**

- Complete 223P mapping UI workflow (auto-popup, AI suggestions, manual override, skip)
- Mock BuildingMOTIF service with 8 equipment types, 15 device types, 25+ observable properties
- AI pattern matching engine achieving 85-95% confidence on common naming patterns
- Real-time SHACL validation feedback (BACnet object type compatibility)
- Visual indicators (badges) showing which points are semantically tagged
- In-memory state management using Zustand (session-only persistence)
- Search/filter capability within all dropdowns
- Keyboard accessibility and screen reader support
- UI polish and responsive design consistent with existing Designer app

**Out of Scope (Deferred to Later Epics):**

- Real BuildingMOTIF API integration (Epic 3)
- RDF graph storage and SHACL validation via backend (Epic 3)
- Project save/load functionality (Epic 5)
- G36 sequence integration (Epic 2, 4)
- Multi-browser compatibility (Chrome-only per NFR004)
- Advanced AI features (learning from corrections, custom templates)

## System Architecture Alignment

**Designer App Architecture:**

- Builds on existing Next.js 15.5 + React Flow 12.8 + Zustand stack
- Uses established patterns: shadcn/ui components, Tailwind CSS v4, TypeScript strict mode
- Integrates with current BACnet point discovery workflow (left panel → canvas drag-drop)
- Leverages existing Zustand store structure, adding new `mapping223p` slice
- No changes required to BMS IoT App or MQTT communication layer

**Mock Service Pattern:**

- Implements `IBuildingMOTIFService` interface that will be swapped for real API in Epic 3
- Mock data loaded from JSON files in `/mocks` directory (not database)
- Returns Promises to match async API behavior (prepares for HTTP calls)
- DTO interfaces defined with Zod schemas for runtime validation and type safety

**Type Safety Strategy:**

- TypeScript DTOs defined in Epic 1, will generate from Pydantic models in Epic 3
- Zod schemas provide runtime validation and export TypeScript types
- Interface segregation: UI components depend on service interface, not implementation

**Constraints:**

- Chrome browser only (per PRD NFR004)
- No database persistence (sessionStorage only)
- Mock AI uses pattern matching (not LLM) for deterministic testing
- Performance target: Popup open <100ms, AI response <500ms (mock synchronous)

## Architecture: DTO vs ViewModel Layer

**Key Design Decision**: Separate DTOs (API contract) from ViewModels (UI needs) to isolate Epic 3 API changes from UI components.

```
┌─────────────────────────────────────────────────────────────────┐
│ Epic 1: Mock with sessionStorage                                │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  sessionStorage  →  DTO  →  Custom Hook  →  ViewModel  →  UI    │
│  (best guess)      (flex)   (mapper)        (UI-optimized)       │
│                                ↓                                 │
│                         React Query Cache                        │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ Epic 3: Real BuildingMOTIF API                                   │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  BuildingMOTIF  →  DTO  →  Custom Hook  →  ViewModel  →  UI     │
│  REST API      (real)    (mapper)        (SAME)       (NO CHANGE)│
│                             ↓                                    │
│                      React Query Cache                           │
│                                                                  │
│  ONLY CHANGES: DTO structure + mapper logic in custom hooks     │
└─────────────────────────────────────────────────────────────────┘
```

**Layer Responsibilities:**

| Layer             | Purpose                                     | Changes in Epic 3                                  |
| ----------------- | ------------------------------------------- | -------------------------------------------------- |
| **DTO**           | Match BuildingMOTIF API structure exactly   | ✅ Will change (spike to determine real structure) |
| **Custom Hook**   | Fetch via React Query + map DTO → ViewModel | ✅ Update mapper logic only                        |
| **ViewModel**     | Flat structure optimized for UI components  | ❌ No changes (stable interface)                   |
| **UI Components** | Consume ViewModels only                     | ❌ No changes (isolated from API)                  |

**Benefits:**

- ✅ UI components never depend on API structure
- ✅ Epic 3 changes isolated to hooks/mappers
- ✅ Can spike BuildingMOTIF API without UI refactor
- ✅ Clean separation of concerns
- ✅ Easier testing (mock ViewModels, not DTOs)

**Epic 1 Strategy**: DTOs are "best guess" based on 223P ontology. Mappers are simple (mostly identity). Epic 3 will refine based on actual BuildingMOTIF API responses.

## Detailed Design

### AI Infrastructure (Shared Library)

AI capabilities are **cross-cutting concerns** that serve multiple domains (223P, G36, future FDD). Following the existing pattern for shared code (`lib/utils`, `lib/store`), AI is organized as a shared library rather than a domain.

**Why Shared Library?**

1. **Multi-Domain Usage**:

   - 223P: AI suggests equipment types from BACnet point names
   - G36: AI validates 223P → G36 connections, explains sequences
   - Future: AI co-programmer, code generation, contextual help

2. **Cross-Domain Validation**:

   - G36 needs to validate 223P recommendations against port types
   - Shared types enable cross-domain AI communication

3. **Future LLM Integration**:
   - Centralized LLM client (OpenAI/Anthropic)
   - Vector embeddings, RAG for documentation search
   - AI-assisted debugging

**AI Library Structure:**

```
apps/designer/src/lib/ai/
├── engines/
│   ├── pattern-matcher.ts           # Pattern matching for point names
│   ├── confidence-calculator.ts     # Confidence score calculations
│   └── index.ts
├── types/
│   ├── recommendation.ts            # Generic FieldRecommendation<T>
│   └── index.ts
└── index.ts                         # Public API
```

**Generic Recommendation Type:**

```typescript
// lib/ai/types/recommendation.ts

/**
 * Generic field recommendation with confidence scoring
 * Reusable across all domains (223P, G36, FDD, etc.)
 */
export const FieldRecommendationSchema = <T extends z.ZodTypeAny>(
  valueSchema: T,
) =>
  z.object({
    value: valueSchema,
    confidence: z.number().min(0).max(100),
    reasoning: z.string().optional(),
    alternatives: z
      .array(
        z.object({
          value: valueSchema,
          confidence: z.number(),
        }),
      )
      .optional(),
  });

export type FieldRecommendation<T> = {
  value: T;
  confidence: number;
  reasoning?: string;
  alternatives?: Array<{ value: T; confidence: number }>;
};
```

**Pattern Matcher Engine:**

```typescript
// lib/ai/engines/pattern-matcher.ts

export interface Pattern {
  regex: RegExp;
  value: string;
  confidence: number;
}

export class PatternMatcher {
  static match(
    input: string,
    patterns: Pattern[],
  ): FieldRecommendation<string> {
    for (const pattern of patterns) {
      if (pattern.regex.test(input)) {
        return {
          value: pattern.value,
          confidence: pattern.confidence,
          reasoning: `Matched pattern: ${pattern.regex.source}`,
        };
      }
    }

    // No match
    return {
      value: "Unknown",
      confidence: 0,
      reasoning: "No pattern match found",
    };
  }
}
```

**Domain-Specific AI Services:**

Each domain creates AI services that use the shared AI infrastructure:

```typescript
// domains/223p/services/ai-suggestion.service.ts
import {
  PatternMatcher,
  ConfidenceCalculator,
  FieldRecommendation,
} from "@/lib/ai";
import type { Equipment223PRecommendation } from "../types/223p-recommendation";

export class AI223PSuggestionService {
  async suggestMapping(
    point: BACnetPointDTO,
  ): Promise<Equipment223PRecommendation> {
    const equipmentMatch = PatternMatcher.match(point.name, EQUIPMENT_PATTERNS);
    // ... returns Equipment223PRecommendation using FieldRecommendation<T>
  }
}

// domains/g36/services/ai-validation.service.ts
import { ConfidenceCalculator } from "@/lib/ai";
import type { Equipment223PRecommendation } from "@/domains/223p";

export class AIG36ValidationService {
  validateConnection(
    point: Equipment223PRecommendation, // From 223P domain!
    g36Port: G36PortDefinition,
  ): G36ConnectionValidation {
    // AI validates cross-domain compatibility
  }
}
```

**Future: LLM Integration (Epic 4+)**

```typescript
// lib/ai/engines/llm-client.ts

export class LLMClient {
  async explain(concept: string, context?: string): Promise<string> {
    // Future: Call OpenAI/Anthropic API for explanations
  }

  async generateCode(prompt: string): Promise<string> {
    // Future: AI code generation
  }

  async embedDocumentation(docs: string[]): Promise<number[][]> {
    // Future: Vector embeddings for RAG
  }
}
```

**Benefits:**

1. **✅ Reusability**: AI engines used by 223P, G36, future domains
2. **✅ Generic Types**: `FieldRecommendation<T>` works for any value type
3. **✅ Cross-Domain**: G36 can validate 223P recommendations
4. **✅ Future-Proof**: Ready for LLM integration, embeddings, RAG
5. **✅ Testable**: Pure functions in engines (no React/hooks)
6. **✅ Centralized**: Single source for confidence calculations, pattern matching

---

### Domain Structure (Domain-Driven Design)

All 223P-related code is organized under `apps/designer/src/domains/223p/` following Domain-Driven Design principles. This creates a clear **bounded context** for semantic modeling concerns.

**Full Folder Structure:**

```
apps/designer/src/domains/223p/
├── api/
│   ├── mappings.api.ts              # sessionStorage API (Epic 1) → REST API (Epic 3)
│   ├── spaces.api.ts                # Space registry API
│   ├── buildingmotif.api.ts         # Mock BuildingMOTIF service API
│   └── queries/                     # React Query hooks (INTERNAL - not exported)
│       ├── use-mappings-query.ts    # useQuery/useMutation for mappings
│       ├── use-spaces-query.ts      # useQuery/useMutation for spaces
│       └── query-keys.ts            # Query key factory
├── view-models/                     # ViewModel hooks (PUBLIC - exported in index.ts)
│   ├── use-equipment-view-model.ts  # Maps DTO → EquipmentViewModel
│   ├── use-space-view-model.ts      # Maps DTO → SpaceViewModel
│   ├── use-space-label.ts           # URN → label resolver
│   ├── use-search-spaces.ts         # Space search/filter
│   └── mappers/                     # Pure mapper functions (testable)
│       ├── equipment.mapper.ts      # mapEquipmentDTOToViewModel()
│       └── space.mapper.ts          # mapSpaceDTOToViewModel()
├── services/
│   ├── mock-buildingmotif.service.ts  # Mock template library
│   ├── ai-suggestion.service.ts       # Uses lib/ai for pattern matching
│   └── shacl-validation.service.ts    # BACnet type validation
├── types/
│   ├── 223p-recommendation.ts         # Equipment223PRecommendation (uses FieldRecommendation<T>)
│   └── index.ts
├── components/                      # 223P-specific components ONLY
│   ├── MappingPopup.tsx             # Uses ONLY 223P view-models/services
│   ├── EquipmentTypeDropdown.tsx    # 223P equipment type selector
│   ├── DeviceTypeDropdown.tsx       # 223P device type selector
│   ├── PropertyDropdown.tsx         # 223P property selector
│   ├── SpaceComboBox.tsx            # 223P space selection
│   └── PointBadge.tsx               # Displays 223P metadata badges
├── schemas/
│   ├── dto.schemas.ts               # DTO Zod schemas (Equipment, Space, Validation)
│   ├── enum.schemas.ts              # Enum schemas (SystemType, DeviceType, etc.)
│   └── view-models.ts               # ViewModel TypeScript interfaces (UI-only)
├── mocks/
│   └── buildingmotif-templates.json
└── index.ts                         # Public API (exports view-models, components, types)
```

**Key Architectural Decisions:**

1. **Network vs ViewModel Separation**:

   - `api/queries/` = React Query hooks that fetch DTOs (internal, not exported)
   - `view-models/` = Hooks that transform DTOs → ViewModels (public API)

2. **Pure Mapper Functions**:

   - `view-models/mappers/` = Stateless transformation functions
   - Easily unit testable without React/hooks
   - Epic 3 complexity isolated in mappers, not hooks

3. **Component Boundary**:
   - `components/` contains ONLY 223P-domain-specific components
   - Multi-domain orchestration components live in `app/_components/` (see below)

**Public API Pattern:**

```typescript
// apps/designer/src/domains/223p/index.ts

/**
 * ASHRAE 223P Semantic Modeling Domain
 *
 * Handles equipment tagging, space grouping, and property mapping
 * using ASHRAE 223P ontology and BuildingMOTIF service.
 */

// ✅ EXPORT: ViewModel hooks (public - stable interface for UI)
export { useEquipmentViewModel } from "./view-models/use-equipment-view-model";
export { useSpaceViewModel } from "./view-models/use-space-view-model";
export { useSpaceLabel } from "./view-models/use-space-label";
export { useSearchSpaces } from "./view-models/use-search-spaces";

// ✅ EXPORT: Domain-specific components
export { MappingPopup } from "./components/MappingPopup";
export { PointBadge } from "./components/PointBadge";
export { EquipmentTypeDropdown } from "./components/EquipmentTypeDropdown";
export { SpaceComboBox } from "./components/SpaceComboBox";

// ✅ EXPORT: Types (DTOs + ViewModels)
export type * from "./types";

// ❌ DO NOT EXPORT: Network queries (internal - encapsulated)
// - api/queries/use-mappings-query.ts
// - api/queries/use-spaces-query.ts
// These stay internal to the domain

// ❌ DO NOT EXPORT: Mappers (used internally by view-model hooks)
// - view-models/mappers/equipment.mapper.ts
// - view-models/mappers/space.mapper.ts
```

**Benefits:**

1. **✅ Bounded Context**: All 223P code isolated in single domain
2. **✅ Clear Ownership**: Epic 1 owns `domains/223p/`, Epic 2 owns `domains/g36/`
3. **✅ Easy Navigation**: Find all 223P files in one place
4. **✅ Testability**: Test entire domain in isolation
5. **✅ Scalability**: Add new domains (`domains/fdd/`, `domains/bacnet/`) without mixing concerns
6. **✅ Import Clarity**: `import { useEquipmentViewModel } from '@/domains/223p'` (domain-scoped)
7. **✅ Future Migration**: Could extract as `@bms/223p` package if needed
8. **✅ Network/ViewModel Separation**: Queries internal, view-models public (clear API boundary)
9. **✅ Pure Mappers**: Transformation logic testable without React/hooks

---

### Component Placement Strategy

**Rule**: Domain components vs App components are separated based on **dependency scope**.

**Decision Matrix:**

| Component                 | Location                   | Dependencies                      | Reason                        |
| ------------------------- | -------------------------- | --------------------------------- | ----------------------------- |
| **MappingPopup**          | `domains/223p/components/` | ONLY 223P (view-models, services) | ✅ Single domain              |
| **EquipmentTypeDropdown** | `domains/223p/components/` | ONLY 223P (templates, types)      | ✅ Single domain              |
| **PointBadge**            | `domains/223p/components/` | ONLY 223P (EquipmentViewModel)    | ✅ Single domain              |
| **BACnetPointCard**       | `app/_components/`         | BACnet + 223P + G36               | ❌ Multi-domain orchestration |
| **LeftPanel**             | `app/_components/`         | BACnet + 223P (filters, lists)    | ❌ Multi-domain orchestration |
| **FlowCanvas**            | `app/_components/`         | React Flow + BACnet + G36         | ❌ App-level layout           |

**Full App Structure (with both domain and app components):**

```
apps/designer/src/
├── domains/
│   ├── 223p/
│   │   ├── components/              # ✅ 223P-specific components
│   │   │   ├── MappingPopup.tsx
│   │   │   ├── EquipmentTypeDropdown.tsx
│   │   │   └── PointBadge.tsx
│   │   ├── view-models/
│   │   ├── api/
│   │   └── index.ts
│   └── g36/                         # Epic 2
│       ├── components/
│       │   ├── G36BlockLibrary.tsx
│       │   └── G36BlockNode.tsx
│       └── index.ts
├── app/                             # Next.js app router
│   ├── (routes)/
│   │   ├── page.tsx
│   │   └── layout.tsx
│   └── _components/                 # ❌ Multi-domain orchestration
│       ├── BACnetPointCard.tsx      # Uses BACnet + 223P + G36
│       ├── LeftPanel.tsx            # Uses BACnet + 223P
│       ├── FlowCanvas.tsx           # React Flow + all domains
│       └── Header.tsx               # App-level UI
└── components/                      # Shared UI (domain-agnostic)
    └── ui/                          # shadcn/ui components
        ├── button.tsx
        └── dialog.tsx
```

**Example: Domain Component**

```typescript
// domains/223p/components/MappingPopup.tsx
// ✅ Uses ONLY 223P domain exports

import { useEquipmentViewModel } from '../view-models/use-equipment-view-model';
import { EquipmentTypeDropdown } from './EquipmentTypeDropdown';
import { SpaceComboBox } from './SpaceComboBox';

export function MappingPopup({ point, onConfirm, onSkip }: Props) {
  const { viewModel, isLoading } = useEquipmentViewModel(projectId, point.id);

  return (
    <Dialog>
      <EquipmentTypeDropdown />
      <SpaceComboBox />
    </Dialog>
  );
}
```

**Example: App Component (Multi-Domain Orchestration)**

```typescript
// app/_components/BACnetPointCard.tsx
// ❌ Orchestrates multiple domains

import { useEquipmentViewModel, PointBadge } from '@/domains/223p';
import { useG36Connections, G36Badge } from '@/domains/g36';
import { useBACnetPoint } from '@/domains/bacnet';

export function BACnetPointCard({ pointId }: Props) {
  // Multi-domain data fetching
  const point = useBACnetPoint(pointId);                       // BACnet domain
  const { viewModel: tags } = useEquipmentViewModel(pointId); // 223P domain
  const connections = useG36Connections(pointId);              // G36 domain

  return (
    <Card>
      <h3>{point.name}</h3>                    {/* BACnet */}
      {tags && <PointBadge tags={tags} />}     {/* 223P */}
      {connections && <G36Badge />}            {/* G36 */}
    </Card>
  );
}
```

**Epic 2 Structure (G36 Domain):**

```
apps/designer/src/domains/g36/
├── api/
│   └── queries/
├── view-models/
│   └── mappers/
├── services/
├── components/
├── schemas/
└── index.ts
```

Clean separation between domains!

---

### Services and Modules

| Module                                                                                 | Responsibility                                                             | Inputs                               | Outputs                                              | Owner            |
| -------------------------------------------------------------------------------------- | -------------------------------------------------------------------------- | ------------------------------------ | ---------------------------------------------------- | ---------------- |
| **Shared AI Library** (`lib/ai/`)                                                      | Provides pattern matching, confidence calculation for all domains          | Point names, patterns                | `FieldRecommendation<T>` (generic)                   | Story 1.3        |
| **Mock BuildingMOTIF Service** (`domains/223p/services/mock-buildingmotif.service.ts`) | Provides 223P template library and validation without backend dependency   | Point metadata (name, type, units)   | Equipment/Device/Property templates                  | Story 1.2        |
| **AI Suggestion Service** (`domains/223p/services/ai-suggestion.service.ts`)           | Uses shared AI lib for pattern-matching, analyzes BACnet point names       | `BACnetPointDTO`                     | `Equipment223PRecommendation` with confidence scores | Story 1.3        |
| **223P Mapping Popup** (`domains/223p/components/MappingPopup.tsx`)                    | Modal dialog for AI-assisted semantic tagging with four dropdown selectors | Point data, AI suggestions           | Confirmed 223P mapping or skip action                | Story 1.4        |
| **Equipment/Device Dropdowns** (`domains/223p/components/*Dropdown.tsx`)               | Searchable dropdown components using shadcn/ui Select                      | Template lists from service          | Selected equipment/device/property type              | Stories 1.5, 1.6 |
| **SHACL Validation Mock** (`domains/223p/services/shacl-validation.service.ts`)        | Client-side validation checking BACnet object type compatibility           | `Equipment223PDTO`, `BACnetPointDTO` | `ValidationResultDTO` (errors, warnings)             | Story 1.7        |
| **223P API Layer** (`domains/223p/api/mappings.api.ts`)                                | sessionStorage API (Epic 1), swaps to REST (Epic 3)                        | CRUD operations                      | DTOs (Equipment, Space)                              | Story 1.9        |
| **Custom Hooks** (`domains/223p/hooks/use-equipment-view-model.ts`)                    | Maps DTOs → ViewModels, provides React Query hooks                         | projectId, pointId                   | `EquipmentViewModel`                                 | Story 1.9        |
| **Badge Component** (`domains/223p/components/PointBadge.tsx`)                         | Visual indicator showing 223P metadata on point cards                      | Point ID, mapping data               | Rendered badge with tooltip                          | Story 1.8        |

**Module Dependencies:**

```
MappingPopup → AISuggestionEngine → MockBuildingMOTIFService
           → TypeDropdowns → MockBuildingMOTIFService
           → SHACLValidation
           → Mapping223pStore (Zustand)
```

### Data Models and Contracts

**Type-Safe 223P Enums (aligned with BuildingMOTIF NREL templates):**

```typescript
// System Types (from systems.yml)
export const SystemType = {
  MAU: "Makeup Air Unit",
  VAV_REHEAT: "VAV Reheat Terminal Unit",
  LAB_VAV_REHEAT: "Lab VAV Reheat Terminal Unit",
  CHW_SYSTEM: "Chilled Water System",
  HW_SYSTEM: "Hot Water System",
  PCHW_SYSTEM: "Process Chilled Water System",
  EAU: "Exhaust Air Unit",
  HRS: "Heat Recovery System",
} as const;
export type SystemType = (typeof SystemType)[keyof typeof SystemType];

// Device Types (from devices.yml)
export const DeviceType = {
  // Air-side devices
  DAMPER: "Damper",
  FAN: "Fan",
  EXHAUST_FAN: "Exhaust Fan",
  FILTER: "Filter",

  // Coils
  CHW_COIL: "Chilled Water Coil",
  HW_COIL: "Hot Water Coil",
  HEAT_RECOVERY_COIL: "Heat Recovery Coil",

  // Water-side devices
  CHW_VALVE: "Chilled Water Valve",
  HW_VALVE: "Hot Water Valve",
  CHW_PUMP: "Chilled Water Pump",
  HW_PUMP: "Hot Water Pump",

  // Sensors (generic - specific property defined separately)
  SENSOR: "Sensor",

  // Other equipment
  EVAPORATIVE_COOLER: "Evaporative Cooler",
  HEAT_EXCHANGER: "Heat Exchanger",
  FCU: "Fan Coil Unit",
  UNIT_HEATER: "Unit Heater",
  TANK: "Tank",
  DOMESTIC_WATER_HEATER: "Domestic Water Heater",
} as const;
export type DeviceType = (typeof DeviceType)[keyof typeof DeviceType];

// Observable Properties (from properties.yml)
// Quantifiable Properties
export const QuantifiableProperty = {
  // Pressure
  STATIC_PRESSURE: "static-pressure",
  LOW_STATIC_PRESSURE: "low-static-pressure",
  WATER_STATIC_PRESSURE: "water-static-pressure",
  DIFFERENTIAL_PRESSURE: "differential-pressure",
  WATER_DIFFERENTIAL_PRESSURE: "water-differential-pressure",

  // Temperature
  AIR_TEMPERATURE: "air-temperature",
  WATER_TEMPERATURE: "water-temperature",

  // Flow
  AIR_FLOW: "air-flow",
  WATER_FLOW: "water-flow",

  // Environmental
  RELATIVE_HUMIDITY: "relative-humidity",

  // VFD Properties
  VFD_CURRENT: "vfd-current",
  VFD_FREQUENCY: "vfd-frequency",
  VFD_VOLTAGE: "vfd-voltage",
  VFD_POWER: "vfd-power",
  VFD_ENERGY: "vfd-energy",

  // BTU Meter
  BTU_METER_ENERGY: "BTU-Meter-energy",
  BTU_METER_ENERGY_RATE: "BTU-Meter-energy-rate",
  BTU_METER_WATER_FLOW: "BTU-Meter-water-flow",
  BTU_METER_WATER_VOLUME: "BTU-Meter-water-volume",
} as const;
export type QuantifiableProperty =
  (typeof QuantifiableProperty)[keyof typeof QuantifiableProperty];

// Enumerated Properties
export const EnumeratedProperty = {
  RUN_STATUS: "run-status",
  FLOW_STATUS: "flow-status",
  VFD_FAULT: "vfd-fault",
  CONDENSATE_OVERFLOW: "condensate-overflow",
  OCCUPANCY_OVERRIDE: "occupancy-override",
} as const;
export type EnumeratedProperty =
  (typeof EnumeratedProperty)[keyof typeof EnumeratedProperty];

// Combined Observable Property type
export type ObservableProperty = QuantifiableProperty | EnumeratedProperty;

// Space Types (from spaces.yml) - NEW!
export const SpaceType = {
  DOMAIN_SPACE: "DomainSpace",
  PHYSICAL_SPACE: "PhysicalSpace",
} as const;
export type SpaceType = (typeof SpaceType)[keyof typeof SpaceType];

// Connection Point Types (from devices.yml)
export const ConnectionPointType = {
  AIR_IN: "air-in",
  AIR_OUT: "air-out",
  WATER_IN: "water-in",
  WATER_OUT: "water-out",
  IN: "in",
  OUT: "out",
} as const;
export type ConnectionPointType =
  (typeof ConnectionPointType)[keyof typeof ConnectionPointType];
```

**Existing Types (Reused from Codebase):**

```typescript
// From @/types/infrastructure.ts (lines 47-56)
type BacnetObjectType =
  | "analog-input"
  | "analog-output"
  | "analog-value"
  | "binary-input"
  | "binary-output"
  | "binary-value"
  | "multi-state-input"
  | "multi-state-output"
  | "multi-state-value";

// From @/lib/db/schema/iot-device-controllers.ts
interface IotDeviceController {
  id: string;
  device_id: number; // BACnet device instance number
  name: string; // Device name
  ip_address: string;
  port: number;
  // ... other fields
}
```

**DTO Schemas and Types (Story 1.1) - Flexible for Epic 3 Refinement:**

> **Note**: These DTOs are "best guess" based on 223P ontology. Epic 3 will refine structure based on actual BuildingMOTIF API responses. UI components use ViewModels (not DTOs) to remain isolated from API changes.
>
> **Architecture**: All DTOs defined as Zod schemas with TypeScript types derived via `z.infer`. This ensures runtime validation and TypeScript types never drift out of sync.

```typescript
import { z } from "zod";

// ============================================================================
// 1. Zod Schemas (Single Source of Truth for DTOs)
// ============================================================================

// Validation error codes enum
export enum ValidationErrorCode {
  INCOMPATIBLE_BACNET_TYPE = "INCOMPATIBLE_BACNET_TYPE",
  INVALID_PROPERTY_FOR_DEVICE = "INVALID_PROPERTY_FOR_DEVICE",
  MISSING_REQUIRED_FIELD = "MISSING_REQUIRED_FIELD",
  SPACE_REQUIRED_FOR_SYSTEM = "SPACE_REQUIRED_FOR_SYSTEM",
}

// BACnet External Reference DTO (simplified for Epic 1)
export const BACnetExternalReferenceDTOSchema = z.object({
  deviceIdentifier: z.string().optional(), // "device,{device_id}"
  deviceName: z.string().optional(), // Human-readable device name
  objectIdentifier: z.string().optional(), // "{objectType},{objectId}" e.g., "analog-input,1"
  objectName: z.string().optional(), // Human-readable object name
  propertyIdentifier: z.string().optional(), // Default: "present-value"
  propertyArrayIndex: z.number().optional(), // For array properties
  priorityForWriting: z.number().min(1).max(16).optional(), // BACnet priority (1-16)
});

// Space DTO (matches what API will return)
export const SpaceDTOSchema = z.object({
  id: z.string(), // URN (server-generated): "urn:bms:PhysicalSpace:space-{uuid}"
  rdfsLabel: z.string(), // Display name: "Room 201"
  spaceType: SpaceTypeSchema, // "PhysicalSpace" | "DomainSpace"
  pointIds: z.array(z.string()), // BACnet point IDs using this space
  createdAt: z.date(),
});

// Equipment Mapping DTO (what API stores/returns)
// Epic 1: Flat structure; Epic 3: May become nested graph
export const Equipment223PDTOSchema = z.object({
  equipmentType: SystemTypeSchema, // e.g., "VAV Reheat Terminal Unit"
  spaceId: z.string().optional(), // Space URN (optional) - full URN string, not UUID
  deviceType: DeviceTypeSchema, // e.g., "Sensor", "Damper"
  observableProperty: ObservablePropertySchema, // e.g., "air-temperature", "run-status"
  propertyType: z.enum(["quantifiable", "enumerated"]),
  connectionPoints: z.array(ConnectionPointTypeSchema).optional(), // For G36 integration (Epic 2)
  externalReference: BACnetExternalReferenceDTOSchema,
  schemaVersion: z.literal("223p-2023"),
});

// Validation Error DTO
export const ValidationErrorDTOSchema = z.object({
  field: z.enum(["equipmentType", "space", "deviceType", "observableProperty"]),
  message: z.string(),
  code: z.nativeEnum(ValidationErrorCode),
  expectedType: z.string().optional(),
  actualType: z.string().optional(),
});

// Validation Warning DTO
export const ValidationWarningDTOSchema = z.object({
  field: z.enum(["equipmentType", "space", "deviceType", "observableProperty"]),
  message: z.string(),
  code: z.string(),
});

// Validation Result DTO
export const ValidationResultDTOSchema = z.object({
  isValid: z.boolean(),
  errors: z.array(ValidationErrorDTOSchema),
  warnings: z.array(ValidationWarningDTOSchema),
});

// BACnet Point DTO (Simplified for AI Suggestion Service)
export const BACnetPointDTOSchema = z.object({
  id: z.string(), // Maps to BacnetConfig.pointId
  name: z.string(), // "VAV-2-01_ZoneTemp"
  description: z.string().optional(),
  objectType: BacnetObjectTypeSchema, // Reuses existing type (kebab-case)
  units: z.string().optional(),
  deviceId: z.string(), // Controller ID for equipment grouping
  presentValue: z.union([z.number(), z.boolean()]).optional(),
});

// ============================================================================
// 2. TypeScript Types (Derived from Zod Schemas)
// ============================================================================

export type BACnetExternalReferenceDTO = z.infer<
  typeof BACnetExternalReferenceDTOSchema
>;
export type SpaceDTO = z.infer<typeof SpaceDTOSchema>;
export type Equipment223PDTO = z.infer<typeof Equipment223PDTOSchema>;
export type ValidationErrorDTO = z.infer<typeof ValidationErrorDTOSchema>;
export type ValidationWarningDTO = z.infer<typeof ValidationWarningDTOSchema>;
export type ValidationResultDTO = z.infer<typeof ValidationResultDTOSchema>;
export type BACnetPointDTO = z.infer<typeof BACnetPointDTOSchema>;

// ============================================================================
// 3. ViewModels (UI Layer - Stable Interface, Plain TypeScript)
// ============================================================================
// ViewModels are UI-only constructs that never cross API boundaries,
// so they remain as plain TypeScript interfaces (no runtime validation needed)

// Flat structure optimized for UI components (dropdowns, badges)
interface EquipmentViewModel {
  equipmentType: string; // For system dropdown + badge
  spaceLabel?: string; // Resolved space display name (from URN lookup)
  deviceType: string; // For device dropdown + badge
  observableProperty: string; // For property dropdown + badge
  propertyType: "quantifiable" | "enumerated";

  // BACnet reference (for tooltip/debugging)
  bacnetDevice?: string; // Resolved device name
  bacnetObject?: string; // Resolved object name
}

// Space ViewModel for combo box
interface SpaceViewModel {
  id: string; // URN (for saving)
  label: string; // Display name (for dropdown)
  type: SpaceType;
  pointCount: number; // How many points use this space
  isRecent: boolean; // For "recently used" section
}

// AI Recommendation ViewModel (component state during popup)
interface AIRecommendationViewModel {
  equipmentType: { value: string; confidence: number };
  space?: { label: string; type: SpaceType; confidence: number };
  deviceType: { value: string; confidence: number };
  observableProperty: { value: string; confidence: number };
  overallConfidence: number;
}
```

---

**223P-Specific AI Recommendation Types:**

These types use the generic `FieldRecommendation<T>` from `lib/ai` but are specific to the 223P domain.

```typescript
// ============================================================================
// 223P AI Recommendation Types (Domain-Specific)
// ============================================================================
// Located: domains/223p/types/223p-recommendation.ts

import { FieldRecommendation } from "@/lib/ai";
import {
  SystemType,
  DeviceType,
  ObservableProperty,
  SpaceType,
} from "../schemas/enum.schemas";

/**
 * Equipment 223P Recommendation (from AI Suggestion Service)
 *
 * Uses generic FieldRecommendation<T> from shared AI library.
 * Returned by domains/223p/services/ai-suggestion.service.ts
 */
export interface Equipment223PRecommendation {
  equipmentType: FieldRecommendation<SystemType>;
  space?: FieldRecommendation<{
    label: string;
    type: SpaceType;
  }>;
  deviceType: FieldRecommendation<DeviceType>;
  observableProperty: FieldRecommendation<ObservableProperty>;
  overallConfidence: number;
}

/**
 * Example usage in AI Suggestion Service:
 *
 * const recommendation: Equipment223PRecommendation = {
 *   equipmentType: {
 *     value: 'VAV Reheat Terminal Unit',
 *     confidence: 95,
 *     reasoning: 'Matched pattern: VAV-\\d+-\\d+',
 *     alternatives: [
 *       { value: 'Lab VAV Reheat Terminal Unit', confidence: 78 }
 *     ]
 *   },
 *   space: {
 *     value: { label: 'Room 201', type: 'PhysicalSpace' },
 *     confidence: 88,
 *     reasoning: 'Parsed room number from device ID'
 *   },
 *   deviceType: {
 *     value: 'Sensor',
 *     confidence: 92,
 *     reasoning: 'Object type: analog-input'
 *   },
 *   observableProperty: {
 *     value: 'air-temperature',
 *     confidence: 95,
 *     reasoning: 'Matched pattern: .*Temp.*'
 *   },
 *   overallConfidence: 92.5
 * };
 */
```

---

**Enum Schemas (Referenced by DTOs Above):**

These enum schemas are used by the DTO schemas defined above. They're defined separately here for clarity and reusability.

```typescript
// System types enum (8 equipment types from NREL BuildingMOTIF templates)
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

// Device types enum (18 device types grouped by category)
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

// Observable properties enum (25+ properties: quantifiable + enumerated)
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

// Space types enum (2 types from ASHRAE 223P)
export const SpaceTypeSchema = z.enum(["DomainSpace", "PhysicalSpace"]);

// Connection point types enum (for G36 integration - Epic 2)
export const ConnectionPointTypeSchema = z.enum([
  "air-in",
  "air-out",
  "water-in",
  "water-out",
  "in",
  "out",
]);

// BACnet object types enum (reused from existing codebase types)
export const BacnetObjectTypeSchema = z.enum([
  "analog-input",
  "analog-output",
  "analog-value",
  "binary-input",
  "binary-output",
  "binary-value",
  "multi-state-input",
  "multi-state-output",
  "multi-state-value",
]);

// TypeScript types derived from enum schemas
export type SystemType = z.infer<typeof SystemTypeSchema>;
export type DeviceType = z.infer<typeof DeviceTypeSchema>;
export type ObservableProperty = z.infer<typeof ObservablePropertySchema>;
export type SpaceType = z.infer<typeof SpaceTypeSchema>;
export type ConnectionPointType = z.infer<typeof ConnectionPointTypeSchema>;
export type BacnetObjectType = z.infer<typeof BacnetObjectTypeSchema>;
```

**Mock Data Structure (`/mocks/buildingmotif-templates.json`) - Updated:**

```json
{
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
  "quantifiableProperties": [
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
  "enumeratedProperties": [
    "run-status",
    "flow-status",
    "vfd-fault",
    "condensate-overflow",
    "occupancy-override"
  ],
  "spaces": ["DomainSpace", "PhysicalSpace"]
}
```

### UI Mockups (Updated for 4-Dropdown Structure)

**223P Mapping Popup - Updated Layout:**

```
┌──────────────────────────────────────────────────────────────┐
│ 223P Semantic Mapping                                   [×]  │
│ ℹ️ Optional - Recommended                                    │
├──────────────────────────────────────────────────────────────┤
│                                                              │
│ VAV-2-01_ZoneTemp                      analog-input         │
│ Present Value: 72.3°F                                        │
│                                                              │
│ ┌────────────────────────────────────────────────────────┐  │
│ │ System Type                    [⟳ Loading...]          │  │
│ │ ▼ VAV Reheat Terminal Unit              ✓ 95%         │  │
│ └────────────────────────────────────────────────────────┘  │
│                                                              │
│ ┌────────────────────────────────────────────────────────┐  │
│ │ Space (Optional)                                       │  │
│ │ ▼ PhysicalSpace                         Auto           │  │
│ │ Space Name: [Room 201____________]      (Optional)     │  │
│ └────────────────────────────────────────────────────────┘  │
│                                                              │
│ ┌────────────────────────────────────────────────────────┐  │
│ │ Device Type                    [⟳ Loading...]          │  │
│ │ ▼ Sensor                                ✓ 92%          │  │
│ └────────────────────────────────────────────────────────┘  │
│                                                              │
│ ┌────────────────────────────────────────────────────────┐  │
│ │ Observable Property            [⟳ Loading...]          │  │
│ │ ▼ air-temperature                       ✓ 95%          │  │
│ │   Quantifiable Property                                │  │
│ └────────────────────────────────────────────────────────┘  │
│                                                              │
│ Overall AI Confidence: ████████████░░ 94%                   │
│                                                              │
│ ℹ️ Why tag?                                                  │
│   • Enables analytics and FDD integration                   │
│   • Prepares points for G36 sequences                       │
│   • Takes 30 sec vs 5 min manual                            │
│                                                              │
│ [Confirm] [Not Sure - Ask AI] [Skip]                       │
└──────────────────────────────────────────────────────────────┘
```

**Dropdown Content (User-Facing Strings):**

**1. System Type Dropdown (8 options):**

```
┌────────────────────────────────────┐
│ Search systems...                  │
├────────────────────────────────────┤
│ ✓ VAV Reheat Terminal Unit    95% │ <- AI selected
│   Lab VAV Reheat Terminal Unit     │
│   Makeup Air Unit                  │
│   Exhaust Air Unit                 │
│   Heat Recovery System             │
│   Chilled Water System             │
│   Hot Water System                 │
│   Process Chilled Water System     │
└────────────────────────────────────┘
```

**2. Space Dropdown (2 options + combo box with autocomplete):**

```
┌────────────────────────────────────┐
│ Space Type                         │
├────────────────────────────────────┤
│ ✓ PhysicalSpace          Auto     │ <- Inferred from system
│   DomainSpace                      │
├────────────────────────────────────┤
│ Space Name (Optional)              │
│ ▼ [Room 201____________] 🔍       │ <- Combo box: dropdown + text input
│                                    │
│ Recently used spaces:              │
│ • Room 201 (3 points)              │ <- Click to reuse
│ • Room 202 (2 points)              │
│ • AHU-1 Mechanical Room (8 points) │
│ • 3rd Floor Zone A (5 points)      │
│                                    │
│ Or type new space name...          │
└────────────────────────────────────┘
```

**Autocomplete Behavior:**

- As user types "Room", dropdown filters to matching spaces
- Shows point count to indicate which spaces are already populated
- Click existing space to reuse exact name (ensures consistency)
- Type new name to create new space grouping

**State Management (React Query + Mock API for Epic 1):**

Following existing codebase pattern (`use-controller-points.ts`, `use-iot-device-controllers.ts`), we use **React Query** for all 223P mappings and spaces.

**Key Design Principle:** sessionStorage stores ONLY domain DTOs (what real BuildingMOTIF API would return). UI concerns stay in component state/React Query cache.

```typescript
// ============================================================================
// Mock API (Epic 1 - sessionStorage, Epic 3 - swap to fetch())
// Stores ONLY domain DTOs - matches real API contract
// ============================================================================

// apps/designer/src/domains/223p/api/mappings.api.ts
export const mapping223pApi = {
  // Returns pure domain model: Map<pointId, Equipment223PDTO>
  async listMappings(
    projectId: string,
  ): Promise<Map<string, Equipment223PDTO>> {
    const key = `223p-mappings:${projectId}`;
    const data = sessionStorage.getItem(key);
    if (!data) return new Map();

    const entries = JSON.parse(data) as [string, Equipment223PDTO][];
    return new Map(entries);
  },

  // Accepts pure DTO, returns created DTO (what real API does)
  async createMapping(
    projectId: string,
    pointId: string,
    mapping: Equipment223PDTO,
  ): Promise<Equipment223PDTO> {
    const mappings = await this.listMappings(projectId);
    mappings.set(pointId, mapping);

    const key = `223p-mappings:${projectId}`;
    sessionStorage.setItem(key, JSON.stringify(Array.from(mappings.entries())));

    return mapping; // Return what was created
  },

  // Returns updated DTO
  async updateMapping(
    projectId: string,
    pointId: string,
    updates: Partial<Equipment223PDTO>,
  ): Promise<Equipment223PDTO> {
    const mappings = await this.listMappings(projectId);
    const existing = mappings.get(pointId);

    if (!existing) {
      throw new Error(`Mapping not found for point: ${pointId}`);
    }

    const updated = { ...existing, ...updates };
    mappings.set(pointId, updated);

    const key = `223p-mappings:${projectId}`;
    sessionStorage.setItem(key, JSON.stringify(Array.from(mappings.entries())));

    return updated;
  },

  async deleteMapping(projectId: string, pointId: string): Promise<void> {
    const mappings = await this.listMappings(projectId);
    mappings.delete(pointId);

    const key = `223p-mappings:${projectId}`;
    sessionStorage.setItem(key, JSON.stringify(Array.from(mappings.entries())));
  },

  // ============================================================================
  // Space Registry API
  // ============================================================================

  async listSpaces(projectId: string): Promise<SpaceGrouping[]> {
    const key = `223p-spaces:${projectId}`;
    const data = sessionStorage.getItem(key);
    return data ? JSON.parse(data) : [];
  },

  // Server generates URN (client sends label + type, receives created space)
  async createSpace(
    projectId: string,
    rdfsLabel: string,
    spaceType: SpaceType,
  ): Promise<SpaceGrouping> {
    // Server-side responsibility: Generate URN
    const urn = this._generateSpaceURN(spaceType);

    const space: SpaceGrouping = {
      id: urn,
      rdfsLabel,
      spaceType,
      pointIds: [],
      createdAt: new Date(),
    };

    const spaces = await this.listSpaces(projectId);
    spaces.push(space);

    const key = `223p-spaces:${projectId}`;
    sessionStorage.setItem(key, JSON.stringify(spaces));

    return space; // Return created space with server-generated URN
  },

  async updateSpace(
    projectId: string,
    spaceUrn: string,
    updates: Partial<SpaceGrouping>,
  ): Promise<SpaceGrouping> {
    const spaces = await this.listSpaces(projectId);
    const index = spaces.findIndex((s) => s.id === spaceUrn);

    if (index === -1) {
      throw new Error(`Space not found: ${spaceUrn}`);
    }

    spaces[index] = { ...spaces[index], ...updates };

    const key = `223p-spaces:${projectId}`;
    sessionStorage.setItem(key, JSON.stringify(spaces));

    return spaces[index];
  },

  // ============================================================================
  // Private helpers (server-side logic)
  // ============================================================================

  _generateSpaceURN(spaceType: SpaceType): string {
    const uuid = crypto.randomUUID();
    return `urn:bms:${spaceType}:space-${uuid}`;
  },
};

// ============================================================================
// React Query Hooks (Internal - Fetch DTOs)
// ============================================================================

// apps/designer/src/domains/223p/api/queries/use-mappings-query.ts
// Internal hooks that work with DTOs - NOT exported to components
export function useMappingsQuery(projectId: string | undefined) {
  return useQuery({
    queryKey: queryKeys.mappings223p.list(projectId || "none"),
    queryFn: () => mapping223pApi.listMappings(projectId!),
    enabled: !!projectId,
    // Returns: Map<pointId, Equipment223PDTO>
  });
}

export function useCreateMappingMutation() {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: ({
      projectId,
      pointId,
      mapping,
    }: {
      projectId: string;
      pointId: string;
      mapping: Equipment223PDTO;
    }) => mapping223pApi.createMapping(projectId, pointId, mapping),
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.mappings223p.list(projectId),
      });
      queryClient.invalidateQueries({
        queryKey: queryKeys.spaces223p.list(projectId),
      });
    },
  });
}

// ============================================================================
// Pure Mapper Functions (Testable without React/Hooks)
// ============================================================================

// apps/designer/src/domains/223p/view-models/mappers/equipment.mapper.ts

/**
 * Maps Equipment DTO → ViewModel for UI components
 *
 * Epic 1: Simple identity mapping
 * Epic 3: Will add complex transformations for BuildingMOTIF graph structure
 *
 * Pure function - easily unit testable without React/hooks
 */
export function mapEquipmentDTOToViewModel(
  dto: Equipment223PDTO,
  spaces: SpaceDTO[],
): EquipmentViewModel {
  // Resolve space URN → label
  const spaceLabel = dto.spaceId
    ? spaces.find((s) => s.id === dto.spaceId)?.rdfsLabel
    : undefined;

  return {
    equipmentType: dto.equipmentType,
    spaceLabel,
    deviceType: dto.deviceType,
    observableProperty: dto.observableProperty,
    propertyType: dto.propertyType,
    bacnetDevice: dto.externalReference.deviceName,
    bacnetObject: dto.externalReference.objectName,
  };
}

// ============================================================================
// ViewModel Hooks (Public - Provide ViewModels to UI Components)
// ============================================================================

// apps/designer/src/domains/223p/view-models/use-equipment-view-model.ts

/**
 * Primary hook for UI components - returns ViewModel
 * Components never see DTOs, only ViewModels
 */
export function useEquipmentViewModel(
  projectId: string | undefined,
  pointId: string | undefined,
) {
  // Import internal query hooks
  const { data: mappings, isLoading: isLoadingMappings } =
    useMappingsQuery(projectId);
  const { data: spaces = [], isLoading: isLoadingSpaces } =
    useSpacesQuery(projectId);

  const viewModel = useMemo(() => {
    if (!mappings || !pointId) return null;
    const dto = mappings.get(pointId);
    if (!dto) return null;

    // Use pure mapper function
    return mapEquipmentDTOToViewModel(dto, spaces);
  }, [mappings, pointId, spaces]);

  return {
    viewModel,
    isLoading: isLoadingMappings || isLoadingSpaces,
  };
}

/**
 * Hook for creating equipment mapping
 * Accepts ViewModel from UI, converts to DTO for API
 */
export function useCreateEquipmentMapping() {
  const createMappingMutation = useCreateMappingMutation();

  return useMutation({
    mutationFn: async ({
      projectId,
      pointId,
      viewModel,
      point,
      controller,
    }: {
      projectId: string;
      pointId: string;
      viewModel: Omit<
        EquipmentViewModel,
        "spaceLabel" | "bacnetDevice" | "bacnetObject"
      >;
      point: BacnetConfig;
      controller: IotDeviceController;
    }) => {
      // Map ViewModel → DTO
      const dto: Equipment223PDTO = {
        equipmentType: viewModel.equipmentType,
        spaceId: viewModel.spaceLabel, // Will be resolved to URN in parent
        deviceType: viewModel.deviceType,
        observableProperty: viewModel.observableProperty,
        propertyType: viewModel.propertyType,
        externalReference: buildBACnetExternalReference(point, controller),
        schemaVersion: "223p-2023",
      };

      return createMappingMutation.mutateAsync({
        projectId,
        pointId,
        mapping: dto,
      });
    },
  });
}

// ============================================================================
// Space ViewModel Hooks
// ============================================================================

// apps/designer/src/domains/223p/view-models/use-space-view-model.ts
export function useSpaceViewModel(projectId: string | undefined) {
  // Uses internal query hook
  const { data: spaces = [], isLoading } = useSpacesQuery(projectId);

  // Transform to ViewModel (add computed fields)
  const spaceViewModels = useMemo(() => {
    return spaces.map((space) => ({
      id: space.id,
      label: space.rdfsLabel,
      type: space.spaceType,
      pointCount: space.pointIds.length,
      isRecent: false, // Epic 1: Simple implementation, Epic 3: Track usage
    }));
  }, [spaces]);

  return {
    spaces: spaceViewModels,
    isLoading,
  };
}

export function useCreate223PSpace() {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: ({
      projectId,
      rdfsLabel,
      spaceType,
    }: {
      projectId: string;
      rdfsLabel: string;
      spaceType: SpaceType;
    }) => mapping223pApi.createSpace(projectId, rdfsLabel, spaceType),
    // API generates URN and returns created space
    onSuccess: (createdSpace, { projectId }) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.spaces223p.list(projectId),
      });
      // Optional: Track space creation in analytics
      console.log("Space created:", createdSpace.id, createdSpace.rdfsLabel);
    },
  });
}

// ============================================================================
// Helper Functions
// ============================================================================

// Get space label for display
export function useSpaceLabel(
  spaceUrn: string | undefined,
  projectId: string | undefined,
) {
  const { data: spaces } = use223PSpaces(projectId);
  return spaces?.find((s) => s.id === spaceUrn)?.rdfsLabel;
}

// Search spaces by label
export function useSearchSpaces(projectId: string | undefined, query: string) {
  const { data: spaces } = use223PSpaces(projectId);
  return (
    spaces?.filter((s) =>
      s.rdfsLabel.toLowerCase().includes(query.toLowerCase()),
    ) ?? []
  );
}

// Get recent spaces (sorted by creation date)
export function useRecentSpaces(
  projectId: string | undefined,
  limit: number = 10,
) {
  const { data: spaces } = use223PSpaces(projectId);
  return (
    spaces
      ?.sort(
        (a, b) =>
          new Date(b.createdAt).getTime() - new Date(a.createdAt).getTime(),
      )
      .slice(0, limit) ?? []
  );
}
```

**Benefits of React Query + Pure DTOs:**

✅ **Consistent with existing codebase** - Controllers, Points all use React Query
✅ **Epic 3 is true zero-refactor** - Just swap `sessionStorage.getItem()` → `fetch()`, no UI changes
✅ **Automatic caching** - Deduplication, background refetching, invalidation
✅ **Optimistic updates built-in** - React Query handles optimistic UI
✅ **DevTools for debugging** - Inspect cache state, query status
✅ **API contract matches reality** - sessionStorage stores exactly what BuildingMOTIF API returns
✅ **UI concerns stay in UI layer** - Recommendations, tracking, analytics live in component state
✅ **Clean separation of concerns** - Domain models vs UI state properly isolated

**Epic 3 Migration Example:**

```typescript
// Epic 1 (Mock - sessionStorage)
export const mapping223pApi = {
  async listMappings(
    projectId: string,
  ): Promise<Map<string, Equipment223PDTO>> {
    const data = sessionStorage.getItem(`223p-mappings:${projectId}`);
    return data ? new Map(JSON.parse(data)) : new Map();
  },
};

// Epic 3 (Real - BuildingMOTIF API)
export const mapping223pApi = {
  async listMappings(
    projectId: string,
  ): Promise<Map<string, Equipment223PDTO>> {
    const response = await fetch(`/api/223p-mappings?project=${projectId}`);
    const data = await response.json();
    return new Map(Object.entries(data)); // ✅ Same return type
  },
};

// Components using React Query hooks: ZERO CHANGES NEEDED
```

**3. Device Type Dropdown (18 options, grouped):**

```
┌────────────────────────────────────┐
│ Search devices...                  │
├────────────────────────────────────┤
│ 🏷️ Sensors & Monitoring            │
│   ✓ Sensor                    92% │ <- AI selected
│                                    │
│ 🏷️ Air-side Equipment              │
│     Damper                         │
│     Fan                            │
│     Exhaust Fan                    │
│     Filter                         │
│                                    │
│ 🏷️ Coils                           │
│     Chilled Water Coil             │
│     Hot Water Coil                 │
│     Heat Recovery Coil             │
│                                    │
│ 🏷️ Water-side Equipment            │
│     Chilled Water Valve            │
│     Hot Water Valve                │
│     Chilled Water Pump             │
│     Hot Water Pump                 │
│                                    │
│ 🏷️ Other Equipment                 │
│     Evaporative Cooler             │
│     Heat Exchanger                 │
│     Fan Coil Unit                  │
│     Unit Heater                    │
│     Tank                           │
│     Domestic Water Heater          │
└────────────────────────────────────┘
```

**4. Observable Property Dropdown (25 options, grouped by type):**

```
┌────────────────────────────────────────┐
│ Search properties...                   │
├────────────────────────────────────────┤
│ 🏷️ Temperature (Quantifiable)          │
│   ✓ air-temperature               95% │ <- AI selected
│     water-temperature                  │
│                                        │
│ 🏷️ Pressure (Quantifiable)             │
│     static-pressure                    │
│     low-static-pressure                │
│     water-static-pressure              │
│     differential-pressure              │
│     water-differential-pressure        │
│                                        │
│ 🏷️ Flow (Quantifiable)                 │
│     air-flow                           │
│     water-flow                         │
│                                        │
│ 🏷️ Environmental (Quantifiable)        │
│     relative-humidity                  │
│                                        │
│ 🏷️ VFD Properties (Quantifiable)       │
│     vfd-current                        │
│     vfd-frequency                      │
│     vfd-voltage                        │
│     vfd-power                          │
│     vfd-energy                         │
│                                        │
│ 🏷️ BTU Meter (Quantifiable)            │
│     BTU-Meter-energy                   │
│     BTU-Meter-energy-rate              │
│     BTU-Meter-water-flow               │
│     BTU-Meter-water-volume             │
│                                        │
│ 🏷️ Status Properties (Enumerated)      │
│     run-status                         │
│     flow-status                        │
│     vfd-fault                          │
│     condensate-overflow                │
│     occupancy-override                 │
└────────────────────────────────────────┘
```

**AI Suggestion Example (Using ViewModel Architecture):**

For point: `VAV-2-01_ZoneTemp` (analog-input, 72.3°F)

```typescript
// ============================================================================
// Component: MappingPopup.tsx (UI Component - Uses ViewModels Only)
// ============================================================================

function MappingPopup({ point, controller, onConfirm, onSkip }: Props) {
  const projectId = useCurrentProjectId();
  const createMapping = useCreateEquipmentMapping();
  const createSpace = useCreateSpace();

  // UI-only state: AI recommendations as ViewModel (NEVER sent to API)
  const [aiRec, setAIRec] = useState<AIRecommendationViewModel | null>(null);
  const [isLoadingAI, setIsLoadingAI] = useState(true);

  // User selections (start with AI suggestions, allow manual override)
  const [equipmentType, setEquipmentType] = useState('');
  const [spaceLabel, setSpaceLabel] = useState('');
  const [deviceType, setDeviceType] = useState('');
  const [property, setProperty] = useState('');

  // Load AI suggestion when popup opens
  useEffect(() => {
    aiSuggestionEngine.analyze(point).then((recommendation) => {
      setAIRec(recommendation);
      // Pre-fill with AI suggestions
      setEquipmentType(recommendation.equipmentType.value);
      setDeviceType(recommendation.deviceType.value);
      setProperty(recommendation.observableProperty.value);
      setSpaceLabel(recommendation.space?.label || '');
      setIsLoadingAI(false);
    });
  }, [point]);

  const handleConfirm = async () => {
    // Step 1: Create/resolve space if provided
    let spaceUrn: string | undefined;
    if (spaceLabel && aiRec?.space) {
      const existingSpace = await searchSpace(projectId, spaceLabel);
      if (existingSpace) {
        spaceUrn = existingSpace.id;  // Reuse existing URN
      } else {
        const created = await createSpace.mutateAsync({
          projectId,
          rdfsLabel: spaceLabel,
          spaceType: aiRec.space.type,
        });
        spaceUrn = created.id;  // Server-generated URN
      }
    }

    // Step 2: Build ViewModel from user selections
    const viewModel: Omit<EquipmentViewModel, 'spaceLabel' | 'bacnetDevice' | 'bacnetObject'> = {
      equipmentType,
      deviceType,
      observableProperty: property,
      propertyType: aiRec?.observableProperty.value.includes('status') ? 'enumerated' : 'quantifiable',
    };

    // Step 3: Save via custom hook (handles ViewModel → DTO conversion)
    await createMapping.mutateAsync({
      projectId,
      pointId: point.pointId,
      viewModel,
      point,
      controller,
    });

    // Optional: Track analytics (client-side only)
    logAnalytics({
      event: 'mapping_created',
      source: 'ai-accepted',
      aiConfidence: aiRec?.overallConfidence,
    });

    onConfirm();
  };

  return (
    <Dialog>
      {isLoadingAI ? (
        <Spinner />
      ) : (
        <>
          <EquipmentTypeDropdown
            value={equipmentType}
            onChange={setEquipmentType}
            aiSuggestion={aiRec?.equipmentType}
          />
          <SpaceComboBox
            value={spaceLabel}
            onChange={setSpaceLabel}
            aiSuggestion={aiRec?.space}
          />
          <DeviceTypeDropdown
            value={deviceType}
            onChange={setDeviceType}
            aiSuggestion={aiRec?.deviceType}
          />
          <PropertyDropdown
            value={property}
            onChange={setProperty}
            aiSuggestion={aiRec?.observableProperty}
          />
          <Button onClick={handleConfirm}>Confirm</Button>
          <Button onClick={onSkip}>Skip</Button>
        </>
      )}
    </Dialog>
  );
}

// ============================================================================
// Dropdown Component Example (Uses ViewModel)
// ============================================================================

interface EquipmentTypeDropdownProps {
  value: string;
  onChange: (value: string) => void;
  aiSuggestion?: { value: string; confidence: number };
}

function EquipmentTypeDropdown({ value, onChange, aiSuggestion }: EquipmentTypeDropdownProps) {
  const equipmentTypes = [
    'VAV Reheat Terminal Unit',
    'Makeup Air Unit',
    'Chilled Water System',
    // ... from mock template data
  ];

  return (
    <Select value={value} onValueChange={onChange}>
      <SelectTrigger>
        <SelectValue placeholder="Select equipment type..." />
      </SelectTrigger>
      <SelectContent>
        {equipmentTypes.map((type) => (
          <SelectItem key={type} value={type}>
            {type}
            {aiSuggestion?.value === type && (
              <Badge variant="success" className="ml-2">
                ✓ {aiSuggestion.confidence}%
              </Badge>
            )}
          </SelectItem>
        ))}
      </SelectContent>
    </Select>
  );
}
```

**What Gets Stored in sessionStorage:**

```json
{
  "223p-mappings:project-123": [
    [
      "point-abc-456",
      {
        "system": "VAV Reheat Terminal Unit",
        "spaceId": "urn:bms:PhysicalSpace:space-def-789",
        "device": "Sensor",
        "property": "air-temperature",
        "propertyType": "quantifiable",
        "externalReference": {
          "deviceIdentifier": "device,12345",
          "objectIdentifier": "analog-input,1",
          "propertyIdentifier": "present-value"
        },
        "schemaVersion": "223p-2023"
      }
    ]
  ]
}
```

**What Does NOT Get Stored:**

- ❌ AI recommendations
- ❌ Confidence scores
- ❌ Source tracking (`ai-accepted`, `manual`)
- ❌ Timestamps
- ❌ Any UI metadata

These live in component state or optional analytics tracking (not in API storage).

**Badge Display (Left Panel Point Card) - Uses ViewModel:**

After tagging, point card shows 223P metadata via ViewModel:

```typescript
// ============================================================================
// Component: BACnetPointCard.tsx (UI Component)
// ============================================================================

function BACnetPointCard({ point }: { point: BacnetConfig }) {
  const projectId = useCurrentProjectId();

  // Custom hook provides ViewModel (no DTOs exposed to component)
  const { viewModel, isLoading } = useEquipmentViewModel(projectId, point.pointId);

  if (isLoading) {
    return <Skeleton className="h-20 w-full" />;
  }

  return (
    <div className="bacnet-point">
      <div className="point-name">{point.name}</div>
      <span className="point-badge">{point.objectType}</span>

      {viewModel && (
        <div className="point-tags">
          <span className="tag-badge">{viewModel.equipmentType}</span>
          <span className="tag-badge success">{viewModel.deviceType}</span>
          <span className="tag-badge warning">{viewModel.observableProperty}</span>
        </div>
      )}

      {viewModel?.spaceLabel && (
        <div className="point-value">📍 {viewModel.spaceLabel}</div>
      )}

      <div className="point-value">Present Value: {point.presentValue}</div>
    </div>
  );
}
```

**Benefits**:

- ✅ Component doesn't know about DTOs or API structure
- ✅ Space URN → label resolution handled in hook
- ✅ Epic 3 API changes won't affect this component
- ✅ Easy to test (mock ViewModel, not DTO)

Visual:

```
┌────────────────────────────────────┐
│ VAV-2-01_ZoneTemp  analog-input    │
│ 🏷️ VAV Reheat | Sensor | air-temp │ <- From EquipmentViewModel
│ 📍 Room 201                        │ <- Resolved spaceLabel
│ Present Value: 72.3°F              │
└────────────────────────────────────┘
```

**User-Facing Property Names (Display vs Internal):**

For better UX, consider displaying human-readable names:

```typescript
const PROPERTY_DISPLAY_NAMES = {
  // Temperature
  "air-temperature": "Air Temperature",
  "water-temperature": "Water Temperature",

  // Pressure
  "static-pressure": "Static Pressure",
  "differential-pressure": "Differential Pressure",

  // Flow
  "air-flow": "Air Flow",
  "water-flow": "Water Flow",

  // VFD
  "vfd-current": "VFD Current",
  "vfd-frequency": "VFD Frequency",

  // Status
  "run-status": "Run Status",
  "flow-status": "Flow Status",

  // ... etc
};
```

**Dropdown Component Pattern (shadcn/ui):**

```tsx
<Select>
  <SelectTrigger>
    <SelectValue placeholder="Select property..." />
  </SelectTrigger>
  <SelectContent>
    <SelectGroup>
      <SelectLabel>🏷️ Temperature (Quantifiable)</SelectLabel>
      <SelectItem value="air-temperature">
        Air Temperature {aiSuggestion === "air-temperature" && "✓ 95%"}
      </SelectItem>
      <SelectItem value="water-temperature">Water Temperature</SelectItem>
    </SelectGroup>

    <SelectSeparator />

    <SelectGroup>
      <SelectLabel>🏷️ Pressure (Quantifiable)</SelectLabel>
      <SelectItem value="static-pressure">Static Pressure</SelectItem>
      {/* ... */}
    </SelectGroup>

    {/* ... more groups ... */}

    <SelectSeparator />

    <SelectGroup>
      <SelectLabel>🏷️ Status Properties (Enumerated)</SelectLabel>
      <SelectItem value="run-status">Run Status</SelectItem>
      {/* ... */}
    </SelectGroup>
  </SelectContent>
</Select>
```

**Space Field Behavior:**

```typescript
// Auto-fill space type based on system
const inferSpaceType = (system: SystemType): SpaceType => {
  // Most HVAC systems serve physical spaces
  const physicalSpaceSystems = [
    "VAV Reheat Terminal Unit",
    "Lab VAV Reheat Terminal Unit",
    "Makeup Air Unit",
    "Exhaust Air Unit",
    "Fan Coil Unit",
  ];

  return physicalSpaceSystems.includes(system)
    ? "PhysicalSpace"
    : "DomainSpace";
};

// AI suggests space name based on device ID and existing mappings
const suggestSpaceName = (
  point: BACnetPointDTO,
  existingMappings: Map<string, Equipment223PDTO>,
  spaceRegistry: Map<string, SpaceGrouping>,
): string | undefined => {
  // Strategy 1: Find other points from same device that are already tagged
  const sameDevicePoints = Array.from(existingMappings.entries()).filter(
    ([pointId, mapping]) => {
      const existingPoint = getPointById(pointId);
      return existingPoint?.deviceId === point.deviceId && mapping.spaceName;
    },
  );

  if (sameDevicePoints.length > 0) {
    // Reuse space from same device
    return sameDevicePoints[0][1].spaceName;
  }

  // Strategy 2: Parse device ID for room number (e.g., VAV-2-01 → "Room 201")
  const roomMatch = point.deviceId.match(/VAV-(\d)-(\d{2})/);
  if (roomMatch) {
    const floor = roomMatch[1];
    const roomNum = roomMatch[2];
    return `Room ${floor}${roomNum}`;
  }

  // Strategy 3: Check if device ID contains common space identifiers
  if (point.deviceId.includes("AHU")) {
    return `${point.deviceId} Mechanical Room`;
  }

  return undefined; // No suggestion
};

// Validation: Some systems require space name
const validateSpace = (
  system: SystemType,
  spaceName?: string,
): ValidationResultDTO => {
  const requiresSpace = [
    "VAV Reheat Terminal Unit",
    "Lab VAV Reheat Terminal Unit",
  ];

  if (requiresSpace.includes(system) && !spaceName) {
    return {
      isValid: false,
      errors: [
        {
          field: "space",
          message: "Space name required for VAV terminal units",
          code: ValidationErrorCode.SPACE_REQUIRED_FOR_SYSTEM,
        },
      ],
      warnings: [],
    };
  }

  return { isValid: true, errors: [], warnings: [] };
};
```

**Space Combo Box Component (shadcn/ui with React Query):**

```tsx
import {
  Command,
  CommandEmpty,
  CommandGroup,
  CommandInput,
  CommandItem,
} from "@/components/ui/command";
import {
  Popover,
  PopoverContent,
  PopoverTrigger,
} from "@/components/ui/popover";
import { useRecentSpaces } from "@/hooks/use-223p-spaces";

function SpaceNameComboBox({ projectId }: { projectId: string }) {
  const [open, setOpen] = useState(false);
  const [value, setValue] = useState("");

  // React Query hook for recent spaces
  const recentSpaces = useRecentSpaces(projectId, 10);

  return (
    <Popover open={open} onOpenChange={setOpen}>
      <PopoverTrigger asChild>
        <Input
          value={value}
          onChange={(e) => setValue(e.target.value)}
          placeholder="Type space name or select..."
          onClick={() => setOpen(true)}
        />
      </PopoverTrigger>
      <PopoverContent className="w-[400px] p-0">
        <Command>
          <CommandInput
            placeholder="Search spaces..."
            value={value}
            onValueChange={setValue}
          />
          <CommandEmpty>No spaces found. Type to create new.</CommandEmpty>
          <CommandGroup heading="Recently used spaces">
            {recentSpaces.map((space) => (
              <CommandItem
                key={space.id}
                onSelect={() => {
                  setValue(space.rdfsLabel);
                  setOpen(false);
                }}
              >
                <span className="font-medium">{space.rdfsLabel}</span>
                <span className="ml-auto text-xs text-muted-foreground">
                  {space.pointIds.length} points
                </span>
              </CommandItem>
            ))}
          </CommandGroup>
        </Command>
      </PopoverContent>
    </Popover>
  );
}
```

**Space Grouping Benefits:**

1. **Consistency**: Prevents typos like "Room 201", "room 201", "Room201"
2. **Analytics**: Can query all points in a specific space
3. **Bulk Operations**: "Re-tag all points in Room 201"
4. **Validation**: "You've already tagged 3 temperature sensors in Room 201, are you sure you want to add another?"
5. **Navigation**: "Show me all points in AHU-1 Mechanical Room"

**Auto-fill Example Workflow:**

```
User tags first point: VAV-2-01_ZoneTemp
  → Space name suggested: "Room 201" (parsed from device ID)
  → User confirms
  → Space registered: { spaceName: "Room 201", spaceType: "PhysicalSpace", pointIds: ["point-1"] }

User tags second point: VAV-2-01_DamperPos (same device)
  → Space name auto-filled: "Room 201" (from same device)
  → User sees: "Auto-filled from VAV-2-01_ZoneTemp"
  → Space updated: { spaceName: "Room 201", spaceType: "PhysicalSpace", pointIds: ["point-1", "point-2"] }

User tags third point: VAV-2-02_ZoneTemp (different room)
  → Space name suggested: "Room 202" (parsed from device ID)
  → Dropdown shows: "Room 201 (2 points)" <- available to reuse if user made mistake
  → User confirms "Room 202"
  → New space registered
```

### APIs and Interfaces

**IBuildingMOTIFService Interface (Story 1.2) - Updated:**

```typescript
interface IBuildingMOTIFService {
  // Template retrieval
  getEquipmentTypes(): Promise<string[]>;
  getDeviceTypes(): Promise<string[]>;
  getObservableProperties(): Promise<string[]>;

  // AI suggestion
  suggestMapping(point: BACnetPointDTO): Promise<EquipmentDTO>;

  // Validation
  validateMapping(
    point: BACnetPointDTO,
    mapping: EquipmentDTO,
  ): Promise<ValidationResultDTO>;
}
```

**Mock Implementation:**

```typescript
class MockBuildingMOTIFService implements IBuildingMOTIFService {
  private templates: TemplateLibrary;

  constructor() {
    // Load from /mocks/buildingmotif-templates.json
    this.templates = loadTemplates();
  }

  async getEquipmentTypes(): Promise<string[]> {
    return Promise.resolve(this.templates.equipmentTypes);
  }

  async suggestMapping(point: BACnetPointDTO): Promise<EquipmentDTO> {
    // Delegates to AISuggestionEngine
    return aiSuggestionEngine.analyze(point, this.templates);
  }

  async validateMapping(point: BACnetPointDTO, mapping: EquipmentDTO): Promise<ValidationResultDTO> {
    // Validates BACnet object type compatibility
    return shac lValidationService.validate(point, mapping);
  }
}
```

**AI Suggestion Engine Pattern Matching (Story 1.3):**

```typescript
class AISuggestionEngine {
  analyze(point: BACnetPointDTO, templates: TemplateLibrary): EquipmentDTO {
    const patterns = [
      {
        regex: /ZoneTemp|RoomTemp|SpaceTemp/i,
        property: "Zone Air Temperature",
        device: "Temperature Sensor",
        confidence: 95,
      },
      {
        regex: /CoolingValve|ClgValve/i,
        property: "Cooling Valve Position",
        device: "Valve Actuator",
        confidence: 88,
      },
      {
        regex: /DamperPos|DmprPos/i,
        property: "Damper Position",
        device: "Damper Actuator",
        confidence: 85,
      },
      // ... 20+ more patterns
    ];

    // Equipment type inferred from device ID prefix (e.g., VAV-2-01 → VAV Terminal Unit)
    const equipmentType = this.inferEquipmentFromDeviceId(point.deviceId);

    // Match point name against patterns
    const match = patterns.find((p) => p.regex.test(point.name));

    return {
      equipmentType,
      deviceType: match?.device ?? "Unknown",
      observableProperty: match?.property ?? "Unknown",
      confidence: match?.confidence ?? 40,
      source: "ai",
      schemaVersion: "223p-2023",
    };
  }
}
```

**Zustand Store Interface (Story 1.9):**

```typescript
interface Mapping223pState {
  mappings: Map<string, EquipmentDTO>;

  // Actions
  add223PMapping: (pointId: string, mapping: EquipmentDTO) => void;
  get223PMapping: (pointId: string) => EquipmentDTO | undefined;
  remove223PMapping: (pointId: string) => void;
  getAllMappings: () => Map<string, EquipmentDTO>;
}
```

### Workflows and Sequencing

**Workflow 1: Optional 223P Tagging (Point → Canvas)**

```
User Action: Drag BACnet point from sidebar to canvas
   ↓
System: Fire onDrop event
   ↓
System: Open MappingPopup modal (<100ms, empty shell)
   ↓
System: Call MockBuildingMOTIFService.suggestMapping(point)
   ↓
AI Engine: Pattern match point name → Generate EquipmentDTO (confidence 40-95%)
   ↓
UI: Progressive fill dropdowns with AI suggestions (show loading → fill)
   ↓
User Decision:
   ├─ [Confirm] → Save to Zustand store → Close modal → Add point to canvas → Show badge
   ├─ [Override] → Manual dropdown selection → Save → Close → Add with badge
   └─ [Skip] → Close modal → Add point to canvas (no mapping, no badge)
```

**Workflow 2: Auto-fill Equipment Type from Previous Point (Story 1.10)**

```
Precondition: Point from same device already tagged (e.g., VAV-2-01_*)
   ↓
User: Drag second point from same device (VAV-2-01_DamperPos)
   ↓
System: Check Zustand store for existing mappings with same deviceId
   ↓
System: Find VAV-2-01_ZoneTemp mapped to "VAV Terminal Unit"
   ↓
AI Engine: Pre-fill equipmentType = "VAV Terminal Unit" (source: 'auto-fill')
   ↓
AI Engine: Still suggest deviceType + property based on point name
   ↓
UI: Show "Equipment type auto-filled from previous points" hint
```

**Workflow 3: SHACL Validation Feedback (Story 1.7)**

```
User: Select dropdown values in popup
   ↓
System: On each dropdown change → Call validateMapping()
   ↓
Validation: Check BACnet object type compatibility:
   - If deviceType = "Actuator" AND objectType != (AO|BO) → ERROR
   - If deviceType = "Sensor" AND objectType != (AI|BI) → ERROR
   ↓
UI: Display validation errors inline below dropdown:
   - Red text: "Actuator requires AO/BO object type, found AI"
   - Warning icon next to dropdown
   - Disable [Confirm] button while errors exist
```

**Component Interaction Sequence:**

```
[Left Panel] → User drags point
   ↓
[React Flow Canvas] → onDrop event
   ↓
[MappingPopup] → Opens, requests AI suggestion
   ↓
[AISuggestionEngine] → Analyzes point → Returns EquipmentDTO
   ↓
[TypeDropdowns] → Pre-fill with AI suggestions
   ↓
[User] → Modifies selection or confirms
   ↓
[SHACLValidation] → Validates on change → Shows errors
   ↓
[Mapping223pStore] → Saves mapping to Zustand
   ↓
[PointBadge] → Displays on left panel point card
   ↓
[Canvas] → Point node added with metadata
```

## Non-Functional Requirements

### Performance

**NFR-PERF-001: AI Response Time**

- **Requirement:** System shall generate 223P suggestions and display popup within 500ms of point drag-and-drop action
- **Rationale:** Maintain workflow fluidity; delays >500ms disrupt integrator's mental model
- **Implementation:** Mock AI uses synchronous pattern matching (no network calls), popup shell renders <100ms while AI processes
- **Measurement:** Chrome DevTools Performance profiling, target: onDrop → popup visible <100ms, AI result → dropdown fill <500ms
- **Epic 1 Scope:** Mock service is synchronous, meets target easily; Epic 3 must maintain performance with network calls

**NFR-PERF-002: Popup Render Time**

- **Requirement:** 223P mapping popup shell renders <100ms (empty state before AI suggestions)
- **Rationale:** Provide immediate visual feedback that system is responding
- **Implementation:** Progressive disclosure - show popup structure immediately, fill AI suggestions asynchronously
- **Measurement:** First contentful paint of modal <100ms

**NFR-PERF-003: Validation Response**

- **Requirement:** SHACL validation mock completes <50ms for real-time feedback on dropdown changes
- **Rationale:** Synchronous validation during user interaction; delays feel laggy
- **Implementation:** Simple BACnet object type checks, no complex RDF queries in mock
- **Epic 3 Note:** Real SHACL validation must optimize for <2s (NFR002 from PRD)

**NFR-PERF-004: In-Memory State Performance**

- **Requirement:** React Query cache operations complete <10ms for flows with up to 100 tagged points
- **Rationale:** Session-only state must not degrade UI responsiveness
- **Implementation:** sessionStorage read/write optimized, no unnecessary re-renders
- **Measurement:** Zustand DevTools performance tab, monitor query cache updates

### Security

**NFR-SEC-001: Client-Side Only Processing**

- **Requirement:** Epic 1 processes all data client-side with no external network calls
- **Rationale:** Mock service eliminates attack surface; no API credentials needed
- **Implementation:** Mock BuildingMOTIF service runs in browser, sessionStorage for persistence
- **Validation:** Network tab shows zero API calls during 223P mapping workflow

**NFR-SEC-002: XSS Prevention**

- **Requirement:** All user-provided text (point names, space names) must be sanitized before rendering
- **Rationale:** Prevent cross-site scripting via malicious BACnet point names
- **Implementation:** React JSX automatic escaping, no dangerouslySetInnerHTML
- **Testing:** Attempt mapping point with name: `<script>alert('xss')</script>` - must render as text

**NFR-SEC-003: Input Validation**

- **Requirement:** All DTOs validated with Zod schemas before processing
- **Rationale:** Prevent invalid data from corrupting in-memory state
- **Implementation:** Zod schema validation at API boundaries (createMapping, updateMapping)
- **Testing:** Unit tests for schema validation edge cases

### Reliability/Availability

**NFR-REL-001: Graceful Degradation**

- **Requirement:** System remains functional if mock service throws errors
- **Rationale:** UI should never crash; show error messages and allow continuation
- **Implementation:** Try-catch blocks around service calls, error boundary components
- **User Experience:** If AI suggestion fails → show error message, allow manual dropdown selection
- **Epic 3 Note:** Critical for BuildingMOTIF service downtime (NFR006 from PRD)

**NFR-REL-002: State Consistency**

- **Requirement:** React Query cache and sessionStorage must stay synchronized
- **Rationale:** Prevent state desync that causes UI bugs
- **Implementation:** Query cache invalidation on mutations, atomic sessionStorage updates
- **Validation:** Integration test: create mapping → refresh page → verify data persists

**NFR-REL-003: Session Persistence**

- **Requirement:** All 223P mappings persist in sessionStorage until browser tab closes
- **Rationale:** Demo session should survive component unmounts, page navigations
- **Implementation:** sessionStorage API (survives refresh within tab, cleared on close)
- **Limitation:** No cross-tab persistence, no multi-day persistence (Epic 5)

### Observability

**NFR-OBS-001: Console Logging**

- **Requirement:** Log key user actions and AI decisions to browser console
- **Rationale:** Debugging and demo troubleshooting during LinkedIn feedback
- **Implementation:**
  - Log AI suggestions with confidence scores: `console.log('AI suggestion:', { equipment, confidence })`
  - Log validation errors: `console.error('SHACL validation failed:', errors)`
  - Log state changes: `console.log('Mapping saved:', pointId, mapping)`
- **Epic 3 Note:** Replace with structured logging service

**NFR-OBS-002: React Query DevTools**

- **Requirement:** React Query DevTools enabled in development mode
- **Rationale:** Inspect cache state, query status, invalidation triggers
- **Implementation:** Include `@tanstack/react-query-devtools` package
- **Usage:** Floating DevTools icon in bottom-right corner (dev only)

**NFR-OBS-003: Error Boundaries**

- **Requirement:** React Error Boundaries catch and display component crashes
- **Rationale:** Prevent white screen of death; show actionable error message
- **Implementation:** Error boundary wrapping MappingPopup, badges, dropdowns
- **User Experience:** "Something went wrong. Please refresh and try again."

## Dependencies and Integrations

### Internal Dependencies

**Existing Designer App Infrastructure:**

| Component        | Version | Usage                                     | Location                |
| ---------------- | ------- | ----------------------------------------- | ----------------------- |
| **Next.js**      | 15.5    | Application framework, routing            | Core framework          |
| **React Flow**   | 12.8    | Visual canvas, drag-drop, node management | `@xyflow/react`         |
| **Zustand**      | -       | Global state management                   | `src/store/`            |
| **React Query**  | Latest  | Server state management, caching          | `@tanstack/react-query` |
| **shadcn/ui**    | Latest  | UI component library                      | `src/components/ui/`    |
| **Tailwind CSS** | v4      | Styling system                            | `tailwind.config.ts`    |
| **Zod**          | Latest  | Runtime schema validation                 | DTOs, forms             |

**Codebase Integration Points:**

1. **BACnet Point Discovery System**

   - **Dependency:** `src/hooks/use-controller-points.ts` - provides BACnet point data
   - **Integration:** 223P popup triggered by existing drag-drop from left panel
   - **Impact:** Zero changes to discovery system; 223P is additive layer

2. **React Flow Canvas**

   - **Dependency:** `src/components/flow-canvas.tsx` - manages visual nodes
   - **Integration:** `onDrop` event intercepted to show 223P popup before adding point
   - **Impact:** Add event handler, no changes to existing node rendering

3. **BACnet Point Cards (Left Panel)**

   - **Dependency:** `src/components/bacnet-point-card.tsx` - renders point list
   - **Integration:** Badge component added to show 223P metadata
   - **Impact:** Minor UI update, no data structure changes

4. **Type System**
   - **Dependency:** `@/types/infrastructure.ts` - BacnetObjectType, BacnetConfig
   - **Integration:** Reuse existing types for 223P DTO external references
   - **Impact:** Zero changes; read-only usage

### External Dependencies (Epic 1: Mock Only)

**No external services in Epic 1.** All dependencies are mocked for in-browser demo.

**Mock Service Implementations:**

| Service                   | Interface                 | Mock Implementation          | Epic 3 Real Implementation   |
| ------------------------- | ------------------------- | ---------------------------- | ---------------------------- |
| **BuildingMOTIF Service** | `IBuildingMOTIFService`   | JSON file + pattern matching | REST API → RDF storage       |
| **SHACL Validation**      | `ISHACLValidationService` | BACnet object type checks    | BuildingMOTIF SHACL endpoint |
| **AI Suggestion Engine**  | `IAISuggestionEngine`     | Regex pattern matching       | LLM or advanced NLP          |

**Mock Data Sources:**

- `/mocks/buildingmotif-templates.json` - Equipment types, device types, observable properties
- Inline pattern matching in `AISuggestionEngine.ts` - Point name → suggestion mapping
- No external API calls, no authentication required

### Integration Constraints (Epic 1 Scope)

**What Epic 1 Does NOT Integrate With:**

- ❌ BuildingMOTIF RDF storage (Epic 3)
- ❌ BMS IoT App MQTT layer (future)
- ❌ Project save/load system (Epic 5)
- ❌ G36 FMU services (Epic 4)
- ❌ BOPTest verification (Epic 6)

**Migration Path to Epic 3:**

When replacing mock services with real BuildingMOTIF API:

1. **Zero UI Component Changes** - React Query hooks abstract service layer
2. **Swap Implementation Only:**

   ```typescript
   // Epic 1 (Mock)
   export const mapping223pApi = {
     async listMappings(projectId: string) {
       const data = sessionStorage.getItem(`223p-mappings:${projectId}`);
       return data ? JSON.parse(data) : [];
     },
   };

   // Epic 3 (Real)
   export const mapping223pApi = {
     async listMappings(projectId: string) {
       const response = await fetch(`/api/223p-mappings?project=${projectId}`);
       return response.json();
     },
   };
   ```

3. **Component Code Unchanged** - Same React Query hooks, same UI behavior

### Dependency Management

**Package Versions (Epic 1):**

```json
{
  "dependencies": {
    "@xyflow/react": "^12.8.0",
    "@tanstack/react-query": "^5.x",
    "zustand": "^4.x",
    "zod": "^3.x",
    "@radix-ui/react-select": "latest",
    "@radix-ui/react-popover": "latest",
    "@radix-ui/react-dialog": "latest"
  },
  "devDependencies": {
    "@tanstack/react-query-devtools": "^5.x"
  }
}
```

**No New External Dependencies Required** - All UI components from existing shadcn/ui library.

### Cross-Epic Dependencies

**Epic 1 → Epic 2 Dependencies:**

- Epic 2 (G36 blocks) depends on Epic 1's 223P mapping being functional
- G36 port validation requires 223P metadata from Epic 1 state
- Epic 2 reuses same React Query pattern established in Epic 1

**Epic 1 → Epic 3 Dependencies:**

- Epic 3 replaces mock services with real API
- Epic 3 must maintain same DTO contracts defined in Epic 1
- Epic 3 adds persistence; Epic 1 establishes UX patterns

## Acceptance Criteria (Authoritative)

This section consolidates acceptance criteria from all 12 Epic 1 stories. **All criteria must be met for Epic 1 completion.**

### AC-1: DTO Interfaces and Type Safety (Story 1.1)

**Goal:** Establish type-safe contracts for BuildingMOTIF DTOs that will be used by both mock (Epic 1) and real services (Epic 3).

**Acceptance Criteria:**

1. ✅ **DTO Interfaces Defined**

   - `Equipment223PDTO` interface with: equipmentType, spaceId, deviceType, observableProperty, propertyType, externalReference, schemaVersion
   - `SpaceDTO` interface with: id (URN), rdfsLabel, spaceType, pointIds, createdAt
   - `BACnetExternalReferenceDTO` interface with: deviceIdentifier, deviceName, objectIdentifier, objectName, propertyIdentifier, propertyArrayIndex, priorityForWriting
   - `ValidationResultDTO` interface with: isValid, errors, warnings
   - `ValidationErrorDTO` interface with: field, message, code, expectedType, actualType

2. ✅ **ViewModel Interfaces Defined** (UI layer - stable)

   - `EquipmentViewModel` with flat structure for UI components
   - `SpaceViewModel` for combo box display
   - `AIRecommendationViewModel` for AI suggestions

3. ✅ **Zod Schemas Created**

   - `Equipment223PDTOSchema` with runtime validation
   - `SpaceGroupingSchema` with URN format validation
   - `BACnetExternalReferenceSchema` with all optional fields
   - Enum schemas: `SystemTypeSchema`, `DeviceTypeSchema`, `ObservablePropertySchema`, `SpaceTypeSchema`

4. ✅ **Schema Version Management**

   - All DTOs include `schemaVersion: '223p-2023'` field
   - Enables future migration tracking when 223P spec evolves

5. ✅ **JSDoc Documentation**
   - All interfaces documented with purpose, example values, Epic 3 migration notes
   - DTOs marked as "flexible for Epic 3 refinement"
   - ViewModels marked as "stable interface"

**Verification:**

- All DTO interfaces compile without TypeScript errors
- Zod schemas validate valid DTOs successfully
- Zod schemas reject invalid DTOs with clear error messages
- JSDoc comments visible in IDE autocomplete

---

### AC-2: Mock BuildingMOTIF Service (Story 1.2)

**Goal:** Provide complete 223P template library without backend dependency.

**Acceptance Criteria:**

1. ✅ **Mock Service Implementation**

   - `MockBuildingMOTIFService` class implements `IBuildingMOTIFService` interface
   - Service returns Promises (async) to match real API behavior

2. ✅ **Template Data Coverage**

   - `getEquipmentTypes()` returns 8 equipment types:
     - Makeup Air Unit
     - VAV Reheat Terminal Unit
     - Lab VAV Reheat Terminal Unit
     - Chilled Water System
     - Hot Water System
     - Process Chilled Water System
     - Exhaust Air Unit
     - Heat Recovery System
   - `getDeviceTypes()` returns 18 device types (grouped: air-side, coils, water-side, sensors, other)
   - `getObservableProperties()` returns 25+ properties (quantifiable + enumerated)

3. ✅ **Mock Data Source**

   - Templates loaded from `/mocks/buildingmotif-templates.json`
   - JSON file structure: `{ systems: [], devices: [], quantifiableProperties: [], enumeratedProperties: [], spaces: [] }`

4. ✅ **Service Methods**
   - `suggestMapping(point: BACnetPointDTO): Promise<Equipment223PRecommendation>`
   - `validateMapping(point: BACnetPointDTO, mapping: Equipment223PDTO): Promise<ValidationResultDTO>`
   - `getTemplates(): Promise<TemplateLibrary>`

**Verification:**

- Load mock service → returns templates within 100ms
- Call `getEquipmentTypes()` → returns 8 types
- Call `getDeviceTypes()` → returns 18 types
- Call `getObservableProperties()` → returns 25+ properties
- All methods return Promises (no synchronous returns)

---

### AC-3: AI Suggestion Engine (Story 1.3)

**Goal:** Pattern-matching AI that analyzes BACnet point names to suggest 223P mappings with 85-95% confidence on common patterns.

**Acceptance Criteria:**

1. ✅ **Pattern Matching Rules**

   - **Temperature sensors:**
     - `ZoneTemp`, `RoomTemp`, `SpaceTemp` → `air-temperature`, Sensor, 95% confidence
     - `SupplyTemp`, `ReturnTemp` → `air-temperature`, Sensor, 92% confidence
   - **Actuators:**
     - `CoolingValve`, `ClgValve` → `Chilled Water Valve`, 88% confidence
     - `DamperPos`, `DmprPos` → `Damper`, 85% confidence
   - **Status points:**
     - `RunStatus`, `FanStatus` → `run-status`, Sensor, 90% confidence
   - **Ambiguous names:**
     - `Temp1`, `Sensor2` → low confidence (<50%), no specific suggestion

2. ✅ **Equipment Type Inference**

   - Device ID prefix parsing: `VAV-2-01_*` → "VAV Reheat Terminal Unit"
   - Device ID prefix parsing: `AHU-1_*` → "Makeup Air Unit"
   - Fallback: "Unknown" if no pattern match

3. ✅ **Space Name Suggestion**

   - Parse device ID for room numbers: `VAV-2-01` → "Room 201"
   - Detect mechanical rooms: `AHU-1` → "AHU-1 Mechanical Room"
   - Reuse space from same device ID if already tagged

4. ✅ **Confidence Score Calculation**

   - High confidence (85-95%): Exact pattern match + common naming convention
   - Medium confidence (60-84%): Partial match or ambiguous
   - Low confidence (<60%): No pattern match, fallback to generic

5. ✅ **Recommendation Format**
   - Returns `Equipment223PRecommendation` (using `FieldRecommendation<T>` from `lib/ai`) with:
     - `equipmentType: FieldRecommendation<SystemType>`
     - `space: FieldRecommendation<{ label, type }>` (optional)
     - `deviceType: FieldRecommendation<DeviceType>`
     - `observableProperty: FieldRecommendation<ObservableProperty>`
     - `overallConfidence: number` (average of all fields)
   - Each `FieldRecommendation<T>` includes: `value`, `confidence`, `reasoning`, `alternatives`

**Verification:**

- Input: `{ name: "VAV-2-01_ZoneTemp", objectType: "analog-input" }` → Output: `{ equipmentType: "VAV Reheat Terminal Unit", deviceType: "Sensor", property: "air-temperature", confidence: 95% }`
- Input: `{ name: "VAV-2-01_DamperPos", objectType: "analog-output" }` → Output: `{ deviceType: "Damper", property: "position", confidence: 85% }`
- Input: `{ name: "Temp1", objectType: "analog-input" }` → Output: `{ confidence: <50%, no specific suggestion }`
- Response time: <500ms for all patterns

---

### AC-4: 223P Mapping Popup Modal (Story 1.4)

**Goal:** Auto-popup modal embedded in drag-drop workflow for seamless semantic tagging.

**Acceptance Criteria:**

1. ✅ **Automatic Trigger**

   - Popup opens automatically when BACnet point dropped onto React Flow canvas
   - Modal appears <100ms after drop event (empty shell)
   - AI suggestions populate progressively within 500ms

2. ✅ **Point Context Display**

   - Shows: Point name, description (if available), present value, units, object type
   - Example: "VAV-2-01_ZoneTemp | analog-input | 72.3°F"

3. ✅ **Dropdown Pre-fill**

   - Equipment type dropdown: Pre-filled with AI suggestion, confidence badge visible
   - Space type dropdown: Auto-selected based on equipment type
   - Space name field: Pre-filled with AI suggestion (if available)
   - Device type dropdown: Pre-filled with AI suggestion, confidence badge visible
   - Observable property dropdown: Pre-filled with AI suggestion, confidence badge visible

4. ✅ **Confidence Indicators**

   - Each dropdown shows confidence % next to AI suggestion
   - Overall confidence bar at bottom: "Overall AI Confidence: ████████████░░ 94%"
   - Color coding: Green (>80%), Yellow (60-80%), Red (<60%)

5. ✅ **User Actions**

   - **[Confirm]** button: Saves mapping → closes modal → adds point to canvas → shows badge
   - Space selection is **optional** - user can confirm mapping without selecting a space
   - **[Skip]** button: Closes modal → adds point to canvas (no mapping, no badge)
   - **ESC key**: Same as Skip button
   - Manual dropdown override allowed before confirming

6. ✅ **UI Framework**
   - Uses shadcn/ui `Dialog` component
   - Modal is centered, overlay dims background
   - Responsive width (max 600px)

**Verification:**

- Drag point → popup opens <100ms
- AI suggestions fill <500ms
- Click Confirm → mapping saved to React Query cache, sessionStorage updated
- Click Skip → point added without mapping
- ESC key → popup closes without saving
- All interactions keyboard accessible

---

### AC-5: Equipment Type Dropdown with Search (Story 1.5)

**Goal:** Searchable dropdown for equipment types with AI suggestion highlighting.

**Acceptance Criteria:**

1. ✅ **Dropdown Content**

   - Displays all 8 equipment types from mock service
   - Types listed in logical order (HVAC → water systems)

2. ✅ **Search/Filter**

   - Type-to-filter: Typing "VAV" filters to "VAV Reheat Terminal Unit", "Lab VAV Reheat Terminal Unit"
   - Search is case-insensitive
   - Clear search button visible when text entered

3. ✅ **AI Suggestion Highlight**

   - AI-suggested item marked with ✓ badge and confidence %
   - Example: `✓ VAV Reheat Terminal Unit 95%`
   - Badge color: Green (success variant)

4. ✅ **Selection UX**

   - Currently selected item highlighted
   - Dropdown closes on selection
   - Selected value displayed in trigger button

5. ✅ **Keyboard Navigation**

   - Arrow keys: Navigate list
   - Enter: Select highlighted item
   - ESC: Close dropdown without changing selection
   - Tab: Move to next dropdown

6. ✅ **Component**
   - Uses shadcn/ui `Select` or `Combobox` component
   - Consistent styling with existing Designer app

**Verification:**

- Open dropdown → see all 8 types
- Type "VAV" → list filters to 2 VAV types
- AI suggestion shows ✓ badge
- Arrow keys navigate, Enter selects
- Tab key moves to next dropdown

---

### AC-6: Device Type and Property Dropdowns (Story 1.6)

**Goal:** Device and property dropdowns with same UX as equipment dropdown for consistency.

**Acceptance Criteria:**

1. ✅ **Device Type Dropdown**

   - Shows all 18 device types with search/filter
   - Grouped by category: "Sensors & Monitoring", "Air-side Equipment", "Coils", "Water-side Equipment", "Other Equipment"
   - AI suggestion highlighted with ✓ badge
   - Keyboard accessible

2. ✅ **Observable Property Dropdown**

   - Shows 25+ properties with search/filter
   - Grouped by type: "Temperature (Quantifiable)", "Pressure (Quantifiable)", "Flow (Quantifiable)", "VFD Properties (Quantifiable)", "Status Properties (Enumerated)"
   - AI suggestion highlighted with ✓ badge
   - Property type badge: "Quantifiable" or "Enumerated"

3. ✅ **Component Reuse**

   - Both dropdowns use same component as equipment dropdown
   - Consistent styling, search UX, keyboard navigation
   - Same shadcn/ui component base

4. ✅ **Grouping UX**
   - Group headers: `<SelectLabel>` with emoji icon (🏷️)
   - Separators between groups: `<SelectSeparator />`
   - Items within groups indented slightly

**Verification:**

- Open device dropdown → see 18 types grouped
- Open property dropdown → see 25+ properties grouped
- Search functionality works in both
- AI suggestions highlighted in both
- Keyboard navigation works in both
- Visual consistency with equipment dropdown

---

### AC-7: SHACL Validation Mock (Story 1.7)

**Goal:** Real-time validation feedback preventing incompatible 223P mappings.

**Acceptance Criteria:**

1. ✅ **Validation Rules**

   - **Rule 1:** Actuator (AO/BO) compatibility
     - Device type = "Damper", "Valve", "Pump", "Fan" → requires `objectType = 'analog-output' | 'binary-output'`
     - If `objectType = 'analog-input'` → ERROR: "Actuator requires AO/BO object type, found AI"
   - **Rule 2:** Sensor (AI/BI) compatibility
     - Device type = "Sensor" → requires `objectType = 'analog-input' | 'binary-input'`
     - If `objectType = 'analog-output'` → ERROR: "Sensor requires AI/BI object type, found AO"
   - **Rule 3:** Property type alignment
     - `propertyType = 'quantifiable'` → requires analog object types (AI/AO)
     - `propertyType = 'enumerated'` → requires binary or multi-state object types (BI/BO/MSI/MSO)

2. ✅ **Validation Trigger**

   - Runs automatically on dropdown selection change
   - Runs before saving mapping (on Confirm click)
   - Response time: <50ms (synchronous mock validation)

3. ✅ **Error Display**

   - Error message displayed below affected dropdown (red text)
   - Warning icon (⚠️) appears next to dropdown trigger
   - Example: "⚠️ Actuator requires AO/BO object type, found AI"

4. ✅ **Save Blocking**

   - [Confirm] button disabled when validation errors exist
   - Button shows disabled state (grayed out, not clickable)
   - Tooltip on hover: "Fix validation errors before saving"

5. ✅ **ValidationResultDTO Format**
   ```typescript
   {
     isValid: false,
     errors: [{
       field: 'device',
       message: 'Actuator requires AO/BO object type, found AI',
       code: ValidationErrorCode.INCOMPATIBLE_BACNET_TYPE,
       expectedType: 'analog-output | binary-output',
       actualType: 'analog-input'
     }],
     warnings: []
   }
   ```

**Verification:**

- Select Damper (actuator) + AI object type → see error, Confirm disabled
- Select Sensor + AO object type → see error, Confirm disabled
- Select Sensor + AI object type → no error, Confirm enabled
- Fix error by changing selection → error clears, Confirm enabled

---

### AC-8: Left Panel 223P Metadata Badges (Story 1.8)

**Goal:** Visual indicators showing which points are semantically tagged.

**Acceptance Criteria:**

1. ✅ **Badge Display**

   - Tagged points show 3 badges on point card:
     - Equipment badge: "VAV Reheat Terminal Unit" (primary color)
     - Device badge: "Sensor" (success color)
     - Property badge: "air-temperature" (warning color)
   - Badges appear below point name, above present value

2. ✅ **Badge Content**

   - Equipment badge: Full equipment type name
   - Device badge: Device type name
   - Property badge: Observable property name (kebab-case or display name)

3. ✅ **Space Display**

   - If space tagged: Show space label with location pin icon
   - Example: "📍 Room 201"
   - Displayed below badges, above present value

4. ✅ **Hover Tooltip**

   - Hover over badge → shows full 223P mapping:
     - "Equipment: VAV Reheat Terminal Unit"
     - "Device: Sensor"
     - "Property: air-temperature (Quantifiable)"
     - "Space: Room 201 (PhysicalSpace)"
     - "Confidence: 95% (AI-suggested)"

5. ✅ **Badge Lifecycle**

   - Badge appears only after mapping saved
   - Badge updates if mapping changed
   - Badge removed if mapping deleted
   - No badge for skipped points

6. ✅ **Styling**
   - Uses shadcn/ui `Badge` component
   - Tailwind CSS classes for colors
   - Responsive sizing (fits in point card width)

**Verification:**

- Tag point → see badges appear on point card
- Hover badge → see tooltip with full mapping
- Skip point → no badges shown
- Change mapping → badges update
- Visual consistency with existing point card design

---

### AC-9: In-Memory State Management (Story 1.9)

**Goal:** React Query + sessionStorage for session-only persistence of 223P mappings.

**Acceptance Criteria:**

1. ✅ **React Query Setup**

   - Query keys: `queryKeys.mappings223p.list(projectId)`, `queryKeys.spaces223p.list(projectId)`
   - `use223PMappingsAPI(projectId)` hook returns `Map<pointId, Equipment223PDTO>`
   - `use223PSpacesAPI(projectId)` hook returns `SpaceDTO[]`

2. ✅ **Mutation Hooks**

   - `useCreate223PMappingAPI()` mutation: Creates mapping, invalidates cache
   - `useUpdate223PMappingAPI()` mutation: Updates mapping, invalidates cache
   - `useDelete223PMappingAPI()` mutation: Deletes mapping, invalidates cache
   - `useCreate223PSpace()` mutation: Creates space, invalidates cache

3. ✅ **sessionStorage Integration**

   - Key format: `223p-mappings:${projectId}`, `223p-spaces:${projectId}`
   - Stores pure DTOs only (no UI metadata)
   - Data persists on component unmount/remount
   - Data cleared on browser tab close

4. ✅ **Custom Hooks (ViewModel Layer)**

   - `useEquipmentViewModel(projectId, pointId)` → returns `EquipmentViewModel | null`
   - Maps DTO → ViewModel (resolves space URN → label)
   - Components consume ViewModels, never DTOs

5. ✅ **Cache Invalidation**

   - After creating mapping → invalidate mappings + spaces queries
   - After creating space → invalidate spaces query
   - React Query refetches stale queries automatically

6. ✅ **State Consistency**
   - React Query cache synced with sessionStorage
   - No state desync between cache and storage
   - Atomic updates (no partial writes)

**Verification:**

- Create mapping → data in React Query cache + sessionStorage
- Refresh page → data persists (loaded from sessionStorage)
- Close tab → reopen → data cleared (sessionStorage cleared)
- Create 100 mappings → performance <10ms per operation
- React Query DevTools shows correct cache state

---

### AC-10: Auto-fill Equipment Type (Story 1.10)

**Goal:** Smart auto-fill from previous points on same device to reduce repetitive selections.

**Acceptance Criteria:**

1. ✅ **Auto-fill Logic**

   - When mapping 2nd+ point from same device ID (e.g., `VAV-2-01_*`)
   - Equipment type pre-filled from first point's mapping
   - Example: First point `VAV-2-01_ZoneTemp` tagged as "VAV Reheat Terminal Unit" → Second point `VAV-2-01_DamperPos` auto-fills "VAV Reheat Terminal Unit"

2. ✅ **Space Auto-fill**

   - Space name also auto-filled from same device
   - Example: First point mapped to "Room 201" → Second point auto-fills "Room 201"

3. ✅ **AI Still Active**

   - Device type + property still suggested by AI based on point name
   - Only equipment type + space auto-filled from history

4. ✅ **User Override**

   - User can change auto-filled values before confirming
   - No forced selection (auto-fill is suggestion, not locked)

5. ✅ **Visual Indicator**

   - Auto-filled dropdown shows hint: "Auto-filled from VAV-2-01_ZoneTemp"
   - Different styling than AI suggestion (secondary color vs success color)

6. ✅ **Multi-device Support**
   - Works across multiple devices simultaneously
   - `VAV-2-01` auto-fills from `VAV-2-01` history
   - `VAV-2-02` auto-fills from `VAV-2-02` history (different room)

**Verification:**

- Tag first point from `VAV-2-01` as "VAV Reheat Terminal Unit", "Room 201"
- Tag second point from `VAV-2-01` → equipment auto-filled, space auto-filled
- Tag first point from `VAV-2-02` → no auto-fill (different device)
- Tag second point from `VAV-2-02` → auto-fills from `VAV-2-02` history

---

### AC-11: Cancel/Skip Mapping Workflow (Story 1.11)

**Goal:** Allow skipping 223P mapping without blocking workflow.

**Acceptance Criteria:**

1. ✅ **Skip Button**

   - [Skip] button in popup footer (secondary variant)
   - Closes modal without saving mapping
   - Point added to canvas without 223P metadata

2. ✅ **ESC Key Behavior**

   - ESC key closes modal (same as Skip)
   - Point still added to canvas
   - No mapping saved

3. ✅ **No Badge Display**

   - Skipped points show no badges in left panel
   - Point card displays only BACnet metadata (name, object type, present value)

4. ✅ **Re-tagging Capability**

   - Skipped points can be tagged later (future story - note only)
   - For Epic 1: Once skipped, cannot re-open popup (acceptable limitation)

5. ✅ **Analytics Tracking**
   - Optional: Log skip action for feedback analysis
   - Track skip rate vs confirm rate (component state, not persisted)

**Verification:**

- Click Skip → modal closes, point on canvas, no badge
- Press ESC → modal closes, point on canvas, no badge
- Skip 10 points → workflow continues smoothly
- Skipped points function normally on canvas (no errors)

---

### AC-12: UI Polish and Accessibility (Story 1.12)

**Goal:** Professional, accessible UI for LinkedIn demo and real-world usage.

**Acceptance Criteria:**

1. ✅ **Visual Design**

   - Consistent spacing: shadcn/ui design tokens (p-4, gap-4, etc.)
   - Typography: Inter font family, size hierarchy (text-sm, text-base, text-lg)
   - Colors: Brand colors from Tailwind config
   - Shadows: Subtle elevation for modal (shadow-lg)

2. ✅ **Loading States**

   - Dropdown search shows loading spinner while filtering
   - Popup shows skeleton loader during AI suggestion generation
   - Button shows loading spinner during save operation

3. ✅ **Error States**

   - Validation errors: Red text, warning icon, clear messaging
   - Network errors (Epic 3): Error alert with retry button
   - Empty states: "No results found" when search returns nothing

4. ✅ **Focus Management**

   - Modal open → auto-focus first dropdown (equipment type)
   - Tab order: Equipment → Space → Device → Property → Confirm/Skip
   - Modal close → focus returns to trigger element (canvas)

5. ✅ **Screen Reader Support**

   - All interactive elements have `aria-label`
   - Dropdowns have `aria-describedby` for AI suggestions
   - Form validation errors announced by screen reader
   - Modal has `aria-labelledby` and `aria-describedby`

6. ✅ **Keyboard Navigation**

   - All interactions possible without mouse
   - Shortcuts: ESC (skip), Enter (confirm when valid), Tab (navigate)
   - Focus visible indicator on all focusable elements

7. ✅ **Color Contrast**

   - WCAG AA compliance (4.5:1 for normal text, 3:1 for large text)
   - Test with browser DevTools Accessibility panel
   - High-contrast mode support (system preference)

8. ✅ **Responsive Design**
   - Modal adapts to viewport size (max-width: 600px, 90vw on mobile)
   - Dropdowns don't overflow viewport
   - Touch targets: min 44x44px for mobile

**Verification:**

- Manual accessibility audit with screen reader (NVDA/JAWS)
- Keyboard-only navigation test (no mouse)
- Color contrast check with axe DevTools
- Responsive test: resize browser, check mobile viewport
- Visual QA: Compare to shadcn/ui design system examples

---

### Epic-Level Acceptance Criteria

**Must be satisfied for Epic 1 sign-off:**

1. ✅ **Complete Workflow Integration**

   - User can drag BACnet point → popup opens → AI suggests → user confirms → point tagged → badge visible
   - Entire workflow <1 minute per point (target: 30 seconds)

2. ✅ **AI Performance**

   - 85%+ confidence on common patterns (ZoneTemp, DamperPos, etc.)
   - <500ms AI response time (mock)

3. ✅ **State Management**

   - 100 tagged points load/save <100ms
   - sessionStorage size <1MB for typical demo (50 points)

4. ✅ **Zero Backend Dependency**

   - No network calls during Epic 1 usage
   - Network tab empty except for static assets

5. ✅ **LinkedIn Demo Ready**

   - Professional visual polish
   - No console errors
   - Smooth performance (60fps interactions)

6. ✅ **Epic 3 Migration Ready**
   - DTOs stable, documented
   - ViewModel layer isolates UI from API changes
   - Custom hooks provide clean swap point for real API

## Traceability Mapping

This section maps PRD requirements → Epic 1 stories → acceptance criteria → implementation components.

| PRD Requirement                             | Epic 1 Stories  | Acceptance Criteria | Implementation Components                                                     |
| ------------------------------------------- | --------------- | ------------------- | ----------------------------------------------------------------------------- |
| **FR001**: Auto-popup on drag-drop          | Story 1.4       | AC-4                | `MappingPopup.tsx`, React Flow onDrop handler                                 |
| **FR002**: AI suggestions with confidence   | Story 1.3       | AC-3                | `AI223PSuggestionService`, `PatternMatcher`                                   |
| **FR003**: Manual override dropdowns        | Story 1.5, 1.6  | AC-5, AC-6          | `EquipmentTypeDropdown.tsx`, `DeviceTypeDropdown.tsx`, `PropertyDropdown.tsx` |
| **FR004**: Real-time SHACL validation       | Story 1.7       | AC-7                | `SHACLValidationService`, validation UI feedback                              |
| **FR005**: Visual badge indicators          | Story 1.8       | AC-8                | `PointBadge.tsx`, left panel integration                                      |
| **FR006**: Equipment type auto-fill         | Story 1.10      | AC-10               | Device history tracking in Zustand store                                      |
| **NFR001**: <100ms popup open               | Story 1.4, 1.12 | AC-4, AC-12         | Lazy loading, optimized rendering                                             |
| **NFR002**: <500ms AI response              | Story 1.3       | AC-3                | Synchronous pattern matching (no network)                                     |
| **NFR003**: Keyboard accessible             | Story 1.12      | AC-12               | shadcn/ui components, focus management                                        |
| **Data Model**: Type-safe DTOs              | Story 1.1       | AC-1                | Zod schemas, TypeScript interfaces                                            |
| **Service Layer**: Mock BuildingMOTIF       | Story 1.2       | AC-2                | `MockBuildingMOTIFService`, JSON templates                                    |
| **State Management**: In-memory persistence | Story 1.9       | AC-9                | Zustand `mapping223p` slice, sessionStorage                                   |

**Component-Level Traceability:**

```
domains/223p/
├── components/
│   ├── MappingPopup.tsx           → AC-4 (Story 1.4)
│   ├── EquipmentTypeDropdown.tsx  → AC-5 (Story 1.5)
│   ├── DeviceTypeDropdown.tsx     → AC-6 (Story 1.6)
│   ├── PropertyDropdown.tsx       → AC-6 (Story 1.6)
│   ├── SpaceComboBox.tsx          → AC-4 (Story 1.4)
│   └── PointBadge.tsx             → AC-8 (Story 1.8)
├── services/
│   ├── ai-suggestion.service.ts   → AC-3 (Story 1.3)
│   ├── shacl-validation.service.ts → AC-7 (Story 1.7)
│   └── mock-buildingmotif.service.ts → AC-2 (Story 1.2)
├── schemas/
│   ├── dto.schemas.ts             → AC-1 (Story 1.1)
│   └── enum.schemas.ts            → AC-1 (Story 1.1)
└── api/
    └── mappings.api.ts            → AC-9 (Story 1.9)
```

**User Journey Traceability:**

1. **Point Discovery → Semantic Tagging**

   - User drags BACnet point from left panel (existing functionality)
   - Popup opens automatically (Story 1.4 → AC-4)
   - AI suggests mappings (Story 1.3 → AC-3)
   - User confirms or overrides (Story 1.5, 1.6 → AC-5, AC-6)
   - Mapping saved to state (Story 1.9 → AC-9)
   - Badge appears in left panel (Story 1.8 → AC-8)

2. **Multi-Point Workflow → Auto-fill Efficiency**

   - First point from device: Full AI suggestion workflow
   - Subsequent points: Equipment + Space auto-fill (Story 1.10 → AC-10)
   - Time saved: 5 min → 30 sec per point (90% reduction)

3. **Skip Workflow → Optional Adoption**
   - User can skip mapping (Story 1.11 → AC-11)
   - Point added to canvas without 223P metadata
   - No badge shown, no space assignment

## Risks, Assumptions, Open Questions

### Risks

| Risk                                                   | Impact                                                        | Mitigation Strategy                                                                                   | Owner                        |
| ------------------------------------------------------ | ------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------- | ---------------------------- |
| **BuildingMOTIF API structure unknown**                | High - DTOs may need significant refactor in Epic 3           | DTO/ViewModel separation isolates UI from API changes; mappers absorb complexity                      | Architecture                 |
| **SHACL validation rules more complex than mock**      | Medium - Mock only validates BACnet object type compatibility | Epic 3 will spike real SHACL engine; ViewModel interface stays stable                                 | Backend Integration (Epic 3) |
| **Space URN format not finalized**                     | Low - Affects Epic 3 API contract                             | Use string URN in Epic 1; Epic 3 spike determines server-generated vs client format                   | API Design (Epic 3)          |
| **Pattern matching AI insufficient (<85% confidence)** | Medium - Users may lose trust in AI suggestions               | Monitor confidence scores in LinkedIn demo; gather real point names from integrators; refine patterns | AI Engineering               |
| **sessionStorage quota exceeded (>5MB)**               | Low - Only affects demos with >500 points                     | Limit demo to 50-100 points; Epic 5 adds real persistence                                             | State Management (Epic 5)    |
| **Performance degradation with 100+ tagged points**    | Low - Badge rendering slowdown                                | Virtualize left panel list; lazy load badges; profile performance                                     | UI Optimization (Story 1.12) |

### Assumptions

| Assumption                                                       | Validation Strategy                                                                | Epic 1 Status                       |
| ---------------------------------------------------------------- | ---------------------------------------------------------------------------------- | ----------------------------------- |
| **sessionStorage capacity sufficient for demo**                  | Store 100 points = ~200KB (well under 5MB quota)                                   | ✅ Safe for Epic 1 scope            |
| **NREL BuildingMOTIF 223P template library stable**              | Templates from systems.yml, devices.yml, properties.yml won't change significantly | ✅ Using v0.10.0 snapshot           |
| **Pattern matching achieves 85%+ confidence on common patterns** | Test with real BACnet point names: "VAV-2-01_ZoneTemp", "AHU-1_ReturnAirTemp"      | ⏳ To be validated in LinkedIn demo |
| **Chrome browser only (NFR004)**                                 | No cross-browser testing required for Epic 1                                       | ✅ Documented constraint            |
| **No backend authentication needed for Epic 1**                  | Mock services run client-side, no API keys or auth                                 | ✅ True for Epic 1                  |
| **React Flow handles 100+ nodes without performance issues**     | Existing Designer app already tested with 50+ nodes                                | ✅ Within tested limits             |
| **shadcn/ui components meet accessibility requirements**         | Components have built-in ARIA labels and keyboard support                          | ✅ Industry-standard library        |

### Open Questions

| Question                                                                      | Impact if Unresolved                                           | Resolution Plan                                                                                | Target Epic       |
| ----------------------------------------------------------------------------- | -------------------------------------------------------------- | ---------------------------------------------------------------------------------------------- | ----------------- |
| **Should Space be required or optional for mapping?**                         | UX friction vs data completeness trade-off                     | Made optional in AC-4; gather integrator feedback in demo                                      | Epic 1 (resolved) |
| **Space URN format: server-generated vs client-generated?**                   | Client generates UUID vs server assigns on persist             | Spike BuildingMOTIF API in Epic 3                                                              | Epic 3            |
| **Does Space auto-fill from previous points in same device?**                 | User convenience vs accuracy (different rooms in same device?) | Implemented in AC-10; works per device prefix (e.g., VAV-2-01)                                 | Epic 1 (resolved) |
| **What happens if user changes 223P mapping of already-connected G36 point?** | G36 connection validation may break                            | Defined in Epic 2 Story 2.18: re-validate connections                                          | Epic 2            |
| **BuildingMOTIF API pagination strategy for large template libraries?**       | May need infinite scroll or search-first approach              | Spike in Epic 3; mock uses full list (8 systems, 18 devices, 25 properties)                    | Epic 3            |
| **How to handle custom equipment types not in NREL templates?**               | Extensibility for integrators with non-standard equipment      | Future: Allow custom template upload; Epic 1 uses fixed library                                | Epic 6+           |
| **Should AI suggestions include confidence reasoning tooltip?**               | Explainability vs UI clutter                                   | Currently shows reasoning in FieldRecommendation but not exposed in UI; defer to user feedback | Epic 2 (optional) |

**Epic 1 Decision Log:**

- **2025-11-01**: Space made optional after reviewing user workflow - some points (actuators, setpoints) don't map to physical spaces
- **2025-11-01**: Space auto-fill implemented per device prefix to handle multi-point devices in same room
- **2025-11-01**: DTO/ViewModel separation chosen to isolate Epic 3 API changes from UI components

## Test Strategy Summary

**N/A for Epic 1** - Mock implementation with manual testing only.

**Rationale:**

- Epic 1 uses mock services with deterministic behavior (no network, no async complexity)
- Primary validation happens through LinkedIn demo and integrator feedback
- Full test suite will be implemented in Epic 3 when real BuildingMOTIF API integration occurs

**Manual Testing Approach (Epic 1):**

1. **Smoke Testing**: Verify each story's acceptance criteria manually
2. **Demo Scenarios**: Prepare 3-5 realistic BACnet point workflows for LinkedIn showcase
3. **Edge Cases**: Test skip workflow, low-confidence suggestions, validation errors
4. **Performance Validation**: Measure popup open time, AI response time, badge rendering

**Future Test Strategy (Epic 3+):**

- **Unit Tests**: DTO validation (Zod), mappers, AI pattern matching
- **Integration Tests**: React Query hooks, BuildingMOTIF API client, state persistence
- **Component Tests**: Dropdowns, popup modal, badges (React Testing Library)
- **E2E Tests**: Complete workflows (Playwright or Cypress)
- **Performance Tests**: Load 100+ points, measure render times
