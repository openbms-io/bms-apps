#!/usr/bin/env python3
"""
Debug script to validate all 223P system templates.

This script:
1. Loads each system template from SystemTemplate enum
2. Inlines dependencies
3. Fills the template
4. Validates against 223P SHACL shapes
5. Reports which templates pass/fail

Run from project root:
    cd /Users/amol/Documents/ai-projects/bms-supervisor-controller
    PYTHONPATH=apps/building-semantics-api-app apps/building-semantics-api-app/.venv/bin/python apps/building-semantics-api-app/debug_template_fill.py
"""

import sys
import logging
from pathlib import Path

# Add app directory to Python path
app_dir = Path(__file__).parent
sys.path.insert(0, str(app_dir))

# Suppress debug logs for performance
logging.basicConfig(level=logging.WARNING)

from rdflib import Namespace
from buildingmotif.dataclasses import Model
from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.adapters.template_types import SystemTemplate
from src.services.validation_service import ValidationService

BMS = Namespace("urn:bms:")


def validate_single_template(adapter, template_id):
    """Validate a single system template."""
    try:
        # Load and inline template
        raw_template = adapter.get_template_by_name(template_id)
        inlined_template = raw_template.inline_dependencies()

        # Fill template
        bindings, filled_graph = inlined_template.fill(BMS)

        # Validate
        test_model = Model.create(Namespace(f"urn:test:{template_id.value}"))
        test_model.graph += filled_graph
        validation_result = ValidationService.validate_model(test_model)

        return {
            "template": template_id.value,
            "valid": validation_result.isValid,
            "errors": validation_result.errors,
            "triple_count": len(filled_graph),
            "exception": None
        }
    except Exception as e:
        return {
            "template": template_id.value,
            "valid": False,
            "errors": [],
            "triple_count": 0,
            "exception": str(e)
        }


def test_single_template_cli(template_name):
    """Test a single template specified by name."""

    print("=" * 80)
    print(f"VALIDATING TEMPLATE: {template_name}")
    print("=" * 80)

    # Initialize adapter
    print("\nInitializing BuildingMOTIF adapter...")
    adapter = BuildingMOTIFAdapter.get_instance()
    print("✓ Adapter initialized\n")

    # Find template
    try:
        template = SystemTemplate(template_name)
    except ValueError:
        print(f"❌ ERROR: Template '{template_name}' not found")
        print(f"\nAvailable templates:")
        for t in SystemTemplate:
            print(f"  - {t.value}")
        return {"valid": False, "exception": f"Template not found: {template_name}"}

    # Test template
    print(f"Testing: {template.value}")
    print("-" * 80)

    result = validate_single_template(adapter, template)

    if result["exception"]:
        print(f"💥 EXCEPTION: {result['exception']}")
    elif result["valid"]:
        print(f"✅ PASSED ({result['triple_count']} triples, 0 errors)")
    else:
        print(f"❌ FAILED ({result['triple_count']} triples, {len(result['errors'])} errors)")
        print("\nAll errors:")
        for j, error in enumerate(result["errors"], 1):
            print(f"  {j}. {error}")

    print("\n" + "=" * 80)

    return result


if __name__ == "__main__":
    # Get template name from command line or use default
    if len(sys.argv) > 1:
        template_name = sys.argv[1]

        # Check for interactive mode
        if template_name == "--interactive" or template_name == "-i":
            print("=== INTERACTIVE MODE ===")
            print("BuildingMOTIF loading once, then testing templates interactively")
            print("\nInitializing BuildingMOTIF adapter...")
            adapter = BuildingMOTIFAdapter.get_instance()
            print("✓ Adapter initialized\n")

            while True:
                print("\nAvailable templates:")
                for t in SystemTemplate:
                    print(f"  - {t.value}")
                print("\nEnter template name (or 'q' to quit):")
                template_input = input("> ").strip()

                if template_input.lower() in ['q', 'quit', 'exit']:
                    print("Exiting...")
                    break

                try:
                    template = SystemTemplate(template_input)
                    result = validate_single_template(adapter, template)

                    print("\n" + "="*80)
                    print(f"TEMPLATE: {template.value}")
                    print("="*80)

                    if result["exception"]:
                        print(f"💥 EXCEPTION: {result['exception']}")
                    elif result["valid"]:
                        print(f"✅ PASSED ({result['triple_count']} triples, 0 errors)")
                    else:
                        print(f"❌ FAILED ({result['triple_count']} triples, {len(result['errors'])} errors)")
                        print("\nAll errors:")
                        for j, error in enumerate(result["errors"], 1):
                            print(f"  {j}. {error}")
                    print("="*80)

                except ValueError:
                    print(f"❌ ERROR: Template '{template_input}' not found")

            sys.exit(0)

        # Single template mode
        result = test_single_template_cli(template_name)
        if result.get("exception") or not result.get("valid"):
            sys.exit(1)
        else:
            sys.exit(0)
    else:
        print("Usage: python debug_template_fill.py <template-name>")
        print("       python debug_template_fill.py --interactive")
        print("\nAvailable templates:")
        for t in SystemTemplate:
            print(f"  - {t.value}")
        print("\nTesting all templates:")
        for t in SystemTemplate:
            print(f"\n{'='*80}")
            result = test_single_template_cli(t.value)
            if not result["valid"]:
                print(f"\n❌ STOPPING - Fix {t.value} before continuing")
                sys.exit(1)
        print(f"\n{'='*80}")
        print("✅ ALL TEMPLATES PASSED!")
        sys.exit(0)
