# BSIT-BOB POC - Epic Overview

## Epic 1: BSIT-BOB Library Evaluation

**Goal:** Evaluate BSIT-BOB library as a replacement for BuildingMOTIF adapter and implement if feasible.

**Context:** BuildingMOTIF has integration challenges. BSIT-BOB offers a more Pythonic approach to ASHRAE 223P semantic modeling with direct class instantiation instead of template-based approach.

### Story 1.1: BSIT-BOB Library Investigation (Spike)

Investigate BSIT-BOB library patterns and capabilities to determine feasibility of replacing BuildingMOTIF adapter implementation.

**Acceptance Criteria:**

- Produce findings document with feasibility assessment
- Document BSIT-BOB usage patterns for our use cases
- Create minimal working example replacing one BuildingMOTIF operation
- Identify missing features that need custom implementation
- Clear GO/NO-GO recommendation with rationale

### Story 1.2: BSIT-BOB Adapter Implementation

Replace the BuildingMOTIF adapter implementation with BSIT-BOB while maintaining the same public interface.

**Prerequisites:** Story 1.1 must have GO recommendation.

**Acceptance Criteria:**

- BsitBobAdapter created with equivalent interface
- Template operations work with BSIT-BOB classes
- Model creation with project namespaces
- Graph serialization to Turtle format
- SHACL validation (if spike confirms feasibility)
- Configuration switch between adapters
- All existing tests pass
