"""FMU data container for Reheat Terminal."""

from dataclasses import dataclass
from enum import StrEnum

from src.adapters.exceptions import FmuExecutionError
from src.adapters.fmu_data.base import FmuDataType, FmuVariable, OutputSpec
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.calculated_parameters import ReheatCalculatedParameters
from src.models.reheat.outputs import ReheatOutputs
from src.models.reheat.parameters import ReheatParameters


class ReheatInputVar(StrEnum):
    """FMU input variables (causality=input) for Reheat Terminal."""

    ZONE_TEMP = "TZon"
    COOLING_SETPOINT = "TCooSet"
    HEATING_SETPOINT = "THeaSet"
    DISCHARGE_AIR_TEMP = "TDis"
    SUPPLY_AIR_TEMP = "TSup"
    SUPPLY_AIR_TEMP_SETPOINT = "TSupSet"
    PRIMARY_AIRFLOW = "VDis_flow"
    CO2_CONCENTRATION = "ppmCO2"
    CO2_SETPOINT = "ppmCO2Set"
    OPERATION_MODE = "uOpeMod"
    FAN_STATUS = "u1Fan"
    HOT_WATER_PLANT_STATUS = "u1HotPla"
    OCCUPANCY_STATUS = "u1Occ"
    WINDOW_STATUS = "u1Win"
    HEATING_OFF = "uHeaOff"
    OVERRIDE_DAMPER_POSITION = "oveDamPos"
    OVERRIDE_FLOW_SETPOINT = "oveFloSet"


class ReheatOutputVar(StrEnum):
    """FMU output variables (causality=output) for Reheat Terminal."""

    DAMPER_POSITION = "yDam"
    VALVE_POSITION = "yVal"
    AIRFLOW_SETPOINT = "VSet_flow"
    MIN_OA_AIRFLOW = "VMinOA_flow"
    ADJ_AREA_BREATHING_ZONE_FLOW = "VAdjAreBreZon_flow"
    ADJ_POP_BREATHING_ZONE_FLOW = "VAdjPopBreZon_flow"
    FLOW_SENSOR_ALARM = "yFloSenAla"
    HEATING_VALVE_REQUEST = "yHeaValResReq"
    HOT_WATER_PLANT_REQUEST = "yHotWatPlaReq"
    LEAKING_DAMPER_ALARM = "yLeaDamAla"
    LEAKING_VALVE_ALARM = "yLeaValAla"
    LOW_FLOW_ALARM = "yLowFloAla"
    LOW_TEMP_ALARM = "yLowTemAla"
    ZONE_PRESSURE_REQUEST = "yZonPreResReq"
    ZONE_TEMP_REQUEST = "yZonTemResReq"


class ReheatParameterVar(StrEnum):
    """FMU parameters (causality=parameter) for Reheat Terminal."""

    # Sensor configuration (Boolean)
    HAS_CO2_SENSOR = "have_CO2Sen_in"
    HAS_HOT_WATER_COIL = "have_hotWatCoi_in"
    HAS_OCCUPANCY_SENSOR = "have_occSen_in"
    HAS_WINDOW_SENSOR = "have_winSen_in"
    PERMIT_OCC_STANDBY = "permit_occStandby_in"

    # Controller types (Enumeration)
    CONTROLLER_TYPE_DAMPER = "controllerTypeDam_in"
    CONTROLLER_TYPE_VALVE = "controllerTypeVal_in"
    VENTILATION_STANDARD = "venStd_in"

    # Airflow parameters (including design minimum)
    MIN_AIRFLOW = "VMin_flow_in"
    MAX_COOLING_AIRFLOW = "VCooMax_flow_in"
    MAX_HEATING_AIRFLOW = "VHeaMax_flow_in"
    MIN_HEATING_AIRFLOW = "VHeaMin_flow_in"
    AREA_BREATHING_ZONE_FLOW = "VAreBreZon_flow_in"
    AREA_MIN_FLOW = "VAreMin_flow_in"
    OCC_MIN_FLOW = "VOccMin_flow_in"
    POP_BREATHING_ZONE_FLOW = "VPopBreZon_flow_in"

    # Temperature parameters
    DISCHARGE_AIR_TEMP_MIN = "TDisMin_in"
    MAX_DISCHARGE_TEMP_ABOVE_SETPOINT = "dTDisZonSetMax_in"

    # Controller gains
    COOLING_CONTROLLER_GAIN = "kCooCon_in"
    HEATING_CONTROLLER_GAIN = "kHeaCon_in"
    DAMPER_CONTROLLER_GAIN = "kDam_in"
    VALVE_CONTROLLER_GAIN = "kVal_in"

    # Controller time constants
    DAMPER_DERIVATIVE_TIME = "TdDam_in"
    VALVE_DERIVATIVE_TIME = "TdVal_in"
    COOLING_INTEGRATOR_TIME = "TiCooCon_in"
    DAMPER_INTEGRATOR_TIME = "TiDam_in"
    HEATING_INTEGRATOR_TIME = "TiHeaCon_in"
    VALVE_INTEGRATOR_TIME = "TiVal_in"

    # Duration/timing parameters
    CHANGE_RATE = "chaRat_in"
    DURATION_DISCHARGE_AIR = "durTimDisAir_in"
    DURATION_FLOW = "durTimFlo_in"
    DURATION_TEMP = "durTimTem_in"
    MAX_SUPPRESSION_TIME = "maxSupTim_in"
    SAMPLE_PERIOD = "samplePeriod_in"

    # Alarm timing thresholds
    FAN_OFF_TIME = "fanOffTim_in"
    LEAK_FLOW_TIME = "leaFloTim_in"
    LOW_FLOW_TIME = "lowFloTim_in"
    LOW_TEMP_TIME = "lowTemTim_in"
    VALVE_CLOSE_TIME = "valCloTim_in"
    TIME_CHECK = "timChe_in"
    STARTUP_TIME = "staTim_in"

    # Temperature thresholds
    THRESHOLD_DISCHARGE_TEMP_1 = "thrTDis_1_in"
    THRESHOLD_DISCHARGE_TEMP_2 = "thrTDis_2_in"
    THRESHOLD_TEMP_DIFF = "thrTemDif_in"
    TWO_TEMP_DIFF = "twoTemDif_in"

    # Importance multipliers
    HOT_WATER_RESET_MULTIPLIER = "hotWatRes_in"
    STATIC_PRESSURE_MULTIPLIER = "staPreMul_in"

    # Zone distribution effectiveness
    ZONE_DIST_EFF_COOL = "zonDisEff_cool_in"
    ZONE_DIST_EFF_HEAT = "zonDisEff_heat_in"

    # Initial values
    INITIAL_DAMPER_POSITION = "iniDam_in"

    # Hysteresis parameters (Advanced)
    TEMP_HYSTERESIS = "dTHys_in"
    LOOP_HYSTERESIS = "looHys_in"
    FLOW_HYSTERESIS = "floHys_in"
    DAMPER_POSITION_HYSTERESIS = "damPosHys_in"
    VALVE_POSITION_HYSTERESIS = "valPosHys_in"


class ReheatCalcParamVar(StrEnum):
    """FMU calculated parameters (causality=calculatedParameter) for Reheat Terminal.

    These are read-only values computed by the FMU from the configurable parameters.
    They mirror the _in parameters but without the suffix.
    """

    MIN_AIRFLOW = "VMin_flow"
    TEMP_HYSTERESIS = "dTHys"
    DAMPER_POSITION_HYSTERESIS = "damPosHys"
    FLOW_HYSTERESIS = "floHys"
    LOOP_HYSTERESIS = "looHys"
    VALVE_POSITION_HYSTERESIS = "valPosHys"
    HAS_CO2_SENSOR = "have_CO2Sen"
    HAS_HOT_WATER_COIL = "have_hotWatCoi"
    HAS_OCCUPANCY_SENSOR = "have_occSen"
    HAS_WINDOW_SENSOR = "have_winSen"
    CONTROLLER_TYPE_DAMPER = "controllerTypeDam"
    CONTROLLER_TYPE_VALVE = "controllerTypeVal"
    VENTILATION_STANDARD = "venStd"


@dataclass(frozen=True, slots=True)
class ReheatFMUData:
    """Immutable FMU data container for Reheat Terminal."""

    inputs: ReheatInputs
    parameters: ReheatParameters | None = None

    @property
    def configuration_variables(self) -> list[FmuVariable]:
        if self.parameters is None:
            return []
        p = self.parameters
        return [
            # Sensor configuration (Boolean)
            FmuVariable(ReheatParameterVar.HAS_CO2_SENSOR, bool(p.hasCO2Sensor)),
            FmuVariable(ReheatParameterVar.HAS_HOT_WATER_COIL, bool(p.hasHotWaterCoil)),
            FmuVariable(ReheatParameterVar.HAS_OCCUPANCY_SENSOR, bool(p.hasOccupancySensor)),
            FmuVariable(ReheatParameterVar.HAS_WINDOW_SENSOR, bool(p.hasWindowSensor)),
            FmuVariable(ReheatParameterVar.PERMIT_OCC_STANDBY, bool(p.permitOccStandby)),
            # Controller types (Enumeration)
            FmuVariable(ReheatParameterVar.CONTROLLER_TYPE_DAMPER, int(p.controllerTypeDamper)),
            FmuVariable(ReheatParameterVar.CONTROLLER_TYPE_VALVE, int(p.controllerTypeValve)),
            FmuVariable(ReheatParameterVar.VENTILATION_STANDARD, int(p.ventilationStandard)),
            # Airflow parameters
            FmuVariable(ReheatParameterVar.MIN_AIRFLOW, float(p.minAirflow)),
            FmuVariable(ReheatParameterVar.MAX_COOLING_AIRFLOW, float(p.maxCoolingAirflow)),
            FmuVariable(ReheatParameterVar.MAX_HEATING_AIRFLOW, float(p.maxHeatingAirflow)),
            FmuVariable(ReheatParameterVar.MIN_HEATING_AIRFLOW, float(p.minHeatingAirflow)),
            FmuVariable(ReheatParameterVar.AREA_BREATHING_ZONE_FLOW, float(p.areaBreathingZoneFlow)),
            FmuVariable(ReheatParameterVar.AREA_MIN_FLOW, float(p.areaMinFlow)),
            FmuVariable(ReheatParameterVar.OCC_MIN_FLOW, float(p.occMinFlow)),
            FmuVariable(ReheatParameterVar.POP_BREATHING_ZONE_FLOW, float(p.popBreathingZoneFlow)),
            # Temperature parameters
            FmuVariable(ReheatParameterVar.DISCHARGE_AIR_TEMP_MIN, float(p.dischargeAirTempMin)),
            FmuVariable(ReheatParameterVar.MAX_DISCHARGE_TEMP_ABOVE_SETPOINT, float(p.maxDischargeTempAboveSetpoint)),
            # Controller gains
            FmuVariable(ReheatParameterVar.COOLING_CONTROLLER_GAIN, float(p.coolingControllerGain)),
            FmuVariable(ReheatParameterVar.HEATING_CONTROLLER_GAIN, float(p.heatingControllerGain)),
            FmuVariable(ReheatParameterVar.DAMPER_CONTROLLER_GAIN, float(p.damperControllerGain)),
            FmuVariable(ReheatParameterVar.VALVE_CONTROLLER_GAIN, float(p.valveControllerGain)),
            # Controller time constants
            FmuVariable(ReheatParameterVar.DAMPER_DERIVATIVE_TIME, float(p.damperDerivativeTime)),
            FmuVariable(ReheatParameterVar.VALVE_DERIVATIVE_TIME, float(p.valveDerivativeTime)),
            FmuVariable(ReheatParameterVar.COOLING_INTEGRATOR_TIME, float(p.coolingIntegratorTime)),
            FmuVariable(ReheatParameterVar.DAMPER_INTEGRATOR_TIME, float(p.damperIntegratorTime)),
            FmuVariable(ReheatParameterVar.HEATING_INTEGRATOR_TIME, float(p.heatingIntegratorTime)),
            FmuVariable(ReheatParameterVar.VALVE_INTEGRATOR_TIME, float(p.valveIntegratorTime)),
            # Duration/timing parameters
            FmuVariable(ReheatParameterVar.CHANGE_RATE, float(p.changeRate)),
            FmuVariable(ReheatParameterVar.DURATION_DISCHARGE_AIR, float(p.durationDischargeAir)),
            FmuVariable(ReheatParameterVar.DURATION_FLOW, float(p.durationFlow)),
            FmuVariable(ReheatParameterVar.DURATION_TEMP, float(p.durationTemp)),
            FmuVariable(ReheatParameterVar.MAX_SUPPRESSION_TIME, float(p.maxSuppressionTime)),
            FmuVariable(ReheatParameterVar.SAMPLE_PERIOD, float(p.samplePeriod)),
            # Alarm timing thresholds
            FmuVariable(ReheatParameterVar.FAN_OFF_TIME, float(p.fanOffTime)),
            FmuVariable(ReheatParameterVar.LEAK_FLOW_TIME, float(p.leakFlowTime)),
            FmuVariable(ReheatParameterVar.LOW_FLOW_TIME, float(p.lowFlowTime)),
            FmuVariable(ReheatParameterVar.LOW_TEMP_TIME, float(p.lowTempTime)),
            FmuVariable(ReheatParameterVar.VALVE_CLOSE_TIME, float(p.valveCloseTime)),
            FmuVariable(ReheatParameterVar.TIME_CHECK, float(p.timeCheck)),
            FmuVariable(ReheatParameterVar.STARTUP_TIME, float(p.startupTime)),
            # Temperature thresholds
            FmuVariable(ReheatParameterVar.THRESHOLD_DISCHARGE_TEMP_1, float(p.thresholdDischargeTemp1)),
            FmuVariable(ReheatParameterVar.THRESHOLD_DISCHARGE_TEMP_2, float(p.thresholdDischargeTemp2)),
            FmuVariable(ReheatParameterVar.THRESHOLD_TEMP_DIFF, float(p.thresholdTempDiff)),
            FmuVariable(ReheatParameterVar.TWO_TEMP_DIFF, float(p.twoTempDiff)),
            # Importance multipliers
            FmuVariable(ReheatParameterVar.HOT_WATER_RESET_MULTIPLIER, float(p.hotWaterResetMultiplier)),
            FmuVariable(ReheatParameterVar.STATIC_PRESSURE_MULTIPLIER, float(p.staticPressureMultiplier)),
            # Zone distribution effectiveness
            FmuVariable(ReheatParameterVar.ZONE_DIST_EFF_COOL, float(p.zoneDistEffCooling)),
            FmuVariable(ReheatParameterVar.ZONE_DIST_EFF_HEAT, float(p.zoneDistEffHeating)),
            # Initial values
            FmuVariable(ReheatParameterVar.INITIAL_DAMPER_POSITION, float(p.initialDamperPosition)),
            # Hysteresis parameters (Advanced)
            FmuVariable(ReheatParameterVar.TEMP_HYSTERESIS, float(p.tempHysteresis)),
            FmuVariable(ReheatParameterVar.LOOP_HYSTERESIS, float(p.loopHysteresis)),
            FmuVariable(ReheatParameterVar.FLOW_HYSTERESIS, float(p.flowHysteresis)),
            FmuVariable(ReheatParameterVar.DAMPER_POSITION_HYSTERESIS, float(p.damperPositionHysteresis)),
            FmuVariable(ReheatParameterVar.VALVE_POSITION_HYSTERESIS, float(p.valvePositionHysteresis)),
        ]

    @property
    def input_variables(self) -> list[FmuVariable]:
        i = self.inputs
        return [
            FmuVariable(ReheatInputVar.ZONE_TEMP, float(i.zoneTemperature)),
            FmuVariable(ReheatInputVar.COOLING_SETPOINT, float(i.coolingSetpoint)),
            FmuVariable(ReheatInputVar.HEATING_SETPOINT, float(i.heatingSetpoint)),
            FmuVariable(ReheatInputVar.DISCHARGE_AIR_TEMP, float(i.dischargeAirTemperature)),
            FmuVariable(ReheatInputVar.PRIMARY_AIRFLOW, float(i.primaryAirflow)),
            FmuVariable(ReheatInputVar.SUPPLY_AIR_TEMP, float(i.supplyAirTemperature)),
            FmuVariable(ReheatInputVar.SUPPLY_AIR_TEMP_SETPOINT, float(i.supplyAirTemperatureSetpoint)),
            FmuVariable(ReheatInputVar.CO2_CONCENTRATION, float(i.co2Concentration)),
            FmuVariable(ReheatInputVar.CO2_SETPOINT, float(i.co2Setpoint)),
            FmuVariable(ReheatInputVar.FAN_STATUS, bool(i.fanStatus)),
            FmuVariable(ReheatInputVar.OPERATION_MODE, int(i.operationMode)),
            FmuVariable(ReheatInputVar.HOT_WATER_PLANT_STATUS, bool(i.hotWaterPlantStatus)),
            FmuVariable(ReheatInputVar.OCCUPANCY_STATUS, bool(i.occupancyStatus)),
            FmuVariable(ReheatInputVar.WINDOW_STATUS, bool(i.windowStatus)),
            FmuVariable(ReheatInputVar.HEATING_OFF, bool(i.heatingOff)),
            FmuVariable(ReheatInputVar.OVERRIDE_DAMPER_POSITION, int(i.overrideDamperPosition)),
            FmuVariable(ReheatInputVar.OVERRIDE_FLOW_SETPOINT, int(i.overrideFlowSetpoint)),
        ]

    @staticmethod
    def output_variable_specs() -> list[OutputSpec]:
        return [
            OutputSpec(ReheatOutputVar.DAMPER_POSITION, FmuDataType.REAL),
            OutputSpec(ReheatOutputVar.VALVE_POSITION, FmuDataType.REAL),
            OutputSpec(ReheatOutputVar.AIRFLOW_SETPOINT, FmuDataType.REAL),
            OutputSpec(ReheatOutputVar.MIN_OA_AIRFLOW, FmuDataType.REAL),
            OutputSpec(ReheatOutputVar.ADJ_AREA_BREATHING_ZONE_FLOW, FmuDataType.REAL),
            OutputSpec(ReheatOutputVar.ADJ_POP_BREATHING_ZONE_FLOW, FmuDataType.REAL),
            OutputSpec(ReheatOutputVar.FLOW_SENSOR_ALARM, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.HEATING_VALVE_REQUEST, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.HOT_WATER_PLANT_REQUEST, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.LEAKING_DAMPER_ALARM, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.LEAKING_VALVE_ALARM, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.LOW_FLOW_ALARM, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.LOW_TEMP_ALARM, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.ZONE_PRESSURE_REQUEST, FmuDataType.INTEGER),
            OutputSpec(ReheatOutputVar.ZONE_TEMP_REQUEST, FmuDataType.INTEGER),
        ]

    @staticmethod
    def calculated_parameter_specs() -> list[OutputSpec]:
        return [
            OutputSpec(ReheatCalcParamVar.MIN_AIRFLOW, FmuDataType.REAL),
            OutputSpec(ReheatCalcParamVar.TEMP_HYSTERESIS, FmuDataType.REAL),
            OutputSpec(ReheatCalcParamVar.DAMPER_POSITION_HYSTERESIS, FmuDataType.REAL),
            OutputSpec(ReheatCalcParamVar.FLOW_HYSTERESIS, FmuDataType.REAL),
            OutputSpec(ReheatCalcParamVar.LOOP_HYSTERESIS, FmuDataType.REAL),
            OutputSpec(ReheatCalcParamVar.VALVE_POSITION_HYSTERESIS, FmuDataType.REAL),
            OutputSpec(ReheatCalcParamVar.HAS_CO2_SENSOR, FmuDataType.BOOLEAN),
            OutputSpec(ReheatCalcParamVar.HAS_HOT_WATER_COIL, FmuDataType.BOOLEAN),
            OutputSpec(ReheatCalcParamVar.HAS_OCCUPANCY_SENSOR, FmuDataType.BOOLEAN),
            OutputSpec(ReheatCalcParamVar.HAS_WINDOW_SENSOR, FmuDataType.BOOLEAN),
            OutputSpec(ReheatCalcParamVar.CONTROLLER_TYPE_DAMPER, FmuDataType.INTEGER),
            OutputSpec(ReheatCalcParamVar.CONTROLLER_TYPE_VALVE, FmuDataType.INTEGER),
            OutputSpec(ReheatCalcParamVar.VENTILATION_STANDARD, FmuDataType.INTEGER),
        ]

    @staticmethod
    def create_outputs(values: dict[str, float | bool | int]) -> ReheatOutputs:
        try:
            return ReheatOutputs(
                damperPosition=float(values[ReheatOutputVar.DAMPER_POSITION]),
                valvePosition=float(values[ReheatOutputVar.VALVE_POSITION]),
                airflowSetpoint=float(values[ReheatOutputVar.AIRFLOW_SETPOINT]),
                minOutdoorAirflow=float(values[ReheatOutputVar.MIN_OA_AIRFLOW]),
                adjAreaBreathingZoneFlow=float(values[ReheatOutputVar.ADJ_AREA_BREATHING_ZONE_FLOW]),
                adjPopBreathingZoneFlow=float(values[ReheatOutputVar.ADJ_POP_BREATHING_ZONE_FLOW]),
                flowSensorAlarm=int(values[ReheatOutputVar.FLOW_SENSOR_ALARM]),
                heatingValveRequest=int(values[ReheatOutputVar.HEATING_VALVE_REQUEST]),
                hotWaterPlantRequest=int(values[ReheatOutputVar.HOT_WATER_PLANT_REQUEST]),
                leakingDamperAlarm=int(values[ReheatOutputVar.LEAKING_DAMPER_ALARM]),
                leakingValveAlarm=int(values[ReheatOutputVar.LEAKING_VALVE_ALARM]),
                lowFlowAlarm=int(values[ReheatOutputVar.LOW_FLOW_ALARM]),
                lowTempAlarm=int(values[ReheatOutputVar.LOW_TEMP_ALARM]),
                zonePressureRequest=int(values[ReheatOutputVar.ZONE_PRESSURE_REQUEST]),
                zoneTempRequest=int(values[ReheatOutputVar.ZONE_TEMP_REQUEST]),
            )
        except KeyError as e:
            raise FmuExecutionError(f"Missing expected FMU output: {e}") from e

    @staticmethod
    def create_calculated_parameters(values: dict[str, float | bool | int]) -> ReheatCalculatedParameters:
        try:
            return ReheatCalculatedParameters(
                minAirflow=float(values[ReheatCalcParamVar.MIN_AIRFLOW]),
                tempHysteresis=float(values[ReheatCalcParamVar.TEMP_HYSTERESIS]),
                damperPositionHysteresis=float(values[ReheatCalcParamVar.DAMPER_POSITION_HYSTERESIS]),
                flowHysteresis=float(values[ReheatCalcParamVar.FLOW_HYSTERESIS]),
                loopHysteresis=float(values[ReheatCalcParamVar.LOOP_HYSTERESIS]),
                valvePositionHysteresis=float(values[ReheatCalcParamVar.VALVE_POSITION_HYSTERESIS]),
                hasCO2Sensor=bool(values[ReheatCalcParamVar.HAS_CO2_SENSOR]),
                hasHotWaterCoil=bool(values[ReheatCalcParamVar.HAS_HOT_WATER_COIL]),
                hasOccupancySensor=bool(values[ReheatCalcParamVar.HAS_OCCUPANCY_SENSOR]),
                hasWindowSensor=bool(values[ReheatCalcParamVar.HAS_WINDOW_SENSOR]),
                controllerTypeDamper=int(values[ReheatCalcParamVar.CONTROLLER_TYPE_DAMPER]),
                controllerTypeValve=int(values[ReheatCalcParamVar.CONTROLLER_TYPE_VALVE]),
                ventilationStandard=int(values[ReheatCalcParamVar.VENTILATION_STANDARD]),
            )
        except KeyError as e:
            raise FmuExecutionError(f"Missing expected FMU calculated parameter: {e}") from e

    @staticmethod
    def required_input_names() -> list[str]:
        return [
            ReheatInputVar.ZONE_TEMP,
            ReheatInputVar.COOLING_SETPOINT,
            ReheatInputVar.HEATING_SETPOINT,
            ReheatInputVar.DISCHARGE_AIR_TEMP,
            ReheatInputVar.PRIMARY_AIRFLOW,
            ReheatInputVar.SUPPLY_AIR_TEMP,
            ReheatInputVar.SUPPLY_AIR_TEMP_SETPOINT,
            ReheatInputVar.CO2_CONCENTRATION,
            ReheatInputVar.CO2_SETPOINT,
            ReheatInputVar.FAN_STATUS,
            ReheatInputVar.OPERATION_MODE,
            ReheatInputVar.HOT_WATER_PLANT_STATUS,
            ReheatInputVar.OCCUPANCY_STATUS,
            ReheatInputVar.WINDOW_STATUS,
            ReheatInputVar.HEATING_OFF,
            ReheatInputVar.OVERRIDE_DAMPER_POSITION,
            ReheatInputVar.OVERRIDE_FLOW_SETPOINT,
        ]
