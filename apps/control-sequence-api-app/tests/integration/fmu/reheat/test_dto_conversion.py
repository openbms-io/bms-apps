import pytest

from src.adapters.fmu_data.reheat_fmu_data import (
    ReheatCalcParamVar,
    ReheatFMUData,
    ReheatInputVar,
    ReheatOutputVar,
    ReheatParameterVar,
)
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.parameters import ReheatParameters


class TestInputVariablesProperty:

    def test_input_variables_returns_17_items(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        assert len(fmu_data.input_variables) == 17

    def test_input_variables_all_have_names(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        for var in fmu_data.input_variables:
            assert var.name is not None
            assert len(var.name) > 0

    def test_input_variables_all_have_values(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        for var in fmu_data.input_variables:
            assert var.value is not None

    def test_input_variables_contain_expected_names(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        names = {var.name for var in fmu_data.input_variables}

        expected_names = {
            ReheatInputVar.ZONE_TEMP,
            ReheatInputVar.COOLING_SETPOINT,
            ReheatInputVar.HEATING_SETPOINT,
            ReheatInputVar.DISCHARGE_AIR_TEMP,
            ReheatInputVar.SUPPLY_AIR_TEMP,
            ReheatInputVar.SUPPLY_AIR_TEMP_SETPOINT,
            ReheatInputVar.PRIMARY_AIRFLOW,
            ReheatInputVar.CO2_CONCENTRATION,
            ReheatInputVar.CO2_SETPOINT,
            ReheatInputVar.OPERATION_MODE,
            ReheatInputVar.FAN_STATUS,
            ReheatInputVar.HOT_WATER_PLANT_STATUS,
            ReheatInputVar.OCCUPANCY_STATUS,
            ReheatInputVar.WINDOW_STATUS,
            ReheatInputVar.HEATING_OFF,
            ReheatInputVar.OVERRIDE_DAMPER_POSITION,
            ReheatInputVar.OVERRIDE_FLOW_SETPOINT,
        }

        for expected in expected_names:
            assert expected.value in names, f"Missing input: {expected}"


class TestConfigurationVariablesProperty:

    def test_configuration_variables_returns_55_items_with_params(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        assert len(fmu_data.configuration_variables) == 55

    def test_configuration_variables_returns_default_params_when_default(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        assert len(fmu_data.configuration_variables) == 55

    def test_configuration_variables_all_have_names(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        for var in fmu_data.configuration_variables:
            assert var.name is not None
            assert len(var.name) > 0

    def test_configuration_variables_contain_expected_names(
        self, base_inputs: ReheatInputs, base_parameters: ReheatParameters
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=base_parameters)

        names = {var.name for var in fmu_data.configuration_variables}

        sample_expected = [
            ReheatParameterVar.MAX_COOLING_AIRFLOW,
            ReheatParameterVar.MAX_HEATING_AIRFLOW,
            ReheatParameterVar.MIN_HEATING_AIRFLOW,
            ReheatParameterVar.COOLING_CONTROLLER_GAIN,
            ReheatParameterVar.DAMPER_INTEGRATOR_TIME,
            ReheatParameterVar.PERMIT_OCC_STANDBY,
        ]

        for expected in sample_expected:
            assert expected.value in names, f"Missing parameter: {expected}"


class TestOutputVariableSpecs:

    def test_output_specs_returns_15_items(self):
        specs = ReheatFMUData.output_variable_specs()

        assert len(specs) == 15

    def test_output_specs_all_have_names(self):
        specs = ReheatFMUData.output_variable_specs()

        for spec in specs:
            assert spec.name is not None
            assert len(spec.name) > 0

    def test_output_specs_all_have_data_types(self):
        specs = ReheatFMUData.output_variable_specs()

        for spec in specs:
            assert spec.data_type is not None

    def test_output_specs_contain_expected_names(self):
        specs = ReheatFMUData.output_variable_specs()

        names = {spec.name for spec in specs}

        expected_names = {
            ReheatOutputVar.DAMPER_POSITION,
            ReheatOutputVar.VALVE_POSITION,
            ReheatOutputVar.AIRFLOW_SETPOINT,
            ReheatOutputVar.MIN_OA_AIRFLOW,
            ReheatOutputVar.ADJ_AREA_BREATHING_ZONE_FLOW,
            ReheatOutputVar.ADJ_POP_BREATHING_ZONE_FLOW,
            ReheatOutputVar.FLOW_SENSOR_ALARM,
            ReheatOutputVar.HEATING_VALVE_REQUEST,
            ReheatOutputVar.HOT_WATER_PLANT_REQUEST,
            ReheatOutputVar.LEAKING_DAMPER_ALARM,
            ReheatOutputVar.LEAKING_VALVE_ALARM,
            ReheatOutputVar.LOW_FLOW_ALARM,
            ReheatOutputVar.LOW_TEMP_ALARM,
            ReheatOutputVar.ZONE_PRESSURE_REQUEST,
            ReheatOutputVar.ZONE_TEMP_REQUEST,
        }

        for expected in expected_names:
            assert expected.value in names, f"Missing output spec: {expected}"


class TestCalculatedParameterSpecs:

    def test_calculated_parameter_specs_returns_13_items(self):
        specs = ReheatFMUData.calculated_parameter_specs()

        assert len(specs) == 13

    def test_calculated_parameter_specs_all_have_names(self):
        specs = ReheatFMUData.calculated_parameter_specs()

        for spec in specs:
            assert spec.name is not None
            assert len(spec.name) > 0

    def test_calculated_parameter_specs_all_have_data_types(self):
        specs = ReheatFMUData.calculated_parameter_specs()

        for spec in specs:
            assert spec.data_type is not None

    def test_calculated_parameter_specs_contain_expected_names(self):
        specs = ReheatFMUData.calculated_parameter_specs()

        names = {spec.name for spec in specs}

        expected_names = {
            ReheatCalcParamVar.MIN_AIRFLOW,
            ReheatCalcParamVar.TEMP_HYSTERESIS,
            ReheatCalcParamVar.DAMPER_POSITION_HYSTERESIS,
            ReheatCalcParamVar.FLOW_HYSTERESIS,
            ReheatCalcParamVar.LOOP_HYSTERESIS,
            ReheatCalcParamVar.VALVE_POSITION_HYSTERESIS,
            ReheatCalcParamVar.HAS_CO2_SENSOR,
            ReheatCalcParamVar.HAS_HOT_WATER_COIL,
            ReheatCalcParamVar.HAS_OCCUPANCY_SENSOR,
            ReheatCalcParamVar.HAS_WINDOW_SENSOR,
            ReheatCalcParamVar.CONTROLLER_TYPE_DAMPER,
            ReheatCalcParamVar.CONTROLLER_TYPE_VALVE,
            ReheatCalcParamVar.VENTILATION_STANDARD,
        }

        for expected in expected_names:
            assert expected.value in names, f"Missing calc param spec: {expected}"


class TestRequiredInputNames:

    def test_required_input_names_returns_17_items(self):
        names = ReheatFMUData.required_input_names()

        assert len(names) == 17

    def test_required_input_names_all_strings(self):
        names = ReheatFMUData.required_input_names()

        for name in names:
            assert isinstance(name, str)
            assert len(name) > 0


class TestCreateOutputs:

    def test_create_outputs_maps_all_fields(self):
        raw_values = {
            ReheatOutputVar.DAMPER_POSITION.value: 0.5,
            ReheatOutputVar.VALVE_POSITION.value: 0.3,
            ReheatOutputVar.AIRFLOW_SETPOINT.value: 0.4,
            ReheatOutputVar.MIN_OA_AIRFLOW.value: 0.1,
            ReheatOutputVar.ADJ_AREA_BREATHING_ZONE_FLOW.value: 0.05,
            ReheatOutputVar.ADJ_POP_BREATHING_ZONE_FLOW.value: 0.03,
            ReheatOutputVar.FLOW_SENSOR_ALARM.value: 0,
            ReheatOutputVar.HEATING_VALVE_REQUEST.value: 1,
            ReheatOutputVar.HOT_WATER_PLANT_REQUEST.value: 0,
            ReheatOutputVar.LEAKING_DAMPER_ALARM.value: 0,
            ReheatOutputVar.LEAKING_VALVE_ALARM.value: 0,
            ReheatOutputVar.LOW_FLOW_ALARM.value: 0,
            ReheatOutputVar.LOW_TEMP_ALARM.value: 0,
            ReheatOutputVar.ZONE_PRESSURE_REQUEST.value: 2,
            ReheatOutputVar.ZONE_TEMP_REQUEST.value: 1,
        }

        outputs = ReheatFMUData.create_outputs(raw_values)

        assert outputs.damperPosition == 0.5
        assert outputs.valvePosition == 0.3
        assert outputs.airflowSetpoint == 0.4
        assert outputs.minOutdoorAirflow == 0.1
        assert outputs.adjAreaBreathingZoneFlow == 0.05
        assert outputs.adjPopBreathingZoneFlow == 0.03
        assert outputs.flowSensorAlarm == 0
        assert outputs.heatingValveRequest == 1
        assert outputs.hotWaterPlantRequest == 0
        assert outputs.leakingDamperAlarm == 0
        assert outputs.leakingValveAlarm == 0
        assert outputs.lowFlowAlarm == 0
        assert outputs.lowTempAlarm == 0
        assert outputs.zonePressureRequest == 2
        assert outputs.zoneTempRequest == 1


class TestCreateCalculatedParameters:

    def test_create_calculated_parameters_maps_all_fields(self):
        raw_values = {
            ReheatCalcParamVar.MIN_AIRFLOW.value: 0.15,
            ReheatCalcParamVar.TEMP_HYSTERESIS.value: 0.5,
            ReheatCalcParamVar.DAMPER_POSITION_HYSTERESIS.value: 0.05,
            ReheatCalcParamVar.FLOW_HYSTERESIS.value: 0.02,
            ReheatCalcParamVar.LOOP_HYSTERESIS.value: 0.04,
            ReheatCalcParamVar.VALVE_POSITION_HYSTERESIS.value: 0.05,
            ReheatCalcParamVar.HAS_CO2_SENSOR.value: True,
            ReheatCalcParamVar.HAS_HOT_WATER_COIL.value: True,
            ReheatCalcParamVar.HAS_OCCUPANCY_SENSOR.value: False,
            ReheatCalcParamVar.HAS_WINDOW_SENSOR.value: False,
            ReheatCalcParamVar.CONTROLLER_TYPE_DAMPER.value: 2,
            ReheatCalcParamVar.CONTROLLER_TYPE_VALVE.value: 2,
            ReheatCalcParamVar.VENTILATION_STANDARD.value: 1,
        }

        calc_params = ReheatFMUData.create_calculated_parameters(raw_values)

        assert calc_params.minAirflow == 0.15
        assert calc_params.tempHysteresis == 0.5
        assert calc_params.damperPositionHysteresis == 0.05
        assert calc_params.flowHysteresis == 0.02
        assert calc_params.loopHysteresis == 0.04
        assert calc_params.valvePositionHysteresis == 0.05
        assert calc_params.hasCO2Sensor is True
        assert calc_params.hasHotWaterCoil is True
        assert calc_params.hasOccupancySensor is False
        assert calc_params.hasWindowSensor is False
        assert calc_params.controllerTypeDamper == 2
        assert calc_params.controllerTypeValve == 2
        assert calc_params.ventilationStandard == 1
