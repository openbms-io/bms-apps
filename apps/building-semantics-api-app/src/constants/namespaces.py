"""RDF namespace constants for ASHRAE 223P and BACnet.

Centralized namespace definitions to avoid duplication across models and mappers.
All RDF-related code should import namespaces from this module.
"""
from rdflib import Namespace

# Core ASHRAE 223P and building automation namespaces
S223 = Namespace("http://data.ashrae.org/standard223#")
QUDT = Namespace("http://qudt.org/schema/qudt/")
BMS = Namespace("urn:bms:")
BACNET = Namespace("urn:bacnet:")

# Standard RDF namespaces
RDFS = Namespace("http://www.w3.org/2000/01/rdf-schema#")
RDF = Namespace("http://www.w3.org/1999/02/22-rdf-syntax-ns#")
DCTERMS = Namespace("http://purl.org/dc/terms/")

# Reusable SPARQL prefix block for queries
SPARQL_PREFIXES = """PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
PREFIX bms: <urn:bms:>
PREFIX s223: <http://data.ashrae.org/standard223#>
PREFIX qudt: <http://qudt.org/schema/qudt/>
"""
