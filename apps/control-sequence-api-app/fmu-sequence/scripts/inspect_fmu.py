#!/usr/bin/env python3
"""
FMU Inspector Script

Loads an FMU file and discovers all variables with their types and causalities.

Usage:
    python inspect_fmu.py <path_to_fmu>
    python inspect_fmu.py ../output/ReheatControllerFMU.fmu
"""

import sys
import argparse
from fmpy import read_model_description


def get_type_name(variable):
    """Get the type name of a variable."""
    if variable.type == 'Real':
        return 'Real'
    elif variable.type == 'Integer':
        return 'Integer'
    elif variable.type == 'Boolean':
        return 'Boolean'
    elif variable.type == 'String':
        return 'String'
    elif variable.type == 'Enumeration':
        return 'Enumeration'
    else:
        return variable.type or 'Unknown'


def format_value(value, var_type):
    """Format a value for display."""
    if value is None:
        return 'N/A'
    if var_type == 'Boolean':
        return 'true' if value else 'false'
    return str(value)


def inspect_fmu(fmu_path, show_all=False):
    """Inspect an FMU and print variable information."""

    print(f"\n{'='*80}")
    print(f"FMU INSPECTOR: {fmu_path}")
    print(f"{'='*80}\n")

    # Read model description
    md = read_model_description(fmu_path)

    # Print model info
    print("MODEL INFO")
    print("-" * 40)
    print(f"  Model Name:      {md.modelName}")
    print(f"  Description:     {md.description or 'N/A'}")
    print(f"  FMI Version:     {md.fmiVersion}")
    print(f"  Generation Tool: {md.generationTool or 'N/A'}")
    print(f"  Generation Date: {md.generationDateAndTime or 'N/A'}")
    print()

    # Categorize variables by causality
    inputs = []
    outputs = []
    parameters = []
    locals_vars = []

    for var in md.modelVariables:
        if var.causality == 'input':
            inputs.append(var)
        elif var.causality == 'output':
            outputs.append(var)
        elif var.causality == 'parameter':
            parameters.append(var)
        else:
            locals_vars.append(var)

    # Print summary
    print("VARIABLE SUMMARY")
    print("-" * 40)
    print(f"  Inputs:     {len(inputs)}")
    print(f"  Outputs:    {len(outputs)}")
    print(f"  Parameters: {len(parameters)}")
    print(f"  Local:      {len(locals_vars)}")
    print(f"  Total:      {len(md.modelVariables)}")
    print()

    # Print inputs
    print("INPUT VARIABLES")
    print("-" * 80)
    print(f"  {'Name':<35} {'Type':<12} {'Start':<15} {'Unit':<10} Description")
    print(f"  {'-'*35} {'-'*12} {'-'*15} {'-'*10} {'-'*30}")
    for var in inputs:
        var_type = get_type_name(var)
        start = format_value(var.start, var_type)
        unit = var.unit or ''
        desc = (var.description or '')[:30]
        print(f"  {var.name:<35} {var_type:<12} {start:<15} {unit:<10} {desc}")
    print()

    # Print outputs
    print("OUTPUT VARIABLES")
    print("-" * 80)
    print(f"  {'Name':<35} {'Type':<12} {'Start':<15} {'Unit':<10} Description")
    print(f"  {'-'*35} {'-'*12} {'-'*15} {'-'*10} {'-'*30}")
    for var in outputs:
        var_type = get_type_name(var)
        start = format_value(var.start, var_type)
        unit = var.unit or ''
        desc = (var.description or '')[:30]
        print(f"  {var.name:<35} {var_type:<12} {start:<15} {unit:<10} {desc}")
    print()

    # Print parameters
    print("PARAMETERS (Tunable)")
    print("-" * 80)
    print(f"  {'Name':<35} {'Type':<12} {'Start':<15} {'Unit':<10} Description")
    print(f"  {'-'*35} {'-'*12} {'-'*15} {'-'*10} {'-'*30}")
    for var in parameters:
        var_type = get_type_name(var)
        start = format_value(var.start, var_type)
        unit = var.unit or ''
        desc = (var.description or '')[:30]
        print(f"  {var.name:<35} {var_type:<12} {start:<15} {unit:<10} {desc}")
    print()

    # Print local variables if requested
    if show_all and locals_vars:
        print("LOCAL VARIABLES")
        print("-" * 80)
        print(f"  {'Name':<35} {'Type':<12} {'Start':<15} {'Unit':<10} Description")
        print(f"  {'-'*35} {'-'*12} {'-'*15} {'-'*10} {'-'*30}")
        for var in locals_vars[:50]:  # Limit to first 50
            var_type = get_type_name(var)
            start = format_value(var.start, var_type)
            unit = var.unit or ''
            desc = (var.description or '')[:30]
            print(f"  {var.name:<35} {var_type:<12} {start:<15} {unit:<10} {desc}")
        if len(locals_vars) > 50:
            print(f"  ... and {len(locals_vars) - 50} more local variables")
        print()

    return {
        'inputs': inputs,
        'outputs': outputs,
        'parameters': parameters,
        'locals': locals_vars
    }


def main():
    parser = argparse.ArgumentParser(
        description='Inspect an FMU file and list all variables with types and causalities.'
    )
    parser.add_argument('fmu_path', help='Path to the FMU file')
    parser.add_argument('--all', '-a', action='store_true',
                        help='Show all variables including local/internal')

    args = parser.parse_args()

    try:
        inspect_fmu(args.fmu_path, show_all=args.all)
    except Exception as e:
        print(f"Error inspecting FMU: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    main()
