# Story 1B.4: G36 Configuration Panel

Status: ready-for-dev

## Story

As a building controls engineer,
I want to configure G36 block parameters,
So that I can customize the controller for my zone.

## Acceptance Criteria

1. Click block opens configuration panel
2. All instance responses (GET/PUT/POST) return flat `parameters` + `categories` mapping
3. Parameters grouped into Basic (Units, Sensors - expanded) and Advanced (collapsed) sections
4. Unit selection dropdown for temperature (K/C/F) and airflow (m³/s, cfm, L/s, m³/h)
5. Conditional visibility: sensor toggle changes hide/show related panel fields AND node input handles
6. Save button calls `PUT /api/v1/g36/vav-reheat/instances/{instance_id}` and updates node handles
7. Uses existing side panel patterns from Designer (FunctionPropertiesContainer pattern)
8. Component tests pass

## Tasks / Subtasks

- [ ] Task 0: Add Categories Mapping to Instance Responses (AC: #2)

  - [ ] Add `category` to `json_schema_extra` in `parameters.py` for each field
  - [ ] Domain categories: units, sensors, airflows, controllerGains, timing, thresholds, hysteresis
  - [ ] Add `categories` field to `GetInstanceResponse`, `CreateInstanceResponse`, `UpdateInstanceResponse`
  - [ ] Categories structure: `{ "units": ["temperatureUnit", "airflowUnit"], "sensors": [...], ... }`
  - [ ] Build categories mapping from ReheatParameters field metadata in controller
  - [ ] Update integration tests to verify categories in responses
  - [ ] Regenerate OpenAPI client types

- [ ] Task 1: Add getInstance/updateInstance to API Client (AC: #2, #6)

  - [ ] Add `getInstance(instanceId)` to `api/client.ts` wrapping generated SDK
  - [ ] Add `updateInstance(instanceId, params)` to `api/client.ts`
  - [ ] Write unit tests for client functions

- [ ] Task 2: Create G36ConfigurationPanel Component (AC: #1, #7)

  - [ ] Create `src/components/panels/g36-configuration-panel.tsx`
  - [ ] Follow FunctionPropertiesContainer pattern (Sheet + ScrollArea + SheetFooter)
  - [ ] Wire click handler on G36VavReheatNode card to open panel
  - [ ] Pass nodeId and instanceId to panel

- [ ] Task 3: Fetch and Display Parameters (AC: #2)

  - [ ] Call `getInstance` on panel mount to fetch current parameters + categories
  - [ ] Handle loading state with skeleton/spinner
  - [ ] Handle error state with toast notification
  - [ ] Populate form fields with fetched values

- [ ] Task 4: Parameter Category Grouping (AC: #3)

  - [ ] Use category metadata from getInstance response
  - [ ] Frontend maps domain categories to UX groups: Basic (units, sensors) vs Advanced (rest)
  - [ ] Create Basic section - expanded by default
  - [ ] Create Advanced section - collapsed by default
  - [ ] Use Collapsible component from shadcn/ui

- [ ] Task 5: Unit Selection Dropdowns (AC: #4)

  - [ ] Temperature unit Select: Kelvin (K), Celsius (C), Fahrenheit (F)
  - [ ] Airflow unit Select: m³/s, cfm, L/s, m³/h
  - [ ] Use generated TemperatureUnit and AirflowUnit types

- [ ] Task 6: Conditional Visibility - Panel Fields (AC: #5)

  - [ ] Hide CO2-related parameter fields when hasCO2Sensor=false
  - [ ] Hide hot water coil fields when hasHotWaterCoil=false
  - [ ] Hide occupancy fields when hasOccupancySensor=false
  - [ ] Hide window fields when hasWindowSensor=false

- [ ] Task 7: Sensor Params Control Node Input Handles (AC: #5)

  - [ ] Sensor params directly control handle visibility for sensor inputs
  - [ ] hasCO2Sensor=true → co2Concentration, co2Setpoint visible + required
  - [ ] hasHotWaterCoil=true → hotWaterPlantStatus visible + required
  - [ ] hasOccupancySensor=true → occupancyStatus visible + required
  - [ ] hasWindowSensor=true → windowStatus visible + required
  - [ ] When sensor=false, sensor handles hidden (not in dropdown, not on node)
  - [ ] Override inputs (heatingOff, overrideDamperPosition, overrideFlowSetpoint) remain in dropdown as optional
  - [ ] Update both visibleInputs and requiredInputs via updateNode store action

- [ ] Task 8: Save Functionality (AC: #6)

  - [ ] Manage form state with useState (avoid over-engineering with React Hook Form)
  - [ ] Add Apply/Cancel buttons in SheetFooter
  - [ ] Call `updateInstance` with updated parameters on Apply
  - [ ] Update node handles based on sensor config changes
  - [ ] Show success/error toast notification
  - [ ] Close panel on successful save

- [ ] Task 9: Write Component Tests (AC: #8)

  - [ ] Test clicking G36 node opens configuration panel
  - [ ] Test parameters fetched and displayed on mount
  - [ ] Test Basic/Advanced collapsible sections
  - [ ] Test unit dropdowns render with correct options
  - [ ] Test conditional field visibility in panel
  - [ ] Test sensor toggle updates node input handles
  - [ ] Test save calls API and updates store
  - [ ] Mock API calls using jest.mock

## Dev Notes

### Learnings from Previous Story

**From Story 1b-3-dto-layer-refactoring (Status: done)**

- **API Client Pattern**: `api/client.ts` wraps generated SDK
- **Generated Types**: `ReheatParameters` includes `temperatureUnit` and `airflowUnit` preferences
- **Unit Types**: `TemperatureUnit = 'K' | 'C' | 'F'`, `AirflowUnit = 'm3/s' | 'cfm' | 'L/s' | 'm3/h'`
- **Test Coverage**: 435 tests passing - maintain test health

### Architecture Patterns

**Input Handle Categories:**

1. **Sensor-controlled inputs** (visibility controlled by sensor params):
   | Sensor Parameter | Node Inputs (visible+required when true) |
   |---------------------|-------------------------------------------|
   | `hasCO2Sensor` | `co2Concentration`, `co2Setpoint` |
   | `hasHotWaterCoil` | `hotWaterPlantStatus` |
   | `hasOccupancySensor`| `occupancyStatus` |
   | `hasWindowSensor` | `windowStatus` |

2. **Override inputs** (always in dropdown, optional):
   - `heatingOff` - Override to close heating valve
   - `overrideDamperPosition` - Manual damper override (0=none, 1=close, 2=open)
   - `overrideFlowSetpoint` - Manual flow override (0=none, 1=zero, 2=cooling max, 3=min, 4=heating max)

**Response Schema (all instance endpoints):**

```json
{
  "instance_id": "550e8400-...",
  "parameters": {
    "temperatureUnit": "C",
    "airflowUnit": "cfm",
    "hasCO2Sensor": true,
    "minAirflow": 0.3,
    ...
  },
  "categories": {
    "units": ["temperatureUnit", "airflowUnit"],
    "sensors": ["hasCO2Sensor", "hasHotWaterCoil", "hasOccupancySensor", "hasWindowSensor"],
    "airflows": ["minAirflow", "maxCoolingAirflow", ...],
    "controllerGains": ["coolingControllerGain", ...],
    "timing": ["coolingIntegratorTime", ...],
    "thresholds": ["thresholdDischargeTemp1", ...],
    "hysteresis": ["tempHysteresis", ...]
  }
}
```

**Frontend UX Grouping:**

- **Basic (expanded by default)**: units, sensors
- **Advanced (collapsed by default)**: airflows, controllerGains, timing, thresholds, hysteresis

**Panel Pattern (FunctionPropertiesContainer):**

```typescript
<Sheet open={isOpen} onOpenChange={onClose}>
  <SheetContent className="w-[400px]">
    <SheetHeader>...</SheetHeader>
    <ScrollArea className="flex-1">
      <Collapsible defaultOpen>Basic...</Collapsible>
      <Collapsible>Advanced...</Collapsible>
    </ScrollArea>
    <SheetFooter>
      <Button variant="outline" onClick={handleCancel}>Cancel</Button>
      <Button onClick={handleApply}>Apply</Button>
    </SheetFooter>
  </SheetContent>
</Sheet>
```

**Updating Node Handles on Save:**

```typescript
updateNode({
  type: "UPDATE_CONTROL_SEQUENCE_HANDLES",
  nodeId,
  handles: {
    ...currentHandles,
    visibleInputs: computeVisibleInputs(parameters),
  },
});
```

### Project Structure Notes

**Files to create/modify:**

- `apps/control-sequence-api-app/src/models/reheat/parameters.py` (MODIFY - add category metadata)
- `apps/control-sequence-api-app/src/dto/base_dto.py` (MODIFY - add categories to responses)
- `apps/control-sequence-api-app/src/controllers/vav_reheat_controller.py` (MODIFY - build categories mapping)
- `apps/designer/src/domains/control-sequence/api/client.ts` (MODIFY - add getInstance, updateInstance)
- `apps/designer/src/components/panels/g36-configuration-panel.tsx` (NEW)
- `apps/designer/src/components/nodes/g36-vav-reheat-node.tsx` (MODIFY - add click handler)

### Testing Standards

- Unit tests for panel component with jest.mock for API
- Integration tests to verify categories in instance responses
- Test conditional rendering based on sensor config
- Test node handle updates on sensor toggle

### References

- [FunctionPropertiesContainer](../../../../apps/designer/src/containers/function-properties/index.tsx)
- [ReheatParameters Model](../../../../apps/control-sequence-api-app/src/models/reheat/parameters.py)
- [Reheat Handles](../../../../apps/designer/src/domains/control-sequence/terminal-units/reheat/handles.ts)

## Dev Agent Record

### Context Reference

- docs/feature-development/g36-implementation/stories/1b-4-g36-configuration-panel.context.xml

### Agent Model Used

### Debug Log References

### Completion Notes List

### File List

## Change Log

| Date       | Change                                                                                                 |
| ---------- | ------------------------------------------------------------------------------------------------------ |
| 2025-12-16 | Story drafted from epics.md                                                                            |
| 2025-12-16 | Finalized: flat parameters + categories approach, removed schema endpoint, added sensor-handle mapping |
| 2025-12-19 | Senior Developer Review notes appended                                                                 |

---

## Senior Developer Review (AI)

### Reviewer

Amol

### Date

2025-12-19

### Outcome

**APPROVE** ✅

The implementation meets all acceptance criteria with comprehensive test coverage. The architecture follows established patterns (FunctionPropertiesContainer, React Query for data fetching) and maintains separation of concerns.

### Summary

The G36 Configuration Panel story has been successfully implemented with:

- Full panel component with Sheet pattern matching FunctionPropertiesContainer
- API client with `getInstance`, `updateInstance`, and unit conversion support
- Backend categories mapping in instance responses
- Sensor toggle → node input handle synchronization
- 22 component tests + 53 API client tests passing

### Key Findings

**MEDIUM Severity:**

1. **OCP Violation in Factory/Serializer** (SOLID - Open/Closed Principle)

   - **Files:** `factory.ts:49-124` and `serializer.ts:229-329`
   - **Issue:** Large `switch` statements keyed by `NodeType` require edits in multiple places when adding a new node type. Adding `g36-vav-reheat` required modifications to both files.
   - **Impact:** Violates OCP - code is not closed for modification when extending with new node types.
   - **Suggestion:** Introduce a **Node Registry Pattern**:

     ```typescript
     // node-registry.ts
     type NodeHandler = {
       create: (params: CreateParams) => DataNode | Promise<DataNode>;
       serialize: (node: DataNode) => SerializedData;
       deserialize: (data: SerializedData) => DataNode | Promise<DataNode>;
     };

     const nodeRegistry = new Map<NodeType, NodeHandler>();

     export function registerNodeType(type: NodeType, handler: NodeHandler) {
       nodeRegistry.set(type, handler);
     }

     // Each node module registers itself on import
     // g36-vav-reheat-node.ts
     registerNodeType("g36-vav-reheat", {
       create: G36VavReheatNode.create,
       serialize: (node) => node.toSerializable(),
       deserialize: async (data) => G36VavReheatNode.create(data),
     });
     ```

   - **Benefit:** New node types can be added by creating a single module that self-registers, without modifying factory.ts or serializer.ts.

**LOW Severity:**

- Note: The `BASIC_CATEGORIES` includes `'features'` but the mock data and actual API returns `'units'` and `'sensors'` as basic categories. This is a minor inconsistency that doesn't affect functionality since only matching categories are rendered.

### Acceptance Criteria Coverage

| AC# | Description                                                                                         | Status         | Evidence                                                                                                                                                       |
| --- | --------------------------------------------------------------------------------------------------- | -------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| AC1 | Click block opens configuration panel                                                               | ✅ IMPLEMENTED | `control-sequence-node-ui.tsx:56` - `useState(false)` for `isPanelOpen`, line 229: `onClick={() => setIsPanelOpen(true)}`                                      |
| AC2 | All instance responses return flat `parameters` + `categories` mapping                              | ✅ IMPLEMENTED | `base_dto.py:36-69` - `InstanceResponseWithCategories` includes `parameters`, `categories`, `inputCategories`, `outputCategories`, `parameterToRequiredInputs` |
| AC3 | Parameters grouped into Basic (expanded) and Advanced (collapsed) sections                          | ✅ IMPLEMENTED | `g36-configuration-panel.tsx:168-206` - Basic Settings with `defaultOpen` and Advanced Settings collapsed                                                      |
| AC4 | Unit selection dropdown for temperature (K/C/F) and airflow (m³/s, cfm, L/s, m³/h)                  | ✅ IMPLEMENTED | `types.ts:68-79` - `TEMPERATURE_UNIT_OPTIONS` and `AIRFLOW_UNIT_OPTIONS` with all required units                                                               |
| AC5 | Conditional visibility: sensor toggle changes hide/show related panel fields AND node input handles | ✅ IMPLEMENTED | `g36-configuration-panel.tsx:53-66` - `computeVisibleInputs` uses `parameterToRequiredInputs` mapping; tests verify sensor toggle → handle updates             |
| AC6 | Save button calls PUT API and updates node handles                                                  | ✅ IMPLEMENTED | `g36-configuration-panel.tsx:107-120` - `handleSave` calls `updateMutation.mutateAsync`, then `onHandlesChange` and `onSaveParameters`                         |
| AC7 | Uses existing side panel patterns (FunctionPropertiesContainer)                                     | ✅ IMPLEMENTED | `g36-configuration-panel.tsx:141-233` - Sheet + SheetContent + ScrollArea + SheetFooter pattern                                                                |
| AC8 | Component tests pass                                                                                | ✅ IMPLEMENTED | 22 tests in `g36-configuration-panel.spec.tsx`, all passing                                                                                                    |

**Summary: 8 of 8 acceptance criteria fully implemented**

### Task Completion Validation

| Task                                                 | Marked As | Verified As | Evidence                                                                                                          |
| ---------------------------------------------------- | --------- | ----------- | ----------------------------------------------------------------------------------------------------------------- |
| Task 0: Add Categories Mapping to Instance Responses | [ ]       | ✅ DONE     | `base_dto.py:36-69` - Full categories structure implemented                                                       |
| Task 1: Add getInstance/updateInstance to API Client | [ ]       | ✅ DONE     | `client.ts:98-137` - Both functions implemented with tests                                                        |
| Task 2: Create G36ConfigurationPanel Component       | [ ]       | ✅ DONE     | `g36-configuration-panel/g36-configuration-panel.tsx` - Full component                                            |
| Task 3: Fetch and Display Parameters                 | [ ]       | ✅ DONE     | `g36-configuration-panel.tsx:36-48` - useInstanceQuery with loading/error states                                  |
| Task 4: Parameter Category Grouping                  | [ ]       | ✅ DONE     | `g36-configuration-panel.tsx:131-139` - basicCategories and advancedCategories                                    |
| Task 5: Unit Selection Dropdowns                     | [ ]       | ✅ DONE     | `category-fields.tsx:104-124` - UnitSelect for temperature and airflow                                            |
| Task 6: Conditional Visibility - Panel Fields        | [ ]       | ✅ DONE     | `category-fields.tsx:127-142` - SensorToggle renders based on sensor fields                                       |
| Task 7: Sensor Params Control Node Input Handles     | [ ]       | ✅ DONE     | `g36-configuration-panel.tsx:53-66` + `control-sequence-node-ui.tsx:420-427` - Panel updates handles via callback |
| Task 8: Save Functionality                           | [ ]       | ✅ DONE     | `g36-configuration-panel.tsx:107-120` - Full save flow with mutation                                              |
| Task 9: Write Component Tests                        | [ ]       | ✅ DONE     | `g36-configuration-panel.spec.tsx` - 22 tests covering all scenarios                                              |

**Summary: 10 of 10 tasks verified as complete (all tasks were done but checkboxes not marked)**

### Test Coverage and Gaps

**Tests Present:**

- Component tests: 22 tests in `g36-configuration-panel.spec.tsx`
- API client tests: 53 tests in `client.spec.ts` (includes getInstance, updateInstance, deleteFmu)
- Node tests: 20 tests in `g36-vav-reheat-node.spec.tsx`

**Test Categories Covered:**

- ✅ Panel rendering (title, badge, sections)
- ✅ Loading and error states
- ✅ Basic/Advanced section expand/collapse
- ✅ Save/Cancel functionality
- ✅ Sensor toggle → visible inputs computation
- ✅ API calls verification

**No significant test gaps identified.**

### Architectural Alignment

- ✅ Follows FunctionPropertiesContainer pattern (Sheet + ScrollArea + SheetFooter)
- ✅ Uses React Query for data fetching (useInstanceQuery, useUpdateInstanceMutation)
- ✅ API client wraps generated SDK following established pattern
- ✅ Backend returns categories mapping as specified in tech-spec
- ✅ No direct database leakage in API layer

### Security Notes

No security concerns identified. The panel:

- Uses existing authenticated API endpoints
- Does not expose sensitive data
- Follows established patterns for data handling

### Best-Practices and References

- [shadcn/ui Sheet component](https://ui.shadcn.com/docs/components/sheet)
- [React Query documentation](https://tanstack.com/query/latest)
- [openapi-ts client generation](https://heyapi.dev/)

### Action Items

**Code Changes Required:**

- None required - implementation is complete

**Advisory Notes:**

- Note: Consider marking task checkboxes as completed in the story file to reflect actual status
- Note: The `'features'` category in `BASIC_CATEGORIES` array is unused but harmless
