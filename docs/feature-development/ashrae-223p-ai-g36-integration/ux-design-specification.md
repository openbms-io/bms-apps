# UX Design Specification: ASHRAE 223P + G36 Integration

**Project:** BMS Supervisor Controller
**Feature:** AI-Powered 223P Semantic Mapping + G36 Visual Sequences
**Author:** Amol
**Date:** 2025-11-01
**Version:** 1.0

---

## 1. Project Overview

### Vision

Enable frictionless ASHRAE 223P semantic tagging through AI-assisted workflow integration and visual G36 control sequence programming, reducing mapping time from 5 minutes to 30 seconds per point.

### Design Goals

1. **Speed First** - Fast path ≤30 seconds (hypothesis test for LinkedIn validation)
2. **User Agency** - Never overwrite user input with AI suggestions
3. **Progressive Disclosure** - Simple confirmation first, details only if needed
4. **Critical Work Signal** - UI communicates "this is valuable" not "tedious form"
5. **Visual Programming** - Port-based connections like Xcode Storyboards

### Target Users

BMS integrators (3-8 years experience) who:

- Understand BACnet but see 223P tagging as tedious overhead
- Need to configure G36 control sequences visually
- Want immediate feedback on configuration validity

---

## 2. Design System & Visual Foundation

### Design Stack

**Component Library:**

- **shadcn/ui** - Base components (Dialog, Dropdown, Form, Badge, Toast)
- **CopilotKit** - Chat interface for conversational AI assistance
- **React Flow** - Visual programming canvas
- **Tailwind CSS v4** - Styling system

**Color Palette:**

- Deferred for later decision
- Use existing Designer app palette for MVP
- Reference: `ux-color-themes.html` (Theme 5: Dark Energy recommended for future)

**Typography:**

- System font stack: `-apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto`
- Font weights: 400 (normal), 500 (medium), 600 (semibold), 700 (bold)
- Font sizes: 0.7rem (tiny), 0.75rem (small), 0.875rem (body), 1rem (base), 1.125rem (large)

**Spacing System:**

- Base unit: 0.25rem (4px)
- Scale: 0.5rem, 0.75rem, 1rem, 1.25rem, 1.5rem, 2rem

---

## 3. Core Experience Principles

### Defining Experience: AI-Assisted 223P Mapping Popup

**Primary Interaction:** When user drags BACnet point, popup appears instantly with AI suggestions

**Two Interaction Modes:**

1. **Fast Path (Confident AI)**

   - Popup shell appears <100ms
   - AI analyzes in background
   - Suggestions populate fields
   - User verifies → Confirm
   - **Target: 10-30 seconds**

2. **Conversational Path (Uncertain AI or User)**
   - AI confidence <50% OR user clicks "Not Sure"
   - CopilotKit chat interface appears
   - User describes context → AI assists
   - Reaches confident decision
   - **Target: 1-2 minutes (still faster than 5 min manual)**

### Emotional Goals

Users should feel:

- **"This is critical, valuable work"** - Not just another form to fill
- **Empowered and in control** - AI assists, doesn't dictate
- **Efficient and productive** - Immediate time savings experienced

### Inspiration Patterns

1. **Xcode Storyboards** - Initial friction → love after experiencing value, visual connections
2. **GitHub Copilot Chat** - Fast autocomplete for confident cases, chat for uncertain cases

---

## 4. Component Specifications

### 4.1 Left Panel - Component Library

**Layout:**

```
┌──────────────────────────────────┐
│ Components            [Search🔍] │
├──────────────────────────────────┤
│ ▼ BACnet Points                  │
│   [Point cards with 223P badges] │
│                                  │
│ ▼ G36 Sequences                  │
│   [G36 block list]               │
│                                  │
│ ▼ Logical                        │
│   [Logic blocks]                 │
│                                  │
│ ▼ Calculations                   │
│   [Math blocks]                  │
└──────────────────────────────────┘
```

**BACnet Point Card:**

```
┌────────────────────────────────┐
│ AHU-1_OAT      analog-input    │  <- Name + type badge
│ 🏷️ AHU | Temp Sensor | OA Temp│  <- 223P badges (if tagged)
│ Present Value: 45.2°F          │  <- Current value
│                                │
│ + Add Property                 │  <- Action button
└────────────────────────────────┘
```

**Untagged Point Card:**

```
┌────────────────────────────────┐
│ AHU-1_Sensor3  analog-input    │
│ ⚠️ Not tagged                  │  <- Warning if needed for G36
│ Present Value: 55.2°F          │
│                                │
│ + Add Property                 │
└────────────────────────────────┘
```

**Badge Styles:**

- Type badge: `analog-input`, `analog-output` (gray background)
- 223P Equipment: Blue badge
- 223P Device: Green badge
- 223P Property: Orange/yellow badge
- Warning: Orange text with ⚠️ icon

---

### 4.2 223P Mapping Popup

#### Variant 1: Optional Tagging (Point → Canvas)

**Trigger:** User drags BACnet point to canvas

**Layout:**

```
┌────────────────────────────────────────────────┐
│ 223P Semantic Mapping                     [×]  │
│ ℹ️ Optional - Recommended                      │
├────────────────────────────────────────────────┤
│                                                │
│ AHU-1_OAT              analog-input           │
│ Present Value: 45.2°F                         │
│                                                │
│ ┌──────────────────────────────────────────┐  │
│ │ Equipment Type          [⟳ Loading...]   │  │
│ │ ▼ VAV Terminal Unit              ✓       │  │
│ └──────────────────────────────────────────┘  │
│                                                │
│ ┌──────────────────────────────────────────┐  │
│ │ Device Type             [⟳ Loading...]   │  │
│ │ ▼ Temperature Sensor             ✓       │  │
│ └──────────────────────────────────────────┘  │
│                                                │
│ ┌──────────────────────────────────────────┐  │
│ │ Observable Property     [⟳ Loading...]   │  │
│ │ ▼ Zone Air Temperature           ✓       │  │
│ └──────────────────────────────────────────┘  │
│                                                │
│ AI Confidence: ████████████░░ 95%             │
│                                                │
│ ℹ️ Why tag?                                    │
│   • Enables analytics and FDD integration     │
│   • Prepares points for G36 sequences         │
│   • Takes 30 sec vs 5 min manual              │
│                                                │
│ [Confirm] [Not Sure - Ask AI] [Skip]         │
└────────────────────────────────────────────────┘
```

**Behavior:**

1. **Instant Popup** - Modal shell appears <100ms
2. **AI Loading** - Inline spinners (⟳) next to each field label
3. **Progressive Fill** - Fields populate as AI responds
4. **User Override** - If user clicks dropdown → Cancel AI request, switch to "Manual Mode"
5. **Manual Mode** - Show dismissible AI suggestion hint: "AI suggests: [suggestion] (95%) - Click to apply"

**States:**

| State         | Badge              | Buttons                 | Behavior                                      |
| ------------- | ------------------ | ----------------------- | --------------------------------------------- |
| AI Mode       | Blue "AI Assisted" | Confirm, Not Sure, Skip | AI suggestions pre-filled                     |
| Manual Mode   | Gray "Manual"      | Confirm, Not Sure, Skip | User entered data, AI hint shown              |
| Loading       | None               | Buttons disabled        | Spinners active                               |
| Timeout (>5s) | Gray "Manual"      | Confirm, Not Sure, Skip | Fields enabled, show manual selection message |

---

#### Variant 2: Required Tagging (Point → G36 Port)

**Trigger:** User drags untagged point to G36 input port

**Layout:**

```
┌────────────────────────────────────────────────┐
│ 223P Semantic Mapping                     [×]  │
│ ⚠️ Required for G36                            │
├────────────────────────────────────────────────┤
│                                                │
│ AHU-1_Sensor3          analog-input           │
│ Present Value: 55.2°F                         │
│                                                │
│ 🎯 Connecting to: G36 AHU Economizer          │
│    Port: Mixed Air Temperature                │
│    Expected: Temperature Sensor               │
│                                                │
│ [Form fields same as Optional variant...]     │
│                                                │
│ ⚠️ Required for G36 Connection                 │
│    This point must be tagged to connect       │
│    to the G36 sequence block.                 │
│                                                │
│ [Confirm] [Not Sure - Ask AI] [Cancel]       │
└────────────────────────────────────────────────┘
```

**Key Differences:**

- **Badge:** Red "⚠️ Required for G36" (not blue optional)
- **G36 Context Panel:** Shows which block, port, and expected type
- **No Skip Button:** Replaced with "Cancel" (aborts connection)
- **Message:** Warning emphasizes requirement, not suggestion

**Cancel Behavior:**

- Connection aborted
- Point returns to left sidebar
- G36 port remains empty

---

#### Variant 3: Chat Mode (CopilotKit)

**Trigger:** User clicks "Not Sure - Ask AI" OR AI confidence <50%

**Layout:**

```
┌────────────────────────────────────────────────┐
│ 223P Semantic Mapping - AI Chat           [×]  │
│ ℹ️ Optional - Recommended                      │
├────────────────────────────────────────────────┤
│                                                │
│ AHU-1_Sensor3          analog-input           │
│ Present Value: 55.2°F                         │
│                                                │
│ ┌────────────────────────────────────────────┐│
│ │ 💬 Chat                                    ││
│ │                                            ││
│ │ AI: I'm not confident about this point.   ││
│ │     Can you tell me what equipment this   ││
│ │     is connected to?                       ││
│ │                                            ││
│ │ You: It's a mixed air temperature sensor  ││
│ │      for the AHU economizer               ││
│ │                                            ││
│ │ AI: Got it! Based on that:                ││
│ │     • Equipment: AHU                       ││
│ │     • Device: Temperature Sensor           ││
│ │     • Property: Mixed Air Temperature      ││
│ │                                            ││
│ │     Does this look correct?                ││
│ │                                            ││
│ │ [Type your message...]                     ││
│ └────────────────────────────────────────────┘│
│                                                │
│ [Apply Suggestion] [Back to Form] [Cancel]   │
└────────────────────────────────────────────────┘
```

**Chat Context (CopilotKit):**

- BACnet point metadata (name, description, type, units)
- Other points from same equipment (for grouping inference)
- BuildingMOTIF template library context
- G36 port requirements (if triggered from G36 connection)

**Actions:**

- **Apply Suggestion** → Fills form fields, returns to form view
- **Back to Form** → Returns to form without applying
- **Cancel** → Closes popup (same as variant 1 or 2 depending on trigger)

---

### 4.3 G36 Block on Canvas

**Default State (React Flow Node):**

```
┌─────────────────────────────────────────┐
│ G36 AHU Economizer        🔧 economizer │  <- Label + badge
├─────────────────────────────────────────┤
│ - Outside Air Temp            OA Damper Cmd -  │
│ - Return Air Temp             RA Damper Cmd -  │
│ - Mixed Air Temp                              │
│                                               │
│ ⚠️ 3 inputs required                         │
│                                               │
│ + Configure Parameters                        │
└───────────────────────────────────────────────┘
```

**Connected State:**

```
┌─────────────────────────────────────────┐
│ G36 AHU Economizer        🔧 economizer │
├─────────────────────────────────────────┤
│ - Outside Air Temp            OA Damper Cmd -  │
│   🔗 AHU-1_OAT ✓                              │
│                                               │
│ - Return Air Temp             RA Damper Cmd -  │
│   🔗 AHU-1_RAT ✓                              │
│                                               │
│ - Mixed Air Temp                              │
│   ⚠️ Not connected                           │
│                                               │
│ ⚠️ 1 input required                          │
│                                               │
│ + Configure Parameters                        │
└───────────────────────────────────────────────┘
```

**Fully Connected State:**

```
┌─────────────────────────────────────────┐
│ G36 AHU Economizer        🔧 economizer │  <- GREEN BORDER
├─────────────────────────────────────────┤
│ - Outside Air Temp            OA Damper Cmd -  │
│   🔗 AHU-1_OAT ✓                              │
│                                               │
│ - Return Air Temp             RA Damper Cmd -  │
│   🔗 AHU-1_RAT ✓                              │
│                                               │
│ - Mixed Air Temp                              │
│   🔗 AHU-1_MAT ✓                              │
│                                               │
│ ✓ Ready to configure parameters              │
│                                               │
│ + Configure Parameters                        │
└───────────────────────────────────────────────┘
```

**Port States:**

| State              | Connector      | Text            | Connection Line |
| ------------------ | -------------- | --------------- | --------------- |
| Empty (required)   | ○ Gray outline | Port name       | -               |
| Connected (valid)  | ● Green filled | 🔗 Point name ✓ | Blue solid      |
| Type mismatch      | ⊗ Red outline  | ✗ Error message | Red dashed      |
| Hover compatible   | ◉ Green pulse  | Port name       | -               |
| Hover incompatible | ⊗ Red pulse    | Error tooltip   | -               |

---

### 4.4 G36 Parameter Configuration Modal

**Trigger:** User clicks "+ Configure Parameters" on G36 block

**Layout:**

```
┌──────────────────────────────────────┐
│ G36 AHU Economizer - Parameters [×] │
├──────────────────────────────────────┤
│                                      │
│ Min OA Setpoint                      │
│ [15] %                               │
│                                      │
│ Economizer Enable Temp               │
│ [65] °F                              │
│                                      │
│ Deadband                             │
│ [2] °F                               │
│                                      │
│ [Save] [Cancel]                      │
└──────────────────────────────────────┘
```

**Parameters Source:**

- Derived from Modelica G36 parameter schemas
- Reference: `https://github.com/lbl-srg/modelica-buildings/tree/master/Buildings/Controls/OBC/ASHRAE/G36`
- See: `docs/feature-development/ashrae-223p-ai-g36-integration/g36-parameter-schemas.json` (to be created in Epic 2)

---

## 5. Interaction Flows

### Flow 1: Fast Path - Tagged Point (30 seconds)

```
1. User drags AHU-1_OAT from left panel
   ↓
2. Popup appears instantly (<100ms)
   ├─ Point info displayed
   ├─ Loading spinners active
   └─ Fields enabled (user can edit immediately)
   ↓
3. AI responds (~1-2 seconds)
   ├─ Equipment: "VAV Terminal Unit" (95%)
   ├─ Device: "Temperature Sensor" (95%)
   ├─ Property: "Zone Air Temperature" (95%)
   └─ Spinners → Green checkmarks ✓
   ↓
4. User verifies suggestion (5 seconds)
   ↓
5. User clicks "Confirm"
   ↓
6. Point added to canvas with 223P tags
   ↓
7. Tags visible in left panel (🏷️ badges)

Total: ~10-30 seconds
```

---

### Flow 2: Conversational Path - Ambiguous Point (1-2 min)

```
1. User drags "Temp1" (ambiguous name)
   ↓
2. Popup appears, AI analyzes
   ↓
3. AI responds with low confidence (45%)
   ├─ User sees low confidence bar
   └─ User clicks "Not Sure - Ask AI"
   ↓
4. Chat interface opens
   ↓
5. AI: "I'm not confident. What equipment is this?"
   ↓
6. User: "Zone temp sensor for VAV box 2-01"
   ↓
7. AI: "Got it! Equipment: VAV, Device: Temp Sensor, Property: Zone Air Temp"
   ↓
8. User: "Yes, correct"
   ↓
9. User clicks "Apply Suggestion"
   ↓
10. Form fields populate
   ↓
11. User clicks "Confirm"
   ↓
12. Point added with 223P tags

Total: ~1-2 minutes
```

---

### Flow 3: G36 Connection - Untagged Point (Required)

```
1. G36 block on canvas (from left panel)
   ├─ 3 empty input ports
   └─ Status: "⚠️ 3 inputs required"
   ↓
2. User drags AHU-1_Sensor3 (untagged)
   ↓
3. User hovers over "Mixed Air Temp" port
   ├─ Port shows green pulse (droppable)
   └─ Tooltip: "Will require 223P tagging"
   ↓
4. User drops point
   ↓
5. 223P popup appears (REQUIRED variant)
   ├─ Badge: "⚠️ Required for G36"
   ├─ G36 Context: "Connecting to: G36 AHU Economizer"
   ├─ Expected: "Temperature Sensor"
   └─ No "Skip" button (only Cancel)
   ↓
6. AI suggests mapping (92% confidence)
   ↓
7. User verifies, clicks "Confirm"
   ↓
8. Connection completes
   ├─ Port: ● Green filled
   ├─ Label: "🔗 AHU-1_Sensor3 ✓"
   └─ Status: "⚠️ 2 inputs required"
   ↓
9. Point now shows 223P badges in left panel

Total: ~30-60 seconds
```

---

### Flow 4: User Override - Manual Entry

```
1. Popup appears, AI loading
   ↓
2. User doesn't wait, clicks "Equipment Type" dropdown
   ↓
3. AI request canceled
   ├─ Mode badge: "AI Assisted" → "Manual"
   └─ Confidence bar hidden
   ↓
4. AI response arrives while user is editing
   ↓
5. System does NOT overwrite user input
   ↓
6. Shows hint: "ℹ️ AI suggests: Zone Air Temp Sensor (95%) - Click to apply"
   ↓
7. User can:
   ├─ Ignore → Continue manual entry
   └─ Click hint → Replace with AI suggestion
   ↓
8. User completes form, clicks "Confirm"
   ↓
9. Point added with user-defined tags

Total: Variable (user-driven)
```

---

## 6. UX Pattern Decisions

### Validation Feedback

| State   | Visual               | Location             | Timing                         |
| ------- | -------------------- | -------------------- | ------------------------------ |
| Success | Green ✓ checkmark    | Inline next to field | After AI response or selection |
| Error   | Red ✗ icon + message | Inline below field   | Real-time on change            |
| Warning | Orange ⚠️ + message  | Inline below field   | Real-time on change            |
| Loading | Blue ⟳ spinner       | Inline next to label | During AI analysis             |

### Modal Behavior

| Behavior         | Decision                           | Rationale                                          |
| ---------------- | ---------------------------------- | -------------------------------------------------- |
| Open trigger     | Auto on point drag                 | Hypothesis: embedding in workflow reduces friction |
| Dismiss          | Click outside → Warning if unsaved | Prevent accidental data loss                       |
| Keyboard         | ESC key → Same as Cancel           | Standard modal UX                                  |
| Focus management | Auto-focus first dropdown          | Enable keyboard navigation                         |

### Connection Feedback

| State              | Port Visual         | Line Visual | Animation         |
| ------------------ | ------------------- | ----------- | ----------------- |
| Compatible hover   | Green pulse         | -           | Pulse 1s infinite |
| Incompatible hover | Red pulse + tooltip | -           | Shake effect      |
| Connected valid    | Green filled ●      | Blue solid  | -                 |
| Type mismatch      | Red outline ⊗       | Red dashed  | -                 |

### Button Hierarchy

| Button Type        | Style               | Usage                               |
| ------------------ | ------------------- | ----------------------------------- |
| Primary            | Blue filled         | Main action (Confirm, Apply)        |
| Secondary          | Gray outline        | Alternative action (Not Sure, Back) |
| Cancel/Destructive | Transparent outline | Cancel, Skip, Disconnect            |

---

## 7. Responsive & Accessibility

### Browser Support

**Target:** Chrome latest version only (per NFR004)

### Accessibility Requirements

**WCAG Level:** Defer to project-wide standard (not specified in PRD)

**Key Requirements:**

- ✅ Keyboard navigation for all interactive elements
- ✅ Focus indicators on all inputs, buttons, ports
- ✅ ARIA labels for screen readers (shadcn/ui provides by default)
- ✅ Alt text for status icons (✓, ✗, ⚠️)
- ✅ Form field labels properly associated
- ✅ Error messages announced to screen readers

**React Flow Accessibility:**

- Keyboard navigation for canvas panning
- Tab through nodes in document order
- Enter/Space to activate connections

---

## 8. Out of Scope

### Excluded from This Release

**BOPTest Visualization:**

- Results visualization UI
- Performance metrics display
- 24hr simulation graphs
- Deferred to Epic 6

**Multi-Browser Support:**

- Firefox, Safari, Edge compatibility
- Chrome only (per NFR004)

**Mobile/Tablet:**

- Desktop-first, no mobile optimization
- Touch gestures not required

**Advanced AI Features:**

- Real-time learning from corrections
- Custom template generation
- NLP for point naming

**Color Branding:**

- Final palette selection deferred
- Use existing Designer app colors for MVP
- Reference themes available in `ux-color-themes.html`

---

## 9. Design Assets

### Mockups

**Interactive HTML:** `ux-design-mockups.html`

**Scenarios:**

1. Scenario 1: Optional Tagging (point → canvas)
2. Scenario 2: Required for G36 (point → G36 port)
3. Scenario 3: Chat Mode (low confidence)
4. Scenario 4: G36 Fully Connected

### Color Themes (Future Reference)

**HTML Visualizer:** `ux-color-themes.html`

**Themes:**

1. Vibrant Tech (blue/purple)
2. Neon Gradient (purple-pink)
3. Cyber Green (neon green)
4. Sunset Energy (orange-pink)
5. **Dark Energy** (tastytrade-inspired, recommended)

---

## 10. Implementation Notes

### Component Library Integration

**shadcn/ui Components:**

- Dialog (223P popup, parameter config)
- Select/Dropdown (equipment, device, property)
- Badge (point types, 223P tags)
- Form (input fields)
- Toast (success/error notifications)
- Button (primary, secondary, cancel)

**CopilotKit Integration:**

- Use default chat component
- Customize with 223P context
- Include BuildingMOTIF template knowledge

**React Flow:**

- Custom node types for G36 blocks
- Custom edge types for connections
- Port validation hooks

### State Management (Zustand)

**Key State:**

- BACnet points with 223P metadata
- G36 block connections
- Modal open/close state
- AI loading state
- Validation errors

**Subscribe Patterns:**

```typescript
// Subscribe to specific nested values
const valueType = useFlowStore((state) => {
  const node = state.nodes.find((n) => n.id === id);
  return node?.data?.valueType ?? "number";
});
```

### DTO Pattern (Mock → API Swap)

**Epic 1-2 (UI with Mocks):**

- `MockBuildingMOTIFService` implements `IBuildingMOTIFService`
- `MockG36Service` implements `IG36Service`
- Returns hardcoded DTOs matching real API structure

**Epic 3-4 (Backend Integration):**

- `ApiBuildingMOTIFService` implements `IBuildingMOTIFService`
- `ApiG36Service` implements `IG36Service`
- Zero UI changes required (same interface, same DTOs)

---

## 11. Success Metrics

### Hypothesis Validation (LinkedIn Demo)

**Goal:** Achieve positive feedback from 5+ BMS integrators

**Metrics:**

- Time to tag 1 point (target: <30 seconds)
- AI suggestion acceptance rate (target: >80%)
- Chat mode usage rate (expected: <20% for confident cases)
- User sentiment (qualitative feedback)

### UX Quality Metrics

**Speed:**

- Popup open time: <100ms
- AI response time: <2s (90th percentile)
- Total tagging time: <30s (fast path)

**Usability:**

- No user input overwritten by AI
- All G36 type mismatches prevented
- BuildingMOTIF unavailable → Fail fast with clear error

---

## 12. Next Steps

### Design Phase Complete

✅ Core experience defined (223P popup + G36 drag-drop)
✅ Interaction patterns specified (fast path + chat mode)
✅ Component specs documented
✅ Interactive mockups created
✅ UX patterns defined

### Implementation Phase (Epic 1-2)

**Epic 1: 223P Mapping UI with Mock DTOs** (12-15 stories)

- Build 223P popup (Optional + Required variants)
- Implement AI loading states
- Add manual override behavior
- Create 223P badge display in left panel
- Mock BuildingMOTIF service

**Epic 2: G36 Visual Blocks UI with Mock DTOs** (15-18 stories)

- Build G36 React Flow nodes
- Implement port-based drag-drop
- Add 223P type validation
- Create parameter configuration modal
- Mock G36/FMU service
- Document Modelica parameter mappings

**Reference:** See `epics.md` for detailed story breakdown

---

## 13. References

**PRD:** `PRD.md`
**Epics:** `epics.md`
**Product Brief:** `product-brief.md`
**Mockups:** `ux-design-mockups.html`
**Color Themes:** `ux-color-themes.html`

**External:**

- shadcn/ui: https://ui.shadcn.com/
- CopilotKit: https://www.copilotkit.ai/
- React Flow: https://reactflow.dev/
- Modelica G36: https://github.com/lbl-srg/modelica-buildings/tree/master/Buildings/Controls/OBC/ASHRAE/G36

---

**Document Status:** Final v1.0 - Ready for Epic 1-2 Implementation
