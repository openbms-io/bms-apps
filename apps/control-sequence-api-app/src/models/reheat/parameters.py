"""ReheatParameters domain model for G36 VAV Reheat control sequence."""

from pydantic import BaseModel, Field

from src.models.reheat.enums import ControllerType, VentilationStandard


class ReheatParameters(BaseModel):
    """Configurable parameters for G36 Reheat Terminal control sequence.

    These are FMU parameters (causality=parameter) that can be set before/during init.
    Stored in database.
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
