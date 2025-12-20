import pytest

from src.models.reheat.parameters import ReheatParameters
from src.utils.unit_conversion import TemperatureUnit


@pytest.fixture
def kelvin_params() -> ReheatParameters:
    return ReheatParameters(temperatureUnit=TemperatureUnit.KELVIN)


def make_kelvin_params(**kwargs) -> ReheatParameters:
    return ReheatParameters(temperatureUnit=TemperatureUnit.KELVIN, **kwargs)
