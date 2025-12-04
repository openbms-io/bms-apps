from enum import IntEnum, StrEnum

from pydantic import BaseModel, Field

CELSIUS_TO_KELVIN_OFFSET = 273.15
FAHRENHEIT_TO_CELSIUS_OFFSET = 32
FAHRENHEIT_TO_CELSIUS_RATIO = 5 / 9


class TemperatureUnit(StrEnum):
    """Supported temperature units for API inputs."""

    KELVIN = "K"
    CELSIUS = "C"
    FAHRENHEIT = "F"


def temp_in_kelvin(value: float, unit: TemperatureUnit) -> float:
    if unit == TemperatureUnit.KELVIN:
        return value
    if unit == TemperatureUnit.CELSIUS:
        return value + CELSIUS_TO_KELVIN_OFFSET
    fahrenheit_as_celsius = (
        (value - FAHRENHEIT_TO_CELSIUS_OFFSET) * FAHRENHEIT_TO_CELSIUS_RATIO
    )
    return fahrenheit_as_celsius + CELSIUS_TO_KELVIN_OFFSET


class OperationMode(IntEnum):
    """G36 operation modes per ASHRAE Guideline 36 specification."""

    OCCUPIED = 1
    UNOCCUPIED = 2
    STANDBY = 3
    WARMUP = 4
    COOLDOWN = 5
    SETUP = 6
    SETBACK = 7


class ReheatParameters(BaseModel):
    """Configurable parameters for G36 Reheat Terminal control sequence."""

    maxCoolingAirflow: float = Field(
        default=0.5,
        ge=0,
        description="Maximum cooling airflow in m³/s (FMU: VCooMax)",
        json_schema_extra={"example": 0.5},
    )
    maxHeatingAirflow: float = Field(
        default=0.3,
        ge=0,
        description="Maximum heating airflow in m³/s (FMU: VHeaMax)",
        json_schema_extra={"example": 0.3},
    )
    minAirflow: float = Field(
        default=0.1,
        ge=0,
        description="Minimum airflow in m³/s (FMU: VMin)",
        json_schema_extra={"example": 0.1},
    )


class ReheatInputsRequest(BaseModel):
    """API request for G36 Reheat Terminal inputs. Accepts any temperature unit."""

    temperatureUnit: TemperatureUnit = Field(
        default=TemperatureUnit.CELSIUS,
        description="Unit for all temperature fields (default: Celsius)",
        json_schema_extra={"example": "C"},
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
        description="Primary airflow in m³/s",
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


class ReheatInputs(BaseModel):
    """Internal model for FMU. All temperatures in Kelvin, validated."""

    zoneTemperature: float = Field(
        ...,
        ge=250,
        le=350,
        description="Zone temperature in Kelvin (FMU: TZon)",
    )
    coolingSetpoint: float = Field(
        ...,
        ge=250,
        le=350,
        description="Cooling setpoint in Kelvin (FMU: TCooSet)",
    )
    heatingSetpoint: float = Field(
        ...,
        ge=250,
        le=350,
        description="Heating setpoint in Kelvin (FMU: THeaSet)",
    )
    dischargeAirTemperature: float = Field(
        ...,
        ge=250,
        le=350,
        description="Discharge air temperature in Kelvin (FMU: TDis)",
    )
    primaryAirflow: float = Field(
        ...,
        ge=0,
        description="Primary airflow in m³/s (FMU: VDis_flow)",
    )
    supplyAirTemperature: float = Field(
        ...,
        ge=250,
        le=350,
        description="AHU supply air temperature in Kelvin (FMU: TSup)",
    )
    supplyAirTemperatureSetpoint: float = Field(
        ...,
        ge=250,
        le=350,
        description="AHU supply air temperature setpoint in Kelvin (FMU: TSupSet)",
    )
    fanStatus: bool = Field(
        ...,
        description="AHU fan status (FMU: u1Fan)",
    )
    operationMode: OperationMode = Field(
        ...,
        description="Operation mode (FMU: uOpeMod)",
    )

    @classmethod
    def from_request(cls, request: ReheatInputsRequest) -> "ReheatInputs":
        unit = request.temperatureUnit
        return cls(
            zoneTemperature=temp_in_kelvin(request.zoneTemperature, unit),
            coolingSetpoint=temp_in_kelvin(request.coolingSetpoint, unit),
            heatingSetpoint=temp_in_kelvin(request.heatingSetpoint, unit),
            dischargeAirTemperature=temp_in_kelvin(
                request.dischargeAirTemperature, unit
            ),
            primaryAirflow=request.primaryAirflow,
            supplyAirTemperature=temp_in_kelvin(request.supplyAirTemperature, unit),
            supplyAirTemperatureSetpoint=temp_in_kelvin(
                request.supplyAirTemperatureSetpoint, unit
            ),
            fanStatus=request.fanStatus,
            operationMode=request.operationMode,
        )


class ReheatOutputs(BaseModel):
    """Output values from G36 Reheat Terminal control sequence step execution."""

    damperPosition: float = Field(
        ...,
        ge=0,
        le=1,
        description="Damper position 0-1 normalized (FMU: yDam)",
        json_schema_extra={"example": 0.75},
    )
    valvePosition: float = Field(
        ...,
        ge=0,
        le=1,
        description="Heating valve position 0-1 normalized (FMU: yVal)",
        json_schema_extra={"example": 0.0},
    )
    airflowSetpoint: float = Field(
        ...,
        description="Airflow setpoint in m³/s (FMU: VSet_flow)",
        json_schema_extra={"example": 0.35},
    )


class CreateInstanceRequest(BaseModel):
    """Request to create a new FMU control sequence instance."""

    instance_id: str = Field(
        ...,
        description="Unique identifier for the FMU instance",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    parameters: ReheatParameters | None = Field(
        default=None,
        description="Optional custom parameters (uses defaults if not provided)",
    )


class CreateInstanceResponse(BaseModel):
    """Response after creating an FMU instance."""

    instance_id: str = Field(
        ...,
        description="The created instance identifier",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    created: bool = Field(
        ...,
        description="Whether the instance was successfully created",
        json_schema_extra={"example": True},
    )


class UpdateInstanceRequest(BaseModel):
    """Request to update parameters of an existing FMU instance."""

    parameters: ReheatParameters = Field(
        ...,
        description="New parameters for the instance",
    )


class UpdateInstanceResponse(BaseModel):
    """Response after updating an FMU instance."""

    instance_id: str = Field(
        ...,
        description="The updated instance identifier",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    updated: bool = Field(
        ...,
        description="Whether the instance was successfully updated",
        json_schema_extra={"example": True},
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


class DeleteInstanceResponse(BaseModel):
    """Response after deleting an FMU instance."""

    instance_id: str = Field(
        ...,
        description="The deleted instance identifier",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    deleted: bool = Field(
        ...,
        description="Whether the instance was successfully deleted",
        json_schema_extra={"example": True},
    )
