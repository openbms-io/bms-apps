# Technical Specification: Vercel AI SDK + Mem0 Integration

**Story**: 2.13 - Setup Vercel AI SDK + Mem0 in Designer App
**GitHub Issue**: [#67](https://github.com/openbms-io/bms-apps/issues/67)
**Status**: Draft
**Last Updated**: 2025-12-25

---

## 1. Overview

### 1.1 Purpose

Integrate production AI infrastructure into the Designer app to replace mock pattern-matching with intelligent semantic mapping suggestions. The system supports multiple AI providers (Claude and OpenAI) via Vercel AI SDK and uses Mem0 Cloud for persistent organization-scoped memory/learning.

### 1.2 Key Design Decisions

| Decision         | Choice                              | Rationale                            |
| ---------------- | ----------------------------------- | ------------------------------------ |
| AI Providers     | Claude (default) + OpenAI           | User requirement for flexibility     |
| Memory Scope     | Organization-level                  | Shared learning across org users     |
| Context Strategy | Option D - Rich Metadata            | Highest accuracy for varied naming   |
| Suggestion Flow  | Multi-step (System→Device→Property) | Matches UI cascade, focused AI calls |

### 1.3 Current State

- `MockAISuggestionService` provides hardcoded pattern matching on point names
- Returns `Equipment223PRecommendation` with confidence scores
- Interface: `IAISuggestionService.suggestMapping(point): Equipment223PRecommendation`

### 1.4 Target State

- Multi-provider AI infrastructure (Claude + OpenAI)
- API route handles AI calls (keeps secrets server-side)
- Organization-scoped memory enables learning from user corrections
- Multi-step suggestion flow matching UI cascade
- Rich metadata context for maximum accuracy

---

## 2. Architecture

### 2.1 Component Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                        Designer App (Client)                         │
├─────────────────────────────────────────────────────────────────────┤
│  React Component                                                     │
│       │                                                              │
│       ▼                                                              │
│  useAISuggestionQuery (React Query)                                 │
│       │                                                              │
│       ▼ HTTP POST                                                    │
└───────┼─────────────────────────────────────────────────────────────┘
        │
        ▼
┌─────────────────────────────────────────────────────────────────────┐
│                    Next.js API Route (Server)                        │
├─────────────────────────────────────────────────────────────────────┤
│  POST /api/ai/suggestions                                           │
│       │                                                              │
│       ├──► MemoryManager.retrieveContext() ──► Mem0 Cloud API       │
│       │                                                              │
│       ├──► SuggestionEngine.generate()                              │
│       │         │                                                    │
│       │         ├──► [AI_PROVIDER=anthropic] ──► Anthropic Claude   │
│       │         └──► [AI_PROVIDER=openai] ──► OpenAI GPT            │
│       │                                                              │
│       └──► MemoryManager.storeInteraction() ──► Mem0 Cloud API      │
│       │                                                              │
│       ▼                                                              │
│  Response: Equipment223PRecommendation                              │
└─────────────────────────────────────────────────────────────────────┘
```

### 2.2 Current State Sequence Diagram

```
┌─────────┐  ┌──────────────┐  ┌─────────────────┐  ┌────────────────┐  ┌─────────────────┐
│  User   │  │ControllerTree│  │ BuildingSemantics│ │ SystemCreate   │  │ Building        │
│         │  │  Container   │  │     Modal        │ │     Modal      │  │ Semantics API   │
└────┬────┘  └──────┬───────┘  └────────┬────────┘ └───────┬────────┘  └────────┬────────┘
     │              │                   │                  │                    │
     │ Drag point   │                   │                  │                    │
     │ onto canvas  │                   │                  │                    │
     │─────────────>│                   │                  │                    │
     │              │                   │                  │                    │
     │              │ Open modal with   │                  │                    │
     │              │ bacnetPointId,    │                  │                    │
     │              │ bacnetObjectType, │                  │                    │
     │              │ projectId         │                  │                    │
     │              │──────────────────>│                  │                    │
     │              │                   │                  │                    │
     │              │                   │ useSystemsQuery()│                    │
     │              │                   │──────────────────────────────────────>│
     │              │                   │<──────────────────────────────────────│
     │              │                   │ systems[]        │                    │
     │              │                   │                  │                    │
     │ See empty    │                   │                  │                    │
     │ system       │                   │                  │                    │
     │ dropdown     │                   │                  │                    │
     │<─────────────────────────────────│                  │                    │
     │              │                   │                  │                    │
     │              │                   │                  │                    │
     │ ┌────────────────────────────────────────────────────────────────────────────────────┐
     │ │  OPTION A: Select Existing System                                                  │
     │ └────────────────────────────────────────────────────────────────────────────────────┘
     │              │                   │                  │                    │
     │ Manually     │                   │                  │                    │
     │ select       │                   │                  │                    │
     │ existing     │                   │                  │                    │
     │ system       │                   │                  │                    │
     │─────────────────────────────────>│                  │                    │
     │              │                   │                  │                    │
     │              │                   │                  │                    │
     │ ┌────────────────────────────────────────────────────────────────────────────────────┐
     │ │  OPTION B: Create New System from Template (Click +)                               │
     │ └────────────────────────────────────────────────────────────────────────────────────┘
     │              │                   │                  │                    │
     │ Click + to   │                   │                  │                    │
     │ create new   │                   │                  │                    │
     │ system       │                   │                  │                    │
     │─────────────────────────────────>│                  │                    │
     │              │                   │                  │                    │
     │              │                   │ Open             │                    │
     │              │                   │ SystemCreate     │                    │
     │              │                   │ Modal            │                    │
     │              │                   │─────────────────>│                    │
     │              │                   │                  │                    │
     │ See template │                   │                  │                    │
     │ dropdown     │                   │                  │                    │
     │<────────────────────────────────────────────────────│                    │
     │              │                   │                  │                    │
     │ Manually     │                   │                  │                    │
     │ select       │                   │                  │                    │
     │ template     │                   │                  │                    │
     │─────────────────────────────────────────────────────>                    │
     │              │                   │                  │                    │
     │ Enter label  │                   │                  │                    │
     │ (e.g.,       │                   │                  │                    │
     │ "VAV-Zone5") │                   │                  │                    │
     │─────────────────────────────────────────────────────>                    │
     │              │                   │                  │                    │
     │ Click Create │                   │                  │                    │
     │─────────────────────────────────────────────────────>                    │
     │              │                   │                  │                    │
     │              │                   │                  │ createSystem()    │
     │              │                   │                  │ {templateId,      │
     │              │                   │                  │  label}           │
     │              │                   │                  │───────────────────>│
     │              │                   │                  │<───────────────────│
     │              │                   │                  │ systemUri         │
     │              │                   │                  │                    │
     │              │                   │<─────────────────│                    │
     │              │                   │ addLocalSystem() │                    │
     │              │                   │ (auto-select)    │                    │
     │              │                   │                  │                    │
     │ System auto- │                   │                  │                    │
     │ selected     │                   │                  │                    │
     │<─────────────────────────────────│                  │                    │
     │              │                   │                  │                    │
     │ ┌────────────────────────────────────────────────────────────────────────────────────┐
     │ │  CONTINUE: Select Device and Property                                              │
     │ └────────────────────────────────────────────────────────────────────────────────────┘
     │              │                   │                  │                    │
     │              │                   │ useDevicesQuery()│                    │
     │              │                   │ (systemUri,      │                    │
     │              │                   │  bacnetObjectType)                    │
     │              │                   │──────────────────────────────────────>│
     │              │                   │<──────────────────────────────────────│
     │              │                   │ devices[]        │                    │
     │              │                   │                  │                    │
     │ Manually     │                   │                  │                    │
     │ select       │                   │                  │                    │
     │ device       │                   │                  │                    │
     │─────────────────────────────────>│                  │                    │
     │              │                   │                  │                    │
     │              │                   │ usePropertiesQuery()                  │
     │              │                   │ (deviceUri,      │                    │
     │              │                   │  bacnetObjectType)                    │
     │              │                   │──────────────────────────────────────>│
     │              │                   │<──────────────────────────────────────│
     │              │                   │ properties[]     │                    │
     │              │                   │                  │                    │
     │ Manually     │                   │                  │                    │
     │ select       │                   │                  │                    │
     │ property     │                   │                  │                    │
     │─────────────────────────────────>│                  │                    │
     │              │                   │                  │                    │
     │ Click Save   │                   │                  │                    │
     │─────────────────────────────────>│                  │                    │
     │              │                   │                  │                    │
     │              │                   │ saveBacnetReference                   │
     │              │                   │ (propertyUri)    │                    │
     │              │                   │──────────────────────────────────────>│
     │              │                   │<──────────────────────────────────────│
     │              │                   │                  │                    │
     │ Modal closes │                   │                  │                    │
     │<─────────────────────────────────│                  │                    │
     │              │                   │                  │                    │
```

**Current State Issues**:

- User must manually select or create System → Device → Property with no guidance
- No AI suggestions to help with mapping
- No learning from previous mappings
- `useAISuggestionQuery` exists but is NOT integrated into the modal

---

### 2.3 Target State Sequence Diagram

```
┌─────────┐  ┌──────────────┐  ┌────────────────┐  ┌─────────────┐  ┌──────────────┐  ┌─────────┐
│  User   │  │ControllerTree│  │BuildingSemantics│ │ AI API Route│  │ MemoryManager│  │ Claude/ │
│         │  │  Container   │  │     Modal      │  │             │  │ (Mem0 Cloud) │  │ OpenAI  │
└────┬────┘  └──────┬───────┘  └───────┬────────┘  └──────┬──────┘  └──────┬───────┘  └────┬────┘
     │              │                  │                  │                │               │
     │ Drag point   │                  │                  │                │               │
     │ onto canvas  │                  │                  │                │               │
     │─────────────>│                  │                  │                │               │
     │              │                  │                  │                │               │
     │              │ Open modal with  │                  │                │               │
     │              │ point + orgId +  │                  │                │               │
     │              │ projectId        │                  │                │               │
     │              │─────────────────>│                  │                │               │
     │              │                  │                  │                │               │
     │              │                  │ useSystemsQuery()│                │               │
     │              │                  │ → GET systems[]  │                │               │
     │              │                  │                  │                │               │
     │              │                  │ ┌──────────────────────────────────────────────────────┐
     │              │                  │ │  STEP 1: SYSTEM SUGGESTION                          │
     │              │                  │ └──────────────────────────────────────────────────────┘
     │              │                  │                  │                │               │
     │              │                  │ Deterministic    │                │               │
     │              │                  │ filter: max 10   │                │               │
     │              │                  │ candidates       │                │               │
     │              │                  │                  │                │               │
     │              │                  │ POST /api/ai/suggestions          │               │
     │              │                  │ {step:"system",  │                │               │
     │              │                  │  orgId, point,   │                │               │
     │              │                  │  candidates}     │                │               │
     │              │                  │─────────────────>│                │               │
     │              │                  │                  │                │               │
     │              │                  │                  │ retrieveContext│               │
     │              │                  │                  │ (orgId, query) │               │
     │              │                  │                  │───────────────>│               │
     │              │                  │                  │<───────────────│               │
     │              │                  │                  │ memories[]     │               │
     │              │                  │                  │                │               │
     │              │                  │                  │ generateStepSuggestion        │
     │              │                  │                  │ (step, point,  │               │
     │              │                  │                  │  candidates,   │               │
     │              │                  │                  │  memories)     │               │
     │              │                  │                  │────────────────────────────────>│
     │              │                  │                  │<────────────────────────────────│
     │              │                  │                  │ {selectedId,   │               │
     │              │                  │                  │  confidence,   │               │
     │              │                  │                  │  reasoning}    │               │
     │              │                  │                  │                │               │
     │              │                  │<─────────────────│                │               │
     │              │                  │ suggestion       │                │               │
     │              │                  │                  │                │               │
     │ System dropdown                 │                  │                │               │
     │ pre-selects                     │                  │                │               │
     │ AI suggestion                   │                  │                │               │
     │ (highlighted)                   │                  │                │               │
     │<────────────────────────────────│                  │                │               │
     │              │                  │                  │                │               │
     │ Confirm or   │                  │                  │                │               │
     │ change       │                  │                  │                │               │
     │ selection    │                  │                  │                │               │
     │ (or click +  │                  │                  │                │               │
     │  to create)  │                  │                  │                │               │
     │─────────────────────────────────>                  │                │               │
     │              │                  │                  │                │               │
     │              │                  │ useDevicesQuery()│                │               │
     │              │                  │ → GET devices[]  │                │               │
     │              │                  │                  │                │               │
     │              │                  │ ┌──────────────────────────────────────────────────────┐
     │              │                  │ │  STEP 2: DEVICE SUGGESTION                          │
     │              │                  │ └──────────────────────────────────────────────────────┘
     │              │                  │                  │                │               │
     │              │                  │ POST /api/ai/suggestions          │               │
     │              │                  │ {step:"device",  │                │               │
     │              │                  │  context:{       │                │               │
     │              │                  │   selectedSystemId│               │               │
     │              │                  │  }}              │                │               │
     │              │                  │─────────────────>│                │               │
     │              │                  │                  │  ... same flow as above ...    │
     │              │                  │<─────────────────│                │               │
     │              │                  │                  │                │               │
     │ Device dropdown                 │                  │                │               │
     │ pre-selects                     │                  │                │               │
     │ AI suggestion                   │                  │                │               │
     │<────────────────────────────────│                  │                │               │
     │              │                  │                  │                │               │
     │ Confirm or   │                  │                  │                │               │
     │ change       │                  │                  │                │               │
     │─────────────────────────────────>                  │                │               │
     │              │                  │                  │                │               │
     │              │                  │ usePropertiesQuery()              │               │
     │              │                  │ → GET properties[]                │               │
     │              │                  │                  │                │               │
     │              │                  │ ┌──────────────────────────────────────────────────────┐
     │              │                  │ │  STEP 3: PROPERTY SUGGESTION                        │
     │              │                  │ └──────────────────────────────────────────────────────┘
     │              │                  │                  │                │               │
     │              │                  │ POST /api/ai/suggestions          │               │
     │              │                  │ {step:"property",│                │               │
     │              │                  │  context:{       │                │               │
     │              │                  │   selectedSystemId,               │               │
     │              │                  │   selectedDeviceId│               │               │
     │              │                  │  }}              │                │               │
     │              │                  │─────────────────>│                │               │
     │              │                  │                  │  ... same flow as above ...    │
     │              │                  │<─────────────────│                │               │
     │              │                  │                  │                │               │
     │ Property dropdown               │                  │                │               │
     │ pre-selects                     │                  │                │               │
     │ AI suggestion                   │                  │                │               │
     │<────────────────────────────────│                  │                │               │
     │              │                  │                  │                │               │
     │ Confirm and  │                  │                  │                │               │
     │ click Save   │                  │                  │                │               │
     │─────────────────────────────────>                  │                │               │
     │              │                  │                  │                │               │
     │              │                  │ POST /api/ai/suggestions/confirm  │               │
     │              │                  │ (for each step with wasOverridden)│               │
     │              │                  │─────────────────>│                │               │
     │              │                  │                  │ storeMapping   │               │
     │              │                  │                  │───────────────>│               │
     │              │                  │                  │                │               │
     │              │                  │ saveBacnetReference()             │               │
     │              │                  │                  │                │               │
     │ Modal closes │                  │                  │                │               │
     │ Point mapped │                  │                  │                │               │
     │ with AI help │                  │                  │                │               │
     │<────────────────────────────────│                  │                │               │
     │              │                  │                  │                │               │
```

### 2.4 Key Differences

| Aspect             | Current State             | Target State                                   |
| ------------------ | ------------------------- | ---------------------------------------------- |
| System Selection   | Manual only               | AI pre-selects, user confirms/overrides        |
| Device Selection   | Manual only               | AI pre-selects, user confirms/overrides        |
| Property Selection | Manual only               | AI pre-selects, user confirms/overrides        |
| Create System (+)  | Manual template selection | Still manual (user decides template)           |
| Learning           | None                      | Mem0 stores decisions, improves over time      |
| Context Used       | None                      | Rich metadata (name, description, units, etc.) |
| orgId              | Not passed                | Passed for org-scoped memory                   |

---

## 3. Technical Design

### 3.1 Dependencies

| Package             | Version | Purpose                   |
| ------------------- | ------- | ------------------------- |
| `ai`                | ^3.x    | Vercel AI SDK core        |
| `@ai-sdk/anthropic` | ^0.x    | Anthropic/Claude provider |
| `@ai-sdk/openai`    | ^0.x    | OpenAI provider           |
| `mem0ai`            | ^1.x    | Mem0 Cloud SDK            |

### 3.2 Environment Variables

| Variable            | Required    | Description                                           |
| ------------------- | ----------- | ----------------------------------------------------- |
| `AI_PROVIDER`       | No          | Provider selection: `anthropic` (default) or `openai` |
| `ANTHROPIC_API_KEY` | Conditional | Required if AI_PROVIDER=anthropic                     |
| `OPENAI_API_KEY`    | Conditional | Required if AI_PROVIDER=openai                        |
| `MEM0_API_KEY`      | Yes         | Mem0 Cloud API key                                    |
| `AI_MODEL`          | No          | Override default model (provider-specific)            |

**Default Models**:

- Anthropic: `claude-3-5-sonnet-20241022`
- OpenAI: `gpt-4o`

**Security Note**: No `NEXT_PUBLIC_` prefix. These are server-side only.

### 3.3 File Structure

```
apps/designer/src/
├── lib/ai/
│   ├── index.ts                    # Exports
│   ├── types.ts                    # (existing) AI type definitions
│   ├── ai-client.ts                # Multi-provider configuration
│   ├── ai-client.spec.ts           # Tests
│   ├── memory-manager.ts           # Mem0 Cloud client wrapper
│   ├── memory-manager.spec.ts      # Tests
│   ├── suggestion-engine.ts        # AI + Memory orchestration
│   └── suggestion-engine.spec.ts   # Tests
├── app/api/ai/suggestions/
│   ├── route.ts                    # POST endpoint
│   ├── route.spec.ts               # Tests
│   └── schemas.ts                  # Zod schemas
└── domains/building-semantics/
    ├── adapters/ashrae-223p/services/
    │   ├── interfaces/ai-suggestion.ts   # (modify) Make async
    │   └── mock-ai-suggestion.service.ts # (modify) Return Promise
    └── api/queries/
        └── use-ai-suggestion-query.ts    # (modify) Use API endpoint
```

---

## 4. Interface Contracts

### 4.1 Context Strategy (Option D - Rich Metadata)

Each AI call includes rich point metadata for maximum accuracy:

```typescript
interface AIPointContext {
  point: {
    name: string; // e.g., "VAV-2-01_ZoneTemp"
    objectType: string; // e.g., "analog-input"
    objectId: number;
    controllerId: string; // Pattern identification
    description?: string; // From discoveredProperties
    units?: string; // From discoveredProperties
    presentValue?: unknown; // From discoveredProperties
    stateText?: string[]; // For multistate objects
  };
  candidates: string[]; // Pre-filtered deterministic list (max 10)
  existingMappings: Array<{
    // Self-learning context from Mem0
    pointPattern: string; // e.g., "VAV-*_ZoneTemp"
    selectedId: string; // Previously selected
  }>;
}
```

### 4.2 Multi-Step Suggestion Flow

```
┌──────────────────────────────────────────────────────────────────────────┐
│  Step 1: System Selection (Modal Opens)                                  │
├──────────────────────────────────────────────────────────────────────────┤
│  1a. Deterministic: Filter templates/instances by controller patterns    │
│  1b. AI Suggestion: Select best from filtered list (≤10 candidates)     │
│  1c. Human: Confirms or overrides → Stored in Mem0                      │
└────────────────────────────────────┬─────────────────────────────────────┘
                                     ↓
┌──────────────────────────────────────────────────────────────────────────┐
│  Step 2: Device Selection (After system selected)                        │
├──────────────────────────────────────────────────────────────────────────┤
│  2a. Deterministic: Filter devices by system + point objectType         │
│  2b. AI Suggestion: Select best device from filtered list               │
│  2c. Human: Confirms or overrides → Stored in Mem0                      │
└────────────────────────────────────┬─────────────────────────────────────┘
                                     ↓
┌──────────────────────────────────────────────────────────────────────────┐
│  Step 3: Property Selection (After device selected)                      │
├──────────────────────────────────────────────────────────────────────────┤
│  3a. Deterministic: Filter properties by device + units/stateText       │
│  3b. AI Suggestion: Select best property from filtered list             │
│  3c. Human: Confirms or overrides → Stored in Mem0                      │
└──────────────────────────────────────────────────────────────────────────┘
```

### 4.3 API Request Schema

```typescript
// POST /api/ai/suggestions

interface AISuggestionRequest {
  step: "system" | "device" | "property";
  orgId: string; // Organization-scoped memory
  projectId: string;
  point: {
    name: string;
    objectType: string;
    objectId: number;
    controllerId: string;
    description?: string; // From discoveredProperties
    units?: string; // From discoveredProperties
    presentValue?: unknown; // From discoveredProperties
    stateText?: string[]; // For multistate objects
  };
  candidates: string[]; // Pre-filtered list (max 10)
  context?: {
    selectedSystemId?: string; // For device/property steps
    selectedDeviceId?: string; // For property step
  };
}
```

### 4.4 API Response Schema

```typescript
interface AISuggestionResponse {
  success: boolean;
  data: StepSuggestion;
}

interface StepSuggestion {
  selectedId: string;
  confidence: number; // 0-100
  reasoning: string;
  alternatives: Array<{ id: string; confidence: number }>;
}
```

### 4.5 Confirmation Endpoint

```typescript
// POST /api/ai/suggestions/confirm

interface AISuggestionConfirmRequest {
  orgId: string;
  projectId: string;
  step: "system" | "device" | "property";
  pointPattern: string; // e.g., "VAV-*_ZoneTemp"
  controllerId: string;
  selectedId: string;
  suggestedId: string; // What AI originally suggested
  wasOverridden: boolean; // True if user changed AI suggestion
}
```

### 4.6 Service Interface (Updated)

```typescript
// Multi-step async interface
interface IAISuggestionService {
  suggestSystem(
    point: BACnetPointData,
    candidates: string[],
  ): Promise<StepSuggestion>;
  suggestDevice(
    point: BACnetPointData,
    systemId: string,
    candidates: string[],
  ): Promise<StepSuggestion>;
  suggestProperty(
    point: BACnetPointData,
    deviceId: string,
    candidates: string[],
  ): Promise<StepSuggestion>;
  confirmSelection(
    step: "system" | "device" | "property",
    selection: ConfirmationData,
  ): Promise<void>;
}
```

---

## 5. Module Specifications

### 5.1 AI Client (`ai-client.ts`)

**Purpose**: Initialize Vercel AI SDK with configurable provider support.

**API**:

```typescript
type AIProvider = "anthropic" | "openai";

function getAIModel(): LanguageModel;
function getProvider(): AIProvider;
```

**Implementation**:

```typescript
import { createAnthropic } from "@ai-sdk/anthropic";
import { createOpenAI } from "@ai-sdk/openai";

type AIProvider = "anthropic" | "openai";

const DEFAULT_MODELS: Record<AIProvider, string> = {
  anthropic: "claude-3-5-sonnet-20241022",
  openai: "gpt-4o",
};

export function getProvider(): AIProvider {
  const provider = process.env.AI_PROVIDER || "anthropic";
  if (provider !== "anthropic" && provider !== "openai") {
    throw new Error(
      `Invalid AI_PROVIDER: ${provider}. Must be 'anthropic' or 'openai'`,
    );
  }
  return provider;
}

export function getAIModel() {
  const provider = getProvider();
  const modelId = process.env.AI_MODEL || DEFAULT_MODELS[provider];

  if (provider === "anthropic") {
    const anthropic = createAnthropic({
      apiKey: process.env.ANTHROPIC_API_KEY,
    });
    return anthropic(modelId);
  }

  const openai = createOpenAI({ apiKey: process.env.OPENAI_API_KEY });
  return openai(modelId);
}
```

### 5.2 Memory Manager (`memory-manager.ts`)

**Purpose**: Manage Mem0 Cloud context storage and retrieval at organization level.

**API**:

```typescript
class MemoryManager {
  retrieveContext(
    orgId: string,
    query: string,
    projectId?: string,
  ): Promise<MemoryContext>;
  storeMapping(
    orgId: string,
    mapping: MappingRecord,
    projectId?: string,
  ): Promise<void>;
}

interface MemoryContext {
  orgId: string;
  projectId?: string;
  relevantMemories: Array<{ text: string; score: number }>;
}

interface MappingRecord {
  pointPattern: string; // e.g., "VAV-*_ZoneTemp"
  controllerId: string;
  step: "system" | "device" | "property";
  selectedId: string;
  wasOverridden: boolean;
}
```

**Implementation**:

```typescript
import MemoryClient from "mem0ai";

export class MemoryManager {
  private client: MemoryClient;

  constructor() {
    this.client = new MemoryClient({ apiKey: process.env.MEM0_API_KEY });
  }

  async retrieveContext(
    orgId: string,
    query: string,
    projectId?: string,
  ): Promise<MemoryContext> {
    const memories = await this.client.search(query, {
      org_id: orgId, // Organization-scoped, not user-scoped
      ...(projectId && { metadata: { projectId } }),
      limit: 5,
    });
    return { orgId, projectId, relevantMemories: memories };
  }

  async storeMapping(
    orgId: string,
    mapping: MappingRecord,
    projectId?: string,
  ): Promise<void> {
    const text = `For ${mapping.step} selection: Points matching "${
      mapping.pointPattern
    }" from controller "${mapping.controllerId}" were mapped to "${
      mapping.selectedId
    }"${mapping.wasOverridden ? " (user override)" : ""}`;

    await this.client.add(text, {
      org_id: orgId,
      ...(projectId && { metadata: { projectId } }),
    });
  }
}

export const memoryManager = new MemoryManager();
```

### 5.3 Suggestion Engine (`suggestion-engine.ts`)

**Purpose**: Generate step-specific AI suggestions with memory context.

**API**:

```typescript
class SuggestionEngine {
  generateStepSuggestion(
    step: "system" | "device" | "property",
    point: AIPointContext["point"],
    candidates: string[],
    memoryContext: MemoryContext,
    selectionContext?: { systemId?: string; deviceId?: string },
  ): Promise<StepSuggestion>;
}
```

**Implementation**:

```typescript
import { generateObject } from "ai";
import { z } from "zod";
import { getAIModel } from "./ai-client";
import type { MemoryContext } from "./memory-manager";

const StepSuggestionSchema = z.object({
  selectedId: z.string(),
  confidence: z.number().min(0).max(100),
  reasoning: z.string(),
  alternatives: z.array(
    z.object({
      id: z.string(),
      confidence: z.number().min(0).max(100),
    }),
  ),
});

export class SuggestionEngine {
  async generateStepSuggestion(
    step: "system" | "device" | "property",
    point: AIPointContext["point"],
    candidates: string[],
    memoryContext: MemoryContext,
    selectionContext?: { systemId?: string; deviceId?: string },
  ): Promise<StepSuggestion> {
    const { object } = await generateObject({
      model: getAIModel(),
      schema: StepSuggestionSchema,
      system: this.buildSystemPrompt(step),
      prompt: this.buildUserPrompt(
        step,
        point,
        candidates,
        memoryContext,
        selectionContext,
      ),
    });

    return object;
  }

  private buildSystemPrompt(step: "system" | "device" | "property"): string {
    const stepDescriptions = {
      system:
        "Select the best ASHRAE 223P system template that matches this BACnet point.",
      device:
        "Select the best device type within the chosen system for this BACnet point.",
      property:
        "Select the best property (observable/actuatable) for this BACnet point.",
    };

    return `You are an expert in ASHRAE Standard 223P semantic modeling and BACnet systems.
${stepDescriptions[step]}

IMPORTANT:
- You MUST select from the provided candidates list only
- Use the point metadata (name, description, units, presentValue) to make your decision
- Consider previous mappings from this organization for similar points
- Provide confidence (0-100) and clear reasoning`;
  }

  private buildUserPrompt(
    step: "system" | "device" | "property",
    point: AIPointContext["point"],
    candidates: string[],
    memoryContext: MemoryContext,
    selectionContext?: { systemId?: string; deviceId?: string },
  ): string {
    const memoryStr =
      memoryContext.relevantMemories.length > 0
        ? `\n\nPrevious mappings from this organization:\n${memoryContext.relevantMemories
            .map((m) => `- ${m.text}`)
            .join("\n")}`
        : "";

    const contextStr = selectionContext
      ? `\n\nCurrent selection context:\n${
          selectionContext.systemId
            ? `- System: ${selectionContext.systemId}`
            : ""
        }${
          selectionContext.deviceId
            ? `\n- Device: ${selectionContext.deviceId}`
            : ""
        }`
      : "";

    return `Select the best ${step} for this BACnet point:

POINT METADATA:
- Name: ${point.name}
- Object Type: ${point.objectType}
- Object ID: ${point.objectId}
- Controller ID: ${point.controllerId}
${point.description ? `- Description: ${point.description}` : ""}
${point.units ? `- Units: ${point.units}` : ""}
${
  point.presentValue !== undefined
    ? `- Present Value: ${JSON.stringify(point.presentValue)}`
    : ""
}
${point.stateText?.length ? `- State Text: ${point.stateText.join(", ")}` : ""}

CANDIDATES (select one):
${candidates.map((c, i) => `${i + 1}. ${c}`).join("\n")}
${contextStr}
${memoryStr}`;
  }
}

export const suggestionEngine = new SuggestionEngine();
```

### 5.4 API Route (`route.ts`)

**Purpose**: HTTP endpoint that orchestrates AI suggestion generation.

**Endpoint**: `POST /api/ai/suggestions`

**Implementation**:

```typescript
import { NextRequest, NextResponse } from "next/server";
import { AISuggestionRequestSchema } from "./schemas";
import { handleApiError } from "@/lib/api/error-handler";
import { memoryManager } from "@/lib/ai/memory-manager";
import { suggestionEngine } from "@/lib/ai/suggestion-engine";

export async function POST(request: NextRequest): Promise<NextResponse> {
  try {
    const body = await request.json();
    const {
      step,
      orgId,
      projectId,
      point,
      candidates,
      context: selectionContext,
    } = AISuggestionRequestSchema.parse(body);

    // Build query for memory search
    const queryString = `${step} selection for BACnet point: ${point.name} (${point.objectType}) from controller ${point.controllerId}`;

    // Retrieve org-scoped memory context
    const memoryContext = await memoryManager.retrieveContext(
      orgId,
      queryString,
      projectId,
    );

    // Generate AI suggestion
    const suggestion = await suggestionEngine.generateStepSuggestion(
      step,
      point,
      candidates,
      memoryContext,
      selectionContext
        ? {
            systemId: selectionContext.selectedSystemId,
            deviceId: selectionContext.selectedDeviceId,
          }
        : undefined,
    );

    return NextResponse.json({ success: true, data: suggestion });
  } catch (error) {
    return handleApiError(error, "generate AI suggestion");
  }
}
```

### 5.5 Confirmation Route (`confirm/route.ts`)

**Purpose**: Store confirmed mappings for learning.

**Endpoint**: `POST /api/ai/suggestions/confirm`

**Implementation**:

```typescript
import { NextRequest, NextResponse } from "next/server";
import { AISuggestionConfirmRequestSchema } from "../schemas";
import { handleApiError } from "@/lib/api/error-handler";
import { memoryManager } from "@/lib/ai/memory-manager";

export async function POST(request: NextRequest): Promise<NextResponse> {
  try {
    const body = await request.json();
    const {
      orgId,
      projectId,
      step,
      pointPattern,
      controllerId,
      selectedId,
      suggestedId,
    } = AISuggestionConfirmRequestSchema.parse(body);

    const wasOverridden = selectedId !== suggestedId;

    await memoryManager.storeMapping(
      orgId,
      { pointPattern, controllerId, step, selectedId, wasOverridden },
      projectId,
    );

    return NextResponse.json({ success: true });
  } catch (error) {
    return handleApiError(error, "confirm AI suggestion");
  }
}
```

---

## 6. Testing Strategy

### 6.1 Unit Tests

| Module              | Test Focus                               | Mocking                               |
| ------------------- | ---------------------------------------- | ------------------------------------- |
| `ai-client`         | Provider selection, model initialization | `@ai-sdk/anthropic`, `@ai-sdk/openai` |
| `memory-manager`    | Context retrieval/storage                | `mem0ai`                              |
| `suggestion-engine` | Prompt building, response parsing        | `ai.generateObject`                   |
| `schemas`           | Validation acceptance/rejection          | None                                  |

### 6.2 AI Client Tests

```typescript
describe("ai-client", () => {
  describe("getProvider", () => {
    it("returns anthropic by default");
    it("returns openai when AI_PROVIDER=openai");
    it("throws for invalid provider");
  });

  describe("getAIModel", () => {
    it("uses Anthropic when provider is anthropic");
    it("uses OpenAI when provider is openai");
    it("uses custom model from AI_MODEL env");
    it("uses default model for provider when AI_MODEL not set");
  });
});
```

### 6.3 API Route Tests

```typescript
/**
 * @jest-environment node
 */
describe("POST /api/ai/suggestions", () => {
  it("returns AI suggestion for valid point data");
  it("returns 400 for invalid request body");
  it("returns 500 when AI service fails");
});
```

Mock both `memoryManager` and `suggestionEngine` to isolate route logic.

---

## 7. Implementation Plan

### Phase 1: Infrastructure Setup

| Step | Task                      | Output                          |
| ---- | ------------------------- | ------------------------------- |
| 1.1  | Install packages          | `package.json` updated          |
| 1.2  | Add environment variables | `.env.template` updated         |
| 1.3  | Create API schemas        | `schemas.ts`, `schemas.spec.ts` |

### Phase 2: Core Modules (TDD)

| Step | Task                       | Output                                              |
| ---- | -------------------------- | --------------------------------------------------- |
| 2.1  | AI client (multi-provider) | `ai-client.ts`, `ai-client.spec.ts`                 |
| 2.2  | Memory manager             | `memory-manager.ts`, `memory-manager.spec.ts`       |
| 2.3  | Suggestion engine          | `suggestion-engine.ts`, `suggestion-engine.spec.ts` |

### Phase 3: API Integration

| Step | Task                      | Output                                   |
| ---- | ------------------------- | ---------------------------------------- |
| 3.1  | Create API route          | `route.ts`, `route.spec.ts`              |
| 3.2  | Update interface to async | `ai-suggestion.ts` modified              |
| 3.3  | Update mock service       | `mock-ai-suggestion.service.ts` modified |
| 3.4  | Update React Query hook   | `use-ai-suggestion-query.ts` modified    |

### Phase 4: Validation

| Step | Task           | Output                   |
| ---- | -------------- | ------------------------ |
| 4.1  | Run all tests  | All tests pass           |
| 4.2  | Manual testing | UI works with real AI    |
| 4.3  | Documentation  | README updated if needed |

---

## 8. Acceptance Criteria

From GitHub Issue #67:

- [ ] Vercel AI SDK packages installed and configured
- [ ] Claude/Anthropic integration functional
- [ ] OpenAI integration functional
- [ ] Mem0 Cloud context storage and retrieval working
- [ ] Environment variables properly configured
- [ ] Basic integration tests passing
- [ ] Documentation complete

---

## 9. Risks and Mitigations

| Risk                       | Impact | Mitigation                              |
| -------------------------- | ------ | --------------------------------------- |
| API key exposure           | High   | Server-side only, no NEXT_PUBLIC prefix |
| Rate limiting              | Medium | Implement request throttling in hook    |
| Mem0 latency               | Low    | Parallel context retrieval              |
| Model response variability | Medium | Zod schema enforces structure           |
| Provider unavailability    | Medium | Fallback to mock service                |

---

## 10. Design Decisions (Resolved)

1. **Memory Scope**: Organization-level memory via `orgId`

   - Memory is shared across all users in an organization
   - Enables collective learning from all mapping decisions
   - `orgId` passed from container through modal

2. **Context Strategy**: Option D - Rich Metadata

   - Includes: name, objectType, objectId, controllerId, description, units, presentValue, stateText
   - Maximum accuracy for both good and poor naming conventions
   - Can reduce context later if needed

3. **Suggestion Flow**: Multi-step cascade

   - Step 1: System suggestion (modal opens)
   - Step 2: Device suggestion (after system selected)
   - Step 3: Property suggestion (after device selected)
   - Each step uses deterministic pre-filtering + AI selection

4. **Fallback behavior**: Show "AI unavailable" message
   - If AI/Mem0 fails, display error message to user
   - User proceeds with manual selection

---

## Appendix A: Existing Code References

| File                                                                                         | Purpose                      |
| -------------------------------------------------------------------------------------------- | ---------------------------- |
| `src/lib/ai/types.ts`                                                                        | Existing AI type definitions |
| `src/domains/building-semantics/adapters/ashrae-223p/services/interfaces/ai-suggestion.ts`   | Service interface            |
| `src/domains/building-semantics/adapters/ashrae-223p/services/mock-ai-suggestion.service.ts` | Mock implementation          |
| `src/domains/building-semantics/api/queries/use-ai-suggestion-query.ts`                      | React Query hook             |
| `src/lib/api/error-handler.ts`                                                               | API error handling pattern   |

## Appendix B: Provider Comparison

| Feature           | Anthropic Claude             | OpenAI GPT                      |
| ----------------- | ---------------------------- | ------------------------------- |
| Default Model     | claude-3-5-sonnet-20241022   | gpt-4o                          |
| Structured Output | generateObject()             | generateObject()                |
| API Key           | ANTHROPIC_API_KEY            | OPENAI_API_KEY                  |
| Cost              | ~$3/1M input, ~$15/1M output | ~$2.50/1M input, ~$10/1M output |
