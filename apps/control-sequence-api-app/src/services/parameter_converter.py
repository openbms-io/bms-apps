"""Parameter converter service for unit conversion between systems."""

from src.adapters.sequence_type import SequenceType
from src.dto.reheat_constants import (
    REHEAT_AIRFLOW_PARAMS,
    REHEAT_TEMP_DIFF_PARAMS,
    REHEAT_TEMPERATURE_PARAMS,
)
from src.dto.reheat_dto import ReheatParametersDTO
from src.utils.unit_conversion import (
    AirflowUnit,
    TemperatureUnit,
    airflow_in_m3_per_s,
    get_temperature_bounds,
    kelvin_diff_to_unit,
    kelvin_to_unit,
    m3_per_s_to_airflow,
    temp_diff_in_kelvin,
    temp_in_kelvin,
)

TEMPERATURE_CONSTRAINED_PARAMS = ["dischargeAirTempMin"]


class ParameterConverter:
    """Converts parameter values between unit systems."""

    def _validate_temperature_ranges(self, params: ReheatParametersDTO) -> None:
        """Validate temperature values are within bounds for source unit."""
        source_unit = params.temperatureUnit
        min_temp, max_temp = get_temperature_bounds(source_unit)

        for param_name in TEMPERATURE_CONSTRAINED_PARAMS:
            value = getattr(params, param_name)
            if not (min_temp <= value <= max_temp):
                raise ValueError(
                    f"{param_name}={value} out of range for {source_unit} "
                    f"(expected {min_temp:.1f} to {max_temp:.1f})"
                )

    def _validate_airflow_ranges(self, params: ReheatParametersDTO) -> None:
        """Validate airflow values are non-negative."""
        for param_name in REHEAT_AIRFLOW_PARAMS:
            value = getattr(params, param_name)
            if value < 0:
                raise ValueError(f"{param_name}={value} must be non-negative")

    def validate_parameters(self, params: ReheatParametersDTO) -> None:
        """Validate all parameter values before saving."""
        self._validate_temperature_ranges(params)
        self._validate_airflow_ranges(params)

    def convert_parameters(
        self,
        sequence_type: SequenceType,
        params: ReheatParametersDTO,
        target_temp_unit: TemperatureUnit,
        target_airflow_unit: AirflowUnit,
    ) -> ReheatParametersDTO:
        """Convert all parameter values to target units."""
        self._validate_temperature_ranges(params)

        if sequence_type == SequenceType.VAV_REHEAT:
            return self._convert_reheat_params(
                params, target_temp_unit, target_airflow_unit
            )
        raise ValueError(f"Unknown sequence type: {sequence_type}")

    def _convert_reheat_params(
        self,
        params: ReheatParametersDTO,
        target_temp_unit: TemperatureUnit,
        target_airflow_unit: AirflowUnit,
    ) -> ReheatParametersDTO:
        """Convert reheat parameters to target units."""
        source_temp_unit = params.temperatureUnit
        source_airflow_unit = params.airflowUnit

        updates: dict = {
            "temperatureUnit": target_temp_unit,
            "airflowUnit": target_airflow_unit,
        }

        for param_name in REHEAT_TEMPERATURE_PARAMS:
            value = getattr(params, param_name)
            kelvin_value = temp_in_kelvin(value, source_temp_unit)
            updates[param_name] = kelvin_to_unit(kelvin_value, target_temp_unit)

        for param_name in REHEAT_TEMP_DIFF_PARAMS:
            value = getattr(params, param_name)
            kelvin_value = temp_diff_in_kelvin(value, source_temp_unit)
            updates[param_name] = kelvin_diff_to_unit(kelvin_value, target_temp_unit)

        for param_name in REHEAT_AIRFLOW_PARAMS:
            value = getattr(params, param_name)
            m3_per_s_value = airflow_in_m3_per_s(value, source_airflow_unit)
            updates[param_name] = m3_per_s_to_airflow(
                m3_per_s_value, target_airflow_unit
            )

        return params.model_copy(update=updates)
