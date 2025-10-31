# BMS Supervisor Controller - Claude Context

## Project Overview

Visual programming platform for building management systems with IoT device integration.

**Architecture Flow**: Designer (Visual Programming with Zod Validation) → BMS IoT App (Execution Engine)

## Schema Validation

The Designer app includes Zod schemas for validating visual programming configurations before sending them to the BMS IoT App for execution on IoT devices.

- **Designer App**: Creates and validates visual flow configurations using drag-and-drop interface with Zod schemas
- **BMS IoT App**: Receives validated configurations and executes the control logic with BACnet/MQTT integration

## Development Philosophy

### Core Principles

1. **Test-Driven Development (TDD)**

   - Write tests first, then implement
   - Red-Green-Refactor cycle
   - Tests drive design decisions
   - Focus on testing behavior and not using logger functions.

2. **DO NOT OVERENGINEER**

   - Simple, direct implementations
   - Avoid premature abstractions
   - Minimal viable solutions that can evolve

3. **Fail Fast**

   - Surface issues immediately
   - Clear error messages
   - Quick feedback loops

4. **Prop Up Issues Faster**

   - Make problems visible quickly
   - Don't hide or suppress errors
   - Enable rapid debugging and resolution

5. **DO NOT ADD COMMENTS**
   - Make the function name and variable names clear enough, so comments are not required
   - Add comments ONLY in special cases to define WHY was something done.
   - Dont add comments for WHAT was done. Use variables and functions for WHAT names.

### TDD Workflow for This Project

#### Schema Development (TDD)

```bash
# 1. Write failing test
cd apps/designer
# Edit .spec.ts file in src/lib/schemas/ with new test case

# 2. Run test (should fail)
pnpm test

# 3. Implement schema to make test pass
# Edit schema .ts file in src/lib/schemas/

# 4. Verify test passes
pnpm test
```

#### BMS IoT App Development (TDD)

```bash
# 1. Write failing test
cd apps/bms-iot-app
# Edit test_*.py file

# 2. Run test (should fail)
pytest tests/

# 3. Implement feature
# Edit src/ files

# 4. Verify test passes
pytest tests/

# 5. Test integration
pnpm bms-iot:run
```

#### Component Development (TDD)

```bash
# 1. Write failing component test
cd apps/designer
# Edit *.spec.ts file

# 2. Run test (should fail)
pnpm test

# 3. Implement component
# Edit component .tsx file

# 4. Verify test passes
pnpm test
```

## Key Commands

### Quick Start

```bash
# Initial setup
pnpm install
pnpm run setup:hooks

# Development
pnpm run dev                    # Start both apps
pnpm run test                   # Run all tests
```

### Schema Development

```bash
cd apps/designer
pnpm test                        # Run schema + component tests
# Schemas are in src/lib/schemas/
```

### BMS IoT App Setup

```bash
# Root-level commands:
pnpm bms-iot:help                 # Show available commands
pnpm bms-iot:run                  # Run main application
pnpm bms-iot:test                 # Run comprehensive tests
```

### Designer App

```bash
cd apps/designer
pnpm run dev                    # Start on port 3000
pnpm test                       # React component tests
```

## Technology Stack

### Frontend (Designer)

- **Next.js 15.5** with Turbopack
- **TypeScript** with strict type checking
- **shadcn/ui** component library (Radix UI + Tailwind)
- **Tailwind CSS v4** for styling
- **React Flow** for visual programming interface
- **Zustand** for state management
- **Jest + React Testing Library** for testing

### Backend (BMS IoT App)

- **BACnet libraries** (BAC0, bacpypes) for IoT device communication
- **MQTT client** (paho-mqtt) for pub/sub messaging
- **Typer** for CLI interface
- **Pydantic** for data validation
- **SQLModel** for database operations
- **pytest** with extensive test coverage (800+ tests)

### Schema Validation

- **Schemas**: Zod schemas in Designer app (TypeScript)
- **Testing**: Jest (TypeScript) for schema validation

## File Structure

```
bms-supervisor-controller/
├── CLAUDE.md                  # This file - project context
├── README.md                  # User documentation
├── docs/coding-standards.md   # Development standards
├── apps/
│   ├── designer/             # Visual programming interface
│   │   └── src/lib/schemas/  # Zod schemas for validation
│   └── bms-iot-app/          # BACnet/MQTT execution engine
└── packages/
    └── mqtt_topics/          # MQTT topic management (Python + TypeScript)
```

## Common Development Tasks

### Adding New Node Type

```bash
# 1. TDD: Write test first
cd apps/designer
# Add test case to src/lib/schemas/nodes/types.spec.ts

# 2. Implement schema
# Add to NodeTypeSchema enum in src/lib/schemas/nodes/types.ts

# 3. Test the changes
pnpm test

# 4. Test integration in Designer
pnpm dev
```

### Adding New UI Components (shadcn/ui)

```bash
# Install specific component
npx shadcn@latest add <component-name>

# Example: Add form components
npx shadcn@latest add form select switch

# Available components: button, input, card, badge, dialog,
# dropdown-menu, separator, tooltip, form, select, switch, etc.
```

### Package manager

Nodejs -> pnpm
Python -> pip

### Tailwind CSS v4 Compatibility

**Important**: This project uses Tailwind CSS v4 with shadcn/ui. Some compatibility notes:

- Replaced `@apply bg-background text-foreground` with direct CSS properties
- Use `background-color: hsl(var(--background))` instead of `@apply bg-background`
- CSS custom properties (--border, --background, etc.) work fine as hsl() values
- All shadcn/ui components are compatible after CSS adjustments

### Troubleshooting (Fail Fast)

#### Schema Issues

```bash
# Test schema validation
cd apps/designer
pnpm test                       # Tests schema validation
```

#### Import Errors in Designer

```bash
# Test imports and schemas
cd apps/designer
pnpm test
```

#### BMS IoT App Import Issues

```bash
pnpm bms-iot:help                 # Test CLI imports
pnpm bms-iot:test                 # Run import tests
```

## Integration Points

### Designer → BMS IoT App

1. **Designer** creates and validates FlowNode configurations using Zod schemas
2. **Designer** serializes to JSON
3. **MQTT message** sends JSON configuration to BMS IoT App
4. **BMS IoT App** receives and executes the configuration
5. **BACnet execution engine** runs the configuration on IoT devices

### Testing Integration

```bash
# Start both apps
pnpm run dev

# Test Designer schemas
cd apps/designer
pnpm test

# Test BMS IoT App
pnpm bms-iot:test
```

## Zustand gotcha

- Subscribe to specific values in zustand store for nested objects. e.g below:

  const valueType = useFlowStore(state => {
  onst node = state.nodes.find(n => n.id === id)
  const nodeData = node?.data
  return nodeData?.metadata?.valueType ?? nodeData?.valueType ?? 'number' as ValueType
  })

  const label = useFlowStore(state => {
  const node = state.nodes.find(n => n.id === id)
  const nodeData = node?.data
  return nodeData?.label ?? 'Constant'
  })

## Development Mindset

- **Write tests first** - they define the expected behavior
- **Keep it simple** - avoid complex abstractions until needed
- **Make errors obvious** - don't hide problems
- **Quick iterations** - fast test-code-test cycles
- **Schema-driven** - changes start with schema tests, then implementation
- **Use existing components** - prefer shadcn/ui components over custom implementations
- **Define Types** - Dont use any or unknown. Define types where it cannot be inferred. But, dont fallback to using any or unknown.
- **Coding Conventions** - Follow coding conventions listed in docs/coding-standards.md
- **Bug Fix** - Always focus on finding and assessing root cause first. Present your plan, before provising a fix with options.
- **SOLID Principle** - Follow SOLID principle and make the code DRY.
- **YAGNI Principle** - YAGNI (You Aren't Gonna Need It) - Don't add complexity until needed
- Why are we setting to null? Keep it undefined. I think we should consistently just use undefined, unless there is a special condition to use null.
- Mock external libraries for integration and E2E tests. Unit test, you can mock designer modules. BUT DO NOT MOCK SYSTEM UNDER TEST.
- Dont add unnecessary comments. Make method names clear enough
- Remember the API layer SHOULD NOT HAVE or leak database relationship. The relationship should belong in Database layer.
- Use shadcn/ui components always.
