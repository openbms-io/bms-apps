# Story 1.3: AI Suggestion Mock Engine

**Epic:** Epic 1 - 223P Mapping UI with Mock DTOs
**Status:** done
**Created:** 2025-11-02
**Completed:** 2025-11-02
**Complexity:** 5 (Medium)
**Estimated Hours:** 4-6 hours

---

## User Story

**As a** BMS integrator,
**I want** AI-generated 223P suggestions based on BACnet point names,
**So that** I can verify suggestions instead of creating mappings from scratch.

---

## Acceptance Criteria

Reference: Tech Spec AC-3

### 1. ✅ Pattern Matching Rules

**Temperature sensors:**

- `ZoneTemp`, `RoomTemp`, `SpaceTemp` → `air-temperature`, Sensor, 95% confidence
- `SupplyTemp`, `ReturnTemp` → `air-temperature`, Sensor, 92% confidence

**Actuators:**

- `CoolingValve`, `ClgValve` → `Chilled Water Valve`, 88% confidence
- `DamperPos`, `DmprPos` → `Damper`, 85% confidence

**Status points:**

- `RunStatus`, `FanStatus` → `run-status`, Sensor, 90% confidence

**Ambiguous names:**

- `Temp1`, `Sensor2` → low confidence (<50%), no specific suggestion

### 2. ✅ Equipment Type Inference

- Device ID prefix parsing: `VAV-2-01_*` → "VAV Reheat Terminal Unit"
- Device ID prefix parsing: `AHU-1_*` → "Makeup Air Unit"
- Device ID prefix parsing: `CHW-*` → "Chilled Water System"
- Device ID prefix parsing: `HW-*` → "Hot Water System"
- Fallback: "Unknown" if no pattern match

### 3. ✅ Space Name Suggestion

- Parse device ID for room numbers: `VAV-2-01` → "Room 201"
- Detect mechanical rooms: `AHU-1` → "AHU-1 Mechanical Room"
- Reuse space from same device ID if already tagged

### 4. ✅ Confidence Score Calculation

- High confidence (85-95%): Exact pattern match + common naming convention
- Medium confidence (60-84%): Partial match or ambiguous
- Low confidence (<60%): No pattern match, fallback to generic

### 5. ✅ Recommendation Format

Returns `Equipment223PRecommendation` (using `FieldRecommendation<T>` from `lib/ai`) with:

- `equipmentType: FieldRecommendation<SystemType>`
- `space: FieldRecommendation<{ label, type }>` (optional)
- `deviceType: FieldRecommendation<DeviceType>`
- `observableProperty: FieldRecommendation<ObservableProperty>`
- `overallConfidence: number` (average of all fields)

Each `FieldRecommendation<T>` includes:

- `value: T` - The recommended value
- `confidence: number` - Confidence percentage (0-100)
- `reasoning: string` - Human-readable explanation
- `alternatives: Array<{ value: T, confidence: number }>` - Alternative suggestions

---

## Verification Checklist

**Test Case 1: High confidence temperature sensor**

- Input: `{ name: "VAV-2-01_ZoneTemp", objectType: "analog-input" }`
- Expected Output:
  - Equipment Type: "VAV Reheat Terminal Unit" (95% confidence)
  - Device Type: "Sensor" (95% confidence)
  - Property: "air-temperature" (95% confidence)
  - Space: "Room 201" (90% confidence)
  - Overall Confidence: ~94%

**Test Case 2: Actuator with clear naming**

- Input: `{ name: "VAV-2-01_DamperPos", objectType: "analog-output" }`
- Expected Output:
  - Equipment Type: "VAV Reheat Terminal Unit" (95% confidence)
  - Device Type: "Damper" (85% confidence)
  - Property: "position" (85% confidence)
  - Overall Confidence: ~88%

**Test Case 3: Ambiguous naming**

- Input: `{ name: "Temp1", objectType: "analog-input" }`
- Expected Output:
  - Device Type: "Sensor" (50% confidence)
  - Property: "air-temperature" (40% confidence)
  - Overall Confidence: <50%

**Performance:**

- Response time: <500ms for all patterns
- All suggestions synchronous (mock service, no network calls)

---

## Implementation Guidance

### File Structure

```
apps/designer/src/
├── lib/
│   └── ai/
│       ├── types.ts                      # FieldRecommendation<T> type
│       └── index.ts                      # Exports
└── domains/223p/
    └── services/
        ├── ai-suggestion.service.interface.ts  # IAISuggestionService
        └── mock-ai-suggestion.service.ts       # MockAISuggestionService
```

### AI Utility Types

```typescript
// lib/ai/types.ts

export interface FieldRecommendation<T> {
  value: T;
  confidence: number; // 0-100
  reasoning: string;
  alternatives: Array<{
    value: T;
    confidence: number;
  }>;
}

export interface Equipment223PRecommendation {
  equipmentType: FieldRecommendation<SystemType>;
  space?: FieldRecommendation<{ label: string; type: SpaceType }>;
  deviceType: FieldRecommendation<DeviceType>;
  observableProperty: FieldRecommendation<ObservableProperty>;
  overallConfidence: number;
}
```

### Service Interface

```typescript
// domains/223p/services/ai-suggestion.service.interface.ts

import type { Equipment223PRecommendation } from "@/lib/ai";
import type { BACnetPointDTO } from "../schemas";

export interface IAISuggestionService {
  /**
   * Generate 223P mapping suggestions based on BACnet point metadata
   *
   * Analyzes point name, object type, device ID patterns to suggest:
   * - Equipment type (e.g., "VAV Reheat Terminal Unit")
   * - Space name and type
   * - Device type (e.g., "Sensor", "Damper")
   * - Observable property (e.g., "air-temperature")
   *
   * @param point - BACnet point with name, objectType, deviceId
   * @returns Recommendation with confidence scores and alternatives
   */
  suggestMapping(point: BACnetPointDTO): Equipment223PRecommendation;
}
```

### Pattern Matching Implementation Pattern

```typescript
// domains/223p/services/mock-ai-suggestion.service.ts

export class MockAISuggestionService implements IAISuggestionService {
  suggestMapping(point: BACnetPointDTO): Equipment223PRecommendation {
    const propertyRec = this.matchObservableProperty(
      point.name,
      point.objectType,
    );
    const deviceRec = this.matchDeviceType(
      point.name,
      point.objectType,
      propertyRec.value,
    );
    const equipmentRec = this.matchEquipmentType(point.name);
    const spaceRec = this.matchSpace(point.name);

    const overallConfidence = this.calculateOverallConfidence([
      propertyRec.confidence,
      deviceRec.confidence,
      equipmentRec.confidence,
      spaceRec?.confidence ?? 0,
    ]);

    return {
      equipmentType: equipmentRec,
      space: spaceRec,
      deviceType: deviceRec,
      observableProperty: propertyRec,
      overallConfidence,
    };
  }

  private matchObservableProperty(
    name: string,
    objectType: string,
  ): FieldRecommendation<ObservableProperty> {
    const lowerName = name.toLowerCase();

    // High confidence patterns (85-95%)
    if (
      lowerName.includes("zonetemp") ||
      lowerName.includes("roomtemp") ||
      lowerName.includes("spacetemp")
    ) {
      return {
        value: "air-temperature",
        confidence: 95,
        reasoning:
          "Point name indicates zone/room/space temperature measurement",
        alternatives: [{ value: "water-temperature", confidence: 20 }],
      };
    }

    // ... more patterns
  }

  private calculateOverallConfidence(scores: number[]): number {
    const validScores = scores.filter((s) => s > 0);
    return validScores.length > 0
      ? Math.round(validScores.reduce((a, b) => a + b, 0) / validScores.length)
      : 0;
  }
}
```

### Pattern Matching Rules Reference

**Temperature Patterns:**

- `zonetemp`, `roomtemp`, `spacetemp` → air-temperature (95%)
- `supplytemp`, `returntemp` → air-temperature (92%)
- `chwtemp`, `hwtemp` → water-temperature (90%)

**Actuator Patterns:**

- `coolingvalve`, `clgvalve` → Chilled Water Valve (88%)
- `heatingvalve`, `htgvalve` → Hot Water Valve (88%)
- `damperpos`, `dmprpos` → Damper (85%)

**Status Patterns:**

- `runstatus`, `fanstatus` → run-status (90%)
- `flowstatus` → flow-status (90%)

**Equipment Prefix Patterns:**

- `VAV-*` → VAV Reheat Terminal Unit
- `AHU-*` → Makeup Air Unit
- `CHW-*` → Chilled Water System
- `HW-*` → Hot Water System
- `EF-*` → Exhaust Air Unit

**Space Parsing:**

- `VAV-2-01` → Room 201 (floor 2, room 1)
- `AHU-1` → AHU-1 Mechanical Room
- Same device prefix → reuse previous space

---

## Technical Notes

### Why Pattern Matching Instead of Real AI?

**Epic 1 Focus:**

- Mock data allows UI component development
- Pattern matching provides predictable, testable behavior
- No LLM API costs during development

**Epic 3 Migration:**

- Replace `MockAISuggestionService` with `ApiAISuggestionService`
- Keep same `IAISuggestionService` interface
- UI components unchanged

### Confidence Score Guidelines

**High (85-95%):**

- Exact string match with common naming conventions
- Clear object type alignment (AI for sensors, AO for actuators)

**Medium (60-84%):**

- Partial string match
- Ambiguous but probable

**Low (<60%):**

- Generic naming ("Temp1", "Sensor2")
- No clear pattern match

### Performance Requirements

- All pattern matching synchronous (no async operations)
- Response time <100ms (mock data, no network)
- Suitable for real-time dropdown pre-fill

---

## Prerequisites

**Story 1.2** ✅ Complete

- Requires: `MockBuildingMOTIFService` for valid template values

**Story 1.1** ✅ Complete

- Requires: `SystemType`, `DeviceType`, `ObservableProperty` types

---

## Dependencies

**Stories that depend on this:**

- Story 1.4: 223P Mapping Popup Modal (needs AI suggestions for pre-fill)
- Story 1.5: Equipment Type Dropdown (displays AI confidence badges)

---

## Definition of Done

- [ ] `FieldRecommendation<T>` type created in `lib/ai/types.ts`
- [ ] `Equipment223PRecommendation` type created
- [ ] `IAISuggestionService` interface defined
- [ ] `MockAISuggestionService` implements all pattern matching rules
- [ ] Temperature sensor patterns working (95% confidence)
- [ ] Actuator patterns working (85-88% confidence)
- [ ] Equipment type inference from device ID prefixes
- [ ] Space name suggestion from device IDs
- [ ] Ambiguous names return low confidence (<50%)
- [ ] Overall confidence calculation accurate
- [ ] Response time <500ms verified
- [ ] TypeScript compiles without errors
- [ ] Code follows project conventions
- [ ] Files committed to git with descriptive commit message

---

## References

- **Tech Spec:** AC-3 (lines 2497-2545)
- **Story 1.1:** DTO interfaces and types
- **Story 1.2:** MockBuildingMOTIFService
- **ASHRAE 223P Standard:** Observable property definitions
