"""Mock spaces data for Epic 1 spaces endpoint.

NOTE:
- Story 2.7 (Templates) - DONE, uses real BuildingMOTIF data
- Story 2.8 (Mappings) - DONE, uses real RDF persistence with BuildingMOTIF
- Story 2.9 (Spaces) - PENDING, currently using MOCK_SPACES below

This file will be deleted after Story 2.9 is implemented.
"""

from datetime import UTC, datetime

from ..dto.spaces_dto import SpaceInstanceDTO

MOCK_SPACES: list[SpaceInstanceDTO] = [
    SpaceInstanceDTO(
        id="mock-space-001",
        spaceTypeId="http://data.ashrae.org/standard223#PhysicalSpace",
        label="Mock Space",
        createdAt=datetime.now(UTC).isoformat(),
    ),
]
