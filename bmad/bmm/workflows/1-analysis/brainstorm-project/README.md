# Project Brainstorming Workflow

Structured ideation for software projects exploring problem spaces, architectures, and innovative solutions beyond traditional requirements gathering.

## Table of Contents

- [Purpose](#purpose)
- [Usage](#usage)
- [Process](#process)
- [Inputs & Outputs](#inputs--outputs)
- [Integration](#integration)

## Purpose

Generate multiple solution approaches for software projects through:

- Parallel ideation tracks (architecture, UX, integration, value delivery)
- Technical-business alignment from inception
- Hidden assumption discovery
- Innovation beyond obvious solutions

## Usage

```bash
# Run brainstorming session
bmad bmm *brainstorm-project

# Or via Analyst agent
*brainstorm-project
```

## Process

### 1. Context Capture

- Business objectives and constraints
- Technical environment
- Stakeholder needs
- Success criteria

### 2. Parallel Ideation

- **Architecture Track**: Technical approaches with trade-offs
- **UX Track**: Interface paradigms and user journeys
- **Integration Track**: System connection patterns
- **Value Track**: Feature prioritization and delivery

### 3. Solution Synthesis

- Evaluate feasibility and impact
- Align with strategic objectives
- Surface hidden assumptions
- Generate recommendations

## Inputs & Outputs

### Inputs

| Input             | Type     | Purpose                                       |
| ----------------- | -------- | --------------------------------------------- |
| Project Context   | Document | Business objectives, environment, constraints |
| Problem Statement | Optional | Core challenge or opportunity                 |

### Outputs

| Output                   | Content                                     |
| ------------------------ | ------------------------------------------- |
| Architecture Proposals   | Multiple approaches with trade-off analysis |
| Value Framework          | Prioritized features aligned to objectives  |
| Risk Analysis            | Dependencies, challenges, opportunities     |
| Strategic Recommendation | Synthesized direction with rationale        |

## Integration

### Workflow Chain

1. **brainstorm-project** ← Current step
2. research (optional deep dive)
3. product-brief (strategic document)
4. Phase 2 planning (PRD/tech-spec)

### Feed Into

- Product Brief development
- Architecture decisions
- PRD requirements
- Epic prioritization

## Best Practices

1. **Prepare context** - Gather business and technical background
2. **Think broadly** - Explore non-obvious approaches
3. **Document assumptions** - Capture implicit beliefs
4. **Consider constraints** - Technical, organizational, resource
5. **Focus on value** - Align to business objectives

## Configuration

```yaml
# bmad/bmm/config.yaml
output_folder: ./output
project_name: Your Project
```

## Related Workflows

- [Research](../research/README.md) - Deep investigation
- [Product Brief](../product-brief/README.md) - Strategic planning
- [PRD](../../2-plan-workflows/prd/README.md) - Requirements document

---

Part of BMad Method v6 - Phase 1 Analysis workflows
