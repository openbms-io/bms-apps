"""ReheatInputs domain model for G36 VAV Reheat control sequence.

Not persisted yet - may be stored in future for time-series analysis.
"""

from pydantic import BaseModel, Field

from src.models.reheat.enums import OperationMode


class ReheatInputs(BaseModel):
    """Internal model for FMU inputs. All temperatures in Kelvin."""

    zoneTemperature: float = Field(
        ...,
        ge=250,
        le=350,
        description="Zone temperature in Kelvin (FMU: TZon)",
        json_schema_extra={"fmu_var": "TZon"},
    )
    coolingSetpoint: float = Field(
        ...,
        ge=250,
        le=350,
        description="Cooling setpoint in Kelvin (FMU: TCooSet)",
        json_schema_extra={"fmu_var": "TCooSet"},
    )
    heatingSetpoint: float = Field(
        ...,
        ge=250,
        le=350,
        description="Heating setpoint in Kelvin (FMU: THeaSet)",
        json_schema_extra={"fmu_var": "THeaSet"},
    )
    dischargeAirTemperature: float = Field(
        ...,
        ge=250,
        le=350,
        description="Discharge air temperature in Kelvin (FMU: TDis)",
        json_schema_extra={"fmu_var": "TDis"},
    )
    primaryAirflow: float = Field(
        ...,
        ge=0,
        description="Primary airflow in m³/s (FMU: VDis_flow)",
        json_schema_extra={"fmu_var": "VDis_flow"},
    )
    supplyAirTemperature: float = Field(
        ...,
        ge=250,
        le=350,
        description="AHU supply air temperature in Kelvin (FMU: TSup)",
        json_schema_extra={"fmu_var": "TSup"},
    )
    supplyAirTemperatureSetpoint: float = Field(
        ...,
        ge=250,
        le=350,
        description="AHU supply air temperature setpoint in Kelvin (FMU: TSupSet)",
        json_schema_extra={"fmu_var": "TSupSet"},
    )
    co2Concentration: float = Field(
        default=400.0,
        ge=0,
        description="Zone CO2 concentration in ppm (FMU: ppmCO2)",
        json_schema_extra={"fmu_var": "ppmCO2"},
    )
    co2Setpoint: float = Field(
        default=1000.0,
        ge=0,
        description="Zone CO2 setpoint in ppm (FMU: ppmCO2Set)",
        json_schema_extra={"fmu_var": "ppmCO2Set"},
    )
    fanStatus: bool = Field(
        ...,
        description="AHU fan status (FMU: u1Fan)",
        json_schema_extra={"fmu_var": "u1Fan"},
    )
    operationMode: OperationMode = Field(
        ...,
        description="Operation mode (FMU: uOpeMod)",
        json_schema_extra={"fmu_var": "uOpeMod"},
    )
    hotWaterPlantStatus: bool = Field(
        default=True,
        description="Hot water plant status (FMU: u1HotPla)",
        json_schema_extra={"fmu_var": "u1HotPla"},
    )
    occupancyStatus: bool = Field(
        default=True,
        description="Zone occupancy status (FMU: u1Occ)",
        json_schema_extra={"fmu_var": "u1Occ"},
    )
    windowStatus: bool = Field(
        default=False,
        description="Window open status (FMU: u1Win)",
        json_schema_extra={"fmu_var": "u1Win"},
    )
    heatingOff: bool = Field(
        default=False,
        description="Heating off signal (FMU: uHeaOff)",
        json_schema_extra={"fmu_var": "uHeaOff"},
    )
    overrideDamperPosition: int = Field(
        default=0,
        ge=0,
        le=1,
        description="Override mode for damper position (FMU: oveDamPos)",
        json_schema_extra={"fmu_var": "oveDamPos"},
    )
    overrideFlowSetpoint: int = Field(
        default=0,
        ge=0,
        le=1,
        description="Override mode for flow setpoint (FMU: oveFloSet)",
        json_schema_extra={"fmu_var": "oveFloSet"},
    )
