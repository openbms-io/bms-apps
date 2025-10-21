"""
Integration tests for monitor_all_devices with real database.
Only mocks BAC0 library network operations.
"""

import pytest
from unittest.mock import Mock, AsyncMock, patch
from src.controllers.monitoring.monitor import BACnetMonitor
from src.models.bacnet_config import (
    BacnetDeviceInfo,
    BacnetObjectInfo,
    insert_bacnet_config_json,
)
from src.models.controller_points import get_points_to_upload
from src.actors.messages.message_type import BacnetReaderConfig


def create_mock_bac0_instance_for_success():
    """Create mock BAC0.lite instance for successful reads"""
    mock_bacnet = Mock()

    # Create mock PropertyIdentifier objects
    class MockPropertyIdentifier:
        def __init__(self, attr_name):
            self.attr = attr_name

    # Create mock StatusFlags object
    class MockStatusFlags:
        def __str__(self):
            return self.value

        def __init__(self, value):
            self.value = value

    # BAC0 readMultiple returns format: {"analog-input,1": [(<PropId>, (value, <PropId>)), ...], ...}
    mock_bacnet.readMultiple = AsyncMock(
        return_value={
            "analog-input,1": [
                (
                    MockPropertyIdentifier("present-value"),
                    (72.5, MockPropertyIdentifier("present-value")),
                ),
                (
                    MockPropertyIdentifier("status-flags"),
                    (
                        [
                            1,
                            0,
                            0,
                            0,
                        ],  # BACnet StatusFlags: [IN_ALARM, FAULT, OVERRIDDEN, OUT_OF_SERVICE]
                        MockPropertyIdentifier("status-flags"),
                    ),
                ),
                (
                    MockPropertyIdentifier("event-state"),
                    ("normal", MockPropertyIdentifier("event-state")),
                ),
                (
                    MockPropertyIdentifier("reliability"),
                    ("no-fault-detected", MockPropertyIdentifier("reliability")),
                ),
            ],
            "analog-output,2": [
                (
                    MockPropertyIdentifier("present-value"),
                    (55.0, MockPropertyIdentifier("present-value")),
                ),
                (
                    MockPropertyIdentifier("status-flags"),
                    (
                        [0, 0, 0, 0],
                        MockPropertyIdentifier("status-flags"),
                    ),  # All normal
                ),
                (
                    MockPropertyIdentifier("event-state"),
                    ("normal", MockPropertyIdentifier("event-state")),
                ),
            ],
        }
    )

    mock_bacnet.who_is = AsyncMock(
        return_value=[
            Mock(
                iAmDeviceIdentifier=("device", 123),
                vendorID=8,
                pduSource="192.168.1.100",
            )
        ]
    )

    mock_bacnet._disconnect = AsyncMock()

    return mock_bacnet


def create_mock_bac0_instance_for_bulk_failure():
    """Create mock BAC0.lite instance where bulk read fails"""
    mock_bacnet = Mock()

    # Create mock PropertyIdentifier objects
    class MockPropertyIdentifier:
        def __init__(self, attr_name):
            self.attr = attr_name

    # Create mock StatusFlags object
    class MockStatusFlags:
        def __str__(self):
            return self.value

        def __init__(self, value):
            self.value = value

    call_count = [0]

    def read_multiple_side_effect(*args, **kwargs):
        call_count[0] += 1
        if call_count[0] == 1:
            raise Exception("Bulk read failed")
        else:
            # Fallback calls read_properties for ["presentValue"] only
            # (because object configuration only has presentValue)
            # Returns: list with single value tuple
            return [(72.5,)]

    mock_bacnet.readMultiple = AsyncMock(side_effect=read_multiple_side_effect)
    mock_bacnet.who_is = AsyncMock(return_value=[])
    mock_bacnet._disconnect = AsyncMock()

    return mock_bacnet


def create_mock_bac0_instance_for_complete_failure():
    """Create mock BAC0.lite instance where all reads fail except final present value"""
    mock_bacnet = Mock()

    call_count = [0]

    def read_multiple_side_effect(*args, **kwargs):
        call_count[0] += 1
        if call_count[0] <= 2:
            # First two calls fail (bulk read + read_properties)
            raise Exception("Read failed")
        else:
            # Third call succeeds (read_present_value returns raw value)
            return 72.5

    mock_bacnet.readMultiple = AsyncMock(side_effect=read_multiple_side_effect)
    mock_bacnet.who_is = AsyncMock(return_value=[])
    mock_bacnet._disconnect = AsyncMock()

    return mock_bacnet


class TestMonitorAllDevicesIntegration:
    """Integration tests for monitor_all_devices with real database"""

    @pytest.mark.isolate
    @pytest.mark.asyncio
    async def test_monitor_all_devices_success_flow(self, cleanup_database):
        """Test: Successful bulk read with all properties"""

        test_device = BacnetDeviceInfo(
            vendor_id=8,
            device_id=123,
            controller_ip_address="192.168.1.100",
            controller_id="test-controller",
            object_list=[
                BacnetObjectInfo(
                    type="analogInput",
                    point_id=1,
                    iot_device_point_id="point-1",
                    properties={"presentValue": 72.5, "statusFlags": [1, 0, 0, 0]},
                ),
                BacnetObjectInfo(
                    type="analogOutput",
                    point_id=2,
                    iot_device_point_id="point-2",
                    properties={"presentValue": 55.0},
                ),
            ],
            configured_by_reader=1,
        )
        await insert_bacnet_config_json([test_device])

        mock_bac0_instance = create_mock_bac0_instance_for_success()

        with patch("BAC0.connect", return_value=mock_bac0_instance):
            reader_config = BacnetReaderConfig(
                id="reader-1",
                ip_address="192.168.1.50",
                subnet_mask=24,
                bacnet_device_id=999,
                port=47808,
                bbmd_enabled=False,
                is_active=True,
            )
            from src.models.bacnet_wrapper_manager import bacnet_wrapper_manager

            await bacnet_wrapper_manager.initialize_readers([reader_config])

            monitor = BACnetMonitor()
            await monitor.monitor_all_devices()

            await bacnet_wrapper_manager.cleanup()

        points = await get_points_to_upload()
        assert len(points) == 2

        point_1 = next(p for p in points if p.point_id == 1)
        assert point_1.present_value == "72.5"
        assert point_1.status_flags == "[1, 0, 0, 0]"
        assert point_1.controller_id == "test-controller"

        mock_bac0_instance.readMultiple.assert_called()

    @pytest.mark.isolate
    @pytest.mark.asyncio
    async def test_bulk_read_fails_fallback_to_individual(self, cleanup_database):
        """Test: Bulk read fails, successfully falls back to individual reads"""

        test_device = BacnetDeviceInfo(
            vendor_id=8,
            device_id=124,
            controller_ip_address="192.168.1.101",
            controller_id="test-controller-2",
            object_list=[
                BacnetObjectInfo(
                    type="analogInput",
                    point_id=1,
                    iot_device_point_id="point-3",
                    properties={"presentValue": 72.5},
                )
            ],
            configured_by_reader=1,
        )
        await insert_bacnet_config_json([test_device])

        mock_bac0_instance = create_mock_bac0_instance_for_bulk_failure()

        with patch("BAC0.connect", return_value=mock_bac0_instance):
            reader_config = BacnetReaderConfig(
                id="reader-2",
                ip_address="192.168.1.50",
                subnet_mask=24,
                bacnet_device_id=999,
                port=47808,
                bbmd_enabled=False,
                is_active=True,
            )
            from src.models.bacnet_wrapper_manager import bacnet_wrapper_manager

            await bacnet_wrapper_manager.initialize_readers([reader_config])

            monitor = BACnetMonitor()
            await monitor.monitor_all_devices()

            await bacnet_wrapper_manager.cleanup()

        points = await get_points_to_upload()
        assert len(points) == 1
        assert points[0].present_value == "72.5"

        assert mock_bac0_instance.readMultiple.call_count > 1

    @pytest.mark.isolate
    @pytest.mark.asyncio
    async def test_complete_failure_fallback_to_present_value_only(
        self, cleanup_database
    ):
        """Test: All reads fail, falls back to present value only"""

        test_device = BacnetDeviceInfo(
            vendor_id=8,
            device_id=126,
            controller_ip_address="192.168.1.103",
            controller_id="test-controller-4",
            object_list=[
                BacnetObjectInfo(
                    type="analogInput",
                    point_id=1,
                    iot_device_point_id="point-6",
                    properties={"presentValue": 72.5},
                )
            ],
            configured_by_reader=1,
        )
        await insert_bacnet_config_json([test_device])

        mock_bac0_instance = create_mock_bac0_instance_for_complete_failure()

        with patch("BAC0.connect", return_value=mock_bac0_instance):
            reader_config = BacnetReaderConfig(
                id="reader-3",
                ip_address="192.168.1.50",
                subnet_mask=24,
                bacnet_device_id=999,
                port=47808,
                bbmd_enabled=False,
                is_active=True,
            )
            from src.models.bacnet_wrapper_manager import bacnet_wrapper_manager

            await bacnet_wrapper_manager.initialize_readers([reader_config])

            monitor = BACnetMonitor()
            await monitor.monitor_all_devices()

            await bacnet_wrapper_manager.cleanup()

        points = await get_points_to_upload()
        assert len(points) == 1
        assert points[0].present_value == "72.5"
        assert points[0].error_info is not None

        # Verify readMultiple was called 3 times (bulk + individual + fallback)
        assert mock_bac0_instance.readMultiple.call_count == 3
