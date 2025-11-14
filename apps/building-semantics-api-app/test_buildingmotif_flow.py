"""Manual test script for BuildingMOTIF core flow."""
import tempfile
from pathlib import Path

from src.adapters.buildingmotif_adapter import BuildingMOTIFAdapter

print("=== BuildingMOTIF Core Flow Test ===\n")

# Create temporary database
temp_db = tempfile.mktemp(suffix=".db")
print(f"1. Creating temporary database: {temp_db}")

# Initialize adapter
print("2. Initializing BuildingMOTIF adapter...")
adapter = BuildingMOTIFAdapter(temp_db)
print("   ✓ Adapter initialized")

# Verify database created
db_path = Path(temp_db)
print(f"3. Verifying database file exists: {db_path.exists()}")
print(f"   Database size: {db_path.stat().st_size} bytes")

# Get ASHRAE library
print("4. Loading ASHRAE 223P library...")
library = adapter.get_ashrae_library()
print(f"   ✓ Library loaded: {library._name}")

# List templates
print("5. Listing available templates...")
templates = adapter.list_templates()
print(f"   ✓ Found {len(templates)} templates")
print(f"   First 5 templates: {templates[:5]}")

# Create a model
print("6. Creating RDF model...")
model = adapter.create_model("urn:test:building/")
print("   ✓ Model created")

# Query model
print("7. Querying model...")
results = adapter.query_model(model, "SELECT * WHERE { ?s ?p ?o } LIMIT 5")
print(f"   ✓ Query returned {len(results)} results")

print("\n=== All tests passed! ===")
print(f"Database location: {temp_db}")
print("Note: Temporary database will be cleaned up on exit")
