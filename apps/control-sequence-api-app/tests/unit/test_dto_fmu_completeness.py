"""DTO-to-FMU field completeness tests.

Tests verify that every DTO field has a corresponding FMU mapping using fmu_var metadata.
This is a fail-fast mechanism: if a DTO field is added without a corresponding FMU mapping,
these tests will fail immediately.

Acceptance Criteria #6: DTO-to-FMU mapping verified with unit tests
"""

import pytest
from pydantic import BaseModel

from src.adapters.fmu_data.reheat_fmu_data import (
    ReheatCalcParamVar,
    ReheatFMUData,
    ReheatInputVar,
    ReheatOutputVar,
    ReheatParameterVar,
)
from src.models.reheat.calculated_parameters import ReheatCalculatedParameters
from src.models.reheat.enums import OperationMode
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.outputs import ReheatOutputs
from src.models.reheat.parameters import ReheatParameters
from src.utils.unit_conversion import TemperatureUnit


def get_fmu_var_metadata(model: type[BaseModel]) -> dict[str, str]:
    """Extract fmu_var metadata from all fields of a Pydantic model."""
    fmu_vars = {}
    for field_name, field_info in model.model_fields.items():
        if field_info.json_schema_extra and "fmu_var" in field_info.json_schema_extra:
            fmu_vars[field_name] = field_info.json_schema_extra["fmu_var"]
    return fmu_vars


class TestReheatInputsFmuMapping:

    def test_all_inputs_have_fmu_var_metadata(self):
        fmu_vars = get_fmu_var_metadata(ReheatInputs)

        for field_name in ReheatInputs.model_fields:
            assert field_name in fmu_vars, (
                f"ReheatInputs.{field_name} missing fmu_var metadata"
            )

    def test_all_input_fmu_vars_exist_in_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatInputs)
        enum_values = {e.value for e in ReheatInputVar}

        for field_name, fmu_var in fmu_vars.items():
            assert fmu_var in enum_values, (
                f"ReheatInputs.{field_name} has fmu_var='{fmu_var}' "
                f"but it's not in ReheatInputVar enum"
            )

    def test_input_field_count_matches_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatInputs)
        enum_count = len(ReheatInputVar)

        assert len(fmu_vars) == enum_count, (
            f"ReheatInputs has {len(fmu_vars)} fmu_var mappings "
            f"but ReheatInputVar has {enum_count} values"
        )

    def test_all_enum_values_mapped_to_dto_fields(self):
        fmu_vars = get_fmu_var_metadata(ReheatInputs)
        dto_fmu_values = set(fmu_vars.values())

        for enum_member in ReheatInputVar:
            assert enum_member.value in dto_fmu_values, (
                f"ReheatInputVar.{enum_member.name} ('{enum_member.value}') "
                f"has no corresponding field in ReheatInputs"
            )


UNIT_PREFERENCE_FIELDS = {"temperatureUnit", "airflowUnit"}


class TestReheatParametersFmuMapping:

    def test_all_parameters_have_fmu_var_metadata(self):
        fmu_vars = get_fmu_var_metadata(ReheatParameters)

        for field_name in ReheatParameters.model_fields:
            if field_name in UNIT_PREFERENCE_FIELDS:
                continue
            assert field_name in fmu_vars, (
                f"ReheatParameters.{field_name} missing fmu_var metadata"
            )

    def test_all_parameter_fmu_vars_exist_in_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatParameters)
        enum_values = {e.value for e in ReheatParameterVar}

        for field_name, fmu_var in fmu_vars.items():
            assert fmu_var in enum_values, (
                f"ReheatParameters.{field_name} has fmu_var='{fmu_var}' "
                f"but it's not in ReheatParameterVar enum"
            )

    def test_parameter_field_count_matches_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatParameters)
        enum_count = len(ReheatParameterVar)

        assert len(fmu_vars) == enum_count, (
            f"ReheatParameters has {len(fmu_vars)} fmu_var mappings "
            f"but ReheatParameterVar has {enum_count} values"
        )

    def test_all_enum_values_mapped_to_dto_fields(self):
        fmu_vars = get_fmu_var_metadata(ReheatParameters)
        dto_fmu_values = set(fmu_vars.values())

        for enum_member in ReheatParameterVar:
            assert enum_member.value in dto_fmu_values, (
                f"ReheatParameterVar.{enum_member.name} ('{enum_member.value}') "
                f"has no corresponding field in ReheatParameters"
            )


class TestReheatOutputsFmuMapping:

    def test_all_outputs_have_fmu_var_metadata(self):
        fmu_vars = get_fmu_var_metadata(ReheatOutputs)

        for field_name in ReheatOutputs.model_fields:
            assert field_name in fmu_vars, (
                f"ReheatOutputs.{field_name} missing fmu_var metadata"
            )

    def test_all_output_fmu_vars_exist_in_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatOutputs)
        enum_values = {e.value for e in ReheatOutputVar}

        for field_name, fmu_var in fmu_vars.items():
            assert fmu_var in enum_values, (
                f"ReheatOutputs.{field_name} has fmu_var='{fmu_var}' "
                f"but it's not in ReheatOutputVar enum"
            )

    def test_output_field_count_matches_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatOutputs)
        enum_count = len(ReheatOutputVar)

        assert len(fmu_vars) == enum_count, (
            f"ReheatOutputs has {len(fmu_vars)} fmu_var mappings "
            f"but ReheatOutputVar has {enum_count} values"
        )

    def test_all_enum_values_mapped_to_dto_fields(self):
        fmu_vars = get_fmu_var_metadata(ReheatOutputs)
        dto_fmu_values = set(fmu_vars.values())

        for enum_member in ReheatOutputVar:
            assert enum_member.value in dto_fmu_values, (
                f"ReheatOutputVar.{enum_member.name} ('{enum_member.value}') "
                f"has no corresponding field in ReheatOutputs"
            )


class TestReheatCalculatedParametersFmuMapping:

    def test_all_calculated_params_have_fmu_var_metadata(self):
        fmu_vars = get_fmu_var_metadata(ReheatCalculatedParameters)

        for field_name in ReheatCalculatedParameters.model_fields:
            assert field_name in fmu_vars, (
                f"ReheatCalculatedParameters.{field_name} missing fmu_var metadata"
            )

    def test_all_calc_param_fmu_vars_exist_in_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatCalculatedParameters)
        enum_values = {e.value for e in ReheatCalcParamVar}

        for field_name, fmu_var in fmu_vars.items():
            assert fmu_var in enum_values, (
                f"ReheatCalculatedParameters.{field_name} has fmu_var='{fmu_var}' "
                f"but it's not in ReheatCalcParamVar enum"
            )

    def test_calc_param_field_count_matches_enum(self):
        fmu_vars = get_fmu_var_metadata(ReheatCalculatedParameters)
        enum_count = len(ReheatCalcParamVar)

        assert len(fmu_vars) == enum_count, (
            f"ReheatCalculatedParameters has {len(fmu_vars)} fmu_var mappings "
            f"but ReheatCalcParamVar has {enum_count} values"
        )

    def test_all_enum_values_mapped_to_dto_fields(self):
        fmu_vars = get_fmu_var_metadata(ReheatCalculatedParameters)
        dto_fmu_values = set(fmu_vars.values())

        for enum_member in ReheatCalcParamVar:
            assert enum_member.value in dto_fmu_values, (
                f"ReheatCalcParamVar.{enum_member.name} ('{enum_member.value}') "
                f"has no corresponding field in ReheatCalculatedParameters"
            )


class TestFmuDataMappingConsistency:

    def test_input_variables_use_enum_values(self):
        inputs = ReheatInputs(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=13.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationMode.OCCUPIED,
        )
        params = ReheatParameters(temperatureUnit=TemperatureUnit.CELSIUS)
        fmu_data = ReheatFMUData(inputs=inputs, parameters=params)
        input_vars = fmu_data.input_variables

        var_names = {var.name for var in input_vars}
        enum_values = {e.value for e in ReheatInputVar}

        assert var_names == enum_values, (
            f"input_variables names {var_names} don't match ReheatInputVar enum {enum_values}"
        )

    def test_configuration_variables_use_enum_values(self):
        inputs = ReheatInputs(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=13.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationMode.OCCUPIED,
        )
        params = ReheatParameters(temperatureUnit=TemperatureUnit.CELSIUS)
        fmu_data = ReheatFMUData(inputs=inputs, parameters=params)
        config_vars = fmu_data.configuration_variables

        var_names = {var.name for var in config_vars}
        enum_values = {e.value for e in ReheatParameterVar}

        assert var_names == enum_values, (
            f"configuration_variables names don't match ReheatParameterVar enum"
        )

    def test_output_specs_use_enum_values(self):
        output_specs = ReheatFMUData.output_variable_specs()

        spec_names = {spec.name for spec in output_specs}
        enum_values = {e.value for e in ReheatOutputVar}

        assert spec_names == enum_values, (
            f"output_variable_specs names don't match ReheatOutputVar enum"
        )

    def test_calculated_parameter_specs_use_enum_values(self):
        calc_specs = ReheatFMUData.calculated_parameter_specs()

        spec_names = {spec.name for spec in calc_specs}
        enum_values = {e.value for e in ReheatCalcParamVar}

        assert spec_names == enum_values, (
            f"calculated_parameter_specs names don't match ReheatCalcParamVar enum"
        )


class TestCreateOutputsFieldMapping:

    def test_create_outputs_maps_all_fmu_vars(self):
        fmu_vars = get_fmu_var_metadata(ReheatOutputs)

        raw_values = {fmu_var: 0.0 for fmu_var in fmu_vars.values()}
        raw_values[ReheatOutputVar.FLOW_SENSOR_ALARM.value] = 0
        raw_values[ReheatOutputVar.HEATING_VALVE_REQUEST.value] = 0
        raw_values[ReheatOutputVar.HOT_WATER_PLANT_REQUEST.value] = 0
        raw_values[ReheatOutputVar.LEAKING_DAMPER_ALARM.value] = 0
        raw_values[ReheatOutputVar.LEAKING_VALVE_ALARM.value] = 0
        raw_values[ReheatOutputVar.LOW_FLOW_ALARM.value] = 0
        raw_values[ReheatOutputVar.LOW_TEMP_ALARM.value] = 0
        raw_values[ReheatOutputVar.ZONE_PRESSURE_REQUEST.value] = 0
        raw_values[ReheatOutputVar.ZONE_TEMP_REQUEST.value] = 0

        outputs = ReheatFMUData.create_outputs(raw_values)

        assert outputs is not None


class TestCreateCalculatedParametersFieldMapping:

    def test_create_calculated_parameters_maps_all_fmu_vars(self):
        fmu_vars = get_fmu_var_metadata(ReheatCalculatedParameters)

        raw_values = {}
        for fmu_var in fmu_vars.values():
            if "have_" in fmu_var:
                raw_values[fmu_var] = True
            elif "controllerType" in fmu_var or "venStd" in fmu_var:
                raw_values[fmu_var] = 1
            else:
                raw_values[fmu_var] = 0.1

        calc_params = ReheatFMUData.create_calculated_parameters(raw_values)

        assert calc_params is not None
