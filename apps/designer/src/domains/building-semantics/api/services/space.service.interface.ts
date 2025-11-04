import type { SpaceDTO } from '../../schemas'

/**
 * Space Service Interface
 *
 * Manages ASHRAE 223P space groupings (rooms, zones, mechanical spaces).
 * Spaces group multiple BACnet points together for semantic organization.
 *
 * Epic 1: Implemented by MockSpaceService (sessionStorage)
 * Epic 3: Implemented by ApiSpaceService (real HTTP calls)
 *
 * UI components depend on this interface, not the implementation.
 */
export interface ISpaceService {
  /**
   * List all spaces for a project
   *
   * Returns spaces sorted by most recently used.
   * Each space includes point count for UI display.
   *
   * Epic 1: Reads from sessionStorage
   * Epic 3: Fetches from BuildingMOTIF API
   *
   * @param projectId - Current project ID
   * @returns Array of spaces with metadata
   */
  listSpaces(projectId: string): Promise<SpaceDTO[]>

  /**
   * Create a new space
   *
   * Generates URN and creates space grouping.
   * Client provides label and type, server generates ID.
   *
   * Epic 1: Generates mock URN, stores in sessionStorage
   * Epic 3: Server generates real URN via API
   *
   * @param projectId - Current project ID
   * @param rdfsLabel - Human-readable space name (e.g., "Room 201")
   * @param spaceType - Space type (PhysicalSpace, DomainSpace, etc.)
   * @returns Created space with server-generated URN
   */
  createSpace(
    projectId: string,
    rdfsLabel: string,
    spaceType: string
  ): Promise<SpaceDTO>

  /**
   * Search for existing space by label
   *
   * Case-insensitive search for exact or partial match.
   * Used to avoid creating duplicate spaces.
   *
   * @param projectId - Current project ID
   * @param label - Space label to search for
   * @returns Matching space or null if not found
   */
  searchSpace(projectId: string, label: string): Promise<SpaceDTO | null>

  /**
   * Add point to space
   *
   * Associates a BACnet point with a space.
   * Updates point count for recently used spaces list.
   *
   * @param projectId - Current project ID
   * @param spaceId - Space URN
   * @param pointId - BACnet point identifier
   */
  addPointToSpace(
    projectId: string,
    spaceId: string,
    pointId: string
  ): Promise<void>
}
