from typing import Any

import pytest
from pydantic import ValidationError

from src.dto.reheat_dto import (
    CELSIUS_TO_KELVIN_OFFSET,
    CreateInstanceRequest,
    OperationMode,
    ReheatInputs,
    ReheatInputsRequest,
    ReheatOutputs,
    ReheatParameters,
    StepRequest,
    TemperatureUnit,
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


class TestReheatInputsRequest:
    @pytest.fixture
    def valid_request_celsius(self) -> dict[str, Any]:
        return {
            "zoneTemperature": 22.0,
            "coolingSetpoint": 24.0,
            "heatingSetpoint": 20.0,
            "dischargeAirTemperature": 16.0,
            "primaryAirflow": 0.3,
            "supplyAirTemperature": 13.0,
            "supplyAirTemperatureSetpoint": 12.0,
            "fanStatus": True,
            "operationMode": OperationMode.STANDBY,
        }

    def test_valid_request_default_celsius(
        self, valid_request_celsius: dict[str, Any]
    ) -> None:
        request = ReheatInputsRequest(**valid_request_celsius)
        assert request.zoneTemperature == 22.0
        assert request.temperatureUnit == TemperatureUnit.CELSIUS
        assert request.operationMode == OperationMode.STANDBY

    def test_explicit_kelvin_unit(self) -> None:
        request = ReheatInputsRequest(
            temperatureUnit=TemperatureUnit.KELVIN,
            zoneTemperature=295.15,
            coolingSetpoint=297.15,
            heatingSetpoint=293.15,
            dischargeAirTemperature=289.15,
            primaryAirflow=0.3,
            supplyAirTemperature=286.15,
            supplyAirTemperatureSetpoint=285.15,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        assert request.temperatureUnit == TemperatureUnit.KELVIN

    def test_explicit_fahrenheit_unit(self) -> None:
        request = ReheatInputsRequest(
            temperatureUnit=TemperatureUnit.FAHRENHEIT,
            zoneTemperature=71.6,
            coolingSetpoint=75.2,
            heatingSetpoint=68.0,
            dischargeAirTemperature=60.8,
            primaryAirflow=0.3,
            supplyAirTemperature=55.4,
            supplyAirTemperatureSetpoint=53.6,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        assert request.temperatureUnit == TemperatureUnit.FAHRENHEIT

    def test_rejects_negative_airflow(
        self, valid_request_celsius: dict[str, Any]
    ) -> None:
        valid_request_celsius["primaryAirflow"] = -0.1
        with pytest.raises(ValidationError) as exc_info:
            ReheatInputsRequest(**valid_request_celsius)
        assert "primaryAirflow" in str(exc_info.value)

    def test_rejects_invalid_operation_mode(
        self, valid_request_celsius: dict[str, Any]
    ) -> None:
        valid_request_celsius["operationMode"] = 0
        with pytest.raises(ValidationError) as exc_info:
            ReheatInputsRequest(**valid_request_celsius)
        assert "operationMode" in str(exc_info.value)


class TestReheatInputs:
    def test_valid_kelvin_inputs(self) -> None:
        inputs = ReheatInputs(
            zoneTemperature=295.15,
            coolingSetpoint=297.15,
            heatingSetpoint=293.15,
            dischargeAirTemperature=289.15,
            primaryAirflow=0.3,
            supplyAirTemperature=286.15,
            supplyAirTemperatureSetpoint=285.15,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        assert inputs.zoneTemperature == 295.15

    def test_rejects_temperature_below_min(self) -> None:
        with pytest.raises(ValidationError) as exc_info:
            ReheatInputs(
                zoneTemperature=200.0,
                coolingSetpoint=297.15,
                heatingSetpoint=293.15,
                dischargeAirTemperature=289.15,
                primaryAirflow=0.3,
                supplyAirTemperature=286.15,
                supplyAirTemperatureSetpoint=285.15,
                fanStatus=True,
                operationMode=OperationMode.STANDBY,
            )
        assert "zoneTemperature" in str(exc_info.value)

    def test_rejects_temperature_above_max(self) -> None:
        with pytest.raises(ValidationError) as exc_info:
            ReheatInputs(
                zoneTemperature=400.0,
                coolingSetpoint=297.15,
                heatingSetpoint=293.15,
                dischargeAirTemperature=289.15,
                primaryAirflow=0.3,
                supplyAirTemperature=286.15,
                supplyAirTemperatureSetpoint=285.15,
                fanStatus=True,
                operationMode=OperationMode.STANDBY,
            )
        assert "zoneTemperature" in str(exc_info.value)

    def test_boundary_values(self) -> None:
        inputs = ReheatInputs(
            zoneTemperature=250.0,
            coolingSetpoint=350.0,
            heatingSetpoint=250.0,
            dischargeAirTemperature=350.0,
            primaryAirflow=0.0,
            supplyAirTemperature=250.0,
            supplyAirTemperatureSetpoint=350.0,
            fanStatus=False,
            operationMode=OperationMode.OCCUPIED,
        )
        assert inputs.zoneTemperature == 250.0
        assert inputs.coolingSetpoint == 350.0


class TestReheatInputsFromRequest:
    def test_celsius_to_kelvin_conversion(self) -> None:
        request = ReheatInputsRequest(
            temperatureUnit=TemperatureUnit.CELSIUS,
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
        inputs = ReheatInputs.from_request(request)
        assert inputs.zoneTemperature == 22.0 + CELSIUS_TO_KELVIN_OFFSET
        assert inputs.coolingSetpoint == 24.0 + CELSIUS_TO_KELVIN_OFFSET
        assert inputs.primaryAirflow == 0.3
        assert inputs.fanStatus is True
        assert inputs.operationMode == OperationMode.STANDBY

    def test_fahrenheit_to_kelvin_conversion(self) -> None:
        request = ReheatInputsRequest(
            temperatureUnit=TemperatureUnit.FAHRENHEIT,
            zoneTemperature=71.6,
            coolingSetpoint=75.2,
            heatingSetpoint=68.0,
            dischargeAirTemperature=60.8,
            primaryAirflow=0.3,
            supplyAirTemperature=55.4,
            supplyAirTemperatureSetpoint=53.6,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        inputs = ReheatInputs.from_request(request)
        assert inputs.zoneTemperature == pytest.approx(295.15, rel=1e-2)

    def test_kelvin_passthrough(self) -> None:
        request = ReheatInputsRequest(
            temperatureUnit=TemperatureUnit.KELVIN,
            zoneTemperature=295.15,
            coolingSetpoint=297.15,
            heatingSetpoint=293.15,
            dischargeAirTemperature=289.15,
            primaryAirflow=0.3,
            supplyAirTemperature=286.15,
            supplyAirTemperatureSetpoint=285.15,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        inputs = ReheatInputs.from_request(request)
        assert inputs.zoneTemperature == 295.15

    def test_rejects_out_of_range_after_conversion(self) -> None:
        request = ReheatInputsRequest(
            temperatureUnit=TemperatureUnit.CELSIUS,
            zoneTemperature=-50.0,
            coolingSetpoint=24.0,
            heatingSetpoint=20.0,
            dischargeAirTemperature=16.0,
            primaryAirflow=0.3,
            supplyAirTemperature=13.0,
            supplyAirTemperatureSetpoint=12.0,
            fanStatus=True,
            operationMode=OperationMode.STANDBY,
        )
        with pytest.raises(ValidationError) as exc_info:
            ReheatInputs.from_request(request)
        assert "zoneTemperature" in str(exc_info.value)


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


class TestCreateInstanceRequest:
    def test_with_parameters(self) -> None:
        params = ReheatParameters(maxCoolingAirflow=0.6)
        request = CreateInstanceRequest(instance_id="test-1", parameters=params)
        assert request.instance_id == "test-1"
        assert request.parameters is not None
        assert request.parameters.maxCoolingAirflow == 0.6

    def test_without_parameters(self) -> None:
        request = CreateInstanceRequest(instance_id="test-1")
        assert request.instance_id == "test-1"
        assert request.parameters is None

    def test_with_explicit_none_parameters(self) -> None:
        request = CreateInstanceRequest(instance_id="test-1", parameters=None)
        assert request.parameters is None


class TestStepRequest:
    def test_valid_step_request(self) -> None:
        inputs = ReheatInputsRequest(
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
        request = StepRequest(stepSize=60.0, inputs=inputs)
        assert request.stepSize == 60.0
        assert request.inputs.zoneTemperature == 22.0

    def test_rejects_zero_step_size(self) -> None:
        inputs = ReheatInputsRequest(
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
        with pytest.raises(ValidationError) as exc_info:
            StepRequest(stepSize=0, inputs=inputs)
        assert "stepSize" in str(exc_info.value)

    def test_rejects_negative_step_size(self) -> None:
        inputs = ReheatInputsRequest(
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
        with pytest.raises(ValidationError) as exc_info:
            StepRequest(stepSize=-1.0, inputs=inputs)
        assert "stepSize" in str(exc_info.value)

    def test_rejects_negative_airflow_in_nested_inputs(self) -> None:
        with pytest.raises(ValidationError):
            StepRequest(
                stepSize=60.0,
                inputs=ReheatInputsRequest(
                    zoneTemperature=22.0,
                    coolingSetpoint=24.0,
                    heatingSetpoint=20.0,
                    dischargeAirTemperature=16.0,
                    primaryAirflow=-0.1,
                    supplyAirTemperature=13.0,
                    supplyAirTemperatureSetpoint=12.0,
                    fanStatus=True,
                    operationMode=OperationMode.STANDBY,
                ),
            )
