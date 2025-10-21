from src.models.bacnet_config import get_latest_bacnet_config_json
from src.network.rest_client import RestClient
from src.models.controller_points import get_points_to_upload, mark_points_as_uploaded
from src.models.controller_points import ControllerPointsModel
from src.dto import BacnetDiscoveredPropertiesDTO

from src.utils.logger import logger


async def upload_config(url: str, jwt_token: str):
    logger.info(f"Uploading config to {url}")
    config = await get_latest_bacnet_config_json()

    if not config or not config.bacnet_devices:
        logger.warning("No BACnet config found to upload.")
        return None

    # Transform to ControllerPoint-compatible format
    transformed_config = []
    for device in config.bacnet_devices:
        transformed_device = {
            "vendor_id": device["vendor_id"],
            "device_id": device["device_id"],
            "controller_ip_address": device["controller_ip_address"],
            "controller_id": device["controller_id"],
            "object_list": [],
        }

        for obj in device.get("object_list", []):
            # Transform properties using DTO
            properties_dto = BacnetDiscoveredPropertiesDTO.from_dict(
                obj.get("properties", {})
            )

            transformed_obj = {
                "type": obj["type"],
                "point_id": obj["point_id"],
                "iot_device_point_id": obj["iot_device_point_id"],
                "properties": properties_dto.model_dump(exclude_none=True),
            }
            transformed_device["object_list"].append(transformed_obj)

        transformed_config.append(transformed_device)

    logger.info(f"Transformed config: {len(transformed_config)} devices")

    # Upload transformed config
    async with RestClient(jwt_token=jwt_token) as rest_client:
        response = await rest_client.post(url, json={"config": transformed_config})
        if response:
            logger.info(f"Upload config response: {response.json()}")
        else:
            logger.error("Failed to upload config. No response received from server.")

    return response


async def get_points_to_publish():
    # 1. Fetch data from controller_points.py
    points = await get_points_to_upload()
    if not points:
        logger.warning("No points found to publish.")
        return None

    return points


async def mark_points_as_uploaded_in_db(points: list[ControllerPointsModel]):
    await mark_points_as_uploaded(points)
