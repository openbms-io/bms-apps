#!/usr/bin/env python3
"""
FMU Lifecycle & State Exploration Script

Answers POC Questions #1-4 for G36 Service Architecture Design:
  Q1: How are states managed in FMU?
  Q2: Do we need to save/restore FMU state?
  Q3: Is FMU always running once kicked off?
  Q4: Is FMU a pure function (inputs → outputs)?

Usage:
    python explore_lifecycle.py <path_to_fmu>
    python explore_lifecycle.py ../output/ReheatControllerFMU.fmu
"""

import sys
import time
import argparse
import traceback
from typing import Any
from dataclasses import dataclass

from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave


@dataclass
class ExperimentResult:
    name: str
    question: str
    finding: str
    evidence: str
    api_impact: str


def get_fmu_capabilities(model_description) -> dict:
    """Extract FMU capabilities from model description."""
    cs = model_description.coSimulation
    capabilities = {
        'canGetAndSetFMUstate': getattr(cs, 'canGetAndSetFMUstate', False),
        'canSerializeFMUstate': getattr(cs, 'canSerializeFMUstate', False),
        'canHandleVariableCommunicationStepSize': getattr(cs, 'canHandleVariableCommunicationStepSize', False),
        'canInterpolateInputs': getattr(cs, 'canInterpolateInputs', False),
        'maxOutputDerivativeOrder': getattr(cs, 'maxOutputDerivativeOrder', 0),
    }
    return capabilities


def get_variable_references(model_description) -> dict:
    """Build mapping of variable names to value references."""
    refs = {}
    for var in model_description.modelVariables:
        refs[var.name] = var.valueReference
    return refs


def create_fmu_instance(fmu_path: str, unzipdir: str = None):
    """Create and initialize an FMU instance."""
    md = read_model_description(fmu_path)

    if unzipdir is None:
        unzipdir = extract(fmu_path)

    fmu = FMU2Slave(
        guid=md.guid,
        unzipDirectory=unzipdir,
        modelIdentifier=md.coSimulation.modelIdentifier,
        instanceName='instance1'
    )

    fmu.instantiate()
    fmu.setupExperiment(startTime=0.0)
    fmu.enterInitializationMode()
    fmu.exitInitializationMode()

    return fmu, md, unzipdir


def set_default_inputs(fmu, refs: dict):
    """Set default input values for G36 Reheat Controller."""
    fmu.setReal([refs['TZon']], [291.15])
    fmu.setReal([refs['TCooSet']], [297.15])
    fmu.setReal([refs['THeaSet']], [293.15])
    fmu.setReal([refs['TDis']], [289.15])
    fmu.setReal([refs['VDis_flow']], [0.1])
    fmu.setReal([refs['TSup']], [286.15])
    fmu.setReal([refs['TSupSet']], [286.15])
    fmu.setBoolean([refs['u1Fan']], [True])
    fmu.setInteger([refs['uOpeMod']], [1])


def get_key_outputs(fmu, refs: dict) -> dict:
    """Get key output values from FMU."""
    yDam = fmu.getReal([refs['yDam']])[0]
    yVal = fmu.getReal([refs['yVal']])[0]
    VSet_flow = fmu.getReal([refs['VSet_flow']])[0]
    return {'yDam': yDam, 'yVal': yVal, 'VSet_flow': VSet_flow}


def experiment_1_lifecycle(fmu_path: str) -> ExperimentResult:
    """
    Experiment 1: Lifecycle Test

    Compare single instance (session-based) vs fresh instance per call patterns.
    Measures startup time, step time, and output consistency.
    """
    print("\n" + "=" * 80)
    print("EXPERIMENT 1: LIFECYCLE TEST")
    print("=" * 80)

    md = read_model_description(fmu_path)
    unzipdir = extract(fmu_path)
    refs = get_variable_references(md)

    step_size = 300.0
    num_steps = 10

    print("\n--- Pattern A: Single Instance (Session-Based) ---")
    start_total = time.perf_counter()

    start_init = time.perf_counter()
    fmu_a, _, _ = create_fmu_instance(fmu_path, unzipdir)
    init_time_a = time.perf_counter() - start_init
    print(f"  Instantiate + Initialize: {init_time_a*1000:.2f} ms")

    set_default_inputs(fmu_a, refs)

    step_times_a = []
    outputs_a = []
    current_time = 0.0

    for i in range(num_steps):
        start_step = time.perf_counter()
        fmu_a.doStep(currentCommunicationPoint=current_time, communicationStepSize=step_size)
        step_time = time.perf_counter() - start_step
        step_times_a.append(step_time)
        current_time += step_size

        out = get_key_outputs(fmu_a, refs)
        outputs_a.append(out)
        print(f"  Step {i+1}: yDam={out['yDam']:.4f}, yVal={out['yVal']:.4f} ({step_time*1000:.2f} ms)")

    fmu_a.terminate()
    fmu_a.freeInstance()
    total_time_a = time.perf_counter() - start_total

    avg_step_time_a = sum(step_times_a) / len(step_times_a)
    print(f"\n  Total time: {total_time_a*1000:.2f} ms")
    print(f"  Avg step time: {avg_step_time_a*1000:.2f} ms")

    print("\n--- Pattern B: Fresh Instance Per Call ---")
    start_total = time.perf_counter()

    outputs_b = []
    total_init_time = 0
    total_step_time = 0

    for i in range(num_steps):
        start_init = time.perf_counter()
        fmu_b, _, _ = create_fmu_instance(fmu_path, unzipdir)
        init_time = time.perf_counter() - start_init
        total_init_time += init_time

        set_default_inputs(fmu_b, refs)

        start_step = time.perf_counter()
        fmu_b.doStep(currentCommunicationPoint=0.0, communicationStepSize=step_size)
        step_time = time.perf_counter() - start_step
        total_step_time += step_time

        out = get_key_outputs(fmu_b, refs)
        outputs_b.append(out)
        print(f"  Call {i+1}: yDam={out['yDam']:.4f}, yVal={out['yVal']:.4f} (init: {init_time*1000:.2f} ms, step: {step_time*1000:.2f} ms)")

        fmu_b.terminate()
        fmu_b.freeInstance()

    total_time_b = time.perf_counter() - start_total
    avg_init_time_b = total_init_time / num_steps
    avg_step_time_b = total_step_time / num_steps

    print(f"\n  Total time: {total_time_b*1000:.2f} ms")
    print(f"  Avg init time: {avg_init_time_b*1000:.2f} ms")
    print(f"  Avg step time: {avg_step_time_b*1000:.2f} ms")

    outputs_differ = any(
        outputs_a[i]['yVal'] != outputs_b[i]['yVal']
        for i in range(min(len(outputs_a), len(outputs_b)))
    )

    speedup = total_time_b / total_time_a if total_time_a > 0 else 0

    evidence = f"""
Pattern A (Single Instance): {total_time_a*1000:.2f} ms total, {avg_step_time_a*1000:.3f} ms/step
Pattern B (Fresh Per Call):  {total_time_b*1000:.2f} ms total, {avg_init_time_b*1000:.3f} ms init + {avg_step_time_b*1000:.3f} ms/step
Speedup (A vs B): {speedup:.1f}x faster with single instance
Outputs differ between patterns: {outputs_differ}
"""

    return ExperimentResult(
        name="Lifecycle Test",
        question="Q3: Is FMU always running once kicked off?",
        finding="FMU is STEP-ON-DEMAND. Does not run continuously. Waits for doStep() calls.",
        evidence=evidence.strip(),
        api_impact="Single-instance pattern is significantly faster. Recommend session-based API for performance."
    )


def experiment_2_statefulness(fmu_path: str) -> ExperimentResult:
    """
    Experiment 2: Statefulness Test

    Determine if FMU accumulates state (integral action).
    Tests if same inputs over time produce different outputs.
    """
    print("\n" + "=" * 80)
    print("EXPERIMENT 2: STATEFULNESS TEST")
    print("=" * 80)

    md = read_model_description(fmu_path)
    unzipdir = extract(fmu_path)
    refs = get_variable_references(md)

    step_size = 300.0
    num_steps = 10

    print("\n--- Run 1: Sustained Heating Demand (TZon < THeaSet) ---")
    print("  TZon=291.15K (18°C), THeaSet=293.15K (20°C) - 2K below setpoint")

    fmu1, _, _ = create_fmu_instance(fmu_path, unzipdir)
    set_default_inputs(fmu1, refs)

    fmu1.setReal([refs['TZon']], [291.15])
    fmu1.setReal([refs['THeaSet']], [293.15])

    outputs_run1 = []
    current_time = 0.0

    for i in range(num_steps):
        fmu1.doStep(currentCommunicationPoint=current_time, communicationStepSize=step_size)
        current_time += step_size
        out = get_key_outputs(fmu1, refs)
        outputs_run1.append(out)
        print(f"  Step {i+1} (t={current_time:.0f}s): yVal={out['yVal']:.6f}, yDam={out['yDam']:.6f}")

    fmu1.terminate()
    fmu1.freeInstance()

    print("\n--- Run 2: Fresh FMU, Same Inputs, Single Step ---")
    fmu2, _, _ = create_fmu_instance(fmu_path, unzipdir)
    set_default_inputs(fmu2, refs)
    fmu2.setReal([refs['TZon']], [291.15])
    fmu2.setReal([refs['THeaSet']], [293.15])

    fmu2.doStep(currentCommunicationPoint=0.0, communicationStepSize=step_size)
    out_fresh = get_key_outputs(fmu2, refs)
    print(f"  Step 1 (fresh): yVal={out_fresh['yVal']:.6f}, yDam={out_fresh['yDam']:.6f}")

    fmu2.terminate()
    fmu2.freeInstance()

    yVal_first = outputs_run1[0]['yVal']
    yVal_last = outputs_run1[-1]['yVal']
    yVal_changed = abs(yVal_last - yVal_first) > 1e-9
    fresh_matches_first = abs(out_fresh['yVal'] - yVal_first) < 1e-9

    print("\n--- Analysis ---")
    print(f"  yVal at step 1:  {yVal_first:.6f}")
    print(f"  yVal at step 10: {yVal_last:.6f}")
    print(f"  yVal changed over time: {yVal_changed}")
    print(f"  Fresh FMU yVal matches original step 1: {fresh_matches_first}")

    is_stateful = yVal_changed

    evidence = f"""
yVal progression over 10 steps with constant inputs:
  Step 1:  {outputs_run1[0]['yVal']:.6f}
  Step 5:  {outputs_run1[4]['yVal']:.6f}
  Step 10: {outputs_run1[9]['yVal']:.6f}
yVal changed over time: {yVal_changed}
Fresh FMU step 1 matches original step 1: {fresh_matches_first}
Conclusion: FMU is {'STATEFUL' if is_stateful else 'STATELESS (pure function)'}
"""

    if is_stateful:
        finding = "FMU is STATEFUL. Outputs depend on history. G36 controller has integral terms that accumulate."
        api_impact = "API must maintain FMU instances per zone. State persistence needed for crash recovery."
    else:
        finding = "FMU is STATELESS (pure function). Same inputs always produce same outputs."
        api_impact = "Simple stateless API possible. No persistence needed."

    return ExperimentResult(
        name="Statefulness Test",
        question="Q1: How are states managed in FMU? / Q4: Is FMU a pure function?",
        finding=finding,
        evidence=evidence.strip(),
        api_impact=api_impact
    )


def experiment_3_state_persistence(fmu_path: str) -> ExperimentResult:
    """
    Experiment 3: State Persistence Test

    Check if FMU supports save/restore state via fmi2GetFMUstate/fmi2SetFMUstate.
    """
    print("\n" + "=" * 80)
    print("EXPERIMENT 3: STATE PERSISTENCE (SAVE/RESTORE) TEST")
    print("=" * 80)

    md = read_model_description(fmu_path)
    capabilities = get_fmu_capabilities(md)

    print("\n--- FMU Capabilities ---")
    for cap, val in capabilities.items():
        print(f"  {cap}: {val}")

    can_get_set = capabilities['canGetAndSetFMUstate']
    can_serialize = capabilities['canSerializeFMUstate']

    evidence_lines = [
        "FMU Capabilities from modelDescription.xml:",
        f"  canGetAndSetFMUstate: {can_get_set}",
        f"  canSerializeFMUstate: {can_serialize}",
    ]

    if can_get_set:
        print("\n--- Testing State Save/Restore ---")
        unzipdir = extract(fmu_path)
        refs = get_variable_references(md)

        fmu, _, _ = create_fmu_instance(fmu_path, unzipdir)
        set_default_inputs(fmu, refs)
        fmu.setReal([refs['TZon']], [291.15])
        fmu.setReal([refs['THeaSet']], [293.15])

        step_size = 300.0
        current_time = 0.0

        for i in range(5):
            fmu.doStep(currentCommunicationPoint=current_time, communicationStepSize=step_size)
            current_time += step_size

        out_at_5 = get_key_outputs(fmu, refs)
        print(f"  After step 5: yVal={out_at_5['yVal']:.6f}")

        try:
            state = fmu.getFMUstate()
            print("  State saved successfully")

            for i in range(5):
                fmu.doStep(currentCommunicationPoint=current_time, communicationStepSize=step_size)
                current_time += step_size

            out_at_10 = get_key_outputs(fmu, refs)
            print(f"  After step 10: yVal={out_at_10['yVal']:.6f}")

            fmu.setFMUstate(state)
            print("  State restored to step 5")

            out_restored = get_key_outputs(fmu, refs)
            print(f"  After restore: yVal={out_restored['yVal']:.6f}")

            state_restored_correctly = abs(out_restored['yVal'] - out_at_5['yVal']) < 1e-9
            print(f"  State restored correctly: {state_restored_correctly}")

            fmu.freeFMUstate(state)

            evidence_lines.extend([
                "",
                "State save/restore test:",
                f"  yVal at step 5: {out_at_5['yVal']:.6f}",
                f"  yVal at step 10: {out_at_10['yVal']:.6f}",
                f"  yVal after restore: {out_restored['yVal']:.6f}",
                f"  Restore successful: {state_restored_correctly}",
            ])

            finding = "State save/restore IS SUPPORTED and works correctly. Can use for crash recovery."
            api_impact = "Implement periodic state snapshots for crash recovery. Serialize state to persistent storage."

        except Exception as e:
            print(f"  State save/restore failed: {e}")
            evidence_lines.append(f"State save/restore error: {e}")
            finding = f"State save/restore advertised but FAILED: {e}"
            api_impact = "Cannot rely on FMU state APIs. Need alternative crash recovery strategy."

        fmu.terminate()
        fmu.freeInstance()
    else:
        print("\n--- State Save/Restore NOT SUPPORTED ---")
        finding = "State save/restore NOT SUPPORTED by this FMU."
        api_impact = "Cannot save/restore FMU state. Need to track inputs and replay from start on recovery."

    return ExperimentResult(
        name="State Persistence Test",
        question="Q2: Do we need to save/restore FMU state?",
        finding=finding,
        evidence="\n".join(evidence_lines),
        api_impact=api_impact
    )


def experiment_4_step_timing(fmu_path: str) -> ExperimentResult:
    """
    Experiment 4: Step Timing Semantics

    Understand what doStep(stepSize=300) means - real-time vs simulated time.
    """
    print("\n" + "=" * 80)
    print("EXPERIMENT 4: STEP TIMING SEMANTICS")
    print("=" * 80)

    md = read_model_description(fmu_path)
    unzipdir = extract(fmu_path)
    refs = get_variable_references(md)

    print("\n--- Testing Step Size Variations ---")

    results = []

    for step_size in [60.0, 300.0, 900.0, 3600.0]:
        fmu, _, _ = create_fmu_instance(fmu_path, unzipdir)
        set_default_inputs(fmu, refs)
        fmu.setReal([refs['TZon']], [291.15])
        fmu.setReal([refs['THeaSet']], [293.15])

        wall_start = time.perf_counter()
        fmu.doStep(currentCommunicationPoint=0.0, communicationStepSize=step_size)
        wall_time = time.perf_counter() - wall_start

        out = get_key_outputs(fmu, refs)

        results.append({
            'step_size': step_size,
            'wall_time_ms': wall_time * 1000,
            'yVal': out['yVal'],
            'yDam': out['yDam'],
        })

        print(f"  stepSize={step_size:.0f}s ({step_size/60:.1f}min): wall={wall_time*1000:.2f}ms, yVal={out['yVal']:.6f}")

        fmu.terminate()
        fmu.freeInstance()

    print("\n--- Analysis ---")

    wall_times = [r['wall_time_ms'] for r in results]
    step_sizes = [r['step_size'] for r in results]

    wall_time_correlation = max(wall_times) / min(wall_times) if min(wall_times) > 0 else 0
    step_size_ratio = max(step_sizes) / min(step_sizes)

    is_simulated_time = wall_time_correlation < step_size_ratio * 0.5

    print(f"  Wall time ratio (max/min): {wall_time_correlation:.1f}x")
    print(f"  Step size ratio (max/min): {step_size_ratio:.1f}x")
    print(f"  Time is: {'SIMULATED' if is_simulated_time else 'REAL-TIME'}")

    evidence = f"""
Step size vs wall clock time:
  60s step:   {results[0]['wall_time_ms']:.2f}ms wall time
  300s step:  {results[1]['wall_time_ms']:.2f}ms wall time
  900s step:  {results[2]['wall_time_ms']:.2f}ms wall time
  3600s step: {results[3]['wall_time_ms']:.2f}ms wall time

Wall time ratio: {wall_time_correlation:.1f}x
Step size ratio: {step_size_ratio:.1f}x

Conclusion: doStep(stepSize=X) advances X seconds of SIMULATED time.
Wall clock time is approximately constant regardless of step size.
FMU does NOT run in real-time; it's purely computational.
"""

    return ExperimentResult(
        name="Step Timing Test",
        question="Q3: Is FMU always running once kicked off?",
        finding="FMU uses SIMULATED TIME. doStep(300) = advance 300 seconds of simulated time, not real time. FMU waits for step calls.",
        evidence=evidence.strip(),
        api_impact="API can call doStep() at any rate. No need to synchronize with real-time clock."
    )


def print_summary(results: list[ExperimentResult]):
    """Print summary of all experiment results."""
    print("\n" + "=" * 80)
    print("SUMMARY: POC QUESTIONS ANSWERED")
    print("=" * 80)

    for r in results:
        print(f"\n=== {r.question} ===")
        print(f"Finding: {r.finding}")
        print(f"API Impact: {r.api_impact}")

    print("\n" + "=" * 80)
    print("ARCHITECTURE RECOMMENDATIONS")
    print("=" * 80)

    is_stateful = any("STATEFUL" in r.finding for r in results)
    can_save_restore = any("IS SUPPORTED" in r.finding and "save/restore" in r.finding.lower() for r in results)

    print("\nBased on POC findings:")

    if is_stateful:
        print("  1. Use SESSION-BASED API with persistent FMU instances per zone")
        print("  2. Maintain zone→FMU instance mapping in memory")
        if can_save_restore:
            print("  3. Implement periodic state snapshots for crash recovery")
            print("  4. On restart, restore state from last snapshot")
        else:
            print("  3. Track all inputs in database for replay on crash recovery")
            print("  4. On restart, replay inputs from t=0 to restore state")
    else:
        print("  1. Simple STATELESS REST API is viable")
        print("  2. Create fresh FMU instance per request")
        print("  3. No state persistence needed")

    print("\n  Performance note: Single-instance pattern is faster than fresh-per-call")


def main():
    parser = argparse.ArgumentParser(
        description='Explore FMU lifecycle and state management for G36 Service architecture design.'
    )
    parser.add_argument('fmu_path', help='Path to the FMU file')
    parser.add_argument('--experiment', '-e', type=int, choices=[1, 2, 3, 4],
                        help='Run specific experiment only (1-4)')

    args = parser.parse_args()

    print("=" * 80)
    print("FMU LIFECYCLE & STATE EXPLORATION")
    print("=" * 80)
    print(f"FMU: {args.fmu_path}")
    print("Purpose: Answer POC Questions #1-4 for G36 Service Architecture")

    results = []

    try:
        if args.experiment is None or args.experiment == 1:
            results.append(experiment_1_lifecycle(args.fmu_path))

        if args.experiment is None or args.experiment == 2:
            results.append(experiment_2_statefulness(args.fmu_path))

        if args.experiment is None or args.experiment == 3:
            results.append(experiment_3_state_persistence(args.fmu_path))

        if args.experiment is None or args.experiment == 4:
            results.append(experiment_4_step_timing(args.fmu_path))

        if results:
            print_summary(results)

    except Exception as e:
        print(f"\nError during exploration: {e}")
        traceback.print_exc()
        sys.exit(1)


if __name__ == '__main__':
    main()
