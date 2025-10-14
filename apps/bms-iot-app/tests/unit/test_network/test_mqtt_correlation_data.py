import pytest
from unittest.mock import Mock, patch
import paho.mqtt.client as mqtt
from src.network.mqtt_command_dispatcher import MqttCommandDispatcher
from src.network.mqtt_client import MQTTClient
from packages.mqtt_topics.topics_loader import CommandNameEnum
from src.controllers.mqtt.mqtt_controller import MQTTHandler
from src.actors.messages.actor_queue_registry import ActorQueueRegistry
from src.actors.messages.message_type import ActorName
from src.network.mqtt_config import MQTTConfig


class TestMQTTCorrelationData:
    """Test MQTT 5.0 correlation data handling."""

    @pytest.fixture
    def mock_mqtt_client(self):
        mock_client = Mock(spec=MQTTClient)
        mock_client.publish = Mock(return_value=True)
        return mock_client

    @pytest.fixture
    def dispatcher(self, mock_mqtt_client):
        return MqttCommandDispatcher(
            mqtt_client=mock_mqtt_client,
            organization_id="test-org",
            site_id="test-site",
            iot_device_id="test-device",
        )

    def test_publish_response_with_correlation_data(self, dispatcher, mock_mqtt_client):
        """Test publish_response includes correlation_data in MQTT 5 properties."""
        test_correlation_data = b"test-correlation-id-12345"
        test_payload = {"success": True, "message": "Config uploaded"}

        dispatcher.publish_response(
            CommandNameEnum.get_config,
            test_payload,
            correlation_data=test_correlation_data,
        )

        # Verify publish was called with correlation data
        mock_mqtt_client.publish.assert_called_once()
        call_args = mock_mqtt_client.publish.call_args

        # Check properties parameter
        properties = call_args[1].get("properties")
        assert properties is not None
        assert properties["correlation_data"] == test_correlation_data

    def test_publish_response_without_correlation_data(
        self, dispatcher, mock_mqtt_client
    ):
        """Test publish_response works without correlation_data (backward compatibility)."""
        test_payload = {"success": True}

        dispatcher.publish_response(CommandNameEnum.get_config, test_payload)

        # Verify publish was called without properties
        mock_mqtt_client.publish.assert_called_once()
        call_args = mock_mqtt_client.publish.call_args

        # Should not have properties parameter or it should be None
        properties = call_args[1].get("properties")
        assert properties is None

    def test_publish_response_passes_correlation_data_to_mqtt_client(
        self, dispatcher, mock_mqtt_client
    ):
        """Test that correlation data is properly passed to MQTT client publish method."""
        test_correlation_data = b"test-correlation-bytes"
        test_payload = {"test": "data"}

        dispatcher.publish_response(
            CommandNameEnum.get_config,
            test_payload,
            correlation_data=test_correlation_data,
        )

        # Verify publish was called with correlation_data in properties
        mock_mqtt_client.publish.assert_called_once()
        call_kwargs = mock_mqtt_client.publish.call_args[1]

        # Verify properties contains correlation_data
        assert "properties" in call_kwargs
        assert call_kwargs["properties"]["correlation_data"] == test_correlation_data


class TestMQTTControllerCorrelation:
    """Test correlation data extraction in mqtt_controller.py"""

    @pytest.mark.asyncio
    async def test_extract_correlation_data_from_message(self):
        """Test extracting correlationData from MQTT 5.0 message properties."""
        # Create mock message with MQTT 5 properties
        mock_message = Mock(spec=mqtt.MQTTMessage)
        mock_message.payload = b'{"urlToUploadConfig": "https://test.com", "jwtToken": "test-jwt", "iotDeviceControllers": [], "bacnetReaders": []}'

        # Mock MQTT 5.0 properties
        mock_properties = Mock()
        mock_properties.CorrelationData = b"test-correlation-123"
        mock_message.properties = mock_properties

        # Setup handler with mocked MQTT client
        mqtt_config = MQTTConfig(broker="test", port=1883)
        handler = MQTTHandler(
            mqtt_config=mqtt_config,
            organization_id="org",
            site_id="site",
            iot_device_id="device",
        )

        actor_registry = ActorQueueRegistry()
        # Register BACNET queue to receive messages
        actor_registry.register(ActorName.BACNET)

        # Mock MQTT client to avoid actual connection
        with patch("src.controllers.mqtt.mqtt_controller.MQTTClient") as MockMQTTClient:
            mock_client = Mock()
            mock_client.connect = Mock(return_value=True)
            MockMQTTClient.return_value = mock_client

            handler.setup(actor_registry, ActorName.MQTT)

            # Call the handler
            await handler.on_get_config_request(
                actor_registry, ActorName.MQTT, Mock(), None, mock_message
            )

            # Verify correlation data was extracted and added to payload
            queue = actor_registry.get_queue(ActorName.BACNET)
            assert not queue.empty()

            actor_message = await queue.get()
            assert actor_message.payload.correlationData == b"test-correlation-123"

    @pytest.mark.asyncio
    async def test_handles_missing_correlation_data(self):
        """Test handling message without correlation_data (MQTT 3.1.1 compatibility)."""
        # Create mock message without properties
        mock_message = Mock(spec=mqtt.MQTTMessage)
        mock_message.payload = b'{"urlToUploadConfig": "https://test.com", "jwtToken": "test-jwt", "iotDeviceControllers": [], "bacnetReaders": []}'
        mock_message.properties = None  # No MQTT 5 properties

        mqtt_config = MQTTConfig(broker="test", port=1883)
        handler = MQTTHandler(
            mqtt_config=mqtt_config,
            organization_id="org",
            site_id="site",
            iot_device_id="device",
        )

        actor_registry = ActorQueueRegistry()
        # Register BACNET queue to receive messages
        actor_registry.register(ActorName.BACNET)

        # Mock MQTT client to avoid actual connection
        with patch("src.controllers.mqtt.mqtt_controller.MQTTClient") as MockMQTTClient:
            mock_client = Mock()
            mock_client.connect = Mock(return_value=True)
            MockMQTTClient.return_value = mock_client

            handler.setup(actor_registry, ActorName.MQTT)

            # Should not raise error
            await handler.on_get_config_request(
                actor_registry, ActorName.MQTT, Mock(), None, mock_message
            )

            # Verify correlation data is None
            queue = actor_registry.get_queue(ActorName.BACNET)
            actor_message = await queue.get()
            assert actor_message.payload.correlationData is None

    @pytest.mark.asyncio
    async def test_correlation_data_logged(self):
        """Test that correlation data extraction is logged."""
        mock_message = Mock(spec=mqtt.MQTTMessage)
        mock_message.payload = b'{"urlToUploadConfig": "https://test.com", "jwtToken": "test-jwt", "iotDeviceControllers": [], "bacnetReaders": []}'

        mock_properties = Mock()
        mock_properties.CorrelationData = b"logged-correlation"
        mock_message.properties = mock_properties

        mqtt_config = MQTTConfig(broker="test", port=1883)
        handler = MQTTHandler(
            mqtt_config=mqtt_config,
            organization_id="org",
            site_id="site",
            iot_device_id="device",
        )

        actor_registry = ActorQueueRegistry()
        # Register BACNET queue to receive messages
        actor_registry.register(ActorName.BACNET)

        # Mock MQTT client to avoid actual connection
        with patch("src.controllers.mqtt.mqtt_controller.MQTTClient") as MockMQTTClient:
            mock_client = Mock()
            mock_client.connect = Mock(return_value=True)
            MockMQTTClient.return_value = mock_client

            handler.setup(actor_registry, ActorName.MQTT)

            with patch("src.controllers.mqtt.mqtt_controller.logger") as mock_logger:
                await handler.on_get_config_request(
                    actor_registry, ActorName.MQTT, Mock(), None, mock_message
                )

                # Check that correlation data was logged
                info_calls = [call[0][0] for call in mock_logger.info.call_args_list]
                assert any("correlationData" in str(call) for call in info_calls)
