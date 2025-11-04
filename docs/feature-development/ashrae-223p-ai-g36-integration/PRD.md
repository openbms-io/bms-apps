# bms-apps Product Requirements Document (PRD)

**Author:** Amol
**Date:** 2025-11-01
**Project Level:** 4
**Target Scale:** 40-100+ stories, enterprise scale expansion

---

## Goals and Background Context

### Goals

**Primary Goals:**

1. **Enable frictionless ASHRAE 223P adoption** - Integrate semantic mapping into existing BACnet discovery workflow, reducing mapping time from 5 minutes to 30 seconds per point through AI-assisted verification

2. **Validate workflow integration concept** - Achieve positive feedback from 5+ BMS integrators, demonstrating that proactive 223P mapping (during point discovery) is more effective than reactive manual tagging

3. **Establish interoperability foundation** - Enable seamless integration with 5+ third-party building applications (analytics, FDD, energy management) through standardized 223P semantic tags

4. **Deploy G36 standardized sequences** - Provide visual programming interface for ASHRAE Guideline 36 control sequences with validation, FMU execution, and BOPTest verification

5. **Achieve production deployments** - Reach 50+ self-hosted installations across 10+ organizations within 12 months, validating product-market fit

6. **Reduce commissioning errors** - Lower commissioning rework rate to <5% through SHACL validation of 223P equipment models and G36 sequence configurations

7. **Position for commercial optionality** - Build technical leadership in ASHRAE 223P adoption and establish community foundation that enables future open-core business model (if validated)

### Background Context

BMS integrators manage thousands of BACnet points per building but don't create ASHRAE 223P semantic tags because manual mapping takes 5 minutes per point and they don't see immediate value. This prevents interoperability between building applications and creates vendor lock-in.

**Why Now:** ASHRAE 223P is becoming an industry standard for semantic building data modeling. Building owners are demanding interoperability between analytics platforms, FDD tools, and energy management systems. However, the adoption barrier is too high - integrators won't spend 83+ hours per building on manual tagging work that doesn't provide immediate ROI.

**Core Hypothesis:** We believe that embedding 223P mapping directly into the existing BACnet discovery workflow (proactive AI-assisted popup during point drag-and-drop) will reduce friction enough for integrators to adopt semantic tagging. This is an assumption based on LinkedIn feedback indicating interest - we need to build a mock flow and get hands-on feedback from integrators to validate whether workflow integration actually solves the adoption problem.

**Technical Foundation:** The existing BMS Supervisor Controller platform provides visual programming for building control with BACnet/MQTT integration. BuildingMOTIF SDK (Python) provides ASHRAE 223P templates, RDF storage, and SHACL validation. This feature builds on proven infrastructure to add semantic modeling and G36 standardized sequences.

---

## Requirements

### Functional Requirements

#### AI-Powered 223P Semantic Mapping

**FR001:** System shall display AI-powered 223P mapping popup automatically when user drags a BACnet point onto the visual canvas

**FR002:** System shall analyze BACnet point metadata (object name, description, units, object type) to generate 223P equipment and point suggestions with confidence scores

**FR003:** System shall pre-fill equipment type suggestions from BuildingMOTIF template library (8 equipment types: VAV, AHU, Boiler, Chiller, Fan, Pump, Damper, Valve)

**FR004:** System shall pre-fill point type suggestions from BuildingMOTIF device library (15 device types including sensors, actuators, setpoints)

**FR005:** System shall pre-fill observable property suggestions from BuildingMOTIF property library (25+ properties: temperature, pressure, flow, position, etc.)

**FR006:** System shall display confidence scores (0-100%) for each AI suggestion to help users assess accuracy

**FR007:** System shall allow users to accept AI suggestions with single-click confirmation

**FR008:** System shall allow users to manually override any AI suggestion via dropdown selection from complete BuildingMOTIF templates

**FR009:** System shall allow users to skip 223P mapping for individual points (mapping optional, not mandatory)

**FR010:** System shall persist 223P mappings with the visual flow project for future editing

**FR011:** System shall provide search/filter capability within equipment, device, and property dropdowns

**FR012:** System shall display validation warnings in real-time as users modify 223P mappings

#### BuildingMOTIF Integration

**FR013:** System shall communicate with BuildingMOTIF service via REST API for template retrieval and RDF storage

**FR014:** System shall store complete 223P equipment models as RDF graphs in BuildingMOTIF

**FR015:** System shall validate 223P mappings using SHACL constraints before saving to BuildingMOTIF

**FR016:** System shall display SHACL validation errors with actionable error messages (e.g., "Actuator requires AO/BO object type, found AI")

**FR017:** System shall support creating equipment hierarchies (e.g., AHU contains dampers, sensors, actuators)

**FR018:** System shall allow querying existing 223P equipment models from BuildingMOTIF for reuse across projects

#### G36 Visual Sequence Blocks

**FR019:** System shall provide visual programming blocks for ASHRAE G36 control sequences (VAV cooling, AHU economizer, etc.)

**FR020:** System shall allow drag-and-drop placement of G36 sequence blocks onto the visual canvas

**FR021:** System shall display input/output configuration panel when G36 block is selected

**FR022:** System shall populate dropdowns with only 223P-mapped points that match expected types for each G36 input/output

**FR023:** System shall validate that G36 sequence references semantically-correct 223P points (e.g., cooling sequence requires zone temp sensor, not supply air temp)

**FR024:** System shall prevent saving G36 sequences with missing or incorrectly-mapped input/output points

**FR025:** System shall support configuring G36 sequence parameters (setpoints, deadbands, time delays) via visual interface

**FR026:** System shall generate FMU configuration metadata for G36 mathematical model execution

**FR027:** System shall support TypeScript ↔ FMU communication layer for G36 sequence configuration

#### Validation & Testing

**FR028:** System shall validate complete flow configurations (223P + G36) before allowing save

**FR029:** System shall integrate with BOPTest for G36 sequence verification against simulated building models

**FR030:** System shall display BOPTest simulation results (performance metrics, energy consumption, comfort violations)

**FR031:** System shall allow users to run BOPTest verification iteratively during G36 sequence development

#### Save & Load Functionality

**FR032:** System shall save complete flow projects including visual nodes, BACnet point mappings, 223P semantic tags, and G36 sequences

**FR033:** System shall save 223P equipment models to BuildingMOTIF RDF storage with project reference

**FR034:** System shall save G36 sequence configurations with FMU metadata to project file

**FR035:** System shall load previously saved projects and restore all visual flow, 223P mappings, and G36 configurations

**FR036:** System shall verify 223P mappings are still valid when loading project (check BuildingMOTIF RDF still exists)

**FR037:** System shall handle loading errors gracefully (missing RDF data, invalid G36 config) and notify user of issues

**FR038:** System shall support autosave functionality to prevent data loss during development

**FR039:** System shall maintain project version history to enable rollback if needed

### Non-Functional Requirements

**NFR001: AI Response Time** - System shall generate 223P suggestions and display popup within 500ms of point drag-and-drop action to maintain workflow fluidity

**NFR002: Validation Performance** - SHACL validation shall complete within 2 seconds for equipment models with up to 50 points to provide real-time feedback

**NFR003: Save/Load Reliability** - System shall save and restore project state with 100% fidelity (no data loss) for flows containing up to 1000 points and 100 G36 sequence blocks

**NFR004: Browser Compatibility** - System shall support Chrome browser (latest version only), no cross-browser compatibility required

**NFR005: Test Coverage** - All new code shall follow TDD methodology with minimum 80% test coverage for TypeScript (Jest) and Python (pytest) components

**NFR006: BuildingMOTIF Service Dependency** - System shall fail fast when BuildingMOTIF service is unavailable: display clear error message, disable 223P mapping popup, and prevent G36 sequence creation/editing

---

## User Journeys

### Journey 1: First-Time 223P Mapping - VAV Equipment Discovery

**Actor:** BMS Integrator (Mike, 5 years experience)

**Context:** Mike is discovering BACnet points for a new VAV box installation. He's heard about 223P but never used semantic tagging before.

**Flow:**

1. Mike opens Designer and creates new project
2. Connects to BACnet network and discovers devices
3. Sees VAV-2-01 with 12 points in left sidebar
4. Drags `VAV-2-01_ZoneTemp` point onto canvas
   - **System displays 223P mapping popup automatically**
   - AI suggests: "Zone Air Temperature Sensor" (confidence: 95%)
   - Equipment: VAV Terminal Unit
   - Device: Temperature Sensor
   - Property: Zone Air Temperature
5. **Decision Point:** Mike sees confidence score and reads suggestion
   - **Path A (Trust AI):** Clicks "Confirm" → mapping saved, continues
   - **Path B (Verify):** Opens equipment dropdown to check other options → sees AHU, Boiler, etc. → confirms VAV is correct → clicks "Confirm"
   - **Path C (Skip):** Clicks "Skip" → no 223P mapping, point added to canvas
6. Drags `VAV-2-01_CoolingValve` onto canvas
   - Popup appears with: "Cooling Valve Actuator" (confidence: 88%)
   - Equipment: VAV Terminal Unit (auto-filled from previous point)
   - Mike clicks "Confirm"
7. Drags `VAV-2-01_DamperPos` onto canvas
   - **Error condition:** AI suggests "Position Sensor" but BACnet object type is AI (analog input)
   - SHACL validation warning appears: "Actuator requires AO/BO object type, found AI"
   - Mike manually changes Device to "Damper Position Sensor"
   - Validation passes, clicks "Confirm"
8. Completes VAV with 12 points, all semantically tagged
9. Left panel now shows 223P metadata badges next to each tagged point
10. Saves project → 223P RDF stored in BuildingMOTIF
11. **Outcome:** Mike realizes 223P mapping took 30 seconds per point (vs 5 min manual), sees value

**Edge Cases:**

- BuildingMOTIF service down → Error message, mapping disabled, Mike can still build visual flow
- Network interruption during save → Autosave recovery on reconnect
- Ambiguous point name (e.g., "Temp1") → Low confidence score (45%), Mike must manually select

---

### Journey 2: Experienced User - G36 Sequence Configuration with Visual Drag-Drop

**Actor:** BMS Integrator (Sarah, 8 years experience, already familiar with 223P)

**Context:** Sarah has completed 223P mapping for an AHU and now wants to add G36 economizer sequence using visual drag-drop workflow.

**Flow:**

1. Sarah opens existing project with AHU already mapped (20 points with 223P tags)
2. **Left panel shows BACnet points with 223P metadata badges:**
   - `AHU-1_OAT` → 🏷️ AHU | Temp Sensor | Outside Air Temp
   - `AHU-1_RAT` → 🏷️ AHU | Temp Sensor | Return Air Temp
   - `AHU-1_MAT` → 🏷️ AHU | Temp Sensor | Mixed Air Temp
   - `AHU-1_OADamper` → 🏷️ AHU | Damper Actuator | OA Damper Position
   - `AHU-1_RADamper` → 🏷️ AHU | Damper Actuator | RA Damper Position
3. Drags "G36 AHU Economizer" block from G36 library onto canvas
4. **G36 block displays labeled input/output ports:**
   - Input ports: "Outside Air Temp", "Return Air Temp", "Mixed Air Temp"
   - Output ports: "OA Damper Cmd", "RA Damper Cmd"
   - Parameter section: Min OA%, Enable Temp, Deadband
5. **Connecting first point:** Sarah drags `AHU-1_OAT` from left panel
   - Hovers over "Outside Air Temp" input port on G36 block
   - **Validation:** Point already tagged as "Temp Sensor | Outside Air Temp" ✅
   - System shows green highlight on port (compatible)
   - Drops point → connection line drawn from BACnet point to G36 input
6. **Connecting second point:** Drags `AHU-1_RAT` to "Return Air Temp" port
   - Already tagged ✅ → Connection successful
7. **Connecting untagged point:** Drags `AHU-1_Sensor3` (not yet tagged) to "Mixed Air Temp" port
   - **223P mapping popup appears automatically**
   - AI suggests: "Mixed Air Temperature Sensor" (confidence: 92%)
   - Equipment: AHU (auto-filled from other points)
   - Sarah clicks "Confirm"
   - **Connection completes** after tagging
8. **Connecting output:** Drags `AHU-1_OADamper` to "OA Damper Cmd" output port
   - Already tagged as "Damper Actuator" ✅
   - Connection successful
9. **Type mismatch scenario:** Sarah accidentally drags `AHU-1_StaticPressure` to "Return Air Temp" port
   - **Validation error:** Red highlight on port
   - Tooltip: "Type mismatch: Expected Temp Sensor, found Pressure Sensor"
   - Connection prevented, point bounces back
10. Sarah completes all connections (5 points connected)
11. Configures G36 parameters in block properties panel:
    - Min OA Setpoint: 15%
    - Economizer Enable Temp: 65°F
    - Deadband: 2°F
12. **Decision Point:** Run BOPTest verification
    - **Path A (Verify now):** Clicks "Run BOPTest" → simulation runs 24hr profile → shows energy savings 12%, comfort violations 0%
    - **Path B (Skip for now):** Clicks "Save without verification" → G36 config saved, can verify later
13. Saves project → G36 connections + FMU metadata stored
14. **Outcome:** G36 sequence configured visually with validated 223P point connections

**Edge Cases:**

- Missing required connection → G36 block shows warning icon, cannot save until all inputs connected
- BOPTest service unavailable → Warning message, allows save without verification
- Dragging non-BACnet node to G36 port → Connection rejected, only BACnet points allowed
- 223P popup canceled during connection → Connection aborted, point returns to sidebar

---

### Journey 3: Loading Existing Project - Validation & Recovery

**Actor:** BMS Integrator (Tom, 3 years experience)

**Context:** Tom is reopening a project from 2 weeks ago to make changes to G36 sequence.

**Flow:**

1. Tom clicks "Load Project" and selects `VAV-System-Building-A.json`
2. **System loads project:**
   - Restores visual flow (50 nodes)
   - Queries BuildingMOTIF for 223P RDF data
   - Loads G36 sequence configurations
3. **Validation check:** System verifies 223P mappings still exist
   - 48 points: ✅ Valid
   - 2 points: ⚠️ RDF data missing (deleted from BuildingMOTIF)
4. **Warning dialog appears:**
   "Warning: 2 points have missing 223P mappings:

   - VAV-3-05_ZoneTemp
   - VAV-3-05_CoolingValve

   G36 sequences may be affected. Remap these points?"

5. **Decision Point:**
   - **Path A (Fix now):** Clicks "Remap" → 223P popup appears for each point → Tom re-tags
   - **Path B (Continue anyway):** Clicks "Continue" → Project loads, affected points highlighted in red
6. Tom makes changes to G36 economizer setpoint (65°F → 60°F)
7. Clicks "Run BOPTest" to verify change
8. Saves project → Updated FMU config stored
9. **Outcome:** Project loaded, issues identified and resolved

**Edge Cases:**

- Corrupt project file → Error message with recovery options (restore from autosave)
- BuildingMOTIF service down during load → Error: "Cannot verify 223P mappings, service unavailable"
- Version mismatch (project saved with older schema) → Migration prompt or compatibility warning

---

## UX Design Principles

1. **Workflow Integration Over Disruption** - 223P mapping must feel like verification (30 sec), not creation from scratch (5 min). Popup appears automatically during drag-drop, pre-filled with AI suggestions. Users confirm rather than configure.

2. **Visual Feedback at Every Step** - Show 223P metadata badges in left panel, validation states on G36 ports (green/red highlights), connection compatibility during hover, and confidence scores for AI suggestions.

3. **Fail Fast with Clear Guidance** - When BuildingMOTIF unavailable, disable 223P features immediately with clear error message. Type mismatches prevent connection with actionable tooltip. Validation errors show what's wrong and how to fix it.

4. **Progressive Disclosure** - Don't overwhelm with 223P complexity upfront. Show metadata badges only for tagged points. G36 configuration reveals complexity progressively (connect points first, then configure parameters, then verify with BOPTest).

---

## User Interface Design Goals

**Platform & Screens:**

- Web-based React Flow canvas (existing Designer app)
- Chrome browser only (latest version)
- Core screens:
  - Visual canvas (existing, enhanced with 223P + G36)
  - BACnet point discovery sidebar (existing, enhanced with 223P badges)
  - 223P mapping popup modal (new)
  - G36 block library panel (new)
  - BOPTest results visualization (new)

**Key Interaction Patterns:**

- **Drag-drop everywhere:** BACnet points → canvas, G36 blocks → canvas, BACnet points → G36 ports
- **Hover hints:** Show connection compatibility, validation errors, 223P metadata tooltips
- **Modal overlays:** 223P mapping popup interrupts workflow for tagging, then resumes
- **Real-time validation:** Visual feedback as user interacts (green highlights, red errors, warning icons)

**Design Constraints:**

- Must use existing shadcn/ui component library
- Must integrate with existing Zustand state management
- Must maintain React Flow visual programming paradigm
- Tailwind CSS v4 for styling

---

## Epic List

**Epic 1: 223P Mapping UI with Mock DTOs**

- **Goal:** Build 223P mapping UX with mock service layer to demonstrate workflow integration concept for LinkedIn feedback
- **Key Deliverables:** 223P popup, AI suggestions (mock), metadata badges, SHACL validation (mock), no persistence
- **Estimated Stories:** 12-15 stories

**Epic 2: G36 Visual Blocks UI with Mock DTOs**

- **Goal:** Build G36 drag-drop workflow with mock FMU data to demonstrate visual programming paradigm
- **Key Deliverables:** G36 block library, port-based connections, 223P type validation, parameter config UI, no BOPTest
- **Estimated Stories:** 15-18 stories

**Epic 3: Backend Integration - BuildingMOTIF API**

- **Goal:** Replace mock BuildingMOTIF service with real API integration (zero UI changes)
- **Key Deliverables:** REST API client, RDF storage, real SHACL validation, template loading, error handling
- **Estimated Stories:** 12-15 stories

**Epic 4: Backend Integration - G36 FMU**

- **Goal:** Replace mock G36 service with real FMU integration (zero UI changes)
- **Key Deliverables:** FMU metadata generation, TypeScript ↔ FMU communication, real sequence configuration
- **Estimated Stories:** 12-15 stories

**Epic 5: Project Persistence (Save/Load)**

- **Goal:** Add complete project save/load functionality with version history and recovery
- **Key Deliverables:** File serialization, autosave, version history, error recovery, migration handling
- **Estimated Stories:** 10-12 stories

**Epic 6: BOPTest Integration**

- **Goal:** Add real BOPTest simulation and verification (final validation phase)
- **Key Deliverables:** BOPTest API client, simulation execution, results visualization, performance metrics
- **Estimated Stories:** 10-12 stories

**Total Estimated Stories:** 71-87 stories

> **Note:** Detailed epic breakdown with full story specifications is available in [epics.md](./epics.md)

---

## Out of Scope

### Explicitly Excluded from This Release

**Deployment & Runtime:**

- Deployment to BMS IoT App (configuration only, no runtime execution)
- MQTT communication with BMS IoT App
- Production BACnet device control
- Real-time G36 sequence execution on physical hardware

**Platform & Browser Support:**

- Multi-browser compatibility (Chrome only)
- Mobile and tablet interfaces
- Offline-first capabilities beyond autosave
- Progressive Web App (PWA) features

**Advanced AI Features:**

- Real-time learning from user corrections
- Custom equipment template generation
- Advanced natural language processing for point naming
- Automated equipment relationship inference beyond BuildingMOTIF templates

**BuildingMOTIF Extensions:**

- Custom template creation UI
- Template library management
- Extended equipment types beyond BuildingMOTIF's 8 types
- Custom SHACL constraint authoring

**Commercial Platform Features:**

- Multi-tenant SaaS architecture
- Enterprise SSO/SAML integration
- Advanced security features (beyond basic auth)
- Audit logs and compliance tracking
- Usage analytics and telemetry
- Team collaboration features
- Cloud hosting infrastructure

**Educational Features (Post-MVP):**

- Training curriculum and documentation
- Sample projects for students
- BOPTest-based learning modules
- Community template sharing

### Future Considerations (Not This Release)

- ASHRAE 231P CDL/CXF format support (different standard)
- Integration with third-party analytics platforms
- Advanced G36 sequence library (starting with 2-3 sequences)
- Multi-building project management
- Equipment commissioning workflows
- Historical data visualization
