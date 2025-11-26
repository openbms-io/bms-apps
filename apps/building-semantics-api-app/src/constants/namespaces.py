"""RDF namespace constants for ASHRAE 223P and BACnet.

Centralized namespace definitions to avoid duplication across models and mappers.
All RDF-related code should import namespaces from this module.
"""
from rdflib import Namespace

# Namespace URI strings (for use in SPARQL queries and string operations)
S223_NAMESPACE_STRING = "http://data.ashrae.org/standard223#"
QUDT_NAMESPACE_STRING = "http://qudt.org/schema/qudt/"
BMS_NAMESPACE_STRING = "urn:bms:"
BACNET_NAMESPACE_STRING = "http://data.ashrae.org/bacnet/2020#"
RDFS_NAMESPACE_STRING = "http://www.w3.org/2000/01/rdf-schema#"
RDF_NAMESPACE_STRING = "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
DCTERMS_NAMESPACE_STRING = "http://purl.org/dc/terms/"

# Internal index namespace for efficient BACnet point reverse lookups
# We maintain two separate RDF structures:
# 1. 223P-compliant: property → s223:hasExternalReference → s223:BACnetExternalReference
#    (stores device-identifier, object-identifier, external-identifier per ASHRAE 223P)
# 2. Internal index: urn:bms:bacnet:{bacnet_point_id} → bms-bacnet:mapsToProperty → property
#    (enables efficient reverse lookup: bacnet_point_id → property for CRUD operations)
# The index is internal lookup metadata, not semantic data, and doesn't affect SHACL validation.
BMS_BACNET_INDEX_STRING = f"{BMS_NAMESPACE_STRING}bacnet:"

# Core ASHRAE 223P and building automation namespaces
S223 = Namespace(S223_NAMESPACE_STRING)
QUDT = Namespace(QUDT_NAMESPACE_STRING)
BMS = Namespace(BMS_NAMESPACE_STRING)
BACNET = Namespace(BACNET_NAMESPACE_STRING)
BMS_BACNET_INDEX = Namespace(BMS_BACNET_INDEX_STRING)

# Standard RDF namespaces
RDFS = Namespace(RDFS_NAMESPACE_STRING)
RDF = Namespace(RDF_NAMESPACE_STRING)
DCTERMS = Namespace(DCTERMS_NAMESPACE_STRING)

# Reusable SPARQL prefix block for queries
SPARQL_PREFIXES = f"""PREFIX rdfs: <{RDFS_NAMESPACE_STRING}>
PREFIX rdf: <{RDF_NAMESPACE_STRING}>
PREFIX bms: <{BMS_NAMESPACE_STRING}>
PREFIX bms-bacnet: <{BMS_BACNET_INDEX_STRING}>
PREFIX s223: <{S223_NAMESPACE_STRING}>
PREFIX qudt: <{QUDT_NAMESPACE_STRING}>
"""
