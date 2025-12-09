"""ReheatCalculatedParameters domain model for G36 VAV Reheat control sequence.

These are READ-ONLY values computed by the FMU during initialization.
They are derived from other parameters and cannot be set directly.
"""

from pydantic import BaseModel, Field


class ReheatCalculatedParameters(BaseModel):
    """Calculated parameters from FMU (causality=calculatedParameter).

    These are READ-ONLY values computed by the FMU during initialization.
    They are derived from other parameters and cannot be set directly.
    """

    minAirflow: float = Field(
        ...,
        ge=0,
        description="Calculated minimum airflow (FMU: VMin_flow) [m3/s]",
        json_schema_extra={"example": 0.1, "unit": "m3/s", "fmu_var": "VMin_flow"},
    )
    tempHysteresis: float = Field(
        ...,
        ge=0,
        description="Temperature hysteresis (FMU: dTHys) [K]",
        json_schema_extra={"example": 0.5, "unit": "K", "fmu_var": "dTHys"},
    )
    damperPositionHysteresis: float = Field(
        ...,
        ge=0,
        le=1,
        description="Damper position hysteresis (FMU: damPosHys) [1]",
        json_schema_extra={"example": 0.05, "unit": "1", "fmu_var": "damPosHys"},
    )
    flowHysteresis: float = Field(
        ...,
        ge=0,
        description="Flow hysteresis (FMU: floHys) [m3/s]",
        json_schema_extra={"example": 0.05, "unit": "m3/s", "fmu_var": "floHys"},
    )
    loopHysteresis: float = Field(
        ...,
        ge=0,
        description="Loop output hysteresis (FMU: looHys) [1]",
        json_schema_extra={"example": 0.05, "unit": "1", "fmu_var": "looHys"},
    )
    valvePositionHysteresis: float = Field(
        ...,
        ge=0,
        le=1,
        description="Valve position hysteresis (FMU: valPosHys) [1]",
        json_schema_extra={"example": 0.05, "unit": "1", "fmu_var": "valPosHys"},
    )
    hasCO2Sensor: bool = Field(
        ...,
        description="Zone has CO2 sensor (FMU: have_CO2Sen)",
        json_schema_extra={"example": False, "fmu_var": "have_CO2Sen"},
    )
    hasHotWaterCoil: bool = Field(
        ...,
        description="Terminal has hot water coil (FMU: have_hotWatCoi)",
        json_schema_extra={"example": True, "fmu_var": "have_hotWatCoi"},
    )
    hasOccupancySensor: bool = Field(
        ...,
        description="Zone has occupancy sensor (FMU: have_occSen)",
        json_schema_extra={"example": False, "fmu_var": "have_occSen"},
    )
    hasWindowSensor: bool = Field(
        ...,
        description="Zone has window sensor (FMU: have_winSen)",
        json_schema_extra={"example": False, "fmu_var": "have_winSen"},
    )
    controllerTypeDamper: int = Field(
        ...,
        ge=1,
        le=4,
        description="Controller type for damper: 1=P, 2=PI, 3=PD, 4=PID (FMU: controllerTypeDam)",
        json_schema_extra={"example": 2, "fmu_var": "controllerTypeDam"},
    )
    controllerTypeValve: int = Field(
        ...,
        ge=1,
        le=4,
        description="Controller type for valve: 1=P, 2=PI, 3=PD, 4=PID (FMU: controllerTypeVal)",
        json_schema_extra={"example": 2, "fmu_var": "controllerTypeVal"},
    )
    ventilationStandard: int = Field(
        ...,
        ge=1,
        le=2,
        description="Ventilation standard: 1=ASHRAE62_1, 2=California_Title_24 (FMU: venStd)",
        json_schema_extra={"example": 1, "fmu_var": "venStd"},
    )
