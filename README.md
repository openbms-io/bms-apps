# BMS Supervisor Controller

[![Phase](https://img.shields.io/badge/Phase-6%2F8-yellow.svg)](docs/PROJECT_STATUS.md)
[![Status](https://img.shields.io/badge/Status-Alpha-orange.svg)](docs/PROJECT_STATUS.md)
[![License](https://img.shields.io/badge/License-AGPL-blue.svg)](docs/LICENSE.md)
[![Discord](https://img.shields.io/discord/1417899927304016146)](https://discord.gg/SUkvbwkDGz)

Visual programming platform for building management systems with IoT device integration.
[Live Preview](https://supervisor-designer.vercel.app/projects)

## 📊 Project Status

**Current Phase**: 6/8 (Persistence & Integration) - See [PROJECT_STATUS.md](docs/PROJECT_STATUS.md) for detailed progress tracking.

- ✅ **Phases 1-5 Complete**: Core visual programming infrastructure
- 🚧 **Phase 6 In Progress**: Database persistence, project management, edge refinements
- 📋 **Phase 7 Planned**: Real BACnet device discovery and integration
- 📋 **Phase 8 Deferred**: Multi-supervisor management

## 🤝 Contributing

We welcome contributions! This project is in active development and there are many areas where help is needed:

- **BACnet Integration**: Real device discovery and protocol expertise
- **Testing**: End-to-end scenarios and performance testing
- **Documentation**: User guides and API documentation
- **UI/UX**: Canvas improvements and mobile responsiveness

See [CONTRIBUTING.md](docs/CONTRIBUTING.md) for detailed contribution guidelines.

## Architecture

This is a **PNPM monorepo** with two main applications and a shared schema package:

- **🎨 Designer App** (`apps/designer/`) - Next.js 15.5 visual programming interface with Zod schema validation
- **🔧 BMS IoT App** (`apps/bms-iot-app/`) - BACnet/MQTT runtime for IoT devices

## 🚀 Quick Start

### Prerequisites

- **Node.js** ≥18.0.0
- **PNPM** ≥9.0.0
- **Python** ≥3.11

### Installation

```bash
# Clone repository with submodules
git clone --recurse-submodules https://github.com/openbms-io/supervisor.git
cd bms-supervisor-controller

# Install all dependencies
pnpm install
```

### Development

```bash
# Start both apps in development mode
pnpm run dev

# Or start individually:
pnpm --filter designer run dev          # Designer on http://localhost:3000
pnpm bms-iot:run                        # BMS IoT App
```

## 📋 Schema Management

### Schema Development Workflow

Schemas are managed within the Designer app using Zod for validation:

1. **Edit schemas** in `apps/designer/src/lib/schemas/`
2. **Run tests** to validate changes: `pnpm --filter designer test`
3. **Test integration** in Designer app

### Schema Structure

```
apps/designer/src/lib/schemas/
├── version.ts              # Schema versioning system
├── common/
│   ├── position.ts         # PositionSchema + tests
│   └── position.spec.ts
└── nodes/
    ├── types.ts           # NodeTypeSchema + tests
    ├── types.spec.ts
    ├── flow-node.ts       # FlowNodeSchema + tests
    └── flow-node.spec.ts
```

### Adding New Schemas

1. Create new schema file in appropriate directory (`common/` or `nodes/`)
2. Create corresponding `.spec.ts` test file
3. Add export to `index.ts`
4. Run `pnpm --filter designer test` to validate

## 🛠️ Commands

### Root Level Commands

```bash
# Development
pnpm run dev                    # Start all apps in development
pnpm run build                  # Build all apps
pnpm run test                   # Run all tests
pnpm run lint                   # Lint all code
pnpm run clean                  # Clean all build outputs

# Code Formatting (Python)
pnpm run python:format          # Format Python code with black
pnpm run python:lint            # Lint Python code with ruff
pnpm run python:test            # Run Python tests
```

### Designer App Commands

```bash
cd apps/designer

npm run dev                     # Development server (http://localhost:3000)
npm run build                   # Production build
npm run start                   # Start production server
npm run lint                    # ESLint
npm run test                    # Jest + React Testing Library
```

### Designer Database (SQLite local, Turso remote)

- Local development (SQLite file):

  - Uses `better-sqlite3` with `apps/designer/designer.db` when `TURSO_DATABASE_URL` is not set.
  - Run migrations locally:
    - `pnpm --filter designer db:migrate`
  - Start app:
    - `pnpm --filter designer dev`

- Remote (Turso/libSQL, e.g. Vercel):

  - Set env vars in your shell (or CI) when running migrations:
    - `TURSO_DATABASE_URL='libsql://<your-db>.turso.io'`
    - `TURSO_AUTH_TOKEN='<token>'` (if your DB requires it)
  - Run migrations against Turso:
    - `TURSO_DATABASE_URL='…' TURSO_AUTH_TOKEN='…' pnpm --filter designer db:migrate`
  - On Vercel, add the same env vars in Project Settings → Environment Variables. At runtime the app auto‑detects Turso and uses `@libsql/client` with Drizzle.
  - Migrations are not run at runtime in serverless. Run the command above locally (before deploy) or in your CI of choice.

- Notes:
  - The repository methods are async and work with both drivers.
  - Keep API routes on the Node.js runtime (do not set `export const runtime = 'edge'`).
  - The first migration seeds two example projects; you’ll see them after running migrations.

### BMS IoT App Commands

```bash
# Root-level commands (run from repository root):
pnpm bms-iot:help                        # Show all available commands
pnpm bms-iot:run                         # Start main application
pnpm bms-iot:test                        # Run comprehensive test suite (800+ tests)
pnpm bms-iot:test:verbose                # Verbose test output
pnpm bms-iot:mqtt --help                 # MQTT commands
pnpm bms-iot:config --help               # Configuration management

# Or run directly from app directory:
cd apps/bms-iot-app
PYTHONPATH=../.. python -m src.cli --help           # Show all available commands
PYTHONPATH=../.. python -m src.cli run-main         # Start main application
PYTHONPATH=../.. python -m src.cli set-credentials  # Set authentication
```

### BMS Schemas Commands

```bash
cd packages/bms-schemas

# Testing
npm test                        # Run all schema tests
npm run test:watch             # Watch mode testing
npm run test:coverage          # Coverage report
npm run test:integration       # E2E schema integration test

# Schema Generation
npm run generate               # Complete pipeline
npm run generate:json          # Generate JSON Schema only
npm run generate:python        # Generate Pydantic only
npm run build:ts              # Compile TypeScript only

# Maintenance
npm run clean                  # Clean all generated files
```

## 🧪 Testing

### Unit Tests

```bash
# All tests
pnpm run test

# Per app
pnpm --filter designer test           # React component + schema tests
pnpm bms-iot:test                     # Python IoT supervisor tests
```

### Integration Tests

```bash
# Run integration tests for Designer
pnpm --filter designer test

# Run integration tests for BMS IoT App
pnpm bms-iot:test
```

## 📊 Manual Verification Steps

### 1. Schema Validation

```bash
# Test schema validation
pnpm --filter designer test    # Should pass all schema tests
```

### 2. Designer App Verification

```bash
# Start Designer app
pnpm --filter designer dev    # http://localhost:3000

# Verify app functionality
# - Visit http://localhost:3000/projects
# - Test creating and editing workflows
# - Verify schema validation works correctly
```

### 3. BMS IoT App Verification

```bash
# Test BMS IoT App CLI
pnpm bms-iot:help

# Run comprehensive tests
pnpm bms-iot:test:verbose

# Test main functionality (requires MQTT configuration)
pnpm bms-iot:run
```

### 4. End-to-End Integration

```bash
# Start both apps
# Terminal 1: pnpm --filter designer dev (port 3000)
# Terminal 2: pnpm bms-iot:run

# Test full integration
# - Create workflows in Designer
# - Verify they can be deployed to BMS IoT App
```

## 🏗️ Project Structure

```
bms-supervisor-controller/
├── package.json               # Root workspace config
├── pnpm-workspace.yaml       # PNPM workspace definition
├── .npmrc                    # PNPM configuration
├── apps/
│   ├── designer/             # Next.js visual programming interface
│   │   └── src/lib/schemas/  # Zod schemas for validation
│   ├── bms-iot-app/          # BACnet/MQTT IoT runtime
│   └── bacnet-simulator/     # BACnet device simulator (git submodule)
└── packages/
    └── mqtt_topics/          # Shared MQTT topic management
```

## 🔧 Development Workflow

### Typical Development Session

1. **Start development**: `pnpm run dev`
2. **Make schema changes**: Edit files in `apps/designer/src/lib/schemas/`
3. **Test schemas**: `pnpm --filter designer test`
4. **Verify integration**: Designer app should reflect changes automatically

### Adding New Features

1. **Designer changes**: Edit React components in `apps/designer/src/`
2. **BMS IoT App changes**: Edit Python modules in `apps/bms-iot-app/src/`
3. **Schema changes**: Add/modify schemas in `apps/designer/src/lib/schemas/`
4. **Always run tests**: `pnpm run test` before committing

## 🚨 Troubleshooting

### Common Issues

**Schema validation fails**:

```bash
pnpm --filter designer test
```

**Import errors in Designer**:

```bash
# Rebuild Designer
pnpm --filter designer dev
```

**Test failures**:

```bash
# Check individual test suites
pnpm --filter designer test
pnpm bms-iot:test
```

**TypeScript errors**:

```bash
# Clean and rebuild everything
pnpm run clean
pnpm install
pnpm run build
```

## 🔧 Git Hooks Setup

### Pre-commit Hooks

```bash
# One-time setup (after initial installation)
pnpm run setup:hooks          # Install pre-commit and git hooks

# Update hooks periodically
pnpm run hooks:update         # Update hook versions
```

**What the hooks do:**

- **Python**: Black (format), Ruff (lint), type checking
- **TypeScript**: Prettier (format), ESLint (lint)
- **Common**: Remove trailing whitespace, fix line endings, validate YAML/JSON
- **Schema**: Verify schema tests pass when schemas are modified

**Manual testing:**

```bash
pnpm run hooks:run            # Run hooks on all files
```

## 📚 Technologies Used

- **Frontend**: Next.js 15.5, TypeScript, Tailwind CSS v4, React Flow, Zustand, Zod
- **Backend**: FastAPI, Typer, uvicorn, BACnet (BAC0, bacpypes)
- **Testing**: Jest, React Testing Library, pytest
- **Build**: PNPM workspaces, TypeScript
- **Code Quality**: Prettier, ESLint, Black, Ruff, pre-commit hooks

## 📄 License

This project is licensed under the AGPL-3.0 License. See the root `LICENSE` file and [docs/LICENSE.md](docs/LICENSE.md) for third-party notices and details.

## 📚 Documentation

- **[Project Status](docs/PROJECT_STATUS.md)** - Current development phase and progress
- **[Contributing Guide](docs/CONTRIBUTING.md)** - How to contribute to the project
- **[License](docs/LICENSE.md)** - AGPL-3.0 License and third-party notices
- **[Coding Standards](docs/coding-standards.md)** - Development standards and practices
