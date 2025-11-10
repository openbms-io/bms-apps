"""Mock templates data extracted from NREL 223P templates for Phase 1 validation.

Data source: docs/feature-development/ashrae-223p-ai-g36-integration/nrel-templates/
"""

from datetime import UTC, datetime

from ..dto.mappings_dto import MappingsResponseDTO
from ..dto.spaces_dto import SpaceInstanceDTO
from ..dto.templates_dto import (
    SpaceTypeDTO,
    TemplateDeviceDTO,
    TemplatePropertyDTO,
    TemplatesResponseDTO,
    TemplateSystemDTO,
)

MOCK_TEMPLATES = TemplatesResponseDTO(
    systems=[
        TemplateSystemDTO(
            id="urn:ashrae:223p:VAVReheatTerminalUnit",
            label="VAV Reheat Terminal Unit",
            description="Variable Air Volume terminal unit with hot water reheat coil",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Damper",
                    label="Damper",
                    description="Air damper for flow control",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:DamperCommand",
                            label="Damper Command",
                            propertyType="quantifiable",
                            description="Damper position command (%)",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:DamperFeedback",
                            label="Damper Feedback",
                            propertyType="quantifiable",
                            description="Damper position feedback (%)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:HeatingCoil",
                    label="Heating Coil",
                    description="Hot water heating coil",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:SupplyWaterTemperature",
                            label="Supply Water Temperature",
                            propertyType="quantifiable",
                            description="Hot water supply temperature (°C)",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:ReturnWaterTemperature",
                            label="Return Water Temperature",
                            propertyType="quantifiable",
                            description="Hot water return temperature (°C)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:AirFlowSensor",
                    label="Air Flow Sensor",
                    description="Supply air flow measurement",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:AirFlow",
                            label="Air Flow",
                            propertyType="quantifiable",
                            description="Air flow rate (CFM)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:TemperatureSensor",
                    label="Temperature Sensor",
                    description="Air temperature measurement",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:AirTemperature",
                            label="Air Temperature",
                            propertyType="quantifiable",
                            description="Air temperature (°C)",
                        ),
                    ],
                ),
            ],
        ),
        TemplateSystemDTO(
            id="urn:ashrae:223p:AirHandlingUnit",
            label="Air Handling Unit (Makeup Air)",
            description="Makeup air unit with heating, cooling, and heat recovery",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Fan",
                    label="Supply Fan",
                    description="Supply air fan with VFD",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:StartCommand",
                            label="Start Command",
                            propertyType="enumerated",
                            description="Fan start/stop command",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:RunStatus",
                            label="Run Status",
                            propertyType="enumerated",
                            description="Fan run status",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:VFDSpeed",
                            label="VFD Speed",
                            propertyType="quantifiable",
                            description="Fan speed as % of max frequency",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:VFDCurrent",
                            label="VFD Current",
                            propertyType="quantifiable",
                            description="VFD current (A)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:OutsideAirDamper",
                    label="Outside Air Damper",
                    description="Outside air intake damper",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:DamperCommand",
                            label="Damper Command",
                            propertyType="quantifiable",
                            description="Damper position command (%)",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:DamperFeedback",
                            label="Damper Feedback",
                            propertyType="quantifiable",
                            description="Damper position feedback (%)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:CoolingCoil",
                    label="Cooling Coil",
                    description="Chilled water cooling coil",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:EnteringAirTemperature",
                            label="Entering Air Temperature",
                            propertyType="quantifiable",
                            description="Entering air temperature (°C)",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:LeavingAirTemperature",
                            label="Leaving Air Temperature",
                            propertyType="quantifiable",
                            description="Leaving air temperature (°C)",
                        ),
                    ],
                ),
            ],
        ),
        TemplateSystemDTO(
            id="urn:ashrae:223p:ChilledWaterSystem",
            label="Chilled Water System",
            description="Central chilled water distribution system",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Pump",
                    label="Chilled Water Pump",
                    description="Chilled water circulation pump",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:StartCommand",
                            label="Start Command",
                            propertyType="enumerated",
                            description="Pump start/stop command",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:RunStatus",
                            label="Run Status",
                            propertyType="enumerated",
                            description="Pump run status",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:VFDPower",
                            label="VFD Power",
                            propertyType="quantifiable",
                            description="VFD power consumption (kW)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Valve",
                    label="Bypass Valve",
                    description="Chilled water bypass valve",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:StartCommand",
                            label="Start Command",
                            propertyType="enumerated",
                            description="Valve open/close command",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:RunStatus",
                            label="Run Status",
                            propertyType="enumerated",
                            description="Valve status",
                        ),
                    ],
                ),
            ],
        ),
        TemplateSystemDTO(
            id="urn:ashrae:223p:HotWaterSystem",
            label="Hot Water System",
            description="Central hot water distribution system",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Pump",
                    label="Hot Water Pump",
                    description="Hot water circulation pump",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:StartCommand",
                            label="Start Command",
                            propertyType="enumerated",
                            description="Pump start/stop command",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:RunStatus",
                            label="Run Status",
                            propertyType="enumerated",
                            description="Pump run status",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:DomesticWaterHeater",
                    label="Domestic Water Heater",
                    description="Domestic hot water heater",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:WaterTemperature",
                            label="Water Temperature",
                            propertyType="quantifiable",
                            description="Hot water temperature (°C)",
                        ),
                    ],
                ),
            ],
        ),
        TemplateSystemDTO(
            id="urn:ashrae:223p:FanCoilUnit",
            label="Fan Coil Unit",
            description="Fan coil unit with heating and cooling",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Fan",
                    label="Fan",
                    description="FCU fan",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:StartCommand",
                            label="Start Command",
                            propertyType="enumerated",
                            description="Fan start/stop command",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:RunStatus",
                            label="Run Status",
                            propertyType="enumerated",
                            description="Fan run status",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:TemperatureSensor",
                    label="Zone Temperature Sensor",
                    description="Zone air temperature sensor",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:AirTemperature",
                            label="Zone Temperature",
                            propertyType="quantifiable",
                            description="Zone air temperature (°C)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:HumiditySensor",
                    label="Zone Humidity Sensor",
                    description="Zone relative humidity sensor",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:RelativeHumidity",
                            label="Relative Humidity",
                            propertyType="quantifiable",
                            description="Relative humidity (%RH)",
                        ),
                    ],
                ),
            ],
        ),
        TemplateSystemDTO(
            id="urn:ashrae:223p:ExhaustAirUnit",
            label="Exhaust Air Unit",
            description="Exhaust air unit with heat recovery",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:ExhaustFan",
                    label="Exhaust Fan",
                    description="Exhaust air fan",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:StartCommand",
                            label="Start Command",
                            propertyType="enumerated",
                            description="Fan start/stop command",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:VFDFault",
                            label="VFD Fault",
                            propertyType="enumerated",
                            description="VFD fault status",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Filter",
                    label="Air Filter",
                    description="Exhaust air filter",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:DifferentialPressure",
                            label="Differential Pressure",
                            propertyType="quantifiable",
                            description="Filter differential pressure (in H2O)",
                        ),
                    ],
                ),
            ],
        ),
        TemplateSystemDTO(
            id="urn:ashrae:223p:HeatRecoverySystem",
            label="Heat Recovery System",
            description="Heat recovery water loop between MAU and EAU",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:HeatRecoveryCoil",
                    label="Heat Recovery Coil",
                    description="Heat recovery coil",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:EnteringAirTemperature",
                            label="Entering Air Temperature",
                            propertyType="quantifiable",
                            description="Entering air temperature (°C)",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:LeavingAirTemperature",
                            label="Leaving Air Temperature",
                            propertyType="quantifiable",
                            description="Leaving air temperature (°C)",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Pump",
                    label="Heat Recovery Pump",
                    description="Heat recovery water circulation pump",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:WaterStaticPressure",
                            label="Water Static Pressure",
                            propertyType="quantifiable",
                            description="Water static pressure (PSI)",
                        ),
                    ],
                ),
            ],
        ),
        TemplateSystemDTO(
            id="urn:ashrae:223p:UnitHeater",
            label="Unit Heater",
            description="Standalone unit heater with fan and heating coil",
            devices=[
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:Fan",
                    label="Fan",
                    description="Unit heater fan",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:StartCommand",
                            label="Start Command",
                            propertyType="enumerated",
                            description="Fan start/stop command",
                        ),
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:RunStatus",
                            label="Run Status",
                            propertyType="enumerated",
                            description="Fan run status",
                        ),
                    ],
                ),
                TemplateDeviceDTO(
                    id="urn:ashrae:223p:HeatingCoil",
                    label="Heating Coil",
                    description="Hot water heating coil",
                    properties=[
                        TemplatePropertyDTO(
                            id="urn:ashrae:223p:SupplyWaterTemperature",
                            label="Supply Water Temperature",
                            propertyType="quantifiable",
                            description="Hot water supply temperature (°C)",
                        ),
                    ],
                ),
            ],
        ),
    ],
    spaceTypes=[
        SpaceTypeDTO(
            id="urn:ashrae:223p:PhysicalSpace",
            label="Physical Space",
            description="Physical location where equipment is installed",
        ),
        SpaceTypeDTO(
            id="urn:ashrae:223p:DomainSpace",
            label="Domain Space (HVAC Zone)",
            description="Functional HVAC zone that equipment serves or controls",
        ),
    ],
)

MOCK_MAPPINGS = MappingsResponseDTO(
    projectId="demo-project-001",
    mappings={},
)

MOCK_SPACES: list[SpaceInstanceDTO] = [
    SpaceInstanceDTO(
        id="urn:bms:PhysicalSpace:building-a-floor-3-mech-room",
        spaceTypeId="urn:ashrae:223p:PhysicalSpace",
        label="Building A - Floor 3 - Mechanical Room",
        createdAt=datetime.now(UTC).isoformat(),
    ),
    SpaceInstanceDTO(
        id="urn:bms:PhysicalSpace:building-a-floor-2-room-201",
        spaceTypeId="urn:ashrae:223p:PhysicalSpace",
        label="Building A - Floor 2 - Room 201",
        createdAt=datetime.now(UTC).isoformat(),
    ),
    SpaceInstanceDTO(
        id="urn:bms:DomainSpace:building-a-north-wing-hvac-zone",
        spaceTypeId="urn:ashrae:223p:DomainSpace",
        label="Building A - North Wing HVAC Zone",
        createdAt=datetime.now(UTC).isoformat(),
    ),
]
