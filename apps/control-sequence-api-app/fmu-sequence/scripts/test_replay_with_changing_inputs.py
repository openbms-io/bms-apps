#!/usr/bin/env python3
"""
Test: Can we replay FMU state with different input histories?

This script answers the critical question:
If inputs change over time, can we replay to a specific simulation_time
with a single large step and get the same outputs?

Scenario A: Step-by-step with CHANGING inputs
  - Steps 1-3: Heating demand (TZon=291.15K)
  - Steps 4-6: Cooling demand (TZon=299.15K)

Scenario B: Fresh FMU, single step to t=1800s with CONSTANT cooling inputs

If outputs match: Replay works (stateless API possible)
If outputs differ: Input history matters (stateful API required)
"""

import sys
from pathlib import Path

from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave


def get_variable_references(model_description) -> dict:
    return {var.name: var.valueReference for var in model_description.modelVariables}


def create_fmu_instance(fmu_path: str, unzipdir: str, instance_name: str = "test"):
    md = read_model_description(fmu_path)
    fmu = FMU2Slave(
        guid=md.guid,
        unzipDirectory=unzipdir,
        modelIdentifier=md.coSimulation.modelIdentifier,
        instanceName=instance_name,
    )
    fmu.instantiate()
    fmu.setupExperiment(startTime=0.0)
    fmu.enterInitializationMode()
    fmu.exitInitializationMode()
    return fmu


def set_inputs(
    fmu,
    refs: dict,
    TZon: float = 295.15,
    TCooSet: float = 297.15,
    THeaSet: float = 293.15,
):
    fmu.setReal([refs["TZon"]], [TZon])
    fmu.setReal([refs["TCooSet"]], [TCooSet])
    fmu.setReal([refs["THeaSet"]], [THeaSet])
    fmu.setReal([refs["TDis"]], [286.15])
    fmu.setReal([refs["VDis_flow"]], [0.1])
    fmu.setReal([refs["TSup"]], [286.15])
    fmu.setReal([refs["TSupSet"]], [285.15])
    fmu.setBoolean([refs["u1Fan"]], [True])
    fmu.setInteger([refs["uOpeMod"]], [1])


def get_outputs(fmu, refs: dict) -> dict:
    return {
        "yDam": fmu.getReal([refs["yDam"]])[0],
        "yVal": fmu.getReal([refs["yVal"]])[0],
    }


def run_scenario_a(fmu_path: str, unzipdir: str, refs: dict) -> dict:
    """Step-by-step with CHANGING inputs."""
    print("=" * 70)
    print("SCENARIO A: Step-by-step with CHANGING inputs")
    print("=" * 70)

    fmu = create_fmu_instance(fmu_path, unzipdir, "scenario_a")
    t = 0.0
    step = 300.0

    print("\nPhase 1: Heating demand (TZon=291.15K, steps 1-3)")
    set_inputs(fmu, refs, TZon=291.15)
    for i in range(3):
        fmu.doStep(currentCommunicationPoint=t, communicationStepSize=step)
        t += step
        out = get_outputs(fmu, refs)
        print(f"  t={t:.0f}s: yDam={out['yDam']:.4f}, yVal={out['yVal']:.4f}")

    print("\nPhase 2: Cooling demand (TZon=299.15K, steps 4-6)")
    set_inputs(fmu, refs, TZon=299.15)
    for i in range(3):
        fmu.doStep(currentCommunicationPoint=t, communicationStepSize=step)
        t += step
        out = get_outputs(fmu, refs)
        print(f"  t={t:.0f}s: yDam={out['yDam']:.4f}, yVal={out['yVal']:.4f}")

    final = get_outputs(fmu, refs)
    fmu.terminate()
    fmu.freeInstance()

    return final


def run_scenario_b(fmu_path: str, unzipdir: str, refs: dict) -> dict:
    """Fresh FMU, single step with CONSTANT cooling inputs."""
    print("\n" + "=" * 70)
    print("SCENARIO B: Fresh FMU, single step to t=1800s with COOLING inputs only")
    print("=" * 70)

    fmu = create_fmu_instance(fmu_path, unzipdir, "scenario_b")
    set_inputs(fmu, refs, TZon=299.15)  # Cooling demand from start
    fmu.doStep(
        currentCommunicationPoint=0.0, communicationStepSize=1800.0
    )  # Single large step

    final = get_outputs(fmu, refs)
    print(f"\n  t=1800s (single step): yDam={final['yDam']:.4f}, yVal={final['yVal']:.4f}")

    fmu.terminate()
    fmu.freeInstance()

    return final


def main():
    if len(sys.argv) < 2:
        fmu_path = Path(__file__).parent.parent / "builds" / "ReheatControllerFMU.fmu"
    else:
        fmu_path = Path(sys.argv[1])

    if not fmu_path.exists():
        print(f"ERROR: FMU not found at {fmu_path}")
        sys.exit(1)

    fmu_path = str(fmu_path.resolve())
    print(f"FMU: {fmu_path}\n")

    md = read_model_description(fmu_path)
    unzipdir = extract(fmu_path)
    refs = get_variable_references(md)

    final_a = run_scenario_a(fmu_path, unzipdir, refs)
    final_b = run_scenario_b(fmu_path, unzipdir, refs)

    print("\n" + "=" * 70)
    print("COMPARISON")
    print("=" * 70)
    print(
        f"\n  Scenario A (step-by-step, changing inputs): yDam={final_a['yDam']:.4f}, yVal={final_a['yVal']:.4f}"
    )
    print(
        f"  Scenario B (single step, constant inputs):   yDam={final_b['yDam']:.4f}, yVal={final_b['yVal']:.4f}"
    )

    yDam_diff = abs(final_a["yDam"] - final_b["yDam"])
    yVal_diff = abs(final_a["yVal"] - final_b["yVal"])

    print(f"\n  Differences: yDam={yDam_diff:.4f}, yVal={yVal_diff:.4f}")

    if yDam_diff < 0.001 and yVal_diff < 0.001:
        print("\n  RESULT: SAME - Replay with single step works!")
        print("  CONCLUSION: Stateless API is possible")
        sys.exit(0)
    else:
        print("\n  RESULT: DIFFERENT - Input history matters!")
        print("  CONCLUSION: Stateful API required (FMU instances must be kept alive)")
        sys.exit(1)


if __name__ == "__main__":
    main()
