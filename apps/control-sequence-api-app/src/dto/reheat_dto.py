"""API request/response DTOs for G36 Reheat control sequence endpoints."""

from pydantic import BaseModel, Field

from src.models.reheat.enums import OperationMode, OverrideMode
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.outputs import ReheatOutputs
from src.utils.unit_conversion import (
    AirflowUnit,
    TemperatureUnit,
    airflow_in_m3_per_s,
    temp_in_kelvin,
)


class ReheatInputsRequest(BaseModel):
    """API request for G36 Reheat Terminal inputs. Accepts user-friendly units."""

    temperatureUnit: TemperatureUnit = Field(
        default=TemperatureUnit.CELSIUS,
        description="Unit for all temperature fields (default: Celsius)",
        json_schema_extra={"example": "C"},
    )
    airflowUnit: AirflowUnit = Field(
        default=AirflowUnit.M3_PER_S,
        description="Unit for all airflow fields (default: m³/s)",
        json_schema_extra={"example": "m3/s"},
    )
    zoneTemperature: float = Field(
        ...,
        description="Zone temperature",
        json_schema_extra={"example": 22.0},
    )
    coolingSetpoint: float = Field(
        ...,
        description="Cooling setpoint",
        json_schema_extra={"example": 24.0},
    )
    heatingSetpoint: float = Field(
        ...,
        description="Heating setpoint",
        json_schema_extra={"example": 20.0},
    )
    dischargeAirTemperature: float = Field(
        ...,
        description="Discharge air temperature",
        json_schema_extra={"example": 16.0},
    )
    primaryAirflow: float = Field(
        ...,
        ge=0,
        description="Primary airflow",
        json_schema_extra={"example": 0.3},
    )
    supplyAirTemperature: float = Field(
        ...,
        description="AHU supply air temperature",
        json_schema_extra={"example": 13.0},
    )
    supplyAirTemperatureSetpoint: float = Field(
        ...,
        description="AHU supply air temperature setpoint",
        json_schema_extra={"example": 12.0},
    )
    co2Concentration: float = Field(
        default=400.0,
        ge=0,
        description="Zone CO2 concentration in ppm (FMU: ppmCO2)",
        json_schema_extra={"example": 400.0},
    )
    co2Setpoint: float = Field(
        default=1000.0,
        ge=0,
        description="Zone CO2 setpoint in ppm (FMU: ppmCO2Set)",
        json_schema_extra={"example": 1000.0},
    )
    fanStatus: bool = Field(
        ...,
        description="AHU fan status (True = on, False = off)",
        json_schema_extra={"example": True},
    )
    operationMode: OperationMode = Field(
        ...,
        description="Operation mode per G36 specification (1-7)",
        json_schema_extra={"example": 3},
    )
    hotWaterPlantStatus: bool = Field(
        default=True,
        description="Hot water plant status (FMU: u1HotPla)",
        json_schema_extra={"example": True},
    )
    occupancyStatus: bool = Field(
        default=True,
        description="Zone occupancy status (FMU: u1Occ)",
        json_schema_extra={"example": True},
    )
    windowStatus: bool = Field(
        default=False,
        description="Window open status (FMU: u1Win)",
        json_schema_extra={"example": False},
    )
    heatingOff: bool = Field(
        default=False,
        description="Heating off signal (FMU: uHeaOff)",
        json_schema_extra={"example": False},
    )
    overrideDamperPosition: OverrideMode = Field(
        default=OverrideMode.NO_OVERRIDE,
        description="Override mode for damper position (FMU: oveDamPos)",
        json_schema_extra={"example": 0},
    )
    overrideFlowSetpoint: OverrideMode = Field(
        default=OverrideMode.NO_OVERRIDE,
        description="Override mode for flow setpoint (FMU: oveFloSet)",
        json_schema_extra={"example": 0},
    )

    def to_domain(self) -> ReheatInputs:
        """Convert API request to domain model with unit conversion."""
        temp_unit = self.temperatureUnit
        airflow_unit = self.airflowUnit
        return ReheatInputs(
            zoneTemperature=temp_in_kelvin(self.zoneTemperature, temp_unit),
            coolingSetpoint=temp_in_kelvin(self.coolingSetpoint, temp_unit),
            heatingSetpoint=temp_in_kelvin(self.heatingSetpoint, temp_unit),
            dischargeAirTemperature=temp_in_kelvin(
                self.dischargeAirTemperature, temp_unit
            ),
            primaryAirflow=airflow_in_m3_per_s(self.primaryAirflow, airflow_unit),
            supplyAirTemperature=temp_in_kelvin(self.supplyAirTemperature, temp_unit),
            supplyAirTemperatureSetpoint=temp_in_kelvin(
                self.supplyAirTemperatureSetpoint, temp_unit
            ),
            co2Concentration=self.co2Concentration,
            co2Setpoint=self.co2Setpoint,
            fanStatus=self.fanStatus,
            operationMode=self.operationMode,
            hotWaterPlantStatus=self.hotWaterPlantStatus,
            occupancyStatus=self.occupancyStatus,
            windowStatus=self.windowStatus,
            heatingOff=self.heatingOff,
            overrideDamperPosition=int(self.overrideDamperPosition),
            overrideFlowSetpoint=int(self.overrideFlowSetpoint),
        )


class StepRequest(BaseModel):
    """Request to execute a simulation step on an FMU instance."""

    stepSize: float = Field(
        ...,
        gt=0,
        description="Simulation step size in seconds",
        json_schema_extra={"example": 60.0},
    )
    inputs: ReheatInputsRequest = Field(
        ...,
        description="Input values for this step",
    )


class StepResponse(BaseModel):
    """Response from executing a simulation step."""

    instance_id: str = Field(
        ...,
        description="The instance that executed the step",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    outputs: ReheatOutputs = Field(
        ...,
        description="Output values from the step execution",
    )
