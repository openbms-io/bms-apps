# BMM Workflows - Complete v6 Guide

Master guide for BMM's four-phase methodology that adapts to project scale (Level 0-4) and context (greenfield/brownfield).

## Table of Contents

- [Core Innovations](#core-innovations)
- [Universal Entry Point](#universal-entry-point)
- [Four Phases Overview](#four-phases-overview)
- [Phase Details](#phase-details)
  - [Documentation Prerequisite](#documentation-prerequisite)
  - [Phase 1: Analysis](#phase-1-analysis)
  - [Phase 2: Planning](#phase-2-planning)
  - [Phase 3: Solutioning](#phase-3-solutioning)
  - [Phase 4: Implementation](#phase-4-implementation)
- [Scale Levels](#scale-levels)
- [Greenfield vs Brownfield](#greenfield-vs-brownfield)
- [Critical Rules](#critical-rules)

## Core Innovations

- **Scale-Adaptive Planning** - Automatic routing based on complexity (Level 0-4)
- **Just-In-Time Design** - Tech specs created per epic during implementation
- **Dynamic Expertise Injection** - Story-specific technical guidance
- **Continuous Learning Loop** - Retrospectives improve each cycle

## Universal Entry Point

**Always start with `workflow-status` or `workflow-init`**

### workflow-status

- Checks for existing workflow status file
- Displays current phase and progress
- Routes to appropriate next workflow
- Shows Phase 4 implementation state

### workflow-init

- Creates initial bmm-workflow-status.md
- Detects greenfield vs brownfield
- Routes undocumented brownfield to document-project
- Sets up workflow tracking

## Four Phases Overview

```
PREREQUISITE: document-project (brownfield without docs)
                    ↓
PHASE 1: Analysis (optional)
    brainstorm → research → brief
                    ↓
PHASE 2: Planning (required, scale-adaptive)
    Level 0-1: tech-spec only
    Level 2-4: PRD + epics
                    ↓
PHASE 3: Solutioning (Level 2-4 only)
    architecture → validation → gate-check
                    ↓
PHASE 4: Implementation (iterative)
    sprint-planning → epic-context → story cycle
```

## Phase Details

### Documentation Prerequisite

**When:** Brownfield projects without documentation OR post-completion cleanup

| Workflow         | Purpose                       | Output             |
| ---------------- | ----------------------------- | ------------------ |
| document-project | Analyze and document codebase | Comprehensive docs |

**Use Cases:**

1. **Pre-Phase 1**: Understand existing brownfield code
2. **Post-Phase 4**: Create clean documentation replacing scattered artifacts

### Phase 1: Analysis

**Optional workflows for discovery and requirements gathering**

| Workflow           | Agent         | Purpose               | Output                 |
| ------------------ | ------------- | --------------------- | ---------------------- |
| brainstorm-project | Analyst       | Software ideation     | Architecture proposals |
| brainstorm-game    | Game Designer | Game concept ideation | Concept proposals      |
| research           | Analyst       | Multi-mode research   | Research artifacts     |
| product-brief      | Analyst       | Strategic planning    | Product brief          |
| game-brief         | Game Designer | Game foundation       | Game brief             |

### Phase 2: Planning

**Required phase with scale-adaptive routing**

| Workflow         | Agent         | Output         | Levels      |
| ---------------- | ------------- | -------------- | ----------- |
| prd              | PM            | PRD.md + epics | 2-4         |
| tech-spec        | PM            | tech-spec.md   | 0-1         |
| gdd              | Game Designer | GDD.md         | Games       |
| create-ux-design | UX            | ux-design.md   | Conditional |

### Phase 3: Solutioning

**Architecture phase for Level 2-4 projects**

| Workflow               | Agent     | Purpose           | Output                 |
| ---------------------- | --------- | ----------------- | ---------------------- |
| create-architecture    | Architect | System design     | architecture.md + ADRs |
| validate-architecture  | Architect | Design validation | Validation report      |
| solutioning-gate-check | Architect | PRD/UX/arch check | Gate report            |

### Phase 4: Implementation

**Sprint-based development cycle**

#### Sprint Status System

**Epic Flow:** `backlog → contexted`

**Story Flow:** `backlog → drafted → ready-for-dev → in-progress → review → done`

#### Implementation Workflows

| Workflow          | Agent | Purpose                 | Status Updates                              |
| ----------------- | ----- | ----------------------- | ------------------------------------------- |
| sprint-planning   | SM    | Initialize tracking     | Creates sprint-status.yaml                  |
| epic-tech-context | SM    | Epic technical context  | Epic: backlog → contexted                   |
| create-story      | SM    | Draft story files       | Story: backlog → drafted                    |
| story-context     | SM    | Implementation guidance | Story: drafted → ready-for-dev              |
| dev-story         | DEV   | Implement               | Story: ready-for-dev → in-progress → review |
| code-review       | DEV   | Quality validation      | No auto update                              |
| retrospective     | SM    | Capture learnings       | Retrospective: optional → completed         |
| correct-course    | SM    | Handle issues           | Adaptive                                    |

#### Implementation Loop

```
sprint-planning (creates sprint-status.yaml)
    ↓
For each epic:
    epic-tech-context
        ↓
    For each story:
        create-story → story-context → dev-story → code-review
            ↓
        Mark done in sprint-status.yaml
    ↓
    retrospective (epic complete)
```

## Scale Levels

| Level | Scope         | Documentation         | Path            |
| ----- | ------------- | --------------------- | --------------- |
| 0     | Single change | tech-spec only        | Phase 2 → 4     |
| 1     | 1-10 stories  | tech-spec only        | Phase 2 → 4     |
| 2     | 5-15 stories  | PRD + architecture    | Phase 2 → 3 → 4 |
| 3     | 12-40 stories | PRD + full arch       | Phase 2 → 3 → 4 |
| 4     | 40+ stories   | PRD + enterprise arch | Phase 2 → 3 → 4 |

## Greenfield vs Brownfield

### Greenfield (New Projects)

```
Phase 1 (optional) → Phase 2 → Phase 3 (L2-4) → Phase 4
```

- Clean slate for design
- No existing constraints
- Direct to planning

### Brownfield (Existing Code)

```
document-project (if needed) → Phase 1 (optional) → Phase 2 → Phase 3 (L2-4) → Phase 4
```

- Must understand existing patterns
- Documentation prerequisite if undocumented
- Consider technical debt in planning

## Critical Rules

### Phase Transitions

1. **Check workflow-status** before any Phase 1-3 workflow
2. **Document brownfield** before planning if undocumented
3. **Complete planning** before solutioning
4. **Complete architecture** (L2-4) before implementation

### Implementation Rules

1. **Epic context first** - Must context epic before drafting stories
2. **Sequential by default** - Work stories in order within epic
3. **Learning transfer** - Draft next story after previous done
4. **Manual status updates** - Update sprint-status.yaml as needed

### Story Management

1. **Single source of truth** - sprint-status.yaml tracks everything
2. **No story search** - Agents read exact story from status file
3. **Context injection** - Each story gets specific technical guidance
4. **Retrospective learning** - Capture improvements per epic

### Best Practices

1. **Trust the process** - Let workflows guide you
2. **Respect scale** - Don't over-document small projects
3. **Use status tracking** - Always know where you are
4. **Iterate and learn** - Each epic improves the next

---

For specific workflow details, see individual workflow READMEs in their respective directories.
