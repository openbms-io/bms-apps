from enum import IntEnum, StrEnum

from pydantic import BaseModel, Field

CELSIUS_TO_KELVIN_OFFSET = 273.15
FAHRENHEIT_TO_CELSIUS_OFFSET = 32
FAHRENHEIT_TO_CELSIUS_RATIO = 5 / 9

CFM_TO_M3_PER_S = 0.000471947
L_PER_S_TO_M3_PER_S = 0.001
M3_PER_H_TO_M3_PER_S = 1 / 3600


class TemperatureUnit(StrEnum):
    """Supported temperature units for API inputs."""

    KELVIN = "K"
    CELSIUS = "C"
    FAHRENHEIT = "F"


class AirflowUnit(StrEnum):
    """Supported airflow units for API inputs."""

    M3_PER_S = "m3/s"
    CFM = "cfm"
    L_PER_S = "L/s"
    M3_PER_H = "m3/h"


def temp_in_kelvin(value: float, unit: TemperatureUnit) -> float:
    if unit == TemperatureUnit.KELVIN:
        return value
    if unit == TemperatureUnit.CELSIUS:
        return value + CELSIUS_TO_KELVIN_OFFSET
    fahrenheit_as_celsius = (
        (value - FAHRENHEIT_TO_CELSIUS_OFFSET) * FAHRENHEIT_TO_CELSIUS_RATIO
    )
    return fahrenheit_as_celsius + CELSIUS_TO_KELVIN_OFFSET


def airflow_in_m3_per_s(value: float, unit: AirflowUnit) -> float:
    if unit == AirflowUnit.M3_PER_S:
        return value
    if unit == AirflowUnit.CFM:
        return value * CFM_TO_M3_PER_S
    if unit == AirflowUnit.L_PER_S:
        return value * L_PER_S_TO_M3_PER_S
    return value * M3_PER_H_TO_M3_PER_S


class OperationMode(IntEnum):
    """G36 operation modes per ASHRAE Guideline 36 specification."""

    OCCUPIED = 1
    UNOCCUPIED = 2
    STANDBY = 3
    WARMUP = 4
    COOLDOWN = 5
    SETUP = 6
    SETBACK = 7


class VentilationStandard(IntEnum):
    """Ventilation standard selection."""

    ASHRAE62_1 = 1
    CALIFORNIA_TITLE_24 = 2


class ControllerType(IntEnum):
    """Controller type for damper/valve control."""

    P = 1
    PI = 2
    PD = 3
    PID = 4


class ReheatParameters(BaseModel):
    """Configurable parameters for G36 Reheat Terminal control sequence.

    These are FMU parameters (causality=parameter) that can be set before/during init.
    """

    # === Sensor configuration (Boolean) ===
    hasCO2Sensor: bool = Field(
        default=True,
        description="Zone has CO2 sensor (FMU: have_CO2Sen_in)",
        json_schema_extra={"example": True, "fmu_var": "have_CO2Sen_in"},
    )
    hasHotWaterCoil: bool = Field(
        default=True,
        description="Terminal has hot water coil (FMU: have_hotWatCoi_in)",
        json_schema_extra={"example": True, "fmu_var": "have_hotWatCoi_in"},
    )
    hasOccupancySensor: bool = Field(
        default=True,
        description="Zone has occupancy sensor (FMU: have_occSen_in)",
        json_schema_extra={"example": True, "fmu_var": "have_occSen_in"},
    )
    hasWindowSensor: bool = Field(
        default=True,
        description="Zone has window sensor (FMU: have_winSen_in)",
        json_schema_extra={"example": True, "fmu_var": "have_winSen_in"},
    )

    # === Controller types (Enumeration) ===
    controllerTypeDamper: ControllerType = Field(
        default=ControllerType.PI,
        description="Controller type for damper: 1=P, 2=PI, 3=PD, 4=PID (FMU: controllerTypeDam_in)",
        json_schema_extra={"example": 2, "fmu_var": "controllerTypeDam_in"},
    )
    controllerTypeValve: ControllerType = Field(
        default=ControllerType.PI,
        description="Controller type for valve: 1=P, 2=PI, 3=PD, 4=PID (FMU: controllerTypeVal_in)",
        json_schema_extra={"example": 2, "fmu_var": "controllerTypeVal_in"},
    )
    ventilationStandard: VentilationStandard = Field(
        default=VentilationStandard.ASHRAE62_1,
        description="Ventilation standard: 1=ASHRAE62_1, 2=California_Title_24 (FMU: venStd_in)",
        json_schema_extra={"example": 1, "fmu_var": "venStd_in"},
    )

    # === Airflow parameters (unit: m3/s) ===
    minAirflow: float = Field(
        default=0.3,
        ge=0,
        description="Design zone minimum airflow setpoint (FMU: VMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.3, "unit": "m3/s", "fmu_var": "VMin_flow_in"},
    )
    maxCoolingAirflow: float = Field(
        default=1.5,
        ge=0,
        description="Maximum cooling airflow (FMU: VCooMax_flow_in) [m3/s]",
        json_schema_extra={"example": 1.5, "unit": "m3/s", "fmu_var": "VCooMax_flow_in"},
    )
    maxHeatingAirflow: float = Field(
        default=1.2,
        ge=0,
        description="Maximum heating airflow (FMU: VHeaMax_flow_in) [m3/s]",
        json_schema_extra={"example": 1.2, "unit": "m3/s", "fmu_var": "VHeaMax_flow_in"},
    )
    minHeatingAirflow: float = Field(
        default=0.5,
        ge=0,
        description="Minimum heating airflow (FMU: VHeaMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.5, "unit": "m3/s", "fmu_var": "VHeaMin_flow_in"},
    )
    areaBreathingZoneFlow: float = Field(
        default=0.006,
        ge=0,
        description="Area component of breathing zone outdoor airflow (FMU: VAreBreZon_flow_in) [m3/s]",
        json_schema_extra={"example": 0.006, "unit": "m3/s", "fmu_var": "VAreBreZon_flow_in"},
    )
    areaMinFlow: float = Field(
        default=0.0,
        ge=0,
        description="Area component of zone minimum airflow (FMU: VAreMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.0, "unit": "m3/s", "fmu_var": "VAreMin_flow_in"},
    )
    occMinFlow: float = Field(
        default=0.0,
        ge=0,
        description="Zone minimum airflow for occupied mode (FMU: VOccMin_flow_in) [m3/s]",
        json_schema_extra={"example": 0.0, "unit": "m3/s", "fmu_var": "VOccMin_flow_in"},
    )
    popBreathingZoneFlow: float = Field(
        default=0.005,
        ge=0,
        description="Population component of breathing zone airflow (FMU: VPopBreZon_flow_in) [m3/s]",
        json_schema_extra={"example": 0.005, "unit": "m3/s", "fmu_var": "VPopBreZon_flow_in"},
    )

    # === Temperature parameters (unit: K) ===
    dischargeAirTempMin: float = Field(
        default=283.15,
        ge=250,
        le=350,
        description="Minimum discharge air temperature (FMU: TDisMin_in) [K]",
        json_schema_extra={"example": 283.15, "unit": "K", "fmu_var": "TDisMin_in"},
    )
    maxDischargeTempAboveSetpoint: float = Field(
        default=11.0,
        ge=0,
        description="Zone max discharge air temp above heating setpoint (FMU: dTDisZonSetMax_in) [K]",
        json_schema_extra={"example": 11.0, "unit": "K", "fmu_var": "dTDisZonSetMax_in"},
    )

    # === Controller gains (unit: 1, dimensionless) ===
    coolingControllerGain: float = Field(
        default=0.1,
        ge=0,
        description="Gain of cooling loop controller (FMU: kCooCon_in) [1]",
        json_schema_extra={"example": 0.1, "unit": "1", "fmu_var": "kCooCon_in"},
    )
    heatingControllerGain: float = Field(
        default=0.1,
        ge=0,
        description="Gain of heating loop controller (FMU: kHeaCon_in) [1]",
        json_schema_extra={"example": 0.1, "unit": "1", "fmu_var": "kHeaCon_in"},
    )
    damperControllerGain: float = Field(
        default=0.5,
        ge=0,
        description="Gain of controller for damper control (FMU: kDam_in) [1]",
        json_schema_extra={"example": 0.5, "unit": "1", "fmu_var": "kDam_in"},
    )
    valveControllerGain: float = Field(
        default=0.5,
        ge=0,
        description="Gain of controller for valve control (FMU: kVal_in) [1]",
        json_schema_extra={"example": 0.5, "unit": "1", "fmu_var": "kVal_in"},
    )

    # === Controller time constants (unit: s) ===
    damperDerivativeTime: float = Field(
        default=0.1,
        ge=0,
        description="Time constant of derivative block for damper control (FMU: TdDam_in) [s]",
        json_schema_extra={"example": 0.1, "unit": "s", "fmu_var": "TdDam_in"},
    )
    valveDerivativeTime: float = Field(
        default=0.1,
        ge=0,
        description="Time constant of derivative block for valve control (FMU: TdVal_in) [s]",
        json_schema_extra={"example": 0.1, "unit": "s", "fmu_var": "TdVal_in"},
    )
    coolingIntegratorTime: float = Field(
        default=120.0,
        ge=0,
        description="Time constant of integrator block for cooling control loop (FMU: TiCooCon_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "TiCooCon_in"},
    )
    damperIntegratorTime: float = Field(
        default=300.0,
        ge=0,
        description="Time constant of integrator block for damper control (FMU: TiDam_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "TiDam_in"},
    )
    heatingIntegratorTime: float = Field(
        default=120.0,
        ge=0,
        description="Time constant of integrator block for heating control loop (FMU: TiHeaCon_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "TiHeaCon_in"},
    )
    valveIntegratorTime: float = Field(
        default=300.0,
        ge=0,
        description="Time constant of integrator block for valve control (FMU: TiVal_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "TiVal_in"},
    )

    # === Duration/timing parameters (unit: s) ===
    changeRate: float = Field(
        default=540.0,
        ge=0,
        description="Gain factor to calculate suppression time based on setpoint change (FMU: chaRat_in) [s/K]",
        json_schema_extra={"example": 540.0, "unit": "s/K", "fmu_var": "chaRat_in"},
    )
    durationDischargeAir: float = Field(
        default=300.0,
        ge=0,
        description="Duration time of discharge air temp less than setpoint (FMU: durTimDisAir_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "durTimDisAir_in"},
    )
    durationFlow: float = Field(
        default=60.0,
        ge=0,
        description="Duration time of airflow rate less than setpoint (FMU: durTimFlo_in) [s]",
        json_schema_extra={"example": 60.0, "unit": "s", "fmu_var": "durTimFlo_in"},
    )
    durationTemp: float = Field(
        default=120.0,
        ge=0,
        description="Duration time of zone temp exceeds setpoint (FMU: durTimTem_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "durTimTem_in"},
    )
    maxSuppressionTime: float = Field(
        default=1800.0,
        ge=0,
        description="Maximum suppression time (FMU: maxSupTim_in) [s]",
        json_schema_extra={"example": 1800.0, "unit": "s", "fmu_var": "maxSupTim_in"},
    )
    samplePeriod: float = Field(
        default=120.0,
        ge=0,
        description="Sample period of component (FMU: samplePeriod_in) [s]",
        json_schema_extra={"example": 120.0, "unit": "s", "fmu_var": "samplePeriod_in"},
    )

    # === Alarm timing thresholds (unit: s) ===
    fanOffTime: float = Field(
        default=600.0,
        ge=0,
        description="Threshold time to check fan off (FMU: fanOffTim_in) [s]",
        json_schema_extra={"example": 600.0, "unit": "s", "fmu_var": "fanOffTim_in"},
    )
    leakFlowTime: float = Field(
        default=600.0,
        ge=0,
        description="Threshold time to check damper leaking airflow (FMU: leaFloTim_in) [s]",
        json_schema_extra={"example": 600.0, "unit": "s", "fmu_var": "leaFloTim_in"},
    )
    lowFlowTime: float = Field(
        default=300.0,
        ge=0,
        description="Threshold time to check low flow rate (FMU: lowFloTim_in) [s]",
        json_schema_extra={"example": 300.0, "unit": "s", "fmu_var": "lowFloTim_in"},
    )
    lowTempTime: float = Field(
        default=600.0,
        ge=0,
        description="Threshold time to check low discharge temperature (FMU: lowTemTim_in) [s]",
        json_schema_extra={"example": 600.0, "unit": "s", "fmu_var": "lowTemTim_in"},
    )
    valveCloseTime: float = Field(
        default=900.0,
        ge=0,
        description="Threshold time to check valve closed (FMU: valCloTim_in) [s]",
        json_schema_extra={"example": 900.0, "unit": "s", "fmu_var": "valCloTim_in"},
    )
    timeCheck: float = Field(
        default=30.0,
        ge=0,
        description="Threshold time to check zone temperature status (FMU: timChe_in) [s]",
        json_schema_extra={"example": 30.0, "unit": "s", "fmu_var": "timChe_in"},
    )
    startupTime: float = Field(
        default=1800.0,
        ge=0,
        description="Delay triggering alarms after enabling AHU supply fan (FMU: staTim_in) [s]",
        json_schema_extra={"example": 1800.0, "unit": "s", "fmu_var": "staTim_in"},
    )

    # === Temperature thresholds (unit: K) ===
    thresholdDischargeTemp1: float = Field(
        default=17.0,
        ge=0,
        description="Threshold difference for 3 hot water reset requests (FMU: thrTDis_1_in) [K]",
        json_schema_extra={"example": 17.0, "unit": "K", "fmu_var": "thrTDis_1_in"},
    )
    thresholdDischargeTemp2: float = Field(
        default=8.0,
        ge=0,
        description="Threshold difference for 2 hot water reset requests (FMU: thrTDis_2_in) [K]",
        json_schema_extra={"example": 8.0, "unit": "K", "fmu_var": "thrTDis_2_in"},
    )
    thresholdTempDiff: float = Field(
        default=3.0,
        ge=0,
        description="Threshold difference for temperature alarms (FMU: thrTemDif_in) [K]",
        json_schema_extra={"example": 3.0, "unit": "K", "fmu_var": "thrTemDif_in"},
    )
    twoTempDiff: float = Field(
        default=2.0,
        ge=0,
        description="Threshold temp difference for 2 zone temp requests (FMU: twoTemDif_in) [K]",
        json_schema_extra={"example": 2.0, "unit": "K", "fmu_var": "twoTemDif_in"},
    )

    # === Importance multipliers (unit: 1, dimensionless) ===
    hotWaterResetMultiplier: float = Field(
        default=1.0,
        ge=0,
        description="Importance multiplier for hot water reset control loop (FMU: hotWatRes_in) [1]",
        json_schema_extra={"example": 1.0, "unit": "1", "fmu_var": "hotWatRes_in"},
    )
    staticPressureMultiplier: float = Field(
        default=1.0,
        ge=0,
        description="Importance multiplier for zone static pressure reset (FMU: staPreMul_in) [1]",
        json_schema_extra={"example": 1.0, "unit": "1", "fmu_var": "staPreMul_in"},
    )

    # === Zone distribution effectiveness (unit: 1, dimensionless) ===
    zoneDistEffCooling: float = Field(
        default=1.0,
        ge=0,
        le=2,
        description="Zone air distribution effectiveness during cooling (FMU: zonDisEff_cool_in) [1]",
        json_schema_extra={"example": 1.0, "unit": "1", "fmu_var": "zonDisEff_cool_in"},
    )
    zoneDistEffHeating: float = Field(
        default=0.8,
        ge=0,
        le=2,
        description="Zone air distribution effectiveness during heating (FMU: zonDisEff_heat_in) [1]",
        json_schema_extra={"example": 0.8, "unit": "1", "fmu_var": "zonDisEff_heat_in"},
    )

    # === Initial values (unit: 1, dimensionless) ===
    initialDamperPosition: float = Field(
        default=0.01,
        ge=0,
        le=1,
        description="Initial damper position when control is enabled (FMU: iniDam_in) [1]",
        json_schema_extra={"example": 0.01, "unit": "1", "fmu_var": "iniDam_in"},
    )

    # === Boolean parameters ===
    permitOccStandby: bool = Field(
        default=True,
        description="Permit occupancy standby mode (FMU: permit_occStandby_in)",
        json_schema_extra={"example": True, "fmu_var": "permit_occStandby_in"},
    )

    # === Hysteresis parameters (Advanced) ===
    tempHysteresis: float = Field(
        default=0.25,
        ge=0,
        description="Near zero temperature difference hysteresis (FMU: dTHys_in) [K]",
        json_schema_extra={"example": 0.25, "unit": "K", "fmu_var": "dTHys_in"},
    )
    loopHysteresis: float = Field(
        default=0.01,
        ge=0,
        le=1,
        description="Loop output hysteresis below which output is seen as zero (FMU: looHys_in) [1]",
        json_schema_extra={"example": 0.01, "unit": "1", "fmu_var": "looHys_in"},
    )
    flowHysteresis: float = Field(
        default=0.003,
        ge=0,
        description="Near zero flow rate hysteresis (FMU: floHys_in) [m3/s]",
        json_schema_extra={"example": 0.003, "unit": "m3/s", "fmu_var": "floHys_in"},
    )
    damperPositionHysteresis: float = Field(
        default=0.005,
        ge=0,
        le=1,
        description="Near zero damper position, below which damper is seen as closed (FMU: damPosHys_in) [1]",
        json_schema_extra={"example": 0.005, "unit": "1", "fmu_var": "damPosHys_in"},
    )
    valvePositionHysteresis: float = Field(
        default=0.005,
        ge=0,
        le=1,
        description="Near zero valve position, below which valve is seen as closed (FMU: valPosHys_in) [1]",
        json_schema_extra={"example": 0.005, "unit": "1", "fmu_var": "valPosHys_in"},
    )


class OverrideMode(IntEnum):
    """Override mode for damper position and flow setpoint."""

    NO_OVERRIDE = 0
    OVERRIDE_ACTIVE = 1


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


class ReheatInputs(BaseModel):
    """Internal model for FMU. All temperatures in Kelvin, validated."""

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

    @classmethod
    def from_request(cls, request: ReheatInputsRequest) -> "ReheatInputs":
        temp_unit = request.temperatureUnit
        airflow_unit = request.airflowUnit
        return cls(
            zoneTemperature=temp_in_kelvin(request.zoneTemperature, temp_unit),
            coolingSetpoint=temp_in_kelvin(request.coolingSetpoint, temp_unit),
            heatingSetpoint=temp_in_kelvin(request.heatingSetpoint, temp_unit),
            dischargeAirTemperature=temp_in_kelvin(
                request.dischargeAirTemperature, temp_unit
            ),
            primaryAirflow=airflow_in_m3_per_s(request.primaryAirflow, airflow_unit),
            supplyAirTemperature=temp_in_kelvin(request.supplyAirTemperature, temp_unit),
            supplyAirTemperatureSetpoint=temp_in_kelvin(
                request.supplyAirTemperatureSetpoint, temp_unit
            ),
            co2Concentration=request.co2Concentration,
            co2Setpoint=request.co2Setpoint,
            fanStatus=request.fanStatus,
            operationMode=request.operationMode,
            hotWaterPlantStatus=request.hotWaterPlantStatus,
            occupancyStatus=request.occupancyStatus,
            windowStatus=request.windowStatus,
            heatingOff=request.heatingOff,
            overrideDamperPosition=int(request.overrideDamperPosition),
            overrideFlowSetpoint=int(request.overrideFlowSetpoint),
        )


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


class CreateInstanceRequest(BaseModel):
    """Request to create a new FMU control sequence instance."""

    instance_id: str = Field(
        ...,
        description="Unique identifier for the FMU instance",
        json_schema_extra={"example": "reheat-zone-1"},
    )
    parameters: ReheatParameters = Field(
        ...,
        description="Parameters for the FMU instance. Call GET /reheat/defaults for default values.",
    )
    inputs: ReheatInputsRequest = Field(
        ...,
        description="Initial input values for the FMU instance.",
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
        description="True if new instance created, False if existing instance was recreated",
        json_schema_extra={"example": True},
    )
    parameters: ReheatParameters = Field(
        ...,
        description="The parameters applied to this instance (user-provided or defaults)",
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
