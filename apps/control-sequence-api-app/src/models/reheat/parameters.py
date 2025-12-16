"""ReheatParameters domain model for G36 VAV Reheat control sequence."""

from pydantic import BaseModel, Field

from src.models.reheat.enums import ControllerType, ParameterCategory, VentilationStandard
from src.utils.unit_conversion import AirflowUnit, TemperatureUnit
from src.dto.reheat_constants import (
    ReheatInputName,
    ReheatParameterName,
    PARAMETER_TO_REQUIRED_INPUTS,
)


class ReheatParameters(BaseModel):
    """Configurable parameters for G36 Reheat Terminal control sequence.

    These are FMU parameters (causality=parameter) that can be set before/during init.
    Stored in database.
    """

    @classmethod
    def get_categories(cls) -> dict[ParameterCategory, list[str]]:
        """Build categories mapping from field metadata."""
        categories: dict[ParameterCategory, list[str]] = {}
        for field_name, field_info in cls.model_fields.items():
            extra = field_info.json_schema_extra
            if extra and isinstance(extra, dict):
                category = extra.get("category")
                if category and isinstance(category, ParameterCategory):
                    if category not in categories:
                        categories[category] = []
                    categories[category].append(field_name)
        return categories

    @classmethod
    def get_parameter_to_required_inputs(
        cls,
    ) -> dict[ReheatParameterName, list[ReheatInputName]]:
        """Return mapping of parameters to their required inputs."""
        return PARAMETER_TO_REQUIRED_INPUTS

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

    # === Temperature parameters ===
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
