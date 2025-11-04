import type { ISpaceService } from './space.service.interface'
import type { SpaceDTO, SpaceType } from '../schemas'

/**
 * Mock Space Service
 *
 * Manages spaces in sessionStorage with mock URN generation.
 * Provides recently-used space tracking for UI combobox.
 *
 * Epic 1: Use this service for all space operations
 * Epic 3: Swap to ApiSpaceService (zero UI changes)
 *
 * @example
 * const service = new MockSpaceService();
 * const space = await service.createSpace('proj-123', 'Room 201', 'PhysicalSpace');
 * // Returns: { id: 'urn:bms:PhysicalSpace:...', rdfsLabel: 'Room 201', ... }
 */
export class MockSpaceService implements ISpaceService {
  private getStorageKey(projectId: string): string {
    return `223p-spaces:${projectId}`
  }

  async listSpaces(projectId: string): Promise<SpaceDTO[]> {
    const key = this.getStorageKey(projectId)
    const data = sessionStorage.getItem(key)
    if (!data) return []

    const spaces: SpaceDTO[] = JSON.parse(data)
    return spaces.sort((a, b) => {
      return new Date(b.createdAt).getTime() - new Date(a.createdAt).getTime()
    })
  }

  async createSpace(
    projectId: string,
    rdfsLabel: string,
    spaceType: string
  ): Promise<SpaceDTO> {
    const urn = this.generateSpaceURN(spaceType as SpaceType)

    const space: SpaceDTO = {
      id: urn,
      rdfsLabel,
      spaceType: spaceType as SpaceType,
      pointIds: [],
      createdAt: new Date(),
    }

    const spaces = await this.listSpaces(projectId)
    spaces.push(space)

    const key = this.getStorageKey(projectId)
    sessionStorage.setItem(key, JSON.stringify(spaces))

    return space
  }

  async searchSpace(
    projectId: string,
    label: string
  ): Promise<SpaceDTO | null> {
    const spaces = await this.listSpaces(projectId)
    const lowerLabel = label.toLowerCase().trim()

    return (
      spaces.find(
        (space) => space.rdfsLabel.toLowerCase().trim() === lowerLabel
      ) || null
    )
  }

  async addPointToSpace(
    projectId: string,
    spaceId: string,
    pointId: string
  ): Promise<void> {
    const spaces = await this.listSpaces(projectId)
    const space = spaces.find((s) => s.id === spaceId)

    if (space && !space.pointIds.includes(pointId)) {
      space.pointIds.push(pointId)

      const key = this.getStorageKey(projectId)
      sessionStorage.setItem(key, JSON.stringify(spaces))
    }
  }

  private generateSpaceURN(spaceType: SpaceType): string {
    const uuid = crypto.randomUUID()
    return `urn:bms:${spaceType}:space-${uuid}`
  }
}

export const mockSpaceService = new MockSpaceService()
