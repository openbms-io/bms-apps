"""ReheatOutputs domain model for G36 VAV Reheat control sequence.

Not persisted yet - may be stored in future for time-series analysis.
"""

from pydantic import BaseModel, Field


class ReheatOutputs(BaseModel):
    """Output values from G36 Reheat Terminal control sequence step execution.

    These are FMU outputs (causality=output) read after each step.
    """

    damperPosition: float = Field(
        ...,
        ge=0,
        le=1,
        description="Damper position 0-1 normalized (FMU: yDam)",
        json_schema_extra={"example": 0.75, "fmu_var": "yDam"},
    )
    valvePosition: float = Field(
        ...,
        ge=0,
        le=1,
        description="Heating valve position 0-1 normalized (FMU: yVal)",
        json_schema_extra={"example": 0.0, "fmu_var": "yVal"},
    )
    airflowSetpoint: float = Field(
        ...,
        description="Airflow setpoint in m³/s (FMU: VSet_flow)",
        json_schema_extra={"example": 0.35, "fmu_var": "VSet_flow"},
    )
    minOutdoorAirflow: float = Field(
        ...,
        ge=0,
        description="Minimum outdoor airflow in m³/s (FMU: VMinOA_flow)",
        json_schema_extra={"example": 0.1, "fmu_var": "VMinOA_flow"},
    )
    adjAreaBreathingZoneFlow: float = Field(
        ...,
        ge=0,
        description="Adjusted area breathing zone flow (FMU: VAdjAreBreZon_flow)",
        json_schema_extra={"example": 0.0, "fmu_var": "VAdjAreBreZon_flow"},
    )
    adjPopBreathingZoneFlow: float = Field(
        ...,
        ge=0,
        description="Adjusted population breathing zone flow (FMU: VAdjPopBreZon_flow)",
        json_schema_extra={"example": 0.0, "fmu_var": "VAdjPopBreZon_flow"},
    )
    flowSensorAlarm: int = Field(
        ...,
        ge=0,
        description="Flow sensor alarm level (FMU: yFloSenAla)",
        json_schema_extra={"example": 0, "fmu_var": "yFloSenAla"},
    )
    heatingValveRequest: int = Field(
        ...,
        ge=0,
        description="Heating valve reset request (FMU: yHeaValResReq)",
        json_schema_extra={"example": 0, "fmu_var": "yHeaValResReq"},
    )
    hotWaterPlantRequest: int = Field(
        ...,
        ge=0,
        description="Hot water plant request (FMU: yHotWatPlaReq)",
        json_schema_extra={"example": 0, "fmu_var": "yHotWatPlaReq"},
    )
    leakingDamperAlarm: int = Field(
        ...,
        ge=0,
        description="Leaking damper alarm level (FMU: yLeaDamAla)",
        json_schema_extra={"example": 0, "fmu_var": "yLeaDamAla"},
    )
    leakingValveAlarm: int = Field(
        ...,
        ge=0,
        description="Leaking valve alarm level (FMU: yLeaValAla)",
        json_schema_extra={"example": 0, "fmu_var": "yLeaValAla"},
    )
    lowFlowAlarm: int = Field(
        ...,
        ge=0,
        description="Low flow alarm level (FMU: yLowFloAla)",
        json_schema_extra={"example": 0, "fmu_var": "yLowFloAla"},
    )
    lowTempAlarm: int = Field(
        ...,
        ge=0,
        description="Low temperature alarm level (FMU: yLowTemAla)",
        json_schema_extra={"example": 0, "fmu_var": "yLowTemAla"},
    )
    zonePressureRequest: int = Field(
        ...,
        ge=0,
        description="Zone pressure reset request (FMU: yZonPreResReq)",
        json_schema_extra={"example": 0, "fmu_var": "yZonPreResReq"},
    )
    zoneTempRequest: int = Field(
        ...,
        ge=0,
        description="Zone temperature reset request (FMU: yZonTemResReq)",
        json_schema_extra={"example": 0, "fmu_var": "yZonTemResReq"},
    )
