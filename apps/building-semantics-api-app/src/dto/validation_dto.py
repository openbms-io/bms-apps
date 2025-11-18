from pydantic import BaseModel, Field


class ValidationResultDTO(BaseModel):
    """SHACL validation result for equipment mappings."""

    isValid: bool = Field(
        ...,
        description="True if all SHACL constraints pass"
    )
    errors: list[str] = Field(
        default_factory=list,
        description="SHACL constraint violation messages"
    )
    warnings: list[str] = Field(
        default_factory=list,
        description="Optional warnings or recommendations"
    )

    model_config = {
        "json_schema_extra": {
            "examples": [
                {
                    "isValid": False,
                    "errors": [
                        "Equipment type 'invalid-type' not found in ASHRAE 223P ontology"
                    ],
                    "warnings": []
                }
            ]
        }
    }
