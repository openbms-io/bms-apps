"""Integration tests for API Documentation (Story 1.16).

Tests verify acceptance criteria:
  AC1: All endpoints have docstrings visible in /docs
  AC2: Request/Response schemas include field descriptions
  AC3: Examples provided for each endpoint
  AC4: Error responses documented
"""

import pytest


class TestG36EndpointsInOpenAPI:

    def test_create_instance_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/vav-reheat/instances" in paths
        assert "post" in paths["/api/v1/g36/vav-reheat/instances"]

    def test_get_instance_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/vav-reheat/instances/{instance_id}" in paths
        assert "get" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}"]

    def test_update_instance_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/vav-reheat/instances/{instance_id}" in paths
        assert "put" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}"]

    def test_step_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/vav-reheat/instances/{instance_id}/step" in paths
        assert "post" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}/step"]

    def test_delete_instance_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/vav-reheat/instances/{instance_id}" in paths
        assert "delete" in paths["/api/v1/g36/vav-reheat/instances/{instance_id}"]

    def test_validate_endpoint_in_openapi(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()
        paths = openapi["paths"]

        assert "/api/v1/g36/validate" in paths
        assert "post" in paths["/api/v1/g36/validate"]


class TestEndpointDocstrings:

    def test_create_instance_has_description(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances"]["post"]
        assert "description" in endpoint or "summary" in endpoint
        desc = endpoint.get("description", "") or endpoint.get("summary", "")
        assert len(desc) > 0

    def test_get_instance_has_description(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances/{instance_id}"]["get"]
        assert "description" in endpoint or "summary" in endpoint

    def test_step_has_description(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances/{instance_id}/step"]["post"]
        assert "description" in endpoint or "summary" in endpoint


class TestErrorResponseDocumentation:

    def test_get_instance_has_404_documented(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances/{instance_id}"]["get"]
        assert "responses" in endpoint
        assert "404" in endpoint["responses"]

    def test_update_instance_has_404_documented(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances/{instance_id}"]["put"]
        assert "responses" in endpoint
        assert "404" in endpoint["responses"]

    def test_update_instance_has_422_documented(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances/{instance_id}"]["put"]
        assert "responses" in endpoint
        assert "422" in endpoint["responses"]

    def test_step_has_404_documented(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances/{instance_id}/step"]["post"]
        assert "responses" in endpoint
        assert "404" in endpoint["responses"]

    def test_step_has_500_documented(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances/{instance_id}/step"]["post"]
        assert "responses" in endpoint
        assert "500" in endpoint["responses"]

    def test_create_instance_has_500_documented(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        endpoint = openapi["paths"]["/api/v1/g36/vav-reheat/instances"]["post"]
        assert "responses" in endpoint
        assert "500" in endpoint["responses"]


class TestErrorResponseModel:

    def test_error_response_schema_exists(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schemas = openapi["components"]["schemas"]
        assert "ErrorResponse" in schemas

    def test_error_response_has_error_field(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["ErrorResponse"]
        assert "properties" in schema
        assert "error" in schema["properties"]

    def test_error_response_has_detail_field(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["ErrorResponse"]
        assert "properties" in schema
        assert "detail" in schema["properties"]


class TestFieldDescriptions:

    def test_step_request_has_field_descriptions(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["StepRequest"]
        props = schema["properties"]
        assert "stepSize" in props
        assert "description" in props["stepSize"]

    def test_reheat_inputs_request_has_field_descriptions(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["ReheatInputsRequest"]
        props = schema["properties"]
        assert "zoneTemperature" in props
        assert "description" in props["zoneTemperature"]

    def test_reheat_outputs_has_field_descriptions(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["ReheatOutputs"]
        props = schema["properties"]
        assert "damperPosition" in props
        assert "description" in props["damperPosition"]


class TestExamples:

    def test_step_request_step_size_has_example(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["StepRequest"]
        props = schema["properties"]
        step_size = props["stepSize"]
        has_example = "example" in step_size or "examples" in step_size
        assert has_example

    def test_reheat_inputs_has_examples(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["ReheatInputsRequest"]
        props = schema["properties"]
        zone_temp = props["zoneTemperature"]
        has_example = "example" in zone_temp or "examples" in zone_temp
        assert has_example

    def test_reheat_outputs_has_examples(self, integration_client):
        response = integration_client.get("/openapi.json")
        openapi = response.json()

        schema = openapi["components"]["schemas"]["ReheatOutputs"]
        props = schema["properties"]
        damper = props["damperPosition"]
        has_example = "example" in damper or "examples" in damper
        assert has_example
