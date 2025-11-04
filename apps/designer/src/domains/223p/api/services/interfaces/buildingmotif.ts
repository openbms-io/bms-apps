import type {
  SystemType,
  DeviceType,
  ObservableProperty,
} from '../../../schemas'

/**
 * BuildingMOTIF Service Interface
 *
 * Defines contract for BuildingMOTIF API interaction.
 * Provides access to ASHRAE 223P templates (equipment types, device types, properties).
 *
 * Epic 1: Implemented by MockBuildingMOTIFService (static JSON data)
 * Epic 3: Implemented by ApiBuildingMOTIFService (real HTTP calls)
 *
 * UI components depend on this interface, not the implementation.
 * This enables swapping mock → real API with zero UI changes.
 */
export interface IBuildingMOTIFService {
  /**
   * Get all available equipment types (systems)
   *
   * Returns NREL BuildingMOTIF system templates.
   * Examples: "VAV Reheat Terminal Unit", "Chilled Water System"
   *
   * Epic 1: Returns 8 equipment types from systems.yml
   * Epic 3: Fetches from BuildingMOTIF API
   *
   * @returns Array of system types from NREL templates
   */
  getTemplates(): Promise<SystemType[]>

  /**
   * Get all available device types
   *
   * Returns NREL BuildingMOTIF device templates.
   * Examples: "Sensor", "Damper", "Chilled Water Valve"
   *
   * Epic 1: Returns 18 device types from devices.yml
   * Epic 3: Fetches from BuildingMOTIF API
   *
   * @returns Array of device types from NREL templates
   */
  getDeviceTypes(): Promise<DeviceType[]>

  /**
   * Get all available observable properties
   *
   * Returns NREL BuildingMOTIF property templates.
   * Includes both quantifiable (numeric) and enumerated (status) properties.
   * Examples: "air-temperature" (quantifiable), "run-status" (enumerated)
   *
   * Epic 1: Returns 25+ properties from properties.yml
   * Epic 3: Fetches from BuildingMOTIF API
   *
   * @returns Array of observable properties from NREL templates
   */
  getObservableProperties(): Promise<ObservableProperty[]>
}
