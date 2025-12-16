"""Unit tests for ParameterConverter service."""

import pytest

from src.adapters.sequence_type import SequenceType
from src.dto.reheat_dto import ReheatParametersDTO
from src.services.parameter_converter import ParameterConverter
from src.utils.unit_conversion import AirflowUnit, TemperatureUnit


class TestParameterConverterReheat:

    def test_convert_from_kelvin_to_celsius(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.KELVIN,
            airflowUnit=AirflowUnit.M3_PER_S,
            dischargeAirTempMin=283.15,
            maxDischargeTempAboveSetpoint=11.0,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.CELSIUS,
            AirflowUnit.M3_PER_S,
        )

        assert result.temperatureUnit == TemperatureUnit.CELSIUS
        assert result.dischargeAirTempMin == pytest.approx(10.0, rel=1e-6)
        assert result.maxDischargeTempAboveSetpoint == pytest.approx(11.0, rel=1e-6)

    def test_convert_from_celsius_to_kelvin(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.CELSIUS,
            airflowUnit=AirflowUnit.M3_PER_S,
            dischargeAirTempMin=10.0,  # 10°C is valid (within -23.1 to 76.9)
            maxDischargeTempAboveSetpoint=11.0,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.KELVIN,
            AirflowUnit.M3_PER_S,
        )

        assert result.temperatureUnit == TemperatureUnit.KELVIN
        assert result.dischargeAirTempMin == pytest.approx(283.15, rel=1e-3)
        assert result.maxDischargeTempAboveSetpoint == pytest.approx(11.0, rel=1e-6)

    def test_convert_from_m3_per_s_to_cfm(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.KELVIN,
            airflowUnit=AirflowUnit.M3_PER_S,
            minAirflow=0.471947,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.KELVIN,
            AirflowUnit.CFM,
        )

        assert result.airflowUnit == AirflowUnit.CFM
        assert result.minAirflow == pytest.approx(1000.0, rel=1e-3)

    def test_convert_from_cfm_to_m3_per_s(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.KELVIN,
            airflowUnit=AirflowUnit.CFM,
            minAirflow=1000.0,
            maxCoolingAirflow=2000.0,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.KELVIN,
            AirflowUnit.M3_PER_S,
        )

        assert result.airflowUnit == AirflowUnit.M3_PER_S
        assert result.minAirflow == pytest.approx(0.471947, rel=1e-3)
        assert result.maxCoolingAirflow == pytest.approx(0.943895, rel=1e-3)

    def test_convert_both_temperature_and_airflow(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.CELSIUS,
            airflowUnit=AirflowUnit.CFM,
            dischargeAirTempMin=10.0,  # 10°C is valid (within -23.1 to 76.9)
            minAirflow=1000.0,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.KELVIN,
            AirflowUnit.M3_PER_S,
        )

        assert result.temperatureUnit == TemperatureUnit.KELVIN
        assert result.airflowUnit == AirflowUnit.M3_PER_S
        assert result.dischargeAirTempMin == pytest.approx(283.15, rel=1e-3)
        assert result.minAirflow == pytest.approx(0.471947, rel=1e-3)

    def test_convert_all_temperature_diff_params(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.FAHRENHEIT,
            airflowUnit=AirflowUnit.M3_PER_S,
            dischargeAirTempMin=50.0,  # 50°F is valid (within -9.7 to 170.3)
            maxDischargeTempAboveSetpoint=9.0,
            thresholdDischargeTemp1=9.0,
            thresholdDischargeTemp2=18.0,
            thresholdTempDiff=9.0,
            twoTempDiff=18.0,
            tempHysteresis=1.8,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.KELVIN,
            AirflowUnit.M3_PER_S,
        )

        assert result.maxDischargeTempAboveSetpoint == pytest.approx(5.0, rel=1e-6)
        assert result.thresholdDischargeTemp1 == pytest.approx(5.0, rel=1e-6)
        assert result.thresholdDischargeTemp2 == pytest.approx(10.0, rel=1e-6)
        assert result.thresholdTempDiff == pytest.approx(5.0, rel=1e-6)
        assert result.twoTempDiff == pytest.approx(10.0, rel=1e-6)
        assert result.tempHysteresis == pytest.approx(1.0, rel=1e-6)

    def test_convert_all_airflow_params(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.KELVIN,
            airflowUnit=AirflowUnit.L_PER_S,
            minAirflow=100.0,
            maxCoolingAirflow=500.0,
            maxHeatingAirflow=400.0,
            minHeatingAirflow=50.0,
            areaBreathingZoneFlow=20.0,
            areaMinFlow=10.0,
            occMinFlow=30.0,
            popBreathingZoneFlow=25.0,
            flowHysteresis=5.0,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.KELVIN,
            AirflowUnit.M3_PER_S,
        )

        assert result.minAirflow == pytest.approx(0.1, rel=1e-6)
        assert result.maxCoolingAirflow == pytest.approx(0.5, rel=1e-6)
        assert result.maxHeatingAirflow == pytest.approx(0.4, rel=1e-6)
        assert result.minHeatingAirflow == pytest.approx(0.05, rel=1e-6)
        assert result.areaBreathingZoneFlow == pytest.approx(0.02, rel=1e-6)
        assert result.areaMinFlow == pytest.approx(0.01, rel=1e-6)
        assert result.occMinFlow == pytest.approx(0.03, rel=1e-6)
        assert result.popBreathingZoneFlow == pytest.approx(0.025, rel=1e-6)
        assert result.flowHysteresis == pytest.approx(0.005, rel=1e-6)

    def test_non_unit_params_unchanged(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.CELSIUS,
            airflowUnit=AirflowUnit.CFM,
            dischargeAirTempMin=10.0,  # 10°C is valid
            hasCO2Sensor=True,
            hasHotWaterCoil=False,
            coolingControllerGain=0.5,
            samplePeriod=120.0,
        )

        result = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            params,
            TemperatureUnit.KELVIN,
            AirflowUnit.M3_PER_S,
        )

        assert result.hasCO2Sensor is True
        assert result.hasHotWaterCoil is False
        assert result.coolingControllerGain == 0.5
        assert result.samplePeriod == 120.0

    def test_roundtrip_conversion(self) -> None:
        converter = ParameterConverter()
        original = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.KELVIN,
            airflowUnit=AirflowUnit.M3_PER_S,
            dischargeAirTempMin=283.15,
            maxDischargeTempAboveSetpoint=11.0,
            minAirflow=0.3,
        )

        to_celsius = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            original,
            TemperatureUnit.CELSIUS,
            AirflowUnit.CFM,
        )

        back_to_kelvin = converter.convert_parameters(
            SequenceType.VAV_REHEAT,
            to_celsius,
            TemperatureUnit.KELVIN,
            AirflowUnit.M3_PER_S,
        )

        assert back_to_kelvin.dischargeAirTempMin == pytest.approx(
            original.dischargeAirTempMin, rel=1e-6
        )
        assert back_to_kelvin.maxDischargeTempAboveSetpoint == pytest.approx(
            original.maxDischargeTempAboveSetpoint, rel=1e-6
        )
        assert back_to_kelvin.minAirflow == pytest.approx(original.minAirflow, rel=1e-6)


class TestParameterConverterErrors:

    def test_unknown_sequence_type_raises_error(self) -> None:
        converter = ParameterConverter()
        params = ReheatParametersDTO(
            temperatureUnit=TemperatureUnit.KELVIN,
            airflowUnit=AirflowUnit.M3_PER_S,
        )

        with pytest.raises(ValueError, match="Unknown sequence type"):
            converter.convert_parameters(
                "invalid-type",  # type: ignore
                params,
                TemperatureUnit.KELVIN,
                AirflowUnit.M3_PER_S,
            )
