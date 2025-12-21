"""Constants for G36 VAV Reheat field names.

Single source of truth for field names used in DTOs and category mappings.
"""

from enum import StrEnum

from src.dto.common_dto import InputCategory, OutputCategory

# TODO: Use these constants in DTOs to avoid hardcoding strings in multiple places.

class ReheatInputName(StrEnum):
    """Input field name constants for G36 VAV Reheat."""

    ZONE_TEMPERATURE = "zoneTemperature"
    COOLING_SETPOINT = "coolingSetpoint"
    HEATING_SETPOINT = "heatingSetpoint"
    DISCHARGE_AIR_TEMPERATURE = "dischargeAirTemperature"
    PRIMARY_AIRFLOW = "primaryAirflow"
    SUPPLY_AIR_TEMPERATURE = "supplyAirTemperature"
    SUPPLY_AIR_TEMPERATURE_SETPOINT = "supplyAirTemperatureSetpoint"
    FAN_STATUS = "fanStatus"
    OPERATION_MODE = "operationMode"
    CO2_CONCENTRATION = "co2Concentration"
    CO2_SETPOINT = "co2Setpoint"
    HOT_WATER_PLANT_STATUS = "hotWaterPlantStatus"
    OCCUPANCY_STATUS = "occupancyStatus"
    WINDOW_STATUS = "windowStatus"
    HEATING_OFF = "heatingOff"
    OVERRIDE_DAMPER_POSITION = "overrideDamperPosition"
    OVERRIDE_FLOW_SETPOINT = "overrideFlowSetpoint"


class ReheatParameterName(StrEnum):
    """Parameter field names for G36 VAV Reheat."""

    # Boolean sensor configuration
    HAS_CO2_SENSOR = "hasCO2Sensor"
    HAS_HOT_WATER_COIL = "hasHotWaterCoil"
    HAS_OCCUPANCY_SENSOR = "hasOccupancySensor"
    HAS_WINDOW_SENSOR = "hasWindowSensor"

    # Absolute temperature parameters
    DISCHARGE_AIR_TEMP_MIN = "dischargeAirTempMin"

    # Temperature difference parameters
    MAX_DISCHARGE_TEMP_ABOVE_SETPOINT = "maxDischargeTempAboveSetpoint"
    THRESHOLD_DISCHARGE_TEMP_1 = "thresholdDischargeTemp1"
    THRESHOLD_DISCHARGE_TEMP_2 = "thresholdDischargeTemp2"
    THRESHOLD_TEMP_DIFF = "thresholdTempDiff"
    TWO_TEMP_DIFF = "twoTempDiff"
    TEMP_HYSTERESIS = "tempHysteresis"

    # Airflow parameters
    MIN_AIRFLOW = "minAirflow"
    MAX_COOLING_AIRFLOW = "maxCoolingAirflow"
    MAX_HEATING_AIRFLOW = "maxHeatingAirflow"
    MIN_HEATING_AIRFLOW = "minHeatingAirflow"
    AREA_BREATHING_ZONE_FLOW = "areaBreathingZoneFlow"
    AREA_MIN_FLOW = "areaMinFlow"
    OCC_MIN_FLOW = "occMinFlow"
    POP_BREATHING_ZONE_FLOW = "popBreathingZoneFlow"
    FLOW_HYSTERESIS = "flowHysteresis"


class ReheatOutputName(StrEnum):
    """Output field name constants for G36 VAV Reheat."""

    DAMPER_POSITION = "damperPosition"
    VALVE_POSITION = "valvePosition"
    AIRFLOW_SETPOINT = "airflowSetpoint"
    HEATING_VALVE_REQUEST = "heatingValveRequest"
    ZONE_PRESSURE_REQUEST = "zonePressureRequest"
    ZONE_TEMP_REQUEST = "zoneTempRequest"
    HOT_WATER_PLANT_REQUEST = "hotWaterPlantRequest"
    FLOW_SENSOR_ALARM = "flowSensorAlarm"
    LEAKING_DAMPER_ALARM = "leakingDamperAlarm"
    LEAKING_VALVE_ALARM = "leakingValveAlarm"
    LOW_FLOW_ALARM = "lowFlowAlarm"
    LOW_TEMP_ALARM = "lowTempAlarm"
    MIN_OUTDOOR_AIRFLOW = "minOutdoorAirflow"
    ADJ_AREA_BREATHING_ZONE_FLOW = "adjAreaBreathingZoneFlow"
    ADJ_POP_BREATHING_ZONE_FLOW = "adjPopBreathingZoneFlow"


PARAMETER_TO_REQUIRED_INPUTS: dict[ReheatParameterName, list[ReheatInputName]] = {
    ReheatParameterName.HAS_CO2_SENSOR: [
        ReheatInputName.CO2_CONCENTRATION,
        ReheatInputName.CO2_SETPOINT,
    ],
    ReheatParameterName.HAS_HOT_WATER_COIL: [
        ReheatInputName.HOT_WATER_PLANT_STATUS,
    ],
    ReheatParameterName.HAS_OCCUPANCY_SENSOR: [
        ReheatInputName.OCCUPANCY_STATUS,
    ],
    ReheatParameterName.HAS_WINDOW_SENSOR: [
        ReheatInputName.WINDOW_STATUS,
    ],
}

PARAMETER_TO_REQUIRED_OUTPUTS: dict[ReheatParameterName, list[ReheatOutputName]] = {
    ReheatParameterName.HAS_HOT_WATER_COIL: [
        ReheatOutputName.HEATING_VALVE_REQUEST,
        ReheatOutputName.HOT_WATER_PLANT_REQUEST,
        ReheatOutputName.LOW_TEMP_ALARM,
        ReheatOutputName.LEAKING_VALVE_ALARM,
    ],
}


INPUT_CATEGORIES: dict[InputCategory, list[ReheatInputName]] = {
    InputCategory.ZONE_TEMPERATURE: [
        ReheatInputName.ZONE_TEMPERATURE,
        ReheatInputName.COOLING_SETPOINT,
        ReheatInputName.HEATING_SETPOINT,
    ],
    InputCategory.ZONE_AIR_QUALITY: [
        ReheatInputName.CO2_CONCENTRATION,
        ReheatInputName.CO2_SETPOINT,
    ],
    InputCategory.ZONE_SENSORS: [
        ReheatInputName.OCCUPANCY_STATUS,
        ReheatInputName.WINDOW_STATUS,
    ],
    InputCategory.VAV_TERMINAL: [
        ReheatInputName.DISCHARGE_AIR_TEMPERATURE,
        ReheatInputName.PRIMARY_AIRFLOW,
    ],
    InputCategory.AHU: [
        ReheatInputName.SUPPLY_AIR_TEMPERATURE,
        ReheatInputName.SUPPLY_AIR_TEMPERATURE_SETPOINT,
        ReheatInputName.FAN_STATUS,
    ],
    InputCategory.PLANT: [
        ReheatInputName.HOT_WATER_PLANT_STATUS,
    ],
    InputCategory.CONTROL: [
        ReheatInputName.OPERATION_MODE,
        ReheatInputName.HEATING_OFF,
        ReheatInputName.OVERRIDE_DAMPER_POSITION,
        ReheatInputName.OVERRIDE_FLOW_SETPOINT,
    ],
}


OUTPUT_CATEGORIES: dict[OutputCategory, list[ReheatOutputName]] = {
    OutputCategory.VAV_CONTROL: [
        ReheatOutputName.DAMPER_POSITION,
        ReheatOutputName.VALVE_POSITION,
    ],
    OutputCategory.AHU_REQUESTS: [
        ReheatOutputName.HEATING_VALVE_REQUEST,
        ReheatOutputName.ZONE_PRESSURE_REQUEST,
        ReheatOutputName.ZONE_TEMP_REQUEST,
    ],
    OutputCategory.PLANT_REQUESTS: [
        ReheatOutputName.HOT_WATER_PLANT_REQUEST,
    ],
    OutputCategory.ALARMS: [
        ReheatOutputName.FLOW_SENSOR_ALARM,
        ReheatOutputName.LEAKING_DAMPER_ALARM,
        ReheatOutputName.LEAKING_VALVE_ALARM,
        ReheatOutputName.LOW_FLOW_ALARM,
        ReheatOutputName.LOW_TEMP_ALARM,
    ],
    OutputCategory.MONITORING: [
        ReheatOutputName.AIRFLOW_SETPOINT,
        ReheatOutputName.MIN_OUTDOOR_AIRFLOW,
        ReheatOutputName.ADJ_AREA_BREATHING_ZONE_FLOW,
        ReheatOutputName.ADJ_POP_BREATHING_ZONE_FLOW,
    ],
}

REHEAT_TEMPERATURE_PARAMS: list[ReheatParameterName] = [
    ReheatParameterName.DISCHARGE_AIR_TEMP_MIN,
]

REHEAT_TEMP_DIFF_PARAMS: list[ReheatParameterName] = [
    ReheatParameterName.MAX_DISCHARGE_TEMP_ABOVE_SETPOINT,
    ReheatParameterName.THRESHOLD_DISCHARGE_TEMP_1,
    ReheatParameterName.THRESHOLD_DISCHARGE_TEMP_2,
    ReheatParameterName.THRESHOLD_TEMP_DIFF,
    ReheatParameterName.TWO_TEMP_DIFF,
    ReheatParameterName.TEMP_HYSTERESIS,
]

REHEAT_AIRFLOW_PARAMS: list[ReheatParameterName] = [
    ReheatParameterName.MIN_AIRFLOW,
    ReheatParameterName.MAX_COOLING_AIRFLOW,
    ReheatParameterName.MAX_HEATING_AIRFLOW,
    ReheatParameterName.MIN_HEATING_AIRFLOW,
    ReheatParameterName.AREA_BREATHING_ZONE_FLOW,
    ReheatParameterName.AREA_MIN_FLOW,
    ReheatParameterName.OCC_MIN_FLOW,
    ReheatParameterName.POP_BREATHING_ZONE_FLOW,
    ReheatParameterName.FLOW_HYSTERESIS,
]
