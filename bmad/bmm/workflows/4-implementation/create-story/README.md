# Create Story Workflow

Just-in-time story generation creating one story at a time based on epic backlog state. Run by Scrum Master (SM) agent to ensure planned stories align with approved epics.

## Table of Contents

- [Usage](#usage)
- [Key Features](#key-features)
- [Inputs & Outputs](#inputs--outputs)
- [Workflow Behavior](#workflow-behavior)
- [Integration](#integration)

## Usage

```bash
# SM initiates next story creation
bmad sm *create-story
```

**When to run:**

- Sprint has capacity for new work
- Previous story is Done/Approved
- Team ready for next planned story

## Key Features

### Strict Planning Enforcement

- **Only creates stories enumerated in epics.md**
- Halts if story not found in epic plan
- Prevents scope creep through validation

### Intelligent Document Discovery

- Auto-finds tech spec: `tech-spec-epic-{N}-*.md`
- Discovers architecture docs across directories
- Builds prioritized requirement sources

### Source Document Grounding

- Every requirement traced to source
- No invention of domain facts
- Citations included in output

### Non-Interactive Mode

- Default "#yolo" mode minimizes prompts
- Smooth automated story preparation
- Only prompts when critical

## Inputs & Outputs

### Required Files

| File                     | Purpose                       | Priority |
| ------------------------ | ----------------------------- | -------- |
| epics.md                 | Story enumeration (MANDATORY) | Critical |
| tech-spec-epic-{N}-\*.md | Epic technical spec           | High     |
| PRD.md                   | Product requirements          | Medium   |
| Architecture docs        | Technical constraints         | Low      |

### Auto-Discovered Docs

- `tech-stack.md`, `unified-project-structure.md`
- `testing-strategy.md`, `backend/frontend-architecture.md`
- `data-models.md`, `database-schema.md`, `api-specs.md`

### Output

**Story Document:** `{story_dir}/story-{epic}.{story}.md`

- User story statement (role, action, benefit)
- Acceptance criteria from tech spec/epics
- Tasks mapped to ACs
- Testing requirements
- Dev notes with sources
- Status: "Draft"

## Workflow Behavior

### Story Number Management

- Auto-detects next story number
- No duplicates or skipped numbers
- Maintains epic.story convention

### Update vs Create

- **If current story not Done:** Updates existing
- **If current story Done:** Creates next (if planned)

### Validation Safeguards

**No Story Found:**

```
"No planned next story found in epics.md for epic {N}.
Run *correct-course to add/modify epic stories."
```

**Missing Config:**
Ensure `dev_story_location` set in config.yaml

## Integration

### v6 Implementation Cycle

1. **create-story** ← Current step (defines "what")
2. story-context (adds technical "how")
3. dev-story (implementation)
4. code-review (validation)
5. correct-course (if needed)
6. retrospective (after epic)

### Document Priority

1. **tech_spec_file** - Epic-specific spec
2. **epics_file** - Story breakdown
3. **prd_file** - Business requirements
4. **architecture_docs** - Technical guidance

## Configuration

```yaml
# bmad/bmm/config.yaml
dev_story_location: ./stories
output_folder: ./output

# workflow.yaml defaults
non_interactive: true
auto_run_context: true
```

## Troubleshooting

| Issue                   | Solution                                   |
| ----------------------- | ------------------------------------------ |
| "No planned next story" | Run `*correct-course` to add story to epic |
| Missing story_dir       | Set `dev_story_location` in config         |
| Tech spec not found     | Use naming: `tech-spec-epic-{N}-*.md`      |
| No architecture docs    | Add docs to docs/ or output/ folder        |

---

For workflow details, see [instructions.md](./instructions.md) and [checklist.md](./checklist.md).
