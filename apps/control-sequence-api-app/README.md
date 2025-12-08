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

The G36 Reheat FMU requires a multi-step build process due to OpenModelica limitations.

### Step 1: Create Modelica Wrapper Model

Create a wrapper model that explicitly declares all parameters. This is required because OpenModelica exports inherited parameters as non-configurable `calculatedParameter` by default.

See `fmu-sequence/modelica/ReheatControllerFMU.mo` for the pattern:

```modelica
model ReheatControllerFMU
  // Declare parameters with _in suffix
  parameter Boolean have_winSen_in = true "True: the zone has window sensor";
  parameter Real kCooCon_in = 0.1 "Gain of controller for cooling control loop";
  // ... all 47 parameters

  // Pass through to base controller
  extends Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller(
    have_winSen = have_winSen_in,
    kCooCon = kCooCon_in,
    // ... all parameters mapped
  );
end ReheatControllerFMU;
```

### Step 2: Export from OpenModelica (Docker)

```bash
# Allow X11 connections (macOS)
xhost +localhost

# Run OpenModelica GUI in Docker
docker run -it --rm \
  -e DISPLAY=host.docker.internal:0 \
  -v $HOME:$HOME \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  openmodelica/openmodelica:v1.27.5-gui OMEdit
```

In OMEdit:

1. File → Open Model/Library File → Load `fmu-sequence/modelica/ReheatControllerFMU.mo`
2. File → Load Library → Browse to local [modelica-buildings](https://github.com/lbl-srg/modelica-buildings) repo and select `Buildings` folder (e.g., `/Users/amol/Documents/ai-projects/modelica-buildings/Buildings`)
3. Right-click on your G36 sequence model (e.g., `ReheatControllerFMU`) → Export → FMU

Export creates a `.fmutmp` directory (path shown in yellow status bar).

### Step 3: Fix Boolean/Enum Parameter Causality

OpenModelica has a bug where Boolean and Enumeration parameters are exported as `calculatedParameter` instead of `parameter`. Fix manually in `modelDescription.xml`.

**Important**: Only fix parameters that are:

1. NOT marked `final` in the base controller (check the [source code](https://github.com/lbl-srg/modelica-buildings/blob/master/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo))
2. Listed in the [G36 documentation parameters](https://simulationresearch.lbl.gov/modelica/releases/v11.1.0/help/Buildings_Controls_OBC_ASHRAE_G36_TerminalUnits_Reheat.html#Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller)

```xml
<!-- BEFORE -->
<ScalarVariable name="have_winSen_in" ... causality="calculatedParameter">
  <Boolean/>
</ScalarVariable>

<!-- AFTER -->
<ScalarVariable name="have_winSen_in" ... causality="parameter">
  <Boolean start="true"/>
</ScalarVariable>
```

Parameters requiring this fix for Reheat Terminal Unit:

| Parameter              | Type        | start value      |
| ---------------------- | ----------- | ---------------- |
| `have_CO2Sen_in`       | Boolean     | `true`           |
| `have_hotWatCoi_in`    | Boolean     | `true`           |
| `have_occSen_in`       | Boolean     | `true`           |
| `have_winSen_in`       | Boolean     | `true`           |
| `permit_occStandby_in` | Boolean     | `true`           |
| `controllerTypeDam_in` | Enumeration | `2` (PI)         |
| `controllerTypeVal_in` | Enumeration | `2` (PI)         |
| `venStd_in`            | Enumeration | `1` (ASHRAE62_1) |
| `VMin_flow_in`         | Real        | `0.0`            |
| `dTHys_in`             | Real        | `0.25`           |
| `looHys_in`            | Real        | `0.01`           |
| `floHys_in`            | Real        | `0.01*VMin_flow` |
| `damPosHys_in`         | Real        | `0.005`          |
| `valPosHys_in`         | Real        | `0.005`          |

### Step 4: Remove Incompatible Binaries

Delete pre-built binaries (e.g., x86_64 on Apple Silicon):

```bash
rm -rf ./fmu-sequence/reheat/ReheatControllerFMU*/*/binaries/darwin64
```

### Step 5: Build for Host Platform

```bash
cd apps/control-sequence-api-app/fmu-sequence
./scripts/build-fmu.sh ./reheat/ReheatControllerFMUc0d0/417.fmutmp ./builds/
```

The script:

- Compiles the FMU sources for macOS, Linux, or Windows
- Patches CMakeLists.txt for macOS compatibility
- Creates the final `.fmu` file in the output directory

### Step 6: Verify

```bash
python -c "
from fmpy import read_model_description
md = read_model_description('fmu-sequence/builds/ReheatControllerFMU.fmu')
params = [v for v in md.modelVariables if v.causality == 'parameter']
print(f'Configurable parameters: {len(params)}')
"
```

Expected output: `Configurable parameters: 55`

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
