import type { SpaceDTO, SpaceType } from '../adapters/ashrae-223p/schemas'

const STORAGE_KEY_PREFIX = '223p-spaces:'

function getStorageKey(projectId: string): string {
  return `${STORAGE_KEY_PREFIX}${projectId}`
}

function generateSpaceURN(spaceType: SpaceType): string {
  const uuid = crypto.randomUUID()
  return `urn:bms:${spaceType}:space-${uuid}`
}

export const spaces223pApi = {
  async listSpaces(projectId: string): Promise<SpaceDTO[]> {
    const key = getStorageKey(projectId)
    const data = sessionStorage.getItem(key)
    if (!data) return []

    const spaces: SpaceDTO[] = JSON.parse(data)
    return spaces.sort((a, b) => {
      return new Date(b.createdAt).getTime() - new Date(a.createdAt).getTime()
    })
  },

  async createSpace(
    projectId: string,
    rdfsLabel: string,
    spaceType: SpaceType
  ): Promise<SpaceDTO> {
    const urn = generateSpaceURN(spaceType)

    const space: SpaceDTO = {
      id: urn,
      rdfsLabel,
      spaceType,
      pointIds: [],
      createdAt: new Date(),
    }

    const spaces = await this.listSpaces(projectId)
    spaces.push(space)

    const key = getStorageKey(projectId)
    sessionStorage.setItem(key, JSON.stringify(spaces))

    return space
  },

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
  },

  async addPointToSpace(
    projectId: string,
    spaceId: string,
    pointId: string
  ): Promise<void> {
    const spaces = await this.listSpaces(projectId)
    const space = spaces.find((s) => s.id === spaceId)

    if (space && !space.pointIds.includes(pointId)) {
      space.pointIds.push(pointId)

      const key = getStorageKey(projectId)
      sessionStorage.setItem(key, JSON.stringify(spaces))
    }
  },
}
