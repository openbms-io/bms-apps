# G36 API App

ASHRAE Guideline 36 control sequence execution engine using Functional Mock-up Units (FMUs).

## Overview

This app provides a service for executing G36 control sequences (VAV Reheat Terminal Unit Controller) via FMU co-simulation. It integrates with the BMS Supervisor Controller to provide standards-compliant HVAC control logic.

## Prerequisites

- Python 3.11+
- FMPy library
- G36 Reheat FMU file (see [Obtaining the FMU](#obtaining-the-fmu))

## Installation

```bash
cd apps/g36-api-app
pip install -r requirements.txt
```

## Building the FMU

The G36 Reheat FMU requires a two-step build process:

### Step 1: Export from OpenModelica (Linux binaries only)

1. Install [OpenModelica](https://openmodelica.org/)
2. Create a wrapper model with default parameters (see `fmu-sequence/modelica/ReheatControllerFMU.mo`)
3. In OpenModelica:
   - Import the wrapper model
   - Import the [LBL modelica-buildings library](https://github.com/lbl-srg/modelica-buildings)
   - Right-click on the wrapper model and export as FMU 2.0 Co-Simulation

This creates a `.fmutmp` directory with sources and Linux binaries.

### Step 2: Build for Host Platform

OpenModelica exports Linux-only binaries. Use the build script to compile for your platform:

```bash
cd apps/g36-api-app
./fmu-sequence/scripts/build-fmu.sh fmu-sequence/reheat/ReheatControllerFMU<hash>/<id>.fmutmp ./builds
```

The script:

- Compiles the FMU sources for macOS, Linux, or Windows
- Patches CMakeLists.txt for macOS compatibility
- Creates the final `.fmu` file in the output directory

The FMU file is gitignored due to its size (~10MB).

## Running POC Scripts

### FMU Lifecycle Exploration (Q1-Q4)

Explores state management, pure function behavior, and lifecycle:

```bash
python fmu-sequence/scripts/explore_lifecycle.py fmu-sequence/builds/ReheatControllerFMU.fmu
```

### FMU Execution Validation (Q7-Q13)

Validates outputs, performance, and error handling:

```bash
python fmu-sequence/scripts/validate_fmu_execution.py fmu-sequence/builds/ReheatControllerFMU.fmu
```

Run a specific experiment:

```bash
python fmu-sequence/scripts/validate_fmu_execution.py fmu-sequence/builds/ReheatControllerFMU.fmu -e 1
```

## Project Structure

```
apps/g36-api-app/
├── README.md                    # This file
├── requirements.txt             # Python dependencies
├── fmu-sequence/
│   ├── builds/                  # Compiled FMU files (gitignored)
│   │   └── ReheatControllerFMU.fmu
│   ├── modelica/                # Modelica wrapper models
│   │   └── ReheatControllerFMU.mo
│   ├── reheat/                  # OpenModelica export output (.fmutmp)
│   └── scripts/
│       ├── build-fmu.sh         # Cross-platform FMU build script
│       ├── explore_lifecycle.py # Q1-Q4 experiments
│       └── validate_fmu_execution.py # Q7-Q13 experiments
└── docs/
    ├── fmu-audit/               # FMU behavior documentation
    │   └── reheat-terminal/
    │       └── reheat-terminal-behavior.md
    └── decisions/               # Architecture Decision Records
        └── 001-fmu-library-architecture.md
```

## Documentation

- [POC Findings Spec](../../docs/feature-development/g36-implementation/specs/poc-findings.md) - All 13 POC questions answered
- [FMU Audit: Reheat Terminal](docs/fmu-audit/reheat-terminal/reheat-terminal-behavior.md) - Detailed FMU behavior analysis
- [ADR-001: FMU Library & Architecture](docs/decisions/001-fmu-library-architecture.md) - Architecture decisions

## Key Findings

| Question   | Finding                                    |
| ---------- | ------------------------------------------ |
| Library    | FMPy (simpler than PyFMI)                  |
| State      | Pure function of (inputs, simulation_time) |
| Execution  | Step-on-demand, ~0.1ms per step            |
| Multi-zone | Concurrent instances supported             |
| Memory     | ~1-2 MB per instance                       |
