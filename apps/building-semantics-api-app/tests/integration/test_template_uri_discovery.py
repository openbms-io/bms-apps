"""Integration test documenting BuildingMOTIF Template URI structure.

This test serves as documentation for Story 2.7 mapper implementation.
It inspects real BuildingMOTIF templates to discover what URIs/identifiers
are available for DTO mapping.
"""
import pytest
from rdflib import RDF, Namespace

from src.adapters import (
    BuildingMOTIFAdapter,
    DeviceTemplate,
    PropertyTemplate,
    SystemTemplate,
)


def test_document_device_template_structure(shared_adapter: BuildingMOTIFAdapter) -> None:
    """
    Document what URIs/identifiers are available in BuildingMOTIF Device templates.

    This test serves as documentation for Story 2.7 mapper implementation.
    Inspects the 'damper' template to understand RDF structure.
    """
    template = shared_adapter.get_template_by_name(DeviceTemplate.DAMPER)

    print(f"\n{'='*60}")
    print(f"Device Template Structure: {DeviceTemplate.DAMPER.value}")
    print(f"{'='*60}")
    print(f"Template name: {template.name}")
    print(f"Template body size: {len(template.body)} triples")

    s223 = Namespace("http://data.ashrae.org/standard223#")

    print(f"\nRDF Class URIs found:")
    class_uris = []
    for subj, pred, obj in template.body:
        if pred == RDF.type and str(obj).startswith(str(s223)):
            class_uri = str(obj)
            class_uris.append(class_uri)
            print(f"  - {class_uri}")
            print(f"    (This should be used for DTO.id)")

    assert template.name == "damper"
    assert len(template.body) > 0
    assert len(class_uris) > 0, "Should find at least one s223: class URI"


def test_document_system_template_structure(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Document System template URIs and nested structure."""
    template = shared_adapter.get_template_by_name(SystemTemplate.VAV_REHEAT)

    print(f"\n{'='*60}")
    print(f"System Template Structure: {SystemTemplate.VAV_REHEAT.value}")
    print(f"{'='*60}")
    print(f"Template name: {template.name}")
    print(f"Template body size: {len(template.body)} triples")

    s223 = Namespace("http://data.ashrae.org/standard223#")

    print(f"\nAll s223: RDF Class URIs in this system:")
    class_uris = set()
    for subj, pred, obj in template.body:
        if pred == RDF.type and str(obj).startswith(str(s223)):
            class_uri = str(obj)
            class_uris.add(class_uri)

    for uri in sorted(class_uris):
        print(f"  - {uri}")

    print(f"\nTotal unique s223 classes: {len(class_uris)}")
    print("Note: Systems contain multiple device/property classes")

    assert template.name == "vav-reheat"
    assert len(class_uris) > 1, "System should contain multiple classes"


def test_document_property_template_structure(shared_adapter: BuildingMOTIFAdapter) -> None:
    """Document Property template URIs."""
    template = shared_adapter.get_template_by_name(PropertyTemplate.DAMPER_COMMAND)

    print(f"\n{'='*60}")
    print(f"Property Template Structure: {PropertyTemplate.DAMPER_COMMAND.value}")
    print(f"{'='*60}")
    print(f"Template name: {template.name}")

    s223 = Namespace("http://data.ashrae.org/standard223#")

    print(f"\nProperty RDF Class URI:")
    for subj, pred, obj in template.body:
        if pred == RDF.type and str(obj).startswith(str(s223)):
            class_uri = str(obj)
            print(f"  - {class_uri}")
            print(f"  - Expected DTO id: {class_uri}")

    assert template.name == "damper-command"


def test_document_template_vs_instance_uri_format(shared_adapter: BuildingMOTIFAdapter) -> None:
    """
    Document the distinction between Template URIs and Instance URIs.

    Templates = HTTP URIs (ASHRAE 223P class definitions)
    Instances = URNs (specific equipment in buildings)
    """
    print(f"\n{'='*60}")
    print("URI Format: Templates vs Instances")
    print(f"{'='*60}")

    # Templates use HTTP URIs (class definitions)
    template = shared_adapter.get_template_by_name(DeviceTemplate.DAMPER)
    s223 = Namespace("http://data.ashrae.org/standard223#")

    template_uri = None
    for subj, pred, obj in template.body:
        if pred == RDF.type and str(obj).startswith(str(s223)):
            template_uri = str(obj)
            break

    print(f"\nTEMPLATES (Story 2.7 - Class Definitions):")
    print(f"  Format:  HTTP URI")
    print(f"  Example: {template_uri}")
    print(f"  Purpose: ASHRAE 223P ontology class definition")
    print(f"  Usage:   Templates endpoint returns these HTTP URIs")

    print(f"\nINSTANCES (Story 2.8+ - Specific Equipment):")
    print(f"  Format:  URN")
    print(f"  Example: urn:building/project-123/vav-101-damper")
    print(f"  Purpose: Specific equipment in a specific building")
    print(f"  Usage:   Created when user maps BACnet points")

    print(f"\nRELATIONSHIP:")
    print(f"  Instance --RDF.type--> Template")
    print(f"  urn:building/project-123/vav-101-damper --type--> {template_uri}")

    print(f"\nEPIC 1 MOCK URNS:")
    print(f"  Mock:    urn:ashrae:223p:Damper")
    print(f"  Real:    {template_uri}")
    print(f"  Status:  Mock URNs were placeholders for mockup phase")

    assert template_uri == "http://data.ashrae.org/standard223#Damper"


def test_compare_mock_vs_real_uris(shared_adapter: BuildingMOTIFAdapter) -> None:
    """
    Compare Epic 1 mock URIs vs real BuildingMOTIF URIs.

    Documents that mock URNs were placeholders.
    Real templates use HTTP URIs (ASHRAE 223P class definitions).
    """
    template = shared_adapter.get_template_by_name(DeviceTemplate.DAMPER)

    mock_uri = "urn:ashrae:223p:Damper"  # Epic 1 placeholder

    s223 = Namespace("http://data.ashrae.org/standard223#")
    real_uri = None

    for subj, pred, obj in template.body:
        if pred == RDF.type and str(obj).startswith(str(s223)):
            real_uri = str(obj)
            break

    print(f"\n{'='*60}")
    print("URI Comparison: Mock (Epic 1) vs Real (BuildingMOTIF)")
    print(f"{'='*60}")
    print(f"Epic 1 Mock URN:       {mock_uri}")
    print(f"Real ASHRAE 223P URI:  {real_uri}")
    print(f"Format:                HTTP URI (ASHRAE 223P class definition)")
    print(f"Breaking change:       {mock_uri != real_uri}")
    print(f"\nExplanation:")
    print(f"  - Templates are ASHRAE 223P class definitions (HTTP URIs)")
    print(f"  - Instances will use URNs (Story 2.8+)")
    print(f"  - Epic 1 mocks were placeholders for mockup phase")

    assert real_uri is not None
    assert real_uri.startswith("http://data.ashrae.org/standard223#")
    assert mock_uri != real_uri, "Mock URIs differ from real ASHRAE 223P URIs"


def test_extract_uri_from_multiple_templates(shared_adapter: BuildingMOTIFAdapter) -> None:
    """
    Test URI extraction pattern across multiple template types.

    Shows consistent pattern for mapper implementation.
    """
    print(f"\n{'='*60}")
    print("URI Extraction Pattern Across Template Types")
    print(f"{'='*60}")

    test_templates = [
        ("Device", DeviceTemplate.FAN),
        ("Device", DeviceTemplate.FILTER),
        ("System", SystemTemplate.MAKEUP_AIR_UNIT),
        ("Property", PropertyTemplate.STATIC_PRESSURE),
    ]

    s223 = Namespace("http://data.ashrae.org/standard223#")

    for template_type, template_enum in test_templates:
        template = shared_adapter.get_template_by_name(template_enum)

        primary_uri = None
        for subj, pred, obj in template.body:
            if pred == RDF.type and str(obj).startswith(str(s223)):
                primary_uri = str(obj)
                break

        print(f"\n{template_type}: {template_enum.value}")
        print(f"  Template name: {template.name}")
        print(f"  Primary URI:   {primary_uri}")

        assert primary_uri is not None, f"Should find URI for {template_enum.value}"


def test_document_mapper_implementation_guidance(shared_adapter: BuildingMOTIFAdapter) -> None:
    """
    Provide implementation guidance for Story 2.7 mapper functions.

    This test documents the recommended approach.
    """
    print(f"\n{'='*60}")
    print("Story 2.7 Mapper Implementation Guidance")
    print(f"{'='*60}")

    template = shared_adapter.get_template_by_name(DeviceTemplate.DAMPER)
    s223 = Namespace("http://data.ashrae.org/standard223#")

    class_uri = None
    for subj, pred, obj in template.body:
        if pred == RDF.type and str(obj).startswith(str(s223)):
            class_uri = str(obj)
            break

    print(f"\nRecommended Mapper Pattern:")
    print(f"```python")
    print(f"def extract_rdf_class_uri(template: Template) -> str:")
    print(f'    """Extract ASHRAE 223P class URI from template."""')
    print(f"    s223 = Namespace('http://data.ashrae.org/standard223#')")
    print(f"    for subj, pred, obj in template.body:")
    print(f"        if pred == RDF.type and str(obj).startswith(str(s223)):")
    print(f"            return str(obj)")
    print(f"    raise ValueError(f'No s223 class URI found in template')")
    print(f"")
    print(f"def to_device_dto(template: Template) -> TemplateDeviceDTO:")
    print(f"    class_uri = extract_rdf_class_uri(template)")
    print(f"    return TemplateDeviceDTO(")
    print(f"        id=class_uri,  # {class_uri}")
    print(f"        label=format_label(template.name),")
    print(f"        ...,")
    print(f"    )")
    print(f"```")

    print(f"\nKey Points:")
    print(f"  1. Use HTTP URIs from RDF graph (not custom URNs)")
    print(f"  2. Extract primary class URI via RDF.type predicate")
    print(f"  3. Filter by s223: namespace")
    print(f"  4. This ensures SHACL validation compatibility (Story 2.10)")

    assert class_uri == "http://data.ashrae.org/standard223#Damper"
