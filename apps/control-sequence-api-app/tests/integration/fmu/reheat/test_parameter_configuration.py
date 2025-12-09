import pytest

from src.adapters.fmu_adapter import FmuAdapter
from src.adapters.fmu_data.reheat_fmu_data import ReheatFMUData, ReheatOutputVar
from src.adapters.sequence_type import SequenceType
from src.dto.reheat_dto import ReheatInputs, ReheatParameters


class TestAirflowParameters:

    @pytest.mark.asyncio
    async def test_min_airflow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(minAirflow=0.25)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_max_cooling_airflow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(maxCoolingAirflow=1.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_max_heating_airflow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(maxHeatingAirflow=0.8)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_min_heating_airflow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(minHeatingAirflow=0.2)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_area_breathing_zone_flow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(areaBreathingZoneFlow=0.01)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_area_min_flow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(areaMinFlow=0.05)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_occ_min_flow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(occMinFlow=0.1)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_pop_breathing_zone_flow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(popBreathingZoneFlow=0.008)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_all_airflow_parameters_together(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(
            maxCoolingAirflow=1.0,
            maxHeatingAirflow=0.8,
            minHeatingAirflow=0.2,
            areaBreathingZoneFlow=0.01,
            areaMinFlow=0.05,
            occMinFlow=0.1,
            popBreathingZoneFlow=0.008,
        )
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestTemperatureParameters:

    @pytest.mark.asyncio
    async def test_discharge_air_temp_min_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(dischargeAirTempMin=280.15)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_max_discharge_temp_above_setpoint_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(maxDischargeTempAboveSetpoint=15.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_threshold_discharge_temp_1_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(thresholdDischargeTemp1=20.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_threshold_discharge_temp_2_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(thresholdDischargeTemp2=10.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_threshold_temp_diff_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(thresholdTempDiff=4.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_two_temp_diff_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(twoTempDiff=2.5)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestControllerGainParameters:

    @pytest.mark.asyncio
    async def test_cooling_controller_gain_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(coolingControllerGain=0.2)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_heating_controller_gain_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(heatingControllerGain=0.2)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_damper_controller_gain_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(damperControllerGain=0.8)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_valve_controller_gain_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(valveControllerGain=0.8)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestControllerTimeConstantParameters:

    @pytest.mark.asyncio
    async def test_damper_derivative_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(damperDerivativeTime=0.2)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_valve_derivative_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(valveDerivativeTime=0.2)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_cooling_integrator_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(coolingIntegratorTime=180.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_damper_integrator_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(damperIntegratorTime=400.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_heating_integrator_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(heatingIntegratorTime=180.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_valve_integrator_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(valveIntegratorTime=400.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestTimingParameters:

    @pytest.mark.asyncio
    async def test_change_rate_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(changeRate=600.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_duration_discharge_air_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(durationDischargeAir=360.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_duration_flow_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(durationFlow=90.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_duration_temp_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(durationTemp=180.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_max_suppression_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(maxSuppressionTime=2400.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_sample_period_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(samplePeriod=180.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestAlarmTimingParameters:

    @pytest.mark.asyncio
    async def test_fan_off_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(fanOffTime=900.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_leak_flow_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(leakFlowTime=900.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_low_flow_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(lowFlowTime=600.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_low_temp_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(lowTempTime=900.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_valve_close_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(valveCloseTime=1200.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_time_check_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(timeCheck=60.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_startup_time_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(startupTime=2400.0)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestMultiplierParameters:

    @pytest.mark.asyncio
    async def test_hot_water_reset_multiplier_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hotWaterResetMultiplier=1.5)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_static_pressure_multiplier_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(staticPressureMultiplier=1.5)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestZoneDistributionParameters:

    @pytest.mark.asyncio
    async def test_zone_dist_eff_cooling_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(zoneDistEffCooling=1.2)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_zone_dist_eff_heating_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(zoneDistEffHeating=0.9)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestInitialValueParameters:

    @pytest.mark.asyncio
    async def test_initial_damper_position_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(initialDamperPosition=0.1)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestSensorConfigurationParameters:

    @pytest.mark.asyncio
    async def test_has_co2_sensor_true_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasCO2Sensor=True)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_has_co2_sensor_false_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasCO2Sensor=False)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_has_hot_water_coil_true_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasHotWaterCoil=True)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_has_hot_water_coil_false_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasHotWaterCoil=False)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_has_occupancy_sensor_true_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasOccupancySensor=True)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_has_occupancy_sensor_false_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasOccupancySensor=False)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_has_window_sensor_true_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasWindowSensor=True)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_has_window_sensor_false_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(hasWindowSensor=False)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_permit_occ_standby_true_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(permitOccStandby=True)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_permit_occ_standby_false_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(permitOccStandby=False)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestControllerTypeParameters:

    @pytest.mark.asyncio
    async def test_controller_type_damper_p_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import ControllerType
        params = ReheatParameters(controllerTypeDamper=ControllerType.P)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_controller_type_damper_pi_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import ControllerType
        params = ReheatParameters(controllerTypeDamper=ControllerType.PI)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_controller_type_damper_pid_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import ControllerType
        params = ReheatParameters(controllerTypeDamper=ControllerType.PID)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_controller_type_valve_p_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import ControllerType
        params = ReheatParameters(controllerTypeValve=ControllerType.P)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_controller_type_valve_pi_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import ControllerType
        params = ReheatParameters(controllerTypeValve=ControllerType.PI)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_controller_type_valve_pid_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import ControllerType
        params = ReheatParameters(controllerTypeValve=ControllerType.PID)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestVentilationStandardParameters:

    @pytest.mark.asyncio
    async def test_ventilation_standard_ashrae_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import VentilationStandard
        params = ReheatParameters(ventilationStandard=VentilationStandard.ASHRAE62_1)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_ventilation_standard_title24_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        from src.models.reheat.enums import VentilationStandard
        params = ReheatParameters(ventilationStandard=VentilationStandard.CALIFORNIA_TITLE_24)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestHysteresisParameters:

    @pytest.mark.asyncio
    async def test_temp_hysteresis_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(tempHysteresis=0.5)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_loop_hysteresis_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(loopHysteresis=0.02)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_flow_hysteresis_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(flowHysteresis=0.005)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_damper_position_hysteresis_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(damperPositionHysteresis=0.01)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None

    @pytest.mark.asyncio
    async def test_valve_position_hysteresis_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(valvePositionHysteresis=0.01)
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None


class TestDefaultParameters:

    @pytest.mark.asyncio
    async def test_default_parameters_work(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters()
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None
        assert ReheatOutputVar.DAMPER_POSITION in outputs

    @pytest.mark.asyncio
    async def test_no_parameters_work(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=None)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None
        assert ReheatOutputVar.DAMPER_POSITION in outputs


class TestAllParametersTogether:

    @pytest.mark.asyncio
    async def test_all_55_parameters_accepted(
        self, fmu_adapter: FmuAdapter, base_inputs: ReheatInputs
    ):
        params = ReheatParameters(
            # Airflow parameters (8)
            minAirflow=0.25,
            maxCoolingAirflow=1.0,
            maxHeatingAirflow=0.8,
            minHeatingAirflow=0.2,
            areaBreathingZoneFlow=0.01,
            areaMinFlow=0.05,
            occMinFlow=0.1,
            popBreathingZoneFlow=0.008,
            # Temperature parameters (6)
            dischargeAirTempMin=280.15,
            maxDischargeTempAboveSetpoint=15.0,
            thresholdDischargeTemp1=20.0,
            thresholdDischargeTemp2=10.0,
            thresholdTempDiff=4.0,
            twoTempDiff=2.5,
            # Controller gains (4)
            coolingControllerGain=0.2,
            heatingControllerGain=0.2,
            damperControllerGain=0.8,
            valveControllerGain=0.8,
            # Controller time constants (6)
            damperDerivativeTime=0.2,
            valveDerivativeTime=0.2,
            coolingIntegratorTime=180.0,
            damperIntegratorTime=400.0,
            heatingIntegratorTime=180.0,
            valveIntegratorTime=400.0,
            # Timing parameters (6)
            changeRate=600.0,
            durationDischargeAir=360.0,
            durationFlow=90.0,
            durationTemp=180.0,
            maxSuppressionTime=2400.0,
            samplePeriod=180.0,
            # Alarm timing (7)
            fanOffTime=900.0,
            leakFlowTime=900.0,
            lowFlowTime=600.0,
            lowTempTime=900.0,
            valveCloseTime=1200.0,
            timeCheck=60.0,
            startupTime=2400.0,
            # Multipliers (2)
            hotWaterResetMultiplier=1.5,
            staticPressureMultiplier=1.5,
            # Zone distribution (2)
            zoneDistEffCooling=1.2,
            zoneDistEffHeating=0.9,
            # Initial values (1)
            initialDamperPosition=0.1,
            # Boolean parameters (5)
            permitOccStandby=True,
            hasCO2Sensor=True,
            hasHotWaterCoil=True,
            hasOccupancySensor=True,
            hasWindowSensor=True,
            # Controller types (3)
            # controllerTypeDamper, controllerTypeValve, ventilationStandard use defaults
            # Hysteresis parameters (5)
            tempHysteresis=0.5,
            loopHysteresis=0.02,
            flowHysteresis=0.005,
            damperPositionHysteresis=0.01,
            valvePositionHysteresis=0.01,
        )
        fmu_data = ReheatFMUData(inputs=base_inputs, parameters=params)
        instance_id = fmu_adapter.create_fmu_instance(SequenceType.REHEAT, fmu_data)

        outputs = await fmu_adapter.step(instance_id, fmu_data, step_size=60.0)

        assert outputs is not None
        assert ReheatOutputVar.DAMPER_POSITION in outputs
