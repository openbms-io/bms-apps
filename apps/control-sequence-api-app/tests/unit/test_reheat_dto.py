from typing import Any

import pytest
from pydantic import ValidationError

from src.dto.reheat_dto import (
    ReheatInputsDTO,
    ReheatOutputsDTO,
    StepRequest,
)
from src.models.reheat.enums import OperationMode, OperationModeStr
from src.models.reheat.inputs import ReheatInputs
from src.models.reheat.outputs import ReheatOutputs
from src.models.reheat.parameters import ReheatParameters
from src.utils.unit_conversion import (
    CELSIUS_TO_KELVIN_OFFSET,
    CFM_TO_M3_PER_S,
    L_PER_S_TO_M3_PER_S,
    M3_PER_H_TO_M3_PER_S,
    AirflowUnit,
    TemperatureUnit,
    airflow_in_m3_per_s,
    kelvin_diff_to_unit,
    m3_per_s_to_airflow,
    temp_diff_in_kelvin,
    temp_in_kelvin,
)


class TestTemperatureUnit:
    def test_enum_values(self) -> None:
        assert TemperatureUnit.KELVIN == "K"
        assert TemperatureUnit.CELSIUS == "C"
        assert TemperatureUnit.FAHRENHEIT == "F"


class TestTempInKelvin:
    def test_kelvin_unchanged(self) -> None:
        assert temp_in_kelvin(300.0, TemperatureUnit.KELVIN) == 300.0

    def test_celsius_to_kelvin(self) -> None:
        assert temp_in_kelvin(0.0, TemperatureUnit.CELSIUS) == 273.15
        assert temp_in_kelvin(100.0, TemperatureUnit.CELSIUS) == 373.15
        assert temp_in_kelvin(22.0, TemperatureUnit.CELSIUS) == 295.15

    def test_fahrenheit_to_kelvin(self) -> None:
        assert temp_in_kelvin(32.0, TemperatureUnit.FAHRENHEIT) == 273.15
        assert temp_in_kelvin(212.0, TemperatureUnit.FAHRENHEIT) == 373.15
        result = temp_in_kelvin(71.6, TemperatureUnit.FAHRENHEIT)
        assert result == pytest.approx(295.15, rel=1e-2)


class TestTempDiffInKelvin:
    def test_kelvin_diff_unchanged(self) -> None:
        assert temp_diff_in_kelvin(5.0, TemperatureUnit.KELVIN) == 5.0
        assert temp_diff_in_kelvin(10.0, TemperatureUnit.KELVIN) == 10.0

    def test_celsius_diff_unchanged(self) -> None:
        assert temp_diff_in_kelvin(5.0, TemperatureUnit.CELSIUS) == 5.0
        assert temp_diff_in_kelvin(10.0, TemperatureUnit.CELSIUS) == 10.0

    def test_fahrenheit_diff_to_kelvin(self) -> None:
        result = temp_diff_in_kelvin(9.0, TemperatureUnit.FAHRENHEIT)
        assert result == pytest.approx(5.0, rel=1e-6)
        result = temp_diff_in_kelvin(18.0, TemperatureUnit.FAHRENHEIT)
        assert result == pytest.approx(10.0, rel=1e-6)


class TestKelvinDiffToUnit:
    def test_kelvin_diff_unchanged(self) -> None:
        assert kelvin_diff_to_unit(5.0, TemperatureUnit.KELVIN) == 5.0
        assert kelvin_diff_to_unit(10.0, TemperatureUnit.KELVIN) == 10.0

    def test_kelvin_diff_to_celsius_unchanged(self) -> None:
        assert kelvin_diff_to_unit(5.0, TemperatureUnit.CELSIUS) == 5.0
        assert kelvin_diff_to_unit(10.0, TemperatureUnit.CELSIUS) == 10.0

    def test_kelvin_diff_to_fahrenheit(self) -> None:
        result = kelvin_diff_to_unit(5.0, TemperatureUnit.FAHRENHEIT)
        assert result == pytest.approx(9.0, rel=1e-6)
        result = kelvin_diff_to_unit(10.0, TemperatureUnit.FAHRENHEIT)
        assert result == pytest.approx(18.0, rel=1e-6)

    def test_roundtrip_conversion(self) -> None:
        for unit in [TemperatureUnit.KELVIN, TemperatureUnit.CELSIUS, TemperatureUnit.FAHRENHEIT]:
            original = 5.5
            converted = temp_diff_in_kelvin(original, unit)
            back = kelvin_diff_to_unit(converted, unit)
            assert back == pytest.approx(original, rel=1e-6)


class TestAirflowUnit:
    def test_enum_values(self) -> None:
        assert AirflowUnit.M3_PER_S == "m3/s"
        assert AirflowUnit.CFM == "cfm"
        assert AirflowUnit.L_PER_S == "L/s"
        assert AirflowUnit.M3_PER_H == "m3/h"


class TestAirflowInM3PerS:
    def test_m3_per_s_unchanged(self) -> None:
        assert airflow_in_m3_per_s(0.5, AirflowUnit.M3_PER_S) == 0.5
        assert airflow_in_m3_per_s(1.0, AirflowUnit.M3_PER_S) == 1.0

    def test_cfm_to_m3_per_s(self) -> None:
        result = airflow_in_m3_per_s(1000.0, AirflowUnit.CFM)
        assert result == pytest.approx(0.471947, rel=1e-4)
        result = airflow_in_m3_per_s(500.0, AirflowUnit.CFM)
        assert result == pytest.approx(0.2359735, rel=1e-4)

    def test_l_per_s_to_m3_per_s(self) -> None:
        assert airflow_in_m3_per_s(1000.0, AirflowUnit.L_PER_S) == 1.0
        assert airflow_in_m3_per_s(500.0, AirflowUnit.L_PER_S) == 0.5
        assert airflow_in_m3_per_s(100.0, AirflowUnit.L_PER_S) == 0.1

    def test_m3_per_h_to_m3_per_s(self) -> None:
        result = airflow_in_m3_per_s(3600.0, AirflowUnit.M3_PER_H)
        assert result == pytest.approx(1.0, rel=1e-6)
        result = airflow_in_m3_per_s(1800.0, AirflowUnit.M3_PER_H)
        assert result == pytest.approx(0.5, rel=1e-6)


class TestM3PerSToAirflow:
    def test_m3_per_s_unchanged(self) -> None:
        assert m3_per_s_to_airflow(0.5, AirflowUnit.M3_PER_S) == 0.5
        assert m3_per_s_to_airflow(1.0, AirflowUnit.M3_PER_S) == 1.0

    def test_m3_per_s_to_cfm(self) -> None:
        result = m3_per_s_to_airflow(0.471947, AirflowUnit.CFM)
        assert result == pytest.approx(1000.0, rel=1e-4)
        result = m3_per_s_to_airflow(0.2359735, AirflowUnit.CFM)
        assert result == pytest.approx(500.0, rel=1e-4)

    def test_m3_per_s_to_l_per_s(self) -> None:
        assert m3_per_s_to_airflow(1.0, AirflowUnit.L_PER_S) == 1000.0
        assert m3_per_s_to_airflow(0.5, AirflowUnit.L_PER_S) == 500.0
        assert m3_per_s_to_airflow(0.1, AirflowUnit.L_PER_S) == 100.0

    def test_m3_per_s_to_m3_per_h(self) -> None:
        result = m3_per_s_to_airflow(1.0, AirflowUnit.M3_PER_H)
        assert result == pytest.approx(3600.0, rel=1e-6)
        result = m3_per_s_to_airflow(0.5, AirflowUnit.M3_PER_H)
        assert result == pytest.approx(1800.0, rel=1e-6)

    def test_roundtrip_conversion(self) -> None:
        for unit in [AirflowUnit.CFM, AirflowUnit.L_PER_S, AirflowUnit.M3_PER_H]:
            original = 0.35
            converted = m3_per_s_to_airflow(original, unit)
            roundtrip = airflow_in_m3_per_s(converted, unit)
            assert roundtrip == pytest.approx(original, rel=1e-6)


class TestOperationMode:
    def test_enum_values(self) -> None:
        assert OperationMode.OCCUPIED == 1
        assert OperationMode.UNOCCUPIED == 2
        assert OperationMode.STANDBY == 3
        assert OperationMode.WARMUP == 4
        assert OperationMode.COOLDOWN == 5
        assert OperationMode.SETUP == 6
        assert OperationMode.SETBACK == 7

    def test_enum_from_int(self) -> None:
        assert OperationMode(3) == OperationMode.STANDBY

    def test_enum_invalid_value(self) -> None:
        with pytest.raises(ValueError):
            OperationMode(0)
        with pytest.raises(ValueError):
            OperationMode(8)


class TestReheatParameters:
    def test_valid_defaults(self) -> None:
        params = ReheatParameters()
        assert params.maxCoolingAirflow == 1.5
        assert params.maxHeatingAirflow == 1.2
        assert params.minHeatingAirflow == 0.5

    def test_valid_custom_values(self) -> None:
        params = ReheatParameters(
            maxCoolingAirflow=0.8, maxHeatingAirflow=0.5, minHeatingAirflow=0.2
        )
        assert params.maxCoolingAirflow == 0.8
        assert params.maxHeatingAirflow == 0.5
        assert params.minHeatingAirflow == 0.2

    def test_rejects_negative_max_cooling_airflow(self) -> None:
        with pytest.raises(ValidationError) as exc_info:
            ReheatParameters(maxCoolingAirflow=-0.1)
        assert "maxCoolingAirflow" in str(exc_info.value)

    def test_rejects_negative_max_heating_airflow(self) -> None:
        with pytest.raises(ValidationError) as exc_info:
            ReheatParameters(maxHeatingAirflow=-0.1)
        assert "maxHeatingAirflow" in str(exc_info.value)

    def test_rejects_negative_min_heating_airflow(self) -> None:
        with pytest.raises(ValidationError) as exc_info:
            ReheatParameters(minHeatingAirflow=-0.1)
        assert "minHeatingAirflow" in str(exc_info.value)

    def test_allows_zero_values(self) -> None:
        params = ReheatParameters(
            maxCoolingAirflow=0, maxHeatingAirflow=0, minHeatingAirflow=0
        )
        assert params.maxCoolingAirflow == 0
        assert params.maxHeatingAirflow == 0
        assert params.minHeatingAirflow == 0


class TestReheatInputsDTO:
    @pytest.fixture
    def valid_request(self) -> dict[str, Any]:
        return {
            "zoneTemperature": 22.0,
            "coolingSetpoint": 24.0,
            "heatingSetpoint": 20.0,
            "dischargeAirTemperature": 16.0,
            "primaryAirflow": 0.3,
            "supplyAirTemperature": 13.0,
            "supplyAirTemperatureSetpoint": 12.0,
            "fanStatus": True,
            "operationMode": OperationModeStr.STANDBY,
        }

    def test_valid_request(self, valid_request: dict[str, Any]) -> None:
        dto = ReheatInputsDTO(**valid_request)
        assert dto.zoneTemperature == 22.0
        assert dto.operationMode == OperationModeStr.STANDBY

    def test_rejects_negative_airflow(self, valid_request: dict[str, Any]) -> None:
        valid_request["primaryAirflow"] = -0.1
        with pytest.raises(ValidationError) as exc_info:
            ReheatInputsDTO(**valid_request)
        assert "primaryAirflow" in str(exc_info.value)

    def test_rejects_invalid_operation_mode(
        self, valid_request: dict[str, Any]
    ) -> None:
        valid_request["operationMode"] = 0
        with pytest.raises(ValidationError) as exc_info:
            ReheatInputsDTO(**valid_request)
        assert "operationMode" in str(exc_info.value)


class TestReheatInputs:
    def test_valid_celsius_inputs(self) -> None:
        inputs = ReheatInputs(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=16.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        assert inputs.zoneTemperature == 22.0

    def test_accepts_any_temperature_value(self) -> None:
        inputs = ReheatInputs(
            zoneTemperature=-50.0,
            coolingSetpoint=100.0,
            heatingSetpoint=-30.0,
            dischargeAirTemperature=80.0,
            primaryAirflow=0.3,
            supplyAirTemperature=-20.0,
            supplyAirTemperatureSetpoint=90.0,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        assert inputs.zoneTemperature == -50.0
        assert inputs.coolingSetpoint == 100.0


class TestReheatInputsDTOToDomain:
    def test_to_domain_passes_values_as_is(self) -> None:
        dto = ReheatInputsDTO(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=16.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationModeStr.STANDBY,
        )
        inputs = dto.to_domain()
        assert inputs.zoneTemperature == 22.0
        assert inputs.coolingSetpoint == 24.0
        assert inputs.primaryAirflow == 0.3
        assert inputs.fanStatus is True
        assert inputs.operationMode == OperationMode.STANDBY

    def test_to_domain_converts_operation_mode_string_to_int(self) -> None:
        dto = ReheatInputsDTO(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=16.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationModeStr.OCCUPIED,
        )
        inputs = dto.to_domain()
        assert inputs.operationMode == OperationMode.OCCUPIED


class TestReheatOutputs:
    @pytest.fixture
    def valid_outputs_data(self) -> dict[str, Any]:
        return {
            "damperPosition": 0.75,
            "valvePosition": 0.0,
            "airflowSetpoint": 0.35,
            "minOutdoorAirflow": 0.1,
            "adjAreaBreathingZoneFlow": 0.0,
            "adjPopBreathingZoneFlow": 0.0,
            "flowSensorAlarm": 0,
            "heatingValveRequest": 0,
            "hotWaterPlantRequest": 0,
            "leakingDamperAlarm": 0,
            "leakingValveAlarm": 0,
            "lowFlowAlarm": 0,
            "lowTempAlarm": 0,
            "zonePressureRequest": 0,
            "zoneTempRequest": 0,
        }

    def test_valid_outputs(self, valid_outputs_data: dict[str, Any]) -> None:
        outputs = ReheatOutputs(**valid_outputs_data)
        assert outputs.damperPosition == 0.75
        assert outputs.valvePosition == 0.0
        assert outputs.airflowSetpoint == 0.35
        assert outputs.minOutdoorAirflow == 0.1
        assert outputs.flowSensorAlarm == 0

    def test_boundary_values_min(self, valid_outputs_data: dict[str, Any]) -> None:
        valid_outputs_data["damperPosition"] = 0
        valid_outputs_data["valvePosition"] = 0
        valid_outputs_data["airflowSetpoint"] = 0
        outputs = ReheatOutputs(**valid_outputs_data)
        assert outputs.damperPosition == 0
        assert outputs.valvePosition == 0

    def test_boundary_values_max(self, valid_outputs_data: dict[str, Any]) -> None:
        valid_outputs_data["damperPosition"] = 1
        valid_outputs_data["valvePosition"] = 1
        valid_outputs_data["airflowSetpoint"] = 0.5
        outputs = ReheatOutputs(**valid_outputs_data)
        assert outputs.damperPosition == 1
        assert outputs.valvePosition == 1

    def test_rejects_damper_position_above_max(self, valid_outputs_data: dict[str, Any]) -> None:
        valid_outputs_data["damperPosition"] = 1.1
        with pytest.raises(ValidationError) as exc_info:
            ReheatOutputs(**valid_outputs_data)
        assert "damperPosition" in str(exc_info.value)

    def test_rejects_damper_position_below_min(self, valid_outputs_data: dict[str, Any]) -> None:
        valid_outputs_data["damperPosition"] = -0.1
        with pytest.raises(ValidationError) as exc_info:
            ReheatOutputs(**valid_outputs_data)
        assert "damperPosition" in str(exc_info.value)

    def test_rejects_valve_position_above_max(self, valid_outputs_data: dict[str, Any]) -> None:
        valid_outputs_data["valvePosition"] = 1.5
        with pytest.raises(ValidationError) as exc_info:
            ReheatOutputs(**valid_outputs_data)
        assert "valvePosition" in str(exc_info.value)

    def test_rejects_valve_position_below_min(self, valid_outputs_data: dict[str, Any]) -> None:
        valid_outputs_data["valvePosition"] = -0.1
        with pytest.raises(ValidationError) as exc_info:
            ReheatOutputs(**valid_outputs_data)
        assert "valvePosition" in str(exc_info.value)


class TestStepRequest:
    def test_valid_step_request(self) -> None:
        inputs = ReheatInputsDTO(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=16.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationModeStr.STANDBY,
        )
        request = StepRequest(stepSize=60.0, inputs=inputs)
        assert request.stepSize == 60.0
        assert request.inputs.zoneTemperature == 22.0

    def test_rejects_zero_step_size(self) -> None:
        inputs = ReheatInputsDTO(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=16.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationModeStr.STANDBY,
        )
        with pytest.raises(ValidationError) as exc_info:
            StepRequest(stepSize=0, inputs=inputs)
        assert "stepSize" in str(exc_info.value)

    def test_rejects_negative_step_size(self) -> None:
        inputs = ReheatInputsDTO(
            zoneTemperature=22.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=16.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationModeStr.STANDBY,
        )
        with pytest.raises(ValidationError) as exc_info:
            StepRequest(stepSize=-1.0, inputs=inputs)
        assert "stepSize" in str(exc_info.value)

    def test_rejects_negative_airflow_in_nested_inputs(self) -> None:
        with pytest.raises(ValidationError):
            StepRequest(
                stepSize=60.0,
                inputs=ReheatInputsDTO(
                    zoneTemperature=22.0,
                    coolingSetpoint=24.0,
                    heatingSetpoint=20.0,
                    dischargeAirTemperature=16.0,
                    primaryAirflow=-0.1,
                    supplyAirTemperature=13.0,
                    supplyAirTemperatureSetpoint=12.0,
                    fanStatus=True,
                    operationMode=OperationModeStr.STANDBY,
                ),
            )


class TestReheatOutputsDTOFromDomain:
    @pytest.fixture
    def domain_outputs(self) -> ReheatOutputs:
        return ReheatOutputs(
            damperPosition=0.75,
            valvePosition=0.25,
            airflowSetpoint=0.35,
            minOutdoorAirflow=0.1,
            adjAreaBreathingZoneFlow=0.05,
            adjPopBreathingZoneFlow=0.03,
            flowSensorAlarm=0,
            heatingValveRequest=1,
            hotWaterPlantRequest=0,
            leakingDamperAlarm=0,
            leakingValveAlarm=0,
            lowFlowAlarm=0,
            lowTempAlarm=0,
            zonePressureRequest=2,
            zoneTempRequest=1,
        )

    def test_from_domain_with_m3_per_s_passes_values_unchanged(
        self, domain_outputs: ReheatOutputs
    ) -> None:
        dto = ReheatOutputsDTO.from_domain(domain_outputs, AirflowUnit.M3_PER_S)

        assert dto.damperPosition == 0.75
        assert dto.valvePosition == 0.25
        assert dto.airflowSetpoint == 0.35
        assert dto.minOutdoorAirflow == 0.1
        assert dto.adjAreaBreathingZoneFlow == 0.05
        assert dto.adjPopBreathingZoneFlow == 0.03
        assert dto.flowSensorAlarm == 0
        assert dto.heatingValveRequest == 1

    def test_from_domain_with_cfm_converts_airflow_values(
        self, domain_outputs: ReheatOutputs
    ) -> None:
        dto = ReheatOutputsDTO.from_domain(domain_outputs, AirflowUnit.CFM)

        expected_cfm = m3_per_s_to_airflow(0.35, AirflowUnit.CFM)
        assert dto.airflowSetpoint == pytest.approx(expected_cfm, rel=1e-4)
        assert dto.damperPosition == 0.75
        assert dto.valvePosition == 0.25

    def test_from_domain_with_l_per_s_converts_airflow_values(
        self, domain_outputs: ReheatOutputs
    ) -> None:
        dto = ReheatOutputsDTO.from_domain(domain_outputs, AirflowUnit.L_PER_S)

        assert dto.airflowSetpoint == pytest.approx(350.0, rel=1e-4)
        assert dto.minOutdoorAirflow == pytest.approx(100.0, rel=1e-4)

    def test_from_domain_with_m3_per_h_converts_airflow_values(
        self, domain_outputs: ReheatOutputs
    ) -> None:
        dto = ReheatOutputsDTO.from_domain(domain_outputs, AirflowUnit.M3_PER_H)

        assert dto.airflowSetpoint == pytest.approx(1260.0, rel=1e-4)
        assert dto.minOutdoorAirflow == pytest.approx(360.0, rel=1e-4)

    def test_from_domain_preserves_alarm_values(
        self, domain_outputs: ReheatOutputs
    ) -> None:
        dto = ReheatOutputsDTO.from_domain(domain_outputs, AirflowUnit.CFM)

        assert dto.flowSensorAlarm == 0
        assert dto.heatingValveRequest == 1
        assert dto.hotWaterPlantRequest == 0
        assert dto.leakingDamperAlarm == 0
        assert dto.leakingValveAlarm == 0
        assert dto.lowFlowAlarm == 0
        assert dto.lowTempAlarm == 0
        assert dto.zonePressureRequest == 2
        assert dto.zoneTempRequest == 1


class TestReheatParametersUnitPreferences:
    def test_default_temperature_unit_is_kelvin(self) -> None:
        params = ReheatParameters()
        assert params.temperatureUnit == TemperatureUnit.KELVIN

    def test_default_airflow_unit_is_m3_per_s(self) -> None:
        params = ReheatParameters()
        assert params.airflowUnit == AirflowUnit.M3_PER_S

    def test_custom_temperature_unit(self) -> None:
        params = ReheatParameters(temperatureUnit=TemperatureUnit.FAHRENHEIT)
        assert params.temperatureUnit == TemperatureUnit.FAHRENHEIT

    def test_custom_airflow_unit(self) -> None:
        params = ReheatParameters(airflowUnit=AirflowUnit.CFM)
        assert params.airflowUnit == AirflowUnit.CFM

    def test_kelvin_temperature_unit(self) -> None:
        params = ReheatParameters(temperatureUnit=TemperatureUnit.KELVIN)
        assert params.temperatureUnit == TemperatureUnit.KELVIN

    def test_all_airflow_units_accepted(self) -> None:
        for unit in AirflowUnit:
            params = ReheatParameters(airflowUnit=unit)
            assert params.airflowUnit == unit
