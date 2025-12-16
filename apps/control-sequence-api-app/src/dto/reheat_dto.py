"""API request/response DTOs for G36 Reheat control sequence endpoints."""

from pydantic import BaseModel, Field

from src.models.reheat.enums import (
    ControllerType,
    OPERATION_MODE_STR_TO_INT,
    OperationModeStr,
    OverrideMode,
    ParameterCategory,
    VentilationStandard,
)
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.outputs import ReheatOutputs
from src.models.reheat.parameters import ReheatParameters
from src.utils.unit_conversion import (
    AirflowUnit,
    m3_per_s_to_airflow,
    TemperatureUnit,
)


class ReheatInputsDTO(BaseModel):
    """API request for G36 Reheat Terminal inputs. Accepts user-friendly units.

    Unit preferences are stored per-instance in ReheatParametersDTO and passed
    to to_domain() from the controller.
    """

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
    operationMode: OperationModeStr = Field(
        ...,
        description="Operation mode per G36 specification",
        json_schema_extra={"example": "occupied"},
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
        """Convert API request to domain model.

        Values are passed as-is. Unit conversion (if needed) is handled by
        the FMU adapter based on stored ReheatParametersDTO unit preferences.
        """
        return ReheatInputs(
            zoneTemperature=self.zoneTemperature,
            coolingSetpoint=self.coolingSetpoint,
            heatingSetpoint=self.heatingSetpoint,
            dischargeAirTemperature=self.dischargeAirTemperature,
            primaryAirflow=self.primaryAirflow,
            supplyAirTemperature=self.supplyAirTemperature,
            supplyAirTemperatureSetpoint=self.supplyAirTemperatureSetpoint,
            co2Concentration=self.co2Concentration,
            co2Setpoint=self.co2Setpoint,
            fanStatus=self.fanStatus,
            operationMode=OPERATION_MODE_STR_TO_INT[self.operationMode],
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
    inputs: ReheatInputsDTO = Field(
        ...,
        description="Input values for this step",
    )


class ReheatOutputsDTO(BaseModel):
    """API DTO for G36 Reheat Terminal outputs.

    Wraps domain ReheatOutputs and converts airflow values to user units.
    Damper/valve positions are 0-1 normalized (unitless).
    """

    damperPosition: float = Field(
        ...,
        ge=0,
        le=1,
        description="Damper position 0-1 normalized",
        json_schema_extra={"example": 0.75},
    )
    valvePosition: float = Field(
        ...,
        ge=0,
        le=1,
        description="Heating valve position 0-1 normalized",
        json_schema_extra={"example": 0.0},
    )
    airflowSetpoint: float = Field(
        ...,
        description="Airflow setpoint (in user's configured unit)",
        json_schema_extra={"example": 0.35},
    )
    minOutdoorAirflow: float = Field(
        ...,
        ge=0,
        description="Minimum outdoor airflow (in user's configured unit)",
        json_schema_extra={"example": 0.1},
    )
    adjAreaBreathingZoneFlow: float = Field(
        ...,
        ge=0,
        description="Adjusted area breathing zone flow (in user's configured unit)",
        json_schema_extra={"example": 0.0},
    )
    adjPopBreathingZoneFlow: float = Field(
        ...,
        ge=0,
        description="Adjusted population breathing zone flow (in user's configured unit)",
        json_schema_extra={"example": 0.0},
    )
    flowSensorAlarm: int = Field(
        ...,
        ge=0,
        description="Flow sensor alarm level",
        json_schema_extra={"example": 0},
    )
    heatingValveRequest: int = Field(
        ...,
        ge=0,
        description="Heating valve reset request",
        json_schema_extra={"example": 0},
    )
    hotWaterPlantRequest: int = Field(
        ...,
        ge=0,
        description="Hot water plant request",
        json_schema_extra={"example": 0},
    )
    leakingDamperAlarm: int = Field(
        ...,
        ge=0,
        description="Leaking damper alarm level",
        json_schema_extra={"example": 0},
    )
    leakingValveAlarm: int = Field(
        ...,
        ge=0,
        description="Leaking valve alarm level",
        json_schema_extra={"example": 0},
    )
    lowFlowAlarm: int = Field(
        ...,
        ge=0,
        description="Low flow alarm level",
        json_schema_extra={"example": 0},
    )
    lowTempAlarm: int = Field(
        ...,
        ge=0,
        description="Low temperature alarm level",
        json_schema_extra={"example": 0},
    )
    zonePressureRequest: int = Field(
        ...,
        ge=0,
        description="Zone pressure reset request",
        json_schema_extra={"example": 0},
    )
    zoneTempRequest: int = Field(
        ...,
        ge=0,
        description="Zone temperature reset request",
        json_schema_extra={"example": 0},
    )

    @classmethod
    def from_domain(
        cls,
        outputs: ReheatOutputs,
        airflow_unit: AirflowUnit,
    ) -> "ReheatOutputsDTO":
        """Create DTO from domain model with airflow unit conversion.

        Args:
            outputs: Domain model with airflow values in m³/s
            airflow_unit: Target airflow unit from stored parameters
        """
        return cls(
            damperPosition=outputs.damperPosition,
            valvePosition=outputs.valvePosition,
            airflowSetpoint=m3_per_s_to_airflow(outputs.airflowSetpoint, airflow_unit),
            minOutdoorAirflow=m3_per_s_to_airflow(outputs.minOutdoorAirflow, airflow_unit),
            adjAreaBreathingZoneFlow=m3_per_s_to_airflow(outputs.adjAreaBreathingZoneFlow, airflow_unit),
            adjPopBreathingZoneFlow=m3_per_s_to_airflow(outputs.adjPopBreathingZoneFlow, airflow_unit),
            flowSensorAlarm=outputs.flowSensorAlarm,
            heatingValveRequest=outputs.heatingValveRequest,
            hotWaterPlantRequest=outputs.hotWaterPlantRequest,
            leakingDamperAlarm=outputs.leakingDamperAlarm,
            leakingValveAlarm=outputs.leakingValveAlarm,
            lowFlowAlarm=outputs.lowFlowAlarm,
            lowTempAlarm=outputs.lowTempAlarm,
            zonePressureRequest=outputs.zonePressureRequest,
            zoneTempRequest=outputs.zoneTempRequest,
        )


class StepResponse(BaseModel):
    """Response from executing a simulation step."""

    model_config = {"populate_by_name": True}

    instance_id: str = Field(
        ...,
        serialization_alias="instanceId",
        description="The instance that executed the step",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    outputs: ReheatOutputsDTO = Field(
        ...,
        description="Output values from the step execution",
    )


class ReheatParametersDTO(BaseModel):
    """API DTO for parameters. No unit-specific temperature constraints.

    Validation of temperature values happens in ParameterConverter using
    get_temperature_bounds() before storing in database.
    """

    # === Unit preferences (stored per-instance) ===
    temperatureUnit: TemperatureUnit = Field(
        default=TemperatureUnit.KELVIN,
        description="Unit for temperature input/output values",
        json_schema_extra={"example": "K", "category": ParameterCategory.UNITS},
    )
    airflowUnit: AirflowUnit = Field(
        default=AirflowUnit.M3_PER_S,
        description="Unit for airflow input/output values",
        json_schema_extra={"example": "m3/s", "category": ParameterCategory.UNITS},
    )

    # === Sensor configuration (Boolean) ===
    hasCO2Sensor: bool = Field(
        default=True,
        description="Zone has CO2 sensor (FMU: have_CO2Sen_in)",
        json_schema_extra={"example": True, "fmu_var": "have_CO2Sen_in", "category": ParameterCategory.SENSORS},
    )
    hasHotWaterCoil: bool = Field(
        default=True,
        description="Terminal has hot water coil (FMU: have_hotWatCoi_in)",
        json_schema_extra={"example": True, "fmu_var": "have_hotWatCoi_in", "category": ParameterCategory.SENSORS},
    )
    hasOccupancySensor: bool = Field(
        default=True,
        description="Zone has occupancy sensor (FMU: have_occSen_in)",
        json_schema_extra={"example": True, "fmu_var": "have_occSen_in", "category": ParameterCategory.SENSORS},
    )
    hasWindowSensor: bool = Field(
        default=True,
        description="Zone has window sensor (FMU: have_winSen_in)",
        json_schema_extra={"example": True, "fmu_var": "have_winSen_in", "category": ParameterCategory.SENSORS},
    )

    # === Controller types (Enumeration) ===
    controllerTypeDamper: ControllerType = Field(
        default=ControllerType.PI,
        description="Controller type for damper: 1=P, 2=PI, 3=PD, 4=PID (FMU: controllerTypeDam_in)",
        json_schema_extra={"example": 2, "fmu_var": "controllerTypeDam_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )
    controllerTypeValve: ControllerType = Field(
        default=ControllerType.PI,
        description="Controller type for valve: 1=P, 2=PI, 3=PD, 4=PID (FMU: controllerTypeVal_in)",
        json_schema_extra={"example": 2, "fmu_var": "controllerTypeVal_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )
    ventilationStandard: VentilationStandard = Field(
        default=VentilationStandard.ASHRAE62_1,
        description="Ventilation standard: 1=ASHRAE62_1, 2=California_Title_24 (FMU: venStd_in)",
        json_schema_extra={"example": 1, "fmu_var": "venStd_in", "category": ParameterCategory.AIRFLOWS},
    )

    # === Airflow parameters (unit: m3/s) ===
    minAirflow: float = Field(
        default=0.3,
        ge=0,
        description="Design zone minimum airflow setpoint (FMU: VMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.3, "unit": "m3/s", "fmu_var": "VMin_flow_in", "category": ParameterCategory.AIRFLOWS},
    )
    maxCoolingAirflow: float = Field(
        default=1.5,
        ge=0,
        description="Maximum cooling airflow (FMU: VCooMax_flow_in) [m3/s]",
        json_schema_extra={"example": 1.5, "unit": "m3/s", "fmu_var": "VCooMax_flow_in", "category": ParameterCategory.AIRFLOWS},
    )
    maxHeatingAirflow: float = Field(
        default=1.2,
        ge=0,
        description="Maximum heating airflow (FMU: VHeaMax_flow_in) [m3/s]",
        json_schema_extra={"example": 1.2, "unit": "m3/s", "fmu_var": "VHeaMax_flow_in", "category": ParameterCategory.AIRFLOWS},
    )
    minHeatingAirflow: float = Field(
        default=0.5,
        ge=0,
        description="Minimum heating airflow (FMU: VHeaMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.5, "unit": "m3/s", "fmu_var": "VHeaMin_flow_in", "category": ParameterCategory.AIRFLOWS},
    )
    areaBreathingZoneFlow: float = Field(
        default=0.006,
        ge=0,
        description="Area component of breathing zone outdoor airflow (FMU: VAreBreZon_flow_in) [m3/s]",
        json_schema_extra={"example": 0.006, "unit": "m3/s", "fmu_var": "VAreBreZon_flow_in", "category": ParameterCategory.AIRFLOWS},
    )
    areaMinFlow: float = Field(
        default=0.0,
        ge=0,
        description="Area component of zone minimum airflow (FMU: VAreMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.0, "unit": "m3/s", "fmu_var": "VAreMin_flow_in", "category": ParameterCategory.AIRFLOWS},
    )
    occMinFlow: float = Field(
        default=0.0,
        ge=0,
        description="Zone minimum airflow for occupied mode (FMU: VOccMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.0, "unit": "m3/s", "fmu_var": "VOccMin_flow_in", "category": ParameterCategory.AIRFLOWS},
    )
    popBreathingZoneFlow: float = Field(
        default=0.005,
        ge=0,
        description="Population component of breathing zone airflow (FMU: VPopBreZon_flow_in) [m3/s]",
        json_schema_extra={"example": 0.005, "unit": "m3/s", "fmu_var": "VPopBreZon_flow_in", "category": ParameterCategory.AIRFLOWS},
    )

    # === Temperature parameters (NO ge/le constraints - validated in ParameterConverter) ===
    dischargeAirTempMin: float = Field(
        default=283.15,
        description="Minimum discharge air temperature (FMU: TDisMin_in)",
        json_schema_extra={"example": 283.15, "unit": "K", "fmu_var": "TDisMin_in", "category": ParameterCategory.THRESHOLDS},
    )
    maxDischargeTempAboveSetpoint: float = Field(
        default=11.0,
        ge=0,
        description="Zone max discharge air temp above heating setpoint (FMU: dTDisZonSetMax_in) [K]",
        json_schema_extra={"example": 11.0, "unit": "K", "fmu_var": "dTDisZonSetMax_in", "category": ParameterCategory.THRESHOLDS},
    )

    # === Controller gains (unit: 1, dimensionless) ===
    coolingControllerGain: float = Field(
        default=0.1,
        ge=0,
        description="Gain of cooling loop controller (FMU: kCooCon_in) [1]",
        json_schema_extra={"example": 0.1, "unit": "1", "fmu_var": "kCooCon_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )
    heatingControllerGain: float = Field(
        default=0.1,
        ge=0,
        description="Gain of heating loop controller (FMU: kHeaCon_in) [1]",
        json_schema_extra={"example": 0.1, "unit": "1", "fmu_var": "kHeaCon_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )
    damperControllerGain: float = Field(
        default=0.5,
        ge=0,
        description="Gain of controller for damper control (FMU: kDam_in) [1]",
        json_schema_extra={"example": 0.5, "unit": "1", "fmu_var": "kDam_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )
    valveControllerGain: float = Field(
        default=0.5,
        ge=0,
        description="Gain of controller for valve control (FMU: kVal_in) [1]",
        json_schema_extra={"example": 0.5, "unit": "1", "fmu_var": "kVal_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )

    # === Controller time constants (unit: s) ===
    damperDerivativeTime: float = Field(
        default=0.1,
        ge=0,
        description="Time constant of derivative block for damper control (FMU: TdDam_in) [s]",
        json_schema_extra={"example": 0.1, "unit": "s", "fmu_var": "TdDam_in", "category": ParameterCategory.TIMING},
    )
    valveDerivativeTime: float = Field(
        default=0.1,
        ge=0,
        description="Time constant of derivative block for valve control (FMU: TdVal_in) [s]",
        json_schema_extra={"example": 0.1, "unit": "s", "fmu_var": "TdVal_in", "category": ParameterCategory.TIMING},
    )
    coolingIntegratorTime: float = Field(
        default=120.0,
        ge=0,
        description="Time constant of integrator block for cooling control loop (FMU: TiCooCon_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "TiCooCon_in", "category": ParameterCategory.TIMING},
    )
    damperIntegratorTime: float = Field(
        default=300.0,
        ge=0,
        description="Time constant of integrator block for damper control (FMU: TiDam_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "TiDam_in", "category": ParameterCategory.TIMING},
    )
    heatingIntegratorTime: float = Field(
        default=120.0,
        ge=0,
        description="Time constant of integrator block for heating control loop (FMU: TiHeaCon_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "TiHeaCon_in", "category": ParameterCategory.TIMING},
    )
    valveIntegratorTime: float = Field(
        default=300.0,
        ge=0,
        description="Time constant of integrator block for valve control (FMU: TiVal_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "TiVal_in", "category": ParameterCategory.TIMING},
    )

    # === Duration/timing parameters (unit: s) ===
    changeRate: float = Field(
        default=540.0,
        ge=0,
        description="Gain factor to calculate suppression time based on setpoint change (FMU: chaRat_in) [s/K]",
        json_schema_extra={"example": 540.0, "unit": "s/K", "fmu_var": "chaRat_in", "category": ParameterCategory.TIMING},
    )
    durationDischargeAir: float = Field(
        default=300.0,
        ge=0,
        description="Duration time of discharge air temp less than setpoint (FMU: durTimDisAir_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "durTimDisAir_in", "category": ParameterCategory.TIMING},
    )
    durationFlow: float = Field(
        default=60.0,
        ge=0,
        description="Duration time of airflow rate less than setpoint (FMU: durTimFlo_in) [s]",
        json_schema_extra={"example": 60.0, "unit": "s", "fmu_var": "durTimFlo_in", "category": ParameterCategory.TIMING},
    )
    durationTemp: float = Field(
        default=120.0,
        ge=0,
        description="Duration time of zone temp exceeds setpoint (FMU: durTimTem_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "durTimTem_in", "category": ParameterCategory.TIMING},
    )
    maxSuppressionTime: float = Field(
        default=1800.0,
        ge=0,
        description="Maximum suppression time (FMU: maxSupTim_in) [s]",
        json_schema_extra={"example": 1800.0, "unit": "s", "fmu_var": "maxSupTim_in", "category": ParameterCategory.TIMING},
    )
    samplePeriod: float = Field(
        default=120.0,
        ge=0,
        description="Sample period of component (FMU: samplePeriod_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "samplePeriod_in", "category": ParameterCategory.TIMING},
    )

    # === Alarm timing thresholds (unit: s) ===
    fanOffTime: float = Field(
        default=600.0,
        ge=0,
        description="Threshold time to check fan off (FMU: fanOffTim_in) [s]",
        json_schema_extra={"example": 600.0, "unit": "s", "fmu_var": "fanOffTim_in", "category": ParameterCategory.TIMING},
    )
    leakFlowTime: float = Field(
        default=600.0,
        ge=0,
        description="Threshold time to check damper leaking airflow (FMU: leaFloTim_in) [s]",
        json_schema_extra={"example": 600.0, "unit": "s", "fmu_var": "leaFloTim_in", "category": ParameterCategory.TIMING},
    )
    lowFlowTime: float = Field(
        default=300.0,
        ge=0,
        description="Threshold time to check low flow rate (FMU: lowFloTim_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "lowFloTim_in", "category": ParameterCategory.TIMING},
    )
    lowTempTime: float = Field(
        default=600.0,
        ge=0,
        description="Threshold time to check low discharge temperature (FMU: lowTemTim_in) [s]",
        json_schema_extra={"example": 600.0, "unit": "s", "fmu_var": "lowTemTim_in", "category": ParameterCategory.TIMING},
    )
    valveCloseTime: float = Field(
        default=900.0,
        ge=0,
        description="Threshold time to check valve closed (FMU: valCloTim_in) [s]",
        json_schema_extra={"example": 900.0, "unit": "s", "fmu_var": "valCloTim_in", "category": ParameterCategory.TIMING},
    )
    timeCheck: float = Field(
        default=30.0,
        ge=0,
        description="Threshold time to check zone temperature status (FMU: timChe_in) [s]",
        json_schema_extra={"example": 30.0, "unit": "s", "fmu_var": "timChe_in", "category": ParameterCategory.TIMING},
    )
    startupTime: float = Field(
        default=1800.0,
        ge=0,
        description="Delay triggering alarms after enabling AHU supply fan (FMU: staTim_in) [s]",
        json_schema_extra={"example": 1800.0, "unit": "s", "fmu_var": "staTim_in", "category": ParameterCategory.TIMING},
    )

    # === Temperature thresholds (unit: K) ===
    thresholdDischargeTemp1: float = Field(
        default=17.0,
        ge=0,
        description="Threshold difference for 3 hot water reset requests (FMU: thrTDis_1_in) [K]",
        json_schema_extra={"example": 17.0, "unit": "K", "fmu_var": "thrTDis_1_in", "category": ParameterCategory.THRESHOLDS},
    )
    thresholdDischargeTemp2: float = Field(
        default=8.0,
        ge=0,
        description="Threshold difference for 2 hot water reset requests (FMU: thrTDis_2_in) [K]",
        json_schema_extra={"example": 8.0, "unit": "K", "fmu_var": "thrTDis_2_in", "category": ParameterCategory.THRESHOLDS},
    )
    thresholdTempDiff: float = Field(
        default=3.0,
        ge=0,
        description="Threshold difference for temperature alarms (FMU: thrTemDif_in) [K]",
        json_schema_extra={"example": 3.0, "unit": "K", "fmu_var": "thrTemDif_in", "category": ParameterCategory.THRESHOLDS},
    )
    twoTempDiff: float = Field(
        default=2.0,
        ge=0,
        description="Threshold temp difference for 2 zone temp requests (FMU: twoTemDif_in) [K]",
        json_schema_extra={"example": 2.0, "unit": "K", "fmu_var": "twoTemDif_in", "category": ParameterCategory.THRESHOLDS},
    )

    # === Importance multipliers (unit: 1, dimensionless) ===
    hotWaterResetMultiplier: float = Field(
        default=1.0,
        ge=0,
        description="Importance multiplier for hot water reset control loop (FMU: hotWatRes_in) [1]",
        json_schema_extra={"example": 1.0, "unit": "1", "fmu_var": "hotWatRes_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )
    staticPressureMultiplier: float = Field(
        default=1.0,
        ge=0,
        description="Importance multiplier for zone static pressure reset (FMU: staPreMul_in) [1]",
        json_schema_extra={"example": 1.0, "unit": "1", "fmu_var": "staPreMul_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )

    # === Zone distribution effectiveness (unit: 1, dimensionless) ===
    zoneDistEffCooling: float = Field(
        default=1.0,
        ge=0,
        le=2,
        description="Zone air distribution effectiveness during cooling (FMU: zonDisEff_cool_in) [1]",
        json_schema_extra={"example": 1.0, "unit": "1", "fmu_var": "zonDisEff_cool_in", "category": ParameterCategory.AIRFLOWS},
    )
    zoneDistEffHeating: float = Field(
        default=0.8,
        ge=0,
        le=2,
        description="Zone air distribution effectiveness during heating (FMU: zonDisEff_heat_in) [1]",
        json_schema_extra={"example": 0.8, "unit": "1", "fmu_var": "zonDisEff_heat_in", "category": ParameterCategory.AIRFLOWS},
    )

    # === Initial values (unit: 1, dimensionless) ===
    initialDamperPosition: float = Field(
        default=0.01,
        ge=0,
        le=1,
        description="Initial damper position when control is enabled (FMU: iniDam_in) [1]",
        json_schema_extra={"example": 0.01, "unit": "1", "fmu_var": "iniDam_in", "category": ParameterCategory.CONTROLLER_GAINS},
    )

    # === Feature toggles (enable/disable control sequence behaviors) ===
    permitOccStandby: bool = Field(
        default=True,
        description="When enabled and zone is unpopulated (per occupancy sensor), reduces ventilation to zero per ASHRAE 62.1 for energy savings (FMU: permit_occStandby_in)",
        json_schema_extra={"example": True, "fmu_var": "permit_occStandby_in", "category": ParameterCategory.FEATURES},
    )

    # === Hysteresis parameters (Advanced) ===
    tempHysteresis: float = Field(
        default=0.25,
        ge=0,
        description="Near zero temperature difference hysteresis (FMU: dTHys_in) [K]",
        json_schema_extra={"example": 0.25, "unit": "K", "fmu_var": "dTHys_in", "category": ParameterCategory.HYSTERESIS},
    )
    loopHysteresis: float = Field(
        default=0.01,
        ge=0,
        le=1,
        description="Loop output hysteresis below which output is seen as zero (FMU: looHys_in) [1]",
        json_schema_extra={"example": 0.01, "unit": "1", "fmu_var": "looHys_in", "category": ParameterCategory.HYSTERESIS},
    )
    flowHysteresis: float = Field(
        default=0.003,
        ge=0,
        description="Near zero flow rate hysteresis (FMU: floHys_in) [m3/s]",
        json_schema_extra={"example": 0.003, "unit": "m3/s", "fmu_var": "floHys_in", "category": ParameterCategory.HYSTERESIS},
    )
    damperPositionHysteresis: float = Field(
        default=0.005,
        ge=0,
        le=1,
        description="Near zero damper position, below which damper is seen as closed (FMU: damPosHys_in) [1]",
        json_schema_extra={"example": 0.005, "unit": "1", "fmu_var": "damPosHys_in", "category": ParameterCategory.HYSTERESIS},
    )
    valvePositionHysteresis: float = Field(
        default=0.005,
        ge=0,
        le=1,
        description="Near zero valve position, below which valve is seen as closed (FMU: valPosHys_in) [1]",
        json_schema_extra={"example": 0.005, "unit": "1", "fmu_var": "valPosHys_in", "category": ParameterCategory.HYSTERESIS},
    )

    def to_domain(self) -> ReheatParameters:
        """Convert to domain model. Caller must validate temperature ranges first."""
        return ReheatParameters(**self.model_dump())
