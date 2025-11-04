# bms-apps - Epic Breakdown

**Author:** Amol
**Date:** 2025-11-01
**Project Level:** 4
**Target Scale:** 71-87 stories total

---

## Overview

This document provides the detailed epic breakdown for the ASHRAE 223P AI + G36 integration project, expanding on the high-level epic list in the [PRD](./PRD.md).

Each epic includes:

- Expanded goal and value proposition
- Complete story breakdown with user stories
- Acceptance criteria for each story
- Story sequencing and dependencies

**Epic Sequencing Principles:**

- Epic 1-2 deliver UI mockups for LinkedIn feedback (no backend)
- Epic 3-4 add real backend integration (zero UI changes)
- Epic 5-6 add persistence and BOPTest verification
- Stories within epics are vertically sliced and sequentially ordered
- No forward dependencies - each story builds only on previous work

---

## Epic 1: 223P Mapping UI with Mock DTOs

**Expanded Goal:**

Build complete 223P mapping user experience with mock BuildingMOTIF service layer to validate workflow integration hypothesis with BMS integrators. Focus on demonstrating that embedding semantic tagging into the BACnet discovery workflow reduces friction enough for adoption. Includes localStorage persistence for demo continuity.

**Value Delivery:**

This epic enables gathering real-world feedback from 5+ BMS integrators on whether the AI-assisted workflow integration actually solves the adoption problem before investing in backend infrastructure.

**Progress:**

- Stories 1.1-1.11: ✅ Complete (Core tagging workflow)
- Stories 1.12-1.16: 🔄 In Progress (Display, editing, persistence, polish)
- Total: 16 stories

### Stories

**Story 1.1: Define BuildingMOTIF DTO Interfaces**

As a developer,
I want TypeScript interfaces for all BuildingMOTIF DTOs,
So that mock and real services share identical contracts.

**Acceptance Criteria:**

1. TemplateDTO interface defined (equipmentType, deviceType, observableProperty)
2. EquipmentDTO interface defined with SHACL validation fields
3. ValidationResultDTO interface defined (errors, warnings, isValid)
4. All DTOs include schemaVersion field for future migration
5. Zod schemas created for runtime validation
6. DTOs documented with JSDoc comments

**Prerequisites:** None

---

**Story 1.2: Create Mock BuildingMOTIF Service**

As a developer,
I want a mock BuildingMOTIF service implementing the DTO interfaces,
So that UI components can be built without backend dependency.

**Acceptance Criteria:**

1. MockBuildingMOTIFService class implements BuildingMOTIFService interface
2. getTemplates() returns 8 equipment types (VAV, AHU, Boiler, Chiller, Fan, Pump, Damper, Valve)
3. getDeviceTypes() returns 15 device types (sensors, actuators, setpoints)
4. getObservableProperties() returns 25+ properties (temperature, pressure, flow, etc.)
5. Mock data loaded from JSON files in /mocks directory
6. Service returns Promises to match async API behavior

**Prerequisites:** Story 1.1

---

**Story 1.3: AI Suggestion Mock Engine**

As a BMS integrator,
I want AI-generated 223P suggestions based on point names,
So that I can verify suggestions instead of creating mappings from scratch.

**Acceptance Criteria:**

1. suggestMapping(point: BACnetPointDTO) returns EquipmentDTO with confidence score
2. Pattern matching: "ZoneTemp" → "Zone Air Temperature Sensor" (95% confidence)
3. Pattern matching: "CoolingValve" → "Cooling Valve Actuator" (88% confidence)
4. Pattern matching: "DamperPos" → "Damper Position Actuator" (85% confidence)
5. Ambiguous names (e.g., "Temp1") return low confidence (< 50%)
6. Equipment type inferred from point grouping (e.g., VAV-2-01\_\* → VAV Terminal Unit)
7. Confidence score calculation based on pattern match quality

**Prerequisites:** Story 1.2

---

**Story 1.4: 223P Mapping Popup Modal Component**

As a BMS integrator,
I want a 223P mapping popup that appears when I drag a BACnet point onto the canvas,
So that semantic tagging is embedded in my normal workflow.

**Acceptance Criteria:**

1. Modal opens automatically on BACnet point drop event
2. Modal displays point name, description, units, object type
3. shadcn/ui Dialog component used for modal
4. Equipment type dropdown pre-filled with AI suggestion
5. Device type dropdown pre-filled with AI suggestion
6. Observable property dropdown pre-filled with AI suggestion
7. Confidence score displayed for each suggestion
8. "Confirm" button saves mapping and closes modal
9. "Skip" button closes modal without saving
10. Modal is keyboard accessible (ESC to close, Tab navigation)

**Prerequisites:** Story 1.3

---

**Story 1.5: Equipment Type Dropdown with Search**

As a BMS integrator,
I want to search and select equipment types in the mapping popup,
So that I can quickly find the correct type when AI suggestion is wrong.

**Acceptance Criteria:**

1. Dropdown shows all 8 equipment types from mock service
2. Search/filter functionality (type to filter list)
3. Currently selected item highlighted
4. AI-suggested item marked with badge/icon
5. shadcn/ui Select or Combobox component used
6. Dropdown closes on selection
7. Keyboard navigation (arrow keys, Enter to select)

**Prerequisites:** Story 1.4

---

**Story 1.6: Device Type and Property Dropdowns**

As a BMS integrator,
I want device type and observable property dropdowns with the same UX as equipment dropdown,
So that I have consistent interface for all 223P selections.

**Acceptance Criteria:**

1. Device type dropdown shows 15 device types with search
2. Observable property dropdown shows 25+ properties with search
3. Both dropdowns use same component/styling as equipment dropdown
4. AI suggestions highlighted in each dropdown
5. Keyboard accessible

**Prerequisites:** Story 1.5

---

**Story 1.7: SHACL Validation Mock**

As a BMS integrator,
I want real-time validation feedback when I select incompatible 223P mappings,
So that I catch configuration errors before saving.

**Acceptance Criteria:**

1. validateMapping() mock service method checks BACnet object type compatibility
2. Rule: Actuator requires AO/BO object type (not AI/BI)
3. Rule: Sensor requires AI/BI object type (not AO/BO)
4. Validation runs on dropdown selection change
5. Validation errors displayed below affected dropdown (red text)
6. Warning icon appears next to invalid selection
7. "Confirm" button disabled when validation fails
8. Example error message: "Actuator requires AO/BO object type, found AI"

**Prerequisites:** Story 1.4

---

**Story 1.8: Left Panel 223P Metadata Badges**

As a BMS integrator,
I want to see which BACnet points have 223P tags in the left sidebar,
So that I can easily identify tagged vs untagged points.

**Acceptance Criteria:**

1. Tagged points show badge icon (🏷️) next to point name
2. Hover tooltip displays: "Equipment | Device | Property"
3. Example: "VAV | Temp Sensor | Zone Air Temp"
4. Badge only appears after point is successfully tagged
5. Badge updates if mapping is changed
6. Badge styling uses Tailwind CSS

**Prerequisites:** Story 1.4

---

**Story 1.9: In-Memory State Management for 223P Mappings**

As a developer,
I want state management for 223P mappings,
So that mapped points persist during the session for demo purposes.

**Acceptance Criteria:**

1. ✅ Implemented using React Query + sessionStorage (not Zustand)
2. ✅ `useMappingsQuery()` hook returns `Map<pointId, Equipment223PDTO>`
3. ✅ `useCreateEquipmentMapping()` mutation adds/updates mappings
4. ✅ State survives component unmounts (sessionStorage)
5. ✅ State cleared on browser refresh (sessionStorage behavior)
6. Note: Replaced Zustand approach with React Query for better data fetching patterns

**Prerequisites:** Story 1.4

---

**Story 1.10: Auto-fill Equipment Type from Previous Point**

As a BMS integrator,
I want the equipment type to auto-fill based on previous points from the same device,
So that I don't have to re-select VAV for every VAV-2-01 point.

**Acceptance Criteria:**

1. When mapping second+ point from same device (e.g., VAV-2-01\_\*)
2. Equipment type pre-filled from first point's mapping
3. AI still suggests device/property based on point name
4. User can override auto-filled equipment type
5. Works across multiple equipment instances

**Prerequisites:** Story 1.9

---

**Story 1.11: Cancel/Skip Mapping Workflow**

As a BMS integrator,
I want to skip 223P mapping for individual points,
So that I can proceed with visual flow without being forced to tag every point.

**Acceptance Criteria:**

1. "Skip" button in popup closes modal without saving
2. Point added to canvas without 223P metadata
3. No badge appears in left panel for skipped point
4. Skipped points can be tagged later (future story)
5. ESC key also skips mapping

**Prerequisites:** Story 1.4

---

**Story 1.12: Edit 223P Mapping from Left Sidebar**

As a BMS integrator,
I want to edit existing 223P mappings from the left sidebar,
So that I can correct mistakes without re-dropping the point on canvas.

**Acceptance Criteria:**

1. Right-click or click edit icon on tagged point in sidebar opens 223P modal
2. Modal pre-filled with existing mapping values
3. Modal title shows "Edit 223P Mapping" (not "Tag BACnet Point")
4. Confirming updates the existing mapping
5. Canceling/ESC closes modal without changes
6. Sidebar badge updates immediately after edit
7. Canvas node badge updates if point is already on canvas

**Prerequisites:** Story 1.8

---

**Story 1.13: Skip 223P Modal for Already-Tagged Points**

As a BMS integrator,
I want already-tagged points to drop directly onto canvas without opening the modal,
So that I don't have to re-tag points I've already configured.

**Acceptance Criteria:**

1. When dropping tagged point on canvas, modal does NOT open
2. Point added to canvas immediately with existing 223P metadata
3. Canvas node displays 223P badge (see Story 1.14)
4. Can still edit mapping from sidebar (Story 1.12) or canvas context menu
5. Visual feedback shows point was added with existing tags
6. Tooltip on canvas node shows mapping summary

**Prerequisites:** Story 1.8, Story 1.9

---

**Story 1.14: Display 223P Metadata on Canvas Nodes**

As a BMS integrator,
I want canvas nodes to visually indicate they have 223P tags,
So that I can see semantic metadata directly on my visual flow.

**Acceptance Criteria:**

1. Tagged BACnet nodes show badge icon (🏷️) in node header
2. Badge appears for nodes created with 223P confirmation
3. Badge persists when node is moved/edited
4. Hover tooltip shows full mapping: "Equipment | Device | Property"
5. Example: "VAV Terminal Unit | Zone Air Temperature Sensor | Zone Air Temperature"
6. Badge styling consistent with sidebar badges (Story 1.8)
7. Untagged nodes show no badge
8. Right-click node → "Edit 223P Mapping" menu option (optional enhancement)

**Prerequisites:** Story 1.13

---

**Story 1.15: Persist 223P Mappings Across Page Refresh**

As a BMS integrator,
I want my 223P mappings to persist after page refresh,
So that I don't lose my tagging work during the demo session.

**Acceptance Criteria:**

1. All 223P mappings saved to localStorage on confirm/edit
2. Mappings restored from localStorage on page load
3. Storage key format: `223p-mappings-${projectId}`
4. Sidebar badges appear immediately on page load for tagged points
5. Already-tagged points skip modal when dropped (using persisted data)
6. Canvas nodes show badges for points with persisted mappings
7. Data survives browser refresh, tab close/reopen
8. Data cleared when explicitly logging out or clearing browser data
9. Handle localStorage quota exceeded gracefully (show warning)
10. Version field in stored data for future migration

**Technical Notes:**

- Use `localStorage.setItem()` on mapping save
- Use `localStorage.getItem()` on app initialization
- JSON serialize/deserialize `Map<pointId, Equipment223PDTO>`
- Initialize React Query cache from localStorage on mount
- Optional: debounce writes to avoid excessive localStorage updates

**Prerequisites:** Story 1.9, Story 1.14

---

**Story 1.16: UI Polish and Accessibility**

As a BMS integrator,
I want polished, accessible UI for 223P mapping,
So that the LinkedIn demo looks professional and works for all users.

**Acceptance Criteria:**

1. Consistent spacing and typography (shadcn/ui design tokens)
2. Loading states for dropdowns
3. Error states with clear messaging
4. Focus management (auto-focus first dropdown on modal open)
5. Screen reader labels for all interactive elements
6. Keyboard-only navigation works smoothly
7. Color contrast meets WCAG AA standards
8. 223P badge styling consistent across sidebar and canvas
9. Edit tag interactions are keyboard accessible
10. Screen reader announces when point is tagged/untagged
11. Loading states for mapping persistence operations

**Prerequisites:** All Epic 1 stories (1.1-1.15)

---

## Epic 2: G36 Visual Blocks UI with Mock DTOs

**Expanded Goal:**

Build G36 visual programming workflow with mock FMU service to demonstrate how 223P-tagged points connect to standardized control sequences. Focus on visual drag-drop interaction where users connect BACnet points to G36 input/output ports, with automatic type validation ensuring correct point types are used. Parameters match actual Modelica Buildings G36 library for realistic demo.

**Value Delivery:**

Demonstrate to BMS integrators that G36 sequences can be configured visually using 223P metadata without writing code, and that type validation prevents common configuration errors. Enables LinkedIn showcase of complete 223P + G36 workflow with real parameter structures.

### Stories

**Story 2.1: Define G36 and FMU DTO Interfaces**

As a developer,
I want TypeScript interfaces for G36 sequence and FMU configuration,
So that mock and real FMU services share identical contracts.

**Acceptance Criteria:**

1. SequenceConfigDTO interface defined (sequenceType, parameters, connections)
2. FMUMetadataDTO interface defined (modelPath, version, inputs, outputs)
3. G36PortDTO interface defined (portId, portType, expectedType, required)
4. ConnectionDTO interface defined (sourcePointId, targetPortId, 223pValidation)
5. G36ParameterSchemaDTO interface defined (paramName, type, unit, defaultValue, minValue, maxValue, description) - matches Modelica parameter structure
6. All DTOs include schemaVersion field
7. Zod schemas for runtime validation

**Prerequisites:** None

---

**Story 2.2: Document Modelica G36 Parameter Mappings**

As a developer,
I want documented mappings of Modelica G36 parameters to UI configuration,
So that mock parameters match real FMU requirements.

**Acceptance Criteria:**

1. Research 2-3 G36 Modelica models from https://github.com/lbl-srg/modelica-buildings/tree/master/Buildings/Controls/OBC/ASHRAE/G36
2. Document parameter schemas in `/docs/feature-development/ashrae-223p-ai-g36-integration/g36-parameter-schemas.json`
3. For each parameter: name, type, unit, default, min, max, description (from Modelica)
4. Include "AHU Economizer" parameters from `G36/AHUs/MultiZone/VAV/Controller.mo`
5. Include "VAV Cooling" parameters from `G36/TerminalUnits/Controller.mo`
6. Reference Modelica model paths in documentation
7. Example parameters: TZonCooOff, VOutMin_flow, dpBui

**Prerequisites:** Story 2.1

---

**Story 2.3: Create Mock G36 Service**

As a developer,
I want a mock G36 service with 2-3 predefined sequences using real Modelica parameter schemas,
So that UI can demonstrate G36 workflow without FMU backend.

**Acceptance Criteria:**

1. MockG36Service implements G36Service interface
2. Provides "AHU Economizer" sequence definition with 5 ports (3 inputs, 2 outputs)
3. Provides "VAV Cooling" sequence definition with 4 ports
4. getSequenceLibrary() returns available sequences
5. getSequenceDefinition(id) returns ports and parameter schemas from Story 2.2
6. Parameter schemas loaded from g36-parameter-schemas.json
7. Mock data structure matches Modelica Buildings library

**Prerequisites:** Story 2.2

---

**Story 2.4: G36 Block Library Panel Component**

As a BMS integrator,
I want a library panel showing available G36 sequences,
So that I can discover and add standardized control sequences to my flow.

**Acceptance Criteria:**

1. Panel displays on right sidebar (or collapsible drawer)
2. Shows "AHU Economizer" and "VAV Cooling" blocks
3. Each block shows icon, name, and short description
4. Blocks are draggable from library to canvas
5. shadcn/ui Card components for block display
6. Search/filter functionality for future expansion
7. Panel can be collapsed/expanded

**Prerequisites:** Story 2.3

---

**Story 2.5: G36 Custom React Flow Node**

As a developer,
I want a custom React Flow node type for G36 blocks,
So that G36 sequences display correctly on the visual canvas with labeled ports.

**Acceptance Criteria:**

1. Custom node type "g36Sequence" registered with React Flow
2. Node displays sequence name and icon
3. Input ports displayed on left side with labels
4. Output ports displayed on right side with labels
5. Example: "Outside Air Temp", "Return Air Temp", "OA Damper Cmd"
6. Ports use React Flow Handle components
7. Node styling consistent with existing design system
8. Node is selectable and movable

**Prerequisites:** Story 2.4

---

**Story 2.6: Drag G36 Block from Library to Canvas**

As a BMS integrator,
I want to drag G36 blocks from the library onto the canvas,
So that I can add standardized sequences to my control flow.

**Acceptance Criteria:**

1. Drag from library panel triggers React Flow node creation
2. Node placed at drop location on canvas
3. Node ID generated automatically
4. Sequence definition loaded from mock service
5. Ports rendered based on sequence definition
6. Zustand store updated with new G36 node
7. Multiple instances of same sequence allowed

**Prerequisites:** Story 2.5

---

**Story 2.7: Display Port Connection Targets on G36 Block**

As a BMS integrator,
I want to see labeled connection ports on G36 blocks,
So that I know where to connect BACnet points.

**Acceptance Criteria:**

1. Each port displays label (e.g., "Outside Air Temp")
2. Input ports on left side (green color)
3. Output ports on right side (blue color)
4. Required ports marked with asterisk (\*)
5. Port hover shows tooltip with expected type (e.g., "Temperature Sensor")
6. Unconnected required ports show warning icon
7. Port styling uses Tailwind CSS

**Prerequisites:** Story 2.5

---

**Story 2.8: Drag BACnet Point to G36 Port (Basic Connection)**

As a BMS integrator,
I want to drag a BACnet point from the sidebar to a G36 port,
So that I can visually connect points to sequence inputs/outputs.

**Acceptance Criteria:**

1. Can drag BACnet point node from canvas or sidebar
2. Hovering over G36 port highlights the port
3. Drop on port creates React Flow edge (connection line)
4. Connection stored in Zustand (sourcePointId → targetPortId)
5. Visual connection line drawn between point and port
6. Connection can be deleted by selecting and pressing Delete key

**Prerequisites:** Story 2.7

---

**Story 2.9: 223P Type Validation During Connection**

As a BMS integrator,
I want type validation when connecting points to G36 ports,
So that I don't accidentally connect incompatible point types.

**Acceptance Criteria:**

1. Check if BACnet point has 223P mapping before allowing connection
2. If tagged: validate 223P device type matches port's expected type
3. Example: "Temperature Sensor" point → "Outside Air Temp" port ✅ allowed
4. Example: "Pressure Sensor" point → "Outside Air Temp" port ❌ rejected
5. Green highlight on port when dragging compatible point
6. Red highlight on port when dragging incompatible point
7. Connection rejected with error message if type mismatch
8. Tooltip shows: "Type mismatch: Expected Temp Sensor, found Pressure Sensor"

**Prerequisites:** Story 2.8, Epic 1 (223P mappings available)

---

**Story 2.10: Auto-trigger 223P Popup for Untagged Points**

As a BMS integrator,
I want the 223P mapping popup to appear automatically when I connect an untagged point to a G36 port,
So that tagging happens as part of the connection workflow.

**Acceptance Criteria:**

1. When dropping untagged BACnet point on G36 port
2. 223P mapping popup opens automatically
3. AI suggests mapping based on port's expected type
4. Example: Dropping on "Outside Air Temp" port → suggests "Outside Air Temperature Sensor"
5. Upon confirming mapping, connection is completed
6. Upon canceling popup, connection is aborted and point returns to original location
7. Equipment type auto-filled if other points from same device already tagged

**Prerequisites:** Story 2.9, Epic 1 (223P popup component)

---

**Story 2.11: Visual Connection State Feedback**

As a BMS integrator,
I want visual feedback showing connection status,
So that I know which ports are properly connected.

**Acceptance Criteria:**

1. Connected port shows green checkmark icon
2. Required but unconnected port shows red warning icon
3. Optional unconnected port shows gray dot
4. Connection line color: green for valid, red for invalid (if validation later fails)
5. G36 block header shows overall status: "3/5 connected"
6. Port tooltip shows connected point name on hover

**Prerequisites:** Story 2.9

---

**Story 2.12: G36 Parameter Configuration Panel**

As a BMS integrator,
I want to configure G36 sequence parameters (setpoints, deadbands, etc.),
So that I can customize sequence behavior for my building.

**Acceptance Criteria:**

1. Clicking G36 block opens parameter panel (right sidebar or modal)
2. Panel shows all configurable parameters from sequence's parameter schema (Story 2.2)
3. Parameters loaded from Modelica schema: name, type, unit, default, min, max, description
4. Example real parameters: TZonCooOff (21°C), VOutMin_flow (m³/s), dpBui (Pa)
5. Input fields with validation using min/max from schema
6. Units displayed from schema (°F, %, Pa, etc.)
7. Default values from Modelica models pre-filled
8. Parameter help text from Modelica descriptions
9. Changes saved to Zustand store
10. Parameter panel updates when different G36 block selected
11. shadcn/ui Form components used

**Prerequisites:** Story 2.6, Story 2.2

---

**Story 2.13: Prevent Saving with Invalid G36 Configuration**

As a BMS integrator,
I want validation that prevents saving flows with incomplete G36 connections,
So that I don't create invalid configurations.

**Acceptance Criteria:**

1. "Save" button disabled when any G36 block has missing required connections
2. Validation error message displayed: "G36 block 'AHU Economizer' is missing required connections"
3. List of missing connections shown in error
4. G36 blocks with errors highlighted on canvas (red border)
5. Can still save if all required connections are satisfied

**Prerequisites:** Story 2.11

---

**Story 2.14: Delete G36 Block and Connections**

As a BMS integrator,
I want to delete G36 blocks from the canvas,
So that I can remove sequences I no longer need.

**Acceptance Criteria:**

1. Select G36 block and press Delete key to remove
2. All connections to/from block are also deleted
3. Zustand store updated (node and connections removed)
4. Connected BACnet points remain on canvas (only connections removed)
5. Confirmation dialog for destructive action (optional)

**Prerequisites:** Story 2.8

---

**Story 2.15: Multiple G36 Block Instances**

As a BMS integrator,
I want to add multiple instances of the same G36 sequence,
So that I can configure multiple VAVs or AHUs with the same sequence type.

**Acceptance Criteria:**

1. Can drag "VAV Cooling" block onto canvas multiple times
2. Each instance gets unique ID
3. Each instance has independent parameter configuration
4. Each instance has independent connections
5. Node titles show instance number: "VAV Cooling #1", "VAV Cooling #2"

**Prerequisites:** Story 2.6

---

**Story 2.16: In-Memory G36 State Management**

As a developer,
I want Zustand store to manage G36 blocks and connections in memory,
So that G36 configuration persists during demo session.

**Acceptance Criteria:**

1. Zustand slice: `g36Blocks` with `Map<blockId, G36BlockState>`
2. `g36Connections` with `Map<connectionId, ConnectionDTO>`
3. `addG36Block(block)` action
4. `updateG36Parameters(blockId, params)` action
5. `addG36Connection(connection)` action
6. `removeG36Block(blockId)` action (cascades to connections)
7. State survives component unmounts
8. State cleared on browser refresh (no persistence yet)

**Prerequisites:** Story 2.6, Story 2.8

---

**Story 2.17: G36 UI Polish and Accessibility**

As a BMS integrator,
I want polished, accessible UI for G36 workflow,
So that the LinkedIn demo is professional and usable.

**Acceptance Criteria:**

1. Smooth drag-drop animations
2. Clear visual hierarchy (ports, labels, status icons)
3. Keyboard navigation for parameter panel
4. Screen reader support for port labels and connection status
5. Consistent with Epic 1 UI patterns
6. Responsive layout (works on different screen sizes)
7. Loading states for sequence library

**Prerequisites:** All Epic 2 stories

---

**Story 2.18: Connection Validation on Point Re-tagging**

As a BMS integrator,
I want existing G36 connections to re-validate if I change a point's 223P mapping,
So that type mismatches are caught immediately.

**Acceptance Criteria:**

1. When user changes 223P mapping of a connected point
2. All G36 connections using that point are re-validated
3. If new mapping is incompatible, connection marked as invalid (red)
4. Error tooltip shown on invalid connection
5. User prompted to fix or remove invalid connections
6. Can revert mapping change to restore valid connections

**Prerequisites:** Story 2.9, Epic 1

---

## Epic 3: Backend Integration - BuildingMOTIF API

**Expanded Goal:** Replace mock BuildingMOTIF service with real API integration, ensuring zero UI changes required.

**Key Stories (12-15 total):**

1. Generate TypeScript API client from BuildingMOTIF OpenAPI spec
2. Implement ApiBuildingMOTIFService class matching mock interface
3. Add BuildingMOTIF service health check and error handling
4. Real template library loading from BuildingMOTIF API
5. Real SHACL validation via BuildingMOTIF
6. RDF graph storage and retrieval
7. Equipment hierarchy creation in BuildingMOTIF
8. Feature flag toggle (mock vs real service)
9. API error handling with user-friendly messages
10. API retry logic and timeout handling
11. Integration tests with BuildingMOTIF service
12. Update Epic 1 components to use service interface (should require zero changes)

---

## Epic 4: Backend Integration - G36 FMU

**Expanded Goal:** Replace mock G36 service with real FMU integration, using parameter schemas from Epic 2.

**Key Stories (12-15 total):**

1. Research FMU generation from Modelica Buildings G36 models
2. Implement FMU metadata generation service
3. Create TypeScript ↔ FMU communication layer
4. Real G36 sequence configuration using FMU parameters
5. Validate FMU parameter values against Modelica schema
6. FMU model path resolution and loading
7. Feature flag toggle (mock vs real FMU)
8. FMU error handling and validation feedback
9. Integration tests with sample FMU models
10. Update Epic 2 components to use FMU service (should require zero changes)
11. Document FMU deployment process
12. FMU version compatibility checking

---

## Epic 5: Project Persistence (Save/Load)

**Expanded Goal:** Add complete project save/load functionality with version history and error recovery.

**Key Stories (10-12 total):**

1. Define project file schema (includes all DTOs from Epics 1-2)
2. Implement project serialization (223P mappings + G36 configs + canvas state)
3. Save project to file system
4. Load project from file with validation
5. Autosave mechanism (configurable interval)
6. Project version history tracking
7. Version migration handling for schema changes
8. Recovery from corrupted project files
9. Conflict resolution for concurrent saves
10. Export project as JSON for sharing
11. Import external project files
12. Project metadata management (name, description, created date, modified date)

---

## Epic 6: BOPTest Integration

**Expanded Goal:** Add real BOPTest simulation and verification for G36 sequences.

**Key Stories (10-12 total):**

1. Define BOPTest DTO interfaces (SimulationRequestDTO, ResultsDTO, MetricsDTO)
2. Implement BOPTest API client
3. Create simulation request builder from G36 configuration
4. Execute simulation runs with progress feedback
5. Parse and store simulation results
6. Results visualization component (charts, metrics)
7. Performance metrics display (energy consumption, comfort violations)
8. Compare multiple simulation runs
9. Export simulation results
10. BOPTest error handling and validation
11. Integration tests with BOPTest service
12. Document BOPTest setup and configuration

---

## Story Guidelines Reference

**Story Format:**

```
**Story [EPIC.N]: [Story Title]**

As a [user type],
I want [goal/desire],
So that [benefit/value].

**Acceptance Criteria:**
1. [Specific testable criterion]
2. [Another specific criterion]
3. [etc.]

**Prerequisites:** [Dependencies on previous stories, if any]
```

**Story Requirements:**

- **Vertical slices** - Complete, testable functionality delivery
- **Sequential ordering** - Logical progression within epic
- **No forward dependencies** - Only depend on previous work
- **AI-agent sized** - Completable in 2-4 hour focused session
- **Value-focused** - Integrate technical enablers into value-delivering stories

---

**For implementation:** Use the `create-story` workflow to generate individual story implementation plans from this epic breakdown.
