import type { IBuildingMOTIFService } from './interfaces/buildingmotif'
import type { SystemType, DeviceType, ObservableProperty } from '../../schemas'
import mockData from '../../mocks/buildingmotif-templates.json'

/**
 * Mock BuildingMOTIF Service
 *
 * Returns static template data from JSON file without network calls.
 * Provides ASHRAE 223P templates for UI component development.
 *
 * Epic 1: Use this service for all 223P template queries
 * Epic 3: Swap to ApiBuildingMOTIFService (zero UI changes)
 *
 * @example
 * const service = new MockBuildingMOTIFService();
 * const systems = await service.getTemplates();
 * // Returns: ["VAV Reheat Terminal Unit", "Chilled Water System", ...]
 */
export class MockBuildingMOTIFService implements IBuildingMOTIFService {
  /**
   * Get all equipment types
   *
   * Returns 8 equipment types from NREL BuildingMOTIF systems.yml
   * No network call - synchronous data wrapped in Promise.
   *
   * @returns Promise resolving to array of 8 system types
   */
  async getTemplates(): Promise<SystemType[]> {
    return Promise.resolve(mockData.templates.systems as SystemType[])
  }

  /**
   * Get all device types
   *
   * Returns 18 device types from NREL BuildingMOTIF devices.yml
   * No network call - synchronous data wrapped in Promise.
   *
   * @returns Promise resolving to array of 18 device types
   */
  async getDeviceTypes(): Promise<DeviceType[]> {
    return Promise.resolve(mockData.templates.devices as DeviceType[])
  }

  /**
   * Get all observable properties
   *
   * Returns 25+ properties from NREL BuildingMOTIF properties.yml
   * Combines quantifiable (19) + enumerated (5) properties.
   * No network call - synchronous data wrapped in Promise.
   *
   * @returns Promise resolving to array of 24+ observable properties
   */
  async getObservableProperties(): Promise<ObservableProperty[]> {
    const { quantifiable, enumerated } = mockData.templates.properties
    return Promise.resolve([
      ...quantifiable,
      ...enumerated,
    ] as ObservableProperty[])
  }
}

/**
 * Singleton instance for application-wide use
 *
 * Use this exported instance instead of creating new instances.
 * Ensures consistent mock data across all components.
 *
 * @example
 * import { mockBuildingMOTIFService } from '@/domains/223p/services';
 * const systems = await mockBuildingMOTIFService.getTemplates();
 */
export const mockBuildingMOTIFService = new MockBuildingMOTIFService()
