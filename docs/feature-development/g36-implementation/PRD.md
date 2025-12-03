# G36 Visual Programming Blocks - Product Requirements Document (PRD)

**Author:** Amol
**Date:** 2025-11-26
**Project Level:** 4
**Target Scale:** Enterprise BMS Platform Feature

---

## Goals and Background Context

### Goals

- Enable visual drag-drop programming of ASHRAE G36 Reheat terminal unit sequences in the Designer app
- Integrate G36 Reheat FMU as a visual programming block with configurable parameters and I/O connectors
- Allow users to manually connect ASHRAE 223P mapped BACnet points to G36 block inputs/outputs via visual wiring
- Validate completed I/O connections using SHACL shapes via BuildingMOTIF before deployment
- Provide a replicable pattern for adding additional G36 sequences (CoolingOnly, DualDuct, etc.) in future phases

> **Note:** BOPTEST integration comes for free once BACnet points are discovered - the `multizone_office_simple_air` test case will be used for validation. BOPTEST's existing KPI endpoint will be used for effectiveness measurement.

### Background Context

ASHRAE Guideline 36 (G36) defines high-performance HVAC control sequences that have been proven to reduce energy consumption by 10-30% while improving occupant comfort. The Lawrence Berkeley National Laboratory (LBL) has implemented these sequences as Modelica blocks in the `modelica-buildings` library, which can be exported as Functional Mock-up Units (FMUs) for integration with external systems.

This feature enables building operators to visually configure G36 control sequences through the Designer app's drag-drop interface, rather than manually programming complex control logic. Users drag a G36 Reheat block onto the canvas and manually wire 223P-mapped BACnet points to the block's inputs and outputs. Once wiring is complete, SHACL validation via BuildingMOTIF verifies the connections are semantically correct before deployment. The FMU blocks wrap the proven LBL implementations, executing the control logic at runtime. Integration with BOPTEST provides a simulation environment for testing and KPI measurement before deployment to real buildings.

### Open Questions

| ID   | Question                                                                 | Impact                                  | Status                                                                                    |
| ---- | ------------------------------------------------------------------------ | --------------------------------------- | ----------------------------------------------------------------------------------------- |
| OQ-1 | ~~Should SHACL validation run per-point or batch?~~                      | —                                       | **Resolved**: Two-level validation - per-point (lightweight or SHACL) + full SHACL on Run |
| OQ-2 | Should per-point validation use lightweight type checking or full SHACL? | Performance vs. early semantic feedback | To be determined during implementation                                                    |

---

## Requirements

### Functional Requirements

**G36 FMU Block Integration**

- FR001: System shall provide a G36 Reheat Terminal Unit block in the Designer visual programming palette
- FR002: G36 Reheat block shall expose all required inputs as connection points (TZon, TCooSet, THeaSet, TDis, VDis_flow, TSup, TSupSet, u1Fan, uOpeMod)
- FR003: G36 Reheat block shall expose conditional inputs based on configuration (ppmCO2Set, ppmCO2 for CO2 sensing; u1HotPla for water-based heating)
- FR004: G36 Reheat block shall expose outputs as connection points (yDam, yVal, VSet_flow, alarm/request outputs)
- FR005: G36 Reheat block shall provide a configuration panel for setting controller parameters (have_CO2Sen, heaCoi type, design airflow values)
- FR006: System shall load and execute the G36 Reheat FMU at runtime with configured parameters

**Visual Wiring & Connection**

- FR007: Users shall be able to drag BACnet point nodes onto the canvas from the 223P-mapped point library
- FR008: Users shall be able to visually connect BACnet point outputs to G36 block inputs via wire connections
- FR009: Users shall be able to visually connect G36 block outputs to BACnet actuator command points
- FR010: System shall validate wire connections for type compatibility (Real, Boolean, Integer)

**Two-Level Automatic Validation**

- FR011: System shall automatically validate each point connection when wired (per-point validation - lightweight or SHACL)
- FR012: System shall perform full SHACL validation via BuildingMOTIF when user clicks "Run"
- FR013: System shall display validation errors with specific connection/point references
- FR014: System shall prevent execution if SHACL validation fails

**Runtime Execution**

- FR015: "Run" button shall trigger full SHACL validation followed by graph execution if valid
- FR016: "Run" shall execute the entire graph (all connected blocks)
- FR017: Scheduler node shall control graph execution frequency (e.g., every 5 minutes per G36 spec)
- FR018: BMS IoT App shall execute G36 FMU with connected BACnet point values as inputs
- FR019: BMS IoT App shall write G36 FMU outputs to connected BACnet actuator points

**BACnet MQTT Integration**

- FR020: System shall read BACnet point values via existing MQTT read implementation
- FR021: System shall implement BACnet writes via MQTT for actuator command points (new capability)
- FR022: MQTT write messages shall include point identifier and commanded value
- FR023: BMS IoT App shall translate MQTT write commands to BACnet WriteProperty requests

### Non-Functional Requirements

- NFR001: G36 FMU execution shall complete within 100ms per control cycle
- NFR002: SHACL validation shall complete within 5 seconds for a single G36 block configuration
- NFR003: System shall support concurrent execution of G36 blocks for multiple zones (5+ zones)

---

## User Journeys

### Journey 1: Configure and Run G36 Reheat Block for a Zone (Happy Path)

**Persona:** Building Controls Engineer

**Goal:** Configure and run a G36 Reheat sequence for a single VAV zone

| Step | User Action                                                                           | System Response                                                          |
| ---- | ------------------------------------------------------------------------------------- | ------------------------------------------------------------------------ |
| 1    | Opens Designer app and creates new flow                                               | Canvas displayed with node palette                                       |
| 2    | Drags "G36 Reheat" block from palette to canvas                                       | Block appears with collapsed I/O connectors                              |
| 3    | Clicks block to open configuration panel                                              | Panel shows controller parameters (have_CO2Sen, heaCoi, design airflows) |
| 4    | Sets have_CO2Sen=true, heaCoi=WaterBased, enters design airflow values                | Block updates to show CO2 and hot water plant inputs                     |
| 5    | Drags zone BACnet points from 223P point library (TZon, CO2, airflow, discharge temp) | Point nodes appear on canvas with output connectors                      |
| 6    | Wires first point output to G36 block input                                           | **Per-point validation runs automatically** - green checkmark if valid   |
| 7    | Continues wiring remaining inputs                                                     | Each connection auto-validated on wire                                   |
| 8    | Drags actuator points (damper, reheat valve) to canvas                                | Actuator nodes appear with input connectors                              |
| 9    | Wires G36 outputs (yDam, yVal) to actuator inputs                                     | Each connection auto-validated                                           |
| 10   | Adds Scheduler node to graph, configures interval (e.g., 5 min)                       | Scheduler node connected to graph                                        |
| 11   | Clicks "Run" button                                                                   | **Full SHACL validation** runs via BuildingMOTIF                         |
| 12   | —                                                                                     | Validation passes, entire graph executes on BMS IoT App per scheduler    |

---

### Journey 2: Per-Point Validation Error

**Persona:** Building Controls Engineer

**Goal:** Immediate feedback on incompatible connection

| Step | User Action                                        | System Response                                                   |
| ---- | -------------------------------------------------- | ----------------------------------------------------------------- |
| 1    | Wires a Boolean point to a Real input on G36 block | **Per-point validation fails immediately**                        |
| 2    | —                                                  | Connection shown in red, tooltip: "Type mismatch: Boolean → Real" |
| 3    | Disconnects wire, selects correct Real point       | —                                                                 |
| 4    | Rewires correctly                                  | Per-point validation passes, green checkmark                      |

---

### Journey 3: SHACL Validation Error on Run

**Persona:** Building Controls Engineer

**Goal:** Fix semantic error caught by full SHACL validation

| Step | User Action                                                 | System Response                                                                                                                        |
| ---- | ----------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| 1    | Completes G36 block wiring (all per-point validations pass) | All connections green                                                                                                                  |
| 2    | Clicks "Run"                                                | Full SHACL validation runs                                                                                                             |
| 3    | —                                                           | **SHACL validation fails**: "TZon input requires 223P:ZoneAirTemperatureSensor, connected point is 223P:DischargeAirTemperatureSensor" |
| 4    | Error panel shows specific connection                       | Problem connection highlighted                                                                                                         |
| 5    | Disconnects incorrect point, wires correct zone temp sensor | Connection updated                                                                                                                     |
| 6    | Clicks "Run" again                                          | SHACL validation passes, execution starts                                                                                              |

---

### Journey 4: Multi-Zone Configuration and Run

**Persona:** Building Controls Engineer

**Goal:** Configure and run G36 Reheat for all 5 zones

| Step | User Action                                 | System Response                                                  |
| ---- | ------------------------------------------- | ---------------------------------------------------------------- |
| 1    | Configures first zone (Core) per Journey 1  | Core zone G36 block wired with all per-point validations passing |
| 2    | Copies Core zone G36 block                  | Duplicate block created with same parameters                     |
| 3    | Selects East zone points from 223P library  | East zone BACnet points available                                |
| 4    | Rewires duplicate block to East zone points | Per-point validations run on each wire                           |
| 5    | Repeats for North, South, West zones        | 5 G36 blocks configured                                          |
| 6    | Clicks "Run"                                | **Full SHACL validation for entire flow**                        |
| 7    | All blocks pass                             | All 5 zones start executing G36 sequences                        |

---

## UX Design Principles

1. **Leverage Existing Infrastructure** - Use existing Designer app patterns and components; only add new UX when existing doesn't satisfy a specific user flow
2. **Immediate Feedback** - Per-point validation provides instant visual feedback (green/red) on wire connections
3. **Progressive Disclosure** - G36 block shows required inputs by default; conditional inputs appear based on configuration
4. **Error Guidance** - Validation errors point to specific connections with actionable messages

---

## User Interface Design Goals

### Platform & Screens

| Platform | Target                                     |
| -------- | ------------------------------------------ |
| Web      | Designer app (Next.js) - primary interface |

| Screen              | Purpose                                                |
| ------------------- | ------------------------------------------------------ |
| Flow Canvas         | Drag-drop G36 blocks, wire to BACnet points (existing) |
| Node Palette        | Add G36 Reheat block, Scheduler node (extend existing) |
| Configuration Panel | G36 block parameters (extend existing side panel)      |
| Validation Panel    | SHACL validation results (new if needed)               |

### Key Interaction Patterns

- Existing drag-drop and wiring patterns
- Existing click-to-configure side panel
- Run button in toolbar triggers validation + execution

### Design Constraints

- Extends existing React Flow-based Designer canvas
- Follows existing shadcn/ui component patterns
- Minimize new UI - reuse existing patterns where possible

---

## Epic List

| Epic | Title                           | Goal                                                                                                     | Est. Stories |
| ---- | ------------------------------- | -------------------------------------------------------------------------------------------------------- | ------------ |
| 1    | G36 Reheat FMU Block Foundation | Integrate G36 Reheat FMU into Designer as a visual block with configurable parameters and I/O connectors | 8-10         |
| 2    | BACnet MQTT Write Integration   | Implement BACnet writes via MQTT to enable actuator command outputs (yDam, yVal)                         | 5-7          |
| 3    | Two-Level Validation            | Per-point automatic validation on wire + full SHACL validation via BuildingMOTIF on Run                  | 6-8          |
| 4    | Graph Execution with Scheduler  | Run button triggers validation + graph execution; Scheduler node controls frequency                      | 5-7          |
| 5    | BOPTEST Integration Testing     | End-to-end testing with `multizone_office_simple_air`; validate G36 with simulated building              | 4-6          |

**Total: ~28-38 stories**

> **Note:** Detailed epic breakdown with full story specifications is available in [epics.md](./epics.md)

---

## Out of Scope

- **FMU state persistence/restoration** - Production reliability features deferred
- **Custom KPI measurement/dashboard** - Use BOPTEST's existing KPI endpoint instead
- **Deploy functionality** - Run executes directly; no separate deployment workflow
- **Additional G36 sequences** - Only Reheat Terminal Unit in this phase (CoolingOnly, DualDuct, etc. are future)
- **Multi-building support** - Single building/BOPTEST instance
- **Real BACnet device testing** - BOPTEST simulation only for this phase
- **Automatic I/O mapping** - Users manually wire points; no auto-discovery of mappings
