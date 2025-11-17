"""Mapper functions for ASHRAE 223P mappings RDF ↔ DTO conversions.

Stateless transformation functions for converting between RDF triples and DTOs.
Note: to_equipment_rdf_triples() uses template.fill() to generate complete graphs,
then substitutes auto-generated URNs with custom URNs.
"""

from typing import TypeAlias
from uuid import uuid4

from rdflib import Graph, Literal, Namespace, RDF, URIRef

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter
from src.adapters.template_types import DeviceTemplate, PropertyTemplate, SystemTemplate
from src.dto.mappings_dto import MappingsResponseDTO, SemanticMappingDTO

# RDF namespace constants
S223 = Namespace("http://data.ashrae.org/standard223#")
BACNET = Namespace("http://data.ashrae.org/bacnet/2020#")
BMS = Namespace("urn:bms:")
DCTERMS = Namespace("http://purl.org/dc/terms/")

# Type aliases
RDFTriple: TypeAlias = tuple[URIRef, URIRef, URIRef | Literal]


def create_equipment_uri(point_id: str) -> URIRef:
    """
    Create equipment instance URI from point ID.

    Args:
        point_id: Point ID from Designer (e.g., "device,123:analog-input,1")

    Returns:
        Equipment URI (e.g., "urn:bms:Equipment:device-123-analog-input-1")
    """
    safe_id = point_id.replace(":", "-").replace(",", "-")
    return URIRef(f"{BMS}Equipment:{safe_id}")


def create_device_uri(point_id: str) -> URIRef:
    """
    Create device instance URI from point ID.

    Args:
        point_id: Point ID from Designer (e.g., "device,123:analog-input,1")

    Returns:
        Device URI (e.g., "urn:bms:Device:device-123-analog-input-1")
    """
    safe_id = point_id.replace(":", "-").replace(",", "-")
    return URIRef(f"{BMS}Device:{safe_id}")


def create_property_uri(point_id: str) -> URIRef:
    """
    Create property instance URI from point ID.

    Args:
        point_id: Point ID from Designer (e.g., "device,123:analog-input,1")

    Returns:
        Property URI (e.g., "urn:bms:Property:device-123-analog-input-1")
    """
    safe_id = point_id.replace(":", "-").replace(",", "-")
    return URIRef(f"{BMS}Property:{safe_id}")


def create_bacnet_ref_uri(point_id: str) -> URIRef:
    """
    Create BACnet external reference URI from point ID.

    Args:
        point_id: Point ID from Designer (e.g., "device,123:analog-input,1")

    Returns:
        BACnet reference URI (e.g., "urn:bms:BACnetRef:device-123-analog-input-1")
    """
    safe_id = point_id.replace(":", "-").replace(",", "-")
    return URIRef(f"{BMS}BACnetRef:{safe_id}")


def create_project_uri(project_id: str) -> URIRef:
    """
    Create project URI from project ID.

    Args:
        project_id: Project identifier (e.g., "proj-123")

    Returns:
        Project URI (e.g., "urn:bms:Project:proj-123")
    """
    return URIRef(f"{BMS}Project:{project_id}")


def to_equipment_rdf_triples(
    equipment_uri: URIRef,
    point_id: str,
    mapping: SemanticMappingDTO,
    adapter: BuildingMOTIFAdapter,
) -> list[RDFTriple]:
    """
    Convert DTO to equipment RDF triples using template.fill() for complete instantiation.

    Uses template.fill() to generate complete instantiated graphs with all sub-components
    (sensors, connection points, etc.), then substitutes auto-generated URNs with our
    custom URNs based on point_id.

    Returns equipment + device + property + BACnetExternalReference triples.
    Does NOT include project relationship (see to_project_relationship_triples).

    Args:
        equipment_uri: Equipment instance URI
        point_id: Point ID from Designer (e.g., "device,123:analog-input,1")
        mapping: SemanticMappingDTO with equipment/device/property/space IDs
        adapter: BuildingMOTIF adapter for template lookups

    Returns:
        List of (subject, predicate, object) triples
    """
    # Parse point_id (simple split, no parsing logic)
    device_id, object_id = point_id.split(":")  # "device,123:analog-input,1"

    # Create URIs
    device_uri = create_device_uri(point_id)
    property_uri = create_property_uri(point_id)
    bacnet_ref_uri = create_bacnet_ref_uri(point_id)

    # Get templates from adapter
    equipment_template = adapter.get_template_by_name(
        SystemTemplate(mapping.equipment_type_id)
    )
    device_template = adapter.get_template_by_name(DeviceTemplate(mapping.device_type_id))
    property_template = adapter.get_template_by_name(
        PropertyTemplate(mapping.property_id)
    )

    # Use fill() to generate complete instantiated graphs with auto-generated URNs
    equipment_bindings, equipment_graph = equipment_template.fill(BMS)
    device_bindings, device_graph = device_template.fill(BMS)
    property_bindings, property_graph = property_template.fill(BMS)

    # Extract auto-generated URNs from bindings
    auto_equipment_uri = equipment_bindings["name"]
    auto_device_uri = device_bindings["name"]
    auto_property_uri = property_bindings["name"]

    # Collect all triples, substituting auto URNs with our custom URNs
    triples: list[RDFTriple] = []

    # Substitute equipment triples (replace auto URN with our equipment_uri)
    for s, p, o in equipment_graph:
        new_s = equipment_uri if s == auto_equipment_uri else s
        new_o = equipment_uri if o == auto_equipment_uri else o
        triples.append((new_s, p, new_o))

    # Substitute device triples (replace auto URN with our device_uri)
    for s, p, o in device_graph:
        new_s = device_uri if s == auto_device_uri else s
        new_o = device_uri if o == auto_device_uri else o
        triples.append((new_s, p, new_o))

    # Substitute property triples (replace auto URN with our property_uri)
    for s, p, o in property_graph:
        new_s = property_uri if s == auto_property_uri else s
        new_o = property_uri if o == auto_property_uri else o
        triples.append((new_s, p, new_o))

    # Add manual linking triples (custom composition based on user selection)
    triples.extend([
        (equipment_uri, S223.contains, device_uri),
        (equipment_uri, S223.hasExternalReference, bacnet_ref_uri),
        (device_uri, S223.hasProperty, property_uri),
    ])

    # Store original template IDs for round-trip fidelity (frontend ↔ backend)
    triples.extend([
        (equipment_uri, BMS.hasTemplateId, Literal(mapping.equipment_type_id)),
        (device_uri, BMS.hasTemplateId, Literal(mapping.device_type_id)),
        (property_uri, BMS.hasTemplateId, Literal(mapping.property_id)),
    ])

    # Optional: Physical space relationship (where equipment is located)
    if mapping.physical_space_id:
        physical_space_uri = URIRef(mapping.physical_space_id)
        triples.append((equipment_uri, S223.locatedIn, physical_space_uri))

    # Optional: Domain space relationships (zones equipment serves)
    if mapping.domain_space_ids:
        for domain_id in mapping.domain_space_ids:
            domain_uri = URIRef(domain_id)
            triples.append((equipment_uri, S223.hasDomain, domain_uri))

    # BACnet External Reference triples (223P-compliant)
    triples.extend(
        [
            (bacnet_ref_uri, RDF.type, S223.BACnetExternalReference),
            (bacnet_ref_uri, BACNET["device-identifier"], Literal(device_id)),
            (bacnet_ref_uri, BACNET["object-identifier"], Literal(object_id)),
            (bacnet_ref_uri, DCTERMS.identifier, Literal(point_id)),
        ]
    )

    return triples


def to_project_relationship_triples(
    project_uri: URIRef, equipment_uris: list[URIRef]
) -> list[RDFTriple]:
    """
    Convert project contains relationships to RDF triples (pure function).

    Returns triples: project s223:contains equipment (for each equipment).
    External relationship pattern - stored separately from equipment instances.

    Args:
        project_uri: Project instance URI
        equipment_uris: List of equipment URIs to link to project

    Returns:
        List of (project_uri, s223:contains, equipment_uri) triples
    """
    triples: list[RDFTriple] = []
    for equipment_uri in equipment_uris:
        triples.append((project_uri, S223.contains, equipment_uri))
    return triples


def to_mapping_dto(
    equipment_uri: URIRef, point_id: str, graph: Graph
) -> SemanticMappingDTO:
    """
    Extract point mapping from RDF graph (pure function).

    Reverse transformation: RDF triples → DTO.
    Extracts equipment/device/property type IDs and space ID from graph.

    Args:
        equipment_uri: Equipment instance URI
        point_id: Point ID extracted from BACnet external reference
        graph: RDF graph to query

    Returns:
        SemanticMappingDTO with equipment/device/property/space IDs
    """
    # Query for equipment class URI
    equipment_class_uri = graph.value(equipment_uri, RDF.type)

    # Query for device
    device_uri = graph.value(equipment_uri, S223.contains)
    device_class_uri = graph.value(device_uri, RDF.type) if device_uri else None

    # Query for property
    property_uri = (
        graph.value(device_uri, S223.hasProperty) if device_uri else None
    )
    property_class_uri = (
        graph.value(property_uri, RDF.type) if property_uri else None
    )

    # Query for space (optional)
    space_uri = graph.value(equipment_uri, S223.locatedIn)

    # Extract template IDs from class URIs (reverse lookup)
    # NOTE: This is a simplified implementation - full version needs mapping
    # from class URIs back to template IDs (stored in separate lookup table)
    equipment_type_id = str(equipment_class_uri).split("#")[-1] if equipment_class_uri else ""
    device_type_id = str(device_class_uri).split("#")[-1] if device_class_uri else ""
    property_id = str(property_class_uri).split("#")[-1] if property_class_uri else ""

    return SemanticMappingDTO(
        equipment_type_id=equipment_type_id,
        device_type_id=device_type_id,
        property_id=property_id,
        space_id=str(space_uri) if space_uri else None,
    )


def to_mappings_response_dto(
    project_id: str, mappings_dict: dict[str, SemanticMappingDTO]
) -> MappingsResponseDTO:
    """
    Convert mappings dictionary to response DTO (pure function).

    Args:
        project_id: Project identifier
        mappings_dict: Dictionary keyed by point ID

    Returns:
        MappingsResponseDTO with project ID and mappings
    """
    return MappingsResponseDTO(projectId=project_id, mappings=mappings_dict)
