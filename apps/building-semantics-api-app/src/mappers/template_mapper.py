"""Pure mapper functions for converting BuildingMOTIF templates to DTOs.

These functions are stateless and have zero adapter dependency.
They accept BuildingMOTIF Template objects and return Pydantic DTOs.
"""

from buildingmotif.dataclasses import Template
from rdflib import RDF, Namespace

from ..adapters.template_types import DeviceTemplate, PropertyTemplate, SystemTemplate
from ..dto.templates_dto import (
    SpaceTypeDTO,
    TemplateDeviceDTO,
    TemplatePropertyDTO,
    TemplateSystemDTO,
)


def extract_rdf_class_uri(template: Template) -> str:
    """Extract ASHRAE 223P HTTP URI from BuildingMOTIF template RDF graph.

    Args:
        template: BuildingMOTIF template with RDF body

    Returns:
        HTTP URI string (e.g., "http://data.ashrae.org/standard223#Damper")

    Raises:
        ValueError: If no s223 class URI found in template
    """
    s223 = Namespace("http://data.ashrae.org/standard223#")

    for subj, pred, obj in template.body:
        if pred == RDF.type and str(obj).startswith(str(s223)):
            return str(obj)

    raise ValueError(f"No s223 class URI found in template: {template.name}")


def _format_label(template_name: str) -> str:
    """Convert template name to human-readable label.

    Args:
        template_name: Template name (e.g., "vav-reheat")

    Returns:
        Formatted label (e.g., "VAV Reheat")
    """
    return template_name.replace("-", " ").title()


def _determine_property_type(class_uri: str) -> str:
    """Determine property type from ASHRAE 223P class URI.

    Args:
        class_uri: HTTP URI for property class

    Returns:
        "quantifiable" or "enumerated"
    """
    # Most properties are quantifiable
    # Enumerated properties have "Enumerable" in the class name
    if "Enumerable" in class_uri or "EnumeratedObservable" in class_uri:
        return "enumerated"
    return "quantifiable"


def _is_actuatable_property(class_uri: str) -> bool:
    """Check if property is actuatable from class URI.

    Args:
        class_uri: ASHRAE 223P property class URI

    Returns:
        True if actuatable, False if observable
    """
    return "Actuatable" in class_uri


def _format_uri_to_label(uri: str) -> str:
    """Convert URI to human-readable label by stripping namespace.

    Args:
        uri: Full URI (e.g., "http://qudt.org/vocab/unit/DEG_C")

    Returns:
        Label (e.g., "DEG_C")
    """
    if not uri:
        return ""
    # Handle fragment identifier (#)
    if "#" in uri:
        return uri.split("#")[-1]
    # Handle path separator (/)
    return uri.split("/")[-1]


def _extract_qudt_property(template: Template, predicate_name: str) -> str | None:
    """Extract QUDT property from template RDF graph.

    Args:
        template: BuildingMOTIF template
        predicate_name: Predicate name (e.g., "hasQuantityKind", "hasUnit")

    Returns:
        Formatted label or None if not found
    """
    qudt = Namespace("http://qudt.org/schema/qudt/")

    for _, pred, obj in template.body:
        pred_str = str(pred)
        if pred_str == str(qudt[predicate_name]):
            return _format_uri_to_label(str(obj))

    return None


def _extract_s223_property(template: Template, predicate_name: str) -> str | None:
    """Extract s223 property from template RDF graph.

    Args:
        template: BuildingMOTIF template
        predicate_name: Predicate name (e.g., "ofMedium", "hasEnumerationKind")

    Returns:
        Formatted label or None if not found
    """
    s223 = Namespace("http://data.ashrae.org/standard223#")

    for _, pred, obj in template.body:
        pred_str = str(pred)
        if pred_str == str(s223[predicate_name]):
            return _format_uri_to_label(str(obj))

    return None


def to_property_dto(template: Template) -> TemplatePropertyDTO:
    """Convert BuildingMOTIF property template to DTO with full metadata.

    Args:
        template: BuildingMOTIF property template

    Returns:
        TemplatePropertyDTO with template name as ID, class URI, metadata fields
    """
    class_uri = extract_rdf_class_uri(template)
    property_type = _determine_property_type(class_uri)
    is_actuatable = _is_actuatable_property(class_uri)

    # Extract QUDT metadata
    quantity_kind = _extract_qudt_property(template, "hasQuantityKind")
    unit = _extract_qudt_property(template, "hasUnit")

    # Extract s223 metadata (optional fields)
    medium = _extract_s223_property(template, "ofMedium")
    enumeration_kind = _extract_s223_property(template, "hasEnumerationKind")

    return TemplatePropertyDTO(
        id=template.name,
        label=_format_label(template.name),
        class_uri=class_uri,
        property_type=property_type,  # type: ignore
        quantity_kind=quantity_kind,
        unit=unit,
        medium=medium,
        enumeration_kind=enumeration_kind,
        is_actuatable=is_actuatable,
        description=None,
    )


def to_device_dto(
    template: Template,
    property_templates: list[Template],
) -> TemplateDeviceDTO:
    """Convert BuildingMOTIF device template to DTO with nested properties.

    Args:
        template: BuildingMOTIF device template
        property_templates: List of property templates for this device

    Returns:
        TemplateDeviceDTO with template name as ID, class URI, device_type, and nested properties
    """
    from ..dto.templates_dto import DeviceType

    # Extract class URI
    class_uri = extract_rdf_class_uri(template)

    # Determine device type (SENSOR vs OTHER)
    device_type = DeviceType.SENSOR if template.name == "sensor" else DeviceType.OTHER

    # Convert property templates to DTOs
    properties = [to_property_dto(prop_template) for prop_template in property_templates]

    return TemplateDeviceDTO(
        id=template.name,
        label=_format_label(template.name),
        class_uri=class_uri,
        device_type=device_type,
        description=None,
        properties=properties,
    )


def to_system_dto(
    template: Template,
    device_templates: dict[str, tuple[Template, list[Template]]],
) -> TemplateSystemDTO:
    """Convert BuildingMOTIF system template to DTO with nested devices and properties.

    Args:
        template: BuildingMOTIF system template
        device_templates: Dict mapping device names to (device_template, property_templates)

    Returns:
        TemplateSystemDTO with template name as ID, class URI, label, and nested devices with properties
    """
    # Extract class URI
    class_uri = extract_rdf_class_uri(template)

    # Convert device templates to DTOs
    devices = []
    for device_template, property_templates in device_templates.values():
        device_dto = to_device_dto(device_template, property_templates)
        devices.append(device_dto)

    return TemplateSystemDTO(
        id=template.name,
        label=_format_label(template.name),
        class_uri=class_uri,
        description=None,
        devices=devices,
    )


def to_space_type_dto(template: Template) -> SpaceTypeDTO:
    """Convert BuildingMOTIF space type template to DTO.

    Args:
        template: BuildingMOTIF space type template

    Returns:
        SpaceTypeDTO with HTTP URI and label
    """
    class_uri = extract_rdf_class_uri(template)

    return SpaceTypeDTO(
        id=class_uri,
        label=_format_label(template.name),
        description=None,
    )


def is_device_template(template_name: str) -> bool:
    """Check if template name corresponds to a device template.

    Args:
        template_name: Template name to check

    Returns:
        True if template is a device template
    """
    return template_name in [t.value for t in DeviceTemplate]


def is_property_template(template_name: str) -> bool:
    """Check if template name corresponds to a property template.

    Args:
        template_name: Template name to check

    Returns:
        True if template is a property template
    """
    return template_name in [t.value for t in PropertyTemplate]


def is_system_template(template_name: str) -> bool:
    """Check if template name corresponds to a system template.

    Args:
        template_name: Template name to check

    Returns:
        True if template is a system template
    """
    return template_name in [t.value for t in SystemTemplate]
