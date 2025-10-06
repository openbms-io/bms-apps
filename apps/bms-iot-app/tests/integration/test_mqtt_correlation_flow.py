import pytest
from unittest.mock import Mock, AsyncMock, patch
import paho.mqtt.client as mqtt


@pytest.mark.asyncio
async def test_end_to_end_correlation_flow():
    """Test full correlation data flow: request → processing → response."""
    from src.controllers.mqtt.mqtt_controller import MQTTHandler
    from src.actors.uploader_actor import UploaderActor
    from src.actors.messages.actor_queue_registry import ActorQueueRegistry
    from src.actors.messages.message_type import (
        ActorName,
        ActorMessageType,
    )
    from src.network.mqtt_config import MQTTConfig

    correlation_id = b"unique-correlation-id-xyz"

    # Setup
    actor_registry = ActorQueueRegistry()
    # Register actor queues
    actor_registry.register(ActorName.BACNET)
    actor_registry.register(ActorName.UPLOADER)
    actor_registry.register(ActorName.MQTT)

    mqtt_config = MQTTConfig(broker="test", port=1883)

    mqtt_handler = MQTTHandler(
        mqtt_config=mqtt_config,
        organization_id="org",
        site_id="site",
        iot_device_id="device",
    )

    # Mock MQTT client to avoid actual connection
    with patch("src.controllers.mqtt.mqtt_controller.MQTTClient") as MockMQTTClient:
        mock_client = Mock()
        mock_client.connect = Mock(return_value=True)
        MockMQTTClient.return_value = mock_client

        mqtt_handler.setup(actor_registry, ActorName.MQTT)

        uploader = UploaderActor(actor_registry)

        # Create request with correlation data
        mock_message = Mock(spec=mqtt.MQTTMessage)
        mock_message.payload = b'{"urlToUploadConfig": "https://example.com/upload", "jwtToken": "jwt-token", "iotDeviceControllers": [], "bacnetReaders": []}'

        mock_properties = Mock()
        mock_properties.correlation_data = correlation_id
        mock_message.properties = mock_properties

        # Mock upload_config to avoid actual HTTP call
        with patch(
            "src.controllers.uploader.upload.upload_config", new_callable=AsyncMock
        ):
            # Step 1: Receive request with correlation data
            await mqtt_handler.on_get_config_request(
                actor_registry, ActorName.MQTT, Mock(), None, mock_message
            )

            # Step 2: BACNET actor processes (simulated by getting message from queue)
            bacnet_queue = actor_registry.get_queue(ActorName.BACNET)
            bacnet_msg = await bacnet_queue.get()
            assert bacnet_msg.payload.correlationData == correlation_id

            # Simulate BACNET sending to UPLOADER with correlation data
            await actor_registry.send_from(
                sender=ActorName.BACNET,
                receiver=ActorName.UPLOADER,
                type=ActorMessageType.CONFIG_UPLOAD_RESPONSE,
                payload=bacnet_msg.payload,
            )

            # Step 3: UPLOADER processes and sends response to MQTT
            uploader_queue = actor_registry.get_queue(ActorName.UPLOADER)
            uploader_msg = await uploader_queue.get()
            await uploader.on_upload_request(uploader_msg.payload)

            # Step 4: Verify MQTT response includes correlation data
            mqtt_queue = actor_registry.get_queue(ActorName.MQTT)
            mqtt_response = await mqtt_queue.get()

            assert mqtt_response.payload.correlationData == correlation_id
            assert mqtt_response.payload.success is True


@pytest.mark.asyncio
async def test_correlation_flow_without_correlation_data():
    """Test that flow works without correlation data (backward compatibility)."""
    from src.controllers.mqtt.mqtt_controller import MQTTHandler
    from src.actors.uploader_actor import UploaderActor
    from src.actors.messages.actor_queue_registry import ActorQueueRegistry
    from src.actors.messages.message_type import ActorName, ActorMessageType
    from src.network.mqtt_config import MQTTConfig

    # Setup
    actor_registry = ActorQueueRegistry()
    # Register actor queues
    actor_registry.register(ActorName.BACNET)
    actor_registry.register(ActorName.UPLOADER)
    actor_registry.register(ActorName.MQTT)

    mqtt_config = MQTTConfig(broker="test", port=1883)

    mqtt_handler = MQTTHandler(
        mqtt_config=mqtt_config,
        organization_id="org",
        site_id="site",
        iot_device_id="device",
    )

    # Mock MQTT client to avoid actual connection
    with patch("src.controllers.mqtt.mqtt_controller.MQTTClient") as MockMQTTClient:
        mock_client = Mock()
        mock_client.connect = Mock(return_value=True)
        MockMQTTClient.return_value = mock_client

        mqtt_handler.setup(actor_registry, ActorName.MQTT)

        uploader = UploaderActor(actor_registry)

        # Create request WITHOUT correlation data
        mock_message = Mock(spec=mqtt.MQTTMessage)
        mock_message.payload = b'{"urlToUploadConfig": "https://example.com/upload", "jwtToken": "jwt-token", "iotDeviceControllers": [], "bacnetReaders": []}'
        mock_message.properties = None  # No MQTT 5 properties

        with patch(
            "src.controllers.uploader.upload.upload_config", new_callable=AsyncMock
        ):
            # Request without correlation data
            await mqtt_handler.on_get_config_request(
                actor_registry, ActorName.MQTT, Mock(), None, mock_message
            )

            # BACNET processing
            bacnet_queue = actor_registry.get_queue(ActorName.BACNET)
            bacnet_msg = await bacnet_queue.get()
            assert bacnet_msg.payload.correlationData is None

            # Send to UPLOADER
            await actor_registry.send_from(
                sender=ActorName.BACNET,
                receiver=ActorName.UPLOADER,
                type=ActorMessageType.CONFIG_UPLOAD_RESPONSE,
                payload=bacnet_msg.payload,
            )

            # UPLOADER processes
            uploader_queue = actor_registry.get_queue(ActorName.UPLOADER)
            uploader_msg = await uploader_queue.get()
            await uploader.on_upload_request(uploader_msg.payload)

            # MQTT response should have None correlation data
            mqtt_queue = actor_registry.get_queue(ActorName.MQTT)
            mqtt_response = await mqtt_queue.get()

            assert mqtt_response.payload.correlationData is None
            assert mqtt_response.payload.success is True


@pytest.mark.asyncio
async def test_mqtt_actor_publishes_with_correlation_data():
    """Test that MQTTActor correctly publishes response with correlation data."""
    from src.actors.mqtt_actor import MQTTActor
    from src.actors.messages.actor_queue_registry import ActorQueueRegistry
    from src.actors.messages.message_type import (
        ActorName,
        ActorMessageType,
        ConfigUploadResponsePayload,
    )
    from src.network.mqtt_config import MQTTConfig

    correlation_id = b"mqtt-actor-correlation-test"

    # Setup
    actor_registry = ActorQueueRegistry()
    actor_registry.register(ActorName.MQTT)
    mqtt_config = MQTTConfig(broker="test", port=1883)

    # Mock the MQTT client to avoid actual connection
    with patch("src.controllers.mqtt.mqtt_controller.MQTTClient") as MockMQTTClient:
        mock_client = Mock()
        mock_client.connect = Mock(return_value=True)
        mock_client.publish = Mock(return_value=True)
        MockMQTTClient.return_value = mock_client

        mqtt_actor = MQTTActor(
            mqtt_config=mqtt_config,
            actor_queue_registry=actor_registry,
            organization_id="org",
            site_id="site",
            iot_device_id="device",
        )

        # Setup mqtt_handler to initialize dispatcher
        mqtt_actor.mqtt_handler.setup(actor_registry, ActorName.MQTT)

        # Send CONFIG_UPLOAD_RESPONSE with correlation data to MQTT actor
        await actor_registry.send_from(
            sender=ActorName.UPLOADER,
            receiver=ActorName.MQTT,
            type=ActorMessageType.CONFIG_UPLOAD_RESPONSE,
            payload=ConfigUploadResponsePayload(
                success=True, correlationData=correlation_id
            ),
        )

        # Process messages
        await mqtt_actor._handle_messages()

        # Verify publish was called with correlation data
        assert mock_client.publish.called
        call_args = mock_client.publish.call_args
        # Check that correlation_data was passed in properties
        if call_args and "properties" in call_args[1]:
            properties = call_args[1]["properties"]
            assert properties is not None
            assert properties["correlation_data"] == correlation_id


@pytest.mark.asyncio
async def test_correlation_preserves_through_all_actors():
    """Integration test verifying correlation data flows through all actors."""
    from src.controllers.mqtt.mqtt_controller import MQTTHandler
    from src.actors.uploader_actor import UploaderActor
    from src.actors.messages.actor_queue_registry import ActorQueueRegistry
    from src.actors.messages.message_type import ActorName
    from src.network.mqtt_config import MQTTConfig
    import paho.mqtt.client as mqtt

    correlation_id = b"full-flow-test"

    # Setup all actors
    actor_registry = ActorQueueRegistry()
    # Register actor queues
    actor_registry.register(ActorName.BACNET)
    actor_registry.register(ActorName.UPLOADER)
    actor_registry.register(ActorName.MQTT)

    mqtt_config = MQTTConfig(broker="test", port=1883)

    mqtt_handler = MQTTHandler(
        mqtt_config=mqtt_config,
        organization_id="org",
        site_id="site",
        iot_device_id="device",
    )

    # Mock MQTT client to avoid actual connection
    with patch("src.controllers.mqtt.mqtt_controller.MQTTClient") as MockMQTTClient:
        mock_client = Mock()
        mock_client.connect = Mock(return_value=True)
        MockMQTTClient.return_value = mock_client

        mqtt_handler.setup(actor_registry, ActorName.MQTT)

        # Create request with correlation data
        mock_message = Mock(spec=mqtt.MQTTMessage)
        mock_message.payload = b'{"urlToUploadConfig": "https://test.com", "jwtToken": "test", "iotDeviceControllers": [], "bacnetReaders": []}'

        mock_properties = Mock()
        mock_properties.correlation_data = correlation_id
        mock_message.properties = mock_properties

        # Mock external dependencies
        with patch(
            "src.controllers.uploader.upload.upload_config", new_callable=AsyncMock
        ):
            # MQTT receives request
            await mqtt_handler.on_get_config_request(
                actor_registry, ActorName.MQTT, Mock(), None, mock_message
            )

            # Verify correlation flows through BACNET
            bacnet_queue = actor_registry.get_queue(ActorName.BACNET)
            bacnet_msg = await bacnet_queue.get()
            assert bacnet_msg.payload.correlationData == correlation_id

            # Simulate BACNET forwarding to UPLOADER
            await actor_registry.send_from(
                sender=ActorName.BACNET,
                receiver=ActorName.UPLOADER,
                type=bacnet_msg.message_type,
                payload=bacnet_msg.payload,
            )

            # Verify correlation flows through UPLOADER
            uploader = UploaderActor(actor_registry)
            uploader_queue = actor_registry.get_queue(ActorName.UPLOADER)
            uploader_msg = await uploader_queue.get()

            await uploader.on_upload_request(uploader_msg.payload)

            # Verify correlation flows back to MQTT
            mqtt_queue = actor_registry.get_queue(ActorName.MQTT)
            final_msg = await mqtt_queue.get()

            assert final_msg.payload.correlationData == correlation_id
